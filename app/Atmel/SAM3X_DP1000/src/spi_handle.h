#ifndef BASIC_SPI_HANDLE_H
#define BASIC_SPI_HANDLE_H

#include "portmacro.h"
#include <semphr.h>

xSemaphoreHandle xSemaNetHandle;

typedef struct{
	bool alloc;
	u_char len;
	u_char buf[8];
}spi_data_send_t ;

extern spi_data_send_t spi_t;
/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
void vStartSpiTaskLauncher( unsigned portBASE_TYPE uxPriority );

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
portTASK_FUNCTION_PROTO( vSpiHandle, pvParameters );

#endif

