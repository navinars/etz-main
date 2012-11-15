/***********************************************************************************

  Filename:     mac.c

  Description:  This file implements the CC2520 Radio HAL.

***********************************************************************************/

#include <stdio.h>
#include <string.h>

#include "hal_rf.h"

#include "mac.h"
#include "mac_hw.h"
#include "ucos_ii.h"

#include "bsp.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
static 	mac_pib_t 	pib;
static  mac_pcb_t	pcb;
extern 	OS_EVENT	*CC2520_RxMbox;
extern 	OS_EVENT	*NET_RfMbox;


/* ------------------------------------------------------------------------------------------------------
 *												mac_init()
 *
 * Description : MAC layer init.
 *
 */
void mac_init(void)
{
	
	halRfInit();													/* Initialise RF radio.*/
	
	pib.coord_addr.mode			= SHORT_ADDR;
	pib.coord_addr.short_addr	= 0x0000;		// Net coord short address is 0x0000;
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
	halRfSetExtAddr(pib.ext_addr);									/* Write ext Address.*/
	halRfSetShortAddr(pib.short_addr);
	halRfSetPanId(pib.pan_id);
	
	halRfRxInterruptConfig(RfRxFrmDoneIsr);							/* Set Radio RX ISR function.*/
	
	mac_buf_init();
	
	halRfReceiveOn();												/* Enable RF reveive.*/
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
 *										mac_host_bcn
 *
 * Describtion : beacon frame send.
 *
 */
#define TICK_VAL	500000
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

/* ------------------------------------------------------------------------------------------------------
 *										mac_event_handle
 *
 * Describtion : RF event handle.
 *
 */
void mac_event_handle(void)
{
	INT8U *msg;
	INT8U err;
	
	//
	// Radio Rx mbox receiving handle, no blocking.
	//
	msg = (INT8U *)OSMboxPend(CC2520_RxMbox, 0, &err);
	
	if((*msg == true) && (err == OS_ERR_NONE))
	{
		mac_hdr_t hdr;
		mac_buf_t *rxbuf;
		rxbuf = read_rx_buf();
		
		mac_parse_hdr(rxbuf, &hdr);									/* Hdr layer frame parse.*/
		
		switch(hdr.mac_frm_ctrl.frame_type)
		{
		case MAC_BEACON:
//			if( pib.coord != true)									// Host can't receive beacon frame.
			{
				if(strstr((const char *)rxbuf->dptr, "dooya") != NULL)
				{
//					rxbuf->dptr += 6;
//					mac_parse_bcn(rxbuf, &hdr);
					OSMboxPost(NET_RfMbox, (void *)rxbuf->dptr);	/* Socket send Zigbee data.*/
					BSP_LedToggle(1);
				}
			}
			break;
			
		case MAC_DATA:
//			mac_parse_dat();
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

