/*
*********************************************************************************************************
*
*                                          lm3s8963-GainSpan/Main
*                                            INTRODUCTION DEMO
*
*
* Filename      : gp_cmd.h
* Version       : V0.01
* Programmer(s) : MC
*********************************************************************************************************
*/
#ifndef GP_CMD_H_
#define GP_CMD_H_

#include "util_type.h"


#ifdef __cplusplus
extern "C"
{
#endif
/*
*********************************************************************************************************
*                                           GLOABLE DEFINES
*********************************************************************************************************
*/
#define HOST_APP_FILL_DUMMY_DATA             'A'

/*
*********************************************************************************************************
*                                          GLOABLE DATA TYPES
*********************************************************************************************************
*/
typedef struct{
	U8			assoc;
	U8			mode;
	U8			dhcp;
	U8			tcp_srvr;
	U8			udp_srvr;
	U8			tcp_client;
	U8			udp_client;
	U8			tcp_uid;
	U8			udp_uid;
	U8			ssid[15];
	U8			myip[15];
} my_wifi_t;

/*
*********************************************************************************************************
*                                          GLOABLE VARIABLE
*********************************************************************************************************
*/
extern my_wifi_t wifiInfo;

/*
*********************************************************************************************************
*                                          GLOABLE FUNCTION
*********************************************************************************************************
*/
extern int GP_Init(void);
extern int GP_AC_Init(S8 *ssid);
extern int GP_AP_Init(S8 *ssid);
extern int GP_Hdcpsrvr(U8 mode);
extern int GP_TCP_Srvr(S8 *port);
extern int GP_Tcp_Assoc(void);
extern int GP_Close_All(void);
extern void GP_Check(void);
extern int hostApp_GetApplicationData(S8 *pBuffer,U32 dataLen, U8 appDataType);
extern void task_GP_Init(void);

/*******************************************************************************
                                   
*******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif 
