;;###########################################################################
;;
;; FILE:	IQNint.asm
;;
;; TITLE:	C Callable IQ Integer Math Function
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
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNint
;;===========================================================================
;;
;; C Usage:    extern long _IQint(long A);   // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;
;; Regs Used:  XT
;;
;; On Exit:    ACC    = integer portion of A stored as "long"
;;                       
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The integer portion of the IQ number is calculated
;;             as follows:
;;
;;                integer = A >> q_value;
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 15 (includes LCR/LRETR) 
;;
;;---------------------------------------------------------------------------
		
IQNint	.macro	q_value
		SETC 	OVM 					; Turn overflow mode on
		CLRC 	TC 						; Clear sign flag
		ABSTC	ACC 					; Take abs value and set sign
		MOV 	@T,#q_value				
		ASRL 	ACC,T					; ACC = ACC >> q_value
		NEGTC 	ACC 					; Negate if sign set
		CLRC 	OVM 					; Turn overflow mode off
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	_IQ30int
_IQ30int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29int
_IQ29int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28int
_IQ28int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27int
_IQ27int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26int
_IQ26int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25int
_IQ25int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24int
_IQ24int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23int
_IQ23int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22int
_IQ22int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21int
_IQ21int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20int
_IQ20int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19int
_IQ19int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18int
_IQ18int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17int
_IQ17int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16int
_IQ16int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15int
_IQ15int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14int
_IQ14int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13int
_IQ13int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12int
_IQ12int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11int
_IQ11int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10int
_IQ10int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9int
_IQ9int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8int
_IQ8int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7int
_IQ7int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6int
_IQ6int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5int
_IQ5int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4int
_IQ4int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3int
_IQ3int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2int
_IQ2int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1int
_IQ1int:
		IQNint	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
