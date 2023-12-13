;;###########################################################################
;;
;; FILE:	IQNmpyI32frac.asm
;;
;; TITLE:	C Callable IQ Multiply I32 Return Fraction Math Function
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
;; Function:   _IQNmpyI32frac
;;===========================================================================
;;
;; C Usage:    extern long _IQmpyI32frac(long A, long B); // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;             SP-4   = B in 32-bit integer (long) format
;;
;; Regs Used:  XT, P, XAR6, XAR7
;;
;; On Exit:    ACC    = fractional portion of A*B stored as IQ
;;                       
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The fractional portion of the IQ*I32 number is calculated
;;             as follows:
;;
;;                fraction = A*B - ((A*B >> q_value) << q_value)
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 34 (worst case, includes LCR/LRETR) 
;;
;;---------------------------------------------------------------------------
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
		
IQNmpyI32frac	.macro	q_value
		SETC	OVM
		CLRC	TC

		
		ABSTC	ACC
		MOVL	XT,ACC
		MOVL	ACC,*-SP[4]
		ABSTC	ACC
		
		IMPYL 	P,XT,@ACC
		QMPYL 	ACC,XT,@ACC		; ACC:P = IQ*I32   (Q=q_value)
		
		MOV       @T,#(32-q_value) 
		LSL64     ACC:P,T		; P=frac bits (aligned to MSB)
		MOVB	  ACC,#0
		MOV       @T,#(q_value) 
		LSL64     ACC:P,T		; ACC=frac bits (aligned to LSB)
		NEGTC     ACC

		CLRC 	OVM 			; Clear overflow mode		
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	__IQ30mpyI32frac
__IQ30mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29mpyI32frac
__IQ29mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28mpyI32frac
__IQ28mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27mpyI32frac
__IQ27mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26mpyI32frac
__IQ26mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25mpyI32frac
__IQ25mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24mpyI32frac
__IQ24mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23mpyI32frac
__IQ23mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22mpyI32frac
__IQ22mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21mpyI32frac
__IQ21mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20mpyI32frac
__IQ20mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19mpyI32frac
__IQ19mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18mpyI32frac
__IQ18mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17mpyI32frac
__IQ17mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16mpyI32frac
__IQ16mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15mpyI32frac
__IQ15mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14mpyI32frac
__IQ14mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13mpyI32frac
__IQ13mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12mpyI32frac
__IQ12mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11mpyI32frac
__IQ11mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10mpyI32frac
__IQ10mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9mpyI32frac
__IQ9mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8mpyI32frac
__IQ8mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7mpyI32frac
__IQ7mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6mpyI32frac
__IQ6mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5mpyI32frac
__IQ5mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4mpyI32frac
__IQ4mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3mpyI32frac
__IQ3mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2mpyI32frac
__IQ2mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1mpyI32frac
__IQ1mpyI32frac:
		IQNmpyI32frac	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
