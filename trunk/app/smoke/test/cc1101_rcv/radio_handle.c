#include <msp430.h>
#include <stdint.h>
#include <string.h>
#include "cc1101.h"
#include "cc1101_defs.h"
#include "radio_handle.h"

uint8_t flag_send = 0;
uint8_t flag_rcv = 0;

uint8_t frm[10] = {0};
uint8_t frm_rcv[10] = {0};

void radio_handle(void)
{
	if(flag_send == 1)
	{
		flag_send = 0;
		
		memcpy(frm, "dooya", 5);
		Radio_Transmit(frm, 5);
	}
	
	if(flag_rcv == 1)
	{
		flag_rcv = 0;
		
		if ((frm_rcv[0] == 'd') && (frm_rcv[1] == 'o'))
		{
			memcpy(frm, "dooya", 5);
			Radio_Transmit(frm, 5);
			P1OUT ^= BIT0;											// Turn LED0..
		}
	}
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	uint8_t d1, len;
	if(!!(P2IFG & BIT0))											// Rx receive.
	{
		d1 = Mrfi_SpiReadReg(RXBYTES);								// Read RxBytes register.
		if (d1 != 0)
		{
			len = Mrfi_SpiReadReg(RXFIFO);
			if ((len > 0) && (len < 10))
			{
				Mrfi_SpiReadRxFifo(frm_rcv, len+2);					// Receive data to buffer.
				flag_rcv = 1;										
//				P1OUT ^= BIT0;										// Turn LED0..
			}
		}
		
		Mrfi_SpiCmdStrobe(SFRX);
		Mrfi_SpiCmdStrobe(SIDLE);
		Mrfi_SpiCmdStrobe(SRX);

		P2IFG &= ~BIT0;                           					// P2.2 IFG cleared
	}
}

