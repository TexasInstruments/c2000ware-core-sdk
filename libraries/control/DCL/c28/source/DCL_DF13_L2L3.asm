; DCL_DF13_L2L3.asm - Pre-computed Direct Form 1 implementation in third order
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


		.if __TI_EABI__
		.asg	DCL_runDF13_L2, _DCL_runDF13_L2
		.asg	DCL_runDF13_L3, _DCL_runDF13_L3
		.endif

		.global _DCL_runDF13_L2
		.global _DCL_runDF13_L3
   		.def	__cla_DCL_DF13_L2L3_sp

SIZEOF_LFRAME		.set	6
LFRAME_MR1			.set	0
LFRAME_MR3			.set	2
LFRAME_MAR0			.set	4
LFRAME_MAR1			.set	5

__cla_DCL_DF13_L2L3_sp	.usect ".scratchpad:Cla1Prog:_DCL_DF13_L2L3_LSECT", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_DF13_L2L3_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_DF13_L2L3_LSECT"

		.align 	2

; C prototype: float DCL_runDF13_L2(DCL_DF13 *p, float32_t ek, float32_t vk);
; argument 1 = *p : controller structure address [MAR0]
; argument 2 = e(k) : controller input [MR0]
; argument 3 = v(k) : partial control [MR1]
; return = u(k) : controller output [MR0]

_DCL_runDF13_L2:
;		MDEBUGSTOP
		MSETFLG 	RNDF32=1					; round to nearest even
		MNOP									; MAR0 load delay slot 2
		MNOP									; MAR0 load delay slot 3
		MMOV32		MR2, *MAR0[0]++				; MR2 = b0
		MRCNDD		UNC							; return call
		MMPYF32		MR0, MR0, MR2				; MR0 = e(k) * b0
		MNOP
		MADDF32		MR0, MR0, MR1				; MR0 = u(k)


; C prototype: float DCL_runDF13_L3(DF13 *p, float ek, float uk)
; argument 1 = *p : structure address [MAR0]
; argument 2 = ek : controller input [MR0]
; argument 3 = uk : u(k) output [MR1]
; return: v(k+1) partial control [MR0]

_DCL_runDF13_L3:
;		MDEBUGSTOP
		MSETFLG 	RNDF32=1					; round to nearest even
		MMOV32		@LFRAME + LFRAME_MR1, MR1 	; save MR1
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MMOV16		@LFRAME + LFRAME_MAR0, MAR0 ; store MAR0 to frame
		MMOV16		@LFRAME + LFRAME_MAR1, MAR1 ; save MAR1
		MNOP									; MAR0 read stall
		MMOVZ16 	MR2, @LFRAME + LFRAME_MAR0  ; MR2 = &b0
		MMOV16  	MAR1, MR2, #0x10			; MAR1 = &d0
		MMOV32		MR1, *MAR0[2]++				; MR1 = b0
		MNOP									; MAR1 load stall
		MNOP

		MMOV32		*MAR1[2]++, MR0				; save d0
		MMOV32		MR3, *MAR1					; MR3 = d1
		MMOV32		*MAR1[2]++, MR0				; save d1

		MMOV32		MR1, *MAR0[2]++				; MR1 = b1
		MMPYF32		MR0, MR0, MR1				; MR0 = v1
		MMOV32		MR1, *MAR0[2]++				; MR1 = b2

		MMOV32		MR2, *MAR1					; MR2 = d2
		MMOV32		*MAR1, MR3					; save d2
		MMPYF32		MR2, MR1, MR3				; MR2 = v2
		MMOV32		MR3, *MAR1[8]++				; MR3 = b3
		MADDF32		MR0, MR0, MR2				; MR0 = v12
		MMOV32		MR1, *MAR0[8]++				; MR1 = b3
		MMPYF32		MR2, MR1, MR3				; MR2 = v3
		MMOV32		MR3, *MAR1[-2]++			; MR3 = d6
		MADDF32		MR0, MR0, MR2				; MR0 = v123

		MMOV32		MR1, *MAR0[-2]++			; MR1 = a3
		MMOV32		MR2, *MAR1[2]++				; MR2 = d5
		MMOV32		*MAR1[-2]++, MR2			; save d6
		MMPYF32		MR3, MR1, MR3				; MR3 = v6
		MMOV32		MR1, *MAR0[-2]++			; MR1 = a2
		MSUBF32		MR0, MR0, MR3				; MR0 = v1236
		MNOP
		MMPYF32		MR3, MR1, MR2				; MR3 = v5
		MMOV32		MR1, *MAR0					; MR1 = a1
		MSUBF32		MR0, MR0, MR3				; MR0 = v12356

		MMOV32		MR2, @LFRAME + LFRAME_MR1	; MR2 = uk
		MMPYF32		MR3, MR1, MR2				; MR4 = v4
||		MMOV32		*MAR1, MR2					; save d5
		MRCNDD		UNC							; return call
		MSUBF32		MR0, MR0, MR3				; MR0 = v(k+1)
		MMOV16		MAR1, @LFRAME + LFRAME_MAR1	; restore MAR1
		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3

		.unasg	LFRAME

; end of file
