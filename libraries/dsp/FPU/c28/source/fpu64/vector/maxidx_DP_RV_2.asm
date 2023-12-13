;;#############################################################################
;;! \file source/fpu64/vector/maxidx_DP_RV_2.asm
;;!
;;! \brief  C-Callable index of maximum value of an even length real array
;;! \author Vishal Coelho (adapted from SP version by David Alter)
;;! \date   07/12/2016
;;
;; DESCRIPTION: C-Callable index of maximum value of an even length real array
;;
;; FUNCTIONS: extern uint16_t maxidx_DP_RV_2(const long double *x, 
;;                                const uint16_t N);
;;  
;; PARAMETERS:  long double *x = pointer to the input array
;;              uint16_t N     = length of x
;;
;; RETURNS:    uint16_t index = index of maximum value in x
;;
;; BENCHMARK:  4*N + 22 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be even and <= 65535.
;;   2) If more than one instance of the max value exists in x[], the function
;;      will return the index of the first occurrence (lowest index value).
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
;;  uint16_t maxidx_DP_RV_2(const long double *x, const uint16_t N)
;;
;; C-Callable index of maximum value of an even length real array
;;
;; Register Usage:
;;     AL  : N, the number of real data points
;;   XAR4  : *x, pointer to the real input array
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg maxidx_DP_RV_2, _maxidx_DP_RV_2
    .endif
    
    .page
    .global _maxidx_DP_RV_2
    .sect   ".text"
_maxidx_DP_RV_2:
    .asmfunc
    MOV32       R0L, *XAR4++    ; R0 = x[0] (initial max is first element 
    MOV32       R0H, *XAR4++    ; in x[])
    ZERO        R2              ; R2 = 0 (initial index is 0)
    ZERO        R3              ; R3 = 0 (index of first max candidate)
    LSR         AL, #1          ; AL = N/2
    SUBB        AL, #1          ; AL = N/2 - 1
    
    ;; Main Loop
    .align  2
    RPTB        _maxidx_DP_RV_2_loop, AL
    ADDF64      R3, R3, #1.0    ; *| increment index candidate
    MOV32       R1L, *XAR4++    ; 1| R1 = x[i] (max candidate)
    MOV32       R1H, *XAR4++    ; 2|
    ;; if max < max_candidate, max = max_candidate and index = index_candidate
    MAXF64      R0, R1          ;    if R0 < R1, R0 = R1 and R2 = R3
 || MOV64       R2, R3
    ADDF64      R3, R3, #1.0    ; *| increment index candidate
    MOV32       R1L, *XAR4++    ; 1| R1 = x[i] (max candidate)
    MOV32       R1H, *XAR4++    ; 2|
    ;; if max < max_candidate, max = max_candidate and index = index_candidate
    MAXF64      R0, R1          ;    if R0 < R1, R0 = R1 and R2 = R3
 || MOV64       R2, R3
_maxidx_DP_RV_2_loop:
    NOP
    ;; prepare the return value
    F64TOUI32   R2H, R2         ; *| convert index from float64 to uint32
    NOP                         ; 1|
    NOP                         ;    alignment cycle for FPU-to-CPU move
    MOV32       ACC, R2H        ;    index (return value) is in AL (uint16_t)
    LRETR
    .endasmfunc

  
;; End of File
