;;###########################################################################
;;
;; FILE:	IQNtoF.asm
;;
;; TITLE:	C Callable IQ to Float Math Function
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
;; Function:   _IQNtoF
;;===========================================================================
;;
;; C Usage:    extern float _IQtoF(long A);   // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;
;; Regs Used:  XT, P
;;
;; On Exit:    ACC    = IEEE 754 floating-point equivalent of A
;;                       
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  This operation converts an IQ number to the equivalent
;;             IEEE 754 Single-Precision floating-point format. This
;;             format is shown below:
;;
;;              31  30        23 22                                 0
;;             +-----------------------------------------------------+
;;             | s |      e     |                 f                  |
;;             +-----------------------------------------------------+
;;
;;             Value = (-1)^s * 2^(e-127) * 1.f
;;
;;             where: e = 1 to 254, f = 0.000000000 to ~1.0
;;                    e = 0, f = 0, s = 0, Value = 0.0
;;                    e = 0 and f != 0 case cannot occur in IQ math
;;                    e = 255 case cannot occur in IQ math
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 22 (includes LCR/LRETR) 
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
		
IQNtoF	.macro	q_value
		CSB 	ACC
		LSLL 	ACC,T
		MOVL 	P,@ACC
		XOR  	@PL,#0xFFFF
		XOR 	@PH,#0x7FFF
		MOVL 	@P,ACC,GEQ
		MOVB 	AH,#(127 + (30-q_value))
		SUBR 	@T,AH
    	MOVL 	ACC,@P
		MOVB 	@T,#0,EQ
 		ASR64 	ACC:P,#14
		AND 	@AH,#0xFF00
		ADD 	AH,@T
		LSL64 	ACC:P,#7
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	__IQ30toF
__IQ30toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29toF
__IQ29toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28toF
__IQ28toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27toF
__IQ27toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26toF
__IQ26toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25toF
__IQ25toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24toF
__IQ24toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23toF
__IQ23toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22toF
__IQ22toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21toF
__IQ21toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20toF
__IQ20toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19toF
__IQ19toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18toF
__IQ18toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17toF
__IQ17toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16toF
__IQ16toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15toF
__IQ15toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14toF
__IQ14toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13toF
__IQ13toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12toF
__IQ12toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11toF
__IQ11toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10toF
__IQ10toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9toF
__IQ9toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8toF
__IQ8toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7toF
__IQ7toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6toF
__IQ6toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5toF
__IQ5toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4toF
__IQ4toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3toF
__IQ3toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2toF
__IQ2toF:
		IQNtoF	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1toF
__IQ1toF:
		IQNtoF	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
