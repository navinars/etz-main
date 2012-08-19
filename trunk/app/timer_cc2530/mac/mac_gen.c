/********************************************************************************************************
  Filename:     mac.c

  Description:  cc2530's Basic RF library

********************************************************************************************************/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"


/********************************************************************************************************
*                                           mac_gen_frm_ctrl()
*
* Description : Generate the mac header frame control field from the given header data.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
U16 mac_gen_frm_ctrl (const mac_hdr_t *hdr)
{
	U16 tmp = 0;
	tmp |= (U16)((hdr->src_addr.mode                     & 0x3) << MAC_SRC_ADDR_MODE_OFF);
    tmp |= (U16)((hdr->dest_addr.mode                    & 0x3) << MAC_DEST_ADDR_MODE_OFF);
    tmp |= (U16)((hdr->mac_frm_ctrl.pan_id_compr         & 0x1) << MAC_PAN_ID_COMPR_OFF);
    tmp |= (U16)((hdr->mac_frm_ctrl.ack_req              & 0x1) << MAC_ACK_REQ_OFF);
    tmp |= (U16)((hdr->mac_frm_ctrl.frame_pending        & 0x1) << MAC_FRM_PEND_OFF);
    tmp |= (U16)(hdr->mac_frm_ctrl.frame_type            & 0x3);
    return tmp;
}

/********************************************************************************************************
*                                           mac_gen_header()
*
* Description : Generate the complete MAC frame header and place it in the specified buffer. 
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void mac_gen_header(mac_buf_t *buf, mac_hdr_t *hdr)
{
	U8 hdr_size, frame_length;
	hdr->mac_fcf = mac_gen_frm_ctrl(hdr);
	
	// Calculate the size of the header
	hdr_size = 4;
	if (hdr->dest_addr.mode > 0)
	{
		hdr_size += ((hdr->dest_addr.mode == SHORT_ADDR) ? 4 : 10);
	}
	
	if (hdr->src_addr.mode > 0)
	{
		hdr_size += ((hdr->mac_frm_ctrl.pan_id_compr == true) ? 0 : 2);
		hdr_size += ((hdr->src_addr.mode == SHORT_ADDR) ? 2 : 8);
	}
	
	buf->dptr -= hdr_size;
	buf->len += hdr_size;
	frame_length = ((buf->len) - 1) + MAC_FCS_LENGTH;
	
	/* Start filling in the frame header. Write in the data, then advance the data pointer.*/
	*buf->dptr++ 		= frame_length;
	*(U16 *)buf->dptr 	= hdr->mac_fcf;
	buf->dptr 		   += sizeof(U16);
	*buf->dptr++ 		= hdr->dsn;
	
	if (hdr->dest_addr.mode > 0)
	{
		*(U16*)buf->dptr = hdr->dest_pan_id;
		buf->dptr += sizeof(U16);
		
		if (hdr->dest_addr.mode  == SHORT_ADDR)
		{
			*(U16*)buf->dptr = hdr->dest_addr.short_addr;
			buf->dptr += sizeof(U16);
		}
		else
		{
			memcpy(buf->dptr, hdr->dest_addr.long_addr, sizeof(hdr->dest_addr.long_addr));
			buf->dptr += sizeof(hdr->dest_addr.long_addr);
		}
	}
	
	if (hdr->src_addr.mode > 0)
	{
		if (!hdr->mac_frm_ctrl.pan_id_compr)
		{
			*(U16*)buf->dptr = hdr->src_pan_id;
			buf->dptr += sizeof(U16);
		}
		
		if (hdr->src_addr.mode == SHORT_ADDR)
		{
			*(U16*)buf->dptr = hdr->src_addr.short_addr;
			buf->dptr += sizeof(U16);
		}
		else
		{
			memcpy(buf->dptr, hdr->src_addr.long_addr, sizeof(hdr->src_addr.long_addr));
			buf->dptr += sizeof(hdr->dest_addr.long_addr);
		}
	}
	
	buf->dptr -= hdr_size;
}

/********************************************************************************************************
*                                         mac_gen_cmd_header()
*
* Description : Generate the complete MAC frame header and place it in the specified buffer. 
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void mac_gen_cmd_header(mac_buf_t *buf, mac_hdr_t *hdr, bool ack_req, address_t *src_addr, address_t *dest_addr)
{
	mac_pib_t *pib = mac_pib_get();
	mac_pcb_t *pcb = mac_pcb_get();

	memset(hdr, 0, sizeof(mac_hdr_t));
    hdr->mac_frm_ctrl.frame_type        = MAC_COMMAND;
    hdr->mac_frm_ctrl.ack_req           = ack_req;
	hdr->mac_frm_ctrl.pan_id_compr		= true;
    hdr->mac_frm_ctrl.frame_ver         = MAC_802_15_4_2006;
    hdr->dsn                            = pib->dsn++;
	
    hdr->src_pan_id  = hdr->dest_pan_id = pib->pan_id;
	
	if(pcb->mac_state == MLME_ASSOC_REQ)
	{
		hdr->mac_frm_ctrl.pan_id_compr	= false;
		hdr->dest_pan_id = pib->tmp_pan_id;
	    hdr->src_pan_id  = pib->pan_id;
	}

    memcpy(&hdr->src_addr, src_addr, sizeof(address_t));
    memcpy(&hdr->dest_addr, dest_addr, sizeof(address_t));

    mac_gen_header(buf, hdr);
}

/********************************************************************************************************
*                                         mac_gen_cmd_header()
*
* Description : Generate the complete MAC frame header and place it in the specified buffer. 
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void mac_gen_ack(mac_buf_t *buf, bool frm_pend, U8 dsn)
{
	U8 hdr_size = 4,
	   frame_len = 5;
	
	U16 fcf = (frm_pend) ? 0x0012 : 0x0002;
	
	buf->len += hdr_size;
	buf->dptr -= hdr_size;
	
	*buf->dptr = frame_len;
	*(U16 *)(buf->dptr+1) = fcf;
	*(buf->dptr + 3) = dsn;
}

/********************************************************************************************************
*                                         mac_gen_cmd()
*
* Description : Generate the complete MAC frame header and place it in the specified buffer. 
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void mac_gen_cmd(mac_buf_t *buf, mac_cmd_t *cmd)
{
	switch (cmd->cmd_id)
	{
	case MAC_DATA_REQ:
	case MAC_BEACON_REQ:
	case MAC_ORPHAN_NOT:
		buf->len++;
		buf->dptr--;
		*buf->dptr = cmd->cmd_id;
		break;
		
	case MAC_ASSOC_REQ:
		buf->len 				+= MAC_ASSOC_REQ_LEN;
		buf->dptr 				-= MAC_ASSOC_REQ_LEN;
		*buf->dptr++ 			 = cmd->cmd_id;
		*buf->dptr++ 			 = cmd->assoc_req.cap_info;
		buf->dptr 				-= MAC_ASSOC_REQ_LEN;
		break;
		
	case MAC_ASSOC_RESP:
		buf->len 				+= MAC_ASSOC_RESP_LEN;
		buf->dptr 				-= MAC_ASSOC_RESP_LEN;
		*buf->dptr++ 			 = cmd->cmd_id;
		*(U16*)buf->dptr 	 	 = cmd->assoc_resp.short_addr;
		buf->dptr 				+= sizeof(U16);
		*buf->dptr ++;
		buf->dptr 				-= MAC_ASSOC_RESP_LEN;
		break;
		
	case MAC_COORD_REALIGN:
		buf->len 				+= MAC_COORD_REALIGN_LEN;
		buf->dptr 				-= MAC_COORD_REALIGN_LEN;
		*buf->dptr++			 = cmd->cmd_id;
		*(U16*)buf->dptr		 = cmd->coord_realign.pan_id;
		buf->dptr 				+= sizeof(U16);
		*(U16*)buf->dptr		 = cmd->coord_realign.coord_short_addr;
		buf->dptr 				+= sizeof(U16);
		*buf->dptr++			 = cmd->coord_realign.channel;
		*(U16*)buf->dptr 	 	 = cmd->coord_realign.short_addr;
		buf->dptr 				+= sizeof(U16);
		buf->dptr 				-= MAC_COORD_REALIGN_LEN;
		break;
		
	default:
		break;
	}
}

/********************************************************************************************************
*                                       mac_gen_superfrm_spec()
*
* Description : Generate the complete MAC frame header and place it in the specified buffer. 
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
U16 mac_gen_superfrm_spec(void)
{
	mac_pib_t *pib = mac_pib_get();
	U16 superfrm_spec = 0;
	
	superfrm_spec |= (pib->assoc_permit & 0x01) << MAC_ASSOC_PERMIT_OFF;
	superfrm_spec |= (pib->coord & 0x01) 		<< MAC_COORDINATOR_OFF;
	superfrm_spec |= MAC_FINAL_CAP_SLOT | MAC_SUPERFRAME_ORDER | MAC_BEACON_ORDER;
	
	return superfrm_spec;
}

/********************************************************************************************************
*                                         mac_gen_beacon()
*
* Description : Generate the complete MAC frame header and place it in the specified buffer. 
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
static void mac_gen_beacon (mac_buf_t *buf)
{
	/* Depend on NWK layer's data*/
//	nwk_gen_beacon(buf);
	
	buf->len					+= MAC_BEACON_PAYLOAD_SIZE;
	buf->dptr					-= MAC_BEACON_PAYLOAD_SIZE;
	*(U16 *)buf->dptr			 = mac_gen_superfrm_spec();
	buf->dptr					+= sizeof(U16);
	*buf->dptr++				 = 0;
	*buf->dptr++				 = 0;
	buf->dptr					-= MAC_BEACON_PAYLOAD_SIZE;
}

/********************************************************************************************************
*                                         mac_gen_beacon_frm()
*
* Description : Generate the full beacon frame and send it out. 
*
* Argument(s) : *buf		pointer to data struct.
*				*hdr		pointer to mac_hdr_t.
*
* Return(s)   : none.
*
* Caller(s)   : mac_cmd_handle().
*
* Note(s)     : none.
*/
void mac_gen_beacon_frm(mac_buf_t *buf, mac_hdr_t *hdr)
{
	mac_pib_t *pib = mac_pib_get();
	
	hdr->mac_frm_ctrl.frame_type	= MAC_BEACON;
	hdr->mac_frm_ctrl.ack_req		= false;
	hdr->mac_frm_ctrl.frame_pending = false;
	hdr->mac_frm_ctrl.frame_ver		= MAC_802_15_4_2006;
	hdr->mac_frm_ctrl.pan_id_compr	= false;
	hdr->src_pan_id					= pib->pan_id;
	hdr->dest_pan_id				= pib->pan_id;
	hdr->src_addr.mode				= SHORT_ADDR;
	hdr->src_addr.short_addr		= pib->short_addr;
	hdr->dest_addr.mode				= NO_PAN_ID_ADDR;
	hdr->dsn						= pib->dsn++;
	
	mac_gen_beacon(buf);
	mac_gen_header(buf, hdr);
}
