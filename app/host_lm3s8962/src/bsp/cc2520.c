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
	unsigned long a;
	
	cc2520_arch_init();
	
	SET_VREG_INACTIVE();
	OSTimeDly(250);
	/* Turn on voltage regulator and reset. */
	SET_VREG_ACTIVE();
	OSTimeDly(250);
	SET_RESET_ACTIVE();
	OSTimeDly(127);
	SET_RESET_INACTIVE();
	OSTimeDly(125);
	
	/* Turn on the crystal oscillator. */
	cc2520_strobe(CC2520_INS_SXOSCON);
	OSTimeDly(500);
	a = cc2520_getreg(CC2520_TXCTRL);
	a = cc2520_status();
	a = cc2520_status();
	a = cc2520_status();
	UARTprintf("\n%4x", a);
	cc2520_setreg(CC2520_TXCTRL,      0x94);
	cc2520_setreg(CC2520_TXPOWER,     0x13);    // Output power 1 dBm
	
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
