/******************************************************************************
    Filename: hal_flash.c

    These functions/macros simplifies usage of the ADC.

******************************************************************************/
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_flash.h"
#include "hal_board.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Constants
 */
#define FLASHDRV_DMA_CH 0
#define ERASE           0x01

/*********************************************************************
 * Typedefs
 */
// DMA descriptor
typedef struct {
  unsigned char srcAddrH;
  unsigned char srcAddrL;
  unsigned char dstAddrH;
  unsigned char dstAddrL;
  unsigned char xferLenV;
  unsigned char xferLenL;
  unsigned char ctrlA;
  unsigned char ctrlB;
} flashdrvDmaDesc_t;

/*********************************************************************
 * Local variables
 */
static flashdrvDmaDesc_t flashdrvDmaDesc; // DMA descriptor table

/*********************************************************************
 * Local functions
 */
static __monitor void flashdrvWriteTrigger(void);

/**************************************************************************************************
 * @fn          FLASHDRV_Init
 *
 * @brief       This function initializes flash driver.
 *
 * input parameters
 *
 * None.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 */
void FLASHDRV_Init(void)
{
#if FLASHDRV_DMA_CH == 0
  DMA0CFGH = (unsigned char) ((unsigned short) &flashdrvDmaDesc >> 8);
  DMA0CFGL = (unsigned char) ((unsigned short) &flashdrvDmaDesc & 0xFF);
#else
# error "flashdrv DMA channel other than 0 is not supported"
#endif
  DMAIE = 1;
}

/**************************************************************************************************
 * @fn          HalFlashRead
 *
 * @brief       This function reads 'cnt' bytes from the internal flash.
 *
 * input parameters
 *
 * @param       pg - A valid flash page number.
 * @param       offset - A valid offset into the page.
 * @param       buf - A valid buffer space at least as big as the 'cnt' parameter.
 * @param       cnt - A valid number of bytes to read.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void HalFlashRead(uint8 pg, uint16 offset, uint8 *buf, uint16 cnt)
{
	// Calculate the offset into the containing flash bank as it gets mapped into XDATA.
	uint8 *pData = (uint8 *)(offset + HAL_FLASH_PAGE_MAP) +
				  ((pg % HAL_FLASH_PAGE_PER_BANK) * HAL_FLASH_PAGE_SIZE);
	uint8 memctr = MEMCTR;  // Save to restore.
	
#if (!defined HAL_OAD_BOOT_CODE) && (!defined HAL_OTA_BOOT_CODE)
	halIntState_t is;
#endif
	
	pg /= HAL_FLASH_PAGE_PER_BANK;  // Calculate the flash bank from the flash page.
	
#if (!defined HAL_OAD_BOOT_CODE) && (!defined HAL_OTA_BOOT_CODE)
	HAL_ENTER_CRITICAL_SECTION(is);
#endif
	
	// Calculate and map the containing flash bank into XDATA.
	MEMCTR = (MEMCTR & 0xF8) | pg;
	
	while (cnt--)
	{
		*buf++ = *pData++;
	}
	
	MEMCTR = memctr;
	
#if (!defined HAL_OAD_BOOT_CODE) && (!defined HAL_OTA_BOOT_CODE)
	HAL_EXIT_CRITICAL_SECTION(is);
#endif
}

/**************************************************************************************************
 * @fn          HalFlashWrite
 *
 * @brief       This function writes 'cnt' bytes to the internal flash.
 *
 * input parameters
 *
 * @param       addr - Valid HAL flash write address: actual addr / 4 and quad-aligned.
 * @param       buf - Valid buffer space at least as big as 'cnt' X 4.
 * @param       cnt - Number of 4-byte blocks to write.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void HalFlashWrite(uint16 addr, uint8 *buf, uint16 cnt)
{
	flashdrvDmaDesc.srcAddrH = (unsigned char) ((unsigned short)buf >> 8);
	flashdrvDmaDesc.srcAddrL = (unsigned char) (unsigned short) buf;
	flashdrvDmaDesc.dstAddrH = (unsigned char) ((unsigned short)&FWDATA >> 8);
	flashdrvDmaDesc.dstAddrL = (unsigned char) (unsigned short) &FWDATA;
	flashdrvDmaDesc.xferLenV =
							(0x00 << 5) | // use length
	(unsigned char)(unsigned short)(cnt >> 6);  // length (12:8). Note that cnt is flash word
	flashdrvDmaDesc.xferLenL = (unsigned char)(unsigned short)(cnt * 4);
	flashdrvDmaDesc.ctrlA =
							(0x00 << 7) | // word size is byte
							(0x00 << 5) | // single byte/word trigger mode
							18;           // trigger source is flash
	flashdrvDmaDesc.ctrlB =
							(0x01 << 6) | // 1 byte/word increment on source address
							(0x00 << 4) | // zero byte/word increment on destination address
							(0x00 << 3) | // The DMA is to be polled and shall not issue an IRQ upon completion.
							(0x00 << 2) | // use all 8 bits for transfer count
							 0x02; 		  // DMA priority high
	
	DMAIRQ &= ~( 1 << FLASHDRV_DMA_CH );  // clear IRQ
	DMAARM = (0x01 << FLASHDRV_DMA_CH );  // arm DMA
	
	FADDRL = (unsigned char)addr;
	FADDRH = (unsigned char)(addr >> 8);
	flashdrvWriteTrigger();
}

/**************************************************************************************************
 * @fn          HalFlashErase
 *
 * @brief       This function erases the specified page of the internal flash.
 *
 * input parameters
 *
 * @param       pg - A valid flash page number to erase.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void HalFlashErase(uint8 pg)
{
  FADDRH = pg * (HAL_FLASH_PAGE_SIZE / HAL_FLASH_WORD_SIZE / 256);
  FCTL |= 0x01;
}

/**************************************************************************************************
 * @fn          flashdrvWriteTrigger
 *
 * @brief       This function must be copied to RAM before running because it triggers and then
 *              awaits completion of Flash write, which can only be done from RAM.
 *
 * input parameters
 *
 * None.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 */
static __monitor void flashdrvWriteTrigger(void)
{
  FCTL |= 0x02;         // Trigger the DMA writes.
  while (FCTL & 0x80);  // Wait until writing is done.
}

