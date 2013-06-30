#ifndef CC1101_PORT_H
#define CC1101_PORT_H

#include "stdint.h"

/* ------------------------------------------------------------------------------------------------
 *                                          Defines
 * ------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------
 *                                         Prototypes
 * ------------------------------------------------------------------------------------------------
 */
void spi_set_clock_configuration(uint8_t configuration);

void SPI_DRIVE_CSN_LOW(void);

void SPI_DRIVE_CSN_HIGH(void);

void Mrfi_DelayUsec(uint16_t howlong);

uint8_t SPI_SO_IS_HIGH(void);
uint8_t SpiWriteByte(uint8_t data);
void SPIWriteArrayBytes(uint8_t *buf, uint8_t cnt);
uint8_t APIReadByte(void);
uint8_t Spi_CheckGpio0(void);
void Mifi_ConfigInt(void);
#endif
