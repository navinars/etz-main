/* ------------------------------------------------------------------------------------------------------
 *
 *                                             hal_cc2530/Main
 *                                            INTRODUCTION DEMO
 *
 *
 * Filename      : Host.c
 * Version       : V1.01a
 * Programmer(s) : MC
 * ------------------------------------------------------------------------------------------------------
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
	
//	timer1_init();													/* Initialise timer 1(16bit).*/
	
//	mac_init();														/* Initialise MAC layer.*/
	
	energy_init();													/* Initialise energy I/O.*/
	
	SLEEPCMD = (SLEEPCMD & ~0x02) | 0x02;
//	EnterSleepModeDisableInterruptsOnWakeup();						/* Enter sleep mode.*/

	for(;;)
	{
		/*
		if(sysflag & SYS_FLAG_SLEEP_START)
		{
			sysflag &= ~SYS_FLAG_SLEEP_START;
			halLedClear(1);
			EnterSleepModeDisableInterruptsOnWakeup();
		}
		*/
//		mac_event_handle();											/* Rx mode handle.*/
	}
}

