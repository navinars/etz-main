#ifndef __IAR_OPTIMIZE_H__
#define __IAR_OPTIMIZE_H__

#define OPTIMIZE_SIZE_NONE    _Pragma("optimize=z 2")
#define OPTIMIZE_SIZE_LOW     _Pragma("optimize=z 3")
#define OPTIMIZE_SIZE_MEDIUM  _Pragma("optimize=z 6")
#define OPTIMIZE_SIZE_HIGH    _Pragma("optimize=z 9")

#define OPTIMIZE_SPEED_NONE    _Pragma("optimize=s 2")
#define OPTIMIZE_SPEED_LOW     _Pragma("optimize=s 3")
#define OPTIMIZE_SPEED_MEDIUM  _Pragma("optimize=s 6")
#define OPTIMIZE_SPEED_HIGH    _Pragma("optimize=s 9")


#define OZ_2 OPTIMIZE_SIZE_NONE
#define OZ_3 OPTIMIZE_SIZE_LOW
#define OZ_6 OPTIMIZE_SIZE_MEDIUM
#define OZ_9 OPTIMIZE_SIZE_HIGH

#define OS_2 OPTIMIZE_SPEED_NONE
#define OS_3 OPTIMIZE_SPEED_LOW
#define OS_6 OPTIMIZE_SPEED_MEDIUM
#define OS_9 OPTIMIZE_SPEED_HIGH

#endif
