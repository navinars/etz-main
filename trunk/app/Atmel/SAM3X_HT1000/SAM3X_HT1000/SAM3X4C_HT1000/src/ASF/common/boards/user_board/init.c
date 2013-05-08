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
	
	/* Configure LED pins */
	gpio_configure_pin(LED0_GPIO, LED0_FLAGS);
	
	/* Configure UART pins */
	gpio_configure_group(PINS_UART_PIO, PINS_UART, PINS_UART_FLAGS);
	
	/* Configure USART RXD pin */
	gpio_configure_pin(PIN_USART1_RXD_IDX, PIN_USART1_RXD_FLAGS);
	
	/* Configure USART TXD pin */
	gpio_configure_pin(PIN_USART1_TXD_IDX, PIN_USART1_TXD_FLAGS);
	
	/* Configure SPI1 pins */
	gpio_configure_pin(SPI0_MOSI_GPIO, PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
	gpio_configure_pin(SPI0_SPCK_GPIO, PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
	
	/* Set direction and pullup on the given button IOPORT */
	ioport_set_pin_dir(SPI0_MISO_GPIO, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(SPI0_MISO_GPIO, IOPORT_MODE_PULLUP);
	
	gpio_configure_pin(SPI0_NPCS0_GPIO, PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
}
