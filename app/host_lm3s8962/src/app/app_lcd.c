/* ------------------------------------------------------------------------------------------------------
 * File: app_lcd.c
 * Data: 2012/10/20
 * Author: MC
 * Ver: V0.1.1b
 * -------------------------------------------------------------------------------------------------------
 */
#include "includes.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Defines
 * ------------------------------------------------------------------------------------------------------
 */


/* ------------------------------------------------------------------------------------------------------
 *											Local Variables
 * ------------------------------------------------------------------------------------------------------
 */
static OS_STK  	Task_LCDStk[TASK_LCD_STK_SIZE];


/* ------------------------------------------------------------------------------------------------------
 *											Local Functions
 * ------------------------------------------------------------------------------------------------------
 */
static void App_TaskLCD(void *parg);


/* ------------------------------------------------------------------------------------------------------
 *									   		App_TaskLCD()
 *
 * Description : App LCD task function.
 *
 * Argument(s) : none.
 *
 */
void TaskLCD_Create(void)
{
	
	// TODO: lcd drive code should be in bsp.c
	RIT128x96x4Init(1000000);
	
	OSTaskCreate (App_TaskLCD, (void *)0,   							/* Create LCD task.*/
				  &Task_LCDStk[TASK_LCD_STK_SIZE-1], 
				  APP_CFG_TASK_LCD_PRIO);
}


/* ------------------------------------------------------------------------------------------------------
 *									   		App_TaskLCD()
 *
 * Description : LCD txt dispaly function.
 *
 * Argument(s) : none.
 *
 */
static void lcdtxt_init(void)
{
	RIT128x96x4Enable(1000000);											/* Enable LCD */
	RIT128x96x4StringDraw("lwIP1.4 uC/OS-2.89", 15, 0, 15);
	RIT128x96x4StringDraw("----------------", 15, 8, 15);
	RIT128x96x4StringDraw("IPv4 :", 0, 16, 8);
	RIT128x96x4StringDraw("Mask :", 0, 24, 8);
	RIT128x96x4StringDraw("Gate :", 0, 32, 8);
	RIT128x96x4StringDraw("DNS  :", 0, 40, 8);
	RIT128x96x4StringDraw("MAC  :", 0, 48, 8);
	RIT128x96x4StringDraw("Sver :", 0, 56, 8);
//	RIT128x96x4StringDraw("UID  :", 0, 64, 8);
	RIT128x96x4Disable();												/* Disable LCD */
}

//*****************************************************************************
//
// Display an lwIP type IP Address.
//
//*****************************************************************************
void DisplayIPAddress(unsigned long ipaddr, unsigned long ulCol,
                 unsigned long ulRow)
{
    char pucBuf[16];
    unsigned char *pucTemp = (unsigned char *)&ipaddr;

    //
    // Convert the IP Address into a string.
    //
    usprintf(pucBuf, "%d.%d.%d.%d", pucTemp[0], pucTemp[1], pucTemp[2],
             pucTemp[3]);

    //
    // Display the string.
    //
    RIT128x96x4StringDraw(pucBuf, ulCol, ulRow, 15);
}

/* ------------------------------------------------------------------------------------------------------
 *									   		App_TaskLCD()
 *
 * Description : App LCD task function.
 *
 * Argument(s) : none.
 *
 */
static void App_TaskLCD(void *parg)
{
	INT32U *msg;
	INT8U err;
	INT32U data;
	
	lcdtxt_init();														/* LCD txt dispaly */
	
	for(;;)
	{
		msg = (INT32U *)OSMboxPend(App_LcdMbox, OS_TICKS_PER_SEC / 10, &err);
		if (err == OS_ERR_NONE) {
			
			data = *msg;
			
			RIT128x96x4Enable(1000000);									/* Enable LCD */
			DisplayIPAddress(data, 36, 16);
			data = lwIPLocalNetMaskGet();
			DisplayIPAddress(data, 36, 24);
			data = lwIPLocalGWAddrGet();
			DisplayIPAddress(data, 36, 32);
			RIT128x96x4Disable();										/* Disable LCD */
		}
	}
}


