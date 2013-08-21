#ifndef BASIC_SPI_HANDLE_H
#define BASIC_SPI_HANDLE_H

#include "portmacro.h"
#include <semphr.h>

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
portTASK_FUNCTION_PROTO( vUartTask, pvParameters );
void vStartUartTaskLauncher( unsigned portBASE_TYPE uxPriority );
#endif

