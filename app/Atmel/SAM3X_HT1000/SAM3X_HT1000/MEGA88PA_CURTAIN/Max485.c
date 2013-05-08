#include "MCU.h"
#include "EEPROM.h"
#include "mcu_rem.h"
#include <string.h>
#define delay1us(x)     _delay_loop_2(8*x)
#define _true           1
#define _false          0
#define BIT(x)	        (1 << (x))
#define EN	        2//O
#define WRITE_485	(PORTD |= BIT(EN))	        //--PORTD
#define READ_485	(PORTD &= ~BIT(EN))

extern struct{
  unsigned char f_spi_recv;
  unsigned char f_spi_update;
  unsigned char SPI_en;
  unsigned char SPI_recv_len;
  unsigned char recv_cnt;
  unsigned char SPI_update_len;
  unsigned char recv_timeout;
  unsigned char SPI_recvbuff_ovf;
  unsigned char SPI_recv[10];
  unsigned char SPI_update[8];
}SPI;
extern struct{
  unsigned char recv_cnt;
  unsigned char recv_timeout;
  unsigned char recvbuff_ovf;
  unsigned char uart_recv[10];
}UART;


unsigned int crc16(unsigned char buff,unsigned int fcs);
unsigned int Crc16CheckSum(unsigned char *ptr, unsigned char length);
//--------------------------------------------------- 
void USART_Init(void)
{
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);  /* 接收器与发送器使能,接受中断允许*/
    UCSR0C = (0<<USBS0)|(3<<UCSZ00);      /* 设置帧格式: 8 个数据位, 1 个停止位 */
    UBRR0  = 51;
    READ_485;       //485接受允许
}

//----------------------------------------发送函数
unsigned char USART_Transmit(unsigned char* im,unsigned char length)
{
    unsigned int i=0;
    unsigned char n;
    WRITE_485;       //485发送允许
    delay1us(500);
    for(n=0; n<length; n++)
    {
          while((UCSR0A&(1<<UDRE0))==0)	
          {
              wdt_reset();
              if(++i>5000)  
              {
	          READ_485;    
	          return _false;
	      }	
          }
          UDR0 = *im++; 
          while (!(UCSR0A & (1<<TXC0)))	//等待发送完成
          {
              wdt_reset();
              if(++i>5000)  
              {
	          READ_485;     
	          return _false;
              }	  
          } 
    }
    UCSR0A|=(1<<TXC0);	//清除发送标志   
    delay1us(500);
    READ_485;   
    return _true;
}
//----------------------------------------接收函数
unsigned char USART_Receive(void)
{
    unsigned int i=0;
    while((UCSR0A&(1<<RXC0))==0)	
    {
        wdt_reset();
        if(++i>3000)
          return _false;	
    }
    return _true;
}

//-------------------------------------------/*刷新接收缓冲器*/
/*unsigned char USART_Flush(void)
{
    unsigned char dummy;
    if (UCSR0A & (1<<RXC0))
    {
      dummy = UDR0;
    }
    return dummy;
}*/

//---------------------------------------------------------------------------
//Crc8 check sum function 
/*unsigned char Crc8CheckSum(unsigned char *ptr, unsigned char length) 
{
    unsigned char i;      
    unsigned char Crc8=0;
    while(length--)
    {
	  for(i=0x80; i; i>>=1)
	  {
		if((Crc8&0x80)!=0)
		{
			Crc8<<=1;
			Crc8^=0x31;
		}
		else
		{
			Crc8<<=1;
		}
		if(*ptr&i)
		{
			Crc8^=0x31;
		} 
	    }
	    ptr++; 
    }
    return Crc8;
}*/

unsigned int crc16(unsigned char buff,unsigned int fcs)
{
	unsigned char  i,temp;   //a001		 	  
	fcs=buff^fcs;
	for(i=0;i<8;i++)
	{
	    temp=fcs&0x01;
	    if(temp==0)
	        fcs=fcs>>1;
	    else
	    {
	        fcs=fcs>>1;
	        fcs = fcs^0xa001;
	    }
	} 
	return fcs;
}

unsigned int Crc16CheckSum(unsigned char *ptr, unsigned char length)
{
        unsigned int   xym;
        xym=0xffff;
        while(length--)
        {
	   xym = crc16(*ptr,xym);
           ptr++;
        }
	return xym;
}


void max485_tarns(void)                            
{
    unsigned  char   crc16_l,crc16_h;
    unsigned  int    check_sum;

    if(UART.recvbuff_ovf)
    {
        check_sum = Crc16CheckSum(UART.uart_recv, UART.recv_cnt-2);
        crc16_l = check_sum & 0x00ff;
        crc16_h = check_sum >> 8;
        if((UART.uart_recv[UART.recv_cnt-2] != crc16_l) || (UART.uart_recv[UART.recv_cnt-1] != crc16_h))
        {
          READ_485;
        }
        memcpy(SPI.SPI_update, UART.uart_recv, UART.recv_cnt);
        READ_485;
    }
}
