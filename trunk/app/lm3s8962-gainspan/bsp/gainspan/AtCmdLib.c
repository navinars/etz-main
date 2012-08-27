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

/******************************************************************************
* File Name	: AtCmdLib.c
* Version 	: 1.00
* Device 	: Microchip PIC24
* Tool Chain 	: 
* H/W Platform	: PIC24FJ128GA010 (100 pin)
* Description 	: Library of command functions and handlers.
*
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//#include "HostApp.h"
#include "AtCmdLib.h"

#include "includes.h"

/* Global variables */
/* receive buffer is a circullar buffer */
/* Recieve buffer to save async and response message from S2w App Node */
UINT8  gRecieveBuffer[HOST_APP_RX_MAX_BUFFER_SIZE]; 
UINT8  gTransmitBuffer[HOST_APP_TX_MAX_BUFFER_SIZE]; 

volatile UINT16 gRB_TxHead;
volatile UINT16 gRB_TxTail;
volatile UINT16 gRB_RxHead;
volatile UINT16 gRB_RxTail;

/* if using isr driven driver we need to copy data for parsing */
/* Recieve buffer to save async and response message from S2w App Node */
UINT8  MRBuffer[HOST_APP_RX_CMD_MAX_SIZE];
UINT16 MRBufferIndex = 0;

char  at_cmd_buf[HOST_APP_TX_CMD_MAX_SIZE];  /* Command transmit buffer */

static UINT8 nodeAssociationFlag=FALSE;             /* Flag to indicate whether S2w Node is currently associated or not */
static UINT8 nodeResetFlag=FALSE;                   /* Flag to indicate whether S2w Node has rebooted after initialisation  */
static UINT8 tcpClientCid=HOST_APP_INVALID_CID;     /* TCP client CID */
static UINT8 udpClientCid=HOST_APP_INVALID_CID;     /* UDP client CID */

/* Tx Rx Ring buffer access functions */

/*************************************************************************
Function: rx_buffer_init
Purpose:  initialize RX/TX ringbuffers  
Returns:  none
**************************************************************************/
void
rx_buffer_init(void)
{	

    gRB_RxHead = 0;
    gRB_RxTail = 0;
    /* clear RX buffer */	
	memset(gRecieveBuffer,'\0',HOST_APP_RX_MAX_BUFFER_SIZE);
}

/*************************************************************************
Function: buffers_init
Purpose:  initialize RX/TX ringbuffers  
Returns:  none
**************************************************************************/
void
buffers_init(void)
{	
    gRB_TxHead = 0;
    gRB_TxTail = 0;
    gRB_RxHead = 0;
    gRB_RxTail = 0;
    /* clear TX buffer */
	memset(gTransmitBuffer,'\0',HOST_APP_TX_MAX_BUFFER_SIZE);
    /* clear RX buffer */	
	memset(gRecieveBuffer,'\0',HOST_APP_RX_MAX_BUFFER_SIZE);
}

void
AtLib_FlushRxBuffer(void)
{/* Reset the response recieve buffer */
	MRBufferIndex = 0;
	memset(MRBuffer,'\0',HOST_APP_RX_CMD_MAX_SIZE);
}



/*---------------------------<AT command list >--------------------------------------------------------------------------
    _________________________________________________________________________________________________________________________
    AT Command                                                                   Description and AT command library API Name
    _________________________________________________________________________________________________________________________

    ATE<0|1>                                                                             Disable/enable echo
                                                                                         API Name: AtLibGs_SetEcho
    
    AT&W<0|1>                                                                            Save Settings to profile 0/1
                                                                                         API Name: AtLibGs_SaveProfile

    ATZ<0|1>                                                                             Load Settings from profile 0/1
                                                                                         API Name: AtLibGs_LoadProfile

    AT+EXTPA=<1/0>                                                                       Enable/disable external PA.
                                                                                         API Name: AtLibGs_EnableExternalPA 

    AT+WSYNCINTRL=<interval>                                                             configure the sync loss interval in TBTT interval
                                                                                         API Name: AtLibGs_SyncLossInterval
 
    AT+PSPOLLINTRL=<interval>                                                            configure the Ps poll interval in Seconds
                                                                                         API Name: AtLibGs_PSPollInterval 
    
    AT+BDATA=<0/1>                                                                       Bulk data reception enable/disable
                                                                                         API Name: AtLibGs_BData

    AT&F                                                                                 Reset to factory defaults
                                                                                         API Name:AtLibGs_ResetFctDflts

    AT+WM=<0|1>                                                                          Set mode to Infrastructure (0) or ad-hoc (1)
                                                                                         API Name: AtLibGs_Mode
    
    AT+WA=<SSID>[[,<BSSID>][,<Ch>]]                                                      Associate to network or form ad-hoc network
                                                                                         API Name: AtLibGs_Assoc

    AT+WD or ATH                                                                         Disassociate from current network
                                                                                         API Name:AtLibGs_DisAssoc

    AT+WRSSI=?                                                                           Query the current RSSI value
                                                                                         API Name: AtLibGs_GetRssi
    
    AT+WWPA=passphrase                                                                   Set WPA passphrase (8 - 63 chars)
                                                                                         API Name: AtLibGs_SetPassPhrase
    
    AT+WRETRY=n                                                                          Set the wireless retry count
                                                                                         API Name: AtLibGs_SetWRetryCount

    AT+WRXACTIVE=<0|1>                                                                   Enable/disable the radio
                                                                                         API Name: AtLibGs_EnableRadio

    AT+WRXPS=<0|1>                                                                       Enable/disable 802.11 power save
                                                                                         API Name: AtLibGs_EnablePwSave

    AT+WP=<power>                                                                        Set the transmit power
                                                                                         API Name: AtLibGs_SetTxPower

    AT+NMAC=<?>/<mac>                                                                    Get/Set MAC address and store in flash
                                                                                         API Name: AtLibGs_GetMAC / AtLibGs_MACSet

    AT+NDHCP=<0|1>                                                                       Disable/Enable DHCP
                                                                                         API Name: AtLibGs_DHCPSet

    AT+NSET=<IP>,<NetMask>,<Gateway>                                                     Configure network address
                                                                                         API Name: AtLibGs_IPSet

    AT+NCTCP=<IP>,<Port>                                                                 Open TCP client
                                                                                         API Name: AtLibGs_TcpClientStart

    AT+NCUDP=<IP>,<RemotePort>,[<LocalPort>                                              Open UDP client
                                                                                         API Name: AtLibGs_UdpClientStart

    AT+NSTCP=<Port>                                                                      Open TCP server on Port
                                                                                         API Name: AtLibGs_TcpServer_Start

    AT+NSUDP=<Port>                                                                      Open UDP server on Port
                                                                                         API Name: AtLibGs_UdpServer_Start

    AT+NCLOSE=cid                                                                        Close the specified connection
                                                                                         API Name: AtLibGs_Close

    AT+NCLOSEALL                                                                         Close all connections
                                                                                         API Name: AtLibGs_CloseAll
    
    AT+WAUTO=<Mode>,<SSID>,<bssid>,[Channel]                                             Configure auto connect wireless settings
                                                                                         API Name: AtLibGs_StoreWAutoConn 

    AT+NAUTO=<Type>,<Protocol>,<DestIP>,<DestPort>                                       Configure auto connection
                                                                                         Client(0)/server(1), protocol UDP(0)/TCP(1),and host.
                                                                                         API Name: AtLibGs_StoreNAutoConn

    ATC<0|1>                                                                             Disable/enable auto connection
                                                                                         API Name: AtLibGs_EnableAutoConnect

    +++                                                                                  Switch to Command mode while in auto-connect mode
                                                                                         API Name: AtLibGs_SwitchFromAutoToCmd

    ATSparam=value                                                                       Set configuration parameters
                                                                                         Network connection timeout (0) / Auto associate timeout (1)
                                                                                         TCP connection timeout (2) / Association retry count (3)
                                                                                         Nagle algorithm wait time (4)
                                                                                         API Name: AtLibGs_StoreATS
    
    AT+PSDPSLEEP                                                                         Enable deep sleep
                                                                                         API Name: AtLibGs_EnableDeepSleep
 
    AT+PSSTBY=<n>[,<delay time>,<alarm1-pol>,<alarm2-pol>]                               Standby request for n milliseconds
                                                                                         API Name: AtLibGs_GotoSTNDBy 

    AT+STORENWCONN                                                                       Store the nw context
                                                                                         API Name: AtLibGs_StoreNwConn 

    AT+RESTORENWCONN                                                                     Restore the nw context
                                                                                         API Name: AtLibGs_ReStoreNwConn 

    AT+FWUP=<SrvIp>,<SrvPort>,<SrcPort>                                                  Start FW Upgrade
                                                                                         API Name: AtLibGs_FWUpgrade

    AT+WPAPSK=<SSID>,<PassPhrase>                                                        Calculate and store the PSK
                                                                                         API Name: AtLibGs_CalcNStorePSK 
    
    AT+NSTAT=?                                                                           Display current network context
                                                                                         API Name: AtLibGs_WlanConnStat 

    AT+VER=?                                                                             Get the Version Info
                                                                                         API Name: AtLibGs_Version 

    AT+DNSLOOKUP=<URL>,[<RETRY>,<TIMEOUT-S>]                                             Get the ip from host name
                                                                                         API Name: AtLibGs_DNSLookup

    AT+DNSSET=<DNS1-IP>,[<DNS2-IP>]                                                      Set static DNS IP addresses
                                                                                         API Name: AtLibGs_SetDNSServerIP

    AT+MCSTSET=<0/1>                                                                     enable/disable the multicast recv
                                                                                         API Name: AtLibGs_MultiCast 

    AT+BCHKSTRT=<Measure interval>                                                       Start the batt chk 
                                                                                         API Name: AtLibGs_BatteryChkStart 
    

    AT+BCHKSTOP                                                                          Stop the batt chk 
                                                                                         API Name: AtLibGs_BatteryChkStop
     
    AT+ERRCOUNT=?                                                                        Get the error counts
                                                                                         API Name: AtLibGs_GetErrCount 

    AT+SETTIME=<dd/mm/yyyy>,<HH:MM:SS>                                                   Set the system time
                                                                                         API Name: AtLibGs_SetTime 
    
    AT+WWPS=<1/2>,<wps pin>                                                              Associate to an AP using WPS. 
                                                                                         1 - Push Button mathod.
                                                                                         2 - PIN mathod. Provide <wps pin> only in case of PIN mathod
                                                                                         API Name: AtLibGs_StartWPSPUSH / AtLibGs_StartWPSPIN

    
    AT&Y<0|1>                                                                            Set default power on profile to profile 0/1
                                                                                         API Name: Not Available

    AT&V                                                                                 Output current configuration
                                                                                         API Name: Not Available

    AT+WS[=<SSID>[,<BSSID>][,<Ch>][,<ScanTime>]]                                         Perform wireless scan
                                                                                         API Name: Not Available

    AT+WRATE=?                                                                           Query the current WiFi rate used
                                                                                         API Name: Not Available

    AT+WWEPn=<key>                                                                       Set WEP key (10 or 26 hex digits) with index n (1-4)
                                                                                         API Name: Not Available

    AT+WAUTH=<authmode>                                                                  Set authmode (1->open,2->shared)
                                                                                         API Name: Not Available

    AT+WSTATUS                                                                           Display current Wireless Status
                                                                                         API Name: Not Available

    AT+NMAC2=<?>/<mac>                                                                   Get/Set MAC address and store in RTC
                                                                                         API Name: Not Available

    AT+SETSOCKOPT=<cid>,<type>,<parameter>,<value>,<length                               Set options of a socket specified by cid
                                                                                         API Name: Not Available

    ATA                                                                                  Initiate AutoConnect
                                                                                         API Name: Not available 

    ATA2                                                                                 Initiate AutoConnect-tcp/udp level
                                                                                         API Name: Not available 

    ATO                                                                                  Return to Auto Data mode
                                                                                         API Name: Not available 

    ATI<n>                                                                               Display identification number n
                                                                                         API Name: Not available 

    AT+WPSK=<PSK>                                                                        Store the PSK
                                                                                         API Name: Not available 

    AT+CID=?                                                                             Display The CID info
                                                                                         API Name: Not available 
    
    AT+BCHK=<?>/<Measure interval>                                                       Get/Set batt chk param 
                                                                                         API Name: Not available 

    AT+BATTVALGET                                                                        Get the latest battery value stored in RTC
                                                                                         API Name: Not available 


    AT+BATTLVLSET=<Warning Level>,<warning Freq>,<Standby Level>                         Set batt warning level, frequency of reporting warning
                                                                                         and batt standby levl 
                                                                                         API Name: Not available 
                              
    AT+PING=<Ip>,<Trails>,<Interval>,<Len>,<TOS>,<TTL>,<PAYLAOD(16 Bytes)>               Starts Ping
                                                                                         API Name: Not available 

    AT+TRACEROUTE=<Ip>,<Interval>,<MaxHops>,<MinHops>,<TOS>                              Starts Trace route
                                                                                         API Name: Not available 
                              

    AT+GETTIME=?                                                                         Get the system time in Milli-seconds since Epoch(1970)
                                                                                         API Name: Not available 

    AT+DGPIO=<GPIO_PIN>,<1-SET/0-RESET>                                                  Set/reset a gpio pin
                                                                                         API Name: Not available 
                              
    AT+TCERTADD=<name>,<format>,<size>,<location>\n\r<ESC>W<data of size above>          Provisions a certificate. 
                                                                                         format-binary/ascii(0/1),location-FLASH/RAM.
                                                                                         Follow the escape sequence to send data.
                                                                                         API Name: Not available 

    AT+TCERTDEL=<name>                                                                   Delete a certificate
                                                                                         API Name: Not available 
                              

    AT+WEAPCONF=<outer authtype>,<inner authtype>,<user name>,<password>                 Configure auth type,user name and password for EAP
                                                                                         API Name: Not available
 
    AT+WEAP=<type>,<format>,<size>,<location>\n\r<ESC>W<data of size above>              Provision certificate for EAP TLS.
                                                                                         Type-CA/CLIENT/PUB_KEY(0/1/2),
                                                                                         format-binary/ascii(0/1),location- flash/RAM(0/1).
                                                                                         Follow the escape sequence to send data.
                                                                                         API Name: Not available 
                              
    AT+SSLOPEN=<cid>,<name>                                                              Opens a ssl connection. name-Name of certificate to use
                                                                                         API Name: Not available
 
    AT+SSLCLOSE=<cid>                                                                    Close a SSL connection
                                                                                         API Name: Not available 

    AT+HTTPOPEN=<hostName/ip addr>,[<port>,<secured/non secured>,<certificate name>]     Opens a http/https connection
                                                                                         API Name: Not available 

    AT+HTTPCLOSE=<cid>                                                                   Closes a http connection
                                                                                         API Name: Not available 
    AT+HTTPSEND=<cid>,<Method>,<TimeOut>,<Page>[,<Size>]\n\r<ESC>H<data of size above>
                                                                                         Send a Get or POST request.Method- GET/HEAD/POST(1/2/3) 
                                                                                         Follow the escape sequence to send data.
                                                                                         API Name: Not available 

    AT+HTTPCONF=<Param>,<Value>                                                          Configures http parameters.
                                                                                         API Name: Not available 
                              
   AT+WEBPROV=<user name>,<passwd>,<ip addr><subnet mask> <gateway>                      start web server. username passwd are used for authentication
                                                                                         The server is atarted with the given ip addr, subnetmask 
                                                                                         and gateway
                                                                                         API Name: Not available 
                              
   AT+WEBPROV=<user name>,<passwd>                                                       start web server. username passwd are used for authentication
                                                                                         API Name: Not available 

   AT+WEBLOGOADD=<size>                                                                  add webserver logo of size <size>. After issuing 
                                                                                         the command, send <esc> followed by l/L   and 
                                                                                         send the content of the logo file
                                                                                         API Name: Not available 
                               
    AT+NRAW=<0/1/2>                                                                      Enable Raw Packet transmission.
                                                                                         API Name: Not available 
                              
    ATV<0|1>                                                                             Disable/enable verbose responses
                                                                                         API Name: Not Available
   _________________________________________________________________________________________________________________________*/
 
/*----------------<AT command library >---------------------------------- */

HOST_APP_MSG_ID_E AtLibGs_Check(void)
{	/* AT
	*  Dummy command 
	*/
	
	HOST_APP_MSG_ID_E rxMsgId;
	
	/* Construct the AT command */
	sprintf(at_cmd_buf,"\r\nAT\r\n");
	
	rxMsgId = AtLib_CommandSend();
	
	return rxMsgId;
}

HOST_APP_MSG_ID_E AtLibGs_SetEcho(UINT8  mode)
{   /*  ATE<0|1> 
	 *  Disable/enable echo   
	 */
         
	HOST_APP_MSG_ID_E rxMsgId;

	/* Construct the AT command */
	sprintf(at_cmd_buf, "ATE%d\r\n", mode);

	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E AtLibGs_MACSet(INT8  *pAddr)
{/* AT+NMAC=<mac>
   *  Set MAC address and store in flash
   *  
   */
	HOST_APP_MSG_ID_E rxMsgId;

	/* Construct the AT command */
        sprintf(at_cmd_buf,"AT+NMAC=%s\r\n",pAddr);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E AtLibGs_GetMAC(void)
{/* AT+NMAC=<?> 
   *  Get  MAC addres
  */
	
	HOST_APP_MSG_ID_E rxMsgId;	

	/* Construct the AT command */
	sprintf(at_cmd_buf,"AT+NMAC=?\r\n");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E
AtLibGs_CalcNStorePSK(INT8 *pSsid, INT8 *pPsk)
{/* AT+WPAPSK=<SSID>,<PassPhrase>
   *  Calculate and store the PSK
   */
	HOST_APP_MSG_ID_E   rxMsgId;

	/* Construct the AT command */
    sprintf(at_cmd_buf,"AT+WPAPSK=%s,%s\r\n",pSsid,pPsk);
   
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E 
AtLibGs_WlanConnStat(void)
{/* AT+NSTAT=?
  *  Display current network context
  */

	HOST_APP_MSG_ID_E   rxMsgId;

	/* Construct the AT command */
	sprintf(at_cmd_buf,"AT+NSTAT=?\r\n");
		
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();
	
	return rxMsgId;
}


HOST_APP_MSG_ID_E
AtLibGs_DHCPSet(UINT8 mode)
{     
   HOST_APP_MSG_ID_E   rxMsgId;

   /* Construct the AT command */
   sprintf(at_cmd_buf,"AT+NDHCP=%d\r\n",mode);
   
   /* Send command to S2w App node */
   rxMsgId = AtLib_CommandSend();
	
   return rxMsgId;
}

HOST_APP_MSG_ID_E AtLibGs_Assoc(INT8 *pSsid, INT8 *pBssid,INT8 *pChan)
{/*  AT+WA=<SSID>[[,<BSSID>][,<Ch>]]
  *  Associate to network or form ad-hoc network
  */
   
	HOST_APP_MSG_ID_E	rxMsgId;
	
	if (pChan)
	{
		 sprintf(at_cmd_buf,"AT+WA=%s,%s,%s\r\n",pSsid, (pBssid)? pBssid:"" ,pChan); 
	 
	}
	else
	{		
		 sprintf(at_cmd_buf,"AT+WA=%s\r\n",pSsid);
	}

	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();
	
	return rxMsgId;
}

HOST_APP_MSG_ID_E AtLibGs_TcpClientStart(INT8 *pRemoteTcpSrvIp,INT8 *pRemoteTcpSrvPort)
{ /*  AT+NCTCP=<IP>,<Port>
   *  Open TCP client
   */
	HOST_APP_MSG_ID_E	rxMsgId;

	sprintf(at_cmd_buf,"AT+NCTCP=%s,%s\r\n",pRemoteTcpSrvIp,pRemoteTcpSrvPort); 
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();
	
	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_UdpClientStart(INT8 *pRemoteUdpSrvIp,INT8  *pRemoteUdpSrvPort,INT8 *pUdpLocalPort)
{/*  AT+NCUDP=<IP>,<RemotePort>,[<LocalPort>]
   *   Open UDP client
   *
   */
	HOST_APP_MSG_ID_E	rxMsgId;

	sprintf(at_cmd_buf,"AT+NCUDP=%s,%s,%s\r\n",pRemoteUdpSrvIp,pRemoteUdpSrvPort,pUdpLocalPort);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();
	
	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_CloseAll(void)
{/* AT+NCLOSEALL
   *  Close all connections
   */
	HOST_APP_MSG_ID_E rxMsgId;

       sprintf(at_cmd_buf,"AT+NCLOSEALL\r\n"); 

	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_BatteryChkStart(UINT32 interval)
{/*  AT+BCHKSTRT=<Measure interval>
   *   Start the batt check
  */
    HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+BCHKSTRT=%d\r\n",interval);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E
AtLibGs_GotoSTNDBy(INT8 *nsec, UINT32 dealy , UINT32 alarm1_Pol, UINT32 alarm2_Pol)
{
    HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+PSSTBY=%s,%d,%d,%d\r\n", nsec,dealy,alarm1_Pol,alarm2_Pol);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
	
}

HOST_APP_MSG_ID_E
AtLibGs_SetPassPhrase(INT8 *pPhrase )
{
	HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+WWPA=%s\r\n",pPhrase);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_EnableDeepSleep(void)
{
    HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+PSDPSLEEP\n");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_StoreNwConn(void)
{
	 HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+STORENWCONN\r\n");
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_ReStoreNwConn(void)
{
	 HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+RESTORENWCONN\r\n");
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
	
}

HOST_APP_MSG_ID_E
AtLibGs_IPSet(INT8* pIpAddr,INT8* pSubnet, INT8 *pGateway)
{
	HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+NSET=%s,%s,%s\r\n",pIpAddr,pSubnet,pGateway);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E
AtLibGs_SaveProfile(UINT8 mode)
{
   HOST_APP_MSG_ID_E rxMsgId;
   
	sprintf(at_cmd_buf,"AT&W%d\r\n",mode);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_LoadProfile(UINT8 mode)
{
	HOST_APP_MSG_ID_E rxMsgId;
   
	sprintf(at_cmd_buf,"ATZ%d\r\n",mode);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

/* Restore Factory Defaults */
HOST_APP_MSG_ID_E
AtLibGs_ResetFctDflts(void)
{
	HOST_APP_MSG_ID_E rxMsgId;
   
	sprintf(at_cmd_buf,"AT&F\r\n");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

/*Get the RSSI value */
HOST_APP_MSG_ID_E
AtLibGs_GetRssi(void)
{
	HOST_APP_MSG_ID_E rxMsgId;
   
	sprintf(at_cmd_buf,"AT+WRSSI=?\r\n");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E
AtLibGs_DisAssoc(void)
{
	HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+WD\r\n");
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_FWUpgrade(INT8 *pSrvip, UINT32  srvport,UINT32  srcPort, INT8 *pSrcIP )
{
	HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+FWUP=%s,%d,%d,%s\r\n",pSrvip,srvport,srcPort,pSrcIP);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_BatteryChkStop(void)
{
	HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+BCHKSTOP\r\n");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
	
}

HOST_APP_MSG_ID_E
AtLibGs_MultiCast(UINT8 mode)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+MCSTSET=%d\r\n",mode);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}



HOST_APP_MSG_ID_E
AtLibGs_Version(void)
{
	HOST_APP_MSG_ID_E rxMsgId;

	sprintf(at_cmd_buf,"AT+VER=?\r\n");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_Mode(UINT32 mode)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+WM=%d\r\n",mode);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId; 
}


HOST_APP_MSG_ID_E
AtLibGs_UdpServer_Start(INT8 *pUdpSrvPort)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+NSUDP=%s\r\n",pUdpSrvPort);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;  
}


HOST_APP_MSG_ID_E
AtLibGs_TcpServer_Start(INT8* pTcpSrvPort, INT8 *pConnId)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+NSTCP=%s\r\n",pTcpSrvPort);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
   
}

HOST_APP_MSG_ID_E
AtLibGs_DNSLookup(INT8* pUrl)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+DNSLOOKUP=%s\r\n",pUrl);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_Close(UINT8 cid )
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+NCLOSE=%c\r\n",cid);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_SetWRetryCount (UINT32 count)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+WRETRY=%d\r\n",count);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
	
}

HOST_APP_MSG_ID_E
AtLibGs_GetErrCount (void)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+ERRCOUNT=?\r\n");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_EnableRadio (UINT8 mode)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+WRXACTIVE=%d\r\n",mode);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}
	
HOST_APP_MSG_ID_E
AtLibGs_EnablePwSave (UINT8 mode)
{
	HOST_APP_MSG_ID_E rxMsgId;
	

	sprintf(at_cmd_buf,"AT+WRXPS=%d\r\n",mode);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E 
AtLibGs_SetTime ( INT8* pDate, INT8 *pTime)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+SETTIME=%s,%s\r\n",pDate,pTime);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E 
AtLibGs_EnableExternalPA(void )
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+EXTPA=1\r\n");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E 
AtLibGs_SyncLossInterval( UINT8 interval)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+WSYNCINTRL=%d\r\n",interval);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E 
AtLibGs_PSPollInterval( UINT8 interval)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+PSPOLLINTRL=%d\r\n",interval);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E 
AtLibGs_SetTxPower(UINT32 power)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+WP=%d\r\n",power);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E 
AtLibGs_SetDNSServerIP( INT8 *pDNS1 ,INT8 *pDNS2 )
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	if (pDNS2 == NULL)
	{
		sprintf (at_cmd_buf,"AT+DNSSET=%s",pDNS1);
	}
	else
	{
		sprintf (at_cmd_buf,"AT+DNSSET=%s,%s",pDNS1,pDNS2);

	}

	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
	
}

HOST_APP_MSG_ID_E
AtLibGs_EnableAutoConnect(UINT8 mode)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"ATC%d\r\n",mode);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


void
AtLibGs_SwitchFromAutoToCmd(void )
{
    UINT32 command_length;
	
	sprintf(at_cmd_buf,"+++");
	/* Get the command length */
    command_length = strlen((const char *)at_cmd_buf);

	#ifdef HOST_APP_INTERFACE_SPI
	   PIC24_MasterSpiTransfer((UINT8 *)&at_cmd_buf[0],MRBuffer,command_length);
	#else
	   BSP_Uart_Send((UINT8 *)&at_cmd_buf[0],command_length);
	#endif
	
	my_delay_ms(1000);

	sprintf(at_cmd_buf,"\r\n");
    command_length = strlen((const char *)at_cmd_buf);
   
	#ifdef HOST_APP_INTERFACE_SPI
	  PIC24_MasterSpiTransfer((UINT8 *)&at_cmd_buf[0],MRBuffer,command_length);
	#else
	  BSP_Uart_Send((UINT8 *)&at_cmd_buf[0],strlen(at_cmd_buf));
	#endif
	
}



HOST_APP_MSG_ID_E
AtLibGs_StoreWAutoConn( INT8 * pSsid, UINT8 channel)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+WAUTO=0,%s,,%d\r\n",pSsid,channel);
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_StoreNAutoConn(INT8* pIpAddr,INT8* pRmtPort)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+NAUTO=0,0,%s,%s\r\n",pIpAddr,pRmtPort);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E
AtLibGs_StoreATS(UINT8 param,UINT8 time)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"ATS%d=%d\r\n",param,time);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E
AtLibGs_BData(UINT32 mode)
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+BDATA=%d\r\n",mode);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

HOST_APP_MSG_ID_E 
AtLibGs_StartWPSPUSH(void )
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf(at_cmd_buf,"AT+WWPS=1");
	
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}


HOST_APP_MSG_ID_E 
AtLibGs_StartWPSPIN(UINT32 pin )
{
	HOST_APP_MSG_ID_E rxMsgId;
	
	sprintf (at_cmd_buf,"AT+WWPS=2,%d",pin);
	/* Send command to S2w App node */
	rxMsgId = AtLib_CommandSend();

	return rxMsgId;
}

/*----------------<End of GS AT command library >------------------------------*/

/*****************< AT command response parsing functions >******************/

UINT8 AtLib_ParseTcpClientCid(void)
{
	UINT8  cid;
	UINT8  *result = NULL;

	if ((result=(UINT8  *)strstr((const char *)MRBuffer,"CONNECT" )) !=NULL )
	{
		/* Succesfull connection done for TCP client */
		cid = result[HOST_APP_TCP_CLIENT_CID_OFFSET_BYTE];
	}
	else
	{
		/* Not able to extract the CID */
		cid = HOST_APP_INVALID_CID;
	}

	return cid;
}

UINT8 
AtLib_ParseUdpClientCid(void)
{
UINT8 cid;
UINT8  *result = NULL;

if ((result=(UINT8  *)strstr((const char *)MRBuffer,"CONNECT" )) !=NULL )
{/* Succesfull connection done for UDP client */
	cid = result[HOST_APP_UDP_CLIENT_CID_OFFSET_BYTE];
}
else
{/* Not able to extract the CID */
	cid = HOST_APP_INVALID_CID;
}

  return cid;
}


UINT8 
AtLib_ParseWlanConnStat(void)
{
  char *pSubStr;

	/*check whether response message contains the following string "BSSID=00:00:00:00:00:00" */
    pSubStr = strstr((const char *)MRBuffer,"BSSID=00:00:00:00:00:00");

	if(pSubStr)
	{//Not been associated 
	    return FALSE;
	}
	else
	{//Already associated
       return TRUE;
	}
}


UINT8 
AtLib_ParseGetMacResponse(UINT8 *pRefNodeMacId)
{
	char *pSubStr;
	char currNodeMac[20]="00:00:00:00:00:00";
		
	/*Set the node MAC address, If the MAC is already set,then skip the flash write operation */
	pSubStr=strstr((const char *)MRBuffer,":");
	
	if (pSubStr)
	{
		/* 00:00:00:01:01:01 */
		memcpy(currNodeMac,(pSubStr-2),17);
		currNodeMac[17] = '\0';

		if(AtLib_strcasecmp((const char *)currNodeMac,(const char *)pRefNodeMacId) !=0 )
		{// MAC address  not matching
		
			return FALSE;
		}
		else
		{//Already confugred , No need to configure the MAC address 
				
           return  TRUE;
		}
	}
	else
	{//Failed to get MAC address information
	
		 return FALSE;
	}

}


/*
  This function shall be called , after getting response for "AT+NSTAT=?" command.
  (This API shall be used in conjuction with 'AtLibGs_WlanConnStat()) API )
  
   Return parameter:
              0: If response buffer does not contain valid IP address
              1 : If  response buffer contains valid IP address and its updated in pIpAddr

*/
UINT8
AtLib_ParseNodeIpAddress(UINT8 *pIpAddr)
{
   char *pSubStr;

	pSubStr=strstr((const char *)MRBuffer,"IP addr=");
	if (pSubStr)
	{
		strcpy((char *)pIpAddr,strtok((pSubStr+8),": " ));
		if( pIpAddr[0]=='0' )
		{
			pIpAddr = NULL;

			return 0; /* Failed */
		}
	}
	else
	{
		return 0; /* Failed */
	}

  return 1; /* Success */
  
}


/*
  This function shall be called , after getting response for "AT+NSTAT=?" command.
  (This API shall be used in conjuction with 'AtLibGs_WlanConnStat()) API )
  
   Return parameter:
              0: If response buffer does not contain valid RSSI
              1 : If  response buffer contains valid RSSI and its updated in pRssi

*/

UINT8
AtLib_ParseRssiResponse(UINT16 *pRssi)
{
   char *pSubStr;

	if( (pSubStr = strstr((const char *)MRBuffer,"-")) != NULL)
	{
		*pRssi= atoi((pSubStr));
		
		return 1;
	}
	else
	{
		return 0;
	}
}


UINT8
AtLib_ParseUdpServerStartResponse(UINT8 *pConnId)
{

	char * result = NULL;

	if( (result=strstr((const char *)MRBuffer,"CONNECT")) != NULL )
	{
		*pConnId= result[8];
		
		return 1; /* Success */
	}
	else if ( ((result = strstr((const char *)MRBuffer,"DISASSOCIATED" )) !=NULL) ||
				(strstr((const char *)MRBuffer,"SOCKET FAILURE") != NULL ))
	{
		return 0; /* Failed  */
	}
	else
	{
		return 0; /* Failed  */
	}
	
}

UINT8
AtLib_ParseTcpServerStartResponse(UINT8 *pConnId)
{
	char* pSubStr = NULL;

	if( (pSubStr=strstr((const char *)MRBuffer,"CONNECT")) != NULL  )
	{
		*pConnId= pSubStr[8];
		return 1;/* Success */
	}
	else if ( ((strstr((const char *)MRBuffer,"DISASSOCIATED" )) !=NULL) ||
               (strstr((const char *)MRBuffer,"SOCKET FAILURE") != NULL) )
	{
		return 0; /* Failed  */
	}
	else
	{
		return 0; /* Failed  */
	}

}

UINT8
AtLib_ParseDNSLookupResponse(char *ipAddr)
{
	char *pSubStr = NULL;

	pSubStr = strstr((const char *)MRBuffer,"IP:");
	if( pSubStr )
	{
		strcpy(ipAddr,(pSubStr+3));
		
		return 1; /* Success */
	}
	else
	{
		return 0; /* Failed  */
	}
}

UINT8
AtLib_ParseWPSPUSHResponse(void)
{
	if ( strstr((const char *)MRBuffer,"SSID=") != NULL )
	{
		return 1;	 /* Success */
	}
	else
	{
		return 0;  /* Failed  */
	}
}


UINT8
AtLib_ParseWPSPINResponse(UINT32 pin )
{
	if ( strstr((const char *)MRBuffer,"SSID=") != NULL )
	{
		return 1;	 /* Success */
	}
	else
	{
		return 0;  /* Failed  */
	}
}

/*****************< End of AT command response parsing functions >******************/



/*-----------------< Helper functions >----------------------------------------*/
#ifdef HOST_APP_INTERFACE_SPI

/**
*****************************************************************************
* @brief         byte-stuffing transmit data
*			If transmit byte is an Escape charcter , then  transmit byte is XOR'd with 0x20
*			
* param pNextData - IN pointer to transmit data 
*
* returns	         FALSE- Byte stuffing is NOT applied
*		         TRUE - Byte stuffing is applied 
* Algorithm: Transmitter eliminates the flags (XOFF,XON,IDLE,ESCAPE)  from the data payload 
*                   using the following operation: everywhere that flag appears in the data it is 
*                    replaced with the two-character sequence [0xFB], [data XOR 0x20].
*                    0xFB  is called the Control Escape byte. 
*
*Note - The "byte-stuffing" is done "on the fly" . The extra byte inserted by the byte stuffing 
*             procedure will not effect  the buffer size needed to hold a message.
*             By "on the fly" means, as each byte is fetched  from the transmission buffer to be 
*             sent, examine it to see if it needs to be expanded into two bytes and if so transmit
*             two bytes instead of one.
************************************* ****************************************/
UINT8
AtLib_SpiByteStuff(UINT8 *pNextData)
{
 UINT8 byteStuffFlag=FALSE;

   switch(*pNextData)
 	{
		case HOST_APP_SPI_IDLE_CHAR:
		case HOST_APP_SPI_XOFF_CHAR:
		case HOST_APP_SPI_XON_CHAR:
		case HOST_APP_SPI_INVALID_CHAR_ALL_ONE:
		case HOST_APP_SPI_INVALID_CHAR_ALL_ZERO:
		case HOST_APP_SPI_READY_ACK:
		case HOST_APP_SPI_ESC_CHAR:
			
			/* Byte stuffing is required */
			*pNextData = *pNextData ^ 0x20;
			byteStuffFlag= TRUE;
		    break;
			
		default:
			/* We can send the data without byte-stuffing */
			byteStuffFlag=FALSE;
			break;
 	}

	return byteStuffFlag;

}


/**
*****************************************************************************
* @ingroup atLib_SpiByteDeStuff
* @brief Un-stuffing recieved data
*			If recieved byte is an Escape charcter , then  next  byte is XOR'd with 0x20
*
* @param pNextData - IN pointer to recieved data
* @returns	  
*                HOST_APP_RET_STATUS_CONTROL_CODE  ==> If control bytes recieved
*                HOST_APP_RET_STATUS_VALID_DATA       ==> If valid data recieved
*
* @Algorithm:  The receiver performs the reverse process: whenever it sees the
*                    Control Escape value(0xFB) it discards that byte and XORs the
*                    following byte with 0x20 to recreate the original input.
*
* @Note - The byte stuffing is undone before the received bytes are stored in the receive
*              buffer. The extra bytes inserted by the byte stuffing do not effect the size of
*              the receive buffer needed.
*
************************************* ****************************************/
HOST_APP_RET_STATUS_E
AtLib_SpiByteDeStuff(UINT8 *pNextData)
{
	UINT8 rxData;
	UINT8 txData;
	HOST_APP_RET_STATUS_E return_status=HOST_APP_RET_STATUS_ERROR;
	
  switch(*pNextData)
  	{
	  case HOST_APP_SPI_IDLE_CHAR:
	  case HOST_APP_SPI_XOFF_CHAR:
	  case HOST_APP_SPI_XON_CHAR:
	  case HOST_APP_SPI_INVALID_CHAR_ALL_ONE:
	  case HOST_APP_SPI_INVALID_CHAR_ALL_ZERO:
	  case HOST_APP_SPI_READY_ACK:
	  	   return_status=HOST_APP_RET_STATUS_CONTROL_CODE; /* Control bytes recieved. */
		   break;

	  case HOST_APP_SPI_ESC_CHAR:/* Byte de-stuffing is required */
	 		{
				txData=HOST_APP_SPI_IDLE_CHAR; /* Idle fill byte */
				
				/* Need to get the next byte  */				
				PIC24_MasterSpiTransfer(&txData,&rxData,1);

				*pNextData = rxData ^ 0x20;	/* apply byte de-stuffing */

				return_status=HOST_APP_RET_STATUS_VALID_DATA; /* Valid data present */
			}
			break;

	 default:
	 		return_status=HOST_APP_RET_STATUS_VALID_DATA;  /* Valid data present */
	 	break;
			
  	}


   return return_status;

}/* AtLib_SpiByteDeStuff */
#endif

HOST_APP_MSG_ID_E  AtLib_CommandSend(void)
{
/*  Note: 
 *          1.  Byte stuffing is NOT required for 'AT' commands. Since 'AT' command contains only 7 bit ASCII characters 
 *          2.  If AT command parameter contains below listed octets,  then byte stuffing must be applied.
 *               0x00, 0xF3,0xF5,0xFA,0xFB,0xFD,0xFF   (all values are in HEX)
 */


	UINT32    command_length;
	HOST_APP_MSG_ID_E rxMsgId;

	/* Get the command length */
	command_length = strlen((const char *)at_cmd_buf);
	
	/* Send command in blocking data*/
	BSP_Uart_Send((UINT8*)&at_cmd_buf[0],command_length);
	rxMsgId = AtLib_ResponseHandle();

	return rxMsgId;
}


void 
AtLib_DataSend(UINT8 *pTxData,UINT32 dataLen)
{
 
#ifdef HOST_APP_INTERFACE_SPI

/*	 Note: 
*		 1. In case of SPI interfface, byte stuffing is required, if user data contains binary data
*		 2. In general, if user data contains following octets,  then byte stuffing must be applied.
*			 0x00, 0xF3,0xF5,0xFA,0xFB,0xFD,0xFF   (all values are in HEX)
*/

    UINT32 writeIndex=0;
	UINT8 rxData=0;
	UINT8 escByte;

	escByte = HOST_APP_SPI_ESC_CHAR;
	for(writeIndex=0;writeIndex< dataLen;writeIndex++)
	{
		/* Check whether byte stuffing is required or not */
		if(TRUE == AtLib_SpiByteStuff(pTxData))
		{
		    /*If byte stuffing required, then first send the ESCAPE octet */
			PIC24_MasterSpiTransfer(&escByte,&rxData,1);
		}

		/* Now send the data */
		PIC24_MasterSpiTransfer(pTxData,&rxData,1);

		/* Process the recieved async messages if any */
		AtLib_RecieveDataProcess(rxData);
		
		pTxData++;
	}
#else
	 BSP_Uart_Send(pTxData,dataLen);
#endif

}


/*
    Data transfer format for TCP server, TCP client :
    ___________________________________________
    | ESC | 'S' | CID | User data  N bytes  | ESC | 'E'  |
     ___________________________________________
  
*/
void
AtLib_SendTcpData( UINT8 cid,UINT8 *txBuf, UINT32 dataLen)
{/* <ESC> < S>  <cid>  <data> <ESC> < E>  */

	UINT32 command_length=0;
   
if(HOST_APP_INVALID_CID != cid )
{
	/***********< send START sequence >********************/
	
	/* Construct the data start indication message  */		
	 sprintf ( at_cmd_buf,"%c%c%c",HOST_APP_ESC_CHAR,'S',cid);
	 /* Get the command length  */
	 command_length = strlen(at_cmd_buf); 
	
	/* Now send the data START indication message  to S2w node */
	#ifdef HOST_APP_INTERFACE_SPI
	  PIC24_MasterSpiTransfer((UINT8 *) &at_cmd_buf[0],MRBuffer,command_length);
	  /* Process the  recieved data */
	  AtLib_ProcessRxChunk(MRBuffer,command_length);
	#else
      BSP_Uart_Send((UINT8 *) &at_cmd_buf[0],command_length);
	#endif

	/* wait for GS1011 to process above command LeZ */
	my_delay_ms(1000);
			
	/***********< send actual data > *********************/	
	/* Now send the actual data */
	AtLib_DataSend( txBuf,dataLen);

	/***********< send STOP sequence >********************/
	
	/* Construct the data start indication message  */
	
	sprintf ( at_cmd_buf,"%c%c",HOST_APP_ESC_CHAR,'E');
	/* Get the command length */
	command_length = strlen(at_cmd_buf); 
	
	/* Now send the data END indication message  to S2w node */
	#ifdef HOST_APP_INTERFACE_SPI
	  PIC24_MasterSpiTransfer((UINT8 *)&at_cmd_buf[0],MRBuffer,command_length);
	#else
      BSP_Uart_Send((UINT8 *) &at_cmd_buf[0],command_length);
	#endif 
	
	  /* Process the  recieved data */
	  AtLib_ProcessRxChunk(MRBuffer,command_length);
}

}


/*
    Data transfer format for  UDP client:
    ___________________________________________
    | ESC | 'S' | CID | User data  N bytes  | ESC | 'E'  |
     ___________________________________________

      Data transfer format for UDP server:
    _______________________________________________________________________
    | ESC | 'U' | CID |IP ADDRESS|:| PORT NUMBER | User data  N bytes  | ESC | 'E'  |
     ______________________________________________________________________

     
*/
void
AtLib_SendUdpData(UINT8 cid,UINT8 *txBuf, UINT32 dataLen,
                        HOST_APP_CON_TYPE conType , UINT8 *pUdpClientIP, UINT8 *pUdpClientPort)
{

	UINT32 command_length=0;
   
if(HOST_APP_INVALID_CID != cid )
{
	/***********< send START sequence >********************/
	
	/* Construct the data start indication message  */
	if(HOST_APP_CON_UDP_SERVER == conType)
	{/* <ESC> < U>  <cid> <ip address><:> <port numer><:> <data> <ESC> < E>  */
		sprintf ( at_cmd_buf,"%c%c%c%s:%s:",HOST_APP_ESC_CHAR,'U',cid,pUdpClientIP,pUdpClientPort);
	}
	else
	{/* <ESC> < S>  <cid>  <data> <ESC> < E>  */
	
		sprintf ( at_cmd_buf,"%c%c%c",HOST_APP_ESC_CHAR,'S',cid);
	}
	
	 /* Get the command length  */
	 command_length = strlen(at_cmd_buf); 
	
	/* Now send the data START indication message  to S2w node */
	#ifdef HOST_APP_INTERFACE_SPI
	  PIC24_MasterSpiTransfer((UINT8 *) &at_cmd_buf[0],MRBuffer,command_length);	  
	  /* Process the  recieved data */
	  AtLib_ProcessRxChunk(MRBuffer,command_length);
	#else
      BSP_Uart_Send((UINT8 *) &at_cmd_buf[0],command_length);
	#endif
	
	/* wait for GS1011 to process above command LeZ */
	my_delay_ms(1000);
	
	/***********< send actual data > *********************/	
	/* Now send the actual data */
	AtLib_DataSend( txBuf,dataLen);

	/***********< send STOP sequence >********************/
	
	/* Construct the data start indication message  */
	
	sprintf ( at_cmd_buf,"%c%c",HOST_APP_ESC_CHAR,'E');
	/* Get the command length */
	command_length = strlen(at_cmd_buf); 
	
	/* Now send the data END indication message  to S2w node */
	#ifdef HOST_APP_INTERFACE_SPI
	  PIC24_MasterSpiTransfer((UINT8 *)&at_cmd_buf[0],MRBuffer,command_length);
	#else
      BSP_Uart_Send((UINT8 *) &at_cmd_buf[0],command_length);
	#endif
		  	  
	  /* Process the recieved data */
	  AtLib_ProcessRxChunk(MRBuffer,command_length);	
}
	
}



/*
   Bulk data transfer format:
    ____________________________________________________________________________
    | ESC | 'Z' | CID | Data length fixed 4 ASCII Characters| User data  N bytes  | ESC | 'E'  |
     ____________________________________________________________________________

     Where , Data Length <= 1400 bytes
     
*/

void 
AtLib_BulkDataTransfer (UINT8 cid,UINT8 *pData, UINT32 dataLen)
{ /*<Esc> <Z> <Cid> <Data Length xxxx 4 ascii char> <data>     */

	UINT32 command_length;
    INT8  asciDigits[5];
	
	/***********< send START sequence >********************/
	 /* Construct the bulk data start indication message  */
     // To send bulk data, the format is "<ESC>Z<cid><data length in 4 digits>DATA"

	 AtLib_ConvertNumberTo4DigitASCII(dataLen,asciDigits);
     sprintf ( &(at_cmd_buf[0]),"%c%c%c%s",HOST_APP_ESC_CHAR,'Z',cid, asciDigits); 
     
     command_length = strlen(at_cmd_buf); /* Get command length */

	/* Now send the bulk data START indication message  to S2w node */
	#ifdef HOST_APP_INTERFACE_SPI
	    PIC24_MasterSpiTransfer((UINT8 *) &at_cmd_buf[0],MRBuffer,command_length);
	#else
	   BSP_Uart_Send((UINT8 *) &at_cmd_buf[0],command_length);
	   /* wait for GS1011 to process above command LeZ */
	   my_delay_ms(1000);
	#endif

	/* Now send the actual data */
	#ifdef HOST_APP_INTERFACE_SPI	 
	   PIC24_MasterSpiTransfer(pData,MRBuffer,dataLen);
	#else  // UART
	   BSP_Uart_Send(pData,dataLen);
	#endif
	
	   /* Process if any pending async messages from S2w App Node*/
	   AtLib_RecieveDataHandle();
}


/*
 This functions is used to check the completion of Commands
 This function will be called after receiving each line.
*/
HOST_APP_MSG_ID_E
AtLib_checkEOFMessage(UINT8 * pBuffer)
{

   
	if( (strstr((const char *)pBuffer,"OK") != NULL) )
	{
		return HOST_APP_MSG_ID_OK;
	}
	else if( (strstr((const char *)pBuffer,"ERROR") != NULL) )
	{
		 return HOST_APP_MSG_ID_ERROR;
	}
	else if (  (strstr((const char *)pBuffer,"INVALID INPUT") != NULL))                                                          
	{
		return HOST_APP_MSG_ID_INVALID_INPUT;
	}
	else if ( (strstr((const char *)pBuffer,"DISASSOCIATED") !=NULL) )                                                          
	{
		/* Reset the local flags */
	    AtLib_ClearNodeAssociationFlag();
		AtLib_ClearAllCid();
		
		return HOST_APP_MSG_ID_DISASSOCIATION_EVENT;
	}
	else if ((strstr((const char *)pBuffer,"ERROR: IP CONFIG FAIL") !=NULL))                                                        
	{
		return HOST_APP_MSG_ID_ERROR_IP_CONFIG_FAIL;
		
	}
	else if ( strstr((const char *)pBuffer,"ERROR: SOCKET FAILURE") !=NULL)                                                           
	{
		/* Reset the local flags */
		AtLib_ClearAllCid();
		
		return HOST_APP_MSG_ID_ERROR_SOCKET_FAIL;
	}
	else if ((strstr((const char *)pBuffer,"APP Reset-APP SW Reset")) != NULL)
	{
		/* Reset the local flags */
		AtLib_ClearNodeAssociationFlag();
		AtLib_SetNodeResetFlag();
		AtLib_ClearAllCid();
		
		return HOST_APP_MSG_ID_APP_RESET;
	}
	else  if(((UINT8 *)strstr((const char *)pBuffer,"DISCONNECT")) != NULL)
	{
		/* Reset the local flags */
		AtLib_ClearAllCid();
		
		return HOST_APP_MSG_ID_DISCONNECT;
	}
	else if((strstr((const char *)pBuffer,"Disassociation Event")) != NULL)
	{
		/* reset the association flag */
		AtLib_ClearNodeAssociationFlag();
		AtLib_ClearAllCid();
		
		return HOST_APP_MSG_ID_DISASSOCIATION_EVENT;
	}
	else if ((strstr((const char *)pBuffer,"Out of StandBy-Alarm") )!= NULL)
	{
		return HOST_APP_MSG_ID_OUT_OF_STBY_ALARM;
	}
	else if ((strstr((const char *)pBuffer,"Out of StandBy-Timer")) != NULL)
	{
		return HOST_APP_MSG_ID_OUT_OF_STBY_TIMER;
		
	}
	else if ((strstr((const char *)pBuffer,"UnExpected Warm Boot")) != NULL)
	{
		/* Reset the local flags */
		AtLib_ClearNodeAssociationFlag();
		AtLib_SetNodeResetFlag();
		AtLib_ClearAllCid();
		
		return HOST_APP_MSG_ID_UNEXPECTED_WARM_BOOT;
		
	}
	else if ((strstr((const char *)pBuffer,"Out of Deep Sleep")) != NULL)
	{
		return HOST_APP_MSG_ID_OUT_OF_DEEP_SLEEP;
	}
	else if ((strstr((const char *)pBuffer,"Serial2WiFi APP")) != NULL)
	{
	    /* Reset the local flags */
		AtLib_ClearNodeAssociationFlag(); 
		AtLib_SetNodeResetFlag();
		AtLib_ClearAllCid();
		
		return HOST_APP_MSG_ID_WELCOME_MSG;
	}
	else if (  (pBuffer[0] == 'A') && (pBuffer[1]=='T')  && ( pBuffer[2]=='+')  )
	{/* Handle the echoed back AT Command, if Echo is enabled.  "AT+" . */
		return HOST_APP_MSG_ID_NONE; 
	}

	return HOST_APP_MSG_ID_NONE; 

}

void AtLib_RecieveDataHandle(void)
{/* Note: This function can be called from ISR, if host wake-up GPIO interrupt is supported.
   *           
   *      Care must be taken to synchronise data transfer, since it works in full-duplex mode.
   *      For demo purpose we are calling from single context.
   *
   */
	
	UINT8 rxData;

	while( UART_YES_DATA == BSP_Uart0_Read(&rxData,1))  /* Read one byte at a time - Use  non-blocking call  */
	{
		/* Process the recieved data */
		AtLib_RecieveDataProcess(rxData);
	}
}



HOST_APP_MSG_ID_E  AtLib_RecieveDataProcess(UINT8 rxData)
{/* recieve data handling state */
	
	static HOST_APP_RX_STATE_E recieve_state = HOST_APP_RX_STATE_START;
	static UINT32 specialDataLen             = 0;
	static UINT8 rxCurrentCid                = 0;
	static UINT8 prevChar                    = 0;
	static UINT8 specialDataLenCharCount     = 0;
	

	HOST_APP_MSG_ID_E    rxMsgId = HOST_APP_MSG_ID_NONE;

	 
	/* Process the recieved data */
	switch(recieve_state)
	{
		case HOST_APP_RX_STATE_START:
		{
			switch(rxData)
			{
				case HOST_APP_CR_CHAR:
				case HOST_APP_LF_CHAR:
				{
					/* CR and LF at the begining, just ignore it */
					MRBufferIndex    = 0;
				}
				break;
				
				case HOST_APP_ESC_CHAR:
				{
					/* ESCAPE sequence detected */				
					recieve_state    = HOST_APP_RX_STATE_ESCAPE_START;						
					MRBufferIndex    = 0;	
					specialDataLen   = 0;
					rxCurrentCid     = 0;						
				}
				break;
						
				default:
				{ 
					/* Not start of ESC char, not start of any CR or NL */
					MRBufferIndex    = 0;
					MRBuffer[MRBufferIndex] = rxData;
					MRBufferIndex++;
					recieve_state = HOST_APP_RX_STATE_CMD_RESP;//收到数据便表示返回OK
				}
				break;
			}
		}
		break;
		
		case HOST_APP_RX_STATE_CMD_RESP:
		{
			if(HOST_APP_LF_CHAR == rxData)
			{
				/* LF detected - Messages from S2w node are terminated with LF/CR character */
				MRBuffer[MRBufferIndex] = rxData;
				// terminate string with NULL for strstr()
				MRBufferIndex++;
				MRBuffer[MRBufferIndex]= '\0';
				// 判断整个字符串的命令类型
				rxMsgId = AtLib_checkEOFMessage(MRBuffer);
				
				/* command echo or end of response detected */
				if(HOST_APP_MSG_ID_NONE != rxMsgId)
				{
					/* Now reset the  state machine */
					recieve_state = HOST_APP_RX_STATE_START;
				}
			}
			else if(HOST_APP_ESC_CHAR == rxData)
			{/* Defensive check - This should not happen */                           
				recieve_state    = HOST_APP_RX_STATE_START;						
			}
			else
			{
				MRBuffer[MRBufferIndex] = rxData; 
				MRBufferIndex++;

				if(MRBufferIndex >= HOST_APP_RX_CMD_MAX_SIZE )
				{/* Message buffer overflow. Something seriousely wrong. */	
					
					MRBufferIndex = 0;
					/* Now reset the  state machine */
					recieve_state	  = HOST_APP_RX_STATE_START;
				}
			}
		}
		break;
		
		case HOST_APP_RX_STATE_ESCAPE_START:
			if(HOST_APP_DATA_MODE_BULK_START_CHAR_H == rxData)
			{/* HTTP Bulk data handling start */
				
				/* <Esc>H<1 Byte - CID><4 bytes - Length of the data><data> */					 
				recieve_state     = HOST_APP_RX_STATE_HTTP_RESPONSE_DATA_HANDLE;
				specialDataLen    = 0;
				specialDataLenCharCount=0;
			}
			else if(HOST_APP_DATA_MODE_BULK_START_CHAR_Z == rxData)
			{/* Bulk data handling start */
				
				/* <Esc>Z<Cid><Data Length xxxx 4 ascii char><data>   */
				recieve_state     = HOST_APP_RX_STATE_BULK_DATA_HANDLE;
				specialDataLen    = 0;
				specialDataLenCharCount=0;					
			}
			else if(HOST_APP_DATA_MODE_NORMAL_START_CHAR_S == rxData)
			{/* Start of data */
				
				/* ESC S  cid  <----data --- > ESC E  */
				recieve_state = HOST_APP_RX_STATE_DATA_HANDLE;
			}
			else if(HOST_APP_DATA_MODE_RAW_INDICATION_CHAR_COL == rxData)
			{/* Start of raw data  */

			  /* ESC R : datalen : <----data --- >
				 Unlike other data format, there is no ESC E at the end .
				 So extract datalength to find out the incoming data size */ 
				recieve_state = HOST_APP_RX_STATE_RAW_DATA_HANDLE;
				specialDataLen = 0;
			}				  
			else if(HOST_APP_DATA_MODE_ESC_OK_CHAR_O == rxData)
			{/* ESC command response OK
				
				* Note: No need to take any action. Its just an data reception acknowledgement S2w node
				*/
				recieve_state = HOST_APP_RX_STATE_START;
			}
			else if(HOST_APP_DATA_MODE_ESC_FAIL_CHAR_F == rxData)
			{/* ESC command response FAILED
				
				* Note: Error reported from S2w node, you can use it for debug purpose.
				*/
				recieve_state    = HOST_APP_RX_STATE_START;
			}
			else
			{/* ESC sequence parse error !  */
				
				/* Reset the recieve buffer */
				recieve_state    = HOST_APP_RX_STATE_START;
			}
			break;
			
		case HOST_APP_RX_STATE_DATA_HANDLE:
		{
			rxCurrentCid=rxData;
			prevChar=0x00;

			do
			{ /* keep recieving data till you get ESC E */

				BSP_Uart0_Read(&rxData, 1);/* Read one byte at a time - blocking call */

				if(HOST_APP_DATA_MODE_NORMAL_END_CHAR_E == rxData)
				{
					if(HOST_APP_ESC_CHAR == prevChar)
					{/* End of data detected */
						
						/* Reset the RX state machine */
						recieve_state    = HOST_APP_RX_STATE_START;
					}
					else
					{
						AtLib_ProcessIncomingData(rxCurrentCid,rxData);								
						prevChar= rxData;
					}						
				}
				else
				{
					AtLib_ProcessIncomingData(rxCurrentCid,rxData);								
					prevChar= rxData;
				}	
			}while(recieve_state != HOST_APP_RX_STATE_START);
		}
		break;

		case HOST_APP_RX_STATE_HTTP_RESPONSE_DATA_HANDLE:
		{
			rxCurrentCid= rxData; /* HTTP response CID */

			do
			{/* extracting  the rx data length*/
				
				BSP_Uart0_Read(&rxData, 1);/* Read one byte at a time - blocking call */

				specialDataLen = (specialDataLen * 10) + ((rxData) - '0');

				specialDataLenCharCount++;

			}while(specialDataLenCharCount < HOST_APP_HTTP_RESP_DATA_LEN_STRING_SIZE);


			/* Now read actual data */
			while(specialDataLen)
			{
				BSP_Uart0_Read(&rxData, 1);/* Read one byte at a time - blocking call */

				specialDataLen--;
				AtLib_ProcessIncomingData(rxCurrentCid,rxData);
			}
			recieve_state     = HOST_APP_RX_STATE_START;		
		}
		break;

		case HOST_APP_RX_STATE_BULK_DATA_HANDLE:
		{
			do
			{/* extracting	the rx data length*/

				BSP_Uart0_Read(&rxData, 1);/* Read one byte at a time - blocking call */

				specialDataLen = (specialDataLen * 10) + ((rxData) - '0');

				specialDataLenCharCount++;

			}while(specialDataLenCharCount < HOST_APP_BULK_DATA_LEN_STRING_SIZE);

			/* Now read actual data */
			while(specialDataLen)
			{
				specialDataLen--;
				AtLib_ProcessIncomingData(rxCurrentCid,rxData);
			}
			recieve_state     = HOST_APP_RX_STATE_START;
		}
		break;

		case HOST_APP_RX_STATE_RAW_DATA_HANDLE:
		   if(HOST_APP_DATA_MODE_RAW_INDICATION_CHAR_COL == rxData)
			{
			  specialDataLenCharCount=0;
			}
				
			/* Now reset the buffer and state machine */
			recieve_state     = HOST_APP_RX_STATE_START;					
			
			do
			{/* extracting	the rx data length*/

			   BSP_Uart0_Read(&rxData, 1);/* Read one byte at a time - blocking call */

				if (rxData != HOST_APP_DATA_MODE_RAW_INDICATION_CHAR_COL)
				{
					specialDataLen = (specialDataLen * 10) + ((rxData) - '0');

					specialDataLenCharCount++;
				}
			}while((rxData != HOST_APP_DATA_MODE_RAW_INDICATION_CHAR_COL) && (specialDataLenCharCount < HOST_APP_BULK_DATA_LEN_STRING_SIZE));

			/* Now read actual data */
			while(specialDataLen)
			{
				BSP_Uart0_Read(&rxData,1);/* Read one byte at a time - blocking call */

				specialDataLen--;
				AtLib_ProcessIncomingData(rxCurrentCid,rxData);
			}
			recieve_state = HOST_APP_RX_STATE_START;
			break;

		default:
			/* This case will not be executed */
			break;
	}
	return rxMsgId;
}


HOST_APP_MSG_ID_E  AtLib_ResponseHandle(void)
{
	HOST_APP_MSG_ID_E responseMsgId;
	
	UINT8   rxData;
	UINT32  waitCount = 0;

	/* Reset the recieve buffer */
	AtLib_FlushRxBuffer();
	
	/* Reset the message ID */
	responseMsgId = HOST_APP_MSG_ID_NONE;
	
	while(HOST_APP_MSG_ID_NONE == responseMsgId)
	{
		/* Read one byte at a time - non-blocking call, block here */
		if (BSP_Uart0_Read(&rxData, 1) == UART_YES_DATA)
		{
			/* Process the recieved data */
			responseMsgId = AtLib_RecieveDataProcess(rxData);
		}
		
		if(responseMsgId !=  HOST_APP_MSG_ID_NONE)
		{/* Message successfully recieved from S2w App node */
			waitCount=0;
			break;
		}
		waitCount++;
		if(waitCount >= HOST_APP_RESPONSE_TIMEOUT_COUNT )
		{
			waitCount=0;	
			break;
		}
	}
	return responseMsgId;
}

HOST_APP_MSG_ID_E
AtLib_ProcessRxChunk(UINT8 *rxBuf, UINT32 bufLen)
{
 HOST_APP_MSG_ID_E rxMsgId;

 	rxMsgId =  HOST_APP_MSG_ID_NONE;
		
	/* Parse the recieved data and check whether any valid message present in the chunk */
	while(bufLen)
	{
		/* Process the recieved data */
	    rxMsgId = AtLib_RecieveDataProcess(*rxBuf);
		if(rxMsgId !=  HOST_APP_MSG_ID_NONE)
		{/* Message recieved from S2w App node */
			break;
		}

		rxBuf++;
		
	  	bufLen--;
	}

	return rxMsgId ;

}





void AtLib_LinkCheck(void)
{/* This function will make sure that SPI interface is UP and able to communicate with GS1011 node */
#ifdef HOST_APP_INTERFACE_SPI

 UINT8 txData;
 UINT8 rxData;

   rxData = 0x00;
   txData = HOST_APP_SPI_IDLE_CHAR;

   /* Write HOST_APP_SPI_IDLE_CHAR byte and expect HOST_APP_SPI_IDLE_CHAR  from GS1011 */
   do
   	{
   		if(1 == PIC24_GetHostWakeUpStatus())
   		{
			PIC24_MasterSpiTransfer(&txData,&rxData,1);
			
   		}
		
   	}while(HOST_APP_SPI_IDLE_CHAR != rxData);
#endif

}


void AtLib_ReadBootUpMessage(void)
{/* This function will read initial boot-up message from S2w App node 
	*  No action taken on recieved message
	*/

	UINT8 rxData;

	while(UART_YES_DATA == BSP_Uart0_Read(&rxData,1));  /*  Read one byte at a time - blocking call */


}



UINT8
AtLib_IsNodeResetDetected(void)
{
	return nodeResetFlag;
}

void
AtLib_SetNodeResetFlag(void)
{
	nodeResetFlag=TRUE;
}

void
AtLib_ClearNodeResetFlag(void)
{
	nodeResetFlag=FALSE;
}


UINT8
AtLib_IsNodeAssociated(void)
{
	return nodeAssociationFlag;
}

void
AtLib_SetNodeAssociationFlag(void)
{
	 nodeAssociationFlag=TRUE;
}

void
AtLib_ClearNodeAssociationFlag(void)
{
	 nodeAssociationFlag=FALSE;
}

void
AtLib_SaveTcpCid(UINT8 cid)
{
   tcpClientCid = cid;
}

void
AtLib_SaveUdpCid(UINT8 cid)
{
   udpClientCid = cid;
}


void
AtLib_ClearAllCid(void)
{
  tcpClientCid = HOST_APP_INVALID_CID;
  udpClientCid = HOST_APP_INVALID_CID;
}

UINT8
AtLib_GetTcpCid(void)
{

   return tcpClientCid;

}

UINT8
AtLib_GetUdpCid(void)
{

   return udpClientCid;

}


INT32
AtLib_strcasecmp(const char *s1, const char *s2)
{
	const UINT8 *us1 = (const UINT8 *)s1, *us2 = (const UINT8 *)s2;

	while (tolower(*us1) == tolower(*us2)) 
	{
		if (*us1++ == '\0')
			return (0);
		us2++;
	}

	return (tolower(*us1) - tolower(*us2));
}


void 
AtLib_ConvertNumberTo4DigitASCII(UINT32 myNum, INT8 *pStr)
{/* Its equivalent of  sprintf("%04d",myNum) */

	/* TBD: Find better way to convert number to 4 digit ASCII value */

	UINT8	digit1 ;
	UINT8	digit2 ;
	UINT8	digit3 ;
	UINT8	digit4 ;

	digit1 = myNum/1000;
	digit2 = (myNum%1000)/100;
	digit3 = ((myNum%1000)%100)/10;
	digit4 = ((myNum%1000)%100)%10;

	sprintf(pStr,"%d%d%d%d",digit1,digit2,digit3,digit4);
	
}

void
AtLib_ProcessIncomingData(UINT8 cid, UINT8 rxData)
{
/* TBD:
           1. Application specific action shall be processed here
           2. One of the option is to save in temporary buffer and then process it later
           
*/

}

