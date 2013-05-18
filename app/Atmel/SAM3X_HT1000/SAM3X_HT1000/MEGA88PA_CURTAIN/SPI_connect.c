
#include "MCU.h"
#include "EEPROM.h"
#include "mcu_rem.h"
#include <string.h>

#define _true           1
#define _false          0
#define ADDR            0
#define CODE            1
#define ADDR_L          3
#define ADDR_H          2
#define COMMAND_L       5
#define COMMAND_H       4
#define CRC16_L         6
#define CRC16_H         7
#define WRITE           6
#define READ            3
#define LED1		7//O常态为高

#define ADDR_PULL_START	        0x04

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
extern unsigned char f_com_open;
extern unsigned char f_com_close;
extern unsigned char f_com_stop;
extern unsigned char f_com_runtopecent;
extern unsigned char runtopecent;
extern unsigned int  ClosePosition;	// Close limit position
extern unsigned int  OpenPosition;
extern unsigned int  CurPosition;		// Current position
extern unsigned int  CurPosReal;
extern unsigned char f_DetectLimit;
extern unsigned char f_Limit;
extern unsigned char en_PullStart;
extern unsigned char set_addr_time;
extern unsigned char f_Running;
extern unsigned char PullCnt;

extern unsigned int crc16(unsigned char buff,unsigned int fcs);
extern unsigned int Crc16CheckSum(unsigned char *ptr, unsigned char length);
extern unsigned char USART_Transmit(unsigned char* im,unsigned char length);
extern void SetLed(unsigned char FlashPort, unsigned char FlashPeriod, unsigned char FlashTimes);
extern unsigned char ack_cmd(void);//应答
unsigned char SPI_process(void);
unsigned char SPI_process(void)
{
      if(SPI.SPI_recvbuff_ovf)
      {
            unsigned short check_sum;
            unsigned char crc16_l;
            unsigned char crc16_h;
            unsigned int Virtual_address;
            unsigned int Command;
            SPI.SPI_recvbuff_ovf = 0;
            check_sum = Crc16CheckSum(SPI.SPI_recv, 6);
            crc16_l = check_sum & 0x00ff;
            crc16_h = check_sum >> 8;
            if((SPI.SPI_recv[CRC16_L] != crc16_l) || (SPI.SPI_recv[CRC16_H] != crc16_h))
            {
                return _false;
            }/*
            if(SPI.SPI_recv[ADDR] != 0)
            {
                USART_Transmit(SPI.SPI_recv,8);
                return _true;
            }*/
            else
            {
                Virtual_address = (SPI.SPI_recv[ADDR_H] * 256) | SPI.SPI_recv[ADDR_L];
                Command = (SPI.SPI_recv[COMMAND_H] * 256) | SPI.SPI_recv[COMMAND_L];
                switch(SPI.SPI_recv[CODE])                           //代码功能识别 
                {
//--------------------------------------------------------------//写指令
                    case  WRITE:
                        if(Virtual_address == 0x0001)
                        {
                            if(Command == 100)
                            {
                                f_com_open = 1;
                            }
                            else if(Command == 0)
                            {
                                f_com_close = 1;
                            }
                            else if(Command == 0xFF)
                            {
                                f_com_stop = 1;
                            }
                            else if((Command>0) && (Command<100))
                            {
                                f_com_runtopecent = 1;
                                runtopecent = Command;
                            }
                            else
                            {
                                SPI.SPI_update[0] = SPI.SPI_recv[0];
                                SPI.SPI_update[1] = SPI.SPI_recv[1] + 0x80;
                                SPI.SPI_update[2] = 3;
                                check_sum = Crc16CheckSum(SPI.SPI_update, 3);
                                SPI.SPI_update[3] = check_sum & 0xff;
                                SPI.SPI_update[4] = check_sum >> 8;
                                return _false;
                            }
                      }
                      else if((Virtual_address == 0x0004)&&(Command == 0x0001))//删行程
                      {
                            CurPosition = 0x7fff;
		            cli();
		            CurPosReal = 0x7fff;
		            sei();
                            ClosePosition = 0x7fff;
                            OpenPosition = 0x7fff;
                            f_DetectLimit = 1;
		            f_Limit = 0;
		            EE_WriteBYTE(ADDR_LIM_FLAG, f_Limit);
		            EE_CheckReady();
                      }
                      else if((Virtual_address == 0x0005)&&(Command == 0x0001))//换向
                      {
                            if (!f_Reverse)
		            {
			        f_Reverse = 1;
		            }
		            else
		            {
			        f_Reverse = 0;
		            }
		            EE_WriteBYTE(ADDR_REVERSE_FLAG, f_Reverse);
		            EE_CheckReady();
                            CurPosition = 0x7fff;
		            cli();
		            CurPosReal = 0x7fff;
		           sei();
                            ClosePosition = 0x7fff;
                            OpenPosition = 0x7fff;
                            f_DetectLimit = 1;
		            f_Limit = 0;
		            EE_WriteBYTE(ADDR_LIM_FLAG, f_Limit);
		            EE_CheckReady();
		            SetLed(LED1, 3, 5);
                      }
                      else if((Virtual_address == 0x0007)&&(Command < 0x0002))//手拉启动设置
                      {
                            if(Command == 0)
                            {
                                en_PullStart = 0;
                            }
                            else if(Command == 1)
                            {
                                PullCnt = 0;
                                en_PullStart = 1;
                            }
                            EE_WriteBYTE(ADDR_PULL_START, en_PullStart);
                            EE_CheckReady();
                      }
                      else if((Virtual_address > 0x0007)||(Command >= 0x0002))
                      {
                            if(Virtual_address > 0x0016)
                            {
                                  SPI.SPI_update[2] = 2;
                            }
                            else if(Virtual_address > 0x000B)
                            {
                                  SPI.SPI_update[2] = 4;
                            }
                            if(Command >= 0x0002)
                            {
                                  SPI.SPI_update[2] = 3;
                            }
                            SPI.SPI_update[0] = SPI.SPI_recv[0];
                            SPI.SPI_update[1] = SPI.SPI_recv[1] + 0x80;
                            check_sum = Crc16CheckSum(SPI.SPI_update, 3);
                            SPI.SPI_update[3] = check_sum & 0xff;
                            SPI.SPI_update[4] = check_sum >> 8;
                            return _false;
                      }
                      memcpy(SPI.SPI_update, SPI.SPI_recv, 8);
                      break;         
  
//--------------------------------------------------------------//读数据
                  case  READ: 
                      if(Virtual_address == 0x0007)
                      {
                            SPI.SPI_update[3] = en_PullStart;
                      }
                      else if(Virtual_address == 0x000C)
                      {
                            SPI.SPI_update[3] = f_Limit;
                      }
                      else if(Virtual_address == 0x000D)
                      {
                            if(!f_Running)
                            {
                                SPI.SPI_update[3] = ack_cmd();
                            }
                            else
                            {
                                SPI.SPI_update[3] = 0xAA;  //返回正在运行标志
                            }
                      }
                      else if(Virtual_address == 0x0016)
                      {
                            SPI.SPI_update[3] = 1;
                      }
                      else if(Virtual_address > 0x0016)
                      {
                            SPI.SPI_update[0] = SPI.SPI_recv[0];
                            SPI.SPI_update[1] = SPI.SPI_recv[1] + 0x80;
                            check_sum = Crc16CheckSum(SPI.SPI_update, 3);
                            SPI.SPI_update[3] = check_sum & 0xff;
                            SPI.SPI_update[4] = check_sum >> 8;
                            return _false;
                      }
                      SPI.SPI_update[0] = SPI.SPI_recv[0];
                      SPI.SPI_update[1] = SPI.SPI_recv[1];
                      SPI.SPI_update[2] = 2;
                      SPI.SPI_update[4] = 0;
                      check_sum = Crc16CheckSum(SPI.SPI_update, 5);
                      SPI.SPI_update[5] = check_sum & 0xff;
                      SPI.SPI_update[6] = check_sum >> 8;
	              break;
                default:                               //功能代码错误，不动作。 
                      return _false;
              }
              return _true;
        }
    }
    return _true;
}

