/* 
 * Include common utilities
 */
#include "common.h"


static	OS_STK	Task_StartStk[TASK_START_STK_SIZE];

static	void  	App_TaskStart (void *p_arg);

/********************************************************************/

int main (void)
{
	
	OSInit(); 														/* Start uC/OS-II init function.*/
	
	OSTaskCreate ( App_TaskStart, 									/* Creat start task.*/
		           (void *)0, 
				   &Task_StartStk[TASK_START_STK_SIZE-1], 
				   APP_CFG_TASK_START_PRIO );
	
	OSStart();
	
	for(;;)
	{
	}
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
	
//	lwIP_init();													/* Initialise lwIP stack. */
	
//	App_EventCreate();
	
//	App_TaskCreate();
	
	/* Turn on all port clocks */
	SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	
	PORTB_PCR10 &= ~PORT_PCR_MUX_MASK;
	PORTB_PCR10 |= PORT_PCR_MUX(1);
	
	
    while(1)
	{
//		OSTaskSuspend(OS_PRIO_SELF);								/* Suspend Start Task.*/
		GPIOB_PDDR |= (1<<10);
		OSTimeDlyHMSM(0, 0, 1, 0);									/* Task delay 1s.*/
		GPIOB_PDDR &=~(1<<10);
		OSTimeDlyHMSM(0, 0, 1, 0);									/* Task delay 1s.*/
    }
}

