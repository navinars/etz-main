/**
 * @file - sys_arch.c
 * System Architecture support routines for Stellaris devices.
 *
 */

/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/* Copyright (c) 2008 Texas Instruments Incorporated */

/* lwIP includes. */
#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/def.h"
#include "lwip/mem.h"

#include "arch/cc.h"
#include "arch/sys_arch.h"

#if NO_SYS

#if SYS_LIGHTWEIGHT_PROT

/* Stellaris header files required for this interface driver. */
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

/**
 * This function is used to lock access to critical sections when lwipopt.h
 * defines SYS_LIGHTWEIGHT_PROT. It disables interrupts and returns a value
 * indicating the interrupt enable state when the function entered. This
 * value must be passed back on the matching call to sys_arch_unprotect().
 *
 * @return the interrupt level when the function was entered.
 */
sys_prot_t
sys_arch_protect(void)
{
  return((sys_prot_t)MAP_IntMasterDisable());
}

/**
 * This function is used to unlock access to critical sections when lwipopt.h
 * defines SYS_LIGHTWEIGHT_PROT. It enables interrupts if the value of the lev
 * parameter indicates that they were enabled when the matching call to
 * sys_arch_protect() was made.
 *
 * @param lev is the interrupt level when the matching protect function was
 * called
 */
void
sys_arch_unprotect(sys_prot_t lev)
{
  /* Only turn interrupts back on if they were originally on when the matching
     sys_arch_protect() call was made. */
  if(!(lev & 1)) {
    MAP_IntMasterEnable();
  }
}
#endif /* SYS_LIGHTWEIGHT_PROT */

#else /* NO_SYS */

static OS_MEM *pQueueMem;

const void * const pvNullPointer = (mem_ptr_t*)0xffffffff;

static char pcQueueMemoryPool[MAX_QUEUES * sizeof(TQ_DESCR) + MEM_ALIGNMENT - 1];

OS_STK LWIP_TASK_STK[LWIP_TASK_MAX][LWIP_STK_SIZE];

struct sys_timeouts lwip_timeouts[LWIP_TASK_MAX];
struct sys_timeouts null_timeouts;

/**
 * Initializes the system architecture layer.
 *
 */
void
sys_init(void)
{
	u8_t i, ucErr;
	
	pQueueMem = OSMemCreate((void *)((u32_t)((u32_t)pcQueueMemoryPool+MEM_ALIGNMENT-1) & 
				~(MEM_ALIGNMENT-1)),
				MAX_QUEUES, sizeof(TQ_DESCR), &ucErr);
	LWIP_ASSERT( "OSMemCreate ", ucErr == OS_NO_ERR );

	for(i = 0;i < LWIP_TASK_MAX;i ++)
	{
		lwip_timeouts[i].next = NULL;
	}
}

/**
 * Creates a new semaphore.
 *
 * @param count is non-zero if the semaphore should be acquired initially.
 * @return the handle of the created semaphore.
 */
err_t
sys_sem_new(sys_sem_t *sem, u8_t count)
{
	*sem = OSSemCreate((u16_t)count);

	if(*sem == ((OS_EVENT *) 0))
		return ERR_MEM;

	return ERR_OK;
}

/**
 * Signal a semaphore.
 *
 * @param sem is the semaphore to signal.
 */
void
sys_sem_signal(sys_sem_t *sem)
{
	OSSemPost(*sem);
}

/**
 * Destroys a semaphore.
 *
 * @param sem is the semaphore to be destroyed.
 */
void
sys_sem_free(sys_sem_t *sem)
{
	u8_t err;
	
	OSSemDel(*sem, OS_DEL_ALWAYS, &err);
}

void sys_sem_set_invalid(sys_sem_t *sem)
{
	*sem = SYS_SEM_NULL ;	 
}

int sys_sem_valid(sys_sem_t *sem)
{	 
      return (int)(*sem); 
}

/**
 * Wait for a semaphore to be signalled.
 *
 * @param sem is the semaphore
 * @param timeout is the maximum number of milliseconds to wait for the
 *        semaphore to be signalled
 * @return the number of milliseconds that passed before the semaphore was
 *         acquired, or SYS_ARCH_TIMEOUT if the timeout occurred
 */
u32_t
sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
    u8_t ucErr;
    u32_t ucos_timeout, timeout_new;
    
    // timeout 单位以ms计 转换为ucos_timeout 单位以TICK计
    if(	timeout != 0)
    {
        ucos_timeout = (timeout * OS_TICKS_PER_SEC) / 1000; // convert to timetick
        if(ucos_timeout < 1)
            ucos_timeout = 1;
        else if(ucos_timeout > 65536) // uC/OS only support u16_t pend
            ucos_timeout = 65535; // 最多等待TICK数 这是uC/OS所能 处理的最大延时
    }
    else
		ucos_timeout = 0;
    
    timeout = OSTimeGet(); // 记录起始时间
    
    OSSemPend (*sem, (u16_t)ucos_timeout, (u8_t *)&ucErr);
    
    if(ucErr == OS_TIMEOUT)
        timeout = SYS_ARCH_TIMEOUT;	// only when timeout!
    else
    {    
    	//LWIP_ASSERT( "OSSemPend ", ucErr == OS_NO_ERR );
        //for pbuf_free, may be called from an ISR
        
        timeout_new = OSTimeGet(); // 记录终止时间
        if (timeout_new >= timeout)
			timeout_new = timeout_new - timeout;
        else
			timeout_new = 0xffffffff - timeout + timeout_new;
        
        timeout = (timeout_new * 1000 / OS_TICKS_PER_SEC + 1); //convert to milisecond 为什么加1？
    }
    
    return timeout;

}

/**
 * Creates a new mailbox.
 *
 * @param size is the number of entries in the mailbox.
 * @return the handle of the created mailbox.
 */
err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
	u8_t 		err;
	
	*mbox = (sys_mbox_t)OSMemGet(pQueueMem, &err);

	if(err == OS_NO_ERR)
	{
		if(size > MAX_QUEUE_ENTRIES)
			size = MAX_QUEUE_ENTRIES;

		//创建消息队列
		(*mbox)->pQ = OSQCreate(&((*mbox)->pvQEntries[0]), size);

		if((*mbox)->pQ != NULL)
			return ERR_OK;
		else
		{
			err = OSMemPut(pQueueMem, *mbox);//释放内存块
			*mbox = SYS_MBOX_NULL;
			return ERR_MEM;
		}
	}
	else
		return ERR_MEM;
}

int sys_mbox_valid(sys_mbox_t *mbox)
{
	return (int)(*mbox);
}

void sys_mbox_set_invalid(sys_mbox_t *mbox)
{

    *mbox = SYS_MBOX_NULL;		 
}

/**
 * Sends a message to a mailbox.
 *
 * @param mbox is the mailbox
 * @param msg is the message to send
 */
void
sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
	if(msg == NULL)
		msg = (void *)&pvNullPointer;

	OSQPost((*mbox)->pQ, msg);
}

/**
 * Tries to send a message to a mailbox.
 *
 * @param mbox is the mailbox
 * @param msg is the message to send
 * @return ERR_OK if the message was sent and ERR_MEM if there was no space for
 *         the message
 */
err_t
sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
	if(msg == NULL)
		msg = (void *)&pvNullPointer;

	if(OSQPost((*mbox)->pQ, msg) != OS_NO_ERR)
		return ERR_MEM;

	return ERR_OK;
}

/**
 * Destroys a mailbox.
 *
 * @param mbox is the mailbox to be destroyed.
 */
void
sys_mbox_free(sys_mbox_t *mbox)
{
	u8_t err;
	
	//clear OSQ EVENT
	OSQFlush((*mbox)->pQ);

	//del OSQ EVENT
	OSQDel((*mbox)->pQ, OS_DEL_NO_PEND, &err);

	//put mem back to mem queue.
	OSMemPut(pQueueMem, *mbox);
}

/**
 * Retrieve a message from a mailbox.
 *
 * @param mbox is the mailbox
 * @param msg is a pointer to the location to receive the message
 * @param timeout is the maximum number of milliseconds to wait for the message
 * @return the number of milliseconds that passed before the message was
 *         received, or SYS_ARCH_TIMEOUT if the tmieout occurred
 */
u32_t
sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
	u8_t		err;
	u32_t		ucos_timeout, timeout_new;
	void 		*dummyptr;

	if(timeout != 0)
	{
		ucos_timeout = (timeout * OS_TICKS_PER_SEC)/1000;

		if(ucos_timeout < 1)
			ucos_timeout = 1;
		else if(ucos_timeout > 65535)
			ucos_timeout = 65535;
	}
	else
		ucos_timeout = 0;

	timeout = OSTimeGet();

	dummyptr = OSQPend((*mbox)->pQ, (u16_t)ucos_timeout, &err);

	/* If the actual message contents are not required, provide a local variable
	to recieve the message. */
	if(msg != NULL)
	{
		if(dummyptr == (void*)&pvNullPointer)
			*msg = NULL;
		else
			*msg = dummyptr;
	}

	if(err != OS_ERR_NONE)
		timeout = SYS_ARCH_TIMEOUT;
	else
	{
		timeout_new = OSTimeGet();
		if (timeout_new > timeout)
			timeout_new = timeout_new - timeout;
		else
			timeout_new = 0xffffffff - timeout + timeout_new;

		//convert to milisecond
		timeout = timeout_new * 1000 / OS_TICKS_PER_SEC + 1;
	}
	return timeout;
}

/**
 * Try to receive a message from a mailbox, returning immediately if one is not
 * available.
 *
 * @param mbox is the mailbox
 * @param msg is a pointer to the location to receive the message
 * @return ERR_OK if a message was available and SYS_MBOX_EMPTY if one was not
 *         available
 */
u32_t
sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
	u8_t err;

	/* If the actual message contents are not required, provide a local variable
	to recieve the message. */
	if(msg == NULL)
	{
		*msg = (void*)&pvNullPointer;
	}

	/* Recieve a message from the queue. */
	*msg = (sys_mbox_t)OSQAccept((*mbox)->pQ, &err);
	if(err == OS_ERR_NONE)
	{
		/* A message was available. */
		return ERR_OK;
	}
	else
	{
		/* A message was not available. */
		return SYS_MBOX_EMPTY;
	}
}

/**
 * Creates a new thread.
 *
 * @param name is the name of this thread
 * @param thread is a pointer to the function to run in the new thread
 * @param arg is the argument to pass to the thread's function
 * @param stacksize is the size of the stack to allocate for this thread
 * @param prio is the priority of the new thread
 * @return the handle fo the created thread
 */
sys_thread_t
sys_thread_new(const char *name, void (*thread)(void *arg), void *arg, int stacksize,
               int prio)
{
	int ubPrio = 0;
	
	arg = arg;

	if((prio > 0) && (prio <= LWIP_TASK_MAX))
	{
		// 计算uC/OS实际的任务优先级
		ubPrio = (u8_t)(LWIP_START_PRIO + prio - 1);

		// 任务堆栈大小不超过LWIP_STK_SIZE=512.
		if(stacksize > LWIP_STK_SIZE)
        	stacksize = LWIP_STK_SIZE;

		OSTaskCreate(thread, (void *)arg, &LWIP_TASK_STK[prio-1][stacksize-1], ubPrio);
	}

	// 返回空指针
	return (sys_thread_t)ubPrio;
}

u32_t sys_now(void)
{
	return OSTimeGet();
}

/**
 * Enters a critical section.
 *
 * @return the previous protection level
 */
sys_prot_t
sys_arch_protect(void)
{
#if OS_CRITICAL_METHOD == 3u
	OS_CPU_SR   cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();
	return cpu_sr;
}

/**
 * Leaves a critical section.
 *
 * @param the preivous protection level
 */
void
sys_arch_unprotect(sys_prot_t val)
{
#if OS_CRITICAL_METHOD == 3u
	OS_CPU_SR   cpu_sr = val;
#endif
	OS_EXIT_CRITICAL();
}

#endif /* NO_SYS */
