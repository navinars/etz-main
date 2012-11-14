/**************************************************************************************************
  Filename:       hal_flash.h
  Revised:        $Date:$
  Revision:       $Revision:$
**************************************************************************************************/

#ifndef HAL_FLASH_H
#define HAL_FLASH_H

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */

#include "hal_board.h"
#include "hal_types.h"

// Flash is partitioned into 8 banks of 32 KB or 16 pages.
#define HAL_FLASH_PAGE_PER_BANK    16
// Flash is constructed of 128 pages of 2 KB.
#define HAL_FLASH_PAGE_SIZE        2048
#define HAL_FLASH_WORD_SIZE        4

// CODE banks get mapped into the XDATA range 8000-FFFF.
#define HAL_FLASH_PAGE_MAP         0x8000

// The last 16 bytes of the last available page are reserved for flash lock bits.
// NV page definitions must coincide with segment declaration in project *.xcl file.
#if defined NON_BANKED
#define HAL_FLASH_LOCK_BITS        16
#define HAL_NV_PAGE_END            30
#define HAL_NV_PAGE_CNT            2
#else
#define HAL_FLASH_LOCK_BITS        16
#define HAL_NV_PAGE_END            62
#define HAL_NV_PAGE_CNT            6
#endif

#define Z_EXTADDR_LEN   		   8

#define HAL_FLASH_IEEE_SIZE        8
#define HAL_FLASH_IEEE_PAGE       (HAL_NV_PAGE_END +1)
#define HAL_FLASH_IEEE_OSET       (HAL_FLASH_PAGE_SIZE - HAL_FLASH_LOCK_BITS - HAL_FLASH_IEEE_SIZE)
#define HAL_INFOP_IEEE_OSET        0xC

void FLASHDRV_Init(void);
void HalFlashRead(uint8 pg, uint16 offset, uint8 *buf, uint16 cnt);
void HalFlashWrite(uint16 addr, uint8 *buf, uint16 cnt);
void HalFlashErase(uint8 pg);

#endif

