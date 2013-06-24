#include "bsp.h"

uint8_t send_dat[] = {0x01,0x02};

void radio_handle(void)
{
	;
}

void radio_timer_send(void)
{
	CC1101_Write_Fifo(send_dat, sizeof(send_dat));
	CC1101_Send_Packet();
}
