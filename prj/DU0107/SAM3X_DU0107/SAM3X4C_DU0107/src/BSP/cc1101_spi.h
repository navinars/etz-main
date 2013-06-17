#ifndef CC1101_SPI_H
#define CC1101_SPI_H

#include "compiler.h"
#include "portmacro.h"

extern void spi_set_clock_configuration(uint8_t configuration);

extern void configure_button(void);

extern void Enable_CC1101(void);

extern void Disable_CC1101(void);

extern uint8_t CC1101_Check_So(void);

extern void APIWriteByte(uint8_t data);

extern void APIWriteArrayBytes(uint8_t *buf, uint8_t cnt);

extern uint8_t APIReadByte(void);

extern void configure_cc1101_int(void);

extern uint8_t Check_Rf_Level(void);

extern void vStartSpiTaskLauncher( unsigned portBASE_TYPE uxPriority );

#endif
