//====================================================================
//	�ļ���:		EEPROM.c
//	�� ��:		V1.0
//	�� ��:		2007/09/09
//====================================================================

#include "MCU.h"
//#include <iom88.h>
//#include <intrinsics.h>

#ifdef __IOM8_H
#define EEROM_WE	EEWE
#define EEROM_MWE	EEMWE
#endif


#define EEROM_WE	EEPE
#define EEROM_MWE	EEMPE



#ifdef __IOM168_H
#define EEROM_WE	EEPE
#define EEROM_MWE	EEMPE
#endif

#ifdef __IOM48_H
#define EEROM_WE	EEPE
#define EEROM_MWE	EEMPE
#endif
//===================================================================
//	��EEPROM�ж�ȡһ��BYTEֵ
//-------------------------------------------------------------------
unsigned char EE_ReadBYTE( unsigned int location)
{
	unsigned char temp;
	
	while (EECR & (1 << EEROM_WE));	// Wait for last write done
	EEAR = location;
    EECR |= (1 << EERE);			// Set READ strobe
    temp = EEDR;
    return temp;
}

//===================================================================
//	��EEPROM�ж�ȡһ��intֵ
//-------------------------------------------------------------------
unsigned int EE_ReadInt( unsigned int location)
{
	unsigned int temp;
	
	while (EECR & (1 << EEROM_WE));	// Wait for last write done
	
	EEAR = location;
    EECR |= (1 << EERE);			// Set READ strobe
    temp = EEDR;
    
    EEAR += 1;
    EECR |= (1 << EERE);			// Set READ strobe
    temp = (temp << 8) + EEDR;
    return temp;
}

//==================================================================
//	��EEPROM��д��һ��BYTEֵ
//--------------------------------------------------------------------
void EE_WriteBYTE( unsigned int location, unsigned char WriteData)
{
	unsigned char oldSREG;

	wdt_reset();
	while (EECR & (1 << EEROM_WE));	// Wait for last write done
	wdt_reset();
	EEAR = location;
    EEDR = WriteData;
    oldSREG = SREG;
	SREG &= ~0x80;				// disable interrupt
    EECR |= (1 << EEROM_MWE);	// Set MASTER WRITE enable
    EECR |= (1 << EEROM_WE);	// Set WRITE strobe
	SREG = oldSREG;
}

//==================================================================
//	��EEPROM��д��һ��intֵ
//--------------------------------------------------------------------
void EE_WriteInt( unsigned int location, unsigned int WriteData)
{
	unsigned char oldSREG;
	
	wdt_reset();
	while (EECR & (1 << EEROM_WE));	// Wait for last write done
	wdt_reset();
	EEAR = location;
    EEDR = WriteData >> 8;
    oldSREG = SREG;
	SREG &= ~0x80;				// disable interrupt
    EECR |= (1 << EEROM_MWE);	// Set MASTER WRITE enable
    EECR |= (1 << EEROM_WE);	// Set WRITE strobe
    SREG = oldSREG;
	
	while (EECR & (1 << EEROM_WE));	// Wait for last write done
	EEAR += 1;
    EEDR = WriteData;
    oldSREG = SREG;
	SREG &= ~0x80;				// disable interrupt
    EECR |= (1 << EEROM_MWE);	// Set MASTER WRITE enable
    EECR |= (1 << EEROM_WE);	// Set WRITE strobe
	SREG = oldSREG;
}

unsigned char EE_CheckReady(void)
{
	while (EECR & (1 << EEROM_WE))
	{
		wdt_reset();		// Wait for last write done
	}
	return 1;
}
