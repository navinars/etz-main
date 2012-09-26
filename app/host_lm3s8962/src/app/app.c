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
static OS_STK  Task_LEDStk[TASK_LED_STK_SIZE];



/* ------------------------------------------------------------------------------------------------------
 *											Local Function
 * ------------------------------------------------------------------------------------------------------
 */
static  void  App_TaskStart (void *p_arg);
static  void  App_TaskLED (void *p_arg);


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
	
	/* Start uC/OS-II init function.*/
	OSInit();
	
	/* Creat start task.*/
	OSTaskCreate ( App_TaskStart, 
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

	BSP_LedInit();
	
	/*Initialise LwIP & Ethernet.*/
	NetServerInit();
	
    /*init os tick*/
	OS_CPU_SysTickInit(SysCtlClockGet() / OS_TICKS_PER_SEC);
	
	/* Creat LED task.*/
	OSTaskCreate (App_TaskLED, (void *)0,   		
				  &Task_LEDStk[TASK_LED_STK_SIZE-1], 
				  APP_CFG_TASK_LED_PRIO);
				  
	/*task process*/
    while(1)
	{
		OSTaskSuspend(OS_PRIO_SELF);		//挂起这个任务。
    }
}

/* ------------------------------------------------------------------------------------------------------
 *									App_TaskLED()
 *
 * Description : Task LED function.
 *
 * Argument(s) : none.
 *
 */
static  void  App_TaskLED (void *p_arg)
{
	(void)p_arg;
	
	/*task process*/
	while(1)
	{
		BSP_LedToggle(1);
		OSTimeDly(OS_TICKS_PER_SEC / 2);
	}
}
