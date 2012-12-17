/* ------------------------------------------------------------------------------------------------------
 * File: cc2520-arch.c
 * Data: 2012/10/20
 * Author: MC
 * Ver: V0.1.1b
 * -------------------------------------------------------------------------------------------------------
 */
#include "cc2520-arch.h"
#include "includes.h"
 
 

/* ------------------------------------------------------------------------------------------------------
 *									cc2520_arch_init()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void cc2520_arch_init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);					/* Initalize ports and SPI. */
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPadConfigSet(GPIO_PORTD_BASE,
					 GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,
					 GPIO_STRENGTH_2MA,
					 GPIO_PIN_TYPE_STD_WPD);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7);
	GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7,
					 GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
}


/* ------------------------------------------------------------------------------------------------------
 *									CC2520_SPI_BEGIN()
 *
 * Description : asserts the CS pin to the cc2520.
 *
 * Argument(s) : none.
 *
 */
void CC2520_SPI_BEGIN(void)
{
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
}

/* ------------------------------------------------------------------------------------------------------
 *									CC2520_SPI_END()
 *
 * Description : de-asserts the CS pin to the cc2520.
 *
 * Argument(s) : none.
 *
 */
void CC2520_SPI_END(void)
{
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
}

/* ------------------------------------------------------------------------------------------------------
 *									CC2520_SPI_TXRX()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
unsigned char CC2520_SPI_TXRX(unsigned char adr)
{
	unsigned long dat;
	
	SSIDataPut(SSI0_BASE, adr);
	SSIDataGet(SSI0_BASE, &dat);
	
	return (unsigned char) dat;
}

/* ------------------------------------------------------------------------------------------------------
 *									CC2520_SPI_TXRX()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void CC2520_SPI_TX(unsigned char dat)
{
	unsigned long uNull;
	
	SSIDataPut(SSI0_BASE, dat);
	SSIDataGet(SSI0_BASE, &uNull);
}

/* ------------------------------------------------------------------------------------------------------
 *									CC2520_SPI_RX()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
unsigned char CC2520_SPI_RX(void)
{
	unsigned long dat;
	
	SSIDataPut(SSI0_BASE, 0xFF);
	SSIDataGet(SSI0_BASE, &dat);
	
	return (unsigned char) dat;
}

/* ------------------------------------------------------------------------------------------------------
 *									CC2520_RESET_OPIN()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void CC2520_RESET_OPIN(unsigned char x)
{
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6 & (x * 0xFF));
}

/* ------------------------------------------------------------------------------------------------------
 *									CC2520_RESET_OPIN()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void CC2520_VREG_EN_OPIN(unsigned char x)
{
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7 & (x * 0xFF));
}

/* ------------------------------------------------------------------------------------------------------
 *									CC2520_RESET_OPIN()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void CC2520_CSN_OPIN(unsigned char x)
{
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6 & (x * 0xFF));
}

/* ------------------------------------------------------------------------------------------------------
 *									halMcuWaitUs()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
#define TheSysClock 50000000
void halMcuWaitUs(unsigned long usec)
{
	SysCtlDelay(usec*(TheSysClock/3000000));
}

void halMcuWaitMs(unsigned long msec)
{
	SysCtlDelay(msec*(TheSysClock/3000));
}
