;;#############################################################################
;; FILE: CLAexp.asm
;; 
;; DESCRIPTION: CLA Exponent function
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
;; Description: 
;;   Step(1):   Calculate absolute of x   
;;   
;;   Step(2):   Identify the integer and mantissa of the input
;;            
;;   Step(3):   Obtain the e^integer(x) from the table 
;;   
;;   Step(4):   Calculate the value of e^(mantissa)by using the 
;;              polynomial approx = 1 + x*(1+x*0.5(1+(x/3)(1+x/4(1+x/5*(1+x/6*(1+x/7))))))
;;   
;;   Step(5):   The value of e^x is the product of results from (3)&(4)
;;              
;;   
;; Benchmark:   Cycles = 41
;;              Instructions = 41
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- exponent temporary variable       (SP+2)
;;   |_______|<- MR3                               (SP+0)
;;
;;---------------------------------------------------------------------------- 

    
    .def    _CLAexp
    .sect   "Cla1Prog:_CLAexp"
    .align  2
	.def    __cla_CLAexp_sp
__cla_CLAexp_sp .usect ".scratchpad:Cla1Prog:_CLAexp",4,0,1

_CLAexp:
    .asmfunc
    .asg    __cla_CLAexp_sp + 0, _save_MR3
    .asg    __cla_CLAexp_sp + 2, _exp_tmp 
; Context Save
    MMOV32   @_save_MR3, MR3
; The input argument fVal is refered to as X
; save input argument on scratchpad
    MMOV32   @_exp_tmp,MR0
; Step 1
    MMOV32    MR3,MR0           ; Load argument into MR3
    MABSF32   MR3,MR3           ; LOAD |X| TO MR3
    
; Step 2    
    MF32TOI32 MR0,MR3           ; MR0 = INTEGER(X)   
    MFRACF32  MR1,MR3           ; MR1 = MANTISSA(X)
; Step 3
    MADD32    MR2,MR0,MR0
    MMOV16    MAR1,MR2,#_CLAExpTable       
           
; Step 3
    MMOV32    MR2,@_CLAINV7     ; MR2 = 1/7
    MMPYF32   MR3,MR2,MR1       ; MR3 = Xm/7
 || MMOV32    MR2,@_CLAINV1     ; MR2 = 1
    MADDF32   MR3,MR3,MR2       ; MR3 =(1+Xm/7)
    MMOV32    MR2,@_CLAINV6     ; MR2 = 1/6
 || MMPYF32   MR3,MR1,MR3       ; MR3 = Xm(1+Xm/7)
    MMPYF32   MR3,MR3,MR2       ; MR3 = Xm(1+Xm/7)/6
 || MMOV32    MR2,@_CLAINV1     ; MR2 = 1
    MADDF32   MR3,MR3,MR2       ; MR3 = 1+(Xm/6)*(1+Xm/7)
 || MMOV32    MR0,*MAR1         ; MR0 = e^(INTEGER(X))
    MMOV32    MR2,@_CLAINV5     ; MR2 = .2
 || MMPYF32   MR3,MR1,MR3       ; MR3 = Xm(1+Xm/6*(1+Xm/7))
    MMPYF32   MR3,MR3,MR2       ; MR3 = Xm(1+Xm/6*(1+Xm/7))/5
 || MMOV32    MR2,@_CLAINV1     ; MR2 = 1
    MADDF32   MR3,MR3,MR2       ; MR3 = 1+(Xm/5)*(1+Xm/6*(1+Xm/7))
    MMOV32    MR2,@_CLAINV4     ; MR2 = .25
 || MMPYF32   MR3,MR1,MR3       ; MR3 = Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))
    MMPYF32   MR3,MR3,MR2       ; MR3 = Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))/4
 || MMOV32    MR2,@_CLAINV1     ; MR2 = 1
    MADDF32   MR3,MR3,MR2       ; MR3 = 1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))
    MMOV32    MR2,@_CLAINV3     ; MR2 = .3333333
 || MMPYF32   MR3,MR1,MR3       ; MR3 = Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))
    MMPYF32   MR3,MR3,MR2       ; MR3 = Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))*0.333333
 || MMOV32    MR2,@_CLAINV1     ; MR2 = 1
    MADDF32   MR3,MR3,MR2       ; MR3 = 1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7))))
    MMOV32    MR2,@_CLAINV2     ; MR2 = .5
 || MMPYF32   MR3,MR1,MR3       ; MR3 = Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))
    MMPYF32   MR3,MR3,MR2       ; MR3 = Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))*0.5
 || MMOV32    MR2,@_CLAINV1     ; MR2 = 1
    MADDF32   MR3,MR3,MR2       ; MR3 = 1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2
    MMPYF32   MR3,MR3,MR1       ; MR3 = Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
 || MMOV32    MR2,@_CLAINV1     ; MR2 = 1
    MADDF32   MR3,MR3,MR2       ; MR3 = e^(MANTISSA)= 1+Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6)*(1+Xm/7))))Xm/2)
; Step 4    
    MMPYF32   MR3,MR3,MR0       ; MR3 = e^(MANTISSA) x e^(INTEGER(X))
    MMOV32    MR1,MR3,UNC   
; Calculation of e^-x 
    MEINVF32  MR2,MR1           ; MR2 = Ye = Estimate(1/Den)
    MMPYF32   MR3,MR2,MR1       ; MR3 = Ye*Den
    MSUBF32   MR3,#2.0,MR3      ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3       ; MR2 = Ye = Ye*(2.0 - Ye*Den)
    MMPYF32   MR3,MR2,MR1       ; MR3 = Ye*Den
    MSUBF32   MR3,#2.0,MR3      ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3       ; MR2 = Ye = Ye*(2.0 - Ye*Den)
 || MMOV32    MR0,@_exp_tmp     ; MR2 = X (set/clear NF,ZF)
; Context Restore and Final Operations
    MRCNDD    UNC
    MMOV32    MR1,MR2,LT        ; update e^X with inverse value     
    MMOV32    MR0,MR1           ; Store result in MR0
    MMOV32    MR3,@_save_MR3 
    .unasg  _save_MR3
    .unasg  _exp_tmp 
    .endasmfunc

;; End of File
 
