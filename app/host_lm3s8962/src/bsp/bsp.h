#ifndef _BSP_H_
#define _BSP_H_


//-----------------------------------bsp.c---------------------------------
extern void BSP_Init(void);


//-----------------------------------bsp_led.c---------------------------------
extern void BSP_LedInit(void);
extern void BSP_LedSet(unsigned char id);
extern void BSP_LedClear(unsigned char id);
extern void BSP_LedToggle(unsigned char id);


//-----------------------------------bsp_ssi.c---------------------------------
extern void BSP_SSI0_Init(void);
extern void cc2520_strobe(unsigned long data);
extern unsigned char cc2520_status(void);
extern unsigned char cc2520_getReg(unsigned short adr);
extern void cc2520_setReg(unsigned short adr, unsigned char value);
extern void cc2520_arch_init(void);

#endif
