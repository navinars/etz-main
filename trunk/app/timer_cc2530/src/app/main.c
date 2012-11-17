/* ------------------------------------------------------------------------------------------------------
 *
 *                                            timer_cc2530/Main
 *                                            INTRODUCTION DEMO
 *
 *
 * Filename      : main.c
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
	
	timer1_init();													/* Initialise timer 1(16bit).*/
	
	mac_init();														/* Initialise MAC layer.*/
	
	energy_init();													/* Initialise energy I/O.*/
	
	SLEEPCMD = (SLEEPCMD & ~0x02) | 0x02;							/* Power-mode setting
																		00: Active / Idle mode
																		01: Power mode 1 (PM1)
																		10: Power mode 2 (PM2)
																		11: Power mode 3 (PM3)*/
//	EnterSleepModeDisableInterruptsOnWakeup();						/* Enter sleep mode.*/

	DEVICE_ON();
	
	for(;;)
	{
		/* Sleep mode.*/
		/*
		if(sysflag & SYS_FLAG_SLEEP_START)
		{
			sysflag &= ~SYS_FLAG_SLEEP_START;
			halLedClear(1);
			EnterSleepModeDisableInterruptsOnWakeup();
		}
		*/
		mac_event_handle();											/* Rx mode handle.*/
		
		if(iCnt_last != 0)											/* Every 3s once.*/
		{
			// DOTO: Send energy data to HOST.
		}
	}
}

