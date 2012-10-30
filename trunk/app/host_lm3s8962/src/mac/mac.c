/* ------------------------------------------------------------------------------------------------------
* File: mac.c
*
* -------------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <string.h>

#include "hal_rf.h"

#include "mac.h"
#include "mac_hw.h"


static 	mac_pib_t 	pib;
//static  mac_pcb_t	pcb;




/* ------------------------------------------------------------------------------------------------------
 *												mac_init()
 *
 * Description : MAC layer init.
 *
 */
void mac_init(void)
{
	
	/* Initialise RF radio.*/
	halRfInit();
	
	pib.coord_addr.mode			= SHORT_ADDR;
//	pib.coord_addr.short_addr	= 0x0000;		// Net coord short address is 0x0000;
	pib.coord					= true;
	pib.short_addr				= 0x0000;		// Default node short address is 0xFFFF.
	pib.pan_id					= 0xFFFF;		// Default PAN ID is 0xFFFF.
	
	// Read MAC address in FALSH.
//	HalFlashRead(HAL_FLASH_IEEE_PAGE, HAL_FLASH_IEEE_OSET, pib.ext_addr, Z_EXTADDR_LEN);
	pib.assoc_permit			= false;		// Node's association is permit.
//	pcb.mac_state				= MLME_SCAN;

	pib.curr_channel			= 20;
	pib.rx_on_when_idle			= true;
	pib.max_csma_backoffs		= 3;
	pib.min_be					= 3;
	pib.dsn						= (U8)halRfGetChipId(); // Random value as frame number.
	pib.tmp_pan_id				= 0xFFFF;
	
	// Set channel
	halRfSetChannel(pib.curr_channel);
	
    /* Write the short address and the PAN ID to the CC2520 RAM*/
	halRfSetExtAddr(pib.ext_addr);
	halRfSetShortAddr(pib.short_addr);
	halRfSetPanId(pib.pan_id);
	
	halRfRxInterruptConfig(RfRxFrmDoneIsr);
	
//	mac_buf_init();
	
	halRfReceiveOff();
}

void RfRxFrmDoneIsr(void)
{
	halRfReceiveOn();
}
