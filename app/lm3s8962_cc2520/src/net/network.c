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
#include "utils/lwiplib.h"
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


unsigned char MACAddress[] = My_Mac_ID;
unsigned char IPAddress[] = MY_IP_ID;
unsigned char NetMaskAddr[] = IP_MARK_ID;
unsigned char GwWayAddr[] = MY_GATEWAY_ID;

uint8_t  g_bNetStatus;


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
	lwIPLocalMACGet(MACAddress);
	
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
	switch(g_bNetStatus)
	{
	case NETS_INIT:
//		TcpClientInit();
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
int NetServerInit(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);
	SysCtlPeripheralReset(SYSCTL_PERIPH_ETH);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3, GPIO_DIR_MODE_HW);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
	GPIOPinTypeEthernetLED(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);
	
	lwIP_init();
	sys_thread_new("TcpClt", TcpClientTask, NULL, TASK_UDP_SERVER_STACK_SIZE, TASK_UDP_SERVER_PRIORITY);
	
	return 1;
}


