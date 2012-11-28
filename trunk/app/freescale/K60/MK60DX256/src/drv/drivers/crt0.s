/*
 * File:	crt0.s
 * Purpose:	Lowest level routines for Kinetis.
 *
 * Notes:	
 *
 */

#ifndef CW10
#define CW10
#endif
;         AREA   Crt0, CODE, READONLY      ; name this block of code
#ifndef CW10
  SECTION .noinit : CODE
#else
	.section .noinit : CODE
#endif   

#ifndef CW10
        EXPORT  __startup
__startup
#else
		.global __startup
__startup:		

#endif
    
    MOV     r0,#0                   ; Initialize the GPRs
	MOV     r1,#0
	MOV     r2,#0
	MOV     r3,#0
	MOV     r4,#0
	MOV     r5,#0
	MOV     r6,#0
	MOV     r7,#0
	MOV     r8,#0
	MOV     r9,#0
	MOV     r10,#0
	MOV     r11,#0
	MOV     r12,#0
	CPSIE   i                       ; Unmask interrupts
#ifndef CW10	
        import start
#else
	.extern start 
#endif        
        BL      start                  ; call the C code
#ifndef CW10        
__done
#else
__done:
#endif
       B  __done
#ifndef CW10

       END
#endif
       
