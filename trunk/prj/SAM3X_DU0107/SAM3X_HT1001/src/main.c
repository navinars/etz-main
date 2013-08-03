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

xTaskHandle vStartTaskHandler = (xTaskHandle)NULL;

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
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
	
	/* Start the ethernet tasks. */
	vStartEthernetTaskLauncher( TASK_START_ETH_PRIORITY );
	
	/* Start the Radio app tasks. */
	vStartRadioTaskLauncher( TASK_RADIO_HANDLE_PRIORITY );
	
	for (;;)
	{
		gpio_toggle_pin(LED0_GPIO);
		vTaskDelay(1000);
		//vTaskSuspend(vStartTaskHandler);							/* Suspend START task. */
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
