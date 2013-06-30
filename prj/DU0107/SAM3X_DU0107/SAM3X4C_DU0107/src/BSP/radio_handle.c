
#include "asf.h"

// From module: FreeRTOS mini Real-Time Kernel
#include <FreeRTOS.h>
#include "task.h"
#include "status_codes.h"

#include "radio_handle.h"
#include "cc1101_radio.h"

/*-------------------------------------------------------------------------------------------------
 * @fn          radio_init
 *
 * @brief       Initialize radio.
 *
 * @param       none
 *
 * @return      none
 *
 */
portTASK_FUNCTION(vAppSpiTask, pvParameters)
{
	uint8_t d[] = {0x01,0x02,0x03,0x04,0x05};
		
	(void)pvParameters;
	
	Radio_Init();
	
	for(;;)
	{
//		Radio_Transmit(d, sizeof(d));

		vTaskDelay(1000);
	}
}

/*-------------------------------------------------------------------------------------------------
 * @fn          radio_init
 *
 * @brief       Initialize radio.
 *
 * @param       none
 *
 * @return      none
 *
 */
void vStartSpiTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vAppSpiTask, (const signed portCHAR *)"SPILAUNCH",
				configMINIMAL_STACK_SIZE, NULL, uxPriority,
				(xTaskHandle *)NULL );
}
