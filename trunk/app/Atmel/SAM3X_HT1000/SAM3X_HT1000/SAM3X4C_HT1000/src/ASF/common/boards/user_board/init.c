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
	uint8_t i = 0;
	
	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	sysclk_enable_peripheral_clock(ID_PIOA);
	//sysclk_enable_peripheral_clock(ID_PIOB);
	//
	//for(i = 0;i < PIO_PB31_IDX;i ++)
	//{
		//gpio_configure_pin(i, PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
	//}
	
	/* Configure LED pins */
	gpio_configure_pin(LED0_GPIO, LED0_FLAGS);
	
	/* Configure UART pins */
	gpio_configure_group(PINS_UART_PIO, PINS_UART, PINS_UART_FLAGS);
	
	/* Configure USART RXD pin */
	gpio_configure_pin(PIN_USART1_RXD_IDX, PIN_USART1_RXD_FLAGS);
	
	/* Configure USART TXD pin */
	gpio_configure_pin(PIN_USART1_TXD_IDX, PIN_USART1_TXD_FLAGS);
	
	/* Configure SPI1 pins */
	gpio_configure_pin(SPI0_MISO_GPIO, (PIO_INPUT | PIO_PULLUP));
	gpio_configure_pin(SPI0_MOSI_GPIO, PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
	gpio_configure_pin(SPI0_SPCK_GPIO, PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
	
	gpio_configure_pin(SPI0_NPCS0_GPIO, PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT);
}
