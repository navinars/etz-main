/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                             Atmel Xmega128A1 Application Configuration File
*
*                                 (c) Copyright 2007; Micrium; Weston, FL
*                                           All Rights Reserved
*
* File    : APP_CFG.H
* By      : FK
*         : FT
*********************************************************************************************************
*/

#ifndef _APP_CFG_H_
#define _APP_CFG_H_


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_PROBE_COM_EN             DEF_DISABLED         /* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */
#define  APP_CFG_PROBE_OS_PLUGIN_EN       DEF_DISABLED
         
/*
**************************************************************************************************************
*                                             TASK PRIORITIES
**************************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                2
#define  APP_CFG_TASK_KBD_PRIO                  3
#define  APP_CFG_TASK_USER_IF_PRIO              4

#define  OS_PROBE_TASK_PRIO                     5
#define  OS_PROBE_TASK_ID                       5

#define  OS_TASK_TMR_PRIO              (OS_LOWEST_PRIO - 2)

/*
**************************************************************************************************************
*                                               STACK SIZES
**************************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE          360
#define  APP_CFG_TASK_USER_IF_STK_SIZE        360
#define  APP_CFG_TASK_KBD_STK_SIZE            360

#define  APP_CFG_TASK_PROBE_STR_STK_SIZE      360

#define  OS_PROBE_TASK_STK_SIZE               360


/*
**************************************************************************************************************
*                                             BSP CONFIGURATION
**************************************************************************************************************
*/

#define  BSP_CFG_LED_PORT_SEL             BSP_PORT_D

#define  BSP_CFG_PB_PORT_SEL              BSP_PORT_C

#define  BSP_CFG_UART_PORT_SEL            BSP_PORT_C
#define  BSP_CFG_UART_NBR_SEL             BSP_UART_0

/*
*********************************************************************************************************
*                               uC/Probe plug-in for uC/OS-II CONFIGURATION
*********************************************************************************************************
*/

#define  OS_PROBE_TASK                          1               /* Task will be created for uC/Probe OS Plug-In              */
#define  OS_PROBE_HOOKS_EN                      1               /* Hooks to update OS_TCB profiling members will be included */
#define  OS_PROBE_TMR_32_BITS                   0               /* uC/Probe timer is a 32-bit timer                          */
#define  OS_PROBE_TMR_SEL                       1               /* Select timer for uC/Probe OS Plug-In timer                */
#define  OS_PROBE_USE_FP                        0               /* uC/Probe does not use floating-point variables            */

/*
*********************************************************************************************************
*                                        TRACE CONFIGURATION
*********************************************************************************************************
*/

#define  TRACE_LEVEL_OFF                        0
#define  TRACE_LEVEL_INFO                       1
#define  TRACE_LEVEL_DBG                        2

#define  APP_CFG_TRACE_LEVEL           TRACE_LEVEL_INFO
#define  APP_CFG_TRACE                 BSP_Ser_Printf

#define  APP_TRACE_INFO(x)            ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DEBUG(x)           ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG )  ? (void)(APP_CFG_TRACE x) : (void)0)

#define  BSP_CFG_TRACE_LEVEL           TRACE_LEVEL_DBG
#define  BSP_CFG_TRACE                 printf

#define  BSP_TRACE_INFO(x)            ((BSP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(BSP_CFG_TRACE x) : (void)0)
#define  BSP_TRACE_DEBUG(x)           ((BSP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG )  ? (void)(BSP_CFG_TRACE x) : (void)0)

#endif  
