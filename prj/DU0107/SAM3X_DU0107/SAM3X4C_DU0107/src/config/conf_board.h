/**
 * \file
 *
 * \brief User board configuration template
 *
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

/*----------------------------------------------------------------------------*/
/**
 *  \page FreeRTOS task options
 *  This page lists several definition related to the board operating frequency
 *
 *  \section Definitions
 *  - \ref BOARD_FREQ_*
 *  - \ref BOARD_MCK
 */
/*******************************************************************************
                              任务堆栈大小定义
*******************************************************************************/
#define TASK_START_STACKSIZE			(configMINIMAL_STACK_SIZE + 50)
#define TASK_LED_STACK_SIZE				(configMINIMAL_STACK_SIZE + 50)
#define TASK_ETH_INT_STACK_SIZE			(configMINIMAL_STACK_SIZE + 50)
#define TASK_TCP_SERVER_STACK_SIZE		(configMINIMAL_STACK_SIZE + 550)


/*******************************************************************************
                              任务优先级
*******************************************************************************/
#define TASK_START_PRIORITY				(tskIDLE_PRIORITY + 19)
#define TASK_LED_PRIORITY				(tskIDLE_PRIORITY + 18)
#define TASK_START_ETH_PRIORITY			(tskIDLE_PRIORITY + 17)
#define TASK_TCP_SERVER_PRIORITY		(tskIDLE_PRIORITY + 16)
#define TASK_SPI_HANDLE_PRIORITY		(tskIDLE_PRIORITY + 15)


/**
 * \file
 * EMAC
 *
 * - BOARD_EMAC_PHY_ADDR: Phy MAC address
 * - BOARD_EMAC_MODE_RMII: Enable RMII connection with the PHY
 */
#define PIN_EEMAC_EREFCK      PIO_PB0_IDX
#define PIN_EMAC_ETXEN        PIO_PB1_IDX
#define PIN_EMAC_ETX0         PIO_PB2_IDX
#define PIN_EMAC_ETX1         PIO_PB3_IDX
#define PIN_EMAC_ECRSDV       PIO_PB4_IDX
#define PIN_EMAC_ERX0         PIO_PB5_IDX
#define PIN_EMAC_ERX1         PIO_PB6_IDX
#define PIN_EMAC_ERXER        PIO_PB7_IDX
#define PIN_EMAC_EMDC         PIO_PB8_IDX
#define PIN_EMAC_EMDIO        PIO_PB9_IDX
#define PIN_EMAC_FLAGS        PIO_PERIPH_A | PIO_DEFAULT

/* ------------------------------------------------------------------------ */
/* SPI                                                                      */
/* ------------------------------------------------------------------------ */
/*! SPI0 MISO pin definition. */
#define SPI0_MISO_GPIO        (PIO_PA25_IDX)
#define SPI0_MISO_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)
#define SPI0_MISO_PORT		  (IOPORT_PIOA)
#define SPI0_MISO_MASK		  (PIO_PA25)

/*! SPI0 MOSI pin definition. */
#define SPI0_MOSI_GPIO        (PIO_PA26_IDX)
#define SPI0_MOSI_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)

/*! SPI0 SPCK pin definition. */
#define SPI0_SPCK_GPIO        (PIO_PA27_IDX)
#define SPI0_SPCK_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)

/*! SPI0 chip select 0 pin definition. (Only one configuration is possible) */
#define SPI0_NPCS0_GPIO            (PIO_PA28_IDX)
#define SPI0_NPCS0_FLAGS           (PIO_PERIPH_A | PIO_DEFAULT)

/** Push button pin definition. */
#define CC1101_GPIO0_PIO          PIOA
#define CC1101_INT_ID           ID_PIOA
#define CC1101_GPIO0			(1 << 23)
#define CC1101_INT_ATTR         (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)
#define CC1101_GPIO0_GPIO		(PIO_PA23_IDX)
#define CC1101_GPIO0_FLAGS      (PIO_INPUT | PIO_PULLUP)

/** Enable Com Port. */
#define CONF_BOARD_UART_CONSOLE

/** Usart Hw ID used by the console (UART). */
#define CONSOLE_UART_ID          ID_UART

/** SPI0 MACRO definition */
#define CONF_BOARD_SPI0

/** SPI0 slave select0 MACRO definition */
#define CONF_BOARD_SPI0_NPCS0

/** Spi Hw ID . */
#define SPI_ID          ID_SPI0

/** SPI base address for SPI master mode*/
#define SPI_MASTER_BASE      SPI0
/** SPI base address for SPI slave mode, (on different board) */
#define SPI_SLAVE_BASE       SPI0
/** EMAC PHY address */
#define BOARD_EMAC_PHY_ADDR  0
/*! EMAC RMII mode */
#define BOARD_EMAC_MODE_RMII 1

#define RS232printf					//printf

#endif // CONF_BOARD_H
