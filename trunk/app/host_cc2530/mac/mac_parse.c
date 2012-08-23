/********************************************************************************************************
  Filename:     mac_parse.c

  Description:  cc2530's Basic RF library

********************************************************************************************************/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *										mac_parse_hdr
 *
 * Description : Parse the mac header frame control field from the RX buffer.
 *
 */
void mac_parse_hdr(mac_buf_t *buf, mac_hdr_t *hdr)
{
	hdr->mac_fcf = *(U16*)buf->dptr;
	buf->dptr += sizeof(U16);
	
	hdr->mac_frm_ctrl.frame_type		= (hdr->mac_fcf								& 0x03);
	hdr->mac_frm_ctrl.frame_pending		= (hdr->mac_fcf >> MAC_FRM_PEND_OFF)		& 0x01;
	hdr->mac_frm_ctrl.ack_req			= (hdr->mac_fcf >> MAC_ACK_REQ_OFF)			& 0x01;
	hdr->mac_frm_ctrl.pan_id_compr		= (hdr->mac_fcf >> MAC_PAN_ID_COMPR_OFF)	& 0x01;
	hdr->dest_addr.mode					= (hdr->mac_fcf >> MAC_DEST_ADDR_MODE_OFF)	& 0x03;
	hdr->src_addr.mode					= (hdr->mac_fcf >> MAC_SRC_ADDR_MODE_OFF)	& 0x03;
	
	hdr->dsn = *buf->dptr ++;
	
	if (hdr->dest_addr.mode > 0)
	{
		hdr->dest_pan_id = *(U16*)(buf->dptr);
		buf->dptr += sizeof(U16);
		
		if(hdr->dest_addr.mode == SHORT_ADDR)
		{
			hdr->dest_addr.short_addr = *(U16*)(buf->dptr);
			buf->dptr += sizeof(U16);
		}
		else
		{
			memcpy(hdr->src_addr.long_addr, buf->dptr, sizeof(hdr->src_addr.long_addr));
			buf->dptr += sizeof(hdr->src_addr.long_addr);
		}
	}
	
	if (hdr->src_addr.mode > 0)
	{
		if (!(hdr->mac_frm_ctrl.pan_id_compr))
		{
			hdr->src_pan_id  = *(U16*)(buf->dptr);
			buf->dptr += sizeof(U16);
		}
		
		if (hdr->src_addr.mode == SHORT_ADDR)
		{
			hdr->src_addr.short_addr  = *(U16*)(buf->dptr);
			buf->dptr += sizeof(U16);
		}
		else
		{
			memcpy(hdr->src_addr.long_addr, buf->dptr, sizeof(hdr->src_addr.long_addr));
			buf->dptr += sizeof(hdr->src_addr.long_addr);
		}
	}
}

/* ------------------------------------------------------------------------------------------------------
 *										mac_parse_data
 *
 * Description : Parse the mac header frame control field from the RX buffer.
 *
 */
void mac_parse_data(mac_buf_t *buf, mac_hdr_t *hdr)
{
	
}
