/* ********************************************************************** *
 *                           DOOYA Company                                *
 * The Tree of the NetWork Design Basic CC1101                            *
 * Compiler : MPLAB IDE V8.66                                             *
 * Crystal  : 32MHZ                                                       *
 * MCU      : PIC24FJ64GA002                                              *
 * FileName : RfSpiDrive.h                                                *
 * Author   : Softli                                                      *
 * Address  : NingBo                                                      *
 * Time     : 2012-12-21                                                  *
 * Version  : V1.0                                                        *
 * Testing                                                                *
 * ********************************************************************** */

 #ifndef _Rf_Spi_Drive_H_
 #define _Rf_Spi_Drive_H_

 #ifdef __cplusplus
    extern "C" {
 #endif
 
 #ifdef _RfSpi_Global_
      #define RfSpi_Ext
 #else
      #define RfSpi_Ext                 extern 
 #endif

/* ============================================== *
 *                     Defines                    *
 * ============================================== */
 //spi communication pin 
 //mosi--RB11
 #define SPI_HOST_MOSI_Pin              11
 //miso--RB13 
 #define SPI_HOST_MISO_Pin              7
 //sclk--RB12 
 #define SPI_HOST_SCLK_Pin              8
 

/* ============================================== *
 *                    Typedefs                    *
 * ============================================== */


/* ============================================== *
 *            function declaration                *
 * ============================================== */
 //spi write byte 
 void Spi_Write_Byte(unsigned char data);

 //spi read byte
 unsigned char Spi_Read_Byte(void);

 //API Write a byte to register
 void APIWriteByte(unsigned char data);

 //API read a byte from register 
 unsigned char APIReadByte(void);

 //API write array bytes to register 
 void APIWriteArrayBytes(unsigned char *data,unsigned int length);

 //API Read array bytes from register 
 void APIReadArrayBytes(unsigned int length);

 //spi initial
 void APISpiModuleInitial(void);

 #ifdef __cplusplus
    }
 #endif


 #endif
