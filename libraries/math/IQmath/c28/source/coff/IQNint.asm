;;###########################################################################
;;
;; FILE:	IQNint.asm
;;
;; TITLE:	C Callable IQ Integer Math Function
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
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNint
;;===========================================================================
;;
;; C Usage:    extern long _IQint(long A);   // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;
;; Regs Used:  XT
;;
;; On Exit:    ACC    = integer portion of A stored as "long"
;;                       
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The integer portion of the IQ number is calculated
;;             as follows:
;;
;;                integer = A >> q_value;
;;			
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 15 (includes LCR/LRETR) 
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
		
IQNint	.macro	q_value
		SETC 	OVM 					; Turn overflow mode on
		CLRC 	TC 						; Clear sign flag
		ABSTC	ACC 					; Take abs value and set sign
		MOV 	@T,#q_value				
		ASRL 	ACC,T					; ACC = ACC >> q_value
		NEGTC 	ACC 					; Negate if sign set
		CLRC 	OVM 					; Turn overflow mode off
		LRETR
		.endm		
		
		;; The value "GLOBAL_Q" needs to be supplied by the assembler
		;; using the "-dGLOBAL_Q=q_value" directive:
		.sect	"IQmath"
		.if	GLOBAL_Q == 30		
		.def	__IQ30int
__IQ30int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 29
		.def	__IQ29int
__IQ29int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28int
__IQ28int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27int
__IQ27int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26int
__IQ26int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25int
__IQ25int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24int
__IQ24int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23int
__IQ23int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22int
__IQ22int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21int
__IQ21int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20int
__IQ20int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19int
__IQ19int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18int
__IQ18int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17int
__IQ17int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16int
__IQ16int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15int
__IQ15int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14int
__IQ14int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13int
__IQ13int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12int
__IQ12int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11int
__IQ11int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10int
__IQ10int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9int
__IQ9int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8int
__IQ8int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7int
__IQ7int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6int
__IQ6int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5int
__IQ5int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4int
__IQ4int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3int
__IQ3int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2int
__IQ2int:
		IQNint	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1int
__IQ1int:
		IQNint	GLOBAL_Q
		.endif
					
;;###########################################################################
;; No More.
;;###########################################################################
