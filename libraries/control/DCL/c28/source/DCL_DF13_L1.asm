; DCL_DF13_L1.asm - Full Direct Form 1 implementation in third order
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
		.asg	DCL_runDF13_L1, _DCL_runDF13_L1
		.endif

		.global _DCL_runDF13_L1
   		.def	__cla_DCL_DF13_L1_sp

SIZEOF_LFRAME		.set	6
LFRAME_MR1			.set	0
LFRAME_MR3			.set	2
LFRAME_MAR0			.set	4
LFRAME_MAR1			.set	5

		.align 	2
__cla_DCL_DF13_L1_sp	.usect ".scratchpad:Cla1Prog:_DCL_DF13_L1_LSECT", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_DF13_L1_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_DF13_L1_LSECT"

; C prototype: float DCL_runDF13_L1(DCL_DF13 *p, float32_t ek);
; argument 1 = *p : 32-bit structure address [MAR0]
; argument 2 = ek : 32-bit floating-point [MR0]
; return = uk : 32-bit floating-point [MR0]

_DCL_runDF13_L1:
;		MDEBUGSTOP
		MSETFLG 	RNDF32=1					; round to nearest even
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MNOP									; MAR0 read stall
		MMOV16		@LFRAME + LFRAME_MAR0, MAR0 ; store MAR0 to frame
		MMOV16		@LFRAME + LFRAME_MAR1, MAR1 ; store MAR1 to frame
		MNOP									; MAR0 read stall
		MMOVZ16 	MR2, @LFRAME + LFRAME_MAR0  ; MR2 = &b0
		MMOV16  	MAR1, MR2, #0x10			; MAR1 = &d0
		MMOV32		MR1, *MAR0[2]++				; MR1 = b0
		MNOP									; MAR1 load stall

		MMPYF32		MR2, MR0, MR1				; MR2 = v0
		MMOV32		*MAR1[2]++, MR0				; save d0
		MMOV32		MR0, *MAR0[2]++				; MR0 = b1
		MMOV32		MR1, *MAR1[2]++				; MR1 = d1

		MMPYF32		MR3, MR0, MR1				; MR3 = v1
		MMOV32		MR0, *MAR0[2]++				; MR0 = b2
		MADDF32		MR2, MR2, MR3				; MR2 = v0 + v1
||		MMOV32		MR1, *MAR1[2]++				; MR1 = d2

		MMPYF32		MR3, MR0, MR1				; MR3 = v2
		MMOV32		MR0, *MAR0[4]++				; MR0 = b3
		MADDF32		MR2, MR2, MR3				; MR2 = v0 + v1 + v2
||		MMOV32		MR1, *MAR1[4]++				; MR1 = d3

		MMPYF32		MR3, MR0, MR1				; MR3 = v3
		MMOV32		MR0, *MAR0[2]++				; MR0 = a1
		MADDF32		MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3
||		MMOV32		MR1, *MAR1[2]++				; MR1 = d5

		MMPYF32		MR3, MR0, MR1				; MR3 = v5
		MMOV32		MR0, *MAR0[2]++				; MR0 = a2
		MSUBF32		MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3 - v5
||		MMOV32		MR1, *MAR1[2]++				; MR1 = d6

		MMPYF32		MR3, MR0, MR1				; MR3 = v6
		MMOV32		MR0, *MAR0[14]++			; MR0 = a3, MAR0 = &d6
		MSUBF32		MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3 - v5 - v6
||		MMOV32		MR1, *MAR1[-6]++			; MR1 = d7, MAR1 = &d4

		MMPYF32		MR3, MR0, MR1				; MR3 = v7
		MNOP
		MSUBF32		MR0, MR2, MR3				; MR0 = v0 + v1 + v2 + v3 - v5 - v6 - v7
		MNOP
		MMOV32		*MAR1[-6]++, MR0			; save uk = d4

		MMOVD32		MR1, *MAR0[-2]++			; u(k-3) <- u(k-2)
		MMOVD32		MR1, *MAR0[-2]++			; u(k-2) <- u(k-1)
		MMOVD32		MR1, *MAR0[-4]++			; u(k-1) <- u(k)
		MMOVD32		MR1, *MAR0[-2]++			; e(k-3) <- e(k-2)
		MMOVD32		MR1, *MAR0[-2]++			; e(k-2) <- e(k-1)
		MRCNDD		UNC							; return call
		MMOVD32		MR1, *MAR0					; e(k-1) <- e(k)
		MMOV16		MAR1, @LFRAME + LFRAME_MAR1	; restore MAR1
		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3

		.unasg		LFRAME

; end of file
