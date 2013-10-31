
#ifndef CONF_EMAC_H_INCLUDED
#define CONF_EMAC_H_INCLUDED

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Number of buffer for RX */
#define EMAC_RX_BUFFERS  16

/** Number of buffer for TX */
#define EMAC_TX_BUFFERS  8

/** MAC PHY operation max retry count */
#define MAC_PHY_RETRY_MAX 1000000

/** MAC address definition.  The MAC address must be unique on the network. */
#define ETHERNET_CONF_ETHADDR0                        0x00
#define ETHERNET_CONF_ETHADDR1                        0x04
#define ETHERNET_CONF_ETHADDR2                        0x25
#define ETHERNET_CONF_ETHADDR3                        0x1C
#define ETHERNET_CONF_ETHADDR4                        0xA0
#define ETHERNET_CONF_ETHADDR5                        0x03

/** WAN Address: 192.168.0.2 */

/* The IP address being used. */
#define ETHERNET_CONF_IPADDR0                         192
#define ETHERNET_CONF_IPADDR1                         168
#define ETHERNET_CONF_IPADDR2                         1
#define ETHERNET_CONF_IPADDR3                         225

/** WAN gateway: 192.168.0.1 */

/*! The gateway address being used. */
#define ETHERNET_CONF_GATEWAY_ADDR0                   192
#define ETHERNET_CONF_GATEWAY_ADDR1                   168
#define ETHERNET_CONF_GATEWAY_ADDR2                   1
#define ETHERNET_CONF_GATEWAY_ADDR3                   1

/** The network mask being used. */
#define ETHERNET_CONF_NET_MASK0                       255
#define ETHERNET_CONF_NET_MASK1                       255
#define ETHERNET_CONF_NET_MASK2                       255
#define ETHERNET_CONF_NET_MASK3                       0

/** Ethernet MII/RMII mode */
#define ETH_PHY_MODE  BOARD_EMAC_MODE_RMII

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* CONF_EMAC_H_INCLUDED */
