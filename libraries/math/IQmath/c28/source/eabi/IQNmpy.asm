;;###########################################################################
;;
;; FILE:	IQNmpy.asm
;;
;; TITLE:	C Callable IQ Multiply Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.2  | 11 Oct 2001 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;; 1.3  | 19 Nov 2001 | A. T. | No changes.
;; -----|-------------|-------|----------------------------------------------
;; 1.4  |  4 May 2002 | A. T. | No changes.
;;      |             |       |
;;      |             |       | Note: In CCS 2.01 and above, the codegen
;;      |             |       |       tools support an _IQmpy(..) intrinsic
;;      |             |       |       which replaces the IQNmpy(..) function.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNmpy
;;===========================================================================
;;
;; C Usage:    extern long _IQmpy(long M, long X);   // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = M in IQ format
;;             [SP-4] = X in IQ format
;;
;; Regs Used:  XT, P
;;
;; On Exit:    ACC    = M * X in IQ format
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The IQmpy operation generates a 64-bit result. The 64-bit
;;             number must then be scaled back to a 32-bit value with the 
;;             same Q value as the original inputs. For example: if Q = 27, 
;;             then the multiplication of two I5Q27 numbers results in the 
;;             following 64-bit value:
;;
;;                          I5Q27 * I5Q27 = I10Q54
;;
;;             The value is then scaled back to an I5Q27 value as follows:
;;
;;                          I5Q27 = I10Q54 >> Q
;;
;;             For some of the operations, the value is either rounded or
;;             saturated (or both) to its maximum value before scaling.
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 13 (Q >= 16, includes LCR/LRETR) 
;;          14 (Q <= 15, includes LCR/LRETR)
;;
;;---------------------------------------------------------------------------
		
IQNmpy	.macro	q_value
		MOVL	XT,@ACC					; XT = M
		IMPYL	P,XT,*-SP[4]
		QMPYL	ACC,XT,*-SP[4]			; ACC:P = M * X
		.if  q_value >= 16
		LSL64	ACC:P,#(32 - q_value)	; Scale back to required IQ value
		.endif
		.if  q_value <= 15
		LSL64	ACC:P,#16				; Scale back to required IQ value
		LSL64	ACC:P,#(16 - q_value)
		.endif
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	_IQ30mpy
_IQ30mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29mpy
_IQ29mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28mpy
_IQ28mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27mpy
_IQ27mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26mpy
_IQ26mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25mpy
_IQ25mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24mpy
_IQ24mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23mpy
_IQ23mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22mpy
_IQ22mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21mpy
_IQ21mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20mpy
_IQ20mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19mpy
_IQ19mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18mpy
_IQ18mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17mpy
_IQ17mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16mpy
_IQ16mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15mpy
_IQ15mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14mpy
_IQ14mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13mpy
_IQ13mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12mpy
_IQ12mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11mpy
_IQ11mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10mpy
_IQ10mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9mpy
_IQ9mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8mpy
_IQ8mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7mpy
_IQ7mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6mpy
_IQ6mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5mpy
_IQ5mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4mpy
_IQ4mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3mpy
_IQ3mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2mpy
_IQ2mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1mpy
_IQ1mpy:
		IQNmpy	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
