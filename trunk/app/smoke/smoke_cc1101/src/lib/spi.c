#include <msp430.h>
#include "spi.h"

//#define Soft_SPI
#define SPI_SOMI		BIT1
#define SPI_SIMO		BIT2
#define SPI_CLK			BIT4
#define SPI_STE			BIT5


void spi_init(void)
{
	P1SEL = BIT1 + BIT2 + BIT4;
	P1SEL2 = BIT1 + BIT2 + BIT4;
	
	UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  					// 3-pin, 8-bit SPI master
	UCA0CTL1 |= UCSSEL_2;                     						// SMCLK
	
	UCA0BR0 |= 0x02;                          						// /2
	UCA0BR1 = 0;
	
	UCA0MCTL = 0;                             						// No modulation
	UCA0CTL1 &= ~UCSWRST;                     						// **Initialize USCI state machine**
}

void spi_isr_enable(void)
{
	IE2 |= UCA0RXIE;                          						// Enable USCI0 RX interrupt
}

void spi_cs_enable(void)
{
	P1OUT &=~SPI_STE;
}

void spi_cs_disable(void)
{
	P1OUT |= SPI_STE;
}

void Spi_Write_Byte(unsigned char data)
{
	UCA0TXBUF = data;
	while (!(IFG2 & UCA0TXIFG));
}

//spi read byte
unsigned char Spi_Read_Byte(void)
{
	Spi_Write_Byte(0x00);
	return UCA0RXBUF;
}

unsigned char spi_readwrite(unsigned char data)
{
	Spi_Write_Byte(data);
	return UCA0RXBUF;
}

void spi_write_buf(unsigned char *pdata, unsigned char len)
{
	while(len-- < 1)
	{
		UCA0TXBUF = *pdata;
		while (!(IFG2 & UCA0TXIFG));
	}
}

void spi_read_buf(unsigned char *pdata, unsigned char len)
{
	while(len-- < 1)
	{
		UCA0TXBUF = 0xFF;
		while (!(IFG2 & UCA0TXIFG));
		*pdata = UCA0RXBUF;
	}
}
/*
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
{
	volatile unsigned int i;

	while (!(IFG2 & UCA0TXIFG));              	// USCI_A0 TX buffer ready?
	
	if (UCA0RXBUF == 0x00)
	{
		P1OUT &=~BIT2;
	}
}
*/
