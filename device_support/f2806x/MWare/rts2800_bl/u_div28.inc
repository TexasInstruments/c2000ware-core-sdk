;*****************************************************************************
;* u_div28_inc  v6.0.1
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
* This module contains the functions for unsigned 16-bit divide and modulus.
*
* Upon entry the numerator is in AH, the denominator is in AL.
* Stack memory is not used.
******************************************************************************

******************************************************************************
* 16-BIT UNSIGNED DIVIDE, CALCULATE Q / D AND RETURN IN ACCUMULATOR "A"
******************************************************************************
	.global	U$$DIV

U$$DIV:	.asmfunc
******************************************************************************
* PREPARATION
******************************************************************************
	MOV	AR6,AH		; move denominator to clear AH
	MOVB	AH,#0		; clear AH

******************************************************************************
* PERFORM DIVIDE
******************************************************************************
	RPT	#15		; repeat 16 times
||	SUBCU	ACC,AR6		; divide step

******************************************************************************
* QUOTIENT IS IN AL
******************************************************************************
	FFCRET	*XAR7		; return
	.endasmfunc

	.page
******************************************************************************
* 16-BIT UNSIGNED MODULUS, CALCULATE Q % D AND RETURN IN ACCUMULATOR "A"
******************************************************************************
	.global	U$$MOD

U$$MOD:	.asmfunc
******************************************************************************
* PREPARATION
******************************************************************************
	MOV	AR6,AH		; move denominator to clear AH
	MOVB	AH,#0		; clear AH

******************************************************************************
* PERFORM DIVIDE
******************************************************************************
	RPT	#15		; repeat 16 times
||	SUBCU	ACC,AR6		; divide step

******************************************************************************
* QUOTIENT IS IN AL, REMAINDER IS IN AH
******************************************************************************
	MOV	AL,AH		; move remainder to return reg (AL)
	FFCRET	*XAR7		; return
	.endasmfunc


