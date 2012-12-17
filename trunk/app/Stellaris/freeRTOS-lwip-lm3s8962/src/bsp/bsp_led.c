#include <bsp.h>

void BSP_LedInit(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
}

void BSP_LedSet(unsigned char id)
{
	switch (id)
	{
	case 1:
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
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
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
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
		status = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
		status = status ^ 1;
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, status);
		break;
	default:
		break;
	}
}
