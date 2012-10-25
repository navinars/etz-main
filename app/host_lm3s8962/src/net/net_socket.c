/* ------------------------------------------------------------------------------------------------------
* File: includes.h
* Data: 2012/9/4
* Author: MC
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


/* ------------------------------------------------------------------------------------------------------
 *											Local Define
 * ------------------------------------------------------------------------------------------------------
 */
#ifndef SOCK_TARGET_HOST
#define SOCK_TARGET_HOST  "192.168.2.99"
#endif

#ifndef SOCK_TARGET_PORT
#define SOCK_TARGET_PORT  8093
#endif

#define SOCKET_NEW			1
#define SOCKET_CON			2
#define SOCKET_REC			3
#define SOCKET_CLS			4
#define SOCKET_CHECK		5

#define RS232printf(x)			//UARTprintf(x)

/* ------------------------------------------------------------------------------------------------------
 *											Local Define
 * ------------------------------------------------------------------------------------------------------
 */
int s;																/* Create socket.*/
static unsigned char socket_state;


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
/*void NetDisplayIPAddress(unsigned long ipaddr)
{
	int ret;
    char pucBuf[16];
    unsigned char *pucTemp = (unsigned char *)&ipaddr;

    //
    // Convert the IP Address into a string.
    //
    usprintf(pucBuf, "%d.%d.%d.%d", pucTemp[0], pucTemp[1], pucTemp[2],
             pucTemp[3]);

    //
    // Display the string.
    //
    ret = lwip_write(s, pucBuf, sizeof(pucBuf));
}
*/

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

	memset(&addr, 0, sizeof(addr));							/* set up address to connect to */
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
					
					if(s < 0)
						break;
					
					socket_state = SOCKET_CON;
				}

				case SOCKET_CON:
				{
					unsigned int addr;
					ret = lwip_connect(s, (struct sockaddr*)&addr, sizeof(addr));/* connect */
					
					LWIP_ASSERT("ret == 0", ret == 0);						/* should succeed */
					if(ret < 0)
					{
						lwip_close(s);
						socket_state = SOCKET_NEW;					/* 重复断开连接，可能出问题*/
						break;
		//				RS232printf("socket connect failed\n");
					}
//					addr = lwIPLocalIPAddrGet();
//					NetDisplayIPAddress(addr);
					socket_state = SOCKET_CHECK;
				}
				
				case SOCKET_CHECK:
					// TODO: Check socket connecting.
				
					FD_ZERO(&readset);
					FD_SET(s, &readset);
					FD_ZERO(&writeset);
					FD_SET(s, &writeset);
					FD_ZERO(&errset);
					FD_SET(s, &errset);
					tv.tv_sec = 3;
					tv.tv_usec = 0;									/* Set time out 0, 函数立即返回*/
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
					
					ret = lwip_write(s, "test\n", 6);
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
 * Description : tests blocking and nonblocking connect.
 *
 * Argument(s) : none.
 *
 */
static void sockex_testrecv(void *arg)
{
	for(;;)
	{
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
  sys_thread_new("sockex_nonblocking_connect", sockex_nonblocking_connect, NULL, 128, 2);
  sys_thread_new("sockex_testrecv", sockex_testrecv, NULL, 128, 3);
  /*sys_thread_new("sockex_testtwoselects", sockex_testtwoselects, NULL, 0, 0);*/
}

