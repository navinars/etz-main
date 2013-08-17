
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
#define SPI_MAX_TIME				1000

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

/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
static void writeRFSettings(void)
{
	Mrfi_SpiWriteReg(IOCFG0,0x06);
	Mrfi_SpiWriteReg(PKTCTRL0,0x05);
	Mrfi_SpiWriteReg(CHANNR,0xAA);
	Mrfi_SpiWriteReg(FSCTRL1,0x08);
	Mrfi_SpiWriteReg(FREQ2,0x21);
	Mrfi_SpiWriteReg(FREQ1,0x62);
	Mrfi_SpiWriteReg(FREQ0,0x76);
	Mrfi_SpiWriteReg(MDMCFG4,0xC7);
	Mrfi_SpiWriteReg(MDMCFG3,0x83);
	Mrfi_SpiWriteReg(MDMCFG2,0x93);
	Mrfi_SpiWriteReg(DEVIATN,0x40);
	Mrfi_SpiWriteReg(MCSM0,0x18);
	Mrfi_SpiWriteReg(FOCCFG,0x16);
	Mrfi_SpiWriteReg(AGCCTRL2,0x43);
	Mrfi_SpiWriteReg(WORCTRL,0xFB);
	Mrfi_SpiWriteReg(FSCAL3,0xE9);
	Mrfi_SpiWriteReg(FSCAL2,0x2A);
	Mrfi_SpiWriteReg(FSCAL1,0x00);
	Mrfi_SpiWriteReg(FSCAL0,0x1F);
	Mrfi_SpiWriteReg(TEST2,0x81);
	Mrfi_SpiWriteReg(TEST1,0x35);
	Mrfi_SpiWriteReg(TEST0,0x09);

	//SPIWriteReg(CCxxx0_IOCFG2,   0x0e);
	Mrfi_SpiWriteReg(IOCFG2,   0x0b);
	Mrfi_SpiWriteReg(FSCTRL0,  0x00);
	Mrfi_SpiWriteReg(BSCFG,    0x6c);
	Mrfi_SpiWriteReg(FSTEST,   0x59);
	Mrfi_SpiWriteReg(PKTCTRL1, 0x04);
	//SPIWriteReg(CCxxx0_ADDR,     0x00);
	Mrfi_SpiWriteReg(PKTLEN,   0xff);
	Mrfi_SpiWriteReg(AGCCTRL1,0x41);
	Mrfi_SpiWriteReg(AGCCTRL0,0xb2);

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
	uint32_t howlong = 0;
	/* disable interrupts that use SPI */
//	MRFI_SPI_ENTER_CRITICAL_SECTION(s);
	
	Spi_CsHigh();
	Spi_CsLow();
	
	while(SPI_CheckGpio1())
	{
		howlong ++;
		if(howlong > SPI_MAX_TIME)
			break;
	}
	
	/* send register address byte, the read/write bit is already configured */
	Spi_WriteByte(addrByte);
	
	/*
	*  Send the byte value to write.  If this operation is a read, this value
	*  is not used and is just dummy data.  Wait for SPI access to complete.
	*/
	readValue = Spi_WriteByte(writeValue);
	
	/* turn off chip select; enable interrupts that call SPI functions */
	Spi_CsHigh();
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
	uint32_t howlong = 0;
	
	/* disable interrupts that use SPI */
//	MRFI_SPI_ENTER_CRITICAL_SECTION(s);
	
	/* turn chip select "off" and then "on" to clear any current SPI access */
	Spi_CsHigh();
	Spi_CsLow();
	
	while(SPI_CheckGpio1())
	{
		howlong ++;
		if(howlong > SPI_MAX_TIME)
		break;
	}
	
	/* send the command strobe, wait for SPI access to complete */
	statusByte = Spi_WriteByte(cmd);	
	
	/* turn off chip select; enable interrupts that call SPI functions */
	Spi_CsHigh();
	
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
	Spi_CsHigh();
	Spi_CsLow();
	
	while(SPI_CheckGpio1());

	/* send FIFO access command byte, wait for SPI access to complete */
	Spi_WriteByte(addrByte);
	Spi_WriteArrayBytes(pData, len);
	
	/* turn off chip select; enable interrupts that call SPI functions */
	Spi_CsHigh();
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
	Mifi_DisableInt();												// Disable cc1101 interrupt.
	
	Mrfi_SpiWriteReg(TXFIFO, len);
	Mrfi_SpiWriteTxFifo(pPacket, len);
	
	{
		uint8_t tx_status;
		
		tx_status = Mrfi_SpiReadReg(TXBYTES);
		if(tx_status != 0x05)
			tx_status = 0;
	}
	
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(STX);
	while(!Spi_CheckGpio0());
	while(Spi_CheckGpio0());
	Mrfi_SpiCmdStrobe(SFTX);										// Clear TxFIFOs..
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(SRX);											// Go to RX mode.
	
	Mifi_EnableInt();												// Enable cc1101 interrupt.
	
	return 1;
}

/**
 * \brief 
 * 
 * \param pPacket
 * 
 * \return uint8_t
 */
uint8_t Radio_ReadFifo(uint8_t *pPacket)
{
	uint8_t rx_len,len;
	
	rx_len = Mrfi_SpiReadReg(RXBYTES);
	if(rx_len != 0)
	{
		gpio_toggle_pin(LED1_GPIO);									// LED1 trun on.
		
		len = Mrfi_SpiReadReg(RXFIFO);
		Mrfi_SpiReadRxFifo(pPacket, len + 2);
		
		return (len+2);
	}
	else
	{
		return (rx_len);
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

	spi_set_clock_configuration(1);									// SPI mode init on 1000000(1MHz)..
	
	/* pulse CSn low then high */
	Spi_CsLow();
	
	Mrfi_DelayUsec(100);
	
	Spi_CsHigh();

	/* hold CSn high for at least 40 microseconds */
	Mrfi_DelayUsec(400);
	
	/* pull CSn low and wait for SO to go low */
	Spi_CsLow();
	while (SPI_CheckGpio1());
	
	/* send the command strobe, wait for SPI access to complete */
	Spi_WriteByte(SRES);
	
	/* wait for SO to go low again, reset is complete at that point */
	while (SPI_CheckGpio1());

	/* return CSn pin to its default high level */
	Spi_CsHigh();
	
	/* initialize radio registers */
	writeRFSettings();
	
	/* Initial radio state is IDLE state */
	mrfiRadioState = MRFI_RADIO_STATE_IDLE;

	Mrfi_SpiWriteReg(IOCFG0, 0x06);									// Set SYNC signal interrupt.
	
	{
		uint8_t d;
		d = Mrfi_SpiReadReg(IOCFG0);
		if (d == 0)
			while(1);
	}

	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(SRX);											// Access Receive mode..
	
	Mifi_ConfigInt();												// Config GPIO0 interrupt.
}

