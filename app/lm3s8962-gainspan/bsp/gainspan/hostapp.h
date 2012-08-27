/*
 * HostApp.h
 */

#ifndef HOST_APP_H_
#define HOST_APP_H_



/***************< S2w App Node  configuration parameters >*******************************/

/* some new tytpedefs */
typedef char INT8;
typedef unsigned char UINT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef int INT32;
typedef unsigned int UINT32;
typedef unsigned char u_char;

#define my_delay_ms(_x) BSP_Timer0_DelayMs(_x)

// define one of the interfaces
//#define  PIC24_PLATFORM_ENABLE         /* PIC24, (PIC24FJ128GA) Platform Enabled */
//#define  HOST_APP_INTERFACE_SPI         /* SPI interface is used for GS1011 S2w App communication */
#define  HOST_APP_INTERFACE_UART      /* UART interface is used for GS1011 S2w App communication */
//#define HOST_APP_DEBUG_ENABLE

/* MAC Address of the S2W Node  */
#define HOST_APP_GS_NODE_MAC_ID		 "00:1D:C9:01:01:D0"
/*AP SSID */
#define HOST_APP_AP_SSID 		     "gp"
#define HOST_APP_AP_PSWD 		     "chxg23@gmail.com"
/* Mention AP channel here. For auto channel, mention AP channel as NULL  */
#define HOST_APP_AP_CHANNEL 	       "1"

/* Uncomment the following macro to enable WPA PSK security */
//#define  HOST_APP_SEC_PSK
/* Specify the AP PSK here  */
//#define HOST_APP_AP_SEC_PSK 		"lestest"

/*Layer 3 Settings */
/* IP Address of the remote TCP Server */
#define HOST_APP_REMOTE_TCP_SRVR_IP     "192.168.3.1"
#define HOST_APP_REMOTE_TCP_SRVR_PORT   "8888"

/* IP Address of the remote UDP Server */
#define HOST_APP_REMOTE_UDP_SRVR_IP     "192.168.1.100"
#define HOST_APP_REMOTE_UDP_SRVR_PORT   "8010"
#define HOST_APP_NODE_LOCAL_UDP_PORT  	"9003"

/***************< End of S2w App Node configuration parameters >*************************/
#define  HOST_APP_USER_DELAY              (10000)   /* Delay inserted between iterations - Must be removed later */

#define HOST_APP_TCP_BULK_DATA_TRANSFER             /* Bulk data transfer handling enabled */
#define HOST_APP_UDP_BULK_DATA_TRANSFER             /* Bulk data transfer handling enabled */

/*TCP/UDP data packet transfer parameters  */
#define HOST_APP_FILL_DUMMY_DATA             'A'     /* Data pattern to be filled */
#define  HOST_APP_TX_MAX_APP_BUFFER_SIZE    (500)   /* Application buffer size */

#define HOST_APP_TCP_TX_COUNT                5      /* No of packets to transfer */ 
#define  HOST_APP_TCP_PACKET_SIZE           (300)   /* TCP packet  size . This value must be less than application buffer size  */
/* @ 500 xfer breaks down */
#define  HOST_APP_UDP_TX_COUNT                5      /* No of packets to transfer */
#define  HOST_APP_UDP_PACKET_SIZE           (200)   /* UDP packet  size . This value must be less than application buffer size  */

/* Transmit data type */
typedef enum
{
	HOST_APP_TX_DATA_TYPE_TCP=1,
    HOST_APP_TX_DATA_TYPE_UDP,
 
	HOST_APP_TX_DATA_TYPE_MAX

}HOST_APP_TX_DATA_TYPE_E;

// FSM related
typedef enum 
{ /* states */
	 ST_IDLE = 0,
	 ST_LINK_CHECK,
     ST_INIT,
	 ST_RESET_CHECK,
	 ST_ASSOCIATE,
	 ST_TCP_CONN,
	 ST_UDP_CONN,
	 ST_CLOSE_CONN
	 
} HOST_FSM_STATES_TYPE_E;

typedef enum 
{ /* error flags */
	 ERR_CONNECTION       = 0x0001,
	 ERR_TCP_CONNECTION   = 0x0002,
	 ERR_TCP_XFER         = 0x0004,
	 ERR_INV_TCP_CID      = 0x0008,  // parse error
	 ERR_RESET_TCP        = 0x0010,
	 ERR_UDP_CONNECTION   = 0x0020,
     ERR_UDP_XFER         = 0x0040,
	 ERR_INV_UDP_CID      = 0x0080,  // parse error
	 ERR_RESET_UDP        = 0x0100
	 
} HOST_FSM_ERROR_TYPE_E;

typedef enum 
{ /* status flags */
     WARN_GS_ASSOCIATE_MAXOUT   = 0x0001,
	 WARN_GS_RESET_ASSOCIATE    = 0x0002,
	 WARN_GS_RESET_TCP_CONN     = 0x0004,
	 WARN_GS_RESET_UDP_CONN     = 0x0008
	 
} HOST_FSM_STATUS_TYPE_E;
typedef void (* const PFV_I)();

/***************************<Function prototye  >************************************/

UINT32
hostApp_GetApplicationData(INT8 *pBuffer,UINT32 dataLen,HOST_APP_TX_DATA_TYPE_E appDataType);

void
fsm_com(void);

void
fsm_init(void);

void
user_app(void);

void
state_set(UINT8 state);

UINT8
state_get(void);

void
status_set(UINT32 warning);

UINT32
status_get(void);

void
error_set(UINT32 error);

UINT32
error_get(void);

//UINT8 PIC24_ReturnSpiStatus(void);

void user_app(void);

UINT32
hostApp_GetApplicationData(INT8 *pBuffer,UINT32 dataLen,HOST_APP_TX_DATA_TYPE_E appDataType);
//void my_delay_ms(int cnt);

//UINT8 PIC24_GetHostWakeUpStatus();


#endif /* HOST_APP_H_ */
