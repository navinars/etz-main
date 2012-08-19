/***********************************************************************************
  Filename:     hal_uart.c

  Description:  UART interface library. Works with HW flow control and
                optionally with buffered TX transmission. Reception is always
                buffered.

***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "hal_types.h"
#include "hal_uart.h"
#include "hal_board.h"
#include "util_buffer.h"
#include "hal_int.h"
#include "hal_mcu.h"


/*********************************************************************
 * CONSTANTS
 */
#define HAL_UART_0_PERCFG_BIT     0x01  // USART0 on P0, so clear this bit.
#define HAL_UART_0_P0_RX_TX       0x0C  // Peripheral I/O Select for Rx/Tx.


// UxCSR - USART Control and Status Register.
#define CSR_MODE                   0x80
#define CSR_RE                     0x40
#define CSR_SLAVE                  0x20
#define CSR_FE                     0x10
#define CSR_ERR                    0x08
#define CSR_RX_BYTE                0x04
#define CSR_TX_BYTE                0x02
#define CSR_ACTIVE                 0x01

// UxUCR - USART UART Control Register.
#define UCR_FLUSH                  0x80
#define UCR_FLOW                   0x40
#define UCR_D9                     0x20
#define UCR_BIT9                   0x10
#define UCR_PARITY                 0x08
#define UCR_SPB                    0x04
#define UCR_STOP                   0x02
#define UCR_START                  0x01

#define UTX0IE                     0x04
#define UTX1IE                     0x08

#define P2DIR_PRIPO                0xC0

// Incompatible redefinitions between the 2 UART driver sub-modules:
#undef PxSEL
#undef UxCSR
#undef UxUCR
#undef UxDBUF
#undef UxBAUD
#undef UxGCR
#undef URXxIE
#undef UTXxIE
#undef UTXxIF
#if (HAL_UART_ISR == 1)
#define PxOUT                      P0
#define PxDIR                      P0DIR
#define PxSEL                      P0SEL
#define UxCSR                      U0CSR
#define UxUCR                      U0UCR
#define UxDBUF                     U0DBUF
#define UxBAUD                     U0BAUD
#define UxGCR                      U0GCR
#define URXxIE                     URX0IE
#define UTXxIE                     UTX0IE
#define UTXxIF                     UTX0IF
#define UxRX_TX                    0x0C
#define HAL_UART_PERCFG_BIT        0x01
#define HAL_UART_Px_CTS            0x10         // Peripheral I/O Select for CTS.
#define HAL_UART_Px_RTS            0x20         // Peripheral I/O Select for RTS.
#else
#define PxOUT                      P1
#define PxDIR                      P1DIR
#define PxSEL                      P1SEL
#define UxCSR                      U1CSR
#define UxUCR                      U1UCR
#define UxDBUF                     U1DBUF
#define UxBAUD                     U1BAUD
#define UxGCR                      U1GCR
#define URXxIE                     URX1IE
#define UTXxIE                     UTX1IE
#define UTXxIF                     UTX1IF
#define UxRX_TX                    0xC0
#define HAL_UART_PERCFG_BIT        0x02
#define HAL_UART_Px_CTS            0x10         // Peripheral I/O Select for CTS.
#define HAL_UART_Px_RTS            0x20         // Peripheral I/O Select for RTS.
#endif

/***********************************************************************************
* LOCAL VARIABLES
*/
ringBuf_t rbRxBuf;

#ifndef HAL_DIRECT_UART_TX
static ringBuf_t rbTxBuf;
#endif
static ISR_FUNC_PTR puISR = NULL;


/***********************************************************************************
* LOCAL FUNCTIONS
*/


/***********************************************************************************
* @fn      halUartRxIntEnable
*
* @brief   Enable UART RX interrupt
*
* @param   none
*
* @return  none
*/
void halUartRxIntEnable(void)
{
	/* Enable Uart_RX interrupt*/
#if (HAL_UART_PORT == 0)
    IEN0 |= 0x04;
#endif
	
#if (HAL_UART_PORT == 1)
    IEN0 |= 0x04;
#endif
}


/***********************************************************************************
* @fn      halUartTxIntEnable
*
* @brief   Enable UART TX interrupt
*
* @param   none
*
* @return  none
*/
static void halUartTxIntEnable(void)
{
	/* Enable Uart_TX interrupt*/
#if (HAL_UART_PORT == 0)
    IEN2 |= UTX0IE;
#endif
	
#if (HAL_UART_PORT == 1)
    IEN2 |= UTX1IE;
#endif
}


/***********************************************************************************
* @fn      halUARTRxIntDisable
*
* @brief   Disable UART RX interrupt
*
* @param   none
*
* @return  none
*/
void halUartRxIntDisable(void)
{
	/* Disable Uart_RX interrupt*/
#if (HAL_UART_PORT == 0)
    IEN2 &= ~0x04;
#endif
	
#if (HAL_UART_PORT == 1)
    IEN0 &= ~0x04;
#endif
}


/***********************************************************************************
* @fn      halUARTTxIntDisable
*
* @brief   Disable UART TX interrupt
*
* @param   none
*
* @return  none
*/
static void halUartTxIntDisable(void)
{
	/* Disable Uart_TX interrupt*/
#if (HAL_UART_PORT == 0)
    IEN2 &= ~UTX0IE;
#endif
	
#if (HAL_UART_PORT == 1)
    IEN2 &= ~UTX1IE;
#endif
}


/***********************************************************************************
* @fn      halUartInit
*
* @brief   Initalise UART. Supported baudrates are: 19220, 38400, 57600 and 115200
*
* @param   uint8 baudrate
*          uint8 options - this parameter is ignored
*
* @return  none
*/
void halUartInit(uint8 baudrate, uint8 options)
{
	(void) options;
	
	// Set P2 prority - USART0 over USART1 if both are defined
	P2DIR &= ~P2DIR_PRIPO;
	P2DIR |= HAL_UART_PRIPO;
	
	PERCFG &= ~HAL_UART_PERCFG_BIT;    // Set UART0 I/O location to P0.
	
	/* Enable Tx and Rx on P0 */
	P0SEL |= HAL_UART_0_P0_RX_TX;
	
	/* Make sure ADC dosen't use this*/
  	ADCCFG &= ~UxRX_TX;
	
	/* Mode is UART Mode*/
	U0CSR = CSR_MODE;
    U0UCR|= UCR_FLUSH;
    
    // Set baud rate
    switch (baudrate)
	{
		case HAL_UART_BAUDRATE_9600:
			U0BAUD = BAUD_M_9600;
			U0GCR = BAUD_E_9600;
			break;
		case HAL_UART_BAUDRATE_19200:
			U0BAUD = BAUD_M_19200;
			U0GCR = BAUD_E_19200;
			break;
		case HAL_UART_BAUDRATE_38400:
			U0BAUD = BAUD_M_38400;
			U0GCR = BAUD_E_38400;
			break;
		case HAL_UART_BAUDRATE_57600:
			U0BAUD = BAUD_M_57600;
			U0GCR = BAUD_E_57600;
			break;
		default:
			// 115200 default
			U0BAUD = BAUD_M_115200;
			U0GCR = BAUD_E_115200;
    }
    
    // Initialize the RX buffer
//    bufInit(&rbRxBuf);
    
    // Enable transmit register empty interrupt
    UTX0IF = 1;
	
    // Initialize the TX buffer
    bufInit(&rbTxBuf);
    
    // One stop bit
    U0UCR |= UCR_STOP; 
    
    // Prepare for reception
    URX0IF = 0;
    U0CSR |= CSR_RE;
//	URX0IE = 1;
//	UxDBUF = 0;  // Prime the ISR pump.
    
    // Enable HW flow control
//	halUartEnableRxFlow(TRUE);
}

/***********************************************************************************
* @fn      halUartRxInterruptConfig
*
* @brief   Write data buffer to UART
*
* @param   uint8* buf - buffer with data to write
*          uint16 length - number of bytes to write
*
* @return  uint16 - number of bytes written
*/
void halUartRxInterruptConfig(ISR_FUNC_PTR pf)
{
    uint8 x;
    HAL_INT_LOCK(x);
    puISR = pf;
    HAL_INT_UNLOCK(x);

}

/***********************************************************************************
* @fn      halUartWrite
*
* @brief   Write data buffer to UART
*
* @param   uint8* buf - buffer with data to write
*          uint16 length - number of bytes to write
*
* @return  uint16 - number of bytes written
*/
uint16 halUartWrite(const uint8* buf, uint16 length)
{
    uint16 i;
    for(i = 0; i < length; i++)
    {
        U0DBUF = buf[i];            		// Output character
        while(UTX0IF == 0);    	// Wait for TX buffer ready to receive new byte
		UTX0IF = 0;
    }
    return (i+1);
}


/***********************************************************************************
* @fn      halUartBufferedWrite
*
* @brief   Write data buffered to UART. Data is written into a buffer, and the
*          buffer is emptied by UART TX interrupt ISR
*
* @param   uint8* buf - buffer with data to write
*          uint16 length - number of bytes to write
*
* @return  none
*/
uint16 halUartBufferedWrite(const uint8* buf, uint16 length)
{
    uint16 nBytes=0;
    while ( (nBytes += bufPut(&rbTxBuf,buf,length)) == 0 )
        halMcuWaitMs(5);

    // Enable UART TX interrupt
    halUartTxIntEnable();
    return nBytes;
}


/***********************************************************************************
* @fn      halUartRxGetByte
*
* @brief   Read byte from UART RX buffer
*
* @param   none
*
* @return  none
*/
uint8 halUartRxGetByte(void)
{

#if (HAL_UART_PORT == 0)
    return U0DBUF;
#endif
	
#if (HAL_UART_PORT == 1)
    return U1DBUF;
#endif
}


/***********************************************************************************
* @fn      halUartRead
*
* @brief   Read data from 7UART Rx buffer
*
* @param   uint8* buf - buffer with data to read in to
*          uint16 length - number of bytes to read
*
* @return  none
*/
uint16 halUartRead(uint8* buf, uint16 length)
{
	return bufGet(&rbRxBuf, (uint8 *)buf, length);
}


/***********************************************************************************
* @fn      halUartGetNumRxBytes
*
* @brief   Returns number of bytes in RX buffer
*
* @param   none
*
* @return  uint8
*/
uint16 halUartGetNumRxBytes(void)
{
	return bufNumBytes(&rbRxBuf);
}


/***********************************************************************************
* @fn      halUartEnableRxFlow
*
* @brief   Signal ready/not ready to receive characters on UART
*
* @param   uint8 enable - TRUE to signal ready to receive on UART
*                         FALSE to signal not ready to receive on UART
*
* @return  none
*/
void halUartEnableRxFlow(uint8 enable)
{
    // Enable RX flow
    if(enable) {
        HAL_RTS_CLR();
    }
    // Disable RX flow
    else {
        HAL_RTS_SET();
    }
}

/***********************************************************************************
* @fn      usart0Rx_ISR
*
* @brief   ISR framework for the USCI A0/B0 Receive component
*
* @param   none
*
* @return  none
*/
HAL_ISR_FUNCTION(usart0Rx_ISR, URX0_VECTOR)
{
	uint8 x;
    HAL_INT_LOCK(x);
	
	if(puISR){
		(*puISR)();                 // Execute the custom ISR
	}

    HAL_INT_UNLOCK(x);
}

/***********************************************************************************
* @fn      usart1Tx_ISR
*
* @brief   ISR framework for the USCI A0/B0 transmit component
*
* @param   none
*
* @return  none
*/
HAL_ISR_FUNCTION(usart0Tx_ISR, UTX0_VECTOR)
{
	uint8 c;

	UTX0IF = 0;
	if (bufGet(&rbTxBuf, &c, 1) == 1) {
		U0DBUF = c;
	}

	// If buffer empty, disable uart TX interrupt
	if( (bufNumBytes(&rbTxBuf)) == 0) {
		halUartTxIntDisable();
	}
}
