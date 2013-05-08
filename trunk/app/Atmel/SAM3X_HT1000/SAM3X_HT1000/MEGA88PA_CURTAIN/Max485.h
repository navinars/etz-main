
extern void USART_Init(void);
extern unsigned char USART_Transmit( unsigned char data );
extern unsigned char USART_Receive( void );
//extern unsigned char USART_Flush( void );
extern unsigned char Crc8CheckSum(unsigned char *ptr, unsigned char length);
extern void max485_tarns(void);
#define	ADDR_ID   	        0x16	// 485 IDµÿ÷∑
