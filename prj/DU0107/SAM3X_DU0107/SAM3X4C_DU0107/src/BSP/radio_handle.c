
#include "asf.h"

// From module: FreeRTOS mini Real-Time Kernel
#include <FreeRTOS.h>
#include "task.h"
#include "status_codes.h"

#include "cc1101_radio.h"

portTASK_FUNCTION(vAppSpiTask, pvParameters)
{
	(void)pvParameters;
	
	//	configure_cc1101_int();
	
	radio_init();
	
	for(;;)
	{
		vTaskDelay(1000);
	}
}

void vStartSpiTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vAppSpiTask, (const signed portCHAR *)"SPILAUNCH",
	configMINIMAL_STACK_SIZE, NULL, uxPriority,
	(xTaskHandle *)NULL );
}
