/* ------------------------------------------------------------------------------------------------------
* File: includes.h
* Data: 2012/9/4
* Author: MC
* Ver: V0.1.1a
* -------------------------------------------------------------------------------------------------------
*/
#ifndef _NETWORK_H
#define _NETWORK_H

/* ------------------------------------------------------------------------------------------------------
 *											Global Define
 * ------------------------------------------------------------------------------------------------------
 */
/*define net status*/
#define NETS_INIT         0   /*lwip init*/
#define NETS_LOCIP        1   /*get local ip*/
#define NETS_SRVIP        2   /*get server ip*/
#define NETS_LOGIN        3   /*login into server*/
#define NETS_NORMAL       4   /*normal data transfer*/

#define ENALE_SERVER_DNS    0x00
#define DISABLE_SERVER_DNS  0x01  

/**************************定义网络通信的IP地址、网关、子网掩码*********************************/
#define My_Mac_ID 	{0X00,0x14,0x97,0x0F,0x1D,0xE3}  //存储以太网控制器的物理地址,即MAC地址
#define IP_MARK_ID 	{255,255,255,0} 		         //255.255.255.0,子网掩码
#define MY_IP_ID       	{192,168,1,25}                   //以太网通信的IP地址
#define MY_GATEWAY_ID   {192,168,1,254}                  //以太网通信的网关地址

/* ------------------------------------------------------------------------------------------------------
 *											Global Variable
 * ------------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------------
 *											Global Function
 * ------------------------------------------------------------------------------------------------------
 */
extern void NetServerInit(void);
 
#endif
