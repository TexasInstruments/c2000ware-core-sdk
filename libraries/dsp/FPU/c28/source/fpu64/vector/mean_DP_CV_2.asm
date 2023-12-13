;;#############################################################################
;;! \file source/fpu64/vector/mean_DP_CV_2.asm
;;!
;;! \brief  C-Callable mean of real and imag parts of a complex vector
;;! \author Vishal Coelho (adapted from SP version by David Alter)
;;! \date   07/13/2016
;;
;; DESCRIPTION: C-Callable mean of real and imag parts of a complex vector.
;;              y_re = sum(x_re)/N
;;              y_im = sum(x_im)/N
;;
;; FUNCTIONS: extern complexf64_t mean_DP_CV_2(const complexf64_t *x, 
;;                                const uint16_t N);
;;  
;; PARAMETERS:  complexf64_t *x = pointer to the complex input array
;;              uint16_t N      = length of x
;;
;; RETURNS:    complexf64_t y = mean of x
;;
;; BENCHMARK:  5*N + 37 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be even.
;;   2) The type 'complexf64_t' is defined as
;;
;;      typedef struct {
;;         long double real;
;;         long double imag;
;;      } complexf64_t;
;;   3) The algorithm is mean_re = sum(re)/N
;;                     mean_im = sum(im)/N
;;      1/N is first computed (for N>8) and stored off.  The summations of the 
;;      real and imaginary parts are then computed, and multiplied by 1/N.  The
;;      first summation of each is a just a load of the first element.
;;      These loads are interleaved at the tail-end of the 1/N computation
;;      to fill delay slots, and is why the loop epilog only shows one
;;      additional summation, and not two).  Register choices for the
;;      summation loop have been carefully chosen (R0 - R3) to allow this.
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

;; the includes

;; external references

;;*****************************************************************************
;;  complexf64_t mean_DP_CV_2(const complexf64_t *x, const uint16_t N);
;;
;; C-Callable mean of real and imag parts of a complex vector
;;
;; Register Usage:
;;     AL  : N, the number of complex data points
;;    AR0  : index into _mean_DP_CV_2_table
;;   XAR4  : *x, pointer to the complex input array
;;   XAR5  : points to _mean_DP_CV_2_table
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- hole                             (SP-1)
;;   |_______|<- AL                               (SP-2)
;;   |_______|<- R6H                              (SP-4)
;;   |_______|<- R5H                              (SP-6)
;;   |_______|<- R4H                              (SP-8)
;;   |_______|<- rpc calling function             (SP-10)
;;*****************************************************************************
    .if __TI_EABI__
    .asg mean_DP_CV_2, _mean_DP_CV_2
    .endif

    .page
    .global _mean_DP_CV_2

    .if __TI_EABI__
    .sect   ".const:_mean_DP_CV_2_table"
    .else
    .sect   ".econst:_mean_DP_CV_2_table"
    .endif
    
    .clink
    .align  2
    ; The notation is hexadecimal. For example 0x1.84p-3 is
    ; (16^0*1 + 16^-1*8 + 16^-2*4)*2^-3 = 0.1895
_mean_DP_CV_2_table:
    .xldouble $strtod("NaN")                   ; _mean_DP_CV_2_table[0]@0   1/0
    .xldouble $strtod("0x1p0")                 ; _mean_DP_CV_2_table[1]@64  1/1
    .xldouble $strtod("0x1p-1")                ; _mean_DP_CV_2_table[2]@128 1/2
    .xldouble $strtod("0x1.554c985f06f69p-2")  ; _mean_DP_CV_2_table[3]@192 1/3
    .xldouble $strtod("0x1p-2")                ; _mean_DP_CV_2_table[4]@256 1/4
    .xldouble $strtod("0x1.999999999999ap-3")  ; _mean_DP_CV_2_table[5]@320 1/5
    .xldouble $strtod("0x1.5566cf41f212dp-3")  ; _mean_DP_CV_2_table[6]@384 1/6
    .xldouble $strtod("0x1.24a8c154c985fp-3")  ; _mean_DP_CV_2_table[7]@448 1/7
    .xldouble $strtod("0x1p-3")                ; _mean_DP_CV_2_table[8]@512 1/8

    .sect   ".text"
_mean_DP_CV_2:
    .asmfunc
    MOV32       *SP++, R4H      ; save R4H to the stack
    MOV32       *SP++, R5H      ; save R5H to the stack
    MOV32       *SP++, R6H      ; save R6H to the stack
    
    MOV         AH, #0          ; AH = 0, AL = N
    MOVL        *SP++, ACC      ; store N on stack for later use

    CMP         AL, #9          ; if(AL < 9)  N=1, Z=0 
                                ; else N=0, Z=? goto over8
    BF          _mean_DP_CV_2_over8, GT
    MOVL        XAR5, #_mean_DP_CV_2_table
    MOV         AR0, ACC<<#2    ; AR0 = N*sizeof(long double)    
    ; R2  = _mean_DP_CV_2_table[N] if AL < 8
    MOV32       R2L, *+XAR5[AR0]
    ADDB        XAR5, #2
    MOV32       R2H, *+XAR5[AR0]
    SUBB        AL, #1
    BF          _mean_DP_CV_2_sub8, UNC
    
_mean_DP_CV_2_over8:
    ;; Compute 1/N
    ZERO        R0              ;      R0 = 0.0
    ZERO        R4              ;      R4 = 0.0
    UI32TOF64   R1, *--SP       ; *|   R1 (B) = float64(N)
    SUBB        AL, #9          ; 1|   AL = N - 9 (-1 for RPTB, -8 for eight 
                                ;           unrolled loop iteration done 
                                ;           during 1/N computation)
    EINVF64     R2, R1          ; *|   R2 = Ye = Estimate(1/B)
    NOP                         ; 1|
    ;; Repeat 4 times - perform 8 accumulations
    .align  2
    RPTB        _mean_DP_CV_2_divLoop, #3
    MPYF64      R3, R2, R1      ; *|1| R3 = Ye*B
 || MOV32       R5L, *XAR4++    ;  | | R5 = x_re[i]
    MOV32       R5H, *XAR4++    ; 1|2| 
    ADDF64      R0, R0, R5      ; 2|*| R0 = sum(x_re[i], i=0:n)
 || MOV32       R6L, *XAR4++    ;  | | R6 = x_im[i]
    MOV32       R6H, *XAR4++    ;  |1|  
    SUBF64      R3, #2.0, R3    ; *|2| R3 = 2.0 - Ye*B       
    ADDF64      R4, R4, R6      ; 1|*| R4 = sum(x_im[i], i=0:n)
 || MOV32       R5L, *XAR4++    ;  | | R5 = x_re[i+1]
    MOV32       R5H, *XAR4++    ; 2|1|
    MPYF64      R2, R2, R3      ; *|2| R2 = Ye = Ye*(2.0 - Ye*B)
 || ADDF64      R0, R0, R5      ;  | | R0 = sum(x_re[i], i=0:n)   
    MOV32       R6L, *XAR4++    ; 1|   R6 = x_im[i+1]
    MOV32       R6H, *XAR4++    ; 2|  
    ADDF64      R4, R4, R6      ;  |*| R4 = sum(x_im[i], i=0:n)
_mean_DP_CV_2_divLoop:

_mean_DP_CV_2_sub8:
    .align  2
    RPTB        _mean_DP_CV_2_loop, AL
    MOV32       R5L, *XAR4++    ;  |1| R5 = x_re[i]
    MOV32       R5H, *XAR4++    ;  |2|  
    ADDF64      R0, R0, R5      ; *|   R0 = sum(x_re[i], i=0:n)
 || MOV32       R6L, *XAR4++    ;  |   R6 = x_im[i]
    MOV32       R6H, *XAR4++    ; 1| 
    ADDF64      R4, R4, R6      ; 2|*| R4 = sum(x_im[i], i=0:n)
_mean_DP_CV_2_loop:

    ;; Divide the sums by N (multiply by 1/N) and store to memory
    MPYF64      R0, R0, R2      ; *|1| R0 = sum(x_re[i])/N returned back
    MOV32       R6H, *--SP      ; 1|2| restore R6H 
    MPYF64      R4, R4, R2      ; 2|*| R4 = sum(x_im[i])/N
 || MOV32       R5H, *--SP      ;  | | restore R5H
    NOP
    NOP
    MOV64       R1, R4, UNC      ; return imaginary average 
    MOV32       R4H, *--SP      ;       restore R4H
    LRETR
    .endasmfunc

  
;; End of File
