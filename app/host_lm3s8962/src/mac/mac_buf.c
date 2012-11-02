/* ------------------------------------------------------------------------------------------------------
* File: mac_buf.c
*
* -------------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <string.h>

#include "hal_rf.h"

#include "mac.h"
#include "mac_hw.h"


mac_buf_t rxbuf;
mac_buf_t txbuf;


/* ------------------------------------------------------------------------------------------------------
 *												mac_buf_init()
 *
 * Description : Initialise buffer.
 *
 */
void mac_buf_init(void)
{
	memset(&rxbuf, 0, sizeof(mac_buf_t));
	memset(&txbuf, 0, sizeof(mac_buf_t));
	
	rxbuf.dptr = &rxbuf.buf[0];
	txbuf.dptr = &txbuf.buf[128];
}

/* ------------------------------------------------------------------------------------------------------
 *												reset_rx_buf()
 *
 * Description : Initialise buffer.
 *
 */
void reset_rx_buf(void)
{
	memset(&rxbuf, 0, sizeof(mac_buf_t));
	rxbuf.dptr = &rxbuf.buf[0];
}

/* ------------------------------------------------------------------------------------------------------
 *												reset_tx_buf()
 *
 * Description : Initialise buffer.
 *
 */
void reset_tx_buf(void)
{
	memset(&txbuf, 0, sizeof(mac_buf_t));
	txbuf.dptr = &txbuf.buf[128];
}

/* ------------------------------------------------------------------------------------------------------
 *												read_rx_buf()
 *
 * Description : none.
 *
 */
mac_buf_t *read_rx_buf(void)
{
	return &rxbuf;
}

/* ------------------------------------------------------------------------------------------------------
 *												mac_buf_init()
 *
 * Description : none.
 *
 */
mac_buf_t *read_tx_buf(void)
{
	return &txbuf;
}
