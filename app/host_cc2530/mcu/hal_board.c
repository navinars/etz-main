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
#include "hal_timer.h"
#include "hal_rf.h"

#include "sfr-bits.h"

#include "util_timer.h"

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
extern void EnterSleepModeDisableInterruptsOnWakeup(void);


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
//	while(CLKCONSTA != CLKCONCMD);
	while(!(CLKCONSTA & (CLKCONCMD_TICKSPD2 | CLKCONCMD_TICKSPD1)));
	
	PREFETCH_ENABLE();
	
	/* Initialize tick value */
	timer_value = ST0;
	timer_value += ((unsigned long int) ST1) << 8;
	timer_value += ((unsigned long int) ST2) << 16;
	timer_value += TICK_VAL;
	ST2 = (unsigned char) (timer_value >> 16);
	ST1 = (unsigned char) (timer_value >> 8);
	ST0 = (unsigned char) timer_value;
	
	STIF = 0;
	STIE = 1; /* Sleep timer interrupt enable */
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
	STIF = 0;
	STIE = 1;
	
	set_sleeptimer(TICK_VAL);
	
	halLedSet(1);
	
	halRfReceiveOn();
	
	/* Start Timer3, 100.*/
	HalTimerStart(HAL_TIMER_1, 3906*1);
	HalTimerStart(HAL_TIMER_3, 390);
//	pconflag = 1;
	halIntOn();
//	EnterSleepModeDisableInterruptsOnWakeup();
//	X_SLEEPCMD |= 0x02;
//	PCON = 0x01;
}

/* ------------------------------------------------------------------------------------------------------
 * @fn		set_sleeptimer
 *
 * @brief
 *
 */
void set_sleeptimer(U32 value)
{
	/* When power on, wait for a positive transition on the 32-kHz clock.*/
	while(!(SLEEPSTA & SLEEPSRA_CLK32K));
	timer_value = ST0;
	timer_value += ((unsigned long int) ST1) << 8;
	timer_value += ((unsigned long int) ST2) << 16;
	timer_value += value;
	
	/* Wait LDRDY is up, writing is allowed.*/
	while(!(STLOAD & LDRDY));
	
	/* Set sleep timer compare value.*/
	ST2 = (unsigned char) (timer_value >> 16);
	ST1 = (unsigned char) (timer_value >> 8);
	ST0 = (unsigned char) timer_value;
}

/* ------------------------------------------------------------------------------------------------------
 * @fn		read_sleeptimer
 *
 * @brief
 *
 */
U32 read_sleeptimer(void)
{
	/* When power on, wait for a positive transition on the 32-kHz clock.*/
//	while(!(SLEEPSTA & SLEEPSRA_CLK32K));
	timer_value = ST0;
	timer_value += ((unsigned long int) ST1) << 8;
	timer_value += ((unsigned long int) ST2) << 16;
	
	return timer_value;
}

