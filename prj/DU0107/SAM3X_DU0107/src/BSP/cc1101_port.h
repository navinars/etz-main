#ifndef CC1101_PORT_H
#define CC1101_PORT_H

#include "compiler.h"
#include "portmacro.h"

void spi_set_clock_configuration(uint8_t configuration);

void Spi_CsLow(void);

void Spi_CsHigh(void);

void Mrfi_DelayUsec(uint16_t howlong);

uint8_t SPI_CheckGpio1(void);

uint8_t Spi_WriteByte(uint8_t data);

void Spi_WriteArrayBytes(uint8_t *buf, uint8_t cnt);

uint8_t APIReadByte(void);

uint8_t Spi_CheckGpio0(void);

void Mifi_ConfigInt(void);
void Mifi_DisableInt(void);
void Mifi_EnableInt(void);
#endif
