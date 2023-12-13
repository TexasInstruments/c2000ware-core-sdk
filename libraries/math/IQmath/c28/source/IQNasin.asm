***********************************************************************
* File: IQNasin.asm
*
* Description: IQmath function for inverse sine
*
* Devices: C28x family
*
* Function Prototype: long IQNasin(long)
*
* C Useage: y = IQNasin(x);
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
* References and Definitions
***********************************************************************
		.ref	__IQ29sqrt
		.ref	_IQasinTable

		.asg	XT, Xsign
		.asg	T, sign
		.asg	XAR5, XiTransform
		.asg	AR5, iTransform
		.asg	XAR6, x
		.asg	XAR6, y
		.asg	XAR7, c

TaylorSeriesOrder	.set	5


***********************************************************************
* Macro start
***********************************************************************
IQNasin:	.macro	q_value

;----------------------------------------------------------------------
; Miscellaneous initialization
;----------------------------------------------------------------------
		SETC	SXM							; enable sign-extension

;----------------------------------------------------------------------
; Convert x to I3Q29 format
;----------------------------------------------------------------------
		.if q_value == 29
		;do nothing
		.elseif q_value >= 13
		LSL		ACC, (29 - q_value)
		.else
		LSL		ACC, #16
		LSL		ACC, (13 - q_value)
		.endif

;----------------------------------------------------------------------
; Determine if x<0 (we will apply the identity sin(-x) = -sin(x))     
;----------------------------------------------------------------------

		MOV		sign, #1					; assume sign = 1
		BF		L1, GEQ						; branch if x >= 0
		MOV		sign, #(-1)					; sign = -1
		NEG		ACC							; x = -x
L1:
		MOVL	x, ACC						; save x
		PUSH	Xsign						; save sign on stack

;----------------------------------------------------------------------
; If x > 0.5, we need to apply the transform
;----------------------------------------------------------------------
		MOVB	XiTransform, #0				; assume no transform needed
		SUB		ACC, #2000h << 15			; subtract _IQ29(0.5) from x
		BF		L2, LT						; branch if x < 0.5

;----------------------------------------------------------------------
; Apply the transform:  x = _IQ29sqrt( (_IQ29(1.0) - x) >> 1 )
;----------------------------------------------------------------------
		MOV		ACC, #4000h << 15			; ACC = _IQ29(1.0)
		SUBL	ACC, x						; subtract x
		SFR		ACC, 1						; shift right by 1		
		LCR		#__IQ29sqrt					; call _IQ29sqrt()
		MOVL	x, ACC						; save x
		MOVB	XiTransform, #1				; iTransform = 1

;----------------------------------------------------------------------
; Determine the lookup table index.  The table contains 2^N+1 = 17 points
; over the interval 0 to 0.5, inclusive (i.e., pt.0 = 0, pt.17 = 0.5).
; Therefore:
;     index = bits(28:24) of (x + half the interval)
;           = bits(28:24) of [x + (0.5/2^N)/2]
;           = bits(28:24) of [x + (0.5/2^4)/2]
;           = bits(28:24) of [x + 0.015625]
;
; LutIndex = ((x + _IQ29(0.015625)) >> 24) & 0x001F;
;----------------------------------------------------------------------
L2:
		MOVL	ACC, x						; load x
		ADD		ACC, #0100h << 15			; add _IQ29(0.015625)
		MOV		T,#24						; T = 24
		ASRL	ACC,T						; ACC >> 24
		ANDB	AL, #001fh					; ACC = LutIndex

;----------------------------------------------------------------------
; Setup the coefficient pointer
; c = &IQasinTable[0] + (TaylorSeriesOrder * LutIndex)
;----------------------------------------------------------------------
		MOV		T,AL						; T = LutIndex
		MPYB	ACC, T, #TaylorSeriesOrder	; ACC = TaylorSeriesOrder * LutIndex 
		MOVL	c, #_IQasinTable			; c = &IQasinTable[0]
		LSL		ACC, 1						; shift offset by 1 since offset is for 32-bit data values
		ADDL	c, ACC						; c = &IQasinTable[0] + (TaylorSeriesOrder * LutIndex)

;----------------------------------------------------------------------
; Perform the computations:
; y = _IQ29mpy((_IQ29mpy((_IQ29mpy((_IQ29mpy(*c++, x) + *c++), x) + *c++) , x) + *c++), x) + *c;
;----------------------------------------------------------------------
		MOVL	XT,*c++
		IMPYL	P,XT,x
		QMPYL	ACC,XT,x
		LSL64	ACC:P,#3	; _IQ29mpy(*c++, x)

		ADDL	ACC,*c++	; _IQ29mpy(*c++, x) + *c++

		MOVL	XT,ACC
		IMPYL	P,XT,x
		QMPYL	ACC,XT,x
		LSL64	ACC:P,#3	; _IQ29mpy((_IQ29mpy(*c++, x) + *c++), x)

		ADDL	ACC,*c++	; _IQ29mpy((_IQ29mpy(*c++, x) + *c++), x) + *c++

		MOVL	XT,ACC
		IMPYL	P,XT,x
		QMPYL	ACC,XT,x
		LSL64	ACC:P,#3	; _IQ29mpy((_IQ29mpy((_IQ29mpy(*c++, x) + *c++), x) + *c++) , x)

		ADDL	ACC,*c++	; _IQ29mpy((_IQ29mpy((_IQ29mpy(*c++, x) + *c++), x) + *c++) , x) + *c++

		MOVL	XT,ACC
		IMPYL	P,XT,x
		QMPYL	ACC,XT,x
		LSL64	ACC:P,#3	; _IQ29mpy((_IQ29mpy((_IQ29mpy((_IQ29mpy(*c++, x) + *c++), x) + *c++) , x) + *c++), x)

		ADDL	ACC,*+c[0]	; _IQ29mpy((_IQ29mpy((_IQ29mpy((_IQ29mpy(*c++, x) + *c++), x) + *c++) , x) + *c++), x) + *c

;----------------------------------------------------------------------
; Further computation needed if the transform was applied:
;     y = _IQ29(pi/2) - (y << 1);
;----------------------------------------------------------------------
		TBIT	iTransform, #0				; test bit 0
		SBF		L3, NTC						; branch if transform not applied

		LSL		ACC, 1						; ACC = y << 1
		MOVL	y, ACC						; store (y << 1)
		MOV		AH, #12867
		MOV		AL, #63144					; ACC = _IQ29(pi/2)
		SUBL	ACC, y						; ACC = _IQ29(pi/2) - (y << 1)

;----------------------------------------------------------------------
; Apply the sign, convert back to original IQ format, and return:
;     return((sign * y) >> (29 - GLOBAL_Q))
;----------------------------------------------------------------------
L3:    
		POP		Xsign						; retrieve the sign
		MOVX	TL, sign					; get the XT properly sign extended
		IMPYL	ACC, XT, ACC				; ACC = sign * y

		.if q_value == 29
		;do nothing
		.elseif q_value >= 13
		SFR		ACC, (29 - q_value)			; ACC = (sign * y) >> (29 - GLOBAL_Q)
		.else
		SFR		ACC, #16
		SFR		ACC, (13 - q_value)			; ACC = (sign * y) >> (29 - GLOBAL_Q)
		.endif

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
		.def	__IQ29asin
__IQ29asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	__IQ28asin
__IQ28asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	__IQ27asin
__IQ27asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	__IQ26asin
__IQ26asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	__IQ25asin
__IQ25asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	__IQ24asin
__IQ24asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	__IQ23asin
__IQ23asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	__IQ22asin
__IQ22asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	__IQ21asin
__IQ21asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	__IQ20asin
__IQ20asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	__IQ19asin
__IQ19asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	__IQ18asin
__IQ18asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	__IQ17asin
__IQ17asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	__IQ16asin
__IQ16asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	__IQ15asin
__IQ15asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	__IQ14asin
__IQ14asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	__IQ13asin
__IQ13asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	__IQ12asin
__IQ12asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	__IQ11asin
__IQ11asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	__IQ10asin
__IQ10asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	__IQ9asin
__IQ9asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	__IQ8asin
__IQ8asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	__IQ7asin
__IQ7asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	__IQ6asin
__IQ6asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	__IQ5asin
__IQ5asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	__IQ4asin
__IQ4asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	__IQ3asin
__IQ3asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	__IQ2asin
__IQ2asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	__IQ1asin
__IQ1asin:
		IQNasin	GLOBAL_Q
		.endif

;----------------------------------------------------------------------
; End of file
;----------------------------------------------------------------------
