;;###########################################################################
;;
;; FILE:	IQNatan2.asm
;;
;; TITLE:	C Callable IQ Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.3  | 19 Nov 2001 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;; 1.4  | 17 May 2002 | A. T. | Added note that a value of Q30 is not
;;      |             |       | feasible for this operation. Q range is
;;      |             |       | limited to Q29 to Q1.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################
;;#############################################################################
;;!
;;! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
;;!	All rights reserved not granted herein.
;;!	Limited License.
;;!
;;! Texas Instruments Incorporated grants a world-wide, royalty-free,
;;! non-exclusive license under copyrights and patents it now or hereafter
;;! owns or controls to make, have made, use, import, offer to sell and sell
;;! ("Utilize") this software subject to the terms herein. With respect to the
;;! foregoing patent license, such license is granted solely to the extent that
;;! any such patent is necessary to Utilize the software alone. The patent
;;! license shall not apply to any combinations which include this software,
;;! other than combinations with devices manufactured by or for TI 
;;! ("TI Devices").
;;! No hardware patent is licensed hereunder.
;;!
;;! Redistributions must preserve existing copyright notices and reproduce this
;;! license (including the above copyright notice and the disclaimer and
;;! (if applicable) source code license limitations below) in the documentation
;;!  and/or other materials provided with the distribution.
;;!
;;! Redistribution and use in binary form, without modification, are permitted
;;! provided that the following conditions are met:
;;!
;;! * No reverse engineering, decompilation, or disassembly of this software is 
;;! permitted with respect to any software provided in binary form.
;;! * Any redistribution and use are licensed by TI for use only 
;;!   with TI Devices.
;;! * Nothing shall obligate TI to provide you with source code for the 
;;!   software licensed and provided to you in object code.
;;!
;;! If software source code is provided to you, modification and redistribution
;;! of the source code are permitted provided that the following conditions 
;;! are met:
;;!
;;! * any redistribution and use of the source code, including any resulting
;;!   derivative works, are licensed by TI for use only with TI Devices.
;;! * any redistribution and use of any object code compiled from the source
;;!   code and any resulting derivative works, are licensed by TI for use 
;;!   only with TI Devices.
;;!
;;! Neither the name of Texas Instruments Incorporated nor the names of its
;;! suppliers may be used to endorse or promote products derived from this 
;;! software without specific prior written permission.
;;#############################################################################

;;===========================================================================
;; Function:   _IQNatan2
;;===========================================================================
;;
;; C Usage:    extern long _IQNatan2(long Y, long X);
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = Y in IQ format
;;             SP-4   = X in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4, XAR0, XT, P
;;
;; On Exit:    ACC    = Radian result in IQ format
;;                      if( X == 0.0 and Y == 0.0 ), ACC = 0.0
;;                      if( Y >= 0.0 ), 0.0 <= ACC <= PI
;;                      if( Y <  0.0 ), -PI < ACC < 0.0
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
;;                        if( Y < 0 )
;;                            Angle = -Angle
;;
;;---------------------------------------------------------------------------
;; Benchmark:
;; * Code executes from 0-wait SARAM block.
;; * _IQatan2Table & _IQdivTable located in seperate SARAM or ROM block.
;; * Stack located in seperate SARAM block.
;; * Includes LCR/LRETR.
;;
;; Cycles = 108 (if       Q == 30 and _IQatan2Table & _IQdivTable in 0-wait SARAM)
;;        = 109 (if 16 <= Q <= 29 and _IQatan2Table & _IQdivTable in 0-wait SARAM)
;;        = 112 (if  1 <= Q <= 15 and _IQatan2Table & _IQdivTable in 0-wait SARAM)
;; Cycles = 114 (if       Q == 30 and _IQatan2Table & _IQdivTable in 1-wait ROM)
;;        = 115 (if 16 <= Q <= 29 and _IQatan2Table & _IQdivTable in 1-wait ROM)
;;        = 118 (if  1 <= Q <= 15 and _IQatan2Table & _IQdivTable in 1-wait ROM)
;;
;;===========================================================================

IQNatan2	.macro	q_value
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
		TBIT	*-SP[5],#15				; Test if(Y < 0)
		NEGTC	ACC						; if(Y < 0), ACC = arctan(Y,X)
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
		.def	__IQ30atan2
__IQ30atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29atan2
__IQ29atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28atan2
__IQ28atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27atan2
__IQ27atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26atan2
__IQ26atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25atan2
__IQ25atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24atan2
__IQ24atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23atan2
__IQ23atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22atan2
__IQ22atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21atan2
__IQ21atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20atan2
__IQ20atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19atan2
__IQ19atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18atan2
__IQ18atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17atan2
__IQ17atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16atan2
__IQ16atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15atan2
__IQ15atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14atan2
__IQ14atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13atan2
__IQ13atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12atan2
__IQ12atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11atan2
__IQ11atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10atan2
__IQ10atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9atan2
__IQ9atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8atan2
__IQ8atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7atan2
__IQ7atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6atan2
__IQ6atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5atan2
__IQ5atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4atan2
__IQ4atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3atan2
__IQ3atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2atan2
__IQ2atan2:
		IQNatan2	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1atan2
__IQ1atan2:
		IQNatan2	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
