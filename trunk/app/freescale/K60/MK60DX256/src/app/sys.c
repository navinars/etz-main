 //*******************************************************************************	 
//硬件    :超核电子Kinetis核心板 V2.2
//处理器  :K10DN512VLL10  K60X256VLL10
//作者    :YANDLD @ UPC
//E-MAIL  :yandld@126.com
//修改日期:2012/6/10
//版本：V2.2
//淘宝：http://upcmcu.taobao.com
//论坛: http://www.tinychip.net
//Copyright(C) YANDLD 2012-2022
//All rights reserved
//********************************************************************************
#include "sys.h"
#include <string.h>

PInfo_Type PInfo;
uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
//获得系统信息
//获得处理器型号 引脚 
//获得内核时钟,总线时钟，FlexBus时钟，Flash时钟 等
void GetProcessorInfo(void)
{
	PInfo.FAMID=(((SIM->SDID)>>4) & 0x07);//获取Kinetis系列家族类型号 具体参见 SIM->SDID寄存器
	PInfo.PINID=(((SIM->SDID)>>0) & 0x0F);//获取Kinetis 引脚数量
	PInfo.ClockOption=CLOCK_SETUP;      //系统时钟选项
	SystemCoreClockUpdate();            //重新计算CoreClock
	PInfo.CoreClock=SystemCoreClock;    //CoreClock
	PInfo.BusClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT)+1));     //计算BusClock
	PInfo.FlexBusClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV3_MASK)>>SIM_CLKDIV1_OUTDIV3_SHIFT)+1)); //计算FlexBusClock
	PInfo.FlashClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+1));   //计算FlashClock
  PInfo.FlashSize=(SIM->FCFG1>>24)&0x0F; //此处获得的是PFlash代号，具体值请参见SIM_FCFG1
	PInfo.RAMSize  =(SIM->SOPT1>>12)&0x0F; //此处获得的是RAM代号，具体值请参见SIM_SOPT1
}
//////////////////////////////////////////////////////
//函数名： SystemInit 
//功  能：提供系统初始化
//////////////////////////////////////////////////////
void SystemInit (void) 
{
	//系时钟初始化
	//内部晶振 CLOCK_SETUP=0
#if (CLOCK_SETUP == 0)
	SIM->CLKDIV1 = (u32)0x00110000u; //配置系统预分频器
	/* 转到 FEI 模式 */
	MCG->C1 = (u8)0x06u;
	MCG->C2 = (u8)0x00u;
	MCG->C4|= (1<<6)|(1<<7)|(1<<5);   //内部参考慢速时钟32.768KHZ  倍频因子 2197 倍频后为72MHZ 参见MCG->C4寄存器
	//分频策略:  
	//SIM_CLKDIV1_OUTDIV1(0) CORE     CLOCK  1分频   UP TO 100M  
	//SIM_CLKDIV1_OUTDIV2(1) BUS      CLOCK  2分频   UP TO 50M 
	//SIM_CLKDIV1_OUTDIV3(1) FlexBus  ClOCK  2分频   UP TO 50M 
	//SIM_CLKDIV1_OUTDIV4(3) Flash    ClOCK  3分频   UP TO 25M 
	SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));
  MCG->C5 = (u8)0x00u;
  MCG->C6 = (u8)0x00u;
  while((MCG->S & MCG_S_IREFST_MASK) == 0u);  //检查 FLL参考时钟是内部参考时钟
  while((MCG->S & 0x0Cu) != 0x00u);           //等待FLL被选择
	//外部晶振 CLOCK_SETUP=1
#elif (CLOCK_SETUP == 1)
	SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));
  /* 转到 FBE 模式 */
	OSC->CR = (u8)0x00u;
	SIM->SOPT2 &= (u8)~(u8)0x01u;
	MCG->C2 = (u8)0x24u;
	MCG->C1 = (u8)0x9Au;
	MCG->C4 &= (u8)~(uint8_t)0xE0u;
	MCG->C5 = (u8)0x03u;
	MCG->C6 = (u8)0x00u;
	while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);//检查 FLL参考时钟是内部参考时钟 
	while((MCG->S & MCG_S_IREFST_MASK) != 0u); //检查 FLL参考时钟是内部参考时钟
	while((MCG->S & 0x0Cu) != 0x08u);          //等待 FBE 被选择
	MCG->C5 = (u8)0x03u;
	MCG->C6 = (u8)(0x40u|0x18u);		    //PLL48倍频
	while((MCG->S & MCG_S_PLLST_MASK) == 0u);   //等待PLLS 时钟源转到 PLL
	while((MCG->S & MCG_S_LOCK_MASK) == 0u);    //等待锁定
  //转到PEE
	MCG->C1 = (uint8_t)0x1Au;
	while((MCG->S & 0x0Cu) != 0x0Cu);           //等待PLL输出
	while((MCG->S & MCG_S_LOCK_MASK) == 0u);      //等待PLL锁定
	//外部晶振 超频 CLOCK_SETUP=2
#elif (CLOCK_SETUP == 2)
	SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(7));
  /* 转到 FBE 模式 */
	OSC->CR = (u8)0x00u;
	SIM->SOPT2 &= (u8)~(u8)0x01u;
	MCG->C2 = (u8)0x24u;
	MCG->C1 = (u8)0x9Au;
	MCG->C4 &= (u8)~(uint8_t)0xE0u;
	MCG->C5 = (u8)0x03u;
	MCG->C6 = (u8)0x00u;
	while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);//检查 FLL参考时钟是内部参考时钟 
	while((MCG->S & MCG_S_IREFST_MASK) != 0u); //检查 FLL参考时钟是内部参考时钟
	while((MCG->S & 0x0Cu) != 0x08u);          //等待 FBE 被选择
	MCG->C5 = (u8)0x01u; //4分频
	MCG->C6 = (u8)(0x40u|MCG_C6_VDIV(26));		    //PLL48倍频
	while((MCG->S & MCG_S_PLLST_MASK) == 0u);   //等待PLLS 时钟源转到 PLL
	while((MCG->S & MCG_S_LOCK_MASK) == 0u);    //等待锁定
  //转到PEE
	MCG->C1 = (uint8_t)0x1Au;
	while((MCG->S & 0x0Cu) != 0x0Cu);           //等待PLL输出
	while((MCG->S & MCG_S_LOCK_MASK) == 0u);      //等待PLL锁定
#endif 
		
}
/////////////////////////////////////////////////////
// 函数名： SystemCoreClockUpdate()
// 作  用： 重新计算内核时钟频率 用户在修改中频后必须调用这个函数以计算出新的主频
////////////////////////////////////////////////////
void SystemCoreClockUpdate(void)
{
    u32 MCGOUTClock;            //存储MCG模块时钟频率变量
    u8 Divider;
    if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x0u) 
	{
    /* 选择FLL 或 PLL 输出 */
      if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u) 
	  {
         /* 选择FLL输出 */
        if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u) 
		{
        /* 选择外部参考时钟 */
         if ((SIM->SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) == 0x0u) 
		 {
            MCGOUTClock = CPU_XTAL_CLK_HZ;   //系统晶振驱动 MCG 时钟
         }
		 else 
		 { 
            MCGOUTClock = CPU_XTAL32k_CLK_HZ;  //RTC 32 kHz 晶振驱动 MCG 时钟
         } 
        Divider = (uint8_t)(1u << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        MCGOUTClock = (MCGOUTClock / Divider);  //计算FLL参考时钟分频
        if ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0u) 
		{
           MCGOUTClock /= 32u;  //如果高范围使能，另外的32位分频是有效的
        } 
       } 
	   else 
	   {
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;     //选择慢的内部参考时钟
       } 
      /* 选择正确的乘数去计算 MCG 输出时钟*/
       switch (MCG->C4 & (MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS_MASK)) {
        case 0x0u:
          MCGOUTClock *= 640u;
          break;
        case 0x20u:
          MCGOUTClock *= 1280u;
          break;
        case 0x40u:
          MCGOUTClock *= 1920u;
          break;
        case 0x60u:
          MCGOUTClock *= 2560u;
          break;
        case 0x80u:
          MCGOUTClock *= 732u;
          break;
        case 0xA0u:
          MCGOUTClock *= 1464u;
          break;
        case 0xC0u:
          MCGOUTClock *= 2197u;
          break;
        case 0xE0u:
          MCGOUTClock *= 2929u;
          break;
        default:
          break;
      }
    } 
	else 
	{ 
      /* 选择 PLL */
      Divider = (1u + (MCG->C5 & MCG_C5_PRDIV_MASK));
      MCGOUTClock = (u32)(CPU_XTAL_CLK_HZ / Divider);   //计算 PLL 参考时钟
      Divider = ((MCG->C6 & MCG_C6_VDIV_MASK) + 24u);
      MCGOUTClock *= Divider;        //计算 MCG 输出时钟
    } 
  }
  else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u) 
     {
       /* 选择内部参考时钟 */
       if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u) 
	   {
         MCGOUTClock = CPU_INT_SLOW_CLK_HZ;    //选择慢的内部参考时钟 
       } 
	   else 
	   { 
         MCGOUTClock = CPU_INT_FAST_CLK_HZ;   //选择内部快的参考时钟 
       } 
     } 
	 else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u) 
	   {
         /* 选择外部参考时钟*/
         if ((SIM->SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) == 0x0u) 
		 {
            MCGOUTClock = CPU_XTAL_CLK_HZ;     //系统晶振驱动 MCG 时钟
         } 
		 else 
		 { 
            MCGOUTClock = CPU_XTAL32k_CLK_HZ;  //RTC 32 kHz 晶振驱动 MCG 时钟
         } 
       } 
	   else 
	   { 
          return;
       } 
   SystemCoreClock = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));
}
/////////////////////////////////////////////
//函数名：NVIC_Pgc
//参  数：PriorityGroup 填写数字“0~7”
//功  能：进行中断分组设置
//说  明：此程序是进行中断分组管理，一般设置一次，避免重复设置
//        一个系统仅能有一种分组，每种分组可以设置16个中断，可以
//		  设置多个中断在同一优先级，系统对这样的中断处理是先按照中断向量表
//        里的顺序进行处理
//说  明：此函数COPY NVIC_SetPriority(IRQn_Type IRQn, u32 priority)详见core_cm4.h
////////////////////////////////////////////
void NVICPgc(u32 PriorityGroup)
{
    u32 reg_value;
    u32 PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);            
    reg_value  =  SCB->AIRCR;                                    //读旧的寄存器配置 
    reg_value &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk);          
    reg_value  =  (reg_value|((uint32_t)0x5FA << SCB_AIRCR_VECTKEY_Pos)|
                    (PriorityGroupTmp << 8));            //写钥匙和优先级分组
    SCB->AIRCR =  reg_value;
}
/////////////////////////////////////////////
//函数名：NVIC_Setp
//参  数：IRQn 填写中断编号，priority 设置优先级
//功  能：进行中断优先级设置
//说  明：此函数COPY NVIC_SetPriority(IRQn_Type IRQn, u32 priority)详见core_cm4.h
////////////////////////////////////////////
void NVICSetp(IRQn_Type IRQn, u32 priority)
{
  if(IRQn < 0) {
    SCB->SHP[((u32)(IRQn) & 0xF)-4] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff); } 
  else {
    NVIC->IP[(u32)(IRQn)] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff);    }   //为中端设置优先级
}
//软复位
void SystemSoftReset(void)
{   
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 
