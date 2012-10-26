/* ------------------------------------------------------------------------------------------------------
 * File: includes.h
 * Data: 2012/9/4
 * Author: MC
 * Ver: V0.1.1a
 * -------------------------------------------------------------------------------------------------------
 */
#include <stdint.h>

#include "app_cfg.h"
#include "net_tcpip.h"
#include "net_socket.h"

//user file
#include "app_lcd.h"
#include "inc/hw_ints.h"
#include "inc/hw_ethernet.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/ethernet.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "utils/lwiplib.h"
#include "utils/ustdlib.h"

#include "rit128x96x4.h"



/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
OS_STK  Task_Eth_Stk[TASK_NET_CLIENT_STACK_SIZE];

extern OS_EVENT		*App_LcdMbox;

unsigned char MACAddress[] = My_Mac_ID;
unsigned char IPAddress[] = MY_IP_ID;
unsigned char NetMaskAddr[] = IP_MARK_ID;
unsigned char GwWayAddr[] = MY_GATEWAY_ID;

unsigned char g_bNetStatus;

/* ------------------------------------------------------------------------------------------------------
 *											Local Function
 * ------------------------------------------------------------------------------------------------------
 */
void DisplayIPAddress(unsigned long ipaddr, unsigned long ulCol,
					  unsigned long ulRow);


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
//	struct ip_addr stIpAddr, stNetMsk, stGatWay;
	
	/*load local net parameter*/
//	lwIPLocalMACGet(MACAddress);
	
	/*use dhcp mode*/
	lwIPInit(MACAddress, 0, 0, 0, IPADDR_USE_DHCP);
	
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
	INT8U mac[20];
	
	lwIPLocalMACGet(mac);

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
	//����TCP/IPӦ������
	OSTaskCreate(TcpClientTask,
				 (void *)0,
				 &Task_Eth_Stk[TASK_NET_CLIENT_STACK_SIZE-1],
				 TASK_NET_CLIENT_PRIORITY);
//	sys_thread_new("TcpClt", TcpClientTask, NULL, TASK_UDP_SERVER_STACK_SIZE, TASK_UDP_SERVER_PRIORITY);
}

