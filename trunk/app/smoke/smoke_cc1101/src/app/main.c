#include "bsp.h"

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;										// Disable WDT.
	
	if (CALBC1_8MHZ==0xFF)											// If calibration constant erased.
	{
		while(1);                               					// do not load, trap CPU!!	
	}
	
	DCOCTL = 0;
	BCSCTL1 = CALBC1_8MHZ;											// MCLK = 12Mhz.
	DCOCTL = CALDCO_8MHZ;
	
	GPIO_init();													// Init gpio.
	
	spi_init();
	
	timer_A_init();
	
	Radio_Init();
	
	_BIS_SR(GIE);													// Enable genration interrupt.
	
	/* Main loop.*/
	for(;;)
	{
		
	}
}
