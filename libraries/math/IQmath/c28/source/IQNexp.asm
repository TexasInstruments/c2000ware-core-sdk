;;###########################################################################
;;
;; FILE:	IQNexp.asm
;;
;; TITLE:	C Callable IQ Exponent Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.0  | 11 Jul 2002 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;; 1.1  | 10 Mar 2005 | A. T. | Fixed Bug #1. "LSL ACC,T" instruction
;;      |             |       | should have been "LSLL  ACC,T".
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################
;;#############################################################################
;;!
;;! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
;;!	All rights reserved not granted herein.
;;!	Limited License.
;;!
;;! Texas Instruments Incorporated grants a world-wide, royalty-free,
;;! non-exclusive license under copyrights and patents it now or hereafter
;;! owns or controls to make, have made, use, import, offer to sell and sell
;;! ("Utilize") this software subject to the terms herein. With respect to the
;;! foregoing patent license, such license is granted solely to the extent that
;;! any such patent is necessary to Utilize the software alone. The patent
;;! license shall not apply to any combinations which include this software,
;;! other than combinations with devices manufactured by or for TI 
;;! ("TI Devices").
;;! No hardware patent is licensed hereunder.
;;!
;;! Redistributions must preserve existing copyright notices and reproduce this
;;! license (including the above copyright notice and the disclaimer and
;;! (if applicable) source code license limitations below) in the documentation
;;!  and/or other materials provided with the distribution.
;;!
;;! Redistribution and use in binary form, without modification, are permitted
;;! provided that the following conditions are met:
;;!
;;! * No reverse engineering, decompilation, or disassembly of this software is 
;;! permitted with respect to any software provided in binary form.
;;! * Any redistribution and use are licensed by TI for use only 
;;!   with TI Devices.
;;! * Nothing shall obligate TI to provide you with source code for the 
;;!   software licensed and provided to you in object code.
;;!
;;! If software source code is provided to you, modification and redistribution
;;! of the source code are permitted provided that the following conditions 
;;! are met:
;;!
;;! * any redistribution and use of the source code, including any resulting
;;!   derivative works, are licensed by TI for use only with TI Devices.
;;! * any redistribution and use of any object code compiled from the source
;;!   code and any resulting derivative works, are licensed by TI for use 
;;!   only with TI Devices.
;;!
;;! Neither the name of Texas Instruments Incorporated nor the names of its
;;! suppliers may be used to endorse or promote products derived from this 
;;! software without specific prior written permission.
;;#############################################################################

;;===========================================================================
;; Function:   _IQNexp
;;===========================================================================
;;
;; C Usage:    extern long _IQNexp(long X);   // Saturated
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = X in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4, XAR3
;;             XT, P
;;
;; On Exit:    ACC    = exp(X) result in IQ format
;;
;; Q range:    29 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The procedure for calculating "Y = exp(X)" is as follows:
;;
;;             Step 1) Saturate input to avoid overflow.
;; 
;;             Step 2) Normalize Input: 
;;
;;                     X' = X * 2^n           -1.0 <= X' < 1.0
;;
;;             Step 3) Obtain Y' = exp(X') using taylor series expansion:
;;
;;                     Y' = 1 + X' + X'^2/2! + .... + X^11/11!
;;
;;             Step 4) Denormalize value to get output Y:
;;
;;                     if( n == 0 ) Y = Y'
;;                     if( n == 1 ) Y = Y'^2
;;                     if( n == 2 ) Y = Y'^4
;;                     if( n == 3 ) Y = Y'^8
;;                     if( n == 4 ) Y = Y'^16
;;        
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Assumptions: 
;; * Code executes from 0-wait SARAM block.
;; * _IQexp Tables located in seperate 0-wait SARAM or 1-wait ROM block.
;; * Stack located in seperate SARAM block.
;; * Includes LCR/LRETR.
;;
;; Cycles = 168 to 215 
;;
;;===========================================================================

IQNexp	.macro	q_value
		PUSH	XAR3

		; Step 1: Saturate input to avoid overflow:
		MOVL	XAR7,#(_IQexpTableMinMax + (q_value - 1)*4)
		MINL	ACC,*+XAR7[0]				; Saturate Input To Max Value
		MAXL	ACC,*+XAR7[2]				; Saturate Input To Min Value
		MOVL	XAR6,@ACC					; XAR6 = X                 (QG)

		; Step 2: Normalize Input:
		CSB		ACC
		MOVB	AL,#(31 - q_value)		
		SUB		AL,@T
		MOVB	@AL,#0,LT
		MOVZ	AR3,@AL 					; AR3 = n
		MOV		T,@AL
		MOVL	ACC,@XAR6
		ASR64	ACC:P,T	                    ; ACC = X'                 (QG)
		.if (q_value <= 29)
		MOV 	@T,#(29 - q_value)
		LSLL	ACC,T 						; (Fixed Bug #1) ACC = X'  (Q29)
		.endif
		MOVL	XAR6,@ACC					; XAR6 = X'                (Q29)

		; Step 3: Repeat 10 Times: ACC = X*(1 + ACC/Coeff)
		MOV		@PH,#(1 << 12)
		MOV		@PL,#0		
		MOVL	XAR5,@P 					; XAR5 = 1.0               (Q28)
		MOVL  	XAR7,#_IQexpTableCoeff		; XAR7 -> 1/10 Coeff       (Q31)
		MOVB	XAR4,#9
IQNexpLoop1:		
		MOVL	XT,@ACC						; XT = ACC                 (Q29)						
		QMPYL	ACC,XT,*XAR7++				; ACC = ACC/Coeff          (Q28)
		ADDL	ACC,@XAR5					; ACC = 1 + ACC/Coeff      (Q28)
		MOVL 	XT,@XAR6					; XT = X                   (Q29)
		IMPYL	P,XT,@ACC
		QMPYL	ACC,XT,@ACC					; ACC:P = X(1 + ACC/Coeff) (Q57) 
		LSL64	ACC:P,#4 					; ACC = X(1 + ACC/Coeff)   (Q29)
		BANZ	IQNexpLoop1,AR4--	
		
		ADDL 	ACC,@XAR5		
		ADDL	ACC,@XAR5					
		.if (q_value <= 29)
		MOV		@T,#(29 - q_value)
		ASR64 	ACC:P,T						; ACC = 1 + ACC = exp(X)   (QG)
		.endif
				
		; Step 4: Denormalize result:		
		MOVB	XAR6,#0
		BAR		IQNexpExit,AR3,AR6,EQ		;if( n == 0 ) Y = ACC
		SUBB	XAR3,#1
IQNexpLoop2:	
		MOVL	XT,@ACC
		IMPYL	P,XT,@ACC
		QMPYL	ACC,XT,@ACC
		MOV 	@T,#(32 - q_value)
		LSL64	ACC:P,T						; ACC = ACC*ACC            (QG)
		BANZ	IQNexpLoop2,AR3-- 			; Loop until n == 0

IQNexpExit:
		POP		XAR3
		LRETR
		.endm
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.ref	_IQexpTableMinMax
		.ref	_IQexpTableCoeff
		.if	GLOBAL_Q == 30
		.def	__IQ30exp
__IQ30exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29exp
__IQ29exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28exp
__IQ28exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27exp
__IQ27exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26exp
__IQ26exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25exp
__IQ25exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24exp
__IQ24exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23exp
__IQ23exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22exp
__IQ22exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21exp
__IQ21exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20exp
__IQ20exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19exp
__IQ19exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18exp
__IQ18exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17exp
__IQ17exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16exp
__IQ16exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15exp
__IQ15exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14exp
__IQ14exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13exp
__IQ13exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12exp
__IQ12exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11exp
__IQ11exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10exp
__IQ10exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9exp
__IQ9exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8exp
__IQ8exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7exp
__IQ7exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6exp
__IQ6exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5exp
__IQ5exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4exp
__IQ4exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3exp
__IQ3exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2exp
__IQ2exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1exp
__IQ1exp:
		IQNexp	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
