/* ------------------------------------------------------------------------------------------------------
 * File: net_tcpip.c
 * Data: 2012/9/4
 * Author: MC
 * Ver: V0.1.1a
 * -------------------------------------------------------------------------------------------------------
 */
#include <common.h>


/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
static struct netif g_sNetIF;										/* The lwIP network interface structure.*/
unsigned char g_bNetStatus;

extern OS_EVENT		*App_LcdMbox;									/* extern mbox.*/

OS_STK  Task_Eth_Stk[TASK_NET_CLIENT_STACK_SIZE];


/* ------------------------------------------------------------------------------------------------------
 *											Local Function
 * ------------------------------------------------------------------------------------------------------
 */
void DisplayIPAddress(unsigned long ipaddr, unsigned long ulCol,
					  unsigned long ulRow);


/* ------------------------------------------------------------------------------------------------------
 *									lwIPLocalIPAddrGet()
 *
 * Description : This function will read and return the currently assigned IP address.
 *
 * Return 	   : Returns the IP address for this interface.
 *
 */
unsigned long lwIPLocalIPAddrGet(void)
{
    return((unsigned long)g_sNetIF.ip_addr.addr);
}

/* ------------------------------------------------------------------------------------------------------
 *									lwIP_init()
 *
 * Description : main function.
 *
 * Argument(s) : none.
 *
 */
void lwIP_init(void)
{
//	struct netconn *pxHTTPListener, *pxNewConnection;
	struct ip_addr  xIpAddr, xNetMast, xGateway;
	extern err_t ethernetif_init( struct netif *netif );

	/* Create and configure the FEC interface. */
	IP4_ADDR( &xIpAddr, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3 );
	IP4_ADDR( &xNetMast, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3 );
	IP4_ADDR( &xGateway, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3 );
 	netif_add( &g_sNetIF, &xIpAddr, &xNetMast, &xGateway, NULL, ethernetif_init, tcpip_input );
// 	
	/*use dhcp mode*/
	tcpip_init(NULL, NULL);
	
	g_bNetStatus = NETS_INIT;
}

/* ------------------------------------------------------------------------------------------------------
 *									TcpClientTask()
 *
 * Description : main function.
 *
 * Argument(s) : none.
 *
 */
static void TcpClientMainProc(void)
{
	struct in_addr  g_sClientIP;
	
	switch(g_bNetStatus)
	{
	case NETS_INIT:
		do
		{
			g_sClientIP.s_addr = lwIPLocalIPAddrGet();
			OSTimeDly(10);
		}while(0 == g_sClientIP.s_addr);
		
		OSMboxPost(App_LcdMbox, (void *)&g_sClientIP.s_addr);		/* Send lcd txt.*/
		
		g_bNetStatus = NETS_LOCIP;									/* Net mode charge LOCIP.*/
	
		TaskSocket_Create();										/* Create Socket task and init.*/
		
		break;

	case NETS_LOCIP:
//		TcpGetLocalIp();
		break;

	case NETS_SRVIP:
//		TcpGetServerIp();
		break;

	case NETS_LOGIN:
//		TcpClientRelogin();
		break;

	case NETS_NORMAL:
//		TcpNormalProc();
		break;

	default:
		break;
	}
}

/* ------------------------------------------------------------------------------------------------------
 *									TcpClientTask()
 *
 * Description : main function.
 *
 * Argument(s) : none.
 *
 */
static void TcpClientTask(void *pArg)
{
	for(;;)
	{
        TcpClientMainProc();
		OSTimeDly(2);
	}
}

/* ------------------------------------------------------------------------------------------------------
 *									NetServerInit()
 *
 * Description : main function.
 *
 * Argument(s) : none.
 *
 */
void TaskTcpip_Create(void)
{
	/*Create TCP/IP application task.*/
	OSTaskCreate(TcpClientTask,
				 (void *)0,
				 &Task_Eth_Stk[TASK_NET_CLIENT_STACK_SIZE-1],
				 TASK_NET_CLIENT_PRIORITY);
//	sys_thread_new("TcpClt", TcpClientTask, NULL, TASK_UDP_SERVER_STACK_SIZE, TASK_UDP_SERVER_PRIORITY);
}

