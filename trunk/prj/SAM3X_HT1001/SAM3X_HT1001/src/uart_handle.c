
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

#define ERROR_DATA_NUM					4

spi_data_send_t				spi_t;
uart_hdr_t					UartHdr;							/**/
static unsigned int crc16(unsigned char buff, unsigned int fcs);
static void spi_transmit(spi_data_send_t *p);

uart_data_rcv_t uart_t;

#define STATE_READ						0
#define STATE_WRITE						1

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
 * \brief SPI data handle function.
 * 
 * \param pdata
 * 
 * \return 
 */
static void uart_data_handle ( spi_data_send_t* pdata )
{
	uint8_t i = 0, a;
	int ret;
	
	spi_data_send_t spi;
	
	memcpy(&spi, pdata, sizeof(spi_data_send_t));					// Copy spi_data to temp struct.
	memcpy(&spi.buf[1], pdata->buf, sizeof(spi.buf));
	spi.buf[0] = 6;
	
	if(spi.port >0)
	{
		spi_transmit(&spi);
		
		a = spi.buf[1];
		while(((a == 0xFF) || (a == 0x00)) && (i < ERROR_DATA_NUM))
		{
			memcpy(&spi, pdata, sizeof(spi_data_send_t));
			memcpy(&spi.buf[1], pdata->buf, sizeof(spi.buf));
			spi.buf[0] = 6;
			
			spi_transmit(&spi);
			vTaskDelay(6);
			a = spi.buf[1];
			i ++;
		}
		
		ret = lwip_write(spi.port, &spi.buf[0], spi.len + 1);
	}
	
	if(ret < 0){
		RS232printf("\n\rAn error occurred lwip_write..");
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
	u_char	len;
	uint8_t i, frm_go[] = {0x01, 0x06, 0x00, 0x01, 0x00, 0x64, 0xD9, 0xE1};
	uint8_t frm_stop[] = {0x01, 0x06, 0x00, 0x01, 0x00, 0xFF, 0x98, 0x4A};
	uint8_t frm_back[] = {0x01, 0x06, 0x00, 0x01, 0x00, 0x00, 0xD8, 0x0A};
	
	(void)pvParameters;
	memset(&spi_t, 0, sizeof(spi_data_send_t));					/* Clear struct spi_t. */
	
	while(1)
	{
		if (xSemaNetHandle != NULL)
		{
			if(xSemaphoreGive( xSemaNetHandle ) == pdTRUE)
			{
				//u_short crc;
				//
				//crc = Crc16CheckSum(&spi_t.buf[0], len);
				//*((u_short *)&spi_t.buf[len]) = crc;
				//
				//RS232printf("0x%x", spi_t.buf[0]);
				//
				//// enable spi receive data function.
				//spi_data_handle( &spi_t );
				//
				//memset(&spi_t, 0, sizeof(spi_data_send_t));	/* clear struct...*/
			}
		}
		for(i = 0;i < sizeof(frm_go);i ++)
		{
			while(uart_write(CONF_UART, frm_go[i]));
		}
		vTaskDelay(5000);
		for(i = 0;i < sizeof(frm_stop);i ++)
		{
			while(uart_write(CONF_UART, frm_stop[i]));
		}
		vTaskDelay(1000);
		for(i = 0;i < sizeof(frm_back);i ++)
		{
			while(uart_write(CONF_UART, frm_back[i]));
		}
		vTaskDelay(5000);
		for(i = 0;i < sizeof(frm_stop);i ++)
		{
			while(uart_write(CONF_UART, frm_stop[i]));
		}
		vTaskDelay(1000);
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
	static uint8_t i = 0;
	
	/* Read USART Status. */
	ul_status = uart_get_status(CONF_UART);
	
	/* Receive buffer is full. */
	if ((ul_status & UART_SR_RXRDY) && (g_uc_state == STATE_READ))
	{
		if (uart_read(CONF_UART, &uart_t.rxbuf[i]) == 0)
		{
			i ++;
		}
		if(i > 8)
		{
			uart_t.alloc = true;
			i = 0;
		}
	}
}
