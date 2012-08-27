/*
*********************************************************************************************************
*
*                                          lm3s8963-GainSpan/Main
*                                            INTRODUCTION DEMO
*
*
* Filename      : main.c
* Version       : V0.01
* Programmer(s) : MC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include "includes.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

/*
*********************************************************************************************************
*                                         LOCAL FUNCIONS
*********************************************************************************************************
*/



/********************************************************************************************************
*                                             main()
*
* Description : main function.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*/
int main(void)
{
	char tmp[10];
	
	/* 使能CPU频率为25MHz*/
    SysCtlClockSet(SYSCTL_SYSDIV_8 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ);
	
	RIT128x96x4Init(1000000);
	
    /* 使能总中断*/
	IntMasterEnable();
	
	BSP_Uart_Init(BSP_SER_ID_UART0, 9600, false, false);
	
	/*初始化Timer_1,用于硬延时*/
	BSP_Timer0_Init();
	
	/* 初始化GainSpan*/
	if (GP_AC_Init() == 1) {
		RIT128x96x4StringDraw("Link GP success", 18, 24, 15);
		if (GP_Tcp_Assoc() == 1)
		{
			sprintf(tmp, "UID is %4c", AtLib_GetTcpCid());
			RIT128x96x4StringDraw(tmp, 32, 32, 15);
		}
		else
		{
			RIT128x96x4StringDraw("UID gets failure", 16, 32, 15);
		}
	} else {
		RIT128x96x4StringDraw("Link GP faile", 18, 24, 15);
	}
	
	while(1)
	{
		GP_Check();
	}
}


