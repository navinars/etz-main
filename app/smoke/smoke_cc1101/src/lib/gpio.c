#include "bsp.h"

void GPIO_init(void)
{
	// Config LED pin.
	P1DIR |= BIT0;
	P1OUT |= BIT0;
	
	/* Config GPIO0 pin.*/
	P2DIR &=~BIT0;
	P2IE  |= BIT0;
	P2IES |= BIT0;													// Ñ¡ÔñÉÏÉý/ÏÂ½µÑØ
	P2REN |= BIT0;													// push-up disable
	
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	if(!!(P2IFG & BIT0))											// Rx receive.
	{
		
		P2IFG &= ~BIT0;                           					// P2.2 IFG cleared
	}
}
