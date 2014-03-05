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
#include "sl808x.h"
#include "uart_handle.h"
#include "net_handle.h"


uint8_t  gRecieveBuffer[HOST_APP_RX_MAX_BUFFER_SIZE];
//uint8_t  gTransmitBuffer[HOST_APP_TX_MAX_BUFFER_SIZE];
uint16_t gRecieveIndex = 0;
uint8_t  gRecieveFlag = 0;
uint8_t  MRBuffer[HOST_APP_RX_CMD_MAX_SIZE];
uint16_t MRBufferIndex = 0;


HOST_APP_MSG_ID_E    rxMsgId = HOST_APP_MSG_ID_NONE;


/**
 * \brief
 *
 * \param pdata
 * \param len
 *
 * \return HOST_APP_MSG_ID_E
 */
HOST_APP_MSG_ID_E sl808x_cmd_rw( char *pdata, uint8_t len )
{
	usart_serial_write_packet( BOARD_USART0, (uint8_t *)pdata, len );

	delay_ms(1000);

	return (rxMsgId);
}

/**
 * \brief
 *
 * \param pBuffer
 *
 * \return HOST_APP_MSG_ID_E
 */
HOST_APP_MSG_ID_E sl808x_cmd_parse( uint8_t* pBuffer )
{
	if( (strstr((const char *)pBuffer,"OK") != NULL) )
	{
		return HOST_APP_MSG_ID_OK;
	}
	else if( (strstr((const char *)pBuffer,"ERROR") != NULL) )
	{
		return HOST_APP_MSG_ID_OK;
	}

	return HOST_APP_MSG_ID_NONE;
}

/**
 * \brief
 *
 * \param rxData
 *
 * \return void
 */
void sl808x_data_handle( uint8_t rxData )
{
	static HOST_APP_RX_STATE_E recieve_state    = HOST_APP_RX_STATE_START;
	static uint32_t specialDataLen              = 0;
	static uint8_t  rxCurrentCid                = 0;
	static uint8_t  prevChar                    = 0;
	static uint8_t  specialDataLenCharCount     = 0;

	switch (recieve_state)
	{
		case HOST_APP_RX_STATE_START:
		{
			switch(rxData)
			{
				case '\n':
				{

					break;
				}
				//case 'C':
				//{
				//MRBufferIndex    = 0;
				//MRBuffer[MRBufferIndex] = rxData;
				//MRBufferIndex++;
				//
				//break;
				//}
				default:
				{
					MRBufferIndex    = 0;
					MRBuffer[MRBufferIndex] = rxData;
					MRBufferIndex ++;

					recieve_state = HOST_APP_RX_STATE_CMD_RESP;

					break;
				}
			}
		}
		case HOST_APP_RX_STATE_CMD_RESP:
		{
			if ( HOST_APP_LF_CHAR == rxData )
			{
				MRBuffer[MRBufferIndex] = rxData;

				MRBufferIndex++;
				MRBuffer[MRBufferIndex]= '\n';

				rxMsgId = sl808x_cmd_parse( MRBuffer );

				if(HOST_APP_MSG_ID_NONE != rxMsgId)
				{
					recieve_state = HOST_APP_RX_STATE_START;
				}
			}
			else if (HOST_APP_ESC_CHAR == rxData)
			{
				recieve_state = HOST_APP_RX_STATE_START;
			}
			else
			{
				MRBuffer[MRBufferIndex] = rxData;
				MRBufferIndex++;

				if(MRBufferIndex >= HOST_APP_RX_CMD_MAX_SIZE )
				{
					MRBufferIndex = 0;

					recieve_state	  = HOST_APP_RX_STATE_START;
				}
			}
		}
		case HOST_APP_RX_STATE_DATA_HANDLE:
		{
			break;
		}

		default:
		break;
	}
}
