
#if (DATA_USED == 1)

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


portTASK_FUNCTION_PROTO( vNetHandle, pvParameters )
{
	int sock_fd, new_fd;
	socklen_t sin_size;
	int ret;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	
	fd_set fdsr;													/* Create file descriptor.*/
	int maxsock, conn_amount;
	struct timeval tv;
	
	unsigned int i;
	
	sock_fd = lwip_socket(AF_INET, SOCK_STREAM, 0);					/* Create new socket.*/
	
	ret = lwip_setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));/* Set socket's options.*/
	
	if(ret == -1)
	{
		RS232printf("Socket server don't create!!!\n");
		
		/* Kill this task. */
		vTaskDelete(NULL);
	}
	
	memset(&server_addr, 0, sizeof(server_addr));					/* Clear data struct.*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_len = sizeof(server_addr);
	server_addr.sin_port = PP_HTONS(SOCK_HOSR_PORT);
	server_addr.sin_addr.s_addr = lwIPLocalIPAddrGet();				/* IP_ADDR_ANY is '0.0.0.0'.*/
	
	lwip_bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	lwip_listen(sock_fd, BACKLOG + 1);								/* MAX TCP client is BACKLOG.*/
	
	sin_size = sizeof(client_addr);
	maxsock = sock_fd;
	
	while(;;)
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
		
		ret = lwip_select(maxsock + 1, &fdsr, NULL, NULL, NULL);
		
		if(ret == 0)												/* If FD is not add, than continue.*/
		{
			continue;
		}
					
		for(i = 0; i < conn_amount; i++)
		{
			
		}
	}
}

#endif
