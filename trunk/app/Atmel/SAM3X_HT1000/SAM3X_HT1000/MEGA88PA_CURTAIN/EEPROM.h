//====================================================================
//	文件名:		EEPROM.h
//	版 本:		V1.0
//	日 期:		2007/07/05
//====================================================================

extern unsigned char EE_ReadBYTE( unsigned int location);	//	从EEPROM中读取一个BYTE值
extern unsigned int EE_ReadInt( unsigned int location);	//	从EEPROM中读取一个int值
extern void EE_WriteBYTE( unsigned int location, unsigned char WriteData);	//	向EEPROM中写入一个BYTE值
extern void EE_WriteInt( unsigned int location, unsigned int WriteData);	//	向EEPROM中写入一个int值
extern unsigned char EE_CheckReady(void);	//	检查写操作完成
