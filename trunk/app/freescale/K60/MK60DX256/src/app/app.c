/* 
 * Include common utilities
 */
#include "MK60DZ10.h"
#include "wdog.h"
#include "sysinit.h"


/********************************************************************/

int main (void)
{
	/* Disable the watchdog timer */
	wdog_disable();

// 	/* Copy any vector or data sections that need to be in RAM */
// 	common_startup();

	/* Perform processor initialization */
	sysinit();
		
// 	/* Determine the flash revision */
// 	flash_identify(); 
//	SystemInit();
	
	
	for(;;)
	{
	}
}
