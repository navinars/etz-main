/***********************************************************************************
  Filename:     hal_types.h

  Description:  HAL type definitions

***********************************************************************************/

#ifndef UTIL_TYPES_H
#define UTIL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif



/***********************************************************************************
* TYPEDEFS
*/
#ifndef bool
typedef unsigned char   bool;
#endif

typedef signed   char   S8;
typedef unsigned char   U8;

typedef signed   short  S16;
typedef unsigned short  U16;

typedef signed   long   S32;
typedef unsigned long   U32;

typedef signed   long	long   	S64;
typedef unsigned long   long	U64;

typedef void (*ISR_FUNC_PTR)(void);
typedef void (*VFPTR)(void);


#ifdef __cplusplus
}
#endif


#endif
