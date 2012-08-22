/***********************************************************************************
  Filename:     hal_types.h

  Description:  HAL type definitions

***********************************************************************************/

#ifndef HAL_TYPES_H
#define HAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif



/***********************************************************************************
 * TYPEDEFS
 */
#ifndef bool
//typedef unsigned char   bool;
#endif

typedef          char   S8;
typedef unsigned char   U8;

typedef          short  S16;
typedef unsigned short  U16;

typedef          long   S32;
typedef unsigned long   U32;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

typedef unsigned char   bool;

typedef signed   char   int8;
typedef unsigned char   uint8;

typedef signed   short  int16;
typedef unsigned short  uint16;

typedef signed   long   int32;
typedef unsigned long   uint32;

typedef void (*ISR_FUNC_PTR)(void);
typedef void (*VFPTR)(void);

typedef uint8           halDataAlign_t;

/***********************************************************************************
 * Compiler abstraction
 */

/*****************************************************
 * IAR MSP430
 */
#ifdef __IAR_SYSTEMS_ICC__

#define _PRAGMA(x) _Pragma(#x)

#if defined __ICC430__

#ifndef CODE
#define CODE
#endif
#ifndef XDATA
#define XDATA
#endif
#define FAR
#define NOP()  asm("NOP")

#define HAL_ISR_FUNC_DECLARATION(f,v)   \
    _PRAGMA(vector=v##_VECTOR) __interrupt void f(void)
#define HAL_ISR_FUNC_PROTOTYPE(f,v)     \
    _PRAGMA(vector=v##_VECTOR) __interrupt void f(void)
#define HAL_ISR_FUNCTION(f,v)           \
    HAL_ISR_FUNC_PROTOTYPE(f,v); HAL_ISR_FUNC_DECLARATION(f,v)


/*****************************************************
 * IAR 8051
 */
#elif defined __ICC8051__

#ifndef BSP_H
#define CODE   __code
#define XDATA  __xdata
#endif

#define FAR
#define NOP()  asm("NOP")

#define HAL_MCU_LITTLE_ENDIAN()   __LITTLE_ENDIAN__
#define HAL_ISR_FUNC_DECLARATION(f,v)   \
    _PRAGMA(vector=v) __near_func __interrupt void f(void)
#define HAL_ISR_FUNC_PROTOTYPE(f,v)     \
    _PRAGMA(vector=v) __near_func __interrupt void f(void)
#define HAL_ISR_FUNCTION(f,v)           \
    HAL_ISR_FUNC_PROTOTYPE(f,v); HAL_ISR_FUNC_DECLARATION(f,v)

#else
#error "Unsupported architecture"
#endif


/*****************************************************
 * KEIL 8051
 */
#elif defined __KEIL__
#include <intrins.h>
#define BIG_ENDIAN

#define CODE   code
#define XDATA  xdata
#define FAR
#define NOP()  _nop_()

#define HAL_ISR_FUNC_DECLARATION(f,v)   \
    void f(void) interrupt v
#define HAL_ISR_FUNC_PROTOTYPE(f,v)     \
    void f(void)
#define HAL_ISR_FUNCTION(f,v)           \
    HAL_ISR_FUNC_PROTOTYPE(f,v); HAL_ISR_FUNC_DECLARATION(f,v)

typedef unsigned short istate_t;

// Keil workaround
#define __code  code
#define __xdata xdata


/*****************************************************
 * WIN32
 */
#elif defined WIN32

#define CODE
#define XDATA
#include "windows.h"
#define FAR far
#pragma warning (disable :4761)


/*****************************************************
 * Code Composer Essential
 */

#elif __TI_COMPILER_VERSION__
#define CODE
#define XDATA
#define FAR

typedef unsigned short istate_t;


/*****************************************************
 * Other compilers
 */
#else
#error "Unsupported compiler"
#endif



#ifdef __cplusplus
}
#endif

#endif
