;;###########################################################################
;;
;; FILE:	IQNrsmpy.asm
;;
;; TITLE:	C Callable IQ Multiply With Rounding & Saturation Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.2  | 11 Oct 2001 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;; 1.3  | 19 Nov 2001 | A. T. | No changes.
;; -----|-------------|-------|----------------------------------------------
;; 1.4  | 17 May 2002 | A. T. | Made correction to table pointer.
;;      |             |       | Corrected benchmark cycles.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNrsmpy
;;===========================================================================
;;
;; C Usage:    extern long _IQNrsmpy(long M, long X); // with sat & round
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
;; Cycles = 20 (Q >= 16, if Table in 0-wait SARAM, includes LCR/LRETR) 
;;          21 (Q <= 15, if Table in 0-wait SARAM, includes LCR/LRETR)
;;
;; Cycles = 26 (Q >= 16, if Table in 1-wait ROM, includes LCR/LRETR) 
;;          27 (Q <= 15, if Table in 1-wait ROM, includes LCR/LRETR)
;;
;;---------------------------------------------------------------------------

IQNrsmpy	.macro	q_value, table
		MOVL	XT,@ACC					; XT = M
		IMPYL	P,XT,*-SP[4]
		QMPYL	ACC,XT,*-SP[4]			; ACC:P = M * X
		MOVL	XAR7,#table
		ADDUL	P,*XAR7++				; Round value
		ADDCL	ACC,*XAR7++
		MINL	ACC,*+XAR7[2]			; Saturate value
		MINCUL	P,*+XAR7[0]
		MAXL	ACC,*+XAR7[6]
		MAXCUL	P,*+XAR7[4]		
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
		.ref	_IQ30mpyRndSatTable
		.def	_IQ30rsmpy
_IQ30rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ30mpyRndSatTable 
		.endif

		.if	GLOBAL_Q == 29
		.ref	_IQ29mpyRndSatTable
		.def	_IQ29rsmpy
_IQ29rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ29mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 28		
		.ref	_IQ28mpyRndSatTable
		.def	_IQ28rsmpy
_IQ28rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ28mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 27		
		.ref	_IQ27mpyRndSatTable
		.def	_IQ27rsmpy
_IQ27rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ27mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 26
		.ref	_IQ26mpyRndSatTable
		.def	_IQ26rsmpy
_IQ26rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ26mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 25
		.ref	_IQ25mpyRndSatTable
		.def	_IQ25rsmpy
_IQ25rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ25mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 24		
		.ref	_IQ24mpyRndSatTable
		.def	_IQ24rsmpy
_IQ24rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ24mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 23
		.ref	_IQ23mpyRndSatTable
		.def	_IQ23rsmpy
_IQ23rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ23mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 22
		.ref	_IQ22mpyRndSatTable
		.def	_IQ22rsmpy
_IQ22rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ22mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 21
		.ref	_IQ21mpyRndSatTable
		.def	_IQ21rsmpy
_IQ21rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ21mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 20		
		.ref	_IQ20mpyRndSatTable
		.def	_IQ20rsmpy
_IQ20rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ20mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 19
		.ref	_IQ19mpyRndSatTable
		.def	_IQ19rsmpy
_IQ19rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ19mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 18
		.ref	_IQ18mpyRndSatTable
		.def	_IQ18rsmpy
_IQ18rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ18mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 17
		.ref	_IQ17mpyRndSatTable
		.def	_IQ17rsmpy
_IQ17rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ17mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 16
		.ref	_IQ16mpyRndSatTable
		.def	_IQ16rsmpy
_IQ16rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ16mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 15
		.ref	_IQ15mpyRndSatTable
		.def	_IQ15rsmpy
_IQ15rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ15mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 14
		.ref	_IQ14mpyRndSatTable
		.def	_IQ14rsmpy
_IQ14rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ14mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 13
		.ref	_IQ13mpyRndSatTable
		.def	_IQ13rsmpy
_IQ13rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ13mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 12
		.ref	_IQ12mpyRndSatTable
		.def	_IQ12rsmpy
_IQ12rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ12mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 11
		.ref	_IQ11mpyRndSatTable
		.def	_IQ11rsmpy
_IQ11rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ11mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 10
		.ref	_IQ10mpyRndSatTable
		.def	_IQ10rsmpy
_IQ10rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ10mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 9
		.ref	_IQ9mpyRndSatTable
		.def	_IQ9rsmpy
_IQ9rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ9mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 8
		.ref	_IQ8mpyRndSatTable
		.def	_IQ8rsmpy
_IQ8rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ8mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 7		
		.ref	_IQ7mpyRndSatTable
		.def	_IQ7rsmpy
_IQ7rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ7mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 6
		.ref	_IQ6mpyRndSatTable
		.def	_IQ6rsmpy
_IQ6rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ6mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 5
		.ref	_IQ5mpyRndSatTable
		.def	_IQ5rsmpy
_IQ5rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ5mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 4
		.ref	_IQ4mpyRndSatTable
		.def	_IQ4rsmpy
_IQ4rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ4mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 3
		.ref	_IQ3mpyRndSatTable
		.def	_IQ3rsmpy
_IQ3rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ3mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 2
		.ref	_IQ2mpyRndSatTable
		.def	_IQ2rsmpy
_IQ2rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ2mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 1
		.ref	_IQ1mpyRndSatTable
		.def	_IQ1rsmpy
_IQ1rsmpy:
		IQNrsmpy	GLOBAL_Q, _IQ1mpyRndSatTable
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
