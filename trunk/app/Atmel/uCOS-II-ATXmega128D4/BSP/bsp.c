/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                          (c) Copyright 2003-2008; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                         BOARD SUPPORT PACKAGE
*
*                                           Atmel ATxmega128A1 
*                                      ATSTK600 Development Board
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : FK
                  FT
*********************************************************************************************************
*/

#include <includes.h>

/*
**************************************************************************************************************
*                                             LOCAL DEFINES
**************************************************************************************************************
*/
                                                                        /* -------------- CLK INPUT FREQUENCY VALUES ------- */
#define  BSP_CLK_IN_INT_32K_ULP_FREQ                   32000L           /* Internal  2 Khz ULP                               */
#define  BSP_CLK_IN_INT_32K_OSC_FREQ                   32000L           /* Internal 32 Khz Oscilator                         */
#define  BSP_CLK_IN_INT_2M_OSC_FREQ                  2000000L           /* Internal  2 Mhz Oscilator                         */
#define  BSP_CLK_IN_INT_32M_OSC_FREQ                32000000L           /* Internal 32 Mhz Oscilator                         */
#define  BSP_CLK_IN_EXT_LOW_XTAL_FREQ                  32768L           /* External 32 Khz XTAL                              */
#define  BSP_CLK_IN_EXT_HIGH_XTAL_FREQ              16000000L           /* External 0.4 - 16 Mhz XTAL                        */
#define  BSP_CLK_IN_EXT_CLK_FREQ                    32000000L           /* External Clk = 16 Mhz                             */

                                                                        /* ----------- PLL REGISTER BIT/MASK DEFINES ------- */
#define  BSP_PLLCTRL_PLLSRC_MASK                         0xC0           /* PLL Control Register PLL source mask              */
#define  BSP_PLLCTRL_PLLAC_MASK                          0x1F           /* PLL Control Register Multipler value mask         */ 
                                                                        /* ---------- PLL MAXIMUM/MINIMUM VALUES ----------- */
#define  BSP_PLL_MIN_FREQ                           10000000L           /* Minimum output PLL frequency                      */ 
#define  BSP_PLL_MAX_FREQ                          200000000L           /* Maximum output PLL frequency                      */
#define  BSP_PLL_MAX_FREQ_MUL                            0x1F           /* Maximum PLL multipler value                       */
                                                                        /* ---- OSC CONTROL/STATUS REGISTER BIT DEFINES ---- */
#define  BSP_OSC_CTRL_RC2M_EN                      DEF_BIT_00
#define  BSP_OSC_CTRL_RC32M_EN                     DEF_BIT_01                
#define  BSP_OSC_CTRL_RC32K_EN                     DEF_BIT_02
#define  BSP_OSC_CTRL_XOSC_EN                      DEF_BIT_03
#define  BSP_OSC_CTRL_PLL_EN                       DEF_BIT_04
                                                                        /* -------- PSCTRL REGISTER FIELD MASKS ------------ */
#define  BSP_PSCTRL_DIVBC_MASK                           0x03        
                                                                        /* -------- XOSCCTRL REGISTER FIELD MASKS ---------- */
#define  BSP_XOSCCTRL_XOSCSEL_MASK                       0x0F
                                                                        /* ------------ CCP REGISTER SIGNATURE ------------- */
#define  BSP_CPP_IOREG_SIGNATURE                         0xD8
#define  BSP_CPP_SPM_SIGNNATURE                          0x9D
                                                                        /* -----------------  I/O DEFINES ------------------ */
#define  BSP_GPIOX_LED_GRP                               0xFF           /* LED output enable bits                            */
#define  BSP_GPIOX_PB_GRP                                0xFF           /* LED output disable bits                           */
                                                                   
#define  BSP_GPIOX_USART0_RX                       DEF_BIT_02           /* UART 0 Port C/D/E/F  pins settings                */
#define  BSP_GPIOX_USART0_TX                       DEF_BIT_03        

#define  BSP_GPIOX_USART1_RX                       DEF_BIT_06           /* UART 1 Port C/D/E/D  pins settings                */
#define  BSP_GPIOX_USART1_TX                       DEF_BIT_07

#define  BSP_USART_CMODE_ASYNC                    (0x00 << 6)
#define  BSP_USART_CMODE_SYNC                     (0x01 << 6)
#define  BSP_USART_CMODE_IRCOM                    (0x02 << 6)
#define  BSP_USART_CMODE_MSPI                     (0x03 << 6)                                                       

#define  BSP_USART_PMODE_PARITY_DIS               (0x00 << 4)
#define  BSP_USART_PMODE_PARITY_EVEN              (0x02 << 4)
#define  BSP_USART_PMODE_PARITY_ODD               (0x03 << 4)

#define  BSP_USART_SBMODE_ONE                     (0x00 << 3)
#define  BSP_USART_SBMODE_TWO                     (0x01 << 3)

#define  BSP_USART_CHSIZE_5                       (0x00 << 0)
#define  BSP_USART_CHSIZE_6                       (0x01 << 0)
#define  BSP_USART_CHSIZE_7                       (0x02 << 0)
#define  BSP_USART_CHSIZE_8                       (0x03 << 0)
#define  BSP_USART_CHSIZE_9                       (0x07 << 0)

#define  BSP_USART_CTRLB_TX_EN                     DEF_BIT_03
#define  BSP_USART_CTRLB_RX_EN                     DEF_BIT_04 

#define  BSP_USART_STATUS_DREIF                    DEF_BIT_05  
#define  BSP_USART_STATUS_RXCIF                    DEF_BIT_07

/*
*********************************************************************************************************
*                                         LOCAL PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_CPU_Init (void);

static  void  BSP_LED_Init (void);

static  void  BSP_PB_Init  (void);

static  void  BSP_TmrInit  (void);



/*
*********************************************************************************************************
*                                        GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         BSP_Init()
*
* Description : This function should be called by your application code before you make use of any of the
*               functions found in this module.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    BSP_CPU_Init();                                             /* Initializes all the system clks                           */
  
    BSP_LED_Init();                                             /* Initialize the LEDs I/O                                   */

    BSP_PB_Init();                                              /* Initialize the PBs  I/O                                   */

    BSP_TmrInit();                                              /* Initialize the uC/OS-II tick timer                        */
    
}

void BSP_IntDisAll (void)
{
    PMIC.CTRL = 0x00;
}

/*
*********************************************************************************************************
*                                         BSP_CPU_ClkFreq()
*
* Description : This function returns the CPU clk frequency.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clk frequency.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    CPU_INT32U  cpu_freq;
    
    
    cpu_freq = BSP_SysClk_DevGetFreq(BSP_SYS_CLK_OUT_CPU);

    return cpu_freq;    
}

/*
*********************************************************************************************************
*                                            PLL FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_PLL_FreqGet()
*
* Description : Gets the output frequency of the PLL module 
*
* Argument(s) : none.

* Return(s)   : The current PLL output frequency in HZ.
*
* Caller(s)   : Application.
*
* Note(s)     : (1)  If the source of the PLL can not be found BSP_PLL_SrcGetFreq() will return 0.
*********************************************************************************************************
*/

CPU_INT32U  BSP_PLL_FreqGet (void) 
{
    CPU_INT32U  pll_freq;
    CPU_INT08U  pll_mul;
    
    
    pll_mul   = OSC.PLLCTRL & BSP_PLLCTRL_PLLAC_MASK;

    pll_freq  = BSP_PLL_SrcGetFreq();    

    pll_freq *= pll_mul;
    
    return pll_freq;    
}

/*
*********************************************************************************************************
*                                          BSP_PLL_FreqSet()
*
* Description : Sets the source clk for the PLL module.
*
* Argument(s) : freq     The PLL output frequency to be set (see Note #1).
*
* Return(s)   : DEF_FALSE     if the desired frequency was not set.
*               DEF_TRUE      if the desired frequency was     set.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) The PLL output frequency SHOULD not exceed 200 Mhz. The PLL must have a minimum 
*                   output frequency of 10 Mhz.
*
*               (2) The PLLFAC bits set the multiplication factor of the PLL. The multiplication factor 
*                   can be in the range of 1 to 31.
*                   
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PLL_FreqSet (CPU_INT32U  freq)
{
    CPU_INT32U   pll_src_freq;
    CPU_INT32U   pll_freq_mul;
    
    
    if ((freq < BSP_PLL_MIN_FREQ) ||                            /* Check the PLL output frequency limitations (see note #1)  */
        (freq > BSP_PLL_MAX_FREQ)) {            
        return DEF_TRUE;
    }
            
    pll_src_freq = BSP_PLL_SrcGetFreq();
    
    if (freq < pll_src_freq ) {                                 /* The desire PLL freq should be higher or equal to the ...  */
        return DEF_FALSE;                                       /* ... the freq of the PLL source                            */
    }

    pll_freq_mul = freq / pll_src_freq;    
    
    if (pll_freq_mul > BSP_PLL_MAX_FREQ_MUL) {                  /* Check the maximum PLL multiplier allow by the hardware ...*/
        return DEF_FALSE;                                       /* ... (see note #2)                                         */
    }
    
    OSC.PLLCTRL = (OSC.PLLCTRL 
	            & BSP_PLLCTRL_PLLSRC_MASK)
				| ((CPU_INT08U)(pll_freq_mul & BSP_PLLCTRL_PLLAC_MASK));
    
	return DEF_TRUE;    
}

/*
*********************************************************************************************************
*                                          BSP_PLL_SrcGet()
*
* Description : Gets the source clk of the PLL module. 
*
* Argument(s) : none.

* Return(s)   : clk_src     The clk source to be set in the System Clk :
*
*                           BSP_PLL_SRC_RC2M
*                           BSP_PLL_SRC_RC32M
*                           BSP_PLL_SRC_XOSC
*                           BSP_PLL_SRC_UNKNOWN
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_PLL_SrcGet  (void)
{
    CPU_INT08U  reg_val;
    CPU_INT08U  src_val;
    
    
    reg_val = OSC.PLLCTRL & BSP_PLLCTRL_PLLSRC_MASK;
    
    switch (reg_val) {        
        case DEF_BIT_NONE:
             src_val = BSP_PLL_SRC_RC2M;          
             break;
             
        case (DEF_BIT_07):
             src_val = BSP_PLL_SRC_RC32M;
             break;
        
        case (DEF_BIT_07 | DEF_BIT_06):
             src_val = BSP_PLL_SRC_XOSC;
             break;
             
        default:
             src_val = BSP_PLL_SRC_UNKNOWN;
    }
    
    return src_val;
}  

/*
*********************************************************************************************************
*                                          BSP_PLL_SrcGetFreq()
*
* Description : Gets the source clk frequency of the PLL module. 
*
* Argument(s) : none.

* Return(s)   : The current PLL source clk frequency in HZ.
*
* Caller(s)   : Application.
*
* Note(s)     : (1)  If the source of the PLL can not be found BSP_PLL_SrcGetFreq() will return 0.
*********************************************************************************************************
*/

CPU_INT32U  BSP_PLL_SrcGetFreq (void)
{
    CPU_INT08U  pll_clk_src;
    CPU_INT32U  freq;
    
    pll_clk_src = BSP_PLL_SrcGet();
    
    if (pll_clk_src == BSP_PLL_SRC_UNKNOWN) {                   /* See note #1                                               */
        return (CPU_INT32U)0;
    }
    
    if (pll_clk_src == BSP_PLL_SRC_RC2M ) {
        freq = BSP_CLK_IN_INT_2M_OSC_FREQ ;
    
    } else if (pll_clk_src == BSP_PLL_SRC_RC32M) {
        freq =  BSP_CLK_IN_INT_32M_OSC_FREQ / 4;
    
    } else {
        freq =  BSP_XOSC_FreqGet();
    }
    
    return freq;
}

/*
*********************************************************************************************************
*                                          BSP_PLL_SrcSet()
*
* Description : Sets the source clk for the PLL module.
*
* Argument(s) : clk_src     The clk source to be set in the PLL module :
*
*                           BSP_PLL_SRC_RC2M
*                           BSP_PLL_SRC_RC32M
*                           BSP_PLL_SRC_XOSC
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_PLL_SrcSet  (CPU_INT08U  clk_src)
{
    switch (clk_src) {        
        default:
        case BSP_PLL_SRC_RC2M:
             OSC.PLLCTRL &= (~BSP_PLLCTRL_PLLSRC_MASK);
             break;            

        case BSP_PLL_SRC_RC32M:
             OSC.PLLCTRL |= (DEF_BIT_07);
             break;
        
        case BSP_PLL_SRC_XOSC:
             OSC.PLLCTRL |= (DEF_BIT_07 | DEF_BIT_06);
             break;        
    }
}   

/*
*********************************************************************************************************
*                                            SYSTEM CLK FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_SysClk_DevSetPre()
*
* Description : Set the values of the systme clock preescalers.
*
* Argument(s) : div_id         The preescaler divisor ID that will be set:
*                              BSP_SYS_CLK_DIV_A        Preescaler A is set.
*                              BSP_SYS_CLK_DIV_BC       Peescaler B and C are set.

*               div_val        The preescaler divisor value.
*
* Return(s)   : none.
*              
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_SysClk_DevSetPre (CPU_INT08U  div_id,
                            CPU_INT08U  div_val)
{
    
    if (div_id == BSP_SYS_CLK_DIV_A) {
        CLK.PSCTRL |= div_val << 2;                     
    } else {
        CLK.PSCTRL |= BSP_PSCTRL_DIVBC_MASK & div_val;                          
    }
       
 
}

/*
*********************************************************************************************************
*                                          BSP_SysClk_FreqGet()
*
* Description : Gets the frequency of the system clk specified by the 'dev_clk' parameter
*
* Argument(s) : dev_clk          Selects the device clk to be measure:
*                                BSP_SYS_CLK_OUT_PER 
*                                BSP_SYS_CLK_OUT_PER2
*                                BSP_SYS_CLK_OUT_PER4
*                                BSP_SYS_CLK_OUT_CPU 

* Return(s)   : The device frequency
*              
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U   BSP_SysClk_DevGetFreq  (CPU_INT08U  dev_clk)
{
    CPU_INT32U  sys_clk_freq;
    CPU_INT32U  dev_clk_freq;
    CPU_INT08U  reg_val;
    CPU_INT08U  diva;
    CPU_INT08U  divb;    
    CPU_INT08U  divc;    
    
    reg_val      = CLK.PSCTRL;
    diva         = (reg_val << 2);

    reg_val      &= 0x03;
    
    if (reg_val == 0x2) {
       divb = 4;
    } else if (reg_val == 0x03) {        
       divb = 2;
    } else {
       divb = 1;
    }
           
    if (DEF_BIT_IS_SET(reg_val, DEF_BIT_00)) {
        divc = 2;
    } else {
        divc = 1;
    }    
    
    dev_clk_freq = 0;    
    sys_clk_freq = BSP_SysClk_FreqGet();
        
    switch (dev_clk) {
        case BSP_SYS_CLK_OUT_PER4:
             dev_clk_freq = sys_clk_freq / (1 << diva);
             break;
             
         case BSP_SYS_CLK_OUT_PER2:
             dev_clk_freq  = sys_clk_freq / (1 << diva);
             dev_clk_freq /= divb; 
             break;

        case BSP_SYS_CLK_OUT_PER:
        case BSP_SYS_CLK_OUT_CPU:
             dev_clk_freq  = sys_clk_freq / (1 << diva);
             dev_clk_freq /= divb; 
             dev_clk_freq /= divc;              
             break;     
    }
    return dev_clk_freq;
}

/*
*********************************************************************************************************
*                                          BSP_SysClk_FreqGet()
*
* Description : Gets the frequency of the system clk (CLKsys)
*
* Argument(s) : none.
*
* Return(s)   : The system clk frequency
*              
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U   BSP_SysClk_FreqGet (void)
{
    CPU_INT08U  sys_clk_src;
    CPU_INT32U  freq;
    
    
    sys_clk_src = BSP_SysClk_SrcGet();
    
    if (sys_clk_src == BSP_SYS_CLK_SRC_UNKNOWN) {
        return 0;
    }
 
    switch (sys_clk_src) {        
        case BSP_SYS_CLK_SRC_RC32M:
             freq = BSP_CLK_IN_INT_32M_OSC_FREQ; 
             break;
        
        case BSP_SYS_CLK_SRC_RC32K:
             freq = BSP_CLK_IN_INT_32K_OSC_FREQ;
             break;
        
        case BSP_SYS_CLK_SRC_XOSC:
             freq = BSP_XOSC_FreqGet();
             break;
        
        case BSP_SYS_CLK_SRC_PLL:
             freq = BSP_PLL_FreqGet();
             break;

        default:     
        case BSP_SYS_CLK_SRC_RC2M:
             freq = BSP_CLK_IN_INT_2M_OSC_FREQ;
             break;            
             
    }
    
    return freq;
}
   

/*
*********************************************************************************************************
*                                          BSP_SysClk_SrcEn()
*
* Description : Enables the system clk source inputs.
*
* Argument(s) : clk_src     The clk source to be enabled in the System Clk :
*
*                           BSP_SYS_CLK_SRC_RC2M 
*                           BSP_SYS_CLK_SRC_RC32M 
*                           BSP_SYS_CLK_SRC_RC32K
*                           BSP_SYS_CLK_SRC_XOSC
*                           BSP_SYS_CLK_SRC_PLL
*
*               timeout     Number of cycles to wait until the clk source becomes enable.
*
* Return(s)   : DEF_TRUE.   If the system clk source is enable. 
*               DEF_FASLE   If the system clk soruce is not enable after the timeout expires.
*              
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_SysClk_SrcEn (CPU_INT08U  clk_src, 
                               CPU_INT16U  timeout)
{
    CPU_INT08U  reg_val;
    CPU_INT16U  timeout_ctr;
        
    
    timeout_ctr = timeout;
    
    switch (clk_src) {        
        case BSP_SYS_CLK_SRC_RC32M:
             reg_val = BSP_OSC_CTRL_RC32M_EN;
             break;
        
        case BSP_SYS_CLK_SRC_RC32K:
             reg_val = BSP_OSC_CTRL_RC32K_EN;
             break;
        
        case BSP_SYS_CLK_SRC_XOSC:
             reg_val = BSP_OSC_CTRL_XOSC_EN;
             break;
        
        case BSP_SYS_CLK_SRC_PLL:
             reg_val = BSP_OSC_CTRL_PLL_EN;
             break;

        case BSP_SYS_CLK_SRC_RC2M:
             reg_val = BSP_OSC_CTRL_RC2M_EN;
             break;            
             
        default:
             return DEF_FALSE;
    }

    OSC.CTRL |= reg_val;
    
    if (timeout_ctr == 0) {
        if (DEF_BIT_IS_SET(OSC.STATUS, reg_val)) {
            return DEF_TRUE;
        } else
            return DEF_FALSE;
    }
            
    while (timeout_ctr > 0) {
        if (DEF_BIT_IS_SET(OSC.STATUS, reg_val)) {
            return DEF_TRUE;
        }
        timeout_ctr--;
    }        
    
    return DEF_FALSE;
}


/*
*********************************************************************************************************
*                                          BSP_SysClk_SrcSet()
*
* Description : Sets the source clk for the System Clk (CLKsys).
*
* Argument(s) : clk_src     The clk source to be set in the System Clk :
*
*                           BSP_SYS_CLK_SRC_RC2M 
*                           BSP_SYS_CLK_SRC_RC32M 
*                           BSP_SYS_CLK_SRC_RC32K
*                           BSP_SYS_CLK_SRC_XOSC
*                           BSP_SYS_CLK_SRC_PLL
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void   BSP_SysClk_SrcSet (CPU_INT08U clk_src)
{
    CPU_INT08U  reg_val;
    

    switch (clk_src) {        
        case BSP_SYS_CLK_SRC_RC32M:
             reg_val = 0x01;
             break;
        
        case BSP_SYS_CLK_SRC_RC32K:
             reg_val = 0x02;
             break;
        
        case BSP_SYS_CLK_SRC_XOSC:
             reg_val = 0x03;
             break;
        
        case BSP_SYS_CLK_SRC_PLL:
             reg_val = 0x04;
             break;

        default:
        case BSP_SYS_CLK_SRC_RC2M:
             reg_val = 0x00;
             break;            
    }

    CCP      = BSP_CPP_IOREG_SIGNATURE;    
    CLK.CTRL = reg_val;

}

/*
*********************************************************************************************************
*                                          BSP_SystemClk_SrcGet()
*
* Description : Gets the source clk for the System Clk (CLKsys)
*
* Argument(s) : none. 
*
* Return(s)   : clk_src     The clk source to be set in the System Clk:
*
*                           BSP_SYS_CLK_SRC_RC2M 
*                           BSP_SYS_CLK_SRC_RC32M 
*                           BSP_SYS_CLK_SRC_RC32K
*                           BSP_SYS_CLK_SRC_XOSC
*                           BSP_SYS_CLK_SRC_PLL
*                           BSP_SYS_CLK_SRC_UNKNOWN
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_SysClk_SrcGet  (void)
{
    CPU_INT08U  reg_val;
    CPU_INT08U  clk_src;
    
    reg_val = CLK.CTRL;
    switch (reg_val) {        
        case 0x00:
             clk_src = BSP_SYS_CLK_SRC_RC2M;
             break;

        case 0x01:
             clk_src = BSP_SYS_CLK_SRC_RC32M;
             break;
             
        case 0x02:        
             clk_src = BSP_SYS_CLK_SRC_RC32K;
             break;

        case 0x03:
             clk_src = BSP_SYS_CLK_SRC_XOSC;
             break;

        case 0x04:        
             clk_src = BSP_SYS_CLK_SRC_PLL;
             break;
            
        default:
            clk_src  = BSP_SYS_CLK_SRC_UNKNOWN;
            break;
    }    
    
    return clk_src;
}

/*
*********************************************************************************************************
*                                          BSP_XOSC_SrcSet()
*
* Description : Sets the source clk of the external XTAL net 
*
* Argument(s) : clk_src     The clk source to be select in the external XTAL net
*
*                           BSP_XTAL_NET_SRC_LOW_XTAL 
*                           BSP_XTAL_NET_SRC_HIGH_XTAL 
*                           BSP_XTAL_NET_SRC_EXT_CLK
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_XOSC_SrcSet (CPU_INT08U  clk_src)
{
    OSC.XOSCCTRL &= (~BSP_XOSCCTRL_XOSCSEL_MASK);
     
    switch (clk_src) {
        case BSP_XTAL_NET_SRC_LOW_XTAL:
             OSC.XOSCCTRL |= DEF_BIT_01; 
             break;

        case BSP_XTAL_NET_SRC_HIGH_XTAL:
             OSC.XOSCCTRL |= (DEF_BIT_01 | DEF_BIT_00); 

             if (BSP_CLK_IN_EXT_HIGH_XTAL_FREQ        <  2000000L) {
                 OSC.XOSCCTRL |= (0x00 << 6); 
             } else if (BSP_CLK_IN_EXT_HIGH_XTAL_FREQ <  9000000L) {
                 OSC.XOSCCTRL |= (0x01 << 6); 
             } else if (BSP_CLK_IN_EXT_HIGH_XTAL_FREQ < 12000000L) {
                 OSC.XOSCCTRL |= (0x02 << 6); 
             } else {
                 OSC.XOSCCTRL |= (0x04 << 6); 
             }             
             
             break;

        default:
        case BSP_XTAL_NET_SRC_EXT_CLK:
             OSC.XOSCCTRL &= (~BSP_XOSCCTRL_XOSCSEL_MASK);
             break;
    }
}

/*
*********************************************************************************************************
*                                      XTAL/OSC NET FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          BSP_XOSC_SrcGet()
*
* Description : Gets the source clk of the external XTAL net.
*
* Argument(s) : none.
*
* Returns(s) : clk_src     The clk source of the external XTAL net
*
*                           BSP_XTAL_NET_SRC_LOW_XTAL 
*                           BSP_XTAL_NET_SRC_HIGH_XTAL 
*                           BSP_XTAL_NET_SRC_EXT_CLK
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT08U  BSP_XOSC_SrcGet (void)
{
    CPU_INT08U  reg_val;
    CPU_INT08U  clk_src;

    reg_val = OSC.XOSCCTRL & BSP_XOSCCTRL_XOSCSEL_MASK;

    switch (reg_val) {
        case 0x00:
             clk_src = BSP_XTAL_NET_SRC_EXT_CLK;
             break;

        case 0x02:
             clk_src = BSP_XTAL_NET_SRC_LOW_XTAL;
             break;

        case 0x03:
        case 0x07:
        case 0x0B:
             clk_src = BSP_XTAL_NET_SRC_HIGH_XTAL;
             break;
             
        default:
             clk_src = BSP_XTAL_NET_SRC_UNKNOWN;
             break;
    }
    
    return clk_src;
}

/*
*********************************************************************************************************
*                                          BSP_XOSC_FreqGet()
*
* Description : Gets frequency of the external XTAL net.
*
* Argument(s) : none. 
*
* Return(s)   : The frequecy of the external XTAL net.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_XOSC_FreqGet  (void)
{
    CPU_INT08U  reg_val;
    
    
    reg_val = OSC.XOSCCTRL & BSP_XOSCCTRL_XOSCSEL_MASK;

    if (reg_val == 0x00) {
        return (CPU_INT32U)BSP_CLK_IN_EXT_CLK_FREQ;
    } else if (reg_val == 0x01){
        return (CPU_INT32U)BSP_CLK_IN_EXT_LOW_XTAL_FREQ;
    } else {
        return (CPU_INT32U)BSP_CLK_IN_EXT_HIGH_XTAL_FREQ;
    }

}


/*
*********************************************************************************************************
*                                        LEDs GLOBAL FUNCTIONS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_LED_On ()
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to control.
*                      0    indicates that you want ALL the LEDs to be ON.
*                      1    turns ON LED1 on the board.
*                      .
*                      .
*                      8    turns ON LED8 on the board.
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none. 
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U led)
{
    CPU_INT08U  reg_val;
    
    
    if (led == 0) {
        reg_val = BSP_GPIOX_LED_GRP;
    } else {
       reg_val  = DEF_BIT(led - 1);
    }
    
#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_A)        
    PORTA.OUTCLR = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_B)        
    PORTB.OUTCLR = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_C)        
    PORTC.OUTCLR = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_D)        
    PORTD.OUTCLR = reg_val;            
#endif    

}

/*
*********************************************************************************************************
*                                             BSP_LED_Off()
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to turn OFF.
*                      0    indicates that you want ALL the LEDs to be OFF.
*                      1    turns OFF LED1 on the board.
*                      .
*                      .
*                      8    turns OFF LED8 on the board.
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none. 
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U led)
{
    CPU_INT08U  reg_val;
    
    
    if (led == 0) {
        reg_val = BSP_GPIOX_LED_GRP;
    } else {
       reg_val  = DEF_BIT(led - 1);
    }
    
#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_A)        
    PORTA.OUTSET = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_B)        
    PORTB.OUTSET = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_C)        
    PORTC.OUTSET = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_D)        
    PORTD.OUTSET = reg_val;            
#endif    
}

/*
*********************************************************************************************************
*                                        BSP_LED_Toggle()
*
* Description : This function is used to toggle the state of any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to toggle.
*                      0    indicates that you want ALL the LEDs to toggle.
*                      1    Toggle LED1 on the board.
*                      .
*                      .
*                      8    Toggle LED8 on the board.
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none. 
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U led)
{
    CPU_INT08U  reg_val;
    
    
    if (led == 0) {
        reg_val = BSP_GPIOX_LED_GRP;
    } else {
       reg_val  = DEF_BIT(led - 1);
    }
    
#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_A)        
    PORTA.OUTTGL = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_B)        
    PORTB.OUTTGL = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_C)        
    PORTC.OUTTGL = reg_val;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_D)        
    PORTD.OUTTGL = reg_val;            
#endif    

}

/*
*********************************************************************************************************
*                                        PB GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             BSP_PB_GetStatus ()
*
* Description : This function is used to get the status of the push buttons.
*
* Arguments   : pb    is the number of PB to probe.
*                       0    probe the push button B0
*                       1    probe the push button B1
*                       .
*                       .
*                       .
*                       7    probe the push button B7

* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none. 
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_GetStatus (CPU_INT08U  pb)
{
    CPU_INT08U  reg_mask;
    CPU_INT08U  reg_val;
    
    
    reg_mask = DEF_BIT(pb);
    
#if (BSP_CFG_PB_PORT_SEL == BSP_PORT_A)        
    reg_val = PORTA.IN;            
#endif

#if (BSP_CFG_PB_PORT_SEL == BSP_PORT_B)        
    reg_val = PORTB.IN;            
#endif

#if (BSP_CFG_PB_PORT_SEL == BSP_PORT_C)        
    reg_val = PORTC.IN;            
#endif

#if (BSP_CFG_PB_PODT_SEL == BSP_PORT_D)        
    reg_val = PORTA.IN;            
#endif
    
    if (DEF_BIT_IS_CLR(reg_val, reg_mask)) {
        return DEF_TRUE;
    } else {
        return DEF_FALSE;
    }
}

/*
*********************************************************************************************************
*                                         SERIAL COMMUNICATIONS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       BSP_Ser_Init()
*
* Description : This function initializes the COM port.
*
* Argument(s) : baud_rate    com port baudrate in bps.
*              
* Return(s)   : none.
*
* Note(s)    :  (1) The BSP_CFG_UART_PORT_SEL must be defined in the app_cfg.h file. It will set the port
*                   for the UART
*                             BSP_PORT_C
*                             BSP_PORT_D
*                             BSP_PORT_E
*                             BSP_PORT_F
*
*               (2) The BSP_CFG_UART_NBR_SEL must be defined in the app_cfg.h file. It will set the UART number
*                   to be used:
*                            BSP_UART_0
*                            BSP_UART_1
* Caller(s)  : Application
*********************************************************************************************************
*/

void  BSP_Ser_Init (CPU_INT32U  baud_rate)
{
    volatile  USART_t     *usart;
    volatile  PORT_t      *port;
              CPU_INT32U   clk_div;                             /* Clock divider                                            */
              CPU_INT32U   per_freq;                            /* UASRT peripheral clk                                     */

              
#if  (BSP_CFG_UART_PORT_SEL  == BSP_PORT_C)
    port  = &PORTC;
    usart = &USARTC0;
    
#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_D)    
    port  = &PORTD;
    usart = &USARTD0;
    
#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_E)    
    port  = &PORTE;
    usart = &USARTE0;              
    
#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_F)    
    port  = &PORTF;
    usart = &USARTF0;
#endif
    
#if (BSP_CFG_UART_NBR_SEL == BSP_UART_0)
    port->OUTSET = BSP_GPIOX_USART0_TX;                         /* Set Px3 (TXD0) state as high                             */ 
    port->DIRSET = BSP_GPIOX_USART0_TX;                         /* Set Px3 (TXD0) as output pin                             */
    port->DIRCLR = BSP_GPIOX_USART0_RX;                         /* set Px2 (RXD0) as input pin                              */
#endif

#if (BSP_CFG_UART_NBR_SEL == BSP_UART_1)    
    port->OUTSET = BSP_GPIOX_USART1_TX;                         /* Set Px7 (TXD0) state as high                             */ 
    port->DIRSET = BSP_GPIOX_USART1_TX;                         /* Set Px7 (TXD0) as output pin                             */
    port->DIRCLR = BSP_GPIOX_USART1_RX;                         /* set Px6 (RXD0) as input pin                              */
    usart        = (USART_t *)((CPU_INT16U)usart + 0x10);
#endif    

    usart->CTRLA      = 0x00;                                   /* Disable all interrupts                                   */
    usart->CTRLC      = BSP_USART_CMODE_ASYNC                   /* Asynchronous USART                                       */
                      | BSP_USART_PMODE_PARITY_DIS              /* Parity disable                                           */
                      | BSP_USART_SBMODE_ONE                    /* Stop bit : 1                                             */
                      | BSP_USART_CHSIZE_8;                     /* 8-bit chatacter                                          */
   
   
    per_freq          =  BSP_SysClk_DevGetFreq(BSP_SYS_CLK_OUT_PER);    
    clk_div           =  ((per_freq / baud_rate) - 1) / 16;     /* Calculate the clk divider for the baud rate generator    */

    usart->BAUDCTRLA  =  (CPU_INT08U)((CPU_INT16U)clk_div & 0xFF);
    usart->BAUDCTRLB  =  (CPU_INT08U)((CPU_INT16U)clk_div      >> 8);

    usart->CTRLB      =  BSP_USART_CTRLB_RX_EN
                      |  BSP_USART_CTRLB_TX_EN;                  /* Enable RX & TX                                           */

}


/*
*********************************************************************************************************
*                                                BSP_Ser_WrByte ()
*
* Description : This function writes a single byte to a serial port. Note, this function
*               also blocks until room is available in the USART for the byte to be sent.
*
* Argument(s) : tx_byte:     byte containing the value of the charcater to output.
*
* Return(s)   : none.
*
* Note(s)     : none.
*
* Caller(s)   : Applicaiton.
*********************************************************************************************************
*/

void   BSP_Ser_WrByte (CPU_CHAR tx_byte)
{
    volatile  USART_t     *usart;

#if  (BSP_CFG_UART_PORT_SEL  == BSP_PORT_C)
    usart = &USARTC0;
    
#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_D)    
    usart = &USARTD0;

#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_E)    
    usart = &USARTE0;
              
#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_F)    
    usart = &USARTF0;
#endif
    
#if (BSP_CFG_UART_NBR_SEL == BSP_UART_1)    
    usart        = (USART_t *)((CPU_INT16U)usart + 0x10);
#endif    
    
    while (DEF_BIT_IS_CLR(usart->STATUS, BSP_USART_STATUS_DREIF)) {
        ;
    }

    usart->DATA = tx_byte;
}

/*
*********************************************************************************************************
*                                                BSP_Ser_RdByte()
*
* Description : This funcion reads a byte from a serial port. This call blocks until a
*               character appears at the port. Echo of the byte is also sent to the serial port.
*
* Argument(s) : none.
*
* Return(s)   : A byte containing the value of the received character.
*
* Note(s)     : none.
*
* Caller(s)   : none.
*********************************************************************************************************
*/

CPU_INT08U   BSP_Ser_RdByte (void)
{
    volatile  USART_t     *usart;
              CPU_INT08U   rx_byte;

#if  (BSP_CFG_UART_PORT_SEL  == BSP_PORT_C)
    usart = &USARTC0;
    
#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_D)    
    usart = &USARTD0;

#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_E)    
    usart = &USARTE0;
              
#elif (BSP_CFG_UART_PORT_SEL == BSP_PORT_F)    
    usart = &USARTF0;
#endif
    
#if (BSP_CFG_UART_NBR_SEL == BSP_UART_1)    
    usart        = (USART_t *)((CPU_INT16U)usart + 0x10);
#endif    
                                                                /*  Wait for a byte to show up.                             */
    while (DEF_BIT_IS_SET(usart->STATUS, BSP_USART_STATUS_RXCIF)) {     
        OSTimeDly(2);
    }

    rx_byte = (CPU_INT08U)(usart->DATA & 0x00FF);               /* Read the character.                                      */

    return (rx_byte);
}

/*
*********************************************************************************************************
*                                                BSP, USART - Write String
*
* Description :   This funcion writes a character string to a serial port.
*
* Arguments   :   com   USART port: 0..7
*                 s     string of characters
*
* Returns     :   None.
*********************************************************************************************************
*/

void  BSP_Ser_WrStr (CPU_INT08U *tx_str)
{
    while (*tx_str) {
        BSP_Ser_WrByte(*tx_str++);
    }
}


/*
*********************************************************************************************************
*                                                BSP_Ser_RdStr()
*
* Description : This function reads a string from a UART.
*
* Argument(s) : s           A pointer to a buffer at which the string can be stored.
*
*               len         The size of the string that will be read.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  BSP_Ser_RdStr (CPU_CHAR    *rx_str,
                     CPU_INT32U   len)
{
    CPU_CHAR  rx_data;
    CPU_CHAR  input_ix;


    input_ix  = 0;
    rx_str[0] = 0;

    while (1)
    {
        rx_data = BSP_Ser_RdByte();

        if ((rx_data == '\r') ||
            (rx_data == '\n')) {
            BSP_Ser_Printf((CPU_CHAR *)"\n");
            rx_str[input_ix] = 0;
            break;
        }

        if (rx_data == '\b') {
            if (input_ix > 0) {
                BSP_Ser_Printf((CPU_CHAR *)"\b \b");
                input_ix--;
                rx_str[input_ix] = 0;
            }
        }

        if (ASCII_IsPrint(rx_data)) {
            BSP_Ser_Printf((CPU_CHAR *)"%c", rx_data);
            rx_str[input_ix] = rx_data;
            input_ix++;
            if (input_ix >= len) {
               input_ix = len;
            }
        }
    }
}

/*
*********************************************************************************************************
*                                                BSP_Ser_Printf()
*
* Description : Formatted outout to the serial port.
*               This funcion reads a string from a serial port. This call blocks until a
*               character appears at the port and the last character is a Carriage
*               Return (0x0D).
*
* Argument(s) : Format string follwing the C format convention.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  BSP_Ser_Printf (CPU_CHAR *format, ...)
{
    static  CPU_CHAR  buffer[80 + 1];
            va_list   vArgs;


    va_start(vArgs, format);
    vsprintf((char *)buffer, (char const *)format, vArgs);
    va_end(vArgs);

    BSP_Ser_WrStr((CPU_CHAR*) buffer);
}

/*
*********************************************************************************************************
*                                        LOCAL FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                        BSP_CPU_Init()
*
* Description   : This function initializes the system clks and set the initial CPU frequency.
*
* Argument(s)   : none.
*              
* Return(s)     : none.         
*********************************************************************************************************
*/

static  void  BSP_CPU_Init(void)
{
    
	BSP_SysClk_SrcEn(BSP_SYS_CLK_SRC_RC32M, 0xFFFF);            /* Enable the Int. 32M Hz. Oscillator                        */
	
	BSP_PLL_SrcSet(BSP_PLL_SRC_RC32M);	                        /* Select Pll Source  = Int 32Mhz Oscillator                 */
    BSP_PLL_FreqSet(32000000);                                  /* Set the PLL frequency = 32 Mhz                            */

    BSP_SysClk_SrcEn(BSP_SYS_CLK_SRC_PLL  , 0xFFFF);            /* Enable the PLL clk source  in the System Clk              */    
    BSP_SysClk_SrcSet(BSP_SYS_CLK_SRC_PLL);                     /* Select the system clk = PLL Clk                           */
    BSP_SysClk_DevSetPre(BSP_SYS_CLK_DIV_A, 0);                 /* Set the divider to generate the peripherals and CPU Clk   */
    BSP_SysClk_DevSetPre(BSP_SYS_CLK_DIV_BC, 0);    
  
  
    
}



/*$PAGE*/
/*
*********************************************************************************************************
*                                        SETUP THE TICK RATE
*
* Note(s): 1) PER = CPU_CLK_FREQ / (2 * Prescaler * OC_freq) - 1
*          2) The equation actually performs rounding by multiplying by 2, adding 1 and then divising by 2
*             in integer math, this is equivalent to adding 0.5
*********************************************************************************************************
*/

static  void  BSP_TmrInit (void)
{
    CPU_INT32U  clk_per_freq;
    CPU_INT32U  period;


    TCC0.CTRLA     =  0x06;                                              /* Set TIMER C0 prescaler to CLK/256                       */
    TCC0.CTRLB     =  0x00;
    TCC0.CTRLC     =  0x00;
    TCC0.CTRLD     =  0x00;
    
    clk_per_freq   =  BSP_SysClk_DevGetFreq(BSP_SYS_CLK_OUT_PER);
    period         =  (CPU_INT32U)(((2 * clk_per_freq) + (256 * 2 * (CPU_INT32U)OS_TICKS_PER_SEC))
                   /               ((256 * 2 * (CPU_INT32U)OS_TICKS_PER_SEC)));

    
    TCC0.PER       = (CPU_INT16U)period;                                /* Load 16-bit TIMER0 period                                */
    TCC0.INTCTRLA  = (0x02);                                            /* Enable interrupt on TIMER0 at level 2                    */
 
    TCC0.CTRLFSET  = DEF_BIT_02;                                        /* Update the timer                                         */
    TCC0.CTRLFCLR  = DEF_BIT_02;

    PMIC.CTRL     |= DEF_BIT_01;                                        /* Enable interrupt level two in PMIC                       */
    
    TCC0.CTRLFSET  = DEF_BIT_03;                                        /* Restart the timer                                        */
    TCC0.CTRLFCLR  = DEF_BIT_03;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                     HANDLE THE TICK INTERRUPT
*********************************************************************************************************
*/

void  BSP_TmrHandler (void)
{
    OSTimeTick();
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                       uC/Probe, INITIALIZE TIMER
*
* Description: This function initializes a 16 or 32-bit free-running timer for uC/Probe.
*
* Arguments  : none
*********************************************************************************************************
*/
#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && (OS_PROBE_HOOKS_EN == 1)
void  OSProbe_TmrInit (void)
{
    TCC1.CTRLA    =  0x07;                                              /* Set TIMER C1 prescaler to CLK                            */
    TCC1.PER      =  0xFFFF; 
}
#endif                                                                  /* #if OS_PROBE_HOOKS_EN > 0                                */

/*$PAGE*/
/*
*********************************************************************************************************
*                                       uC/Probe, TIMER READ
*
* Description: This function reads a 16 or 32-bit free-running timer for uC/Probe.
*
* Arguments  : none
*
* Returns    : The current COUNT register value with the amount of elapsed clock cycles since reset.
*********************************************************************************************************
*/
#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && (OS_PROBE_HOOKS_EN == 1)
CPU_INT32U  OSProbe_TmrRd (void)
{
    return(TCC1.CNT);
}
#endif                                                                  /* #if OS_PROBE_HOOKS_EN > 0                                */


/*
*********************************************************************************************************
*                                            BSP_LED_Init()
*
* Description : This function is used to initialize the LEDs on the board.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)  : BSP_Init().
*
* Note(s)     : none. 
*********************************************************************************************************
*/

static  void  BSP_LED_Init (void)
{
#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_A)        
    PORTA.DIRSET = BSP_GPIOX_LED_GRP;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_B)        
    PORTB.DIRSET = BSP_GPIOX_LED_GRP;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_C)        
    PORTC.DIRSET = BSP_GPIOX_LED_GRP;            
#endif

#if (BSP_CFG_LED_PORT_SEL == BSP_PORT_D)        
    PORTD.DIRSET = BSP_GPIOX_LED_GRP;            
#endif    
    
    BSP_LED_Off(0);                                                       /* Turn Off all the LEDs                                     */
}



/*
*********************************************************************************************************
*                                            BSP_PB_Init()
*
* Description : This function is used to initialize the PBs on the board.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none. 
*********************************************************************************************************
*/

static  void  BSP_PB_Init (void)
{
#if (BSP_CFG_PB_PORT_SEL == BSP_PORT_A)        
    PORTA.DIRCLR = BSP_GPIOX_PB_GRP;            
#endif

#if (BSP_CFG_PB_PORT_SEL == BSP_PORT_B)        
    PORTB.DIRCLR = BSP_GPIOX_PB_GRP;            
#endif

#if (BSP_CFG_PB_PORT_SEL == BSP_PORT_C)        
    PORTC.DIRCLR = BSP_GPIOX_PB_GRP;            
#endif

#if (BSP_CFG_PB_PORT_SEL == BSP_PORT_D)        
    PORTD.DIRCLR = BSP_GPIOX_PB_GRP;            
#endif    
    
}
