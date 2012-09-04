/* ------------------------------------------------------------------------------------------------------
* File: main.c
*
* -------------------------------------------------------------------------------------------------------
*/
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
static OS_STK  Task_StartStk[TASK_START_STK_SIZE];
static OS_STK  Task_LEDStk[TASK_LED_STK_SIZE];
/* Peripheral definitions for EK-LM3S8962 board */

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
	OSInit();
	
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

    /*init os tick*/
	OS_CPU_SysTickInit(SysCtlClockGet() / OS_TICKS_PER_SEC);
	
	OSTaskCreate (App_TaskLED, (void *)0,   		
				  &Task_LEDStk[TASK_LED_STK_SIZE-1], 
				  APP_CFG_TASK_LED_PRIO);
	
	/*task process*/
    while (1) 
	{
		OSTimeDly(2);
//		OSTaskSuspend(OS_PRIO_SELF);
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
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_8MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
	
	/*task process*/
	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
		OSTimeDly(500);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
		OSTimeDly(500);
	}
}
