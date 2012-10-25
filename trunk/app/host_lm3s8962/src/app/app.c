/* ------------------------------------------------------------------------------------------------------
* File: app.c
* Data: 2012/9/4
* Author: MC
* Ver: V0.1.1a
* -------------------------------------------------------------------------------------------------------
*/
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
static OS_STK  Task_StartStk[TASK_START_STK_SIZE];


/* ------------------------------------------------------------------------------------------------------
 *											Local Function
 * ------------------------------------------------------------------------------------------------------
 */
static  void  App_TaskStart (void *p_arg);


/* ------------------------------------------------------------------------------------------------------
 *									main()
 *
 * Description : main function.
 *
 * Argument(s) : none.
 *
 */
int main(void)
{
	BSP_Init();
	
	OSInit(); 													/* Start uC/OS-II init function.*/
	
	OSTaskCreate ( App_TaskStart, 								/* Creat start task.*/
		           (void *)0, 
				   &Task_StartStk[TASK_START_STK_SIZE-1], 
				   APP_CFG_TASK_START_PRIO );

	OSStart();
    return(0);
}

/* ------------------------------------------------------------------------------------------------------
 *									App_TaskStart()
 *
 * Description : Task start function.
 *
 * Argument(s) : none.
 *
 */
static  void  App_TaskStart (void *p_arg)
{
	(void)p_arg;
	
	OS_CPU_SysTickInit(SysCtlClockGet() / OS_TICKS_PER_SEC);	/* Initialize the SysTick.*/
	
	lwIP_init();												/* Initialise lwIP stack. */
	
	TaskTcpip_Create();											/* Create lwIP task and init.*/
	
	TaskSocket_Create();										/* Create Socket task and init.*/

#ifdef LCD
//	TaskLCD_Create();											/* Create LCD task.*/
#endif
	
#ifdef CC2520
	TaskCC2520_Create();										/* Create CC2520 task.*/
#endif
	
    while(1)
	{
		OSTaskSuspend(OS_PRIO_SELF);
    }
}

