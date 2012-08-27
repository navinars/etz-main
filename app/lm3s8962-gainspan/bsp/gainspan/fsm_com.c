/******************************************************************************
* DISCLAIMER:
* The software supplied by GainSpan Corporation is
* intended and supplied for use on GainSpan products.
* This software is owned by GainSpan Corporation and
* is protected under applicable
* copyright laws. All rights are reserved.
*
* THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS,
* IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* APPLY TO THIS SOFTWARE. GAINSPAN CORPORATION SHALL NOT
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
* CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER ARISING OUT OF THE
* USE OR APPLICATION OF THIS SOFTWARE.
******************************************************************************/

/* Copyright (C) 2011. GainSpan Corporation, All Rights Reserved */

#include "includes.h"
#include "HostApp.h"
#include "AtCmdLib.h"

UINT8  gHostAppBuffer[HOST_APP_TX_MAX_APP_BUFFER_SIZE]; /* Host Application buffer */
// externs
extern UINT8  gHostAppBuffer[];

HOST_FSM_STATUS_TYPE_E state_tokens;
HOST_FSM_ERROR_TYPE_E  error_tokens;

static UINT8 fsm_state = ST_IDLE;
static UINT8 associate_try = 0;
static UINT32 status_register = 0;
static UINT32 error_register = 0;

HOST_APP_MSG_ID_E rxMsgId = HOST_APP_MSG_ID_NONE;
UINT32 txCount = 0;
UINT8 cid = 0;

/* User define initial state transitions */
void fsm_init(void)
{
    associate_try = 0;
    status_set(0);
    error_set(0);

    state_set(ST_IDLE);	
	
/* for SPI HOST Application we start with LINK CHECK state */   
#ifdef HOST_APP_INTERFACE_SPI
    if (state_get() == ST_IDLE)
    {
    	/* do processing in IDLE state */
    	state_set(ST_LINK_CHECK);
    }
#else   // UART
     if (state_get() == ST_IDLE)
    {
    	/* do processing in IDLE state */
    	state_set(ST_LINK_CHECK);
    }
#endif

}

UINT32 status_get(void)
{
	return(status_register);
}

void status_set(UINT32 warning)
{
	status_register |= warning;
}

UINT32 error_get(void)
{
	return(error_register);
}

void error_set(UINT32 error)
{
	error_register |= error;
}

void state_set(UINT8 state)
{
	fsm_state = state;
}

UINT8 state_get(void)
{
	return(fsm_state);
}

/* 
 *  FSM States
 */

void st_idle(void)
//----------------------
{
	/* This state will run if user has not started any GS1011 processing */
	status_set(0);   // clear warnings
	error_set(0);    // clear errors
	state_set(ST_IDLE);
}

void st_link_check(void)
//----------------------
{
    /* Make sure that SPI link is UP and we are able to communicate with S2w App node */
//	AtLib_LinkCheck();

    #ifdef HOST_APP_DEBUG_ENABLE
    AtLib_Printf("\n SPI Link up \n");
    #endif
	
    /* 读取GP启动信息，不进行任何操作，死循环 */
    AtLib_ReadBootUpMessage();
    state_set(ST_INIT);
}

// common stuff, starting with disabling echo
void st_init(void)
//------------------
{
	/* 全局变量，连接尝试请求*/
    associate_try = 0;
	
    /* 取消命令字符重显示功能 */
    do
    {
        rxMsgId = AtLibGs_SetEcho(HOST_APP_DISABLE);
    }while(HOST_APP_MSG_ID_OK != rxMsgId);
	
    /* 设置MAC地址 */
/*	do
	{
		rxMsgId = AtLibGs_MACSet(HOST_APP_GS_NODE_MAC_ID);
	}while(HOST_APP_MSG_ID_OK != rxMsgId);
*/
    state_set(ST_RESET_CHECK);
}


void st_reset_check(void)
//----------------------
{
    /* Handle pending  data if any */
    AtLib_RecieveDataHandle();

    if(TRUE == AtLib_IsNodeResetDetected())
    {
        /* Node reset event received !*/
        AtLib_ClearNodeResetFlag();      /* Reset the flag */
        // status_set(WARN_GS_RESET);
	    // state_set(ST_INIT);
	    state_set(ST_CLOSE_CONN);
    }
    else
    {
        if (FALSE == AtLib_IsNodeAssociated())
        {
	        /*Currently S2w node is  dis-associated */
            state_set(ST_ASSOCIATE);
        }
	    else  // check association
	    {
            /* Get the current status of WLAN connection
             * Check whether it is already associated to one of the AP or NOT ?
	         */
            rxMsgId = AtLibGs_WlanConnStat();
            if(FALSE == AtLib_ParseWlanConnStat())
            {
		        /* Currently S2w App node is NOT associated.
                 * Start Association.
                 */	
                 state_set(ST_ASSOCIATE);
	        }
	        else
	        {
				/* S2w App node is already associated. Proceed to data connection set-up */
				state_set(ST_TCP_CONN);  // default ?
				// or
//				state_set(ST_UDP_CONN);
	        }
	    }
    }
}

void st_associate(void)
//----------------------------
{
	/* First Enable DHCP */
	do
	{
		rxMsgId = AtLibGs_DHCPSet(1);
	}while(HOST_APP_MSG_ID_OK != rxMsgId);
	
	/* First Enable AC Mode */
	do
	{
		rxMsgId = AtLibGs_Mode(0);
	}while(HOST_APP_MSG_ID_OK != rxMsgId);
	
	/* First Enable AC Mode */
/*	do
	{
		rxMsgId = AtLibGs_CalcNStorePSK("TP", "chxg23@gmail.com");
	}while(HOST_APP_MSG_ID_OK != rxMsgId);
*/
	AtLib_ClearNodeAssociationFlag();     /* reset the association flag */
	
    /* Associate to a particular AP specified by SSID "TP"  */
    rxMsgId = AtLibGs_Assoc(HOST_APP_AP_SSID, NULL, NULL);
	
    if(HOST_APP_MSG_ID_OK != rxMsgId)
    {
	    /* Association error - we can retry */
	    associate_try++;
        my_delay_ms(1000); /* Retry after 1 seconds */
		
	    if(TRUE == AtLib_IsNodeResetDetected())
	    {
            AtLib_ClearNodeResetFlag(); /* Reset the flag */
            status_set(WARN_GS_RESET_ASSOCIATE);
	        state_set(ST_INIT);
	    }
	    
        if (associate_try > 10)
        {
        	associate_try = 0;
        	status_set(WARN_GS_ASSOCIATE_MAXOUT);
	        state_set(ST_IDLE);
        }
    }
    else
    {
		/* 连接成功 */
		AtLib_SetNodeAssociationFlag();
		state_set(ST_TCP_CONN);
//		state_set(ST_UDP_CONN);
    }
}

void st_tcp_conn(void)
//--------------------------
{
    if(TRUE == AtLib_IsNodeAssociated())
    {	
        /********<TCP connection set up >********/
        /* Start TCP Client connection */
        rxMsgId = AtLibGs_TcpClientStart(HOST_APP_REMOTE_TCP_SRVR_IP,HOST_APP_REMOTE_TCP_SRVR_PORT);
   
        if(HOST_APP_MSG_ID_OK != rxMsgId)
        {
       	    /* TCP connection error */
	        #ifdef HOST_APP_DEBUG_ENABLE
	        AtLib_Printf("\n TCP Connection ERROR !\n");
            #endif
            error_set(ERR_TCP_CONNECTION);
            //fsm_state = ST_UDP_CONN; - old code
            state_set(ST_CLOSE_CONN);
        }
        else
        {
            /* Extract the CID from the response */
            cid = AtLib_ParseTcpClientCid();
            AtLib_SaveTcpCid(cid);        /* Save CID value for future reference */
            if(HOST_APP_INVALID_CID == cid )
            {
	            /* TCP connection response parsing error */
   	            #ifdef HOST_APP_DEBUG_ENABLE
	            AtLib_Printf("\nTCP connection response parsing error!\n");
	            #endif
	            error_set(ERR_INV_TCP_CID);
                // state_set(ST_UDP_CONN); - old code
                state_set(ST_CLOSE_CONN);
   	        }
	        else
	        {
                /*********<End of TCP connection set up >*********/
                for(txCount = 0; txCount < HOST_APP_TCP_TX_COUNT; txCount++)
                {
	                if(FALSE == AtLib_IsNodeAssociated())
	                {
		                /* Node is dis-associated ,  So abort the transmission*/
		                #ifdef HOST_APP_DEBUG_ENABLE
		                AtLib_Printf("\nNode is dis-associated ,  So abort the transmission\n");
		                #endif
		                error_set(ERR_TCP_XFER);
	                    state_set(ST_CLOSE_CONN);
		            }
		            else
		            {
	                    /* Get the current TCP  client CID */
	                    cid = AtLib_GetTcpCid();
	                    /* Get application data to send 
                         * For demo we are sending few dummy bytes 
	                     */
	                    hostApp_GetApplicationData((INT8 *)gHostAppBuffer,HOST_APP_TCP_PACKET_SIZE,HOST_APP_TX_DATA_TYPE_TCP);
	                    #ifdef HOST_APP_TCP_BULK_DATA_TRANSFER
		                /* Bulk transfer mode */
		                AtLib_BulkDataTransfer(cid, gHostAppBuffer,HOST_APP_TCP_PACKET_SIZE);
	                    #else		
		                /* Send data to remote TCP server */
		                AtLib_SendTcpData(cid,gHostAppBuffer,HOST_APP_TCP_PACKET_SIZE);
	                    #endif
	                    state_set(ST_RESET_CHECK);
		            }   
	            }   
	        }
        }
    }	
}

void st_udp_conn(void)
//--------------------------
{
    do
    {/* Check AT command state - just defensive check */
        rxMsgId =  AtLibGs_Check();
  
    }while(HOST_APP_MSG_ID_OK != rxMsgId);

    if(TRUE == AtLib_IsNodeAssociated())
    {	
        /***********<UDP connection set up >*************/ 
        /* Start UDP Client connection */
        rxMsgId = AtLibGs_UdpClientStart(HOST_APP_REMOTE_UDP_SRVR_IP,
										 HOST_APP_REMOTE_UDP_SRVR_PORT,
										 HOST_APP_NODE_LOCAL_UDP_PORT);
   
        if(HOST_APP_MSG_ID_OK != rxMsgId)
        {
            /* UDP connection error */
            #ifdef HOST_APP_DEBUG_ENABLE
	        AtLib_Printf("\n UDP Connection ERROR !\n");
            #endif
            error_set(ERR_UDP_XFER);
	        state_set(ST_CLOSE_CONN);
        }
        else
        {
            /* Extract the CID from the response */
            cid = AtLib_ParseUdpClientCid();
            AtLib_SaveUdpCid(cid);    /* Save CID value for future reference */
            if(HOST_APP_INVALID_CID == cid )
            {
                /* UDP connection response parsing error */
   	            #ifdef HOST_APP_DEBUG_ENABLE
                AtLib_Printf("\nUDP connection response parsing error!\n");
	            #endif
	            error_set(ERR_INV_UDP_CID);
	            state_set(ST_CLOSE_CONN);
   	        }
	        else
	        /************<End of UDP connection set up >*************/
	        {
                for (txCount = 0; txCount < HOST_APP_UDP_TX_COUNT; txCount++)
                {   
	                if(FALSE == AtLib_IsNodeAssociated())
	                {
	                    /* Node is dis-associated ,  So abort the transmission*/
	                    #ifdef HOST_APP_DEBUG_ENABLE
	                    AtLib_Printf("\nNode is dis-associated ,  So abort the transmission\n");
	                    #endif
	                    error_set(ERR_UDP_XFER);
	                    state_set(ST_CLOSE_CONN);
		                break;
	                }
	                else
	                {   
	                    /* Get the current UDP  client CID */
	                    cid = AtLib_GetUdpCid();
	                    /* Get application data to send 
                         *  For demo we are sending few dummy bytes 
	                     */
	                    hostApp_GetApplicationData((INT8 *)gHostAppBuffer,
													HOST_APP_UDP_PACKET_SIZE,
													HOST_APP_TX_DATA_TYPE_UDP);
	                    #ifdef HOST_APP_UDP_BULK_DATA_TRANSFER
	                    /* Bulk transfer mode */
		                AtLib_BulkDataTransfer(cid, gHostAppBuffer,HOST_APP_UDP_PACKET_SIZE);
	                    #else		
	                    /* Send data to remote UDP server */
		                AtLib_SendUdpData(cid,gHostAppBuffer,HOST_APP_UDP_PACKET_SIZE,HOST_APP_CON_UDP_CLIENT,NULL,NULL);
	                    #endif
                    }   
	            }
	        }
	    }
    }
}
	

void st_close_conn(void)
//---------------------
{
    do
    {
        rxMsgId =  AtLibGs_Check();          /* Check AT command state */
    }while(HOST_APP_MSG_ID_OK != rxMsgId);

    do
    {
    /* Close all active connections 
     * Note: You can also close individual connection using AtLibGs_Close()
     */
        rxMsgId = AtLibGs_CloseAll(); 
    }while(HOST_APP_MSG_ID_OK != rxMsgId);

    /* Since connections are closed, clear CID's */
    AtLib_ClearAllCid();
    state_set(ST_IDLE);
}



void fsm_com(void)
{
	PFV_I pf[] = {st_idle, st_link_check, st_init, st_reset_check, st_associate, st_tcp_conn,
				  st_udp_conn, st_close_conn};

	pf[fsm_state]();
}

UINT32 hostApp_GetApplicationData(INT8 *pBuffer,UINT32 dataLen,HOST_APP_TX_DATA_TYPE_E appDataType)
{
    /* Note: For demo purpose dummy data is filled for transmission. Contains only ASCII value.
     *       If application data contains below listed octets,  then byte stuffing must be applied, before sending over SPI interface.
     *       0x00, 0xF3,0xF5,0xFA,0xFB,0xFD,0xFF   (all values are in HEX)
     */
	
	static   UINT32  tcpPktCount=1;
	static   UINT32  udpPktCount=1;

	UINT32 count=0;
	
	if(16 > dataLen)
	{
	  appDataType = HOST_APP_TX_DATA_TYPE_MAX;
	}

	switch(appDataType)
	{
		case HOST_APP_TX_DATA_TYPE_TCP:
		{/* Note: You can add your own transmit data here */
			count=0;
			/* Fill start pattern */
			pBuffer[count++]='<';
			pBuffer[count++]='#';

		    /* Fill packet number */
			AtLib_ConvertNumberTo4DigitASCII(tcpPktCount,&(pBuffer[count]));
		    count +=4;

		    /* Fill packet length */
		    pBuffer[count++]='-';

			AtLib_ConvertNumberTo4DigitASCII(dataLen,&(pBuffer[count]));
			
	  	    count +=4;

			/* Fill packet identifier  */
			pBuffer[count++]='-';
			pBuffer[count++]='T';
			pBuffer[count++]='C';
			pBuffer[count++]='P';
			pBuffer[count++]='-';

			/* Filling Some Dummy Data for Tx */
			for(; count <(dataLen-5); count++)
			{
				pBuffer[count]= 'T';
			}

			/* Fill packet end pattern   */
			pBuffer[count++]='-';
			pBuffer[count++]='E';
			pBuffer[count++]='N';
			pBuffer[count++]='D';
			pBuffer[count++]='>';
			pBuffer[count] = '>';

			tcpPktCount++;
			if(tcpPktCount>=9999)
			{
				tcpPktCount=1;  
			}
		}	  
		break;
		
		case HOST_APP_TX_DATA_TYPE_UDP:
		{/* Note: You can add your own transmit data here */
			 
			count=0;
			/* Fill start pattern */
			pBuffer[count++]='<';
			pBuffer[count++]='#';

			AtLib_ConvertNumberTo4DigitASCII(udpPktCount,&(pBuffer[count]));

			count +=4;

		    /* Fill packet length */
		    pBuffer[count++]='-';
			
			AtLib_ConvertNumberTo4DigitASCII(dataLen,&(pBuffer[count]));

		    count +=4;

			/* Fill packet identifier  */
			pBuffer[count++]='-';
			pBuffer[count++]='U';
			pBuffer[count++]='D';
			pBuffer[count++]='P';
			pBuffer[count++]='-';

			/* Filling Some Dummy Data for Tx */
			for(; count <(dataLen-5); count++)
			{
				pBuffer[count]= 'U';
			}

			/* Fill packet end pattern   */
			pBuffer[count++]='-';
			pBuffer[count++]='E';
			pBuffer[count++]='N';
			pBuffer[count++]='D';
			pBuffer[count++]='>';
			pBuffer[count] = '>';

			udpPktCount++;
			if(udpPktCount>=9999)
			{
				udpPktCount=0;  
			}
		}	  
		break;

	default:
		/* Filling Some Dummy Data for Tx */
		for(count=0; count <dataLen; count++)
		{
			pBuffer[count]= HOST_APP_FILL_DUMMY_DATA;
		}
		pBuffer[count] = '>';
		break;
	}
	return count;
}
