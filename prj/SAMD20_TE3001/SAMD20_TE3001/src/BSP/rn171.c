#include "asf.h"
#include <string.h>

#include "rn171.h"

uint8_t  gRecieveBuffer[HOST_APP_RX_MAX_BUFFER_SIZE];
uint8_t  gTransmitBuffer[HOST_APP_TX_MAX_BUFFER_SIZE];
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
 * \return void
 */
void rn171_cmd_rw( uint8_t *pdata, uint8_t len )
{
	usart_write_buffer_wait( &usart_instance, pdata, len);

	delay_ms( 100 );
}

/**
 * \brief
 *
 * \param pdata
 *
 * \return uint8_t
 */
uint8_t rn171_cmd_parse( uint8_t* pBuffer )
{

	if( (strstr((const char *)pBuffer,"CMD") != NULL) )
	{
		return HOST_APP_MSG_ID_OK;
	}
	else if( (strstr((const char *)pBuffer,"OK") != NULL) )
	{
		return HOST_APP_MSG_ID_ERROR;
	}
	else if (  (strstr((const char *)pBuffer,"ERROR") != NULL))
	{
		return HOST_APP_MSG_ID_INVALID_INPUT;
	}
	return 0;
}

/**
 * \brief
 *
 * \param
 *
 * \return void
 */
void rn171_int_handle( void )
{
	//rn171_data_handle(rxdata);
}

/**
 * \brief
 *
 * \param
 *
 * \return void
 */
void rn171_init( void )
{
	delay_ms( 10 );
	rn171_cmd_rw( RN171_CMD_START, strlen(RN171_CMD_START) );
	rn171_cmd_rw( RN171_CMD_SSID, strlen(RN171_CMD_SSID) );
	rn171_cmd_rw( RN171_CMD_PASS, strlen(RN171_CMD_PASS) );
	rn171_cmd_rw( RN171_CMD_JOIN, strlen(RN171_CMD_JOIN) );
	rn171_cmd_rw( RN171_CMD_JOIN, strlen(RN171_CMD_JOIN) );
	rn171_cmd_rw( RN171_CMD_JOIN, strlen(RN171_CMD_JOIN) );
}

/**
 * \brief
 *
 * \param dat
 *
 * \return void
 */
void rn171_data_handle( uint8_t rxData )
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
					case 'C':
					{

						break;
					}
					default:
					{
						MRBufferIndex    = 0;
						MRBuffer[MRBufferIndex] = rxData;
						MRBufferIndex++;
						recieve_state = HOST_APP_RX_STATE_CMD_RESP;
						break;
					}
				}
			}
			case HOST_APP_RX_STATE_CMD_RESP:
			{
				if(HOST_APP_LF_CHAR == rxData)
				{
					MRBuffer[MRBufferIndex] = rxData;

					MRBufferIndex++;
					MRBuffer[MRBufferIndex]= '\0';

					rxMsgId = rn171_cmd_parse( MRBuffer );

					if(HOST_APP_MSG_ID_NONE != rxMsgId)
					{

						recieve_state = HOST_APP_RX_STATE_START;
					}
				}
				else if(HOST_APP_ESC_CHAR == rxData)
				{
					recieve_state    = HOST_APP_RX_STATE_START;
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
