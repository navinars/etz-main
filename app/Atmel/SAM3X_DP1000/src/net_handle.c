
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


#define BACKLOG								6

u_char sock_buf[100] = {0};

portTASK_FUNCTION_PROTO( vNetHandle, pvParameters )
{
	int sock_fd, new_fd, max_fd, old_fd = 0;
	socklen_t sin_size;
	int ret, yes = 1;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	
	fd_set fdsr;													/* Create file descriptor.*/
	int conn_amount = 0;
	struct timeval tv;
	
	unsigned int i;
	int fd_A[BACKLOG] = {0};
	
	sock_fd = lwip_socket(AF_INET, SOCK_STREAM, 0);					/* Create new socket.*/
	
																	/* Set socket's options.*/
	ret = lwip_setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	
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
	
	lwip_bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	lwip_listen(sock_fd, BACKLOG + 1);								/* MAX TCP client is BACKLOG.*/
	
	sin_size = sizeof(client_addr);
	max_fd = sock_fd;
	
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
		
		ret = lwip_select(max_fd + 1, &fdsr, NULL, NULL, NULL);
		
		if(ret == 0)												/* If FD is not add, than continue.*/
		{
			continue;
		}
		
		for(i = 0; i < conn_amount; i++)							/* Check every fd in the set.*/
		{
			if (FD_ISSET(fd_A[i], &fdsr))
			{
				u_char	len;
				int opt = 100;										/* set recv timeout (100 ms) */
				lwip_setsockopt(fd_A[i], SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(int));
				
				ret = lwip_read(fd_A[i], &len, 1);
				if (ret > 0)
				{
					len = len - 0x30;								/* Char type to integer type.*/
					ret = lwip_read(fd_A[i], sock_buf, len);		/* receive data to buffers.*/
					if (ret <= 0)
					{
						memset(sock_buf, 0, 100);
					}
					else
					{
						// TODO: Socket frame handle.
						memset(sock_buf, 0, len);
					}
				}
				else if(ret == 0){
					lwip_close(fd_A[i]);							/* Can't decide which socket is closed.*/
				}
				else {
					;
				}
			}
		}
		
		if (FD_ISSET(sock_fd, &fdsr))								/* Check whether a new connection comes.*/
		{
			new_fd = lwip_accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
			
			if (new_fd <= 0) {
				continue;
			}
			if (conn_amount < BACKLOG) {
				fd_A[conn_amount ++] = new_fd;
				
				if(new_fd > max_fd) {
					max_fd = new_fd;
				}
			}
			else {
				lwip_close(fd_A[old_fd]);
				fd_A[old_fd ++] = new_fd;
				
				if (old_fd == BACKLOG) {
					old_fd = 0;
				}
			}
		}
//		vTaskDelay(2);												/* Not need.*/
	}
}

#endif
