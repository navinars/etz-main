/***************************************************************
 *  SmartRF Studio(tm) Export
 *
 *  Radio register settings specifed with C-code
 *  compatible #define statements.
 *
 ***************************************************************/

#ifndef CC1101_DEFS_H
#define CC1101_DEFS_H


// Configuration Registers
#define TI_CCxxx0_IOCFG2       0x00        // GDO2 output pin configuration
#define TI_CCxxx0_IOCFG1       0x01        // GDO1 output pin configuration
#define TI_CCxxx0_IOCFG0       0x02        // GDO0 output pin configuration
#define TI_CCxxx0_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define TI_CCxxx0_SYNC1        0x04        // Sync word, high byte
#define TI_CCxxx0_SYNC0        0x05        // Sync word, low byte
#define TI_CCxxx0_PKTLEN       0x06        // Packet length
#define TI_CCxxx0_PKTCTRL1     0x07        // Packet automation control
#define TI_CCxxx0_PKTCTRL0     0x08        // Packet automation control
#define TI_CCxxx0_ADDR         0x09        // Device address
#define TI_CCxxx0_CHANNR       0x0A        // Channel number
#define TI_CCxxx0_FSCTRL1      0x0B        // Frequency synthesizer control
#define TI_CCxxx0_FSCTRL0      0x0C        // Frequency synthesizer control
#define TI_CCxxx0_FREQ2        0x0D        // Frequency control word, high byte
#define TI_CCxxx0_FREQ1        0x0E        // Frequency control word, middle byte
#define TI_CCxxx0_FREQ0        0x0F        // Frequency control word, low byte
#define TI_CCxxx0_MDMCFG4      0x10        // Modem configuration
#define TI_CCxxx0_MDMCFG3      0x11        // Modem configuration
#define TI_CCxxx0_MDMCFG2      0x12        // Modem configuration
#define TI_CCxxx0_MDMCFG1      0x13        // Modem configuration
#define TI_CCxxx0_MDMCFG0      0x14        // Modem configuration
#define TI_CCxxx0_DEVIATN      0x15        // Modem deviation setting
#define TI_CCxxx0_MCSM2        0x16        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_MCSM1        0x17        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_MCSM0        0x18        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_FOCCFG       0x19        // Frequency Offset Compensation config
#define TI_CCxxx0_BSCFG        0x1A        // Bit Synchronization configuration
#define TI_CCxxx0_AGCCTRL2     0x1B        // AGC control
#define TI_CCxxx0_AGCCTRL1     0x1C        // AGC control
#define TI_CCxxx0_AGCCTRL0     0x1D        // AGC control
#define TI_CCxxx0_WOREVT1      0x1E        // High byte Event 0 timeout
#define TI_CCxxx0_WOREVT0      0x1F        // Low byte Event 0 timeout
#define TI_CCxxx0_WORCTRL      0x20        // Wake On Radio control
#define TI_CCxxx0_FREND1       0x21        // Front end RX configuration
#define TI_CCxxx0_FREND0       0x22        // Front end TX configuration
#define TI_CCxxx0_FSCAL3       0x23        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL2       0x24        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL1       0x25        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL0       0x26        // Frequency synthesizer calibration
#define TI_CCxxx0_RCCTRL1      0x27        // RC oscillator configuration
#define TI_CCxxx0_RCCTRL0      0x28        // RC oscillator configuration
#define TI_CCxxx0_FSTEST       0x29        // Frequency synthesizer cal control
#define TI_CCxxx0_PTEST        0x2A        // Production test
#define TI_CCxxx0_AGCTEST      0x2B        // AGC test
#define TI_CCxxx0_TEST2        0x2C        // Various test settings
#define TI_CCxxx0_TEST1        0x2D        // Various test settings
#define TI_CCxxx0_TEST0        0x2E        // Various test settings

// Strobe commands
#define TI_CCxxx0_SRES         0x30        // Reset chip.
#define TI_CCxxx0_SFSTXON      0x31        // Enable/calibrate freq synthesizer
#define TI_CCxxx0_SXOFF        0x32        // Turn off crystal oscillator.
#define TI_CCxxx0_SCAL         0x33        // Calibrate freq synthesizer & disable
#define TI_CCxxx0_SRX          0x34        // Enable RX.
#define TI_CCxxx0_STX          0x35        // Enable TX.
#define TI_CCxxx0_SIDLE        0x36        // Exit RX / TX
#define TI_CCxxx0_SAFC         0x37        // AFC adjustment of freq synthesizer
#define TI_CCxxx0_SWOR         0x38        // Start automatic RX polling sequence
#define TI_CCxxx0_SPWD         0x39        // Enter pwr down mode when CSn goes hi
#define TI_CCxxx0_SFRX         0x3A        // Flush the RX FIFO buffer.
#define TI_CCxxx0_SFTX         0x3B        // Flush the TX FIFO buffer.
#define TI_CCxxx0_SWORRST      0x3C        // Reset real time clock.
#define TI_CCxxx0_SNOP         0x3D        // No operation.

// Status registers
#define TI_CCxxx0_PARTNUM      0x30        // Part number
#define TI_CCxxx0_VERSION      0x31        // Current version number
#define TI_CCxxx0_FREQEST      0x32        // Frequency offset estimate
#define TI_CCxxx0_LQI          0x33        // Demodulator estimate for link quality
#define TI_CCxxx0_RSSI         0x34        // Received signal strength indication
#define TI_CCxxx0_MARCSTATE    0x35        // Control state machine state
#define TI_CCxxx0_WORTIME1     0x36        // High byte of WOR timer
#define TI_CCxxx0_WORTIME0     0x37        // Low byte of WOR timer
#define TI_CCxxx0_PKTSTATUS    0x38        // Current GDOx status and packet status
#define TI_CCxxx0_VCO_VC_DAC   0x39        // Current setting from PLL cal module
#define TI_CCxxx0_TXBYTES      0x3A        // Underflow and # of bytes in TXFIFO
#define TI_CCxxx0_RXBYTES      0x3B        // Overflow and # of bytes in RXFIFO
#define TI_CCxxx0_NUM_RXBYTES  0x7F        // Mask "# of bytes" field in _RXBYTES

// Other memory locations
#define TI_CCxxx0_PATABLE      0x3E
#define TI_CCxxx0_TXFIFO       0x3F
#define TI_CCxxx0_RXFIFO       0x3F

// Masks for appended status bytes
#define TI_CCxxx0_LQI_RX       0x01        // Position of LQI byte
#define TI_CCxxx0_CRC_OK       0x80        // Mask "CRC_OK" bit within LQI byte

// Definitions to support burst/single access:
#define TI_CCxxx0_WRITE_BURST  0x40
#define TI_CCxxx0_READ_SINGLE  0x80
#define TI_CCxxx0_READ_BURST   0xC0


/* configuration registers */
#define IOCFG2      0x00      /*  IOCFG2   - GDO2 output pin configuration  */
#define IOCFG1      0x01      /*  IOCFG1   - GDO1 output pin configuration  */
#define IOCFG0      0x02      /*  IOCFG1   - GDO0 output pin configuration  */
#define FIFOTHR     0x03      /*  FIFOTHR  - RX FIFO and TX FIFO thresholds */
#define SYNC1       0x04      /*  SYNC1    - Sync word, high byte */
#define SYNC0       0x05      /*  SYNC0    - Sync word, low byte */
#define PKTLEN      0x06      /*  PKTLEN   - Packet length */
#define PKTCTRL1    0x07      /*  PKTCTRL1 - Packet automation control */
#define PKTCTRL0    0x08      /*  PKTCTRL0 - Packet automation control */
#define ADDR        0x09      /*  ADDR     - Device address */
#define CHANNR      0x0A      /*  CHANNR   - Channel number */
#define FSCTRL1     0x0B      /*  FSCTRL1  - Frequency synthesizer control */
#define FSCTRL0     0x0C      /*  FSCTRL0  - Frequency synthesizer control */
#define FREQ2       0x0D      /*  FREQ2    - Frequency control word, high byte */
#define FREQ1       0x0E      /*  FREQ1    - Frequency control word, middle byte */
#define FREQ0       0x0F      /*  FREQ0    - Frequency control word, low byte */
#define MDMCFG4     0x10      /*  MDMCFG4  - Modem configuration */
#define MDMCFG3     0x11      /*  MDMCFG3  - Modem configuration */
#define MDMCFG2     0x12      /*  MDMCFG2  - Modem configuration */
#define MDMCFG1     0x13      /*  MDMCFG1  - Modem configuration */
#define MDMCFG0     0x14      /*  MDMCFG0  - Modem configuration */
#define DEVIATN     0x15      /*  DEVIATN  - Modem deviation setting */
#define MCSM2       0x16      /*  MCSM2    - Main Radio Control State Machine configuration */
#define MCSM1       0x17      /*  MCSM1    - Main Radio Control State Machine configuration */
#define MCSM0       0x18      /*  MCSM0    - Main Radio Control State Machine configuration */
#define FOCCFG      0x19      /*  FOCCFG   - Frequency Offset Compensation configuration */
#define BSCFG       0x1A      /*  BSCFG    - Bit Synchronization configuration */
#define AGCCTRL2    0x1B      /*  AGCCTRL2 - AGC control */
#define AGCCTRL1    0x1C      /*  AGCCTRL1 - AGC control */
#define AGCCTRL0    0x1D      /*  AGCCTRL0 - AGC control */
#define WOREVT1     0x1E      /*  WOREVT1  - High byte Event0 timeout */
#define WOREVT0     0x1F      /*  WOREVT0  - Low byte Event0 timeout */
#define WORCTRL     0x20      /*  WORCTRL  - Wake On Radio control */
#define FREND1      0x21      /*  FREND1   - Front end RX configuration */
#define FREND0      0x22      /*  FREDN0   - Front end TX configuration */
#define FSCAL3      0x23      /*  FSCAL3   - Frequency synthesizer calibration */
#define FSCAL2      0x24      /*  FSCAL2   - Frequency synthesizer calibration */
#define FSCAL1      0x25      /*  FSCAL1   - Frequency synthesizer calibration */
#define FSCAL0      0x26      /*  FSCAL0   - Frequency synthesizer calibration */
#define RCCTRL1     0x27      /*  RCCTRL1  - RC oscillator configuration */
#define RCCTRL0     0x28      /*  RCCTRL0  - RC oscillator configuration */
#define FSTEST      0x29      /*  FSTEST   - Frequency synthesizer calibration control */
#define PTEST       0x2A      /*  PTEST    - Production test */
#define AGCTEST     0x2B      /*  AGCTEST  - AGC test */
#define TEST2       0x2C      /*  TEST2    - Various test settings */
#define TEST1       0x2D      /*  TEST1    - Various test settings */
#define TEST0       0x2E      /*  TEST0    - Various test settings */

/* status registers */
#define PARTNUM     0x30      /*  PARTNUM    - Chip ID */
#define VERSION     0x31      /*  VERSION    - Chip ID */
#define FREQEST     0x32      /*  FREQEST    ?Frequency Offset Estimate from demodulator */
#define LQI         0x33      /*  LQI        ?Demodulator estimate for Link Quality */
#define RSSI        0x34      /*  RSSI       ?Received signal strength indication */
#define MARCSTATE   0x35      /*  MARCSTATE  ?Main Radio Control State Machine state */
#define WORTIME1    0x36      /*  WORTIME1   ?High byte of WOR time */
#define WORTIME0    0x37      /*  WORTIME0   ?Low byte of WOR time */
#define PKTSTATUS   0x38      /*  PKTSTATUS  ?Current GDOx status and packet status */
#define VCO_VC_DAC  0x39      /*  VCO_VC_DAC ?Current setting from PLL calibration module */
#define TXBYTES     0x3A      /*  TXBYTES    ?Underflow and number of bytes */
#define RXBYTES     0x3B      /*  RXBYTES    ?Overflow and number of bytes */

/* burst write registers */
#define PA_TABLE0   0x3E      /*  PA_TABLE0 - PA control settings table */
#define TXFIFO      0x3F      /*  TXFIFO  - Transmit FIFO */
#define RXFIFO      0x3F      /*  RXFIFO  - Receive FIFO */

/* command strobe registers */
#define SRES        0x30      /*  SRES    - Reset chip. */
#define SFSTXON     0x31      /*  SFSTXON - Enable and calibrate frequency synthesizer. */
#define SXOFF       0x32      /*  SXOFF   - Turn off crystal oscillator. */
#define SCAL        0x33      /*  SCAL    - Calibrate frequency synthesizer and turn it off. */
#define SRX         0x34      /*  SRX     - Enable RX. Perform calibration if enabled. */
#define STX         0x35      /*  STX     - Enable TX. If in RX state, only enable TX if CCA passes. */
#define SIDLE       0x36      /*  SIDLE   - Exit RX / TX, turn off frequency synthesizer. */
#define SRSVD       0x37      /*  SRVSD   - Reserved.  Do not use. */
#define SWOR        0x38      /*  SWOR    - Start automatic RX polling sequence (Wake-on-Radio) */
#define SPWD        0x39      /*  SPWD    - Enter power down mode when CSn goes high. */
#define SFRX        0x3A      /*  SFRX    - Flush the RX FIFO buffer. */
#define SFTX        0x3B      /*  SFTX    - Flush the TX FIFO buffer. */
#define SWORRST     0x3C      /*  SWORRST - Reset real time clock. */
#define SNOP        0x3D      /*  SNOP    - No operation. Returns status byte. */

//
#endif