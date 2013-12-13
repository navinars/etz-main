
#include "asf.h"
#include "net_config.h"

#include <string.h>

f_ip_config_t f_ip_config_tmp;
f_ip_config_t f_ip_config;

/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
void f_config_handle(void)
{
	uint32_t ul_last_page_addr = LAST_PAGE_ADDRESS;
	uint32_t *pul_last_page = (uint32_t *) ul_last_page_addr;
	uint32_t ul_page_buffer[IFLASH_PAGE_SIZE / sizeof(uint32_t)];
	
	memset( &f_ip_config, 0, sizeof(f_ip_config_t) );
	
	/* Initialize flash: 6 wait states for flash writing. */
	flash_init(FLASH_ACCESS_MODE_128, 6);
	
	/* Unlock page */
	flash_unlock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
	
	/* Read Flash page */
	memcpy((uint8_t*)(&f_ip_config), (uint8_t*)pul_last_page, sizeof(f_ip_config_t));
	
	if (( f_ip_config.alloc != IP_CONFIG_ALLOC_TRUE ) ||
			 ( gpio_pin_is_low(RESTKEY_GPIO) == 1 ))			/* net parameters init. */
	{
		uint32_t unique_id[4];
		
		flash_read_unique_id(unique_id, 4);						/* read unique ID. */
		
		f_ip_config.mode     = IP_CONFIG_MODE_FIXEDIP;
		
		f_ip_config.alloc    = IP_CONFIG_ALLOC_TRUE;			/* net parameters are occupied.. */
		
		f_ip_config.ip[0]	 = ETHERNET_CONF_IPADDR0;
		f_ip_config.ip[1]	 = ETHERNET_CONF_IPADDR1;
		f_ip_config.ip[2]	 = ETHERNET_CONF_IPADDR2;
		f_ip_config.ip[3]    = ETHERNET_CONF_IPADDR3;
		
		f_ip_config.mac[0]   = ETHERNET_CONF_ETHADDR0;
		f_ip_config.mac[1]   = ETHERNET_CONF_ETHADDR1;
		f_ip_config.mac[2]   = ETHERNET_CONF_ETHADDR2;
		f_ip_config.mac[3]   = unique_id[3]>>8;
		f_ip_config.mac[4]   = unique_id[3];
		
		f_ip_config.mask[0]  = ETHERNET_CONF_NET_MASK0;
		f_ip_config.mask[1]  = ETHERNET_CONF_NET_MASK1;
		f_ip_config.mask[2]  = ETHERNET_CONF_NET_MASK2;
		f_ip_config.mask[3]  = ETHERNET_CONF_NET_MASK3;
		
		/* Copy information to FLASH buffer..*/
		memcpy((uint8_t*)ul_page_buffer, (uint8_t *)(&f_ip_config), sizeof(f_ip_config_t));
		
		/* Write page */
		flash_write(ul_last_page_addr, ul_page_buffer, IFLASH_PAGE_SIZE, 1);
	}
	
	/* Lock page */
	flash_lock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
}
