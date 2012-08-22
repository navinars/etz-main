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
	HalTimerConfig(HAL_TIMER_1,
				   HAL_TIMER_MODE_CTC,
				   HAL_TIMER_CHANNEL_0, 
				   HAL_TIMER_CH_MODE_OUTPUT_COMPARE,
				   TRUE,
				   util_Timer1CallBack);
	HalTimerStart(HAL_TIMER_1, 3906*3);		// 3s run timer1 ISR.
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
	(void)timerId;
	(void)channelMode;
	
	switch(channel)
	{
	case HAL_TIMER_CHANNEL_0:			// Every 3s HOST send beacon frame.
		mac_host_beacon();
		break;
	case HAL_TIMER_CHANNEL_1:
		break;
	case HAL_TIMER_CHANNEL_2:
		break;
	case HAL_TIMER_CHANNEL_3:
		break;
	case HAL_TIMER_CHANNEL_4:
		break;
	default:
		break;
	}
}
