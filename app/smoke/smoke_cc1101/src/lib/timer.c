#include <msp430.h>
#include "timer.h"

void timer_A_init(void)
{
	CCTL0 = CCIE;                             						// CCR0 interrupt enabled
	CCR0 = 1000-1;                             						// CCR0 Period
	
	TACTL = TASSEL_1 + MC_1;	            						// ACLK, up mode, interrupt.

	_BIS_SR(LPM3_bits);                       						// Enter LPM3
}

extern void radio_timer_send(void);

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
//	radio_timer_send();

	switch( TA0IV )
	{
		case  2:  break;                        					// CCR1 not used
		case  4:  break;                        					// CCR2 not used
		case 10:  
			                						// send timer data
				  break;
	}
}
