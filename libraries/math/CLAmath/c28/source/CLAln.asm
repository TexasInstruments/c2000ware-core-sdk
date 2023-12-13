;;#############################################################################
;; FILE: CLAln.asm
;; 
;; DESCRIPTION: CLA Natural Logarithm Function
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
;;   Step(2):   Identify the exponent of the input, store it float.
;;            
;;   Step(3):   Identify the mantissa{Xm}.
;;   
;;   Step(4):   Subtract the bias from the exponent and multiply it by Ln(2) 
;;   
;;   Step(5):   Calculate the value of Ln(1+mantissa)by using the 
;;              polynomial approx = a0 + Xm*(a1 + Xm*a2)
;;   
;;   Step(6):   Result = Ln(1+mantissa) + (Exponent-127)*(Ln(2))
;;              
;;   
;; Benchmark:   Cycles =  28 
;;              Instructions = 28
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- MR3                               (SP+0)
;;
;;----------------------------------------------------------------------------  


    .def    _CLAln
    .sect   "Cla1Prog:_CLAln"
    .align  2
	.def    __cla_CLAln_sp
__cla_CLAln_sp  .usect ".scratchpad:Cla1Prog:_CLAln",2,0,1

_CLAln:
    .asmfunc
    .asg     __cla_CLAln_sp + 0, _save_MR3
; Context Save
    MMOV32      @_save_MR3, MR3
; Step 1
    MMOV32      MR3,MR0             
;   MABSF32     MR3,MR3             ; LOAD |X| TO MR3
    MMOV32      MR2, MR3            ; LOAD |X| TO MR2

; Step 2
    MLSR32      MR2, #23            ; MR2 = EXPONENT(X)
    MI32TOF32   MR2,MR2             
; Step 3    
    MMOV32      MR1,@_CLALN_TABLE_MASK1  ; MR1 = 0x3FFFFFFF
    MAND32      MR3, MR1, MR3            ; 
    MMOV32      MR1,@_CLALN_TABLE_MASK2  ; MR1 = 0x3F800000
    MOR32       MR3, MR1, MR3            ; MR3 = X/2^(EXPONENT)
    
    MFRACF32    MR3,MR3             ; MR3 = MANTISSA
; Step 4
;   || MMOV32 MR1,@_CLABIAS
;    MSUBF32 MR2,MR2,MR1            ; MR2 = EXPONENT - BIAS
;       
;   ||MMOV32 MR1,@_CLALNV2          
;    MMPYF32 MR2,MR2,MR1            ; MR2 = (Exponent-127)*(Ln(2))

    MMPYF32     MR0,MR3,#32.0       ; 32 = Elements In Table
    MF32TOUI16  MR0,MR0             ; MR0 = int(32*Xm)
    MADD32      MR0,MR0,MR0         ; MR0 = 2*MR0
    MADD32      MR1,MR0,MR0         ; MR1 = 4*MR0
    MADD32      MR0,MR0,MR1         ; MR0 = 6*MR0 this is the index value for 
                                    ; the stored data array
    
    MMOV16      MAR1,MR0,#_CLALnTable+4     

    MMOV32      MR1,@_CLABIAS        
    MSUBF32     MR2,MR2,MR1         ; MR2 = EXPONENT - BIAS
 || MMOV32      MR1,@_CLALNV2       
    MMPYF32     MR2,MR2,MR1         ; MR2 = (Exponent-127)*(Ln(2))
; Step 5

; Ln(X) = A0 + Xm(A1 + A2*Xm)
    MMOV32      MR1,*MAR1[#-2]++    ; MR1 = A2
    MMPYF32     MR1,MR3,MR1         ; MR1 = A2*Xm
 || MMOV32      MR0,*MAR1[#-2]++    ; MR0 = A1
    MADDF32     MR1,MR0,MR1         ; MR1 = A1 + A2*Xm
    MMPYF32     MR0,MR3,MR1         ; MR0 = Xm*(A1 + A2*Xm)
 || MMOV32      MR1,*MAR1[#-2]++           ; MR1 = A0 
    MADDF32     MR3,MR1,MR0         ; MR3 = A0 + Xm*(A1 + A2*Xm) = Ln(1+mantissa)

; Context Restore and Final Operations
    MRCNDD      UNC
    MADDF32     MR3,MR3,MR2         
    MMOV32      MR0,MR3             ; Y = Ln(1+mantissa) + (Exponent-127)*(Ln(2))
    MMOV32      MR3,@_save_MR3 
    .unasg  _save_MR3
    .endasmfunc

;; End of File
 
