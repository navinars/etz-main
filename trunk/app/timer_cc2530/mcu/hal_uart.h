/***********************************************************************************
  Filename:     hal_uart.h

  Description:  hal UART library header file

***********************************************************************************/

#ifndef HAL_UART_H
#define HAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************
* INCLUDES
*/
#include "hal_types.h"
#include "util_buffer.h"

/***********************************************************************************
 * CONSTANTS AND DEFINES
 */
#define HAL_UART_PORT					0

/* Serial Port Baudrate Settings */
#define HAL_UART_BAUDRATE_4800        0x01
#define HAL_UART_BAUDRATE_9600        0x02
#define HAL_UART_BAUDRATE_19200       0x03
#define HAL_UART_BAUDRATE_38400       0x04
#define HAL_UART_BAUDRATE_57600       0x05
#define HAL_UART_BAUDRATE_115200      0x06

//#if BSP_CONFIG_CLOCK_MHZ==32
#define BAUD_M_9600                  59
#define BAUD_M_19200                 59
#define BAUD_M_38400                 59
#define BAUD_M_57600                216
#define BAUD_M_115200               216

#define BAUD_E_9600                   8
#define BAUD_E_19200                  9
#define BAUD_E_38400                 10
#define BAUD_E_57600                 10
#define BAUD_E_115200                11
	
/* Stop Bits */
#define HAL_UART_ONE_STOP_BIT         0x01
#define HAL_UART_TWO_STOP_BITS        0x02

/* Parity settings */
#define HAL_UART_NO_PARITY            0x04
#define HAL_UART_EVEN_PARITY          0x08
#define HAL_UART_ODD_PARITY           0x10

/* Number of bits in data field */
#define HAL_UART_7_BIT_DATA           0x20
#define HAL_UART_8_BIT_DATA           0x40

	
/*********************************************************************************************************
 * GLOBAL VARIABLES
 */
	

/***********************************************************************************
 * GLOBAL FUNCTIONS
 */
void   halUartRxIntEnable(void);
void   halUartRxIntDisable(void);
void   halUartInit(uint8 baudrate, uint8 options);
void   halUartRxInterruptConfig(ISR_FUNC_PTR pf);
uint16 halUartWrite(const uint8* buf, uint16 length);
uint16 halUartRead(uint8* buf, uint16 length);
uint8  halUartRxGetByte(void);
uint16 halUartGetNumRxBytes(void);
void   halUartEnableRxFlow(uint8 enable);
uint16 halUartBufferedWrite(const uint8* buf, uint16 length);


#ifdef  __cplusplus
}
#endif

/**********************************************************************************/
#endif
