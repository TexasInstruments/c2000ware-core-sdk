;******************************************************************************
; FILE: CLAacos.asm
; 
; DESCRIPTION: CLA arccosine function
; 
;******************************************************************************
;
;  $Release Date: December 10, 2011 $
;  $Copyright:
;// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
;//
;// Redistribution and use in source and binary forms, with or without 
;// modification, are permitted provided that the following conditions 
;// are met:
;// 
;//   Redistributions of source code must retain the above copyright 
;//   notice, this list of conditions and the following disclaimer.
;// 
;//   Redistributions in binary form must reproduce the above copyright
;//   notice, this list of conditions and the following disclaimer in the 
;//   documentation and/or other materials provided with the   
;//   distribution.
;// 
;//   Neither the name of Texas Instruments Incorporated nor the names of
;//   its contributors may be used to endorse or promote products derived
;//   from this software without specific prior written permission.
;// 
;// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;// $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;******************************************************************************

	.cdecls C,LIST,"cla_mixed_c_asm_shared.h"

;;----------------------------------------------------------------------------
;; Description: 
;;
;;             Step(1): Calculate absolute of the input X  
;;
;;             Step(2): Use the upper 6-bits of input "X" value as an
;;                          index into the table to obtain the coefficients
;;                          for a second order equation:
;;
;;                        _CLAacosinTable:
;;                             CoeffA0[0]
;;                             CoeffA1[0]
;;                             CoeffA2[0]
;;                                .
;;                                .
;;                             CoeffA0[63]
;;                             CoeffA1[63]
;;                             CoeffA2[63]
;;
;;             Step(3):   Calculate the angle using the folowing equation:
;;
;;                        arccos(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;;                        arccos(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;;
;;             Step(4):   The final angle is determined as follows:
;;
;;                        if( X < 0 )
;;                            Angle = Pi - Angle
;;
;; Equation:    y = acos(x)
;;
;; Regs Used:   MR0, MR1, MR2, MR3 , MAR0,MAR1
;;
;; Input:   x           f32 value in memory
;;
;; Output:  y           f32 value in memory
;;          MR0 = y     f32 result
;; 
;; Benchmark:   Cycles =  27 
;;              Instructions =  27
;;----------------------------------------------------------------------------

	.sect "Cla1Prog"
	.def _CLAacos

_acos_tmp .usect "CLAscratch",2
_save_MR3 .usect "CLAscratch",2

_CLAacos:
; Context Save
	 MMOV32		@_save_MR3, MR3
	 
; MR0 = X(fVal) is stored in the scratchpad memory
     MMOV32		@_acos_tmp, MR0
	
; Perform Step (1):
     MABSF32     MR3,MR0            ; MR3 = abs(X)
     
; Perform Step (2):
;V.C.130408: The table at this point has 65 triplets instead of 64
;hence we start the table lookup from _CLAacosinTable+6+4 instead
; of just _CLAacosinTable+4

     MMPYF32     MR2,MR3,#63.0      ; 64 = Elements In Table
     MF32TOUI16  MR2,MR2            ; MR2 = int(64*x)
     MADD32      MR2,MR2,MR2        ; MR2 = 2*MR2
     MADD32      MR1,MR2,MR2        ; MR1 = 4*MR2
     MADD32      MR2,MR2,MR1        ; MR2 = 6*MR2 this is the index value for the stored data array
;correct code
     MMOV16      MAR0,MR2,#_CLAacosinTable+4       ; MAR0 points to A2, this will be used in step 4
; old code for incorrect table
; MMOV16      MAR0,MR2,#_CLAacosinTable+10      ; MAR0 points to A2, this will be used in step 4
     MMOVI16     MAR1,#_CLAacosinHalfPITable+2     ; MAR1 points to pi/2, this will be used in step 5
     MNOP
     MNOP
; Perform Step (4):
; arcsin(x) = A0 + x(A1 + A2*x)
     MMOV32      MR1,*MAR0[#-2]++   ; MR1 = A2
     MMPYF32     MR1,MR1,MR3        ; MR1 = A2*x
  || MMOV32      MR2,*MAR0[#-2]++   ; MR2 = A1

     MADDF32     MR2,MR2,MR1        ; MR2 = A1 + A2*x
  || MMOV32      MR1,*MAR0          ; MR1 = A0
     MMPYF32     MR2,MR2,MR3        ; MR3 = x*(A1 + A2*x)
  
     MADDF32     MR3,MR1,MR2        ; MR3 = A0 + x*(A1 + A2*x)=arccosin(x)

; Perform Step (5):
    MMOV32      MR1,*MAR1,UNC     ; MR1 = pi  (no flag change)
	MSUBF32     MR1,MR1,MR3       ; MR2= pi - arcos(x)
  
    MMOV32      MR2,@_acos_tmp    ; MR2 = x (set/clear NF,ZF)
    MMOV32      MR3,MR1,LT 
  
    MMOV32      MR0,MR3           ; Store Y = acos(X)
; Context Restore
	MMOV32		MR3,@_save_MR3 
    MRCNDD	    UNC
    MNOP
    MNOP
    MNOP
