/*! @file radio.c
 * @brief This file contains functions to manage behavior of basic human module interfaces (push-buttons, switches, LEDs).
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#include "bsp.h"

/*****************************************************************************
 *  Local Macros & Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variables
 *****************************************************************************/
SEGMENT_VARIABLE(RadioConfiguration, tRadioConfiguration, CODE) = \
                        RADIO_CONFIGURATION_DATA;

SEGMENT_VARIABLE_SEGMENT_POINTER(pRadioConfiguration, tRadioConfiguration, CODE, CODE) = \
                        &RadioConfiguration;
	 
/*****************************************************************************
 *  Local Function Declarations
 *****************************************************************************/
void vRadio_PowerUp(void);
/*!
 *  Power up the Radio, set GPIOs to HiZ state, get Part Info
 *  then set Sleep mode.
 *
 *  @note
 *
 */
void vRadio_PowerUp(void)
{
  SEGMENT_VARIABLE(wDelay, U16, XDATA) = 0u;

  si4455_reset();
  for (; wDelay < pRadioConfiguration->Radio_Delay_Cnt_After_Reset; wDelay++);

  si4455_power_up(pRadioConfiguration->Radio_BOOT_OPTIONS,
                  pRadioConfiguration->Radio_XTAL_OPTIONS,
                  pRadioConfiguration->Radio_XO_FREQ);

  radio_comm_PollCTS();
}

/*!
 *  Radio Initialization.
 *
 *  @author Sz. Papp
 *
 *  @note
 *
 */
void vRadio_Init(void)
{
  U16 lTemp;

#if (RADIO_CONFIGURATION_DATA_RADIO_PATCH_INCLUDED > 0x00)
  const SEGMENT_VARIABLE(RadioPatch[RADIO_CONFIGURATION_DATA_RADIO_PATCH_SIZE], U8, CODE) = \
      RADIO_CONFIGURATION_DATA_RADIO_PATCH;

#endif

  do
  {
    /* Power Up the radio chip */
    vRadio_PowerUp();

    /* Load the 1st part of the configuration array (128 bytes) */
    si4455_write_ezconfig_array(128u, pRadioConfiguration->EzConfig_Array);

    /* Delay between two part to let the radio process the incoming data */
    for (lTemp = 0x07FF; lTemp; lTemp--)  ;

    /* Load the final part of the configuration array (128 bytes) */
    si4455_write_ezconfig_array(EZCONFIG_RADIO_CFG_SIZE - 128u, (U8 *) pRadioConfiguration->EzConfig_Array + 128u);

    lTemp = bRadio_Check_Ezconfig(pRadioConfiguration->EzConfig_Array_CRC);

    /* Check the return value */
//    if (lTemp == 1u) { LED4 = !LED4; }
//    if (lTemp == 2u) { LED3 = !LED3; }
  } while(lTemp != 0u);

  // Read ITs, clear pending ones
  si4455_get_int_status(0u, 0u, 0u);

  /* Set XO TUNE */
  si4455_set_property(
      SI4455_PROP_GRP_ID_EZCONFIG,
      SI4455_PROP_GRP_LEN_EZCONFIG,
      SI4455_PROP_GRP_INDEX_EZCONFIG_XO_TUNE,
      (U8) pRadioConfiguration->Radio_EZCONFIG_XO_TUNE
  );

  /* Enable ITs */
  si4455_set_property(
      SI4455_PROP_GRP_ID_INT_CTL,
      SI4455_PROP_GRP_LEN_INT_CTL,
      SI4455_PROP_GRP_INDEX_INT_CTL_ENABLE,
      (U8) pRadioConfiguration->Radio_INT_CTL_ENABLE,
      (U8) pRadioConfiguration->Radio_INT_CTL_PH_ENABLE,
      (U8) pRadioConfiguration->Radio_INT_CTL_MODEM_ENABLE,
      (U8) pRadioConfiguration->Radio_INT_CTL_CHIP_ENABLE
  );

  // Configure Fast response registers
  si4455_set_property(
      SI4455_PROP_GRP_ID_FRR_CTL,
      SI4455_PROP_GRP_LEN_FRR_CTL,
      SI4455_PROP_GRP_INDEX_FRR_CTL_A_MODE,
      (U8) pRadioConfiguration->Radio_FRR_CTL_A_MODE,
      (U8) pRadioConfiguration->Radio_FRR_CTL_B_MODE,
      (U8) pRadioConfiguration->Radio_FRR_CTL_C_MODE,
      (U8) pRadioConfiguration->Radio_FRR_CTL_D_MODE
  );

  // Configure GPIO pins
  si4455_gpio_pin_cfg(
      pRadioConfiguration->Radio_GPIO0_PIN_CFG,
      pRadioConfiguration->Radio_GPIO1_PIN_CFG,
      pRadioConfiguration->Radio_GPIO2_PIN_CFG,
      pRadioConfiguration->Radio_GPIO3_PIN_CFG,
      pRadioConfiguration->Radio_GPIO_NIRQ_MODE,
      pRadioConfiguration->Radio_GPIO_SDO_MODE,
      pRadioConfiguration->Radio_GPIO_GEN_CONFIG
  );

  // Put the Radio into configured state
  si4455_change_state(pRadioConfiguration->Radio_State_After_Power_Up);

  // Read ITs, clear pending ones
  si4455_get_int_status(0u, 0u, 0u);
}

/*!
 *  Set Radio to RX mode, fixed packet length.
 *
 *  @param channel Freq. Channel
 *
 *  @note
 *
 */
void vRadio_StartRX(U8 channel)
{
  // Read ITs, clear pending ones
  si4455_get_int_status(0u, 0u, 0u);

  /* Start Receiving packet, channel 0, START immediately, Packet n bytes long */
  si4455_start_rx(channel, 0u, RadioConfiguration.Radio_PacketLength,
                  SI4455_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_RX,
                  SI4455_CMD_START_RX_ARG_RXVALID_STATE_ENUM_RX,
                  SI4455_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX );
}

/*!
 *  Set Radio to TX mode, fixed packet length.
 *
 *  @param channel Freq. Channel, Packet to be sent
 *
 *  @note
 *
 */
void  vRadio_StartTx(U8 channel, U8 *pioFixRadioPacket)
{
  // Read ITs, clear pending ones
  si4455_get_int_status(0u, 0u, 0u);

  /* Start sending packet on channel, START immediately, Packet according to PH */
  si4455_start_tx(channel, 0u,  0u);
}


/*!
 * Check if EzConfig Array sent to the radio chip correctly.
 *
 * @param[in] crc CRC of the EZCONFIG array.
 *
 * @return    Respons from the radio chip.
 *
 * @note
 *
 */
U8 bRadio_Check_Ezconfig(U16 crc)
{
  si4455_ezconfig_check(crc);

  return radioCmd[0u];
}
