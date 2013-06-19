/* ********************************************************************** *
 *                           DOOYA Company                                *
 * The Tree of the NetWork Design Basic CC1101                            *
 * Compiler : MPLAB IDE V8.66                                             *
 * Crystal  : 32MHZ                                                       *
 * MCU      : PIC24FJ64GA002                                              *
 * FileName : RfTranceiver.c                                              *
 * Author   : Softli                                                      *
 * Address  : NingBo                                                      *
 * Time     : 2012-12-21                                                  *
 * Version  : V1.0                                                        *
 * Testing                                                                *
 * ********************************************************************** */
 
#define _Tranceiver_Global_
 
#include "cc1101_spi.h"
#include "RfTranceiver.h"
#include "stdio.h"
 
 // From module: FreeRTOS mini Real-Time Kernel
 #include <FreeRTOS.h>
 #include "task.h"
 #include "status_codes.h"
 
 #define StoreAndDisRfInterrupt(x)
 #define RestoreRfInterrupt(x)
 #define APIReadArrayBytes(x)
 #define Disable_Interrupt
 
 //routine check counter 
 static unsigned char          RoutineCounter = 0;
 //cc1101 reset call back function  
 static RfResetCallBack        pRfResetCallBack = NULL;
 
 unsigned char dat[2] = {0xB1, 0x01};
 unsigned char sys_send = 0;

/* ============================================ *
 *    register cc1101 reset callback function   *
 * ============================================ */
 void CC1101_ResetCallBackRegister(RfResetCallBack pCallBack)
 {
    pRfResetCallBack=pCallBack;
 }
 
/* ============================================ *
 *        write strobe command to cc11001       *
 * ============================================ */
 void CC1101_Strobe(unsigned char stro)
 {
//    unsigned char Rex;
    //save break point
//    StoreAndDisRfInterrupt(Rex);
    //enable stabilize
	Enable_CC1101();
	//wait for cc1101
	while(CC1101_Check_So());
	//write strobe command to register 
	APIWriteByte(stro); 
    //disable cc1101 
	Disable_CC1101();
    //resume break point 
//    RestoreRfInterrupt(Rex);
 }
 
/* ============================================ *
 *            write register to cc1101          *
 * ============================================ */
 void CC1101_Write_Reg(unsigned char addr,unsigned char value)
 {
//    unsigned char Rex;
    //save break point 
    StoreAndDisRfInterrupt(Rex);
    //enable cc1101 
    Enable_CC1101(); 
	//wait for ....
    while(CC1101_Check_So());
	//write address of register 
	APIWriteByte(addr);  
	//write value to register 
	APIWriteByte(value); 
	//disable cc1101 
	Disable_CC1101();
    //resume break point 
    RestoreRfInterrupt(Rex);
 }
   
/* ============================================ *
 *            write many register once          *
 * ============================================ */
 void CC1101_Write_Burst_Reg(unsigned char addr,unsigned char *buffer,unsigned char count)
 {
    unsigned char temp;
    //save break point 
    StoreAndDisRfInterrupt(Rex);
	//write burst set 1
	temp=addr|WRITE_BURST;
	//enable cc1101 
	Enable_CC1101();
	//wait for....
	while(CC1101_Check_So());
	//write address
	APIWriteByte(temp);
	//write data bytes
    APIWriteArrayBytes(buffer,count);
    //disable cc1101 
	Disable_CC1101();
    //resume break point 
    RestoreRfInterrupt(Rex);
 }
 
/* ============================================ * 
 *           read single register once          * 
 * ============================================ */
 unsigned char CC1101_Read_Reg(unsigned char addr) 
 {
	unsigned char value,temp;
//    unsigned char Rex;
    //save break point 
    StoreAndDisRfInterrupt(Rex);
    //re-build address
	temp=addr|READ_SINGLE; 
	//enable cc1101
	Enable_CC1101();
	//wait for...
	while(CC1101_Check_So());
	//write address
	APIWriteByte(temp);
	//read data byte
	value=APIReadByte();
	//disable cc1101 
	Disable_CC1101();
    //resume break point 
    RestoreRfInterrupt(Rex);
	return value;
 }

/* ============================================ *
 *           read read register more once       *
 * ============================================ */
 void CC1101_Read_Burst_Reg(unsigned char count)
 {  
    unsigned char temp;
    StoreAndDisRfInterrupt(Rex);
    //re-build net address
	temp=cc1101_RXFIFO|READ_BURST;
	//enable cc1101 
	Enable_CC1101();
	//wait for ...
	while(CC1101_Check_So());
	//write address
	APIWriteByte(temp);
	//从CC1101 RX FIFO 中读取数据
	APIReadArrayBytes(count);
    //disable cc1101 
	Disable_CC1101();
    //resume break point 
    RestoreRfInterrupt(Rex);
 }
 
/* ============================================ *
 *     读状态积存器  burst 位应该为 --> 1      *
 * ============================================ */
 unsigned char CC1101_Read_Status(unsigned char addr) 
 {
   	unsigned char value,temp;
//    unsigned char Rex;
    StoreAndDisRfInterrupt(Rex);
    //re-build new address
	temp=addr|READ_BURST;
	//enable cc1101 
	Enable_CC1101();
	//wait for ...
	while(CC1101_Check_So());
	//write address...
	APIWriteByte(temp);
	//read data byte 
	value=APIReadByte();
	//disable cc1101 
	Disable_CC1101();
    //resume break point 
    RestoreRfInterrupt(Rex);
    //return read data 
	return value;
 }

/* ============================================ *
 *           CC1101 Setting Parameter           *
 * ============================================ */
 void CC1101_Rf_Write_Settings(void)
 {
	 uint8_t tmp;
    //CC1100 FSCTRL
	CC1101_Write_Reg(cc1101_FSCTRL0,FSCTRL2);
    CC1101_Write_Reg(cc1101_FSCTRL1,FSCTRL1);
    tmp = CC1101_Read_Reg(cc1101_FSCTRL1);
	if(tmp == 0x00)
	{
		tmp = 0;
	}
	CC1101_Write_Reg(cc1101_FSCTRL0,FSCTRL0);
	//MDMCFG
    CC1101_Write_Reg(cc1101_MDMCFG4,MDMCFG4);
	CC1101_Write_Reg(cc1101_MDMCFG3,MDMCFG3);
	CC1101_Write_Reg(cc1101_MDMCFG2,MDMCFG2);
	CC1101_Write_Reg(cc1101_MDMCFG1,MDMCFG1);
	CC1101_Write_Reg(cc1101_MDMCFG0,MDMCFG0);
	CC1101_Write_Reg(cc1101_FIFOTHR,FIFOTHR);
	//DEVIATN 
	CC1101_Write_Reg(cc1101_DEVIATN,DEVIATN);
	//FREND
	CC1101_Write_Reg(cc1101_FREND1,FREND1);
	CC1101_Write_Reg(cc1101_FREND0,FREND0);
    CC1101_Write_Reg(cc1101_MCSM1,MCSM1);
	//MCSM0
	CC1101_Write_Reg(cc1101_MCSM0,MCSM0);
	//FOCCFG
	CC1101_Write_Reg(cc1101_FOCCFG,FOCCFG);
	//BSCFG
	CC1101_Write_Reg(cc1101_BSCFG,BSCFG);
	//FSCAL
	CC1101_Write_Reg(cc1101_FSCAL3,FSCAL3);
	CC1101_Write_Reg(cc1101_FSCAL2,FSCAL2);
	CC1101_Write_Reg(cc1101_FSCAL1,FSCAL1);
	CC1101_Write_Reg(cc1101_FSCAL0,FSCAL0);
	///FSTEST TEST2 1 0
	CC1101_Write_Reg(cc1101_FSTEST,FSTEST);
	CC1101_Write_Reg(cc1101_TEST2,TEST2);
	CC1101_Write_Reg(cc1101_TEST1,TEST1);
	CC1101_Write_Reg(cc1101_TEST0,TEST0);
	//PKTCTRL 
	CC1101_Write_Reg(cc1101_PKTCTRL1,PKTCTRL1);
	CC1101_Write_Reg(cc1101_PKTCTRL0,PKTCTRL0);
	CC1101_Write_Reg(cc1101_PKTLEN,PKTLEN);
 }

void _delay_us(unsigned char x)
{
	unsigned long i;
	
	while(x --)
	{
		for(i = 0;i < 10000;i++)
		{
			asm("NOP");
		}
	}
}

/* ============================================ *
 *                power up reset                *
 * ============================================ */
 void CC1101_Power_Up(void) 
 {
	//enable cc1101
	Enable_CC1101();
    _delay_us(10);
    //disable cc1101
	Disable_CC1101();
	//delay 40 us
	_delay_us(40);
	//enable cc1101
	Enable_CC1101();
	//wait cc1101 stabilize
	while(CC1101_Check_So());										// SOMI is low...
	//transmit cc1101 command
	APIWriteByte(cc1101_SRES);
	//wait
	while(CC1101_Check_So());
	//disable cc1101
	Disable_CC1101();
 }
   
/* ============================================ *
 *                  rf set power                *
 * ============================================ */
 void CC1101_Setting_Power(RF_Tx_Power power)
 {
    unsigned char i,temp;
    //setting rf cc100 power address
	temp = cc1101_PATABLE|WRITE_BURST;
	Enable_CC1101();
	while(CC1101_Check_So());
	APIWriteByte(temp);
	//write data 8 times 
	for(i=0;i<8;i++)
	{
		APIWriteByte(power);
	}
	Disable_CC1101();
 }
 
/* ============================================ *
 *         rf Select transmit power             *
 * ============================================ */
 void CC1101_Select_Transmit_Power_Level(Rf_Transmit_Level level)
 {
    switch(level)
    {
        //max level
        case Rf_Transmit_Level9 :
        {
            CC1101_Setting_Power(RF_TxPower_12dbm);
        }break;
        //level -8
        case Rf_Transmit_Level8 :
        { 
            CC1101_Setting_Power(RF_TxPower_10dbm);
        }break;
        //level -7
        case Rf_Transmit_Level7 : 
        {
            CC1101_Setting_Power(RF_TxPower_7dbm);
        }break;
        //level -6
        case Rf_Transmit_Level6 : 
        {
            CC1101_Setting_Power(RF_TxPower_5dbm);
        }break;
        //level -5
        case Rf_Transmit_Level5 : 
        {
            CC1101_Setting_Power(RF_TxPower_0dbm);
        }break;
        //level -4
        case Rf_Transmit_Level4 : 
        {
            CC1101_Setting_Power(RF_TxPower_N6dbm);
        }break;
        //level -3
        case Rf_Transmit_Level3 :  
        {
            CC1101_Setting_Power(RF_TxPower_N10dbm);
        }break;
        //level -2
        case Rf_Transmit_Level2 : 
        {
            CC1101_Setting_Power(RF_TxPower_N15dbm);
        }break;
        //level -1
        case Rf_Transmit_Level1 : 
        {
            CC1101_Setting_Power(RF_TxPower_N20dbm);
        }break;
        //level -0
        case Rf_Transmit_Level0 : 
        {
            CC1101_Setting_Power(RF_TxPower_N30dbm);
        }break;
        //default 0dbm 
        default :
        {
            CC1101_Setting_Power(RF_TxPower_0dbm);
        }break;
    }
 }

/* ============================================== *
 *               CC1101 set channel               *
 * ============================================== */
 void CC1101_Setting_Channel(RF_Frequency_Channel channel)
 {
    //setting channel 
	CC1101_Write_Reg(cc1101_CHANNR,channel);
 }
 
/* ============================================== *
 *           CC1101 set Synch Head word           *
 * ============================================== */
 void CC1101_Setting_SynchHead(void)
 {
 	//SYNCH
	CC1101_Write_Reg(cc1101_SYNC1,Hi_Uint8(Rf_Synch_Code));
	CC1101_Write_Reg(cc1101_SYNC0,Lo_Uint8(Rf_Synch_Code));
 }

/* ============================================== *
 *       CC1101 set carrier sense threshold       *
 * ============================================== */
 void CC1101_CarrierSense_Threshold(RF_Threshold threshold)
 {
    switch(threshold)
    {
        //-80dbm
        case RF_Threshold_80dbm :
        {
	        CC1101_Write_Reg(cc1101_AGCCTRL2,0x0e);
        }break;
        //-78dbm
        case RF_Threshold_78dbm :
        {
	        CC1101_Write_Reg(cc1101_AGCCTRL2,0x15);
        }break;
        //-75dbm 
        case RF_Threshold_75dbm :
        {
	        CC1101_Write_Reg(cc1101_AGCCTRL2,0x17);
        }break;
        //-72dbm 
        case RF_Threshold_72dbm :
        {
	        CC1101_Write_Reg(cc1101_AGCCTRL2,0x1f);
        }break;
        //-68dbm 
        case RF_Threshold_68dbm :
        {
	        CC1101_Write_Reg(cc1101_AGCCTRL2,0x2f);
        }break;
        //otherwise way -72dbm 
        default :
        {
	        CC1101_Write_Reg(cc1101_AGCCTRL2,0x1f);
        }break;
    }
    CC1101_Write_Reg(cc1101_AGCCTRL1,AGCCTRL1);
    CC1101_Write_Reg(cc1101_AGCCTRL0,AGCCTRL0);
 }

/* ============================================== *
 *                 CC1101 set Gpio2               *
 * ============================================== */
 void CC1101_Config_Gpio2(RF_Gpio gpio)
 {
	//IOCFG
    CC1101_Write_Reg(cc1101_IOCFG2,gpio);
 }

/* ============================================== *
 *                 CC1101 set Gpio0               *
 * ============================================== */
 void CC1101_Config_Gpio0(RF_Gpio gpio)
 {
	//IOCFG
    CC1101_Write_Reg(cc1101_IOCFG0,gpio);
 }

/* ============================================== *
 *            setting cc1101 address              *
 * ============================================== */
 void CC1101_Setting_Address(unsigned char Addr)
 {
    CC1101_Write_Reg(cc1101_ADDR,Addr);
 }

/* ============================================== *
 *         CC1101 set Frequency section           *
 * ============================================== */
 void CC1101_Setting_FreSection(RF_Frequency_Section section)
 {
     switch(section)
     {
         //ism 315MHz
         case RF_ISM_315MHz :
         {
	        CC1101_Write_Reg(cc1101_FREQ2,0x0c);
 	        CC1101_Write_Reg(cc1101_FREQ1,0x1d);
	        CC1101_Write_Reg(cc1101_FREQ0,0x89);
         }break;
         //ISM 433MHz 
         case RF_ISM_433MHz :
         {
	        CC1101_Write_Reg(cc1101_FREQ2,0x10);
 	        CC1101_Write_Reg(cc1101_FREQ1,0xa7);
	        CC1101_Write_Reg(cc1101_FREQ0,0x62); 
         }break;
         //ISM 868MHz
         case RF_ISM_868MHz :
	     {
            //CC1101_Write_Reg(cc1101_FREQ2,0x21);
 	        //CC1101_Write_Reg(cc1101_FREQ1,0x62);
	        //CC1101_Write_Reg(cc1101_FREQ0,0x76);
            CC1101_Write_Reg(cc1101_FREQ2,0x21);
 	        CC1101_Write_Reg(cc1101_FREQ1,0x13);
	        CC1101_Write_Reg(cc1101_FREQ0,0xb1);
         }break;
         //ISM 915MHz
         case RF_ISM_915MHz :
         {
	        CC1101_Write_Reg(cc1101_FREQ2,0x23);
 	        CC1101_Write_Reg(cc1101_FREQ1,0x31);
	        CC1101_Write_Reg(cc1101_FREQ0,0x3b);
         }break;
         //otherwise is ISM 433MHz
         default :
         {
	        CC1101_Write_Reg(cc1101_FREQ2,0x10);
 	        CC1101_Write_Reg(cc1101_FREQ1,0xa7);
	        CC1101_Write_Reg(cc1101_FREQ0,0x62);
         }break;
     }
 }

/* ============================================== *
 *               CC1101 entry x mode              *
 * ============================================== */
 void CC1101_Entry_XMode(RF_Mode Mode)
 {
    //idle mode 
    CC1101_Strobe(cc1101_SIDLE);
    switch(Mode)
    {
        //rf rx mode
        case Rf_Rx_Mode : 
        {
            //CC1100 回到接收模式 
            CC1101_Strobe(cc1101_SRX);
        }break;
        //rf tx mode
        case Rf_Tx_Mode :  
        {
            //进入发送模式发送数据
	        CC1101_Strobe(cc1101_STX);
        }break;
        //rf idle mode
        case Rf_Idle_Mode :
        {
            
        }break;
        //rf WOR mode
        case Rf_Wor_Mode :
        {
            CC1101_Strobe(cc1101_SWOR);
        }break;
        //rf power down mode
        case Rf_Pwd_Mode :
        {
            CC1101_Strobe(cc1101_SPWD);
        }break;
        //rf frequency scal 
        case Rf_Frq_Scal :
        {
            //开启和校准频率合成器....
	        CC1101_Strobe(cc1101_SCAL); 
        }break;
        //flush rx fifo
        case Rf_Flush_RxFifo :
        {
            CC1101_Strobe(cc1101_SFRX); 
        }break;
        //flush tx fifo
        case Rf_Flush_TxFfio :
        {
            CC1101_Strobe(cc1101_SFTX);
        }break;
        //entry rx mode and flush rx fifo
        case Rf_Rx_Flush_RxFifo :
        {
            //清空接收缓冲区
            CC1101_Strobe(cc1101_SFRX);
            //CC1100 回到接收模式
            CC1101_Strobe(cc1101_SRX);
        }break;
        //otherwise none
        default :
         break;
    }                 
 }
 
 /* ============================================== *
  *            CC1101 Initialization               *
  * ============================================== */
void CC1101_Config_Pins(void)
{
	
}

/* ============================================== *
 *          CC1101 Interrupt  Config              *
 * ============================================== */
void CC1101_Interrupt_Config(unsigned char priority)
{
	configure_cc1101_int();
}
 
/* ============================================== *
 *            rf mac rx buffer initial            *
 * ============================================== */
 void CC1101_RxBuffer_Initial(void)
 {
    ptrRxBufWrite = &RxBuf[0];
 	ptrRxBufRead  = &RxBuf[0];
 }
 
/* ============================================== *
 *          CC1101 enter into sleep mode          *
 * ============================================== */
 void CC1101_EnterIntoSleepMode(void)
 {
    //cc1101 power down 
    CC1101_Entry_XMode(Rf_Pwd_Mode);
 }

/* ============================================== *
 *          CC1101 wake up to idle mode           *
 * ============================================== */
 void CC1101_WakeUpToIdleMode(void)
 {
    //wake up cc1101
    Enable_CC1101();
    //delay 100us 
    _delay_us(100);
	Disable_CC1101();
    //rf frequency scal 
    CC1101_Entry_XMode(Rf_Frq_Scal);
 }

 /* ============================================== *
  *            CC1101 Initialization               *
  * ============================================== */
 void CC1101_Initialization(void)
 {
    //Confing CC1101 Pins
	CC1101_Config_Pins();
    //spi initial
//	APISpiModuleInitial();
    //disable rf interrupt
    Disable_Interrupt;
	//power un and reset
	CC1101_Power_Up();
	//cc1100 setting config register
	CC1101_Rf_Write_Settings();
    //setting cc1101 synch head word 
    CC1101_Setting_SynchHead();
    //config gpio function
    CC1101_Config_Gpio2(IOCFG2);
    CC1101_Config_Gpio0(IOCFG0);
	//check CC1101 initial whether success.....
	if(CC1101_Read_Reg(cc1101_IOCFG0) != IOCFG0)
	{
	    for(;;)
		{
			CC1101_Config_Gpio0(IOCFG0);
		    vTaskDelay(2);
		}
	}
	
	CC1101_Select_Transmit_Power_Level(Rf_Transmit_Level5);
	CC1101_Setting_Channel(RF_Frequency_Channel10);
	CC1101_CarrierSense_Threshold(RF_Threshold_72dbm);
	CC1101_Setting_Address(0x01);
	CC1101_Setting_FreSection(RF_ISM_915MHz);
//	CC1101_Entry_XMode(Rf_Rx_Mode);
	
	
    //wish cc1101 rx fifo ...
    CC1101_Entry_XMode(Rf_Flush_RxFifo);
    //wish cc1101 tx fifo ...
    CC1101_Entry_XMode(Rf_Flush_TxFfio);
	
    //config ... 
    CC1101_Interrupt_Config(Rf_Level_Priority);
	
	CC1101_Entry_XMode(Rf_Rx_Mode);
 }
 
/* ============================================ *
 *              rf cc1101 write FIFO            *
 * ============================================ */
 void CC1101_Write_Fifo(unsigned char *txptr,unsigned char size)
 {
//    unsigned char Rex;
    StoreAndDisRfInterrupt(Rex);
    //length
	CC1101_Write_Reg(cc1101_TXFIFO,size);
    //write data buffer 
	CC1101_Write_Burst_Reg(cc1101_TXFIFO,txptr,size);
    RestoreRfInterrupt(Rex);
 }
 
/* ============================================ *
 *              rf cc1101 send packet           *
 * ============================================ */
 void CC1101_Send_Packet(void)
 {	
//    unsigned char Rex;
    //disable rf interrupt
    StoreAndDisRfInterrupt(Rex);
    //rx mode after tx
    CC1101_Entry_XMode(Rf_Tx_Mode);
	// Wait for GDO0 to be set -> sync transmitted  
	while(!Check_Rf_Level)
    {
	   asm("nop");
    }
	// Wait for GDO0 to be cleared -> end of packet  
	while(Check_Rf_Level)
    {
	   asm("nop");
    }
//	_delay_us(100);
    //wish cc1101 tx fifo
    CC1101_Entry_XMode(Rf_Flush_TxFfio);
    //rx mode after tx 
    CC1101_Entry_XMode(Rf_Rx_Mode);
    //enable rf rx interrupt
//	Clean_Interrupt_ISR_Flag;
    RestoreRfInterrupt(Rex);
 }
 
/* ======================================= * 
 *     check cc1101 rx buffer is free?     * 
 * ======================================= */
 void CC1101_Read_Packet(unsigned char length)
 {
    unsigned int remain;
    //check rx buffer wheterh free .....
    remain = CC1101_Check_RxBuffer_Free();
    //add status bytes
    length += RfFcsBytes;
    //check rx buffer space wheterh enough...
    if(remain < length)
	{
         return;
    }
    //write length of data packet 
    *ptrRxBufWrite++ =  length;
    if(ptrRxBufWrite == ptrRxBufOver)
    {
        ptrRxBufWrite = &RxBuf[0];
    }
    //read cc1101 FIFO to RXbuffer 
    CC1101_Read_Burst_Reg(length);
 }
 
/* ============================================ *
 *             rf cc1100 receive packet         *
 * status[0] = RSSI-->6:2, status[1] = LQI      *
 * ============================================ */
 void CC1101_Receive_Packet(void)
 {
	//check CRC
    if(CC1101_Read_Status(cc1101_LQI) & cc1101_CRC_OK)
	{
	    unsigned char length;
        //get length of data packet
		length=CC1101_Read_Reg(cc1101_RXFIFO);
		
		if((length > 0)&&(length <= MAX_RX_DATA_LEN))
		{	
			//get data packet
		    CC1101_Read_Packet(length);
	    }
	}
    //CC1100 回到接收模式
    CC1101_Entry_XMode(Rf_Rx_Flush_RxFifo); 	
 }

/* ======================================= *
 *     check cc1101 rx buffer is free?     *
 * ======================================= */
 unsigned int CC1101_Check_RxBuffer_Free(void)
 {  
//    unsigned char  Rex;
    unsigned int   remain;
    //disable rf interrupt
    StoreAndDisRfInterrupt(Rex);
    
	// Check cc1101 rx buffer free
    if(ptrRxBufWrite < ptrRxBufRead)
	{
        remain = ptrRxBufRead - ptrRxBufWrite - 1;
    }
    else
	{
        remain = RX_BUFFER_SIZE - (ptrRxBufWrite - ptrRxBufRead) - 1;
	}
    
    //enable rf rx interrupt 
    RestoreRfInterrupt(Rex);
    
	return remain;
 }

/* ======================================= *
 *    check RX rx receive data packet ?    *
 * ======================================= */
 unsigned int CC1101_Check_Receive_Packet(void)
 {
 //   unsigned char  Rex;
    unsigned int   length;
    //disable rf interrupt
    StoreAndDisRfInterrupt(Rex);
    
	// Check Serial whether to receive data
    if(ptrRxBufWrite < ptrRxBufRead)
    {
        length = RX_BUFFER_SIZE - (ptrRxBufRead - ptrRxBufWrite);
    }
    else
	{
        length = ptrRxBufWrite - ptrRxBufRead; 
    }
    //enable rf rx interrupt 
    RestoreRfInterrupt(Rex);
	return length;
 }
 
/* ============================================ *
 *       rf Erase the Packet of The length      *
 * ============================================ */
 void CC1101_Erase_Buffer(unsigned int length)
 {
//	unsigned char  Rex;
    unsigned int   used;
    //disable rf interrupt
    StoreAndDisRfInterrupt(Rex);
    //需要擦除的大小必须小于等于写进去的长度
    if(ptrRxBufWrite < ptrRxBufRead)
    {
        used = RX_BUFFER_SIZE - (ptrRxBufRead - ptrRxBufWrite);
    }
    else
    {
        used = ptrRxBufWrite - ptrRxBufRead;
    }
    length = (length > used)?used:length;
    //erase .....
    ptrRxBufRead=((ptrRxBufRead+length)<ptrRxBufOver)?\
	              (ptrRxBufRead+length):(ptrRxBufRead-(RX_BUFFER_SIZE-length));
	//enable rf rx interrupt 
    RestoreRfInterrupt(Rex);
 }

/* ============================================ *
 *           Get cc1101 rx data packet          *
 * ============================================ */
 void CC1101_Get_Rx_Data(unsigned char *Dst,unsigned int length)
 {
    unsigned char  *pDst=Dst;
    unsigned int   i;
    for(i=0;i<length;i++)
    {
        *pDst++ = *ptrRxBufRead++;
        if(ptrRxBufRead == ptrRxBufOver)
        {
           ptrRxBufRead=&RxBuf[0];
        }
    }
 }
 
/* ============================================ *
 *        Get cc1101 current signal strong      *
 * ============================================ */
 void CC1101_Get_Channel_RSSI(unsigned char *Rssi)
 {
    *Rssi = CC1101_Read_Status(cc1101_RSSI);
 }
 
/* ============================================ *
 *         Get cc1101 current signal LQI        *
 * ============================================ */
 void CC1101_Get_Channel_LQI(unsigned char *Lqi)
 {
    *Lqi = CC1101_Read_Status(cc1101_LQI)&cc1101_CRC_OK;
 }

/* ============================================ *
 *          RF cc1101 frequency adjust          *
 * ============================================ */ 
 void CC1101_Frequency_Adjust(void)
 {
    //rf frequency scal 
    CC1101_Entry_XMode(Rf_Frq_Scal);
    //rx mode after tx 
    CC1101_Entry_XMode(Rf_Rx_Mode);
 }
 
/* ============================================ *
 *               RF cc1101 Routine              *
 * ============================================ */
 void CC1101_Routine_Check(void)
 {
    RoutineCounter += 1;
    if(RoutineCounter < CC1101_ROUTINE_CHECK_COUTER)
    {
//        unsigned char   Rex;
        unsigned char   status;
        //disable rf interrupt
        StoreAndDisRfInterrupt(Rex);
        //enable cc1101
	    Enable_CC1101();
        //wait for ....
	    while(CC1101_Check_So());
        //get cc1101 status
        status = APIReadByte();
	    //disable cc1101
	    Disable_CC1101();

        //检查发送是否溢出
	    if(CHECK_TXFIFO(status) == TX_OVERFLOW)
	    {
	        //清洗发送缓冲区
	        CC1101_Strobe(cc1101_SFTX);  
        }
	    if((CHECK_RXFIFO(status) == RX_OVERFLOW))
  	    {
	        //清空接收缓冲区
	        CC1101_Strobe(cc1101_SFRX); 
   	    }
 
        //RF cc1101 frequency adjust
        CC1101_Frequency_Adjust();

        //enable rf rx interrupt
        RestoreRfInterrupt(Rex);
        
    }
    else
    {
        RoutineCounter = 0;
	    if(pRfResetCallBack != NULL)
        {
           pRfResetCallBack();
        }
    }    
 }
