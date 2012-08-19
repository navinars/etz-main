/* ------------------------------------------------------------------------------------------------------
* File: util_timer.c
*
* -------------------------------------------------------------------------------------------------------
*/
#include "includes.h"

/* ------------------------------------------------------------------------------------------------------
 *											Local Functions
 * ------------------------------------------------------------------------------------------------------
 */
static void util_Timer1CallBack ( uint8 timerId, uint8 channel, uint8 channelMode );


/* ------------------------------------------------------------------------------------------------------
 *									timer1_init()
 *
 * Description : timer1 initlisation.
 *
 * Argument(s) : none.
 *
 */
void timer1_init(void)
{
	/* Initalise Timer1(16bit).*/
	HalTimerInit();
	HalTimerConfig(HAL_TIMER_3,
				   HAL_TIMER_MODE_NORMAL,
				   HAL_TIMER_CHANNEL_SINGLE, 
				   HAL_TIMER_CH_MODE_OVERFLOW,
				   TRUE,
				   util_Timer1CallBack);
	HalTimerStart(HAL_TIMER_3, 50000);
}

/* ------------------------------------------------------------------------------------------------------
 *									util_Timer1CallBack()
 *
 * Description : timer1 initlisation.
 *
 * Argument(s) : none.
 *
 */
static void util_Timer1CallBack ( uint8 timerId, uint8 channel, uint8 channelMode )
{
	(void) timerId;
	data_updata();
}
