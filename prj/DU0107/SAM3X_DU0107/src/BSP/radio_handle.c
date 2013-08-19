
#include <asf.h>
#include <string.h>

// From module: FreeRTOS mini Real-Time Kernel
#include <FreeRTOS.h>
#include "task.h"
#include "status_codes.h"

#include "radio_handle.h"
#include "cc1101_radio.h"

phy_buf_t phy;
uint8_t rPHY_Buf[64] = {0};

xQueueHandle rQueueISR;

/**
 * \brief 
 * 
 * \param 
 * \param 
 * 
 * \return 
 */
portTASK_FUNCTION(vAppSpiTask, pvParameters)
{
	uint8_t frm[10];
	
	(void)pvParameters;
	
	rQueueISR = xQueueCreate(10, sizeof(unsigned portLONG));
	if( rQueueISR == 0 )
	{
		
	}
	
	Radio_Init();
	
	for(;;)
	{
		if( xQueueReceive(rQueueISR, &(frm[0]), 10) == pdTRUE)
		{
			// handle received data.
			
			gpio_toggle_pin(LED1_GPIO);
		}
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
void vStartRadioTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vAppSpiTask, (const signed portCHAR *)"SPILAUNCH",
				configMINIMAL_STACK_SIZE, NULL, uxPriority,
				(xTaskHandle *)NULL );
}

/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
void Radio_RcvHandler(void)
{
	portCHAR cIn = 100;
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	
	phy.alloc = true;
	phy.len = Radio_ReadFifo(phy.buf);
	
	if(phy.len == 4) {
		if(phy.buf[1] == 0x05){
			
			xQueueSendFromISR(rQueueISR, &cIn, &xHigherPriorityTaskWoken);
			if(xHigherPriorityTaskWoken) {
				taskYIELD();
			}
		}
	}
	memset(&phy, 0, sizeof(phy_buf_t));
	Radio_ClearRcvFifo();
	Radio_RcvMode();
}
