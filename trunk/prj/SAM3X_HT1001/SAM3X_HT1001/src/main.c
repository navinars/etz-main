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
#include <string.h>

#include "ethernet.h"
#include "uart_handle.h"
#include "BasicWEB.h"
#include "net_config.h"

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
//	taskDISABLE_INTERRUPTS();
	for( ;; );
}

/**
 * \brief Configure the console UART.
 * 
 * \param 
 * 
 * \return void
 */
static void configure_console(void)
{
	const sam_uart_opt_t uart_serial_options = {
		.ul_mck = sysclk_get_peripheral_hz(),
		.ul_baudrate = CONF_UART_BAUDRATE,
		.ul_mode = UART_MR_PAR_NO
	};
	
	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	uart_init(CONF_UART, &uart_serial_options);
	
	/* Enable all the interrupts. */
	uart_enable_interrupt(CONF_UART, UART_IER_RXRDY);
	
	/* Configure and enable interrupt of UART. */
	NVIC_EnableIRQ(UART_IRQn);
	
	/* Specify that stdout should not be buffered. */
	//setbuf(stdout, NULL);
}

/**
 * \brief 
 * 
 * \param pvParameters
 * 
 * \return void
 */
void task_start(void *pvParameters)
{
	(void) pvParameters;
	
	vSemaphoreCreateBinary(xSemaNetHandle);						/* Create binary semaphore.*/
	
	f_config_handle();											/* init net mode from flash.*/
	
	vStartEthernetTaskLauncher( TASK_START_ETH_PRIORITY );		/* Start the ethernet tasks. */
	
	vStartUartTaskLauncher( TASK_UART_HANDLE_PRIORITY );		/* Start the UART app tasks. */
	
	vStartMotorTaskLauncher( TASK_MOTOR_HANDLE_PRIORITY );		/* Start motor status update tasks.*/
	
	for (;;)
	{
		gpio_toggle_pin(LED0_GPIO);
		vTaskDelay(1000);
		//vTaskSuspend(vStartTaskHandler);						/* Suspend START task. */
	}
}
/*-----------------------------------------------------------*/

int main (void)
{
	/* Initialize the SAM system */
	sysclk_init();
	
	/* Initialize mcu's peripheral.*/
	board_init();
	
	configure_console();										/* Config UART parameters.*/
	
	/* Ensure all priority bits are assigned as preemption priority bits. */
	NVIC_SetPriorityGrouping( 0 );
	
	/* Create freeRTOS START task.*/
	xTaskCreate(task_start, (signed char *)"START", TASK_START_STACKSIZE, NULL,
				TASK_START_PRIORITY, NULL);
	
	/* Start the scheduler. */
	vTaskStartScheduler();
	
	return 0;
	// Insert application code here, after the board has been initialized.
}
