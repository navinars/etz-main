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

#define SPI_ERROR_SEQ					3						/* SPI write fail repeat frequency.*/

spi_data_send_t							spi_t;					/* SPI frame.*/
net_frm_send_t							net_t;					/* NET frame.*/
	
xSemaphoreHandle						xSemaMotor = NULL;

uint8_t									last_cmd;

bool									gf_spi_alloc;			/* Global flag for SPI send.*/

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

/**
 * \brief 
 * 
 * \param p
 * 
 * \return void
 */
static void spi_transmit( uint8_t *pdata ,uint8_t len)
{
	uint8_t *p = pdata;
	
	spi_csn0_disable();
	
	vTaskDelay(1);												/* Wait 1 millisecond.*/
	
	spi_soft_transfer( p, len);
	
	vTaskDelay(6);												/* Wait 6 millisecond.*/
	
	spi_soft_transfer( p, len );								/* Update to spi.buf[].*/
	
	spi_csn0_enable();
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
 * \brief SPI data handle function.
 * 
 * \param pdata
 * 
 * \return 
 */
static void spi_data_req( spi_data_send_t* pdata )
{
	
	uint8_t i = 0, tmp_value;
	int ret;
	
	spi_data_send_t tmp;
	memcpy(&tmp, pdata, sizeof(spi_data_send_t));
	
	if ( tmp.port > 0 )											/* socket descriptor must greater than ZERO! */
	{
		do
		{
			memcpy(&tmp, pdata, sizeof(spi_data_send_t));		/* Copy spi_data to temp struct.*/
			
			spi_transmit( &tmp.buf, tmp.len );					/* send spi buffer. */
			
			vTaskDelay(20);
			tmp_value = tmp.buf[1];
			
			i ++;
		}while( (tmp_value == 0xFF) && (i < SPI_ERROR_SEQ) );
		
		memcpy( pdata, &tmp, sizeof(spi_data_send_t) );
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
	uint16_t crc = 0;
	
	(void)pvParameters;
	bzero( &spi_t, sizeof(spi_data_send_t) );
	
	for (;;)
	{
		if ( xSemaNetHandle != NULL )
		{
			if ( xSemaphoreGive( xSemaNetHandle ) == pdTRUE )
			{
				spi_t.len = 8;
				
				crc = Crc16CheckSum( &spi_t.buf[0], 6 );		/* add CRC value. */
				*((uint16_t *)&spi_t.buf[6]) = crc;
				
				gf_spi_alloc = true;
				// enable spi receive data function.
				spi_data_req( &spi_t );
				gf_spi_alloc = false;
				
				net_t.alloc = true;
				net_t.port  = spi_t.port;
				net_t.len	= 7;
				net_t.buf[0]= 6;
				
				memcpy( &net_t.buf[1], &spi_t.buf[0], spi_t.len );
				
				net_data_send( &net_t );
				
				if ( spi_t.buf[5] != 0xFF )
				{
					last_cmd = spi_t.buf[5];
				}
				memset( &spi_t, 0, sizeof(spi_data_send_t) );	/* clear struct...*/
			}
		}
		vTaskDelay(1);
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
 * \brief 
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
	uint8_t last_value = 0xF9,pre_value;
	
	spi_data_send_t update_spi;
	net_frm_send_t  update_net;
	
	(void) pvParameters;
	
	for(;;)
	{
		vTaskDelay( 500 );										/* Delay 0.5s.*/
		update_spi.len = 8;
		update_spi.port = 1;
		
		update_spi.buf[0] = 0x01;
		update_spi.buf[1] = 0x03;
		update_spi.buf[2] = 0x00;
		update_spi.buf[3] = 0x0D;
		update_spi.buf[4] = 0x00;
		update_spi.buf[5] = 0x00;
		
		crc = Crc16CheckSum( &update_spi.buf[0], 6 );
		*( (uint16_t *)&update_spi.buf[6] ) = crc;
		
		if(gf_spi_alloc != true) {								/* when spi isn't sending, process this.*/
			spi_data_req( &update_spi );
		}
		else
		{
			memset( &update_spi, 0, sizeof(spi_data_send_t) );
		}
		
		pre_value = update_spi.buf[5];
																/* Using last command correct error.*/
		if ( (pre_value > (last_cmd-4)) && (pre_value < (last_cmd+4)) )
		{
			update_spi.buf[5] = last_cmd;
		}
		pre_value = update_spi.buf[5];
																/* Be not sending socket's data when twice value is same.*/
		if ( (pre_value == last_value) || (pre_value == 0xFF) )
		{
			continue;
		}
		
		update_net.alloc	= true;
		update_net.len		= 7;
		update_net.buf[0]	= 6;
		
		for(i = 0;i < BACKLOG;i ++)
		{
			if( client_fd[i] != 0 )
			{
				update_net.port	= client_fd[i];
				memcpy( &update_net.buf[1], &update_spi.buf[0], update_spi.len );
				
				net_data_send( &update_net );
			}
		}
		
		last_value = pre_value;
	}
}
