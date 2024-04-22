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
		.def	_IQ30exp
_IQ30exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29exp
_IQ29exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28exp
_IQ28exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27exp
_IQ27exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26exp
_IQ26exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25exp
_IQ25exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24exp
_IQ24exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23exp
_IQ23exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22exp
_IQ22exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21exp
_IQ21exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20exp
_IQ20exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19exp
_IQ19exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18exp
_IQ18exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17exp
_IQ17exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16exp
_IQ16exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15exp
_IQ15exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14exp
_IQ14exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13exp
_IQ13exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12exp
_IQ12exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11exp
_IQ11exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10exp
_IQ10exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9exp
_IQ9exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8exp
_IQ8exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7exp
_IQ7exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6exp
_IQ6exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5exp
_IQ5exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4exp
_IQ4exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3exp
_IQ3exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2exp
_IQ2exp:
		IQNexp	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1exp
_IQ1exp:
		IQNexp	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
