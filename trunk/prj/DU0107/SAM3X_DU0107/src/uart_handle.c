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

uint8_t gs_ul_read_buffer[100];

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
		.ul_mck = sysclk_get_peripheral_hz(),
		.ul_baudrate = 38400,
		.ul_mode = UART_MR_PAR_NO
	};
	
	const sam_usart_opt_t usart_console_settings = {
		.baudrate = 38400,
		.char_length = US_MR_CHRL_8_BIT,
		.parity_type = US_MR_PAR_NO,
		.stop_bits = US_MR_NBSTOP_1_BIT,
		.channel_mode = US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		.irda_filter = 0
	};
	
	sysclk_enable_peripheral_clock(ID_UART);
	uart_init(UART, &uart_settings);
	
	sysclk_enable_peripheral_clock(BOART_ID_USART0);
	usart_init_rs232(BOARD_USART0, &usart_console_settings, sysclk_get_peripheral_hz());
	
	/* Disable all the interrupts. */
	usart_disable_interrupt(BOARD_USART0, 0xffffffff);

	/* Enable the receiver and transmitter. */
	usart_enable_tx(BOARD_USART0);
	usart_enable_rx(BOARD_USART0);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART0_IRQn);
	
	usart_enable_interrupt(BOARD_USART0, US_IER_RXRDY);
	
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
	uint8_t	i, sms_text[] = "AT+SMS=0,0,8615000930605,123456";
	
	(void)pvParameters;
	
	uart_config();												/* Initialize UART model.*/
	
//	gpio_set_pin_high(SMS_CMD_GPIO);							/* Set DATA/CMD mode. */
	gpio_set_pin_low(SMS_CMD_GPIO);
	gpio_set_pin_high(SMS_RESET_GPIO);							/* Reset SMS model. */
	
	vTaskDelay(10000);
	
	for(i = 0;i < sizeof(sms_text);i ++)
	{
		while(usart_write(BOARD_USART0, sms_text[i]));
	}
	
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
void USART0_Handler(void)
{
	uint32_t ul_status;
	
	/* Read USART Status. */
	ul_status = usart_get_status(BOARD_USART0);
	
	/* Receive buffer is full. */
	if (ul_status & US_CSR_RXRDY)
	{
		usart_read(BOARD_USART0, (uint32_t *)&gs_ul_read_buffer[0]);
	}
}
