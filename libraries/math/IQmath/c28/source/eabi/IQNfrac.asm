;;###########################################################################
;;
;; FILE:	IQNfrac.asm
;;
;; TITLE:	C Callable IQ Fractional Math Function
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
;; 1.4d | 30 Mar 2002 | SD    | Frac was implemented as  ((A >> q_value) << q_value) - A
;;      |             |       | Hence sign was changed. Reimplemented it correctly.
;;------|-------------|-------|----------------------------------------------
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNfrac
;;===========================================================================
;;
;; C Usage:    extern long _IQfrac(long A);   // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;
;; Regs Used:  XT, XAR7
;;
;; On Exit:    ACC    = fractional portion of A stored as IQ
;;                       
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The fractional portion of the IQ number is calculated
;;             as follows:
;;
;;                frac = A - ((A >> q_value) << q_value);
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 18 (includes LCR/LRETR) 
;;
;;---------------------------------------------------------------------------
		
IQNfrac	.macro	q_value
		SETC 	OVM						; Turn overflow mode on
		CLRC 	TC						; Clear sign flag
		ABSTC	ACC						; Take abs value of ACC
		
		MOV 	@T,#q_value				; Extract the fractional bits.
		LSR64 	ACC:P,T					; P=frac bits (aligned to MSB)
		MOVB 	ACC,#0
		LSL64 	ACC:P,T					; ACC=frac bits (aligned to LSB)

		NEGTC 	ACC 					; Negate if sign set
		CLRC 	OVM 					; Clear overflow mode
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	_IQ30frac
_IQ30frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29frac
_IQ29frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28frac
_IQ28frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27frac
_IQ27frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26frac
_IQ26frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25frac
_IQ25frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24frac
_IQ24frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23frac
_IQ23frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22frac
_IQ22frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21frac
_IQ21frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20frac
_IQ20frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19frac
_IQ19frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18frac
_IQ18frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17frac
_IQ17frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16frac
_IQ16frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15frac
_IQ15frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14frac
_IQ14frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13frac
_IQ13frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12frac
_IQ12frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11frac
_IQ11frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10frac
_IQ10frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9frac
_IQ9frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8frac
_IQ8frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7frac
_IQ7frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6frac
_IQ6frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5frac
_IQ5frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4frac
_IQ4frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3frac
_IQ3frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2frac
_IQ2frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1frac
_IQ1frac:
		IQNfrac	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
