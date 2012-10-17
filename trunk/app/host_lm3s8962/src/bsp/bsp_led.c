/* ------------------------------------------------------------------------------------------------------
 *											Local Includes
 * ------------------------------------------------------------------------------------------------------
 */
#include <bsp.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define SYSCTL_PERIPH_LED	SYSCTL_PERIPH_GPIOD
#define GPIO_BASE_LED		GPIO_PORTD_BASE
#define GPIO_PIN_LED1		GPIO_PIN_6
#define GPIO_PIN_LED2		GPIO_PIN_7
#define GPIO_PIN_LED_PINS	(GPIO_PIN_LED1 | GPIO_PIN_LED2)

void BSP_LedInit(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_LED);
	
	GPIOPinTypeGPIOOutput(GPIO_BASE_LED, GPIO_PIN_LED_PINS);
    GPIOPadConfigSet(GPIO_BASE_LED, GPIO_PIN_LED_PINS, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
//	GPIOPinWrite(GPIO_BASE_LED, GPIO_PIN_LED1, GPIO_PIN_LED1);
//	GPIOPinWrite(GPIO_BASE_LED, GPIO_PIN_LED2, GPIO_PIN_LED2);
}

void BSP_LedSet(unsigned char id)
{
	switch (id)
	{
	case 1:
		GPIOPinWrite(GPIO_BASE_LED, GPIO_PIN_LED1, GPIO_PIN_LED1);
		break;
	case 2:
		GPIOPinWrite(GPIO_BASE_LED, GPIO_PIN_LED2, GPIO_PIN_LED2);
		break;
	default:
		break;
	}
}

void BSP_LedClear(unsigned char id)
{
	switch (id)
	{
	case 1:
		GPIOPinWrite(GPIO_BASE_LED, GPIO_PIN_LED1, 0);
		break;
	case 2:
		GPIOPinWrite(GPIO_BASE_LED, GPIO_PIN_LED2, 0);
		break;
	default:
		break;
	}
}

void BSP_LedToggle(unsigned char id)
{
	unsigned char status;
	switch (id)
	{
	case 1:
		status = GPIOPinRead(GPIO_BASE_LED, GPIO_PIN_LED1);
		status = status ^ GPIO_PIN_LED1;
		GPIOPinWrite(GPIO_BASE_LED, GPIO_PIN_LED1, status);
		break;
	case 2:
		status = GPIOPinRead(GPIO_BASE_LED, GPIO_PIN_LED2);
		status = status ^ GPIO_PIN_LED2;
		GPIOPinWrite(GPIO_BASE_LED, GPIO_PIN_LED2, status);
		break;
	default:
		break;
	}
}
