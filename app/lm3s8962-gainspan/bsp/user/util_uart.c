/*******************************************************************************
 Name        : Commdrv.c
 Author      : Writed by songzi&jingjing in 2011.09.07
 Version     : 1.0
 Description : led low-level driver
*******************************************************************************/
#include "includes.h"
#include "util_uart.h"

/*
*********************************************************************************************************
*                                           LOCAL DEFINES
*********************************************************************************************************
*/
#define UART_FIFOS_NUM						14


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/
uart_rx_buf_t rxBuf;


/********************************************************************************************************
*                                          BSP_Uart_Init()
*
* Description : none.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void BSP_Uart_Init(U8 port, U32 baud, bool rxISREn, bool txISREn)
{
	switch (port)
	{
	case BSP_SER_ID_UART0:
		SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0 );
		SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );
		GPIOPinTypeUART( GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 );
	
		UARTConfigSetExpClk( UART0_BASE, SysCtlClockGet(), baud,
						   ( UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
							 UART_CONFIG_PAR_NONE ) );
		if(rxISREn)
		{
			UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX7_8);
			IntEnable(INT_UART0);
			UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

			if(txISREn == true) {
				UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
			}
		}
		break;
		
	case BSP_SER_ID_UART1:
		SysCtlPeripheralEnable( SYSCTL_PERIPH_UART1 );
		SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD );
		GPIOPinTypeUART( GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3 );
		
		UARTConfigSetExpClk( UART1_BASE, SysCtlClockGet(), baud,
				( UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
				 UART_CONFIG_PAR_NONE ) );
		if(rxISREn)
		{
			UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX1_8, UART_FIFO_RX7_8);
			IntEnable(INT_UART1);

			if(txISREn)
				UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
			else
				UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
		}
		break;
		
	case BSP_SER_ID_UART2:
		SysCtlPeripheralEnable( SYSCTL_PERIPH_UART2 );
        SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOG );
        GPIOPinTypeUART( GPIO_PORTG_BASE, GPIO_PIN_0 | GPIO_PIN_1 );
	
	
		UARTConfigSetExpClk( UART2_BASE, SysCtlClockGet(), baud,
				( UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
				 UART_CONFIG_PAR_NONE ) );
		if(rxISREn)
		{
			UARTFIFOLevelSet(UART2_BASE, UART_FIFO_TX1_8, UART_FIFO_RX7_8);
			IntEnable(INT_UART2);

			if(txISREn)
				UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
			else
				UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
		}
		break;
		
	default:
		break;
	}
}


/********************************************************************************************************
*                                          BSP_Uart_Send()
*
* Description : none.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
int  BSP_Uart_Send(unsigned char *pBuf, unsigned long len)
{
	U32 iLoop;
	
	for(iLoop = 0;iLoop < len;iLoop ++)
	{
		/* 使能UART库发送，循环检测，无超时机制*/
		UARTCharPut(UART0_BASE, *pBuf ++);
	}
	
	return 1;
}

/********************************************************************************************************
*                                          BSP_Uart_Send()
*
* Description : none.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void UART0_Int_Handler (void)
{
	U16 status;
	U16 iLoop;
	
	// Read COM0 interrupt status,and clear interrupt status.
	status = UARTIntStatus(UART0_BASE, true);
	UARTIntClear(UART0_BASE, status);
	
		// Read UART FIFOs data at most 13.
	for (iLoop = 0;iLoop < (UART_FIFOS_NUM - 1);iLoop ++)
	{
		if (UARTCharsAvail(UART0_BASE))
		{
			rxBuf.buf[rxBuf.num] = UARTCharGetNonBlocking(UART0_BASE);
			rxBuf.num ++;
			
			// Aviod UART receive buffer boundary greater than 512.
			if(rxBuf.num > 512)
			{
				rxBuf.num = 0;
				memset(rxBuf.buf, 512, 0x00);
				rxBuf.status = FALSE;
				break;
			}
		}
	}
	
	if (status & UART_RIS_RTRIS)
	{
		rxBuf.status = TRUE;
	}
}

/********************************************************************************************************
*                                          BSP_Uart0_Read()
*
* Description : none.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
U8 BSP_Uart0_Read(U8 *pData, U16 length)
{
	long tmp;
	tmp = UARTCharGetNonBlocking(UART0_BASE);
	
	if(tmp == -1) {
		return 0;
	} else {
		*pData = tmp;
		return 1;
	}
}
