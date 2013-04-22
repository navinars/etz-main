
#if (DATA_USED == 1)

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
#include "lwip/sockets.h"
#if ( (LWIP_VERSION) == ((1U << 24) | (3U << 16) | (2U << 8) | (LWIP_VERSION_RC)) )
#include "netif/loopif.h"
#endif

/* ethernet includes */
#include "ethernet.h"

/* user header file.*/
#include "net_handle.h"
#include "spi_handle.h"


#define BACKLOG					6

u_char sock_buf[NETBUF_NUM] = {0};
	
int client_fd[BACKLOG] = {0};										/* Inti client file describe.*/
	
xSemaphoreHandle xSemaNetHandle = NULL;

static unsigned int crc16(unsigned char buff, unsigned int fcs);
unsigned int Crc16CheckSum(unsigned char *ptr, unsigned char length);


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

static void eth_data_handle(void)
{
	u_char len;
	u_short crc;
	
	len = sock_buf[0] - 0x30;
	if ((len == 6) && (spi_t.alloc == false))
	{
		spi_t.alloc = true;
		spi_t.len = len;
		
		crc = Crc16CheckSum(&sock_buf[1], len);
		*((u_short *)&sock_buf[len]) = crc;
		
		memcpy(spi_t.buf, &sock_buf[1], len + 2);
																	/* Take semaphore with waiting 1 ticks.*/
		if (xSemaphoreTake(xSemaNetHandle,( portTickType ) 1 ) == pdTRUE)
		{
			;
		}
		bzero(sock_buf, 100);
		memset(&spi_t, 0, sizeof(spi_data_send_t));
	}
	else
	{
		bzero(sock_buf, 100);
	}
}

portTASK_FUNCTION_PROTO( vNetHandle, pvParameters )
{
	int listen_fd, new_fd, max_fd, old_fd = 0;
	socklen_t sin_size;
	int ret, yes = 1;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	
	fd_set allset;													/* Create file descriptor.*/
	u_char conn_amount = 0;
	struct timeval tv;
	
	u_char i;
	
	vSemaphoreCreateBinary(xSemaNetHandle);							/* Create binary semaphore.*/
	RS232printf("\nCreate binary semaphore.");
	
	listen_fd = lwip_socket(AF_INET, SOCK_STREAM, 0);				/* Create new socket.*/
	
																	/* Set socket's options.*/
	ret = lwip_setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	
	if(ret == -1)
	{
		RS232printf("Socket server don't create!!!\n");
		
		/* Suspend this task, not kill itself. */
		vTaskSuspend(vNetHandle);
	}
	
	memset(&server_addr, 0, sizeof(server_addr));					/* Clear socket server struct.*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_len = sizeof(server_addr);
	server_addr.sin_port = PP_HTONS(SOCK_HOSR_PORT);
	server_addr.sin_addr.s_addr = lwIPLocalIPAddrGet();				/* IP_ADDR_ANY is '0.0.0.0'.*/
	
	lwip_bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	lwip_listen(listen_fd, BACKLOG + 1);							/* MAX TCP client is BACKLOG.*/
	
	sin_size = sizeof(client_addr);
	max_fd = listen_fd;
	
	tv.tv_sec = 10;													/* Timeout setting.*/
	tv.tv_usec = 0;
	
	while(1)
	{
		FD_ZERO(&allset);											/* Initialize file descriptor set.*/
		FD_SET(listen_fd, &allset);
		
		for (i = 0; i < BACKLOG; i++)								/* Add active connection to fd set.*/
		{
			if (client_fd[i] != 0) {
				FD_SET(client_fd[i], &allset);
			}
		}
		
		ret = lwip_select(max_fd + 1, &allset, NULL, NULL, &tv);
		
		if(ret < 0)													/* If FD is not add, than continue.*/
		{
			continue;
		}
		
		for(i = 0; i < conn_amount; i++)							/* Check every fd in the set.*/
		{
			if (FD_ISSET(client_fd[i], &allset))
			{
				u_char	len;
				int opt = 100;										/* set recv timeout (100 ms) */
				lwip_setsockopt(client_fd[i], SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(int));
				
				ret = lwip_read(client_fd[i], &sock_buf, 20);
				if (ret > 0)
				{
					len = ret - 1;
					if(len > 16)
					{
						memset(&sock_buf, 0, len);
						continue;
					}
					
					eth_data_handle();
					
					RS232printf("\n\rRead from socket %d", client_fd[i]);
				}
				else if(ret == 0)									/* If read ZERO,than return end of file .*/
				{
				}
				else												/* Read error, than close this socket.*/
				{
					lwip_close(client_fd[i]);						/* Can't decide which socket is closed.*/
					RS232printf("\nClose old socket");
					client_fd[i] = 0;
				}
			}
		}
		
		if (FD_ISSET(listen_fd, &allset))							/* Check whether a new connection comes.*/
		{
			new_fd = lwip_accept(listen_fd, (struct sockaddr *)&client_addr, &sin_size);
			
			if (new_fd <= 0) {
				continue;
			}
			if (conn_amount < BACKLOG) {
				client_fd[conn_amount ++] = new_fd;
				puts("\n\rNew socket");
				
				if(new_fd > max_fd) {
					max_fd = new_fd;
				}
			}
			else {
				lwip_close(client_fd[old_fd]);
				client_fd[old_fd ++] = new_fd;
				
				RS232printf("\nNew socket");
				RS232printf("\nClose old socket");
				
				if (old_fd == BACKLOG) {
					old_fd = 0;
				}
			}
		}
//		vTaskDelay(2);												/* Not need.*/
	}
}

#endif
