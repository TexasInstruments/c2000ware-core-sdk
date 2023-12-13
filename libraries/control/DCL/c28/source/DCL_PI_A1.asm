; DCL_PI_A1.asm - Series PI controller on C28x (fixed point) [r1.02]
;
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


   	  .if $defined(__TI_EABI__)
		.if __TI_EABI__
		.asg	DCL_runPI_A1, _DCL_runPI_A1
		.endif
      .endif

		.global _DCL_runPI_A1

 		.sect	"dcl32funcs"

; C prototype: int32_t DCL_runPI_A1(DCL_PI32 *p, int32_t rk, int32_t yk)
; argument 1 = *p : DCL_PI32 structure address [XAR4]
; argument 2 = rk : set point reference [ACC]
; argument 3 = yk : feedback [stack-2]
; return = uk : control [ACC]

		.align	2

_DCL_runPI_A1:
		.asmfunc
		MOVL	XT, *-SP[4]			; XT = yk
		SUBL	ACC, XT				; ACC = v1
		MOVL	XT, ACC				; XT = v1
		IMPYL	P, XT, *XAR4		; P = v2(L)
		QMPYL	ACC, XT, *XAR4++	; ACC = v2(H)
		LSL64	ACC:P, #8			; ACC = v2 [I8Q24]
		MOVL	XT, ACC				; XT = v2
		IMPYL	P, XT, *XAR4		; P = v3(L)
		QMPYL	ACC, XT, *XAR4++	; ACC = v3(H)
		LSL64	ACC:P, #8			; ACC = v3 [I8Q24]
		MOVL	XAR0, XT			; store v2
		MOVL	XT, ACC				; XT = v3
		IMPYL	P, XT, *XAR4		; P = v8(L)
		QMPYL	ACC, XT, *XAR4++	; ACC = v8(H)
		LSL64	ACC:P, #8			; ACC = v8 [I8Q24]
		ADDL	ACC, *XAR4			; ACC = v4
		SAT		ACC					; saturate ACC
		MOVL	*XAR4++, ACC		; store i10
		ADDL	ACC, XAR0			; ACC = v5
		SAT		ACC					; saturate v5
		MOVL	P, ACC				; P = v5
		MINL	ACC, *XAR4++		; clamp v5 pos
		MAXL	ACC, *XAR4			; ACC = uk
		PUSH	ACC					; push uk to stack
		SPM		0					; zero PM
		CMPL	ACC, P<<PM			; set flags on (uk-v5)
		PUSH	ST0					; save flags
		ZAPA						; ACC = P = 0
		OR		ACC, #0x1000<<12	; ACC = IQ24(1.0)
		POP		ST0					; restore flags
		MOVL	P, ACC, EQ			; P = i6
		SUBB	XAR4, #6			; XAR4 = &i6
		MOVL	*XAR4, P			; store i6
		MOVL	ACC, *--SP			; ACC = uk
		LRETR						; return uk
		.endasmfunc

		.end

; end of file
