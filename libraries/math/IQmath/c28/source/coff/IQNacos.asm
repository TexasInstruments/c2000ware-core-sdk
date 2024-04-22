***********************************************************************
* File: IQNacos.asm
*
* Description: IQmath function for inverse cosine
*
* Devices: C28x family
*
* Function Prototype: long IQNacos(long)
*
* C Useage: y = IQNacos(x);
*
* Input Parameters: x = angle (radians)
*
* Return Value: y = result
*
* Author: DA, Texas Instruments Inc.
*
* History:
*   06/10/04 - original
*
* Notes:
*   1) IQ format is limited to I31Q1 to I3Q29 inclusive.  Formats
*      greater than Q29 are excluded since they would overflow return
*      angles greater than 2 (e.g., y = pi).
*
*   2) This function uses the identity: acos(x) = pi/2 - asin(x).
*      It simply calls IQasin(x), and then forms (pi/2 - IQasin(x))
*
***********************************************************************
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


***********************************************************************
* Macro start
***********************************************************************
IQNacos:	.macro	q_value, __IQasin

;----------------------------------------------------------------------
; Call IQasin()
;----------------------------------------------------------------------
		LCR		#__IQasin					; call _IQasin()

;----------------------------------------------------------------------
; Convert y to I1Q29 format
;----------------------------------------------------------------------
		.if q_value == 29
		;do nothing
		.elseif q_value >= 13
		LSL		ACC, (29 - q_value)
		.else
		LSL		ACC, #16
		LSL		ACC, (13 - q_value)
		.endif

		PUSH	ACC							; save y on stack

;----------------------------------------------------------------------
; Form (pi/2 - y) to apply acos(x) = pi/2 - asin(x)
;----------------------------------------------------------------------
		MOV		AH, #12867
		MOV		AL, #63144					; ACC = _IQ29(pi/2)
		SUBL	ACC, *--SP					; ACC = (pi/2 - y)

;----------------------------------------------------------------------
; Convert back to original IQ format
;----------------------------------------------------------------------
		.if q_value == 29
		;do nothing
		.elseif q_value >= 13
		SFR		ACC, (29 - q_value)
		.else
		SFR		ACC, #16
		SFR		ACC, (13 - q_value)
		.endif

;----------------------------------------------------------------------
; Return
;----------------------------------------------------------------------
		LRETR								; return

        .endm
;----------------------------------------------------------------------
; End of macro
;----------------------------------------------------------------------



***********************************************************************
* The value "GLOBAL_Q" needs to be supplied by the assembler using the
* "-dGLOBAL_Q=q_value" directive:
***********************************************************************
		.sect	"IQmath"

		.if	GLOBAL_Q == 29
		.def	__IQ29acos
		.ref	__IQ29asin
__IQ29acos:
		IQNacos	GLOBAL_Q, __IQ29asin
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28acos
		.ref	__IQ28asin
__IQ28acos:
		IQNacos	GLOBAL_Q, __IQ28asin
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27acos
		.ref	__IQ27asin
__IQ27acos:
		IQNacos	GLOBAL_Q, __IQ27asin
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26acos
		.ref	__IQ26asin
__IQ26acos:
		IQNacos	GLOBAL_Q, __IQ26asin
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25acos
		.ref	__IQ25asin
__IQ25acos:
		IQNacos	GLOBAL_Q, __IQ25asin
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24acos
		.ref	__IQ24asin
__IQ24acos:
		IQNacos	GLOBAL_Q, __IQ24asin
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23acos
		.ref	__IQ23asin
__IQ23acos:
		IQNacos	GLOBAL_Q, __IQ23asin
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22acos
		.ref	__IQ22asin
__IQ22acos:
		IQNacos	GLOBAL_Q, __IQ22asin
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21acos
		.ref	__IQ21asin
__IQ21acos:
		IQNacos	GLOBAL_Q, __IQ21asin
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20acos
		.ref	__IQ20asin
__IQ20acos:
		IQNacos	GLOBAL_Q, __IQ20asin
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19acos
		.ref	__IQ19asin
__IQ19acos:
		IQNacos	GLOBAL_Q, __IQ19asin
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18acos
		.ref	__IQ18asin
__IQ18acos:
		IQNacos	GLOBAL_Q, __IQ18asin
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17acos
		.ref	__IQ17asin
__IQ17acos:
		IQNacos	GLOBAL_Q, __IQ17asin
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16acos
		.ref	__IQ16asin
__IQ16acos:
		IQNacos	GLOBAL_Q, __IQ16asin
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15acos
		.ref	__IQ15asin
__IQ15acos:
		IQNacos	GLOBAL_Q, __IQ15asin
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14acos
		.ref	__IQ14asin
__IQ14acos:
		IQNacos	GLOBAL_Q, __IQ14asin
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13acos
		.ref	__IQ13asin
__IQ13acos:
		IQNacos	GLOBAL_Q, __IQ13asin
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12acos
		.ref	__IQ12asin
__IQ12acos:
		IQNacos	GLOBAL_Q, __IQ12asin
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11acos
		.ref	__IQ11asin
__IQ11acos:
		IQNacos	GLOBAL_Q, __IQ11asin
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10acos
		.ref	__IQ10asin
__IQ10acos:
		IQNacos	GLOBAL_Q, __IQ10asin
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9acos
		.ref	__IQ9asin
__IQ9acos:
		IQNacos	GLOBAL_Q, __IQ9asin
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8acos
		.ref	__IQ8asin
__IQ8acos:
		IQNacos	GLOBAL_Q, __IQ8asin
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7acos
		.ref	__IQ7asin
__IQ7acos:
		IQNacos	GLOBAL_Q, __IQ7asin
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6acos
		.ref	__IQ6asin
__IQ6acos:
		IQNacos	GLOBAL_Q, __IQ6asin
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5acos
		.ref	__IQ5asin
__IQ5acos:
		IQNacos	GLOBAL_Q, __IQ5asin
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4acos
		.ref	__IQ4asin
__IQ4acos:
		IQNacos	GLOBAL_Q, __IQ4asin
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3acos
		.ref	__IQ3asin
__IQ3acos:
		IQNacos	GLOBAL_Q, __IQ3asin
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2acos
		.ref	__IQ2asin
__IQ2acos:
		IQNacos	GLOBAL_Q, __IQ2asin
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1acos
		.ref	__IQ1asin
__IQ1acos:
		IQNacos	GLOBAL_Q, __IQ1asin
		.endif

;----------------------------------------------------------------------
; End of file
;----------------------------------------------------------------------
