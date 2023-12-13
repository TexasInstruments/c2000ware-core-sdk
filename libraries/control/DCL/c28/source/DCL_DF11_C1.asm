; DCL_DF11_C1.asm - Direct Form 1 implementation in first order
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
		.asg	DCL_runDF11_C1, _DCL_runDF11_C1
		.endif
      .endif

		.global _DCL_runDF11_C1

		.sect	"dclfuncs"

; C prototype: float DCL_runDF11_C1(DCL_DF11 *p, float32_t ek)
; argument 1 = *p : 32-bit structure address [XAR4]
; argument 2 = ek : 32-bit floating-point input [R0H]
; return = uk : 32-bit floating-point [R0H]

		.align	2

_DCL_runDF11_C1:
		.asmfunc
		MOV32		R1H, *XAR4++			; R1H = b0
		MPYF32		R2H, R0H, R1H			; R2H = v2
||		MOV32		R3H, *XAR4++			; R3H = b1
		MOV32		R1H, *+XAR4[2]			; R1H = d1
		MPYF32		R3H, R1H, R3H			; R3H = v3
		MOV32		*+XAR4[2], R0H			; save e(k)
		ADDF32		R0H, R2H, R3H			; R0H = v2 + v3
||		MOV32		R2H, *+XAR4[4]			; R2H = d2
		MOV32		R3H, *+XAR4[0]			; R3H = a1
		MPYF32		R1H, R2H, R3H			; R1H = v6
		NOP									; delay slot
		SUBF32		R0H, R0H, R1H			; R0H = v5
		NOP									; delay slot
		MOV32		*+XAR4[4], R0H			; save u(k)
		LRETR
		.endasmfunc

		.end

; end of file
