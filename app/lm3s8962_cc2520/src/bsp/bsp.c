/* ------------------------------------------------------------------------------------------------------
 *											Local Includes
 * ------------------------------------------------------------------------------------------------------
 */
#include <bsp.h>

/* ------------------------------------------------------------------------------------------------------
 *									BSP_Init()
 *
 * Description : MCU sysctl init function.
 *
 * Argument(s) : none.
 *
 */
void BSP_Init(void)
{
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
	
}

