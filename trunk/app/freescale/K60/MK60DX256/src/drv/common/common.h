/*
 * File:        common.h
 * Purpose:     File to be included by all project files
 *
 * Notes:
 */

#ifndef _COMMON_H_
#define _COMMON_H_

/********************************************************************/

/*
 * Debug prints ON (#define) or OFF (#undef)
 */
#define DEBUG
#define DEBUG_PRINT

/* 
 * Include the generic CPU header file 
 */
#include "arm_cm4.h"

/* 
 * Include the platform specific header file 
 */
#if (defined(TWR_K40X256))
  #include "k40_tower.h"
#elif (defined(K60DX256))
 #include "k60_tower.h"
#else
  #error "No valid platform defined"
#endif

/* 
 * Include the cpu specific header file 
 */
#if (defined(CPU_MK40N512VMD100))
  #include "MK40N512VMD100.h"
#elif (defined(CPU_MK60N512VMD100))
  #include "MK40N512VMD100.h"
#else
//  #error "No valid CPU defined"
  #include "MK60DZ10.h"
#include "MemMapPtr_MK60DZ10.h"
#endif


/* 
 * Include common utilities
 */
#include "assert.h"
#include "io.h"
//#include "startup.h"
#include "stdlib.h"


/* 
 * Include bsp utilities
 */
#include "sysinit.h"


/* 
 * Include OS
 */
#include <ucos_ii.h>

/* 
 * Include LwIP 1.4.0
 */
#include "lwip/sys.h"
#include "lwip/api.h"
#include "lwip/memp.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/sockets.h"

#include "net_tcpip.h"
#include "net_socket.h"
 
/********************************************************************/

#endif /* _COMMON_H_ */
