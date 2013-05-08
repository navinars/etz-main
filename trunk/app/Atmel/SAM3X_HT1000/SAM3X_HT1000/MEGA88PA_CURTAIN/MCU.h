//*********************************************************************
//	单片机和IO定义
//*********************************************************************
//
//	版本:		1.0
//	日期:		2007/09/20
//
//--------------------------------------------------------------------

#ifndef	MCU_H
#define MCU_H


#define MCU_ATMega88
#define F_CPU 8000000UL

#ifdef MCU_ATMega88
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
#define wdt_reset()	   __asm__ __volatile__ ("wdr")
//#define _delay_loop_2()	_delay_loop_2()

#endif


#endif	// #ifdef MCU_H
