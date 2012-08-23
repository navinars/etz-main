/********************************************************************************************************
  Filename:     mac.h

  Description:  MAC layer library header file

********************************************************************************************************/

#ifndef MAC_H
#define MAC_H
/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"

#define aMaxPHYPacketSize	127
/*
*********************************************************************************************************
*                                            GLOBALE DEFINES
*********************************************************************************************************
*/

typedef enum
{
    MAC_FRM_PEND_OFF                    = 4,        ///< Data pending flag offset in FCF
    MAC_ACK_REQ_OFF                     = 5,        ///< Ack request flag offset in FCF
    MAC_PAN_ID_COMPR_OFF                = 6,        ///< Pan ID compression offset in FCF
    MAC_DEST_ADDR_MODE_OFF              = 10,       ///< Destination address mode offset in FCF
    MAC_SRC_ADDR_MODE_OFF               = 14,       ///< Source address offset in FCF

    // MAC frame control field bit masks
    MAC_FRAME_TYPE_MASK                 = 0x0003,   ///< Data, command, ACK, or beacon frame indicator
    MAC_PENDING_FRAME_MASK              = 0x0010,   ///< Indirect data awaiting retrieval for dest address
    MAC_ACK_REQ_MASK                    = 0x0020,   ///< Ack required for this frame
    MAC_PAN_ID_COMPR_MASK               = 0x0040,   ///< If src and dest PAN ID are same, then include once and set this flag
    MAC_DEST_ADDR_MODE_MASK             = 0x0C00,   ///< Address mode in address field for dest - network or extended addr
    MAC_SRC_ADDR_MODE_MASK              = 0xC000,   ///< Address mode in address field for src - network or extended addr

    // frame type for FCF enums
    MAC_BEACON                          = 0x0,      ///< Beacon frame indicator
    MAC_DATA                            = 0x1,      ///< Data frame indicator
    MAC_ACK                             = 0x2,      ///< ACK frame indicator
    MAC_COMMAND                         = 0x3,      ///< Command frame indicator

    // address mode enums
    NO_PAN_ID_ADDR                      = 0x0,      ///< No address and no PAN ID in address field
    SHORT_ADDR                          = 0x2,      ///< Address field contains network (short) address
    LONG_ADDR                           = 0x3       ///< Address field contains IEEE (long) address
} mac_frm_ctrl_enums_t;

typedef enum
{
    // tx options
    MAC_ACK_REQUEST                     = 0x01,     ///< Ack is required for this transmission. MAC data request service.
    MAC_INDIRECT_TRANS                  = 0x04,     ///< Frame will be sent indirectly. MAC data request service.

    // broadcast address
    MAC_BROADCAST_ADDR                  = 0xFFFF,   ///< MAC broadcast address

    // 802.15.4 Frame Versions
    MAC_802_15_4_2003                   = 0x0,      ///< Compliant to 802.15.4 2003 frame format
    MAC_802_15_4_2006                   = 0x1,      ///< Compliant to 802.15.4 2006 frame format

    // scan types
    MAC_ENERGY_SCAN                     = 0x00,     ///< Energy scan identifier
    MAC_ACTIVE_SCAN                     = 0x01,     ///< Active scan identifier
    MAC_ORPHAN_SCAN                     = 0x03,     ///< Orphan scan identifier

    MAC_MAX_CHANNELS                    = 16,       ///< Max number of channels supported by MAC
    MAC_PHY_CHANNEL_OFFSET              = 11,       ///< Channel offset. 802.15.4 range is Ch 11-26
    MAC_FCS_LENGTH                      = 2,        ///< Size of the MAC frame checksum

    // mac management states
    MLME_IDLE                           = 0x0,      ///< Idle state for the MAC management state machine
    MLME_ASSOC_REQ                      = 0x1,      ///< Association request state of MAC management state machine
    MLME_DATA_REQ                       = 0x2,      ///< Data request state of MAC management state machine
    MLME_SCAN                           = 0x3       ///< Scan state of MAC management state machine
} mac_misc_enums_t;

typedef enum
{
    // mac command frames
    MAC_ASSOC_REQ                       = 0x1,  ///< Association request command ID
    MAC_ASSOC_RESP                      = 0x2,  ///< Association response command ID
    MAC_DATA_REQ                        = 0x4,  ///< Data request command ID
    MAC_ORPHAN_NOT                      = 0x6,  ///< Orphan notification command ID
    MAC_BEACON_REQ                      = 0x7,  ///< Beacon request command ID
    MAC_COORD_REALIGN                   = 0x8,  ///< Coordinator realignment command ID

    MAC_ASSOC_REQ_LEN                   = 0x2,
    MAC_ASSOC_RESP_LEN                  = 0x4,
    MAC_COORD_REALIGN_LEN               = 0x8
} mac_cmd_frm_enums_t;

typedef enum
{
    // mac status
    MAC_SUCCESS                     = 0x0,      ///< Transaction was successful
    MAC_BEACON_LOSS                 = 0xE0,     ///< Beacon was lost (used in beacon'd networks)
    MAC_CHANNEL_ACCESS_FAILURE      = 0xE1,     ///< Unable to transmit due to channel being busy
    MAC_COUNTER_ERROR               = 0xDB,     ///< Frame counter of received frame is invalid
    MAC_DENIED                      = 0xE2,     ///< GTS request denied
    MAC_DISABLE_TRX_FAILURE         = 0xE3,     ///< Failed to disable the transceiver
    MAC_SECURITY_ERROR              = 0xE4,     ///< Frame failed decryption
    MAC_FRAME_TOO_LONG              = 0xE5,     ///< Frame exceeded maximum size
    MAC_IMPROPER_KEY_TYPE           = 0xDC,     ///< Key not allowed to be used with this frame type
    MAC_IMPROPER_SECURITY_LEVEL     = 0xDD,     ///< Frame does not meet min security level expected
    MAC_INVALID_ADDRESS             = 0xF5,     ///< Data request failed because no src or dest address
    MAC_INVALID_GTS                 = 0xE6,     ///< Invalid timeslot requested (beacon'd networks)
    MAC_INVALID_HANDLE              = 0xE7,     ///< Invalid frame data handle
    MAC_INVALID_INDEX               = 0xF9,     ///< Invalid index when trying to write MAC PIB
    MAC_INVALID_PARAMETER           = 0xE8,     ///< Invalid parameter passed to service
    MAC_LIMIT_REACHED               = 0xFA,     ///< Scan terminated because max pan descriptors reached
    MAC_NO_ACK                      = 0xE9,     ///< ACK not received after tx with ack_req flag set
    MAC_NO_BEACON                   = 0xEA,     ///< Beacon not returned after beacon request
    MAC_NO_DATA                     = 0xEB,     ///< Data frame not returned after data request (indirect poll)
    MAC_NO_SHORT_ADDRESS            = 0xEC,     ///< No short address allocated to this device (due to lack of address space)
    MAC_ON_TIME_TOO_LONG            = 0xF6,     ///< Rx enable request failed. Spec'd number of symbols longer than beacon interval
    MAC_OUT_OF_CAP                  = 0xED,     ///< Association failed due to lack of capacity (no nbor tbl entry or no address)
    MAC_PAN_ID_CONFLICT             = 0xEE,     ///< Different networks within listening range have identical PAN IDs
    MAC_PAST_TIME                   = 0xF7,     ///< Rx enable failed. Too late for current superframe and unable to be deferred
    MAC_READ_ONLY                   = 0xFB,     ///< PIB attribute is read only
    MAC_REALIGNMENT                 = 0xEF,     ///< Coordinator realignment received
    MAC_SCAN_IN_PROGRESS            = 0xFC,     ///< Request to perform scan failed because scan already in progress
    MAC_SUPERFRAME_OVERLAP          = 0xFD,     ///< Start time of beacon overlapped transmission time of coordinator beacon
    MAC_TRACKING_OFF                = 0xF8,     ///< Device not tracking beacons but instructed to send beacons based on tracked beacons
    MAC_TRANSACTION_EXPIRED         = 0xF0,     ///< Frame buffered in indirect queue expired
    MAC_TRANSACTION_OVERFLOW        = 0xF1,     ///< Exceeded maximum amount of entries in indirect queue
    MAC_TX_ACTIVE                   = 0xF2,     ///< Transmission in progress
    MAC_UNAVAILABLE_KEY             = 0xF3,     ///< Security key unavailable
    MAC_UNSUPPORTED_ATTRIBUTE       = 0xF4,     ///< Requested PIB attribute is not supported
    MAC_UNSPECIFIED_FAILURE         = 0xF5,     ///< Unspecified failure occurs. This is catch all for any type of general failure.
    MAC_UNSUPPORTED_LEGACY          = 0xDE,     ///< 802.15.4 2003 security on frame, but not supported by device
    MAC_UNSUPPORTED_SECURITY        = 0xDF      ///< Security on received frame is not supported
} mac_status_enums_t;

typedef enum
{
    // mac beacon fields
    MAC_GTS_MASK                        = 0x7,      ///< Guaranteed timeslot mask for beacon frame
    MAC_GTS_DESC_SIZE                   = 0x3,      ///< Guaranteed timeslot descriptor size for beacon frame
    MAC_GTS_DIR_SIZE                    = 0x1,      ///< Guaranteed timeslot direction size for beacon frame
    MAC_PENDING_SHORT_ADDR_MASK         = 0x7,      ///< Pending short address mask for beacon frame
    MAC_PENDING_LONG_ADDR_OFF           = 0x4,      ///< Pending long address offset for beacon frame
    MAC_PENDING_LONG_ADDR_MASK          = 0x70,     ///< Pending long address mask for beacon frame
    MAC_BEACON_PAYLOAD_SIZE             = 0x4,      ///< Beacon frame payload size

    // mac superframe spec fields
    MAC_ASSOC_PERMIT_OFF                = 15,
    MAC_COORDINATOR_OFF                 = 14,
    MAC_FINAL_CAP_SLOT_OFF              = 8,
    MAC_SUPERFRAME_ORDER_OFF            = 4,
    MAC_BEACON_ORDER_OFF                = 0,
    MAC_ASSOC_PERMIT_MASK               = (0x1 << MAC_ASSOC_PERMIT_OFF),    ///< Indicate if association is permitted (superfrm spec)
    MAC_COORDINATOR_MASK                = (0x1 << MAC_COORDINATOR_OFF),     ///< Indicate if coordinator (superfrm spec)
    MAC_BEACON_ORDER                    = (0xF << MAC_BEACON_ORDER_OFF),    ///< Indicate beacon order (superfrm spec)
    MAC_SUPERFRAME_ORDER                = (0xF << MAC_SUPERFRAME_ORDER_OFF), ///< Indicate superfrm order (superfrm spec)
    MAC_FINAL_CAP_SLOT                  = (0xF << MAC_FINAL_CAP_SLOT_OFF)   ///< Indicate final contention access period slot (superfrm spec)
} mac_beacon_enums_t;

/*
*********************************************************************************************************
*                                          GLOBALE DATA TYPES
*********************************************************************************************************
*/
typedef struct _mac_buf_t
{
	bool					alloc;
	U8						*dptr;
	U8						mode;
	U8						len;
	U8						index;
	U8						buf[aMaxPHYPacketSize +1];
} mac_buf_t;

typedef struct
{
	U8				mode;
	union
	{
		U16			short_addr;
		U8			long_addr[8];
	};
} address_t;

typedef struct
{
	U16				ack_wait_duration;
	bool			assoc_permit;
	address_t		coord_addr;
	U8				dsn;
	U8				min_be;
	U8				max_csma_backoffs;
	U16				pan_id;
	U16				tmp_pan_id;
	bool			rx_on_when_idle;
	U16				resp_wait_time;
	bool			security_enb;
	U16				short_addr;
	U8				ext_addr[8];
	bool			coord;
	U8				curr_channel;
} mac_pib_t;

typedef struct
{
	U8				mac_state;
//	struct ctimer	mlme_tmr;
	
	// association
	address_t		parent_addr;
	U8				assoc_req_dsn;
	
	// channel scanning
	U16				original_pan_id;
	U8				curr_scan_channel;
	U32				channel_mask;
	U8				duration;
	U8				nwk_cnt;
	U8				scan_type;
	bool			coor_realign_rcvd;
	U8				energy_list[MAC_MAX_CHANNELS];
	
	// statistics
	U16				total_xmit;
	U16				total_fail;
} mac_pcb_t;


typedef struct
{
	U8				frame_type;
	bool			sec_enb;
	bool			frame_pending;
	bool			ack_req;
	bool			pan_id_compr;
	U8				frame_ver;
} mac_frm_ctrl_t;

typedef struct
{
	mac_frm_ctrl_t	mac_frm_ctrl;
	U16				mac_fcf;
	U8				dsn;
	U16				dest_pan_id;
	address_t		dest_addr;
	U16				src_pan_id;
	address_t		src_addr;
} mac_hdr_t;

typedef struct
{
	address_t		src_addr;
	address_t		dest_addr;
	U16				src_pan_id;
	U16				dest_pan_id;
	mac_buf_t		*buf;
	U8				msdu_handle;
	U8				tx_options;
} mac_data_req_t;

typedef struct
{
	U8				cap_info;
} cmd_assoc_req_t;

typedef struct
{
	U16				short_addr;
	U8				assoc_status;
} cmd_assoc_resp_t;

typedef struct
{
	U16				pan_id;
	U16				coord_short_addr;
	U8				channel;
	U16				short_addr;
} cmd_coord_realign_t;

typedef struct
{
	U8 cmd_id;
	union
	{
		cmd_assoc_req_t			assoc_req;
		cmd_assoc_resp_t		assoc_resp;
		cmd_coord_realign_t		coord_realign;
	};
} mac_cmd_t;

typedef struct
{
	address_t		dev_addr;
	U8				capability;
} mac_assoc_ind_t;

typedef struct
{
	address_t		dev_addr;
	U16				assoc_short_addr;
	U8				status;
} mac_assoc_resp_t;

typedef struct
{
	U8				channel;
	address_t		coord_addr;
	U16				coord_pan_id;
	U8				capability;
} mac_assoc_req_t;

/*
*********************************************************************************************************
*                                           GLOBAL VARIABLES
*********************************************************************************************************
*/
extern U8 			mac_TaskId;

/*
*********************************************************************************************************
*                                            GLOBALE TABLES
*********************************************************************************************************
*/
extern void mac_init(void);

extern mac_pib_t *mac_pib_get(void);

extern mac_pcb_t *mac_pcb_get(void);

extern void mac_event_handle(void);

extern void mac_host_beacon(void);


//---------------------------------------mac_buf.c-------------------------------------------------------
extern void mac_buf_init(void);

extern mac_buf_t *read_rx_buf(void);

extern mac_buf_t *read_tx_buf(void);

extern void reset_rx_buf(void);

extern void reset_tx_buf(void);


//---------------------------------------mac_gen.c-------------------------------------------------------
extern void mac_gen_header(mac_buf_t *buf, mac_hdr_t *hdr);

extern void mac_gen_cmd(mac_buf_t *buf, mac_cmd_t *cmd);

extern U16  mac_gen_superfrm_spec(void);

extern void mac_gen_beacon_frm(mac_buf_t *buf, mac_hdr_t *hdr);


//---------------------------------------mac_hw.c--------------------------------------------------------
extern int  send(mac_buf_t *buf);

extern int  mac_tx_handle(address_t *dest_addr, U8 *pdata, U8 len, U8 option);

extern void RfRxFrmDoneIsr(void);

//---------------------------------------mac_parse.c--------------------------------------------------------
extern void mac_parse_hdr(mac_buf_t *buf, mac_hdr_t *hdr);

extern void mac_parse_data(mac_buf_t *buf, mac_hdr_t *hdr);


#endif

