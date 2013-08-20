#ifndef BASIC_NET_HANDLE_H
#define BASIC_NET_HANDLE_H

#include "portmacro.h"



#define NETBUF_NUM				100									/* Maximum socket buffer number.*/
#define BACKLOG					6									/* Maximum socket client number.*/


extern int client_fd[BACKLOG];

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
portTASK_FUNCTION_PROTO( vNetHandle, pvParameters );

#endif

