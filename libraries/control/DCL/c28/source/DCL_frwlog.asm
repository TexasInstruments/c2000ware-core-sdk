; DCL_frwlog.asm - fast read & write operations to floating-point data log [DCL_fdlog.h]
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
		.asg	DCL_freadLog, _DCL_freadLog
		.asg	DCL_fwriteLog, _DCL_fwriteLog
		.endif
      .endif

		.global _DCL_freadLog
		.global _DCL_fwriteLog

		.sect	"dclfuncs"

; C prototype: float DCL_freadLog(FDLOG *p);
; argument 1 = *p: address of FDLOG structure [XAR4]
; return = FDLOG data [R0H]

		.align	2

_DCL_freadLog:
		.asmfunc
		MOVL		XAR0, *+XAR4[4]				; XAR0 = p.dptr
		MOVL		ACC, *+XAR4[0]				; ACC = p.fptr
		MOV32		R0H, *XAR0++				; R0H = data, XAR0 = p.dptr + 1
		MOVL		*+XAR4[4], XAR0				; save dptr
		MOVL		P, XAR0						; P = dptr
		SUBUL		P, *+XAR4[2]				; P = dptr - lptr
		MOVL		*+XAR4[4], ACC, GT			; wrap if p.lptr < (p.dptr + 1)
		LRETR
		.endasmfunc

; C prototype: float32_t DCL_fwriteLog(FDLOG *p, float32_t data);
; argument 1 = *p: address of FDLOG structure [XAR4]
; argument 2 = data: input FDLOG data [R0H]
; return = over-written FDLOG data [R0H]

		.align	2

_DCL_fwriteLog:
		.asmfunc
		MOVL		XAR0, *+XAR4[4]				; XAR0 = p.dptr
		MOVL		ACC, *XAR0					; ACC = old data
		MOV32		*XAR0++, R0H				; write new data, XAR0 = p.dptr + 1
		MOV32		R0H, ACC					; save old data to R0H [4 delay slots]
		MOVL		ACC, *+XAR4[0]				; ACC = p.fptr
		MOVL		*+XAR4[4], XAR0				; save dptr
		MOVL		P, XAR0						; P = dptr
		SUBUL		P, *+XAR4[2]				; P = dptr - lptr
		MOVL		*+XAR4[4], ACC, GT			; wrap if p.lptr < (p.dptr + 1)
		LRETR
		.endasmfunc

		.end

; end of file
