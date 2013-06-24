/* ********************************************************************** *
 *                           DOOYA Company                                *
 * The Tree of the NetWork Design Basic CC1101                            *
 * Compiler : MPLAB IDE V8.66                                             *
 * Crystal  : 32MHZ                                                       *
 * MCU      : PIC24FJ128GA106                                             *
 * FileName : RfCsma.c                                                    *
 * Author   : Softli                                                      *
 * Address  : NingBo                                                      *
 * Time     : 2012-12-21                                                  *
 * Version  : V1.0                                                        *
 * Testing                                                                *
 * ********************************************************************** */
 
 //include header files
 #include "stdlib.h"
 #include "p24fj64ga002.h"
 #include "../Common/Common.h"
 #include "../Common/Hal_StaTsk.h"
 #include "../Common/Hal_Defs.h"
 #include "../Components/Hal/MCUConfig.h"
 #include "../Components/Hal/SystemTime.h"
 #include "../Components/Hal/RfTranceiver.h"
 #include "../Components/Phy/RfCsma.h"
 #include "../Components/Phy/RfPhysics.h"

/* ============================================ *
 *           random product number              *
 * ============================================ */
 unsigned int Get_Random_Number(void)
 {
    unsigned int    Random;
    ZTIME_TICK      TimePoint;
    //get the current time point
    TimePoint = SystemTimeTickGet();
    //rand seed  
    srand(TimePoint.Val);
    Random = rand();
    return Random;
 }

 //得到min 到max之间的一个随机数
 unsigned int GetRand(unsigned int min,unsigned int max)
 {
    unsigned int    random;
    ZTIME_TICK      TimePoint;
    //get the current time point
    TimePoint=SystemTimeTickGet();
    //rand seed  
    srand(TimePoint.Val);
    random=rand()%(max-min + 1) + min;
    return random;
 }

 //二的K次幂
 unsigned int TwoPowerK(unsigned char k)
 {
    unsigned int   i = 1;
    while(k--)
    {
       i <<= 1;
    }
    return i;
 }

 //第i次重传操作,计算重传退避时间,等待重传
 unsigned int ReSendBackTime(unsigned char i)
 {
    unsigned int random,Max;
    unsigned int BackTime;
    if(i <= 9)
    {
        Max = TwoPowerK(i)-1;
    }
    else
    {
        Max = TwoPowerK(9)-1;
    }
    random   = GetRand(0,Max);
    BackTime = random * CONTENTION_PERIOD;

    return BackTime;
 }
 
/* ============================================ *
 *            rf cc1101 PhyLayer CSMA           *
 * ============================================ */
 Bool Csma_Channel_Detection(unsigned char times)
 {
    //rf csma is enable
    #ifdef CSMA_CA
        unsigned char i = 0;
	    for(;i<times;i++)
        {
            unsigned char retryCount;
            for(retryCount=0;retryCount<CSMA_COUNT;retryCount++)
            {
                //if waitchdog enable
                #ifdef WATCH_DOG
                    //reset watchdog
                    RstWatchdog;
                #endif
                //if channel clean ,break;
                if(!Check_Csma_Level)
                {
                    break;
                }
                else
                {
                    unsigned int Random;

                    //csma status led on
                    Rf_Csma_Status_On;
                    Random=ReSendBackTime(retryCount);
                    //delay n* 100us 
                    _delay_100us(Random);
                    //csma status led off
                    Rf_Csma_Status_Off;
                }
            }
            if(retryCount == CSMA_COUNT)
            {
                if(times == 0)
                {
                    return False; 
                }
            }
			//signal below set value on the air....
			else
			{
			    return True;
			}
        }
    #endif

	//no csma
	return True;
 }
