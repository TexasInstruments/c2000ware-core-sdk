;;###########################################################################
;;
;; \file cla_memcpy16.asm
;;
;; \brief Example data block copy using CLA
;;
;; Group: 			C2000
;; Target Family:	F2837x
;;
;; CLA tasks will copy "Cla16bWords" number of continuous 16b words from
;; "ClaSrcAddr" to "ClaDstAddr" using bursts of 16 MOV instructions.
;;
;; Parameters Cla16bWords, ClaSrcAddr, and ClaDstAddr should be declared in
;; CPU to CLA message memory.
;;
;; Cla1Task1 uses 16b MOV instructions 
;; Cla1Task2 uses 32b MOV instructions
;;
;;
;;#############################################################################
;;
;;
;;$Copyright:
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
;;#############################################################################

;; Include variables and constants that will be shared in the
;; C28x C-code and CLA assembly code.  This is accomplished by
;; using .cdecls to include a C-code header file that contains
;; these variables and constants

      .cdecls   C,LIST,"cla_memcpy16.h"

;; CLA code must be within its own assembly section and must be
;; even aligned.  Note: since all CLA instructions are 32-bit
;; this alignment naturally occurs and the .align 2 is most likely
;; redundant

      .sect    "Cla1Prog"
      .align  2


_Cla1Prog_Start:

_Cla1Task1:
    MMOV16     MAR0,  @_ClaSrcAddr
    MMOV16     MAR1,  @_ClaDstAddr
    MMOV32     MR1,   @_Cla16bWords ; 16b word counter
    MMOVIZ     MR2,   #0x0000   ; MR2[31:16] = 0x0000
    MMOVXI     MR2,   #0x0010   ; MR2[15:00] = 0x0010 -- 16x16b words moved per loop iteration

_Move16x16bWords
    MMOVZ16    MR0,  *MAR0[1]++  ;  1 R
    MMOV16     *MAR1[1]++, MR0   ;  1 W
    MMOVZ16    MR0,  *MAR0[1]++  ;  2 R
    MMOV16     *MAR1[1]++, MR0   ;  2 W
    MMOVZ16    MR0,  *MAR0[1]++  ;  3 R
    MMOV16     *MAR1[1]++, MR0   ;  3 W
    MMOVZ16    MR0,  *MAR0[1]++  ;  4 R
    MMOV16     *MAR1[1]++, MR0   ;  4 W
    MMOVZ16    MR0,  *MAR0[1]++  ;  5 R
    MMOV16     *MAR1[1]++, MR0   ;  5 W
    MMOVZ16    MR0,  *MAR0[1]++  ;  6 R
    MMOV16     *MAR1[1]++, MR0   ;  6 W
    MMOVZ16    MR0,  *MAR0[1]++  ;  7 R
    MMOV16     *MAR1[1]++, MR0   ;  7 W
    MMOVZ16    MR0,  *MAR0[1]++  ;  8 R
    MMOV16     *MAR1[1]++, MR0   ;  8 W
    MMOVZ16    MR0,  *MAR0[1]++  ;  9 R
    MMOV16     *MAR1[1]++, MR0   ;  9 W
    MMOVZ16    MR0,  *MAR0[1]++  ; 10 R
    MMOV16     *MAR1[1]++, MR0   ; 10 W
    MMOVZ16    MR0,  *MAR0[1]++  ; 11 R
    MMOV16     *MAR1[1]++, MR0   ; 11 W
    MMOVZ16    MR0,  *MAR0[1]++  ; 12 R
    MMOV16     *MAR1[1]++, MR0   ; 12 W
    MMOVZ16    MR0,  *MAR0[1]++  ; 13 R
    MMOV16     *MAR1[1]++, MR0   ; 13 W
    MMOVZ16    MR0,  *MAR0[1]++  ; 14 R
    MMOV16     *MAR1[1]++, MR0   ; 14 W
    MMOVZ16    MR0,  *MAR0[1]++  ; 15 R

    MSUB32     MR1, MR1, MR2     ;  MR1=MR1-MR2 -- Subtract 16 from counter
    MNOP
    MNOP
    MNOP
    MBCNDD     _Move16x16bWords, GT ; Branch based on ZF/NF set by MSBU32

    MMOV16     *MAR1[1]++, MR0   ; 15 W
    MMOVZ16    MR0,  *MAR0[1]++  ; 16 R
    MMOV16     *MAR1[1]++, MR0   ; 16 W

    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T1End:


_Cla1Task2:
    MMOV16     MAR0,  @_ClaSrcAddr
    MMOV16     MAR1,  @_ClaDstAddr
    MMOV32     MR1,   @_Cla16bWords ; 16b word counter
    MMOVIZ     MR2,   #0x0000   ; MR2[31:16] = 0x0000
    MMOVXI     MR2,   #0x0020   ; MR2[15:00] = 0x0020 -- 16x32b words moved per loop iteration

_Move16x32bWords
    MMOV32     MR0,  *MAR0[2]++  ;  1 R
    MMOV32     *MAR1[2]++, MR0   ;  1 W
    MMOV32     MR0,  *MAR0[2]++  ;  2 R
    MMOV32     *MAR1[2]++, MR0   ;  2 W
    MMOV32     MR0,  *MAR0[2]++  ;  3 R
    MMOV32     *MAR1[2]++, MR0   ;  3 W
    MMOV32     MR0,  *MAR0[2]++  ;  4 R
    MMOV32     *MAR1[2]++, MR0   ;  4 W
    MMOV32     MR0,  *MAR0[2]++  ;  5 R
    MMOV32     *MAR1[2]++, MR0   ;  5 W
    MMOV32     MR0,  *MAR0[2]++  ;  6 R
    MMOV32     *MAR1[2]++, MR0   ;  6 W
    MMOV32     MR0,  *MAR0[2]++  ;  7 R
    MMOV32     *MAR1[2]++, MR0   ;  7 W
    MMOV32     MR0,  *MAR0[2]++  ;  8 R
    MMOV32     *MAR1[2]++, MR0   ;  8 W
    MMOV32     MR0,  *MAR0[2]++  ;  9 R
    MMOV32     *MAR1[2]++, MR0   ;  9 W
    MMOV32     MR0,  *MAR0[2]++  ; 10 R
    MMOV32     *MAR1[2]++, MR0   ; 10 W
    MMOV32     MR0,  *MAR0[2]++  ; 11 R
    MMOV32     *MAR1[2]++, MR0   ; 11 W
    MMOV32     MR0,  *MAR0[2]++  ; 12 R
    MMOV32     *MAR1[2]++, MR0   ; 12 W
    MMOV32     MR0,  *MAR0[2]++  ; 13 R
    MMOV32     *MAR1[2]++, MR0   ; 13 W
    MMOV32     MR0,  *MAR0[2]++  ; 14 R
    MMOV32     *MAR1[2]++, MR0   ; 14 W
    MMOV32     MR0,  *MAR0[2]++  ; 15 R

    MSUB32     MR1, MR1, MR2     ;  MR1=MR1-MR2 -- Subtract 32 from counter
    MNOP
    MNOP
    MNOP
    MBCNDD     _Move16x32bWords, GT ; Branch based on ZF/NF set by MSBU32

    MMOV32     *MAR1[2]++, MR0   ; 15 W
    MMOV32     MR0,  *MAR0[2]++  ; 16 R
    MMOV32     *MAR1[2]++, MR0   ; 16 W

    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T2End:

_Cla1Task3:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T3End:

_Cla1Task4:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T4End:

_Cla1Task5:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T5End:

_Cla1Task6:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T6End:

_Cla1Task7:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T7End:

_Cla1Task8:
    MSTOP
    MNOP
    MNOP
    MNOP
_Cla1T8End:



_Cla1Prog_End:


    .end
    .include "CLAShared.h"




