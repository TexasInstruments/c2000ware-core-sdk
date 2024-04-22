;;###########################################################################
;;
;; FILE:    IQNlog.asm
;;
;; TITLE:   IQ Natural Logarithmic Math Function
;;
;;###########################################################################
;;
;; Ver  | dd-mmm-yyyy |  Who  | Description of changes
;; =====|=============|=======|==============================================
;;  1.0 |  2 Aug 2010 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;;
;;###########################################################################
;;
;; On Entry:  		ACC    = X in IQ format
;;
;; On Exit:   		ACC    = log(X) result in IQ format
;;
;; Regs Used: 		ACC, P, XT
;;					XAR2, XAR3, XAR4, XAR5, XAR6, XAR7
;;
;; Q range:    		29 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The procedure for calculating "Y = log(X)" is as follows:
;;
;;             Step 1) Check to see if Input is less than zero..
;;								
;;					   Return = most negative number possible for given Q value.
;; 
;;             Step 2) Normalize Input: 
;;
;;                     X' = X * 2^n           0.5 <= X' < 1.0
;;
;;             Step 3) Obtain Y' = log(X') using taylor series expansion:
;;
;;                     y = (X'-1)/(X'+1)     -0.3333.. <= y < -1.0
;;
;;                     Y' = 2y (1 + y^2(1/3 + y^2(1/7 + y^2(1/9 + ........)))
;;
;;             Step 4) Denormalize value to get output 
;;
;;                     Result = Y' + n*log(2)
;;
;;--------------------------------------------------------------------------
;; Cycles:	~148 (includes call & return)
;;--------------------------------------------------------------------------
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

IQNlog	.macro		q_value
		PUSH		XAR2
		PUSH		XAR3

		MOVL		XAR6,@ACC				; XAR6 = X                 (QG)
;;-------------------------------------------------------------------------------
;;	checking to see if input is < 0
;;-------------------------------------------------------------------------------
		MOVL		ACC,@ACC				; Set Z, N flags on ACC content
		BF			$90,LEQ					; Exit if X <= 0

;;-------------------------------------------------------------------------------
;; Step 1: Normalize Input:
;;-------------------------------------------------------------------------------
		CSB			ACC						; TH = normalization shift
		MOV			TL,#0					; TL = 0
		MOVL		XAR3,@XT				; XAR3 = save shift value for de-norm operation.
		LSLL		ACC,T					; ACC = Xnorm (0.5 to 0.99999 range in Q31)
		LSR64		ACC:P,#1				; ACC = Xnorm (Q30)

;;---------------------------------------------------------------------------------
;;	 y = (Xnorm - 1)/(Xnorm + 1)
;;---------------------------------------------------------------------------------
		MOV			@PL,#0x0000				; P = 1.0 	(Q30)
		MOV			@PH,#0x4000
		MOVL		@XAR7,ACC				; XAR7 = Xnorm
		ADDL		ACC,@P					; ACC  = Xnorm + 1.0		(Q30)
		MOVL		@XAR6,ACC				; XAR6 = Xnorm + 1.0 		(Q30)
		MOVL		ACC,@XAR7				; ACC  = Xnorm
		SUBL		ACC,@P					; ACC  = Xnorm - 1.0		(Q30) 

;;---------------------------------------------------------------------------------
;;		Perform Q30 Division
;;---------------------------------------------------------------------------------
		ABS			ACC						; ACC   = Num = abs(Xnorm - 1.0)
		MOVL		P,@ACC					; P     = abs(Num)
		MOVB		ACC,#0					; ACC:P = abs(0:Num)
		LSL64		ACC:P,#16
		LSL64		ACC:P,#14
		RPT			#31
		||SUBCUL	ACC,@XAR6				; Den = XAR6 = Xnorm + 1
		MOVL		ACC,@P					; ACC = abs(Result) = y		(Q30)
		NEG			ACC						; Negate result				(Q30)
		MOVL		XT,@ACC					; XT = y                    (Q30)
		ADDL		ACC,@ACC				; ACC = 2*y					(Q30)
		MOVL		XAR2,@ACC				; XAR2 = 2*y				(Q30)
		LSL64		ACC:P,#1				; ACC = 2*y                 (Q31)
		MOVL		XAR4,@ACC				; XAR4 = 2*y				(Q31)

;;--------------------------------------------------------------------------------
;;	Step 3) Obtain Y' = log(y) using taylor series expansion:
;;                     Y' = 2y (1 + y^2(1/3 + y^2(1/5 + y^2(1/7 + ........)))
;;--------------------------------------------------------------------------------
		IMPYL		P,XT,@XT
		QMPYL		ACC,XT,@XT
		LSL64		ACC:P,#4				; ACC = y^2					(Q32 = Q30 + Q30 + Q4 - 32)
		MOVL		XAR5,@ACC				; XAR5 = y^2				(Q32)

		MOV			@AL,#0x6186
		MOV			@AH,#0x0618				; ACC = 1/21				(Q31)

		MOVL		XT,@ACC					; XT = 1/21					(Q31)
		QMPYL		P,XT,@XAR5				; P  = y^2*1/21				(Q31 = Q31 + Q32 - 32)

		MOV			@AL,#0xA1AF
		MOV			@AH,#0x06BC				; ACC = 1/19				(Q31)

		ADDL		ACC,@P					; ACC = 1/19 + Y^2*1/21		(Q31)
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(1/19 + Y^2*1/21)	

		MOV			@AL,#0x8788
		MOV			@AH,#0x0787				; ACC = 1/17				(Q31)

		ADDL		ACC,@P					; ACC = 1/17 + y^2(1/19 + Y^2*1/21)
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(17 + y^2(1/19 + Y^2*1/21))

		MOV			@AL,#0x8889
		MOV			@AH,#0x0888				; ACC = 1/15				(Q31)

		ADDL		ACC,@P					; ACC = 1/15 + y^2(17 + y^2(1/19 + Y^2*1/21))
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21)))

		MOV			@AL,#0x9D8A
		MOV			@AH,#0x09D8				; ACC = 1/13				(Q31)

		ADDL		ACC,@P					; ACC = 1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21)))
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21))))

		MOV			@AL,#0xE8BA
		MOV			@AH,#0x0BA2				; ACC = 1/11				(Q31)

		ADDL		ACC,@P					; ACC = 1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21))))
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21)))))

		MOV			@AL,#0xE38E
		MOV			@AH,#0x0E38				; ACC = 1/9				(Q31)

		ADDL		ACC,@P					; ACC = 1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21)))))
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21))))))

		MOV			@AL,#0x2492
		MOV			@AH,#0x1249				; ACC = 1/7				(Q31)

		ADDL		ACC,@P					; ACC = 1/7 + y^2(1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21))))))
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(1/7 + y^2(1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21)))))))

		MOV			@AL,#0x999A
		MOV			@AH,#0x1999				; ACC = 1/5				(Q31)

		ADDL		ACC,@P					; ACC = 1/5 + y^2(1/7 + y^2(1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21)))))))
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(1/5 + y^2(1/7 + y^2(1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21))))))))

		MOV			@AL,#0xAAAB
		MOV			@AH,#0x2AAA				; ACC = 1/3				(Q31)

		ADDL		ACC,@P					; ACC = 1/3 + y^2(1/5 + y^2(1/7 + y^2(1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21))))))))
		MOVL		XT,@ACC				
		QMPYL		P,XT,@XAR5				; P = y^2(1/3 + y^2(1/5 + y^2(1/7 + y^2(1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21)))))))))

		MOVL		XT,@XAR4				; XT = 2*y  (Q31)
		QMPYL		P,XT,@P					; P = 2*y(y^2(1/3 + y^2(1/5 + y^2(1/7 + y^2(1/9 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21))))))))))
											; P = (Q30 = Q31 + Q31 - 32)

		MOVL		ACC,@XAR2				; ACC = 2*y  (Q30)
		ADDL		ACC,@P					; ACC = 2*y + 2*y(y^2(1/3 + y^2(1/5 + y^2(1/7 + y^2(1/11 + y^2(1/13 + y^2(1/15 + y^2(17 + y^2(1/19 + Y^2*1/21)))))))))
											; ACC = Y' (Q30)

		MPYB		P,T,#0					; P = 0
		.if q_value > 13
		ASR64		ACC:P,#(30 - q_value)	; ACC:P = Y' (q_value)
		.else
		ASR64		ACC:P,#16
		ASR64		ACC:P,#(14 - q_value)
		.endif
		MOVL		XAR6,@P
		MOVL		XAR7,ACC				; temp save Y'

;;---------------------------------------------------------------------------------
;;		 Step 4) Denormalize value to get output 
;;---------------------------------------------------------------------------------

		MOV			@AL,#0x0000				
		MOV			@AH,#(31 - q_value)		; ACC = (31 - q_value) << 16
		SUBL		ACC,@XAR3				; ACC = ((31 - q-value) - norm shift) << 16
		ASR64		ACC:P,#16				; ACC = (31 - q-value) - norm shift
		MOVL		XT,@ACC					; XT  = (31 - q-value) - norm shift
		MOV			@AL,#0x0BFC
		MOV			@AH,#0x58B9				; ACC = ln(2)  (Q31)
		IMPYL		P,XT,@ACC				
		QMPYL		ACC,XT,@ACC				; ACC:P = ((31 - q-value) - norm shift) * ln(2)  (Q31)
		.if q_value > 15
		LSL64		ACC:P,#16
		LSL64		ACC:P,#(q_value - 15)
		.else
		LSL64		ACC:P,#(q_value + 1)
		.endif								; ACC:P = ((31 - q-value) - norm shift) * ln(2) (q_value)
		ADDUL		P,@XAR6	
		ADDCL		ACC,@XAR7				; ACC:P = Y' + ((31 - q-value) - norm shift) * ln(2) (q_value)

		POP			XAR3
		POP			XAR2
		LRETR

		; Exit for X <= 0	
$90:
		MOV			@AL,#0x0000				; Return most negative value.
		MOV			@AH,#0x8000
		POP			XAR3
		POP			XAR2
		LRETR
		.endm


		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"

		.if	GLOBAL_Q == 30
		.def	_IQ30log
_IQ30log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	_IQ29log
_IQ29log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28log
_IQ28log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27log
_IQ27log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26log
_IQ26log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25log
_IQ25log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24log
_IQ24log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23log
_IQ23log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22log
_IQ22log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21log
_IQ21log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20log
_IQ20log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19log
_IQ19log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18log
_IQ18log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17log
_IQ17log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16log
_IQ16log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15log
_IQ15log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14log
_IQ14log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13log
_IQ13log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12log
_IQ12log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11log
_IQ11log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10log
_IQ10log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9log
_IQ9log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8log
_IQ8log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7log
_IQ7log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6log
_IQ6log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5log
_IQ5log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4log
_IQ4log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3log
_IQ3log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2log
_IQ2log:
		IQNlog	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1log
_IQ1log:
		IQNlog	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################



