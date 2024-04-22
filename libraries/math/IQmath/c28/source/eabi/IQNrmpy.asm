;;###########################################################################
;;
;; FILE:	IQNrmpy.asm
;;
;; TITLE:	C Callable IQ Multiply With Rounding Math Function
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
;; Function:   _IQNrmpy
;;===========================================================================
;;
;; C Usage:    extern long _IQNrmpy(long M, long X); // with rounding only
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
;; Cycles = 16 (Q >= 16, if Table in 0-wait SARAM, includes LCR/LRETR) 
;;          17 (Q <= 15, if Table in 0-wait SARAM, includes LCR/LRETR)
;;
;; Cycles = 18 (Q >= 16, if Table in 1-wait ROM, includes LCR/LRETR) 
;;          19 (Q <= 15, if Table in 1-wait ROM, includes LCR/LRETR)
;;
;;---------------------------------------------------------------------------

IQNrmpy	.macro	q_value, table
		MOVL	XT,@ACC					; XT = M
		IMPYL	P,XT,*-SP[4]
		QMPYL	ACC,XT,*-SP[4]			; ACC:P = M * X
		MOVL	XAR7,#table
		ADDUL	P,*XAR7++				; Round value
		ADDCL	ACC,*XAR7++	
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
		.def	_IQ30rmpy
_IQ30rmpy:
		IQNrmpy	GLOBAL_Q, _IQ30mpyRndSatTable 
		.endif

		.if	GLOBAL_Q == 29
		.ref	_IQ29mpyRndSatTable
		.def	_IQ29rmpy
_IQ29rmpy:
		IQNrmpy	GLOBAL_Q, _IQ29mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 28		
		.ref	_IQ28mpyRndSatTable
		.def	_IQ28rmpy
_IQ28rmpy:
		IQNrmpy	GLOBAL_Q, _IQ28mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 27		
		.ref	_IQ27mpyRndSatTable
		.def	_IQ27rmpy
_IQ27rmpy:
		IQNrmpy	GLOBAL_Q, _IQ27mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 26
		.ref	_IQ26mpyRndSatTable
		.def	_IQ26rmpy
_IQ26rmpy:
		IQNrmpy	GLOBAL_Q, _IQ26mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 25
		.ref	_IQ25mpyRndSatTable
		.def	_IQ25rmpy
_IQ25rmpy:
		IQNrmpy	GLOBAL_Q, _IQ25mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 24		
		.ref	_IQ24mpyRndSatTable
		.def	_IQ24rmpy
_IQ24rmpy:
		IQNrmpy	GLOBAL_Q, _IQ24mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 23
		.ref	_IQ23mpyRndSatTable
		.def	_IQ23rmpy
_IQ23rmpy:
		IQNrmpy	GLOBAL_Q, _IQ23mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 22
		.ref	_IQ22mpyRndSatTable
		.def	_IQ22rmpy
_IQ22rmpy:
		IQNrmpy	GLOBAL_Q, _IQ22mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 21
		.ref	_IQ21mpyRndSatTable
		.def	_IQ21rmpy
_IQ21rmpy:
		IQNrmpy	GLOBAL_Q, _IQ21mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 20		
		.ref	_IQ20mpyRndSatTable
		.def	_IQ20rmpy
_IQ20rmpy:
		IQNrmpy	GLOBAL_Q, _IQ20mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 19
		.ref	_IQ19mpyRndSatTable
		.def	_IQ19rmpy
_IQ19rmpy:
		IQNrmpy	GLOBAL_Q, _IQ19mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 18
		.ref	_IQ18mpyRndSatTable
		.def	_IQ18rmpy
_IQ18rmpy:
		IQNrmpy	GLOBAL_Q, _IQ18mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 17
		.ref	_IQ17mpyRndSatTable
		.def	_IQ17rmpy
_IQ17rmpy:
		IQNrmpy	GLOBAL_Q, _IQ17mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 16
		.ref	_IQ16mpyRndSatTable
		.def	_IQ16rmpy
_IQ16rmpy:
		IQNrmpy	GLOBAL_Q, _IQ16mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 15
		.ref	_IQ15mpyRndSatTable
		.def	_IQ15rmpy
_IQ15rmpy:
		IQNrmpy	GLOBAL_Q, _IQ15mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 14
		.ref	_IQ14mpyRndSatTable
		.def	_IQ14rmpy
_IQ14rmpy:
		IQNrmpy	GLOBAL_Q, _IQ14mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 13
		.ref	_IQ13mpyRndSatTable
		.def	_IQ13rmpy
_IQ13rmpy:
		IQNrmpy	GLOBAL_Q, _IQ13mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 12
		.ref	_IQ12mpyRndSatTable
		.def	_IQ12rmpy
_IQ12rmpy:
		IQNrmpy	GLOBAL_Q, _IQ12mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 11
		.ref	_IQ11mpyRndSatTable
		.def	_IQ11rmpy
_IQ11rmpy:
		IQNrmpy	GLOBAL_Q, _IQ11mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 10
		.ref	_IQ10mpyRndSatTable
		.def	_IQ10rmpy
_IQ10rmpy:
		IQNrmpy	GLOBAL_Q, _IQ10mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 9
		.ref	_IQ9mpyRndSatTable
		.def	_IQ9rmpy
_IQ9rmpy:
		IQNrmpy	GLOBAL_Q, _IQ9mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 8
		.ref	_IQ8mpyRndSatTable
		.def	_IQ8rmpy
_IQ8rmpy:
		IQNrmpy	GLOBAL_Q, _IQ8mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 7		
		.ref	_IQ7mpyRndSatTable
		.def	_IQ7rmpy
_IQ7rmpy:
		IQNrmpy	GLOBAL_Q, _IQ7mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 6
		.ref	_IQ6mpyRndSatTable
		.def	_IQ6rmpy
_IQ6rmpy:
		IQNrmpy	GLOBAL_Q, _IQ6mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 5
		.ref	_IQ5mpyRndSatTable
		.def	_IQ5rmpy
_IQ5rmpy:
		IQNrmpy	GLOBAL_Q, _IQ5mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 4
		.ref	_IQ4mpyRndSatTable
		.def	_IQ4rmpy
_IQ4rmpy:
		IQNrmpy	GLOBAL_Q, _IQ4mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 3
		.ref	_IQ3mpyRndSatTable
		.def	_IQ3rmpy
_IQ3rmpy:
		IQNrmpy	GLOBAL_Q, _IQ3mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 2
		.ref	_IQ2mpyRndSatTable
		.def	_IQ2rmpy
_IQ2rmpy:
		IQNrmpy	GLOBAL_Q, _IQ2mpyRndSatTable
		.endif

		.if	GLOBAL_Q == 1
		.ref	_IQ1mpyRndSatTable
		.def	_IQ1rmpy
_IQ1rmpy:
		IQNrmpy	GLOBAL_Q, _IQ1mpyRndSatTable
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
