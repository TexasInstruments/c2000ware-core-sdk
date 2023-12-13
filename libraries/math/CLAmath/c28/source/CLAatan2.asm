;;#############################################################################
;; FILE: CLAatan2.asm
;; 
;; DESCRIPTION: CLA arctan2 function
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
;;   The algorithm steps to calculate the "atan2" of the given
;;   input X and Y is as follows:
;;   
;;   Step(1):   if( abs(X) >= abs(Y) )
;;                  Numerator   = abs(Y)
;;                  Denominator = abs(X)
;;              else
;;                  Numerator   = abs(X)
;;                  Denominator = abs(Y)
;;   
;;   Step(2):   Ratio = Numerator/Denominator
;;   
;;              Note: Ratio range = 0.0 to 1.0
;;   
;;   Step(3):   Use the upper 6-bits of the "Ratio" value as an
;;              index into the table to obtain the coefficients
;;              for a second order equation:
;;   
;;              _FPUatan2Table:
;;                   CoeffA0[0]
;;                   CoeffA1[0]
;;                   CoeffA2[0]
;;                      .
;;                      .
;;                   CoeffA0[63]
;;                   CoeffA1[63]
;;                   CoeffA2[63]
;;   
;;   Step(4):   Calculate the angle using the folowing equation:
;;   
;;              arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;;              arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;;   
;;   Step(5):   The final angle is determined as follows:
;;   
;;              if( X >= 0 and Y >= 0 and abs(X) >= abs(Y) )
;;                  Angle = arctan(abs(Y)/abs(X))
;;              if( X >= 0 and Y >= 0 and abs(X) <  abs(Y) )
;;                  Angle = PI/2 - arctan(abs(X)/abs(Y))
;;              if( X < 0  and Y >= 0 and abs(X) <  abs(Y) )
;;                  Angle = PI/2 + arctan(abs(X)/abs(Y))
;;              if( X < 0  and Y >= 0 and abs(X) >= abs(Y) )
;;                  Angle = PI - arctan(abs(Y)/abs(X))
;;              if( Y < 0 )
;;                  Angle = -Angle
;; Equation:    z = atan(y/x)
;;
;; Regs Used:   MR0, MR1, MR2, MR3, MAR0,MAR1
;;
;; Input:   x , y       two f32 values in memory
;;
;; Output:  z           f32 value in memory
;;          MR0 = z     f32 result
;; 
;; Benchmark:   Cycles = 44  
;;          Instructions = 44
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- MR3                               (SP+4)
;;   |_______|<- atan2 temporary variable 2        (SP+2)
;;   |_______|<- atan2 temporary variable 1        (SP+0)
;;
;;----------------------------------------------------------------------------  


    .def    _CLAatan2
    .sect   "Cla1Prog:_CLAatan2"
    .align  2
	.def    __cla_CLAatan2_sp
__cla_CLAatan2_sp   .usect ".scratchpad:Cla1Prog:_CLAatan2",6,0,1

_CLAatan2:
    .asmfunc
    .asg    __cla_CLAatan2_sp + 0, _atan2_tmp1
    .asg    __cla_CLAatan2_sp + 2, _atan2_tmp2
    .asg    __cla_CLAatan2_sp + 4, _save_MR3  
; Context Save
    MMOV32     @_save_MR3, MR3
; MR0 = Y(fVal1) and MR1 = X(fVal2) is stored in the 
; scratchpad memory
    MMOV32      @_atan2_tmp1,MR0  ;Y
    MMOV32      @_atan2_tmp2,MR1  ;X
; Perform Step (1):
    MABSF32     MR3,MR0           ; MR3 = abs(Y)
    MMOV32      MR2,MR3           ; Store abs(Y) in MR2
    MABSF32     MR1,MR1           ; Store abs(X) in MR1
    MMINF32     MR3,MR1           ; MR3 = numerator (A) = min(abs(Y),abs(X)) 
    MMOV32      MR1,MR2,GT        ; MR1 = denominator (B) = max(abs(Y),abs(X))
                                  ; Ratio = A/B
; Perform Step (2):
    MEINVF32    MR2,MR1           ; MR2 = Ye = Estimate(1/Denominator) i.e 1/B
    MTESTTF     LEQ               ; Set TF if 1.0 >= abs(X) , this will be used in step 5
    MMPYF32     MR0,MR2,MR1       ; MR0 = Ye*B
    MSUBF32     MR0,#2.0,MR0      ; MR0 = 2.0 - Ye*B
    MMPYF32     MR2,MR2,MR0       ; MR2 = Ye = Ye*(2.0 - Ye*B)  (first estimate)
    MMPYF32     MR0,MR2,MR1       ; MR0 = Ye*B
    MSUBF32     MR0,#2.0,MR0      ; MR0 = 2.0 - Ye*B
    MMPYF32     MR2,MR2,MR0       ; MR2 = Ye = Ye*(2.0 - Ye*B)  (second estimate)
    MMPYF32     MR0,MR2,MR3       ; MR0 = Ratio = A*Ye = A/B
; Perform Step (3):
    MMPYF32     MR2,MR0,#64.0     ; 64 = Elements In Table
    MF32TOUI16  MR2,MR2           ; MR2 = int(64*ratio)
    MADD32      MR2,MR2,MR2       ; MR2 = 2*MR2
    MADD32      MR1,MR2,MR2       ; MR1 = 4*MR2
    MADD32      MR2,MR2,MR1       ; MR2 = 6*MR2 this is the index value for the stored data array
    MMOV16      MAR0,MR2,#_CLAatan2Table+4     ; MAR0 points to A2, this will be used in step 4
    MMOVI16     MAR1,#_CLAatan2HalfPITable+2   ; MAR1 points to pi/2, this will be used in step 5
    MNOP
    MNOP
; Perform Step (4):
; arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
    MMOV32      MR1,*MAR0[#-2]++  ; MR1 = A2
    MMPYF32     MR1,MR1,MR0       ; MR1 = A2*Ratio
 || MMOV32      MR3,*MAR0[#-2]++  ; MR3 = A1
    MADDF32     MR3,MR3,MR1       ; MR3 = A1 + A2*Ratio
 || MMOV32      MR1,*MAR0         ; MR1 = A0
    MMPYF32     MR3,MR3,MR0       ; MR3 = Ratio*(A1 + A2*Ratio)
    MADDF32     MR3,MR1,MR3       ; MR3 = A0 + Ratio*(A1 + A2*Ratio)
 || MMOV32      MR2,@_atan2_tmp2  ; MR2 = X (set/clear NF,ZF for use below)
; Perform Step (5):
    MMOV32      MR1,*MAR1,UNC     ; MR1 = pi/2  (no flag change)
    MNEGF32     MR0,MR1,UNC       ; MR0 = -pi/2 (no flag change)
    MMOV32      MR3,MR2,EQ        ; if (X == 0), MR3 = 0
    MNEGF32     MR3,MR3,GEQ       ; if (X >= 0) MR3 flip sign of atan(Ratio)
    MNEGF32     MR3,MR3,TF        ; if (abs(X) >= abs(Y)) flip sign of atan(Ratio)
    
    MNEGF32     MR0,MR0,LT        ; if (X < 0) MR0 = pi/2
    MADDF32     MR0,MR0,MR1       ; MR0 = MR0+pi/2
                                  ; if(X < 0) MR0 = pi
                                  ; if(X > 0) MR0 = 0
 || MMOV32      MR2,@_atan2_tmp1  ; MR2 = Y (set/clear NF,ZF)
    MMOV32      MR0,MR1,NTF       ; if(abs(X) < abs(Y) R3H = pi/2
    MADDF32     MR3,MR3,MR0       ; MR3 = Angle

; Context Restore and Final Operations
    MRCNDD      UNC
    MNEGF32     MR3,MR3,LT        ; if (Y < 0) Angle = -Angle
    MMOV32      MR0,MR3           ; Store Y = atan2(X)
    MMOV32      MR3,@_save_MR3 
    .unasg  _atan2_tmp1
    .unasg  _atan2_tmp2
    .unasg  _save_MR3  
    .endasmfunc
    
;; End of File
