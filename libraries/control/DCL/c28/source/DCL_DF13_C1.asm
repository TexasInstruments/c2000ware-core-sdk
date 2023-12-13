; DCL_DF13_C1.asm - Full Direct Form 1 implementation in third order
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
		.asg	DCL_runDF13_C1, _DCL_runDF13_C1
		.endif
      .endif

		.global _DCL_runDF13_C1

		.sect	"dclfuncs"

; C prototype: float DCL_runDF13_C1(DCL_DF13 *p, float32_t ek)
; argument 1 = *p : 32-bit ARMA structure address [XAR4]
; argument 2 = ek : 32-bit floating-point input [R0H]
; return = uk : 32-bit floating-point [R0H]

; XAR4 = coefficient pointer
; XAR5 = data pointer

		.align	2

_DCL_runDF13_C1:
		.asmfunc
; context save
		PUSH  		XAR5
		MOV32   	*SP++, R4H
		MOV32   	*SP++, R5H

; initialize pointers
		MOVL		ACC, @XAR4				; ACC = &p(0) = &b0
		ADDB		ACC, #0x10				; ACC = &p(8) = &d0
		MOVL		XAR5, ACC				; XAR5 = &d0
		MOV32		*XAR5++, R0H			; save d0, XAR5 = &d1

; v0 = b0 * d0
		MOV32		R1H, *XAR4++			; R1H = b0
		MPYF32		R2H, R0H, R1H			; R2H = v0
||		MOV32		R3H, *XAR5				; R3H = d1
		MOV32		*XAR5++, R0H			; save d0

; v1 = b1 * d1
		MOV32		R1H, *XAR4++			; R1H = b1
		MPYF32		R4H, R1H, R3H			; R4H = v1
||		MOV32		R5H, *XAR5				; R5H = d2
		MOV32		*XAR5++, R3H			; save d1

; v2 = b2 * d2
 		ADDF32		R0H, R2H, R4H			; R0H = v01
|| 		MOV32		R1H, *XAR4++			; R1H = b2
 		MPYF32		R2H, R1H, R5H			; R2H = v2
|| 		MOV32		R4H, *XAR5				; R4H = d3
 		MOV32		*XAR5++, R5H			; save d2

; v3 = b3 * d3
 		ADDF32		R0H, R0H, R2H			; R0H = v012
|| 		MOV32		R1H, *XAR4++			; R1H = b3
		MPYF32		R3H, R1H, R4H			; R3H = v3
		MOV32		R2H, *+XAR5[6]			; R2H = d7

; XAR4 = &a0, XAR5 = &d4.  Indirect offset addressing from here.

; v7 = a3 * d7
		ADDF32		R0H, R0H, R3H			; R0H = v0123
||		MOV32		R1H, *+XAR4[6]			; R1H = a3
		MPYF32		R3H, R1H, R2H			; R3H = v7
		MOV32		R4H, *+XAR5[4]			; R4H = d6
		MOV32		*+XAR5[6], R4H			; save d6

; v6 = a2 * d6
		SUBF32		R0H, R0H, R3H			; R0H = v01237
||		MOV32		R1H, *+XAR4[4]			; R1H = a2
		MPYF32		R2H, R1H, R4H			; R2H = v6
		MOV32		R5H, *+XAR5[2]			; R5H = d5
		MOV32		*+XAR5[4], R5H			; save d5

; v5 = a1 * d5
		SUBF32		R0H, R0H, R2H			; R0H = v012367
||		MOV32		R1H, *+XAR4[2]			; R1H = a1
		MPYF32		R2H, R1H, R5H			; R2H = v5
	    MOV32   	R5H, *--SP, UNC
		SUBF32		R0H, R0H, R2H			; R0H = v0123567
	    MOV32   	R4H, *--SP, UNC
		MOV32		*+XAR5[2], R0H			; save d4
		MOV32		*+XAR5[0], R0H			; save u(k)
		POP   		XAR5
		LRETR
		.endasmfunc

		.end

; end of file
