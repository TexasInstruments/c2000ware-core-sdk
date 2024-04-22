;;###########################################################################
;;
;; FILE:	IQNmpyI32frac.asm
;;
;; TITLE:	C Callable IQ Multiply I32 Return Fraction Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.4  | 17 May 2002 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;; 1.4c | 20 Jun 2002 | A. T. | Fixed problem with function when operating
;;      |             |       | on negative values with a zero fractional
;;      |             |       | part, incorrect result was given.
;; -----|-------------|-------|----------------------------------------------
;; 1.4d | 30 Mar 2002 | SD    | Re-implemented the function without branch
;; -----|-------------|-------|----------------------------------------------
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNmpyI32frac
;;===========================================================================
;;
;; C Usage:    extern long _IQmpyI32frac(long A, long B); // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;             SP-4   = B in 32-bit integer (long) format
;;
;; Regs Used:  XT, P, XAR6, XAR7
;;
;; On Exit:    ACC    = fractional portion of A*B stored as IQ
;;                       
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The fractional portion of the IQ*I32 number is calculated
;;             as follows:
;;
;;                fraction = A*B - ((A*B >> q_value) << q_value)
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 34 (worst case, includes LCR/LRETR) 
;;
;;---------------------------------------------------------------------------
		
IQNmpyI32frac	.macro	q_value
		SETC	OVM
		CLRC	TC

		
		ABSTC	ACC
		MOVL	XT,ACC
		MOVL	ACC,*-SP[4]
		ABSTC	ACC
		
		IMPYL 	P,XT,@ACC
		QMPYL 	ACC,XT,@ACC		; ACC:P = IQ*I32   (Q=q_value)
		
		MOV       @T,#(32-q_value) 
		LSL64     ACC:P,T		; P=frac bits (aligned to MSB)
		MOVB	  ACC,#0
		MOV       @T,#(q_value) 
		LSL64     ACC:P,T		; ACC=frac bits (aligned to LSB)
		NEGTC     ACC

		CLRC 	OVM 			; Clear overflow mode		
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	_IQ30mpyI32frac
_IQ30mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29mpyI32frac
_IQ29mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28mpyI32frac
_IQ28mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27mpyI32frac
_IQ27mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26mpyI32frac
_IQ26mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25mpyI32frac
_IQ25mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24mpyI32frac
_IQ24mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23mpyI32frac
_IQ23mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22mpyI32frac
_IQ22mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21mpyI32frac
_IQ21mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20mpyI32frac
_IQ20mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19mpyI32frac
_IQ19mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18mpyI32frac
_IQ18mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17mpyI32frac
_IQ17mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16mpyI32frac
_IQ16mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15mpyI32frac
_IQ15mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14mpyI32frac
_IQ14mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13mpyI32frac
_IQ13mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12mpyI32frac
_IQ12mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11mpyI32frac
_IQ11mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10mpyI32frac
_IQ10mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9mpyI32frac
_IQ9mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8mpyI32frac
_IQ8mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7mpyI32frac
_IQ7mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6mpyI32frac
_IQ6mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5mpyI32frac
_IQ5mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4mpyI32frac
_IQ4mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3mpyI32frac
_IQ3mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2mpyI32frac
_IQ2mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1mpyI32frac
_IQ1mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
