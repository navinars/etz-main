/* ------------------------------------------------------------------------------------------------------
 *
 *                                             lwIP1.40/Main
 *                                            INTRODUCTION DEMO
 *
 *
 * Filename      : app.c
 * Data			 : 2012/9/4
 * Version       : V1.01a
 * Programmer(s) : MC
 * ------------------------------------------------------------------------------------------------------
 */
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
static OS_STK  Task_StartStk[TASK_START_STK_SIZE];
OS_EVENT		*App_LcdMbox;
OS_EVENT		*CC2520_RxMbox;
OS_EVENT		*NET_RfMbox;


/* ------------------------------------------------------------------------------------------------------
 *											Local Function
 * ------------------------------------------------------------------------------------------------------
 */
static  void  App_TaskStart (void *p_arg);
static  void  App_EventCreate (void);


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
	
	OSInit(); 														/* Start uC/OS-II init function.*/
	
	OSTaskCreate ( App_TaskStart, 									/* Creat start task.*/
		           (void *)0, 
				   &Task_StartStk[TASK_START_STK_SIZE-1], 
				   APP_CFG_TASK_START_PRIO );
	
	OSStart();
}

/* ------------------------------------------------------------------------------------------------------
 *									App_TaskStart()
 *
 * Description : Task start function.
 *
 * Argument(s) : none.
 *
 */
static  void  App_EventCreate (void)
{
	App_LcdMbox = OSMboxCreate((void *)0);							/* Create LCD dispaly event Mbox. */
	CC2520_RxMbox = OSMboxCreate((void *)0);
	NET_RfMbox = OSMboxCreate((void *)0);
}

/* ------------------------------------------------------------------------------------------------------
 *									App_TaskStart()
 *
 * Description : Task start function.
 *
 * Argument(s) : none.
 *
 */
static  void  App_TaskCreate (void)
{
	TaskTcpip_Create();												/* Create lwIP task and init.*/

#ifdef LCD
	TaskLCD_Create();												/* Create LCD task.*/
#endif
	
#ifdef CC2520
	TaskCC2520_Create();											/* Create CC2520 task.*/
#endif
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
	
	OS_CPU_SysTickInit(SysCtlClockGet() / OS_TICKS_PER_SEC);		/* Initialize the SysTick.*/
	
	lwIP_init();													/* Initialise lwIP stack. */
	
	App_EventCreate();
	
	App_TaskCreate();
	
    while(1)
	{
		OSTaskSuspend(OS_PRIO_SELF);								/* Suspend Start Task.*/
//		OSTimeDlyHMSM(0, 0, 0, 2);									/* Task delay 2ms.*/
    }
}

