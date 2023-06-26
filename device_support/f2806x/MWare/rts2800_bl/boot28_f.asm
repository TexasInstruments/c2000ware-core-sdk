;******************************************************************************
;* BOOT  v6.0.1
;* 
;* Copyright (c) 2000-2015 Texas Instruments Incorporated
;* http://www.ti.com/ 
;* 
;*  Redistribution and  use in source  and binary forms, with  or without
;*  modification,  are permitted provided  that the  following conditions
;*  are met:
;* 
;*     Redistributions  of source  code must  retain the  above copyright
;*     notice, this list of conditions and the following disclaimer.
;* 
;*     Redistributions in binary form  must reproduce the above copyright
;*     notice, this  list of conditions  and the following  disclaimer in
;*     the  documentation  and/or   other  materials  provided  with  the
;*     distribution.
;* 
;*     Neither the  name of Texas Instruments Incorporated  nor the names
;*     of its  contributors may  be used to  endorse or  promote products
;*     derived  from   this  software  without   specific  prior  written
;*     permission.
;* 
;*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS
;*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT
;*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
;*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT
;*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT
;*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;* 
;******************************************************************************

;****************************************************************************
;* BOOT.ASM
;*
;* THIS IS THE INITAL BOOT ROUTINE FOR C28xx C++ PROGRAMS.
;* IT MUST BE LINKED AND LOADED WITH ALL C++ PROGRAMS.
;* 
;* THIS MODULE PERFORMS THE FOLLOWING ACTIONS:
;*   1) SET RESET VECTOR TO POINT AT _C_INT00
;*   2) ALLOCATES THE STACK AND INITIALIZES THE STACK POINTER
;*   3) SET UP PROPER STATUS
;*   4) PERFORMS AUTO-INITIALIZATION
;*   5) CALLS INITALIZATION ROUTINES FOR FILE SCOPE CONSTRUCTION
;*   6) CALLS THE FUNCTION MAIN TO START THE C++ PROGRAM
;*   7) CALLS THE STANDARD EXIT ROUTINE
;*
;* THIS MODULE DEFINES THE FOLLOWING GLOBAL SYMBOLS:
;*   1) __stack     STACK MEMORY AREA
;*   2) _c_int00    BOOT ROUTINE
;*
;****************************************************************************
    .cdecls "boot_loader/bl_config.h"

 .if $defined("ENABLE_FAILSAFE")  

CONST_COPY	.set 0

	.global  _c_int00f, cinit, pinit
	.global  _FailsafeEntry, _exit
	.global  __stack

****************************************************************************
*  INITIALIZE RESET VECTOR TO POINT AT _c_int00                            *
****************************************************************************
	.sect .reset
	.long _c_int00f

	.sect "failsafe"
****************************************************************************
* FUNCTION DEF : _c_int00f                                                 *
*                                                                          *
****************************************************************************

_c_int00f:	.asmfunc
****************************************************************************
*  INITIALIZE STACK POINTER.                                               *
****************************************************************************
	MOV  	SP,#__stack		; set to beginning of stack space

****************************************************************************
* INITIALIZE STATUS BIT FIELDS *NOT* INITIALIZED AT RESET                  *
****************************************************************************
	SPM	0			; set product shift to 0

****************************************************************************
* SET C28x MODES                                                           *
****************************************************************************
        C28OBJ                          ; select C28x object mode
        C28ADDR                         ; clear the addressing mode
        C28MAP                          ; set block M0 and M1 mode

        .if .TMS320C2800_FPU32
        SETFLG            RNDF32=1      ; Enable rounding in FPU32 mode.
        .endif
****************************************************************************
* SETTING THESE STATUS BITS/REGISTER TO RESET VALUES.  IF YOU RUN          *
* _c_int00 FROM RESET, YOU CAN REMOVE THIS CODE                            *
****************************************************************************
	CLRC    PAGE0			; use stack addressing mode
        MOVW    DP,#0			; initialize DP to point at low 64K
	CLRC    OVM         		; turn off overflow mode

	ASP				; ensure SP is aligned

****************************************************************************
* SET THE EALLOW BIT BEFORE THE CINIT TABLE IS COPIED.                     *
****************************************************************************
	EALLOW

****************************************************************************
*  IF cinit IS NOT -1, PROCESS CINIT INITIALIZATION TABLE	           *
****************************************************************************
	MOV	AL,#cinit+0x4000
	MOV	AH,#hi16(cinit+0x4000)
	ADDB	ACC,#1
	B	DO_PINIT,EQ		; if cinit < 0 (-1) no init tables

****************************************************************************
*  PROCESS CINIT INITIALIZATION TABLE.  TABLE IS IN PROGRAM MEMORY IN THE  *
*  FOLLOWING FORMAT:                                                       *
*                                                                          *
*       .word  <length of init data in words>                              *
*       .word  or .long <address of variable to initialize>                *
*       .word  <init data>                                                 *
*       .word  ...                                                         *
*                                                                          *
*  If the variable's address is greater than 65535 (located in 'far'       *
*  memory), then the address field of the cinit record will be 32-bits     *
*  instead of the default 16-bits. The length value is negated to tag      *
*  cinit records for those variables located in far memory.                *
*                                                                          *
*  The init table is terminated with a zero length                         *
*                                                                          *
****************************************************************************
	MOVL	XAR7,#cinit+0x4000		; point XAR7 at start of table	
	CLRC    TC		        ; reset TC bit used as far flag 
	B 	START, UNC		; jump to start processing
LOOP:
	MOVB    AH,#0		        ; zero out upper addr bits
	PREAD   AL,*XAR7		; load address of variable to be inited
	ADDB    XAR7,#1			; point to initialization data
       	B	GET_DATA,NTC	        ; get data if variable is not far 
	CLRC    TC		        ; reset TC bit used as far flag 
	PREAD   AH,*XAR7	        ; otherwise, get hi bits of 22-bit addr
	ADDB    XAR7,#1
GET_DATA:	
	MOVL	XAR6,ACC	        ; address
	RPT	AR1			; repeat length + 1 times
||	PREAD   *XAR6++,*XAR7		; copy data from table to memory
	
	MOVL	ACC,XAR7		; using ACC as temp, point XAR7 to 
	ADD  	ACC,AR1			; next cinit record since PREAD 
	ADDB	ACC,#1			; doesn't change value of XAR7. 
	MOVL	XAR7,ACC	
START:
	PREAD	AL,*XAR7		; load length
	B	GET_ADDR,GEQ	        ; a length < 0 denotes far data	 
        NEG     AL		        ; negate value to get real length	
	SETC    TC		        ; flag that the address field is 32-bits
GET_ADDR:	
	MOVZ	AR1,AL		        ; copy length value to loop register
        ADDB    XAR7,#1			; point to address field
	BANZ	LOOP,AR1--		; if (length-- != 0) continue 

****************************************************************************
*  IF pinit IS NOT -1, PROCESS CONSTRUCTOR ROUTINES                        *
****************************************************************************
DO_PINIT:			

****************************************************************************
* CLEAR THE EALLOW BIT AFTER THE CINIT TABLE IS COPIED.                    *
****************************************************************************
	EDIS

	MOV	AL,#pinit+0x4000
	MOV	AH,#hi16(pinit+0x4000)
	ADDB	ACC,#1
	B	DONE_INIT,EQ		; if pinit < 0 (-1) no pinit table

****************************************************************************
*  PROCESS PINIT SECTION. TABLE CONSISTS OF CONSTRUCTOR ROUTINE ADDRESSES  *
*  THAT POINT TO C++ INITIALIZATION FUNCTIONS. THESE ROUTINES MUST EXECUTE *
*  BEFORE MAIN IS CALLED                                                   *
****************************************************************************
	MOVL    XAR7,#pinit+0x4000	        ; set up pointer to initialization table
	B	START_PINIT, UNC        ; jump to start processing

LOOP_PINIT:	
	ADDB    XAR7,#1			; point to next table entry	
	PUSH	XAR7			; save off table entry address 
	MOVL	XAR7,ACC		; load constructor routine address
	LCR     *XAR7			; execute routine
	POP	XAR7			; reload table entry address 
	
START_PINIT:	
	PREAD   AL,*XAR7	        ; unpack constructor routine address 
	ADDB    XAR7,#1		
	PREAD   AH,*XAR7	
	TEST	ACC			; test for table end condition (zero)	
	B	LOOP_PINIT,NEQ		; process table entry if not zero
	
	
****************************************************************************
*  COPY CONSTANTS TO DATA MEMORY, IF NECESSARY                             *
****************************************************************************
DONE_INIT:
	.if CONST_COPY
        LCR	_const_init
	.endif

****************************************************************************
*  CALL USER'S PROGRAM                                                     *
****************************************************************************
	LCR     _FailsafeEntry			; execute main()
	LCR  	_exit
	.endasmfunc

	.if CONST_COPY

****************************************************************************
* FUNCTION DEF : __const_init                                              *
*                                                                          *
*  COPY .CONST AND .ECONST SECTION FROM PROGRAM TO DATA MEMORY             *
*                                                                          *
*   The function depends on the following variables                        *
*   defined in the linker command file                                     *
*                                                                          *
*   __c_load         ; global var containing start                         *
*                      of .const in program memory                         *
*   __const_run      ; global var containing run                           *
*                      address in data memory                              *
*   __const_length   ; global var length of .const                         *
*                      section                                             *
*                                                                          *
*                                                                          *
*   Similarly for constants to be placed into extended memory (far):       *
*                                                                          *
*   __ec_load         ; global var containing start                        *
*                      of .econst in program memory                        *
*   __econst_run      ; global var containing run                          *
*                      address in data memory                              *
*   __econst_length   ; global var length of .econst                       *
*                      section                                             *
*                                                                          *
****************************************************************************
        .global __const_length,  __c_load,  __const_run
        .global __econst_length, __ec_load, __econst_run
 
        .sect ".c_mark"              ; establish LOAD adress of
        .label __c_load              ; .const section
 
        .sect ".ec_mark"              ; establish LOAD adress of
        .label __ec_load              ; .econst section
 
        .text
_const_init:	.asmfunc
 
        MOV     AL,#__const_length
        B       __econst_init,EQ
        DEC     AL
        MOVL    XAR6,#__const_run
        MOVL    XAR7,#__c_load
        RPT     AL
||      PREAD   *XAR6++,*XAR7
 
__econst_init:
        MOVL    XAR6, #__econst_length
        MOVL    ACC,XAR6
        B       __end_const,EQ
        MOVL    XAR6,#__econst_run
        MOVL    XAR7,#__ec_load
        DEC     AL
        B       __econst_loop,GEQ
        DEC     AH
__econst_loop:
        MOV     AR0,AH
        RPT     AL
||      PREAD   *XAR6++,*XAR7
        MOV     AH,#0
        ADDL    ACC,XAR7
        ADDB    ACC, #1
        MOVL    XAR7,ACC
        MOV     AL, #0xffff
        MOV     AH,AR0
        SUBB    AH,#1
        B       __econst_loop,GEQ
 
******************************************************
*  AT END OF CONSTANT SECTIONS RETURN TO CALLER      *
******************************************************
__end_const:
        LRETR
	.endasmfunc
        .endif			;  if CONST_COPY
        .endif          ;  if ENABLE_FAILSAFE


