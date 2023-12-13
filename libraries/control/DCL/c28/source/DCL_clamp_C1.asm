; DCL_clamp_C1.asm - clamps output from immediate ARMA controller
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
		.asg	DCL_runClamp_C1, _DCL_runClamp_C1
		.endif
      .endif

		.global _DCL_runClamp_C1

		.sect	"dclfuncs"

; This function saturates an input data value to defined upper & lower limits.
; If the input data lies definitely within limits the function returns 0,
; otherwise it returns 1.
; i.e. return 0 if (lowerLim < data < upperLim), otherwise return 1.

; C prototype: uint16_t DCL_runClamp_C1(float *data, float Umax, float Umin)
; argument 1 = *data: address of input data [XAR4]
; argument 2 = Umax : upper limit [R0H]
; argument 3 = Umin : lower limit [R1H]
; return = integer : 1 = clamped, 0 = not clamped [AL]

		.align	2

_DCL_runClamp_C1:
		.asmfunc
		ZAPA								; AL = 0
		MOV32 		R2H, *+XAR4[0]			; R2H = data
		CMPF32		R2H, R0H				; compare: data, Umax
		MOVST0		ZF, NF					; copy flags: Z = ZF, N = NF
		MOVB		AL, #1, GEQ				; data >= Umax ---> AL = 1
		MOV32		R0H, R2H, LT			; data < Umax ---> R0H = data
		CMPF32		R2H, R1H				; comapare: data, Umin
		MOVST0		ZF, NF					; copy flags: Z = ZF, N = NF
		MOVB		AL, #1, LEQ				; data <= Umin ---> AL = 1
		MOV32		R0H, R1H, LT			; data < Umin ---> R0H = Umin
		MOV32		*+XAR4[0], R0H			; &data = R0H
		LRETR
		.endasmfunc

		.end

; end of file
