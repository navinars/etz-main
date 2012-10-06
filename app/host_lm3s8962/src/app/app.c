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
static OS_STK  Task_LCDStk[TASK_LCD_STK_SIZE];



/* ------------------------------------------------------------------------------------------------------
 *											Local Function
 * ------------------------------------------------------------------------------------------------------
 */
static  void  App_TaskStart (void *p_arg);
static  void  App_TaskLED (void *p_arg);
void task_LCD_Init(void);
static  void  App_TaskLCD(void *parg);


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
	
	task_LCD_Init();
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

/********************************************************************************************************
*                                             prvStartTask()
*
* Description : main function.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void task_LCD_Init(void)
{
	OSTaskCreate (App_TaskLCD, (void *)0,   		
				  &Task_LCDStk[TASK_LCD_STK_SIZE-1], 
				  APP_CFG_TASK_LCD_PRIO);
}

/********************************************************************************************************
*                                             prvStartTask()
*
* Description : main function.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
static void App_TaskLCD(void *parg)
{
	RIT128x96x4Init(1000000);
	// Enable LCD
	RIT128x96x4Enable(1000000);
	RIT128x96x4StringDraw("lwIP1.4 uC/OS-2.89", 15, 0, 15);
	RIT128x96x4StringDraw("----------------", 15, 8, 15);
	RIT128x96x4StringDraw("IPv4 :", 0, 16, 8);
	RIT128x96x4StringDraw("Mask :", 0, 24, 8);
	RIT128x96x4StringDraw("Gate :", 0, 32, 8);
	RIT128x96x4StringDraw("DNS  :", 0, 40, 8);
	RIT128x96x4StringDraw("MAC  :", 0, 48, 8);
	RIT128x96x4StringDraw("Sver :", 0, 56, 8);
//	RIT128x96x4StringDraw("UID  :", 0, 64, 8);
	
	//Disable LCD
	RIT128x96x4Disable();
	
	for(;;)
	{
		OSTimeDly(2);
	}
}

