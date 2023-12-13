; DCL_PID_L1.asm - Series PID controller
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
		.asg	DCL_runPID_L1, _DCL_runPID_L1
		.endif
      .endif

   		.global	_DCL_runPID_L1
		.def	__cla_DCL_runPID_L1_sp

SIZEOF_LFRAME	.set	10
LFRAME_MR3		.set	0
LFRAME_V5		.set	2
LFRAME_V6		.set	4
LFRAME_V7		.set	6
LFRAME_LK		.set	8

__cla_DCL_runPID_L1_sp	.usect ".scratchpad:Cla1Prog:_DCL_runPID_L1", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_runPID_L1_sp, LFRAME

		.sect 	"Cla1Prog:_DCL_runPID_L1"

		.align 	2

; C prototype:
; float DCL_runPID_L1(DCL_PID *p, float32_t rk, float32_t yk, float32_t lk)
; argument 1 = *p : PID structure address [MAR0]
; argument 2 = rk : control loop reference [MR0]
; argument 3 = yk : control loop feedback [MR1]
; argument 4 = lk : controller saturation input [MR2]
; return = uk : control effort [MR0]

_DCL_runPID_L1:
;		MDEBUGSTOP
		MSETFLG 	RNDF32=1					; round to nearest even
		MMOV32		@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MMOV32		@LFRAME + LFRAME_LK, MR2 	; save lk

;*** proportional path & integral prelude ***
		MSUBF32		MR3, MR0, MR1				; MR3 = ek
||		MMOV32		MR2, *MAR0[2]++				; MR2 = Kpa
		MMPYF32		MR2, MR2, MR3				; MR2 = Kpa * ek
||		MMOV32		MR3, *MAR0[4]++				; MR3 = Kia
		MMPYF32		MR2, MR2, MR3				; MR2 = v7
||		MMOV32		MR3, *MAR0[-2]++			; MR3 = Kra
		MMPYF32		MR3, MR0, MR3				; MR3 = Kra * rk
||		MMOV32		@LFRAME + LFRAME_V7, MR2	; save v7
		MSUBF32		MR3, MR3, MR1				; MR3 = v5
||		MMOV32		MR2, *MAR0[4]++				; MR2 = Kda

;*** derivative path ***
		MMPYF32		MR0, MR1, MR2				; MR0 = Kda * yk
||		MMOV32		@LFRAME + LFRAME_V5, MR3	; save v5
		MMOV32		MR3, *MAR0[6]++				; MR3 = c1a
		MMPYF32		MR0, MR0, MR3				; MR0 = v1
||		MMOV32		MR1, *MAR0[-2]++			; MR1 = d3
		MSUBF32		MR2, MR0, MR1				; MR2 = v1 - d3
||		MMOV32		MR3, *MAR0					; MR3 = d2
		MMOV32		*MAR0[-2]++, MR0			; save d2 = v1
		MSUBF32		MR2, MR2, MR3				; MR2 = v4
||		MMOV32		MR1, *MAR0[4]++				; MR1 = c2a
		MMPYF32		MR0, MR1, MR2				; MR0 = c2a * v4
||		MMOV32		MR3, @LFRAME + LFRAME_V5	; MR3 = v5
		MSUBF32		MR2, MR3, MR2				; MR2 = v5 - v4
||		MMOV32		*MAR0[-14]++, MR0			; save d3

;*** integral path ***
		MMOV32		MR3, *MAR0[18]++			; MR3 = Kpa
		MMPYF32		MR0, MR2, MR3				; MR0 = v6
||		MMOV32		MR1, *MAR0[-2]++			; MR1 = i14
		MMOV32		@LFRAME + LFRAME_V6, MR0	; save v6
		MMOV32		MR2, @LFRAME + LFRAME_V7	; MR2 = v7
		MMPYF32		MR0, MR1, MR2				; MR0 = i14 * v7
||		MMOV32		MR3, *MAR0 					; MR3 = i10
		MADDF32		MR1, MR0, MR3				; MR1 = v8
||		MMOV32		MR2, @LFRAME + LFRAME_V6	; MR2 = v6
		MADDF32		MR0, MR1, MR2				; MR0 = v9
||		MMOV32		*MAR0[4]++, MR1				; save i10

;*** saturation ***
		MMOVF32		MR2, #0.0f					; MR2 = 0.0f
		MMOVF32		MR3, #1.0f					; MR3 = 1.0f
		MMOV32		MR1, *MAR0[2]++				; MR1 = Umaxa
		MMINF32		MR0, MR1					; MR0 = sat+
		MMOV32		MR3, MR2, GT				; MR3 = v12
		MMOV32		MR1, *MAR0[-4]++			; MR1 = Umina
		MMAXF32		MR0, MR1					; MR0 = sat-
		MMOV32		MR3, MR2, LT				; MR3 = v12
		MRCNDD		UNC							; return call
		MMOV32		MR1, @LFRAME + LFRAME_LK	; MR1 = lk
		MMPYF32		MR2, MR1, MR3				; MR2 = v12 * lk
||		MMOV32		MR3, @LFRAME + LFRAME_MR3	; restore MR3
		MMOV32		*MAR0, MR2					; save i14

		.unasg	LFRAME

; end of file
