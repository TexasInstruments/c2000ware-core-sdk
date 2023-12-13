;;#############################################################################
;;! \file source/fpu64/vector/mac_DP_RVxCV.asm
;;!
;;! \brief  C-Callable multiply-and-accumulate of a real vector and a 
;;!         double precision complex vector
;;! \author Vishal Coelho (adapted from SP version by David Alter)
;;! \date   07/12/2016
;;
;; DESCRIPTION: C-Callable multiply-and-accumulate of a real vector and a 
;;              double precision complex vector
;;               y_re = sum(x[i]*w_re[i])
;;               y_im = sum(x[i]*w_im[i])
;;
;; FUNCTIONS:
;;   extern complexf64_t mac_DP_RVxCV(const complexf64_t *w,
;;                            const long double *x, const uint16_t N)
;;  
;; PARAMETERS:  complexf64_t *w = input complex array
;;              long double *x  = input real array
;;              uint16_t N      = length of w and x arrays
;;
;; RETURNS:    complexf64_t y = complex result
;;
;; BENCHMARK:   6*N + 34 cycles if N=even (including the call and return)
;;              6*N + 28 cycles if N=odd (including the call and return)
;;
;; NOTES:
;;   1) N must be at least 5, and can be odd or even.
;;   2) The main loop is unrolled once, but does NOT require N to be even.
;;      The N=odd case is handled by executing one iteration prior to the main
;;      loop, and then executing the unrolled loop for the remaining even 
;;      counts.
;;   3) The type 'complexf64_t' is defined as
;;
;;      typedef struct {
;;         long double real;
;;         long double imag;
;;      } complexf64_t;
;;   4) Return type is a structure; the compiler allocates space for the 
;;      returned structure and passes its address to the function (implicitly)
;;      in XAR6
;;   5) The MACF64 instruction must be accompanied by a parallel move. 
;;      Although R5H is not used in this routine, it is saved to the stack as 
;;      this provides for a convenient (and safe) dummy parallel read for the 
;;      last MACF64
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
;;  complexf64_t mac_DP_RVxCV(const complexf64_t *w,
;;                            const long double *x, const uint16_t N)
;;
;; C-Callable multiply-and-accumulate of a signed 16-bit integer
;; real vector and a double precision complex vector
;;      y_re = sum(x[i]*w_re[i])
;;      y_im = sum(x[i]*w_im[i])
;;
;;
;; Register Usage:
;;     AL  : N, the number of complex data points
;;   XAR4  : *w, pointer to the complex input array
;;   XAR5  : *x, pointer to the real input array
;;   R0,R1 : returned MAC output
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- R7H                              (SP-2)
;;   |_______|<- R6H                              (SP-4)
;;   |_______|<- R5H                              (SP-6)
;;   |_______|<- rpc calling function             (SP-8)
;;*****************************************************************************
    .if __TI_EABI__
    .asg mac_DP_RVxCV, _mac_DP_RVxCV
    .endif
    
    .page
    .global _mac_DP_RVxCV
    .sect   ".text"
_mac_DP_RVxCV:
    .asmfunc
    MOV32       *SP++, R7H          ; save R7H to the stack
    MOV32       *SP++, R6H          ; save R6H to the stack
    MOV32       *SP++, R5H          ; save R5H to the stack
    
    ZERO        R3                  ; zero R3 (y_re accumulator)
    ZERO        R7                  ; zero R7 (y_im accumulator)
            
    TBIT        AL, #0              ; if N is odd TC = 1, else TC = 0
    ADDB        AL, #1              ; Add 1 to properly handle the N=odd case
                                    ; (no effect on N=even case)
    LSR         AL, #1              ; Divide N by 2 (main loop is spatially 
                                    ; unrolled once to eliminate delay slots)
    ADDB        AL, #-3             ; Subtract 3 since RPTB is 'n-1' times, 
                                    ; and first and last iterations done 
                                    ; separately
    MOV32       R0L, *XAR4++        ; load first w_re[i]
    MOV32       R0H, *XAR4++        ; 
    
    ;; First loop iteration done separately to avoid having to zero R2H and R6H
    ;; registers, and also for odd/even loop count control.
    MOV32       R1L, *XAR5++        ; load x[i]
    MOV32       R1H, *XAR5++        ;
    MPYF64      R2, R1, R0          ; *|   R2 = x[i]*w_re[i]
 || MOV32       R0L, *XAR4++        ;  |   R0 = w_im[i]
    MOV32       R0H, *XAR4++        ; 1|
    MPYF64      R6, R1, R0          ; 2|*| R6 = x[i]*w_im[i]
 || MOV32       R0L, *XAR4++        ;  | | R0 = w_re[i+1]    
    MOV32       R0H, *XAR4++        ;  |1|
    ;; skip one MAC if N odd        ;  |2|
    BF          _mac_DP_RVxCV_odd, TC   
    MOV32       R1L, *XAR5++        ;      load x[i+1]
    MOV32       R1H, *XAR5++        ;
    MACF64      R3, R2, R2, R1, R0  ; *|   y_re += R2, R2 = x[i+1]*w_re[i+1]
 || MOV32       R0L, *XAR4++        ;  |   load w_im[i+1]
    MOV32       R0H, *XAR4++        ; 1|   
    MACF64      R7, R6, R6, R1, R0  ; 2|*| y_im += R6, R6 = x[i+1]*w_im[i+1]
 || MOV32       R0L, *XAR4++        ;  | | load w_re[i]
    MOV32       R0H, *XAR4++        ;  |1| 
_mac_DP_RVxCV_odd:
    ;; Main Loop
    .align  2
    RPTB        _mac_DP_RVxCV_loop, AL
    MOV32       R1L, *XAR5++        ;  |2| load x[i]
    MOV32       R1H, *XAR5++        ;
    MACF64      R3, R2, R2, R1, R0  ; *|   y_re += R2, R2 = x[i]*w_re[i]
 || MOV32       R0L, *XAR4++        ;  |   load w_im[i+1]
    MOV32       R0H, *XAR4++        ; 1|    
    MACF64      R7, R6, R6, R1, R0  ; 2|*| y_im += R6, R6 = x[i]*w_im[i]
 || MOV32       R0L, *XAR4++        ;  | | load w_re[i+1]
    MOV32       R0H, *XAR4++        ;  |1| 
    
    MOV32       R1L, *XAR5++        ;  |2| load x[i+1]
    MOV32       R1H, *XAR5++        ;  | 
    MACF64      R3, R2, R2, R1, R0  ; *|   y_re += R2, R2 = x[i+1]*w_re[i+1]
 || MOV32       R0L, *XAR4++        ;  |   load w_im[i+1]
    MOV32       R0H, *XAR4++        ; 1|   
    MACF64      R7, R6, R6, R1, R0  ; 2|*| y_im += R6, R6 = x[i+1]*w_im[i+1]
 || MOV32       R0L, *XAR4++        ;  | | load w_re[i]
    MOV32       R0H, *XAR4++        ;  |1| 
_mac_DP_RVxCV_loop:
    
    ;; Last loop iteration done separately to avoid pointer overrun and loading
    ;; from possibly undefined memory 
    MOV32       R1L, *XAR5++        ;      load x[i]
    MOV32       R1H, *XAR5++        ;
    MACF64      R3, R2, R2, R1, R0  ; *|   y_re += R2, R2 = x[i]*w_re[i]
 || MOV32       R0L, *XAR4++        ;  |   load w_im[i]
    MOV32       R0H, *XAR4++        ; 1|    
    MACF64      R7, R6, R6, R1, R0  ; 2|*| y_im += R6, R6 = x[i]*w_im[i]
 || MOV32       R0L, *XAR4++        ;  | | load w_re[i+1]
    MOV32       R0H, *XAR4++        ;  |1| 

    MOV32       R1L, *XAR5++        ;  |2| load x[i+1]
    MOV32       R1H, *XAR5++        ;  |
    MACF64      R3, R2, R2, R1, R0  ; *|   y_re += R2, R2 = x[i+1]*w_re[i+1]
 || MOV32       R0L, *XAR4++        ;  |   load w_im[i+1]
    MOV32       R0H, *XAR4++        ; 1|   
    MACF64      R7, R6, R6, R1, R0  ; 2|*| y_im += R6, R6 = x[i+1]*w_im[i+1]
 || MOV32       R5H, *--SP          ;  | | restore R5H  (dummy parallel read) 
    ;; Final accumulations and result storage
    ADDF64      R3, R3, R2          ; *|1| Final accumulate for y_re
    NOP                             ; 1|2|
    ADDF64      R7, R7, R6          ; 2|*| Final accumulate for y_im
 || MOV32       R6H, *--SP          ;  | | restore R6H
    NOP
    MOV64 R0, R3, UNC               ;  |2| save y_re
    MOV64 R1, R7, UNC               ;  | | save y_im    
    
    MOV32       R7H, *--SP          ; restore R7H
    LRETR
    .endasmfunc

  
;; End of File
