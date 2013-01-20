/* ------------------------------------------------------------------------------------------------------
 * File: net_socket.h
 * Data: 2012/11/4
 * Author: Stephen
 * Ver: V0.1.2a
 * -------------------------------------------------------------------------------------------------------
 */
#include "common.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Define
 * ------------------------------------------------------------------------------------------------------
 */
#define RS232printf(x)			//UARTprintf(x)


/* ------------------------------------------------------------------------------------------------------
 *											Local Define
 * ------------------------------------------------------------------------------------------------------
 */
int s;																/* Create socket.*/
static unsigned char socket_state;
int listenfd, connfd = -1;
extern 	OS_EVENT	*NET_RfMbox;									/* Declare mbox.*/

int fd_A[BACKLOG];				/* Accepted connection fd.*/
int conn_amount;				/* current connection amount.*/

//*****************************************************************************
//
// Display an lwIP type IP Address.
//
//*****************************************************************************
void NetDisplayIPAddress(unsigned long ipaddr)
{
// 	int ret;
//     char pucBuf[16];
//     unsigned char *pucTemp = (unsigned char *)&ipaddr;

    //
    // Convert the IP Address into a string.
    //
//     sprintf(pucBuf, "%d.%d.%d.%d\n", pucTemp[0], pucTemp[1], pucTemp[2],
//              pucTemp[3]);

//     //
//     // Display the string.
//     //
//     ret = lwip_write(s, pucBuf, sizeof(pucBuf));
// 	LWIP_ASSERT("ret == -1", ret == -1);
}

/* ------------------------------------------------------------------------------------------------------
 *									   sockex_nonblocking_connect()
 *
 * Description : tests socket blocking and nonblocking connect.
 *
 * Argument(s) : none.
 *
 */
void sockex_nonblocking_connect(void *arg)
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
					tv.tv_usec = 0;									/* Set time out 3s, 函数立即返回*/
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
void sockex_testrecv(void *arg)
{
//	int ret;
	struct sockaddr_in servaddr, cliaddr;
//	struct timeval tv;
	unsigned long cliaddr_len;
	
	LWIP_UNUSED_ARG(arg);

	memset(&servaddr, 0, sizeof(servaddr));							/* set up address to connect to */
	servaddr.sin_len = sizeof(servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = PP_HTONS(SOCK_HOSR_PORT);
	servaddr.sin_addr.s_addr = lwIPLocalIPAddrGet();				/* Set local IP address.*/

	listenfd = lwip_socket(AF_INET, SOCK_STREAM, 0);

	lwip_bind(listenfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));

	lwip_listen(listenfd, SOCK_HOSR_PORT);

	RS232printf("Accepting connections ...\n");
	
	cliaddr_len = sizeof(cliaddr);
	
	for(;;)
	{
		connfd = lwip_accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		if(connfd <= 0)
		{
			OSTimeDly(2);
			continue;
		}
		else
		{
			connfd = connfd;
			RS232printf("cli is ok!");
		}
//		lwip_select();
		
		OSTimeDly(2);
	}
}


/* ------------------------------------------------------------------------------------------------------
 *									   			sockex_app()
 *
 * Description : Handing socket receive data.
 *
 * Argument(s) : none.
 *
 */
void sockex_app(void *arg)
{
	int opt, ret;
	INT8U sock_rxbuf[50];
//	INT8U len;
	
	LWIP_UNUSED_ARG(arg);
	
	for(;;)
	{
		if(connfd > 0)
		{
			
			opt = 100;												/* set recv timeout (100 ms) */
			lwip_setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(int));

			
			ret = lwip_read(connfd, sock_rxbuf, 8);
			if(ret == -1)
			{
				OSTimeDly(2);
				continue;
			}
			if((sock_rxbuf[0] == 'C')&&(sock_rxbuf[1] == 'o'))		/* Compare start frame.*/
			{
// 				address_t addr;
// 				INT8U mac[8] = {0x00, 0x12, 0x4B, 0x00, 0x01, 0xC0, 0xB7, 0xE0};
// 				
//				len = sock_rxbuf[8];								/* Set frame length.*/
/*				if(len != 0x0F)
				{
					OSTimeDly(2);
					continue;
				}
				*/
//				addr.mode = LONG_ADDR;								/* Using device long address.*/
//				lwip_setsockopt(connfd, SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(int));
//				ret = lwip_read(connfd, sock_rxbuf, len);			/* Read other frame data.*/
/*				if(ret == -1)
				{
					OSTimeDly(2);
					continue;
				}
				*/
// 				utilReverseBuf(mac, 8);
// 				memcpy(addr.long_addr, mac, 8);				/* 提取MAC地址*/
// 				
// 				// DOTO: MAC layer send frame. Using deveice MAC address.
// 				mac_tx_handle(&addr, &sock_rxbuf[7], 1, MAC_DATA);	/* Send command frame.*/
			}
		}
		OSTimeDly(2);
	}
}

/* ------------------------------------------------------------------------------------------------------
 *									      sockex_selects()
 *
 * Description : socket selects test.
 *
 * Argument(s) : none.
 *
 */
void sockex_selects(void *arg)
{
	int sock_fd, new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t sin_size;
	int yes;
	INT8U buf[BUF_SIZE];
	int ret;
	int i;
	
	fd_set fdsr;													/* Create file descriptor.*/
	int maxsock;
	struct timeval tv;
	
	conn_amount = 0;
	LWIP_UNUSED_ARG(arg);
	
	sock_fd = lwip_socket(AF_INET, SOCK_STREAM, 0);
	
	yes = 1;
	ret = lwip_setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	if(ret == -1)
	{
		return;
	}
	
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_len = sizeof(server_addr);
	server_addr.sin_port = PP_HTONS(SOCK_HOSR_PORT);
	server_addr.sin_addr.s_addr = lwIPLocalIPAddrGet();				/* IP_ADDR_ANY is '0.0.0.0'.*/
	
	lwip_bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	lwip_listen(sock_fd, BACKLOG + 1);								/* MAX TCP client is BACKLOG.*/
	
	sin_size = sizeof(client_addr);
	maxsock = sock_fd;
	

	
	while(1)
	{
		FD_ZERO(&fdsr);												/* Initialize file descriptor set.*/
		FD_SET(sock_fd, &fdsr);

		tv.tv_sec = 10;												/* Timeout setting.*/
		tv.tv_usec = 0;
		
		for (i = 0; i < BACKLOG; i++)								/* Add active connection to fd set.*/
		{								
			if (fd_A[i] != 0) {
				FD_SET(fd_A[i], &fdsr);
			}
		}
		
		ret = lwip_select(maxsock + 1, &fdsr, NULL, NULL, &tv);
		if(ret < 0)
		{
			break;
		}
		else if(ret == 0)
		{
			continue;
		}
		
		for (i = 0; i < conn_amount; i++)							/* Check every fd in the set.*/
		{
			if (FD_ISSET(fd_A[i], &fdsr))
			{
				int opt = 100;										/* set recv timeout (100 ms) */
				lwip_setsockopt(fd_A[i], SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(int));

				ret = lwip_read(fd_A[i], buf, 8);
				if (ret <= 0)
				{
// 					lwip_close(fd_A[i]);
// 					FD_CLR(fd_A[i], &fdsr);
// 					fd_A[i] = 0;
				}
				else        										/* receive data.*/
				{
					if((buf[0] == 'C')&&(buf[1] == 'o'))
					{
// 						address_t addr;
// 						INT8U mac[8] = {0x00, 0x12, 0x4B, 0x00, 0x01, 0xC0, 0xB7, 0xE0};
// 						addr.mode = LONG_ADDR;
// 						utilReverseBuf(mac, 8);
// 						memcpy(addr.long_addr, mac, 8);
// 						mac_tx_handle(&addr, &buf[7], 1, MAC_DATA);
					}
					if (ret < BUF_SIZE)
						memset(&buf[ret], '\0', 1);
				}
			}
		}

		if(FD_ISSET(sock_fd, &fdsr))								/* Check whether a new connection comes.*/
		{
			new_fd = lwip_accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
			if(new_fd <= 0)
			{
				continue;
			}
//			lwip_send(new_fd, "con", 4, 0);
			if(conn_amount < BACKLOG)								/* Add to fd queue.*/
			{
				fd_A[conn_amount++] = new_fd;
				
				if(new_fd > maxsock)
					maxsock = new_fd;
			}
			else
			{
//				conn_amount = 0;
				lwip_close(fd_A[conn_amount-1]);
				fd_A[conn_amount-1] = new_fd;
				if(new_fd > maxsock)
					maxsock = new_fd;
//				lwip_send(new_fd, "bye", 4, 0);
//				lwip_close(new_fd);									/* Close larger than 5 socket.*/
			}
		}
		
// 		for (i = 0; i < BACKLOG; i++)								/* Close other connections.*/
// 		{
// 			if (fd_A[i] != 0) {
// 				lwip_close(fd_A[i]);
// 			}
// 		}
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
//	sys_thread_new("sockex_testrecv", sockex_testrecv, NULL, 128, 3);
//	sys_thread_new("sockex_app", sockex_app, NULL, 128, 4);
	sys_thread_new("sockex_selects", sockex_selects, NULL, 256, 2);
}

