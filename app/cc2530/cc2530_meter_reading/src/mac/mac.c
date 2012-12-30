/* ------------------------------------------------------------------------------------------------------
* File: mac.c
*
* -------------------------------------------------------------------------------------------------------
*/
#include "includes.h"


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
	
#if (0)
	pib.coord_addr.mode			= SHORT_ADDR;
	pib.coord_addr.short_addr	= 0x0000;		// Net coord short address is 0x0000;
	pib.coord					= true;
	pib.short_addr				= 0x0000;		// Default node short address is 0xFFFF.
	pib.pan_id					= 0xFFFF;		// Default PAN ID is 0xFFFF.
	
	// Read MAC address in FALSH.
	HalFlashRead(HAL_FLASH_IEEE_PAGE, HAL_FLASH_IEEE_OSET, pib.ext_addr, Z_EXTADDR_LEN);
	pib.assoc_permit			= false;		// Node's association is permit.
//	pcb.mac_state				= MLME_SCAN;

	pib.curr_channel			= 20;								/* channel 20.*/
	pib.rx_on_when_idle			= true;
	pib.max_csma_backoffs		= 3;
	pib.min_be					= 3;
	pib.dsn						= (U8)halRfGetChipId(); // Random value as frame number.
	pib.tmp_pan_id				= 0xFFFF;
	
    /* Write the short address and the PAN ID to the CC2520 RAM*/
	halRfSetExtAddr(pib.ext_addr);
	halRfSetShortAddr(pib.short_addr);
	halRfSetPanId(pib.pan_id);
#endif
	pib.curr_channel			= 20;								/* channel 20.*/
	
	// Set channel
	halRfSetChannel(pib.curr_channel);
	
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
//	return &pcb;
	return NULL;
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
	
	/* RX buffer has data.*/
	if(rxbuf->alloc == true)
	{
		/* Random wake mode.*/
		if ((rxbuf->len == 2) && (sys_mode == SYS_MODE_RAND_WAKE))
		{
			mac_syn_t syn;
			
			syn.msgType 		= BROADCAST_SYN;					/* Broadcast message type.*/
			syn.routeCnt 		= (*rxbuf->dptr)&0x0F + 1;			/* Route count.*/
			
			syn.offset 			= halRfGetRandomByte();				/* Time offset number.*/
			
			// DOTO: Rande delay(using Sleep Timer), send syn time frame.
			mac_gen_syn_frm(&syn);									/* Generate time syn frame.*/
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
void mac_host_bcn(U16 offset)
{
	U8 data[20], len, option;
	address_t destAddr;

	memcpy(data, "dooya", 6);
	
	*(U32 *)(&data[6]) = TICK_VAL - offset;
	
	len = 6 + 4;
	
	destAddr.mode = SHORT_ADDR;
	destAddr.short_addr = 0xFFFF;
	
	option = MAC_BEACON;
	mac_tx_handle(&destAddr, data, len, option);
}

