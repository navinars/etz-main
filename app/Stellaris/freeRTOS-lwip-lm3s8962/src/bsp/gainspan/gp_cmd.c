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
#include <string.h>

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "util_type.h"
#include "gp_cmd.h"
#include "AtCmdLib.h"
#include "app_cfg.h"
#include "user/rit128x96x4.h"

/*
*********************************************************************************************************
*                                         LOCAL DEFINE
*********************************************************************************************************
*/
#define HOST_APP_AP_SSID					"gp"
#define HOST_APP_REMOTE_TCP_SRVR_IP			"192.168.3.1"
#define HOST_APP_REMOTE_TCP_SRVR_PORT		"9003"


#define HOST_APP_LOCAL_IP					"192.168.3.1"
#define HOST_APP_LOCAL_MASK					"255.255.255.0"
#define HOST_APP_LOCAL_GATEWAY				"192.168.3.1"

#define TCP_SERVER_PORT						"9003"

/*
*********************************************************************************************************
*                                         LOCAL VARIABLE
*********************************************************************************************************
*/
static U8 			cid;
HOST_APP_MSG_ID_E 	rxMsgId = HOST_APP_MSG_ID_NONE;
my_wifi_t 			wifiInfo;

/*
*********************************************************************************************************
*                                         LOCAL FUNCIONS
*********************************************************************************************************
*/
static void task_GainSpan(void *parg);

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
int GP_Init(void)
{
	AtLib_ClearNodeAssociationFlag();
	AtLib_ClearAllCid();
	memset(&wifiInfo, 0, sizeof(wifiInfo));
	
	if (AtLibGs_SetEcho(0) == HOST_APP_MSG_ID_OK)
		return SUCCESS;
	else
	{
		if (AtLibGs_SetEcho(0) == HOST_APP_MSG_ID_OK)
			return SUCCESS;
		else
			return FAILED;
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
int GP_AC_Init(S8 *ssid)
{
	GP_Close_All();
	if (wifiInfo.assoc == false)
	{
		if(AtLibGs_DHCPSet(1) == HOST_APP_MSG_ID_OK) {
			wifiInfo.dhcp = 0;
		} else return FAILED;
		
		if (AtLibGs_Mode(0) == HOST_APP_MSG_ID_OK) {
			wifiInfo.mode = 0;
		} else return FAILED;
		
		if (AtLibGs_Assoc(ssid, NULL, NULL) == HOST_APP_MSG_ID_OK)
		{
			/* link AP, set associaton flag.*/
			AtLib_ParseNodeIpAddress(wifiInfo.myip);
			AtLib_SetNodeAssociationFlag();
			wifiInfo.assoc = true;
			return SUCCESS;
		}
		else
			return FAILED;
	}
	return SUCCESS;
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
int GP_AP_Init(S8 *ssid)
{
	
	if (AtLib_IsNodeAssociated() == false)
	{
		if (AtLibGs_DHCPSet(0) != HOST_APP_MSG_ID_OK)
			return FAILED;
		
		if (AtLibGs_Mode(2) != HOST_APP_MSG_ID_OK)
			return FAILED;
		
		if (AtLibGs_IPSet(HOST_APP_LOCAL_IP, HOST_APP_LOCAL_MASK, HOST_APP_LOCAL_GATEWAY) != HOST_APP_MSG_ID_OK)
			return FAILED;
		
		if (AtLibGs_Assoc(ssid, NULL, NULL) != HOST_APP_MSG_ID_OK)
			return FAILED;
	}
	return SUCCESS;
}

/********************************************************************************************************
*                                             GP_DisAssoc()
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
int GP_DisAssoc(void)
{
	if (AtLibGs_DisAssoc() == HOST_APP_MSG_ID_OK)
		return 1;
	else
		return 0;
}

/********************************************************************************************************
*                                             GP_Hdcpsrvr()
*
* Description : Set HDCP servive mode;
*
* Argument(s) : mode			1 or 0.
*
* Return(s)   : success is 1, failure is 0.
*
* Caller(s)   : app.
*
* Note(s)     : none.
*/
int GP_Hdcpsrvr(U8 mode)
{
	
	if (AtLibGs_DHCPSrvrSet(mode) == HOST_APP_MSG_ID_OK)
		return SUCCESS;
	else
		return FAILED;
}

/********************************************************************************************************
*                                             GP_TCP_Srvr()
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
int GP_TCP_Srvr(S8 *port)
{

	if (AtLibGs_TcpServer_Start(port, NULL) == HOST_APP_MSG_ID_OK)
	{
		cid = AtLib_ParseTcpClientCid();
		/* */
		if (cid == HOST_APP_INVALID_CID) {
			return FAILED;
		} else {
			/* Save CID value for future reference */
			cid = AtLib_ParseTcpClientCid();
			AtLib_SaveTcpCid(cid);

			if (cid == HOST_APP_INVALID_CID) {
	            return FAILED;
   	        } else {
				return SUCCESS;
			}
		}
	}
	else
		return FAILED;
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
            return FAILED;
        }
		else
		{
			wifiInfo.tcp_client = true;
			wifiInfo.tcp_uid = AtLib_ParseTcpClientCid();
			return SUCCESS;
		}
	}
	return FAILED;
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
int GP_Close_All(void)
{
	if (AtLibGs_CloseAll() == HOST_APP_MSG_ID_OK)
		return SUCCESS;
	else
		return FAILED;
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
	
}
 
/********************************************************************************************************
*                                             hostApp_GetApplicationData()
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
int hostApp_GetApplicationData(S8 *pBuffer,U32 dataLen, U8 appDataType)
{
 static   UINT32  tcpPktCount=1;
 static   UINT32  udpPktCount=1;

 UINT32 count=0;
	
	if(16 > dataLen)
	{
	  appDataType = 3;
	}

	switch(appDataType)
	{
		
		case 1:
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
		
		case 2:
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

/********************************************************************************************************
*                                             hostApp_GetApplicationData()
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
void task_GP_Init(void)
{
	xTaskCreate( task_GainSpan, ( signed char * ) "task_GainSpan",
				configMINIMAL_STACK_SIZE, NULL, TASK_GP_TASK_PRIORITY, NULL );
}

/********************************************************************************************************
*                                             hostApp_GetApplicationData()
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
static void task_GainSpan(void *parg)
{
	if (GP_Init() == SUCCESS)
	{
		RIT128x96x4StringDraw("ON", 99, 16, 15);
	}
	else
	{
		RIT128x96x4StringDraw("OFF", 93, 16, 15);
	}
	
	if (GP_AP_Init("AP") == SUCCESS)
	{
		RIT128x96x4StringDraw("AP", 99, 24, 15);
		RIT128x96x4StringDraw("GP", 99, 32, 15);
	}
	else
	{
		RIT128x96x4StringDraw("AC", 99, 24, 15);
		RIT128x96x4StringDraw("NO FOUND", 63, 32, 15);
	}
	
	if(GP_Hdcpsrvr(1) == SUCCESS)
	{
		RIT128x96x4StringDraw("ON", 99, 40, 15);
	}
	
	if (GP_TCP_Srvr("9003") == SUCCESS)
	{
		RIT128x96x4StringDraw("Server", 75, 56, 15);
		RIT128x96x4StringDraw("9003", 87, 64, 8);
	}
	for(;;)
	{
		//串口轮询接受，单字节处理
		AtLib_RecieveDataHandle();
		if (gRecieveFlag == 1)
		{
			gRecieveFlag = 0;
			memset(gRecieveBuffer, '\0', HOST_APP_RX_MAX_BUFFER_SIZE);
		}
		vTaskDelay(2);
	}
}


