;;#############################################################################
;;! \file source/fpu64/sqrt_f64.asm
;;!
;;! \brief  Square Root function for the C28x + FPU64
;;! \author Vishal Coelho  
;;! \date   01/06/2016 
;;
;; DESCRIPTION:
;;
;;   This function computes a 64-bit floating point sqrt(X). 
;;
;; FUNCTIONS:
;;
;;  float64 sqrt (float64 X) 
;;  
;; ASSUMPTIONS:
;;
;; ALGORITHM:
;;
;:    Ye     = Estimate(1/sqrt(X));
;;    Ye'    = Ye*(1.5 - Ye*Ye*X*0.5)
;;    Ye''   = Ye'*(1.5 - Ye'*Ye'*X*0.5)
;;    Ye'''  = Ye''*(1.5 - Ye''*Ye''*X*0.5)
;;    Ye'''' = Ye'''*(1.5 - Ye'''*Ye'''*X*0.5)
;;    Y      = sqrt(X) = X * Ye''''     
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
    .cdecls C, LIST, "fastrts.h"

;;*****************************************************************************
;; Register Usage:
;;   R0 : X,Y, the argument and the result
;;   R1 :  Ye, first estimate of 1/sqrt(X)(all successive estimates Ye',...)
;;   R2 : X*0.5
;;   R3 : 1.5 - Ye*Ye*X*0.5 (all successive estimates Ye', Ye'' ..)
;;*****************************************************************************
    .page
    .if __TI_EABI__
    .asg        sqrt, _sqrtl
    .endif
    .global     _sqrtl
    .sect       ".text"
_sqrtl:         .asmfunc
    .if CONVERT_F32_TO_F64 == 1
    F32TOF64    R0, R0H          ; convert argument to double precision
    .endif
    EISQRTF64   R1, R0           ; *|R1 = Ye = Estimate(1/sqrt(X))
    NOP                          ; 1|
    MPYF64      R2, R0, #0.5     ; *| R2 = X*0.5
    RPTB        #_isqrt_loop, #2 ; run loop 3 times
    MPYF64      R3, R1, R1       ; 1|*| R3 = Ye*Ye
    NOP                          ; 2|1|
    NOP                          ;   2|
    MPYF64      R3, R3, R2       ; *| R3 = Ye*Ye*X*0.5
    NOP                          ; 1|
    NOP                          ; 2|
    SUBF64      R3, #1.5, R3     ; *| R3 = 1.5 - Ye*Ye*X*0.5
    NOP                          ; 1|
    NOP                          ; 2|
    MPYF64      R1, R1, R3       ; *| R1 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
    NOP                          ; 1|
    NOP                          ; 2|
_isqrt_loop:
    MPYF64      R3, R1, R2       ; *| R3 = Ye'''*X*0.5
    NOP                          ; 1|
    NOP                          ; 2|
    MPYF64      R3, R1, R3       ; *| R3 = Ye'''*Ye'''*X*0.5
    NOP                          ; 1|
    NOP                          ; 2|
    SUBF64      R3, #1.5, R3     ; *| R3 = 1.5 - Ye'''*Ye'''*X*0.5
    CMPF64      R0, #0.0         ; 1| if X == 0, set ZF, NF
    NOP                          ; 2|
    MPYF64      R1, R1, R3       ; *| R1 = Ye'''*(1.5 - Ye'''*Ye'''*X*0.5)
    NOP                          ; 1|
    NOP                          ; 2|
    MOV64       R1, R0, EQ       ; If X is zero, set Ye'''' to 0
    MPYF64      R0, R0, R1       ; *  | R0 = Y = X * Ye''''
    LRETR                        ; 1,2|
    .endasmfunc

;;*****************************************************************************
;; This function will run the function above taking the address of the input  
;; and output as arguments                                                    
;;                                                                            
;; Register Usage:                                                            
;;   XAR4 : points to the destination argument                                
;;   XAR5 : points to the source argument                                     
;;*****************************************************************************
    .if __TI_EABI__
    .asg    run_sqrt, _run_sqrt
    .endif
    .global _run_sqrt
    .sect   ".text"
_run_sqrt:  .asmfunc
    MOV32   R0L, *+XAR5[0]
    MOV32   R0H, *+XAR5[2]
    LCR     #_sqrtl
    MOV32   *+XAR4[0], R0L
    MOV32   *+XAR4[2], R0H
    LRETR
    .endasmfunc
;; End of File
