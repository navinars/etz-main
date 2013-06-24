
#ifndef INT_H
#define INT_H


#include "msp430.h"

unsigned char  OSCPUSaveSR(void);
void       OSCPURestoreSR(unsigned char cpu_sr);

#endif
