
//====================================================================
//	DOOYA遥控接收解码程序
//--------------------------------------------------------------------
//
//	文件名:		mcu_rem.c
//	作  者:     zhouyafei
//	公  司:     Ningbo Duya Mechanical & Electrical Equipment Co., Ltd.
//	版  本:		V1.0
//	日  期:		2010/12/17
//	功  能：	DOOYA Remote Reciever.
//
//====================================================================

#include "MCU.h"
#include <string.h>
#include "EEPROM.h"
#include "mcu_rem.h"




//---------------------------------------------------------------
//
// receive buffer map
//
// 
// IIIIIIII.IIIIIIII.IIIIIIII.IIIIIIII.CCCCCCCC
//	  0		   1		2		 3		  4
//
// I=S/N   -> SERIAL NUMBER		  (32 BIT)
// C=COMM  -> commond encoding	   (8 BIT)
//
//-----------------------------------------------------------------------------
//
// EEROM Table structure definition:
//
//  +-------+-------+
//  | TXFull| LPtr  |  0	Learn pointer and TX full flag
//  +-------+-------+
//  | IDMi1 | IDLo  |  1	IDMi and IDLo,contain the 16 lsb of the Serial Number
//  +-------+-------+	   
//  | IDHi  | IDMi2 |  2	IDHi and IDMi,contain the 16 msb of the Serial Number 
//  +-------+-------+		
//    ....    ....
//  +-------+-------+
//  | IDMi1 | IDLo  |  61	IDMi and IDLo,contain the 16 lsb of the Serial Number
//  +-------+-------+	   
//  | IDHi  | IDMi2 |  62	IDHi and IDMi,contain the 16 msb of the Serial Number 
//  +-------+-------+         
//
//--------------------------------------------------------------

#define	T_REMOTEOUT	40		// 400ms output delay
#define	NBIT		40		// number of bit to	receive	-1
#define	TRFreset	0
#define	TRFSYNC1	1
#define	TRFSYNC2	2
#define	TRFUNO		3
#define	TRFZERO		4
#define TRFFALL		5

#define	HIGH_TO		11		// longest high	Te
#define	LOW_TO		11		// longest low	Te
#define	SHORT_HEAD_H    28		// shortest	Thead accepted 2,8ms
#define	LONG_HEAD_H	74		// longest Thead accepted 7,4ms
#define SHORT_HEAD_L    9
#define LONG_HEAD_L     23

// 发送代码：（地址+通道+功能码）+mode +定时开小时+定时开分钟+
// 定时关小时+定时关分钟+当前小时+当前分钟+当前秒+校验和
// mode:  man 0x11, auto 0x22, random 0x44
#define IDLo	  Buffer[0]	// Buffer[0] 	//sync counter
#define IDMi1	  Buffer[1]	// Buffer[1] 	//
#define IDMi2	  Buffer[2] 	//discrimination bits	LSB
#define IDHi	  Buffer[3] 	//Disc. MSB +	Ovf	+ Key
#define	FCode	  Buffer[4] 	//S/N	LSB

//-----------------	variable defines ------------------------------------
unsigned char buf_rec[6];	//receive buffer
unsigned char RFstate;		//receiver state
unsigned char HiCount;		//timer counter
unsigned char LoCount;		//timer counter
unsigned char MinCount;
unsigned char Bptr;		//receive	buffer pointer
unsigned char BitCount;		//received bits counter
unsigned char HiCountTemp;	//received bits counter
unsigned char LoCountTemp;
unsigned char RecBufFull;	// buffer full
//unsigned char RFBit;		// sampled RF signal

unsigned char Buffer[6];	// data	waitting for decryption
unsigned char IDBuffer[6];
unsigned int EE_addr;		// address pointer to record in	mem.
unsigned int EE_data;		// data in	mem

unsigned char FLearn;		// Learn mode active
unsigned char RemData;		// Key data
unsigned char f_Interference;
unsigned char RemOutTime;	// output timer

// prototypes
void InitReceiver(void);		// initialize interrupt receiver
void rxi(unsigned char RFBit);	// remoter data receiver
void  Remote(void);				// Decode Routine
unsigned char Find(void);		// FIND Routine
void UpdateLPtr(void);			// update learn pointer
void WriteID(void);				// write ID number
void ClearMem(void);			// clear EEPROM
unsigned char GetRemData(void);

extern unsigned char f_Remotedelay;
//===========================================================
// 中断方式接收遥控数据，中断时间间隔：100us
// this	routine	gets called	every time TMR0	overflows
//-----------------------------------------------------------
void rxi(unsigned char RFBit)
{
	// this	routine	gets called	every time TMR0	overflows
	if (RecBufFull)
	{
		return;
	}
	switch (RFstate)	// state machine main switch
	{
		case TRFUNO:
			if (RFBit == 0)
			{ // falling edge detected	----+
			  //							|
			  //							+----
					RFstate = TRFZERO;
					LoCount++;
			}
			else
			{ // while high	
				HiCount++;
				if ( HiCount > HIGH_TO)
				{
					RFstate	= TRFreset;		 //	reset if too long
				}
			}
			break;
		case TRFZERO:
			if (RFBit)
			{ // rising	edge detected	  +----
			  //						  |
			  //					  ----+
				RFstate= TRFUNO;
				if ((HiCount + LoCount) < MinCount)
				{
					HiCount++;
					break;
				}
				if (LoCount == HiCount)
				{
					RFstate	= TRFreset;		// fall	back into RFSYNC state
					break;
				}
				buf_rec[Bptr] <<= 1;		// rotate	
				if (LoCount < HiCount)
				{
					buf_rec[Bptr] |= 0x01;	// shift in bit
				}
				LoCount	= 0;				// reset length	counter
				HiCount = 1;
				if (( ++BitCount & 7) == 0)
				{
					Bptr++;					// advance one unsigned	char
				}
				if (BitCount ==	NBIT)
				{
					RFstate	= TRFreset;		// finished	receiving
					RecBufFull = 1;
				}
			}
			else
			{ // still low
				LoCount++;
                /////////////////////////////////////////////////
                if (BitCount == 39)
                {
                    buf_rec[Bptr] <<= 1;		// rotate	
					if (HiCount > 5)
					{
						buf_rec[Bptr] |= 0x01;	// shift in bit
					}
					RecBufFull = 1;
                    RFstate	= TRFreset;		// fall	back into RFSYNC state
                }
                else
                {
                    if ( LoCount >=	LOW_TO)		// too long	low
                    {
                        RFstate	= TRFreset;		// fall	back into RFSYNC state
                    }
                }
                /////////////////////////////////////////////
				/*if ( LoCount >=	LOW_TO)		// too long	low
				{
					if (BitCount == 39)
					{
						buf_rec[Bptr] <<= 1;		// rotate	
						if (HiCount > 5)
						{
							buf_rec[Bptr] |= 0x01;	// shift in bit
						}
						RecBufFull = 1;
					}
					RFstate	= TRFreset;		// fall	back into RFSYNC state
				}*/
			}
			break;
		case TRFSYNC2:
			if (RFBit)
			{ // rising	edge detected  +---+				+---..
			  //					   |   |  <-Theader->	|	
			  //						   +----------------+
				HiCount++;
				HiCountTemp++;
				if (HiCountTemp < 2)
				{
					break;
				}
				HiCountTemp = 0;
				
				if ((LoCount < SHORT_HEAD_L) || (HiCount > 5))
				{
					HiCount = 2;
					LoCount	= 0;
					RFstate	= TRFFALL;
					break;					// too short/long, no header
				}
				else
				{
					
					LoCount	= 0;			// restart counter
					HiCount = 2;
					Bptr = 0;
					BitCount = 0;
					RFstate = TRFUNO;
				}
			}
			else
			{ // still low
				LoCount++;
				HiCountTemp = 0;
				if ((LoCount + HiCount) > LONG_HEAD_L)
				{
					RFstate	= TRFreset;	// too short/long, no header
				}
			}
			break;
		case TRFSYNC1:
			if (!RFBit)
			{
				LoCount++;
				LoCountTemp++;
				if (LoCountTemp < 2)
				{
					break;
				}
				LoCountTemp = 0;
				if ((HiCount < SHORT_HEAD_H) || (LoCount > 6))
				{
					RFstate = TRFFALL;
				}
				else
				{
					MinCount = (LoCount + HiCount - 2) / 5;	//
					RFstate = TRFSYNC2;
				}
				LoCount = 2;
				HiCount = 0;
			}
			else
			{
				HiCount++;
				LoCountTemp = 0;
				if ((HiCount + LoCount) > LONG_HEAD_H)
				{
					RFstate = TRFreset;
				}
			}
			break;
		case TRFFALL:
			if (!RFBit)				// detect falling edge	----+
			{			  			//							|
				LoCount++;			//							+----
				if (HiCount > 0)
				{
					HiCount = 0;
					LoCount = 1;
				}
			}
			else
			{
				HiCount++;
				if ((HiCount >= 2) && (LoCount >= 2))
				{
					LoCount = 0;
					LoCountTemp = 0;
					RFstate	= TRFSYNC1;		// reset state machine
				}
			}
			break;
		case TRFreset:
		default:
			LoCount	= 0;
			HiCount = 0;
			RFstate = TRFFALL;
			break;
	} // switch
} // rxi
//=============================================================
// initialize interrupt receiver
//
//-------------------------------------------------------------
void InitReceiver(void)
{
	RFstate	= TRFreset;	// reset state machine in all other	cases
	RecBufFull = 0;			// start with buffer empty
}

void Remote(void)
{
        unsigned char i;
	memcpy(Buffer, buf_rec, 6);
	RecBufFull = 0;
        for (i = 0;i < 6;i++)
        {
             buf_rec[i] = 0;
        }
	if (FLearn)		// Learn Mode
	{
		if (FLearn == CHECK)
		{
			if ((IDBuffer[0] == Buffer[0]) &&
			( IDBuffer[1] == Buffer[1]) &&
			( IDBuffer[2] == Buffer[2]) && 
			( IDBuffer[3] == Buffer[3]) &&
			( FCode == 0xcc))
			{
				FLearn = PASS;
			}
			return;
		}
		if (FLearn == LEARN)
		{
			if ((IDBuffer[0] != Buffer[0]) ||
			( IDBuffer[1] != Buffer[1]) ||
			( IDBuffer[2] != Buffer[2]) || 
			( IDBuffer[3] != Buffer[3]) ||
			( (FCode != 0x11) && (FCode != 0x33)))
			{
				return;
			}
			
			if (IDHi & 0x0F)
			{
				//清码
				ClearMem();
				//清行程
				f_Limit = 0;
				EE_WriteBYTE(ADDR_LIM_FLAG, f_Limit);
				EE_CheckReady();
				//确定转动方向
				if (FCode==0x11)
				{
					f_Reverse = 1;
				}
				else
				{
					f_Reverse = 0;
				}
				EE_WriteBYTE(ADDR_REVERSE_FLAG, f_Reverse);
				EE_CheckReady();
				EE_addr = ADDR_TABLE;
				WriteID();		// write Serial	Number in memory
				UpdateLPtr();
                                FLearn = LEARNOK;
			}
                        return;
		}
		
		if (FLearn == ADD_RF)
		{
                        if (FCode != 0x11)
			{
                                if ((FCode == 0xcc) && (IDHi & 0x0F))
                                {
                                      memcpy(IDBuffer, Buffer, 4);
                                      FLearn = MATCH_RF;
                                }
                                if (Find() == 0)
                                return;
                               
                                if(FCode == 0x55)
                                {
                                      FLearn = ENPLLUS;
                                }
                                
				return;
			}
			if ((Find() == 0)&& (IDHi & 0x0F))
			{
				EE_addr = EE_ReadInt(ADDR_LPTR) & 0x7FFF;	// read learn pointer
                                if(EE_addr >= ADDR_TABLE + EL_SIZE)
                                {
				      WriteID();		// write Serial	Number in memory
				      UpdateLPtr();
                                      FLearn = LEARNOK;
                                }
			}
		}	
	
                return;
		
	}
	else
	{
                
		  
                if ((FCode == 0xcc) && (IDHi & 0x0F) && f_Remotedelay)
		{
			memcpy(IDBuffer, Buffer, 4);
			FLearn = MATCH_RF;
                        return;
		}
                if (Find() == 0)
		{
		        return;
		}
		
		RemData = FCode;

		RemOutTime = T_REMOTEOUT;
                return;
	}
}

//=============================================================
// 获取遥控发射机按键信号，需要每10ms调用一次。
//
//-------------------------------------------------------------
unsigned char GetRemData(void)
{
  
	if (RemOutTime > 0)		// Remote output time
	{
		RemOutTime--;
		if (RemOutTime == 0)
		{
			RemData = 0;
		}
	}
       
	return RemData;
}

//==============================================================
// FIND Routine
//
// search through the whole table the given a record whose ID match
//
//	INPUT:		IDHi, IDMi,	IDLo,	serial number to search
//
// OUTPUT:		FCode_E		function code
//
// RETURN:		EE_addr if	matching record	 found
//				0 if matching record not found
//------------------------------------------------------------
unsigned char Find(void)
{
	unsigned int count;
	EE_data = EE_ReadInt(ADDR_LPTR);		//读取学习指针和存储满标志
	if (EE_data & 0x8000)		// 判断存储满标志
	{
		count = EL_SIZE * MAX_USER + ADDR_TABLE;
	}
	else
	{
		count = EE_data & 0x7FFF;
	}
	for (EE_addr = ADDR_TABLE; EE_addr < count; EE_addr += EL_SIZE)
	{
		wdt_reset();
		EE_data = EE_ReadInt(EE_addr);		// read	first Word
		if (((EE_data & 0xFF) == IDLo) && ((EE_data >> 8) == IDMi1))
		{
			EE_data = EE_ReadInt(EE_addr + (EL_SIZE/2));		  // read next unsigned	int
			if (((EE_data & 0xFF) == IDMi2) && (((EE_data >> 8) & 0xF0) == (IDHi & 0xF0)))
			{
				if (((IDHi & 0x0F) == 0) || ((EE_data >> 8) == IDHi))
				{
					return 1;
				}
			}
		}
	}
	return	0;
}

//============================================================
// update learn pointer
//		
//-----------------------------------------------------------
void UpdateLPtr(void)
{
	EE_data = EE_ReadInt(ADDR_LPTR);
	
	// 判断是否存储满MAX_USER个发射机
	if (((EE_data & 0x7FFF) + EL_SIZE) >= (EL_SIZE * MAX_USER + ADDR_TABLE))
	{
		EE_data = 0x8000 + ADDR_TABLE + EL_SIZE * (MAX_USER - 1);
	}
	else
	{
		EE_data += EL_SIZE;
	}
	EE_WriteInt(ADDR_LPTR,EE_data);
	EE_CheckReady();
}

//==========================================================
// Function IDWrite 
//	store IDHi,Mi,Lo at current address EE_addr
// INPUT:
//	EE_addr					point to record	+ offset 0 
//	IDHi, IDMi,	IDLo	Serial Number
// OUTPUT:
//---------------------------------------------------------
void WriteID(void)
{
	EE_data	= IDMi1;
	EE_data	= (EE_data << 8) + IDLo;
	EE_WriteInt(EE_addr, EE_data);				  // write first unsigned int
	EE_CheckReady();
	
	EE_data	= IDHi;
	EE_data	= (EE_data << 8) + IDMi2;
	EE_WriteInt(EE_addr + (EL_SIZE/2), EE_data);			  // write second unsigned int
	EE_CheckReady();
}

//============================================================
// Clear all records
//
//------------------------------------------------------------
void ClearMem(void)
{
	EE_WriteInt(ADDR_LPTR, ADDR_TABLE);
	EE_CheckReady();
}
