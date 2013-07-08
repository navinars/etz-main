#ifndef _CC1101_H
#define _CC1101_H


#define MISO			BIT1
#define MOSI			BIT2
#define CLK				BIT4
#define CSN				BIT5
#define GPIO0			BIT0

#define SPI_SCLK_H()	P1OUT |= CLK
#define SPI_SCLK_L()	P1OUT &=~CLK

#define SPI_MOSI_H()	P1OUT |= MOSI
#define SPI_MOSI_L()	P1OUT &=~MOSI

#define SPI_CSN_H()		P1OUT |= CSN
#define SPI_CSN_L()		P1OUT &=~CSN


uint8_t Radio_Transmit(uint8_t * pPacket, uint8_t len);

void cc1101_init(void);

uint8_t Mrfi_SpiCmdStrobe(uint8_t cmd);

uint8_t Mrfi_SpiWriteTxFifo(uint8_t * pData, uint8_t len);

uint8_t Mrfi_SpiReadRxFifo(uint8_t * pData, uint8_t len);

uint8_t Mrfi_SpiReadReg(uint8_t addr);

void Mrfi_SpiWriteReg(uint8_t addr, uint8_t value);

#endif