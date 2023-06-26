;*****************************************************************************
;* PROLOG CODE FOR C28X v6.0.1                                                *
;*                                                                           *
;* Copyright (c) 2001-2015 Texas Instruments Incorporated                    *
;* http://www.ti.com/                                                        *
;*                                                                           *
;*  Redistribution and  use in source  and binary forms, with  or without    *
;*  modification,  are permitted provided  that the  following conditions    *
;*  are met:                                                                 *
;*                                                                           *
;*     Redistributions  of source  code must  retain the  above copyright    *
;*     notice, this list of conditions and the following disclaimer.         *
;*                                                                           *
;*     Redistributions in binary form  must reproduce the above copyright    *
;*     notice, this  list of conditions  and the following  disclaimer in    *
;*     the  documentation  and/or   other  materials  provided  with  the    *
;*     distribution.                                                         *
;*                                                                           *
;*     Neither the  name of Texas Instruments Incorporated  nor the names    *
;*     of its  contributors may  be used to  endorse or  promote products    *
;*     derived  from   this  software  without   specific  prior  written    *
;*     permission.                                                           *
;*                                                                           *
;*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    *
;*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    *
;*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    *
;*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    *
;*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    *
;*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    *
;*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    *
;*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    *
;*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    *
;*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    *
;*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     *
;*                                                                           *
;*****************************************************************************

;*****************************************************************************
;* PROLOG CODE IF NO FRAME IS NEEDED                                         *
;* 1. PUSH SOE REGISTERS                                                     *
;* 2. RETURN                                                                 *
;*****************************************************************************
	.sect	".text"
	.global	_prolog_c28x_1

_prolog_c28x_1:	.asmfunc
	MOVL	*SP++,XAR1
	MOVL	*SP++,XAR2
	MOVL	*SP++,XAR3
	FFCRET	*XAR7
	.endasmfunc

;*****************************************************************************
;* PROLOG CODE IF FRAME IS NEEDED                                            *
;* 1. PUSH SOE REGISTERS                                                     *
;* 2. ADD FRAME TO SP                                                        *
;* 3. RETURN                                                                 *
;*****************************************************************************
	.sect	".text"
	.global	_prolog_c28x_2

_prolog_c28x_2:	.asmfunc
	MOVL	*SP++,XAR1
	MOVL	*SP++,XAR2
	MOVL	*SP++,XAR3
	MOV	PL,SP
	ADDUL	P,XAR0
	MOV	SP,P
	FFCRET	*XAR7
	.endasmfunc

;*****************************************************************************
;* PROLOG CODE IF FRAME IS NEEDED AND FRAME POINTER (XAR2)                   *
;* 1. PUSH SOE REGISTERS                                                     *
;* 2. SAVE SP TO FP                                                          *
;* 3. ADD FRAME TO SP                                                        *
;* 4. SUBTRACT OFFSET FROM FP                                                *
;* 5. RETURN                                                                 *
;*****************************************************************************
	.sect	".text"
	.global	_prolog_c28x_3

_prolog_c28x_3:	.asmfunc
	MOVL	*SP++,XAR1
	MOVL	*SP++,XAR2
	MOVL	*SP++,XAR3
	MOVZ	AR2,SP
	MOV	PL,SP
	ADDUL	P,XAR0
	MOV	SP,P
	MOVL	P,XAR2
	SUBUL	P,XAR6
	MOVL	XAR2,P
	FFCRET	*XAR7
	.endasmfunc


