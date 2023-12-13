; DCL_PI_C1.asm - Series PI controller
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
		.asg	DCL_runPI_C1, _DCL_runPI_C1
		.endif
      .endif

FASTCR_PI_C1	.set	0		; set to 1 to enable shadowed context save/restore

		.global _DCL_runPI_C1

		.sect	"dclfuncs"

; 11/14/2017: [RP] added XAR1 to context save

; C prototype: float DCL_runPI_C1(DCL_PI *p, float32_t rk, float32_t yk)
; argument 1 = *p : 32-bit PI structure address [XAR4]
; argument 2 = rk : 32-bit floating-point reference [R0H]
; argument 3 = yk : 32-bit floating-point feedback [R1H]
; return = uk : 32-bit floating-point [R0H]

		.align	2

_DCL_runPI_C1:
		.asmfunc
; context save
		MOVL		*SP++, XAR1
	.if FASTCR_PI_C1 = 0
		MOV32   	*SP++, R4H
		MOV32   	*SP++, R5H
		MOV32   	*SP++, R6H
	.else
		SAVE
	.endif

; servo error
		SUBF32		R4H, R0H, R1H				; R4H = v1

; proportional path
		MOV32		R5H, *+XAR4[0]				; R5H = Kpa
		MPYF32		R6H, R4H, R5H				; R6H = v2

; integral path
		MOV32		R5H, *+XAR4[2]				; R5H = Kia
		MPYF32		R4H, R5H, R6H				; R4H = v3
		MOV			AR1, #0xA					; AR1 = 10
		MOV32		R5H, *+XAR4[AR1]			; R5H = i6
		MPYF32		R3H, R4H, R5H				; R3H = v8
		MOV32		R4H, *+XAR4[4]				; R4H = i10
		ADDF32		R5H, R4H, R3H				; R5H = v4
		ZERO		R1H							; R1H = 0.0f
		MOV32		*+XAR4[4], R5H				; save i10

; control
		ADDF32		R0H, R5H, R6H				; R0H = v5
		ADDF32		R5H, R1H, #1.0				; R5H = 1.0f
		MOV32		R3H, *+XAR4[6]				; R3H = Umaxa
		MINF32		R0H, R3H					; if (v5 > Umaxa) R0H = Umax else R0H = v5
||		MOV32		R5H, R1H					; R5H = 0.0f
		MOV			AR0, #8						; AR0 = 8
		MOV32		R3H, *+XAR4[AR0]			; R3H = Umina
		MAXF32		R0H, R3H					; if (v5 < Umina) R0H = Umin else R0H = v5
||		MOV32		R5H, R1H					; R5H = 0.0f

; anti-windup
		NOP										; delay slot
		MOV32		*+XAR4[AR1], R5H			; save i6

; context restore
	.if FASTCR_PI_C1 = 0
		MOV32   	R6H, *--SP, UNC				; delay slot
	    MOV32   	R5H, *--SP, UNC
	    MOV32   	R4H, *--SP, UNC
	.else
		RESTORE
	.endif
	    MOVL		XAR1, *--SP
		LRETR
		.endasmfunc

		.end

; end of file
