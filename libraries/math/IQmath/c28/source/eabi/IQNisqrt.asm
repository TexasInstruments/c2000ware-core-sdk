;;###########################################################################
;;
;; FILE:	IQNisqrt.asm
;;
;; TITLE:	C Callable IQ Inverse Square Root Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date     | Who   | Description of changes
;; =====|==============|=======|=============================================
;; 1.2  | 11 Oct 2001  | A. T. | Original Release.
;; -----|--------------|-------|---------------------------------------------
;; 1.3  | 19 Nov 2001  | A. T. | Improved accuracy.
;; -----|--------------|-------|---------------------------------------------
;; 1.4  | 17 May 2002  | A. T. | Corrected cycle benchmarks.
;; -----|--------------|-------|---------------------------------------------
;;      |              |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNisqrt
;;===========================================================================
;;
;; C Usage:    extern long _IQNisqrt(long X); // with saturation and rounding
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = Val in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4
;;             XT, P, XAR0
;;
;; On Exit:    ACC    = 1/sqrt(X) result in IQ format
;;             ACC    = 0 if input is -ve or 0
;;             ACC    = max value "0x7FFFFFFF" if result saturates
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The procedure for calculating "Y = 1/sqrt(X)" is as follows:
;;
;;             Step 1) Normalize Input: 
;;
;;                     V = X * 2^n 
;;
;;             Step 2) Obtain initial estimate from "_IQisqrtTable" 
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
;;             Step 4) Denormalize result, round and saturate:
;;
;;                     Y = Yn / sqrt(2^n)
;;        
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Assumptions: 
;; * Code executes from 0-wait SARAM block.
;; * _IQisqrt Tables located in seperate 0-wait SARAM or 1-wait ROM block.
;; * Stack located in seperate 0-wait SARAM block.
;; * Includes LCR/LRETR.
;;
;; Cycles = 66 (30 >= Q >= 18 if _IQisqrt Tables in 0-wait SARAM)
;;          67 (17 >= Q >= 0  if _IQisqrt Tables in 0-wait SARAM)
;;
;; Cycles = 73 (30 >= Q >= 18 if _IQisqrt Tables in 1-wait ROM)
;;          74 (17 >= Q >= 0  if _IQisqrt Tables in 1-wait ROM)
;;
;;===========================================================================

IQNisqrt	.macro	q_value
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
		MOVL	XAR7,#_IQisqrtTable	; XAR7 = pointer to _IQisqrtTable
		MOVL	XAR4,*+XAR7[AR0]	; (1) XAR4  = initial Yn estimate  (Q30)
		
		MOVL	XAR7,#_IQisqrtRoundSatTable	
		MOVL	XAR5,*XAR7++		; XAR5 = 1.5                       (Q30)
		.if (q_value & 0x0001) == 0	; Q even
		MOVB	@AR0,#12,NTC		; AR0 -> 1/sqrt(2) if n == even    (Q30)
		MOVB	@AR0,#8,TC			; AR0 -> 1.0       if n == odd     (Q30)
		.endif
		.if (q_value & 0x0001) == 1	; Q odd
		MOVB	@AR0,#12,TC			; AR0 -> 1/sqrt(2) if n == odd     (Q30)
		MOVB	@AR0,#10,NTC		; AR0 -> 0.5       if n == even    (Q30)
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

		MOVL	XT,*+XAR7[AR0]		; Scale with 1.0 or 1/sqrt(X) or 0.5
		IMPYL	P,XT,@ACC
		QMPYL	ACC,XT,@ACC
		
		.if	q_value == 30			; Scale final result based on Q value
		LSL64	ACC:P,#2
		.endif
		.if	q_value == 29
		LSL64	ACC:P,#1
		.endif
		.if	(q_value >= 18) & (q_value <= 28)
		ASR64	ACC:P,#((86 - q_value*3)/2)
		.endif
		.if	(q_value >= 7) & (q_value <= 17)
		ASR64	ACC:P,#16
		ASR64	ACC:P,#(((86 - q_value*3)/2) - 16)
		.endif
		.if	q_value <= 6
		ASR64	ACC:P,#16
		ASR64	ACC:P,#16
		ASR64	ACC:P,#(((86 - q_value*3)/2) - 32)
		.endif
		
		ASR64	ACC:P,#16
		MOVL	XT,*--SP			; T = n/2
		LSL64	ACC:P,T				; Scale final result based on n/2
		ADDUL	P,*+XAR7[0]			; Round result
		ADDCL	ACC,*+XAR7[2]
		MINL	ACC,*+XAR7[6]		; Saturate if exceeds max pos value
		MINCUL	P,*+XAR7[4]
		LSL64	ACC:P,#16
		LRETR
		.endm
 		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.ref	_IQisqrtTable
		.ref	_IQisqrtRoundSatTable
		.if	GLOBAL_Q == 30
		.def	_IQ30isqrt
_IQ30isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29isqrt
_IQ29isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28isqrt
_IQ28isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27isqrt
_IQ27isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26isqrt
_IQ26isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25isqrt
_IQ25isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24isqrt
_IQ24isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23isqrt
_IQ23isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22isqrt
_IQ22isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21isqrt
_IQ21isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20isqrt
_IQ20isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19isqrt
_IQ19isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18isqrt
_IQ18isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17isqrt
_IQ17isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16isqrt
_IQ16isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15isqrt
_IQ15isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14isqrt
_IQ14isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13isqrt
_IQ13isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12isqrt
_IQ12isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11isqrt
_IQ11isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10isqrt
_IQ10isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9isqrt
_IQ9isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8isqrt
_IQ8isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7isqrt
_IQ7isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6isqrt
_IQ6isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5isqrt
_IQ5isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4isqrt
_IQ4isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3isqrt
_IQ3isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2isqrt
_IQ2isqrt:
		IQNisqrt	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1isqrt
_IQ1isqrt:
		IQNisqrt	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
