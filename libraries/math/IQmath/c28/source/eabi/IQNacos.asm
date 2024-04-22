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
*   2) This function uses the identity: acos(x) = pi/2 - asin(x).
*      It simply calls IQasin(x), and then forms (pi/2 - IQasin(x))
*
***********************************************************************


***********************************************************************
* Macro start
***********************************************************************
IQNacos:	.macro	q_value, _IQasin

;----------------------------------------------------------------------
; Call IQasin()
;----------------------------------------------------------------------
		LCR		#_IQasin					; call _IQasin()

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
		.def	_IQ29acos
		.ref	_IQ29asin
_IQ29acos:
		IQNacos	GLOBAL_Q, _IQ29asin
		.endif

		.if	GLOBAL_Q == 28		
		.def	_IQ28acos
		.ref	_IQ28asin
_IQ28acos:
		IQNacos	GLOBAL_Q, _IQ28asin
		.endif

		.if	GLOBAL_Q == 27		
		.def	_IQ27acos
		.ref	_IQ27asin
_IQ27acos:
		IQNacos	GLOBAL_Q, _IQ27asin
		.endif

		.if	GLOBAL_Q == 26
		.def	_IQ26acos
		.ref	_IQ26asin
_IQ26acos:
		IQNacos	GLOBAL_Q, _IQ26asin
		.endif

		.if	GLOBAL_Q == 25
		.def	_IQ25acos
		.ref	_IQ25asin
_IQ25acos:
		IQNacos	GLOBAL_Q, _IQ25asin
		.endif

		.if	GLOBAL_Q == 24		
		.def	_IQ24acos
		.ref	_IQ24asin
_IQ24acos:
		IQNacos	GLOBAL_Q, _IQ24asin
		.endif

		.if	GLOBAL_Q == 23
		.def	_IQ23acos
		.ref	_IQ23asin
_IQ23acos:
		IQNacos	GLOBAL_Q, _IQ23asin
		.endif

		.if	GLOBAL_Q == 22
		.def	_IQ22acos
		.ref	_IQ22asin
_IQ22acos:
		IQNacos	GLOBAL_Q, _IQ22asin
		.endif

		.if	GLOBAL_Q == 21
		.def	_IQ21acos
		.ref	_IQ21asin
_IQ21acos:
		IQNacos	GLOBAL_Q, _IQ21asin
		.endif

		.if	GLOBAL_Q == 20		
		.def	_IQ20acos
		.ref	_IQ20asin
_IQ20acos:
		IQNacos	GLOBAL_Q, _IQ20asin
		.endif

		.if	GLOBAL_Q == 19
		.def	_IQ19acos
		.ref	_IQ19asin
_IQ19acos:
		IQNacos	GLOBAL_Q, _IQ19asin
		.endif

		.if	GLOBAL_Q == 18
		.def	_IQ18acos
		.ref	_IQ18asin
_IQ18acos:
		IQNacos	GLOBAL_Q, _IQ18asin
		.endif

		.if	GLOBAL_Q == 17
		.def	_IQ17acos
		.ref	_IQ17asin
_IQ17acos:
		IQNacos	GLOBAL_Q, _IQ17asin
		.endif

		.if	GLOBAL_Q == 16
		.def	_IQ16acos
		.ref	_IQ16asin
_IQ16acos:
		IQNacos	GLOBAL_Q, _IQ16asin
		.endif

		.if	GLOBAL_Q == 15
		.def	_IQ15acos
		.ref	_IQ15asin
_IQ15acos:
		IQNacos	GLOBAL_Q, _IQ15asin
		.endif

		.if	GLOBAL_Q == 14
		.def	_IQ14acos
		.ref	_IQ14asin
_IQ14acos:
		IQNacos	GLOBAL_Q, _IQ14asin
		.endif

		.if	GLOBAL_Q == 13
		.def	_IQ13acos
		.ref	_IQ13asin
_IQ13acos:
		IQNacos	GLOBAL_Q, _IQ13asin
		.endif

		.if	GLOBAL_Q == 12
		.def	_IQ12acos
		.ref	_IQ12asin
_IQ12acos:
		IQNacos	GLOBAL_Q, _IQ12asin
		.endif

		.if	GLOBAL_Q == 11
		.def	_IQ11acos
		.ref	_IQ11asin
_IQ11acos:
		IQNacos	GLOBAL_Q, _IQ11asin
		.endif

		.if	GLOBAL_Q == 10
		.def	_IQ10acos
		.ref	_IQ10asin
_IQ10acos:
		IQNacos	GLOBAL_Q, _IQ10asin
		.endif

		.if	GLOBAL_Q == 9
		.def	_IQ9acos
		.ref	_IQ9asin
_IQ9acos:
		IQNacos	GLOBAL_Q, _IQ9asin
		.endif

		.if	GLOBAL_Q == 8
		.def	_IQ8acos
		.ref	_IQ8asin
_IQ8acos:
		IQNacos	GLOBAL_Q, _IQ8asin
		.endif

		.if	GLOBAL_Q == 7		
		.def	_IQ7acos
		.ref	_IQ7asin
_IQ7acos:
		IQNacos	GLOBAL_Q, _IQ7asin
		.endif

		.if	GLOBAL_Q == 6
		.def	_IQ6acos
		.ref	_IQ6asin
_IQ6acos:
		IQNacos	GLOBAL_Q, _IQ6asin
		.endif

		.if	GLOBAL_Q == 5
		.def	_IQ5acos
		.ref	_IQ5asin
_IQ5acos:
		IQNacos	GLOBAL_Q, _IQ5asin
		.endif

		.if	GLOBAL_Q == 4
		.def	_IQ4acos
		.ref	_IQ4asin
_IQ4acos:
		IQNacos	GLOBAL_Q, _IQ4asin
		.endif

		.if	GLOBAL_Q == 3
		.def	_IQ3acos
		.ref	_IQ3asin
_IQ3acos:
		IQNacos	GLOBAL_Q, _IQ3asin
		.endif

		.if	GLOBAL_Q == 2
		.def	_IQ2acos
		.ref	_IQ2asin
_IQ2acos:
		IQNacos	GLOBAL_Q, _IQ2asin
		.endif

		.if	GLOBAL_Q == 1
		.def	_IQ1acos
		.ref	_IQ1asin
_IQ1acos:
		IQNacos	GLOBAL_Q, _IQ1asin
		.endif

;----------------------------------------------------------------------
; End of file
;----------------------------------------------------------------------
