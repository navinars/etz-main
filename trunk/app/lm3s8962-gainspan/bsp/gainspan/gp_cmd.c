/*
*********************************************************************************************************
*
*                                          lm3s8963-GainSpan/Main
*                                            INTRODUCTION DEMO
*
*
* Filename      : gp_commands.c
* Version       : V0.01
* Programmer(s) : MC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"
#include "AtCmdLib.h"

/*
*********************************************************************************************************
*                                         LOCAL DEFINE
*********************************************************************************************************
*/
#define HOST_APP_AP_SSID					"gp"
#define HOST_APP_REMOTE_TCP_SRVR_IP			"192.168.3.1"
#define HOST_APP_REMOTE_TCP_SRVR_PORT		"9002"

#define HOST_APP_LOCAL_IP					"192.168.3.1"
#define HOST_APP_LOCAL_SUBNET				"255.255.255.0"
#define HOST_APP_LOCAL_GATEWAY				"192.168.3.1"
/*
*********************************************************************************************************
*                                         LOCAL VARIABLE
*********************************************************************************************************
*/
static U8 cid;
HOST_APP_MSG_ID_E rxMsgId = HOST_APP_MSG_ID_NONE;


/*
*********************************************************************************************************
*                                         LOCAL FUNCIONS
*********************************************************************************************************
*/


/********************************************************************************************************
*                                             GP_AC_Init()
*
* Description : Initiase GainSpan.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
int GP_AC_Init(void)
{
	U8 init_try = 0;
	U8 associate_try = 0;
	
	do{
		init_try ++;
		if (init_try > 10){
			init_try = 0;
			return 0;
		}
		rxMsgId = AtLibGs_SetEcho(0);
	}while(rxMsgId != HOST_APP_MSG_ID_OK);
	
	do{
		init_try ++;
		if (init_try > 10){
			init_try = 0;
			return 0;
		}
		rxMsgId = AtLibGs_DHCPSet(1);
	}while(rxMsgId != HOST_APP_MSG_ID_OK);
	
	do{
		init_try ++;
		if (init_try > 10){
			init_try = 0;
			return 0;
		}
		rxMsgId = AtLibGs_Mode(0);
	}while(rxMsgId != HOST_APP_MSG_ID_OK);
	
	for(;;)
	{
		/* Associate to a particular AP specified by SSID "TP"  */
		rxMsgId = AtLibGs_Assoc(HOST_APP_AP_SSID, NULL, NULL);
		
		if(HOST_APP_MSG_ID_OK != rxMsgId)
		{
			/* Association error - we can retry */
			associate_try++;
			my_delay_ms(1000); /* Retry after 1 seconds */
			
			if (associate_try > 10)
			{
				associate_try = 0;
				return 0;
			}
		}
		else
		{
			//Read gateway
			
			// 连接到AP，设置连接标志位
			AtLib_SetNodeAssociationFlag();
			return 1;
		}
	}
}


/********************************************************************************************************
*                                             GP_AP_Init()
*
* Description : Initiase GainSpan.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
int GP_AP_Init(void)
{
	U8 init_try = 0;
	U8 associate_try = 0;
	
	do{
		init_try ++;
		if (init_try > 10){
			init_try = 0;
			return 0;
		}
		rxMsgId = AtLibGs_SetEcho(0);
	}while(rxMsgId != HOST_APP_MSG_ID_OK);
	
	do{
		init_try ++;
		if (init_try > 10){
			init_try = 0;
			return 0;
		}
		rxMsgId = AtLibGs_DHCPSet(0);
	}while(rxMsgId != HOST_APP_MSG_ID_OK);
	
	do{
		init_try ++;
		if (init_try > 10){
			init_try = 0;
			return 0;
		}
		rxMsgId = AtLibGs_Mode(2);
	}while(rxMsgId != HOST_APP_MSG_ID_OK);
	
	do{
		init_try ++;
		if (init_try > 10){
			init_try = 0;
			return 0;
		}
		rxMsgId = AtLibGs_IPSet(HOST_APP_LOCAL_IP, HOST_APP_LOCAL_SUBNET, HOST_APP_LOCAL_GATEWAY);
	}while(rxMsgId != HOST_APP_MSG_ID_OK);
	
	for(;;)
	{
		/* Associate to a particular AP specified by SSID "TP"  */
		rxMsgId = AtLibGs_Assoc(HOST_APP_AP_SSID, NULL, NULL);
		
		if(HOST_APP_MSG_ID_OK != rxMsgId)
		{
			/* Association error - we can retry */
			associate_try++;
			my_delay_ms(1000); /* Retry after 1 seconds */
			
			if (associate_try > 10)
			{
				associate_try = 0;
				return 0;
			}
		}
		else
		{
			//Read gateway
			
			// 连接到AP，设置连接标志位
			AtLib_SetNodeAssociationFlag();
			return 1;
		}
	}
}

/********************************************************************************************************
*                                             GP_AC_Init()
*
* Description : Initiase GainSpan.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
int GP_Tcp_Assoc(void)
{
	
	if (AtLib_IsNodeAssociated() == true)
	{
		rxMsgId = AtLibGs_TcpClientStart(HOST_APP_REMOTE_TCP_SRVR_IP, HOST_APP_REMOTE_TCP_SRVR_PORT);
		
		if (rxMsgId != HOST_APP_MSG_ID_OK)
        {
            return 0;
        }
		else
		{
			/* Save CID value for future reference */
			cid = AtLib_ParseTcpClientCid();
            AtLib_SaveTcpCid(cid);
			
			if (cid == HOST_APP_INVALID_CID)
            {
	            return 0;
   	        }
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

/********************************************************************************************************
*                                             GP_Close_All()
*
* Description : check GainSpan datas.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void GP_Close_All(void)
{
	U8 init_try = 0;
	
	do{
		init_try ++;
		if (init_try > 10){
			init_try = 0;
			return;
		}
		rxMsgId = AtLibGs_CloseAll(); 
	}while(rxMsgId != HOST_APP_MSG_ID_OK);
}

/********************************************************************************************************
*                                             GP_Check()
*
* Description : check GainSpan datas.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
void GP_Check(void)
{
    /* Handle pending  data if any */
    AtLib_RecieveDataHandle();

    if(AtLib_IsNodeResetDetected() == TRUE)
    {
        /* Reset the flag */
        AtLib_ClearNodeResetFlag();
		
		/* Initialise GainSpan*/
		GP_Close_All();
	    GP_AC_Init();
    }
    else
    {
        if (AtLib_IsNodeAssociated() == FALSE)
        {
			/* 重新初始化*/
//	        GP_AC_Init();
			RIT128x96x4StringDraw("Link GP FAILURE", 18, 24, 15);
			GP_AC_Init();
            GP_Tcp_Assoc();
        }
	    else  // check association
	    {
            /* Get the current status of WLAN connection
             * Check whether it is already associated to one of the AP or NOT ?
	         */
//			rxMsgId = AtLibGs_WlanConnStat();
			//socket连接断开
            if(AtLib_GetTcpCid() == 0xFF)
            {
		        /* Currently S2w App node is NOT associated.
                 * Start Association.
                 */	
				/* 重新初始化*/
				
				RIT128x96x4StringDraw("socket is disconnect", 12, 24, 15);
				GP_AC_Init();
                GP_Tcp_Assoc();
	        }
	        else
	        {
                /* S2w App node is already associated. Proceed to data connection set-up */
                //state_set(ST_TCP_CONN);  // default ?
                // or
				/* 重新建立TCP链接*/
                //GP_Tcp_Assoc();
	        }
	    }
    }
}









