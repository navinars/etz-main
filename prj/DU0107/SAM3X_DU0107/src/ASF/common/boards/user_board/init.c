/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;

	/* Enable GPIOA clock.*/
	sysclk_enable_peripheral_clock(ID_PIOA);

	/* Configure LED#0 pins */
	gpio_configure_pin(LED0_GPIO, LED0_FLAGS);

	/* Configure LED#1 pins */
	gpio_configure_pin(LED1_GPIO, LED1_FLAGS);

	/* Configure UART pins */
	gpio_configure_group(PINS_UART_PIO, PINS_UART, PINS_UART_FLAGS);

	/* Configure USART RXD pin */
	gpio_configure_pin(PIN_USART0_RXD_IDX, PIN_USART0_RXD_FLAGS);

	/* Configure USART1 TXD pin */
	gpio_configure_pin(PIN_USART0_TXD_IDX, PIN_USART0_TXD_FLAGS);

	/* Configure USART1 RXD pin */
	gpio_configure_pin(PIN_USART1_RXD_IDX, PIN_USART1_RXD_FLAGS);

	/* Configure USART TXD pin */
	gpio_configure_pin(PIN_USART1_TXD_IDX, PIN_USART1_TXD_FLAGS);

	/* Configure Key pin init.*/
	gpio_configure_pin(RESTKEY_GPIO, (PIO_INPUT | PIO_PULLUP));

	/* Configure SPI0 pins */
	gpio_configure_pin(SPI0_MISO_GPIO, (PIO_PERIPH_A | PIO_DEFAULT));
	gpio_configure_pin(SPI0_MOSI_GPIO, (PIO_PERIPH_A | PIO_DEFAULT));
	gpio_configure_pin(SPI0_SPCK_GPIO, (PIO_PERIPH_A | PIO_DEFAULT));

	gpio_configure_pin(SPI0_NPCS0_GPIO, (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT));
	gpio_configure_pin(CC1101_GPIO0_GPIO, (PIO_INPUT | PIO_DEFAULT));

	/* Configure SMS pins */
	gpio_configure_pin(SMS_RESET_GPIO, SMS_RESET_FLAGS);
	gpio_configure_pin(SMS_CMD_GPIO, SMS_CMD_FLAGS);
	gpio_configure_pin( PIO_PA17_IDX, (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT) );
}
