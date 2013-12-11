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
#include "spi_handle.h"
#include "BasicWEB.h"

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

void netmode_init(void)
{
	uint32_t ul_last_page_addr = LAST_PAGE_ADDRESS;
	uint32_t *pul_last_page = (uint32_t *) ul_last_page_addr;
	
	//	memset(&IPsave_tmp, 0, sizeof(ip_save_t));
	
	/* Initialize flash: 6 wait states for flash writing. */
	flash_init(FLASH_ACCESS_MODE_128, 6);
	
	/* Unlock page */
	flash_unlock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
	
	/* Read Flash page */
	memcpy((uint8_t*)(&IPsave_tmp), (uint8_t*)pul_last_page, sizeof(ip_save_t));
	
	//	IPsave_tmp.mode = 2;
	
	if ((IPsave_tmp.ip[0] == 0)|| (IPsave_tmp.ip[0] == 0xFF))
	{
		uint32_t ul_last_page_addr = LAST_PAGE_ADDRESS;
		uint32_t ul_page_buffer[IFLASH_PAGE_SIZE / sizeof(uint32_t)];
		
		IPsave_tmp.mode = 1;
		IPsave_tmp.ip[0] = 223;
		
		/* Copy information to FLASH buffer..*/
		memcpy((uint8_t*)ul_page_buffer, (uint8_t *)(&IPsave_tmp), sizeof(ip_save_t));
		
		/* Write page */
		flash_write(ul_last_page_addr, ul_page_buffer, IFLASH_PAGE_SIZE, 1);
	}
	
	if (gpio_pin_is_low(RESTKEY_GPIO) == 1)
	{
		uint32_t ul_last_page_addr = LAST_PAGE_ADDRESS;
		uint32_t ul_page_buffer[IFLASH_PAGE_SIZE / sizeof(uint32_t)];
		
		IPsave_tmp.mode = 1;
		IPsave_tmp.ip[0] = 223;
		
		/* Copy information to FLASH buffer..*/
		memcpy((uint8_t*)ul_page_buffer, (uint8_t *)(&IPsave_tmp), sizeof(ip_save_t));
		
		/* Write page */
		flash_write(ul_last_page_addr, ul_page_buffer, IFLASH_PAGE_SIZE, 1);
	}
	
	/* Lock page */
	flash_lock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
	
}

void task_start(void *pvParameters)
{
	(void) pvParameters;
	
	netmode_init();												/* init net mode from flash.*/
	
	vStartEthernetTaskLauncher( TASK_START_ETH_PRIORITY );		/* Start the ethernet tasks. */
	
	vStartSpiTaskLauncher( TASK_SPI_HANDLE_PRIORITY );			/* Start the SPI app tasks. */
	
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
