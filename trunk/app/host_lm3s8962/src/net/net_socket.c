/* ------------------------------------------------------------------------------------------------------
* File: includes.h
* Data: 2012/9/4
* Author: Stephen
* Ver: V0.1.1a
* -------------------------------------------------------------------------------------------------------
*/
#include <string.h>
#include <stdio.h>


#include "app_cfg.h"
#include "net_tcpip.h"
#include "net_socket.h"

#include "lwip/opt.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"

#include "utils/lwiplib.h"
#include "utils/ustdlib.h"
#include "utils/uartstdio.h"

#include "ucos_ii.h"
#include "mac.h"

/* ------------------------------------------------------------------------------------------------------
 *											Local Define
 * ------------------------------------------------------------------------------------------------------
 */
#ifndef SOCK_TARGET_HOST
#define SOCK_TARGET_HOST  "192.168.2.99"
#endif

#ifndef SOCK_TARGET_PORT
#define SOCK_TARGET_PORT  8091
#define SOCK_HOSR_PORT		8090
#endif

#define SOCKET_NEW			1
#define SOCKET_CON			2
#define SOCKET_REC			3
#define SOCKET_CLS			4
#define SOCKET_CHECK		5
#define SOCKET_IDIE			6

#define RS232printf(x)			//UARTprintf(x)

/* ------------------------------------------------------------------------------------------------------
 *											Local Define
 * ------------------------------------------------------------------------------------------------------
 */
int s;													/* Create socket.*/
static unsigned char socket_state;
extern 	OS_EVENT	*NET_RfMbox;


/* ------------------------------------------------------------------------------------------------------
 *									   sockex_nonblocking_connect()
 *
 * Description : tests socket blocking and nonblocking connect.
 *
 * Argument(s) : none.
 *
 */
void socket_loop(void)
{
	
}
//*****************************************************************************
//
// Display an lwIP type IP Address.
//
//*****************************************************************************
void NetDisplayIPAddress(unsigned long ipaddr)
{
	int ret;
    char pucBuf[16];
    unsigned char *pucTemp = (unsigned char *)&ipaddr;

    //
    // Convert the IP Address into a string.
    //
    usprintf(pucBuf, "%d.%d.%d.%d\n", pucTemp[0], pucTemp[1], pucTemp[2],
             pucTemp[3]);

    //
    // Display the string.
    //
    ret = lwip_write(s, pucBuf, sizeof(pucBuf));
	LWIP_ASSERT("ret == -1", ret == -1);
}

/* ------------------------------------------------------------------------------------------------------
 *									   sockex_nonblocking_connect()
 *
 * Description : tests socket blocking and nonblocking connect.
 *
 * Argument(s) : none.
 *
 */
static void sockex_nonblocking_connect(void *arg)
{
	int ret;
	struct sockaddr_in addr;
	fd_set readset;
	fd_set writeset;
	fd_set errset;
	struct timeval tv;
	
	LWIP_UNUSED_ARG(arg);

	memset(&addr, 0, sizeof(addr));									/* set up address to connect to */
	addr.sin_len = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = PP_HTONS(SOCK_TARGET_PORT);
	addr.sin_addr.s_addr = inet_addr(SOCK_TARGET_HOST);
	
	socket_state = SOCKET_NEW;
	
	for(;;)
	{
		if(g_bNetStatus == NETS_LOCIP)								/* IP is setted.*/
		{
			switch(socket_state)
			{
				case SOCKET_NEW:
				{
					s = lwip_socket(AF_INET, SOCK_STREAM, 0);
					
					socket_state = SOCKET_CON;
					break;
				}

				case SOCKET_CON:
				{
					unsigned int ip;
					ret = lwip_connect(s, (struct sockaddr*)&addr, sizeof(addr));
					
					LWIP_ASSERT("ret == 0", ret == 0);
					if(ret < 0)
					{
						lwip_close(s);
						socket_state = SOCKET_NEW;
						OSTimeDly(2);
						RS232printf("socket connect failed.\n");
						break;
					}
					ip = lwIPLocalIPAddrGet();
					NetDisplayIPAddress(ip);						/* Socket updata IP address.*/
					socket_state = SOCKET_IDIE;
				}
				
				case SOCKET_IDIE:
				{
					INT8U *msg;
					INT8U err;
					
					msg = (INT8U *)OSMboxPend(NET_RfMbox, 0, &err);	/* Waiting socket writing data.*/			
					
					if(err != OS_ERR_NONE)
						break;
					
					ret = lwip_write(s, msg, 6);				
					if(ret < 0)
					{
						lwip_close(s);
						socket_state = SOCKET_CON;	
					}
				}
				break;
				
				case SOCKET_CHECK:
					// TODO: Check socket connecting.
				
					FD_ZERO(&readset);
					FD_SET(s, &readset);
					FD_ZERO(&writeset);
					FD_SET(s, &writeset);
					FD_ZERO(&errset);
					FD_SET(s, &errset);
				
					tv.tv_sec = 3;
					tv.tv_usec = 0;									/* Set time out 3s, º¯ÊýÁ¢¼´·µ»Ø*/
					ret = lwip_select(s+1, &readset, &writeset, &errset, &tv);
					
					if(ret == 0)
					{
						RS232printf("socket check timeout.\n");
						lwip_close(s);
						socket_state = SOCKET_CON;					/* Reconnect socket.*/
					}
					
					if(FD_ISSET(s, &writeset) == 0)					/* If socket couldn't write.*/
					{
						RS232printf("socket write test error.\n");
						lwip_close(s);
						socket_state = SOCKET_CON;					/* Reconnect socket.*/
					}
					
					ret = lwip_write(s, "test", 6);
					if(ret < 0)
					{
						lwip_close(s);
						socket_state = SOCKET_CON;	
					}
					OSTimeDly(2000);
					break;
				
				default:
					break;
			}
		}
		OSTimeDly(2);
	}
}

/* ------------------------------------------------------------------------------------------------------
 *									   sockex_nonblocking_connect()
 *
 * Description : Handing socket receive data.
 *
 * Argument(s) : none.
 *
 */
static void sockex_testrecv(void *arg)
{
	int listenfd, connfd;
	int ret;
	struct sockaddr_in servaddr, cliaddr;
	struct timeval tv;
	unsigned int cliaddr_len;
	
	LWIP_UNUSED_ARG(arg);

	memset(&servaddr, 0, sizeof(servaddr));							/* set up address to connect to */
	servaddr.sin_len = sizeof(servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = PP_HTONS(SOCK_HOSR_PORT);
	servaddr.sin_addr.s_addr = lwIPLocalIPAddrGet();				/* Set local IP address.*/

	listenfd = lwip_socket(AF_INET, SOCK_STREAM, 0);

	lwip_bind(listenfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));

	lwip_listen(listenfd, 8090);

	RS232printf("Accepting connections ...\n");
	
	for(;;)
	{
		cliaddr_len = sizeof(cliaddr);
																	/* Waiting mbox message.*/
		connfd = lwip_accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		if(connfd == -1)
		{
			OSTimeDly(2);
			continue;
		}
		else
		{
			RS232printf("cli is ok!");
		}
//		lwip_select();
		
		OSTimeDly(2);
	}
}

/* ------------------------------------------------------------------------------------------------------
 *									      socket_examples_init()
 *
 * Description : socket initialisation function.
 *
 * Argument(s) : none.
 *
 */
void TaskSocket_Create(void)
{
//	sys_thread_new("sockex_nonblocking_connect", sockex_nonblocking_connect, NULL, 128, 2);
	sys_thread_new("sockex_testrecv", sockex_testrecv, NULL, 128, 3);
	/*sys_thread_new("sockex_testtwoselects", sockex_testtwoselects, NULL, 0, 0);*/
}

