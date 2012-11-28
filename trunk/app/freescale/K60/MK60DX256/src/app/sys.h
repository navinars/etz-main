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
#ifndef __SYS_H__
#define __SYS_H__
#include <MK60DZ10.h>
#include "wdog.h"

//Ƶ������
#define CLOCK_SETUP     (1)	 
/* Ԥ�����ʱ������
   0 ... �ڲ�����
	       Core/System Clock: 96M 
				 Bus         Clock: 48M
				 FlexBus     Clock: 48M
				 Flash       Clock: 24M
   1 ... �ⲿ8M���� 
	       Core/System Clock: 96M 
				 Bus         Clock: 48M
				 FlexBus     Clock: 48M
				 Flash       Clock: 24M
   2 ... �ⲿ8M���� ��Ƶ
	       Core/System Clock: 200M 
				 Bus         Clock: 100M
				 FlexBus     Clock: 100M
				 Flash       Clock: 25M
*/


//�ض��峣�����ݱ�������
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;
typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
//���ó������궨��
#define TRUE		(1)
#define FALSE		(0)
//�����ֵ����Сֵ 
#define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) ) 
#define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) ) 
//�õ�һ���ṹ����field��ռ�õ��ֽ��� 
#define FSIZ( type, field ) sizeof( ((type *) 0)->field ) 
//�õ�һ�������ĵ�ַ��word��ȣ� 
#define  B_PTR( var )  ( (byte *) (void *) &(var) ) 
#define  W_PTR( var )  ( (word *) (void *) &(var) ) 
//��������Ԫ�صĸ��� 
#define  ARR_SIZE( a )  ( sizeof( (a) ) / sizeof( (a[0]) ) ) 

#if (CLOCK_SETUP == 0)
    #define CPU_XTAL_CLK_HZ                 4000000u  //ʱ�ӷ�����Ƶ��Hz 
    #define CPU_XTAL32k_CLK_HZ              32768u    //ʱ�ӷ�����Ƶ��Hz 
    #define CPU_INT_SLOW_CLK_HZ             32768u    //�����ڲ�ʱ������Ƶ�� Hz 
    #define CPU_INT_FAST_CLK_HZ             4000000u  //�����ڲ�ʱ������Ƶ�� Hz
    #define DEFAULT_SYSTEM_CLOCK            96000000u //Ĭ��ϵͳʱ��Ƶ��
#elif (CLOCK_SETUP == 1)
    #define CPU_XTAL_CLK_HZ                 8000000u  //ʱ�ӷ�����Ƶ��Hz 
    #define CPU_XTAL32k_CLK_HZ              32768u    //ʱ�ӷ�����Ƶ��Hz /
    #define CPU_INT_SLOW_CLK_HZ             32768u    //�����ڲ�ʱ������Ƶ�� Hz 
    #define CPU_INT_FAST_CLK_HZ             4000000u  //�����ڲ�ʱ������Ƶ�� Hz
    #define DEFAULT_SYSTEM_CLOCK            96000000u //Ĭ��ϵͳʱ��Ƶ��
#elif (CLOCK_SETUP == 2)
    #define CPU_XTAL_CLK_HZ                 8000000u  //ʱ�ӷ�����Ƶ��Hz 
    #define CPU_XTAL32k_CLK_HZ              32768u    //ʱ�ӷ�����Ƶ��Hz /
    #define CPU_INT_SLOW_CLK_HZ             32768u    //�����ڲ�ʱ������Ƶ�� Hz 
    #define CPU_INT_FAST_CLK_HZ             4000000u  //�����ڲ�ʱ������Ƶ�� Hz
    #define DEFAULT_SYSTEM_CLOCK            200000000 //Ĭ��ϵͳʱ��Ƶ��
#endif
//оƬ���ͺ궨��  �μ�SIM_SDID�Ĵ���
#define FAMID_K10    (0)
#define FAMID_K20    (1)
#define FAMID_K30    (2)
#define FAMID_K40    (3)
#define FAMID_K60    (4)
#define FAMID_K70    (5)
#define FAMID_K50K52 (6)
#define FAMID_K51K53 (7)
//���ŷ�װ����
#define PIND_32      (2)
#define PIND_48      (4)
#define PIND_64      (5)
#define PIND_80      (6)
#define PIND_81      (7)
#define PIND_100     (8)
#define PIND_121     (9)
#define PIND_144     (10)
#define PIND_196     (12)
#define PIND_256     (14)

//��������Ϣ����Ƶ��Ϣ�ṹ
typedef struct
{
	u8 FAMID; //Kinetisϵ�м������ͺ� ����μ� SIM->SDID�Ĵ���
	u8 PINID; //������Ϣ
	u8 ClockOption;  //��Ƶѡ��
	u32 CoreClock;   //�ں�ʱ��
	u32 BusClock;    //����ʱ��
	u32 FlexBusClock;//FlexBusʱ��
	u32 FlashClock;  //Flashʱ��
	u16 FlashSize;   //Flash��С
	u16 RAMSize;     //RAM��С
} PInfo_Type;
extern PInfo_Type PInfo;
//������ʵ�ֵĽӿں����б�
void SystemSoftReset(void);                                     //��λ
void GetProcessorInfo(void);                                    //��ô�������Ϣ
void SystemInit (void);                                         //ϵͳ��ʼ��
void SystemCoreClockUpdate (void);                              //���¼����ں�Ƶ��
void NVIC_Pgc (u32 PriorityGroup);                              //����NVIC�ж���
void NVIC_Setp (IRQn_Type IRQn, u32 priority);                  //����NVIC�ж����ȼ�
#endif
