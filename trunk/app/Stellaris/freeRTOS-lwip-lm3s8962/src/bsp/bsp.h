#ifndef _BSP_H_
#define _BSP_H_

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

//-----------------------------------bsp.c---------------------------------
extern void BSP_Init(void);


//-----------------------------------bsp_led.c---------------------------------
extern void BSP_LedInit(void);
extern void BSP_LedSet(unsigned char id);
extern void BSP_LedClear(unsigned char id);
extern void BSP_LedToggle(unsigned char id);



#endif
