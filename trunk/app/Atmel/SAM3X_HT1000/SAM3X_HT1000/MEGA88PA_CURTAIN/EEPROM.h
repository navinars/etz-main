//====================================================================
//	�ļ���:		EEPROM.h
//	�� ��:		V1.0
//	�� ��:		2007/07/05
//====================================================================

extern unsigned char EE_ReadBYTE( unsigned int location);	//	��EEPROM�ж�ȡһ��BYTEֵ
extern unsigned int EE_ReadInt( unsigned int location);	//	��EEPROM�ж�ȡһ��intֵ
extern void EE_WriteBYTE( unsigned int location, unsigned char WriteData);	//	��EEPROM��д��һ��BYTEֵ
extern void EE_WriteInt( unsigned int location, unsigned int WriteData);	//	��EEPROM��д��һ��intֵ
extern unsigned char EE_CheckReady(void);	//	���д�������
