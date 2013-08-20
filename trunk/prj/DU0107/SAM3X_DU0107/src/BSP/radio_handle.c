
#include <asf.h>
#include <string.h>

#include "conf_board.h"
#include "conf_eth.h"

/* Demo includes. */
/* Demo app includes. */
#include "portmacro.h"

/* lwIP includes */
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include "lwip/stats.h"
#include "lwip/init.h"
#include "lwip/sockets.h"
#if ( (LWIP_VERSION) == ((1U << 24) | (3U << 16) | (2U << 8) | (LWIP_VERSION_RC)) )
#include "netif/loopif.h"
#endif

/* ethernet includes */
#include "ethernet.h"
#include "net_handle.h"

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
	
	rQueueISR = xQueueCreate(2, sizeof(unsigned portLONG));
	if( rQueueISR == 0 )
	{
		
	}
	
	Radio_Init();													// init cc1101.
	
	for(;;)
	{
		if( xQueueReceive(rQueueISR, &(frm[0]), 10) == pdTRUE)
		{
			uint8_t i = 0;
			uint8_t ul_eth_data[] = "alarm";
			// handle received data.
			// Send gsm message to cell.
			// Send data through ethernet.
			for(i = 0;i < BACKLOG;i ++)
			{
				if(client_fd[i] != 0)
				{
					lwip_write(client_fd[i], ul_eth_data, sizeof(ul_eth_data));
				}
			}
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
				TASK_RADIO_STACK_SIZE, NULL, uxPriority,
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
	portBASE_TYPE xHigherPriorityTaskWoken = pdTRUE;
	
	phy.alloc = true;
	phy.len = Radio_ReadFifo(phy.buf);
	
	if(phy.len == 4) {
		
		xQueueSendFromISR(rQueueISR, &phy.buf[0], &xHigherPriorityTaskWoken);
		
	}
	
	memset(&phy, 0, sizeof(phy_buf_t));
	
	Radio_ClearRcvFifo();
	Radio_RcvMode();
	
	if(xHigherPriorityTaskWoken) {
		taskYIELD();
	}
}
