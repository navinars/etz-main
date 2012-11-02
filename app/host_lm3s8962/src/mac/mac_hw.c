/* ------------------------------------------------------------------------------------------------------
 * File: mac_hw.c
 * Data: 2012/10/20
 * Author: MC
 * Ver: V0.1.1b
 * -------------------------------------------------------------------------------------------------------
 */
#include "string.h"

#include "hal_rf.h"
#include "mac.h"

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

/* ------------------------------------------------------------------------------------------------------
 *										  		send
 *
 * Describtion : none.
 *
 */
int cc2520_send(mac_buf_t *buf)
{
	halRfDisableRxInterrupt();
	
	halRfWriteTxBuf(buf->dptr, buf->len);
	
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
	status = cc2520_send(txbuf);
	reset_tx_buf();
	// send the frame to the tx handler for processing
	return status;
}

/* ------------------------------------------------------------------------------------------------------
 *												RfRxFrmDoneIsr()
 *
 * Description : RF interrupt function.
 *
 */
void RfRxFrmDoneIsr(void)
{
	unsigned long ulStatus;
	unsigned char len;
	mac_buf_t *rxbuf = read_rx_buf();
	
	halRfDisableRxInterrupt();										/* Disable RX radio interrupter.*/
	
	memset(rxbuf, 0, sizeof(mac_buf_t));
	rxbuf->dptr = rxbuf->buf;
	rxbuf->alloc = true;
	
	ulStatus = GPIOPinIntStatus(GPIO_PORTD_BASE, true);
	if(ulStatus & GPIO_PIN_1)
	{
		halRfReadRxBuf(&len, 1);
		rxbuf->len = len;
		halRfReadRxBuf(rxbuf->dptr, len);

		rxbuf->alloc = true;
		
		GPIOPinIntClear(GPIO_PORTD_BASE, ulStatus);
	}
	
	GPIOPinIntClear(GPIO_PORTD_BASE, ulStatus);
	
	halRfEnableRxInterrupt();										/* Enable RX frame done interrupt again.*/
}
