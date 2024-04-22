;;###########################################################################
;;
;; FILE:	IQNmag.asm
;;
;; TITLE:	C Callable IQ Magnitude Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.4  | 17 May 2002 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNmag
;;===========================================================================
;;
;; C Usage:    extern long _IQNmag(long A, long B); // with rounding & sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;             SP-4   = B in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4
;;             XT, P, XAR0
;;
;; On Exit:    ACC    = sqrt(A*A + B*B) result in IQ format
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  To calculate the magnitute we basically use the sqrt function.
;;             The procedure for calculating "Y = sqrt(X)" is similar
;;             to calculating the inverse sqare root due to the
;;             following relationship:
;;
;;                     sqrt(X) = X * 1/sqrt(X)
;;
;;             The procedure is as follows:
;;
;;             Step 1) Calculate value to square root:
;;
;;                     X = (A*A + B*B)
;;
;;             Step 2) Normalize Input: 
;;
;;                     V = X * 2^n 
;;
;;             Step 3) Obtain initial estimate from "_IQsqrtTable" 
;;                     using the upper 8-bits of the normalized V value.
;;
;;             Step 4) Use Newton-Raphson algorithm to improve accuracy.
;;                     Repeat following equation two times. First iteration
;;                     gives 16-bit accuracy. Second iteration gives 32-bit
;;                     accuracy:
;;
;;                     Yn = Yn(1.5 - Yn*Yn*V/2)
;;
;;                     Yn = 1/sqrt(V)
;;
;;             Step 5) Caculate the square root of the normalized number:
;;
;;                     Yn = V * Yn
;;
;;             Step 6) Denormalize result and round:
;;
;;                     Y = Yn * 2^n / sqrt(2^n)
;;
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Assumptions: 
;; * Code executes from 0-wait SARAM block.
;; * _IQsqrt Tables located in seperate 0-wait SARAM or 1-wait ROM block.
;; * Stack located in seperate 0-wait SARAM block.
;; * Includes LCR/LRETR.
;;
;; Cycles = 89 (if _IQsqrt Tables in 0-wait SARAM)
;;        = 93 (if _IQsqrt Tables in 1-wait ROM)
;;
;;===========================================================================

IQNmag	.macro	q_value
		MOVL 	XT,@ACC
		IMPYL 	P,XT,@ACC
		QMPYL 	ACC,XT,@ACC 		; ACC:P = A*A
		MOVL 	XAR6,@P
		MOVL 	XAR7,@ACC 			; XAR7:XAR6 = B*B
		MOVL 	XT,*-SP[4]
		IMPYL   P,XT,*-SP[4]
		QMPYL  	ACC,XT,*-SP[4]  	; ACC:P = B*B
		ADDUL 	P,@XAR6
 		ZAP 	OVC
		ADDCL 	ACC,@XAR7  			; ACC:P = A*A + B*B          (2*q_value)
		SAT64 	ACC:P 				; ACC:P = saturated(A*A + B*B) = X
		 				
		CSB 	ACC
		LSL64 	ACC:P,T
		MOV 	@AR7,T
		CSB		ACC
		LSL64	ACC:P,T				; ACC:P = V/2                      (Q32)
		MOVL	XAR6,@ACC			; XAR6  = V/2                      (Q32)
        ASR     AH,#6
        MOVB	@AH,#0xFE,LEQ		; AR0 -> zero value if -ve or 0 input
        SUB		@AH,#254			; Scale to table offset
        MOVZ    AR0,@AH             ; AR0 -> index into _IQisqrtTable for
        							;        initial estimate of Yn
        MOV 	AH,@AR7
        ADD 	AH,@T 				; AH   = n
		TBIT	@AH,#0				; TC   = odd/even shift indicator
		LSR		AH,#1				; AH   = n/2
		MOVL	*SP++,ACC			; SP-2 = n/2
		MOVL	XAR7,#_IQsqrtTable	; XAR7 = pointer to _IQisqrtTable
		MOVL	XAR4,*+XAR7[AR0]	; (1) XAR4  = initial Yn estimate  (Q30)
		
		MOVL	XAR7,#_IQsqrtRoundSatTable	
		MOVL	XAR5,*XAR7++		; XAR5 = 1.5                       (Q30)
		MOVB	@AR0,#12,NTC		; AR0 -> 1/sqrt(2) if n == even    (Q30)
		MOVB	@AR0,#10,TC			; AR0 -> 0.5       if n == odd     (Q30)
		
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

		MOVL	XT,@XAR6
		QMPYL	ACC,XT,@ACC			; sqrt(X) = X * 1/sqrt(X)

		MOVL	XT,*+XAR7[AR0]		; Scale with 1.0 or 1/sqrt(X) or 0.5
		IMPYL	P,XT,@ACC
		QMPYL	ACC,XT,@ACC
		
		MOVL	XT,*--SP			; T = n/2
		ASR64	ACC:P,T				; Scale final result based on n/2

		LSL64 	ACC:P,#4			; Scale final result based on Q value
		ADDUL 	P,@P
		ZAP 	OVC
		ADDCL 	ACC,@ACC
		SAT64 	ACC:P 
						
		ADD		@PH,#-32768			; Round final result (ACC:P += 0x0000000080000000)
		ZAP 	OVC 				; Zero overflow counter
		ADDCL	ACC,*+XAR7[2]  		
		SAT64 	ACC:P 				; Satuate if overflow								
		LRETR
		.endm
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.ref	_IQsqrtTable
		.ref	_IQsqrtRoundSatTable
		.if	GLOBAL_Q == 30
		.def	_IQ30mag
_IQ30mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29mag
_IQ29mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28mag
_IQ28mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27mag
_IQ27mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26mag
_IQ26mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25mag
_IQ25mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24mag
_IQ24mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23mag
_IQ23mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22mag
_IQ22mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21mag
_IQ21mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20mag
_IQ20mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19mag
_IQ19mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18mag
_IQ18mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17mag
_IQ17mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16mag
_IQ16mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15mag
_IQ15mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14mag
_IQ14mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13mag
_IQ13mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12mag
_IQ12mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11mag
_IQ11mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10mag
_IQ10mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9mag
_IQ9mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8mag
_IQ8mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7mag
_IQ7mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6mag
_IQ6mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5mag
_IQ5mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4mag
_IQ4mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3mag
_IQ3mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2mag
_IQ2mag:
		IQNmag	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1mag
_IQ1mag:
		IQNmag	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
