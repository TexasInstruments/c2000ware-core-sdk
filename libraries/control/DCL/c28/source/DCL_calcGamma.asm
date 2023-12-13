; DCL_calcGamma.asm - compultes the linear region gain on TMU type 1
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
		.asg	DCL_calcGamma, _DCL_calcGamma
		.endif
      .endif

		.global _DCL_calcGamma

		.sect	"dclfuncs"

; C prototype: float32_t DCL_calcGamma(float32_t a, float32_t d)
; argument 1 = a : [R0H] alpha - normalized [0.0f, +2.0f]
; argument 2 = d : [R1H] delta - normalized (0.0f, +1.0f]
; return = v : [R0H] calcGamma(d,a)

		.align	2

_DCL_calcGamma:
		.asmfunc
		.if $defined(.TMS320C2800_TMU1)
;		.if (.TMS320C2800_TMU1 = 1)

		LOG2F32		R2H, R1H			; R2H = log2(d)
		NOP
		NOP
		NOP
		MPYF32		R3H, R0H, R2H		; R3H = a*log2(d)
		NOP
		NEGF32		R2H, R3H			; R2H = -a*log2(d)
		IEXP2F32	R3H, R2H			; R3H = d^a
		NOP
		NOP
		NOP
		NOP
		DIVF32		R0H, R3H, R1H		; R0H = d^(a-1)
		NOP								; first delay slot for DIVF32, others in LRETR pipeline
		.endif
		LRETR							; return

		.endasmfunc
		.end

; end of file
