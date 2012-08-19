/* ------------------------------------------------------------------------------------------------------
* File: mac.c
*
* -------------------------------------------------------------------------------------------------------
*/
#include "includes.h"


static 	mac_pib_t 	pib;
static  mac_pcb_t	pcb;


static void RfRxFrmDoneIsr(void);


/* ------------------------------------------------------------------------------------------------------
 *												mac_init()
 *
 * Description : MAC layer init.
 *
 */
void mac_init(void)
{
	pib.coord_addr.mode			= SHORT_ADDR;
	pib.coord_addr.short_addr	= 0x0000;		// Net coord short address is 0x0000;
	pib.coord					= false;
	pib.short_addr				= 0xFFFF;		// Default node short address is 0xFFFF.
	pib.pan_id					= 0xFFFF;		// Default PAN ID is 0xFFFF.
	
	// Read MAC address in FALSH.
	HalFlashRead(HAL_FLASH_IEEE_PAGE, HAL_FLASH_IEEE_OSET, pib.ext_addr, Z_EXTADDR_LEN);
	pib.assoc_permit			= false;		// Node's association is permit.
	pcb.mac_state				= MLME_SCAN;

	pib.curr_channel			= 21;
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
	
	/* Initialise RF radio.*/
	halRfInit();
	
	halRfReceiveOn();
	
	halRfEnableRxInterrupt();
	
	halRfRxInterruptConfig(RfRxFrmDoneIsr);
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
 *										  mac_out
 *
 * Describtion : none.
 *
 */
void mac_out(mac_buf_t *buf)
{
	halRfDisableRxInterrupt();
	
	halRfWriteTxBuf(buf->dptr, buf->len);
	
	halRfEnableRxInterrupt();
	
	halRfTransmit();
}

/* ------------------------------------------------------------------------------------------------------
 *										mac_tx_handle
 *
 * Describtion : RF tx function.
 *
 */
void mac_tx_handle(address_t *dest_addr, U8 *pdata, U8 len, bool ack_req, bool dsn)
{
	
	mac_hdr_t hdr;
	mac_buf_t buf;
	
	memset(&hdr, 0, sizeof(mac_hdr_t));
	hdr.mac_frm_ctrl.frame_type		= MAC_DATA;
	hdr.mac_frm_ctrl.ack_req		= ack_req;
	hdr.mac_frm_ctrl.frame_ver		= MAC_802_15_4_2006;
	hdr.dsn							= dsn;
	hdr.dest_pan_id					= pib.pan_id;
	hdr.src_pan_id					= 0xFFFF;
	hdr.mac_frm_ctrl.pan_id_compr	= true;						// Put off source PAN ID.
	memcpy(&hdr.src_addr, &pib.ext_addr, sizeof(address_t));
    memcpy(&hdr.dest_addr, dest_addr, sizeof(address_t));
	
	// generate the header
	mac_gen_header(&buf, &hdr);
	
	// send the frame to the tx handler for processing
	mac_out(&buf);
}

/* ------------------------------------------------------------------------------------------------------
 *										mac_tx_handle
 *
 * Describtion : RF tx function.
 *
 */
void data_updata(void)
{
	U8 data[3], len;
	address_t destAddr;

	memcpy(data, "ok", 3);
	len = sizeof(data);
	
	destAddr.mode = SHORT_ADDR;
	destAddr.short_addr = 0x0000;
	
	mac_tx_handle(&destAddr, data, len, true, pib.dsn);
}

/* ------------------------------------------------------------------------------------------------------
 *										RfRxFrmDoneIsr
 *
 * Describtion : none.
 *
 */
static void RfRxFrmDoneIsr(void)
{
	// Clear interrupt and disable new RX frame done interrupt
	halRfDisableRxInterrupt();
	
//	halRfReadRxBuf(&len, 1);
//	halRfReadRxBuf(buf, len);
	
	// Enable RX frame done interrupt again
	halRfEnableRxInterrupt();
}
