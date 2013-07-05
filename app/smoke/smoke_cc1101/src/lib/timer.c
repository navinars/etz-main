#include "bsp.h"

uint8_t frm[] = {0x05,0x00,0x02,0x03,0x04,0x05};

void timer_A_init(void)
{
	CCTL0 = CCIE;                             						// CCR0 interrupt enabled
	CCR0 = 4096;//24576;                             						// CCR0 Period
	
	TACTL = TASSEL_1 + ID_3 + MC_1;	           						// ACLK, up mode, interrupt.
	
//	_BIS_SR(LPM3_bits);                       						// Enter LPM3
}

extern void radio_timer_send(void);

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
//	Radio_Transmit(frm, 6);
//	P1OUT ^= BIT0;													// Turn LED0..
}
