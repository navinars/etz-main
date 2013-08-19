
/* ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 *   MRFI (Minimal RF Interface)
 *   Include file for all MRFI services.
 * ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 */

#ifndef CC1101_RADIO_H
#define CC1101_RADIO_H

/* Radio States */
#define MRFI_RADIO_STATE_UNKNOWN  0
#define MRFI_RADIO_STATE_OFF      1
#define MRFI_RADIO_STATE_IDLE     2
#define MRFI_RADIO_STATE_RX       3

typedef enum _RF_Tx_Power_
{
	RF_TxPower_12dbm                  = 0xc0,
	RF_TxPower_10dbm                  = 0xc5,
	RF_TxPower_7dbm                   = 0xcd,
	RF_TxPower_5dbm                   = 0x86,
	RF_TxPower_0dbm                   = 0x50,
	RF_TxPower_N6dbm                  = 0x37,
	RF_TxPower_N10dbm                 = 0x26,
	RF_TxPower_N15dbm                 = 0x1d,
	RF_TxPower_N20dbm                 = 0x17,
	RF_TxPower_N30dbm                 = 0x03
}RF_Tx_Power;

typedef struct{
	uint8_t txFrame[10];
	uint8_t len;
}nwkPacket_t;



void Radio_Init(void);
uint8_t Mrfi_SpiReadReg(uint8_t addr);
void Mrfi_SpiWriteReg(uint8_t addr, uint8_t value);
uint8_t Mrfi_SpiReadRxFifo(uint8_t * pData, uint8_t len);
uint8_t Mrfi_SpiWriteTxFifo(uint8_t * pData, uint8_t len);
uint8_t Radio_Transmit(uint8_t * pPacket, uint8_t len);
uint8_t Mrfi_SpiCmdStrobe(uint8_t cmd);
void Radio_ClearRcvFifo(void);
uint8_t Radio_ReadFifo(uint8_t *pPacket);
void Radio_RcvMode(void);
#endif