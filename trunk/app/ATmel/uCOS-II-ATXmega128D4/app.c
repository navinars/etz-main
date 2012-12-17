/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2008; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                             EXAMPLE CODE
*
*                                           Atmel  Xmega 128D3
*                                                on the
*                                         STK600 development kit
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
**************************************************************************************************************
*                                               INCLUDE FILES
**************************************************************************************************************
*/

#include  <includes.h>

/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/

#define  APP_SER_SCR_SIGN_ON                        1
#define  APP_SER_SCR_VER_TICK_RATE                  2
#define  APP_SER_SCR_CPU                            3
#define  APP_SER_SCR_CTXSW                          4

/*
**************************************************************************************************************
*                                               VARIABLES
**************************************************************************************************************
*/

static  OS_STK        App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_STK        App_TaskUserIFStk[APP_CFG_TASK_USER_IF_STK_SIZE];

static  OS_STK        App_TaskKbdStk[APP_CFG_TASK_KBD_STK_SIZE];

static  CPU_CHAR      App_SerOut[80];

static  CPU_INT08U    App_UserIFState;                         
static  OS_EVENT     *App_UserIFMbox;


#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
static  CPU_INT32U    App_ProbeCnts;
static  CPU_INT08U    App_ProbePB[8];
#endif


/*
**************************************************************************************************************
*                                           FUNCTION PROTOTYPES
**************************************************************************************************************
*/

static  void          App_TaskCreate           (void);
static  void          App_EventCreate          (void);

static  void          App_TaskStart            (void       *p_arg);

static  void          App_TaskUserIF           (void       *p_arg);
static  void          App_TaskKbd              (void       *p_arg);

static  void          App_DispScr_SignOn       (void);
static  void          App_DispScr_VerTickRate  (void);
static  void          App_DispScr_CPU          (void);
static  void          App_DispScr_CtxSw        (void);

static  void          App_FormatDec            (CPU_INT08U *s, 
                                                CPU_INT32U  value, 
							                    CPU_INT08U  digits);

#if (APP_CFG_PROBE_COM_EN       == DEF_ENABLED) || \
    (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
static  void          App_ProbeInit            (void);
#endif


#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_TRUE)
static  void          App_ProbeCallback        (void);
#endif


/*$PAGE*/
/*
**************************************************************************************************************
*                                                MAIN
**************************************************************************************************************
*/

int  main (void)
{
    CPU_INT08U  os_err;


    BSP_IntDisAll();                                            /* Disable all interrupts until we are ready to accept them */

    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt((void (*)(void *)) App_TaskStart,           /* Create the start task                                    */
                    (void           *) 0,
                    (OS_STK         *)&App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_START_PRIO,
                    (INT16U          ) APP_CFG_TASK_START_PRIO,
                    (OS_STK         *)&App_TaskStartStk[0],
                    (INT32U          )(APP_CFG_TASK_START_STK_SIZE),
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_SIZE > 5)
    OSTaskNameSet(APP_CFG_TASK_START_PRIO, (CPU_CHAR *)"Start", &os_err);
#else
    (void)err;        
#endif
    
    
    OSStart();                                                          /* Start multitasking (i.e. give control to uC/OS-II)       */
	
	return (0);
}


/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description: This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments  : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Return(s)  : This is a task.
*
* Caller(s)  : This is a task.
*
* Note(s)    : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                 used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static void  App_TaskStart (void *p_arg)
{
//    CPU_INT08U  i;


    (void)p_arg;                                                /* Prevent compiler warnings                                */

    BSP_Init();                                                 /* Initialize the BSP                                       */

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                                   */
#endif

#if (APP_CFG_PROBE_COM_EN       == DEF_ENABLED) || \
    (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
    App_ProbeInit();                                            /* Initialize uC/Probe modules                              */
#endif

    App_TaskCreate();                                           /* Create the application tasks                             */
    App_EventCreate();                                          /* Create the application events                            */

    BSP_Ser_Init(115200);                                       
    
	BSP_LED_Off(4);
	
    while (1) {                                                 /* Task body, always written as an infinite loop.           */

            BSP_LED_On(3);
            OSTimeDlyHMSM(0, 0, 0, 100);
            BSP_LED_Off(3);
            OSTimeDlyHMSM(0, 0, 0, 100);
    }
}


/*
**************************************************************************************************************
*                                           App_TaskCreate()
*
* Description : This function creates the application tasks.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskStart()
*
* Note(s)     : none.
*                 
**************************************************************************************************************
*/
static  void  App_TaskCreate (void)
{
    CPU_INT08U  os_err;
    
    OSTaskCreateExt((void (*)(void *)) App_TaskUserIF,
                    (void           *) 0,
                    (OS_STK         *)&App_TaskUserIFStk[APP_CFG_TASK_USER_IF_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_USER_IF_PRIO,
                    (INT16U          ) APP_CFG_TASK_USER_IF_PRIO,
                    (OS_STK         *)&App_TaskUserIFStk[0],
                    (INT32U          ) APP_CFG_TASK_USER_IF_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_SIZE > 13)
    OSTaskNameSet(APP_CFG_TASK_USER_IF_PRIO, (CPU_CHAR *)"User I/F", &os_err);
#endif

    OSTaskCreateExt((void (*)(void *)) App_TaskKbd,
                    (void           *) 0,
                    (OS_STK         *)&App_TaskKbdStk[APP_CFG_TASK_KBD_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_KBD_PRIO,
                    (INT16U          ) APP_CFG_TASK_KBD_PRIO,
                    (OS_STK         *)&App_TaskKbdStk[0],
                    (INT32U          ) APP_CFG_TASK_KBD_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if (OS_TASK_NAME_SIZE > 13)
    OSTaskNameSet(APP_CFG_TASK_KBD_PRIO, (CPU_CHAR *)"Keyboard", &os_err);
#endif
    
#if (OS_TASK_NAME_SIZE < 13)
    (void)os_err;
#endif    
}

/*
**************************************************************************************************************
*                                            App_EventCreate()
*
* Description : This function creates the application events.
*
* Argument(s) : none.
*
* Caller(s)   : App_TaskStart()
*
* Return(s)   : none. 
*
* Note(s)     : none.
**************************************************************************************************************
*/

static  void  App_EventCreate (void)
{
#if (OS_EVENT_NAME_SIZE > 8)
	CPU_INT08U  os_err;
#endif
    
    App_UserIFMbox = OSMboxCreate((void *)0);                   /* MBOX for comm between App_TaskKbd() and App_TaskUserIF()  */

#if (OS_EVENT_NAME_SIZE > 8)
    OSEventNameSet(App_UserIFMbox, (CPU_CHAR *)"User I/F", &os_err);
#endif   

}

/*
*********************************************************************************************************
*                                            App_TaskKbd()
*
* Description : This task monitors the state of the push buttons and passes messages to App_TaskUserIF()
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskKbd()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
* 
* Caller(s)   : This is a Task.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_TaskKbd (void *p_arg)
{
    CPU_BOOLEAN  b1;                                            /* State of Push Button #1                                  */
    CPU_BOOLEAN  b1_prev;
    CPU_BOOLEAN  b2;
    CPU_BOOLEAN  b2_prev;
    CPU_BOOLEAN  b3;
    CPU_BOOLEAN  b3_prev;
    CPU_BOOLEAN  b4;
    CPU_BOOLEAN  b4_prev;


    (void)p_arg;
    b1_prev = DEF_FALSE;
    b2_prev = DEF_FALSE;
    b3_prev = DEF_FALSE;
    b4_prev = DEF_FALSE;
    
    while (DEF_TRUE) {

        b1  = BSP_PB_GetStatus(0);
        b2  = BSP_PB_GetStatus(1);
        b3  = BSP_PB_GetStatus(2);
        b4  = BSP_PB_GetStatus(3);

        if (b1 == DEF_TRUE && b1_prev == DEF_FALSE) {
            App_UserIFState = APP_SER_SCR_SIGN_ON;
            OSMboxPost(App_UserIFMbox, &App_UserIFState);
        }

        if (b2 == DEF_TRUE && b2_prev == DEF_FALSE) {
            App_UserIFState = APP_SER_SCR_VER_TICK_RATE;
            OSMboxPost(App_UserIFMbox, &App_UserIFState);
        }

        if (b3 == DEF_TRUE && b3_prev == DEF_FALSE) {
            App_UserIFState = APP_SER_SCR_CPU;
            OSMboxPost(App_UserIFMbox, &App_UserIFState);
        }

        if (b4 == DEF_TRUE && b4_prev == DEF_FALSE) {
            App_UserIFState = APP_SER_SCR_CTXSW;
            OSMboxPost(App_UserIFMbox, &App_UserIFState);
        }

        b1_prev = b1;
        b2_prev = b2;
        b3_prev = b3;
        b4_prev = b4;
        
        OSTimeDly(OS_TICKS_PER_SEC / 20);
    }
}


/*
*********************************************************************************************************
*                                         App_TaskUserIF
*
* Description : This task updates the Terminal Output screen based on messages passed to it by App_TaskKbd().
*
* Argument(s) : p_arg   is the argument passed to 'AppStartUserIF()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  App_TaskUserIF (void *p_arg)
{
    CPU_INT08U     *msg;
    CPU_INT08U      err;
    CPU_INT32U      ser_scr;


    (void)p_arg;

    BSP_Ser_WrStr((CPU_CHAR *)"\n\n\r");
    
	App_DispScr_SignOn();
    
	BSP_Ser_WrStr((CPU_CHAR *)"\n\n\r");
    
	OSTimeDly(OS_TICKS_PER_SEC);
    
    ser_scr = APP_SER_SCR_VER_TICK_RATE;

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.           */
        msg = (CPU_INT08U *)(OSMboxPend(App_UserIFMbox, OS_TICKS_PER_SEC / 10, &err));
        if (err == OS_NO_ERR) {
            if (msg != (CPU_INT08U *)0) {
                ser_scr = *msg;
                
				BSP_Ser_WrStr((CPU_CHAR *)"\n\n\r");    
            }
        }

        switch (ser_scr) {
            case APP_SER_SCR_VER_TICK_RATE:
                 App_DispScr_VerTickRate();
                 break;

            case APP_SER_SCR_CPU:
                 App_DispScr_CPU();
                 break;

            case APP_SER_SCR_CTXSW:
                 App_DispScr_CtxSw();
                 break;
              
            default:            
            case APP_SER_SCR_SIGN_ON:
                 App_DispScr_SignOn();
                 break;

        }
    }
}

/*
*********************************************************************************************************
*                                            App_DispScr_SignOn()
*                                          App_DispScr_VerTickRate()
*                                              App_DispScr_CPU()
*                                             App_DispScr_CtxSw()
*
* Descrition  : These functions each display one of the screens used in the demonstration.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskUserIF()
*
* Note(s)     : none.
*********************************************************************************************************
*/


static  void  App_DispScr_SignOn (void)
{
    Str_Copy(&App_SerOut[0],(CPU_CHAR *)"Micrium uC/OS-II on the ATMEL XMEGA 128A1 - STK600 \r");
	
	BSP_Ser_WrStr(&App_SerOut[0]);
	
}

static  void  App_DispScr_VerTickRate (void)
{
    CPU_INT32U  val;


    Str_Copy(&App_SerOut[0], (CPU_CHAR *)"uC/OS-II:  Vx.yy  TickRate: xxxx \r");
    
	val            = (CPU_INT32U)OSVersion();
    App_SerOut[12] = (val      ) / 100 + '0';
    App_SerOut[14] = (val % 100) /  10 + '0';
    App_SerOut[15] = (val %  10) /   1 + '0';   
    val           = (CPU_INT32U)OS_TICKS_PER_SEC;
    
	App_FormatDec(&App_SerOut[28], val, 4);
    
	BSP_Ser_WrStr(&App_SerOut[0]);

}

static  void  App_DispScr_CPU (void)
{
    CPU_INT32U  val;


    Str_Copy(&App_SerOut[0], (CPU_CHAR *)"CPU Usage:xx CPU Speed:xxx MHz \r");
    val               = (CPU_INT32U)OSCPUUsage;
    App_SerOut[10]    = (val / 10) + '0';
    App_SerOut[11]    = (val % 10) + '0';
    
	val               = (CPU_INT32U)BSP_CPU_ClkFreq() / 1000000L;
    App_FormatDec(&App_SerOut[23], val, 3);
	BSP_Ser_WrStr(&App_SerOut[0]);
}

static  void  App_DispScr_CtxSw (void)
{
    CPU_INT32U  val;


    Str_Copy(&App_SerOut[0],(CPU_CHAR *)"#Ticks: xxxxxxxxx #CtxSw: xxxxxxxxx \r");
    
	val = (CPU_INT32U)OSTime;
    
	App_FormatDec(&App_SerOut[8], val, 9);    
	val = (CPU_INT32U)OSCtxSwCtr;
    
	App_FormatDec(&App_SerOut[26], val, 9);
    BSP_Ser_WrStr(&App_SerOut[0]);
}

/*
*********************************************************************************************************
*                                            App_FormatDec()
*
* Description: This function converts a decimal value to ASCII (with leading zeros)
*
* Argument(s): s       is a pointer to the destination ASCII string
*              value   is the value to convert (assumes an unsigned value)
*              digits  is the desired number of digits
*
* Return(s)  : none
*
* Caller(s)  : Display Screen funcitons.
*
* Note(s)    : None. 
*********************************************************************************************************
*/

static  void  App_FormatDec (CPU_INT08U *s, 
                             CPU_INT32U  value, 
							 CPU_INT08U  digits)
{
    CPU_INT08U      i;
    CPU_INT32U      mult;


    mult        = 1;
    for (i = 0; i < (digits - 1); i++) {
        mult   *= 10;
    }
    while (mult > 0) {
        *s++    = value / mult + '0';
        value  %= mult;
        mult   /= 10;
    }
}
/*
*********************************************************************************************************
*                                            App_ProbeInit()
*
* Description: This function initializes the modules required for uC/Probe.
*
* Arguments  : none.
*
* Return(s)  : none.
*
* Caller(s)  : App_TaskStart().
*
* Note(s)    : none.
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_COM_EN       == DEF_ENABLED) || \
    (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
void  App_ProbeInit (void)
{
#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
    (void)App_ProbeCnts;
	(void)App_ProbePB;


    OSProbe_Init();
    OSProbe_SetCallback(App_ProbeCallback);
    OSProbe_SetDelay(50);
#endif

    ProbeCom_Init();                                                    /* Initialize the uC/Probe communications module            */

#if (PROBE_COM_CFG_RS232_EN == DEF_ENABLED)
    ProbeRS232_Init(115200);
    ProbeRS232_RxIntEn();
#endif

}
#endif

    
/*
*********************************************************************************************************
*                                          App_ProbeCallback()
*
* Description : This function is called by the uC/Probe uC/OS-II plug-in after updating task information.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : OSProbe_Task()
*
* Note(s)     : none.
*********************************************************************************************************
*/


#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED)
static  void  App_ProbeCallback (void)
{

    App_ProbeCnts++;
	App_ProbePB[0] = BSP_PB_GetStatus(0);
	App_ProbePB[1] = BSP_PB_GetStatus(1);
    App_ProbePB[2] = BSP_PB_GetStatus(2);
    App_ProbePB[3] = BSP_PB_GetStatus(3);
    App_ProbePB[4] = BSP_PB_GetStatus(4);
    App_ProbePB[5] = BSP_PB_GetStatus(5);
    App_ProbePB[6] = BSP_PB_GetStatus(6);
    App_ProbePB[7] = BSP_PB_GetStatus(7);    

}
#endif

/*
*********************************************************************************************************
*********************************************************************************************************
**                                         uC/OS-II APP HOOKS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          App_TaskCreateHook()
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

#if (OS_APP_HOOKS_EN > 0)
void  App_TaskCreateHook (OS_TCB *ptcb)
{
#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TaskCreateHook(ptcb);
#else
    (void)ptcb;
#endif
}

/*
*********************************************************************************************************
*                                           App_TaskDelHook()
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void  App_TaskDelHook (OS_TCB *ptcb)
{
    (void)ptcb;
}

/*
*********************************************************************************************************
*                                             App_TaskIdleHook()
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void  App_TaskIdleHook (void)
{
}
#endif

/*
*********************************************************************************************************
*                                   App_TaskStatHook()
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Returns    : none
*********************************************************************************************************
*/

void  App_TaskStatHook (void)
{
}

/*
*********************************************************************************************************
*                                           App_TaskSwHook()
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void  App_TaskSwHook (void)
{
#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TaskSwHook();
#endif
}
#endif

/*
*********************************************************************************************************
*                                           App_TCBInitHook()
*
* Description: This function is called by OS_TCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void  App_TCBInitHook (OS_TCB *ptcb)
{
    (void)ptcb;
}
#endif

/*
*********************************************************************************************************
*                                               App_TimeTickHook()
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_TIME_TICK_HOOK_EN > 0
void  App_TimeTickHook (void)
{
#if (APP_CFG_PROBE_OS_PLUGIN_EN == DEF_ENABLED) && (OS_PROBE_HOOKS_EN > 0)
    OSProbe_TickHook();
#endif
}
#endif

#endif
