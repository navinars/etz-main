
#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_spi.h"
#include "RfTranceiver.h"

// From module: FreeRTOS mini Real-Time Kernel
#include <FreeRTOS.h>
#include "task.h"
#include "status_codes.h"

/* Chip select. */
#define SPI_CHIP_SEL 0

/* Clock polarity. */
#define SPI_CLK_POLARITY 1

/* Clock phase. */
#define SPI_CLK_PHASE 0

/* Delay before SPCK. */
#define SPI_DLYBS 0x40

/* Delay between consecutive transfers. */
#define SPI_DLYBCT 0x10

/* SPI clock configuration. */
static const uint32_t gs_ul_clock_configurations[] =
{ 500000, 1000000, 2000000, 5000000 };


void button_handler(uint32_t id, uint32_t mask)
{
	if ((CC1101_INT_ID == id) && (CC1101_INT_PIN_MSK == mask)) {
		CC1101_Receive_Packet();
	}
}

/**
 *  \brief Configure the push button.
 *
 *  Configure the PIOs as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
void configure_cc1101_int(void)
{
	/* Configure PIO clock. */
	//pmc_enable_periph_clk(CC1101_INT_ID);

	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	//pio_set_debounce_filter(CC1101_INT_PIO, CC1101_INT_PIN_MSK, 10);

	/* Initialize pios interrupt handlers, see PIO definition in board.h. */
	pio_handler_set(CC1101_INT_PIO, CC1101_INT_ID, CC1101_INT_PIN_MSK,
					CC1101_INT_ATTR, button_handler);
	
	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)CC1101_INT_ID);
	
	/* Enable PIO line interrupts. */
	pio_enable_interrupt(CC1101_INT_PIO, CC1101_INT_PIN_MSK);
}

/**
 * \brief Initialize SPI as master.
 */
static void spi_master_initialize(void)
{
	puts("-I- Initialize SPI as master\r");

	/* Configure an SPI peripheral. */
	spi_enable_clock(SPI_MASTER_BASE);
	spi_disable(SPI_MASTER_BASE);
	spi_reset(SPI_MASTER_BASE);
	spi_set_lastxfer(SPI_MASTER_BASE);
	spi_set_master_mode(SPI_MASTER_BASE);
	spi_disable_mode_fault_detect(SPI_MASTER_BASE);
	spi_set_peripheral_chip_select_value(SPI_MASTER_BASE, SPI_CHIP_SEL);
	spi_set_clock_polarity(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_MASTER_BASE, SPI_CHIP_SEL,
								SPI_CSR_BITS_8_BIT);
	spi_set_baudrate_div(SPI_MASTER_BASE, SPI_CHIP_SEL,
						(sysclk_get_cpu_hz() / gs_ul_spi_clock));
	spi_set_transfer_delay(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_DLYBS,
							SPI_DLYBCT);
	spi_enable(SPI_MASTER_BASE);
}

/**
 * \brief Set the specified SPI clock configuration.
 *
 * \param configuration  Index of the configuration to set.
 */
void spi_set_clock_configuration(uint8_t configuration)
{
	gs_ul_spi_clock = gs_ul_clock_configurations[configuration];
	printf("Setting SPI clock #%lu ... \n\r", (unsigned long)gs_ul_spi_clock);
	spi_master_initialize();
}

/**
 * \brief Perform SPI master transfer.
 *
 * \param pbuf Pointer to buffer to transfer.
 * \param size Size of the buffer.
 */
static void spi_master_transfer(void *p_buf, uint32_t size)
{
	uint32_t i;
	uint8_t uc_pcs;
	static uint16_t data;

	uint8_t *p_buffer;

	p_buffer = p_buf;

	for (i = 0; i < size; i++) {
		spi_write(SPI_MASTER_BASE, p_buffer[i], 0, 0);
		/* Wait transfer done. */
		while ((spi_read_status(SPI_MASTER_BASE) & SPI_SR_RDRF) == 0);
		spi_read(SPI_MASTER_BASE, &data, &uc_pcs);
		p_buffer[i] = data;
	}
}

void Enable_CC1101(void)
{
	gpio_set_pin_low(SPI0_NPCS0_GPIO);
}

void Disable_CC1101(void)
{
	gpio_set_pin_high(SPI0_NPCS0_GPIO);
}

uint8_t CC1101_Check_So(void)
{
	while(gpio_pin_is_high(SPI0_MISO_GPIO));
	
	return 0;
}

void APIWriteByte(uint8_t data)
{
	spi_master_transfer(&data, 1);
}

void APIWriteArrayBytes(uint8_t *buf, uint8_t cnt)
{
	spi_master_transfer(buf, cnt);
}

uint8_t APIReadByte(void)
{
	uint8_t tmp;
	
	spi_master_transfer(&tmp, 1);
	
	return tmp;
}

uint8_t Check_Rf_Level(void)
{
	return gpio_pin_is_high(SPI0_MISO_GPIO);
}

portTASK_FUNCTION(vAppSpiTask, pvParameters)
{
	(void)pvParameters;
	
//	configure_cc1101_int();
	
	CC1101_Initialization();
	
	for(;;)
	{
		vTaskDelay(1000);
	}
}

void vStartSpiTaskLauncher( unsigned portBASE_TYPE uxPriority )
{
	/* Spawn the Sentinel task. */
	xTaskCreate( vAppSpiTask, (const signed portCHAR *)"SPILAUNCH",
				configMINIMAL_STACK_SIZE, NULL, uxPriority,
				(xTaskHandle *)NULL );
}
