/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "rn171.h"


/* Declare all global variables*/
xTaskHandle worker1_id;

struct usart_module usart_instance;


static void led_task (void *pvParameters)
{
	(void)pvParameters;

	for(;;)
	{
		
		vTaskDelay( 1000 );
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		vTaskDelay( 1000 );
		port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
	}
	/* Should never go there */
	vTaskDelete(worker1_id);
}

void configure_usart( void )
{
	//! [setup_config]
	struct usart_config config_usart;

	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = 9600;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;

	while (usart_init(&usart_instance,
		EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}

	usart_enable(&usart_instance);
}

int main (void)
{
	system_init();

	configure_usart();

	xTaskCreate(led_task, (signed char *) "LED task#1",
				configMINIMAL_STACK_SIZE+100,NULL, 2,& worker1_id);

	vTaskStartScheduler();

	// Insert application code here, after the board has been initialized.
	while(1);
}
