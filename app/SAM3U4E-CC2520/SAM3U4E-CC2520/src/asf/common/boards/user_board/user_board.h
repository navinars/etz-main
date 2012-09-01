/**
 * \file
 *
 * \brief User board definition template
 *
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

/* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL		(32768U)
#define BOARD_FREQ_SLCK_BYPASS		(32768U)
#define BOARD_FREQ_MAINCK_XTAL		(12000000U)
#define BOARD_FREQ_MAINCK_BYPASS	(12000000U)

/** Master clock frequency */
#define BOARD_MCK					CHIP_FREQ_CPU_MAX

/*----------------------------------------------------------------------------*/
/**
 * \page sam3u_ek_board_info SAM3U-EK - Board informations
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 * - \ref sam3uek
 * - \ref sam3u
 * - \ref cortexm3
 */

/** Name of the board */
#define BOARD_NAME "SAM3U-EK"
/** Board definition */
#define sam3uek
/** Family definition (already defined) */
#define sam3u
/** Core definition */
#define cortexm3

#define CONSOLE_UART			   UART

#endif // USER_BOARD_H
