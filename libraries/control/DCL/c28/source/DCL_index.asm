; DCL_index.asm - computes performance indices from TCM data
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
		.asg	DCL_runITAE_C1, _DCL_runITAE_C1
		.asg	DCL_runIAE_C1, _DCL_runIAE_C1
		.asg	DCL_runIES_C1, _DCL_runIES_C1
		.endif
      .endif

		.global	_DCL_runITAE_C1
		.global	_DCL_runIAE_C1
		.global	_DCL_runIES_C1

		.sect	"dclfuncs"

; 11/14/2017: [RP] changed AR7 to AR0

; C prototype: float DCL_runITAE_C1(FDLOG *elog, float prd)
; argument 1 = *elog: address of input data [XAR4]
; argument 2 = prd : sample period in seconds [R0H]
; return = ITAE index [R0H]

		.align	2

_DCL_runITAE_C1:
		.asmfunc
		MOVL		ACC, *+XAR4[2]				; ACC = elog.lptr
		SUBL		ACC, *+XAR4[0]				; ACC = buffer length
		LSR			AL, #1						; AL = N/2
		MOV			AR0, AL
		ZERO		R2H
		ZERO		R3H
		MOVL		XAR5, *XAR4
;--- repeat loop
		RPTB		_ITAE_END, AR0
		MOV32		R1H, *XAR5++				; R1H = data
		ABSF32		R1H, R1H					; R1H = abs(data)
		MPYF32		R1H, R1H, R3H				; R1H = abs(data) * time
		ADDF32		R3H, R3H, R0H				; R3H = time
		ADDF32		R2H, R2H, R1H				; R2H = cumulative index
_ITAE_END:
		NOP
		MOV32		R0H, R2H
		LRETR
		.endasmfunc

		.page

; C prototype: float DCL_runIAE_C1(FDLOG *elog)
; argument 1 = *elog: address of input data [XAR4]
; return = IAE index [R0H]

		.align	2

_DCL_runIAE_C1:
		.asmfunc
		MOVL		ACC, *+XAR4[2]				; ACC = elog.lptr
		SUBL		ACC, *+XAR4[0]				; ACC = buffer length
		LSR			AL, #1						; AL = N/2
		MOV			AR0, AL
		ZERO		R0H
		MOVL		XAR5, *XAR4
;--- repeat loop
		RPTB		_IAE_END, AR0
		MOV32		R1H, *XAR5++				; R1H = data
		ABSF32		R1H, R1H					; R1H = abs(data)
		ADDF32		R0H, R0H, R1H				; R0H = cumulative index
		NOP
		NOP
		NOP
_IAE_END:
		LRETR
		.endasmfunc

		.page

; C prototype: float DCL_runIES_C1(FDLOG *elog)
; argument 1 = *elog: address of input data [XAR4]
; return = IES index [R0H]

		.align	2

_DCL_runIES_C1:
		.asmfunc
		MOVL		ACC, *+XAR4[2]				; ACC = elog.lptr
		SUBL		ACC, *+XAR4[0]				; ACC = buffer length (N) in 16-bit words
		LSR			AL, #1						; AL = N in 32-bit words
		MOV			AR0, AL						; AR7 = loop count
		ZERO		R0H
		MOVL		XAR5, *XAR4
;--- repeat loop
		RPTB		_IES_END, AR0
		MOV32		R1H, *XAR5++				; R1H = data
		MPYF32		R2H, R1H, R1H				; R2H = data^2
		NOP
		ADDF32		R0H, R0H, R2H				; R0H = cumulative index
		NOP
		NOP
_IES_END:
		LRETR
		.endasmfunc

		.end

; end of file
