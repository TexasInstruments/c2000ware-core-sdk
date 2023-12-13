;;#############################################################################
;; FILE: CLAisqrt.asm
;; 
;; DESCRIPTION: CLA inverse square root function using Newton Raphson 
;;              Approximation
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

    .cdecls C,LIST,"CLAmath.h"
	.include "CLAeabi.asm"
	
;;----------------------------------------------------------------------------
;; Description: Implement 1/(square root) using Newton-Raphson Method
;;
;; Equation:    y = 1/(sqrt(x))
;;
;; Regs Used:   MR0, MR1, MR2, MR3
;;
;; Input:   x           f32 value in memory
;;
;; Output:  y           f32 value in memory
;;          MR0 = y     f32 result
;;
;; Benchmark:   Cycles = 14
;;              Instructions = 14
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- MR3                               (SP+0)
;;
;;----------------------------------------------------------------------------  


    .def    _CLAisqrt
    .sect   "Cla1Prog:_CLAisqrt"
    .align  2
	.def    __cla_CLAisqrt_sp
__cla_CLAisqrt_sp   .usect ".scratchpad:Cla1Prog:_CLAisqrt",2,0,1
    
_CLAisqrt:
    .asmfunc
    .asg    __cla_CLAisqrt_sp + 0, _save_MR3
; Context Save
    MMOV32      @_save_MR3, MR3
; MR0 = Number
    MEISQRTF32  MR1, MR0        ; MR1 = Ye = Estimate(1/sqrt(X))        
    MMPYF32     MR2, MR0, #0.5  ; MR2 = X*0.5
    MMPYF32     MR3, MR1, MR1   ; MR3 = Ye*Ye
    MMPYF32     MR3, MR3, MR2   ; MR3 = Ye*Ye*X*0.5
    MSUBF32     MR3, #1.5,MR3   ; MR3 = 1.5 - Ye*Ye*X*0.5
    MMPYF32     MR1, MR1, MR3   ; MR1 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
    MMPYF32     MR3, MR1, MR2   ; MR3 = Ye*X*0.5
    MMPYF32     MR3, MR1, MR3   ; MR3 = Ye*Ye*X*0.5
    MSUBF32     MR3, #1.5,MR3   ; MR3 = 1.5 - Ye*Ye*X*0.5        
; Context Restore and Final Operations
    MRCNDD      UNC
    MMPYF32     MR0, MR1, MR3   ; MR0 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
    MMOV32      MR0, MR0        ; Optional: set MSTF NF and ZF flags
    MMOV32      MR3,@_save_MR3 
    .unasg  _save_MR3
    .endasmfunc

;; End of File
 
