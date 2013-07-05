#include "bsp.h"

uint8_t d1,len,d[20];
	
void GPIO_init(void)
{
	// Config LED pin.
	P1DIR |= BIT0;
	P1OUT |= BIT0;

	// Config GPIO0 pin.
	P2DIR &=~BIT0;
	P2REN |= BIT0;													// push-up enable
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	if(!!(P2IFG & BIT0))											// Rx receive.
	{
		d1 = Mrfi_SpiReadReg(RXBYTES);								// Read RxBytes register.
		if (d1 != 0)
		{
			len = Mrfi_SpiReadReg(RXFIFO);
			if(len != 10)
			{
				memset(d,0xFF,10);
				Mrfi_SpiReadRxFifo(d,20);
				memset(d,0,10);
				P1OUT ^= BIT0;										// Turn LED0..
			}
		}
		
		Mrfi_SpiCmdStrobe(SFRX);

		P2IFG &= ~BIT0;                           					// P2.2 IFG cleared
	}
}
