
/*
  Implements a simplistic WEB server.  Every time a connection is made and
  data is received a dynamic page that shows the current FreeRTOS.org kernel
  statistics is generated and returned.  The connection is then closed.

  This file was adapted from a FreeRTOS lwIP slip demo supplied by a third
  party.
*/
#include "asf.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "conf_eth.h"

/* Demo includes. */
/* Demo app includes. */
#include "portmacro.h"

/* lwIP includes. */
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"
#include "lwip/stats.h"
#include "lwip/init.h"
#if ( (LWIP_VERSION) == ((1U << 24) | (3U << 16) | (2U << 8) | (LWIP_VERSION_RC)) )
#include "netif/loopif.h"
#endif

/* ethernet includes */
#include "net_config.h"
#include "ethernet.h"
#include "BasicWEB.h"

/*! The size of the buffer in which the dynamic WEB page is created. */
#define webMAX_PAGE_SIZE	1024

/*! Standard GET response. */
#define webHTTP_OK	"HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n"

/*! The port on which we listen. */
#define webHTTP_PORT		( 80 )

/*! Delay on close error. */
#define webSHORT_DELAY		( 10 )

/*! Format of the dynamic page that is returned on each connection. */
#define webHTML_START \
"<html>\
<head>\
</head>\
<BODY bgcolor=\"#FFFFFF\" text=\"#2477E6\"><form method='get'>\
\r\n\
\r\n</pre>\
\r\n</font>\
\r\n</p><span>网络模式: <select name='dhcp'><option value=1>固定IP</option><option value=2>DHCP</option></select></p>\
\r\n<span>IP 地址 :</span><span> 192.168.</span><span><input type='text' size = 3 name='msg_ip2' /></span><input type='text' size = 3 name='msg_ip3' /></p>\
\r\n<span>子网掩码: 255.255.255.0</span></p>\
"

#define webHTML_END \
"\r\n<input type='submit' /></form></BODY>\
</html>"

portCHAR cDynamicPage[ webMAX_PAGE_SIZE ];
portCHAR cPageHits[ 11 ];

/*! Function to process the current connection */
static void prvweb_ParseHTMLRequest( struct netconn *pxNetCon );


/*! \brief WEB server main task
 *         check for incoming connection and process it
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
portTASK_FUNCTION( vBasicWEBServer, pvParameters );
portTASK_FUNCTION( vBasicWEBServer, pvParameters )
{
struct netconn *pxHTTPListener, *pxNewConnection;

	/* Create a new tcp connection handle */
	pxHTTPListener = netconn_new( NETCONN_TCP );
	netconn_bind(pxHTTPListener, NULL, webHTTP_PORT );
	netconn_listen( pxHTTPListener );

	/* Loop forever */
	for( ;; )
	{
#if ( (LWIP_VERSION) == ((1U << 24) | (3U << 16) | (2U << 8) | (LWIP_VERSION_RC)) )
		/* Wait for a first connection. */
		pxNewConnection = netconn_accept(pxHTTPListener);
#else
        while(netconn_accept(pxHTTPListener, &pxNewConnection) != ERR_OK)
        {
            vTaskDelay( webSHORT_DELAY );
		}
#endif
//		vParTestSetLED(webCONN_LED, pdTRUE);

		if(pxNewConnection != NULL)
		{
			prvweb_ParseHTMLRequest(pxNewConnection);
		}/* end if new connection */

//		vParTestSetLED(webCONN_LED, pdFALSE);

	} /* end infinite loop */
}


/*! \brief parse the incoming request
 *         parse the HTML request and send file
 *
 *  \param pxNetCon   Input. The netconn to use to send and receive data.
 *
 */
static void prvweb_ParseHTMLRequest( struct netconn *pxNetCon )
{
	struct netbuf *pxRxBuffer;
	portCHAR *pcRxString;
	portCHAR pcTxString[30];
	portCHAR pcRxStringTmp[30];
	unsigned portSHORT usLength;

	uint8_t f_write = 0;

#if ( (LWIP_VERSION) == ((1U << 24) | (3U << 16) | (2U << 8) | (LWIP_VERSION_RC)) )
	/* We expect to immediately get data. */
	pxRxBuffer = netconn_recv( pxNetCon );
#else
    while(netconn_recv( pxNetCon, &pxRxBuffer) != ERR_OK)
    {
		vTaskDelay( webSHORT_DELAY );
	}
#endif
	if( pxRxBuffer != NULL )
	{
		/* Where is the data? */
		netbuf_data( pxRxBuffer, ( void * ) &pcRxString, &usLength );
		
		/* Is this a GET?  We don't handle anything else. */
		if(( NULL != pcRxString )&& ( !strncmp( pcRxString, "GET", 3 ) ))
		{
			char *str_tmp,*str_len,len, *str_tmp1;
			
			/* Write out the HTTP OK header. */
			netconn_write( pxNetCon, webHTTP_OK, (u16_t) strlen( webHTTP_OK ), NETCONN_COPY );
			
			f_ip_config_tmp.ip[0]	 = ETHERNET_CONF_IPADDR0;
			f_ip_config_tmp.ip[1]	 = ETHERNET_CONF_IPADDR1;
			f_ip_config_tmp.ip[2]	 = 0;
			f_ip_config_tmp.ip[3]    = 0;
			
			str_tmp = strstr(pcRxString, "dhcp");				/* Set net mode..*/
			if ( str_tmp != NULL)
			{
				f_ip_config_tmp.mode = *(str_tmp + 5) - 0x31;
				
				//f_write = 1;
			}
			
			str_tmp = strstr(pcRxString, "msg_ip2");			/* Set IP address..*/
			if (str_tmp != NULL)
			{
				str_len = strstr(str_tmp, "=");
				if (str_len != NULL)
				{
					str_tmp1 = strstr(str_len, "&");
					if (str_tmp1 != NULL)
					{
						uint8_t i;
						len = str_tmp1 - str_len;

						if(len < 5)								/* Textbox number < 5 byte.*/
						{
							for(i = 1;i < len;i ++)
							{
								f_ip_config_tmp.ip[2] = f_ip_config_tmp.ip[2] * 10;
								f_ip_config_tmp.ip[2] += (str_len[i] - 0x30);
							}
						}
						else
						{
							f_ip_config_tmp.ip[2] = 0;
						}
					}
				}
			}
			
			str_tmp = strstr(pcRxString, "msg_ip3");			/* Set IP address..*/
			if (str_tmp != NULL)
			{
				str_len = strstr(str_tmp, "=");
				if (str_len != NULL)
				{
					str_tmp1 = strstr(str_len, " ");
					if (str_tmp1 != NULL)
					{
						uint8_t i;
						len = str_tmp1 - str_len;

						if(len < 5)								/* Textbox number < 5 byte.*/
						{
							for(i = 1;i < len;i ++)
							{
								f_ip_config_tmp.ip[3] = f_ip_config_tmp.ip[3] * 10;
								f_ip_config_tmp.ip[3] += (str_len[i] - 0x30);
							}
						}
						else
						{
							f_ip_config_tmp.ip[3] = 0;
						}
						
						
						if ( (f_ip_config_tmp.ip[2] > 0) && (f_ip_config_tmp.ip[3] > 1))
						{
							f_ip_config_tmp.alloc = IP_CONFIG_ALLOC_TRUE;
							f_write = 1;									/* you can updata FLASH.*/
						}
						else
						{
							f_ip_config_tmp.ip[0]	 = f_ip_config.ip[0];
							f_ip_config_tmp.ip[1]	 = f_ip_config.ip[1];
							f_ip_config_tmp.ip[2]	 = f_ip_config.ip[2];
							f_ip_config_tmp.ip[3]    = f_ip_config.ip[3];
						}
					}
				}
			}
			
			/* Generate the dynamic page... First the page header. */
			strcpy( cDynamicPage, webHTML_START );
			
			memcpy( pcTxString, "MAC 地址:", sizeof("MAC 地址:") );
			sprintf( pcRxStringTmp, " 0x%02X %02X %02X %02X %02X %02X\r\n</p>",
					 f_ip_config.mac[0], f_ip_config.mac[1], f_ip_config.mac[2],
					 f_ip_config.mac[3], f_ip_config.mac[4], f_ip_config.mac[5] );
			strcat( pcTxString, pcRxStringTmp);
			strcat( cDynamicPage, pcTxString );					// display debug information..

			/* ... Finally the page footer. */
			strcat( cDynamicPage, webHTML_END );

			/* Write out the dynamically generated page. */
			netconn_write( pxNetCon, cDynamicPage, (u16_t) strlen( cDynamicPage ), NETCONN_COPY );
		}
		netbuf_delete( pxRxBuffer );
	}

	netconn_close( pxNetCon );
	netconn_delete( pxNetCon );

	if ( f_write == 1)
	{
		uint32_t ul_last_page_addr = LAST_PAGE_ADDRESS;
		uint32_t ul_page_buffer[IFLASH_PAGE_SIZE / sizeof(uint32_t)];
		
		f_write = 0;
		
		/* Initialize flash: 6 wait states for flash writing. */
		flash_init(FLASH_ACCESS_MODE_128, 6);
		
		/* Unlock page */
		flash_unlock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
		
		/* Copy information to FLASH buffer..*/
		memcpy((uint8_t*)ul_page_buffer, (uint8_t *)(&f_ip_config_tmp), sizeof(f_ip_config_tmp));
		
		/* Write page */
		flash_write(ul_last_page_addr, ul_page_buffer, IFLASH_PAGE_SIZE, 1);
		
		/* Lock page */
		flash_lock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
		
		wdt_disable(WDT);
		
		vTaskDelay(3000);										/* delay 3s before reset.*/
		
		rstc_start_software_reset(RSTC);						/* Reset SAM3X with software.*/
	}
}


