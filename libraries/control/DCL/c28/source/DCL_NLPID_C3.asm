; DCL_NLPID_C3.asm - Series form nonlinear PID controller
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
		.asg	DCL_runNLPID_C3, _DCL_runNLPID_C3
		.endif
      .endif

		.global _DCL_runNLPID_C3

		.sect	"dclfuncs"

; C prototype: float32_t DCL_runNLPID_C3(DCL_NLPID *p, float32_t rk, float32_t yk, float32_t lk)
; argument 1 = *p : [XAR4] NLPID structure address
; argument 2 = rk : [R0H] reference - normalized [-1.0f, +1.0f]
; argument 3 = yk : [R1H] feedback - normalized [-1.0f, +1.0f]
; argument 4 = lk : [R2H] saturation - either 0.0f (saturated) or 1.0f (in range)
; return = uk : [R0H] control

		.align	2

_DCL_runNLPID_C3:
		.asmfunc
		.if (.TMS320C2800_TMU1 = 1)

		; normalized servo error
		SUBF32		R0H, R0H, R1H		; R0H = ek
		ZERO		R5H					; R5H = 0.0f, SUBF32 delay slot
		MPYF32		R0H, #0.5, R0H		; R0H = ek/2 = v1
		ADDF32		R4H, R5H, #1.0		; R4H = 1.0f, MPYF32 delay slot
		ABSF32		R3H, R0H			; R3H = |ek/2| = v3
		SUBF32		R5H, #-1.0, R5H		; R5H = -1.0f
		CMPF32		R0H, #0.0			; set flags on v1
		MOV32		R4H, R5H, LT		; R4H = v2
		MOV32		*SP++, R2H			; push lk

		; nonlinear p-path block
		MOV32		R6H, *+XAR4[6]		; R6H = alpha_p
		LOG2F32		R7H, R3H			; R7H = log2(v3)
		MOV			AR0, #12			; AR0 = delta_p offset
		MOV32		R5H, *+XAR4[AR0]	; R5H = delta_p
		MOV			AR1, #18			; AR1 = gamma_p offset
		MPYF32		R2H, R6H, R7H		; R2H = alpha_p * log2(v3)
		MOV32		*SP++, R7H			; push log2(v3)
		NEGF32		R2H, R2H			; R2H = -(alpha_p * log2(v3))
		IEXP2F32	R2H, R2H			; R2H = 2^(x*log2(v3))
		MOV32		R7H, *+XAR4[AR1]	; R6H = gamma_p
		MPYF32		R7H, R0H, R7H		; R7H = v4 (linear)
		MOV			AR0, #8				; AR0 = alpha_i offset
		MPYF32		R6H, R2H, R4H		; R6H = v4 (sign restore)
		CMPF32		R3H, R5H			; set flags on (v3 - delta_p)
		MOV32		R6H, R7H, LEQ		; R6H = v4

		; nonlinear i-path block
		MOV			AR1, #20			; AR1 = gamma_i offset
		MOV32		R5H, *+XAR4[AR1]	; R5H = gamma_i
		MPYF32		R5H, R0H, R5H		; R5H = v5 (linear)
		MOV32		R2H, *+XAR4[AR0]	; R2H = alpha_i
		MOV32		R7H, *--SP			; R7H = log2(v3)
		MPYF32		R2H, R2H, R7H		; R2H = alpha_i * log2(v3)
		MOV			AR1, #14			; AR1 = delta_i offset
		NEGF32		R2H, R2H			; R2H = -(alpha_i * log2(v3))
		IEXP2F32	R7H, R2H			; R7H = 2^(x*log2(v3))
		NOP								; IEXPF32 delay slot 1
		MOV			AR0, #10			; AR0 = alpha_d offset
		MOV32		R0H, *+XAR4[AR1]	; R0H = delta_i
		MPYF32		R7H, R7H, R4H		; R7H = v5 (sign restore), delay slot after
		CMPF32		R3H, R0H			; set flags on (v3 delta_i)
		MOV32		R5H, R7H, GT		; R5H = v5

		; nonlinear d-path block
		ZERO		R2H					; R2H = 0.0f
		ADDF32		R3H, R2H, #1.0		; R3H = 1.0f
		ABSF32		R4H, R1H			; R4H = |yk| = vd3, ADDF32 delay slot
		SUBF32		R2H, #0.0, R3H		; R2H = -1.0f
		CMPF32		R1H, #0.0			; set flags on yk
		MOV32		R3H, R2H, LT		; R3H = sgn(yk) = vd2
		MOV32		R2H, *+XAR4[AR0]	; R2H = alpha_d
		LOG2F32		R0H, R1H			; R0H = log2(yk)
		MOV			AR1, #22			; AR1 = gamma_d offset
		MOV32		R7H, *+XAR4[AR1]	; R7H = gamma_d
		MPYF32		R7H, R1H, R7H		; R7H = v6 (linear)
		MPYF32		R0H, R2H, R0H		; R0H = alpha_d*log2(yk)
		NOP								; MPYF32 delay slot
		NEGF32		R0H, R0H			; R2H = -(alpha_d * log2(yk))
		IEXP2F32	R1H, R0H			; R1H = 2^(x*log2(yk))
		MOV			AR1, #16			; AR1 = delta_d offset
		MOV32		R2H, *+XAR4[AR1]	; R2H = delta_d
		NOP								; IEXP2F32 delay slot 3
		MPYF32		R1H, R1H, R3H		; R1H = v6 (sign restore), delay slot after
		CMPF32		R4H, R2H			; set flags on (vd3 - delta_d)
		MOV32		R7H, R1H, GT 		; R7H = v6

		; linear i-path
		MOV32		R2H, *+XAR4[0]		; R2H = kp
		MPYF32		R0H, R5H, R2H		; R0H = v5*kp
||		MOV32		R1H, *+XAR4[2]		; R1H = ki
		MOV			AR0, #34			; AR0 = i16 offset
		MPYF32		R0H, R0H, R1H		; R0H = v7
||		MOV32		R4H, *+XAR4[AR0]	; R4H = i16
		MOV			AR0, #32			; AR0 = i7 offset
		MPYF32		R0H, R0H, R4H		; R0H = v7*i16
		MOV32		R1H, *+XAR4[AR0]	; R1H = i7
		ADDF32		R0H, R0H, R1H		; R0H = v8
		MOV			AR1, #24			; AR1 = c1 offset, ADDF32 delay slot
		MOV32		*+XAR4[AR0], R0H	; store i7

		; linear d-path
		MOV32		R1H, *+XAR4[4]		; R1H = kd
		MPYF32		R1H, R7H, R1H		; R1H = v6*kd
||		MOV32		R3H, *+XAR4[AR1]	; R3H = c1
		MOV			AR0, #28			; AR0 = d2 offset
		MPYF32		R1H, R1H, R3H		; R1H = v15
||		MOV32		R3H, *+XAR4[AR0]	; R3H = d2
		MOV			AR1, #30			; AR1 = d3 offset
		SUBF32		R5H, R1H, R3H		; R5H = v15-d2
||		MOV32		*+XAR4[AR0], R1H	; store d2
		MOV32		R4H, *+XAR4[AR1]	; R4H = d3
		SUBF32		R1H, R5H, R4H		; R1H = v16
		MOV			AR0, #26			; AR0 = c2 offset
		MOV32		R4H, *+XAR4[AR0]	; R4H = c2
		MPYF32		R3H, R1H, R4H		; R3H = c2*v16
		SUBF32		R6H, R6H, R1H		; R6H = v4-v16
		MOV32		*+XAR4[AR1], R3H	; store d3
		MPYF32		R2H, R2H, R6H		; R2H = v4a, delay slot after

		; saturation
		MOV			AR0, #38			; AR0 = Umax offset
		ADDF32		R0H, R0H, R2H		; R0H = v9
||		MOV32		R1H, *+XAR4[AR0]	; R1H = Umax
		MOV			AR1, #40			; AR1 = Umin offset
		ZERO		R7H					; R7H = 0.0f
		ADDF32		R6H, R7H, #1.0		; R6H = 1.0
		MOV32		R2H, *+XAR4[AR1]	; R2H = Umin
		MINF32		R0H, R1H			; saturate positive
||		MOV32		R6H, R7H			; R0H = v17
		MAXF32		R0H, R2H			; saturate negative
||		MOV32		R6H, R7H			; R6H = v12
		MOV32		R3H, *--SP			; R3H = lk
		MPYF32		R4H, R3H, R6H		; R4H = lk*v12
		MOV 		AR0, #34			; AR0 = i16 offset
		MOV32		*+XAR4[AR0], R4H	; store i16
		.else
		.emsg			"ERROR - TMU1 NOT PRESENT: _DCL_runNLPID_C3 NOT BUILT"
		.endif
		LRETR							; return

		.endasmfunc
		.end

; end of file
