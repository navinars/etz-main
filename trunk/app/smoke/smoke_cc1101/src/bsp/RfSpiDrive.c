/* ********************************************************************** *
 *                           DOOYA Company                                *
 * The Tree of the NetWork Design Basic CC1101                            *
 * Compiler : MPLAB IDE V8.66                                             *
 * Crystal  : 32MHZ                                                       *
 * MCU      : PIC24FJ64GA002                                              *
 * FileName : RfSpiDrive.c                                                *
 * Author   : Softli                                                      *
 * Address  : NingBo                                                      *
 * Time     : 2012-12-21                                                  *
 * Version  : V1.0                                                        *
 * Testing                                                                *
 * ********************************************************************** */
 
 #define _RfSpi_Global_
 
 #include "p24fj64ga002.h"
 #include "../Common/Common.h"
 #include "../Common/Hal_Defs.h"
 #include "../Common/Hal_StaTsk.h"
 #include "../Components/Hal/MCUConfig.h"
 #include "../Components/Hal/RfSpiDrive.h"
 #include "../Components/Hal/RfTranceiver.h"
 
 //spi write byte
 void Spi_Write_Byte(unsigned char data)
 {
    unsigned char i;
    IFS0bits.SPI1IF = 0;
    i = SPI1BUF;
    SPI1BUF = data;
    while(IFS0bits.SPI1IF == 0);
 }

 //spi read byte
 unsigned char Spi_Read_Byte(void)
 {
	Spi_Write_Byte(0x00);
	return SPI1BUF;
 }

 //API Write a byte to register
 void APIWriteByte(unsigned char data)
 {
    Spi_Write_Byte(data);
 }
 
 //API read a byte from register 
 unsigned char APIReadByte(void)
 {
    unsigned char data;

    data=Spi_Read_Byte();

    return data;
 }

 //API write array bytes to register 
 void APIWriteArrayBytes(unsigned char *data,unsigned int length)
 { 
    unsigned int    i;
    unsigned char  *temp_ptr = data;
    for(i=0;i<length;i++)
    {
        Spi_Write_Byte(*temp_ptr++);
    }
 }

 //API Read array bytes from register 
 void APIReadArrayBytes(unsigned int length)
 {
    unsigned int i;
    for(i=0;i<length;i++)
    {
        *ptrRxBufWrite++=Spi_Read_Byte();
        if(ptrRxBufWrite == ptrRxBufOver)
        {
            ptrRxBufWrite = &RxBuf[0];
        }
    }
 }
 
 //spi initial
 void APISpiModuleInitial(void)
 {
    //port initial
    //pin:mosi
    RPINR20bits.SDI1R = SPI_HOST_MOSI_Pin;
    //pin:miso
    RPOR6bits.RP13R   = SPI_HOST_MISO_Pin;
    //pin:sclk
    RPOR6bits.RP12R   = SPI_HOST_SCLK_Pin;
    
	SPI1CON1=0x013f;
	SPI1STAT=0x8000;

    //清除中断标志位
    IFS0bits.SPI1IF = 0;
    IFS0bits.SPF1IF = 0;
    //不使能中断
    IEC0bits.SPI1IE = 0;
    IEC0bits.SPF1IE = 0;
 }
