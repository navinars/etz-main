
#include <string.h>
#include "asf.h"

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

/* HT1000_BSP includes */
#include "ht1000_spi.h"

/* APP includes */
#include "uart_handle.h"
#include "net_handle.h"


#define STATE_READ						0
#define STATE_WRITE						1
#define ERROR_DATA_NUM					4

uart_hdr_t					uart_hdr;
uart_data_frm_t				uart_frm_t;
//static uint8_t			uart_hdr_count;
bool						gf_uart_alloc;

volatile uint8_t g_uc_state = STATE_READ;

volatile static uint8_t  last_cmd;


portTASK_FUNCTION_PROTO( vMotorHandle, pvParameters );
static unsigned int crc16(unsigned char buff, unsigned int fcs);



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
	xTaskCreate( vSpiHandle, (const signed portCHAR *)"SPIHANDLE",
				configMINIMAL_STACK_SIZE + 100, NULL, uxPriority,
				(xTaskHandle *)NULL );
}

/**
 * \brief 
 * 
 * \param buff
 * \param fcs
 * 
 * \return unsigned int
 */
static unsigned int crc16(unsigned char buff, unsigned int fcs)
{
	unsigned char i,temp;
	
	fcs = buff^fcs;
	
	for (i = 0;i < 8;i ++)
	{
		temp = fcs&0x01;
		
		if (temp == 0)
			fcs = fcs >> 1;
		else
		{
			fcs = fcs >> 1;
			fcs = fcs^0xa001;
		}
	}
	return fcs;
}

/**
 * \brief Sum CRC number
 * 
 * \param ptr
 * \param length
 * 
 * \return unsigned int
 */
unsigned int Crc16CheckSum(unsigned char *ptr, unsigned char length)
{
	unsigned int xym;
	
	xym = 0xffff;
	
	while(length --)
	{
		xym = crc16(*ptr, xym);
		ptr ++;
	}
	return xym;
}

/**
 * \brief 
 * 
 * \param net
 * 
 * \return uint8_t
 */
static uint8_t net_data_send( net_frm_send_t *net )
{
	int ret;
	
	ret = lwip_write( net->port, &net->buf[0], net->len );
	
	if (ret < 0 )
	{
		return 1;
	}
	
	return 0;
}

/**
 * \brief 
 * 
 * \param spi
 * 
 * \return void
 */
void uart_transmit( uart_data_frm_t* pdata ) 
{
	uint8_t i, n =0 ;
	
	gf_uart_alloc = true;										/* Lock uart module!! */
	
	memset( &uart_hdr, 0, sizeof(uart_hdr_t));					/**/
	
	for (i = 0;i < pdata->txlen;i ++)
	{
		while (uart_write(CONF_UART, pdata->txbuf[i]))
		{
			//delay_us(100);
			//n ++;
			//if(n > 30)
				//break;
		}
	}
	
	pdata->alloc	= true;
	pdata->rxlen	= 6;
	
	vTaskDelay(20);												/* waiting to received data.*/
	
	memcpy(pdata->rxbuf, uart_hdr.rxbuf, pdata->rxlen);
	
	gf_uart_alloc = false;
}

/**
 * \brief SPI data handle function.
 * 
 * \param pdata
 * 
 * \return 
 */
static void uart_data_handle ( uart_data_frm_t* pdata )
{
	uint8_t i;
	int ret;
	
	if (pdata->port > 0)
	{
		uart_transmit( pdata );
		
		ret = lwip_write(pdata->port, &pdata->rxbuf[0], pdata->rxlen);
		
		if(ret < 0){
			
		}
	}
}

/**
 * \brief SPI handle task..
 * 
 * \param 
 * \param 
 * 
 * \return None
 */
portTASK_FUNCTION_PROTO( vSpiHandle, pvParameters )
{
	uint8_t	len = 6;
	u_short crc;
	
	(void)pvParameters;
	
	while(1)
	{
		if (xSemaNetHandle != NULL)
		{
			if (xSemaphoreGive( xSemaNetHandle) == pdTRUE)
			{
				uart_frm_t.txlen = 8;
				
				crc = Crc16CheckSum( &uart_frm_t.txbuf[0], 6 );
				*((uint16_t *)&uart_frm_t.txbuf[len]) = crc;
				
				if( gf_uart_alloc == true )						/* If uart is sending, delay 20ms. */
				{
					vTaskDelay(20);
				}
				uart_data_handle( &uart_frm_t );				/* process uart receive data function.*/
				
				memset(&uart_frm_t, 0, sizeof(uart_data_frm_t));/* clear struct...*/
			}
		}
		vTaskDelay(1);
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
	ul_status = uart_get_status(CONF_UART);
	
	/* Receive buffer is full. */
	if ((ul_status & UART_SR_RXRDY) && (g_uc_state == STATE_READ))
	{
		if (uart_read(CONF_UART, &uart_hdr.rxbuf[uart_hdr.rxlen]) == 0)
		{
			uart_hdr.rxlen ++;
		}
		if (uart_hdr.rxlen > 7)
		{
			uart_frm_t.alloc = true;
			uart_hdr.rxlen   = 0;
		}
	}
}

/**
 * \brief 
 * 
 * \param uxPriority
 * 
 * \return void
 */
void vStartMotorTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vMotorHandle, (const signed portCHAR *)"MotorTask",
				TASK_MOTOR_STACK_SIZE, NULL, uxPriority,
				(xTaskHandle *)NULL );
}


/**
 * \brief The task of motoring the route.
 * 
 * \param 
 * \param 
 * 
 * \return 
 */
portTASK_FUNCTION_PROTO( vMotorHandle, pvParameters )
{
	uint8_t i = 0;
	uint16_t crc;
	uint8_t last_value = 0xF9, pre_value;
	
	uart_data_frm_t		update_uart;
	net_frm_send_t		update_net;
	
	(void) pvParameters;
	
	for(;;)
	{
		vTaskDelay( 500 );										/* Delay 0.5s.*/
		
		update_uart.txlen = 8;
//		update_uart.port = 1;
		
		update_uart.txbuf[0] = 0x01;
		update_uart.txbuf[1] = 0x03;
		update_uart.txbuf[2] = 0x00;
		update_uart.txbuf[3] = 0x0D;
		update_uart.txbuf[4] = 0x00;
		update_uart.txbuf[5] = 0x01;
		
		crc = Crc16CheckSum( &update_uart.txbuf[0], 6 );		/* calculate CRC value.*/
		*( (uint16_t *)&update_uart.txbuf[6] ) = crc;
		
		if(gf_uart_alloc != true) {								/* when UART isn't sending, process this.*/
			uart_transmit( &update_uart );
		}
		
		pre_value = update_uart.rxbuf[5];
																/* Using last command correct error.*/
		if ( (pre_value > (last_cmd-4)) && (pre_value < (last_cmd+4)) )
		{
			update_uart.rxbuf[5] = last_cmd;
		}
		pre_value = update_uart.rxbuf[5];
																/* Be not sending socket's data when twice value is same.*/
		if ( (pre_value == last_value) || (pre_value == 0xFF) )
		{
			continue;
		}
		
		update_net.alloc	= true;
		update_net.len		= 6;
		//update_net.buf[0]	= 6;
		
		for(i = 0;i < BACKLOG;i ++)
		{
			if( client_fd[i] != 0 )
			{
				update_net.port	= client_fd[i];
				memcpy( &update_net.buf[0], &update_uart.rxbuf[0], update_uart.rxlen );
				
				net_data_send( &update_net );
			}
		}
		memset( &update_uart, 0, sizeof(update_uart));
		last_value = pre_value;
	}
}
