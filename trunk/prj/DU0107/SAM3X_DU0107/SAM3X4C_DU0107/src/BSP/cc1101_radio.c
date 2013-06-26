
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
#define DUMMY_BYTE                  0xDB

#define READ_BIT                    0x80
#define BURST_BIT                   0x40

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
 * @fn          spiRegAccess
 *
 * @brief       Read value from radio register.
 *
 * @param       none
 *
 * @return      none
 *
 */
static uint8_t spiRegAccess(uint8_t addrByte, uint8_t writeValue)
{
	uint8_t readValue;
	
	/* disable interrupts that use SPI */
//	MRFI_SPI_ENTER_CRITICAL_SECTION(s);
	
	MRFI_SPI_DRIVE_CSN_LOW();
	
	/* send register address byte, the read/write bit is already configured */
	mrfiSpiWriteByte(addrByte);
	
	/*
	*  Send the byte value to write.  If this operation is a read, this value
	*  is not used and is just dummy data.  Wait for SPI access to complete.
	*/
	readValue = mrfiSpiWriteByte(writeValue);
	
	/* turn off chip select; enable interrupts that call SPI functions */
	MRFI_SPI_DRIVE_CSN_HIGH();
//	MRFI_SPI_EXIT_CRITICAL_SECTION(s);
	
	/* return the register value */
	return(readValue);
}

/*-------------------------------------------------------------------------------------------------
 * @fn          mrfiSpiReadReg
 *
 * @brief       Read value from radio register.
 *
 * @param       none
 *
 * @return      none
 *
 */
static uint8_t mrfiSpiReadReg(uint8_t addr)
{
	/*
	*  The burst bit is set to allow access to read-only status registers.
	*  This does not affect normal register reads.
	*/
	return( spiRegAccess(addr | BURST_BIT | READ_BIT, DUMMY_BYTE) );
}

/*-------------------------------------------------------------------------------------------------
 * @fn          mrfiSpiWriteReg
 *
 * @brief       Initialize radio.
 *
 * @param       none
 *
 * @return      none
 *
 */
static void mrfiSpiWriteReg(uint8_t addr, uint8_t value)
{
	spiRegAccess(addr, value);
}


/**************************************************************************************************
 * @fn          mrfiSpiCmdStrobe
 *
 * @brief       Send command strobe to the radio.  Returns status byte read during transfer
 *              of strobe command.
 *
 * @param       addr - address of register to strobe
 *
 * @return      status byte of radio
 **************************************************************************************************
 */
uint8_t mrfiSpiCmdStrobe(uint8_t addr)
{
	uint8_t statusByte;

	/* disable interrupts that use SPI */
//	MRFI_SPI_ENTER_CRITICAL_SECTION(s);

	/* turn chip select "off" and then "on" to clear any current SPI access */
	MRFI_SPI_DRIVE_CSN_LOW();

	/* send the command strobe, wait for SPI access to complete */
	statusByte = mrfiSpiWriteByte(addr);

	/* read the readio status byte returned by the command strobe */
	

	/* turn off chip select; enable interrupts that call SPI functions */
	MRFI_SPI_DRIVE_CSN_HIGH();
//	MRFI_SPI_EXIT_CRITICAL_SECTION(s);

	/* return the status byte */
	return(statusByte);
}

/**************************************************************************************************
 * @fn          MRFI_RxOn
 *
 * @brief       Turn on the receiver.  No harm is done if this function is called when
 *              receiver is already on.
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
void Mrfi_RxModeOn(void)
{
	/* clear any residual receive interrupt */
//	MRFI_CLEAR_SYNC_PIN_INT_FLAG();

	/* send strobe to enter receive mode */
	mrfiSpiCmdStrobe( SRX );

	/* enable receive interrupts */
//	MRFI_ENABLE_SYNC_PIN_INT();
}

/**************************************************************************************************
 * @fn          MRFI_RxOn
 *
 * @brief       Turn on the receiver.  No harm is done if this function is called when
 *              receiver is already on.
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
void Mrfi_RxModeOff(void)
{
	/* clear any residual receive interrupt */
//	MRFI_CLEAR_SYNC_PIN_INT_FLAG();

	/* send strobe to enter receive mode */
	mrfiSpiCmdStrobe( SFRX );

	/* enable receive interrupts */
//	MRFI_ENABLE_SYNC_PIN_INT();
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SetLogicalChannel
 *
 * @brief       Change radio.
 *
 * @param       none
 *
 * @return      none
 *
 */
void MRFI_SetLogicalChannel(uint8_t chan)
{
	/* make sure radio is off before changing channels */
	Mrfi_RxModeOff();

	mrfiSpiWriteReg( CHANNR, chan );

	/* turn radio back on if it was on before channel change */
	if(mrfiRadioState == MRFI_RADIO_STATE_RX)
	{
		Mrfi_RxModeOn();
	}
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SetRFPwr
 *
 * @brief       Change radio.
 *
 * @param       none
 *
 * @return      none
 *
 */
void MRFI_SetRFPwr(uint8_t idx) 
{
	/* make sure radio is off before changing power levels */
	Mrfi_RxModeOff();

	mrfiSpiWriteReg( PA_TABLE0, idx);

	/* turn radio back on if it was on before power level change */
	if(mrfiRadioState == MRFI_RADIO_STATE_RX)
	{
		Mrfi_RxModeOn();
	}
}

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
	
	/* pull CSn low and wait for SO to go low */
	MRFI_SPI_DRIVE_CSN_LOW();
	while (MRFI_SPI_SO_IS_HIGH());
	
	/* send the command strobe, wait for SPI access to complete */
	mrfiSpiWriteByte(SRES);
	
	/* wait for SO to go low again, reset is complete at that point */
	while (MRFI_SPI_SO_IS_HIGH());

	/* return CSn pin to its default high level */
	MRFI_SPI_DRIVE_CSN_HIGH();
	
	/* initialize radio registers */
	{
		uint8_t i;

		for (i=0; i<(sizeof(mrfiRadioCfg)/sizeof(mrfiRadioCfg[0])); i++)
		{
			mrfiSpiWriteReg(mrfiRadioCfg[i][0], mrfiRadioCfg[i][1]);
		}
	}
	
	/* Initial radio state is IDLE state */
	mrfiRadioState = MRFI_RADIO_STATE_IDLE;

	/* set default channel */
	MRFI_SetLogicalChannel( 0 );
	
	/* set default power */
	MRFI_SetRFPwr(RF_TxPower_5dbm);

	Mrfi_RxModeOn();												// Put the radio in RX state.
	
	/* Turn off RF. */
	Mrfi_RxModeOff();
	
	mrfiSpiWriteReg(IOCFG0, MRFI_GDO_SYNC);							// Set SYNC signal interrupt.
	
	Mrfi_RxModeOn();
	
	BSP_ENABLE_INTERRUPTS();
}

