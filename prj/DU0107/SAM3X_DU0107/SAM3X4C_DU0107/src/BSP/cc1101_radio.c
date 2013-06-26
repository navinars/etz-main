
/* ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 *   MRFI (Minimal RF Interface)
 *   Radios: CC2500, CC1100, CC1101
 *   Primary code file for supported radios.
 * ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 */

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "asf.h"
#include "cc1101_defs.h"
#include "cc1101_port.h"
#include "cc1101_radio.h"


/* ------------------------------------------------------------------------------------------------
 *                                          Defines
 * ------------------------------------------------------------------------------------------------
 */

/* GDO functionality */
#define MRFI_GDO_SYNC           6
#define MRFI_GDO_CCA            9
#define MRFI_GDO_PA_PD          27  /* low when transmit is active, low during sleep */
#define MRFI_GDO_LNA_PD         28  /* low when receive is active, low during sleep */

/* GDO0 output pin configuration */
#define MRFI_SETTING_IOCFG0     MRFI_GDO_SYNC

/* Main Radio Control State Machine control configuration:
 * - Remain RX state after RX
 * - Go to IDLE after TX
 * - RSSI below threshold and NOT receiving.
 */
#define MRFI_SETTING_MCSM1      0x3C

/* Main Radio Control State Machine control configuration:
 * Auto Calibrate - when going from IDLE to RX/TX
 * PO_TIMEOUT is extracted from SmartRF setting.
 * XOSC is OFF in Sleep state.
 */
#define MRFI_SETTING_MCSM0      (0x10 | (SMARTRF_SETTING_MCSM0 & ((1 <<2)|(1<<3))))

/*
 *  Packet Length - Setting for maximum allowed packet length.
 *  The PKTLEN setting does not include the length field but maximum frame size does.
 *  Subtract length field size from maximum frame size to get value for PKTLEN.
 */
#define MRFI_SETTING_PKTLEN     0xff	//(MRFI_MAX_FRAME_SIZE - MRFI_LENGTH_FIELD_SIZE)

/* Packet automation control - Original value except WHITE_DATA is extracted from SmartRF setting. */
#define MRFI_SETTING_PKTCTRL0   (0x05 | (SMARTRF_SETTING_PKTCTRL0 & (1 << 6)))

/* FIFO threshold - this register has fields that need to be configured for the CC1101 */
#define MRFI_SETTING_FIFOTHR    (0x07 | (SMARTRF_SETTING_FIFOTHR & ((1<<4)|(1<<5)|(1<<6))))

/* ------------------------------------------------------------------------------------------------
 *                                           Macros
 * ------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------
 *                                    Local Constants
 * ------------------------------------------------------------------------------------------------
 */
static const uint8_t mrfiRadioCfg[][2] =
{
  /* internal radio configuration */
  {  IOCFG0,    MRFI_SETTING_IOCFG0       },
  {  MCSM1,     MRFI_SETTING_MCSM1        }, /* CCA mode, RX_OFF_MODE and TX_OFF_MODE */
  {  MCSM0,     MRFI_SETTING_MCSM0        }, /* AUTO_CAL and XOSC state in sleep */
  {  PKTLEN,    MRFI_SETTING_PKTLEN       },
  {  PKTCTRL0,  MRFI_SETTING_PKTCTRL0     },
#ifdef MRFI_CC1101
  {  FIFOTHR,   MRFI_SETTING_FIFOTHR      },
#endif

  /* imported SmartRF radio configuration */
  {  FSCTRL1,   SMARTRF_SETTING_FSCTRL1   },
  {  FSCTRL0,   SMARTRF_SETTING_FSCTRL0   },
  {  FREQ2,     SMARTRF_SETTING_FREQ2     },
  {  FREQ1,     SMARTRF_SETTING_FREQ1     },
  {  FREQ0,     SMARTRF_SETTING_FREQ0     },
  {  MDMCFG4,   SMARTRF_SETTING_MDMCFG4   },
  {  MDMCFG3,   SMARTRF_SETTING_MDMCFG3   },
  {  MDMCFG2,   SMARTRF_SETTING_MDMCFG2   },
  {  MDMCFG1,   SMARTRF_SETTING_MDMCFG1   },
  {  MDMCFG0,   SMARTRF_SETTING_MDMCFG0   },
  {  DEVIATN,   SMARTRF_SETTING_DEVIATN   },
  {  FOCCFG,    SMARTRF_SETTING_FOCCFG    },
  {  BSCFG,     SMARTRF_SETTING_BSCFG     },
  {  AGCCTRL2,  SMARTRF_SETTING_AGCCTRL2  },
  {  AGCCTRL1,  SMARTRF_SETTING_AGCCTRL1  },
  {  AGCCTRL0,  SMARTRF_SETTING_AGCCTRL0  },
  {  FREND1,    SMARTRF_SETTING_FREND1    },
  {  FREND0,    SMARTRF_SETTING_FREND0    },
  {  FSCAL3,    SMARTRF_SETTING_FSCAL3    },
  {  FSCAL2,    SMARTRF_SETTING_FSCAL2    },
  {  FSCAL1,    SMARTRF_SETTING_FSCAL1    },
  {  FSCAL0,    SMARTRF_SETTING_FSCAL0    },
  {  TEST2,     SMARTRF_SETTING_TEST2     },
  {  TEST1,     SMARTRF_SETTING_TEST1     },
  {  TEST0,     SMARTRF_SETTING_TEST0     },
};

/* ------------------------------------------------------------------------------------------------
 *                                       Local Prototypes
 * ------------------------------------------------------------------------------------------------
 */

/* ------------------------------------------------------------------------------------------------
 *                                       Local Variables
 * ------------------------------------------------------------------------------------------------
 */
static uint8_t mrfiRadioState = MRFI_RADIO_STATE_UNKNOWN;


/*-------------------------------------------------------------------------------------------------
 * @fn          radio_init
 *
 * @brief       Initialize radio.
 *
 * @param       none
 *
 * @return      none
 *
 */
void radio_init(void)
{
	
	/* Initial radio state is IDLE state */
	mrfiRadioState = MRFI_RADIO_STATE_IDLE;

//	radioSpiInit();													// SPI modle init in main.c
	
	/* pulse CSn low then high */
	MRFI_SPI_DRIVE_CSN_LOW();
	Mrfi_DelayUsec(10);
	MRFI_SPI_DRIVE_CSN_HIGH();

	/* hold CSn high for at least 40 microseconds */
	Mrfi_DelayUsec(40);
}

