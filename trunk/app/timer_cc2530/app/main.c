/*
*********************************************************************************************************
*
*                                             hal_cc2530/Main
*                                            INTRODUCTION DEMO
*
*
* Filename      : endDevice.c
* Version       : V1.01a
* Programmer(s) : MC
*********************************************************************************************************
*/
#include "includes.h"

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

	mac_init();				// Initialise radio.
	
	for(;;)
	{
		;
	}
}

