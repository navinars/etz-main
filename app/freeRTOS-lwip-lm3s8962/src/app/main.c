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
static void prvStartTask(void *pvParameters);
void task_LCD_Init(void);
static void taskLCD(void *parg);


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
*                                             BSP_Init()
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
void BSP_Init(void)
{
	if( DEVICE_IS_REVA2 )
	{
		SysCtlLDOSet( SYSCTL_LDO_2_75V );
	}
	
	/* 使能CPU频率为25MHz*/
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
	
	/*Disable all the interrupts*/
	IntMasterDisable();
	
	RIT128x96x4Init(1000000);
	
    /* 使能总中断*/
	IntMasterEnable();
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
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
	RIT128x96x4StringDraw("lm3s8962 example", 15, 0, 15);
	RIT128x96x4StringDraw("----------------", 15, 8, 15);
	RIT128x96x4StringDraw("IPv4 :", 0, 16, 8);
	RIT128x96x4StringDraw("Mask :", 0, 24, 8);
	RIT128x96x4StringDraw("Gate :", 0, 32, 8);
	RIT128x96x4StringDraw("DNS  :", 0, 40, 8);
	RIT128x96x4StringDraw("MAC  :", 0, 48, 8);
	RIT128x96x4StringDraw("Sver :", 0, 56, 8);
//	RIT128x96x4StringDraw("UID  :", 0, 64, 8);
	
	for(;;)
	{
		vTaskDelay(2);
	}
}

