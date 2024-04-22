;;###########################################################################
;;
;; FILE:	IQNdiv.asm
;;
;; TITLE:	C Callable IQ Divide Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date     | Who   | Description of changes
;; =====|==============|=======|=============================================
;; 1.2  | 11 Oct 2001  | A. T. | Original Release.
;; -----|--------------|-------|---------------------------------------------
;; 1.3  | 19 Nov 2001  | A. T. | Improved accuracy of function.
;; -----|--------------|-------|---------------------------------------------
;; 1.4  | 17 May 2002  | A. T. | Modified result when Den==0. Gives most
;;      |              |       | positive result rather then zero.
;; -----|--------------|-------|---------------------------------------------
;;      |              |       |
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
;; Function:   _IQNdiv
;;===========================================================================
;;
;; C Usage:    extern long _IQNdiv(long Num, long Den);
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = Numerator in IQ format
;;             [SP-4] = Denominator in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4, XAR0
;;             XT, P
;;
;; On Exit:    ACC    = Num/Den result in IQ format
;;                    = 0x7FFFFFFF if +ve overflow
;;                    = 0x80000000 if -ve overflow
;;                    = 0x7FFFFFFF if Den == 0
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The procedure for calculating Y = N/D is as follows:
;;
;;             Step 1) Normalize Input: 
;;
;;                     Dnorm = D * 2^n 
;;
;;             Step 2) Obtain initial estimate of Dm = 1/Dnorm from 
;;                     "_IQdivTable" using the upper 8-bits of the 
;;                     normalized value.
;;
;;             Step 3) Use Newton-Raphson algorithm to improve accuracy.
;;                     Repeat following equation two times. First iteration
;;                     gives 16-bit accuracy. Second iteration gives 32-bit
;;                     accuracy:
;;
;;                     Dm = 2(Dm - Dm^2*Dnorm/2)   
;;
;;             Step 4) Multiply by numerator value:
;;
;;                     Ym = N * Dm
;;
;;             Step 5) Denormalize result, saturate and round:
;;
;;                     Y = Ym >> n 
;;
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Assumptions: 
;; * Code executes from 0-wait SARAM block.
;; * _IQdiv Tables located in seperate 0-wait SARAM or 1-wait ROM block.
;; * Stack located in seperate 0-wait SARAM block.
;; * Includes LCR/LRETR.
;;
;; Cycles = 62 (if _IQdiv Tables in 0-wait SARAM)
;;          70 (if _IQdiv Tables in 1-wait ROM)
;;          22 (if Den == 0)
;;
;;===========================================================================

IQNdiv	.macro	q_value
		MOVL	*SP++,ACC			; Temp save Numerator on stack		
		MOVL	ACC,*-SP[6]			; Load ACC with Denominator
		CSB		ACC					; Count sign bits, T = n
		LSLL	ACC,T				; ACC = Dnorm                     (Q31)
        MOVL    @XAR4,ACC			; Temp save "Dnorm"
        LSR     AH,#6
		SBF		$10,EQ				; If Den = 0, exit and load max value
        MOVZ    AR0,@AH             ; AR0 = index into _IQdivTable
		MOVL	XAR7,#(_IQdivTable-254) 
		MOVB	AH,#(61 - q_value)	; AH   = 61 - q_value
		SUBR	@T,AH				; T    = 61 - q_value - n
		MOVL	XAR5,@XT			; AR5H = 61 - q_value - n
		MOVL    XT,*+XAR7[AR0]  	; (1) XT    = initial Dm estimate (Q29)	
		MOVL	XAR7,#_IQdivRoundSatTable	
		MOVL	XAR6,*XAR7++		; XAR6 = 2.0                      (Q29)

		IMPYL	P,XT,@XAR4			; (2) 
		QMPYL	ACC,XT,@XAR4		; (2) ACC:P = Dm*Dnorm            (Q60)
		LSL64	ACC:P,#1			; (3) ACC:P = Dm*Dnorm            (Q61)
		SUBL	ACC,@XAR6			; (4) ACC   = Dm*Dnorm - 2.0      (Q29)
		NEG		ACC					; (5) ACC   = 2.0 - Dm*Dnorm      (Q29)
		IMPYL	P,XT,@ACC			; (6) 
		QMPYL	ACC,XT,@ACC			; (6) ACC:P = Dm(2.0 - Dm*Dnorm)  (Q58) 
		LSL64	ACC:P,#3 			; (7) ACC:P = Dm(2.0 - Dm*Dnorm)  (Q61)

		MOVL    XT,@ACC  			; (1) XT    = Dm                  (Q29)	
		IMPYL	P,XT,@XAR4			; (2) 
		QMPYL	ACC,XT,@XAR4		; (2) ACC:P = Dm*Dnorm            (Q60)
		LSL64	ACC:P,#1			; (3) ACC:P = Dm*Dnorm            (Q61)
		SUBL	ACC,@XAR6			; (4) ACC   = Dm*Dnorm - 2.0      (Q29)
		NEG		ACC					; (5) ACC   = 2.0 - Dm*Dnorm      (Q29)
		IMPYL	P,XT,@ACC			; (6) 
		QMPYL	ACC,XT,@ACC			; (6) ACC:P = Dm(2.0 - Dm*Dnorm)  (Q58) 
		LSL64	ACC:P,#3 			; (7) ACC:P = Dm(2.0 - Dm*Dnorm)  (Q61)
				
		MOVL    XT,*--SP 			; XT = Numerator
		IMPYL   P,XT,@ACC
		QMPYL   ACC,XT,@ACC			; ACC:P = N * Dm

		LSL64	ACC:P,#2
		MOVL    XT,@XAR5			; T = 61 - q_value - n
		ASR64	ACC:P,T				; scale back result

		ADDUL	P,*XAR7++			; Round result
		ADDCL	ACC,*XAR7++
		MINL	ACC,*+XAR7[2]		; Saturate result
		MINCUL	P,*+XAR7[0]
		MAXL	ACC,*+XAR7[6]
		MAXCUL	P,*+XAR7[4]
		
		ASR64	ACC:P,#1			; ACC = final IQ result
		MOVL	ACC,@P
		LRETR
		
$10:
		MOV		@AL,#0xFFFF
		MOV		@AH,#0x7FFF
		SUBB	SP,#2
		LRETR
		.endm

		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.ref	_IQdivTable
		.ref	_IQdivRoundSatTable
		
		.if	GLOBAL_Q == 30
		.def	__IQ30div
__IQ30div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29div
__IQ29div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28div
__IQ28div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27div
__IQ27div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26div
__IQ26div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25div
__IQ25div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24div
__IQ24div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23div
__IQ23div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22div
__IQ22div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21div
__IQ21div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20div
__IQ20div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19div
__IQ19div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18div
__IQ18div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17div
__IQ17div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16div
__IQ16div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15div
__IQ15div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14div
__IQ14div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13div
__IQ13div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12div
__IQ12div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11div
__IQ11div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10div
__IQ10div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9div
__IQ9div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8div
__IQ8div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7div
__IQ7div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6div
__IQ6div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5div
__IQ5div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4div
__IQ4div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3div
__IQ3div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2div
__IQ2div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1div
__IQ1div:
		IQNdiv	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
