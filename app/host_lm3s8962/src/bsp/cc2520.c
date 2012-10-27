/*
 * This code is almost device independent and should be easy to port.
 */
/* ------------------------------------------------------------------------------------------------------
 *											Local Includes
 * ------------------------------------------------------------------------------------------------------
 */
#include <string.h>

#include "cc2520.h"

#include "bsp.h"
#include "utils/uartstdio.h"

#include "ucos_ii.h"


/* ------------------------------------------------------------------------------------------------------
 *											Local Defines
 * ------------------------------------------------------------------------------------------------------
 */
#ifndef CC2520_CONF_AUTOACK
#define CC2520_CONF_AUTOACK 0
#endif /* CC2520_CONF_AUTOACK */

#define WITH_SEND_CCA 1

#define FOOTER_LEN 2

#define FOOTER1_CRC_OK      0x80
#define FOOTER1_CORRELATION 0x7f


/* ------------------------------------------------------------------------------------------------------
 *											Local Variable
 * ------------------------------------------------------------------------------------------------------
 */
static unsigned char receive_on;

static int channel;


/* ------------------------------------------------------------------------------------------------------
 *									cc2520_init()
 *
 * Description : cc2520 init function.
 *
 * Argument(s) : none.
 *
 */
void cc2520_init(void)
{
	unsigned long a = 0xFF;
	
	SET_VREG_INACTIVE();											/* Turn on voltage regulator and reset. */
	OSTimeDly(200);
	SET_VREG_ACTIVE();
	OSTimeDly(200);
	SET_RESET_ACTIVE();
	OSTimeDly(200);
	SET_RESET_INACTIVE();
	OSTimeDly(200);
	
	/* Turn on the crystal oscillator. */
	cc2520_strobe(CC2520_INS_SXOSCON);
	OSTimeDly(500);
	
	a = cc2520_status();
	UARTprintf("\n%4x", a);
	
	a = 0xff;
	cc2520_setReg(CC2520_TXCTRL,      0x94);
	a = cc2520_getReg(CC2520_TXCTRL);
	
	a = 0xff;
	cc2520_setReg(CC2520_TXPOWER,     0x93);    // Output power 1 dBm
	a = cc2520_getReg(CC2520_TXPOWER);
	UARTprintf("\n%4x", a);
}

/* ------------------------------------------------------------------------------------------------------
 *									on()
 *
 * Description : cc2520 chip power on.
 *
 * Argument(s) : none.
 *
 */
void on(void)
{
	cc2520_strobe(CC2520_INS_SRXON);
	
	//timer rx
	receive_on = 1;
}

/* ------------------------------------------------------------------------------------------------------
 *									off()
 *
 * Description : cc2520 chip power on.
 *
 * Argument(s) : none.
 *
 */
void off(void)
{
	receive_on = 0;
	
	cc2520_strobe(CC2520_INS_SRFOFF);
}
