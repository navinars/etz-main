
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

spi_data_send_t				spi_frm_t;
uart_hdr_t					UartHdr;
uart_data_frm_t				uart_frm_t;
static uint8_t				uart_hdr_count;


static unsigned int crc16(unsigned char buff, unsigned int fcs);
static void spi_transmit(spi_data_send_t *p);

volatile uint8_t g_uc_state = STATE_READ;;
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
 * \param spi
 * 
 * \return void
 */
void uart_transmit( uart_data_frm_t* pdata ) 
{
	uint8_t i;
	
	for (i = 0;i < pdata->txlen;i ++)
	{
		while (uart_write(CONF_UART, pdata->txbuf[i]));
	}
	
	pdata->alloc	= true;
	pdata->rxlen	= 7;
	uart_hdr_count  = 0;
	
	vTaskDelay(20);												/* waiting to received data.*/
//	assert(!"The method or operation is not implemented.");
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
		
		ret = lwip_write(pdata->port, &pdata->rxbuf[0], pdata->rxlen - 1);
		
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
				uart_frm_t.txlen = len + 2;
				
				crc = Crc16CheckSum( &uart_frm_t.txbuf[0], len );
				*((uint16_t *)&uart_frm_t.txbuf[len]) = crc;
				
				uart_data_handle( &uart_frm_t );				/* process spi receive data function.*/
				
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
		if (uart_read(CONF_UART, &uart_frm_t.rxbuf[uart_hdr_count]) == 0)
		{
			uart_hdr_count ++;
		}
		if (uart_hdr_count > 8)
		{
			uart_frm_t.alloc = true;
			uart_hdr_count   = 0;
		}
	}
}
