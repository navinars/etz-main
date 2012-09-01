/*
*********************************************************************************************************
*                                               uC/CPU
*                                    CPU CONFIGURATION & PORT LAYER
*
*                          (c) Copyright 2004-2008; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CPU is provided in source form for FREE evaluation, for educational
*               use or peaceful research.  If you plan on using uC/CPU in a commercial
*               product you need to contact Micrium to properly license its use in your
*               product.  We provide ALL the source code for your convenience and to
*               help you experience uC/CPU.  The fact that the source code is provided
*               does NOT mean that you can use it without paying a licensing fee.
*
*               Knowledge of the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            CPU PORT FILE
*
*                                           Atmel ATxmega128
*                                            GNU C Compiler
*
* Filename      : cpu_a.s90
* Version       : V1.20
* Programmer(s) : FGK
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             ASM HEADER
*********************************************************************************************************
*/

        .text


;/*$PAGE*/
/*
*********************************************************************************************************
*                                              DEFINES
*********************************************************************************************************
*/

        .equ SREG, 0x3F                                         /* Status  Register                                     */


/*
*********************************************************************************************************
*                                          PUBLIC DECLARATIONS
*********************************************************************************************************
*/

        .global CPU_SR_Save
        .global CPU_SR_Restore


;/*$PAGE*/
/*
*********************************************************************************************************
*                            DISABLE/ENABLE INTERRUPTS USING OS_CRITICAL_METHOD #3
*
* Description : These functions are used to disable and enable interrupts using OS_CRITICAL_METHOD #3.
*
*               CPU_SR  CPU_SR_Save (void)
*                     Get current value of SREG
*                     Disable interrupts
*                     Return original value of SREG
*
*               void  CPU_SR_Restore (OS_CPU_SR cpu_sr)
*                     Set SREG to cpu_sr
*                     Return
*********************************************************************************************************
*/

CPU_SR_Save:
        IN      R16,SREG                                        /* Get current state of interrupts disable flag         */
        CLI                                                     /* Disable interrupts                                   */
        RET                                                     /* Return original SREG value in R16                    */


CPU_SR_Restore:
        OUT     SREG,R16                                        /* Restore SREG                                         */
        RET                                                     /* Return                                               */

