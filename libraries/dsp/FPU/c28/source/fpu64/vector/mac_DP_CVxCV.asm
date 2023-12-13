;;#############################################################################
;;! \file source/fpu64/vector/mac_DP_CVxCV.asm
;;!
;;! \brief  C-Callable multiply-and-accumulate of a complex vector and a 
;;!         double precision complex vector
;;! \author Vishal Coelho (adapted from SP version)
;;! \date   07/19/2016
;;
;; DESCRIPTION: C-Callable multiply-and-accumulate of a complex vector and a 
;;              complex vector
;;               y_re = sum(w_re[i]*x_re[i] - w_im[i]*x_im[i])
;;               y_im = sum(w_re[i]*x_im[i] + w_im[i]*x_re[i])
;;
;; FUNCTIONS:
;;   extern complexf64_t mac_DP_CVxCV(const complexf64_t *w,
;;                            const complexf64_t *x, const uint16_t N)
;;  
;; PARAMETERS:  complexf64_t *w = input complex array #1
;;              complexf64_t *x = input complex array #2
;;              uint16_t N      = length of w and x arrays
;;
;; RETURNS:    complexf64_t y = complex result
;;
;; BENCHMARK:  9*N + 27 cycles (including the call and return) 
;;
;; NOTES:
;;   1) N must be at least 3, and can be odd or even.
;;   2) The type 'complexf64_t' is defined as
;;
;;      typedef struct {
;;         long double real;
;;         long double imag;
;;      } complexf64_t;
;;   3) Return type is a structure; the compiler allocates space for the 
;;      returned structure and passes its address to the function (implicitly)
;;      in XAR6
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
;;  complexf64_t mac_DP_CVxCV(const complexf64_t *w,
;;                            const complexf64_t *x, const uint16_t N)
;;
;; C-Callable multiply-and-accumulate of a complex vector and a 
;; complex vector
;;    y_re = sum(w_re[i]*x_re[i] - w_im[i]*x_im[i])
;;    y_im = sum(w_re[i]*x_im[i] + w_im[i]*x_re[i])
;;
;;
;; Register Usage:
;;     AL  : N, the number of complex data points
;;   XAR4  : *w, pointer to the first complex input array
;;   XAR5  : *x, pointer to the second complex input array
;;   R0,R1 :  returned MAC output
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- R4H                              (SP-2)
;;   |_______|<- R5H                              (SP-4)
;;   |_______|<- R6H                              (SP-6)
;;   |_______|<- R7H                              (SP-8)
;;   |_______|<- rpc calling function             (SP-10)
;;*****************************************************************************
    .if __TI_EABI__
    .asg mac_DP_CVxCV, _mac_DP_CVxCV
    .endif
    
    .page
    .global _mac_DP_CVxCV
    .sect   ".text"
_mac_DP_CVxCV:
    .asmfunc
    MOV32   *SP++, R7H              ; save R7H to the stack
    MOV32   *SP++, R6H              ; save R6H to the stack
    MOV32   *SP++, R5H              ; save R5H to the stack
    MOV32   *SP++, R4H              ; save R4H to the stack
    
    SUBB    AL, #3                  ; AL = N-3 (-1 for RPTB, -2 since two
                                    ; iterations are done seperately from the
                                    ; main loop)        
    MOV32   R0L, *XAR4++            ;      R0 = w_re[0]
    MOV32   R0H, *XAR4++            ;       
    MOV32   R1L, *XAR5++            ;      R1 = x_re[0]
    MOV32   R1H, *XAR5++            ;      
    MPYF64  R3, R0, R1              ; *|   R3 = w_re[0]*x_re[0]
 || MOV32   R4L, *XAR4++            ;  |   R4 = w_im[0]
    MOV32   R4H, *XAR4++            ; 1| 
    MPYF64  R7, R4, R1              ; 2|*| R7 = w_im[0]*x_re[0] 
 || MOV32   R5L, *XAR5++            ;  | | R5 = x_im[0]   
    MOV32   R5H, *XAR5++            ;  |1|
    MPYF64  R2, R4, R5              ; *|2| R2 = w_im[0]*x_im[0]
 || MOV32   R1L, *XAR5++            ;  | | R1 = x_re[i]   
    MOV32   R1H, *XAR5++            ; 1| | 
    MPYF64  R6, R0, R5              ; 2|*| R6 = w_re[0]*x_im[0]
 || MOV32   R0L, *XAR4++            ;  | | R0 = w_re[i]
    MOV32   R0H, *XAR4++            ;  |1| 
    NEGF64  R2, R2                  ;  |2| R2 = -(w_im[0]*x_im[0])

    ;; Main Loop
    .align  2
    RPTB    _mac_DP_CVxCV_loop, AL
    ; R3 = (w_re[i]*x_re[i])-(w_im[i]*x_im[i]), R2 = w_re[i]*x_re[i]
    MACF64  R3, R2, R2, R0, R1      ; *|
 || MOV32   R4L, *XAR4++            ;  |   R4 = w_im[i]
    MOV32   R4H, *XAR4++            ; 1| 
    ; R7 = (w_im[i]*x_re[i])+(w_re[i]*x_im[i]), R6 = w_im[i]*x_re[i]
    MACF64  R7, R6, R6, R4, R1      ; 2|*|
 || MOV32   R5L, *XAR5++            ;  | | R5 = x_im[i]
    MOV32   R5H, *XAR5++            ;  |1|
    ; R3 += (w_re[i]*x_re[i]), R2 = w_im[i]*x_im[i]
    MACF64  R3, R2, R2, R4, R5      ; *|2|
 || MOV32   R1L, *XAR5++            ;  | | R1 = x_re[i+1]
    MOV32   R1H, *XAR5++            ; 1| |
    ; R7 += (w_im[i]*x_re[i]), R6 = w_re[i]*x_im[i]
    MACF64  R7, R6, R6, R0, R5      ; 2|*|
 || MOV32   R0L, *XAR4++            ;  | | R0 = w_re[i+1]
    MOV32   R0H, *XAR4++            ;  |1|
    NEGF64  R2, R2                  ;  |2| R2 = -(w_im[i]*x_im[i])
_mac_DP_CVxCV_loop:
   
    ;; Last Iteration
    ; R3 = (w_re[i]*x_re[i])-(w_im[i]*x_im[i]), R2 = w_re[i]*x_re[i]
    MACF64  R3, R2, R2, R0, R1      ; *| 
 || MOV32   R4L, *XAR4++            ;  |   R4 = w_im[i]
    MOV32   R4H, *XAR4++            ; 1|
    ; R7 = (w_im[i]*x_re[i])+(w_re[i]*x_im[i]), R6 = w_im[i]*x_re[i]
    MACF64  R7, R6, R6, R4, R1      ; 2|*|
 || MOV32   R5L, *XAR5++            ;  | | R5 = x_im[i]
    MOV32   R5H, *XAR5++            ;  |1| 
    ; R3 += (w_re[i]*x_re[i]), R2 = w_im[i]*x_im[i]
    MACF64  R3, R2, R2, R4, R5      ; *|2|
 || MOV32   R4H, *--SP              ;  | | restore R4H
    ; R7 += (w_im[i]*x_re[i]), R6 = w_re[i]*x_im[i]
    MACF64  R7, R6, R6, R0, R5      ; 1|*|
 || MOV32   R5H, *--SP              ;  | | restore R5H
    NOP                             ; 2|1|
    SUBF64  R3, R3, R2              ; *|2| R3 -= (w_im[i]*x_im[i]) {y_re}
    ADDF64  R7, R7, R6              ; 1|*| R7 += (w_re[i]*x_im[i])  {y_im}
 || MOV32   R6H, *--SP              ;  | | restore R6H    
    NOP                             ; 2|1|
    MOV64 R0, R3, UNC               ;  |2| save y_re
    MOV64 R1, R7, UNC               ;  | | save y_im
    MOV32   R7H, *--SP              ;  | | restore R7H
    LRETR
    .endasmfunc

  
;; End of File
