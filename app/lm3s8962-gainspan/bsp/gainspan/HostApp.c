/******************************************************************************
* DISCLAIMER:
* The software supplied by GainSpan Corporation is
* intended and supplied for use on GainSpan products.
* This software is owned by GainSpan Corporation and
* is protected under applicable
* copyright laws. All rights are reserved.
*
* THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS,
* IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* APPLY TO THIS SOFTWARE. GAINSPAN CORPORATION SHALL NOT
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
* CONSEQUENTIAL DAMAGES FOR ANY REASON WHATSOEVER ARISING OUT OF THE
* USE OR APPLICATION OF THIS SOFTWARE.
******************************************************************************/

/* Copyright (C) 2011. GainSpan Corporation, All Rights Reserved */

/******************************************************************************
* File Name	: HostApp.c
* Version 	: 1.00
* Device 	: PIC24FJ128GA010 
* Tool Chain 	: C30
* H/W Platform	: Explorer 16 Development Board
* Description 	: S2WIFI Master Application demo.
* Note: Please review Errata sheet 80471a, UART and SPI affected !!!
******************************************************************************/
//#include "p24fxxxx.h"
#include <stdio.h>
#include <ctype.h>
#include "HostApp.h"
#include "AtCmdLib.h"
#include "hal_uart.h"
#include "hal_mcu.h"


/*******************************************************************************
User Program Code
*******************************************************************************/


/****************< Global variables section >***********************************/
UINT8  gHostAppBuffer[HOST_APP_TX_MAX_APP_BUFFER_SIZE]; /* Host Application buffer */

/****************< End of Global variables section >*****************************/

 
/**************< Host application helper functions >*********************************/
UINT32
hostApp_GetApplicationData(INT8 *pBuffer,UINT32 dataLen,HOST_APP_TX_DATA_TYPE_E appDataType)
{
    /* Note: For demo purpose dummy data is filled for transmission. Contains only ASCII value.
     *       If application data contains below listed octets,  then byte stuffing must be applied, before sending over SPI interface.
     *       0x00, 0xF3,0xF5,0xFA,0xFB,0xFD,0xFF   (all values are in HEX)
     */

 static   UINT32  tcpPktCount=1;
 static   UINT32  udpPktCount=1;

 UINT32 count=0;
	
	if(16 > dataLen)
	{
	  appDataType = HOST_APP_TX_DATA_TYPE_MAX;
	}

	switch(appDataType)
	{
		
		case HOST_APP_TX_DATA_TYPE_TCP:
		 {/* Note: You can add your own transmit data here */
		   count=0;
		   /* Fill start pattern */
		   pBuffer[count++]='<';
		   pBuffer[count++]='#';

		    /* Fill packet number */
			AtLib_ConvertNumberTo4DigitASCII(tcpPktCount,&(pBuffer[count]));
		    count +=4;

		    /* Fill packet length */
		    pBuffer[count++]='-';

			AtLib_ConvertNumberTo4DigitASCII(dataLen,&(pBuffer[count]));
			
	  	    count +=4;

		   /* Fill packet identifier  */
		   pBuffer[count++]='-';
		   pBuffer[count++]='T';
		   pBuffer[count++]='C';
		   pBuffer[count++]='P';
		   pBuffer[count++]='-';

		   /* Filling Some Dummy Data for Tx */
		   for(; count <(dataLen-5); count++)
		   {
			   pBuffer[count]= 'T';
		   }

		   /* Fill packet end pattern   */
		   pBuffer[count++]='-';
		   pBuffer[count++]='E';
		   pBuffer[count++]='N';
		   pBuffer[count++]='D';
		   pBuffer[count++]='>';
		   pBuffer[count] = '>';

		  tcpPktCount++;
		  if(tcpPktCount>=9999)
		  {
			  tcpPktCount=1;  
		  }
		}	  
		break;
		
		case HOST_APP_TX_DATA_TYPE_UDP:
		 {/* Note: You can add your own transmit data here */
		   count=0;
		   /* Fill start pattern */
		   pBuffer[count++]='<';
		   pBuffer[count++]='#';

		   AtLib_ConvertNumberTo4DigitASCII(udpPktCount,&(pBuffer[count]));
			
		   count +=4;

		    /* Fill packet length */
		    pBuffer[count++]='-';
			
			AtLib_ConvertNumberTo4DigitASCII(dataLen,&(pBuffer[count]));

		    count +=4;

		    /* Fill packet identifier  */
		   pBuffer[count++]='-';
		   pBuffer[count++]='U';
		   pBuffer[count++]='D';
		   pBuffer[count++]='P';
		   pBuffer[count++]='-';

		   /* Filling Some Dummy Data for Tx */
		   for(; count <(dataLen-5); count++)
		   {
			   pBuffer[count]= 'U';
		   }

		    /* Fill packet end pattern   */
		   pBuffer[count++]='-';
		   pBuffer[count++]='E';
		   pBuffer[count++]='N';
		   pBuffer[count++]='D';
		   pBuffer[count++]='>';
		   pBuffer[count] = '>';

		  udpPktCount++;
		  if(udpPktCount>=9999)
		  {
			  udpPktCount=0;  
		  }
		}	  
		break;


	default:
		/* Filling Some Dummy Data for Tx */
	   for(count=0; count <dataLen; count++)
	   {
		   pBuffer[count]= HOST_APP_FILL_DUMMY_DATA;
	   }
	   
	   pBuffer[count] = '>';

		break;
		
	}


	return count;
}


void my_delay_ms(int cnt)
{
	halMcuWaitUs(1000);
}


UINT8 PIC24_GetHostWakeUpStatus()
{
	return 1;
}


/******************************************************************************
End of function main
******************************************************************************/
