/* ------------------------------------------------------------------------------------------------------
 *											Local Includes
 * ------------------------------------------------------------------------------------------------------
 */
#include "bsp.h"

#include "cc2520_const.h"

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/ssi.h"

/* ------------------------------------------------------------------------------------------------------
 *									ssi0_Init()
 *
 * Description : asserts the CS pin to the cc2520.
 *
 * Argument(s) : none.
 *
 */
static void cc2520_SELECT(void)
{
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
}


/* ------------------------------------------------------------------------------------------------------
 *									ssi0_Init()
 *
 * Description : de-asserts the CS pin to the cc2520.
 *
 * Argument(s) : none.
 *
 */
static void cc2520_DESELECT(void)
{
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6);
}

/* ------------------------------------------------------------------------------------------------------
 *									ssi0_Init()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void BSP_SSI0_Init(void)
{
	cc2520_arch_init();
	
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	/*Configure the SPI port*/
	GPIOPinTypeSSI(GPIO_PORTA_BASE, 
				   GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTA_BASE,
					 GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_4,
					 GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
	/*Configure the CS port*/
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
	/* Deassert the SSI0 chip select */
    cc2520_DESELECT();
	
	/* Configure the SSI0 port */
	SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
					   SSI_MODE_MASTER, 400000, 8);
	SSIEnable(SSI0_BASE);
}

/* ------------------------------------------------------------------------------------------------------
 *									cc2520_strobe()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void cc2520_strobe(unsigned long data)
{
	cc2520_SELECT();
	SSIDataPut(SSI0_BASE, data);
	cc2520_DESELECT();
}

/* ------------------------------------------------------------------------------------------------------
 *									status()
 *
 * Description : SPI sysctl init cc2520_status.
 *
 * Argument(s) : none.
 *
 */
unsigned char cc2520_status(void)
{
	unsigned long data;
	
	cc2520_SELECT();
	SSIDataPut(SSI0_BASE, CC2520_INS_SNOP);
	SSIDataGet(SSI0_BASE, &data);
	cc2520_DESELECT();
	
	return (unsigned char) data;
}

/* ------------------------------------------------------------------------------------------------------
 *									getreg()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
unsigned char cc2520_getreg(unsigned short adr)
{
	unsigned long reg;
	
	cc2520_SELECT();
	SSIDataPut(SSI0_BASE, (CC2520_INS_MEMRD | ((adr>>8)&0xFF)));
	SSIDataPut(SSI0_BASE, (adr & 0xFF));
	SSIDataPut(SSI0_BASE, 0x00);
	SSIDataGet(SSI0_BASE, &reg);
	cc2520_DESELECT();
	
	return (unsigned char)reg;
}

/* ------------------------------------------------------------------------------------------------------
 *									setreg()
 *
 * Description : SPI sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void cc2520_setreg(unsigned short adr, unsigned char value)
{
	cc2520_SELECT();
	SSIDataPut(SSI0_BASE, CC2520_INS_MEMWR | ((adr>>8)&0xFF));
	SSIDataPut(SSI0_BASE, (adr & 0xFF));
	SSIDataPut(SSI0_BASE, (unsigned long)value);
	cc2520_DESELECT();
}

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
	/* Initalize ports and SPI. */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7);
	GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_6|GPIO_PIN_7,
					 GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
}
