/*
*********************************************************************************************************
*
*                                             hal_cc2530/Main
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
 * -------------------------------------------------------------------------------------------------------
 */
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *                                            Local Variable
 * -------------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------------
 *												main()
 *
 * Description : main function.
 */
int main(void)
{
	/* Initialise clock, and put on INT.*/
	halBoardInit();
	
	timer1_init();			// Initialise timer 1(16bit).

//	mac_init();				// Initialise radio.
	
	for(;;)
	{
		SLEEPCMD = (SLEEPCMD & ~0x02) | 0x02;
		PCON = 1;
//		mac_event_handle();
	}
}
