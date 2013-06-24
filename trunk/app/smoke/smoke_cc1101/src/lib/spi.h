#ifndef _SPI_H_
#define _SPI_H_

extern void spi_init(void);

extern void spi_isr_enable(void);

extern void spi_cs_enable(void);

extern void spi_cs_disable(void);

extern unsigned char spi_readwrite(unsigned char data);

extern void spi_write_buf(unsigned char *pdata, unsigned char len);

extern void spi_read_buf(unsigned char *pdata, unsigned char len);


#endif
