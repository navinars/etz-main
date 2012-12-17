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

#define HAL_MAC_SPI_ENABLE() SSIEnable(SSI0_BASE)
#define HAL_MAC_SPI_DISABLE() SSIDisable(SSI0_BASE)

#define HAL_MAC_SPI_PERIPHERAL_DISABLE() SysCtlPeripheralDisable(SYSCTL_PERIPH_SSI0)
/* SO Pin Configuration */
#define HAL_MAC_SPI_SO_GPIO_BIT                   GPIO_PIN_4
#define HAL_MAC_SPI_SO_GPIO_PORT                  GPIO_PORTF_BASE
#define HAL_MAC_SPI_CONFIG_SO_PIN_AS_INPUT()      GPIOPinTypeGPIOInput(HAL_MAC_SPI_SO_GPIO_PORT, HAL_MAC_SPI_SO_GPIO_BIT)
#define HAL_MAC_SPI_READ_SO_PIN()                 GPIOPinRead(HAL_MAC_SPI_SO_GPIO_PORT, HAL_MAC_SPI_SO_GPIO_BIT)

#define HAL_MAC_SPI_LUMINARY_SO_AS_GPIO()           \
{                                                   \
  HAL_MAC_SPI_DISABLE();                            \
  HAL_MAC_SPI_PERIPHERAL_DISABLE();                 \
  HAL_MAC_SPI_CONFIG_SO_PIN_AS_INPUT();             \
}

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
