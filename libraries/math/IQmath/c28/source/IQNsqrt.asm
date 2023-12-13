;;###########################################################################
;;
;; FILE:	IQNsqrt.asm
;;
;; TITLE:	C Callable IQ Square Root Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.2  | 11 Oct 2001 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;; 1.3  | 19 Nov 2001 | A. T. | Improved accuracy.
;; -----|-------------|-------|----------------------------------------------
;; 1.4  | 17 May 2002 | A. T. | Corrected benchmark cycles.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNsqrt
;;===========================================================================
;;
;; C Usage:    extern long _IQNsqrt(long X);   // with rounding
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = X in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4
;;             XT, P, XAR0
;;
;; On Exit:    ACC    = sqrt(X) result in IQ format
;;             ACC    = 0 if input is -ve or 0
;;
;;                      Note: The square root of any number will never 
;;                            overflow, hence saturation is not required.
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The procedure for calculating "Y = sqrt(X)" is similar
;;             to calculating the inverse sqare root due to the
;;             following relationship:
;;
;;                     sqrt(X) = X * 1/sqrt(X)
;;
;;             The procedure is as follows:
;;
;;             Step 1) Normalize Input: 
;;
;;                     V = X * 2^n 
;;
;;             Step 2) Obtain initial estimate from "_IQsqrtTable" 
;;                     using the upper 8-bits of the normalized V value.
;;
;;             Step 3) Use Newton-Raphson algorithm to improve accuracy.
;;                     Repeat following equation two times. First iteration
;;                     gives 16-bit accuracy. Second iteration gives 32-bit
;;                     accuracy:
;;
;;                     Yn = Yn(1.5 - Yn*Yn*V/2)
;;
;;                     Yn = 1/sqrt(V)
;;
;;             Step 4) Caculate the square root of the normalized number:
;;
;;                     Yn = V * Yn
;;
;;             Step 5) Denormalize result and round:
;;
;;                     Y = Yn * 2^n / sqrt(2^n)
;;        
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Assumptions: 
;; * Code executes from 0-wait SARAM block.
;; * _IQsqrt Tables located in seperate 0-wait SARAM or 1-wait ROM block.
;; * Stack located in seperate SARAM block.
;; * Includes LCR/LRETR.
;;
;; Cycles = 65 (30 >= Q >= 24 if _IQsqrt Tables in 0-wait SARAM)
;;          64 (23 >= Q >= 22 if _IQsqrt Tables in 0-wait SARAM)
;;          65 (21 >= Q >= 0  if _IQsqrt Tables in 0-wait SARAM)
;;
;; Cycles = 69 (30 >= Q >= 24 if _IQsqrt Tables in 1-wait ROM)
;;          68 (23 >= Q >= 22 if _IQsqrt Tables in 1-wait ROM)
;;          69 (21 >= Q >= 0  if _IQsqrt Tables in 1-wait ROM)
;;
;;===========================================================================
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

IQNsqrt	.macro	q_value
		CSB		ACC					; Count sign bits, T = n
		LSLL	ACC,T				; ACC  = V/2                       (Q32)
		MOVL	XAR6,@ACC			; XAR6 = V/2                       (Q32)
        ASR     AH,#6
        MOVB	@AH,#0xFE,LEQ		; AR0 -> zero value if -ve or 0 input
        SUB		@AH,#254			; Scale to table offset
        MOVZ    AR0,@AH             ; AR0 -> index into _IQisqrtTable for
        							;        initial estimate of Yn
		TBIT	@T,#0				; TC   = odd/even shift indicator
		MOV		AH,@T				; AH   = n 
		LSR		AH,#1				; AH   = n/2
		MOVL	*SP++,ACC			; SP-2 = n/2
		MOVL	XAR7,#_IQsqrtTable	; XAR7 = pointer to _IQisqrtTable
		MOVL	XAR4,*+XAR7[AR0]	; (1) XAR4  = initial Yn estimate  (Q30)
		
		MOVL	XAR7,#_IQsqrtRoundSatTable	
		MOVL	XAR5,*XAR7++		; XAR5 = 1.5                       (Q30)
		.if (q_value & 0x0001) == 0	; Q even
		MOVB	@AR0,#12,NTC		; AR0 -> 1/sqrt(2) if n == even    (Q30)
		MOVB	@AR0,#10,TC			; AR0 -> 0.5       if n == odd     (Q30)
		.endif
		.if (q_value & 0x0001) == 1	; Q odd
		MOVB	@AR0,#12,TC			; AR0 -> 1/sqrt(2) if n == odd     (Q30)
		MOVB	@AR0,#8,NTC			; AR0 -> 1.0       if n == even    (Q30)
		.endif
		
		MOVL	XT,@XAR4			;(2)  XT    = Yn                   (Q30)
		QMPYL	ACC,XT,@XT			;(3)  ACC   = Yn*Yn                (Q28)
		MOVL	XT,@XAR6			;(4)  XT    = V/2                  (Q32)
		LSL		ACC,#2				;(5)  ACC   = Yn*Yn                (Q30)
		QMPYL	ACC,XT,@ACC			;(6)  ACC   = Yn*Yn*V/2            (Q30)
		MOVL	XT,@XAR5			;(7)  XT    = 1.5                  (Q30)
		SUBL	@XT,ACC				;(8)  XT    = 1.5 - Yn*Yn*V/2      (Q30)
		QMPYL	ACC,XT,@XAR4		;(9)  ACC   = Yn(1.5 - Yn*Yn*V/2)  (Q28)
		LSL		ACC,#2				;(10) ACC   = Yn(1.5 - Yn*Yn*V/2)  (Q30)

		MOVL	XAR4,@ACC			;(1)  XAR4  = Yn                   (Q30)
		MOVL	XT,@XAR4			;(2)  XT    = Yn                   (Q30)
		QMPYL	ACC,XT,@XT			;(3)  ACC   = Yn*Yn                (Q28)
		MOVL	XT,@XAR6			;(4)  XT    = V/2                  (Q32)
		LSL		ACC,#2				;(5)  ACC   = Yn*Yn                (Q30)
		QMPYL	ACC,XT,@ACC			;(6)  ACC   = Yn*Yn*V/2            (Q30)
		MOVL	XT,@XAR5			;(7)  XT    = 1.5                  (Q30)
		SUBL	@XT,ACC				;(8)  XT    = 1.5 - Yn*Yn*V/2      (Q30)
		QMPYL	ACC,XT,@XAR4		;(9)  ACC   = Yn(1.5 - Yn*Yn*V/2)  (Q28)
		LSL		ACC,#2				;(10) ACC   = Yn(1.5 - Yn*Yn*V/2)  (Q30)

		MOVL	XT,@XAR6
		QMPYL	ACC,XT,@ACC			; sqrt(X) = X * 1/sqrt(X)

		MOVL	XT,*+XAR7[AR0]		; Scale with 1.0 or 1/sqrt(X) or 0.5
		IMPYL	P,XT,@ACC
		QMPYL	ACC,XT,@ACC
		
		.if	q_value >= 24			; Scale final result based on Q value
		LSL64	ACC:P,#((q_value - 22)/2)
		.endif
		.if	q_value <= 21
		ASR64	ACC:P,#((23 - q_value)/2)
		.endif
		
		MOVL	XT,*--SP			; T = n/2
		ASR64	ACC:P,T				; Scale final result based on n/2
		ADD		@PH,#-32768			; Round final result
		ADDCL	ACC,*+XAR7[2]
		LRETR
		.endm
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.ref	_IQsqrtTable
		.ref	_IQsqrtRoundSatTable
		.if	GLOBAL_Q == 30
		.def	__IQ30sqrt
__IQ30sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29sqrt
__IQ29sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28sqrt
__IQ28sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27sqrt
__IQ27sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26sqrt
__IQ26sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25sqrt
__IQ25sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24sqrt
__IQ24sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23sqrt
__IQ23sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22sqrt
__IQ22sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21sqrt
__IQ21sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20sqrt
__IQ20sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19sqrt
__IQ19sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18sqrt
__IQ18sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17sqrt
__IQ17sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16sqrt
__IQ16sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15sqrt
__IQ15sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14sqrt
__IQ14sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13sqrt
__IQ13sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12sqrt
__IQ12sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11sqrt
__IQ11sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10sqrt
__IQ10sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9sqrt
__IQ9sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8sqrt
__IQ8sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7sqrt
__IQ7sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6sqrt
__IQ6sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5sqrt
__IQ5sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4sqrt
__IQ4sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3sqrt
__IQ3sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2sqrt
__IQ2sqrt:
		IQNsqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1sqrt
__IQ1sqrt:
		IQNsqrt	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
