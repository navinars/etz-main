#ifndef CC1101_HANDLE_H
#define CC1101_HANDLE_H

#include "compiler.h"
#include "portmacro.h"

#include "radio_config.h"

typedef struct _buffer_t
{
	struct      _buffer_t *next;									///< Next pointer
	bool        alloc;												///< Alloc flag
	U8          *dptr;												///< Data pointer - points to current position in buffer array
	U8          len;												///< Len of the data
	U8          lqi;												///< Link quality indicator
	U8          index;												///< Index used for buffer tracking and debugging
	U8          buf[aMaxPHYPacketSize+1];							///< Main data storage
} buffer_t;


typedef struct{
	bool			alloc;
	uint8_t			*dptr;
	uint8_t			len;
	uint8_t			lqi;
	uint8_t			index;
	uint8_t			buf[aMaxPHYPacketSize+1];
}phy_buf_t;

typedef struct{
	uint8_t			frm_type;
	uint8_t			len;
	uint8_t			buf[2];
}mac_data_send_t;

xQueueHandle rQueueISR;

void vStartRadioTaskLauncher( unsigned portBASE_TYPE uxPriority );

#endif