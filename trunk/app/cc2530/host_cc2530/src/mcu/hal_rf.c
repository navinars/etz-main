/***********************************************************************************

  Filename:       hal_rf.c

  Description:    CC2530 radio interface.

***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "hal_board.h"
#include "hal_mcu.h"
#include "hal_int.h"
#include "hal_rf.h"
#include "hal_led.h"
#include "util.h"
#include "string.h"
#include "sfr-bits.h"


/***********************************************************************************
* CONSTANTS AND DEFINES
*/

// Chip revision
#define REV_A                      0x01
#define CHIPREVISION              REV_A

// CC2530 RSSI Offset
#define RSSI_OFFSET                  73
#define RSSI_OFFSET_LNA_HIGHGAIN     79
#define RSSI_OFFSET_LNA_LOWGAIN      67

// Various radio settings
#define AUTO_ACK                   0x20
#define AUTO_CRC                   0x40

// MDMTEST1 (0x61B9) ¨C Test Register for Modem
#define MODULATION_MODE				0x02

#define FRAME_FILTER_EN				0x01


// TXPOWER values
#if CC2530_PG1
#define CC2530_TXPOWER_MIN_3_DBM   0x88
#define CC2530_TXPOWER_0_DBM       0x32
#define CC2530_TXPOWER_4_DBM       0xF7
#else
#define CC2530_TXPOWER_MIN_3_DBM   0xB5
#define CC2530_TXPOWER_0_DBM       0xD5
#define CC2530_TXPOWER_4_DBM       0xF5
#endif

// RF interrupt flags
#define IRQ_TXDONE                 0x02
#define IRQ_RXPKTDONE              0x40

// Selected strobes
#define ISRXON()                st(RFST = 0xE3;)
#define ISTXON()                st(RFST = 0xE9;)
#define ISTXONCCA()             st(RFST = 0xEA;)
#define ISRFOFF()               st(RFST = 0xEF;)
#define ISFLUSHRX()             st(RFST = 0xED;)
#define ISFLUSHTX()             st(RFST = 0xEE;)

// other files
#define CCA_THRES_USER_GUIDE          0xF8
#define CCA_THRES_ALONE               0xFC   /* -4-76=-80dBm when CC2530 operated alone or with CC2591 in LGM */
#define CCA_THR_HGM                   0x06   /* 6-76=-70dBm when CC2530 operated with CC2591 in HGM */
#define CORR_THR                      0x14

#ifdef CC2530_RF_CONF_CCA_THRES
#define CC2530_RF_CCA_THRES CC2530_RF_CONF_CCA_THRES
#else
#define CC2530_RF_CCA_THRES CCA_THRES_USER_GUIDE /* User guide recommendation */
#endif /* CC2530_RF_CONF_CCA_THRES */

// CC2590-CC2591 support
#if INCLUDE_PA==2591

// Support for PA/LNA
#define HAL_PA_LNA_INIT()

// Select CC2591 RX high gain mode
#define HAL_PA_LNA_RX_HGM() st( uint8 i; P0_7 = 1; for (i=0; i<8; i++) asm("NOP"); )

// Select CC2591 RX low gain mode
#define HAL_PA_LNA_RX_LGM() st( uint8 i; P0_7 = 0; for (i=0; i<8; i++) asm("NOP"); )

// TX power lookup index
#define HAL_RF_TXPOWER_0_DBM          0
#define HAL_RF_TXPOWER_13_DBM         1
#define HAL_RF_TXPOWER_16_DBM         2
#define HAL_RF_TXPOWER_18_DBM         3
#define HAL_RF_TXPOWER_20_DBM         4

// TX power values
#define CC2530_91_TXPOWER_0_DBM       0x25
#define CC2530_91_TXPOWER_13_DBM      0x85
#define CC2530_91_TXPOWER_16_DBM      0xA5
#define CC2530_91_TXPOWER_18_DBM      0xC5
#define CC2530_91_TXPOWER_20_DBM      0xE5

#else // dummy macros when not using CC2591

#define HAL_PA_LNA_INIT()
#define HAL_PA_LNA_RX_LGM()
#define HAL_PA_LNA_RX_HGM()

#define HAL_RF_TXPOWER_MIN_3_DBM  0
#define HAL_RF_TXPOWER_0_DBM      1
#define HAL_RF_TXPOWER_4_DBM	  2

#endif


/***********************************************************************************
* GLOBAL DATA
*/
#if INCLUDE_PA==2591
static const menuItem_t pPowerSettings[] =
{
  "0dBm", HAL_RF_TXPOWER_0_DBM,
  "13dBm", HAL_RF_TXPOWER_13_DBM,
  "16dBm", HAL_RF_TXPOWER_16_DBM,
  "18dBm", HAL_RF_TXPOWER_18_DBM,
  "20dBm", HAL_RF_TXPOWER_20_DBM
};
#else
static const menuItem_t pPowerSettings[] =
{
  "-3dBm", HAL_RF_TXPOWER_MIN_3_DBM,
  "0dBm", HAL_RF_TXPOWER_0_DBM,
  "4dBm", HAL_RF_TXPOWER_4_DBM
};
#endif

const menu_t powerMenu =
{
  pPowerSettings,
  N_ITEMS(pPowerSettings)
};

/***********************************************************************************
* LOCAL DATA
*/
#ifndef MRFI
static ISR_FUNC_PTR pfISR= NULL;
#endif
static uint8 rssiOffset = RSSI_OFFSET;

/***********************************************************************************
* GLOBAL FUNCTIONS
*/
static void halPaLnaInit(void);


/***********************************************************************************
* @fn      halRfInit
*
* @brief   Power up, sets default tuning settings, enables autoack, enables random
*          generator.
*
* @param   none
*
* @return  SUCCESS always (for interface compatibility)
*/
uint8 halRfInit(void)
{
#if CC2530_RF_LOW_POWER_RX
	/* Reduce RX power consumption current to 20mA at the cost of sensitivity */
	RXCTRL = 0x00;
	FSCTRL = 0x50;
#else
	RXCTRL = 0x3F;
	FSCTRL = 0x55;
#endif

	// Set CCA threshold value.
	CCACTRL0 = CC2530_RF_CCA_THRES;

    // Disable auto ack and auto crc.
    FRMCTRL0 &=~(AUTO_ACK | AUTO_CRC);

	// Disable IEEE 802.15.4 compliant mode.
	MDMTEST1 &=~MODULATION_MODE;
	
	// Disable RX mode frame filter
	FRMFILT0 &=~FRAME_FILTER_EN;
	
    // Recommended RX settings
	/*
	* According to the user guide, these registers must be updated from their
	* defaults for optimal performance
	*
	* Table 23-6, Sec. 23.15.1, p. 259
	*/
	TXFILTCFG = 0x09; /* TX anti-aliasing filter */
	AGCCTRL1 = 0x15;  /* AGC target value */
	FSCAL1 = 0x00;    /* Reduce the VCO leakage */

    // Enable random generator -> Not implemented yet
	random_init();
	
    // Enable CC2591 with High Gain Mode
    halPaLnaInit();
	
    // Enable RX interrupt
    halRfEnableRxInterrupt();

    return SUCCESS;
}


/***********************************************************************************
* @fn      halRfGetChipId
*
* @brief   Get chip id
*
* @param   none
*
* @return  uint8 - result
*/
uint8 halRfGetChipId(void)
{
    return CHIPID;
}


/***********************************************************************************
* @fn      halRfGetChipVer
*
* @brief   Get chip version
*
* @param   none
*
* @return  uint8 - result
*/
uint8 halRfGetChipVer(void)
{
    // return major revision (4 upper bits)
    return CHVER>>4;
}

/***********************************************************************************
* @fn      halRfGetRandomByte
*
* @brief   Return random byte
*
* @param   none
*
* @return  uint8 - random byte
*/
uint16 halRfGetRandomByte(void)
{
	uint16 rand;
	
	/* Clock the RNG LSFR once */
	ADCCON1 |= ADCCON1_RCTRL0;
	
	rand = (RNDH << 8);
	rand += RNDL;
	
	return (rand);
}

/*---------------------------------------------------------------------------*/
/**
 * \brief      Seed the cc253x random number generator.
 * \param seed Ignored. It's here because the function prototype is in core.
 *
 *             We form a seed for the RNG by sampling IF_ADC as
 *             discussed in the user guide.
 *             Seeding with this method should not be done during
 *             normal radio operation. Thus, use this function before
 *             initialising the network.
 */
void random_init(void)
{
	int i;
	uint16 seed = 0;
	
	/* Make sure the RNG is on */
	ADCCON1 &= ~(ADCCON1_RCTRL1 | ADCCON1_RCTRL0);
	
	/* Infinite RX */
	FRMCTRL0 = FRMCTRL0_RX_MODE1;
	
	/* Turn RF on */
	ISRXON();
	
	/* Wait until (user guide sec. 23.12, p 239) "the chip has been in RX long
	* enough for the transients to have died out. A convenient way to do this is
	* to wait for the RSSI-valid signal to go high." */
	while(!(RSSISTAT & RSSISTAT_RSSI_VALID));
	
	/*
	* Form the seed by concatenating bits from IF_ADC in the RF receive path.
	* Keep sampling until we have read at least 16 bits AND the seed is valid
	*
	* Invalid seeds are 0x0000 and 0x8003 - User Guide (sec. 14.2.2 p. 146):
	* "Note that a seed value of 0x0000 or 0x8003 always leads to an unchanged
	* value in the LFSR after clocking, as no values are pushed in via in_bit
	* (see Figure 14-1); hence, neither of these seed values should not be used
	* for random-number generation."
	*/
	i = 0;
	while(i < 16 || (seed == 0x0000 || seed == 0x8003)) {
		seed = (seed << 1) | (RFRND & RFRND_IRND);
		seed <<= 1;
		i++;
	}
	
	/* High byte first */
	RNDL = seed & 0xFF;
	RNDL = seed >> 8;
	
	/* RF Off. NETSTACK_RADIO.init() will sort out normal RF operation */
	ISRFOFF();
	
	/* Disable Infinite RX.*/
	FRMCTRL0 &=~FRMCTRL0_RX_MODE1;
}

/***********************************************************************************
* @fn      halRfGetRssiOffset
*
* @brief   Return RSSI Offset
*
* @param   none
*
* @return  uint8 - RSSI offset
*/
uint8 halRfGetRssiOffset(void)
{
    return rssiOffset;
}

/***********************************************************************************
* @fn      halRfSetChannel
*
* @brief   Set RF channel in the 2.4GHz band. The Channel must be in the range 11-26,
*          11= 2005 MHz, channel spacing 5 MHz.
*
* @param   channel - logical channel number
*
* @return  none
*/
void halRfSetChannel(uint8 channel)
{
    FREQCTRL = (MIN_CHANNEL + (channel - MIN_CHANNEL) * CHANNEL_SPACING);
}


/***********************************************************************************
* @fn      halRfSetShortAddr
*
* @brief   Write short address to chip
*
* @param   none
*
* @return  none
*/
void halRfSetShortAddr(uint16 shortAddr)
{
    SHORT_ADDR0 = LO_UINT16(shortAddr);
    SHORT_ADDR1 = HI_UINT16(shortAddr);
}


/***********************************************************************************
* @fn          halRfSetExtAddr
*
* @brief       Set chip IEEE MAC address
*
* @param       none
*
* @return      none
*/
void  halRfSetExtAddr(const uint8* extAddr)
{
	EXT_ADDR0 = *(extAddr++);
	EXT_ADDR1 = *(extAddr++);
	EXT_ADDR2 = *(extAddr++);
	EXT_ADDR3 = *(extAddr++);
	EXT_ADDR4 = *(extAddr++);
	EXT_ADDR5 = *(extAddr++);
	EXT_ADDR6 = *(extAddr++);
	EXT_ADDR7 = *extAddr;
}

/***********************************************************************************
* @fn      halRfSetPanId
*
* @brief   Write PAN Id to chip
*
* @param   none
*
* @return  none
*/
void halRfSetPanId(uint16 panId)
{
    PAN_ID0 = LO_UINT16(panId);
    PAN_ID1 = HI_UINT16(panId);
}


/***********************************************************************************
* @fn      halRfSetPower
*
* @brief   Set TX output power
*
* @param   uint8 power - power level: TXPOWER_MIN_4_DBM, TXPOWER_0_DBM,
*                        TXPOWER_4_DBM
*
* @return  uint8 - SUCCESS or FAILED
*/
uint8 halRfSetTxPower(uint8 power)
{
    uint8 n;

    switch(power)
    {
#if INCLUDE_PA==2591
    case HAL_RF_TXPOWER_0_DBM: n = CC2530_91_TXPOWER_0_DBM; break;
    case HAL_RF_TXPOWER_13_DBM: n = CC2530_91_TXPOWER_13_DBM; break;
    case HAL_RF_TXPOWER_16_DBM: n = CC2530_91_TXPOWER_16_DBM; break;
    case HAL_RF_TXPOWER_18_DBM: n = CC2530_91_TXPOWER_18_DBM; break;
    case HAL_RF_TXPOWER_20_DBM: n = CC2530_91_TXPOWER_20_DBM; break;
#else
    case HAL_RF_TXPOWER_MIN_3_DBM: n = CC2530_TXPOWER_MIN_3_DBM; break;
    case HAL_RF_TXPOWER_0_DBM: n = CC2530_TXPOWER_0_DBM; break;
    case HAL_RF_TXPOWER_4_DBM: n = CC2530_TXPOWER_4_DBM; break;
#endif
    default:
        return FAILED;
    }

    // Set TX power
    TXPOWER = n;

    return SUCCESS;
}


/***********************************************************************************
* @fn      halRfSetGain
*
* @brief   Set gain mode - only applicable for units with CC2590/91.
*
* @param   uint8 - gain mode
*
* @return  none
*/
void halRfSetGain(uint8 gainMode)
{
    if (gainMode==HAL_RF_GAIN_LOW)
	{
        HAL_PA_LNA_RX_LGM();
        rssiOffset = RSSI_OFFSET_LNA_LOWGAIN;
    }
	else
	{
        HAL_PA_LNA_RX_HGM();
        rssiOffset = RSSI_OFFSET_LNA_HIGHGAIN;
    }
}

/***********************************************************************************
* @fn      halRfWriteTxBuf
*
* @brief   Write to TX buffer
*
* @param   uint8* pData - buffer to write
*          uint8 length - number of bytes
*
* @return  none
*/
void halRfWriteTxBuf(uint8* pData, uint8 length)
{
    uint8 i;

    ISFLUSHTX();          											/* Making sure that the TX FIFO is empty.*/

    RFIRQF1 = ~IRQ_TXDONE;   										/* Clear TX done interrupt.*/

    for(i=0;i<length;i++){											/* Insert data*/
        RFD = pData[i];
    }
}


/***********************************************************************************
* @fn      halRfAppendTxBuf
*
* @brief   Write to TX buffer
*
* @param   uint8* pData - buffer to write
*          uint8 length - number of bytes
*
* @return  none
*/
void halRfAppendTxBuf(uint8* pData, uint8 length)
{
    uint8 i;

	/*
	* When we transmit in very quick bursts, make sure previous transmission
	* is not still in progress before re-writing to the TX FIFO
	*/
	while(FSMSTAT1 & FSMSTAT1_TX_ACTIVE);
	
    // Insert data
    for(i=0;i<length;i++){
        RFD = pData[i];
    }
}


/***********************************************************************************
* @fn      halRfReadRxBuf
*
* @brief   Read RX buffer
*
* @param   uint8* pData - data buffer. This must be allocated by caller.
*          uint8 length - number of bytes
*
* @return  none
*/
void halRfReadRxBuf(uint8* pData, uint8 length)
{
    // Read data
    while (length>0) {
        *pData++= RFD;
        length--;
    }
}

/***********************************************************************************
* @fn      halRfTransmit
*
* @brief   Transmit frame with Clear Channel Assessment.
*
* @param   none
*
* @return  uint8 - SUCCESS or FAILED
*/
int halRfTransmit(void)
{
    uint8 status;

	/* Check channel clear.*/
	if(!(FSMSTAT1 & FSMSTAT1_CCA))
	{
		return FAILED;
	}
	
	while(FSMSTAT1 & FSMSTAT1_SFD);

	halLedSet(1);
    ISTXON(); // Sending

	// Waiting for transmission to finish
//	while(!(RFIRQF1 & IRQ_TXDONE) );
	while(FSMSTAT1 & FSMSTAT1_TX_ACTIVE);
	
//	RFIRQF1 = ~IRQ_TXDONE;
    status= SUCCESS;

	halLedClear(1);
    return status;
}

/***********************************************************************************
* @fn      halRfReceiveOn
*
* @brief   Turn receiver on
*
* @param   none
*
* @return  none
*/
void halRfReceiveOn(void)
{
    ISFLUSHRX();     // Making sure that the TX FIFO is empty.
    ISRXON();
}

/***********************************************************************************
* @fn      halRfReceiveOff
*
* @brief   Turn receiver off
*
* @param   none
*
* @return  none
*/
void halRfReceiveOff(void)
{
    ISRFOFF();
    ISFLUSHRX();    // Making sure that the TX FIFO is empty.
}


/***********************************************************************************
* @fn      halRfDisableRxInterrupt
*
* @brief   Clear and disable RX interrupt.
*
* @param   none
*
* @return  none
*/
void halRfDisableRxInterrupt(void)
{
    // disable RXPKTDONE interrupt
    RFIRQM0 &= ~BV(6);
    // disable general RF interrupts
    IEN2 &= ~BV(0);
}


/***********************************************************************************
* @fn      halRfEnableRxInterrupt
*
* @brief   Enable RX interrupt.
*
* @param   none
*
* @return  none
*/
void halRfEnableRxInterrupt(void)
{
    // enable RXPKTDONE interrupt
    RFIRQM0 |= BV(6);
    // enable general RF interrupts
    IEN2 |= BV(0);
}


/***********************************************************************************
* @fn      halRfRxInterruptConfig
*
* @brief   Configure RX interrupt.
*
* @param   none
*
* @return  none
*/
void halRfRxInterruptConfig(ISR_FUNC_PTR pf)
{
    uint8 x;
    HAL_INT_LOCK(x);
    pfISR= pf;
    HAL_INT_UNLOCK(x);
}


/***********************************************************************************
* @fn      halRfWaitTransceiverReady
*
* @brief   Wait until the transciever is ready (SFD inactive).
*
* @param   none
*
* @return  none
*/
void halRfWaitTransceiverReady(void)
{
    // Wait for SFD not active and TX_Active not active
    while (FSMSTAT1 & (BV(1) | BV(5) ));
}

/***********************************************************************************
* @fn      halRfWaitReceiveReady
*
* @brief   Wait until the Receieve is ready (SFD inactive).
*
* @param   none
*
* @return  none
*/
void halRfWaitReceiveReady(void)
{
    // Wait for SFD not active and RX_Active not active
    while (FSMSTAT1 & (BV(0) | BV(4) ));
}

/************************************************************************************
* @fn          rfIsr
*
* @brief       Interrupt service routine that handles RFPKTDONE interrupt.
*
* @param       none
*
* @return      none
*/
HAL_ISR_FUNCTION( rfIsr, RF_VECTOR )
{
    uint8 x;

    HAL_INT_LOCK(x);
	
    if( RFIRQF0 & IRQ_RXPKTDONE )
    {
        if(pfISR){
            (*pfISR)();              // Execute the custom ISR
        }
        S1CON = 0;                   // Clear general RF interrupt flag
        RFIRQF0 &= ~IRQ_RXPKTDONE;   // Clear RXPKTDONE interrupt
    }
    HAL_INT_UNLOCK(x);
}

/***********************************************************************************
* LOCAL FUNCTIONS
*/
static void halPaLnaInit(void)
{
#if INCLUDE_PA==2591
    // Initialize CC2591 to RX high gain mode
    static uint8 fFirst= TRUE;

    if(fFirst) {
        AGCCTRL1  = 0x15;
        FSCAL1 = 0x0;
        RFC_OBS_CTRL0 = 0x68;
        RFC_OBS_CTRL1 = 0x6A;
        OBSSEL1 = 0xFB;
        OBSSEL4 = 0xFC;
        P0DIR |= 0x80;
        halRfSetGain(HAL_RF_GAIN_HIGH);
    }

#else // do nothing
#endif
}

