;;#############################################################################
;;! \file source/fpu64/vector/mpy_DP_CVxCV.asm
;;!
;;! \brief  C-Callable multiply of two double precision complex vectors
;;! \author Vishal Coelho (adapted from SP version by David Alter)
;;! \date   07/13/2016
;;
;; DESCRIPTION: C-Callable multiplication of a complex vector and a complex 
;;              vector
;;              y_re[i] = w_re[i]*x_re[i] - w_im[i]*x_im[i]
;;              y_im[i] = w_re[i]*x_im[i] + w_im[i]*x_re[i]
;;
;; FUNCTIONS:
;;   extern void mpy_DP_CVxCV(complexf64_t *y, const complexf64_t *w, 
;;                    const complexf64_t *x, const uint16_t N)
;;  
;; PARAMETERS:  complexf64_t *y = result complex array
;;              complexf64_t *w = input complex array #1
;;              complexf64_t *x = input complex array #2
;;              uint16_t N      = length of w, x, and y arrays
;;
;; RETURNS:    none
;;
;; BENCHMARK:  20*N + 16 cycles (including the call and return)
;;             
;; NOTES:
;;   1) The type 'complexf64_t' is defined as
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
;; void mpy_DP_CVxCV(complexf64_t *y, const complexf64_t *w, 
;;                    const complexf64_t *x, const uint16_t N)
;;
;; C-Callable multiplication of a complex vector and a complex vector
;;      y_re[i] = w_re[i]*x_re[i] - w_im[i]*x_im[i]
;;      y_im[i] = w_re[i]*x_im[i] + w_im[i]*x_re[i]
;;
;; Register Usage:
;;     AL  :  N, size of the vectors
;;   XAR4  : *y, pointer to the complex output
;;   XAR5  : *w, pointer to the first complex input
;;   XAR6  : *x, pointer to the second complex input
;;   
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- R4H                              (SP-2)
;;   |_______|<- rpc calling function             (SP-4)
;;   |_______|<- pointer to x                     (SP-6)
;;*****************************************************************************
    .if __TI_EABI__
    .asg mpy_DP_CVxCV, _mpy_DP_CVxCV
    .endif
    
    .page
    .global _mpy_DP_CVxCV
    .sect   ".text"
_mpy_DP_CVxCV:
    .asmfunc
    .asg    *-SP[6], STK_ARG_X
    MOV32   *SP++, R4H          ; save R4H to the stack
    MOVL    XAR6, STK_ARG_X     ; XAR6 = &x[0]
    SUBB    AL, #1              ; AL = N - 1 (-1 for RPTB)    
    .align  2
    RPTB    _mpy_DP_CVxCV_loop, AL
    MOV32   R0L, *XAR5++        ;      R0 = w_re
    MOV32   R0H, *XAR5++        ;      
    MOV32   R2L, *XAR6++        ;      R2 = x_re
    MOV32   R2H, *XAR6++        ;      
    MPYF64  R3, R0, R2          ; *|   R3 = w_re * x_re
 || MOV32   R1L, *XAR5++        ;  |   R1 = w_im
    MOV32   R1H, *XAR5++        ; 1|   
    NOP                         ; 2|
    MPYF64  R2, R1, R2          ; *|   R2 = w_im * x_re
 || MOV32   R4L, *XAR6++        ;  |   R4 = x_im
    MOV32   R4H, *XAR6++        ; 1|   
    NOP                         ; 2|   
    MPYF64  R1, R1, R4          ; *|   R1 = w_im * x_im
    MPYF64  R0, R0, R4          ; 1|*| R0 = w_re * x_im
    NOP                         ; 2|1|
    SUBF64  R3, R3, R1          ; *|2| R3 = (w_re * x_re) - (w_im * x_im)
    ADDF64  R2, R2, R0          ; 1|*| R2 = (w_im * x_re) + (w_re * x_im)
    NOP                         ; 2|1|
    MOV32   *XAR4++, R3L        ;  |2| store real part of return value
    MOV32   *XAR4++, R3H        ;
    MOV32   *XAR4++, R2L        ;      store imag part of return value
    MOV32   *XAR4++, R2H        ;
_mpy_DP_CVxCV_loop:

    MOV32   R4H, *--SP          ; restore R4H
    LRETR
    .endasmfunc
    .unasg  STK_ARG_X
  
;; End of File
