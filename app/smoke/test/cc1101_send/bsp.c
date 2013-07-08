#include "bsp.h"


void gpio_init(void)
{
	P1DIR |= BIT0;
	P1DIR |= MOSI + CLK + CSN;
	P1DIR &=~MISO;
	P2DIR &=~GPIO0 + KEY + IO;
	
	P2DIR |= BIT3;
	P2OUT |= BIT3;													// Press down KEY..
//	P2OUT &=~BIT3;
	
	P1REN |= MISO;
	
	P2IES &=~KEY;													// —°‘Ò…œ…˝
//	P2REN |= GPIO0;													// push-up enable
	P2IFG &=~KEY;
	P2IE  |= KEY;
	
	SPI_SCLK_L();
	SPI_MOSI_L();
	SPI_CSN_H();
}
