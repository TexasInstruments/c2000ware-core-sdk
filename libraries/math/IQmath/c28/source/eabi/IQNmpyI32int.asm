;;###########################################################################
;;
;; FILE:	IQNmpyI32int.asm
;;
;; TITLE:	C Callable IQ Multiply I32 Return Integer Math Function
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
;; Function:   _IQNmpyI32int
;;===========================================================================
;;
;; C Usage:    extern long _IQmpyI32int(long A, long B); // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;             SP-4   = B in 32-bit integer (long) format
;;
;; Regs Used:  XT, P
;;
;; On Exit:    ACC    = integer portion of A*B stored as "long"
;;                       
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The integer portion of the IQ*I32 number is calculated
;;             as follows:
;;
;;                integer = A*B >> q_value;
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 28 (worst case, includes LCR/LRETR) 
;;
;;---------------------------------------------------------------------------
		
IQNmpyI32int	.macro	q_value

		SETC 	OVM 					; Turn overflow mode on
		CLRC 	TC 						; Clear sign flag
		
		ABSTC	ACC
		MOVL	XT,ACC
		MOVL	ACC,*-SP[4]
		ABSTC	ACC
		
		IMPYL 	P,XT,@ACC
		QMPYL 	ACC,XT,@ACC		; ACC:P = IQ*I32   (Q=q_value)
		
		MOV 	@T,#(q_value)
		LSR64   ACC:P,T			; P=integer bits
		MOVL	ACC,P
		NEGTC   ACC
		
		CLRC 	OVM 					; Turn overflow mode off		
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	_IQ30mpyI32int
_IQ30mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29mpyI32int
_IQ29mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28mpyI32int
_IQ28mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27mpyI32int
_IQ27mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26mpyI32int
_IQ26mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25mpyI32int
_IQ25mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24mpyI32int
_IQ24mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23mpyI32int
_IQ23mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22mpyI32int
_IQ22mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21mpyI32int
_IQ21mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20mpyI32int
_IQ20mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19mpyI32int
_IQ19mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18mpyI32int
_IQ18mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17mpyI32int
_IQ17mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16mpyI32int
_IQ16mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15mpyI32int
_IQ15mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14mpyI32int
_IQ14mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13mpyI32int
_IQ13mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12mpyI32int
_IQ12mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11mpyI32int
_IQ11mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10mpyI32int
_IQ10mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9mpyI32int
_IQ9mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8mpyI32int
_IQ8mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7mpyI32int
_IQ7mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6mpyI32int
_IQ6mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5mpyI32int
_IQ5mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4mpyI32int
_IQ4mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3mpyI32int
_IQ3mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2mpyI32int
_IQ2mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1mpyI32int
_IQ1mpyI32int:
		IQNmpyI32int	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
