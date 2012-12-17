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
	
//	timer_init();													/* Initialise timer 1(16bit).*/
	
	mac_init();														/* Initialise MAC layer.*/
	
//	energy_init();													/* Initialise energy I/O.*/
	
	set_sleeptimer(TICK_VAL);										/* Enable sleep timer.*/
	
	SLEEPCMD = (SLEEPCMD & ~0x02) | 0x02;							/* Power-mode setting
																		00: Active / Idle mode
																		01: Power mode 1 (PM1)
																		10: Power mode 2 (PM2)
																		11: Power mode 3 (PM3)*/
	EnterSleepModeDisableInterruptsOnWakeup();						/* Enter sleep mode.*/
	
	for(;;)
	{
		if(sysflag & SYS_FLAG_SLEEP_START)							/* Sleep mode.*/
		{
			sysflag &= ~SYS_FLAG_SLEEP_START;						/* Clear system flag.*/
			
			halLedClear(2);
			EnterSleepModeDisableInterruptsOnWakeup();
		}
		else if(sysflag & ADC_FLAG_ISR)								/* ADC mode.*/
		{
			sysflag &= ~ADC_FLAG_ISR;								/* Clear system flag.*/
			
			SensorADCInit();
			SensorADCBegin();
			halLedSet(2);
		}
		mac_event_handle();											/* Rx mode handle.*/
	}
}

