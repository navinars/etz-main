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


#define SW1_GPIO     (PIO_PA20_IDX)
#define SW1_FLAGS    (PIO_INPUT | PIO_DEFAULT)

//! LED #0 pin definition (BLUE).
#define LED_0_NAME    "green LED D2"
#define LED0_GPIO     (PIO_PA2_IDX)
#define LED0_FLAGS    (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED0_ACTIVE_LEVEL 0
//! LED #0 pin definition (BLUE).
#define LED_1_NAME    "green LED D1"
#define LED1_GPIO     (PIO_PA3_IDX)
#define LED1_FLAGS    (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LED1_ACTIVE_LEVEL 0

//! UART pins (UTXD0 and URXD0) definitions, PA8,9.
#define PINS_UART		(PIO_PA8A_URXD | PIO_PA9A_UTXD)
#define PINS_UART_FLAGS	(PIO_PERIPH_A | PIO_DEFAULT)

#define PINS_UART_MASK	(PIO_PA8A_URXD | PIO_PA9A_UTXD)
#define PINS_UART_PIO	PIOA
#define PINS_UART_ID	ID_PIOA
#define PINS_UART_TYPE	PIO_PERIPH_A
#define PINS_UART_ATTR	PIO_DEFAULT

/*! USART0 pin RX */
#define PIN_USART0_RXD			{PIO_PA10A_RXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RXD_IDX        (PIO_PA10_IDX)
#define PIN_USART0_RXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)
/*! USART0 pin TX */
#define PIN_USART0_TXD			{PIO_PA11A_TXD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD_IDX        (PIO_PA11_IDX)
#define PIN_USART0_TXD_FLAGS      (PIO_PERIPH_A | PIO_DEFAULT)


#endif // USER_BOARD_H
