#ifndef _CC1101_H
#define _CC1101_H

void gpio_init(void);

uint8_t Radio_Transmit(uint8_t * pPacket, uint8_t len);

void cc1101_init(void);

uint8_t Mrfi_SpiCmdStrobe(uint8_t cmd);

uint8_t Mrfi_SpiWriteTxFifo(uint8_t * pData, uint8_t len);

uint8_t Mrfi_SpiReadRxFifo(uint8_t * pData, uint8_t len);

uint8_t Mrfi_SpiReadReg(uint8_t addr);

void Mrfi_SpiWriteReg(uint8_t addr, uint8_t value);

#endif