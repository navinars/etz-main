#ifndef BASIC_NET_HANDLE_H
#define BASIC_NET_HANDLE_H

#include "portmacro.h"

#define SERVER_PORT				8090

#define NETBUF_NUM				200								/* Maximum socket buffer number.*/
#define BACKLOG					1								/* Maximum socket client number.*/


extern uint8_t	sock_buf[NETBUF_NUM];
extern int		client_fd[BACKLOG];

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
portTASK_FUNCTION_PROTO( vNetHandle, pvParameters );

#endif

