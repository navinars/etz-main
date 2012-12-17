/*
*********************************************************************************************************
*
*                                          lm3s8963-lwIP/Main
*                                           INTRODUCTION DEMO
*
*
* Filename      : main.c
* Version       : V0.01
* Programmer(s) : MC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

/*
*********************************************************************************************************
*                                         LOCAL FUNCIONS
*********************************************************************************************************
*/
void BSP_Init(void);
void task_LCD_Init(void);
static void taskLCD(void *parg);
static void prvStartTask(void *pvParameters);


/********************************************************************************************************
*                                             main()
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
int main(void)
{
	BSP_Init();
	
	xTaskCreate( prvStartTask, ( signed char * ) "prvStartTask",
				configMINIMAL_STACK_SIZE, NULL, TASK_START_TASK_PRIORITY, NULL );

	/* Start the tasks running. */
	vTaskStartScheduler();
	
	return (0);
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
static void prvStartTask(void *pvParameters)
{
	(void) pvParameters;
	
	task_LCD_Init();
	
	NetServerInit();
	
	for (;;)
	{
		vTaskSuspend( NULL );			//挂起这个任务
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
	xTaskCreate( taskLCD, ( signed char * ) "taskLCD",
				configMINIMAL_STACK_SIZE, NULL, TASK_LCD_TASK_PRIORITY, NULL );
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
static void taskLCD(void *parg)
{
	RIT128x96x4Init(1000000);
	// Enable LCD
	RIT128x96x4Enable(1000000);
	RIT128x96x4StringDraw("lwIP1.32 RTOS7.1.1", 15, 0, 15);
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
		BSP_LedToggle(1);
		vTaskDelay(500);
	}
}

/********************************************************************************************************
*                                        vApplicationStackOverflowHook()
*
* Description : freeRTOS hook function.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : 堆栈检查钩子函数.
*/
void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed portCHAR *pcTaskName )
{
	( void ) pxTask;
	( void ) pcTaskName;

    
    UARTprintf("Stack Overflow : ");
    UARTprintf((const char*)pcTaskName);
    
	for( ;; );
}
