#include "bsp.h"

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;										// Disable WDT.
	
	if (CALBC1_12MHZ==0xFF)											// If calibration constant erased.
	{
		while(1);                               					// do not load, trap CPU!!	
	}
	
	DCOCTL = 0;
	BCSCTL1 = CALBC1_12MHZ;											// MCLK = 12Mhz.
	DCOCTL = CALDCO_12MHZ;
	
	GPIO_init();													// Init gpio.
	
	spi_init();
	
	CC1101_Initialization();
	
	timer_A_init();
	
	_BIS_SR(GIE);													// Enable genration interrupt.
	for(;;)
	{
		
	}
}
