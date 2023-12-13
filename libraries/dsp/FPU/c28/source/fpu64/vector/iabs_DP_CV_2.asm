;;#############################################################################
;;! \file source/fpu64/vector/iabs_DP_CV_2.asm
;;!
;;! \brief  C-Callable inverse absolute value of an even length complex vector.
;;! \author Vishal Coelho (adapted from SP version by David Alter)
;;! \date   07/11/2016
;;
;; DESCRIPTION:  C-Callable absolute inverse value of a complex vector
;;          y[i] = 1/sqrt(x_re[i]^2 + x_im[i]^2)
;;
;; FUNCTIONS:
;;   void iabs_DP_CV_2(long double *y, const complexf64_t *x, 
;;                  const uint16_t N)
;;  
;; PARAMETERS: long double *y     = output array
;;             complexf64_t *x    = input array
;;             uint16_t N         = length of x and y arrays
;;
;; RETURNS:    none
;;
;; BENCHMARK:  74*N/2 + 17 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be even - the routine does not perform an assertion on the 
;;      arguments, so it is incumbent on the user to pass an even argument
;;   2) The type 'complexf64_t' is defined as
;;
;;      typedef struct {
;;         long double real;
;;         long double imag;
;;      } complexf64_t;
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
;;  void iabs_DP_CV_2(long double *y, const complexf64_t *x, 
;;                  const uint16_t N)
;;
;;  C-Callable absolute value of a complex vector
;;          y[i] = 1/sqrt(x_re[i]^2 + x_im[i]^2)
;;
;; Register Usage:
;;     AL  : N, the number of complex data points (even)
;;    AR0  : N, the number of complex data points (even)
;;   XAR4  : *y, pointer to the output array
;;   XAR5  : *x, pointer to the complex input array
;;

;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- R7H                              (SP-2)
;;   |_______|<- R6H                              (SP-4)
;;   |_______|<- R5H                              (SP-6)
;;   |_______|<- R4H                              (SP-8)
;;   |_______|<- rpc calling function             (SP-10)
;;*****************************************************************************
    .if __TI_EABI__
    .asg iabs_DP_CV_2, _iabs_DP_CV_2
    .endif
    
    .page
    .global _iabs_DP_CV_2
    .sect   ".text"
_iabs_DP_CV_2:
    .asmfunc
    MOV32   *SP++, R4H          ; save R4H to the stack
    MOV32   *SP++, R5H          ; save R5H to the stack
    MOV32   *SP++, R6H          ; save R6H to the stack
    MOV32   *SP++, R7H          ; save R7H to the stack
    
    LSR     AL, #1              ; AL  = N/2
    SUBB    AL, #1              ;     = N/2 - 1
    MOVZ    AR0, AL             ; AR0 = N/2 - 1
    
_iabs_DP_CV_2_loop:
    ;; Computing the magnitude squared
    MOV32       R0L, *XAR5++    ;      R0 = x_re[i]
    MOV32       R0H, *XAR5++    ;      
    MPYF64      R0, R0, R0      ; *|   R0 = x_re[i]^2
 || MOV32       R1L, *XAR5++    ;  |   R1 = x_im[i]
    MOV32       R1H, *XAR5++    ; 1|   
    MOV32       R4L, *XAR5++    ; 2|   R4 = x_re[i+1]
    MPYF64      R1, R1, R1      ; *|   R1 = x_im[i]^2
 || MOV32       R4H, *XAR5++    ;  |   
    MOV32       R5L, *XAR5++    ; 1|   R5 = x_im[i+1]
    MOV32       R5H, *XAR5++    ; 2|   
    MPYF64      R4, R4, R4      ; *|   R4 = x_re[i+1]^2
 || ADDF64      R0, R0, R1      ;  |   R0 = x_re[i]^2 + x_im[i]^2--------X_i
    MPYF64      R5, R5, R5      ; 1|*| R5 = x_im[i+1]^2
    NOP                         ; 2|1|
    ;; Compute the square root
    EISQRTF64   R1, R0          ; *|2| R1 = Ye_i = Estimate(1/sqrt(X_i))
    ADDF64      R4, R4, R5      ; 1|*| R4 = x_re[i+1]^2 + x_im[i+1]^2----X_i+1
    MPYF64      R2, R0, #0.5    ; *|1| R2 = X_i*0.5
    NOP                         ; 1|2|
    EISQRTF64   R5, R4          ; 2|*| R5 = Ye_i+1 = Estimate(1/sqrt(X_i+1))
    MPYF64      R6, R4, #0.5    ; *|1| R6 = X_i+1*0.5
    ;; run loop 3 times         ; -|-| RPTB takes 4 cycles on first iteration
    .align  2
    RPTB        #_iabs_DP_CV_2_isqrt_loop, #2 
    MPYF64      R3, R1, R1      ; *| | R3 = Ye_i^2
    MPYF64      R7, R5, R5      ; 1|*| R7 = Ye_i+1^2
    NOP                         ; 2|1|
    MPYF64      R3, R3, R2      ; *|2| R3 = Ye_i^2*X_i*0.5
    MPYF64      R7, R7, R6      ; 1|*| R7 = Ye_i+1^2*X_i+1*0.5
    NOP                         ; 2|1| 
    SUBF64      R3, #1.5, R3    ; *|2| R3 = 1.5 - Ye_i^2*X_i*0.5
    SUBF64      R7, #1.5, R7    ; 1|*| R7 = 1.5 - Ye_i+1^2*X_i+1*0.5
    NOP                         ; 2|1| 
    ;; R1 = Ye_i   = Ye_i*(1.5 - Ye_i^2*X_i*0.5)
    ;; R1 = Ye_i+1 = Ye_i+1*(1.5 - Ye_i+1^2*X_i+1*0.5)
    MPYF64      R1, R1, R3      ; *|2| 
    MPYF64      R5, R5, R7      ; 1|*| 
    NOP                         ; 2|1|
_iabs_DP_CV_2_isqrt_loop:
    MPYF64      R3, R1, R2      ; *|2| R3 = Ye_i'''*X_i*0.5
    MPYF64      R7, R5, R6      ; 1|*| R7 = Ye_i+1'''*X_i+1*0.5
    NOP                         ; 2|1|
    MPYF64      R3, R1, R3      ; *|2| R3 = Ye_i'''^2*X_i*0.5
    MPYF64      R7, R5, R7      ; 1|*| R7 = Ye_i+1'''^2*X_i+1*0.5
    NOP                         ; 2|1|
    SUBF64      R3, #1.5, R3    ; *|2| R3 = 1.5 - Ye_i'''^2*X_i*0.5
    SUBF64      R7, #1.5, R7    ; 1|*| R7 = 1.5 - Ye_i+1'''^2*X_i+1*0.5
    NOP                         ; 2|1|
    ;; R0 = Ye_i'''*(1.5 - Ye_i'''^2*X_i*0.5)
    ;; R4 = Ye_i+1'''*(1.5 - Ye_i+1'''^2*X_i+1*0.5)
    MPYF64      R0, R1, R3      ; *|2| 
    MPYF64      R4, R5, R7      ; 1|*| 
    NOP                         ; 2|1|
    MOV32       *XAR4++, R0L    ;  |2| 
    MOV32       *XAR4++, R0H    ;  | |
    MOV32       *XAR4++, R4L    ;  | | 
    MOV32       *XAR4++, R4H    ;  | |
    BANZ        _iabs_DP_CV_2_loop, AR0--
    
    MOV32       R7H, *--SP      ; restore R7H from stack
    MOV32       R6H, *--SP      ; restore R6H from stack
    MOV32       R5H, *--SP      ; restore R5H from stack
    MOV32       R4H, *--SP      ; restore R4H from stack
    LRETR
    .endasmfunc

;; End of File
