/* ------------------------------------------------------------------------------------------------------
* File: main.c
*
* -------------------------------------------------------------------------------------------------------
*/
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
 
 
/* Peripheral definitions for EK-LM3S8962 board */
// SSI port
#define SDC_SSI_BASE            SSI0_BASE
#define SDC_SSI_SYSCTL_PERIPH   SYSCTL_PERIPH_SSI0

// GPIO for SSI pins
#define SDC_GPIO_PORT_BASE      GPIO_PORTA_BASE
#define SDC_GPIO_SYSCTL_PERIPH  SYSCTL_PERIPH_GPIOA
#define SDC_SSI_CLK             GPIO_PIN_2
#define SDC_SSI_TX              GPIO_PIN_5
#define SDC_SSI_RX              GPIO_PIN_4
#define SDC_SSI_FSS             GPIO_PIN_3
#define SDC_SSI_PINS            (SDC_SSI_TX | SDC_SSI_RX | SDC_SSI_CLK)

// GPIO for card chip select
#define SDC_CS_GPIO_PORT_BASE      GPIO_PORTG_BASE
#define SDC_CS_GPIO_SYSCTL_PERIPH  SYSCTL_PERIPH_GPIOG
#define SDC_CS                     GPIO_PIN_0

/* ------------------------------------------------------------------------------------------------------
 *											Local Function
 * ------------------------------------------------------------------------------------------------------
 */
void ssi_init(void);
void CC2520_SPI_ENABLE(void);
void CC2520_SPI_DISABLE(void);


/* ------------------------------------------------------------------------------------------------------
 *									main()
 *
 * Description : main function.
 *
 * Argument(s) : none.
 *
 */
int main(void)
{
	unsigned long dat;
	
	/* If running on Rev A2 silicon, turn the LDO voltage up to 2.75V.  This is
    a workaround to allow the PLL to operate reliably. */
    if( DEVICE_IS_REVA2 )
    {
		SysCtlLDOSet( SYSCTL_LDO_2_75V );
    }
	
	//
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);

	ssi_init();
	
	CC2520_SPI_DISABLE();
	CC2520_SPI_ENABLE();
	SSIDataPut(SDC_SSI_BASE, 0x10);
	SSIDataPut(SDC_SSI_BASE, 0x00);
	SSIDataPut(SDC_SSI_BASE, 0xFF);
	SSIDataGet(SDC_SSI_BASE, &dat);
	CC2520_SPI_DISABLE();
	
	if(dat == 0xff)
	{
		dat = 0;
	}
	
	for(;;)
	{
	}
}

/* ------------------------------------------------------------------------------------------------------
 *									ssi_init()
 *
 * Description : timer1 initlisation.
 *
 * Argument(s) : none.
 *
 */
void ssi_init(void)
{
    /*
     * This doesnt really turn the power on, but initializes the
     * SSI port and pins needed to talk to the card.
     */

    /* Enable the peripherals used to drive the SDC on SSI, and the CS */
    SysCtlPeripheralEnable(SDC_SSI_SYSCTL_PERIPH);
    SysCtlPeripheralEnable(SDC_GPIO_SYSCTL_PERIPH);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    /* Configure the appropriate pins to be SSI instead of GPIO */
    GPIOPinTypeSSI(SDC_GPIO_PORT_BASE, SDC_SSI_PINS);
    GPIOPadConfigSet(SDC_GPIO_PORT_BASE, SDC_SSI_PINS, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
	/* Configure the PC4*/
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_STRENGTH_4MA,
                     GPIO_PIN_TYPE_STD_WPU);
	
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
	
	/* Configure the SSI0 port */
    SSIConfigSetExpClk(SDC_SSI_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 8000000, 8);
    SSIEnable(SDC_SSI_BASE);
	
	CC2520_SPI_DISABLE();
}

void CC2520_SPI_ENABLE(void)
{
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
}

void CC2520_SPI_DISABLE(void)
{
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
}

