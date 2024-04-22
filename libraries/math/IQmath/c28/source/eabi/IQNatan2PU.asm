;;###########################################################################
;;
;; FILE:	IQNatan2PU.asm
;;
;; TITLE:	C Callable IQ Math Function
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
;; Function:   _IQNatan2PU
;;===========================================================================
;;
;; C Usage:    extern long _IQNatan2PU(long Y, long X);
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = Y in IQ format
;;             SP-4   = X in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4, XAR0, XT, P
;;
;; On Exit:    ACC    = Per Unit result in IQ format (0.0=0Deg, 1.0=360Deg)
;;                      if( X == 0.0 and Y == 0.0 ), ACC = 0.0
;;                      if( Y >= 0.0 ), 0.0 <= ACC <= 0.5
;;                      if( Y <  0.0 ), 0.5 < ACC < 1.0
;;
;; Q range:    29 to 1
;;
;;             Note: A value of Q30 is not feasible since the result would
;;                   saturate for angles greater then +/- 2.0 radians.
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The algorithm steps to calculate the "atan2" of the given 
;;             input X and Y is as follows:
;;
;;             Step(1):   if( abs(X) >= abs(Y) )
;;                            Numerator   = abs(Y)
;;                            Denominator = abs(X)
;;                        else
;;                            Numerator   = abs(X)
;;                            Denominator = abs(Y)
;;
;;             Step(2):   Ratio = Numerator/Denominator
;;
;;                        Note: Ratio range = 0.0 to 1.0
;;
;;             Step(3):   Use the upper 6-bits of the "Ratio" value as an
;;                        index into the table to obtain the coefficients
;;                        for a second order equation:
;;
;;                        _IQNatan2Table:
;;                             CoeffA0[0]
;;                             CoeffA1[0]
;;                             CoeffA2[0]
;;                                .
;;                                .
;;                             CoeffA0[63]
;;                             CoeffA1[63]
;;                             CoeffA2[63]
;;
;;             Step(4):   Calculate the angle using the folowing equation:
;;
;;                        arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;;                        arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;;
;;
;;             Step(5):   The final angle is determined as follows:
;;
;;                        if( X >= 0 and Y >= 0 and abs(X) >= abs(Y) )
;;                            Angle = arctan(abs(Y)/abs(X))
;;                        if( X >= 0 and Y >= 0 and abs(X) <  abs(Y) )
;;                            Angle = PI/2 - arctan(abs(X)/abs(Y))
;;                        if( X < 0  and Y >= 0 and abs(X) <  abs(Y) )
;;                            Angle = PI/2 + arctan(abs(X)/abs(Y))
;;                        if( X < 0  and Y >= 0 and abs(X) >= abs(Y) )
;;                            Angle = PI - arctan(abs(Y)/abs(X))
;;
;;             Step(6):   Convert to Per Unit (PU) value:
;;
;;                        PUangle(Ratio) = arctan(Ratio)/(2*pi)
;;                        PUangle(Ratio) = arctan(Ratio) * 0.159154943
;;                        PUangle(Ratio) = 0.0 to 0.5 
;;                        if( Y < 0 )
;;                            PUAngle(Ratio) = 1.0 - PUAngle(Ratio);
;;
;;                        PUangle(Ratio) = 0.0 (0deg) to 1.0 (360deg)
;;
;;---------------------------------------------------------------------------
;; Benchmark:
;; * Code executes from 0-wait SARAM block.
;; * _IQatan2 & _IQdiv Tables located in seperate 0-wait SARAM or 1-wait ROM block.
;; * Stack located in seperate 0-wait SARAM block.
;; * Includes LCR/LRETR.
;;
;; Cycles = 121 (if 16 <= Q <= 29 and _IQatan2 & _IQdiv Tables in 0-wait SARAM)
;;        = 124 (if  1 <= Q <= 15 and _IQatan2 & _IQdiv Tables in 0-wait SARAM)
;;
;; Cycles = 127 (if 16 <= Q <= 29 and _IQatan2Table & _IQdivTable in 1-wait ROM)
;;        = 130 (if  1 <= Q <= 15 and _IQatan2Table & _IQdivTable in 1-wait ROM)
;;
;;===========================================================================

IQNatan2PU	.macro	q_value
		;; Perform Step 1:
		SETC	OVM						; Make sure overflow mode is on
		MOVL	*SP++,ACC				; SP-6  = Y
		ABS		ACC						; ACC   = abs(Y)
		MOVL	XT,@ACC					; XT    = abs(Y)
		MOVL	ACC,*-SP[6]				; ACC   = X
		ABS		ACC						; ACC   = abs(X)
		MOVL	P,@ACC					; P     = abs(X)
		SUBL	ACC,@XT					; ACC   = abs(X) - abs(Y)
		MOVL	*SP++,ACC				; SP-4  = abs(X) - abs(Y)

		MOVL	ACC,@XT					; ACC   =  abs(Y) 
		MINL	ACC,@P					; if( abs(Y) > abs(X) ), ACC = abs(X) 
		MOVL	*SP++,ACC       		; SP-2  = Numerator
		MOVL	ACC,@P					; ACC   = abs(X)
		MAXL	ACC,@XT					; if( abs(X) < abs(Y) ), ACC = abs(Y)
										; ACC   = Denominator					
										; SP-10 = X 
										; SP-8  = Return Address
										; SP-6  = Y
										; SP-4  = abs(X) - abs(Y)
										; SP-2  = Numerator

		;; Perform Step 2:
		CSB		ACC						; Count sign bits, T = n
		LSLL	ACC,T					; ACC = Dnorm                     (Q31)
        MOVL    @XAR4,ACC				; Temp save "Dnorm"
        LSR     AH,#6
		MOVB	@AH,#0xFE,EQ			; If Den = 0, load zero value
        MOVZ    AR0,@AH             	; AR0 = index into _IQdivTable
		MOVL	XAR7,#(_IQdivTable-254) 
		MOVB	AH,#(62 - q_value)		; AH   = 62 - q_value
		SUBR	@T,AH					; T    = 62 - q_value - n
		MOVL	XAR5,@XT				; AR5H = 62 - q_value - n
		MOVL    XT,*+XAR7[AR0]  		; (1) XT    = initial Dm estimate (Q29)
		MOV		@AH,#0x4000
		MOVB	AL,#0
		MOVL	XAR6,@ACC				; XAR6 = 2.0                      (Q29)

		IMPYL	P,XT,@XAR4				; (2) 
		QMPYL	ACC,XT,@XAR4			; (2) ACC:P = Dm*Dnorm            (Q60)
		LSL64	ACC:P,#1				; (3) ACC:P = Dm*Dnorm            (Q61)
		SUBL	ACC,@XAR6				; (4) ACC   = Dm*Dnorm - 2.0      (Q29)
		NEG		ACC						; (5) ACC   = 2.0 - Dm*Dnorm      (Q29)
		IMPYL	P,XT,@ACC				; (6) 
		QMPYL	ACC,XT,@ACC				; (6) ACC:P = Dm(2.0 - Dm*Dnorm)  (Q58) 
		LSL64	ACC:P,#3 				; (7) ACC:P = Dm(2.0 - Dm*Dnorm)  (Q61)

		MOVL    XT,@ACC  				; (1) XT    = Dm                  (Q29)	
		IMPYL	P,XT,@XAR4				; (2) 
		QMPYL	ACC,XT,@XAR4			; (2) ACC:P = Dm*Dnorm            (Q60)
		LSL64	ACC:P,#1				; (3) ACC:P = Dm*Dnorm            (Q61)
		SUBL	ACC,@XAR6				; (4) ACC   = Dm*Dnorm - 2.0      (Q29)
		NEG		ACC						; (5) ACC   = 2.0 - Dm*Dnorm      (Q29)
		IMPYL	P,XT,@ACC				; (6) 
		QMPYL	ACC,XT,@ACC				; (6) ACC:P = Dm(2.0 - Dm*Dnorm)  (Q58) 
		LSL64	ACC:P,#3 				; (7) ACC:P = Dm(2.0 - Dm*Dnorm)  (Q61)
				
		MOVL    XT,*-SP[2] 				; XT = Numerator
		IMPYL   P,XT,@ACC
		QMPYL   ACC,XT,@ACC				; ACC:P = N * Dm
		LSL64	ACC:P,#2
		MOVL    XT,@XAR5				; T = 62 - q_value - n
		ASR64	ACC:P,T					; scale back result
										; P = Ratio in IQ format
		;; Perform Step 3:
		MOVL	XT,@P					; XT  = Ratio
		MOVB	ACC,#64					; ACC = 64 = Elements In Table
		IMPYL	P,XT,@ACC
		QMPYL	ACC,XT,@ACC				; ACC:P = 64*Ratio
		.if q_value >= 16
		LSL64	ACC:P,#(32 - q_value) 	; ACC = int(64*Ratio)
		.else
		LSL64	ACC:P,#16
		LSL64	ACC:P,#(16 - q_value) 	; ACC = int(64*Ratio)
		.endif
		MPY		P,@AL,#6				; P = 6 * int(64*Ratio)	
		MOVZ	AR0,@PL					; AR0 = _IQatan2Table index
		MOVL	XAR5,#_IQatan2Table		; Point to A0
		MOVL	XAR6,#_IQatan2Table+2 	; Point to A1
		MOVL	XAR7,#_IQatan2Table+4	; Point to A2

		;; Perform Step 4:		
		IMPYL	P,XT,*+XAR7[AR0]
		QMPYL	ACC,XT,*+XAR7[AR0]		; ACC:P = A2*Ratio                   (q_value + Q30)
		.if q_value >= 16
		LSL64	ACC:P,#(32-q_value)		; ACC   = A2*Ratio                   (Q30)
		.else
		LSL64	ACC:P,#16
		LSL64	ACC:P,#(16-q_value)		; ACC   = A2*Ratio                   (Q30)
		.endif
		ADDL	ACC,*+XAR6[AR0]			; ACC   = A1 + A2*Ratio              (Q30) 
		IMPYL	P,XT,@ACC
		QMPYL	ACC,XT,@ACC				; ACC:P = Ratio(A1 + A2*Ratio)       (q_value + Q30)
		.if q_value >= 16
		LSL64	ACC:P,#(32-q_value)		; ACC:P = Ratio(A1 + A2*Ratio)       (Q30)
		.else
		LSL64	ACC:P,#16
		LSL64	ACC:P,#(16-q_value)		; ACC:P = Ratio(A1 + A2*Ratio)       (Q30)
		.endif
		ADDL	ACC,*+XAR5[AR0]			; ACC   = A0 + Ratio(A1 + A2*Ratio)  (Q30) 	
		.if (q_value >= 14) & (q_value <= 29)
		LSR64	ACC:P,#(30-q_value)		; ACC   = A0 + Ratio(A1 + A2*Ratio)  (q_value)	  		
		.endif
		.if q_value <= 13
		LSR64	ACC:P,#16	  		
		LSR64	ACC:P,#(14-q_value)		; ACC   = A0 + Ratio(A1 + A2*Ratio)  (q_value)	  		
		.endif

		;; Perform Step 5:
		MOVL	XAR7,#(_IQatan2HalfPITable + q_value*2)
		MOVL	XAR6,*XAR7				; XAR6 =  PI/2
		MOVL	P,@ACC					; P    =  arctan(Ratio)
		NEG		ACC						; ACC  = -arctan(Ratio)
		TBIT	*-SP[9],#15				; Test if(X >= 0)
		MOVL	@P,ACC,NTC				; if(X >= 0), P = -arctan(Ratio)
		MOVL	ACC,@P
		NEG		ACC						; ACC = -P
		TBIT	*-SP[3],#15				; Test if(abs(X) >= abs(Y))
		MOVL	@P,ACC,NTC				; if(abs(X) >= abs(Y)), P = -P

		MOVL	ACC,@XAR6				; ACC =  PI/2
		NEG		ACC						; ACC = -PI/2
		TBIT	*-SP[9],#15				; Test if(X < 0)
		NEGTC	ACC						; if(X < 0), ACC = PI/2
		ADDL	ACC,@XAR6				; ACC = ACC + PI/2
		TBIT	*-SP[3],#15				; Test if(abs(X) >= abs(Y))
		MOVL	@XAR6,ACC,NTC			; if(abs(X) >= abs(Y)), XAR6 = ACC
		MOVL	ACC,@XAR6
		ADDL	ACC,@P					; ACC = arctan(abs(Y),X)
		
		;; Perform Step 6:
		MOVL	XT,@ACC
		MOV		@PL,#0x60DC				; P = 1/(2*pi)       (Q32)
		MOV		@PH,#0x28BE
		QMPYL	P,XT,@P					; P = arctan(Ratio) * 1/(2*pi) = PUangle (q_value)
		.if q_value <= 15				; ACC = 1.0         (q_value)
		MOV		@AL,#(1 << q_value)
		MOV 	@AH,#0x0000
		.endif
		.if q_value == 16
		MOV		@AL,#0x0000
		MOV 	@AH,#0x0001
		.endif
		.if q_value >= 17
		MOV 	@AL,#0x0000
		MOV		@AH,#(1 << (q_value - 16))
		.endif
		SUBL	ACC,@P					; ACC = 1.0 - PUangle
		TBIT	*-SP[5],#15				; Test if(Y < 0)
		MOVL	@P,ACC,TC				; if(Y < 0), P = 1.0 - PUangle
		MOVL	ACC,@P					; ACC = PUangle

		SUBB	SP,#6					; Deallocate stack
		CLRC	OVM						; Turn off overflow mode
		LRETR		
		.endm
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.ref	_IQatan2HalfPITable
		.ref	_IQatan2Table
		.ref	_IQdivTable
				
		.if	GLOBAL_Q == 30
		.def	_IQ30atan2PU
_IQ30atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29atan2PU
_IQ29atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28atan2PU
_IQ28atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27atan2PU
_IQ27atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26atan2PU
_IQ26atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25atan2PU
_IQ25atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24atan2PU
_IQ24atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23atan2PU
_IQ23atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22atan2PU
_IQ22atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21atan2PU
_IQ21atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20atan2PU
_IQ20atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19atan2PU
_IQ19atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18atan2PU
_IQ18atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17atan2PU
_IQ17atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16atan2PU
_IQ16atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15atan2PU
_IQ15atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14atan2PU
_IQ14atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13atan2PU
_IQ13atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12atan2PU
_IQ12atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11atan2PU
_IQ11atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10atan2PU
_IQ10atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9atan2PU
_IQ9atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8atan2PU
_IQ8atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7atan2PU
_IQ7atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6atan2PU
_IQ6atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5atan2PU
_IQ5atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4atan2PU
_IQ4atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3atan2PU
_IQ3atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2atan2PU
_IQ2atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1atan2PU
_IQ1atan2PU:
		IQNatan2PU	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
