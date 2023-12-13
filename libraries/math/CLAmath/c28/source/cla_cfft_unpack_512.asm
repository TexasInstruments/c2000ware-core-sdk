;;#############################################################################
;;
;; FILE:    cla_fft_unpack_512.asm
;;
;; TITLE:   512-pt Complex FFT Spectrum Unpack for the C2000 real-time CLA CPU
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

;;
;;*****************************************************************************
;; includes
;;*****************************************************************************

    .cdecls C,LIST,"CLAmath.h"
    .include "CLAeabi.asm"

;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _CLA_CFFT_unpack512Pt
    .ref    _cla_twiddleFactors
    .ref    _IOBuffer
    .ref    _IOBuffer2

;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; FFT Routine defines
TWIDDLES_TBL_SIZE   .set    1024              ; size of twiddle factor table
NCSTAGES            .set    9                 ; # of complex stages in the CFFT
NCSAMPLES           .set    (1 << NCSTAGES)   ; # of complex samples to unpack
NSAMPLES            .set    (1 <<(NCSTAGES+1)); # of real samples

; If the user changes the name of the buffers in the header files it must be 
; changed here and the code rebuilt
I_BUFFER            .set    _IOBuffer    
O_BUFFER            .set    _IOBuffer2     
; skipfactor = tbl_size/size_of_rfft * 2(complex)*2(words per float)
; where size_of_rfft = 2 * size_of_cfft
SKIPFACTOR          .set    4*(TWIDDLES_TBL_SIZE/(NCSAMPLES*2))
DEBUG_BRKPT_ENABLE  .set    0x0
;;*****************************************************************************
;; macros
;;*****************************************************************************
SET_BRKPT_AT_ITER   .macro  ITER
    .if DEBUG_BRKPT_ENABLE
    MNOP
    MMOVZ16  MR0, @LOOP_COUNTER          ; set ZF = 1 if loop count = 0
    MMOVIZ   MR1, #0
    MMOVXI   MR1, #(NSAMPLES/4 - :ITER: - 1 + 1)
    MCMP32   MR0, MR1
    MNOP
    MNOP
    MNOP
    MBCNDD  _skip_bkpt_:ITER:, NEQ     ; if count != 100 skipfactor
    MNOP
    MNOP
    MNOP
    MNOP
    MNOP
    MNOP
    MDEBUGSTOP
    MNOP
    MNOP
    MNOP
_skip_bkpt_:ITER:
    .endif ;;DEBUG_BRKPT_ENABLE
    .endm
    
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .sect     "Cla1Prog:_CLA_CFFT_unpack512Pt"
    .align    2
__CLA_CFFT_unpack512Pt_sp .usect ".scratchpad:Cla1Prog:_CLA_CFFT_unpack512Pt",14,0,1

;;
;; \brief Run the unpack function on a 1024 point complex spectrum to get 
;;  half of the spectrum of the 2048 point real data (original)
;;
;;! \note
;;! -# This is an off-place algorithm
;;! -# Since this function follows an FFT the input buffer must have been 
;;!   aligned to a 12-bit address, usually the starting address of one of the 
;;!   CLA data RAMs
;;! -# The complex data has real-first ordering i.e. the real part occupies
;;!    the lower double word
;;! -# This function expects the FFT buffers to be global (to both 
;;!   the C28 and CLA) and to be named "IOBuffer" and "IOBuffer2" respectively.
;;!   If the user desires to  change the name, the macros I_BUFFER and O_BUFFER
;;!   must be altered in the source assembly to reflect the new name and the 
;;!   code rebuilt
;;! -# In the loops the code does two extra reads beyond the end of the 
;;!    twiddle factor table. Ensure that atleast 4 words after the twiddle 
;;!    factor table are within CLA accessible data RAM. If using the tables in
;;!    Data ROM this is not an issue as the bit reversal tables follow the 
;;!    twiddle table and you end up reading the first two entries of that 
;;!    table instead
;;
;; \return FFT of the real input in the I/O buffer
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input/Output pointer to the buffer
;;  MAR1: Input/Output pointer to the buffer, pointer to twiddles
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- PTR_OUTPUT                        (SP+13)
;;   |_______|<- PTR_TWIDDLES                      (SP+12)
;;   |_______|<- COS                               (SP+10)
;;   |_______|<- SIN                               (SP+8)
;;   |_______|<- MAR1                              (SP+6)
;;   |_______|<- MAR0                              (SP+5)
;;   |_______|<- loop counter                      (SP+4)
;;   |_______|<- RS                                (SP+2)
;;   |_______|<- MR3                               (SP+0)
;;
;; #cycles = 20 + 36*loop_1Q_count + 8 + 36*loop_2Q_count + 4
;;         = 20 + 36*254 + 8 + 36*255 + 4
;;         = 18356
;;
_CLA_CFFT_unpack512Pt:
    .asmfunc
    .asg    __CLA_CFFT_unpack512Pt_sp + 0,  SCRATCH_MR3
    .asg    __CLA_CFFT_unpack512Pt_sp + 2,  RS_TEMP
    .asg    __CLA_CFFT_unpack512Pt_sp + 4,  LOOP_COUNTER
    .asg    __CLA_CFFT_unpack512Pt_sp + 5,  SCRATCH_MAR0
    .asg    __CLA_CFFT_unpack512Pt_sp + 6,  SCRATCH_MAR1
    .asg    __CLA_CFFT_unpack512Pt_sp + 8,  SCRATCH_SIN
    .asg    __CLA_CFFT_unpack512Pt_sp + 10, SCRATCH_COS
    .asg    __CLA_CFFT_unpack512Pt_sp + 12, PTR_TWIDDLES
    .asg    __CLA_CFFT_unpack512Pt_sp + 13, PTR_OUTPUT
    ;;                                                  |Order of access
    ;;                            MAR0 starts at F[0].r | 
    .asg     2  ,  I0_NEXT      ; MAR0 -> F[0].i        | 1, 3
    .asg     -2 ,  R0_NEXT      ; MAR0 -> F[0].r        | 2
    .asg     2  ,  R0_NEXT_1    ; MAR0 -> F[1].r        | 4
    ;;                                                  |Order of access
    ;;                           MAR1 starts at F[N/2].r|
    .asg     2  ,  IN_O_2_M_K_NEXT  ; MAR1 -> F[N/2].i  | 1, 3
    .asg     -2 ,  RN_O_2_M_K_NEXT  ; MAR1 -> F[N/2].r  | 2
    .asg     -6 ,  RN_O_2_M_K_NEXT_1; MAR1 -> F[N/2-1].r| 4
    .if DEBUG_BRKPT_ENABLE
    MDEBUGSTOP
    .endif ;;DEBUG_BRKPT_ENABLE    
    MMOV32   @SCRATCH_MR3, MR3                  ; Save MR3 on entry
    ;; Note N is the number of real samples N = 1024
    MMOV32   MR0, @I_BUFFER+0                   ; MR0 = Z[0].r
    MMOV32   MR1, @I_BUFFER+2                   ; MR0 = Z[0].i
    MMOVIZ   MR3, #0                            ; MR3 = 0
    MADDF32  MR2, MR0, MR1                      ; MR0 = Z[0].r + Z[0].i
 || MMOV32   @O_BUFFER+2, MR3                   ; Save F[0].i = 0   
    MSUBF32  MR1, MR0, MR1                      ; MR1 = Z[0].r - Z[0].i
 || MMOV32   @O_BUFFER+0, MR2                   ; Save F[0].r
    MMOV32   @O_BUFFER+4*(NCSAMPLES), MR1       ; Save F[N/2].r
    MMOV32   @O_BUFFER+4*(NCSAMPLES)+2, MR3     ; Save F[N/2].i = 0
    MMOVI16  MAR0, #I_BUFFER+4                  ; MAR0 -> Z[1].r
    MMOVI16  MAR1, #I_BUFFER+((NSAMPLES/2-1)*4) ; MAR1 -> Z[N/2-1].r
    ; MR3.L = IOBuffer2+4 (F[1].r), MR3.H = 0
    MMOVXI   MR3, #O_BUFFER+4
    MMOV16   @PTR_OUTPUT, MR3
    ; MR3.L = twiddle_tbl + 2*skipfactor, MR3.H = 0 
    MMOVXI   MR3, #_cla_twiddleFactors+2*SKIPFACTOR 
    MMOV16   @PTR_TWIDDLES, MR3                 ; Save to the twiddle pointer
    MMOV32   MR0, @_cla_twiddleFactors+SKIPFACTOR
    MMOV32   @SCRATCH_SIN, MR0                  ; MR0 = SIN, save to scratchpad
    MMOV32   MR0, @_cla_twiddleFactors+SKIPFACTOR+2
    MMOV32   @SCRATCH_COS, MR0                  ; MR0 = COS, save to scratchpad
     
    ;;                                                           | Order of access 
    ;;                                 MAR0 starts at F[k].r     | 
    .asg    2 , I0_NEXT                  ; MAR0 -> F[k].i        | 1, 3
    .asg    2 , R0_NEXT_1                ; MAR0 -> F[k+1].r      | 2, 4
    ;;                                                           | Order of access 
    ;;                                 MAR1 starts at F[N/2-k].r |
    .asg    2 , IN_O_2_M_K_NEXT          ; MAR0 -> F[N/2-k].i    | 1
    .asg    -6, RN_O_2_M_K_NEXT_1        ; MAR0 -> F[N/2-k-1].r  | 2   

    
    MMOVI32  MR0, #(NSAMPLES/4-2)               ; 1| MR0 = NSAMPLES/4 - 2
    MMOV16   @LOOP_COUNTER, MR0                 ; 2|
                                                ; 3| first instruction of loop
_CLA_CFFT_unpack512Pt_loop_1Q:    
    SET_BRKPT_AT_ITER   255
;+-----------------------------------------------+---------------------------------------------------------------------------------------------------+
;| unpack for k = 1 to N/4-1                     |          MR0       |  MR1               |       MR2          |    MR3    | MAR0      | MAR1       |
;| cycles = 36                                   |                    |                    |                    |           |           |            | 
;+-----------------------------------------------+---------------------------------------------------------------------------------------------------+
                                                ;|                    |                    |                    |           |Z[k].r     |Z[N/2-k].r  | 
    MMOV32   MR1, *MAR1[IN_O_2_M_K_NEXT]++      ;|                    |Z[N/2-k].r          |                    |           |           |Z[N/2-k].i  |
    MMOV32   MR0, *MAR0[I0_NEXT]++              ;|Z[k].r              |                    |                    |           |Z[k].i     |            |
    MSUBF32  MR2, MR0, MR1                      ;|                    |                    |RS=Z[k].r-Z[N/2-k].r|           |           |            |
 || MMOV32   MR3, @SCRATCH_SIN                  ;|                    |                    |                    |SIN or S   |           |            |
    MMPYF32  MR3, MR3, MR2                      ;|                    |                    |                    |S*RS       |           |            |
 || MADDF32  MR0, MR0, MR1                      ;|RA=Z[k].r+Z[N/2-k].r|free                |                    |           |           |            |
    MSUBF32  MR0, MR0, MR3                      ;|RA-S*RS             |                    |                    |free       |           |            |
 || MMOV32   MR1, *MAR0[R0_NEXT_1]++            ;|                    |Z[k].i              |                    |           |Z[k+1].r   |            |
    MMOV16   @SCRATCH_MAR0, MAR0                ;|----Save MAR0 to scratchpad--------------|---------------------------------------------------------|
    MMOV16   MAR0, @PTR_OUTPUT                  ;|----MAR0 -> output--------------------------------------------------------|F[k].r     |------------|
    MMOV32   MR3, *MAR1[RN_O_2_M_K_NEXT_1]++    ;|                    |                    |                    |Z[N/2-k].i |           |Z[N/2-k-1].r|
    MADDF32  MR2, MR1, MR3                      ;|                    |                    |IA=Z[k].i+Z[N/2-k].i|           |           |            |
 || MMOV32   @RS_TEMP, MR2                      ;|                    |                    |IA (RS saved)       |           |           |            |
    MSUBF32  MR1, MR1, MR3                      ;|                    |IS=Z[k].i-Z[N/2-k].i|                    |free       |           |            |
 || MMOV32   MR3, @SCRATCH_COS                  ;|                    |                    |                    |COS or C   |           |            |
    MMPYF32  MR3, MR3, MR2                      ;|                    |                    |                    |C*IA       |           |            |
    MADDF32  MR0, MR0, MR3                      ;|RA-S*RS+C*IA        |                    |                    |free       |           |            |
 || MMOV32   MR3, @SCRATCH_SIN                  ;|                    |                    |                    |S          |           |            |
    MMPYF32  MR2, MR3, MR2                      ;|                    |                    |S*IA                |free       |           |            |
    MMOV32   MR3, @RS_TEMP                      ;|                    |                    |                    |RS         |           |            |
    MMPYF32  MR0, #0.5, MR0                     ;|0.5*(RA-S*RS+C*IA)  |                    |                    |           |           |            |
    MSUBF32  MR1, MR1, MR2                      ;|                    |IS-S*IA             |free                |           |           |            |
 || MMOV32   MR2, @SCRATCH_COS                  ;|                    |                    |C                   |           |           |            |
    MMPYF32  MR2, MR2, MR3                      ;|                    |                    |C *RS               |free       |           |            |
 || MMOV32   *MAR0[I0_NEXT]++, MR0              ;|free(saved)         |                    |                    |           |F[k].i     |            |
    MMOV16   @SCRATCH_MAR1, MAR1                ;|----Save MAR1 to scratchpad--------------|---------------------------------------------------------|
    MMOV16   MAR1, @PTR_TWIDDLES                ;|----MAR1 -> twiddles-------------------------------------------------------------------------------|
    MSUBF32  MR1, MR1, MR2                      ;|                    |IS-S*IA-C*RS        |free                |           |           |            | 
    MMPYF32  MR1, #0.5, MR1                     ;|                    |0.5*(IS-S*IA-C*RS)  |                    |           |           |            | 
    MMOV32   *MAR0[R0_NEXT_1]++, MR1            ;|free                |free(saved)         |free                |free       |F[k+1].r   |            |
    MMOV16   @PTR_OUTPUT, MAR0                  ;|----Save MAR0 to Output Pointer--------------------------------------------------------------------|    
    MMOV16   MAR0, @SCRATCH_MAR0                ;|----Restore MAR0----------------------------------------------------------|Z[k+1].r   |------------|
;+-----------------------------------------------+---------------------------------------------------------------------------------------------------+    
;| State of registers                            |free                |free                |free                |free       |Z[k+1].r   |Z[N/2-k-1].r|
;+-----------------------------------------------+---------------------------------------------------------------------------------------------------+
    MMOV32   MR0, *MAR1[2]++                    ; MR0 = SIN, save to scratchpad
    MMOV32   @SCRATCH_SIN, MR0                  ; 
    MMOV32   MR0, *MAR1[SKIPFACTOR-2]++         ; MR0 = COS, save to scratchpad
    MMOV32   @SCRATCH_COS, MR0                  ; 
    MMOVZ16  MR0, @LOOP_COUNTER                 ; set ZF = 1 if loop count = 0
    MMOV16   @PTR_TWIDDLES, MAR1                ;-1| Save to the twiddle pointer
    MMOV16   MAR1, @SCRATCH_MAR1                ;-2|*| Restore MAR1
    MMOVIZ   MR1, #0                            ;-3|1| 
    MBCNDD   _CLA_CFFT_unpack512Pt_loop_1Q, NEQ ; *|2| Branch if loop count != 0
    MMOVXI   MR1, #1                            ;-2|3| 
    MSUB32   MR0, MR0, MR1                      ;-1| loop counter --
    MMOV32   @LOOP_COUNTER, MR0                 ;+1|

    .if DEBUG_BRKPT_ENABLE
    MDEBUGSTOP
    .endif ;;DEBUG_BRKPT_ENABLE
   ; Reset the twiddle pointers 
   ; MR1.L = twiddle_tbl + skipfactor,  MR1.H = 0 from last loop
    MMOVXI   MR1, #_cla_twiddleFactors+SKIPFACTOR
    MMOV16   @PTR_TWIDDLES, MR1
    MMOV32   MR0, @_cla_twiddleFactors+0
    MMOV32   @SCRATCH_SIN, MR0
    MMOV32   MR0, @_cla_twiddleFactors+2
    MMOV32   @SCRATCH_COS, MR0
    
    MMOVI32  MR0, #(NSAMPLES/4-1)               ; MR0 = NSAMPLES/4-1
    MMOV16   @LOOP_COUNTER, MR0
_CLA_CFFT_unpack512Pt_loop_2Q:
;+-----------------------------------------------+---------------------------------------------------------------------------------------------------+
;| unpack for k = N/4 to N/2-1                   |          MR0       |  MR1               |       MR2          |    MR3    | MAR0      | MAR1       |
;| For the second quadrant the twiddles have the |                    |                    |                    |           |           |            | 
;| following relationship                        |                    |                    |                    |           |           |            | 
;| COS = -SIN and SIN = COS                      |                    |                    |                    |           |           |            | 
;| cycles = 36                                   |                    |                    |                    |           |           |            | 
;+-----------------------------------------------+---------------------------------------------------------------------------------------------------+
                                                ;|                    |                    |                    |           |Z[k].r     |Z[N/2-k].r  | 
    MMOV32   MR1, *MAR1[IN_O_2_M_K_NEXT]++      ;|                    |Z[N/2-k].r          |                    |           |           |Z[N/2-k].i  | 
    MMOV32   MR0, *MAR0[I0_NEXT]++              ;|Z[k].r              |                    |                    |           |Z[k].i     |            |
    MSUBF32  MR2, MR0, MR1                      ;|                    |                    |RS=Z[k].r-Z[N/2-k].r|           |           |            |
 || MMOV32   MR3, @SCRATCH_COS                  ;|                    |                    |                    |COS or C   |           |            |
    MMPYF32  MR3, MR3, MR2                      ;|                    |                    |                    |C*RS       |           |            |
 || MADDF32  MR0, MR0, MR1                      ;|RA=Z[k].r+Z[N/2-k].r|free                |                    |           |           |            |
    MSUBF32  MR0, MR0, MR3                      ;|RA-C*RS             |                    |                    |free       |           |            |
 || MMOV32   MR1, *MAR0[R0_NEXT_1]++            ;|                    |Z[k].i              |                    |           |Z[k+1].r   |            |
    MMOV16   @SCRATCH_MAR0, MAR0                ;|----Save MAR0 to scratchpad--------------|---------------------------------------------------------|
    MMOV16   MAR0, @PTR_OUTPUT                  ;|----MAR0 -> output--------------------------------------------------------|F[k].r     |------------|
    MMOV32   MR3, *MAR1[RN_O_2_M_K_NEXT_1]++    ;|                    |                    |                    |Z[N/2-k].i |           |Z[N/2-k-1].r|
    MADDF32  MR2, MR1, MR3                      ;|                    |                    |IA=Z[k].i+Z[N/2-k].i|           |           |            |
 || MMOV32   @RS_TEMP, MR2                      ;|                    |                    |IA (RS saved)       |           |           |            |
    MSUBF32  MR1, MR1, MR3                      ;|                    |IS=Z[k].i-Z[N/2-k].i|                    |free       |           |            |
 || MMOV32   MR3, @SCRATCH_SIN                  ;|                    |                    |                    |SIN or S   |           |            |
    MMPYF32  MR3, MR3, MR2                      ;|                    |                    |                    |S*IA       |           |            |
    MSUBF32  MR0, MR0, MR3                      ;|RA-C*RS-S*IA        |                    |                    |free       |           |            |
 || MMOV32   MR3, @SCRATCH_COS                  ;|                    |                    |                    |C          |           |            |
    MMPYF32  MR2, MR3, MR2                      ;|                    |                    |C*IA                |free       |           |            |
    MMOV32   MR3, @RS_TEMP                      ;|                    |                    |                    |RS         |           |            |
    MMPYF32  MR0, #0.5, MR0                     ;|0.5*(RA-C*RS-S*IA)  |                    |                    |           |           |            |
    MSUBF32  MR1, MR1, MR2                      ;|                    |IS-C*IA             |free                |           |           |            |
 || MMOV32   MR2, @SCRATCH_SIN                  ;|                    |                    |S                   |           |           |            |
    MMPYF32  MR2, MR2, MR3                      ;|                    |                    |S*RS                |free       |           |            |
 || MMOV32   *MAR0[I0_NEXT]++, MR0              ;|free(saved)         |                    |                    |           |F[k].i     |            |
    MMOV16   @SCRATCH_MAR1, MAR1                ;|----Save MAR1 to scratchpad--------------|                    |           |           |            |
    MMOV16   MAR1, @PTR_TWIDDLES                ;|----MAR1 -> twiddles---------------------|                    |           |           |            |    
    MADDF32  MR1, MR1, MR2                      ;|                    |IS-C*IA+S*RS        |free                |           |           |            | 
    MMPYF32  MR1, #0.5, MR1                     ;|                    |0.5*(IS-C*IA+S*RS)  |                    |           |           |            | 
    MMOV32   *MAR0[R0_NEXT_1]++, MR1            ;|free                |free(saved)         |free                |free       |F[k+1].r   |            |
    MMOV16   @PTR_OUTPUT, MAR0                  ;|----Save MAR0 to Output Pointer--------------------------------------------------------------------|
    MMOV16   MAR0, @SCRATCH_MAR0                ;|----Restore MAR0----------------------------------------------------------|Z[k+1].r   |------------|
;+-----------------------------------------------+---------------------------------------------------------------------------------------------------+    
;| State of registers                            |free                |free                |free                |free       |Z[k+1].r   |Z[N/2-k-1].r|
;+-----------------------------------------------+---------------------------------------------------------------------------------------------------+    
    MMOV32   MR0, *MAR1[2]++                    ; MR0 = SIN, save to scratchpad
    MMOV32   @SCRATCH_SIN, MR0                  ; 
    MMOV32   MR0, *MAR1[SKIPFACTOR-2]++         ; MR0 = COS, save to scratchpad
    MMOV32   @SCRATCH_COS, MR0                  ; 
    MMOVZ16  MR0, @LOOP_COUNTER                 ; set ZF = 1 if loop count = 0
    MMOV16   @PTR_TWIDDLES, MAR1                ;-1| Save to the twiddle pointer
    MMOV16   MAR1, @SCRATCH_MAR1                ;-2|*| Restore MAR1
    MMOVIZ   MR1, #0                            ;-3|1| 
    MBCNDD   _CLA_CFFT_unpack512Pt_loop_2Q, NEQ ; *| Branch if loop count != 0
    MMOVXI   MR1, #1                            ;-2|3| 
    MSUB32   MR0, MR0, MR1                      ;-1| loop counter --
    MMOV32   @LOOP_COUNTER, MR0                 ;+1|
    
    MRCNDD   UNC
    MMOV32   MR3, @SCRATCH_MR3                  ; Restore MR3
    MNOP
    MNOP
    .unasg   I0_NEXT      
    .unasg   R0_NEXT_1    
    .unasg   IN_O_2_M_K_NEXT  
    .unasg   RN_O_2_M_K_NEXT  
    .unasg   RN_O_2_M_K_NEXT_1
    .unasg   SCRATCH_MR3
    .unasg   RS_TEMP
    .unasg   LOOP_COUNTER
    .unasg   SCRATCH_MAR0
    .unasg   SCRATCH_MAR1
    .unasg   SCRATCH_SIN
    .unasg   SCRATCH_COS
    .unasg   PTR_TWIDDLES
    .endasmfunc

;; End of file
