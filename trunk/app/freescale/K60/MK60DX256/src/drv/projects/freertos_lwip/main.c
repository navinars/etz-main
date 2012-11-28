/*
    FreeRTOS V6.0.4 - Copyright (C) 2010 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS eBook                                  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/*
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/

/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 *
 * A few tasks are created that are not part of the standard demo.  These are
 * the 'LCD' task, the 'LCD Message' task, a WEB server task and the 'Check'
 * task.
 *
 * The LCD task is the only task that accesses the LCD directly, so mutual
 * exclusion is ensured.  Any task wishing to display text sends the LCD task
 * a message containing a pointer to the string that should be displayed.
 * The LCD task itself just blocks on a queue waiting for such a message to
 * arrive - processing each in turn.
 *
 * The LCD Message task does nothing other than periodically send messages to
 * the LCD task.  The messages originating from the LCD Message task are
 * displayed on the top row of the LCD.
 *
 * The Check task only executes every three seconds but has the highest
 * priority so is guaranteed to get processor time.  Its main function is to
 * check that all the other tasks are still operational. Most tasks maintain
 * a unique count that is incremented each time the task successfully completes
 * a cycle of its function.  Should any error occur within such a task the
 * count is permanently halted.  The check task sets a bit in an error status
 * flag should it find any counter variable at a value that indicates an
 * error has occurred.  The error flag value is converted to a string and sent
 * to the LCD task for display on the bottom row on the LCD.
 */

/* Library includes. */
#include "common.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* lwIP includes. */
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"

/* Apps includes */
#include "HTTPDemo.h"
#include "partest.h"

/*
 * Configure the processor clock and ports.
 */
static void prvSetupHardware( void );

/*-----------------------------------------------------------*/

/*
 * Starts all the other tasks, then starts the scheduler.
 */
void main( void )
{
#if 0
        #define DUMMY_ADD                     (*(volatile uint8_t*)(0x12345678))
        DUMMY_ADD = 1;
        printf("Hello World\n");
#endif
        
	/* Setup any hardware that has not already been configured by the low
	level init routines. */
	prvSetupHardware();

	sys_thread_new( ( char * ) "httpd", vBasicWEBServer, ( void * ) NULL, lwipBASIC_SERVER_STACK_SIZE, basicwebWEBSERVER_PRIORITY );	

	/* Start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */

	vTaskStartScheduler();

	/* We should never get here as control is now taken by the scheduler. */
	for( ;; )
        ;
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Peripheral initialisation. */
	vParTestInitialise();
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will get called if a task overflows its stack. */

	( void ) pxTask;
	( void ) pcTaskName;

	for( ;; );
}
