#include "msp430.h"
#include <stdint.h>
#include <string.h>
#include "cc1101.h"
#include "cc1101_defs.h"

#define MISO			BIT1
#define MOSI			BIT2
#define CLK				BIT4
#define CSN				BIT5
#define GPIO0			BIT0

#define SPI_SCLK_H()	P1OUT |= CLK
#define SPI_SCLK_L()	P1OUT &=~CLK

#define SPI_MOSI_H()	P1OUT |= MOSI
#define SPI_MOSI_L()	P1OUT &=~MOSI

#define SPI_CSN_H()		P1OUT |= CSN
#define SPI_CSN_L()		P1OUT &=~CSN

#define SPI_MISO_READ()	(!!(P1IN&MISO))
#define SPI_GPIO0_READ()	(!!(P2IN&GPIO0))

#define DUMMY_BYTE                  0xDB
#define READ_BIT                    0x80
#define BURST_BIT                   0x40

void Mrfi_DelayUsec(uint16_t howlong)
{
	uint16_t i;
	
	while(howlong --)
	{
		for(i = 0;i < 10000;i++)
		{
			asm("NOP");
		}
	}
}

void gpio_init(void)
{
	P1DIR |= BIT0;
	P1DIR |= MOSI + CLK + CSN;
	P1DIR &=~MISO;
	P2DIR &=~GPIO0;
	
	P1REN |= MISO;
	
	SPI_SCLK_L();
	SPI_MOSI_L();
	SPI_CSN_H();
}

uint8_t spi_writebyte (uint8_t value)
{
	uint8_t i,temp,data;
	
	data = value;
	temp = 0;
	
	for(i = 0;i < 8;i ++)
	{
		if((data&0x80) == 0x80)
			SPI_MOSI_H();
		else
			SPI_MOSI_L();
		
		SPI_SCLK_H();
		
		data = data<<1;
		
		if(SPI_MISO_READ() == 1)
		{
			temp = temp | (1<<(7-i));
		}
		
		SPI_MOSI_L();
		
		SPI_SCLK_L();
	}
	
	return temp;
}

uint8_t spiRegAccess(uint8_t addrByte, uint8_t writeValue)
{
	uint8_t readValue;
	SPI_CSN_L();
//	while (SPI_MISO_READ());
	spi_writebyte(addrByte);
	readValue = spi_writebyte(writeValue);
	SPI_CSN_H();
	return(readValue);
}

uint8_t Mrfi_SpiReadReg(uint8_t addr)
{
	return( spiRegAccess(addr | BURST_BIT | READ_BIT, DUMMY_BYTE) );
}

void Mrfi_SpiWriteReg(uint8_t addr, uint8_t value)
{
	spiRegAccess(addr, value);
}

uint8_t Mrfi_SpiCmdStrobe(uint8_t cmd)
{
	uint8_t statusByte;
	SPI_CSN_L();
//	while (SPI_MISO_READ());
	statusByte = spi_writebyte(cmd);
	SPI_CSN_H();
	return(statusByte);
}

void SPI_WriteBuf(uint8_t *buf, uint8_t cnt)
{
	uint8_t statusByte,i;
	
	for(i = 0;i < cnt;i ++)
	{
		statusByte = spi_writebyte(buf[i]);
		buf[i] = statusByte;
	}
}

uint8_t spiBurstFifoAccess(uint8_t addrByte, uint8_t * pData, uint8_t len)
{
	SPI_CSN_L();
//	while (SPI_MISO_READ());
	spi_writebyte(addrByte);
	SPI_WriteBuf(pData, len);
	SPI_CSN_H();
	return 1;
}

uint8_t Mrfi_SpiWriteTxFifo(uint8_t * pData, uint8_t len)
{
	return spiBurstFifoAccess(TXFIFO | BURST_BIT, pData, len);
}

uint8_t Mrfi_SpiReadRxFifo(uint8_t * pData, uint8_t len)
{
	return spiBurstFifoAccess(RXFIFO | BURST_BIT | READ_BIT, pData, len);
}

uint8_t Radio_Transmit(uint8_t * pPacket, uint8_t len)
{
	P2IFG &=~GPIO0;
	P2IE  &=~GPIO0;
	
	Mrfi_SpiWriteReg(TXFIFO, len);
	Mrfi_SpiWriteTxFifo(pPacket, len);
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(STX);
	while(!SPI_GPIO0_READ());
	while(SPI_GPIO0_READ());
	Mrfi_SpiCmdStrobe(SFTX);
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(SRX);
	
	P2IFG &=~GPIO0;
	P2IE  |= GPIO0;
	
	return 1;
}

void RfWriteRfSettings(void) 
{
	Mrfi_SpiWriteReg(IOCFG0,0x06);
	Mrfi_SpiWriteReg(PKTCTRL0,0x05);
	Mrfi_SpiWriteReg(CHANNR,0x0C);
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

void cc1101_init(void)
{
	SPI_CSN_L();
	Mrfi_DelayUsec(10);
	SPI_CSN_H();
	Mrfi_DelayUsec(40);
	SPI_CSN_L();
	while (SPI_MISO_READ());
	spi_writebyte(SRES);
	while (SPI_MISO_READ());
	SPI_CSN_H();
	
	RfWriteRfSettings();
	
	Mrfi_SpiWriteReg(TI_CCxxx0_IOCFG0, 0x06);
	{
		uint8_t tmp = 0;
		tmp = Mrfi_SpiReadReg(TI_CCxxx0_IOCFG0);
		if(tmp != 0x06)
			while(1);
	}
	Mrfi_SpiCmdStrobe(SIDLE);
	Mrfi_SpiCmdStrobe(SRX);
	
	P2IES |= GPIO0;													// Ñ¡ÔñÉÏÉý/ÏÂ½µÑØ
	P2REN |= GPIO0;													// push-up enable
	P2IFG &=~GPIO0;
	P2IE  |= GPIO0;
}
