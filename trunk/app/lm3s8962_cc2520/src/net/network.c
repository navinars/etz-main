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
#include "includes.h"


static struct netif netif;
static uint32_t IPaddress = 0;


static void TcpipInitDone(void *arg);

err_t lwIP_init(void)
{
	err_t err;
	struct ip_addr ipaddr, netmask, gw;
	uint8_t macaddress[6] = {0,0,0,0,0,1};

	sys_sem_t sem;

	sys_init();

	/* Initializes the dynamic memory heap defined by MEM_SIZE.*/
	mem_init();

	/* Initializes the memory pools defined by MEMP_NUM_x.*/
	memp_init();

	pbuf_init();
	netif_init();

	err = sys_sem_new(&sem, 0);
	
	if(err != ERR_OK)
		return err;
	
	tcpip_init(TcpipInitDone, &sem);
    sys_sem_wait(&sem);
    sys_sem_free(&sem);

#if LWIP_DHCP
    /* 启用DHCP服务器 */
    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;
#else
    /* 启用静态IP */
    IP4_ADDR(&ipaddr, 10, 21, 11, 245);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
    IP4_ADDR(&gw, 10, 21, 11, 254);
#endif

//	Set_MAC_Address(macaddress);
    
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &stellarisif_init, &tcpip_input);
    netif_set_default(&netif);
    
#if LWIP_DHCP
//    dhcp_start(&netif);
#endif
    netif_set_up(&netif);
	
	return ERR_OK;
}

static void TcpipInitDone(void *arg)
{
    sys_sem_t *sem;
    sem = arg;
    sys_sem_signal(sem);
}

