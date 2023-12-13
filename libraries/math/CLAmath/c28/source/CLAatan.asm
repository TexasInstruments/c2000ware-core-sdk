;;#############################################################################
;; FILE: CLAatan.asm
;; 
;; DESCRIPTION: CLA arctan function
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
;;   Step(1):   if( 1.0 >= abs(Y) )
;;                  Numerator   = abs(Y)
;;                  Denominator = 1.0
;;              else
;;                  Numerator   = 1.0
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
;;              if( Y >= 0 and 1.0 >= abs(Y) )
;;                  Angle = arctan(abs(Y)/1.0)
;;              if( Y >= 0 and 1.0 <  abs(Y) )
;;                  Angle = PI/2 - arctan(1.0/abs(Y))
;;              if( Y < 0 )
;;                  Angle = -Angle
;; Equation:    y = atan(x)
;;
;; Regs Used:   MR0, MR1, MR2, MR3 , MAR0,MAR1
;;
;; Input:   x           f32 value in memory
;;
;; Output:  y           f32 value in memory
;;          MR0 = y     f32 result
;; 
;; Benchmark:   Cycles =  41 
;;              Instructions =  41
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- MR3                               (SP+2)
;;   |_______|<- atan temporary variable           (SP+0)
;;
;;----------------------------------------------------------------------------


    .def    _CLAatan
    .sect   "Cla1Prog:_CLAatan"
    .align  2
	.def    __cla_CLAatan_sp
__cla_CLAatan_sp    .usect  ".scratchpad:Cla1Prog:_CLAatan",4,0,1

_CLAatan:
    .asmfunc
    .asg    __cla_CLAatan_sp + 0, _atan_tmp
    .asg    __cla_CLAatan_sp + 2, _save_MR3
; Context Save
    MMOV32     @_save_MR3, MR3
; MR0 = X(fVal) is stored in the scratchpad memory
    MMOV32     @_atan_tmp, MR0
; Perform Step (1):
    MABSF32     MR3,MR0            ; MR3 = abs(X)
    MMOVIZ      MR1,#0x3f80        ; MR1 = 1.0 , 0x3f800000 = 1.0 in 32 bit Float
    MMOV32      MR2,MR3            ; Store abs(X) in MR2
    MMINF32     MR3,MR1            ; MR3 = numerator (A) = min(abs(X),1.0) 
    MMOV32      MR1,MR2,GT         ; MR1 = denominator (B) = max(abs(X),1.0)
                                   ; Ratio = A/B
; Perform Step (2):
    MEINVF32    MR2,MR1            ; MR2 = Ye = Estimate(1/Dinominator) i.e 1/B
    MTESTTF     LEQ                ; Set TF if 1.0 >= abs(X) , this will be used in step 5
    MMPYF32     MR0,MR2,MR1        ; MR0 = Ye*B
    MSUBF32     MR0,#2.0,MR0       ; MR0 = 2.0 - Ye*B
    MMPYF32     MR2,MR2,MR0        ; MR2 = Ye = Ye*(2.0 - Ye*B)  (first estimate)
    MMPYF32     MR0,MR2,MR1        ; MR0 = Ye*B
    MSUBF32     MR0,#2.0,MR0       ; MR0 = 2.0 - Ye*B
    MMPYF32     MR2,MR2,MR0        ; MR2 = Ye = Ye*(2.0 - Ye*B)  (second estimate)
    MMPYF32     MR0,MR2,MR3        ; MR0 = Ratio = A*Ye = A/B
; Perform Step (3):
    MMPYF32     MR2,MR0,#64.0      ; 64 = Elements In Table
    MF32TOUI16  MR2,MR2            ; MR2 = int(64*ratio)
    MADD32      MR2,MR2,MR2        ; MR2 = 2*MR2
    MADD32      MR1,MR2,MR2        ; MR1 = 4*MR2
    MADD32      MR2,MR2,MR1        ; MR2 = 6*MR2 this is the index value for the stored data array
    MMOV16      MAR0,MR2,#_CLAatan2Table+4       ; MAR0 points to A2, this will be used in step 4
    MMOVI16     MAR1,#_CLAatan2HalfPITable+2     ; MAR1 points to pi/2, this will be used in step 5
    MNOP
    MNOP
; Perform Step (4):
; arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
    MMOV32      MR1,*MAR0[#-2]++   ; MR1 = A2
    MMPYF32     MR1,MR1,MR0        ; MR1 = A2*Ratio
 || MMOV32      MR3,*MAR0[#-2]++   ; MR3 = A1
    MADDF32     MR3,MR3,MR1        ; MR3 = A1 + A2*Ratio
 || MMOV32      MR1,*MAR0          ; MR1 = A0
    MMPYF32     MR3,MR3,MR0        ; MR3 = Ratio*(A1 + A2*Ratio)
    MADDF32     MR3,MR1,MR3        ; MR3 = A0 + Ratio*(A1 + A2*Ratio)
; Perform Step (5):
    MMOVIZ      MR0,#0.0
    MMOV32      MR1,*MAR1          ; MR1 = pi/2
    MNEGF32     MR3, MR3, UNC      ; MR3 = flip sign of atan(Ratio)
    MNEGF32     MR3, MR3, TF       ; if (1.0 >= abs(Y)) flip sign of atan(Ratio)
    MMOV32      MR2,@_atan_tmp          ; MR2 = Y (set/clear NF,ZF)
    MMOV32      MR0, MR1, NTF      ; if(1.0 < abs(Y) MR0 = pi/2, else MR0 = 0.0
    MADDF32     MR3, MR3, MR0      ; MR3 = Angle

; Context Restore and Final Operations
    MRCNDD      UNC
    MNEGF32     MR3,MR3,LT         ; if (Y < 0) Angle = -Angle
    MMOV32      MR0,MR3            ; Store Y = atan(X)
    MMOV32      MR3,@_save_MR3 
    .unasg  _atan_tmp
    .unasg  _save_MR3
    .endasmfunc
    
;; End of File
