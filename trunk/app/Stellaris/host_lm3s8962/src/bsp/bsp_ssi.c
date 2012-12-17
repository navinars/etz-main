/* ------------------------------------------------------------------------------------------------------
 *											Local Includes
 * ------------------------------------------------------------------------------------------------------
 */
#include "bsp.h"

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/ssi.h"


// asserts the CS pin to the card
static
void SELECT(void)
{
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0);
}

// de-asserts the CS pin to the card
static
void DESELECT(void)
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	SSIDisable(SSI0_BASE);											/* Disable SSI0.*/
	
	GPIOPinTypeSSI(GPIO_PORTA_BASE, 								/* Configure the SPI port*/
				   GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5);
	GPIOPadConfigSet(GPIO_PORTA_BASE,
					 GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5,
					 GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
	
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);				/* Configure the CS port*/
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
    SELECT();
	DESELECT();														/* Deassert the SSI0 chip select */
	
	SSIConfigSetExpClk(SSI0_BASE,									/* Configure the SSI0 port */
						SysCtlClockGet(),
						SSI_FRF_MOTO_MODE_0,
						SSI_MODE_MASTER, 400000, 8);
	SSIEnable(SSI0_BASE);											/* Enable SSI0.*/
}

