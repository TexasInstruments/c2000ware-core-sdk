;;#############################################################################
;;! \file source/vector/mac_SP_RVxCV.asm
;;!
;;! \brief  C-Callable multiply-and-accumulate of a real vector and a 
;;              complex vector
;;! \author David M. Alter
;;! \date   04/23/15
;;
;; HISTORY:
;;    - original (D. Alter)
;;
;; DESCRIPTION: C-Callable multiply-and-accumulate of a real vector and a 
;;              complex vector
;                y_re = sum(x[i]*w_re[i])
;                y_im = sum(x[i]*w_im[i])
;;
;; FUNCTION: 
;;   extern complex_float mac_SP_RVxCV(const complex_float *w,
;;                            const float32 *x, const Uint16 N)
;;
;; USAGE:       y = mac_SP_RVxCV(w, x, N);
;;
;; PARAMETERS:  complex_float *w = input complex array
;;              float32 *x  = input real array
;;              Uint16 N = length of w and x arrays
;; 
;; RETURNS:     complex_float y = complex result
;; 
;; BENCHMARK:   3*N + 28 cycles (including the call and return)
;; 
;; NOTES:
;;   1) N must be at least 5, and can be odd or even.
;;   2) The main loop is unrolled once, but does NOT require N to be even.
;;      The N=odd case is handled by executing one iteration prior to the main
;;      loop, and then executing the unrolled loop for the remaining even 
;;      counts.
;;   3) The inputs and return value are of type 'complex_float':
;; 
;;      typedef struct {
;;         float32 dat[2];
;;      } complex_float;
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
    .asg mac_SP_RVxCV, _mac_SP_RVxCV
    .endif
    
    .global _mac_SP_RVxCV
    .text

_mac_SP_RVxCV:
    MOV32       *SP++,R7H      ;Save R7H (save-on-entry register)
    MOV32       *SP++,R6H      ;Save R6H (save-on-entry register)
                
    ZERO        R3H            ;Zero R3H (y_re accumulator)
    ZERO        R7H            ;Zero R7H (y_im accumulator)
                               
    TBIT        AL, #0         ;Test if N odd or even (result stored in TC bit)
    ADDB        AL, #1         ;Add 1 to properly handle the N=odd case (no 
                               ;effect on N=even case)
    LSR         AL, #1         ;Divide N by 2 (main loop is spatially unrolled 
                               ;once to eliminate delay slots)
    ADDB        AL, #-3        ;Subtract 3 since RPTB is 'n-1' times, and first
                               ;and last iterations done separately

    MOV32       R0H, *XAR4++   ;load first w_re[i]

;--- First loop iteration done separately to avoid having to zero R2H and R6H
;    registers, and also for odd/even loop count control.
    MOV32       R1H, *XAR5++                ;load x[i]
    MPYF32      R2H, R1H, R0H               ;R2H = x[i]*w_re[i]
    || MOV32    R0H, *XAR4++                ;load w_im[i]
    MPYF32      R6H, R1H, R0H               ;R6H = x[i]*w_im[i]
    || MOV32    R0H, *XAR4++                ;load w_re[i+1]

    BF          line1, TC                   ;skip one MAC set if N was odd

    MOV32       R1H, *XAR5++                ;load x[i+1]
    MACF32      R3H, R2H, R2H, R1H, R0H     ;y_re += R2H, R2H = x[i+1]*w_re[i+1]
    || MOV32    R0H, *XAR4++                ;load w_im[i+1]
    MACF32      R7H, R6H, R6H, R1H, R0H     ;y_im += R6H, R6H = x[i+1]*w_im[i+1]
    || MOV32    R0H, *XAR4++                ;load w_re[i]

;---Main loop
line1:
    RPTB        end_loop, @AL

    MOV32       R1H, *XAR5++                ;load x[i]
    MACF32      R3H, R2H, R2H, R1H, R0H     ;y_re += R2H, R2H = x[i]*w_re[i]
    || MOV32    R0H, *XAR4++                ;load w_im[i]
    MACF32      R7H, R6H, R6H, R1H, R0H     ;y_im += R6H, R6H = x[i]*w_im[i]
    || MOV32    R0H, *XAR4++                ;load w_re[i+1]
                
    MOV32       R1H, *XAR5++                ;load x[i+1]
    MACF32      R3H, R2H, R2H, R1H, R0H     ;y_re += R2H, R2H = x[i+1]*w_re[i+1]
    || MOV32    R0H, *XAR4++                ;load w_im[i+1]
    MACF32      R7H, R6H, R6H, R1H, R0H     ;y_im += R6H, R6H = x[i+1]*w_im[i+1]
    || MOV32    R0H, *XAR4++                ;load w_re[i]

end_loop:

;--- Last loop iteration done separately to avoid pointer overrun and loading
;    from possibly undefined memory
    MOV32       R1H, *XAR5++                ;load x[i]
    MACF32      R3H, R2H, R2H, R1H, R0H     ;y_re += R2H, R2H = x[i]*w_re[i]
    || MOV32    R0H, *XAR4++                ;load w_im[i]
    MACF32      R7H, R6H, R6H, R1H, R0H     ;y_im += R6H, R6H = x[i]*w_im[i]
    || MOV32    R0H, *XAR4++                ;load w_re[i+1]
                
    MOV32       R1H, *XAR5                  ;load x[i+1]
    MACF32      R3H, R2H, R2H, R1H, R0H     ;y_re += R2H, R2H = x[i+1]*w_re[i+1]
    || MOV32    R0H, *XAR4                  ;load w_im[i+1]
    MACF32      R7H, R6H, R6H, R1H, R0H     ;y_im += R6H, R6H = x[i+1]*w_im[i+1]

;--- Final accumulations and result storage
    NOP                                     ;delay slot
    ADDF32      R3H, R3H, R2H               ;Final accumulate for y_re
    ADDF32      R7H, R7H, R6H               ;Final accumulate for y_im
    || MOV32    R6H,*--SP                   ;Restore R6H

;Store the return value
 	.if		__TI_EABI__
    MOV32       R0H, R3H                    ;store real part of return value
    MOV32       R1H, R7H                    ;store imag part of return value
    .else
    MOV32       *+XAR6[0], R3H              ;store real part of return value
    MOV32       *+XAR6[2], R7H              ;store imag part of return value
    .endif

;Finish up
    MOV32       R7H,*--SP                   ;Restore R7H
    LRETR                                   ;return

;end of function _mac_SP_RVxCV()
;*********************************************************************

    .end

;;#############################################################################
;;  End of File
;;#############################################################################
