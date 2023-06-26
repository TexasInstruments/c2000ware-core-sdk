;*****************************************************************************
;* i_div28.inc  v6.0.1
;* 
;* Copyright (c) 1997-2015 Texas Instruments Incorporated
;* http://www.ti.com/ 
;* 
;*  Redistribution and  use in source  and binary forms, with  or without
;*  modification,  are permitted provided  that the  following conditions
;*  are met:
;* 
;*     Redistributions  of source  code must  retain the  above copyright
;*     notice, this list of conditions and the following disclaimer.
;* 
;*     Redistributions in binary form  must reproduce the above copyright
;*     notice, this  list of conditions  and the following  disclaimer in
;*     the  documentation  and/or   other  materials  provided  with  the
;*     distribution.
;* 
;*     Neither the  name of Texas Instruments Incorporated  nor the names
;*     of its  contributors may  be used to  endorse or  promote products
;*     derived  from   this  software  without   specific  prior  written
;*     permission.
;* 
;*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS
;*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT
;*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
;*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT
;*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT
;*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;* 
;*****************************************************************************

******************************************************************************
* This module contains the functions for signed 16-bit divide and modulus.
*
* SYMBOL DEFINITIONS:
*
*  NUM - Numerator 
*  DEN - Denominator 
*  SIGN - Sign of result
*
* NO MEMORY USED ON STACK
******************************************************************************

******************************************************************************
* ASSIGN ALIASES TO REGISTERS USED
******************************************************************************
	.asg	AR6,SIGN     	; sign of result
	.asg	AR4,DEN	 	; denominator
	.asg	AR5,NUM	 	; numerator

	.page
******************************************************************************
* 16-BIT SIGNED DIVIDE, CALCULATE NUM/DEN RETURN QUOTIENT IN AL
******************************************************************************
	.global	I$$DIV

I$$DIV:		.asmfunc
******************************************************************************
* DETERMINE SIGN OF RESULT, TAKE ABSOLUTE VALUE OF OPERANDS
******************************************************************************
	MOVZ	DEN,AH		; store off divisor
	XOR	AH,AL		; determine sign of result			
	MOV	SIGN,AH		; save off sign of result

	SETC	SXM		; turn on sign-extension, needed for ABS step
	MOV	ACC,AL		; sign-extend dividend		 
	ABS	ACC		; dividend = | dividend |
	MOVZ	NUM,AL		; save off dividend 
	MOV	ACC,DEN		; sign-extend divisor
	ABS	ACC		; divisor = | divisor |
	MOVZ	DEN,AL		; save off divisor

	MOV	AL,NUM		; reload dividend
******************************************************************************
* PERFORM DIVIDE
******************************************************************************
	RPT	#15		; repeat 16 times
||	SUBCU	ACC,DEN		; divide step

******************************************************************************
* QUOTIENT IS IN AL, REMAINDER IS IN AH 
******************************************************************************
	TBIT	SIGN,#15	; check MSB(sign)
	B	RET1,NTC	; if (1)
	NEG	AL		; negate Quotient
RET1:
	FFCRET	*XAR7		; return
	.endasmfunc



	.page
******************************************************************************
* 16-BIT SIGNED MODULUS, CALCULATE NUM % DEN, RETURN REMAINDER IN AL
******************************************************************************
	.global	I$$MOD

I$$MOD:		.asmfunc

******************************************************************************
* DETERMINE SIGN OF RESULT, TAKE ABSOLUTE VALUE OF OPERANDS
******************************************************************************
	MOV	SIGN,AL		; sign of result is sign of dividend, save

	MOVZ	DEN,AH		; store off divisor
	SETC	SXM		; turn on sign-extension, needed for ABS step
	MOV	ACC,AL		; sign-extend dividend		 
	ABS	ACC		; dividend = | dividend |
	MOVZ	NUM,AL		; save off dividend 
	MOV	ACC,DEN		; sign-extend divisor
	ABS	ACC		; divisor = | divisor |
	MOVZ	DEN,AL		; save off divisor

	MOV	AL,NUM		; reload dividend
******************************************************************************
* PERFORM DIVIDE
******************************************************************************
	RPT	#15		; repeat 16 times
||	SUBCU	ACC,DEN		; divide step

******************************************************************************
* QUOTIENT IS IN AL, REMAINDER IS IN AH 
******************************************************************************
	TBIT	SIGN,#15	; check MSB(sign)
	B	RET2,NTC	; if (1)
	NEG	AH		; negate Q
RET2:
	MOV	AL,AH

	FFCRET	*XAR7		; return
	.endasmfunc


