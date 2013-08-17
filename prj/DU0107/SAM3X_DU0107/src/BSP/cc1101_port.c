
#include <asf.h>
#include "stdio_serial.h"											// printf need this file.
#include "conf_clock.h"
#include "cc1101_port.h"
#include "cc1101_defs.h"
#include "cc1101_radio.h"
#include "string.h"

/* Chip select. */
#define SPI_CHIP_SEL 0

/* Clock polarity. */
#define SPI_CLK_POLARITY 0

/* Clock phase. */
#define SPI_CLK_PHASE 1

/* Delay before SPCK. */
#define SPI_DLYBS 0x40

/* Delay between consecutive transfers. */
#define SPI_DLYBCT 0x10

/* SPI clock configuration. */
static const uint32_t gs_ul_clock_configurations[] =
{ 500000, 1000000, 2000000, 5000000 };

static uint32_t gs_ul_spi_clock;

/**
 *  \brief GPIO0 handle function.
 *
 *  Configure the PIOs as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
extern void Radio_RcvHandler(void);
static void Radio_ISRhandler(uint32_t id, uint32_t mask)
{
	if ((CC1101_INT_ID == id) && (CC1101_GPIO0 == mask))			// GPIO0 interrupt 
	{
		Radio_RcvHandler();
		
		NVIC_EnableIRQ((IRQn_Type)CC1101_INT_ID);
	}
}

/**
 *  \brief Configure the push button.
 *
 *  Configure the PIOs as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
void Mifi_ConfigInt(void)
{
	/* Configure PIO clock. */
	//pmc_enable_periph_clk(CC1101_INT_ID);
	
	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	//pio_set_debounce_filter(CC1101_INT_PIO, CC1101_INT_PIN_MSK, 10);
	
	/* Initialize pios interrupt handlers, see PIO definition in board.h. */
	pio_handler_set(CC1101_GPIO0_PIO, CC1101_INT_ID, CC1101_GPIO0,
					CC1101_INT_ATTR, Radio_ISRhandler);
	
	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)CC1101_INT_ID);
	
	/* Enable PIO line interrupts. */
	pio_enable_interrupt(CC1101_GPIO0_PIO, CC1101_GPIO0);
}

/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
void Mifi_DisableInt(void)
{
	/* Enable PIO line interrupts. */
	pio_disable_interrupt(CC1101_GPIO0_PIO, CC1101_GPIO0);
}

/**
 * \brief 
 * 
 * \param 
 * 
 * \return void
 */
void Mifi_EnableInt(void)
{
	/* Enable PIO line interrupts. */
	pio_enable_interrupt(CC1101_GPIO0_PIO, CC1101_GPIO0);
}

/**
 * \brief Initialize SPI as master.
 */
static void radioSpiInit(void)
{
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
	spi_set_bits_per_transfer(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CSR_BITS_8_BIT);
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
	//RS232printf("Setting SPI clock #%lu ... \n\r", (unsigned long)gs_ul_spi_clock);
	radioSpiInit();
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

/*-------------------------------------------------------------------------------------------------
 * @fn          Mrfi_DelayUsec
 *
 * @brief       delay us.
 *
 * @param       none
 *
 * @return      none
 *
 */
void Mrfi_DelayUsec(uint16_t howlong)
{
	uint16_t i;
	
	while(howlong --)
	{
		for(i = 0;i < 10000;i++)
		{
			asm("NOP");
		}
	}
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SPI_CSN_IS_LOW
 *
 * @brief       Low
 *
 * @param       none
 *
 * @return      none
 *
 */
void Spi_CsLow(void)
{
	gpio_set_pin_low(SPI0_NPCS0_GPIO);
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SPI_CSN_IS_HIGH
 *
 * @brief       HIGH
 *
 * @param       none
 *
 * @return      none
 *
 */
void Spi_CsHigh(void)
{
	gpio_set_pin_high(SPI0_NPCS0_GPIO);
}

/**
 * \brief Check GPIO1(SOMI) pin is high
 * 
 * \param none.
 * 
 * \return uint8_t SOMI pin is high return 1.
 */
uint8_t SPI_CheckGpio1(void)
{
	return gpio_pin_is_high(SPI0_MISO_GPIO);
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SPI_WRITE_BYTE
 *
 * @brief       data
 *
 * @param       none
 *
 * @return      none
 *
 */
uint8_t Spi_WriteByte(uint8_t data)
{
	uint8_t tmp;
	tmp = data;
	spi_master_transfer(&tmp, 1);
	return tmp;
}

/*-------------------------------------------------------------------------------------------------
 * @fn          APIWriteArrayBytes
 *
 * @brief       data
 *
 * @param       none
 *
 * @return      none
 *
 */
void Spi_WriteArrayBytes(uint8_t *buf, uint8_t cnt)
{
	uint8_t *p;
	p = buf;
	spi_master_transfer(p, cnt);
}

/*-------------------------------------------------------------------------------------------------
 * @fn          Check_Rf_Level
 *
 * @brief       data
 *
 * @param       none
 *
 * @return      none
 *
 */
uint8_t Spi_CheckGpio0(void)
{
	return gpio_pin_is_high(CC1101_GPIO0_GPIO);
}
