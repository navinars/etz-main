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
                              �����ջ��С����
*******************************************************************************/
#define TASK_START_STACKSIZE			(configMINIMAL_STACK_SIZE + 50)
#define TASK_LED_STACK_SIZE				(configMINIMAL_STACK_SIZE + 50)
#define TASK_ETH_INT_STACK_SIZE			(configMINIMAL_STACK_SIZE + 50)
#define TASK_LWIP_TCP_STACK_SIZE		(configMINIMAL_STACK_SIZE + 160)
#define TASK_TCP_SERVER_STACK_SIZE		(configMINIMAL_STACK_SIZE + 150)


/*******************************************************************************
                              �������ȼ�
*******************************************************************************/
#define TASK_START_PRIORITY				(tskIDLE_PRIORITY + 9)
#define TASK_ETH_INT_PRIORITY			(tskIDLE_PRIORITY + 8)
#define TASK_TCPIP_PRIORITY				(tskIDLE_PRIORITY + 7)
#define TASK_TCP_SERVER_PRIORITY		(tskIDLE_PRIORITY + 4)
#define TASK_LED_PRIORITY				(tskIDLE_PRIORITY + 3)


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

/** EMAC PHY address */
#define BOARD_EMAC_PHY_ADDR  0
/*! EMAC RMII mode */
#define BOARD_EMAC_MODE_RMII 1

#endif // CONF_BOARD_H