#ifndef _BSP_H_
#define _BSP_H_



#define KEY				BIT4
#define IO				BIT2


#include "msp430.h"
#include <stdint.h>
#include <string.h>
#include "cc1101.h"
#include "cc1101_defs.h"
#include "radio_handle.h"


extern void gpio_init(void);

#endif