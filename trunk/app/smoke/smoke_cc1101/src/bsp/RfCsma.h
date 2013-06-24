/* ********************************************************************** *
 *                           DOOYA Company                                *
 * The Tree of the NetWork Design Basic CC1101                            *
 * Compiler : MPLAB IDE V8.66                                             *
 * Crystal  : 32MHZ                                                       *
 * MCU      : PIC24FJ128GA106                                             *
 * FileName : RfCsma.h                                                    *
 * Author   : Softli                                                      *
 * Address  : NingBo                                                      *
 * Time     : 2012-12-21                                                  *
 * Version  : V1.0                                                        *
 * Testing                                                                *
 * ********************************************************************** */
 
 #ifndef _Rf_Wirless_CSMA_H_
 #define _Rf_Wirless_CSMA_H_
 
 #ifdef __cplusplus
    extern "C" {
 #endif

 //include head files...
 #include "../Components/Hal/RfTranceiver.h"
 
/* ============================================ *
 *                    Defines                   * 
 * ============================================ */
 //csma
 #ifdef  CSMA_CA
    //wait for period
    #define CONTENTION_PERIOD         40.96
    
    //csma counter
    #define  CSMA_COUNT               16
 #endif
 
 //turn on transmit busy led
 #ifdef Zigbee_Busy_Led_On
     //csms led on
     #define Rf_Csma_Status_On        Zigbee_Busy_Led_On
 #else
     #define Rf_Csma_Status_On
 #endif
 
 //turn off transmit busy led
 #ifdef Zigbee_Busy_Led_Off
     //csma led off 
     #define Rf_Csma_Status_Off       Zigbee_Busy_Led_Off
 #else
     #define Rf_Csma_Status_Off
 #endif
 
/* ============================================== *
 *            function declaration                *
 * ============================================== */
 //�õ�min ��max֮���һ�������
 unsigned int GetRand(unsigned int min,unsigned int max);

 //����K����
 unsigned int TwoPowerK(unsigned char k);

 //��i���ش�����,�����ش��˱�ʱ��,�ȴ��ش�
 unsigned int ReSendBackTime(unsigned char i);

 //random product number  
 unsigned int Get_Random_Number(void);

 //rf cc1101 PhyLayer CSMA
 Bool Csma_Channel_Detection(unsigned char times);

 #ifdef __cplusplus
    }
 #endif

 #endif
