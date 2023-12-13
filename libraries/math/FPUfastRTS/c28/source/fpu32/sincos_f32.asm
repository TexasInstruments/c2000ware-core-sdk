;;#############################################################################
;;! \file source/fpu32/sincos_f32.asm
;;!
;;! \brief  Fast combined sin and cos function for the C28x + Floating-Point 
;;!         Unit.
;;! \author N/A
;;! \date   N/A
;;
;; DESCRIPTION:
;;
;;    This function computes a 32-bit floating point sin and cos given a
;;    radian input.  This function uses the FPU math tables to
;;    compute the sin and cos.
;;
;; FUNCTIONS:
;;
;;    void sincosf (float32 radian, float32* PtrSin, float32* PtrCos)
;;
;; ASSUMPTIONS:
;;
;;     * FPU32sinTable and FPU32cosTable are linked into the project.
;;
;; ALGORITHM:
;;
;;       The sin and cos values are calculated as follows:
;;
;;       1) The offset into a 512 word sin/cos table is calculated:
;;
;;          k = 0x1FF & (int(Radian*512/(2*pi)))
;;
;;
;;       2) The fractional component between table samples is
;;          calculated:
;;
;;          x = fract(Radian*512/2*pi) * (2*pi)/512
;;
;;       3) The output values are calculated as follows:
;;
;;          sin(Radian) = S(k) + x*( C(k) + x*(-0.5*S(k) - x*0.166667*C(k)))
;;          cos(Radian) = C(k) + x*(-S(k) + x*(-0.5*C(k) + x*0.166667*S(k)))
;;
;;          where  S(k) = Sin table value at offset "k"
;;                 C(k) = Cos table value at offset "k"
;;
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

        .page
        .if __TI_EABI__
        .asg    sincosf, _sincos
        .asg    FPU32sinTable, _FPU32sinTable
        .asg    FPU32cosTable, _FPU32cosTable
        .endif
        .global _sincos
        .ref    _FPU32sinTable
        .ref    _FPU32cosTable
        .text
        .if (__TI_EABI__ = 0)
        ; For TI COFF double and float are the same size, so sincosf() and 
        ; sincos() should be the same function
        .global _sincosf
_sincosf:
        .endif
_sincos:                             ; On entry: R0H = Radian, XAR4 = PtrSin, XAR5 = PtrCos
        .asmfunc
        MOVIZ     R1H,#0x42A2        ; R1H = 512/(2*pi) = 512/6.28318531 = 81.4873309
        MOVXI     R1H,#0xF983

        MPYF32    R0H, R0H, R1H      ; R0H = Radian * 512/(2*pi)
     || MOV32     *SP++, R4H         ; store R4H on the stack

        MOVIZ     R2H,#0x3C49        ; R2H = (2*pi)/512 = 6.28318531/512
        MOVXI     R2H,#0x0FDB        ;     = 0x3C490FDB or 0.012271846644531
        F32TOI32  R1H, R0H           ; R1H = int(Radian * 512/(2*pi))
        MOVL      XAR6,#_FPU32cosTable
        MOVL      XAR7,#_FPU32sinTable
        MOV32     ACC, R1H           ; ACC = int(Radian *512/(2*pi))
        AND       @AL,#0x1FF
        LSL       AL,#1
        MOVZ      AR0,@AL            ; AR0 = Index into "sin/cos" table = k
        FRACF32   R0H, R0H           ; R0H = fract(Radian*512/(2*pi))
        MOVIZ     R1H,#0x3E2A        ; R1H = 0.166667 (0x3E2AAAAB)
        MOVXI     R1H,#0xAAAB

        MPYF32    R0H, R0H, R2H      ; R0H = x = fract(Radian*512/(2*pi)) * (2*pi)/512
     || MOV32     R3H, *+XAR6[AR0]   ; R3H = C(k)

        MPYF32    R2H, R1H, R3H      ; R2H = 0.166667*C(k)
     || MOV32     R4H, *+XAR7[AR0]   ; R4H = S(k)

        MPYF32    R1H, R1H, R4H      ; R1H = 0.166667*S(k)
        MPYF32    R2H, R0H, R2H      ; R2H = x*0.166667*C(k)

        MPYF32    R4H, -0.5, R4H     ; R4H = -0.5*S(k)
        MPYF32    R3H, -0.5, R3H     ; R3H = -0.5*C(k)

        MPYF32    R1H, R0H, R1H      ; R1H = x*0.166667*S(k)
     || SUBF32    R2H, R4H, R2H      ; R2H = -0.5*S(k) - x*0.166667*C(k)

        MOV32     R4H, *+XAR6[AR0]   ; R4H = C(k)

        ADDF32    R1H, R3H, R1H      ; R1H = -0.5*C(k) + x*0.166667*S(k)
     || MOV32     R3H, *+XAR7[AR0]   ; R3H = S(k)

        MPYF32    R2H, R0H, R2H      ; R2H = x*(-0.5*S(k) - x*0.166667*C(k))
        MPYF32    R1H, R0H, R1H      ; R1H = x*(-0.5*C(k) + x*0.166667*S(k))
        ADDF32    R2H, R4H, R2H      ; R2H = C(k) + x*(-0.5*S(k) - x*0.166667*C(k))
        SUBF32    R1H, R1H, R3H      ; R1H = -S(k) + x*(-0.5*C(k) + x*0.166667*S(k))

        MPYF32    R2H, R0H, R2H      ; R2H = x*(C(k) + x*(-0.5*S(k) - x*0.166667*C(k)))
     || MOV32     R4H, *+XAR7[AR0]   ; R4H = S(k)

        MPYF32    R1H, R0H, R1H      ; R1H = x*(-S(k) + x*(-0.5*C(k) + x*0.166667*S(k)))
     || MOV32     R3H, *+XAR6[AR0]   ; R3H = C(k)

        ADDF32    R2H, R4H, R2H      ; R2H = S(k) + x*(C(k) + x*(-0.5*S(k) - x*0.166667*C(k)))
     || MOV32     R4H, *--SP         ; Restore R4H from the stack

        ADDF32    R1H, R3H, R1H      ; R1H = C(k) + x*(-S(k) + x*(-0.5*C(k) + x*0.166667*S(k)))

        MOV32     *XAR4, R2H         ; *PtrSin = R2H
        MOV32     *XAR5, R1H         ; *PtrCos = R1H

        LRETR
    
;; End of File
