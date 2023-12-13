;;#############################################################################
;;! \file source/vector/mpy_SP_CSxCS.asm
;;!
;;! \brief C-Callable complex multiply of two floating point numbers
;;! \author David M. Alter
;;! \date   07/20/11
;;
;; HISTORY:
;;   07/20/11 - original (D. Alter)
;;
;; DESCRIPTION: C-Callable complex multiply of two floating point numbers
;;
;; FUNCTION: 
;;   extern complex_float mpy_SP_CSxCS(const complex_float w, 
;;                                     const complex_float x);
;;
;; USAGE:       y = mpy_SP_CSxCS(w,x);
;;
;; PARAMETERS:  complex_float w = input #1
;;              complex_float x = input #2
;;
;; RETURNS:     complex_float y = result
;;
;; BENCHMARK:   19 cycles (including the call and return for COFF)
;;              17 cycles (including the call and return for EABI)
;; NOTES:
;;   1) This is a highly optimized function.  The order of the instructions
;;      is very important.
;;   2) The restore of Save-on-entry register R4H is hidden in a parallel
;;      instruction after its last use.
;;   3) The input and return value is of type 'complex_float':
;;
;;      typedef struct {
;;         float32 dat[2];
;;      } complex_float;
;;
;;      Element dat[0] is the real part, dat[1] is the imag part.
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
        .if __TI_EABI__
        .asg mpy_SP_CSxCS, _mpy_SP_CSxCS
        .endif
    
        .global _mpy_SP_CSxCS
        .text

_mpy_SP_CSxCS:
;Save the utilized save on entry registers
        MOV32       *SP++, R4H      ;save R4H on stack

;Optimally load the input values and do the math
        .if         !__TI_EABI__
        MOV32       R0H, *+XAR4[0]  ;R0H = w_re
        MOV32       R2H, *+XAR5[0]  ;R2H = x_re

        MPYF32      R4H, R0H, R2H   ;R4H = w_re * x_re
        || MOV32    R1H, *+XAR4[2]  ;R1H = w_im

        MPYF32      R2H, R1H, R2H   ;R2H = w_im * x_re
        || MOV32    R3H, *+XAR5[2]  ;R4H = x_im
        .else
        MPYF32      R4H, R0H, R2H   ;R4H = w_re * x_re
        MPYF32      R2H, R1H, R2H   ;R2H = w_im * x_re
        .endif

        MPYF32      R1H, R1H, R3H   ;R1H = w_im * x_im

        MPYF32      R0H, R0H, R3H   ;R0H = w_re * x_im

        SUBF32      R3H, R4H, R1H   ;R3H = (w_re * x_re) - (w_im * x_im)
        || MOV32    R4H, *--SP      ;restore R4H from stack
        ADDF32      R2H, R2H, R0H   ;R2H = (w_im * x_re) + (w_re * x_im)

;Store the return value
        .if         __TI_EABI__
        MOV32       R0H, R3H        ;store real part of return value
        MOV32       R1H, R2H        ;store imag part of return value
        .else
        MOV32       *+XAR6[0], R3H  ;store real part of return value
        MOV32       *+XAR6[2], R2H  ;store imag part of return value
        .endif

;Finish up
        LRETR                       ;return

;end of function mpy_SP_CSxCS()
;*********************************************************************
       .end
;;#############################################################################
;;  End of File
;;#############################################################################
