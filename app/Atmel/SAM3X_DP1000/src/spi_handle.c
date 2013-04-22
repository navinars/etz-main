/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "conf_board.h"
#include "conf_eth.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
//#include "partest.h"

/* Demo includes. */
/* Demo app includes. */
#include "portmacro.h"

/* HT1000_BSP includes */
#include "ht1000_spi.h"

/* APP includes */
#include "spi_handle.h"
#include "net_handle.h"

spi_data_send_t spi_t;

void vStartSpiTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vSpiHandle, (const signed portCHAR *)"SPIHANDLE",
				configMINIMAL_STACK_SIZE + 550, NULL, uxPriority,
				(xTaskHandle *)NULL );
}


static spi_data_handle(spi_data_send_t* pdata)
{
//	RS232printf("\r\nSPI_HANDLE is running...");

}

portTASK_FUNCTION_PROTO( vSpiHandle, pvParameters )
{
	
	(void)pvParameters;
	memset(&spi_t, 0, sizeof(spi_data_send_t));
	
	while(1)
	{
		if (xSemaNetHandle != NULL)
		{
			if(xSemaphoreGive( xSemaNetHandle ) == pdTRUE)
			{
				RS232printf("\r\nSPI_HANDLE is running...");
				
				spi_csn0_disable();
				spi_master_transfer(spi_t.buf, spi_t.len);
				vTaskDelay(20);										/* Wait 20 millisecond.*/
				spi_master_transfer(spi_t.buf, spi_t.len);			/* Update to spi.buf[].*/
				spi_csn0_enable();
				
				// enable spi receive data function.
				spi_data_handle(&spi_t);
				
				RS232printf("%4x", sock_buf[0]);
				
				bzero(sock_buf, 20);
			}
		}
		vTaskDelay(2);
	}
}

