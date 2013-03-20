/**
 * \file
 *
 * \brief User board definition template
 *
 */

 /* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

#include <conf_board.h>

/*----------------------------------------------------------------------------*/
/**
 *  \page sam3u_ek_opfreq SAM3U-EK - Operating frequencies
 *  This page lists several definition related to the board operating frequency
 *
 *  \section Definitions
 *  - \ref BOARD_FREQ_*
 *  - \ref BOARD_MCK
 */

/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL		(32768U)
#define BOARD_FREQ_SLCK_BYPASS		(32768U)
#define BOARD_FREQ_MAINCK_XTAL		(12000000U)
#define BOARD_FREQ_MAINCK_BYPASS	(12000000U)

/** Master clock frequency */
#define BOARD_MCK					CHIP_FREQ_CPU_MAX

/** board main clock xtal statup time */
#define BOARD_OSC_STARTUP_US   15625

#define CONSOLE_UART			   UART
#define CONSOLE_UART_ID            ID_UART

//! LED #0 pin definition (BLUE).
#define LED_0_NAME    "green LED D2"
#define LED0_GPIO     (PIO_PB0_IDX)
#define LED0_FLAGS    (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED0_ACTIVE_LEVEL 0

//! UART pins (UTXD0 and URXD0) definitions, PA8,9.
#define PINS_UART		(PIO_PA8A_URXD | PIO_PA9A_UTXD)
#define PINS_UART_FLAGS	(PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART_MASK	(PIO_PA8A_URXD | PIO_PA9A_UTXD)
#define PINS_UART_PIO	PIOA
#define PINS_UART_ID	ID_PIOA
#define PINS_UART_TYPE	PIO_PERIPH_A
#define PINS_UART_ATTR	PIO_DEFAULT

//! USART0
#define PIN_USART0_RXD    {0x1 << 19, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA19_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART0_TXD    {0x1 << 18, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX        (PIO_PA18_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART0_CTS    {0x1 << 8, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS_IDX        (PIO_PA8_IDX)
#define PIN_USART0_CTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART0_RTS    {0x1 << 7, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS_IDX        (PIO_PA7_IDX)
#define PIN_USART0_RTS_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART0_SCK    {0x1 << 17, PIOA,ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_SCK_IDX        (PIO_PA17_IDX)
#define PIN_USART0_SCK_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)

//! USART1
#define PIN_USART1_RXD    {0x1 << 21, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_RXD_IDX        (PIO_PA21_IDX)
#define PIN_USART1_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART1_TXD    {0x1 << 20, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_TXD_IDX        (PIO_PA20_IDX)
#define PIN_USART1_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
#define PIN_USART1_CTS    {0x1 << 23, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART1_CTS_IDX        (PIO_PA23_IDX)
#define PIN_USART1_CTS_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_USART1_RTS    {0x1 << 22, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART1_RTS_IDX        (PIO_PA22_IDX)
#define PIN_USART1_RTS_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)
#define PIN_USART1_EN     {0x1 << 24, PIOA, ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_USART1_EN_IDX         (PIO_PA24_IDX)
#define PIN_USART1_EN_FLAGS       (PIO_OUTPUT_0 | PIO_DEFAULT)
#define PIN_USART1_SCK    {0x1 << 24, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART1_SCK_IDX        (PIO_PA24_IDX)
#define PIN_USART1_SCK_FLAGS      (PIO_PERIPH_B | PIO_DEFAULT)

// External oscillator settings.
// Uncomment and set correct values if external oscillator is used.

// External oscillator frequency
//#define BOARD_XOSC_HZ          8000000

// External oscillator type.
//!< External clock signal
//#define BOARD_XOSC_TYPE        XOSC_TYPE_EXTERNAL
//!< 32.768 kHz resonator on TOSC
//#define BOARD_XOSC_TYPE        XOSC_TYPE_32KHZ
//!< 0.4 to 16 MHz resonator on XTALS
//#define BOARD_XOSC_TYPE        XOSC_TYPE_XTAL

// External oscillator startup time
//#define BOARD_XOSC_STARTUP_US  500000


#endif // USER_BOARD_H
