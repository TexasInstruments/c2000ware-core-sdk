;;#############################################################################
;;! \file source/fpu32/cos_f32.asm
;;!
;;! \brief  Fast cos function for the C28x + Floating-Point Unit.
;;! \author N/A
;;! \date   N/A
;;
;; DESCRIPTION:
;;
;;    This function computes a 32-bit floating point cos given a
;;    radian input.  This function uses the FPU math tables to
;;    compute the cos.
;;
;; FUNCTIONS:
;;
;;    float32 cosf (float32 radian)
;;
;; ASSUMPTIONS:
;;
;;     * FPU32sinTable and FPU32cosTable are linked into the project.
;;
;; ALGORITHM:
;;
;;       The cos value is calculated as follows:
;;
;;       1) The offset into a 512 word sin/cos table is calculated:
;;          k = 0x1FF & (int(Radian*512/(2*pi)))
;;
;;
;;       2) The fractional component between table samples is
;;          calculated:
;;          x = fract(Radian*512/2*pi) * (2*pi)/512
;;
;;       3) The output sine value is calculated as follows:
;;
;;          cos(Radian) = C(k) + x*(-S(k) + x*(-0.5*C(k) + 0.166667*x*S(k)))
;;
;;          sin(Radian) = S(k) + x*(C(k) + x*(-0.5*S(k) - 0.166667*x*C(k)))
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
        .asg    cosf, _cos
        .asg    FPU32sinTable, _FPU32sinTable
        .asg    FPU32cosTable, _FPU32cosTable
        .endif
        .global _cos
        .ref    _FPU32sinTable
        .ref    _FPU32cosTable
        .text
        .if (__TI_EABI__ = 0)
        ; For TI COFF double and float are the same size, so cosf() and 
        ; cos() should be the same function
        .global _cosf
_cosf:
        .endif
_cos:   .asmfunc                     ; R0H = Radian (on entry)
        MOVIZ     R1H,#0x42A2        ; R1H = 512/(2*pi) = 512/6.28318531 = 81.4873309
        MOVXI     R1H,#0xF983
        MPYF32    R0H, R0H, R1H      ; R0H = Radian * 512/(2*pi)
        MOVIZ     R2H,#0x3C49        ; R2H = (2*pi)/512 = 6.28318531/512
        MOVXI     R2H,#0x0FDB        ;     = 0x3C490FDB or 0.012271846644531
        F32TOI32  R1H, R0H           ; R1H = int(Radian * 512/(2*pi))
        MOVL      XAR6,#_FPU32sinTable
        MOVL      XAR7,#_FPU32cosTable
        MOV32     ACC, R1H           ; ACC = int(Radian *512/(2*pi))
        AND       @AL,#0x1FF
        LSL       AL,#1
        MOVZ      AR0,@AL            ; AR0 = Index into "sin/cos" table = k
        FRACF32   R0H, R0H           ; R0H = fract(Radian*512/(2*pi))
        MOVIZ     R3H,#0x3E2A        ; R3H = 0.166667 (0x3E2AAAAB)
        MOVXI     R3H,#0xAAAB
        MPYF32    R2H, R0H, R2H      ; R2H = x = fract(Radian*512/(2*pi)) * (2*pi)/512
     || MOV32     R1H,*+XAR6[AR0]    ; R1H = S(k)
        MPYF32    R3H, R3H, R1H      ; R3H = .166*C(k)
     || MOV32     R0H,*+XAR7[AR0]    ; R0H = C(k)
        MPYF32    R0H, -0.5, R0H     ; R0H = -.5*C(k)
        MPYF32    R3H, R2H, R3H      ; R1H = x*0.166667*S(k)
        NOP
        ADDF32    R0H, R0H, R3H      ; R0H = -.5*C(k) + 0.166667*x*S(k)
        NOP
        MPYF32    R3H, R2H, R0H      ; R3H = x*(-.5*C(k) + 0.166667*x*S(k))
     || MOV32     R1H, *+XAR6[AR0]   ; R1H = S(k)
        NOP
        SUBF32    R3H, R3H, R1H      ; R3H = -S(k) + x*(-.5*C(k) + 0.166667*x*S(k))
        NOP
        MPYF32    R3H, R2H, R3H      ; R3H = x*(-S(k) + x*(-.5*C(k) + 0.166667*x*S(k)))
     || MOV32     R0H, *+XAR7[AR0]   ; R0H = C(k)
        NOP
        ADDF32    R0H, R0H, R3H      ; R0H = cos(Radian) = C(k) + x*(-S(k) + x*(-.5*C(k) + 0.166667*x*S(k)))
        LRETR
        .endasmfunc
    
;; End of File
