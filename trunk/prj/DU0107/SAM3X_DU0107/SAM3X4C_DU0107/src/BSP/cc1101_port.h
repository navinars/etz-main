#ifndef CC1101_PORT_H
#define CC1101_PORT_H

#include "compiler.h"
#include "portmacro.h"

/* ------------------------------------------------------------------------------------------------
 *                                          Defines
 * ------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------
 *                                         Prototypes
 * ------------------------------------------------------------------------------------------------
 */
void spi_set_clock_configuration(uint8_t configuration);

void MRFI_SPI_DRIVE_CSN_LOW(void);

void MRFI_SPI_DRIVE_CSN_HIGH(void);

void Mrfi_DelayUsec(uint16_t howlong);

uint8_t MRFI_SPI_SO_IS_HIGH(void);
uint8_t mrfiSpiWriteByte(uint8_t data);
void APIWriteArrayBytes(uint8_t *buf, uint8_t cnt);
uint8_t APIReadByte(void);
uint8_t Check_Rf_Level(void);
void BSP_ENABLE_INTERRUPTS(void);
#endif
