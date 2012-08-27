/*******************************************************************************
 Name        : Commdrv.c
 Author      : Writed by songzi&jingjing in 2011.09.07
 Version     : 1.0
 Description : led low-level driver
*******************************************************************************/
#include "includes.h"


/*
*********************************************************************************************************
*                                           LOCAL DEFINES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/



/********************************************************************************************************
*                                          BSP_Led_Init()
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
void BSP_Led_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
}


/********************************************************************************************************
*                                          BSP_Led_On()
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
void BSP_Led_On(void)
{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 1);
}

/********************************************************************************************************
*                                          BSP_Led_Off()
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
void BSP_Led_Off(void)
{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
}

