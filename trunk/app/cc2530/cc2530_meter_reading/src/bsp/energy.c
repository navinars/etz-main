/* ------------------------------------------------------------------------------------------------------
 * File: energy.c
 *
 * -------------------------------------------------------------------------------------------------------
 */
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *                                            Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
volatile unsigned long 			iCnt = 0;
volatile float 					iCnt_last = 0;


/* ------------------------------------------------------------------------------------------------------
 *												mac_init()
 *
 * Description : Energy port init.
 *
 */
void energy_init(void)
{
	MCU_IO_INPUT(0, 4, MCU_IO_PULLUP);								/* Input & pull-up mode.*/
	PICTL |= 0x01;													/* P0 falling edge gives interrupt.*/
	P0IEN |= (1<<4);												/* Enable P0.4 interrupt mask.*/
	P0IE   = 1;														/* Enable P0 interrupt.*/
}

/* ------------------------------------------------------------------------------------------------------
 *											HAL_ISR_FUNCTION()
 *
 * Description : port0 ISR interrupt function.
 *
 */
HAL_ISR_FUNCTION(port0_ISR,P0INT_VECTOR)
{
	P0IFG &=~(1 << 4);												/* Clear P0.4 interrupt mask falg.
																	   this step must in front*/
	P0IF = 0;														/* Clear PO interrupt flag.*/
	
	iCnt ++;
}


