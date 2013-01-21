/* ------------------------------------------------------------------------------------------------------
 * File: app_cc2520.c
 * Data: 2012/10/20
 * Author: MC
 * Ver: V0.1.1b
 * -------------------------------------------------------------------------------------------------------
 */
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Defines
 * ------------------------------------------------------------------------------------------------------
 */



/* ------------------------------------------------------------------------------------------------------
 *											Local Variables
 * ------------------------------------------------------------------------------------------------------
 */
static OS_STK  Task_CC2520Stk[TASK_CC2520_STK_SIZE];



/* ------------------------------------------------------------------------------------------------------
 *											Local Functions
 * ------------------------------------------------------------------------------------------------------
 */
static  void  App_TaskCC2520 (void *p_arg);



/* ------------------------------------------------------------------------------------------------------
 *									   		App_TaskLCD()
 *
 * Description : Creat LCD task.
 *
 * Argument(s) : none.
 *
 */
void TaskCC2520_Create(void)
{
	OSTaskCreate (App_TaskCC2520, (void *)0,
				  &Task_CC2520Stk[TASK_CC2520_STK_SIZE-1], 
				  APP_CFG_TASK_CC2520_PRIO);
}

/* ------------------------------------------------------------------------------------------------------
 *									App_TaskLED()
 *
 * Description : Task LED function.
 *
 * Argument(s) : none.
 *
 */

static  void  App_TaskCC2520 (void *p_arg)
{
	(void)p_arg;
	
	cc2520_arch_init();												/* Initialise CC2520 GPIO1~4.*/
	
	mac_init();
	
	while(1)														/* task process.*/
	{
		mac_event_handle();											/* Radio Rx event handle.*/
//		mac_host_bcn(50);
//		BSP_LedToggle(1);
		OSTimeDlyHMSM(0, 0, 0, 2);									/* OS delay 2ms.*/
	}
}
