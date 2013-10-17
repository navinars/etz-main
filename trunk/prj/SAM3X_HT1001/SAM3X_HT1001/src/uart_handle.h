#ifndef BASIC_SPI_HANDLE_H
#define BASIC_SPI_HANDLE_H

#include "portmacro.h"
#include <semphr.h>

#define SPI_BUF_NUM				16
#define UART_BUF_NUM			100

typedef struct{
	bool			alloc;
	int				port;
	uint8_t			len;
	uint8_t			buf[SPI_BUF_NUM];
}spi_data_send_t ;

typedef struct{
	bool			alloc;
	uint8_t			rxlen;
	uint8_t			txlen;
	uint8_t			rebuf[UART_BUF_NUM];
	uint8_t			txbuf[UART_BUF_NUM];
}uart_hdr_t;

typedef struct{
	bool alloc;
	int port;
	uint8_t rxlen;
	uint8_t rxbuf[8];
	uint8_t txlen;
	uint8_t txbuf[8];
}uart_data_frm_t;

xSemaphoreHandle xSemaNetHandle;

extern spi_data_send_t spi_frm_t;
extern uart_data_frm_t uart_frm_t;

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
extern unsigned int Crc16CheckSum(unsigned char *ptr, unsigned char length);

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
void vStartUartTaskLauncher( unsigned portBASE_TYPE uxPriority );

/*! \brief WEB server main task
 *
 *  \param pvParameters   Input. Not Used.
 *
 */
portTASK_FUNCTION_PROTO( vSpiHandle, pvParameters );

#endif

