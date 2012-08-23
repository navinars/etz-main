/* ------------------------------------------------------------------------------------------------------
* File: mac.c
*
* -------------------------------------------------------------------------------------------------------
*/
#include "includes.h"


static 	mac_pib_t 	pib;
static  mac_pcb_t	pcb;




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
	pib.coord_addr.short_addr	= 0x0000;		// Net coord short address is 0x0000;
	pib.coord					= false;
	pib.short_addr				= 0x0000;		// Default node short address is 0xFFFF.
	pib.pan_id					= 0xFFFF;		// Default PAN ID is 0xFFFF.
	
	// Read MAC address in FALSH.
	HalFlashRead(HAL_FLASH_IEEE_PAGE, HAL_FLASH_IEEE_OSET, pib.ext_addr, Z_EXTADDR_LEN);
	pib.assoc_permit			= false;		// Node's association is permit.
	pcb.mac_state				= MLME_SCAN;

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
	
	mac_buf_init();
	
	halRfReceiveOn();
}

/********************************************************************************************************
*                                           *mac_pib_get()
*
* Description : get pib struct pionter.
*
* Argument(s) : none.
*
*/
mac_pib_t *mac_pib_get(void)
{
	return &pib;
}

/********************************************************************************************************
*                                           *mac_pcb_get()
*
* Description : get pib struct pionter.
*
* Argument(s) : none.
*
*/
mac_pcb_t *mac_pcb_get(void)
{
	return &pcb;
}

/* ------------------------------------------------------------------------------------------------------
 *										mac_handle
 *
 * Describtion : RF event handle.
 *
 */
void mac_event_handle(void)
{
	mac_buf_t *rxbuf = read_rx_buf();
	if(rxbuf->alloc == true)
	{
		mac_hdr_t hdr;
		mac_parse_hdr(rxbuf, &hdr);
		
		switch(hdr.mac_frm_ctrl.frame_type)
		{
		case MAC_BEACON:
			if(strstr((const char *)rxbuf->dptr, "dooya") != NULL)
			{
				mac_parse_data(rxbuf, &hdr);
//				halLedToggle(2);
			}
			break;
			
		case MAC_DATA:
			break;
			
		case MAC_ACK:
			break;
			
		case MAC_COMMAND:
			break;
			
		default:
			break;
		}
		reset_rx_buf();
	}
}

/* ------------------------------------------------------------------------------------------------------
 *										data_updata
 *
 * Describtion : RF tx function.
 *
 */
void mac_host_beacon(void)
{
	U8 data[20], len, option;
	address_t destAddr;

	memcpy(data, "dooya", 6);
	len = sizeof(data);
	
	destAddr.mode = SHORT_ADDR;
	destAddr.short_addr = 0xFFFF;
	
	option = MAC_BEACON;
	mac_tx_handle(&destAddr, data, len, option);
}

