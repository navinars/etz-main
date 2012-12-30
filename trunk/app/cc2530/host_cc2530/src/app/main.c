/*
*********************************************************************************************************
*
*                                             host_cc2530/Main
*                                            INTRODUCTION DEMO
*
*
* Filename      : Host.c
* Version       : V1.01a
* Programmer(s) : MC
*********************************************************************************************************
*/
/* ------------------------------------------------------------------------------------------------------
 *                                            INCLUDE FILES
 * ------------------------------------------------------------------------------------------------------
 */
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *                                            Local Variable
 * ------------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------------
 *                                            Local Function
 * ------------------------------------------------------------------------------------------------------
 */
extern void EnterSleepModeDisableInterruptsOnWakeup(void);

/* ------------------------------------------------------------------------------------------------------
 *												main()
 *
 * Description : main function.
 *
 */
int main(void)
{
	halBoardInit();													/* Initialise clock, enable master interrupt.*/
	
	timer_init();													/* Initialise timer 1(16bit).*/
	
	mac_init();														/* Initialise MAC layer.*/
	
//	set_sleeptimer(TICK_VAL);										/* Enable sleep timer.*/
	
	SLEEPCMD |= 0x02;												/* Power-mode setting
																		00: Active / Idle mode
																		01: Power mode 1 (PM1)
																		10: Power mode 2 (PM2)
																		11: Power mode 3 (PM3)*/
	for(;;)
	{
		if (sysflag & SYS_FLAG_SLEEP_START)							/* Sleep mode.*/
		{
			sysflag &= ~SYS_FLAG_SLEEP_START;						/* Clear system flag.*/
			
			halLedClear(2);
			EnterSleepModeDisableInterruptsOnWakeup();
		}
		else if (sysflag & ADC_FLAG_ISR)							/* ADC mode.*/
		{
			sysflag &= ~ADC_FLAG_ISR;								/* Clear system flag.*/
			
//			SensorADCInit();
//			SensorADCBegin();
			halLedSet(2);
		}
		else if (sysflag & BROADCASR_FLAG_SYN)						/* Broadcast syn frame.*/
		{
			mac_syn_t syn;
			sysflag &=~BROADCASR_FLAG_SYN;
			
			syn.msgType 		= BROADCAST_SYN;					/* Broadcast message type.*/
			syn.routeCnt 		= 0;								/* Route count.*/
			syn.offset			= halRfGetRandomByte();				/* Time offset number.*/
			mac_gen_syn_frm(&syn);									/* Generate time syn frame.*/
		}
		mac_event_handle();											/* Rx mode handle.*/
	}
}

