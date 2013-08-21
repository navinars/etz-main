/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "asf.h"
#include "conf_board.h"
#include "conf_uart_serial.h"
#include "conf_eth.h"

/* lwIP includes. */
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include "lwip/stats.h"
#include "lwip/init.h"
#include "lwip/sockets.h"
#if ( (LWIP_VERSION) == ((1U << 24) | (3U << 16) | (2U << 8) | (LWIP_VERSION_RC)) )
#include "netif/loopif.h"
#endif

/* Demo includes. */
#include "portmacro.h"

/* APP includes */
#include "uart_handle.h"
#include "net_handle.h"

/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
void uart_config(void)
{
	const sam_uart_opt_t uart_settings = {
		.ul_baudrate = 9600,
		.ul_mode = UART_MR_PAR_NO
	};
	sysclk_enable_peripheral_clock(ID_UART);
	uart_init(ID_UART, &uart_settings);
}

/**
 * \brief 
 * 
 * \param uxPriority
 * 
 * \return void
 */
void vStartUartTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vUartTask, (const signed portCHAR *)"SPILAUNCH",
				TASK_RADIO_STACK_SIZE, NULL, uxPriority,
				(xTaskHandle *)NULL );
}

/**
 * \brief UART handle task..
 * 
 * \param 
 * \param 
 * 
 * \return None
 */
portTASK_FUNCTION_PROTO( vUartTask, pvParameters )
{
	uint8_t	sms_text[] = "AT+SMS=0,0,8615000930605,123456";
	
	(void)pvParameters;
	uart_config();
	uart_write(ID_UART, sms_text);
	
	for (;;)
	{
		vTaskDelay(12);
	}
}

/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
void UART_Handler(void)
{
	uint32_t ul_status;
	
	/* Read USART Status. */
	ul_status = uart_get_status(ID_UART);
	
	/* Receive buffer is full. */
	if (ul_status & UART_SR_RXRDY)
	{		 
	}
}
