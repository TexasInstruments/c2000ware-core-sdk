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
;;      |             |       |       tools support an __IQmpy(..) intrinsic
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
		.def	__IQ30mpy
__IQ30mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29mpy
__IQ29mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28mpy
__IQ28mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27mpy
__IQ27mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26mpy
__IQ26mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25mpy
__IQ25mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24mpy
__IQ24mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23mpy
__IQ23mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22mpy
__IQ22mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21mpy
__IQ21mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20mpy
__IQ20mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19mpy
__IQ19mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18mpy
__IQ18mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17mpy
__IQ17mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16mpy
__IQ16mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15mpy
__IQ15mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14mpy
__IQ14mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13mpy
__IQ13mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12mpy
__IQ12mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11mpy
__IQ11mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10mpy
__IQ10mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9mpy
__IQ9mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8mpy
__IQ8mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7mpy
__IQ7mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6mpy
__IQ6mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5mpy
__IQ5mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4mpy
__IQ4mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3mpy
__IQ3mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2mpy
__IQ2mpy:
		IQNmpy	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1mpy
__IQ1mpy:
		IQNmpy	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
