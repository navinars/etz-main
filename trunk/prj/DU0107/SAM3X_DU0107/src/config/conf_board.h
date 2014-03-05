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
#define TASK_ETH_INT_STACK_SIZE			(configMINIMAL_STACK_SIZE + 50)
#define TASK_TCP_SERVER_STACK_SIZE		(configMINIMAL_STACK_SIZE + 150)
#define TASK_RADIO_STACK_SIZE			(configMINIMAL_STACK_SIZE + 150)
#define TASK_UART_STACK_SIZE			(configMINIMAL_STACK_SIZE + 150)


/*******************************************************************************
                              任务优先级
*******************************************************************************/
#define TASK_START_PRIORITY				(tskIDLE_PRIORITY + 1)
#define TASK_START_ETH_PRIORITY			(tskIDLE_PRIORITY + 2)
#define TASK_TCP_SERVER_PRIORITY		(tskIDLE_PRIORITY + 13)
#define TASK_RADIO_HANDLE_PRIORITY		(tskIDLE_PRIORITY + 14)
#define TASK_UART_HANDLE_PRIORITY		(tskIDLE_PRIORITY + 12)


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

/* Internal Flash 0 base address. */
#define IFLASH_ADDR						IFLASH0_ADDR
/* Internal flash page size. */
#define IFLASH_PAGE_SIZE				IFLASH0_PAGE_SIZE

/* Last page start address. */
#define LAST_PAGE_ADDRESS				(IFLASH1_ADDR + IFLASH1_SIZE - IFLASH1_PAGE_SIZE)

#define RS232printf						//printf

#define BOART_ID_USART0					ID_USART0
#define BOARD_USART0					USART0

#define BOARD_UART						UART

#endif // CONF_BOARD_H
