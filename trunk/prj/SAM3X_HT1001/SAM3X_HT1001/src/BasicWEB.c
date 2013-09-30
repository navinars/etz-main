/*****************************************************************************
 *
 * \file
 *
 * \brief Basic WEB Server for AVR32 UC3.
 *
 * Copyright (c) 2009-2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 *****************************************************************************/


/*
  Implements a simplistic WEB server.  Every time a connection is made and
  data is received a dynamic page that shows the current FreeRTOS.org kernel
  statistics is generated and returned.  The connection is then closed.

  This file was adapted from a FreeRTOS lwIP slip demo supplied by a third
  party.
*/
#include "asf.h"

#if (HTTP_USED == 1)


/* Standard includes. */
#include <stdio.h>
#include <string.h>

#include "conf_eth.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
//#include "partest.h"

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
\r\n"

#define webHTML_END \
"\r\n</pre>\
\r\n</font>\
\r\n</p><select name='dhcp'><option value=1>πÃ∂®IP</option><option value=2>DHCP</option></select></p>\
\r\n<span>192.168.1.</span><input type='text' name='msg_ip' /><span>IPµÿ÷∑</span></p>\
\r\n<input type='submit' /></form></BODY>\
</html>"

portCHAR cDynamicPage[ webMAX_PAGE_SIZE ];
portCHAR cPageHits[ 11 ];

ip_save_t IPsave;
ip_save_t IPsave_tmp;

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
			
			//if (( NULL != pcRxString )&& ( !strncmp( pcRxString, "GET", 3 ) ))
			//{
				//
			//}
			str_tmp = strstr(pcRxString, "dhcp");					// Set net mode..
			if ( str_tmp != NULL)
			{
				IPsave.mode = *(str_tmp + 5) - 0x30;
				f_write = 1;
			}
			
			str_tmp = strstr(pcRxString, "msg_ip");					// Set IP address..
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

						if(len < 5)									// Textbox number < 5 byte.
						{
							for(i = 1;i < len;i ++)
							{
								IPsave.ip[0] = IPsave.ip[0] * 10;
								IPsave.ip[0] += (str_len[i] - 0x30);
								
								f_write = 1;						// Can be write FLASH..
							}
						}
					}
				}
			}
			
			/* Generate the dynamic page... First the page header. */
			strcpy( cDynamicPage, webHTML_START );
			
//			strcat( cDynamicPage, pcRxString );						// Web display debug information..

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
		memcpy((uint8_t*)ul_page_buffer, (uint8_t *)(&IPsave), sizeof(ip_save_t));
		
		/* Write page */
		flash_write(ul_last_page_addr, ul_page_buffer, IFLASH_PAGE_SIZE, 1);
		
		/* Lock page */
		flash_lock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
		
		rstc_start_software_reset(RSTC);							// Reset SAM3X with software..
	}
}

#endif

