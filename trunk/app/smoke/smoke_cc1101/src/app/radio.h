/*! @file radio.h
 * @brief This file is the interface file for basic HMI functions.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#ifndef RADIO_H_
#define RADIO_H_

/*****************************************************************************
 *  Global Macros & Definitions
 *****************************************************************************/
#define EZCONFIG_RADIO_CFG_SIZE 211u

/*****************************************************************************
 *  Global Typedefs & Enums
 *****************************************************************************/
typedef struct
{
    U8   EzConfig_Array[EZCONFIG_RADIO_CFG_SIZE];
    U16  EzConfig_Array_CRC;

    U8   Radio_BOOT_OPTIONS;
    U8   Radio_XTAL_OPTIONS;
    U32  Radio_XO_FREQ;

    U8   Radio_INT_CTL_ENABLE;
    U8   Radio_INT_CTL_PH_ENABLE;
    U8   Radio_INT_CTL_MODEM_ENABLE;
    U8   Radio_INT_CTL_CHIP_ENABLE;

    U8   Radio_FRR_CTL_A_MODE;
    U8   Radio_FRR_CTL_B_MODE;
    U8   Radio_FRR_CTL_C_MODE;
    U8   Radio_FRR_CTL_D_MODE;

    U8   Radio_SYNC_BITS_31_24;
    U8   Radio_SYNC_BITS_23_16;

    U8   Radio_PA_PWR_LVL;

    U8   Radio_EZCONFIG_MODULATION;
    U8   Radio_EZCONFIG_XO_TUNE;

    U8   Radio_FREQ_CONTROL_INTE;
    U8   Radio_FREQ_CONTROL_FRAC_2;
    U8   Radio_FREQ_CONTROL_FRAC_1;
    U8   Radio_FREQ_CONTROL_FRAC_0;

    U8   Radio_FREQ_CONTROL_CHANNEL_STEP_SIZE_1;
    U8   Radio_FREQ_CONTROL_CHANNEL_STEP_SIZE_0;

    U8   Radio_GPIO0_PIN_CFG;
    U8   Radio_GPIO1_PIN_CFG;
    U8   Radio_GPIO2_PIN_CFG;
    U8   Radio_GPIO3_PIN_CFG;
    U8   Radio_GPIO_NIRQ_MODE;
    U8   Radio_GPIO_SDO_MODE;
    U8   Radio_GPIO_GEN_CONFIG;

    U8   Radio_ChannelNumber;
    U8   Radio_PacketLength;
    U8   Radio_State_After_Power_Up;

    U16  Radio_Delay_Cnt_After_Reset;
} tRadioConfiguration;

/*****************************************************************************
 *  Global Variable Declarations
 *****************************************************************************/
extern SEGMENT_VARIABLE_SEGMENT_POINTER(pRadioConfiguration, tRadioConfiguration, CODE, CODE);

/*****************************************************************************
 *  Global Function Declarations
 *****************************************************************************/
void  vRadio_Init(void);
void  vRadio_StartRX(U8);
void  vRadio_StartTx(U8, U8 *);
U8    bRadio_Check_Ezconfig(U16);

#endif /* RADIO_H_ */
