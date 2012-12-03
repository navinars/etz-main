/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

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

#ifndef  APP_CFG_MODULE
#define  APP_CFG_MODULE


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*
* Note(s)  (1) The following #define's enables or disables the uC/modules

*              (a) APP_CFG_PROBE_OS_PLUGIN_EN   Enables the uC/OS-II plugin in uC/Probe
*
*              (b) APP_CFG_PROBE_COM_EN         Enables communication in uC/Probe 
*                                               Look at the probe_com_cfg.h file to see all the available 
*                                               comunication methods.
* 
*              (c) APP_CFG_PROBE_DEMO_INTRO_EN  Enables The introductory demo for uC/Probe
*********************************************************************************************************
*/


#define  APP_CFG_PROBE_COM_EN                    DEF_ENABLED     /* DEF_ENABLED = Present, DEF_DISABLED = Not Present    */
#define  APP_CFG_PROBE_OS_PLUGIN_EN              DEF_ENABLED
#define  APP_CFG_PROBE_DEMO_INTRO_EN             DEF_ENABLED


/*
*********************************************************************************************************
*                                            TASKS PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                           	2
#define  APP_CFG_TASK_CC2520_PRIO							4
#define  APP_CFG_TASK_LCD_PRIO								5

#define configETHERNET_INPUT_TASK_PRIORITY					3

/*lwIP TCP/IP stack task.*/
#define  TASK_LWIP_TASK_ISR_PRIO							14
#define  TASK_NET_CLIENT_PRIORITY							11

//
#define  LWIP_TASK_START_PRIO								6
#define  LWIP_TASK_END_PRIO									9

/*uC/OS port task.*/
#define  OS_PROBE_TASK_PRIO              	(OS_LOWEST_PRIO - 3)
#define  OS_TASK_TMR_PRIO                	(OS_LOWEST_PRIO - 2)



/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                            Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  TASK_START_STK_SIZE                     	 50
#define  TASK_CC2520_STK_SIZE                       512
#define  TASK_NET_CLIENT_STACK_SIZE					512
#define  TASK_LCD_STK_SIZE							128
#define  TASK_LWIP_STK_SIZE							512
/*
*********************************************************************************************************
*                               uC/Probe plug-in for uC/OS-II CONFIGURATION
*********************************************************************************************************
*/

#define  OS_PROBE_TASK                                     1    /* Task will be created for uC/Probe OS Plug-In         */
#define  OS_PROBE_TMR_32_BITS                              1    /* uC/Probe OS Plug-In timer is a 32-bit timer          */
#define  OS_PROBE_HOOKS_EN                                 1    /* Hooks to update OS_TCB profiling members will be ... */
                                                                /* ... included                                         */


/*
*********************************************************************************************************
*                                      uC/OS-II DCC CONFIGURATION
*********************************************************************************************************
*/

#define  OS_CPU_ARM_DCC_EN                                 1


/*
*********************************************************************************************************
*                                             uC/LIB CONFIGURATION
*********************************************************************************************************
*/

#define  LIB_MEM_CFG_OPTIMIZE_ASM_EN             DEF_ENABLED
#define  LIB_MEM_CFG_ARG_CHK_EXT_EN              DEF_ENABLED
#define  LIB_MEM_CFG_ALLOC_EN                    DEF_DISABLED


/*
*********************************************************************************************************
*                                        BSP CONFIGURATION
*
* Note(s) : (1) BSP_CFG_SER_COMM_SEL defines the UART to be used to output the system state:
*
*                   BSP_SER_COMM_UART_01           UART #1  is selected to output the system state
*
*                   BSP_SER_COMM_UART_DBG          UART DBG is selected to output the system state
*            
*********************************************************************************************************
*/

#define  BSP_CFG_SER_COMM_SEL                    BSP_SER_COMM_UART_DBG


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#define  TRACE_LEVEL_OFF                                  0
#define  TRACE_LEVEL_INFO                                 1
#define  TRACE_LEVEL_DBG                                  2

#define  APP_CFG_TRACE_LEVEL                       TRACE_LEVEL_INFO
#define  APP_CFG_TRACE                             BSP_SerPrintf           

#define  APP_TRACE_INFO(x)                        ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                         ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)


/*
*********************************************************************************************************
*                                     MODULE CONFIGURATION
*********************************************************************************************************
*/
//#define LCD
//#define CC2520

/*
*********************************************************************************************************
*                                     ENET CONFIGURATION
*********************************************************************************************************
*/
#include "os_cfg.h"
#define portTICK_RATE_MS				( 1000 / OS_TICKS_PER_SEC)

/* MAC address configuration. */
#define configMAC_ADDR0	0x00
#define configMAC_ADDR1	0xCF
#define configMAC_ADDR2	0x52
#define configMAC_ADDR3	0x35
#define configMAC_ADDR4	0x00
#define configMAC_ADDR5	0x01

/* IP address configuration. */
#define configIP_ADDR0		192
#define configIP_ADDR1		168
#define configIP_ADDR2		0
#define configIP_ADDR3		201

/* Netmask configuration. */
#define configNET_MASK0		255
#define configNET_MASK1		255
#define configNET_MASK2		255
#define configNET_MASK3		0

/* Gateway IP address configuration. */
#define configGW_ADDR0	        192
#define configGW_ADDR1	        168
#define configGW_ADDR2	        0
#define configGW_ADDR3	        1

#define configPRIO_BITS         4/*FSL:defined in arm_cm4.h*/

/* The lowest priority. */
#define configKERNEL_INTERRUPT_PRIORITY 	( 15 << (8 - configPRIO_BITS) )
/* Priority 5, or 160 as only the top three bits are implemented. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( 5 << (8 - configPRIO_BITS) )

/*FSL: using multiple buffer for a more efficent use of memory at rx stage by ENET-MAC*/
#define configENET_RX_SINGLE_BUFFER     0/*1: one buffer per frame - 0: multiple buffers per frame*/

#if configENET_RX_SINGLE_BUFFER
#define configENET_RX_BUFFER_SIZE	1520
#if (LWIP_PERF_SETTINGS==1)
#define configNUM_ENET_RX_BUFFERS	12
#else
#define configNUM_ENET_RX_BUFFERS	8
#endif
#else
#define configENET_RX_BUFFER_SIZE	256/*must be PBUF_POOL_BUFSIZE multiple*/
#if (LWIP_PERF_SETTINGS==1)
#define configNUM_ENET_RX_BUFFERS	72
#else
#define configNUM_ENET_RX_BUFFERS	48
#endif
//PBUF_POOL_BUFSIZE macro must be greater than ENET min pkt"
#endif

#define configNUM_ENET_TX_BUFFERS       3//more is useless for this specific driver: might try with lower
#define configENET_TX_BUFFER_SIZE	1520/*no need to reduce this number*/

#define configENET_MAX_PACKET_SIZE      1520
#define configUSE_PROMISCUOUS_MODE	0
#define configUSE_MII_MODE              0/*FSL: using RMII mode*/
#define configETHERNET_INPUT_TASK_STACK_SIZE ( 256 )
//#define configETHERNET_INPUT_TASK_PRIORITY 		//( configMAX_PRIORITIES - 1 )

#ifndef TSIEVB
#define configPHY_ADDRESS	0
#else
#define configPHY_ADDRESS	1
#endif

#if ( configENET_MAX_PACKET_SIZE & 0x0F ) != 0
	#error configENET_BUFFER_SIZE must be a multiple of 16.
#endif

#endif /* FREERTOS_CONFIG_H */


