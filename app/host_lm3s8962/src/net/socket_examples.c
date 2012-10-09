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
#include "network.h"
#include "socket_examples.h"

#include "lwip/opt.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Define
 * ------------------------------------------------------------------------------------------------------
 */
#ifndef SOCK_TARGET_HOST
#define SOCK_TARGET_HOST  "192.168.2.99"
#endif

#ifndef SOCK_TARGET_PORT
#define SOCK_TARGET_PORT  8091
#endif


/* ------------------------------------------------------------------------------------------------------
 *									   sockex_nonblocking_connect()
 *
 * Description : tests blocking and nonblocking connect.
 *
 * Argument(s) : none.
 *
 */
static void sockex_nonblocking_connect(void *arg)
{
	int s;
	int ret;
	struct sockaddr_in addr;
	
	LWIP_UNUSED_ARG(arg);
	

	
	for(;;)
	{
		if(g_bNetStatus == NETS_LOCIP)
		{
			/* set up address to connect to */
			memset(&addr, 0, sizeof(addr));
			addr.sin_len = sizeof(addr);
			addr.sin_family = AF_INET;
			addr.sin_port = PP_HTONS(SOCK_TARGET_PORT);
			addr.sin_addr.s_addr = inet_addr(SOCK_TARGET_HOST);

			/* connect */
			ret = lwip_connect(s, (struct sockaddr*)&addr, sizeof(addr));
			/* should succeed */
			LWIP_ASSERT("ret == 0", ret == 0);

			/* write something */
			ret = lwip_write(s, "test", 4);
			LWIP_ASSERT("ret == 4", ret == 4);

			/* close */
			ret = lwip_close(s);
			LWIP_ASSERT("ret == 0", ret == 0);
		}
		OSTimeDly(2000);
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
void socket_examples_init(void)
{
  sys_thread_new("sockex_nonblocking_connect", sockex_nonblocking_connect, NULL, 128, 2);
  sys_thread_new("sockex_testrecv", sockex_testrecv, NULL, 128, 3);
  /*sys_thread_new("sockex_testtwoselects", sockex_testtwoselects, NULL, 0, 0);*/
}

