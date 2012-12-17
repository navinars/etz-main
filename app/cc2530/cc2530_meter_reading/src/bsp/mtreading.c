#include "includes.h"

unsigned char 	flag1=0,flag2=0;
unsigned int  	adcvalue,adcvalue2=0;


/* ------------------------------------------------------------------------------------------------------
 *												mac_init()
 *
 * Description : ADC init.
 *
 */
void SensorADCInit(void)
{
    APCFG |= 0x01;//通道0模拟输入
    ADCIF = 0;   //清楚中断标志，得试试是否是硬件清楚（好像是）
    ADCIE=1;
}

/* ------------------------------------------------------------------------------------------------------
 *												SensorADCBegin()
 *
 * Description : ADC convert start.
 *
 */
void SensorADCBegin(void)
{
    ADCCON1 = 0x73;//转换启动,选择的是ST=1时开始ADC
    ADCCON3 = 0x70;//VDD参考//ADCCON3 = 0x70;//外部AIN7参考电压//ADCCON3 = 0xB0;//VDD参考//ADCCON3 = 0x30;//内部参考电压
                   //通道0，采样率512，
}

/* ------------------------------------------------------------------------------------------------------
 *												ADC_ISR()
 *
 * Description : ADC ISR handle function.
 *
 */
#pragma vector = ADC_VECTOR 
__interrupt void ADC_ISR(void)
{
	adcvalue = (signed short)ADCL;//从ADCL,ADCH读取转换值,此操作还清零ADCCON1.EOC
	adcvalue|= (signed short)(ADCH<<8);
	adcvalue >>= 4;//取出12位有效位
	
/***将第二次获得的数同第一次的作比较保留最大值直到最大压差产生为止***/        
	if (flag2 == 0)
	{
		flag1 = 1;
		flag2 = 1;
		adcvalue2 = adcvalue;
	}
	if (flag1 == 1)
	{
		if(adcvalue < adcvalue2)
		{
			if ((adcvalue2 - adcvalue) >= 3)
			{
				flag1 = 0;
				flag2 = 0;
				
				adcvalue2 = 0;
				adcvalue = 0;
				
				// DOTO: Ready mac send frame.
			}
		}
		else
		{
			adcvalue2 = adcvalue;
		}
	}
	sysflag = SYS_FLAG_SLEEP_START;									/* Set flag is ADC mode.*/
}
