/*
 * AtCmdLib.h
 */

#ifndef ATCMDLIB_H_
#define ATCMDLIB_H_

/* some new tytpedefs */
typedef char INT8;
typedef unsigned char UINT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef unsigned char u_char;




/* WARNING !!!
C30 doesn't allow pointers to constant strings.
If you want to pass a pointer, you first have
to copy the string into a ram array by using
the strcpy() function. 
*/
#define const

/* boolean  defined here */
#ifndef  TRUE
#define  TRUE   1
#define  FALSE  0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

/* For units with extra UART for debugging */
//#define HOST_APP_DEBUG_ENABLE


/* Parsing related defines */
#define  HOST_APP_TCP_CLIENT_CID_OFFSET_BYTE        (8)  /* CID parameter offset in TCP connection response */
#define  HOST_APP_UDP_CLIENT_CID_OFFSET_BYTE        (8)  /* CID parameter offset in UDP connection response */
#define  HOST_APP_BULK_DATA_LEN_STRING_SIZE         (4)  /* Number of octets representing the data lenght field in bulk data transfer message */
#define  HOST_APP_RAW_DATA_STRING_SIZE_MAX          (4)  /* Number of octets representing the data lenght field in raw data transfer message*/
#define  HOST_APP_HTTP_RESP_DATA_LEN_STRING_SIZE    (4)  /* Number of octets representing the data lenght field in HTTP data transfer message*/

#define  HOST_APP_INVALID_CID                    (0xFF) /* invalid CID */

typedef enum
{
	HOST_APP_RET_STATUS_ERROR=0,
	HOST_APP_RET_STATUS_OK=1,
	HOST_APP_RET_STATUS_VALID_DATA=2,
	HOST_APP_RET_STATUS_CONTROL_CODE=3,
	
	HOST_APP_RET_STATUS_MAX
	
}HOST_APP_RET_STATUS_E;

typedef enum
{
	HOST_APP_DISABLE=0,
	HOST_APP_ENABLE=1
}HOST_APP_STATUS_E;

typedef enum
{
 HOST_APP_CON_TCP_SERVER,
 HOST_APP_CON_UDP_SERVER,
 HOST_APP_CON_UDP_CLIENT,
 HOST_APP_CON_TCP_CLIENT
 
}HOST_APP_CON_TYPE;


typedef enum
{
    HOST_APP_RX_STATE_START=0,
	HOST_APP_RX_STATE_CMD_RESP,
	HOST_APP_RX_STATE_ESCAPE_START,
	HOST_APP_RX_STATE_DATA_HANDLE,
	HOST_APP_RX_STATE_BULK_DATA_HANDLE,
	HOST_APP_RX_STATE_HTTP_RESPONSE_DATA_HANDLE,
	HOST_APP_RX_STATE_RAW_DATA_HANDLE,
	HOST_APP_RX_STATE_MAX

}HOST_APP_RX_STATE_E;


typedef enum
{
  HOST_APP_MSG_ID_NONE        = 0,
  HOST_APP_MSG_ID_OK          = 1,
  HOST_APP_MSG_ID_INVALID_INPUT,
  HOST_APP_MSG_ID_ERROR,
  HOST_APP_MSG_ID_ERROR_IP_CONFIG_FAIL,
  HOST_APP_MSG_ID_ERROR_SOCKET_FAIL, 
  HOST_APP_MSG_ID_DISCONNECT,
  HOST_APP_MSG_ID_DISASSOCIATION_EVENT,
  HOST_APP_MSG_ID_APP_RESET,
  HOST_APP_MSG_ID_OUT_OF_STBY_ALARM,
  HOST_APP_MSG_ID_OUT_OF_STBY_TIMER, 
  HOST_APP_MSG_ID_UNEXPECTED_WARM_BOOT,
  HOST_APP_MSG_ID_OUT_OF_DEEP_SLEEP,
  HOST_APP_MSG_ID_WELCOME_MSG,
  HOST_APP_MSG_ID_STBY_CMD_ECHO,
  HOST_APP_MSG_ID_TCP_CON_DONE,  
  HOST_APP_MSG_ID_RESPONSE_TIMEOUT,
  HOST_APP_MSG_ID_BULK_DATA_RX,
  HOST_APP_MSG_ID_DATA_RX,
  HOST_APP_MSG_ID_RAW_DATA_RX,
  HOST_APP_MSG_ID_ESC_CMD_OK,
  HOST_APP_MSG_ID_ESC_CMD_FAIL,
  HOST_APP_MSG_ID_HTTP_RESPONSE_DATA_RX,
  HOST_APP_MSG_ID_MAX
  
}HOST_APP_MSG_ID_E;


#define  HOST_APP_CR_CHAR          0x0D     /* octet value in hex representing Carriage return    */
#define  HOST_APP_LF_CHAR          0x0A     /* octet value in hex representing Line feed             */
#define  HOST_APP_ESC_CHAR         0x1B     /* octet value in hex representing application level ESCAPE sequence */

/* Special characters used for data mode handling */
#define  HOST_APP_DATA_MODE_NORMAL_START_CHAR_S      'S'
#define  HOST_APP_DATA_MODE_NORMAL_END_CHAR_E        'E'   
#define  HOST_APP_DATA_MODE_BULK_START_CHAR_Z        'Z'
#define  HOST_APP_DATA_MODE_BULK_START_CHAR_H        'H'
#define  HOST_APP_DATA_MODE_RAW_INDICATION_CHAR_COL  ':'
#define  HOST_APP_DATA_MODE_RAW_INDICATION_CHAR_R    'R'
#define  HOST_APP_DATA_MODE_ESC_OK_CHAR_O            'O'
#define  HOST_APP_DATA_MODE_ESC_FAIL_CHAR_F          'F'

/************* Following control octets are  used by SPI driver layer *****************************/
#define  HOST_APP_SPI_ESC_CHAR               (0xFB)    /* Start transmission indication */
#define  HOST_APP_SPI_IDLE_CHAR              (0xF5)    /* synchronous IDLE */
#define  HOST_APP_SPI_XOFF_CHAR              (0xFA)    /* Stop transmission indication */
#define  HOST_APP_SPI_XON_CHAR               (0xFD)    /* Start transmission indication */      
#define  HOST_APP_SPI_INVALID_CHAR_ALL_ONE   (0xFF)    /* Invalid character possibly recieved during reboot */
#define  HOST_APP_SPI_INVALID_CHAR_ALL_ZERO  (0x00)    /* Invalid character possibly recieved during reboot */
#define  HOST_APP_SPI_READY_CHECK            (0xF3)    /* SPI link ready check */
#define  HOST_APP_SPI_READY_ACK              (0xF3)    /* SPI link ready response */
#define  HOST_APP_SPI_CTRL_BYTE_MASK         (0x80)    /* Control byte mask */

/************* End of  SPI driver layer  specific defines*****************************/
#define HOST_APP_TX_CMD_MAX_SIZE             (128)
#define HOST_APP_RX_CMD_MAX_SIZE             (50)

#define HOST_APP_TX_MAX_BUFFER_SIZE 512
#define TX_BUFFER_MASK (HOST_APP_TX_MAX_BUFFER_SIZE - 1)

#if ( HOST_APP_TX_MAX_BUFFER_SIZE & TX_BUFFER_MASK )
#error TX buffer size is not a power of 2
#endif

#define HOST_APP_RX_MAX_BUFFER_SIZE 512
#define RX_BUFFER_MASK (HOST_APP_RX_MAX_BUFFER_SIZE  - 1)

#if ( HOST_APP_RX_MAX_BUFFER_SIZE & RX_BUFFER_MASK )
#error RX buffer size is not a power of 2
#endif

#if ( HOST_APP_TX_CMD_MAX_SIZE > HOST_APP_TX_MAX_BUFFER_SIZE )
#error TX buffer size is not big enough to hold CMD data buffer 
#endif

/* this should be tied to a timer, faster processor larger the number */
#define  HOST_APP_RESPONSE_TIMEOUT_COUNT    (0x004FFFFF) /* Time out value for reponse message */
//#define  HOST_APP_RESPONSE_TIMEOUT_COUNT    (0xFFFFFF) OK for SPI

/*************<Function prototye forward delarations >***************/

HOST_APP_MSG_ID_E 
AtLib_CommandSend(void);
void
AtLib_DataSend(UINT8 *pTxData,UINT32 dataLen);
HOST_APP_MSG_ID_E
AtLibGs_Check(void);
HOST_APP_MSG_ID_E
AtLibGs_SetEcho(UINT8  mode);
HOST_APP_MSG_ID_E
AtLibGs_MACSet(INT8  *pAddr);
HOST_APP_MSG_ID_E
AtLibGs_CalcNStorePSK(INT8 *pSsid, INT8 *pPsk);
HOST_APP_MSG_ID_E
AtLibGs_WlanConnStat(void);
HOST_APP_MSG_ID_E
AtLibGs_DHCPSet(UINT8 mode);
HOST_APP_MSG_ID_E
AtLibGs_DHCPSrvrSet(UINT8 mode);
HOST_APP_MSG_ID_E
AtLibGs_Assoc(INT8 *pSsid, INT8 *pBssid,INT8 *pChan);
HOST_APP_MSG_ID_E
AtLibGs_TcpClientStart(INT8 *pRemoteTcpSrvIp,INT8 *pRemoteTcpSrvPort);
HOST_APP_MSG_ID_E
AtLibGs_UdpClientStart(INT8 *pRemoteUdpSrvIp,INT8  *pRemoteUdpSrvPort,INT8 *pUdpLocalPort);

HOST_APP_MSG_ID_E
AtLibGs_CloseAll(void);

HOST_APP_MSG_ID_E
AtLibGs_BatteryChkStart(UINT32 interval);
HOST_APP_MSG_ID_E
AtLibGs_GotoSTNDBy(INT8 *nsec, UINT32 dealy , UINT32 alarm1_Pol, UINT32 alarm2_Pol);
HOST_APP_MSG_ID_E
AtLibGs_PSK(INT8 *pPsk );
HOST_APP_MSG_ID_E
AtLibGs_EnableDeepSleep(void);
HOST_APP_MSG_ID_E
AtLibGs_StoreNwConn(void);
HOST_APP_MSG_ID_E
AtLibGs_ReStoreNwConn(void);
HOST_APP_MSG_ID_E
AtLibGs_IPSet(INT8* pIpAddr,INT8* pSubnet, INT8 *pGateway);

HOST_APP_MSG_ID_E
AtLibGs_SaveProfile(UINT8 mode);
HOST_APP_MSG_ID_E
AtLibGs_LoadProfile(UINT8 mode);
HOST_APP_MSG_ID_E
AtLibGs_ResetFctDflts(void);
HOST_APP_MSG_ID_E
AtLibGs_GetRssi(void);
HOST_APP_MSG_ID_E
AtLibGs_DisAssoc(void);
HOST_APP_MSG_ID_E
AtLibGs_FWUpgrade(INT8 *pSrvip, UINT32  srvport,UINT32  srcPort, INT8 *pSrcIP );
HOST_APP_MSG_ID_E
AtLibGs_BatteryChkStop(void);
HOST_APP_MSG_ID_E
AtLibGs_MultiCast(UINT8 mode);
HOST_APP_MSG_ID_E
AtLibGs_Version(void);
HOST_APP_MSG_ID_E
AtLibGs_Mode(UINT32 mode);
HOST_APP_MSG_ID_E
AtLibGs_UdpServer_Start(INT8 *pUdpSrvPort);
HOST_APP_MSG_ID_E
AtLibGs_TcpServer_Start(INT8* pTcpSrvPort, INT8 *pConnId);
HOST_APP_MSG_ID_E
AtLibGs_DNSLookup(INT8* pUrl);
HOST_APP_MSG_ID_E
AtLibGs_Close(UINT8 cid );
HOST_APP_MSG_ID_E
AtLibGs_SetWRetryCount (UINT32 count);
HOST_APP_MSG_ID_E
AtLibGs_GetErrCount (void);
HOST_APP_MSG_ID_E
AtLibGs_EnableRadio (UINT8 mode);
HOST_APP_MSG_ID_E
AtLibGs_EnablePwSave ( UINT8 mode);
HOST_APP_MSG_ID_E 
AtLibGs_SetTime ( INT8* pDate, INT8 *pTime);
HOST_APP_MSG_ID_E 
AtLibGs_EnableExternalPA(void );
HOST_APP_MSG_ID_E 
AtLibGs_SyncLossInterval( UINT8 interval);
HOST_APP_MSG_ID_E 
AtLibGs_PSPollInterval( UINT8 interval);
HOST_APP_MSG_ID_E 
AtLibGs_SetTxPower(UINT32 power);
HOST_APP_MSG_ID_E 
AtLibGs_SetDNSServerIP( INT8 *pDNS1 ,INT8 *pDNS2 );
HOST_APP_MSG_ID_E
AtLibGs_EnableAutoConnect(UINT8 mode);
void
AtLibGs_SwitchFromAutoToCmd(void );
HOST_APP_MSG_ID_E
AtLibGs_StoreWAutoConn( INT8 * pSsid, UINT8 channel);
HOST_APP_MSG_ID_E
AtLibGs_StoreNAutoConn(INT8* pIpAddr,INT8* pRmtPort);
HOST_APP_MSG_ID_E
AtLibGs_StoreATS(UINT8 param,UINT8 time);
HOST_APP_MSG_ID_E
AtLibGs_BData(UINT32 mode);
HOST_APP_MSG_ID_E 
AtLibGs_StartWPSPUSH(void );
HOST_APP_MSG_ID_E 
AtLibGs_StartWPSPIN(UINT32 pin );

UINT8 
AtLib_ParseTcpClientCid(void);
UINT8 
AtLib_ParseUdpClientCid(void);

UINT8 
AtLib_ParseWlanConnStat(void);
UINT8 
AtLib_ParseGetMacResponse(UINT8 *pRefNodeMacId);
UINT8
AtLib_ParseNodeIpAddress(UINT8 *pIpAddr);
UINT8
AtLib_ParseRssiResponse(UINT16 *pRssi);
UINT8
AtLib_ParseUdpServerStartResponse(UINT8 *pConnId);
UINT8
AtLib_ParseTcpServerStartResponse(UINT8 *pConnId);
UINT8
AtLib_ParseDNSLookupResponse(char *ipAddr);
UINT8
AtLib_ParseWPSPUSHResponse(void);
UINT8
AtLib_ParseWPSPINResponse(UINT32 pin );

#ifdef HOST_APP_INTERFACE_SPI
UINT8
AtLib_SpiByteStuff(UINT8 *pNextData);
HOST_APP_RET_STATUS_E
AtLib_SpiByteDeStuff(UINT8 *pNextData);
#endif

HOST_APP_MSG_ID_E 
AtLib_CommandSend(void);
void 
AtLib_DataSend(UINT8 *pTxData,UINT32 dataLen);
void
AtLib_SendTcpData( UINT8 cid,UINT8 *txBuf, UINT32 dataLen);
void
AtLib_SendUdpData(UINT8 cid,UINT8 *txBuf, UINT32 dataLen,
						HOST_APP_CON_TYPE conType , UINT8 *pUdpClientIP, UINT8 *pUdpClientPort);

void 
AtLib_BulkDataTransfer (UINT8 cid,UINT8 *pData, UINT32 dataLen);
HOST_APP_MSG_ID_E
AtLib_checkEOFMessage(UINT8 * pBuffer);
void
AtLib_RecieveDataHandle(void);
HOST_APP_MSG_ID_E
AtLib_RecieveDataProcess(UINT8 rxData);
HOST_APP_MSG_ID_E
AtLib_ResponseHandle(void);
HOST_APP_MSG_ID_E
AtLib_ProcessRxChunk(UINT8 *rxBuf, UINT32 bufLen);
void
AtLib_ProcessIncomingData(UINT8 cid, UINT8 rxData);
void
AtLib_LinkCheck(void);
void
AtLib_ReadBootUpMessage(void);
UINT8
AtLib_IsNodeResetDetected(void);
void
AtLib_SetNodeResetFlag(void);
void
AtLib_ClearNodeResetFlag(void);
UINT8
AtLib_IsNodeAssociated(void);
void
AtLib_SetNodeAssociationFlag(void);
void
AtLib_ClearNodeAssociationFlag(void);

void
AtLib_ClearAllCid(void);
void
AtLib_SaveTcpCid(UINT8 cid);
void
AtLib_SaveUdpCid(UINT8 cid);

void
AtLib_ClearAllCid(void);
UINT8
AtLib_GetTcpCid(void);
UINT8
AtLib_GetUdpCid(void);

void
AtLib_FlushRxBuffer(void);
INT32
AtLib_strcasecmp(const char *s1, const char *s2);
void 
AtLib_ConvertNumberTo4DigitASCII(UINT32 myNum, INT8 *pStr);

void
rx_buffer_init(void);

void
buffers_init(void);

extern UINT8  gRecieveBuffer[]; 
extern UINT8  gTransmitBuffer[]; 
extern UINT8 gRecieveFlag;

extern volatile UINT16 gRB_TxHead;
extern volatile UINT16 gRB_TxTail;
extern volatile UINT16 gRB_RxHead;
extern volatile UINT16 gRB_RxTail;

#endif  // ATCMDLIB_H_

/*************< End of  Function  forward delarations >***************/

