/////////////////////////////////////////////
//修改记录：
//1.增大了堵转检测的力量
//2.修改了手拉启动每2秒钟更新一次位置数据
//3.行程不保存，无论上电复位或狗复位均重新检测行程
//4.修改了群控只能上下停控制，不能设置的问题。2011/11/25 8:47
//5.修改挂50KG时遇阻太轻(5倍)，打开(5cm)与关闭(2cm)时的间距。2011/12/14 8:36
/////////////////////////////////////////////
#include "DC475.h"
#include "EEPROM.h"
#include "SPI_connect.h"
#include "Max485.h"
#include <string.h>
#include "optimize.h"
#include <util/delay.h>

#define OPEN	1
#define CLOSE	2
#define STOP    3

#define MENU_REMOTE 	        10
#define MENU_SET		20
#define MENU_ADD_RF		30
#define MENU_CLR_RF		40
#define MENU_SET_LIMIT	        50
#define MENU_CLR_LIMIT	        60
#define MENU_PULLSTART          70
#define MENU_THIRDPOS           80
#define MENU_EXIT 		100

//电机转速定义
#define NEW                     1
// 时间常量定义
#define T_TMR0			0x9C	// TMR0 定时器初值 @8MHz 100us
#define T_TMR1                  0xFCE8  // TMR1 定时器初值 @8MHz 1ms
// unit:0.5ms

// unit:10ms
#define T_REVERSE		70		// 反转时间：700ms
#define T_KEYDELAY		50		// 按键检测延时：50ms
#define T_BREAK_START	        200		// 启动时堵转检测时间：500ms
#define T_BREAK_RUN		50		// 运行时堵转检测时间：200ms
#define T_EXIT			500		// 5S
#define T_REMOTE                10              //上电10S内对码
#define START_TIME              100               //上电全速启动50ms
// unit:100ms
#define T_COUNTDELAY	        5		// 停止后的脉冲计数延时：12*100ms = 1.2s
//#define T_COUNTDELAY1	        8		// 停止后的脉冲计数延时：12*100ms = 1.2s
#define T_CLEARDELAY	        10
#define T_CLEARDELAY1	        10
#define STARTUP_DIST	        10		// 启动距离：
// unit:1s
#define T_TOTALRUN		255		// 总运行时间：255s
#define T_SET_ADDR              10              //接收485信号超时设置
#define T_PULLSTARTRELAY        200             //遇阻2S内无手拉

// EEPROM地址定义
#define ADDR_REVERSE_FLAG       0x02
#define ADDR_PULL_START	        0x04
#define ADDR_LIM_FLAG	        0x06
#define ADDR_POS_CL		0x08
#define ADDR_POS_OP		0x0a	        // address of close limit position
#define ADDR_POS_CUR	        0x0c	        // current position address
#define ADDR_POS_SPEEDDOWN	0x0e            //减速位置
#define ADDR_THIRD_POS_FLAG     0x10
#define ADDR_POS_MID1           0x12
#define ADDR_POS_DISTANSE       0x14
#define ADDR_MID_PERCENT        0x16
// 力量检测设置
#define PULSE_COUNTER           4
#define MAX_FORCE T_BREAK_RUN * 100	        // 30*100*0.1mS = 100ms
#define FOREC_RANGE	        3*10		// 3*10*0.1ms = 3ms
#define FORCEOVER               100             //电流过载值
#define ELASTIC_DISTANSE        1               //设置行程反转距离
//慢启慢停
//#define START_SPEEDUP         20
#define START_SPEEDUP           100             //调试
#define POS_SPEEDDOWN           35              //调试
//#define POS_SPEEDDOWN         172
#define END_SPEEDDOWN1          90             //调试
#define END_SPEEDDOWN2          120             //调试
#define END_SPEEDDOWN3          150             //调试
//#define END_SPEEDDOWN1        50
#define PULL_CNT                7
// 变量定义

//unsigned char POS_SPEEDDOWN;
unsigned char POS_SPEEDDOWN_OPEN;
unsigned char Time100us;
unsigned char Time05ms;			// 0.5ms counter
unsigned char Time10ms;			// 10ms counter
unsigned char Time100ms;		// 100ms counter
unsigned char Time1s;

unsigned char PauseTime;		// Stop pause time
unsigned char ClearDoor_sec;

unsigned char f_RemStopPush;
unsigned char f_RemStopHold;
unsigned char f_RemOpenPush;
unsigned char f_RemOpenHold;
unsigned char f_RemClosePush;
unsigned char f_RemCloseHold;
unsigned char f_RemSetPush;
unsigned char f_RemSetHold;
unsigned char f_Key1Push;
unsigned char f_Key1Pop;
unsigned char f_Key1Hold;
unsigned int  KeyHoldTime;
unsigned char ChangeHoldtime;
unsigned char f_Key2Push;
unsigned char f_Key2Pop;
unsigned char f_Key2Hold;
unsigned char f_OpenPush;
unsigned char f_OpenPop;
unsigned char f_OpenHold;
unsigned char f_ClosePush;
unsigned char f_ClosePop;
unsigned char f_CloseHold;
unsigned char f_StopPush;
unsigned char f_StopPop;
unsigned char f_StopHold;
unsigned char f_DetectSpeeddown;
unsigned char f_KeyswChange;
unsigned char inputbuf;


unsigned char DoorStatus;	// Door Open/Close flag
unsigned char f_Running;		// Door is running flag
unsigned char f_Start;
unsigned char StartCounter;
unsigned char f_stop;

unsigned char f_Setting;
unsigned char Task_Menu;

unsigned char f_RunTimeOver;	// 运行时间溢出标志
unsigned char TotalRunTime;		// Total run time

unsigned char f_LastPulse1;		// Last pulse status
unsigned char f_LastPulse2;		// Last pulse status
unsigned char SamplingCount1;	// 脉冲连续采样次数计数器
unsigned char SamplingCount2;	// 脉冲连续采样次数计数器
unsigned char f_DetectLimit;
unsigned char f_Limit;
unsigned char CountDelay;
unsigned char CountDelay_sec;
unsigned char Clearclucth;
unsigned int  Cleardoor;
unsigned char f_OpenLimit;		// Open limit switch active
unsigned char f_CloseLimit;		// Close limit switch active
unsigned int  ClosePosition;	// Close limit position
unsigned int  OpenPosition;
unsigned int  CurPosition;		// Current position
unsigned int  CurPosReal;
unsigned char SetLimit_count;

unsigned int  PulseWidth;		// 脉宽检测值
unsigned int  CurPulseWidth;
unsigned int  Pulse[PULSE_COUNTER];
unsigned int  LowspeedPulse;

unsigned char en_CheckForce;
unsigned int  LastForce;
unsigned char f_ForceOver;		// Force overload flag
unsigned char BreakTime;		// 电机堵转时间
unsigned char ReverseTime;		// Reverse pause time
unsigned char I_detectime0;
unsigned int I_detectime1;
//unsigned char en_Learn;
unsigned char DetectTime;
unsigned int  ExitTime;
unsigned char RemoteTime;
unsigned char Startup_Time;

unsigned char FlashPeriod_Led;
unsigned char FlashTime_Led;
unsigned char f_FlashLed;
unsigned char LedStatus;

unsigned char f_ReallyStop;
unsigned char en_PullStart;
unsigned char dis_PullStart;
unsigned char dis_PullStartTime;
unsigned char pullstartflag;
unsigned char pullflag1;
//unsigned char pullflag2;
unsigned int  CurPositionBack;		// Current position
unsigned char f_Way;
unsigned char f_Reverse;

unsigned char RelayDelay;

unsigned char f_SpeedDown;
unsigned char f_SpeedLow;
unsigned char f_SpeedUp;
unsigned char EndSpeedDown;
unsigned char Flash_Port;
unsigned char f_LimitRerse;
unsigned char f_Remotedelay;
unsigned char PullCnt;
unsigned char LastDir;
unsigned char PullDir;
unsigned char f_clearclucth;
unsigned char f_cleardoor;
unsigned char cleardoor_delay;
unsigned char clearclucth_relay;
/*unsigned char RunMode;
unsigned char Hour;
unsigned char Minute;
unsigned char Seconds;
unsigned char SecPass;
unsigned char HourOp;
unsigned char MinuOp;
unsigned char HourCl;
unsigned char MinuCl;*/

unsigned char setthirdpos_count;
unsigned char f_ThirdPos;
unsigned int MidPosition1;
unsigned int MidPosition2;
unsigned int MidPosition;
unsigned char DelThirdTime;
unsigned char f_MidLimit;
extern unsigned char f_Interference;
unsigned char RemKeyHoldTime;
unsigned char f_RunToMid;
unsigned char f_ThirdPos_set;

unsigned char f_setCloseLimit;
unsigned char f_setOpenLimit;
//unsigned char f_Openback;
//unsigned char f_Closeback;
unsigned char f_Limitback;
unsigned char f_Limitback_1;
unsigned char BackPosition;

unsigned char DelLimtTime;
unsigned char StopCnt;

unsigned char f_Sleep;
unsigned char f_Pcint0wake;
unsigned char f_Pcint1wake;
unsigned char f_Pcint2wake;
unsigned char f_wakeup;
unsigned char f_Timerwake;
unsigned char f_WakeTimerout;
unsigned char Recv_Type;
unsigned char f_RFlast;
unsigned char f_Hall1;
unsigned char Hi_count;
unsigned char Lo_count;
unsigned char Half_H;
unsigned char f_Powerdown;
unsigned char Powerdown_count;

unsigned char AC_L1_count;
unsigned char AC_L2_count;
unsigned char f_AC_Open;
unsigned char f_AC_Close;
unsigned char f_AC_Stop;
unsigned char f_LastL1;
unsigned char f_LastL2;

unsigned char f_set_addr;
unsigned char set_addr_time;
unsigned char f_max485_trans;
unsigned char ID;
unsigned char f_com_open;
unsigned char f_com_close;
unsigned char f_com_stop;
unsigned char f_com_runtopecent;
unsigned char runtopecent;
unsigned char f_runtopercent;
unsigned char Percent_mid;
unsigned char Percent_mid1;
unsigned char MidPosition_percent;
unsigned char Percent;
unsigned int  distance;

unsigned char ad_in;      //测试用
unsigned int sum_ad_in;
unsigned int addr;
unsigned char table[8];
unsigned  char  com[11];

struct{
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

struct{
  unsigned char recv_cnt;
  unsigned char recv_timeout;
  unsigned char recvbuff_ovf;
  unsigned char uart_recv[10];
}UART;


// 函数声明
void Init(void);				// initialize
void GetPowerDown(void);
void GetLimit(void);			// get end of travel
void GetForce(void);
void Open(void);				// Open door
void Close(void);				// Close door
void Stop(void);				// Stop door running
void SetLed(unsigned char FlashPort, unsigned char FlashPeriod, unsigned char FlashTimes);
void FlashLed(void);
unsigned char ReadKey(void);
void GetKey(void);
void PullStart(void);
void Reverse(void);
void DetectSpeeddownPos(void);
unsigned char GetADInput(unsigned char Chanel);
unsigned char ADInputFilter(unsigned char Chanel);
void InitTimer2(void);
void RunToMid(unsigned int Mid_Position);
void GoToSleep(void);
void InitTimer0(void);
void InitTimer1(void);
void  SetLimit(void);
void clearclucth_set(unsigned char sec,unsigned char delay,unsigned char relay);
extern unsigned char SPI_process(void);
unsigned char ack_cmd(void);//应答

//#pragma vector = USART_RX_vect
//__interrupt void USART_RX_ISR(void)
ISR( USART_RX_vect )
{
	UART.recv_timeout = 30;
	UART.uart_recv[UART.recv_cnt] = UDR0;
	UART.recv_cnt++;
}

//#pragma vector = PCINT0_vect
//__interrupt void PCINT0_ISR(void)
ISR( INT0_vect )
{
	//static unsigned char i = 0;
	static unsigned char n = 0;
	static unsigned char tdata;
	if(!PIN_SPI_CLK)
	{
//		SPI.recv_cnt++;
		if(SPI.f_spi_recv)
		{
			n = 0;
			SPI.recv_timeout = 30;         //3ms接收超时，表示接收完成
			
			if(PIN_SPI_MOSI)
				tdata = tdata|0x01;    // 若接收到的位为1，则数据的最后一位置1
			else 
				tdata = tdata&0xfe;    // 否则数据的最后一位置0
			
			SPI.SPI_recv_len++;
			
			if(SPI.SPI_recv_len>7)
			{
				SPI.SPI_recv[SPI.recv_cnt]=tdata;
				SPI.recv_cnt++;
				//if(i>9)i=0;//调试
				SPI.SPI_recv_len=0;
			}
			else
				tdata = tdata<<1;
		}
		if(SPI.f_spi_update)
		{
			SPI.recv_cnt = 0;
			
			if((SPI.SPI_update[n]&0x80) == 0x80)
				SET_SPI_MISO;
			else
				CLR_SPI_MISO;
			
			SPI.SPI_update[n] = SPI.SPI_update[n]<<1;
			SPI.SPI_update_len++;
			
			if(SPI.SPI_update_len>7)
			{
				n++;
				SPI.SPI_update_len=0;
				
				if(n>7)
				{
					for(unsigned char j=0;j<8;j++)
						SPI.SPI_update[j] = 0;
				}
			}
		}
	}
}


//#pragma vector = PCINT1_vect
//__interrupt void PCINT1_ISR(void)
ISR( INT1_vect )
{
	unsigned char temp,temp1,temp2;
	f_KeyswChange = 1;
	ChangeHoldtime = 0;
	temp = PIN_SW_KEY2;
	temp1 = PIN_SW_KEY1;
	temp2 = PIN_KEY1;
	temp = temp + temp1 + temp2;
	inputbuf = temp;
}

//===========================================================
//Function:	TMR0 interrupt service process.
//			100us timer.
//-----------------------------------------------------------
//#pragma vector = TIMER0_OVF_vect
//__interrupt void TMR0_ISR(void)
ISR( TIMER0_OVF_vect )
{
	sei();
	TCNT0 = T_TMR0;
	Time100us++;
	PulseWidth++;
	if(UART.recv_timeout)
	{
		UART.recv_timeout--;
		if(!UART.recv_timeout)
		{
			UART.recvbuff_ovf = 1;
			UART.recv_cnt = 0;
		}
	}

	if(SPI.recv_timeout)
	{
		SPI.recv_timeout--;
		if(!SPI.recv_timeout)
		{
			SPI.SPI_recvbuff_ovf = 1;
			SPI.f_spi_recv   = 0;
			SPI.f_spi_update = 1;
		}
	}
	/******判断SPI片选使能，开clk接收中断*****/
	//if((PIN_SPI_CS_WIFI || PIN_SPI_CS_LAN)&&(!SPI.SPI_en))
	if(PIN_SPI_CS_LAN&&(!SPI.SPI_en))
	{
		SPI.SPI_en       = 1;
		SPI.SPI_recv_len = 0;
		SPI.recv_timeout = 30;    //3ms接收超时，表示接收完成
		SPI.f_spi_recv   = 1;
		PCIFR |= 0x01;
		PCICR |= 0x01;
	}
	else if((!PIN_SPI_CS_LAN)&&SPI.SPI_en)
	{
		SPI.SPI_en       = 0;
		SPI.f_spi_update = 0;
		SPI.f_spi_recv   = 0;
		SPI.recv_cnt	 = 0;
		PCICR &= ~0x01;
	}
	
	// 检测脉冲输入是否变化
		if (PIN_HALL1 == f_LastPulse1)
		{
			SamplingCount1 = 0;
		}
		else
		{
			SamplingCount1++;
			if (SamplingCount1 >= 3)//脉冲计数去抖时间：0.5ms
			{
				if (f_LastPulse1)
				{
					f_LastPulse1 = 0;
				}
				else
				{
					f_LastPulse1 = 0x01;
				}
				SamplingCount1 = 0;
                                if (f_ReallyStop)
                                {
                                        if (PullDir != LastDir)
                                        {
                                              PullCnt = 0;
                                              LastDir = PullDir;
                                        }
                                        if (PulseWidth < 0x300)
                                        {
                                              if (PullCnt < PULL_CNT)
                                              {
                                                    PullCnt++;
                                              }
                                        }
                                        else
                                        {
                                                PullCnt = 0;
                                        }
                                 }
                                 else
                                 {
                                         if (PulseWidth > 0x50)
                                         {
                                                Pulse[0] = Pulse[1];
                                                Pulse[1] = Pulse[2];
                                                Pulse[2] = Pulse[3];
                                                Pulse[3] = PulseWidth;
                                         }
                                 }
				PulseWidth = 0;
	               }
		}
		if (PIN_HALL2 == f_LastPulse2)
		{
			SamplingCount2 = 0;
		}
		else
		{
			SamplingCount2++;
			if (SamplingCount2 >= 3)//脉冲计数去抖时间：0.5ms
			{
				if (f_LastPulse2)
				{
					f_LastPulse2 = 0;
				}
				else
				{
					f_LastPulse2 = 0x02;
				}
				SamplingCount2 = 0;
				
				if (f_Start)	// 启动加速
				{
					BreakTime = T_BREAK_START;	// 设置堵转检测时间
				}
				else			// 正常运行
				{
					BreakTime = T_BREAK_RUN;		// 设置堵转检测时间
				}
				if (f_LastPulse2)		// 脉冲计数		__|--|__|--|__
				{//										  __|--|__|--|__
					if (f_LastPulse1)
					{
                      
                                                PullDir = 0;
						CurPosReal--;
					}
					else
					{
                                                PullDir = 1;
						CurPosReal++;
					}
				}
				else
				{
					if (f_LastPulse1)			 
					{
                                                PullDir = 1;
						CurPosReal++;
					}
					else
					{
                      
                                                PullDir = 0;
						CurPosReal--;
					}
				}
				if (f_Start)
				{
					if (StartCounter>0)
					{
						StartCounter--;
						if (!StartCounter)
						{
							f_Start = 0;
							en_CheckForce = 1;
						}
					}
				}
			}
		}
   
}
//=============================================================
//main program
//-------------------------------------------------------------
int main(void)
{
	Init();
	for ( ; ; )
	{
		SPI_process();
		max485_tarns();
		
		// 保存缓冲区中的力量数据到EEPROM
		
		if (Time100us < 5)
		{
			continue;
		}
		
		// Every 0.5ms
		Time100us = 0;
		Time05ms++;
		
		wdt_reset();
		cli();
		CurPosition = CurPosReal;
		sei();

		GetLimit();
                
		if (f_Running)
		{
                        f_LimitRerse = 0;
                        if (f_MidLimit)
			{
                                clearclucth_relay = 7;
				Stop();
			}
			if (DoorStatus == OPEN)		
			{
				if (f_OpenLimit)
				{
                                        clearclucth_set(1,6,7);
                                        f_Limitback = 1;
					Stop();
				}
			}
			else if(DoorStatus == CLOSE)
			{
				if (f_CloseLimit)
				{
                                        clearclucth_set(1,6,7);
                                        f_Limitback = 1;
					Stop();
				}
			}
		}
		// Every 10ms
		if (Time05ms < 20)
		{
			continue;
		}
		Time05ms = 0;
		Time10ms++;
		if (DelLimtTime)
		{
			DelLimtTime--;
		}
		if (RelayDelay > 0)
		{
			RelayDelay--;
			if (!RelayDelay)
			{
				if (f_Running)
				{
                                        
                                        if(pullstartflag && f_Limit)
                                        {
                                                OCR1B = 255;
                                        }
                                        else if(pullstartflag && !f_Limit)
                                        {
                                          
                                                OCR1B = 150;
                                        } 
                                        else
                                        {
                                                OCR1B = START_SPEEDUP;
                                        }
                                        
					TCCR1A = 0x21;  // OCR1B输出，相位修正的PWM模式
					TCCR1B = 0x01;  // 1分频
					f_SpeedUp = 1;  // 加速标志
                                        Startup_Time = START_TIME;
				}
				else
				{
					CLR_DOOR;
				}
			}
		}
		if (f_SpeedUp)  // 加速
		{
                        if(Startup_Time > 0)
                        {
                            Startup_Time--;

                            if(Startup_Time == 0)
                            {
                                  if(pullstartflag)
                                  {
                                          if(f_Limit)
                                          {
                                                OCR1B = 255;
                                          }
                                          else
                                          {
#ifdef NEW
                                              OCR1B = 120;
#else
                                              OCR1B = 150;
#endif
                                                
                                          }
                                  }
                                  else
                                  {
                                          OCR1B = START_SPEEDUP;
                                  }
                            }
                        }
                        if(Startup_Time == 0)
                        {
                            unsigned char comp;
                            if(f_Limit)
                            {
                                comp = 254;
                            }
                            else
                            {
#ifdef NEW
                                comp = 120;
#else
                                comp = 150;
#endif
                            }
			    if (OCR1B < comp)
			    {
				OCR1B += 1;
			    }
			    else
			    {
				f_SpeedUp = 0;
			    }
                        }
			if (f_SpeedDown) 
			{
				if (OCR1B >= EndSpeedDown)
				{
					f_SpeedUp = 0;
				}
			}
		}

                if (f_SpeedDown)  //减速
		{
			if (!f_SpeedLow)
			{
				if (OCR1B > EndSpeedDown)
				{
					OCR1B -= 2;
				}
				else
				{
					f_SpeedLow = 1;
                                        //LowspeedPulse = Pulse[3];
				}
			}
		}
		
		GetKey();
                
		if (!f_Setting)
		{
                        if (f_RemOpenPush || f_RemClosePush || f_RemSetPush)
			{
				StopCnt = 0;
			}
                       
			if (f_Running)
			{
				if (f_RemStopPush || f_StopPush || f_AC_Stop || f_com_stop)
				{
                                        f_AC_Stop = 0;
                                        f_com_stop = 0;
                                        clearclucth_relay = 7;
                                        if (f_Way)
	                                {
		                              if ((CurPosition > OpenPosition - 18) || (CurPosition < ClosePosition + 18))
		                              {
                                                    f_Limitback_1 = 1;
                                                    clearclucth_set(1,8,7);
		                              }
	                                }
	                                else
	                                {
		                              if ((CurPosition < OpenPosition + 18) || (CurPosition > ClosePosition - 18))
		                              {
                                                    f_Limitback_1 = 1;
                                                    clearclucth_set(1,8,7);
		                              }
	                                }
					Stop();
				}
                                if(f_com_runtopecent)
                                {
                                        if (ClosePosition > OpenPosition)
		                        {
			                        MidPosition2 = OpenPosition + (ClosePosition - OpenPosition)*runtopecent / 100;
		                        }
	                                else
	                                {
		                                MidPosition2 = OpenPosition - (OpenPosition - ClosePosition)*runtopecent / 100;
	                                }
                                        Stop();
                                        ReverseTime = T_REVERSE;
                                        
                                }
				if (DoorStatus == OPEN)
				{
					if (f_RemClosePush || f_ClosePush || f_AC_Close || f_com_close)
					{
                                                f_AC_Close = 0;
                                                f_com_close = 0;
						Stop();
						ReverseTime = T_REVERSE;
					}
				}
				else
				{
					if (f_RemOpenPush || f_OpenPush || f_AC_Open || f_com_open)
					{
                                                f_AC_Open = 0;
                                                f_com_open = 0;
						Stop();
						ReverseTime = T_REVERSE;
					}
				}
			}
			else
			{
                                if (f_RemOpenPush || f_OpenPush || f_AC_Open || f_com_open)
				{
                                        f_AC_Open = 0;
                                        f_com_open = 0;
                                        Open();
				}
				if (f_RemClosePush || f_ClosePush || f_AC_Close || f_com_close)
				{
                                        f_AC_Close = 0;
                                        f_com_close = 0;
                                        Close();
				}
                                if(f_com_runtopecent)
                                {
                                        if (ClosePosition > OpenPosition)
		                        {
			                        MidPosition2 = OpenPosition + (ClosePosition - OpenPosition)*runtopecent / 100;
		                        }
	                                else
	                                {
		                                MidPosition2 = OpenPosition - (OpenPosition - ClosePosition)*runtopecent / 100;
	                                }
                                        f_com_runtopecent = 0;
                                        Percent = runtopecent;
                                        RunToMid(MidPosition2);
                                        
                                }
				if (f_Key1Hold)
				{
					if (KeyHoldTime < 200)
					{
						KeyHoldTime++;
						if (KeyHoldTime == 200)
						{
							SET_LED1;
							f_Setting = 1;
                                                        f_set_addr = 1;
                                                        set_addr_time = T_SET_ADDR;
                                                        Task_Menu = MENU_SET;
						}
					}
				}
				
                                
			}
		}
                
		if (f_ThirdPos)
		{
			if (f_RemStopHold && (RemKeyHoldTime<240))
			{
				RemKeyHoldTime++;
				if (RemKeyHoldTime==200)
				{
					RunToMid(MidPosition1);
				}
                                if ((RemKeyHoldTime >= 200) && (RemKeyHoldTime < 240))
                                {
					f_RemStopPush = 0;
                                }
			}
		}

		if (en_CheckForce)		// 检测负载力
		{
			GetForce();
		}
                
		if (f_Running)
		{
			if (f_ForceOver)
			{
                              if (f_Way)
	                      {
		                    if ((CurPosition > OpenPosition - 12) || (CurPosition < ClosePosition + 12))
		                    {
                                          /*ClearDoor_sec = 1;
                                          cleardoor_delay = 6;
                                          BackPosition = 1;
                                          clearclucth_relay = 7;*/
                                          clearclucth_set(1,6,7);
                                          f_Limitback = 1;
                                          
                                          //clearclucth_relay = 10;
		                    }
                                    else
                                    {
                                          /*ClearDoor_sec = 2;
                                          cleardoor_delay = 8;
                                          BackPosition = 1;
                                          clearclucth_relay = 7;*/
                                          clearclucth_set(1,6,7);
                                    }
	                      }
	                      else
	                      {
		                    if ((CurPosition < OpenPosition + 12) || (CurPosition > ClosePosition - 12))
		                    {
			                  /*ClearDoor_sec = 1;
                                          cleardoor_delay = 6;
                                          BackPosition = 1;
                                          clearclucth_relay = 7;*/
                                          f_Limitback = 1;
                                          clearclucth_set(1,6,7);
                                          //clearclucth_relay = 10;
		                    }
                                    else
                                    {
                                          /*ClearDoor_sec = 2;
                                          cleardoor_delay = 8;
                                          BackPosition = 1;
                                          clearclucth_relay = 7;*/
                                          clearclucth_set(1,6,7);
                                    }
		
	                      }
                              Stop();
			}
			
			if (BreakTime > 0 )	// 检测电机堵转
			{
				BreakTime--;
				if (BreakTime == 0 )
				{
					f_ForceOver = 1;
                                        dis_PullStartTime = T_PULLSTARTRELAY;
                                        if(en_PullStart)
                                        {
                                              en_PullStart = 0;
                                              dis_PullStart = 1;
                                        }
				}
			}
			
			if (f_RunTimeOver)
			{
				f_RunTimeOver = 0;
                                clearclucth_relay = 7;
				Stop();
			}
		}
		if (ReverseTime)
		{
			ReverseTime--;
			if (!ReverseTime)
			{
                                if(f_com_runtopecent)
                                {
                                        f_com_runtopecent = 0;
                                        RunToMid(MidPosition2);
                                }
				if (DoorStatus == OPEN)
				{
					Close();
				}
				else
				{
					Open();
				}
			}
		}
		if (!f_Setting && f_Running && !f_DetectSpeeddown && f_Limit)
		{
			DetectSpeeddownPos();
		}
                
                if(f_cleardoor && Cleardoor)
                {
                        Cleardoor--;
                        if(!Cleardoor)
                        {
                              f_cleardoor = 0;
                              CLR_DOOR;
                        }
                }
                
                if(f_clearclucth && Clearclucth)
                {
                        Clearclucth--;
                        PullCnt = 0;
                        if(OCR1B < 200)
                        {
                            OCR1B += 10;
                        }
                        if(!Clearclucth)
                        {
                              f_ReallyStop = 1;
                              //f_cleardoor = 1;
                              
                              //Cleardoor = T_CLEARDELAY1;
                              TCCR1A = 0x00;
	                      TCCR1B = 0x00;
	                      CLR_PWM;
                              f_clearclucth = 0;
			      CurPositionBack = CurPosition;
			      EE_WriteInt(ADDR_POS_CUR, CurPosition);
			      EE_CheckReady();
                              //if(ClearDoor_sec && (!f_Openback) && (!f_Closeback))
                              if(ClearDoor_sec)
                              {
                                    ClearDoor_sec = 0;
                                    CountDelay_sec = 30;
                              }
                              //f_Openback = 0;
                              //f_Closeback = 0;
                        }
                }
                
                if(dis_PullStartTime)
                {
                      dis_PullStartTime--;
                      if((!dis_PullStartTime) && dis_PullStart)
                      {
                            dis_PullStart = 0;
                            pullflag1 = 0;
                            en_PullStart = 1;
                            PullCnt = 0;
                      }
                }
                
                if (en_PullStart && f_ReallyStop)
		{
			PullStart();
		}
                
		// Pulse count delay
		if (Time10ms < 10)
		{
			continue;
		}
		
		// Every 100ms
		Time10ms = 0;
		Time100ms++;
		
                if (DelThirdTime)
		{
			DelThirdTime--;
		}

		if (f_FlashLed)
		{
			FlashLed();
		}
                if (!f_Running && CountDelay_sec)
                {
                            CountDelay_sec--;
                            PullCnt = 0;
                            if(((DoorStatus == OPEN) && (OpenPosition > ClosePosition) && (CurPositionBack >= CurPosition + BackPosition)) ||
                              ((DoorStatus == OPEN) && (OpenPosition < ClosePosition) && (CurPositionBack <= CurPosition - BackPosition)) ||
                              ((DoorStatus == CLOSE) && (OpenPosition > ClosePosition) && (CurPositionBack <= CurPosition - BackPosition)) ||
                              ((DoorStatus == CLOSE) && (OpenPosition < ClosePosition) && (CurPositionBack >= CurPosition + BackPosition)))
                            { 
                                  if(CountDelay_sec < 10)
                                  { 
                                        CountDelay_sec = 0;
                                        
                                        if(!f_Limitback_1)
                                        {
                                            f_Limitback_1 = 0;
                                            PullCnt = PULL_CNT;
                                            PullStart();
                                        }
                                  }
                                  else
                                  {
                                        //PullCnt = 0;
                                        CurPositionBack = CurPosition;
                                        CountDelay = cleardoor_delay;
                                  }
                            }
                }
		if (!f_Running && CountDelay)//3s
		{
			CountDelay--;
			if (!CountDelay)
			{                            
                                f_clearclucth = 1;                                
                                if(DoorStatus == OPEN)
                                {
	                                  if (f_Reverse)
	                                  {
		                                    CLR_DOOR;
	                                  }
	                                  else
	                                  {
		                                    SET_DOOR;
	                                  }
                                }
                                if(DoorStatus == CLOSE)
                                {
	                                  if (f_Reverse)
	                                  {
		                                    SET_DOOR;
	                                  }
	                                  else
	                                  {
		                                    CLR_DOOR;
	                                  }
                                }
                               
                                if(f_Limitback)
                                {
                                      f_Limitback = 0;
                                      f_Limitback_1 = 1;
                                      Clearclucth = 10;
                                      OCR1B = 20;
                                      TCCR1A = 0x21;  // OCR1B输出，相位修正的PWM模式
				      TCCR1B = 0x01;  // 1分频
                                      //SET_PWM;
                                      CurPositionBack = CurPosition;
                                }
                                else
                                {
#ifdef NEW
                                      Clearclucth = clearclucth_relay;
#else
                                      Clearclucth = clearclucth_relay;
#endif                                  
                                      OCR1B = 40;
                                      TCCR1A = 0x21;  // OCR1B输出，相位修正的PWM模式
				      TCCR1B = 0x01;  // 1分频
                                      //SET_PWM;
                                      CurPositionBack = CurPosition;
                                }
			}
		}

		if (Time100ms < 10)
		{
			continue;
		}
		
		// Every 1s
		Time100ms = 0;
		Time1s++;
		if (f_Running && (TotalRunTime > 0))	// 总运行时间
		{
			TotalRunTime--;
			if (TotalRunTime == 0)
			{
				f_RunTimeOver = 1;
			}
		}
                
                if(set_addr_time > 0)
                {
                      set_addr_time--;
                      if(!set_addr_time)
                      {
                            f_set_addr = 0;
                      }
                }
                  
	}
}

//===========================================================
//Function:	上电和复位初始化。
//
//-----------------------------------------------------------
void Init()
{
	cli();
	
	DDRB = (1 << PWM);
	PORTD = (1 << LED1);
	DDRD = (1 << LED1)|(1<<EN_485)|(1 << DOOR_WAY)|(1 << MISO);
	PORTD = 0x80;
	//DDRD  |= 1 << DOOR_WAY;
        
	ACSR  = 0x80;	//disable Analog Comparator
        
	TCNT0 = T_TMR0;	// set count 8MHz
	TCCR0A = 0x00;	//
	TCCR0B = 0x02;	// 8分频
	TIMSK0 = 0x01;	// timer 0 interrupt sources
	MCUSR = 0x00;
	
	CLKPR = 0x80;
        CLKPR = 0x00;

        /*****外部电平变化中断*******/
        PCMSK0 = 0x01;
        PCMSK1 = 0x34;
        PCIFR = 0x03;
        PCICR = 0x02;

	if (MCUSR & (1<<WDRF))
	{
		MCUSR = 0x00;					//复位状态寄存器
		WDTCSR |= (1<<WDCE) | (1<<WDE);	// WATCHDOG ENABLED，使能看门狗
		WDTCSR |= (1<<WDE) | (1<<WDP1) | (1<<WDP0); // 64ms喂狗
                DoorStatus = CLOSE;
		CurPosition = EE_ReadInt(ADDR_POS_CUR);
		CurPosReal = CurPosition;
	}
	else								// 上电复位、掉电检测复位、外部复位
	{
		_delay_ms(120);
		WDTCSR |= (1<<WDCE) | (1<<WDE);	// WATCHDOG ENABLED，使能看门狗
		WDTCSR |= (1<<WDE) | (1<<WDP1) | (1<<WDP0); // 125ms喂狗
	}
        f_ReallyStop = 1;
	f_LastPulse1 = PIN_HALL1;
	f_LastPulse2 = PIN_HALL2;
	f_Reverse = EE_ReadBYTE(ADDR_REVERSE_FLAG);
        
	en_PullStart = EE_ReadBYTE(ADDR_PULL_START);
        ID = EE_ReadBYTE(ADDR_ID);
	CurPosition = 0x7fff;
	CurPosReal = 0x7fff;
        ClosePosition = 0x7fff;
        OpenPosition = 0x7fff;
        
        POS_SPEEDDOWN_OPEN = POS_SPEEDDOWN;
        
        USART_Init();
	sei();
	SetLed(LED1, 3, 1);
        f_Remotedelay = 1;
        f_DetectSpeeddown = 1;
        f_DetectLimit = 1;
        BackPosition = 1;
}

//===========================================================
//Function:	初始化相关参数并开始开门。
//
//-----------------------------------------------------------
void InitRun(void)
{
	f_Running = 1;
	//SET_CLUCTCH;
        Cleardoor = 0;
	TotalRunTime = T_TOTALRUN;		// 设置总运行时间
	BreakTime = T_BREAK_START;		// 设置电机堵转时间
	f_ForceOver = 0;
	en_CheckForce = 0;
	f_Start = 1;
	StartCounter = STARTUP_DIST;
	f_ReallyStop = 0;
	f_SpeedDown = 0;
	f_SpeedLow = 0;
        f_cleardoor = 0;
        f_clearclucth = 0;
	RelayDelay = 5;
        PullCnt = 0;
        ClearDoor_sec = 0;
        CountDelay_sec = 0;
        f_LimitRerse = 0;
        f_Limitback = 0;
        f_Limitback_1 = 0;
        //f_Openback = 0;
        //f_Closeback = 0;
        /*if((OpenPosition == ClosePosition)&&f_Limit)
        {
              SetLed(LED1, 1, 10);
        }
        else
        {
              SET_LED1;
        }*/
        SET_LED1;
        for(unsigned char i=0;i<8;i++)
          table[i]=0;
}
void Open(void)
{
	if (ReverseTime)
	{
		return;
	}
	if (f_OpenLimit && (!f_DetectLimit) && f_Limit)
	{
		return;
	}
        if (f_Way)//调试
	{
		if ((CurPosition > OpenPosition - 20) && (!f_Setting) && f_Limit && (f_LimitRerse))
		{
			return;
		}
	}
	else
	{
		if ((CurPosition < OpenPosition + 20) && (!f_Setting) && f_Limit && (f_LimitRerse))
		{
			return;
		}
	}
	DoorStatus = OPEN;
	InitRun();
	if (f_Reverse)
	{
		SET_DOOR;
	}
	else
	{
		CLR_DOOR;
	}
}

void Close(void)
{
	if (ReverseTime)
	//if (ReverseTime || (CountDelay > 5))
	{
		return;
	}
	if (f_CloseLimit && (!f_DetectLimit) && f_Limit)
	{
		return;
	}
        if (f_Way)//调试
	{
		if ((CurPosition < ClosePosition + 20) && (!f_Setting) && f_Limit && (f_LimitRerse))
		{
			return;
		}
	}
	else
	{
		if ((CurPosition > ClosePosition - 20) && (!f_Setting) && f_Limit && (f_LimitRerse))
		{
			return;
		}
	}
        I_detectime0 = 150;
        I_detectime1 = 0;
	DoorStatus = CLOSE;
	InitRun();
	if (f_Reverse)
	{
		CLR_DOOR;
	}
	else
	{
		SET_DOOR;
	}
}

void Stop(void)
{
	f_Running = 0;
        CLR_LED1;
	f_Start = 0;
        f_RunToMid = 0;
        f_DetectSpeeddown = 0;
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	CLR_PWM;
	//RelayDelay = 110;
	en_CheckForce = 0;
        f_SpeedDown = 0;     //调试
        f_SpeedLow = 0;     //调试
        PullCnt = 0;
        pullstartflag = 0;
        sum_ad_in = 0;
	CountDelay = T_COUNTDELAY;
        f_cleardoor = 1;
        Cleardoor = 40*T_CLEARDELAY1;
	if (f_ForceOver)
	{
                if(!f_Limit)
                {
                      if(DoorStatus == OPEN)
                      {
                            OpenPosition = CurPosition;
                            f_setOpenLimit = 1;
                            //f_Openback = 1;
                            //f_Closeback = 0;
                            /*ClearDoor_sec = 1;
                            cleardoor_delay = 6;
                            BackPosition = 1;
                            clearclucth_relay = 7;*/
                            f_Limitback = 1;
                            clearclucth_set(1,6,7);
                            if(f_setCloseLimit)
                            {
                                  SetLimit();
                            }
                      }
                      else if(DoorStatus == CLOSE)
                      {
                            ClosePosition = CurPosition;
                            f_setCloseLimit = 1;
                            //f_Openback = 0;
                            //f_Closeback = 1;
                            /*ClearDoor_sec = 1;
                            cleardoor_delay = 6;
                            BackPosition = 1;
                            clearclucth_relay = 7;*/
                            clearclucth_set(1,6,7);
                            f_Limitback = 1;
                            if(f_setOpenLimit)
                            {
                                  SetLimit();
                            }
                      }
                }
                if (f_Way)//调试
	        {
		        if ((CurPosition > OpenPosition - 8) || (CurPosition < ClosePosition + 8))
		        {
			        f_LimitRerse = 1;
		        }
		
	        }
	        else
	        {
		        if ((CurPosition > OpenPosition - 8) || (CurPosition < ClosePosition + 8))
		        {
			        f_LimitRerse = 1;
		        }
		
	        }
                f_ForceOver = 0;
                //CountDelay = 5 * T_COUNTDELAY;
                f_stop = 1;
	}
        
        if (f_MidLimit)
	{
		DelThirdTime = 100;//10S
	}
}

unsigned char ack_cmd(void)//应答
{
      if (ClosePosition > OpenPosition)
      {
            if (CurPosition >= ClosePosition - 4)
            {
                  Percent = 100;
            }
            else if (CurPosition <= OpenPosition + 4)
            {
                  Percent = 0;
            }
            else
            {
                  Percent = ((CurPosition - (OpenPosition + 4)) * 100) / (ClosePosition - OpenPosition - 8);
                  if((f_runtopercent) && (!f_Running))
                  {
                        f_runtopercent = 0;
                        if((Percent < Percent_mid + 7) && (Percent > Percent_mid - 7))
                        {
                              Percent = Percent_mid;
                        }
                  }
            }
      }
      else
      {
            if(!f_Limit)
            {
                  Percent = 0;
            }
            else if (CurPosition <= ClosePosition + 4)
            {
                  Percent = 100;
            }
            else if (CurPosition >= OpenPosition - 4)
            {
                  Percent = 0;
            }
            else
            {
	          Percent = (OpenPosition - 4 - CurPosition) * 100 / (OpenPosition - ClosePosition - 8);
                  //if((f_runtopercent) && (!f_Running))
                  if(!f_Running)
                  {
                        f_runtopercent = 0;
                        if((Percent < Percent_mid + 7) && (Percent > Percent_mid - 7))
                        {
                              Percent = Percent_mid;
                        }
                        Percent_mid1 = Percent;
                  }
                  else if(f_Running)
                  {
                        if((Percent < Percent_mid1 + 7) && (Percent > Percent_mid1 - 7))
                        {
                              Percent = Percent_mid1;
                        }
                  }
            }
      }
      if(Percent > 100) Percent = 100;
      return  Percent;    
}

//===========================================================
//Function:	检测行程限位,如果到达开门限位位置，则置开门到位标志；
//			如果到达关门限位位置，则置关门到位标志。
//
//------------------------------------------------------------

void GetLimit(void)
{
	f_OpenLimit = 0;
	f_CloseLimit = 0;
        f_MidLimit = 0;
	/*if (OpenPosition > ClosePosition)
	{
		f_Way = 1;
	}
	else
	{
		f_Way = 0;
	}*/
        if(f_Reverse)
        {
              f_Way = 0;
        }
        else
        {
              f_Way = 1;
        }
        if (f_DetectLimit)
	{
		return;
	}
	if (f_Way)
	{
		if (CurPosition > OpenPosition - 3)
		{
			f_OpenLimit = 1;
                        f_Limitback = 1;
                        f_LimitRerse = 1;
                        /*ClearDoor_sec = 1;
                        cleardoor_delay = 6;
                        BackPosition = 1;
                        clearclucth_relay = 7;*/
                        clearclucth_set(1,6,7);
		}
		if (CurPosition < ClosePosition + 3)
		{
			f_CloseLimit = 1;
                        f_Limitback = 1;
                        f_LimitRerse = 1;
                        /*ClearDoor_sec = 1;
                        cleardoor_delay = 6;
                        BackPosition = 1;
                        clearclucth_relay = 7;*/
                        clearclucth_set(1,6,7);
		}
		/*if (f_ThirdPos)
		{
		        //删除第三个行程点
			if ((MidPosition1 > OpenPosition - 10) || (MidPosition1 < ClosePosition + 10))
			{
			    f_ThirdPos = 0;
			    EE_WriteBYTE(ADDR_THIRD_POS_FLAG, f_ThirdPos);
			    EE_CheckReady();
		        }
		}*/
	}
	else
	{
		if (CurPosition < OpenPosition + 3)
		{
			f_OpenLimit = 1;
                        f_Limitback = 1;
                        f_LimitRerse = 1;
                        /*ClearDoor_sec = 1;
                        cleardoor_delay = 6;
                        BackPosition = 1;
                        clearclucth_relay = 7;*/
                        clearclucth_set(1,6,7);
		}
		if (CurPosition > ClosePosition - 3)
		{
			f_CloseLimit = 1;
                        f_Limitback = 1;
                        f_LimitRerse = 1;
                        /*ClearDoor_sec = 1;
                        cleardoor_delay = 6;
                        BackPosition = 1;
                        clearclucth_relay = 7;*/
                        clearclucth_set(1,6,7);
		}
		/*if (f_ThirdPos)
		{
                  
		        //删除第三个行程点
			if((MidPosition1 < OpenPosition) || (MidPosition1 > (ClosePosition - 10)))
			{
			    f_ThirdPos = 0;
			    EE_WriteBYTE(ADDR_THIRD_POS_FLAG, f_ThirdPos);
			    EE_CheckReady();
		        }
		}*/
	}
        if (f_RunToMid)
	{
		if (CurPosition == MidPosition)
		{
			f_MidLimit = 1;
		}
	}
}




//================================================================
//Function:	检测过载，设置过载标志，并更新保存的负载力值。
//
//----------------------------------------------------------------
void GetForce(void)
{
	unsigned int ForceBag[PULSE_COUNTER];
	//unsigned char ForceRange;
        
	cli();
	memcpy(ForceBag, Pulse, PULSE_COUNTER);
	sei();
	if (f_DetectLimit | f_Start)
	{
                /*if(DoorStatus == CLOSE)
                {
                    
                    if(I_detectime0 > 0)
                    {
                        I_detectime0--;
                        return;
                    }
                    I_detectime1++;
                    if(I_detectime1 > 350)
                    {
                          return;
                    }
                    sum_ad_in = ADInputFilter(0x06);
                    ad_in = ADInputFilter(0x06);
                    sum_ad_in +=  ad_in;
                    sum_ad_in = (sum_ad_in >> 1);
                }*/
		return;
	}
        ad_in = ADInputFilter(0x06);
        sum_ad_in +=  ad_in;
        sum_ad_in = (sum_ad_in >> 1);
	/*if (f_SpeedDown && !f_SpeedLow)
	{
		ForceRange = 3;
	}
	else
	{
		ForceRange = 2;
	}
	if (((Pulse[2] >= Pulse[0]*ForceRange) || (Pulse[3] >= Pulse[1]*ForceRange)) && (Pulse[0] > 0x1FF))
	{
		f_ForceOver = 1;
                dis_PullStartTime = T_PULLSTARTRELAY;
                if(en_PullStart)
                {
                      en_PullStart = 0;
                      dis_PullStart = 1;
                }
	}*/
        
        if(sum_ad_in > FORCEOVER)
        {          
              f_ForceOver = 1;
              dis_PullStartTime = T_PULLSTARTRELAY;
              if(en_PullStart)
              {
                    en_PullStart = 0;
                    dis_PullStart = 1;
              }
        }
}

void SetLed(unsigned char FlashPort, unsigned char FlashPeriod, unsigned char FlashTimes)
{
	Flash_Port = FlashPort;
	FlashPeriod_Led = FlashPeriod;
	FlashTime_Led = FlashTimes;
	f_FlashLed = 0xff;
	LedStatus = 0xff;
}

void FlashLed(void)
{
	static unsigned char FlashPeriod;
	if (!FlashPeriod)
	{
	    if (LedStatus)
		{
			if (Flash_Port == LED1)
			{
				SET_LED1;
			}
			LedStatus = 0;
		}
		else
		{
			if (Flash_Port == LED1)
			{
				CLR_LED1;
			}
			
			LedStatus = 0xff;
			if (FlashTime_Led)
			{
				FlashTime_Led--;
				if (!FlashTime_Led)
				{
					CLR_LED1;
					f_FlashLed = 0;
					return;
				}
			}
		}
		FlashPeriod = FlashPeriod_Led;
	}
	FlashPeriod--;
}

void GetKey(void)
{
        unsigned char temp,temp1,temp2;
        f_StopPush = 0;
        f_OpenPush = 0;
        f_ClosePush = 0;
	if(f_KeyswChange)
        {
             temp = PIN_SW_KEY2;
             temp1 = PIN_SW_KEY1;
             temp2 = PIN_KEY1;
             temp = temp + temp1 + temp2;
             if(inputbuf == temp)
             {
                  ChangeHoldtime++;
             }
             else
             {
                  f_KeyswChange = 0;
                  ChangeHoldtime = 0;
             }
             if(ChangeHoldtime >= 5)
             {
                   f_KeyswChange = 0;
                   ChangeHoldtime = 0;
                   switch(inputbuf)
                   {
                               case 0x34:
                                  f_StopPush = 1;
                                  break;
                               case 0x14:
                                  f_OpenPush = 1;
                                  break;
                               case 0x24:
                                  f_ClosePush = 1;
                                  break;
                               case 0x00:
                                  f_Key1Hold = 1;
                                  break;
                               case 0x04:
                                  f_Key1Hold = 0;
                                  break;   
                               default:
                                  break;
                    }
              }
        }
}


void PullStart(void)
{
    if (PullCnt == PULL_CNT)
    {
        pullstartflag = 1;
        pullflag1 = 0;
        if (!LastDir)
        {
            if (f_Way)
            {
                Close();
            }
            else
            {
                Open();
            }
        }
        else
        {
            if (f_Way)
            {
                Open();
            }
            else
            {
                Close();
            }
        }
    }
}
void Reverse(void)
{
	unsigned int TempPos;
	if (f_Reverse)
			{
				f_Reverse = 0;
			}
			else
			{
				f_Reverse = 1;
			}
			EE_WriteBYTE(ADDR_REVERSE_FLAG, f_Reverse);
			EE_CheckReady();
			
			TempPos = OpenPosition;
			OpenPosition = ClosePosition;
			ClosePosition = TempPos;
			
			EE_WriteInt(ADDR_POS_OP, OpenPosition);
			EE_CheckReady();
			EE_WriteInt(ADDR_POS_CL, ClosePosition);
			EE_CheckReady();
			
			GetLimit();
}
//===========================================================
//Function: 检测是否到达减速起始位置，如果到达则置减速标志位。
//
//-----------------------------------------------------------
void DetectSpeeddownPos(void)
{
	if (ClosePosition > OpenPosition)
	{
		if (((DoorStatus == OPEN) && (CurPosition <= (OpenPosition + POS_SPEEDDOWN_OPEN))) || 
			((DoorStatus == CLOSE) && (CurPosition >= (ClosePosition - POS_SPEEDDOWN))))
		//if ((DoorStatus == CLOSE) && (CurPosition >= (ClosePosition - POS_SPEEDDOWN)))
		{
			f_DetectSpeeddown = 1;
			f_SpeedDown = 1;
                        if(sum_ad_in < 25)
                        {
			    EndSpeedDown = END_SPEEDDOWN1;          // 2/5
                        }
                        else if((sum_ad_in > 25)&&(sum_ad_in < 50))
                        {
                            EndSpeedDown = END_SPEEDDOWN2;          // 2/5
                        }
                        else
                        {
                            EndSpeedDown = END_SPEEDDOWN3;          // 2/5
                        }
		}
	}
	else
	{
		if (((DoorStatus == OPEN) && (CurPosition >= (OpenPosition - POS_SPEEDDOWN_OPEN))) || 
			((DoorStatus == CLOSE) && (CurPosition <= (ClosePosition + POS_SPEEDDOWN))))
		//if ((DoorStatus == CLOSE) && (CurPosition <= (ClosePosition + POS_SPEEDDOWN)))
		{
			f_DetectSpeeddown = 1;
			f_SpeedDown = 1;
			if(sum_ad_in < 18)
                        {
			    EndSpeedDown = END_SPEEDDOWN1;          // 2/5
                        }
                        else if((sum_ad_in > 18)&&(sum_ad_in < 30))
                        {
                            EndSpeedDown = END_SPEEDDOWN2;          // 2/5
                        }
                        else
                        {
                            EndSpeedDown = END_SPEEDDOWN3;          // 2/5
                        }
		}
	}
}

//===========================================================

//Name:		GetADInput(u8 Chanel)

//Function:	进行8BIT A/D转换，返回转换结果

//Input:	Chanel-AD通道

//Output:	ADCH-AD数值

//UseNote:	需要AD转换的时候调用

//----------------------------------------------------------
unsigned char GetADInput(unsigned char Chanel)

{
	
  ADMUX = 0x60 | Chanel;
	
  ADCSRA = 0xC6;
	
  ADCSRB = 0x00;
	
  while (ADCSRA & BIT(ADSC)) { ;}
	
  return(ADCH);

}
//======================================
  //name:       ADInputFilter(u8 Chanel)
  //Function:	对AD输入数值进行8阶滑动滤波

 //Input:	Chanel-AD通道

 //Output:	ADCH-AD滤波后数值

 //UseNote:    需要AD转换的时候调用
//----------------------------------------------------------

unsigned char ADInputFilter(unsigned char Chanel)
{
  //static unsigned char table[8];
  static unsigned char i;
  unsigned int sum;
  unsigned char temp,count;
  sum = 0;
  table[i] = GetADInput(Chanel);
  i++;
  if(i > 7) i = 0;
  for(count = 0;count < 8;count++)
  {
    sum += table[count];
  }
  temp = sum >> 3;
  return temp;
}

void RunToMid(unsigned int Mid_Position)
{
	MidPosition = Mid_Position;
	if ((CurPosition > MidPosition-5) && (CurPosition < MidPosition+5))
	{
		return;
	}
	f_RunToMid = 1;
        f_runtopercent = 1;
        Percent_mid = Percent;
	if (CurPosition > MidPosition)
	{
		if (!f_Way)
		{
			Open();
		}
		else
		{
			Close();
		}
	}
	else
	{
		if (!f_Way)
		{
			Close();
		}
		else
		{
			Open();
		}
	}
}

/*void GoToSleep(void)
{
	ADCSRA &= 0x7f;//关闭ADC
	ACSR &= 0x77;//关闭模拟比较器
        
        WDTCSR=(1<<WDCE) | (1<<WDE); //关闭看门狗复位
	WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP1) | (1<<WDP0); //使能看门狗中断， 125ms中断
        
        PCIFR = 0x07;
        PCICR |= 0x07;   //开启外部电平变化中断
              
        cli();
        CLKPR = 0x80;
        CLKPR = 0x03;
        sei();
	
	SMCR =  (1<<SM1);
	do
	{
              CLR_DECV;
              //CLR_HOLL;
              CLR_RF;
              CLR_LED1;
              TCCR0A = 0x00;	//
              TCCR0B = 0x00;	// 关闭T0定时器
	      TIMSK0 = 0x00;	// 关闭T0中断源
              
              TCCR1B = 0x00;      //禁止定时器1
              TIFR1 |= (1 << ICIE1);
              TIMSK1 &= ~(1 << ICIE1); //清中断

              clrwdt();
              
              SMCR |= BIT(SE);
	      __sleep();//开始睡眠
              SMCR &= ~BIT(SE);
             
	      __delay_cycles(8);
              
              if(!f_Powerdown)
              {
                    if (f_Timerwake)
		    {
                        f_Timerwake = 0;
                        SET_RF;
                        f_RFlast = PIN_RFIN;
                        Recv_Type = 1;
                        __delay_cycles(10);
                        
                        TCCR1B = 0x02;      //捕获功能，8分频
                        if (PIN_RFIN)
                        {
                                TCCR1B &= ~(1 << ICES1);
                        }
                        else
                        {
                                TCCR1B |= (1 << ICES1);
                        }
                        TCNT1H = 0;
                        TCNT1L = 0;
                        TIFR1 |= (1 << ICF1);
                        TIMSK1 = 1 << ICIE1;    //捕获中断使能

                        f_WakeTimerout = 0;
                        do{
                              __delay_cycles(8);
                              if(TIM16_ReadTCNT1() > 200)   //1.5MS无电平变化则进入休眠
                              {
                                  if (PIN_RFIN)
                                  {
                                        f_Sleep = 0;        //起床
                                  }
                                  f_WakeTimerout = 1;
                              }
                        }while(!f_WakeTimerout);
                        Powerdown_count++;
                        if(Powerdown_count > 20)  //3S检测一次
                        {
                              Powerdown_count = 0;
                              SET_DECV;
                              __delay_cycles(10);
                              if(!PIN_POWERDETECT)
                              {
                                    __delay_cycles(5000);//延时5MS
                                    if(!PIN_POWERDETECT)
                                    {
                                          f_Powerdown = 1;
                                          PCIFR = 0x07;
                                          PCICR = 0;        //禁止外部电平中断
                                    }
                              }
                              else
                              {
                                    f_Powerdown = 0;
                              }
                        }
                        if(!f_Timerwake)
                        {
                              RecvTimeout = T_RECVTIMEOUT;
                        }
		    }
                    if (f_Pcint0wake)
		    {
                        f_Pcint0wake = 0;
                        if(PIN_KEY1 == 0)
                        {
                              cli();
                              __delay_cycles(20000);//延时5MS
                              if(PIN_KEY1 == 0)
                              {  
                                    f_Sleep = 0;        //起床
                                    RecvTimeout = 0;
                              }
                              sei();
                        }
		    }
                    if (f_Pcint2wake)
		    {
                        f_Pcint2wake = 0;
                        RecvTimeout = 0;
                        f_Sleep = 0;        //起床
                        
                 
		    }
                    
                    if (f_Pcint1wake)
		    {
                        f_Pcint1wake = 0;
                        f_Sleep = 0;        //起床
                        RecvTimeout = 0;
		    }
              }
              else
              {
                   Powerdown_count++;
                   if(Powerdown_count > 20)  //3S检测一次
                   {
                        Powerdown_count = 0;
                        SET_DECV;
                        __delay_cycles(80);
                        if(!PIN_POWERDETECT)
                        {
                            __delay_cycles(5000);//延时5MS
                            if(!PIN_POWERDETECT)
                            {
                                f_Powerdown = 1;
                            }
                        }
                        else
                        {
                            __delay_cycles(5000);//延时5MS
                            if(PIN_POWERDETECT)
                            {
                                f_Powerdown = 0;
                                PCICR = 0x07;
                            }
                        }
                        Powerdown_count = 0;
                        SET_LED1;
                        __delay_cycles(20000);//延时20MS
                        CLR_LED1;
                    }
              }
                
              asm("nop");         
              TCCR2B=0x06;
              while(ASSR&0x1F); 
	}
	while (f_Sleep);
	
        cli();
        CLKPR = 0x80;
        CLKPR = 0x00;
        sei();
        
	TCCR1B = 0x00;      //禁止定时器1
        TIMSK1 &= ~(1 << ICIE1); //清中断
        
        PCIFR = 0x04;
        PCICR &= ~(0x04);   //关闭霍尔电平变化中断
        
	SET_RF;
        //SET_HOLL;
        
	InitTimer0();

	Wakeup_Hold = T_WAKETIOMEOUT;
	InitReceiver();
        
	MCUSR = 0x00;                               //启动看门狗
	WDTCSR |= (1<<WDCE) | (1<<WDE); 	    // WATCHDOG ENABLED
	WDTCSR = (1<<WDE) | (1<<WDP1) | (1<<WDP0);  //使能看门狗中断， 125ms中断
}*/

void InitTimer0(void)
{
	TCNT0 = T_TMR0;	// set count 8MHz
	TCCR0A = 0x00;	//
	TCCR0B = 0x02;	// 8分频
	TIMSK0 = 0x01;	// timer 0 interrupt sources
}

/*void InitTimer1(void)
{
	TCNT1 = T_TMR1;	// set count 8MHz
	TCCR1A = 0x00;	//
	TCCR1B = 0x02;	// 8分频
	TIMSK1 = 0x01;	// timer 1 interrupt sources
}*/
/*unsigned int TIM16_ReadTCNT1( void)
{
    unsigned char sreg;
    unsigned int i; 
    sreg = SREG;
    cli();
    i = TCNT1;
    SREG = sreg;
    sei();
    return i;
}

unsigned int TIM16_ReadICR1( void)
{
    unsigned char sreg;
    unsigned int i; 
    sreg = SREG;              // 保存全局中断标志    
    cli();    // 禁用中断   
    i = ICR1;                 // 将ICR1读入i 
    SREG = sreg;              // 恢复全局中断标志
    sei();
    return i;
}*/

void  SetLimit(void)
{
    f_DetectLimit = 0;
    f_setCloseLimit = 0;
    f_setOpenLimit = 0;
    /*if(OpenPosition == ClosePosition)
    {
          SetLed(LED1, 1, 10);
    }*/
    POS_SPEEDDOWN_OPEN = POS_SPEEDDOWN;
    EE_WriteInt(ADDR_POS_OP, OpenPosition);
    EE_CheckReady();
    EE_WriteInt(ADDR_POS_CL, ClosePosition);
    EE_CheckReady();
    EE_WriteInt(ADDR_POS_SPEEDDOWN, POS_SPEEDDOWN);
    EE_CheckReady();
    f_Limit = 1;
    EE_WriteBYTE(ADDR_LIM_FLAG, f_Limit);
    EE_CheckReady();
    if(OpenPosition > ClosePosition)
    {
        distance = OpenPosition - ClosePosition;
    }
    else
    {
        distance = ClosePosition - OpenPosition;
    }
    EE_WriteInt(ADDR_POS_DISTANSE, distance);
    EE_CheckReady();
    
    f_ThirdPos = EE_ReadBYTE(ADDR_THIRD_POS_FLAG);
    if(f_ThirdPos == 1)
    {
          MidPosition_percent = EE_ReadBYTE(ADDR_MID_PERCENT);
          if(OpenPosition > ClosePosition)
          {
                MidPosition1 = OpenPosition - MidPosition_percent*distance/100;
          }
          else
          {
                MidPosition1 = OpenPosition + MidPosition_percent*distance/100;
          }
    }
    else
    {
          f_ThirdPos = 0;
    }
}

void clearclucth_set(unsigned char sec,unsigned char delay,unsigned char relay)
{
      ClearDoor_sec = sec;
      cleardoor_delay = delay;
      BackPosition = 1;
      clearclucth_relay = relay;
}
