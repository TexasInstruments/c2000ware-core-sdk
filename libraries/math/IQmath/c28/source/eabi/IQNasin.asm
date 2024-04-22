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
* Author: David M. Alter, Texas Instruments Inc.
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


***********************************************************************
* References and Definitions
***********************************************************************
		.ref	_IQ29sqrt
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
		LCR		#_IQ29sqrt					; call _IQ29sqrt()
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
		.def	_IQ29asin
_IQ29asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28asin
_IQ28asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27asin
_IQ27asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26asin
_IQ26asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25asin
_IQ25asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24asin
_IQ24asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23asin
_IQ23asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22asin
_IQ22asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21asin
_IQ21asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20asin
_IQ20asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19asin
_IQ19asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18asin
_IQ18asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17asin
_IQ17asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16asin
_IQ16asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15asin
_IQ15asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14asin
_IQ14asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13asin
_IQ13asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12asin
_IQ12asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11asin
_IQ11asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10asin
_IQ10asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9asin
_IQ9asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8asin
_IQ8asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7asin
_IQ7asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6asin
_IQ6asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5asin
_IQ5asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4asin
_IQ4asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3asin
_IQ3asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2asin
_IQ2asin:
		IQNasin	GLOBAL_Q
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1asin
_IQ1asin:
		IQNasin	GLOBAL_Q
		.endif

;----------------------------------------------------------------------
; End of file
;----------------------------------------------------------------------
