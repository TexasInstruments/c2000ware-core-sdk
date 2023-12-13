; DCL_DF13_C2C3.asm - Pre-computed Direct Form 1 implementation in third order
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
		.asg	DCL_runDF13_C2, _DCL_runDF13_C2
		.asg	DCL_runDF13_C3, _DCL_runDF13_C3
		.endif
      .endif

FASTCR_DF13_C3	.set	0		; set to 1 to enable shadowed context save/restore

		.global _DCL_runDF13_C2
		.global _DCL_runDF13_C3

		.sect	"dclfuncs"

; C prototype: float DCL_runDF13_C2(DCL_DF13 *p, float32_t ek, float32_t vk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = vk : partial product [R1H]
; return = uk : controller output [R0H]

_DCL_runDF13_C2:
		.asmfunc
		MOV32	R2H, *+XAR4[0]				; R2H = b0
		MPYF32	R0H, R0H, R2H				; R0H = e(k) * b0
		MOV 	AR0, #0x18					; AR0 = 24
		ADDF32	R0H, R0H, R1H				; R0H = u(k)
		LRETR
		.endasmfunc

; C prototype: float DCL_runDF13_C3(DF13 *p, float ek, float uk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = uk : controller output [R1H]
; return : v(k)

_DCL_runDF13_C3:
		.asmfunc
; context save
		PUSH  	XAR5
	.if FASTCR_DF13_C3 = 0
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H
		MOV32   *SP++, R6H
		MOV32   *SP++, R7H
	.else
		SAVE
	.endif


; initialise pointers
		MOVL	ACC, @XAR4					; ACC = &p(0) = &b0
		ADDB	ACC, #0x10					; ACC = &p(8) = &d0
		MOVL	XAR5, ACC					; XAR5 = &d0
		MOV32	*XAR5++, R0H				; save d0, XAR5 = d1

; v1 = e(k) * b1
		MOV32	R2H, *XAR4++				; R2H = b0
		MOV32	R2H, *XAR4++				; R2H = b1
		MPYF32	R3H, R2H, R0H				; R3H = v1
||		MOV32	R4H, *XAR5					; R4H = d1
		MOV32	*XAR5++, R0H				; save e(k-1)

; v2 = e(k-1) * b2
		MOV32	R5H, *XAR4++				; R5H = b2
		MPYF32	R2H, R5H, R4H				; R2H = v2
||		MOV32	R6H, *XAR5					; R6H = d2
		MOV32	*XAR5++, R4H				; save e(k-2)

; v3 = e(k-3) * b3
		MOV32	R5H, *XAR4++				; R5H = b3
		MPYF32	R7H, R5H, R6H				; R7H = v2
||		MOV32	*XAR5++, R6H				; save e(k-3)

; save v123
		ADDF32	R0H, R3H, R2H				; R0H = v1 + v2
		MOV32	R5H, *XAR4++				; R5H = a0
		ADDF32	R0H, R0H, R7H				; R0H = v1 + v2 + v3
||		MOV32	R5H, *XAR4++				; R5H = a1

; v4 = u(k) * a1
		MPYF32	R2H, R1H, R5H				; R2H = v4
||		MOV32	*XAR5++, R1H				; XAR5 = &d5
		MOV32	R3H, *XAR5					; R3H = d5
		SUBF32	R0H, R0H, R2H				; R0H = v1 + v2 + v3 - v4
		MOV32	*XAR5++, R1H				; save u(k-1)

; v5 = u(k-1) * a2
		MOV32	R4H, *XAR4++				; R4H = a2
		MPYF32	R5H, R4H, R3H				; R5H = v5
||		MOV32	R1H, *XAR5					; R2H = d6
		MOV32	*XAR5++, R3H				; save u(k-2)

; v6 = u(k-2) * a3
		SUBF32	R0H, R0H, R5H				; R0H = v1 + v2 + v3 - v4 - v5
||		MOV32	R6H, *XAR4					; R6H = a3
		MPYF32	R7H, R6H, R1H				; R7H = v7
		MOV32	*XAR5, R1H					; save u(k-3)
		SUBF32	R0H, R0H, R7H				; save v(k+1)

; context restore
	.if FASTCR_DF13_C3 = 0
	    MOV32   R7H, *--SP, UNC				; do not parallel with previous SUBF32
		MOV32   R6H, *--SP, UNC
	    MOV32   R5H, *--SP, UNC
	    MOV32   R4H, *--SP, UNC
	.else
		RESTORE
	.endif
		POP   	XAR5
		LRETR
		.endasmfunc

		.end

; end of file
