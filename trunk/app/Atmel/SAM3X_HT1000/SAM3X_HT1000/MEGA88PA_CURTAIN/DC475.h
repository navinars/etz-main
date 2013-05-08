//*********************************************************************
//	Header define file for FBM.1.0.c
//*********************************************************************
//	Filename:	FBM.h
//	Author:		ZhouYaFei
//	Rev:		1.0
//	Date:		2010/12/10
//	CPU:		ATmega88
//
//********************************************************************
#include "MCU.h"
#ifndef	DC193V_H
#define DC193V_H

#define BIT(x)	(1 << (x))

//PORTB
#define CLK     	0//O
#define CS_WIFI 	1//O
#define PWM		2//O

//PORTC
#define HALL1		0//I
#define HALL2		1//I
#define KEY1		2//I常态是低

#define SW_KEY1		4//I
#define SW_KEY2		5//I

//PORTD
#define MOSI	        4//I
#define CS_LAN		6//I
#define DOOR_WAY	5//O
#define MISO	        3//O
#define LED1		7//O常态为高
#define EN_485		2//O常态为高
// 定义I/O操作
//9个输入脚
#define PIN_SPI_CLK		(PINB & BIT(CLK))		//--PORTB
#define PIN_SPI_CS_WIFI		(PINB & BIT(CS_WIFI))		//--PORTB

#define PIN_KEY1		(PINC & BIT(KEY1))		//--PORTC
#define PIN_SW_KEY1		(PINC & BIT(SW_KEY1))	        //--PORTC
#define PIN_SW_KEY2		(PINC & BIT(SW_KEY2))	        //--PORTC
#define PIN_HALL1		(PINC & BIT(HALL1))		//--PORTC
#define PIN_HALL2		(PINC & BIT(HALL2))		//--PORTC

//#define PIN_DOORWAY		(PIND & BIT(DOOR_WAY))	        //--PORTD
#define PIN_SPI_MOSI		(PIND & BIT(MOSI))	        //--PORTD
#define PIN_SPI_CS_LAN		(PIND & BIT(CS_LAN))		//--PORTD

//3个输出脚
#define SET_PWM			(PORTB |= BIT(PWM))		//--PORTB
#define CLR_PWM			(PORTB &= ~BIT(PWM))

#define CLR_LED1		(PORTD |= BIT(LED1))		//--PORTC
#define SET_LED1		(PORTD &= ~BIT(LED1))

#define SET_DOOR		(PORTD |= BIT(DOOR_WAY))	//--PORTD
#define CLR_DOOR		(PORTD &= ~BIT(DOOR_WAY))

#define SET_SPI_MISO		(PORTD |= BIT(MISO))	//--PORTD
#define CLR_SPI_MISO		(PORTD &= ~BIT(MISO))

#endif
