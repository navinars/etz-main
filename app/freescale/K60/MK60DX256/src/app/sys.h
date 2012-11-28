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
#ifndef __SYS_H__
#define __SYS_H__
#include <MK60DZ10.h>
#include "wdog.h"

//频率设置
#define CLOCK_SETUP     (1)	 
/* 预定义的时钟设置
   0 ... 内部晶振
	       Core/System Clock: 96M 
				 Bus         Clock: 48M
				 FlexBus     Clock: 48M
				 Flash       Clock: 24M
   1 ... 外部8M晶振 
	       Core/System Clock: 96M 
				 Bus         Clock: 48M
				 FlexBus     Clock: 48M
				 Flash       Clock: 24M
   2 ... 外部8M晶振 超频
	       Core/System Clock: 200M 
				 Bus         Clock: 100M
				 FlexBus     Clock: 100M
				 Flash       Clock: 25M
*/


//重定义常用数据变量类型
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;
typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
//常用常量及宏定义
#define TRUE		(1)
#define FALSE		(0)
//求最大值和最小值 
#define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) ) 
#define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) ) 
//得到一个结构体中field所占用的字节数 
#define FSIZ( type, field ) sizeof( ((type *) 0)->field ) 
//得到一个变量的地址（word宽度） 
#define  B_PTR( var )  ( (byte *) (void *) &(var) ) 
#define  W_PTR( var )  ( (word *) (void *) &(var) ) 
//返回数组元素的个数 
#define  ARR_SIZE( a )  ( sizeof( (a) ) / sizeof( (a[0]) ) ) 

#if (CLOCK_SETUP == 0)
    #define CPU_XTAL_CLK_HZ                 4000000u  //时钟发生器频率Hz 
    #define CPU_XTAL32k_CLK_HZ              32768u    //时钟发生器频率Hz 
    #define CPU_INT_SLOW_CLK_HZ             32768u    //慢速内部时钟振荡器频率 Hz 
    #define CPU_INT_FAST_CLK_HZ             4000000u  //快速内部时钟振荡器频率 Hz
    #define DEFAULT_SYSTEM_CLOCK            96000000u //默认系统时钟频率
#elif (CLOCK_SETUP == 1)
    #define CPU_XTAL_CLK_HZ                 8000000u  //时钟发生器频率Hz 
    #define CPU_XTAL32k_CLK_HZ              32768u    //时钟发生器频率Hz /
    #define CPU_INT_SLOW_CLK_HZ             32768u    //慢速内部时钟振荡器频率 Hz 
    #define CPU_INT_FAST_CLK_HZ             4000000u  //快速内部时钟振荡器频率 Hz
    #define DEFAULT_SYSTEM_CLOCK            96000000u //默认系统时钟频率
#elif (CLOCK_SETUP == 2)
    #define CPU_XTAL_CLK_HZ                 8000000u  //时钟发生器频率Hz 
    #define CPU_XTAL32k_CLK_HZ              32768u    //时钟发生器频率Hz /
    #define CPU_INT_SLOW_CLK_HZ             32768u    //慢速内部时钟振荡器频率 Hz 
    #define CPU_INT_FAST_CLK_HZ             4000000u  //快速内部时钟振荡器频率 Hz
    #define DEFAULT_SYSTEM_CLOCK            200000000 //默认系统时钟频率
#endif
//芯片类型宏定义  参见SIM_SDID寄存器
#define FAMID_K10    (0)
#define FAMID_K20    (1)
#define FAMID_K30    (2)
#define FAMID_K40    (3)
#define FAMID_K60    (4)
#define FAMID_K70    (5)
#define FAMID_K50K52 (6)
#define FAMID_K51K53 (7)
//引脚封装定义
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

//处理器信息及主频信息结构
typedef struct
{
	u8 FAMID; //Kinetis系列家族类型号 具体参见 SIM->SDID寄存器
	u8 PINID; //引脚信息
	u8 ClockOption;  //主频选项
	u32 CoreClock;   //内核时钟
	u32 BusClock;    //总线时钟
	u32 FlexBusClock;//FlexBus时钟
	u32 FlashClock;  //Flash时钟
	u16 FlashSize;   //Flash大小
	u16 RAMSize;     //RAM大小
} PInfo_Type;
extern PInfo_Type PInfo;
//本构件实现的接口函数列表
void SystemSoftReset(void);                                     //软复位
void GetProcessorInfo(void);                                    //获得处理器信息
void SystemInit (void);                                         //系统初始化
void SystemCoreClockUpdate (void);                              //重新计算内核频率
void NVIC_Pgc (u32 PriorityGroup);                              //设置NVIC中断组
void NVIC_Setp (IRQn_Type IRQn, u32 priority);                  //设置NVIC中断优先级
#endif
