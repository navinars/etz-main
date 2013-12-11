
/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "asf.h"
#include "conf_board.h"
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
#include "lwip/sockets.h"
#if ( (LWIP_VERSION) == ((1U << 24) | (3U << 16) | (2U << 8) | (LWIP_VERSION_RC)) )
#include "netif/loopif.h"
#endif

/* ethernet includes */
#include "ethernet.h"
#include "BasicWEB.h"
#include "net_config.h"

/* user header file.*/
#include "net_handle.h"
#include "uart_handle.h"

uint8_t sock_buf[NETBUF_NUM];									/* create socket buffer. */
	
xSemaphoreHandle xSemaNetHandle = NULL;							/* initialize freeRTOS's Semaphore.*/

int		client_fd[BACKLOG];										/* create client file describe.*/

/**
 * \brief Net receive data handle..
 * 
 * \param pbuf
 * \param port
 * 
 * \return void
 */
static void eth_data_handle( u_char* pbuf, int port )
{
	u_char len, cmd;
	
	cmd = *(pbuf + 1);
	if( cmd == 0x07 )
	{
		cmd = *(pbuf + 5);
		if(cmd == 0)
		{
			IPsave.mode = 2;
			IPsave.ip[0] = 0;
		}
		else
		{
			IPsave.mode = 1;
			IPsave.ip[0] = cmd;
		}
		{
			uint32_t ul_last_page_addr = LAST_PAGE_ADDRESS;
			uint32_t ul_page_buffer[IFLASH_PAGE_SIZE / sizeof(uint32_t)];
				
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
				
			rstc_start_software_reset(RSTC);				// Reset SAM3X with software..
		}
	}
	else
	{
		uint8_t len = 6;
		
		uart_frm_t.alloc = true;
		uart_frm_t.txlen = 8;
		uart_frm_t.port = port;
		
		memcpy(uart_frm_t.txbuf, pbuf, len);
		/* Take Semaphore in waiting 1 tick.*/
		if (xSemaphoreTake(xSemaNetHandle, ( portTickType ) 3 ) == pdTRUE) { }
	}
	bzero(pbuf, 100);
}

/**
 * \brief 
 * 
 * \param 
 * \param 
 * 
 * \return 
 */
portTASK_FUNCTION_PROTO( vNetHandle, pvParameters )
{
	int listen_fd, new_fd, max_fd, old_fd = 0;
	socklen_t sin_size;
	int ret, yes = 1;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	
	fd_set allset;												/* Create file descriptor.*/
	u_char conn_amount = 0;
	struct timeval tv;
	
	u_char i;
	
	listen_fd = lwip_socket(AF_INET, SOCK_STREAM, 0);			/* Create new socket.*/
	
																/* Set socket's options.*/
	ret = lwip_setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	
	if(ret == -1)
	{
		/* Suspend this task, not kill itself. */
		vTaskSuspend(vNetHandle);
	}
	
	memset(&server_addr, 0, sizeof(server_addr));				/* Clear socket server struct.*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_len = sizeof(server_addr);
	server_addr.sin_port = PP_HTONS(SERVER_PORT);
	server_addr.sin_addr.s_addr = lwIPLocalIPAddrGet();			/* IP_ADDR_ANY is '0.0.0.0'.*/
	
	lwip_bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	lwip_listen(listen_fd, BACKLOG + 1);						/* MAX TCP client is BACKLOG.*/
	
	sin_size = sizeof(client_addr);
	max_fd = listen_fd = 0;
	
	tv.tv_sec = 10;												/* Timeout setting.*/
	tv.tv_usec = 0;
	
	while(1)
	{
		FD_ZERO(&allset);										/* Initialize file descriptor set.*/
		FD_SET(listen_fd, &allset);
		
		for (i = 0; i < BACKLOG; i++)							/* Add active connection to fd set.*/
		{
			if (client_fd[i] != 0) {
				FD_SET(client_fd[i], &allset);
			}
		}
		
		ret = lwip_select(max_fd + 1, &allset, NULL, NULL, &tv);
		
		if(ret < 0)												/* If FD is not add, than continue.*/
		{
			continue;
		}
		
		for(i = 0; i < conn_amount; i++)						/* Check every fd in the set.*/
		{
			if (FD_ISSET(client_fd[i], &allset))
			{
				u_char	len;
				int opt = 10;									/* set recv timeout (100 ms) */
				lwip_setsockopt(client_fd[i], SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(int));
				
				ret = lwip_read(client_fd[i], &sock_buf, sizeof(sock_buf));
				if (ret == 6)
				{
					eth_data_handle( sock_buf, client_fd[i] );	/* !!handle socket data to SPI modle.!!*/
				}
			}
		}
		
		if (FD_ISSET(listen_fd, &allset))						/* Check whether a new connection comes.*/
		{
			new_fd = lwip_accept(listen_fd, (struct sockaddr *)&client_addr, &sin_size);
			
			if (new_fd <= 0) {
				continue;
			}
			if (conn_amount < BACKLOG) {
				client_fd[conn_amount ++] = new_fd;
				
				if(new_fd > max_fd)
					max_fd = new_fd;
			}
			else {
				lwip_close(client_fd[old_fd]);
				client_fd[old_fd ++] = new_fd;
				
				if (old_fd == BACKLOG)
					old_fd = 0;
				
				if(new_fd > max_fd)
					max_fd = new_fd;
			}
		}
//		vTaskDelay(2);											/* No need.*/
	}
}
