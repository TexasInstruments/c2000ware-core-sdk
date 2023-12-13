;;#############################################################################
;;! \file source/fpu64/vector/rnd_DP_RS.asm
;;!
;;! \brief  C-Callable unbiased rounding of a floating point scalar.
;;! \author Vishal Coelho (adapted from SP version by David Alter)
;;! \date   07/15/2016
;;
;; FUNCTIONS:
;;   extern long double rnd_DP_RS(long double x);
;;  
;; PARAMETERS: long double x = input value
;;
;; RETURNS:    long double y = result
;;
;; BENCHMARK: 26 cycles (including the call and return)
;; 
;; NOTES:
;;   1) numerical examples:
;;      rnd_DP_RS(+4.4) = +4.0
;;      rnd_DP_RS(-4.4) = -4.0
;;      rnd_DP_RS(+4.5) = +5.0
;;      rnd_DP_RS(-4.5) = -5.0
;;      rnd_DP_RS(+4.6) = +5.0
;;      rnd_DP_RS(-4.6) = -5.0
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
;; long double rnd_DP_RS(long double x);
;;
;; C-Callable unbiased rounding of a floating point scalar
;;
;; Register Usage:
;;   XAR4  : pointer to x
;;   XAR6  : pointer to rounded result (return long double)
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- rpc calling function             (SP-2)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg    rnd_DP_RS, _rnd_DP_RS
    .endif
    
    .page
    .global _rnd_DP_RS
    .sect   ".text"
_rnd_DP_RS:
    .asmfunc
    .asg    *-SP[4], STK_ARG_X
    MOV32   R0L, *+XAR4[0]          ; R0 = x
    MOV32   R0H, *+XAR4[2]          ;
    CMPF64  R0, #0.0                ; determine if x is positive or negative
    MOVST0  NF                      ; Copy NF from MSTF to ST0
    BF      _rnd_DP_RS_negative, LT ; if (x < 0) jump to negative branch
    
    ;; x is positive
    ADDF64  R0, #0.5, R0            ;  *| R0 = x + 0.5
    NOP                             ;  1|
    NOP                             ;  2|
    FRACF64 R1, R0                  ;  *| R1 = fraction of R0
    NOP                             ;  1|
    SUBF64  R0, R0, R1              ;  *| R0 = floor(x+0.5)
    NOP                             ;  1|
    NOP                             ;  2|
    MOV32   *+XAR6[0], R0L          ;   | Return R0
    MOV32   *+XAR6[2], R0H          ;   |
    LRETR                           ;1,2|
   
_rnd_DP_RS_negative:
    ;; x is negative
    ADDF64  R0, #-0.5, R0           ;  *| R0 = x - 0.5
    NOP                             ;  1|
    NOP                             ;  2|
    FRACF64 R1, R0                  ;  *| R1 = fraction of R0
    NOP                             ;  1|
    SUBF64  R0, R0, R1              ;  *| R0 = floor(x-q0.5)
    NOP                             ;  1|
    NOP                             ;  2|
    MOV32   *+XAR6[0], R0L          ;   | Return R0
    MOV32   *+XAR6[2], R0H          ;   |
    LRETR                           ;1,2|
   
    .endasmfunc
    .unasg  STK_ARG_X
  
;; End of File
