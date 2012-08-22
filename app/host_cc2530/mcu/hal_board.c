/***********************************************************************************
  Filename:     hal_board.c

  Description:  HAL board peripherals library for the
                SmartRF05EB + CC2430EM/CC2531EM/CC2510/CC1110 platforms
***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "hal_types.h"
#include "hal_defs.h"
#include "hal_digio.h"
#include "hal_int.h"
#include "hal_mcu.h"
#include "hal_clock.h"
#include "hal_board.h"
#include "hal_led.h"

#include "sfr-bits.h"

/* Sleep timer runs on the 32k RC osc. */
/* One clock tick is 7.8 ms */
#define TICK_VAL (32768/128)  /* 256 */


/***********************************************************************************
* LOCAL FUNCTIONS
*/

/***********************************************************************************
* GLOBAL VARIABLES
*/
/* Do NOT remove the absolute address and do NOT remove the initialiser here */
__xdata static unsigned long timer_value = 0;


/***********************************************************************************
* GLOBAL FUNCTIONS
*/

/***********************************************************************************
* @fn      halBoardInit
*
* @brief   Set up board. Initialize MCU, configure I/O pins and user interfaces
*
* @param   none
*
* @return  none
*/
void halBoardInit(void)
{
    halMcuInit();			// Initialise mcu clock.
	
	halLedInit();			// Initialise LED.
	
	clock_init();			// Initialise sleep timer.
	
    halIntOn();				// Global interrupt is enable.
}

/* ------------------------------------------------------------------------------------------------------
 * @fn		clock_init
 *
 * @brief
 *
 */
void clock_init(void)
{
	/* Tickspeed 500 kHz for timers[1-4] */
	CLKCONCMD |= CLKCONCMD_TICKSPD2 | CLKCONCMD_TICKSPD1;
	while(CLKCONSTA != CLKCONCMD);
	
	/* Initialize tick value */
	timer_value = ST0;
	timer_value += ((unsigned long int) ST1) << 8;
	timer_value += ((unsigned long int) ST2) << 16;
	timer_value += TICK_VAL;
	ST2 = (unsigned char) (timer_value >> 16);
	ST1 = (unsigned char) (timer_value >> 8);
	ST0 = (unsigned char) timer_value;
	
//	STIE = 1; /* IEN0.STIE interrupt enable */
}

/* ------------------------------------------------------------------------------------------------------
 * @fn		HAL_ISR_FUNCTION
 *
 * @brief
 *
 */
HAL_ISR_FUNCTION( stIsr, ST_VECTOR )
{
	halIntOff();
	
	timer_value = ST0;
	timer_value += ((unsigned long int) ST1) << 8;
	timer_value += ((unsigned long int) ST2) << 16;
	timer_value += TICK_VAL;
	ST2 = (unsigned char) (timer_value >> 16);
	ST1 = (unsigned char) (timer_value >> 8);
	ST0 = (unsigned char) timer_value;
	
	halIntOn();
}
