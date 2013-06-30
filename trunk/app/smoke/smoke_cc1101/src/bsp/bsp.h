/*! @file bsp.h
 * @brief This file contains application specific definitions and includes.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#ifndef BSP_H
#define BSP_H

/*------------------------------------------------------------------------*/
/*            Application specific includes                               */
/*------------------------------------------------------------------------*/
/*
#include "drivers\compiler_defs.h"
#include "platform_defs.h"
#include "hardware_defs.h"
*/

#include <string.h>
#include <stdint.h>

#include "msp430.h"
#include "gpio.h"
#include "spi.h"
#include "timer.h"

#include "hal_defs.h"
#include "hal_types.h"

#include "cc1101_port.h"
#include "cc1101_radio.h"
#include "radio_handle.h"
#include "cc1101_defs.h"

//#include "RfTranceiver.h"
/*
#include "radio_config.h"
#include "radio.h"

#include "radio_hal.h"
#include "radio_comm.h"

#include "si4455_api_lib.h"
#include "si4455_defs.h"
#include "si4455_nirq.h"
*/

#endif //BSP_H