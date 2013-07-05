
#include "bsp.h"
#include "cc1101_port.h"


/*-------------------------------------------------------------------------------------------------
 * @fn          Mrfi_DelayUsec
 *
 * @brief       delay us.
 *
 * @param       none
 *
 * @return      none
 *
 */
void Mrfi_DelayUsec(uint16_t howlong)
{
	uint16_t i;
	
	while(howlong --)
	{
		for(i = 0;i < 10000;i++)
		{
			asm("NOP");
		}
	}
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SPI_CSN_IS_LOW
 *
 * @brief       Low
 *
 * @param       none
 *
 * @return      none
 *
 */
void SPI_DRIVE_CSN_LOW(void)
{
	spi_cs_enable();
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SPI_CSN_IS_HIGH
 *
 * @brief       HIGH
 *
 * @param       none
 *
 * @return      none
 *
 */
void SPI_DRIVE_CSN_HIGH(void)
{
	spi_cs_disable();
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SPI_SO_IS_HIGH
 *
 * @brief       HIGH
 *
 * @param       none
 *
 * @return      none
 *
 */
uint8_t SPI_SO_IS_HIGH(void)
{
	return (!!(P1IN&BIT1));
}

/*-------------------------------------------------------------------------------------------------
 * @fn          MRFI_SPI_WRITE_BYTE
 *
 * @brief       data
 *
 * @param       none
 *
 * @return      none
 *
 */
uint8_t SpiWriteByte(uint8_t data)
{
	return spi_readwrite(data);
}

/*-------------------------------------------------------------------------------------------------
 * @fn          APIWriteArrayBytes
 *
 * @brief       data
 *
 * @param       none
 *
 * @return      none
 *
 */
void SPIWriteArrayBytes(uint8_t *buf, uint8_t cnt)
{
	spi_write_buf(buf, cnt);
}

/*-------------------------------------------------------------------------------------------------
 * @fn          Check_Rf_Level
 *
 * @brief       data
 *
 * @param       none
 *
 * @return      none
 *
 */
uint8_t Spi_CheckGpio0(void)
{
	return (!!(P2IN&BIT0));
}

/*-------------------------------------------------------------------------------------------------
 * @fn          Config GPIO0 pin
 *
 * @brief       data
 *
 * @param       none
 *
 * @return      none
 *
 */
void Mifi_ConfigInt(void)
{
	P2DIR &=~BIT0;
	P2IES |= BIT0;													// Ñ¡ÔñÉÏÉý/ÏÂ½µÑØ
	P2REN |= BIT0;													// push-up enable
	P2IFG &=~BIT0;
	P2IE  |= BIT0;
}
