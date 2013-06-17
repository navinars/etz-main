/* ********************************************************************** *
 *                           DOOYA Company                                *
 * The Tree of the NetWork Design Basic CC1101                            *
 * Compiler : MPLAB IDE V8.66                                             *
 * Crystal  : 32MHZ                                                       *
 * MCU      : PIC24FJ64GA002                                              *
 * FileName : Rfcc1101.h                                                  *
 * Author   : Softli                                                      *
 * Address  : NingBo                                                      *
 * Time     : 2012-12-21                                                  *
 * Version  : V1.0                                                        *
 * Testing                                                                *
 * ********************************************************************** */
 
 #ifndef _Rf_ISMx_CC1101_H_
 #define _Rf_ISMx_CC1101_H_
 
 #ifdef __cplusplus
    extern "C" {
 #endif
 
  //RX FIFO 溢出
 #define RX_OVERFLOW                  0x60
 //如果RXFIFO 溢出 值为真 
 #define CHECK_RXFIFO(S)              ((S)&RX_OVERFLOW)
 //TX FIDO 溢出
 #define TX_OVERFLOW                  0x70
 //如果TXFIFO 溢出 值为真
 #define CHECK_TXFIFO(S)              ((S)&TX_OVERFLOW)
 //cc1101 rx mode 
 #define cc1101_RxMode                0x10
 #define CHECK_RXMODE(S)              ((S)&cc1101_RxMode)
 //pa table address
 #define cc1101_PATABLE               0x3E
 //cc1100 tx buffer write many bytes command
 #define cc1101_TXFIFO                0x3F
 
 //write a byte only
 #define WRITE_SINGLE                 0x00
 //write many bytes 
 #define WRITE_BURST                  0x40
 //read a byte only
 #define READ_SINGLE                  0x80
 //read many bytes
 #define READ_BURST                   0xC0
 
 //cc1100 rx buffer read many bytes command
 #define cc1101_RXFIFO                0x3F
 //判断接收 接收缓冲区的有效字节数 
 #define BYTES_IN_RXFIFO              0x7F
 //check cc1100 ok
 #define cc1101_CRC_OK                0x80

 //rf fcs information rssi and lqi 
 #define RfFcsBytes                   2
 
 //synch code word
 #define Rf_Synch_Code                0xc526

 //rf cc1101 gpio function 
 typedef enum _RF_CC1101_Gpio_
 {
     SignalCheck                      =0x06,
     CleanChannelAssessment           =0x09,
     CarrierSense                     =0x0e,
     HardWareToZero                   =0x2f
 }RF_Gpio;                             

 //carrier sense threshold--minus value 
 typedef enum _RF_Carrier_Threshold_
 {
    RF_Threshold_80dbm                =0,
    RF_Threshold_78dbm                  ,
    RF_Threshold_75dbm                  ,
    RF_Threshold_72dbm                  ,
    RF_Threshold_68dbm          
 }RF_Threshold;

 //rf mode
 typedef enum _RF_CC1101_Mode_
 {
    Rf_Rx_Mode                        =0,
    Rf_Tx_Mode                          ,
    Rf_Idle_Mode                        ,
    Rf_Wor_Mode                         ,
    Rf_Pwd_Mode                         ,
    Rf_Frq_Scal                         ,
    Rf_Flush_RxFifo                     ,
    Rf_Flush_TxFfio                     ,
    Rf_Rx_Flush_RxFifo                  
 }RF_Mode;

 //rf transmit power level 
 typedef enum _Rf_Transmit_Level_
 {
    Rf_Transmit_Level0                =0,
    Rf_Transmit_Level1                  ,
    Rf_Transmit_Level2                  ,
    Rf_Transmit_Level3                  ,
    Rf_Transmit_Level4                  ,
    Rf_Transmit_Level5                  ,
    Rf_Transmit_Level6                  ,
    Rf_Transmit_Level7                  ,
    Rf_Transmit_Level8                  ,
    Rf_Transmit_Level9                  ,
    Rf_Transmit_Level_Num            =10
 }Rf_Transmit_Level;

 //cc1101 channel
 typedef enum _RF_Frequency_Channel_
 {
    RF_Frequency_Channel0             = 0,
    RF_Frequency_Channel1             = 1,
    RF_Frequency_Channel2             = 2,
    RF_Frequency_Channel3             = 3,
    RF_Frequency_Channel4             = 4,
    RF_Frequency_Channel5             = 5,
    RF_Frequency_Channel6             = 6,
    RF_Frequency_Channel7             = 7,
    RF_Frequency_Channel8             = 8,
    RF_Frequency_Channel9             = 9,
    RF_Frequency_Channel10            = 10, 
    RF_Frequency_Channel11            = 11,
    RF_Frequency_Channel12            = 12,
    RF_Frequency_Channel13            = 13,
    RF_Frequency_Channel14            = 14,
    RF_Frequency_Channel15            = 15,
    Rf_Frequency_Channel_MAX          = 16
 }RF_Frequency_Channel;

 //cc1101 Frequency section 
 typedef enum _RF_Frequency_Section_
 {
    RF_ISM_315MHz                     = 0,
    RF_ISM_433MHz                        ,
    RF_ISM_868MHz                        ,
    RF_ISM_915MHz    
 }RF_Frequency_Section;

 //cc1101 tx power enum 
 typedef enum _RF_Tx_Power_
 {
    RF_TxPower_12dbm                  = 0xc0,
    RF_TxPower_10dbm                  = 0xc5,
    RF_TxPower_7dbm                   = 0xcd,
    RF_TxPower_5dbm                   = 0x86,
    RF_TxPower_0dbm                   = 0x50,
    RF_TxPower_N6dbm                  = 0x37,
    RF_TxPower_N10dbm                 = 0x26,
    RF_TxPower_N15dbm                 = 0x1d,
    RF_TxPower_N20dbm                 = 0x17,
    RF_TxPower_N30dbm                 = 0x03
 }RF_Tx_Power;
 
/* ============================================ *
 *                    Defines                   * 
 * ============================================ */
 #define cc1101_IOCFG2                0x00
 //GDO2 output pin configuration
 #define cc1101_IOCFG1                0x01
 //GDO1 output pin configuration
 #define cc1101_IOCFG0                0x02        
 //GDO0 output pin configuration
 #define cc1101_FIFOTHR               0x03       
 //RX FIFO and TX FIFO thresholds
 #define cc1101_SYNC1                 0x04        
 //Sync word, high byte
 #define cc1101_SYNC0                 0x05       
 //Sync word, low byte
 #define cc1101_PKTLEN                0x06        
 //Packet length
 #define cc1101_PKTCTRL1              0x07        
 //Packet automation control
 #define cc1101_PKTCTRL0              0x08        
 //Packet automation control
 #define cc1101_ADDR                  0x09        
 //Device address
 #define cc1101_CHANNR                0x0A        
 //Channel number
 #define cc1101_FSCTRL1               0x0B       
 //Frequency synthesizer control
 #define cc1101_FSCTRL0               0x0C        
 //Frequency synthesizer control
 #define cc1101_FREQ2                 0x0D        
 //Frequency control word, high byte
 #define cc1101_FREQ1                 0x0E        
 //Frequency control word, middle byte
 #define cc1101_FREQ0                 0x0F        
 //Frequency control word, low byte
 #define cc1101_MDMCFG4               0x10        
 //Modem configuration
 #define cc1101_MDMCFG3               0x11        
 //Modem configuration
 #define cc1101_MDMCFG2               0x12       
 //Modem configuration
 #define cc1101_MDMCFG1               0x13        
 //Modem configuration
 #define cc1101_MDMCFG0               0x14        
 //Modem configuration
 #define cc1101_DEVIATN               0x15        
 //Modem deviation setting
 #define cc1101_MCSM2                 0x16        
 //Main Radio Control State Machine configuration
 #define cc1101_MCSM1                 0x17        
 //Main Radio Control State Machine configuration
 #define cc1101_MCSM0                 0x18        
 //Main Radio Control State Machine configuration
 #define cc1101_FOCCFG                0x19       
 //Frequency Offset Compensation configuration
 #define cc1101_BSCFG                 0x1A        
 //Bit Synchronization configuration
 #define cc1101_AGCCTRL2              0x1B        
 //AGC control
 #define cc1101_AGCCTRL1              0x1C        
 //AGC control
 #define cc1101_AGCCTRL0              0x1D        
 //AGC control
 #define cc1101_WOREVT1               0x1E        
 //High byte Event 0 timeout
 #define cc1101_WOREVT0               0x1F        
 //Low byte Event 0 timeout
 #define cc1101_WORCTRL               0x20        
 //Wake On Radio control         
 #define cc1101_FREND1                0x21        
 //Front end RX configuration
 #define cc1101_FREND0                0x22        
 //Front end TX configuration
 #define cc1101_FSCAL3                0x23       
 //Frequency synthesizer calibration
 #define cc1101_FSCAL2                0x24        
 //Frequency synthesizer calibration
 #define cc1101_FSCAL1                0x25        
 //Frequency synthesizer calibration
 #define cc1101_FSCAL0                0x26        
 //Frequency synthesizer calibration
 #define cc1101_RCCTRL1               0x27        
 //RC oscillator configuration
 #define cc1101_RCCTRL0               0x28        
 //RC oscillator configuration
 #define cc1101_FSTEST                0x29        
 //Frequency synthesizer calibration control
 #define cc1101_PTEST                 0x2A        
 //Production test
 #define cc1101_AGCTEST               0x2B        
 //AGC test
 #define cc1101_TEST2                 0x2C        
 //Various test settings
 #define cc1101_TEST1                 0x2D        
 //Various test settings
 #define cc1101_TEST0                 0x2E        
 //Various test settings


 //Strobe commands
 #define cc1101_SRES                  0x30        
 //Reset chip.
 #define cc1101_SFSTXON               0x31        
 //Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
 //If in RX/TX: Go to a wait state where only the synthesizer is
 //running (for quick RX / TX turnaround).
 #define cc1101_SXOFF                 0x32        
 //Turn off crystal oscillator.
 #define cc1101_SCAL                  0x33        
 //Calibrate frequency synthesizer and turn it off
 //(enables quick start).
 #define cc1101_SRX                   0x34       
 //Enable RX. Perform calibration first if coming from IDLE and
 //MCSM0.FS_AUTOCAL=1.
 #define cc1101_STX                   0x35        
 //In IDLE state: Enable TX. Perform calibration first if
 //MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
 //Only go to TX if channel is clear.
 #define cc1101_SIDLE                 0x36        
 //Exit RX / TX, turn off frequency synthesizer and exit
 //Wake-On-Radio mode if applicable.
 #define cc1101_SAFC                  0x37        
 //Perform AFC adjustment of the frequency synthesizer
 #define cc1101_SWOR                  0x38        
 //Start automatic RX polling sequence (Wake-on-Radio)
 #define cc1101_SPWD                  0x39        
 //Enter power down mode when CSn goes high.
 #define cc1101_SFRX                  0x3A        
 //Flush the RX FIFO buffer.
 #define cc1101_SFTX                  0x3B        
 //Flush the TX FIFO buffer.
 #define cc1101_SWORRST               0x3C        
 //Reset real time clock.
 #define cc1101_SNOP                  0x3D     
 //No operation. May be used to pad strobe commands to two
 //bytes for simpler software. 
	
 //cc1101 status register 
 #define cc1101_PARTNUM               0x30
 #define cc1101_VERSION               0x31
 #define cc1101_FREQEST               0x32
 #define cc1101_LQI                   0x33
 #define cc1101_RSSI                  0x34
 #define cc1101_MARCSTATE             0x35
 #define cc1101_WORTIME1              0x36
 #define cc1101_WORTIME0              0x37
 #define cc1101_PKTSTATUS             0x38
 #define cc1101_VCO_VC_DAC            0x39
 #define cc1101_TXBYTES               0x3A
 #define cc1101_RXBYTES               0x3B
 
 /* =============CC1101 Config Parameter =============== */
 //ism 433mhz 250kbps 
 #define FSCTRL2                      0x00
 #define FSCTRL1                      0x0c
 #define FSCTRL0                      0x00
 #define MDMCFG4                      0x2D
 #define MDMCFG3                      0x3B
 #define MDMCFG2                      0x13
 #define MDMCFG1                      0x23
 #define MDMCFG0                      0xff
 #define DEVIATN                      0x62
 #define FREND1                       0xB6
 #define FREND0                       0x10
 #define MCSM1                        0x30
 #define MCSM0                        0x18
 #define FOCCFG                       0x1D
 #define BSCFG                        0x1C
 //AGCCTRL 在RSSI 高于-80时 GPIO脚为高电平
 //-88+(40-33)+1 ==-80
 #define AGCCTRL2                     0x4e
 #define AGCCTRL1                     0x41
 #define AGCCTRL0                     0x91
 #define FSCAL3                       0xEA
 #define FSCAL2                       0x2A
 #define FSCAL1                       0x00
 #define FSCAL0                       0x1F
 #define FSTEST                       0x59
 #define TEST2                        0x88
 #define TEST1                        0x31
 #define TEST0                        0x09
 //FIFOTHR
 #define FIFOTHR                      0x07
 //IOCFG
 #define IOCFG2                       CarrierSense
 #define IOCFG0                       SignalCheck
 //PKTCTRL  white data
 #define PKTCTRL1                     0x06
 #define PKTCTRL0                     0x05
 //PKELEN  30 bytes 
 #define PKTLEN                       0xff

 
 #ifdef __cplusplus
     }
 #endif
 
 #endif
