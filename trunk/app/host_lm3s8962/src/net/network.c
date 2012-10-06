/*
*********************************************************************************************************
*
*                                       APPLICATION CONFIGURATION
*
*                                          Atmel AT91SAM3U4
*                                                on the
*                                 Atmel AT91SAM3U-EK Development Board.
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/
#include <stdint.h>
#include "network.h"
#include "app_cfg.h"
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

#include "ping.h"
#include "rit128x96x4.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
OS_STK  Task_Eth_Stk[TASK_NET_CLIENT_STACK_SIZE];

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
err_t lwIP_init(void)
{
	err_t err = ERR_OK;
//	struct ip_addr stIpAddr, stNetMsk, stGatWay;

	/*load local net parameter*/
//	lwIPLocalMACGet(MACAddress);
	
	/*use dhcp mode*/
	lwIPInit(MACAddress, 0, 0, 0, IPADDR_USE_DHCP);

	g_bNetStatus = NETS_INIT;
	return err;
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

		// Enable LCD
		RIT128x96x4Enable(1000000);
		DisplayIPAddress(g_sClientIP.s_addr, 36, 16);
		g_sClientIP.s_addr = lwIPLocalNetMaskGet();//获取子网掩码
        DisplayIPAddress(g_sClientIP.s_addr, 36, 24);
        g_sClientIP.s_addr = lwIPLocalGWAddrGet();//获取网关
        DisplayIPAddress(g_sClientIP.s_addr, 36, 32);
		//Disable LCD
        RIT128x96x4Disable();
		g_bNetStatus = NETS_LOCIP;
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
void NetServerInit(void)
{
	//
	// Enable and Reset the Ethernet Controller.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);
	SysCtlPeripheralReset(SYSCTL_PERIPH_ETH);

	//
	// Enable Port F for Ethernet LEDs.
	//  LED0        Bit 3   Output
	//  LED1        Bit 2   Output
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeEthernetLED(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);

	lwIP_init();
	
//	ping_init();
	
	//创建TCP/IP应用任务
	OSTaskCreate(TcpClientTask,
				 (void *)0,
				 &Task_Eth_Stk[TASK_NET_CLIENT_STACK_SIZE-1],
				 TASK_NET_CLIENT_PRIORITY);
//	sys_thread_new("TcpClt", TcpClientTask, NULL, TASK_UDP_SERVER_STACK_SIZE, TASK_UDP_SERVER_PRIORITY);
}



//*****************************************************************************
//
// Display an lwIP type IP Address.
//
//*****************************************************************************
void DisplayIPAddress(unsigned long ipaddr, unsigned long ulCol,
                 unsigned long ulRow)
{
    char pucBuf[16];
    unsigned char *pucTemp = (unsigned char *)&ipaddr;

    //
    // Convert the IP Address into a string.
    //
    usprintf(pucBuf, "%d.%d.%d.%d", pucTemp[0], pucTemp[1], pucTemp[2],
             pucTemp[3]);

    //
    // Display the string.
    //
    RIT128x96x4StringDraw(pucBuf, ulCol, ulRow, 15);
}

