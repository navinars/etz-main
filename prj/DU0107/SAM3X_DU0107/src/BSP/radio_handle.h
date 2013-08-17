#ifndef CC1101_HANDLE_H
#define CC1101_HANDLE_H

#include "compiler.h"
#include "portmacro.h"

#include "radio_config.h"

typedef struct{
	bool			alloc;
	uint8_t			*dptr;
	uint8_t			len;
	uint8_t			lqi;
	uint8_t			index;
	uint8_t			buf[aMaxPHYPacketSize+1];
}phy_buf_t;

void vStartRadioTaskLauncher( unsigned portBASE_TYPE uxPriority );

#endif