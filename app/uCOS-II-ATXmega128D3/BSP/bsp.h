/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2008; Micrium, Inc.; Weston, FL
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
*                                        BOARD SUPPORT PACKAGE
*
*                                       Atmel ATxmega128A1
*                                              on the 
*                                  ATMEL  STK600 Development Board
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : FT
*               : FK        
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_PRESENT
#define  BSP_PRESENT

/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


#ifdef   BSP_MODULE
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif

/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                  DEFINES
*********************************************************************************************************
*/
                                                                /* ------------------ SYSTEM CKL SOURCE -------------------- */
#define     BSP_SYS_CLK_SRC_RC2M                            1   /* 2  Mhz Internal Oscillator                                */
#define     BSP_SYS_CLK_SRC_RC32M                           2   /* 32 Mhz Internal Oscillator                                */
#define     BSP_SYS_CLK_SRC_RC32K                           3   /* 32 Khz Internal Oscillator                                */
#define     BSP_SYS_CLK_SRC_XOSC                            4   /* External Oscillator/Clk (32K or 0.4-16M XTAL or EXT clk)  */
#define     BSP_SYS_CLK_SRC_PLL                             5   /* Pll output clk                                            */
#define     BSP_SYS_CLK_SRC_UNKNOWN                         6   /* Unkown SYSTEM CLK source clk                              */
                                                                /* ------------------ SYSTEM CKL OUTPUTS ------------------- */
#define     BSP_SYS_CLK_OUT_PER                             1   /* CLKper   clk output                                       */
#define     BSP_SYS_CLK_OUT_PER2                            2   /* CLKper2  clk output                                       */
#define     BSP_SYS_CLK_OUT_PER4                            3   /* CLKper4  clk output                                       */
#define     BSP_SYS_CLK_OUT_CPU                             4   /* CLKcpu   clk output                                       */
                                                                /* ------------------ SYSTEM CKL DIVIDER ID ---------------- */
#define     BSP_SYS_CLK_DIV_A                               1   /* Preescaler A division factor                              */
#define     BSP_SYS_CLK_DIV_BC                              2   /* Preescaler B division factor                              */

                                                                /* ------------------- PLL CKL SOURCE ---------------------- */
#define     BSP_PLL_SRC_RC2M                                1   /* 2     Mhz Internal Oscillator                             */
#define     BSP_PLL_SRC_RC32M                               2   /* 32/4  Mhz Internal Oscillator                             */
#define     BSP_PLL_SRC_XOSC                                3   /* External Oscillator/Clk  (0.4-16 XTAL or EXT clk          */
#define     BSP_PLL_SRC_UNKNOWN                             4   /* Unknow PLL source clk                                     */
                                                                /* ------------------- XTAL NET SOURCE --------------------- */
#define     BSP_XTAL_NET_SRC_LOW_XTAL                       1   /* External 32       Khz XTAL                                */
#define     BSP_XTAL_NET_SRC_HIGH_XTAL                      2   /* External 0.4 - 16 Mhz XTAL                                */
#define     BSP_XTAL_NET_SRC_EXT_CLK                        3   /* External clk                                              */
#define     BSP_XTAL_NET_SRC_UNKNOWN                        4   /* Unkown XTAL NET source clk                                */
                                                                /* ------------------- XMEGA PORTs ID ---------------------- */
#define     BSP_PORT_A                                      1
#define     BSP_PORT_B                                      2
#define     BSP_PORT_C                                      3
#define     BSP_PORT_D                                      4
#define     BSP_PORT_E                                      5
#define     BSP_PORT_F                                      6
#define     BSP_PORT_G                                      7
#define     BSP_PORT_H                                      8

#define     BSP_UART_0                                      1
#define     BSP_UART_1                                      2

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void         BSP_Init               (void);

void         BSP_IntDisAll          (void);
 
CPU_INT32U   BSP_CPU_ClkFreq        (void);

void         BSP_TmrHandler         (void);

/*
*********************************************************************************************************
*                                          PLL FUNCTIONS PROTORYPES
*********************************************************************************************************
*/

CPU_INT32U   BSP_PLL_FreqGet        (void);

CPU_BOOLEAN  BSP_PLL_FreqSet        (CPU_INT32U  freq);

CPU_INT08U   BSP_PLL_SrcGet         (void);

CPU_INT32U   BSP_PLL_SrcGetFreq     (void);

void         BSP_PLL_SrcSet         (CPU_INT08U  clk_src);

/*
*********************************************************************************************************
*                                          SYSTEM CLK FUNCTIONS PROTORYPES
*********************************************************************************************************
*/

void         BSP_SysClk_DevSetPre   (CPU_INT08U  div_id,
                                     CPU_INT08U  div_val);

CPU_INT32U   BSP_SysClk_DevGetFreq  (CPU_INT08U  dev_clk);

CPU_INT32U   BSP_SysClk_FreqGet     (void);

CPU_BOOLEAN  BSP_SysClk_SrcEn       (CPU_INT08U  clk_src,
                                     CPU_INT16U  timeout);

void         BSP_SysClk_SrcSet      (CPU_INT08U  clk_src);

CPU_INT08U   BSP_SysClk_SrcGet      (void);

/*
*********************************************************************************************************
*                                          XTAL NET FUNCTIONS PROTORYPES
*********************************************************************************************************
*/

CPU_INT32U   BSP_XOSC_FreqGet       (void);

CPU_INT08U   BSP_XOSC_SrcGet        (void);

void         BSP_XOSC_SrcSet        (CPU_INT08U  clk_src);

/*
*********************************************************************************************************
*                                            USART PROTOTYPES
*********************************************************************************************************
*/

void         BSP_Ser_Init           (CPU_INT32U     baud_rate);
void         BSP_Ser_WrByte         (CPU_CHAR       tx_byte);
void         BSP_Ser_WrStr          (CPU_CHAR      *tx_str);
CPU_INT08U   BSP_Ser_RdByte         (void);
void         BSP_Ser_RdStr          (CPU_CHAR      *rx_str,
                                     CPU_INT32U     len);
void         BSP_Ser_Printf         (CPU_CHAR      *format,
                                                    ...);


/*
*********************************************************************************************************
*                                            LED PROTOTYPES
*********************************************************************************************************
*/

void        BSP_LED_On              (CPU_INT08U  led);
void        BSP_LED_Off             (CPU_INT08U  led);
void        BSP_LED_Toggle          (CPU_INT08U  led);

/*
*********************************************************************************************************
*                                            PB PROTOTYPES
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_GetStatus       (CPU_INT08U  pb);


/*
*********************************************************************************************************
*                                            MISCELLANEOUS
*********************************************************************************************************
*/

#if    !defined(BSP_CFG_LED_PORT_SEL)
  #error  "BSP_CFG_LED_PORT_SEL                    not #define'd in 'app_cfg.h'                 "
  #error  "                              [MUST be  BSP_PORT_A  Port A is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_B  Port B is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_C  Port B is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_D  Port B is selected for the LEDs ] "

#elif  !defined(BSP_CFG_PB_PORT_SEL)
  #error  "BSP_CFG_PB_PORT_SEL                    not #define'd in 'app_cfg.h'                   "
  #error  "                              [MUST be  BSP_PORT_A  Port A is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_B  Port B is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_C  Port B is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_D  Port B is selected for the LEDs ] "

#elif  (BSP_CFG_LED_PORT_SEL != BSP_PORT_A) && \
       (BSP_CFG_LED_PORT_SEL != BSP_PORT_B) && \
       (BSP_CFG_LED_PORT_SEL != BSP_PORT_C) && \
       (BSP_CFG_LED_PORT_SEL != BSP_PORT_D)
  #error  "BSP_CFG_LED_PORT_SEL               ilegally #define'd in 'app_cfg.h'                  "
  #error  "                              [MUST be  BSP_PORT_A  Port A is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_B  Port B is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_C  Port B is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_D  Port B is selected for the LEDs ] "

#elif  (BSP_CFG_PB_PORT_SEL != BSP_PORT_A) && \
       (BSP_CFG_PB_PORT_SEL != BSP_PORT_B) && \
       (BSP_CFG_PB_PORT_SEL != BSP_PORT_C) && \
       (BSP_CFG_PB_PORT_SEL != BSP_PORT_D)
  #error  "BSP_CFG_PB_PORT_SEL               ilegally #define'd in 'app_cfg.h'                   "
  #error  "                              [MUST be  BSP_PORT_A  Port A is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_B  Port B is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_C  Port B is selected for the LEDs ] "
  #error  "                              [     ||  BSP_PORT_D  Port B is selected for the LEDs ] "
           
#elif  (BSP_CFG_PB_PORT_SEL == BSP_CFG_LED_PORT_SEL) 
  #error  "BSP_CFG_PB_PORT_SEL or BSP_CFG_LED_PORT_SEL     ilegally #define'd in 'app_cfg.h'     "
  #error  "                              [MUST be BSP_CFG_PB_PORT_SEL != BSP_CFG_LED_PORT_SEL  ] "

#endif

/*
*********************************************************************************************************
*                                              MODULE END
*
* Note(s) : See 'MODULE  Note #1'.
*********************************************************************************************************
*/

#endif                                                          /* End of BSP module include (see Note #1).       */
