/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "trcUser.h"

#include "ethernet.h"
#include "radio_handle.h"
#include "uart_handle.h"
#include "net_config.h"

xTaskHandle vStartTaskHandler = (xTaskHandle)NULL;

void vApplicationMallocFailedHook( void )
{
	
	gpio_set_pin_high(LED0_GPIO);								/* If memory is failed,LED0 is lighted.*/
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

void vApplicationIdleHook (void)
{
	while(1);
}

void task_start(void *pvParameters)
{
	(void) pvParameters;
	
	netmode_init();
	
	vStartEthernetTaskLauncher( TASK_START_ETH_PRIORITY );		/* Start the ethernet tasks. */
	
	//vStartRadioTaskLauncher( TASK_RADIO_HANDLE_PRIORITY );	/* Start the Radio tasks. */
	//
	//vStartUartTaskLauncher( TASK_UART_HANDLE_PRIORITY );		/* Start the Uart task. */
	
	for (;;)
	{
		//gpio_toggle_pin(LED0_GPIO);
		//vTaskDelay(1000);
		vTaskSuspend(vStartTaskHandler);						/* Suspend START task. */
	}
}
/*-----------------------------------------------------------*/

int main (void)
{
	/* Initialize the SAM system */
	sysclk_init();
	
	/* Initialize mcu's peripheral.*/
	board_init();
	
	/* Ensure all priority bits are assigned as preemption priority bits. */
	NVIC_SetPriorityGrouping( 0 );
	
	/* Create freeRTOS START task.*/
	xTaskCreate(task_start, (signed char *)"START", TASK_START_STACKSIZE, NULL,
				TASK_START_PRIORITY, NULL);
	
	/* Start the FreeRTOS + Trace record..*/
	uiTraceStart();
	
	/* Start the scheduler. */
	vTaskStartScheduler();
	
	// Insert application code here, after the board has been initialized.
	return 0;
}
