/***********************************************************************************
  Filename:     hal_board.c

  Description:  HAL board peripherals library for the
                SmartRF05EB + CC2430EM/CC2531EM/CC2510/CC1110 platforms
***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "hal_types.h"
#include "hal_defs.h"
#include "hal_digio.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_clock.h"
#include "hal_board.h"


// comment: should this be here?
#define SPI_CLOCK_POL_LO       0x00
#define SPI_CLOCK_POL_HI       0x80
#define SPI_CLOCK_PHA_0        0x00
#define SPI_CLOCK_PHA_1        0x40
#define SPI_TRANSFER_MSB_FIRST 0x20
#define SPI_TRANSFER_MSB_LAST  0x00

/***********************************************************************************
* LOCAL FUNCTIONS
*/

/***********************************************************************************
* GLOBAL VARIABLES
*/

/***********************************************************************************
* GLOBAL FUNCTIONS
*/

/***********************************************************************************
* @fn      halBoardInit
*
* @brief   Set up board. Initialize MCU, configure I/O pins and user interfaces
*
* @param   none
*
* @return  none
*/
void halBoardInit(void)
{
    halMcuInit();			// Initialise mcu clock.
	
    halIntOn();				// Global interrupt is enable.
}

/***********************************************************************************
* @fn          halLcdSpiInit
*
* @brief       Initalise LCD SPI interface
*
* @param       none
*
* @return      none
*/
void halLcdSpiInit(void)
{
   register uint8 baud_exponent;
   register uint8 baud_mantissa;


   // Set SPI on UART 1 alternative 2
   PERCFG |= 0x02;

   // Use SPI on USART 1 alternative 2
   MCU_IO_PERIPHERAL(HAL_BOARD_IO_SPI_MISO_PORT, HAL_BOARD_IO_SPI_MISO_PIN);
   MCU_IO_PERIPHERAL(HAL_BOARD_IO_SPI_MOSI_PORT, HAL_BOARD_IO_SPI_MOSI_PIN);
   MCU_IO_PERIPHERAL(HAL_BOARD_IO_SPI_CLK_PORT,  HAL_BOARD_IO_SPI_CLK_PIN);

   // Set SPI speed to 1 MHz (3 MHz is max on CC2511)
# if (chip==2430 || chip==2431)
   baud_exponent = 15 + CC2430_GET_CLKSPD();
#elif (chip==2530 || chip==2531)
   baud_exponent = 15 + CC2530_GET_CLKSPD();
#elif (chip==2510 || chip==1110)
   baud_exponent = 15 + CLKSPD_GET();
#endif
   baud_mantissa = 83;

   // Configure peripheral
   U1UCR  = 0x80;      // Flush and goto IDLE state. 8-N-1.
   U1CSR  = 0x00;      // SPI mode, master.
   U1GCR  = SPI_TRANSFER_MSB_FIRST | SPI_CLOCK_PHA_0 | SPI_CLOCK_POL_LO | baud_exponent;
   U1BAUD = baud_mantissa;
}

/***********************************************************************************
* @fn          halLcdSpiEn
*
* @brief       Enable LCD SPI interface
*
* @param       none
*
* @return      none
*/
void halLcdSpiEna(void)
{
   // Use SPI on USART 1 alternative 2
   MCU_IO_PERIPHERAL(HAL_BOARD_IO_SPI_MISO_PORT, HAL_BOARD_IO_SPI_MISO_PIN);
   MCU_IO_PERIPHERAL(HAL_BOARD_IO_SPI_MOSI_PORT, HAL_BOARD_IO_SPI_MOSI_PIN);
   MCU_IO_PERIPHERAL(HAL_BOARD_IO_SPI_CLK_PORT,  HAL_BOARD_IO_SPI_CLK_PIN);
}

/***********************************************************************************
* @fn          halLcdSpiDis
*
* @brief       Disable LCD SPI interface (set pins to input, except CS)
*
* @param       none
*
* @return      none
*/
void halLcdSpiDis(void)
{
	MCU_IO_INPUT(HAL_BOARD_IO_SPI_MISO_PORT, HAL_BOARD_IO_SPI_MISO_PIN, MCU_IO_TRISTATE);
	MCU_IO_INPUT(HAL_BOARD_IO_SPI_MOSI_PORT, HAL_BOARD_IO_SPI_MOSI_PIN, MCU_IO_TRISTATE);
	MCU_IO_INPUT(HAL_BOARD_IO_SPI_CLK_PORT, HAL_BOARD_IO_SPI_CLK_PIN, MCU_IO_TRISTATE);
}

