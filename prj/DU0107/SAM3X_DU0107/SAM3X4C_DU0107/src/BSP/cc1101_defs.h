/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 *
 ***************************************************************/

#ifndef CC1101_DEFS_H
#define CC1101_DEFS_H

 #define IOCFG2                0x00
 //GDO2 output pin configuration
 #define IOCFG1                0x01
 //GDO1 output pin configuration
 #define IOCFG0                0x02
 //GDO0 output pin configuration
 #define FIFOTHR               0x03
 //RX FIFO and TX FIFO thresholds
 #define SYNC1                 0x04
 //Sync word, high byte
 #define SYNC0                 0x05
 //Sync word, low byte
 #define PKTLEN                0x06
 //Packet length
 #define PKTCTRL1              0x07
 //Packet automation control
 #define PKTCTRL0              0x08
 //Packet automation control
 #define ADDR                  0x09
 //Device address
 #define CHANNR                0x0A
 //Channel number
 #define FSCTRL1               0x0B
 //Frequency synthesizer control
 #define FSCTRL0               0x0C
 //Frequency synthesizer control
 #define FREQ2                 0x0D
 //Frequency control word, high byte
 #define FREQ1                 0x0E
 //Frequency control word, middle byte
 #define FREQ0                 0x0F
 //Frequency control word, low byte
 #define MDMCFG4               0x10
 //Modem configuration
 #define MDMCFG3               0x11
 //Modem configuration
 #define MDMCFG2               0x12
 //Modem configuration
 #define MDMCFG1               0x13
 //Modem configuration
 #define MDMCFG0               0x14
 //Modem configuration
 #define DEVIATN               0x15
 //Modem deviation setting
 #define MCSM2                 0x16
 //Main Radio Control State Machine configuration
 #define MCSM1                 0x17
 //Main Radio Control State Machine configuration
 #define MCSM0                 0x18
 //Main Radio Control State Machine configuration
 #define FOCCFG                0x19
 //Frequency Offset Compensation configuration
 #define BSCFG                 0x1A
 //Bit Synchronization configuration
 #define AGCCTRL2              0x1B
 //AGC control
 #define AGCCTRL1              0x1C
 //AGC control
 #define AGCCTRL0              0x1D
 //AGC control
 #define WOREVT1               0x1E
 //High byte Event 0 timeout
 #define WOREVT0               0x1F
 //Low byte Event 0 timeout
 #define WORCTRL               0x20
 //Wake On Radio control
 #define FREND1                0x21
 //Front end RX configuration
 #define FREND0                0x22
 //Front end TX configuration
 #define FSCAL3                0x23
 //Frequency synthesizer calibration
 #define FSCAL2                0x24
 //Frequency synthesizer calibration
 #define FSCAL1                0x25
 //Frequency synthesizer calibration
 #define FSCAL0                0x26
 //Frequency synthesizer calibration
 #define RCCTRL1               0x27
 //RC oscillator configuration
 #define RCCTRL0               0x28
 //RC oscillator configuration
 #define FSTEST                0x29
 //Frequency synthesizer calibration control
 #define PTEST                 0x2A
 //Production test
 #define AGCTEST               0x2B
 //AGC test
 #define TEST2                 0x2C
 //Various test settings
 #define TEST1                 0x2D
 //Various test settings
 #define TEST0                 0x2E
 //Various test settings


#define SMARTRF_SETTING_FSCTRL1    0x0C
#define SMARTRF_SETTING_FSCTRL0    0x00
#define SMARTRF_SETTING_FREQ2      0x22
#define SMARTRF_SETTING_FREQ1      0xB1
#define SMARTRF_SETTING_FREQ0      0x3B
#define SMARTRF_SETTING_MDMCFG4    0x2D
#define SMARTRF_SETTING_MDMCFG3    0x3B
#define SMARTRF_SETTING_MDMCFG2    0x13
#define SMARTRF_SETTING_MDMCFG1    0x22
#define SMARTRF_SETTING_MDMCFG0    0xF8
#define SMARTRF_SETTING_CHANNR     0x14
#define SMARTRF_SETTING_DEVIATN    0x62
#define SMARTRF_SETTING_FREND1     0xB6
#define SMARTRF_SETTING_FREND0     0x10
#define SMARTRF_SETTING_MCSM0      0x18
#define SMARTRF_SETTING_FOCCFG     0x1D
#define SMARTRF_SETTING_BSCFG      0x1C
#define SMARTRF_SETTING_AGCCTRL2   0xC7
#define SMARTRF_SETTING_AGCCTRL1   0x00
#define SMARTRF_SETTING_AGCCTRL0   0xB0
#define SMARTRF_SETTING_FSCAL3     0xEA
#define SMARTRF_SETTING_FSCAL2     0x2A
#define SMARTRF_SETTING_FSCAL1     0x00
#define SMARTRF_SETTING_FSCAL0     0x1F
#define SMARTRF_SETTING_FSTEST     0x59
#define SMARTRF_SETTING_TEST2      0x88
#define SMARTRF_SETTING_TEST1      0x31
#define SMARTRF_SETTING_TEST0      0x09
#define SMARTRF_SETTING_FIFOTHR    0x07
#define SMARTRF_SETTING_IOCFG2     0x29
#define SMARTRF_SETTING_IOCFG0D    0x06
#define SMARTRF_SETTING_PKTCTRL1   0x04
#define SMARTRF_SETTING_PKTCTRL0   0x05
#define SMARTRF_SETTING_ADDR       0x00
#define SMARTRF_SETTING_PKTLEN     0xFF

#endif