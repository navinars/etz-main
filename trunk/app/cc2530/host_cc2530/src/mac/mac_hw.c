/********************************************************************************************************
  Filename:     mac_hw.c

  Description:  cc2530's Basic RF library

********************************************************************************************************/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *										  		send
 *
 * Describtion : none.
 *
 */
int send(unsigned char *buf, unsigned char len)
{
	halRfDisableRxInterrupt();
	
	halRfWriteTxBuf(buf, len);
	
	halRfEnableRxInterrupt();
	
	return halRfTransmit();
}

/* ------------------------------------------------------------------------------------------------------
 *										mac_tx_handle
 *
 * Describtion : RF tx function.
 *
 */
int mac_tx_handle(address_t *dest_addr, U8 *pdata, U8 len, U8 option)
{
	int status;
	mac_hdr_t hdr;
	mac_buf_t *txbuf = read_tx_buf();
	mac_pib_t *pib = mac_pib_get();
	
	memset(&hdr, 0, sizeof(mac_hdr_t));
	
	txbuf->len 		+= len;
	txbuf->dptr 	-= len;
	memcpy(txbuf->dptr, pdata, len);
	
	if ((dest_addr->short_addr == 0xFFFF) && (dest_addr->mode == SHORT_ADDR))
		hdr.mac_frm_ctrl.ack_req	= false;
	else
		hdr.mac_frm_ctrl.ack_req	= true;
	
	hdr.mac_frm_ctrl.frame_ver		= MAC_802_15_4_2006;
	hdr.dsn							= pib->dsn;
	hdr.dest_pan_id					= pib->pan_id;
	hdr.src_pan_id					= 0xFFFF;
	hdr.mac_frm_ctrl.pan_id_compr	= true;		// Put off source PAN ID.
	
	hdr.src_addr.mode 				= LONG_ADDR;
	memcpy(&hdr.src_addr.long_addr, pib->ext_addr, 8);
    memcpy(&hdr.dest_addr, dest_addr, sizeof(address_t));

	switch(option)
	{
	case MAC_DATA:
		hdr.mac_frm_ctrl.frame_type	= MAC_DATA;
		// generate the header
		mac_gen_header(txbuf, &hdr);
		break;
	case MAC_BEACON:
		mac_gen_beacon_frm(txbuf, &hdr);
		break;
	case MAC_ACK:
		break;
	default:
		return FAILED;
	}
	status = send(txbuf->dptr, txbuf->len);
	reset_tx_buf();
	// send the frame to the tx handler for processing
	return status;
}


/* ------------------------------------------------------------------------------------------------------
 *										RfRxFrmDoneIsr
 *
 * Describtion : none.
 *
 */
void RfRxFrmDoneIsr(void)
{
	U8 len;
	mac_buf_t *rxbuf = read_rx_buf();
	
	// Clear interrupt and disable new RX frame done interrupt
	halRfDisableRxInterrupt();
	
	rxbuf->alloc = true;
	
	memset(rxbuf, 0, sizeof(mac_buf_t));
	rxbuf->dptr = rxbuf->buf;
	
	halRfReadRxBuf(&len, 1);
	rxbuf->len = len;
	halRfReadRxBuf(rxbuf->dptr, len);
	
	rxbuf->alloc = true;
	
	
	halRfReceiveOn();    											/* Making sure that the RX FIFO is empty.*/
	
	halRfEnableRxInterrupt();										/* Enable RX frame done interrupt again.*/
}

