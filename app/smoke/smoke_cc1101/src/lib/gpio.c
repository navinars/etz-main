#include "bsp.h"

void GPIO_init(void)
{
	P2DIR &=~BIT0;
	P2IE  |= BIT0;
	P2IES |= BIT0;													// Ñ¡ÔñÉÏÉý/ÏÂ½µÑØ
//	P2REN |= BIT0;													// push-up disable
}

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	
	if(!!(P2IFG & BIT0))											// Rx receive.
	{
		
		P2IFG &= ~BIT0;                           					// P2.2 IFG cleared
	}
		/*
		unsigned char len, tmp;
		P2IFG &= ~BIT0;
		//check CRC
//		if(CC1101_Read_Status(cc1101_LQI) & cc1101_CRC_OK)
		{
			len = CC1101_Read_Reg(cc1101_RXFIFO);
			if(len != 0x00)
			{
				TACTL = TASSEL_1 + MC_1 + ID_3 + TAIE;
				TACCR0 = 5214;					// delay 6.4s.
				P2OUT &=~BIT3;
				tmp = CC1101_Read_Reg(cc1101_RXFIFO);
				if(tmp == 0xB1)
				{
					P1OUT ^= BIT3;			// Open LED.
				}
			}
			len = CC1101_Read_Reg(cc1101_RXFIFO);
			if(len == 2)
			{
				tmp = CC1101_Read_Reg(cc1101_RXFIFO);
				if(tmp == 0xB1)
				{
					P1OUT ^= BIT3;			// Open LED.
				}
			}
			len = CC1101_Read_Reg(cc1101_RXFIFO);
			if(len == 2)
			{
				tmp = CC1101_Read_Reg(cc1101_RXFIFO);
				if(tmp == 0xB1)
				{
					P1OUT ^= BIT3;			// Open LED.
				}
			}
		}
		//wish cc1101 rx fifo and access to RX mode...
		CC1101_Entry_XMode(Rf_Rx_Flush_RxFifo);
	}
	else if(!!(P2IFG & BIT2))				// KEY is down.
	{
		P2IFG &= ~BIT2;
		
		sys_send = 1;
	}
	*/
//	_BIS_SR(LPM0_bits + GIE);                 // Enter LPM0 w/ interrupt
    //Clean interrupt flag
//    Clean_Interrupt_ISR_Flag;
    //get data packet
//    CC1101_Receive_Packet();
 }
