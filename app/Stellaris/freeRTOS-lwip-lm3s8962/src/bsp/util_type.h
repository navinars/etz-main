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

typedef          char   S8;
typedef unsigned char   U8;

typedef          short  S16;
typedef unsigned short  U16;

typedef          long   S32;
typedef unsigned long   U32;

typedef          long	long   	S64;
typedef unsigned long   long	U64;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef SUCCESS
#define SUCCESS 0
#else
#warning "Macro SUCCESS already defined"
#endif

#ifndef FAILED
#define FAILED  1
#else
#warning "Macro SUCCESS already defined"
#endif

#ifdef __cplusplus
}
#endif


#endif
