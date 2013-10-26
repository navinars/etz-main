
#include "asf.h"
#include "net_config.h"

#include <string.h>

ip_save_t IPsave;
ip_save_t IPsave_tmp;


/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
void netmode_init(void)
{
	uint32_t ul_last_page_addr = LAST_PAGE_ADDRESS;
	uint32_t *pul_last_page = (uint32_t *) ul_last_page_addr;
	
	memset(&IPsave_tmp, 0, sizeof(ip_save_t));
	
	/* Initialize flash: 6 wait states for flash writing. */
	flash_init(FLASH_ACCESS_MODE_128, 6);
	
	/* Unlock page */
	flash_unlock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
	
	/* Read Flash page */
	memcpy((uint8_t*)(&IPsave_tmp), (uint8_t*)pul_last_page, sizeof(ip_save_t));
	
	//IPsave_tmp.mode = 2;
	
	if (IPsave_tmp.ip[0] == 0)									/* IP value is NOT zero.*/
	{
		IPsave_tmp.ip[0] = 224;
		IPsave_tmp.mode  = 1;
	}
	
	else if(IPsave_tmp.ip[0] == 0xFF)
	{
		IPsave_tmp.ip[0] = 224;
		IPsave_tmp.mode  = 1;
	}
	if (gpio_pin_is_low(RESTKEY_GPIO) == 1)
	{ 
		uint32_t ul_last_page_addr = LAST_PAGE_ADDRESS;
		uint32_t ul_page_buffer[IFLASH_PAGE_SIZE / sizeof(uint32_t)];
		
		IPsave_tmp.mode = 1;
		IPsave_tmp.ip[0] = 224;
		
		/* Copy information to FLASH buffer..*/
		memcpy((uint8_t*)ul_page_buffer, (uint8_t *)(&IPsave_tmp), sizeof(ip_save_t));
		
		/* Write page */
		flash_write(ul_last_page_addr, ul_page_buffer, IFLASH_PAGE_SIZE, 1);
	}
	
	/* Lock page */
	flash_lock(ul_last_page_addr, ul_last_page_addr + IFLASH_PAGE_SIZE - 1, 0, 0);
}
