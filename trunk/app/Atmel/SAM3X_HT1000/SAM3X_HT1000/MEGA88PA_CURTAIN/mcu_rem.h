
//====================================================================
//	文件名:		mcu_rem.h
//	版 本:		V1.0
//	日 期:		2010/12/21
//====================================================================

#ifndef	HCS_REM_H
#define HCS_REM_H

// 存储设置，应根据使用的EEPROM设置合适的数值
#define	ADDR_LPTR	0x30	// 学习指针存储地址
#define	ADDR_TABLE	0x32	// 发射机存储首地址
#define	MAX_USER	20		// 最大发射机数量，从0x20到0x1B0
#define	EL_SIZE		4		// 单个发射机的存储单元数

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
#define	ADDR_ID   	        0x16	// 485 ID地址
//#define ADDR_THIRD_POS_FLAG	0x08

/*extern unsigned char Hour;
extern unsigned char Minute;
extern unsigned char Seconds;
extern unsigned char SecPass;
extern unsigned char HourOp;
extern unsigned char MinuOp;
extern unsigned char HourCl;
extern unsigned char MinuCl;*/
//模式
extern unsigned char RunMode;

extern unsigned char f_Reverse;
extern unsigned char f_Limit;
extern unsigned char RecBufFull;
extern unsigned char FLearn;

extern void	InitReceiver(void);			// 初始化接收
extern void	rxi(unsigned char RFBit);	        // 遥控数据接收，每100us调用一次
extern void	Remote(void);			// 数据解码，接收缓冲区满后调用
extern void ClearMem(void);				// 清除所有发射机数据
extern unsigned char GetRemData(void);	                // 获取发射机按键数据，每10ms调用一次

#endif
