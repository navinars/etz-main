/* ********************************************************************** *
 *                           DOOYA Company                                *
 * The Tree of the NetWork Design Basic CC1101                            *
 * Compiler : MPLAB IDE V8.66                                             *
 * Crystal  : 32MHZ                                                       *
 * MCU      : PIC24FJ64GA002                                              *
 * FileName : RfTranceiver.h                                              *
 * Author   : Softli                                                      *
 * Address  : NingBo                                                      *
 * Time     : 2012-12-21                                                  *
 * Version  : V1.0                                                        *
 * Testing                                                                *
 * ********************************************************************** */
 
 #ifndef _Rf_Tranceiver_H_
 #define _Rf_Tranceiver_H_
 
 #ifdef _Tranceiver_Global_
      #define Rf_Ext
 #else
      #define Rf_Ext                extern
 #endif
 
 //include header files
 #include "Rfcc1101.h"
#include "int.h"
 
/* ============================================ *
 *                    Defines                   *
 * ============================================ */

#define Hi_Uint8(a)						(((unsigned long)(a) >> 8) & 0xFF)
#define Lo_Uint8(a)						((unsigned long)(a) & 0xFF)
 //clean interrupt flag 
 #define Clean_Interrupt_ISR_Flag      P2IFG &= ~BIT0
 //Up level interrupt 
 #define Enable_UpLevel_Interrupt      //INTCON2bits.INT1EP = 0
 //Down level interrupt 
 #define Enable_DownLevel_Interrupt    //INTCON2bits.INT1EP = 1
 //enable int0 interrupt 
 #define Enable_Interrupt              P2IE  |= BIT0
 //disable int0 interrupt 
 #define Disable_Interrupt             P2IE  &=~BIT0
 //Store and disable interrupt 
 #define StoreAndDisRfInterrupt(x)     P2IE  &=~BIT0
 //restore interrupt 
 #define RestoreRfInterrupt(x)         P2IE  |= BIT0

 //enable CSMA_CA
 #define CSMA_CA
 
 
 //rf cc1101 break down 
 #define CC1101_BreakDown_Status       Zigbee_NetWork_Led_TGL

 //rf c1101 interrupt pin --RP9 
 #define Rf_Interrupt_Pin              9

 //cc1101 routine check counter 
 #define CC1101_ROUTINE_CHECK_COUTER   4
 
 //rf level interrupt 
 #define Rf_Level_Priority             7
 
 //rf cc1101 receive max length of actual data  
 #define MAX_RX_DATA_LEN               62
 
 //Tx buffer size
 #define MAX_TX_DATA_SIZE              62
 
 //rf cc1101 receive max length of all data 
 #define MAX_RX_FRAME_LEN              64
 
 //Rx buffer size
 #define RX_BUFFER_SIZE                20
 
 //PORTB,pin 4       
 #define CS_DDR                        P1DIR&BIT5
 #define CS_PORT                       P1OUT&BIT5
 //PORTB,pin 5  
 #define SI_DDR                        P1DIR&BIT2
 #define SI_PORT                       P1OUT&BIT2
 //PORTB,pin 6
 #define SO_DDR                        P1DIR&BIT1
 #define SO_PORT                       P1OUT&BIT1
 #define SO_PIN                        P1IN&BIT1
 //PORTB,pin 7
 #define SCLK_DDR                      P1DIR&BIT4
 #define SCLK_PORT                     P1OUT&BIT4
 //PORTB,pin 3 ---> RB10 interrupt 
 #define GDO0_DDR                      P2DIR&BIT0
 #define GDO0_PORT                     P2OUT&BIT0
 #define GDO0_PIN                      P2IN&BIT0
 //csma 
 #ifdef  CSMA_CA
    //PORTD,pin2 --->csma 
    #define GDO2_DDR                   P2DIR&BIT1
    #define GDO2_PORT                  P2OUT&BIT1
    #define GDO2_PIN                   P2IN&BIT1
 #endif 
 
 //cs
 #define CS_OUTPUT                     P1DIR |= BIT5
 #define CS_INPUT                      P1DIR &=~BIT5
 //si
 #define SI_OUTPUT                     P1DIR |= BIT2
 #define SI_INPUT                      P1DIR &=~BIT2
 //so
 #define SO_OUTPUT                     P1DIR |= BIT1
 #define SO_INPUT                      P1DIR &=~BIT1
 //sclk
 #define SCLK_OUTPUT                   P1DIR |= BIT4
 #define SCLK_INPUT                    P1DIR &=~BIT4
 //gdo0
 #define GDO0_OUTPUT                   P2DIR |= BIT0
 #define GDO0_INPUT                    P2DIR &=~BIT0
 //csma
 #ifdef  CSMA_CA
    //gdo2
    #define GDO2_OUTPUT                P2DIR |= BIT1
    #define GDO2_INPUT                 P2DIR &=~BIT1
 #endif

 //cs
 #define Enable_CC1101                 P1OUT &=~BIT5
 #define Disable_CC1101                P1OUT |= BIT5
 //si
 #define CC1101_Si_High                P1OUT |= BIT2
 #define CC1101_Si_Low                 P1OUT &=~BIT2
 //so
 #define CC1101_So_High                P1OUT |= BIT1
 #define CC1101_So_Low                 P1OUT &=~BIT1
 #define CC1101_Check_So               (!!(P1IN&BIT1))
 //sclk
 #define CC1101_Sclk_High              P1OUT |= BIT4
 #define CC1101_Sclk_Low               P1OUT &=~BIT4
 //gdo0
 #define CC1101_Gdo0_High              P2OUT |= BIT0
 #define CC1101_Gdo0_Low               P2OUT &=~BIT0
 #define CC1101_Check_Gdo0             (!!(P2IN&BIT0))
 //csma
 #ifdef  CSMA_CA
    //gdo2
    #define CC1101_Gdo2_High           P2OUT |= BIT1
    #define CC1101_Gdo2_Low            P2OUT &=~BIT1
    #define CC1101_Check_Gdo2         (!!(P2IN&BIT1))
 #endif
	 
 //check RF signal level
 #define Check_Rf_Level                CC1101_Check_Gdo0
 
 //check CSMA
 #ifdef CSMA_CA
    #define Check_Csma_Level           CC1101_Check_Gdo2
 #endif
	 
 #if MAX_RX_DATA_LEN != 62 
    #error "CC1101 Rx data length is Error! Please check and modification."
 #endif
 
 #if MAX_TX_DATA_SIZE != 62
    #error "CC1101 Tx buffer is Error! Please Check and modification."
 #endif

 #if MAX_RX_FRAME_LEN != 64 
    #error "CC1101 Rx frame is Error! Please check and modification."
 #endif

 #if RX_BUFFER_SIZE > 2048
    #error "CC1101 Rx buffer is bigger!Please Check and modification."
 #endif

/* =============================================== *
 *                   Typedefs                      *
 * =============================================== */
 //Receive data buffer
 //循环的buffer
 Rf_Ext unsigned char             RxBuf[RX_BUFFER_SIZE];

 #ifdef   _Tranceiver_Global_
    Rf_Ext unsigned char* const   ptrRxBufOver=&RxBuf[RX_BUFFER_SIZE];
 #else
    extern unsigned char*         ptrRxBufOver;
 #endif

 Rf_Ext volatile unsigned char*   ptrRxBufWrite;
 Rf_Ext          unsigned char*   ptrRxBufRead;
 
 //射频模块buf为空，也就是没有接收到数据
 #define  RF_RXBUF_EMPTY          (ptrRxBufRead == ptrRxBufWrite)
 
 //cc1101 reset and initial callback function type 
 typedef void (*RfResetCallBack)(void);
 
 extern unsigned char sys_send;
/* ============================================== *
 *            function declaration                *
 * ============================================== */
 //register cc1101 reset callback function
 void CC1101_ResetCallBackRegister(RfResetCallBack pCallBack);
 
 //write strobe command to cc1100
 void CC1101_Strobe(unsigned char stro);
 
 //write a byte data
 void CC1101_Write_Reg(unsigned char addr,unsigned char value);
 
 //write many register once 
 void CC1101_Write_Burst_Reg(unsigned char addr,unsigned char *buffer,unsigned char count);
 
 //read single register once
 unsigned char CC1101_Read_Reg(unsigned char addr);
 
 //连续读多个积存器
 void CC1101_Read_Burst_Reg(unsigned char count);
 
 //读状态积存器  burst 位应该为 --> 1
 unsigned char CC1101_Read_Status(unsigned char addr);
 
 //config rf cc1100 register
 void CC1101_Rf_Write_Settings(void);
 
 //power up reset
 void CC1101_Power_Up(void);
 
 //rf set power
 void CC1101_Setting_Power(RF_Tx_Power power);

 //rf Select transmit power 
 void CC1101_Select_Transmit_Power_Level(Rf_Transmit_Level level);

 //rf set Channel
 void CC1101_Setting_Channel(RF_Frequency_Channel channel);

 //CC1101 set Synch Head word
 void CC1101_Setting_SynchHead(void);

 //CC1101 set carrier sense threshold
 void CC1101_CarrierSense_Threshold(RF_Threshold threshold);

 //CC1101 set Gpi02
 void CC1101_Config_Gpio2(RF_Gpio gpio);

 //cc1101 set Gpio0
 void CC1101_Config_Gpio0(RF_Gpio gpio);

 //setting cc1101 address
 void CC1101_Setting_Address(unsigned char Addr);

 //CC1101 set Frequency section
 void CC1101_Setting_FreSection(RF_Frequency_Section section);

 //CC1101 entry rx mode 
 void CC1101_Entry_XMode(RF_Mode Mode);
 
 //cc1100 config pin
 void CC1101_Config_Pins(void);

 //CC1101 Interrupt CN Config
 void CC1101_Interrupt_Config(unsigned char priority);

 //rf mac rx buffer initial 
 void CC1101_RxBuffer_Initial(void);
  
 //CC1101 enter into sleep mode
 void CC1101_EnterIntoSleepMode(void);

 //cc1101 wake up 
 void CC1101_WakeUpToIdleMode(void);
 
 //cc1101 initialization
 void CC1101_Initialization(void);
 
 //rf cc1101 write FIFO
 void CC1101_Write_Fifo(unsigned char *txptr,unsigned char size);

 //rf cc1100 send packet
 void CC1101_Send_Packet(void);

 //rf read packet 
 void CC1101_Read_Packet(unsigned char length);

 //rf cc1100 receive packet 
 //status[0] = RSSI, status[1] = LQI
 void CC1101_Receive_Packet(void);

 //check cc1101 rx buffer is free?
 unsigned int CC1101_Check_RxBuffer_Free(void);

 //check RX rx receive data packet ?
 unsigned int CC1101_Check_Receive_Packet(void);

 //rf Erase the Packet of The length
 void CC1101_Erase_Buffer(unsigned int length);

 //Get cc1101 rx data packet
 void CC1101_Get_Rx_Data(unsigned char *Dst,unsigned int length);

 //Get cc1101 current signal strong
 void CC1101_Get_Channel_RSSI(unsigned char *Rssi);

 //Get the curren communicate LQI
 void CC1101_Get_Channel_LQI(unsigned char *Lqi);
 
 //RF cc1101 frequency adjust
 void CC1101_Frequency_Adjust(void);

 //RF cc1101 Routine 
 void CC1101_Routine_Check(void);

 #ifdef __cplusplus
    }
 #endif

 #endif
