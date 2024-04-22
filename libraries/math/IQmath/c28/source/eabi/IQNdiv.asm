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
		.def	_IQ30div
_IQ30div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29div
_IQ29div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28div
_IQ28div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27div
_IQ27div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26div
_IQ26div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25div
_IQ25div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24div
_IQ24div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23div
_IQ23div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22div
_IQ22div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21div
_IQ21div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20div
_IQ20div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19div
_IQ19div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18div
_IQ18div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17div
_IQ17div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16div
_IQ16div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15div
_IQ15div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14div
_IQ14div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13div
_IQ13div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12div
_IQ12div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11div
_IQ11div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10div
_IQ10div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9div
_IQ9div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8div
_IQ8div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7div
_IQ7div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6div
_IQ6div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5div
_IQ5div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4div
_IQ4div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3div
_IQ3div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2div
_IQ2div:
		IQNdiv	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1div
_IQ1div:
		IQNdiv	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
