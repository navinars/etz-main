#ifndef CC2520_ARCH_H
#define CC2520_ARCH_H

#define CC2520_GPIO0_IPIN	
#define CC2520_GPIO1_IPIN	(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0) == GPIO_PIN_0)
#define CC2520_GPIO2_IPIN	(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1) == GPIO_PIN_1)
#define CC2520_GPIO3_IPIN	(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2) == GPIO_PIN_2)
#define CC2520_GPIO4_IPIN	(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3) == GPIO_PIN_3)
#define CC2520_GPIO5_IPIN

// Inputs: SPI interface
#define CC2520_MISO_IPIN	(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4) == GPIO_PIN_4)

#define HAL_INT_OFF()
#define HAL_INT_ON()


extern void cc2520_arch_init(void);
extern void CC2520_SPI_BEGIN(void);
extern void CC2520_SPI_END(void);
extern unsigned char CC2520_SPI_TXRX(unsigned char dat);
extern void CC2520_SPI_TX(unsigned char dat);
extern unsigned char CC2520_SPI_RX(void);
extern void CC2520_RESET_OPIN(unsigned char x);
extern void CC2520_VREG_EN_OPIN(unsigned char x);
extern void CC2520_CSN_OPIN(unsigned char x);
extern void halMcuWaitUs(unsigned long usec);
extern void halMcuWaitMs(unsigned long msec);


#endif /* CC2520_ARCH_SFD_H */
