/***********************************************************************************

  Filename:     mac.c

  Description:  This file implements the CC2520 Radio HAL.

***********************************************************************************/

#include <includes.h>


unsigned char cc2520_mac[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
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
	pib.coord_addr.short_addr	= 0x0000;							/* Net coord short address is 0x0000;*/
	pib.coord					= true;
	pib.short_addr				= 0x0000;							/* Default node short address is 0xFFFF.*/
	pib.pan_id					= 0xFFFF;							/* Default PAN ID is 0xFFFF.*/
	
	memcpy(&pib.ext_addr, cc2520_mac, 8);
	// Read MAC address in FALSH.
//	HalFlashRead(HAL_FLASH_IEEE_PAGE, HAL_FLASH_IEEE_OSET, pib.ext_addr, Z_EXTADDR_LEN);
	pib.assoc_permit			= false;							/* Node's association is permit.*/
	
//	pcb.mac_state				= MLME_SCAN;

	pib.curr_channel			= 20;
	pib.rx_on_when_idle			= true;
	pib.max_csma_backoffs		= 3;
	pib.min_be					= 3;
	pib.dsn						= (U8)halRfGetChipId(); 			/* Random value as frame number.*/
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
			if(fd_A[0] != 0)
			{
				int ret, opt = 100;
				INT8U mac_data_buf[24];
				memcpy(mac_data_buf, "DataRsp", 7);
				mac_data_buf[7] = 0;
				mac_data_buf[8] = 15;
				memcpy(&mac_data_buf[9], hdr.src_addr.long_addr, 8);/* Write dev MAC address.*/
				memcpy(&mac_data_buf[17], rxbuf->dptr, 5);
				ret = lwip_setsockopt(fd_A[0], SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(int));
				if(ret == -1)
					break;
				ret = lwip_write(fd_A[0], mac_data_buf, 24);		/* Socket send energy data.*/
				if(ret == -1)
					break;
			}
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

