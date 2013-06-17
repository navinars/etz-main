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
#include "spi_handle.h"
#include "net_handle.h"

#define ERROR_DATA_NUM					4

spi_data_send_t spi_t;

static unsigned int crc16(unsigned char buff, unsigned int fcs);
static void spi_transmit(spi_data_send_t *p);


/**
 * \brief 
 * 
 * \param uxPriority
 * 
 * \return void
 */
void vStartSpiTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vSpiHandle, (const signed portCHAR *)"SPIHANDLE",
				configMINIMAL_STACK_SIZE + 550, NULL, uxPriority,
				(xTaskHandle *)NULL );
}

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
 * \param p
 * 
 * \return void
 */
static void spi_transmit(spi_data_send_t* p)
{
	spi_csn0_disable();
	vTaskDelay(1);													/* Wait 20 millisecond.*/
	spi_soft_transfer(&p->buf[1], p->len + 2);
	vTaskDelay(6);													/* Wait 20 millisecond.*/
//	bzero(p, sizeof(spi_data_send_t));
	spi_soft_transfer(&p->buf[1], p->len + 2);						/* Update to spi.buf[].*/
	spi_csn0_enable();
}

/**
 * \brief SPI data handle function.
 * 
 * \param pdata
 * 
 * \return 
 */
static void spi_data_handle ( spi_data_send_t* pdata )
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
	
	(void)pvParameters;
	memset(&spi_t, 0, sizeof(spi_data_send_t));						/* Clear struct spi_t. */
	
	while(1)
	{
		if (xSemaNetHandle != NULL)
		{
			if(xSemaphoreGive( xSemaNetHandle ) == pdTRUE)
			{
				u_short crc;
				
				RS232printf("\r\nSPI_HANDLE is running...");
				
				len = spi_t.len;
				
				crc = Crc16CheckSum(&spi_t.buf[0], len);
				*((u_short *)&spi_t.buf[len]) = crc;
				
				RS232printf("0x%x", spi_t.buf[0]);
				
				// enable spi receive data function.
				spi_data_handle( &spi_t );
				
				memset(&spi_t, 0, sizeof(spi_data_send_t));			/* clear struct...*/
			}
		}
		vTaskDelay(1);
	}
}

