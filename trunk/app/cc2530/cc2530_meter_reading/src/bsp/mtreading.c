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
    APCFG |= 0x01;//ͨ��0ģ������
    ADCIF = 0;   //����жϱ�־���������Ƿ���Ӳ������������ǣ�
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
    ADCCON1 = 0x73;//ת������,ѡ�����ST=1ʱ��ʼADC
    ADCCON3 = 0x70;//VDD�ο�//ADCCON3 = 0x70;//�ⲿAIN7�ο���ѹ//ADCCON3 = 0xB0;//VDD�ο�//ADCCON3 = 0x30;//�ڲ��ο���ѹ
                   //ͨ��0��������512��
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
	adcvalue = (signed short)ADCL;//��ADCL,ADCH��ȡת��ֵ,�˲���������ADCCON1.EOC
	adcvalue|= (signed short)(ADCH<<8);
	adcvalue >>= 4;//ȡ��12λ��Чλ
	
/***���ڶ��λ�õ���ͬ��һ�ε����Ƚϱ������ֱֵ�����ѹ�����Ϊֹ***/        
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
