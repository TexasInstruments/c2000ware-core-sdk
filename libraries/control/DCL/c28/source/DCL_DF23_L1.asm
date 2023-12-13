; DCL_DF23_L1.asm - Full Direct Form 2 implementation in third order
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
		.asg	DCL_runDF23_L1, _DCL_runDF23_L1
		.endif

		.global _DCL_runDF23_L1
   		.def	__cla_DCL_DF23_L1_sp

SIZEOF_LFRAME		.set	2
LFRAME_MR3			.set	0

		.align 	2
__cla_DCL_DF23_L1_sp	.usect ".scratchpad:Cla1Prog:_DCL_DF23_L1_LSECT", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_DF23_L1_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_DF23_L1_LSECT"


; C prototype: float DCL_runDF23_L1(DCL_DF23 *p, float32_t ek);
; argument 1 = *p : 32-bit structure address [MAR0]
; argument 2 = ek : 32-bit floating-point [MR0]
; return = uk : 32-bit floating-point [MR0]

_DCL_runDF23_L1:
;		MDEBUGSTOP
		MSETFLG 	RNDF32=1					; round to nearest even
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MNOP									; MAR0 load delay slot 3

		MMOV32		MR1, *MAR0[2]++				; MR1 = b0
		MMPYF32		MR2, MR1, MR0				; MR2 = v1
||		MMOV32		MR3, *MAR0[12]++			; MR3 = b1
		MMOV32		MR1, *MAR0[2]++				; MR1 = x1
		MADDF32		MR2, MR1, MR2				; MR2 = uk

		MMPYF32		MR3, MR0, MR3				; MR3 = v2
		MMOV32		MR1, *MAR0[-8]++			; MR1 = x2
		MADDF32		MR3, MR1, MR3				; MR3 = x2 + v2
||		MMOV32		MR1, *MAR0[-4]++			; MR1 = a1
		MMPYF32		MR1, MR1, MR2				; MR1 = v3
		MNOP
		MSUBF32		MR3, MR3, MR1				; MR3 = x1d
		MMOV32		MR1, *MAR0[10]++			; MR1 = b2
		MMOV32		*MAR0[4]++, MR3				; save x1

		MMPYF32		MR1, MR0, MR1				; MR1 = v4
		MMOV32		MR3, *MAR0[-8]++			; MR3 = x3
		MADDF32		MR3, MR1, MR3				; MR3 = x3 + v4
||		MMOV32		MR1, *MAR0[-4]++			; MR1 = a2
		MMPYF32		MR1, MR1, MR2				; MR1 = v5
		MNOP
		MSUBF32		MR3, MR3, MR1				; MR3 = x2d
		MMOV32		MR1, *MAR0[10]++			; MR1 = b3
		MMOV32		*MAR0[-4]++, MR3			; save x2

		MMPYF32		MR1, MR0, MR1				; MR1 = v6
||		MMOV32		MR3, *MAR0[6]++				; MR3 = a3
		MMPYF32		MR3, MR2, MR3				; MR3 = v7
		MSUBF32		MR1, MR1, MR3				; MR1 = x3d
		MRCNDD		UNC							; return call
		MMOV32		MR0, MR2, UNC				; return uk
		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3
		MMOV32		*MAR0[0]++, MR1				; save x3

		.unasg	LFRAME

; end of file
