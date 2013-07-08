#include "bsp.h"

void timer_A_init(void)
{
	CCTL0 = CCIE;                             						// CCR0 interrupt enabled
	CCR0 = 4096 * 3;//24576;                             				// CCR0 Period
	
//	TACTL = TASSEL_1 + ID_3 + MC_1;	           						// ACLK, up mode, interrupt.
	
//	_BIS_SR(LPM3_bits);                       						// Enter LPM3
}

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
	
	gpio_init();
	cc1101_init();
	timer_A_init();
	
	_BIS_SR(GIE);
	
	for(;;)
	{
		radio_handle();
	}
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
//	flag_send = 1;
//	P1OUT ^= BIT0;													// Turn LED0..
	CCR0 = 0;
	P2OUT |= BIT3;													// Press up KEY pin..
}
