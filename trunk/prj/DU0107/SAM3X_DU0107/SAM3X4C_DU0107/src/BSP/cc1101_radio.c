
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

/* ------------------------------------------------------------------------------------------------
 *                                           Macros
 * ------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------
 *                                    Local Constants
 * ------------------------------------------------------------------------------------------------
 */

/* ------------------------------------------------------------------------------------------------
 *                                       Local Prototypes
 * ------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------
 *                                       Local Variables
 * ------------------------------------------------------------------------------------------------
 */
static uint8_t mrfiRadioState = MRFI_RADIO_STATE_UNKNOWN;


// Product = CC1100
// Crystal accuracy = 40 ppm
// X-tal frequency = 26 MHz
// RF output power = 0 dBm
// RX filterbandwidth = 540.000000 kHz
// Deviation = 0.000000
// Return state:  Return to RX state upon leaving either TX or RX
// Datarate = 250.000000 kbps
// Modulation = (7) MSK
// Manchester enable = (0) Manchester disabled
// RF Frequency = 868.000000 MHz
// Channel spacing = 199.951172 kHz
// Channel number = 0
// Optimization = Sensitivity
// Sync mode = (3) 30/32 sync word bits detected
// Format of RX/TX data = (0) Normal mode, use FIFOs for RX and TX
// CRC operation = (1) CRC calculation in TX and CRC check in RX enabled
// Forward Error Correction = (0) FEC disabled
// Length configuration = (1) Variable length packets, packet length configured by the first received byte after sync word.
// Packetlength = 255
// Preamble count = (2)  4 bytes
// Append status = 1
// Address check = (0) No address check
// FIFO autoflush = 0
// Device address = 0
// GDO0 signal selection = ( 6) Asserts when sync word has been sent / received, and de-asserts at the end of the packet
// GDO2 signal selection = (11) Serial Clock

void writeRFSettings(void)
{
	// Write register settings
	Mrfi_SpiWriteReg(TI_CCxxx0_IOCFG2,   0x0B); // GDO2 output pin config.
	Mrfi_SpiWriteReg(TI_CCxxx0_IOCFG0,   0x06); // GDO0 output pin config.
	Mrfi_SpiWriteReg(TI_CCxxx0_PKTLEN,   0xFF); // Packet length.
	Mrfi_SpiWriteReg(TI_CCxxx0_PKTCTRL1, 0x04); // Packet automation control.
	Mrfi_SpiWriteReg(TI_CCxxx0_PKTCTRL0, 0x05); // Packet automation control.
	Mrfi_SpiWriteReg(TI_CCxxx0_ADDR,     0x00); // Device address.
	Mrfi_SpiWriteReg(TI_CCxxx0_CHANNR,   0x00); // Channel number.
	Mrfi_SpiWriteReg(TI_CCxxx0_FSCTRL1,  0x0B); // Freq synthesizer control.
	Mrfi_SpiWriteReg(TI_CCxxx0_FSCTRL0,  0x00); // Freq synthesizer control.
	Mrfi_SpiWriteReg(TI_CCxxx0_FREQ2,    0x21); // Freq control word, high byte
	Mrfi_SpiWriteReg(TI_CCxxx0_FREQ1,    0x62); // Freq control word, mid byte.
	Mrfi_SpiWriteReg(TI_CCxxx0_FREQ0,    0x76); // Freq control word, low byte.
	Mrfi_SpiWriteReg(TI_CCxxx0_MDMCFG4,  0x2D); // Modem configuration.
	Mrfi_SpiWriteReg(TI_CCxxx0_MDMCFG3,  0x3B); // Modem configuration.
	Mrfi_SpiWriteReg(TI_CCxxx0_MDMCFG2,  0x73); // Modem configuration.
	Mrfi_SpiWriteReg(TI_CCxxx0_MDMCFG1,  0x22); // Modem configuration.
	Mrfi_SpiWriteReg(TI_CCxxx0_MDMCFG0,  0xF8); // Modem configuration.
	Mrfi_SpiWriteReg(TI_CCxxx0_DEVIATN,  0x00); // Modem dev (when FSK mod en)
	Mrfi_SpiWriteReg(TI_CCxxx0_MCSM1 ,   0x3F); //MainRadio Cntrl State Machine
	Mrfi_SpiWriteReg(TI_CCxxx0_MCSM0 ,   0x18); //MainRadio Cntrl State Machine
	Mrfi_SpiWriteReg(TI_CCxxx0_FOCCFG,   0x1D); // Freq Offset Compens. Config
	Mrfi_SpiWriteReg(TI_CCxxx0_BSCFG,    0x1C); //  Bit synchronization config.
	Mrfi_SpiWriteReg(TI_CCxxx0_AGCCTRL2, 0xC7); // AGC control.
	Mrfi_SpiWriteReg(TI_CCxxx0_AGCCTRL1, 0x00); // AGC control.
	Mrfi_SpiWriteReg(TI_CCxxx0_AGCCTRL0, 0xB2); // AGC control.
	Mrfi_SpiWriteReg(TI_CCxxx0_FREND1,   0xB6); // Front end RX configuration.
	Mrfi_SpiWriteReg(TI_CCxxx0_FREND0,   0x10); // Front end RX configuration.
	Mrfi_SpiWriteReg(TI_CCxxx0_FSCAL3,   0xEA); // Frequency synthesizer cal.
	Mrfi_SpiWriteReg(TI_CCxxx0_FSCAL2,   0x0A); // Frequency synthesizer cal.
	Mrfi_SpiWriteReg(TI_CCxxx0_FSCAL1,   0x00); // Frequency synthesizer cal.
	Mrfi_SpiWriteReg(TI_CCxxx0_FSCAL0,   0x11); // Frequency synthesizer cal.
	Mrfi_SpiWriteReg(TI_CCxxx0_FSTEST,   0x59); // Frequency synthesizer cal.
	Mrfi_SpiWriteReg(TI_CCxxx0_TEST2,    0x88); // Various test settings.
	Mrfi_SpiWriteReg(TI_CCxxx0_TEST1,    0x31); // Various test settings.
	Mrfi_SpiWriteReg(TI_CCxxx0_TEST0,    0x0B); // Various test settings.
}
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
	
	SPI_DRIVE_CSN_LOW();
	
	/* send register address byte, the read/write bit is already configured */
	SpiWriteByte(addrByte);
	
	/*
	*  Send the byte value to write.  If this operation is a read, this value
	*  is not used and is just dummy data.  Wait for SPI access to complete.
	*/
	readValue = SpiWriteByte(writeValue);
	
	/* turn off chip select; enable interrupts that call SPI functions */
	SPI_DRIVE_CSN_HIGH();
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
uint8_t Mrfi_SpiReadReg(uint8_t addr)
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
void Mrfi_SpiWriteReg(uint8_t addr, uint8_t value)
{
	spiRegAccess(addr, value);
}

/*-------------------------------------------------------------------------------------------------
 * \brief 
 * 
 * \param pPacket
 * \param txType
 * 
 * \return uint8_t
 */
uint8_t Mrfi_SpiCmdStrobe(uint8_t cmd)
{
	uint8_t statusByte;

	/* disable interrupts that use SPI */
//	MRFI_SPI_ENTER_CRITICAL_SECTION(s);

	/* turn chip select "off" and then "on" to clear any current SPI access */
	SPI_DRIVE_CSN_LOW();

	/* send the command strobe, wait for SPI access to complete */
	statusByte = SpiWriteByte(cmd);

	/* read the readio status byte returned by the command strobe */
	

	/* turn off chip select; enable interrupts that call SPI functions */
	SPI_DRIVE_CSN_HIGH();
//	MRFI_SPI_EXIT_CRITICAL_SECTION(s);

	/* return the status byte */
	return(statusByte);
}

/*-------------------------------------------------------------------------------------------------
 * \brief 
 * 
 * \param pPacket
 * \param txType
 * 
 * \return uint8_t
 */
static uint8_t spiBurstFifoAccess(uint8_t addrByte, uint8_t * pData, uint8_t len)
{
	/* disable interrupts that use SPI */
//	MRFI_SPI_ENTER_CRITICAL_SECTION(s);

	/* turn chip select "off" and then "on" to clear any current SPI access */
	SPI_DRIVE_CSN_HIGH();
	SPI_DRIVE_CSN_LOW();

	/* send FIFO access command byte, wait for SPI access to complete */
	SpiWriteByte(addrByte);
	SPIWriteArrayBytes(pData, len);
	
	/* turn off chip select; enable interrupts that call SPI functions */
	SPI_DRIVE_CSN_HIGH();
//	MRFI_SPI_EXIT_CRITICAL_SECTION(s);
	
	return 1;
}

/*-------------------------------------------------------------------------------------------------
 * \brief 
 * 
 * \param pPacket
 * \param txType
 * 
 * \return uint8_t
 */
uint8_t Mrfi_SpiWriteTxFifo(uint8_t * pData, uint8_t len)
{
  return spiBurstFifoAccess(TXFIFO | BURST_BIT, pData, len);
}

/*-------------------------------------------------------------------------------------------------
 * \brief 
 * 
 * \param pPacket
 * \param txType
 * 
 * \return uint8_t
 */
uint8_t Mrfi_SpiReadRxFifo(uint8_t * pData, uint8_t len)
{
  return spiBurstFifoAccess(RXFIFO | BURST_BIT | READ_BIT, pData, len);
}

/*-------------------------------------------------------------------------------------------------
 * \brief 
 * 
 * \param pPacket
 * \param txType
 * 
 * \return uint8_t
 */
uint8_t Radio_Transmit(uint8_t * pPacket, uint8_t len)
{
	Mrfi_SpiWriteReg(TXFIFO, len);
	//
	Mrfi_SpiWriteTxFifo(pPacket, len);
	
	{
		uint8_t len;
		len = Mrfi_SpiReadReg(TXBYTES);
		if(len == 5)
			len =0;
	}
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(STX);
	while(!Spi_CheckGpio0());
	while(Spi_CheckGpio0());
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(SFTX);
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(SRX);
	
	return 1;
}

/*-------------------------------------------------------------------------------------------------
 * \brief 
 * 
 * \param pPacket
 * \param txType
 * 
 * \return uint8_t
 */
void Mrfi_RxModeOn(void)
{
	/* clear any residual receive interrupt */
//	MRFI_CLEAR_SYNC_PIN_INT_FLAG();

	/* send strobe to enter receive mode */
	Mrfi_SpiCmdStrobe( SRX );

	/* enable receive interrupts */
//	MRFI_ENABLE_SYNC_PIN_INT();
}

/*-------------------------------------------------------------------------------------------------
 * \brief 
 * 
 * \param pPacket
 * \param txType
 * 
 * \return uint8_t
 */
void Mrfi_RxModeOff(void)
{
	/* clear any residual receive interrupt */
//	MRFI_CLEAR_SYNC_PIN_INT_FLAG();

	/* send strobe to enter receive mode */
	Mrfi_SpiCmdStrobe( SIDLE );

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
void Mrfi_SetLogicalChannel(uint8_t chan)
{
	/* make sure radio is off before changing channels */
	Mrfi_RxModeOff();

	Mrfi_SpiWriteReg( CHANNR, chan );

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
void Mrfi_SetRFPwr(uint8_t idx) 
{
	/* make sure radio is off before changing power levels */
	Mrfi_RxModeOff();

	Mrfi_SpiWriteReg( PA_TABLE0, idx);

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
void Radio_Init(void)
{
	
	/* Initial radio state is IDLE state */
	mrfiRadioState = MRFI_RADIO_STATE_IDLE;

//	radioSpiInit();													// SPI modle init in main.c
	
	/* pulse CSn low then high */
	SPI_DRIVE_CSN_LOW();
	Mrfi_DelayUsec(10);
	SPI_DRIVE_CSN_HIGH();

	/* hold CSn high for at least 40 microseconds */
	Mrfi_DelayUsec(40);
	
	/* pull CSn low and wait for SO to go low */
	SPI_DRIVE_CSN_LOW();
	while (SPI_SO_IS_HIGH());
	
	/* send the command strobe, wait for SPI access to complete */
	SpiWriteByte(SRES);
	
	/* wait for SO to go low again, reset is complete at that point */
	while (SPI_SO_IS_HIGH());

	/* return CSn pin to its default high level */
	SPI_DRIVE_CSN_HIGH();
	
	/* initialize radio registers */
	writeRFSettings();
	
	/* Initial radio state is IDLE state */
	mrfiRadioState = MRFI_RADIO_STATE_IDLE;
	
	/* set default channel */
//	Mrfi_SetLogicalChannel( 10 );
	
	/* set default power */
//	Mrfi_SetRFPwr(RF_TxPower_5dbm);
	
	Mrfi_RxModeOn();												// Put the radio in RX state.
	
	/* Turn off RF. */
	Mrfi_RxModeOff();
	
	Mrfi_SpiWriteReg(IOCFG0, 0x06);									// Set SYNC signal interrupt.
	
	{
		uint8_t d;
		d = Mrfi_SpiReadReg(MCSM0);
		if(d == 0x18)
			d = 0;
	}
	Mrfi_RxModeOn();
	
	Mifi_ConfigInt();												// Config GPIO0 interrupt.
}

