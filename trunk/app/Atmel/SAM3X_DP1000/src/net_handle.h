#ifndef BASIC_NET_HANDLE_H
#define BASIC_NET_HANDLE_H

#include "portmacro.h"

#define NETBUF_NUM			100

extern u_char sock_buf[NETBUF_NUM];

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
extern unsigned int Crc16CheckSum(unsigned char *ptr, unsigned char length);

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
portTASK_FUNCTION_PROTO( vNetHandle, pvParameters );

#endif

