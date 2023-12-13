;;#############################################################################
;; FILE: CLAlogN.asm
;; 
;; DESCRIPTION: CLA Base N Logarithmic Function
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
;;   Step(1):   Calculate natural logarithm of fVal (or x)
;;   
;;   Step(2):   Calculate natural logarithm of N
;;            
;;   Step(3):   log_N(x) = log_e(x)/log_e(N)
;;   
;; Benchmark:   Cycles =  67
;;              Instructions =  67
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- temporary logN variable           (SP+2)
;;   |_______|<- MR3                               (SP+0)
;;
;;----------------------------------------------------------------------------  


    .def    _CLAlogN
    .sect   "Cla1Prog:_CLAlogN"
    .align  2
	.def    __cla_CLAlogN_sp
__cla_CLAlogN_sp    .usect ".scratchpad:Cla1Prog:_CLAlogN",4,0,1

_CLAlogN:
    .asmfunc
    .asg    __cla_CLAlogN_sp + 0, _save_MR3
    .asg    __cla_CLAlogN_sp + 2, _logN_tmp
; Context Save
    MMOV32      @_save_MR3, MR3
    MMOV32      @_logN_tmp, MR1           ; Save N to scratchpad
;;----------------------------------------------------------------------------  
;; Step(1):   Calculate natural logarithm of fVal (or x)
;;----------------------------------------------------------------------------      
    
; Step 1    
    MMOV32      MR3,MR0                   
    MMOV32      MR2, MR3                  ; LOAD X TO MR2
; Step 2
    MLSR32      MR2, #23                  ; MR2 = EXPONENT(X)
    MI32TOF32   MR2,MR2                   
; Step 3    
    MMOV32      MR1,@_CLALN_TABLE_MASK1   ; MR1 = 0x3FFFFFFF
    MAND32      MR3, MR1, MR3              
    MMOV32      MR1,@_CLALN_TABLE_MASK2   ; MR1 = 0x3F800000
    MOR32       MR3, MR1, MR3             ; MR3 =X/2^(EXPONENT)
    MFRACF32    MR3,MR3                   ; MR3 = MANTISSA
; Step 4
; || MMOV32  MR1,@_CLABIAS      
;    MSUBF32 MR2,MR2,MR1                  ; MR2 = EXPONENT - BIAS
;
; || MMOV32  MR1,@_CLALNV2                
;    MMPYF32 MR2,MR2,MR1                  ; MR2 = (Exponent-127)*(Ln(2))

    MMPYF32     MR0,MR3,#32.0             ; 32 = Elements In Table
    MF32TOUI16  MR0,MR0                   ; MR0 = int(32*x)
    MADD32      MR0,MR0,MR0               ; MR0 = 2*MR0
    MADD32      MR1,MR0,MR0               ; MR1 = 4*MR0
    MADD32      MR0,MR0,MR1               ; MR0 = 6*MR0 this is the index value 
                                          ; for the stored data array
; MAR1 points to A2, this will be used later
    MMOV16      MAR1,MR0,#_CLALnTable+4   
    
    MMOV32      MR1,@_CLABIAS
    MSUBF32     MR2,MR2,MR1               ; MR2 = EXPONENT - BIAS
 || MMOV32      MR1,@_CLALNV2             ; 
    MMPYF32     MR2,MR2,MR1               ; MR2 = (Exponent-127)*(Ln(2))
; Step 5
; Ln(X) = A0 + Xm(A1 + A2*Xm)
    MMOV32      MR1,*MAR1[#-2]++          ; MR1 = A2
    MMPYF32     MR1,MR3,MR1               ; MR1 = A2*Xm
 || MMOV32      MR0,*MAR1[#-2]++          ; MR0 = A1
    MADDF32     MR1,MR0,MR1               ; MR1 = A1 + A2*Xm
    MMPYF32     MR0,MR3,MR1               ; MR0 = Xm*(A1 + A2*Xm)
 || MMOV32      MR1,*MAR1[#-2]++          ; MR1 = A0 
    MADDF32     MR3,MR1,MR0               ; MR3 = A0 + Ratio*(A1 + A2*Ratio) = Ln(1+mantissa)
    MMOV32      MR0, @_logN_tmp           ; MR0 = N                                          
    MADDF32     MR3,MR3,MR2               
 || MMOV32      MR1,@_CLALNV10         
    MMPYF32     MR3,MR3,MR1               ; Y= (Ln(1+mantissa) + (Exponent-127)*(Ln(2)))/Ln(10)
    MMOV32      @_logN_tmp, MR3           ; Save Ln(x) to scratchpad
    
;;----------------------------------------------------------------------------  
;; Step(2):   Calculate natural logarithm of N
;;----------------------------------------------------------------------------      

; Step 1    
    MMOV32      MR3,MR0                   
    MMOV32      MR2, MR3                  ; LOAD X (N) TO MR2
; Step 2
    MLSR32      MR2, #23                  ; MR2 = EXPONENT(X)
    MI32TOF32   MR2,MR2                   
; Step 3    
    MMOV32      MR1,@_CLALN_TABLE_MASK1   ; MR1 = 0x3FFFFFFF
    MAND32      MR3, MR1, MR3              
    MMOV32      MR1,@_CLALN_TABLE_MASK2   ; MR1 = 0x3F800000
    MOR32       MR3, MR1, MR3             ; MR3 =X/2^(EXPONENT)
    MFRACF32    MR3,MR3                   ; MR3 = MANTISSA
; Step 4
; || MMOV32  MR1,@_CLABIAS      
;    MSUBF32 MR2,MR2,MR1                  ; MR2 = EXPONENT - BIAS
;
; || MMOV32  MR1,@_CLALNV2                
;    MMPYF32 MR2,MR2,MR1                  ; MR2 = (Exponent-127)*(Ln(2))

    MMPYF32     MR0,MR3,#32.0             ; 32 = Elements In Table
    MF32TOUI16  MR0,MR0                   ; MR0 = int(32*x)
    MADD32      MR0,MR0,MR0               ; MR0 = 2*MR0
    MADD32      MR1,MR0,MR0               ; MR1 = 4*MR0
    MADD32      MR0,MR0,MR1               ; MR0 = 6*MR0 this is the index value 
                                          ; for the stored data array
; MAR1 points to A2, this will be used later
    MMOV16      MAR1,MR0,#_CLALnTable+4   
    
    MMOV32      MR1,@_CLABIAS
    MSUBF32     MR2,MR2,MR1               ; MR2 = EXPONENT - BIAS
 || MMOV32      MR1,@_CLALNV2             ; 
    MMPYF32     MR2,MR2,MR1               ; MR2 = (Exponent-127)*(Ln(2))
; Step 5
; Ln(X) = A0 + Xm(A1 + A2*Xm)
    MMOV32      MR1,*MAR1[#-2]++          ; MR1 = A2
    MMPYF32     MR1,MR3,MR1               ; MR1 = A2*Xm
 || MMOV32      MR0,*MAR1[#-2]++          ; MR0 = A1
    MADDF32     MR1,MR0,MR1               ; MR1 = A1 + A2*Xm
    MMPYF32     MR0,MR3,MR1               ; MR0 = Xm*(A1 + A2*Xm)
 || MMOV32      MR1,*MAR1[#-2]++          ; MR1 = A0 
    MADDF32     MR3,MR1,MR0               ; MR3 = A0 + Ratio*(A1 + A2*Ratio) = Ln(1+mantissa)
    MMOV32      MR0, @_logN_tmp           ; MR0 = log_e(x)
    MADDF32     MR3,MR3,MR2               
 || MMOV32      MR1,@_CLALNV10         

    MMPYF32     MR1,MR3,MR1               ; Y= (Ln(1+mantissa) + (Exponent-127)*(Ln(2)))/Ln(10)
                                          ; MR1 = log_e(N)
;;----------------------------------------------------------------------------  
;; Step(3):   log_N(x) = log_e(x)/log_e(N)
;;----------------------------------------------------------------------------      
    MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
    MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
 || MMOV32    @_logN_tmp, MR1  ; save off denominator
    MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
    MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
    MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
 || MMOV32    MR1, @_logN_tmp  ; Reload denominator to set sign
    MNEGF32   MR0,MR0,EQ       ; Optional: if(Den == 0.0) Change Sign Of Num 
; Context Restore and Final Operations
    MRCNDD    UNC
    MMPYF32   MR0,MR2,MR0      ; MR0 = Y = Ye*Num
    MMOV32    MR0,MR0          ; Optional: Set/Clear MSTF NF and ZF flags
    MMOV32    MR3,@_save_MR3 
    .unasg  _save_MR3
    .unasg  _logN_tmp
    .endasmfunc

;; End of File
 
