; DCL_DF23_C1.asm - Full Direct Form 2 implementation in third order
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
		.asg	DCL_runDF23_C1, _DCL_runDF23_C1
		.endif
      .endif

FASTCR_DF23_C1	.set	0		; set to 1 to enable shadowed context save/restore

		.global _DCL_runDF23_C1

		.sect	"dclfuncs"

; C prototype: float DCL_runDF23_C1(DCL_DF23 *p, float32_t ek)
; argument 1 = *p : 32-bit ARMA structure address [XAR4]
; argument 2 = ek : 32-bit floating-point input [R0H]
; return = uk : 32-bit floating-point [R0H]

		.align 	2

_DCL_runDF23_C1:
		.asmfunc
		PUSH  		XAR5
	.if FASTCR_DF23_C1 = 0
		MOV32   	*SP++, R4H
		MOV32   	*SP++, R5H
		MOV32   	*SP++, R6H
		MOV32		*SP++, R7H
	.else
		SAVE
	.endif
		MOVL		ACC, @XAR4				; ACC = &b0
		ADDB		ACC, #0xE				; ACC = &x1
		MOVL		XAR5, ACC				; XAR5 = &x1
		MOV32		R1H, *XAR5++			; R1H = x1
		MOV32		R2H, *XAR4++			; R2H = b0
		MPYF32		R3H, R2H, R0H			; R3H = v1
		MOV32		R2H, *XAR4++			; R2H = b1
		ADDF32		R7H, R1H, R3H			; R7H = uk
||		MOV32		R3H, *XAR4++			; R3H = b2
		MPYF32		R1H, R2H, R0H			; R1H = v2
||		MOV32		R4H, *XAR4++			; R4H = b3
		MPYF32		R2H, R3H, R0H			; R2H = v4
||		MOV32		R5H, *XAR4++			; R5H = a1
		MPYF32		R3H, R4H, R0H			; R3H = v6
||		MOV32		R6H, *XAR4++			; R6H = a2
		MPYF32		R4H, R5H, R7H			; R4H = v3
||		MOV32		R0H, *XAR5++			; R0H = x2
		ADDF32		R1H, R0H, R1H			; R1H = v2 + x2
		MOV32		R0H, *XAR4++			; R0H = a3
		SUBF32		R1H, R1H, R4H			; R1H = x1d
		MPYF32		R5H, R6H, R7H			; R5H = v5
||		MOV32		R6H, *XAR5				; R6H = x3
		ADDF32		R2H, R2H, R6H			; R2H = v4 + x3
		MOV32		*XAR4++, R1H			; save x1
		SUBF32		R2H, R2H, R5H			; R2H = x2d
		MPYF32		R5H, R0H, R7H			; R5H = v7
		MOV32		*XAR4++, R2H			; save x2
		SUBF32		R3H, R3H, R5H			; R3H = x3d
		MOV32		R0H, R7H, UNC			; save uk
		MOV32		*XAR4, R3H				; save x3
	.if FASTCR_DF23_C1 = 0
	    MOV32   	R7H, *--SP, UNC
	    MOV32   	R6H, *--SP, UNC
		MOV32   	R5H, *--SP, UNC
	    MOV32   	R4H, *--SP, UNC
	.else
		RESTORE
	.endif
		POP   		XAR5
		LRETR
		.endasmfunc

		.end

; end of file
