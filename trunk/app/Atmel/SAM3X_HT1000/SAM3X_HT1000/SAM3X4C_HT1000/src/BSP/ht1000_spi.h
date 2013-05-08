#ifndef HT1000_SPI_H
#define HT1000_SPI_H

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

void spi_slave_initialize(void);

void spi_master_initialize(void);

void spi_set_clock_configuration(uint8_t configuration);

void spi_master_transfer(void *p_buf, uint32_t size);

void spi_master_go(void);

void spi_csn0_disable(void);

void spi_csn0_enable(void);

void spi_soft_transfer(void *p_buf, uint32_t size);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif
