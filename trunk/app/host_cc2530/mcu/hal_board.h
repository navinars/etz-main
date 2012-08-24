/***********************************************************************************

  Filename:     bsp_board.h

  Description:  SmartRF05 board with CCxxxxEM.

***********************************************************************************/

#ifndef HAL_BOARD_H
#define HAL_BOARD_H

#include "ioCC2530.h"

#include "hal_cc8051.h"
#include "hal_defs.h"
#include "hal_mcu.h"


/***********************************************************************************
 * CONSTANTS
 */
/* Sleep timer runs on the 32.768k external RC. */
/* One clock tick is 7.8 ms */
#define TICK_VAL 32768*2//(32768/128)  /* 256 */


// Internal (MCU) RAM addresses
#define MCU_RAM_BEG 0x0100
#define MCU_RAM_END RAMEND
#define MCU_RAM_LEN (MCU_RAM_END - MCU_RAM_BEG + 1)

// Internal (MCU) heap size
#define INT_HEAP_LEN  2048  // 1.00K

// Clock
#define BSP_CONFIG_CLOCK_MHZ                32

// LEDs
#define HAL_BOARD_IO_LED_1_PORT        0   // Green
#define HAL_BOARD_IO_LED_1_PIN         0
#define HAL_BOARD_IO_LED_2_PORT        0   // Red
#define HAL_BOARD_IO_LED_2_PIN         1


// Buttons
#define HAL_BOARD_IO_BTN_1_PORT        0   // Button S1
#define HAL_BOARD_IO_BTN_1_PIN         5

// Potmeter
#define HAL_POTMETER_ADC_PORT               0
#define HAL_POTMETER_ADC_CH                 7

// UART
#define HAL_BOARD_IO_UART_RTS_PORT          0
#define HAL_BOARD_IO_UART_RTS_PIN           5

#define HAL_UART	TRUE


// Debounce
#define HAL_DEBOUNCE(expr)    { int i; for (i=0; i<500; i++) { if (!(expr)) i = 0; } }

/***********************************************************************************
 * MACROS
 */

// LED
#define HAL_LED_CLR_1()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_1_PORT, HAL_BOARD_IO_LED_1_PIN)
#define HAL_LED_CLR_2()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_2_PORT, HAL_BOARD_IO_LED_2_PIN)
#define HAL_LED_CLR_3()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_3_PORT, HAL_BOARD_IO_LED_3_PIN)
#define HAL_LED_CLR_4()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_4_PORT, HAL_BOARD_IO_LED_4_PIN)

#define HAL_LED_SET_1()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_1_PORT, HAL_BOARD_IO_LED_1_PIN)
#define HAL_LED_SET_2()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_2_PORT, HAL_BOARD_IO_LED_2_PIN)
#define HAL_LED_SET_3()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_3_PORT, HAL_BOARD_IO_LED_3_PIN)
#define HAL_LED_SER_4()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_4_PORT, HAL_BOARD_IO_LED_4_PIN)

#define HAL_LED_TGL_1()                 MCU_IO_TGL(HAL_BOARD_IO_LED_1_PORT, HAL_BOARD_IO_LED_1_PIN)
#define HAL_LED_TGL_2()                 MCU_IO_TGL(HAL_BOARD_IO_LED_2_PORT, HAL_BOARD_IO_LED_2_PIN)
#define HAL_LED_TGL_3()                 MCU_IO_TGL(HAL_BOARD_IO_LED_3_PORT, HAL_BOARD_IO_LED_3_PIN)
#define HAL_LED_TGL_4()                 MCU_IO_TGL(HAL_BOARD_IO_LED_4_PORT, HAL_BOARD_IO_LED_4_PIN)

/* ----------- Cache Prefetch control ---------- */
#define PREFETCH_ENABLE()     st( FCTL = 0x08; )
#define PREFETCH_DISABLE()    st( FCTL = 0x04; )
/***********************************************************************************
 * FUNCTION PROTOTYPES
 */
void halBoardInit(void);
void clock_init(void);
void set_sleeptimer(U32 value);
U32 read_sleeptimer(void);

#endif
