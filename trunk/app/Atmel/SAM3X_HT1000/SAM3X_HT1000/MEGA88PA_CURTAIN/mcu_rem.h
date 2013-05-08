
//====================================================================
//	�ļ���:		mcu_rem.h
//	�� ��:		V1.0
//	�� ��:		2010/12/21
//====================================================================

#ifndef	HCS_REM_H
#define HCS_REM_H

// �洢���ã�Ӧ����ʹ�õ�EEPROM���ú��ʵ���ֵ
#define	ADDR_LPTR	0x30	// ѧϰָ��洢��ַ
#define	ADDR_TABLE	0x32	// ������洢�׵�ַ
#define	MAX_USER	20		// ��������������0x20��0x1B0
#define	EL_SIZE		4		// ����������Ĵ洢��Ԫ��

#define MATCH_RF        1
#define CHECK           2
#define PASS            3
#define LEARN           4
#define ADD_RF          5
#define LEARNOK         6
#define ENPLLUS         7
#define CLR_LIMIT       8

#define ADDR_REVERSE_FLAG	0x02
#define ADDR_LIM_FLAG	        0x06
#define	ADDR_ID   	        0x16	// 485 ID��ַ
//#define ADDR_THIRD_POS_FLAG	0x08

/*extern unsigned char Hour;
extern unsigned char Minute;
extern unsigned char Seconds;
extern unsigned char SecPass;
extern unsigned char HourOp;
extern unsigned char MinuOp;
extern unsigned char HourCl;
extern unsigned char MinuCl;*/
//ģʽ
extern unsigned char RunMode;

extern unsigned char f_Reverse;
extern unsigned char f_Limit;
extern unsigned char RecBufFull;
extern unsigned char FLearn;

extern void	InitReceiver(void);			// ��ʼ������
extern void	rxi(unsigned char RFBit);	        // ң�����ݽ��գ�ÿ100us����һ��
extern void	Remote(void);			// ���ݽ��룬���ջ������������
extern void ClearMem(void);				// ������з��������
extern unsigned char GetRemData(void);	                // ��ȡ������������ݣ�ÿ10ms����һ��

#endif
