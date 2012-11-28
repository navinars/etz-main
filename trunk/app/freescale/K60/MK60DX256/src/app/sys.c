 //*******************************************************************************	 
//Ӳ��    :���˵���Kinetis���İ� V2.2
//������  :K10DN512VLL10  K60X256VLL10
//����    :YANDLD @ UPC
//E-MAIL  :yandld@126.com
//�޸�����:2012/6/10
//�汾��V2.2
//�Ա���http://upcmcu.taobao.com
//��̳: http://www.tinychip.net
//Copyright(C) YANDLD 2012-2022
//All rights reserved
//********************************************************************************
#include "sys.h"
#include <string.h>

PInfo_Type PInfo;
uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
//���ϵͳ��Ϣ
//��ô������ͺ� ���� 
//����ں�ʱ��,����ʱ�ӣ�FlexBusʱ�ӣ�Flashʱ�� ��
void GetProcessorInfo(void)
{
	PInfo.FAMID=(((SIM->SDID)>>4) & 0x07);//��ȡKinetisϵ�м������ͺ� ����μ� SIM->SDID�Ĵ���
	PInfo.PINID=(((SIM->SDID)>>0) & 0x0F);//��ȡKinetis ��������
	PInfo.ClockOption=CLOCK_SETUP;      //ϵͳʱ��ѡ��
	SystemCoreClockUpdate();            //���¼���CoreClock
	PInfo.CoreClock=SystemCoreClock;    //CoreClock
	PInfo.BusClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT)+1));     //����BusClock
	PInfo.FlexBusClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV3_MASK)>>SIM_CLKDIV1_OUTDIV3_SHIFT)+1)); //����FlexBusClock
	PInfo.FlashClock=(SystemCoreClock/(((SIM->CLKDIV1&SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+1));   //����FlashClock
  PInfo.FlashSize=(SIM->FCFG1>>24)&0x0F; //�˴���õ���PFlash���ţ�����ֵ��μ�SIM_FCFG1
	PInfo.RAMSize  =(SIM->SOPT1>>12)&0x0F; //�˴���õ���RAM���ţ�����ֵ��μ�SIM_SOPT1
}
//////////////////////////////////////////////////////
//�������� SystemInit 
//��  �ܣ��ṩϵͳ��ʼ��
//////////////////////////////////////////////////////
void SystemInit (void) 
{
	//ϵʱ�ӳ�ʼ��
	//�ڲ����� CLOCK_SETUP=0
#if (CLOCK_SETUP == 0)
	SIM->CLKDIV1 = (u32)0x00110000u; //����ϵͳԤ��Ƶ��
	/* ת�� FEI ģʽ */
	MCG->C1 = (u8)0x06u;
	MCG->C2 = (u8)0x00u;
	MCG->C4|= (1<<6)|(1<<7)|(1<<5);   //�ڲ��ο�����ʱ��32.768KHZ  ��Ƶ���� 2197 ��Ƶ��Ϊ72MHZ �μ�MCG->C4�Ĵ���
	//��Ƶ����:  
	//SIM_CLKDIV1_OUTDIV1(0) CORE     CLOCK  1��Ƶ   UP TO 100M  
	//SIM_CLKDIV1_OUTDIV2(1) BUS      CLOCK  2��Ƶ   UP TO 50M 
	//SIM_CLKDIV1_OUTDIV3(1) FlexBus  ClOCK  2��Ƶ   UP TO 50M 
	//SIM_CLKDIV1_OUTDIV4(3) Flash    ClOCK  3��Ƶ   UP TO 25M 
	SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));
  MCG->C5 = (u8)0x00u;
  MCG->C6 = (u8)0x00u;
  while((MCG->S & MCG_S_IREFST_MASK) == 0u);  //��� FLL�ο�ʱ�����ڲ��ο�ʱ��
  while((MCG->S & 0x0Cu) != 0x00u);           //�ȴ�FLL��ѡ��
	//�ⲿ���� CLOCK_SETUP=1
#elif (CLOCK_SETUP == 1)
	SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(3));
  /* ת�� FBE ģʽ */
	OSC->CR = (u8)0x00u;
	SIM->SOPT2 &= (u8)~(u8)0x01u;
	MCG->C2 = (u8)0x24u;
	MCG->C1 = (u8)0x9Au;
	MCG->C4 &= (u8)~(uint8_t)0xE0u;
	MCG->C5 = (u8)0x03u;
	MCG->C6 = (u8)0x00u;
	while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);//��� FLL�ο�ʱ�����ڲ��ο�ʱ�� 
	while((MCG->S & MCG_S_IREFST_MASK) != 0u); //��� FLL�ο�ʱ�����ڲ��ο�ʱ��
	while((MCG->S & 0x0Cu) != 0x08u);          //�ȴ� FBE ��ѡ��
	MCG->C5 = (u8)0x03u;
	MCG->C6 = (u8)(0x40u|0x18u);		    //PLL48��Ƶ
	while((MCG->S & MCG_S_PLLST_MASK) == 0u);   //�ȴ�PLLS ʱ��Դת�� PLL
	while((MCG->S & MCG_S_LOCK_MASK) == 0u);    //�ȴ�����
  //ת��PEE
	MCG->C1 = (uint8_t)0x1Au;
	while((MCG->S & 0x0Cu) != 0x0Cu);           //�ȴ�PLL���
	while((MCG->S & MCG_S_LOCK_MASK) == 0u);      //�ȴ�PLL����
	//�ⲿ���� ��Ƶ CLOCK_SETUP=2
#elif (CLOCK_SETUP == 2)
	SIM->CLKDIV1 =(SIM_CLKDIV1_OUTDIV1(0)|SIM_CLKDIV1_OUTDIV2(1)|SIM_CLKDIV1_OUTDIV3(1)|SIM_CLKDIV1_OUTDIV4(7));
  /* ת�� FBE ģʽ */
	OSC->CR = (u8)0x00u;
	SIM->SOPT2 &= (u8)~(u8)0x01u;
	MCG->C2 = (u8)0x24u;
	MCG->C1 = (u8)0x9Au;
	MCG->C4 &= (u8)~(uint8_t)0xE0u;
	MCG->C5 = (u8)0x03u;
	MCG->C6 = (u8)0x00u;
	while((MCG->S & MCG_S_OSCINIT_MASK) == 0u);//��� FLL�ο�ʱ�����ڲ��ο�ʱ�� 
	while((MCG->S & MCG_S_IREFST_MASK) != 0u); //��� FLL�ο�ʱ�����ڲ��ο�ʱ��
	while((MCG->S & 0x0Cu) != 0x08u);          //�ȴ� FBE ��ѡ��
	MCG->C5 = (u8)0x01u; //4��Ƶ
	MCG->C6 = (u8)(0x40u|MCG_C6_VDIV(26));		    //PLL48��Ƶ
	while((MCG->S & MCG_S_PLLST_MASK) == 0u);   //�ȴ�PLLS ʱ��Դת�� PLL
	while((MCG->S & MCG_S_LOCK_MASK) == 0u);    //�ȴ�����
  //ת��PEE
	MCG->C1 = (uint8_t)0x1Au;
	while((MCG->S & 0x0Cu) != 0x0Cu);           //�ȴ�PLL���
	while((MCG->S & MCG_S_LOCK_MASK) == 0u);      //�ȴ�PLL����
#endif 
		
}
/////////////////////////////////////////////////////
// �������� SystemCoreClockUpdate()
// ��  �ã� ���¼����ں�ʱ��Ƶ�� �û����޸���Ƶ����������������Լ�����µ���Ƶ
////////////////////////////////////////////////////
void SystemCoreClockUpdate(void)
{
    u32 MCGOUTClock;            //�洢MCGģ��ʱ��Ƶ�ʱ���
    u8 Divider;
    if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x0u) 
	{
    /* ѡ��FLL �� PLL ��� */
      if ((MCG->C6 & MCG_C6_PLLS_MASK) == 0x0u) 
	  {
         /* ѡ��FLL��� */
        if ((MCG->C1 & MCG_C1_IREFS_MASK) == 0x0u) 
		{
        /* ѡ���ⲿ�ο�ʱ�� */
         if ((SIM->SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) == 0x0u) 
		 {
            MCGOUTClock = CPU_XTAL_CLK_HZ;   //ϵͳ�������� MCG ʱ��
         }
		 else 
		 { 
            MCGOUTClock = CPU_XTAL32k_CLK_HZ;  //RTC 32 kHz �������� MCG ʱ��
         } 
        Divider = (uint8_t)(1u << ((MCG->C1 & MCG_C1_FRDIV_MASK) >> MCG_C1_FRDIV_SHIFT));
        MCGOUTClock = (MCGOUTClock / Divider);  //����FLL�ο�ʱ�ӷ�Ƶ
        if ((MCG->C2 & MCG_C2_RANGE_MASK) != 0x0u) 
		{
           MCGOUTClock /= 32u;  //����߷�Χʹ�ܣ������32λ��Ƶ����Ч��
        } 
       } 
	   else 
	   {
        MCGOUTClock = CPU_INT_SLOW_CLK_HZ;     //ѡ�������ڲ��ο�ʱ��
       } 
      /* ѡ����ȷ�ĳ���ȥ���� MCG ���ʱ��*/
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
      /* ѡ�� PLL */
      Divider = (1u + (MCG->C5 & MCG_C5_PRDIV_MASK));
      MCGOUTClock = (u32)(CPU_XTAL_CLK_HZ / Divider);   //���� PLL �ο�ʱ��
      Divider = ((MCG->C6 & MCG_C6_VDIV_MASK) + 24u);
      MCGOUTClock *= Divider;        //���� MCG ���ʱ��
    } 
  }
  else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x40u) 
     {
       /* ѡ���ڲ��ο�ʱ�� */
       if ((MCG->C2 & MCG_C2_IRCS_MASK) == 0x0u) 
	   {
         MCGOUTClock = CPU_INT_SLOW_CLK_HZ;    //ѡ�������ڲ��ο�ʱ�� 
       } 
	   else 
	   { 
         MCGOUTClock = CPU_INT_FAST_CLK_HZ;   //ѡ���ڲ���Ĳο�ʱ�� 
       } 
     } 
	 else if ((MCG->C1 & MCG_C1_CLKS_MASK) == 0x80u) 
	   {
         /* ѡ���ⲿ�ο�ʱ��*/
         if ((SIM->SOPT2 & SIM_SOPT2_MCGCLKSEL_MASK) == 0x0u) 
		 {
            MCGOUTClock = CPU_XTAL_CLK_HZ;     //ϵͳ�������� MCG ʱ��
         } 
		 else 
		 { 
            MCGOUTClock = CPU_XTAL32k_CLK_HZ;  //RTC 32 kHz �������� MCG ʱ��
         } 
       } 
	   else 
	   { 
          return;
       } 
   SystemCoreClock = (MCGOUTClock / (1u + ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> SIM_CLKDIV1_OUTDIV1_SHIFT)));
}
/////////////////////////////////////////////
//��������NVIC_Pgc
//��  ����PriorityGroup ��д���֡�0~7��
//��  �ܣ������жϷ�������
//˵  �����˳����ǽ����жϷ������һ������һ�Σ������ظ�����
//        һ��ϵͳ������һ�ַ��飬ÿ�ַ����������16���жϣ�����
//		  ���ö���ж���ͬһ���ȼ���ϵͳ���������жϴ������Ȱ����ж�������
//        ���˳����д���
//˵  �����˺���COPY NVIC_SetPriority(IRQn_Type IRQn, u32 priority)���core_cm4.h
////////////////////////////////////////////
void NVICPgc(u32 PriorityGroup)
{
    u32 reg_value;
    u32 PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);            
    reg_value  =  SCB->AIRCR;                                    //���ɵļĴ������� 
    reg_value &= ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk);          
    reg_value  =  (reg_value|((uint32_t)0x5FA << SCB_AIRCR_VECTKEY_Pos)|
                    (PriorityGroupTmp << 8));            //дԿ�׺����ȼ�����
    SCB->AIRCR =  reg_value;
}
/////////////////////////////////////////////
//��������NVIC_Setp
//��  ����IRQn ��д�жϱ�ţ�priority �������ȼ�
//��  �ܣ������ж����ȼ�����
//˵  �����˺���COPY NVIC_SetPriority(IRQn_Type IRQn, u32 priority)���core_cm4.h
////////////////////////////////////////////
void NVICSetp(IRQn_Type IRQn, u32 priority)
{
  if(IRQn < 0) {
    SCB->SHP[((u32)(IRQn) & 0xF)-4] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff); } 
  else {
    NVIC->IP[(u32)(IRQn)] = ((priority << (8 - __NVIC_PRIO_BITS)) & 0xff);    }   //Ϊ�ж��������ȼ�
}
//��λ
void SystemSoftReset(void)
{   
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 
