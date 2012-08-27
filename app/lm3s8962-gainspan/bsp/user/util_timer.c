/*******************************************************************************
 Name        : util_timer.c
 Author      : Writed by songzi&jingjing in 2011.09.07
 Version     : 1.0
 Description : led low-level driver
*******************************************************************************/
#include "util_timer.h"

/*
*********************************************************************************************************
*                                           LOCAL DEFINES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/



/********************************************************************************************************
*                                          BSP_Timer0_Init()
*
* Description : none.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void BSP_Timer0_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

/********************************************************************************************************
*                                          BSP_Timer0_Init()
*
* Description : none.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void BSP_Timer0_DelayMs(U16 value)
{
	
	TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet()/1000)*value);
	TimerEnable(TIMER0_BASE, TIMER_A);
	while((TimerIntStatus(TIMER0_BASE, TIMER_O_MIS)&TIMER_TIMA_TIMEOUT) != TIMER_TIMA_TIMEOUT);
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}
