#ifndef CC1101_PORT_H
#define CC1101_PORT_H

#include "compiler.h"
#include "portmacro.h"

void spi_set_clock_configuration(uint8_t configuration);

void MRFI_SPI_DRIVE_CSN_LOW(void);

void MRFI_SPI_DRIVE_CSN_HIGH(void);

void Mrfi_DelayUsec(uint16_t howlong);

#endif
