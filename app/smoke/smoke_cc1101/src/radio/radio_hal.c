/*!
 * File:
 *  radio_hal.c
 *
 * Description:
 *  This file contains RADIO HAL.
 *
 * Silicon Laboratories Confidential
 * Copyright 2011 Silicon Laboratories, Inc.
 */

                /* ======================================= *
                 *              I N C L U D E              *
                 * ======================================= */

#include "bsp.h"


                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

                /* ======================================= *
                 *     G L O B A L   V A R I A B L E S     *
                 * ======================================= */

                /* ======================================= *
                 *      L O C A L   F U N C T I O N S      *
                 * ======================================= */

                /* ======================================= *
                 *     P U B L I C   F U N C T I O N S     *
                 * ======================================= */

void radio_hal_AssertShutdown(void)
{
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  RF_PWRDN = 1;
#else
  P2OUT |= BIT3;
#endif
}

void radio_hal_DeassertShutdown(void)
{
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  RF_PWRDN = 0;
#else
  P2OUT &=~BIT3;
#endif
}

void radio_hal_ClearNsel(void)
{
    P2OUT &=~BIT4;
}

void radio_hal_SetNsel(void)
{
    P2OUT |= BIT4;
}

U8 radio_hal_NirqLevel(void)
{
    return P2IN&BIT5;
}

void radio_hal_SpiWriteByte(U8 byteToWrite)
{
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  bSpi_ReadWriteSpi1(byteToWrite);
#else
  spi_readwrite(byteToWrite);
#endif
}

U8 radio_hal_SpiReadByte(void)
{
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  return bSpi_ReadWriteSpi1(0xFF);
#else
  return spi_readwrite(0xFF);
#endif
}

void radio_hal_SpiWriteData(U8 byteCount, U8* pData)
{
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  vSpi_WriteDataSpi1(byteCount, pData);
#else
  spi_write_buf(pData, byteCount);
#endif
}

void radio_hal_SpiReadData(U8 byteCount, U8* pData)
{
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  vSpi_ReadDataSpi1(byteCount, pData);
#else
  spi_write_buf(pData, byteCount);
#endif
}

#ifdef RADIO_DRIVER_EXTENDED_SUPPORT
BIT radio_hal_Gpio0Level(void)
{
#ifdef SILABS_PLATFORM_DKMB
  return 0;
#endif
#ifdef SILABS_PLATFORM_UDP
  return EZRP_RX_DOUT;
#endif
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB)
  return RF_GPIO0;
#endif
#if (defined SILABS_PLATFORM_WMB)
  return 0;
#endif
}

BIT radio_hal_Gpio1Level(void)
{
#ifdef SILABS_PLATFORM_DKMB
  return FSK_CLK_OUT;
#endif
#ifdef SILABS_PLATFORM_UDP
  return 0; //No Pop
#endif
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  return RF_GPIO1;
#endif
}

BIT radio_hal_Gpio2Level(void)
{
#ifdef SILABS_PLATFORM_DKMB
  return DATA_NFFS;
#endif
#ifdef SILABS_PLATFORM_UDP
  return 0; //No Pop
#endif
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  return RF_GPIO2;
#endif
}

BIT radio_hal_Gpio3Level(void)
{
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  return RF_GPIO3;
#else
  return 0;
#endif
}

#endif
