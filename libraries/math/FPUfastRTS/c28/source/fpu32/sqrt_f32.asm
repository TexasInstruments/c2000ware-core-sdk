;;#############################################################################
;;! \file source/fpu32/sqrt_f32.asm
;;!
;;! \brief  Fast 32-bit floating-point sqrt for the C28x + Floating-Point Unit.
;;! \author N/A
;;! \date   N/A
;;
;; DESCRIPTION:
;;
;;    This function computes a 32-bit floating point sqrt..
;;
;; FUNCTIONS:
;;
;;    float32 sqrtf(float32 X)
;;
;; ASSUMPTIONS:
;; 
;;
;; ALGORITHM:
;;
;;              Ye = Estimate(1/sqrt(X));
;;              Ye = Ye*(1.5 - Ye*Ye*X*0.5)
;;              Ye = Ye*(1.5 - Ye*Ye*X*0.5)
;;              Y  = sqrt(X) = X*Ye
;;
;;  Group:            C2000
;;  Target Family:    C28x+FPU32
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
       .asg        sqrtf, _sqrt
       .endif
       .global     _sqrt
       .text
	   .if (__TI_EABI__ = 0)
       ; For TI COFF double and float are the same size, so sqrtf() and sqrt()
       ; should be the same function
       .global _sqrtf
_sqrtf:
	   .endif
_sqrt:
                                        ; R0H = X on entry
        EISQRTF32   R1H, R0H            ; R1H = Ye = Estimate(1/sqrt(X))
        MPYF32      R2H, R0H, #0.5      ; R2H = X*0.5
        MPYF32      R3H, R1H, R1H       ; R3H = Ye*Ye
        NOP
        MPYF32      R3H, R3H, R2H       ; R3H = Ye*Ye*X*0.5
        NOP
        SUBF32      R3H, #1.5, R3H      ; R3H = 1.5 - Ye*Ye*X*0.5
        NOP
        MPYF32      R1H, R1H, R3H       ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP
        MPYF32      R3H, R1H, R2H       ; R3H = Ye*X*0.5
        NOP
        MPYF32      R3H, R1H, R3H       ; R3H = Ye*Ye*X*0.5
        NOP
        SUBF32      R3H, #1.5, R3H      ; R3H = 1.5 - Ye*Ye*X*0.5
        CMPF32      R0H, #0.0           ; Check if X == 0
        MPYF32      R1H, R1H, R3H       ; R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP
        MOV32       R1H, R0H, EQ        ; If X is zero, change the Ye estimate to 0
        MPYF32      R0H, R0H, R1H       ; R0H = Y = X*Ye = sqrt(X)
        LRETR
        .endasmfunc
    
;; End of File
