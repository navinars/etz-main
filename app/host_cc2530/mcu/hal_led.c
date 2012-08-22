
/***********************************************************************************
  Filename:     hal_led.c

  Description:  hal led library

***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "hal_types.h"
#include "hal_led.h"
#include "hal_board.h"

/***********************************************************************************
* GLOBAL VARIABLES
*/
// Stores state of led 4
//volatile uint8 led4State=0;


/***********************************************************************************
* GLOBAL FUNCTIONS
*/

void halLedInit(void)
{
	MCU_IO_DIR_OUTPUT(HAL_BOARD_IO_LED_1_PORT, HAL_BOARD_IO_LED_1_PIN);

	MCU_IO_DIR_OUTPUT(HAL_BOARD_IO_LED_2_PORT, HAL_BOARD_IO_LED_2_PIN);
	
	halLedClear(1);
	halLedClear(2);
}

/***********************************************************************************
* @fn          halLedSet
*
* @brief       Turn LED on.
*
* @param       uint8 id - led to set
*
* @return      none
*/
void halLedSet(uint8 id)
{
    switch (id)
    {
    case 1: HAL_LED_SET_1(); break;
    case 2: HAL_LED_SET_2(); break;

    default: break;
    }
}


/***********************************************************************************
* @fn          halLedClear
*
* @brief       Turn LED off.
*
* @param       uint8 id - led to clear
*
* @return      none
*/
void halLedClear(uint8 id)
{
    switch (id)
    {
    case 1: HAL_LED_CLR_1(); break;
    case 2: HAL_LED_CLR_2(); break;
    default: break;
    }
}


/***********************************************************************************
* @fn          halLedToggle
*
* @brief       Change state of LED. If on, turn it off. Else turn on.
*
* @param       uint8 id - led to toggle
*
* @return      none
*/
void halLedToggle(uint8 id)
{
    switch (id)
    {
    case 1: HAL_LED_TGL_1(); break;
    case 2: HAL_LED_TGL_2(); break;
    default: break;
    }
}
