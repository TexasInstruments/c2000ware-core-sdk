;;###########################################################################
;;
;; FILE:	IQNfrac.asm
;;
;; TITLE:	C Callable IQ Fractional Math Function
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
;; 1.4d | 30 Mar 2002 | SD    | Frac was implemented as  ((A >> q_value) << q_value) - A
;;      |             |       | Hence sign was changed. Reimplemented it correctly.
;;------|-------------|-------|----------------------------------------------
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNfrac
;;===========================================================================
;;
;; C Usage:    extern long _IQfrac(long A);   // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;
;; Regs Used:  XT, XAR7
;;
;; On Exit:    ACC    = fractional portion of A stored as IQ
;;                       
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The fractional portion of the IQ number is calculated
;;             as follows:
;;
;;                frac = A - ((A >> q_value) << q_value);
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 18 (includes LCR/LRETR) 
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
		
IQNfrac	.macro	q_value
		SETC 	OVM						; Turn overflow mode on
		CLRC 	TC						; Clear sign flag
		ABSTC	ACC						; Take abs value of ACC
		
		MOV 	@T,#q_value				; Extract the fractional bits.
		LSR64 	ACC:P,T					; P=frac bits (aligned to MSB)
		MOVB 	ACC,#0
		LSL64 	ACC:P,T					; ACC=frac bits (aligned to LSB)

		NEGTC 	ACC 					; Negate if sign set
		CLRC 	OVM 					; Clear overflow mode
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	__IQ30frac
__IQ30frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29frac
__IQ29frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28frac
__IQ28frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27frac
__IQ27frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26frac
__IQ26frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25frac
__IQ25frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24frac
__IQ24frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23frac
__IQ23frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22frac
__IQ22frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21frac
__IQ21frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20frac
__IQ20frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19frac
__IQ19frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18frac
__IQ18frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17frac
__IQ17frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16frac
__IQ16frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15frac
__IQ15frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14frac
__IQ14frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13frac
__IQ13frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12frac
__IQ12frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11frac
__IQ11frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10frac
__IQ10frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9frac
__IQ9frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8frac
__IQ8frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7frac
__IQ7frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6frac
__IQ6frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5frac
__IQ5frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4frac
__IQ4frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3frac
__IQ3frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2frac
__IQ2frac:
		IQNfrac	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1frac
__IQ1frac:
		IQNfrac	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
