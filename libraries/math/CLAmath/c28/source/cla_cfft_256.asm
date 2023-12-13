;;#############################################################################
;;
;; FILE:	cla_cfft_256.asm
;;
;; TITLE:	256-pt complex FFT for the C2000 Real-Time CLA CPU
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
    .global _CLA_CFFT_run256Pt
    .ref    _cla_twiddleFactors
    .ref    _cla_bitReversalTable
    .ref    _IOBuffer

_one                 .usect    ".bss_cla", 2, 2, 2
_loopCountBitRev     .usect    ".bss_cla", 2, 2, 2
_loopCountS1_2       .usect    ".bss_cla", 2, 2, 2
_loopCountS3_8_Q     .usect    ".bss_cla", 2, 2, 2
_loopCountS3_8       .usect    ".bss_cla", 2, 2, 2

_pTwiddlesStageN     .usect    ".bss_cla", 2, 2, 2
_pTwiddlesStageN1    .usect    ".bss_cla", 2, 2, 2
_SIN1                .usect    ".bss_cla", 2, 2, 2
_COS1                .usect    ".bss_cla", 2, 2, 2
_SIN2                .usect    ".bss_cla", 2, 2, 2
_COS2                .usect    ".bss_cla", 2, 2, 2


_R0_p                .usect    ".bss_cla", 2, 2, 2
_R1_p                .usect    ".bss_cla", 2, 2, 2
_R2_p                .usect    ".bss_cla", 2, 2, 2
_R3_p                .usect    ".bss_cla", 2, 2, 2
_I0_p                .usect    ".bss_cla", 2, 2, 2
_I1_p                .usect    ".bss_cla", 2, 2, 2
_I2_p                .usect    ".bss_cla", 2, 2, 2
_I3_p                .usect    ".bss_cla", 2, 2, 2

_temp_R2             .usect    ".bss_cla", 2, 2, 2
_temp_R3             .usect    ".bss_cla", 2, 2, 2
_temp_MAR0           .usect    ".bss_cla", 2, 2, 2
_temp_MAR1           .usect    ".bss_cla", 2, 2, 2
;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; FFT Routine defines
NSTAGES             .set    8               ; 256
NSAMPLES            .set    (1 << NSTAGES)
TWIDDLE_TBL_SIZE    .set    1024
NTWIDDLES           .set    (TWIDDLE_TBL_SIZE/8)
STAGE1              .set    1
STAGE3              .set    3
STAGE4              .set    4
STAGE5              .set    5
STAGE6              .set    6
STAGE7              .set    7
STAGE8              .set    8
STAGE9              .set    9

IOBUFFER            .set    _IOBuffer         ; If the user changes the name of the buffer in
                                              ; the header files it must be changed here and the
                                              ; code rebuilt
                                              
DEBUG_DISABLE_NONE  .set    0x00
DISABLE_STAGE1_2_M  .set    0x01  ; Disable all stages
DISABLE_STAGE3_4_M  .set    0x02  ; Disable all stages 3 and above
DISABLE_STAGE5_6_M  .set    0x04  ; Disable all stages 5 and above
DISABLE_STAGE7_8_M  .set    0x08  ; Disable all stages 7 and above
DISABLE_STAGE9_M    .set    0x10  ; Disable all stages 9 and above

DEBUG_STAGE_DISABLE .set    DISABLE_STAGE9_M
DEBUG_BRKPT_ENABLE  .set    0x0
;;*****************************************************************************
;; macros
;;*****************************************************************************

;;
;;=============================================================================
;;
;; Stage N butterfly with stage N twiddle factors in the 1st 
;; quadrant
;;
;; Notes:
;; - The twiddle factors have the following relationship with each other
;;   +---------------------------------+-------------------------------------+
;;   | Stage N | A |  cos(1) - j sin(1)| W(N,0)..W(N,N/4 -1)                 |
;;   |         | B | -cos(1) + j sin(1)| W(N,N/2)..W(N,N/2 + N/4 -1)         |
;;   +---------------------------------+-------------------------------------+
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;;             Stage N               
;; --[R0:I0]---o----*---[R0':I0']-------->
;;              \ (A)                
;;               \/                  
;;               /\                  
;;              /  \                 
;; --[R1:I1]---o-(B)*---[R1':I1']-------->
;;                                   
;; Cycles = 18
;;=============================================================================
BUTTERFLY_STAGE_N_1ST_QUADRANT  .macro SIN1, COS1
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
;| STAGE N Computations                            |          MR0            |  MR1 |       MR2         |            MR3          | MAR0 | MAR1 |
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
    MMOV32    MR2, *MAR0[SN_INSEP]++             ; |                         |      |R0 (dummy read)    |                         |R1,R1*|R0'   |
    MMOV32    MR2, *MAR0[I1_NEXT]++              ; |                         |      |R1                 |                         |I1    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMOV32    MR1, @:COS1:                       ; |                         |cos(1)|                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R1cos(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[R0_NEXT]++              ; |                         |      |                   |I1                       |R0    |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I1sin(1)                 |      |      |
    MADDF32   MR2, MR2, MR3                      ; |                         |      |R1cos(1)+I1sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R1_NEXT]++              ; |                         |      |                   |R0                       |R1    |      |
    MADDF32   MR0, MR3, MR2                      ; |R0+(R1cos(1)+I1sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |R0-(R1cos(1)+I1sin(1))   |      |      |
 || MMOV32    *MAR1[R1p_NEXT]++, MR0             ; |                         |      |                   |                         |      |R1'   |
    MMOV32    *MAR1[I0p_NEXT]++, MR3             ; |                         |      |                   |                         |      |I0'   |
    MMOV32    MR2, *MAR0[I1_NEXT]++              ; |                         |      |R1                 |                         |I1    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R1sin(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[I0_NEXT]++              ; |                         |      |                   |I1                       |I0    |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I1cos(1)                 |      |      |
    MSUBF32   MR2, MR3, MR2                      ; |                         |      |I1cos(1)-R1sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R0_NEXT_1]++            ; |                         |      |                   |I0                       |R0*   |      |
    MADDF32   MR0, MR3, MR2                      ; |I0+(I1cos(1)-R1sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |I0-(I1cos(1)-R1sin(1))   |      |      |
 || MMOV32    *MAR1[I1p_NEXT]++, MR0             ; |                         |      |                   |                         |      |I1'   |
    MMOV32    *MAR1[R0p_NEXT_1]++, MR3           ; |                         |      |                   |                         |      |R0'*  |
                                                 ; +--------------------------------------------------------------------------------------------+
    .endm


;;=============================================================================
;;
;; Stage N butterfly with stage N twiddle factors in the 2nd 
;; quadrant
;;
;; Notes:
;; - The twiddle factors have the following relationship with each other
;;   +---------------------------------+-------------------------------------+
;;   | Stage N | A | -sin(1) - j cos(1)| W(N,N/4)..W(N,N/2-1)                |
;;   |         | B |  sin(1) + j cos(1)| W(N,3N/4)..W(N,N-1)                 |
;;   +---------------------------------+-------------------------------------+
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;;             Stage N              
;; --[R0:I0]---o----*---[R0':I0']------->
;;              \ (A)               
;;               \/                 
;;               /\                 
;;              /  \                
;; --[R1:I1]---o-(B)*---[R1':I1']------->
;;                                  
;; Cycles = 18
;;=============================================================================

BUTTERFLY_STAGE_N_2ND_QUADRANT  .macro SIN1, COS1
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
;| STAGE N Computations                            |          MR0            |  MR1 |       MR2         |            MR3          | MAR0 | MAR1 |
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
    MMOV32    MR2, *MAR0[SN_INSEP]++             ; |                         |      |R0 (dummy read)    |                         |R1,R1*|R0'   |
    MMOV32    MR2, *MAR0[I1_NEXT]++              ; |                         |      |R1                 |                         |I1    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMOV32    MR1, @:COS1:                       ; |                         |cos(1)|                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R1sin(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[R0_NEXT]++              ; |                         |      |                   |I1                       |R0    |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I1cos(1)                 |      |      |
    MSUBF32   MR2, MR3, MR2                      ; |                         |      |I1cos(1)-R1sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R1_NEXT]++              ; |                         |      |                   |R0                       |R1    |      |
    MADDF32   MR0, MR3, MR2                      ; |R0+(I1cos(1)-R1sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |R0-(I1cos(1)-R1sin(1))   |      |      |
 || MMOV32    *MAR1[R1p_NEXT]++, MR0             ; |                         |      |                   |                         |      |R1'   |
    MMOV32    *MAR1[I0p_NEXT]++, MR3             ; |                         |      |                   |                         |      |I0'   |
    MMOV32    MR2, *MAR0[I1_NEXT]++              ; |                         |      |R1                 |                         |I1    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R1cos(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[I0_NEXT]++              ; |                         |      |                   |I1                       |I0    |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I1sin(1)                 |      |      |
    MADDF32   MR2, MR3, MR2                      ; |                         |      |I1sin(1)+R1cos(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R0_NEXT_1]++            ; |                         |      |                   |I0                       |R0*   |      |
    MSUBF32   MR0, MR3, MR2                      ; |I0-(I1sin(1)+R1cos(1))   |      |                   |                         |      |      |
    MADDF32   MR3, MR3, MR2                      ; |                         |      |                   |I0+(I1sin(1)+R1cos(1))   |      |      |
 || MMOV32    *MAR1[I1p_NEXT]++, MR0             ; |                         |      |                   |                         |      |I1'   |
    MMOV32    *MAR1[R0p_NEXT_1]++, MR3           ; |                         |      |                   |                         |      |R0'*  |
                                                 ; +--------------------------------------------------------------------------------------------+
    .endm
;;
;;=============================================================================
;;
;; Stages N and N+1 Combined butterfly with stage N twiddle factors in the 1st 
;; quadrant
;;
;; Notes:
;; - The twiddle factors have the following relationship with each other
;;   +---------------------------------+-------------------------------------+
;;   | Stage N | A |  cos(1) - j sin(1)| W(N,0)..W(N,N/4 -1)                 |
;;   |         | B | -cos(1) + j sin(1)| W(N,N/2)..W(N,N/2 + N/4 -1)         |
;;   | Stage N1| C |  cos(2) - j sin(2)| W(N1,0)..W(N1,N1/4-1)               |
;;   |         | D | -sin(2) - j cos(2)| W(N1,N1/4)..W(N1,N1/2-1)            |
;;   |         | E | -cos(2) + j sin(2)| W(N1,N1/2)..W(N1/N1/2+N1/4-1)       |
;;   |         | F |  sin(2) + j cos(2)| W(N1,3N1/4)..W(N1,N1-1)             |
;;   +---------------------------------+-------------------------------------+
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;;             Stage N               Stage N+1
;; --[R0:I0]---o----*---[R0':I0']----o--------*--[R0'':I0'']----->
;;              \ (A)                 \      /       
;;               \/                    \   (C)        
;;               /\                     \  /         
;;              /  \                     \/          
;; --[R1:I1]---o-(B)*---[R1':I1']----o---/\---*--[R1'':I1'']----->
;;                                    \ /  \(D)          
;;                                     \    \        
;;                                    / \  / \      
;; --[R2:I2]---o----*---[R2':I2']----o---\(E)-*--[R2'':I2'']----->
;;              \ (A)                    /\              
;;               \/                     /  \         
;;               /\                    /    \        
;;              /  \                  /      \      
;; --[R3:I3]---o-(B)*---[R2':I2']----o----(F)-*--[R3'':I3'']----->
;;
;; Cycles = 67
;;=============================================================================

BUTTERFLY_STAGE_N_N1_1ST_QUADRANT  .macro SIN1, COS1, SIN2, COS2
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
;| STAGE N Computations                            |          MR0            |  MR1 |       MR2         |            MR3          | MAR0 | MAR1 |
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
    MMOV32    MR2, *MAR0[SNN1_INSEP]++           ; |                         |      |R0 (dummy read)    |                         |R1,R1*|      |
    MMOV32    MR2, *MAR0[I1_NEXT]++              ; |                         |      |R1                 |                         |I1    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMOV32    MR1, @:COS1:                       ; |                         |cos(1)|                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R1cos(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[R0_NEXT]++              ; |                         |      |                   |I1                       |R0    |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I1sin(1)                 |      |      |
    MADDF32   MR2, MR2, MR3                      ; |                         |      |R1cos(1)+I1sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R1_NEXT]++              ; |                         |      |                   |R0                       |R1    |      |
    MADDF32   MR0, MR3, MR2                      ; |R0+(R1cos(1)+I1sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |R0-(R1cos(1)+I1sin(1))   |      |      |
 || MMOV32    @_R0_p, MR0                        ; |                         |      |                   |                         |      |      |
    MMOV32    @_R1_p, MR3                        ; |                         |      |                   |                         |      |      |
    MMOV32    MR2, *MAR0[I1_NEXT]++              ; |                         |      |R1                 |                         |I1    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R1sin(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[I0_NEXT]++              ; |                         |      |                   |I1                       |I0    |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I1cos(1)                 |      |      |
    MSUBF32   MR2, MR3, MR2                      ; |                         |      |I1cos(1)-R1sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R3_NEXT]++              ; |                         |      |                   |I0                       |R3    |      |
    MADDF32   MR0, MR3, MR2                      ; |I0+(I1cos(1)-R1sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |I0-(I1cos(1)-R1sin(1))   |      |      |
 || MMOV32    @_I0_p, MR0                        ; |                         |      |                   |                         |      |      |
    MMOV32    @_I1_p, MR3                        ; |                         |      |                   |                         |      |      |
    MMOV32    MR2, *MAR0[I3_NEXT]++              ; |                         |      |R3                 |                         |I3    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R3cos(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[R2_NEXT]++              ; |                         |      |                   |I3                       |R2    |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I3sin(1)                 |      |      |
    MADDF32   MR2, MR2, MR3                      ; |                         |      |R3cos(1)+I3sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R3_NEXT_1]++            ; |                         |      |                   |R2                       |R3    |      |
    MADDF32   MR0, MR3, MR2                      ; |R2+(R3cos(1)+I3sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |R2-(R3cos(1)+I3sin(1))   |      |      |
 || MMOV32    @_R2_p, MR0                        ; |                         |      |                   |                         |      |      |
    MMOV32    @_R3_p, MR3                        ; |                         |      |                   |                         |      |      |
    MMOV32    MR2, *MAR0[I3_NEXT]++              ; |                         |      |R3                 |                         |I3    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R3sin(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[I2_NEXT]++              ; |                         |      |                   |I3                       |I2    |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I3cos(1)                 |      |      |
    MSUBF32   MR2, MR3, MR2                      ; |                         |      |I3cos(1)-R3sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R0_NEXT_1]++            ; |                         |      |                   |I2                       |R0*   |      |
    MADDF32   MR0, MR3, MR2                      ; |I2+(I3cos(1)-R3sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |I2-(I3cos(1)-R3sin(1))   |      |      |
 || MMOV32    @_I2_p, MR0                        ; |                         |      |                   |                         |      |      |
    MMOV32    @_I3_p, MR3                        ; |                         |      |                   |                         |      |      |
                                                 ; |                         |      |                   |                         |      |      |
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
;| STAGE N+1 Computations                          |          MR0            |  MR1 |       MR2         |            MR3          | MAR0 | MAR1 |
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
    MMOV32    MR2, @_R2_p                        ; |                         |      |R2'                |                         |      |R0''  |
    MMOV32    MR0, @:SIN2:                       ; |sin(2)                   |      |                   |                         |      |      |
    MMOV32    MR1, @:COS2:                       ; |                         |cos(2)|                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R2'cos(2)          |                         |      |      |
 || MMOV32    MR3, @_I2_p                        ; |                         |      |                   |I2'                      |      |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I2'sin(2)                |      |      |
    MADDF32   MR2, MR2, MR3                      ; |                         |      |R2'cos(2)+I2'sin(2)|                         |      |      |
 || MMOV32    MR3, @_R0_p                        ; |                         |      |                   |R0'                      |      |      |
    MADDF32   MR0, MR3, MR2                      ; |R0'+(R2'cos(2)+I2'sin(2))|      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |R0'-(R2'cos(2)+I2'sin(2))|      |      |
 || MMOV32    *MAR1[R2pp_NEXT]++, MR0            ; |                         |      |                   |                         |      |R2''  |
    MMOV32    *MAR1[R1pp_NEXT]++, MR3            ; |                         |      |                   |                         |      |R1''  |
    MMOV32    MR2, @_R3_p                        ; |                         |      |R3'                |                         |      |      |
    MMOV32    MR0, @:SIN2:                       ; |sin(2)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R3'sin(2)          |                         |      |      |
 || MMOV32    MR3, @_I3_p                        ; |                         |      |                   |I3'                      |      |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I3'cos(2)                |      |      |
    MSUBF32   MR2, MR2, MR3                      ; |                         |      |R3'sin(2)-I3'cos(2)|                         |      |      |
 || MMOV32    MR3, @_R1_p                        ; |                         |      |                   |R1'                      |      |      |
    MSUBF32   MR0, MR3, MR2                      ; |R1'-(R3'sin(2)-I3'cos(2))|      |                   |                         |      |      |
    MADDF32   MR3, MR3, MR2                      ; |                         |      |                   |R1'+(R3'sin(2)-I3'cos(2))|      |      |
 || MMOV32    *MAR1[R3pp_NEXT]++, MR0            ; |                         |      |                   |                         |      |R3''  |
    MMOV32    *MAR1[I0pp_NEXT]++, MR3            ; |                         |      |                   |                         |      |I0''  |
    MMOV32    MR2, @_R2_p                        ; |                         |      |R2'                |                         |      |      |
    MMOV32    MR0, @:SIN2:                       ; |sin(2)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R2'sin(2)          |                         |      |      |
 || MMOV32    MR3, @_I2_p                        ; |                         |      |                   |I2'                      |      |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I2'cos(2)                |      |      |
    MSUBF32   MR2, MR3, MR2                      ; |                         |      |I2'cos(2)-R2'sin(2)|                         |      |      |
 || MMOV32    MR3, @_I0_p                        ; |                         |      |                   |I0'                      |      |      |
    MADDF32   MR0, MR3, MR2                      ; |I0'+(I2'cos(2)-R2'sin(2))|      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |I0'-(I2'cos(2)-R2'sin(2))|      |      |
 || MMOV32    *MAR1[I2pp_NEXT]++, MR0            ; |                         |      |                   |                         |      |I2''  |
    MMOV32    *MAR1[I1pp_NEXT]++, MR3            ; |                         |      |                   |                         |      |I1''  |
    MMOV32    MR2, @_R3_p                        ; |                         |      |R3'                |                         |      |      |
    MMOV32    MR0, @:SIN2:                       ; |sin(2)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R3'cos(2)          |                         |      |      |
 || MMOV32    MR3, @_I3_p                        ; |                         |      |                   |I3'                      |      |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I3'sin(2)                |      |      |
    MADDF32   MR2, MR2, MR3                      ; |                         |      |I3'sin(2)+R3'cos(2)|                         |      |      |
 || MMOV32    MR3, @_I1_p                        ; |                         |      |                   |I1'                      |      |      |
    MSUBF32   MR0, MR3, MR2                      ; |I1'-(I3'sin(2)+R3'cos(2))|      |                   |                         |      |      |
    MADDF32   MR3, MR3, MR2                      ; |                         |      |                   |I1'+(I3'sin(2)+R3'cos(2))|      |      |
 || MMOV32    *MAR1[I3pp_NEXT]++, MR0            ; |                         |      |                   |                         |      |I3''  |
    MMOV32    *MAR1[R0pp_NEXT_1]++, MR3          ; |                         |      |                   |                         |      |R0''* |
                                                 ; |                         |      |                   |                         |      |      |
                                                 ; +--------------------------------------------------------------------------------------------+
    .endm

;;=============================================================================
;;
;; Stages N and N+1 Combined butterfly with stage N twiddle factors in the 2nd 
;; quadrant
;;
;; Notes:
;; - The twiddle factors have the following relationship with each other
;;   +---------------------------------+-------------------------------------+
;;   | Stage N | A | -sin(1) - j cos(1)| W(N,N/4)..W(N,N/2-1)                |
;;   |         | B |  sin(1) + j cos(1)| W(N,3N/4)..W(N,N-1)                 |
;;   | Stage N1| C |  cos(2) - j sin(2)| W(N1,0)..W(N1,N1/4-1)               |
;;   |         | D | -sin(2) - j cos(2)| W(N1,N1/4)..W(N1,N1/2-1)            |
;;   |         | E | -cos(2) + j sin(2)| W(N1,N1/2)..W(N1/N1/2+N1/4-1)       |
;;   |         | F |  sin(2) + j cos(2)| W(N1,3N1/4)..W(N1,N1-1)             |
;;   +---------------------------------+-------------------------------------+
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;;             Stage N               Stage N+1
;; --[R0:I0]---o----*---[R0':I0']----o--------*--[R0'':I0'']----->
;;              \ (A)                 \      /       
;;               \/                    \   (C)        
;;               /\                     \  /         
;;              /  \                     \/          
;; --[R1:I1]---o-(B)*---[R1':I1']----o---/\---*--[R1'':I1'']----->
;;                                    \ /  \(D)          
;;                                     \    \        
;;                                    / \  / \      
;; --[R2:I2]---o----*---[R2':I2']----o---\(E)-*--[R2'':I2'']----->
;;              \ (A)                    /\              
;;               \/                     /  \         
;;               /\                    /    \        
;;              /  \                  /      \      
;; --[R3:I3]---o-(B)*---[R2':I2']----o----(F)-*--[R3'':I3'']----->
;;
;; Cycles = 67
;;=============================================================================

BUTTERFLY_STAGE_N_N1_2ND_QUADRANT  .macro SIN1, COS1, SIN2, COS2
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
;| STAGE N Computations                            |          MR0            |  MR1 |       MR2         |            MR3          | MAR0 | MAR1 |
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
    MMOV32    MR2, *MAR0[SNN1_INSEP]++           ; |                         |      |R0 (dummy read)    |                         |R1,R1*|      |
    MMOV32    MR2, *MAR0[I1_NEXT]++              ; |                         |      |R1                 |                         |I1    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMOV32    MR1, @:COS1:                       ; |                         |cos(1)|                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R1sin(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[R0_NEXT]++              ; |                         |      |                   |I1                       |R0    |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I1cos(1)                 |      |      |
    MSUBF32   MR2, MR3, MR2                      ; |                         |      |I1cos(1)-R1sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R1_NEXT]++              ; |                         |      |                   |R0                       |R1    |      |
    MADDF32   MR0, MR3, MR2                      ; |R0+(I1cos(1)-R1sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |R0-(I1cos(1)-R1sin(1))   |      |      |
 || MMOV32    @_R0_p, MR0                        ; |                         |      |                   |                         |      |      |
    MMOV32    @_R1_p, MR3                        ; |                         |      |                   |                         |      |      |
    MMOV32    MR2, *MAR0[I1_NEXT]++              ; |                         |      |R1                 |                         |I1    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R1cos(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[I0_NEXT]++              ; |                         |      |                   |I1                       |I0    |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I1sin(1)                 |      |      |
    MADDF32   MR2, MR3, MR2                      ; |                         |      |I1sin(1)+R1cos(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R3_NEXT]++              ; |                         |      |                   |I0                       |R3    |      |
    MSUBF32   MR0, MR3, MR2                      ; |I0-(I1sin(1)+R1cos(1))   |      |                   |                         |      |      |
    MADDF32   MR3, MR3, MR2                      ; |                         |      |                   |I0+(I1sin(1)+R1cos(1))   |      |      |
 || MMOV32    @_I0_p, MR0                        ; |                         |      |                   |                         |      |      |
    MMOV32    @_I1_p, MR3                        ; |                         |      |                   |                         |      |      |
    MMOV32    MR2, *MAR0[I3_NEXT]++              ; |                         |      |R3                 |                         |I3    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R3sin(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[R2_NEXT]++              ; |                         |      |                   |I3                       |R2    |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I3cos(1)                 |      |      |
    MSUBF32   MR2, MR3, MR2                      ; |                         |      |I3cos(1)-R3sin(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R3_NEXT_1]++            ; |                         |      |                   |R2                       |R3    |      |
    MADDF32   MR0, MR3, MR2                      ; |R2+(I3cos(1)-R3sin(1))   |      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |R2-(I3cos(1)-R3sin(1))   |      |      |
 || MMOV32    @_R2_p, MR0                        ; |                         |      |                   |                         |      |      |
    MMOV32    @_R3_p, MR3                        ; |                         |      |                   |                         |      |      |
    MMOV32    MR2, *MAR0[I3_NEXT]++              ; |                         |      |R3                 |                         |I3    |      |
    MMOV32    MR0, @:SIN1:                       ; |sin(1)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R3cos(1)           |                         |      |      |
 || MMOV32    MR3, *MAR0[I2_NEXT]++              ; |                         |      |                   |I3                       |I2    |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I3sin(1)                 |      |      |
    MADDF32   MR2, MR3, MR2                      ; |                         |      |I3sin(1)+R3cos(1)  |                         |      |      |
 || MMOV32    MR3, *MAR0[R0_NEXT_1]++            ; |                         |      |                   |I2                       |R0*   |      |
    MSUBF32   MR0, MR3, MR2                      ; |I2-(I3sin(1)+R3cos(1))   |      |                   |                         |      |      |
    MADDF32   MR3, MR3, MR2                      ; |                         |      |                   |I2+(I3sin(1)+R3cos(1))   |      |      |
 || MMOV32    @_I2_p, MR0                        ; |                         |      |                   |                         |      |      |
    MMOV32    @_I3_p, MR3                        ; |                         |      |                   |                         |      |      |
                                                 ; |                         |      |                   |                         |      |      |
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
;| STAGE N+1 Computations                          |          MR0            |  MR1 |       MR2         |            MR3          | MAR0 | MAR1 |
;+-------------------------------------------------+--------------------------------------------------------------------------------------------+
    MMOV32    MR2, @_R2_p                        ; |                         |      |R2'                |                         |      |R0''  |
    MMOV32    MR0, @:SIN2:                       ; |sin(2)                   |      |                   |                         |      |      |
    MMOV32    MR1, @:COS2:                       ; |                         |cos(2)|                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R2'cos(2)          |                         |      |      |
 || MMOV32    MR3, @_I2_p                        ; |                         |      |                   |I2'                      |      |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I2'sin(2)                |      |      |
    MADDF32   MR2, MR2, MR3                      ; |                         |      |R2'cos(2)+I2'sin(2)|                         |      |      |
 || MMOV32    MR3, @_R0_p                        ; |                         |      |                   |R0'                      |      |      |
    MADDF32   MR0, MR3, MR2                      ; |R0'+(R2'cos(2)+I2'sin(2))|      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |R0'-(R2'cos(2)+I2'sin(2))|      |      |
 || MMOV32    *MAR1[R2pp_NEXT]++, MR0            ; |                         |      |                   |                         |      |R2''  |
    MMOV32    *MAR1[R1pp_NEXT]++, MR3            ; |                         |      |                   |                         |      |R1''  |
    MMOV32    MR2, @_R3_p                        ; |                         |      |R3'                |                         |      |      |
    MMOV32    MR0, @:SIN2:                       ; |sin(2)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R3'sin(2)          |                         |      |      |
 || MMOV32    MR3, @_I3_p                        ; |                         |      |                   |I3'                      |      |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I3'cos(2)                |      |      |
    MSUBF32   MR2, MR2, MR3                      ; |                         |      |R3'sin(2)-I3'cos(2)|                         |      |      |
 || MMOV32    MR3, @_R1_p                        ; |                         |      |                   |R1'                      |      |      |
    MSUBF32   MR0, MR3, MR2                      ; |R1'-(R3'sin(2)-I3'cos(2))|      |                   |                         |      |      |
    MADDF32   MR3, MR3, MR2                      ; |                         |      |                   |R1'+(R3'sin(2)-I3'cos(2))|      |      |
 || MMOV32    *MAR1[R3pp_NEXT]++, MR0            ; |                         |      |                   |                         |      |R3''  |
    MMOV32    *MAR1[I0pp_NEXT]++, MR3            ; |                         |      |                   |                         |      |I0''  |
    MMOV32    MR2, @_R2_p                        ; |                         |      |R2'                |                         |      |      |
    MMOV32    MR0, @:SIN2:                       ; |sin(2)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR0                      ; |                         |      |R2'sin(2)          |                         |      |      |
 || MMOV32    MR3, @_I2_p                        ; |                         |      |                   |I2'                      |      |      |
    MMPYF32   MR3, MR3, MR1                      ; |                         |      |                   |I2'cos(2)                |      |      |
    MSUBF32   MR2, MR3, MR2                      ; |                         |      |I2'cos(2)-R2'sin(2)|                         |      |      |
 || MMOV32    MR3, @_I0_p                        ; |                         |      |                   |I0'                      |      |      |
    MADDF32   MR0, MR3, MR2                      ; |I0'+(I2'cos(2)-R2'sin(2))|      |                   |                         |      |      |
    MSUBF32   MR3, MR3, MR2                      ; |                         |      |                   |I0'-(I2'cos(2)-R2'sin(2))|      |      |
 || MMOV32    *MAR1[I2pp_NEXT]++, MR0            ; |                         |      |                   |                         |      |I2''  |
    MMOV32    *MAR1[I1pp_NEXT]++, MR3            ; |                         |      |                   |                         |      |I1''  |
    MMOV32    MR2, @_R3_p                        ; |                         |      |R3'                |                         |      |      |
    MMOV32    MR0, @:SIN2:                       ; |sin(2)                   |      |                   |                         |      |      |
    MMPYF32   MR2, MR2, MR1                      ; |                         |      |R3'cos(2)          |                         |      |      |
 || MMOV32    MR3, @_I3_p                        ; |                         |      |                   |I3'                      |      |      |
    MMPYF32   MR3, MR3, MR0                      ; |                         |      |                   |I3'sin(2)                |      |      |
    MADDF32   MR2, MR2, MR3                      ; |                         |      |I3'sin(2)+R3'cos(2)|                         |      |      |
 || MMOV32    MR3, @_I1_p                        ; |                         |      |                   |I1'                      |      |      |
    MSUBF32   MR0, MR3, MR2                      ; |I1'-(I3'sin(2)+R3'cos(2))|      |                   |                         |      |      |
    MADDF32   MR3, MR3, MR2                      ; |                         |      |                   |I1'+(I3'sin(2)+R3'cos(2))|      |      |
 || MMOV32    *MAR1[I3pp_NEXT]++, MR0            ; |                         |      |                   |                         |      |I3''  |
    MMOV32    *MAR1[R0pp_NEXT_1]++, MR3          ; |                         |      |                   |                         |      |R0''* |
                                                 ; |                         |      |                   |                         |      |      |
                                                 ; +--------------------------------------------------------------------------------------------+
    .endm

    
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .sect     "Cla1Prog:_CLA_CFFT_run256Pt"
    .align    2
__CLA_CFFT_run256Pt_sp .usect ".scratchpad:Cla1Prog:_CLA_CFFT_run256Pt",2,0,1

;;
;; \brief Calculate the 256 pt Complex FFT
;;
;;
;;! \note
;;! -# This is an in-place algorithm
;;! -# The input/output buffer must be aligned to a 12-bit address, usually the
;;!   starting address of one of the CLA data RAMs
;;! -# The complex data has real-first ordering i.e. the real part occupies
;;!    the lower double word
;;! -# This function is not re-entrant as it uses global variable to store temporary
;;!   values. It also expects the FFT buffer to be global (to both the C28 and CLA)
;;!   and to be named "IOBuffer". If the user desires to change the name, the macro
;;!   IOBUFFER must be altered in the source assembly to reflect the new name and the
;;!   code rebuilt
;;
;; \return FFT of the input in the I/O buffer
;;

MAX_SUPPORTED_STAGES .set    10
BITREVTBL_RSHIFT     .set    (MAX_SUPPORTED_STAGES - NSTAGES)
_CLA_CFFT_run256Pt:
    .asmfunc                                     ; Cycles = 14 (start of code)
    MMOV32   @__CLA_CFFT_run256Pt_sp + 0, MR3    ; Save MR3 on entry
    MMOVI32  MR0, #NSAMPLES - 1                  ; MR0 = NSAMPLES - 1
    ; MAR1 -> _cla_bitReversalTable + 1023
    MMOV16   MAR1, MR0, #_cla_bitReversalTable   
    MMOV32   @_loopCountBitRev, MR0              ; _loopCountBitRev = 1023
    MMOVI32  MR1, #0                             ; MR1 = 0
    MLSL32   MR0, #2                             ; MR0 = (NSAMPLES - 1) * 4
    ; MAR0 -> IOBUFFER + (NSAMPLES - 1)*2(complex)*2(float)
    MMOV16   MAR0, MR0, #IOBUFFER                
    ; MAR1 = @(_cla_bitReversalTable + (NSAMPLES - 1)) >> 1
    MMOVZ16  MR0, *MAR1[0]++                    
    MLSR32   MR0, #BITREVTBL_RSHIFT
    MMOV16   MAR1, MR0, #0
    MMOV32   MR0, MR1                            ; MR0 = 0
    MMOVI32  MR2, #1                             ; MR1 = 1
    MMOV32   @_one, MR2                          ; one = 1
    MSETFLG  TF=0                                ; Set TF to 0 initially

;;=============================================================================
;; #cycles   = 23 * #swaps + 16 * #no_swaps
;; The bit reversal table has 1024 10-bit addresses
;; there are 2^5=32 combinations that when reversed look the same; and of the
;; remaining 512 - 32 = 224 entries we swap exactly half 
;; #no_swaps = 32 + 240 = 272
;; #swaps    = (512 - #no_swaps)/2
;;           =  120
;; Cycles    = 23 * 120 + 16 * 392
;;           = 9032
;;=============================================================================
_CLA_CFFT_run256Pt_bitReversal:
    MSUB32   MR0, MR0, MR1                       ; MR0 = MAR0 - MAR1 (the difference is 0 for first iteration)
    MMOV32   MR3, @_loopCountBitRev              ; -3 | MR3 = _loopCountBitRev
    MMOVZ16  MR1, @_one                          ; -2 | MR1 = 1
    MSUB32   MR3, MR3, MR1                       ; -1 |Sets the flags for bitRev loop branch decision
    ; branch to no swap if MAR0 >= MAR1
    MBCNDD   _CLA_CFFT_run256Pt_bitReversal_noswap, GEQ
    MMOV32   @_loopCountBitRev, MR3              ; +1 | _loopCountBitRev--
    MTESTTF  EQ                                  ; +2 | if (_loopCountBitRev==0) TF = 1 else TF = 0
    MMOV32   MR0, *MAR0[2]++                     ; +3 | MR0 = Real part of upper complex point

    MMOV32   MR1, *MAR0[0]++                     ; MR1 = Imaginary part of upper complex point
    MMOV32   MR2, *MAR1[2]++                     ; MR2 = Real part of lower complex point
    MMOV32   MR3, *MAR1[0]++                     ; MR3 = Imaginary part of lower complex point
_CLA_CFFT_run256Pt_bitReversal_swap:
    MMOV32   *MAR0[-2]++, MR3                    ;
    MMOV32   *MAR0[2]++, MR2                     ; MAR0 -> points to the imag part, noswap dummy read will set
    MMOV32   *MAR1[-2]++, MR1                    ;         MAR0 to point to the next complex input
    MMOV32   *MAR1[0]++, MR0                     ; 
_CLA_CFFT_run256Pt_bitReversal_noswap:
    MMOV32   MR0, @_loopCountBitRev              ; MR0 = _loopCountBitRev
    MMOV16   MAR1, MR0, #_cla_bitReversalTable   ; -3 | MAR1 -> _cla_bitReversalTable + _loopCountBitRev
    MLSL32   MR0, #2                             ; -2 | MR0 = _loopCountBitRev << (2) (next buffer location offset from base)
    ; branch if _loopCountBitRev > 0
    MMOV32   MR2, *MAR0[-6]++                    ; -1 |Do a dummy read to have MAR0 to point to the next complex point
    MBCNDD   _CLA_CFFT_run256Pt_bitReversal, NTF
    MMOVZ16  MR1, *MAR1[0]++                     ; +1 | MR0 = MAR1 (next bitRevTbl entry)
    MLSR32   MR1, #BITREVTBL_RSHIFT              ; +2 | (_cla_bitReversalTable + _loopCountBitRev) >> 1
    MMOV16   MAR1, MR1, #IOBUFFER                ; +3 | MAR1 = @(_cla_bitReversalTable + _loopCountBitRev)/2 + IOBUFFER

    .if (DEBUG_STAGE_DISABLE != DISABLE_STAGE1_2_M )
;;=============================================================================
;;
;; Stages 1 and 2 Combined
;;
;; Notes:
;; - These stages use trivial twiddle factors: 1,-1,j and -j.
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;;             Stage 1            Stage 2    (R0':I0')
;; --[R0:I0]---o----*---[R0+R1--o--------*--[R0+R1+R2+R3----->
;;              \ (1)   :I0+I1]  \      /   :I0+I1+I2+I3]    
;;               \/               \   (1)        
;;               /\                \  /         
;;              /  \                \/       (R1':I1')   
;; --[R1:I1]---o(-1)*---[R0-R1--o---/\---*--[R0-R1+I2-I3----->
;;                      :I0-I1]  \ /  \(-j) :I0-I1-R2+R3]         
;;                                \    \        
;;                               / \  / \    (R2':I2')   
;; --[R2:I2]---o----*---[R2+R3--o---\(-1)*--[R0+R1-R2-R3----->
;;              \ (1)   :I2+I3]     /\      :I0+I1-I2-I3]        
;;               \/                /  \         
;;               /\               /    \        
;;              /  \             /      \    (R3':I3')   
;; --[R3:I3]---o(-1)*---[R2-R3--o----(+j)*--[R0-R1-I2+I3----->
;;                      :I2-I3]             :I0-I1+R2-R3]    
;;
;; #cycles = 4 + ((25 * nLoopUnroll) + 10) * nLoopBranch
;;         = 4 + ((25 * 16) + 10) *  16
;;         = 6564 
;;=============================================================================
_CLA_CFFT_run256Pt_stages1and2Combined:

;; Local Defines
S1_2_LOOPUNROLL     .set    16                ; Combined stages 1 and 2 are unrolled these many times
NBFLY_S1_2          .set    2 * S1_2_LOOPUNROLL
                                              ; stages 1,2 are unrolled S1_2_LOOPUNROLL times, but perform
                                              ; 2 butterflies each time
LOOP_COUNT_S1_2     .set    (NSAMPLES/(2 * NBFLY_S1_2))
                                              ; stages 1,2 are combined to do 32 butterflies in an
                                              ; unrolled loop, we need to do NSAMPLES/64 iterations to get an
                                              ; NSAMPLE-pt FFT
                                              ; NSAMPLE-pt FFT
                                              
    .if DEBUG_BRKPT_ENABLE
    MDEBUGSTOP
    .endif ;;DEBUG_BRKPT_ENABLE
    ;;-------------------------------------------------------------------------
    ;; Preamble
    ;; Load counters, load MAR0/MAR1 (input/output) pointers
    ;;-------------------------------------------------------------------------
    MMOVI16   MAR0, #IOBUFFER                    ; D2|    MAR0 -> [R0;I0]
    MMOVI16   MAR1, #IOBUFFER                    ; R1|D2| MAR1 -> [R0;I0]
    MMOVI32   MR0, #LOOP_COUNT_S1_2              ; R2|R1| MR0 = LOOP_COUNT_S1_2
    MMOV32    @_loopCountS1_2, MR0               ; E |R2| _loopCountS1_2 = LOOP_COUNT_S1_2
                                                 ;    E |
                                                 ; The MARx columns indicate  what the MARx registers are pointting to                                                                       
                                                 ; * - indicates data for the next set of combined butterflies
;+-------------------------------------------------+-------------------------------------------------------------------+
;| STAGES 1 & 2 Computations                       | MR0 |  MR1          |       MR2     |     MR3       | MAR0 | MAR1 |
;+-------------------------------------------------+-------------------------------------------------------------------+
_CLA_CFFT_run256Pt_stages1and2Combined_loop:    ; |     |               |               |               |      |      |
    .asg     0, N                                ; |     |               |               |               |      |      |
    .loop                                        ; |     |               |               |               |      |      |
    ;; Calculating the Real part first           ; |     |               |               |               |R0    |R0'   |
    MMOV32    MR0, *MAR0[4]++                    ; |R0   |               |               |               |R1    |      |
    MMOV32    MR1, *MAR0[4]++                    ; |     |R1             |               |               |R2    |      |
    MADDF32   MR2, MR0, MR1                      ; |     |               |R0+R1          |               |      |      |
 || MMOV32    MR3, *MAR0[4]++                    ; |     |               |               |R2             |R3    |      |
    MSUBF32   MR0, MR0, MR1                      ; |R0-R1|               |               |               |      |      |
 || MMOV32    MR1, *MAR0[-2]++                   ; |     |R3             |               |               |I2    |      |
    MADDF32   MR3, MR3, MR1                      ; |     |               |               |R2+R3          |      |      |
 || MMOV32    @_temp_R2, MR3                     ; |     |               |               |save R2 (temp) |      |      |
    MADDF32   MR1, MR2, MR3                      ; |     |(R0+R1)+(R2+R3)|               |               |      |      |
 || MMOV32    @_temp_R3, MR1                     ; |     |save R3 (temp) |               |               |      |      |
    MSUBF32   MR2, MR2, MR3                      ; |     |               |(R0+R1)-(R2+R3)|               |      |      |
 || MMOV32    *MAR1[8]++, MR1                    ; |     |               |               |               |      |R2'   |
    MMOV32    MR1, *MAR0[4]++                    ; |     |I2             |               |               |I3    |      |
    MMOV32    MR3, *MAR0[-12]++                  ; |     |               |               |I3             |I0    |      |
    MSUBF32   MR2, MR1, MR3                      ; |     |               |I2-I3          |               |      |      |
 || MMOV32    *MAR1[4]++, MR2                    ; |     |               |               |               |      |R3'   |
    MSUBF32   MR3, MR0, MR2                      ; |     |               |               |(R0-R1)-(I2-I3)|      |      |
 || MMOV32    MR1, *MAR0[4]++                    ; |     |I0             |               |               |I1    |      |
    MADDF32   MR3, MR0, MR2                      ; |     |               |               |(R0-R1)+(I2-I3)|      |      |
 || MMOV32    *MAR1[-8]++, MR3                   ; |     |               |               |               |      |R1'   |
    MMOV32    *MAR1[-2]++, MR3                   ; |     |               |               |               |      |I0'   |
    ;; Calculating the Imaginary part            ; |     |               |               |               |      |      |
    MMOV32    MR0, *MAR0[4]++                    ; |I1   |               |               |               |I2    |      |
    MADDF32   MR2, MR1, MR0                      ; |     |               |I0+I1          |               |      |      |
 || MMOV32    MR3, *MAR0[4]++                    ; |     |               |               |I2             |I3    |      |
    MSUBF32   MR0, MR1, MR0                      ; |I0-I1|               |               |               |      |      |
;; <<VC140213- change offset to point to R0*     ; |-------------------------------------------------------------------|
;; || MMOV32    MR1, *MAR0[-6]++                 ; |     |I3             |               |               |R2    |      |
 || MMOV32    MR1, *MAR0[2]++                    ; |     |I3             |               |               |R0*   |      |
;; VC140213>>                                    ; |-------------------------------------------------------------------|
    MADDF32   MR3, MR3, MR1                      ; |     |               |               |I2+I3          |      |      |
    MADDF32   MR1, MR2, MR3                      ; |     |(I0+I1)+(I2+I3)|               |               |      |      |
    MSUBF32   MR2, MR2, MR3                      ; |     |               |(I0+I1)-(I2+I3)|               |      |      |
 || MMOV32    *MAR1[8]++, MR1                    ; |     |               |               |               |      |I2'   |
;; <<VC140213-R2,R3 overwritten already          ; |-------------------------------------------------------------------|
;;    MMOV32    MR1, *MAR0[4]++                  ; |     |R2             |               |               |R3    |      |
;;    MMOV32    MR3, *MAR0[4]++                  ; |     |               |               |R3             |R0*   |      |
    MMOV32    MR1, @_temp_R2                     ; |     |R2             |               |               |      |      |
    MMOV32    MR3, @_temp_R3                     ; |     |               |               |R3             |      |      |
;; VC140213>>                                    ; |-------------------------------------------------------------------|
    MSUBF32   MR2, MR1, MR3                      ; |     |               |R2-R3          |               |      |      |
 || MMOV32    *MAR1[4]++, MR2                    ; |     |               |               |               |      |I3'   |
    MADDF32   MR3, MR0, MR2                      ; |     |               |               |(I0-I1)+(R2-R3)|      |      |
    MSUBF32   MR3, MR0, MR2                      ; |     |               |               |(I0-I1)-(R2-R3)|      |      |
 || MMOV32    *MAR1[-8]++, MR3                   ; |     |               |               |               |      |I1'   |
    MMOV32    *MAR1[10]++, MR3                   ; |     |               |               |               |      |R0'*  |
                                                 ; +-------------------------------------------------------------------+
    .eval    N + 1, N                            ; increment N
    .break   N = S1_2_LOOPUNROLL                 ; We want to do S1_2_LOOPUNROLL of these combined butterflies
    .endloop                                     ; for stage 1 & 2

    MMOV32    MR0, @_loopCountS1_2               ; MR0 = _loopCountS1_2
    MMOVI32   MR1, #1                            ; MR1 = 1
    MSUB32    MR0, MR0, MR1                      ; _loopCountS1_2--
    MMOV32    @_loopCountS1_2, MR0               ; -3 | _loopCountS1_2 = MR0
    MNOP                                         ; -2
    MNOP                                         ; -1
    MBCNDD    _CLA_CFFT_run256Pt_stages1and2Combined_loop, NEQ   ; Branch
    MNOP                                         ; +1
    MNOP                                         ; +2
    MNOP                                         ; +3
    .unasg    N

    .if (DEBUG_STAGE_DISABLE != DISABLE_STAGE3_4_M )
;;=============================================================================
;;
;; Stages 3 and 4 Combined
;;
;; Notes:
;; - Stage 3 will use the twiddle factors W(8,0) to W(8,1) while stage 4
;;   will use the twiddles W(16,0) to W(16,3)
;; - The twiddle factors have the following relationship with each other
;;   +---------------------------------+-------------------------------------+
;;   | Stage 3 | A |  cos(1) - j sin(1)| W(8,0) W(8,1) W(8,2) W(8,3)         |
;;   |         | B | -cos(1) + j sin(1)| W(8,4) W(8,5) W(8,6) W(8,7)         |
;;   | Stage 4 | C |  cos(2) - j sin(2)| W(16,0) W(16,1) W(16,2) W(16,3)     |
;;   |         | D | -sin(2) - j cos(2)| W(16,4) W(16,5) W(16,6) W(16,7)     |
;;   |         | E | -cos(2) + j sin(2)| W(16,8) W(16,9) W(16,10) W(16,11)   |
;;   |         | F |  sin(2) + j cos(2)| W(16,12) W(16,13) W(16,14) W(16,15) |
;;   +---------------------------------+-------------------------------------+
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;; #cycles = 12 + (41 + 92 * (nLoopQ1Bfly + nLoopQ2Bfly)) * nLoopBranch
;;         = 12 + (41 + 92 * (2 + 2)) * 64
;;         = 26188
;;=============================================================================
_CLA_CFFT_run256Pt_stages3and4Combined:

;; local defines
S34_INSEP            .set  2*(1<<STAGE3)              ; Input Separation = 2^(S_n-1) * 2(size of complex inputs) * 2(float)
S34_GROUPSEP         .set  3*2*(1<<STAGE3)
                                                      ; Group Separation = 3 (# of complex inputs between last input of
                                                      ;                     previous group and 1st input of next group)
                                                      ;                    * 2(complex) *2(float) * 2^(S_n - 1)(seperation between inputs)
S3_TFSKIP            .set  ((4*TWIDDLE_TBL_SIZE)/(1<<STAGE3))
                                                      ; Twiddle table skip factor for stage n 2(float)*2(complex)*(NSAMPLES)/(1<<STAGE<n>)
S4_TFSKIP            .set  ((4*TWIDDLE_TBL_SIZE)/(1<<STAGE4))
                                                      ; Twiddle table skip factor for stage n+1 2(float)*2(complex)*(NSAMPLES)/(1<<STAGE<n+1>)
                                                      ; For each stage N', there are N/N' groups of butterflies, but since
                                                      ; we are doing a combination butterfly i.e. two butterflies at once
                                                      ; we have to further divide by 2
S34_NGROUPS          .set  ((NSAMPLES/(1 << STAGE4)) - 1)
                                                      ; Since we only have the 1st quadrant of twiddles, we are
                                                      ; forced to split the combination butterflies into two sets,
                                                      ; the first where the twiddles A are in the 1st Quadrant and
                                                      ; the other where the twiddles A are in the 2nd Quadrant. The
                                                      ; butterflies are evenly split into 1Q and 2Q
S34_COMBOBFLY_Q      .set  ((1<<STAGE3)/4 - 1)

;; These numbers are the post-increment amounts for the MARx[] addressing
;; the numbers are determined from the sequence of access
    .asg       S34_INSEP        , SNN1_INSEP
                                                      ;; Order of Access
    .asg       -(S34_INSEP+2)   , R0_NEXT             ;; 2
    .asg       -(2*S34_INSEP-2) , R0_NEXT_1           ;; 12
    .asg       -S34_INSEP       , I0_NEXT             ;; 5
    .asg       S34_INSEP        , R1_NEXT             ;; 3
    .asg       2                , I1_NEXT             ;; 1,4
    .asg       -(S34_INSEP+2)   , R2_NEXT             ;; 8
    .asg       -S34_INSEP       , I2_NEXT             ;; 11
    .asg       (3*S34_INSEP-2)  , R3_NEXT             ;; 6
    .asg       S34_INSEP        , R3_NEXT_1           ;; 9
    .asg       2                , I3_NEXT             ;; 7,10
                                                      ;;
    .asg       0                , R0pp_NEXT           ;; 1
    .asg       -(3*S34_INSEP-2) , R0pp_NEXT_1         ;; 9
    .asg       -(3*S34_INSEP-2) , I0pp_NEXT           ;; 5
    .asg       -S34_INSEP       , R1pp_NEXT           ;; 3
    .asg       -S34_INSEP       , I1pp_NEXT           ;; 7
    .asg       2*S34_INSEP      , R2pp_NEXT           ;; 2
    .asg       2*S34_INSEP      , I2pp_NEXT           ;; 6
    .asg       2*S34_INSEP      , R3pp_NEXT           ;; 4
    .asg       2*S34_INSEP      , I3pp_NEXT           ;; 8

    .if DEBUG_BRKPT_ENABLE
    MDEBUGSTOP
    .endif ;;DEBUG_BRKPT_ENABLE
    ;;-------------------------------------------------------------------------
    ;; Preamble
    ;; Load counters, load MAR0/MAR1 (input/output) pointers
    ;;-------------------------------------------------------------------------
    MMOVIZ    MR0, #0
    MMOVXI    MR0, #_cla_twiddleFactors
    MMOV16    MAR1, MR0, #S3_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S3_TFSKIP
    MMOV16    MAR0, MR0, #S4_TFSKIP
    MMOV16    @_pTwiddlesStageN1, MAR0           ; _pTwiddlesStageN1-> _cla_twiddleFactors + S4_TFSKIP
    MMOVXI    MR0, #S34_NGROUPS                  ; MR0 = S34_NGROUPS 
    MMOV32    @_loopCountS3_8, MR0               ; _loopCountS3_8 = S34_NGROUPS 
    MMOVI16   MAR1, #IOBUFFER                    ; MAR1 -> [R0;I0]
    MMOVI16   MAR0, #IOBUFFER                    ; MAR0 -> [R0;I0]
    ;;-------------------------------------------------------------------------
    ;; The pointers point to the next set of N' combined butterflies
    ;; MAR0 -> R0   (need to point to R1, do a dummy read)
    ;; MAR1 -> R0''
    ;;-------------------------------------------------------------------------
    MMOVXI    MR0, #S34_COMBOBFLY_Q              ; MR0 = S34_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = S34_COMBOBFLY_Q 
_CLA_CFFT_run256Pt_stages3and4Combined_loop:
    MMOV32    MR2, @_cla_twiddleFactors
    MMOV32    MR3, @_cla_twiddleFactors+2
    MMOV32    @_SIN1, MR2
    MMOV32    @_COS1, MR3
    MMOV32    @_SIN2, MR2
    MMOV32    @_COS2, MR3

    MMOVIZ    MR2, #0
_CLA_CFFT_run256Pt_stages3and4Combined_loop_1QComboBfly:
    MMOV32    MR0, @_loopCountS3_8_Q             ; MR0 = _loopCountS3_8_Q
    MCMP32    MR0, MR2                           ;
    MTESTTF   EQ                                 ; if (_loopCountS3_8_Q==0) TF = 1 else TF = 0
    MMOVXI    MR2, #1                            ; MR2  = 1
    MSUB32    MR0, MR0, MR2                      ; _loopCountS3_8_Q--
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = MR0

    ;; Run the 1st quadrant butterfly
    BUTTERFLY_STAGE_N_N1_1ST_QUADRANT   _SIN1, _COS1, _SIN2, _COS2
    
    ;; Update the twiddles
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOV16    @_temp_MAR0, MAR0                  ; Save off MAR0
    MMOV16    MAR1, @_pTwiddlesStageN            ; MAR1 = _pTwiddlesStageN
    MMOV16    MAR0, @_pTwiddlesStageN1           ; MAR0 = _pTwiddlesStageN1
    MMOVXI    MR2, #0                            ; MR2 = 0 (for next iteration)
    MMOVIZ    MR2, #0
    MMOV32    MR0, *MAR1[2]++                    ; MR0 = _pTwiddlesStageN[0], MAR1 += 2
    MMOV32    @_SIN1, MR0                        ; SIN1 = _pTwiddlesStageN[0]
    MMOV32    MR1, *MAR1[#(S3_TFSKIP - 2)]++     ; MR1 = _pTwiddlesStageN[1], MAR1 += S3_TFSKIP - 2 (point to next twiddle)
    MMOV32    @_COS1, MR1                        ; COS1 = _pTwiddlesStageN[1]
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN = MAR1
    MMOV32    MR0, *MAR0[2]++                    ; MR0 = _pTwiddlesStageN1[0], MAR1 += 2
    MMOV32    @_SIN2, MR0                        ; -3 | SIN2 = _pTwiddlesStageN1[0]
    MMOV32    MR1, *MAR0[#(S4_TFSKIP - 2)]++     ; -2 | MR1 = _pTwiddlesStageN1[1], MAR1 += S4_TFSKIP - 2 (point to next twiddle)
    MMOV16    @_pTwiddlesStageN1, MAR0           ; -1 | _pTwiddlesStageN1 = MAR1
    MBCNDD    _CLA_CFFT_run256Pt_stages3and4Combined_loop_1QComboBfly, NTF   ; Branch if TF == 0
    MMOV32    @_COS2, MR1                        ; +1 | COS1 = _pTwiddlesStageN1[1]
    MMOV16    MAR1, @_temp_MAR1                  ; +2 | Restore MAR1
    MMOV16    MAR0, @_temp_MAR0                  ; +3 | Restore MAR0

    ;; Reset the quadrant loop counter and twiddles (only SIN1 and COS1) for the
    ;; 2nd quadrant butterfly calculations
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOVIZ    MR0, #0
    MMOVXI    MR0, #S34_COMBOBFLY_Q              ;  MR0 = S34_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR0             ;  _loopCountS3_9_Q = S34_COMBOBFLY_Q
    MMOVXI    MR0, #_cla_twiddleFactors
    MMOV16    MAR1, MR0, #S3_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S3_TFSKIP
    MMOV32    MR2, @_cla_twiddleFactors
    MMOV32    MR3, @_cla_twiddleFactors+2
    MMOV32    @_SIN1, MR2
    MMOV32    @_COS1, MR3
    MMOV16    MAR1, @_temp_MAR1                  ; Restore MAR1

    MMOVIZ    MR2, #0
_CLA_CFFT_run256Pt_stages3and4Combined_loop_2QComboBfly:
    MMOV32    MR0, @_loopCountS3_8_Q             ; MR0 = _loopCountS3_8_Q
    MCMP32    MR0, MR2                           ;
    MTESTTF   EQ                                 ; if (_loopCountS3_8_Q==0) TF = 1 else TF = 0
    MMOVXI    MR2, #1                            ; MR2  = 1
    MSUB32    MR0, MR0, MR2                      ; _loopCountS3_8_Q--
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = MR0

    ;; Run the 2nd quadrant butterfly
    BUTTERFLY_STAGE_N_N1_2ND_QUADRANT   _SIN1, _COS1, _SIN2, _COS2
    
    ;; Update the twiddles
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOV16    @_temp_MAR0, MAR0                  ; Save off MAR0
    MMOV16    MAR1, @_pTwiddlesStageN            ; MAR1 = _pTwiddlesStageN
    MMOV16    MAR0, @_pTwiddlesStageN1           ; MAR0 = _pTwiddlesStageN1
    MMOVXI    MR2, #0                            ; MR2 = 0 (for next iteration)
    MMOVIZ    MR2, #0
    MMOV32    MR0, *MAR1[2]++                    ; MR0 = _pTwiddlesStageN[0], MAR1 += 2
    MMOV32    @_SIN1, MR0                        ; SIN1 = _pTwiddlesStageN[0]
    MMOV32    MR1, *MAR1[#(S3_TFSKIP - 2)]++     ; MR1 = _pTwiddlesStageN[1], MAR1 += S3_TFSKIP - 2 (point to next twiddle)
    MMOV32    @_COS1, MR1                        ; COS1 = _pTwiddlesStageN[1]
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN = MAR1
    MMOV32    MR0, *MAR0[2]++                    ; MR0 = _pTwiddlesStageN1[0], MAR0 += 2
    MMOV32    @_SIN2, MR0                        ; -3 | SIN2 = _pTwiddlesStageN1[0]
    MMOV32    MR1, *MAR0[#(S4_TFSKIP - 2)]++     ; -2 | MR1 = _pTwiddlesStageN1[1], MAR0 += S4_TFSKIP - 2 (point to next twiddle)
    MMOV16    @_pTwiddlesStageN1, MAR0           ; -1 | _pTwiddlesStageN1 = MAR0
    MBCNDD    _CLA_CFFT_run256Pt_stages3and4Combined_loop_2QComboBfly, NTF   ; Branch if TF == 0
    MMOV32    @_COS2, MR1                        ; +1 | COS1 = _pTwiddlesStageN1[1]
    MMOV16    MAR1, @_temp_MAR1                  ; +2 | Restore MAR1
    MMOV16    MAR0, @_temp_MAR0                  ; +3 | Restore MAR0

    MMOVIZ    MR2, #0
    MMOVXI    MR2, #_cla_twiddleFactors
    MMOV16    MAR1, MR2, #S3_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S3_TFSKIP
    MMOV16    MAR0, MR2, #S4_TFSKIP
    MMOV16    @_pTwiddlesStageN1, MAR0           ; _pTwiddlesStageN1-> _cla_twiddleFactors + S4_TFSKIP
    MMOV32    MR0, @_temp_MAR0                   ; MR0 = MAR0
    MMOV32    MR1, @_temp_MAR1                   ; MR1 = MAR1
    MMOV16    MAR1, MR1, #S34_GROUPSEP           ; MAR1 += S34_GROUPSEP
    MMOVIZ    MR2, #0                            ; MR2 = 0
    MMOV32    MR3, @_loopCountS3_8               ; MR3 = _loopCountS3_8 (changes ZF - used in branch)
    MCMP32    MR3, MR2                           ; if(_loopCountS3_8 == 0) ZF = 1 else ZF = 0
    MMOV16    MAR0, MR0, #S34_GROUPSEP           ; -3 | MAR0 += S34_GROUPSEP
    MMOVXI    MR2, #1                            ; -2 | MR2 = [0:1]
    MSUB32    MR3, MR3, MR2                      ; -1 | _loopCountS3_8--
    MBCNDD    _CLA_CFFT_run256Pt_stages3and4Combined_loop, NEQ   ; Branch if _loopCountS3_8 != 0
    MMOV32    @_loopCountS3_8, MR3               ; +1 | _loopCountS3_8 = MR3
    MMOVXI    MR2, #S34_COMBOBFLY_Q              ; +2 | MR1 = S34_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR2             ; +3 | _loopCountS3_8_Q = S34_COMBOBFLY_Q 

    .if (DEBUG_STAGE_DISABLE != DISABLE_STAGE5_6_M )
;;=============================================================================
;;
;; Stages 5 and 6 Combined
;;
;; Notes:
;; - Stage 5 will use the twiddle factors W(32,0) to W(32,7) while stage 6
;;   will use the twiddles W(64,0) to W(64,15)
;; - The twiddle factors have the following relationship with each other
;;   +---------------------------------+-------------------------------------+
;;   | Stage 5 | A |  cos(1) - j sin(1)| W(32,0) .. W(32,7)                  |
;;   |         | B | -cos(1) + j sin(1)| W(32,8) .. W(32,15)                 |
;;   | Stage 6 | C |  cos(2) - j sin(2)| W(64,0) .. W(64,15)                 |
;;   |         | D | -sin(2) - j cos(2)| W(64,16).. W(64,31)                 |
;;   |         | E | -cos(2) + j sin(2)| W(64,32).. W(64,47)                 |
;;   |         | F |  sin(2) + j cos(2)| W(64,48).. W(64,63)                 |
;;   +---------------------------------+-------------------------------------+
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;; #cycles = 12 + (41 + 92 * (nLoopQ1Bfly + nLoopQ2Bfly)) * nLoopBranch
;;         = 12 + (41 + 92 * (8 + 8)) * 16
;;         = 24220
;;=============================================================================
_CLA_CFFT_run256Pt_stages5and6Combined:

;; local defines
S56_INSEP            .set  2*(1<<STAGE5)              ; Input Separation = 2^(S_n-1) * 2(size of complex inputs) * 2(float)
S56_GROUPSEP         .set  3*2*(1<<STAGE5)
                                                      ; Group Separation = 3 (# of complex inputs between last input of
                                                      ;                     previous group and 1st input of next group)
                                                      ;                    * 2(complex) *2(float) * 2^(S_n - 1)(seperation between inputs)

S5_TFSKIP            .set  ((4*TWIDDLE_TBL_SIZE)/(1<<STAGE5))
                                                      ; Twiddle table skip factor for stage n 2(float)*2(complex)*(NSAMPLES)/(1<<STAGE<n>)
S6_TFSKIP            .set  ((4*TWIDDLE_TBL_SIZE)/(1<<STAGE6))
                                                      ; Twiddle table skip factor for stage 4 2(float)*2(complex)*(NSAMPLES)/(1<<STAGE<n+1>)
                                                      ; For each stage N', there are N/N' groups of butterflies, but since
                                                      ; we are doing a combination butterfly i.e. two butterflies at once
                                                      ; we have to further divide by 2
S56_NGROUPS          .set  ((NSAMPLES/(1 << STAGE6)) - 1)
                                                      ; Since we only have the 1st quadrant of twiddles, we are
                                                      ; forced to split the combination butterflies into two sets,
                                                      ; the first where the twiddles A are in the 1st Quadrant and
                                                      ; the other where the twiddles A are in the 2nd Quadrant. The
                                                      ; butterflies are evenly split into 1Q and 2Q
S56_COMBOBFLY_Q      .set  ((1<<STAGE5)/4 - 1)

;; These numbers are the post-increment amounts for the MARx[] addressing
;; the numbers are determined from the sequence of access
    .asg       S56_INSEP        , SNN1_INSEP
                                                      ;; Order of Access
    .asg       -(S56_INSEP+2)   , R0_NEXT             ;; 2
    .asg       -(2*S56_INSEP-2) , R0_NEXT_1           ;; 12
    .asg       -S56_INSEP       , I0_NEXT             ;; 5
    .asg       S56_INSEP        , R1_NEXT             ;; 3
    .asg       2                , I1_NEXT             ;; 1,4
    .asg       -(S56_INSEP+2)   , R2_NEXT             ;; 8
    .asg       -S56_INSEP       , I2_NEXT             ;; 11
    .asg       (3*S56_INSEP-2)  , R3_NEXT             ;; 6
    .asg       S56_INSEP        , R3_NEXT_1           ;; 9
    .asg       2                , I3_NEXT             ;; 7,10
                                                      ;;
    .asg       0                , R0pp_NEXT           ;; 1
    .asg       -(3*S56_INSEP-2) , R0pp_NEXT_1         ;; 9
    .asg       -(3*S56_INSEP-2) , I0pp_NEXT           ;; 5
    .asg       -S56_INSEP       , R1pp_NEXT           ;; 3
    .asg       -S56_INSEP       , I1pp_NEXT           ;; 7
    .asg       2*S56_INSEP      , R2pp_NEXT           ;; 2
    .asg       2*S56_INSEP      , I2pp_NEXT           ;; 6
    .asg       2*S56_INSEP      , R3pp_NEXT           ;; 4
    .asg       2*S56_INSEP      , I3pp_NEXT           ;; 8


    .if DEBUG_BRKPT_ENABLE
    MDEBUGSTOP
    .endif ;;DEBUG_BRKPT_ENABLE
    ;;-------------------------------------------------------------------------
    ;; Preamble
    ;; Load counters, load MAR0/MAR1 (input/output) pointers
    ;;-------------------------------------------------------------------------
    MMOVIZ    MR0, #0
    MMOVXI    MR0, #_cla_twiddleFactors
    MMOV16    MAR1, MR0, #S5_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S5_TFSKIP
    MMOV16    MAR0, MR0, #S6_TFSKIP
    MMOV16    @_pTwiddlesStageN1, MAR0           ; _pTwiddlesStageN1-> _cla_twiddleFactors + S6_TFSKIP
    MMOVXI    MR0, #S56_NGROUPS                  ; MR0 = S56_NGROUPS 
    MMOV32    @_loopCountS3_8, MR0               ; _loopCountS3_8 = S56_NGROUPS 
    MMOVI16   MAR1, #IOBUFFER                    ; MAR1 -> [R0;I0]
    MMOVI16   MAR0, #IOBUFFER                    ; MAR0 -> [R0;I0]
    ;;-------------------------------------------------------------------------
    ;; The pointers point to the next set of N' combined butterflies
    ;; MAR0 -> R0   (need to point to R1, do a dummy read)
    ;; MAR1 -> R0''
    ;;-------------------------------------------------------------------------
    MMOVXI    MR0, #S56_COMBOBFLY_Q              ; MR0 = S56_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = S56_COMBOBFLY_Q 
_CLA_CFFT_run256Pt_stages5and6Combined_loop:
    MMOV32    MR2, @_cla_twiddleFactors
    MMOV32    MR3, @_cla_twiddleFactors+2
    MMOV32    @_SIN1, MR2
    MMOV32    @_COS1, MR3
    MMOV32    @_SIN2, MR2
    MMOV32    @_COS2, MR3

    MMOVIZ    MR2, #0
_CLA_CFFT_run256Pt_stages5and6Combined_loop_1QComboBfly:
    MMOV32    MR0, @_loopCountS3_8_Q             ; MR0 = _loopCountS3_8_Q
    MCMP32    MR0, MR2                           ;
    MTESTTF   EQ                                 ; if (_loopCountS3_8_Q==0) TF = 1 else TF = 0
    MMOVXI    MR2, #1                            ; MR2  = 1
    MSUB32    MR0, MR0, MR2                      ; _loopCountS3_8_Q--
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = MR0

    ;; Run the 1st quadrant butterfly
    BUTTERFLY_STAGE_N_N1_1ST_QUADRANT   _SIN1, _COS1, _SIN2, _COS2
    
    ;; Update the twiddles
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOV16    @_temp_MAR0, MAR0                  ; Save off MAR0
    MMOV16    MAR1, @_pTwiddlesStageN            ; MAR1 = _pTwiddlesStageN
    MMOV16    MAR0, @_pTwiddlesStageN1           ; MAR0 = _pTwiddlesStageN1
    MMOVXI    MR2, #0                            ; MR2 = 0 (for next iteration)
    MMOVIZ    MR2, #0
    MMOV32    MR0, *MAR1[2]++                    ; MR0 = _pTwiddlesStageN[0], MAR1 += 2
    MMOV32    @_SIN1, MR0                        ; SIN1 = _pTwiddlesStageN[0]
    MMOV32    MR1, *MAR1[#(S5_TFSKIP - 2)]++     ; MR1 = _pTwiddlesStageN[1], MAR1 += S5_TFSKIP - 2 (point to next twiddle)
    MMOV32    @_COS1, MR1                        ; COS1 = _pTwiddlesStageN[1]
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN = MAR1
    MMOV32    MR0, *MAR0[2]++                    ; MR0 = _pTwiddlesStageN1[0], MAR1 += 2
    MMOV32    @_SIN2, MR0                        ; -3 | SIN2 = _pTwiddlesStageN1[0]
    MMOV32    MR1, *MAR0[#(S6_TFSKIP - 2)]++     ; -2 | MR1 = _pTwiddlesStageN1[1], MAR1 += S6_TFSKIP - 2 (point to next twiddle)
    MMOV16    @_pTwiddlesStageN1, MAR0           ; -1 | _pTwiddlesStageN1 = MAR1
    MBCNDD    _CLA_CFFT_run256Pt_stages5and6Combined_loop_1QComboBfly, NTF   ; Branch if TF == 0
    MMOV32    @_COS2, MR1                        ; +1 | COS1 = _pTwiddlesStageN1[1]
    MMOV16    MAR1, @_temp_MAR1                  ; +2 | Restore MAR1
    MMOV16    MAR0, @_temp_MAR0                  ; +3 | Restore MAR0

    ;; Reset the quadrant loop counter and twiddles (only SIN1 and COS1) for the
    ;; 2nd quadrant butterfly calculations
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOVIZ    MR0, #0
    MMOVXI    MR0, #S56_COMBOBFLY_Q              ;  MR0 = S56_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR0             ;  _loopCountS3_8_Q = S56_COMBOBFLY_Q 
    MMOVXI    MR0, #_cla_twiddleFactors
    MMOV16    MAR1, MR0, #S5_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S5_TFSKIP
    MMOV32    MR2, @_cla_twiddleFactors
    MMOV32    MR3, @_cla_twiddleFactors+2
    MMOV32    @_SIN1, MR2
    MMOV32    @_COS1, MR3
    MMOV16    MAR1, @_temp_MAR1                  ; Restore MAR1

    MMOVIZ    MR2, #0
_CLA_CFFT_run256Pt_stages5and6Combined_loop_2QComboBfly:
    MMOV32    MR0, @_loopCountS3_8_Q             ; MR0 = _loopCountS3_8_Q
    MCMP32    MR0, MR2                           ;
    MTESTTF   EQ                                 ; if (_loopCountS3_8_Q==0) TF = 1 else TF = 0
    MMOVXI    MR2, #1                            ; MR2  = 1
    MSUB32    MR0, MR0, MR2                      ; _loopCountS3_8_Q--
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = MR0

    ;; Run the 2nd quadrant butterfly
    BUTTERFLY_STAGE_N_N1_2ND_QUADRANT   _SIN1, _COS1, _SIN2, _COS2
    
    ;; Update the twiddles
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOV16    @_temp_MAR0, MAR0                  ; Save off MAR0
    MMOV16    MAR1, @_pTwiddlesStageN            ; MAR1 = _pTwiddlesStageN
    MMOV16    MAR0, @_pTwiddlesStageN1           ; MAR0 = _pTwiddlesStageN1
    MMOVXI    MR2, #0                            ; MR2 = 0 (for next iteration)
    MMOVIZ    MR2, #0
    MMOV32    MR0, *MAR1[2]++                    ; MR0 = _pTwiddlesStageN[0], MAR1 += 2
    MMOV32    @_SIN1, MR0                        ; SIN1 = _pTwiddlesStageN[0]
    MMOV32    MR1, *MAR1[#(S5_TFSKIP - 2)]++     ; MR1 = _pTwiddlesStageN[1], MAR1 += S5_TFSKIP - 2 (point to next twiddle)
    MMOV32    @_COS1, MR1                        ; COS1 = _pTwiddlesStageN[1]
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN = MAR1
    MMOV32    MR0, *MAR0[2]++                    ; MR0 = _pTwiddlesStageN1[0], MAR0 += 2
    MMOV32    @_SIN2, MR0                        ; -3 | SIN2 = _pTwiddlesStageN1[0]
    MMOV32    MR1, *MAR0[#(S6_TFSKIP - 2)]++     ; -2 | MR1 = _pTwiddlesStageN1[1], MAR0 += S6_TFSKIP - 2 (point to next twiddle)
    MMOV16    @_pTwiddlesStageN1, MAR0           ; -1 | _pTwiddlesStageN1 = MAR0
    MBCNDD    _CLA_CFFT_run256Pt_stages5and6Combined_loop_2QComboBfly, NTF   ; Branch if TF == 0
    MMOV32    @_COS2, MR1                        ; +1 | COS1 = _pTwiddlesStageN1[1]
    MMOV16    MAR1, @_temp_MAR1                  ; +2 | Restore MAR1
    MMOV16    MAR0, @_temp_MAR0                  ; +3 | Restore MAR0

    MMOVIZ    MR2, #0
    MMOVXI    MR2, #_cla_twiddleFactors
    MMOV16    MAR1, MR2, #S5_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S5_TFSKIP
    MMOV16    MAR0, MR2, #S6_TFSKIP
    MMOV16    @_pTwiddlesStageN1, MAR0           ; _pTwiddlesStageN1-> _cla_twiddleFactors + S6_TFSKIP
    MMOV32    MR0, @_temp_MAR0                   ; MR0 = MAR0
    MMOV32    MR1, @_temp_MAR1                   ; MR1 = MAR1
    MMOV16    MAR1, MR1, #S56_GROUPSEP           ; MAR1 += S56_GROUPSEP
    MMOVIZ    MR2, #0                            ; MR2 = 0
    MMOV32    MR3, @_loopCountS3_8               ; MR3 = _loopCountS3_8 (changes ZF - used in branch)
    MCMP32    MR3, MR2                           ; if(_loopCountS3_8 == 0) ZF = 1 else ZF = 0
    MMOV16    MAR0, MR0, #S56_GROUPSEP           ; -3 | MAR0 += S56_GROUPSEP
    MMOVXI    MR2, #1                            ; -2 | MR2 = [0:1]
    MSUB32    MR3, MR3, MR2                      ; -1 | _loopCountS3_8--
    MBCNDD    _CLA_CFFT_run256Pt_stages5and6Combined_loop, NEQ   ; Branch if _loopCountS3_9 != 0
    MMOV32    @_loopCountS3_8, MR3               ; +1 | _loopCountS3_8 = MR3
    MMOVXI    MR2, #S56_COMBOBFLY_Q              ; +2 | MR1 = S56_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR2             ; +3 | _loopCountS3_8_Q = S56_COMBOBFLY_Q 
    
    .if (DEBUG_STAGE_DISABLE != DISABLE_STAGE7_8_M )
;;=============================================================================
;;
;; Stages 7 and 8 Combined
;;
;; Notes:
;; - Stage 7 will use the twiddle factors W(128,0) to W(128,31) while stage 8
;;   will use the twiddles W(256,0) to W(256,63)
;; - The twiddle factors have the following relationship with each other
;;   +---------------------------------+-------------------------------------+
;;   | Stage 7 | A |  cos(1) - j sin(1)| W(128,0)  .. W(128,31)              |
;;   |         | B | -cos(1) + j sin(1)| W(128,32) .. W(128,63)              |
;;   | Stage 8 | C |  cos(2) - j sin(2)| W(256,0)  .. W(256,63)              |
;;   |         | D | -sin(2) - j cos(2)| W(256,64) .. W(256,127)             |
;;   |         | E | -cos(2) + j sin(2)| W(256,128).. W(256,191)             |
;;   |         | F |  sin(2) + j cos(2)| W(256,192).. W(256,255)             |
;;   +---------------------------------+-------------------------------------+
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;; #cycles = 12 + (41 + 92 * (nLoopQ1Bfly + nLoopQ2Bfly)) * nLoopBranch
;;         = 12 + (41 + 92 * (32 + 32)) * 4
;;         = 23728
;;=============================================================================
_CLA_CFFT_run256Pt_stages7and8Combined:

;; local defines
S78_INSEP            .set  2*(1<<STAGE7)              ; Input Separation = 2^(S_n-1) * 2(size of complex inputs) * 2(float)
S78_GROUPSEP         .set  3*2*(1<<STAGE7)
                                                      ; Group Separation = 3 (# of complex inputs between last input of
                                                      ;                     previous group and 1st input of next group)
                                                      ;                    * 2(complex) *2(float) * 2^(S_n - 1)(seperation between inputs)
S7_TFSKIP            .set  ((4*TWIDDLE_TBL_SIZE)/(1<<STAGE7)) 
                                                      ; Twiddle table skip factor for stage n 2(float)*2(complex)*(NSAMPLES)/(1<<STAGE<n>)
S8_TFSKIP            .set  ((4*TWIDDLE_TBL_SIZE)/(1<<STAGE8)) 
                                                      ; Twiddle table skip factor for stage 4 2(float)*2(complex)*(NSAMPLES)/(1<<STAGE<n+1>)
                                                      ; For each stage N', there are N/N' groups of butterflies, but since
                                                      ; we are doing a combination butterfly i.e. two butterflies at once
                                                      ; we have to further divide by 2
S78_NGROUPS          .set  ((NSAMPLES/(1 << STAGE8)) - 1)
                                                      ; Since we only have the 1st quadrant of twiddles, we are
                                                      ; forced to split the combination butterflies into two sets,
                                                      ; the first where the twiddles A are in the 1st Quadrant and
                                                      ; the other where the twiddles A are in the 2nd Quadrant. The
                                                      ; butterflies are evenly split into 1Q and 2Q
S78_COMBOBFLY_Q      .set  ((1<<STAGE7)/4 - 1)

;; These numbers are the post-increment amounts for the MARx[] addressing
;; the numbers are determined from the sequence of access
    .asg       S78_INSEP        , SNN1_INSEP
                                                      ;; Order of Access
    .asg       -(S78_INSEP+2)   , R0_NEXT             ;; 2
    .asg       -(2*S78_INSEP-2) , R0_NEXT_1           ;; 12
    .asg       -S78_INSEP       , I0_NEXT             ;; 5
    .asg       S78_INSEP        , R1_NEXT             ;; 3
    .asg       2                , I1_NEXT             ;; 1,4
    .asg       -(S78_INSEP+2)   , R2_NEXT             ;; 8
    .asg       -S78_INSEP       , I2_NEXT             ;; 11
    .asg       (3*S78_INSEP-2)  , R3_NEXT             ;; 6
    .asg       S78_INSEP        , R3_NEXT_1           ;; 9
    .asg       2                , I3_NEXT             ;; 7,10
                                                      ;;
    .asg       0                , R0pp_NEXT           ;; 1
    .asg       -(3*S78_INSEP-2) , R0pp_NEXT_1         ;; 9
    .asg       -(3*S78_INSEP-2) , I0pp_NEXT           ;; 5
    .asg       -S78_INSEP       , R1pp_NEXT           ;; 3
    .asg       -S78_INSEP       , I1pp_NEXT           ;; 7
    .asg       2*S78_INSEP      , R2pp_NEXT           ;; 2
    .asg       2*S78_INSEP      , I2pp_NEXT           ;; 6
    .asg       2*S78_INSEP      , R3pp_NEXT           ;; 4
    .asg       2*S78_INSEP      , I3pp_NEXT           ;; 8


    .if DEBUG_BRKPT_ENABLE
    MDEBUGSTOP
    .endif ;;DEBUG_BRKPT_ENABLE
    ;;-------------------------------------------------------------------------
    ;; Preamble
    ;; Load counters, load MAR0/MAR1 (input/output) pointers
    ;;-------------------------------------------------------------------------
    MMOVIZ    MR0, #0
    MMOVXI    MR0, #_cla_twiddleFactors
    MMOV16    MAR1, MR0, #S7_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S7_TFSKIP
    MMOV16    MAR0, MR0, #S8_TFSKIP
    MMOV16    @_pTwiddlesStageN1, MAR0           ; _pTwiddlesStageN1-> _cla_twiddleFactors + S8_TFSKIP
    MMOVXI    MR0, #S78_NGROUPS                  ; MR0 = S78_NGROUPS 
    MMOV32    @_loopCountS3_8, MR0               ; _loopCountS3_8 = S78_NGROUPS 
    MMOVI16   MAR1, #IOBUFFER                    ; MAR1 -> [R0;I0]
    MMOVI16   MAR0, #IOBUFFER                    ; MAR0 -> [R0;I0]
    ;;-------------------------------------------------------------------------
    ;; The pointers point to the next set of N' combined butterflies
    ;; MAR0 -> R0   (need to point to R1, do a dummy read)
    ;; MAR1 -> R0''
    ;;-------------------------------------------------------------------------
    MMOVXI    MR0, #S78_COMBOBFLY_Q              ; MR0 = S78_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = S78_COMBOBFLY_Q 
_CLA_CFFT_run256Pt_stages7and8Combined_loop:
    MMOV32    MR2, @_cla_twiddleFactors
    MMOV32    MR3, @_cla_twiddleFactors+2
    MMOV32    @_SIN1, MR2
    MMOV32    @_COS1, MR3
    MMOV32    @_SIN2, MR2
    MMOV32    @_COS2, MR3

    MMOVIZ    MR2, #0
_CLA_CFFT_run256Pt_stages7and8Combined_loop_1QComboBfly:
    MMOV32    MR0, @_loopCountS3_8_Q             ; MR0 = _loopCountS3_8_Q
    MCMP32    MR0, MR2                           ;
    MTESTTF   EQ                                 ; if (_loopCountS3_8_Q==0) TF = 1 else TF = 0
    MMOVXI    MR2, #1                            ; MR2  = 1
    MSUB32    MR0, MR0, MR2                      ; _loopCountS3_8_Q--
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = MR0

    ;; Run the 1st quadrant butterfly
    BUTTERFLY_STAGE_N_N1_1ST_QUADRANT   _SIN1, _COS1, _SIN2, _COS2
    
    ;; Update the twiddles
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOV16    @_temp_MAR0, MAR0                  ; Save off MAR0
    MMOV16    MAR1, @_pTwiddlesStageN            ; MAR1 = _pTwiddlesStageN
    MMOV16    MAR0, @_pTwiddlesStageN1           ; MAR0 = _pTwiddlesStageN1
    MMOVXI    MR2, #0                            ; MR2 = 0 (for next iteration)
    MMOVIZ    MR2, #0
    MMOV32    MR0, *MAR1[2]++                    ; MR0 = _pTwiddlesStageN[0], MAR1 += 2
    MMOV32    @_SIN1, MR0                        ; SIN1 = _pTwiddlesStageN[0]
    MMOV32    MR1, *MAR1[#(S7_TFSKIP - 2)]++     ; MR1 = _pTwiddlesStageN[1], MAR1 += S7_TFSKIP - 2 (point to next twiddle)
    MMOV32    @_COS1, MR1                        ; COS1 = _pTwiddlesStageN[1]
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN = MAR1
    MMOV32    MR0, *MAR0[2]++                    ; MR0 = _pTwiddlesStageN1[0], MAR1 += 2
    MMOV32    @_SIN2, MR0                        ; -3 | SIN2 = _pTwiddlesStageN1[0]
    MMOV32    MR1, *MAR0[#(S8_TFSKIP - 2)]++     ; -2 | MR1 = _pTwiddlesStageN1[1], MAR1 += S8_TFSKIP - 2 (point to next twiddle)
    MMOV16    @_pTwiddlesStageN1, MAR0           ; -1 | _pTwiddlesStageN1 = MAR1
    MBCNDD    _CLA_CFFT_run256Pt_stages7and8Combined_loop_1QComboBfly, NTF   ; Branch if TF == 0
    MMOV32    @_COS2, MR1                        ; +1 | COS1 = _pTwiddlesStageN1[1]
    MMOV16    MAR1, @_temp_MAR1                  ; +2 | Restore MAR1
    MMOV16    MAR0, @_temp_MAR0                  ; +3 | Restore MAR0

    ;; Reset the quadrant loop counter and twiddles (only SIN1 and COS1) for the
    ;; 2nd quadrant butterfly calculations
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOVIZ    MR0, #0
    MMOVXI    MR0, #S78_COMBOBFLY_Q              ;  MR0 = S78_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR0             ;  _loopCountS3_8_Q = S78_COMBOBFLY_Q 
    MMOVXI    MR0, #_cla_twiddleFactors
    MMOV16    MAR1, MR0, #S7_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S7_TFSKIP
    MMOV32    MR2, @_cla_twiddleFactors
    MMOV32    MR3, @_cla_twiddleFactors+2
    MMOV32    @_SIN1, MR2
    MMOV32    @_COS1, MR3
    MMOV16    MAR1, @_temp_MAR1                  ; Restore MAR1

    MMOVIZ    MR2, #0
_CLA_CFFT_run256Pt_stages7and8Combined_loop_2QComboBfly:
    MMOV32    MR0, @_loopCountS3_8_Q             ; MR0 = _loopCountS3_8_Q
    MCMP32    MR0, MR2                           ;
    MTESTTF   EQ                                 ; if (_loopCountS3_8_Q==0) TF = 1 else TF = 0
    MMOVXI    MR2, #1                            ; MR2  = 1
    MSUB32    MR0, MR0, MR2                      ; _loopCountS3_8_Q--
    MMOV32    @_loopCountS3_8_Q, MR0             ; _loopCountS3_8_Q = MR0

    ;; Run the 2nd quadrant butterfly
    BUTTERFLY_STAGE_N_N1_2ND_QUADRANT   _SIN1, _COS1, _SIN2, _COS2
    
    ;; Update the twiddles
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOV16    @_temp_MAR0, MAR0                  ; Save off MAR0
    MMOV16    MAR1, @_pTwiddlesStageN            ; MAR1 = _pTwiddlesStageN
    MMOV16    MAR0, @_pTwiddlesStageN1           ; MAR0 = _pTwiddlesStageN1
    MMOVXI    MR2, #0                            ; MR2 = 0 (for next iteration)
    MMOVIZ    MR2, #0
    MMOV32    MR0, *MAR1[2]++                    ; MR0 = _pTwiddlesStageN[0], MAR1 += 2
    MMOV32    @_SIN1, MR0                        ; SIN1 = _pTwiddlesStageN[0]
    MMOV32    MR1, *MAR1[#(S7_TFSKIP - 2)]++     ; MR1 = _pTwiddlesStageN[1], MAR1 += S7_TFSKIP - 2 (point to next twiddle)
    MMOV32    @_COS1, MR1                        ; COS1 = _pTwiddlesStageN[1]
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN = MAR1
    MMOV32    MR0, *MAR0[2]++                    ; MR0 = _pTwiddlesStageN1[0], MAR0 += 2
    MMOV32    @_SIN2, MR0                        ; -3 | SIN2 = _pTwiddlesStageN1[0]
    MMOV32    MR1, *MAR0[#(S8_TFSKIP - 2)]++     ; -2 | MR1 = _pTwiddlesStageN1[1], MAR0 += S8_TFSKIP - 2 (point to next twiddle)
    MMOV16    @_pTwiddlesStageN1, MAR0           ; -1 | _pTwiddlesStageN1 = MAR0
    MBCNDD    _CLA_CFFT_run256Pt_stages7and8Combined_loop_2QComboBfly, NTF   ; Branch if TF == 0
    MMOV32    @_COS2, MR1                        ; +1 | COS1 = _pTwiddlesStageN1[1]
    MMOV16    MAR1, @_temp_MAR1                  ; +2 | Restore MAR1
    MMOV16    MAR0, @_temp_MAR0                  ; +3 | Restore MAR0

    MMOVIZ    MR2, #0
    MMOVXI    MR2, #_cla_twiddleFactors
    MMOV16    MAR1, MR2, #S7_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S7_TFSKIP
    MMOV16    MAR0, MR2, #S8_TFSKIP
    MMOV16    @_pTwiddlesStageN1, MAR0           ; _pTwiddlesStageN1-> _cla_twiddleFactors + S8_TFSKIP
    MMOV32    MR0, @_temp_MAR0                   ; MR0 = MAR0
    MMOV32    MR1, @_temp_MAR1                   ; MR1 = MAR1
    MMOV16    MAR1, MR1, #S78_GROUPSEP           ; MAR1 += S78_GROUPSEP
    MMOVIZ    MR2, #0                            ; MR2 = 0
    MMOV32    MR3, @_loopCountS3_8               ; MR3 = _loopCountS3_8 (changes ZF - used in branch)
    MCMP32    MR3, MR2                           ; if(_loopCountS3_8 == 0) ZF = 1 else ZF = 0
    MMOV16    MAR0, MR0, #S78_GROUPSEP           ; -3 | MAR0 += S78_GROUPSEP
    MMOVXI    MR2, #1                            ; -2 | MR2 = [0:1]
    MSUB32    MR3, MR3, MR2                      ; -1 | _loopCountS3_8--
    MBCNDD    _CLA_CFFT_run256Pt_stages7and8Combined_loop, NEQ   ; Branch if _loopCountS3_9 != 0
    MMOV32    @_loopCountS3_8, MR3               ; +1 | _loopCountS3_8 = MR3
    MMOVXI    MR2, #S78_COMBOBFLY_Q              ; +2 | MR1 = S78_COMBOBFLY_Q 
    MMOV32    @_loopCountS3_8_Q, MR2             ; +3 | _loopCountS3_8_Q = S78_COMBOBFLY_Q 
    
    .unasg    SNN1_INSEP
    .unasg    R0_NEXT     
    .unasg    R0_NEXT_1   
    .unasg    I0_NEXT     
    .unasg    R1_NEXT     
    .unasg    I1_NEXT     
    .unasg    R2_NEXT     
    .unasg    I2_NEXT     
    .unasg    R3_NEXT     
    .unasg    R3_NEXT_1   
    .unasg    I3_NEXT     
    .unasg    R0pp_NEXT   
    .unasg    R0pp_NEXT_1 
    .unasg    I0pp_NEXT   
    .unasg    R1pp_NEXT   
    .unasg    I1pp_NEXT   
    .unasg    R2pp_NEXT   
    .unasg    I2pp_NEXT   
    .unasg    R3pp_NEXT   
    .unasg    I3pp_NEXT   
    .if (DEBUG_STAGE_DISABLE != DISABLE_STAGE9_M )
;;=============================================================================
;;
;; Stage 9
;;
;; Notes:
;; - Stage 9 will use the twiddle factors W(512,0) to W(512,127) 
;; - The twiddle factors have the following relationship with each other
;;   +---------------------------------+-------------------------------------+
;;   | Stage 9 | A |  cos(1) - j sin(1)| W(512,0)    .. W(512,127)           |
;;   |         | B | -cos(1) + j sin(1)| W(512,128)  .. W(512,255)           |
;;   +---------------------------------+-------------------------------------+
;;
;; Register Usage:
;;   MR0: Used in complex calculations  
;;   MR1: Used in complex calculations
;;   MR2: Used in complex calculations
;;   MR3: Used in complex calculations
;;  MAR0: Input pointer to the buffer
;;  MAR1: Output pointer to the buffer
;;
;; #cycles = 9 + (31 + 36 * (nLoopQ1Bfly + nLoopQ2Bfly)) * nLoopBranch
;;         = 9 + (31 + 36 * (2 + 2)) * 128
;;         = 22409
;;=============================================================================
_CLA_CFFT_run256Pt_stage9:

;; local defines
S9_INSEP        .set  2*(1<<STAGE9)               ; Input Separation = 2^(S_n-1) * 2(size of complex inputs) * 2(float)
S9_GROUPSEP     .set  1*2*(1<<STAGE9)
                                                  ; Group Separation = 1 (# of complex inputs between last input of
                                                  ;                     previous group and 1st input of next group)
                                                  ;                    * 2(complex) *2(float) * 2^(S_n - 1)(seperation between inputs)
S9_TFSKIP       .set  ((4*TWIDDLE_TBL_SIZE)/(1<<STAGE9))  
                                                  ; Twiddle table skip factor for stage n 2(float)*2(complex)*(NSAMPLES)/(1<<STAGE<n>)
S9_NGROUPS      .set  ((NSAMPLES/(1 << STAGE9)) - 1)
                                                  ; Since we only have the 1st quadrant of twiddles, we are
                                                  ; forced to split the butterflies into two sets,
                                                  ; the first where the twiddles A are in the 1st Quadrant and
                                                  ; the other where the twiddles A are in the 2nd Quadrant. The
                                                  ; butterflies are evenly split into 1Q and 2Q
S9_BFLY_Q       .set  ((1<<STAGE9)/4 - 1)

;; These numbers are the post-increment amounts for the MARx[] addressing
;; the numbers are determined from the sequence of access
    .asg       S9_INSEP        , SN_INSEP
                                                 ;; Order of Access(input)
    .asg       -(S9_INSEP+2)   , R0_NEXT         ;; 2
    .asg       -S9_INSEP       , I0_NEXT         ;; 5
    .asg       S9_INSEP        , R1_NEXT         ;; 3
    .asg       2               , I1_NEXT         ;; 1,4
    .asg       2               , R0_NEXT_1       ;; 6
                                                 ;; Order of Access(output)
    .asg       S9_INSEP        , R1p_NEXT        ;; 1
    .asg       -(S9_INSEP-2)   , I0p_NEXT        ;; 2
    .asg       S9_INSEP        , I1p_NEXT        ;; 3
    .asg       -(S9_INSEP-2)   , R0p_NEXT_1      ;; 4
    .if DEBUG_BRKPT_ENABLE
    MDEBUGSTOP
    .endif ;;DEBUG_BRKPT_ENABLE
    ;;-------------------------------------------------------------------------
    ;; Preamble
    ;; Load counters, load MAR0/MAR1 (input/output) pointers
    ;;-------------------------------------------------------------------------
    MMOVIZ    MR0, #0
    MMOVI16   MAR1, #_cla_twiddleFactors+S9_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S9_TFSKIP
    MMOVXI    MR0, #S9_NGROUPS                   ; MR0 = S910_NGROUPS 
    MMOV32    @_loopCountS3_9, MR0               ; _loopCountS3_9 = S9_NGROUPS 
    MMOVI16   MAR1, #IOBUFFER                    ; MAR1 -> [R0;I0]
    MMOVI16   MAR0, #IOBUFFER                    ; MAR0 -> [R0;I0]
    ;;-------------------------------------------------------------------------
    ;; The pointers point to the next set of N' combined butterflies
    ;; MAR0 -> R0   (need to point to R1, do a dummy read)
    ;; MAR1 -> R0''
    ;;-------------------------------------------------------------------------
    MMOVXI    MR0, #S9_BFLY_Q                    ; MR0 = S9_BFLY_Q 
    MMOV32    @_loopCountS3_9_Q, MR0             ; _loopCountS3_9_Q = S9_BFLY_Q 
_CLA_CFFT_run256Pt_stage9_loop:
    MMOV32    MR2, @_cla_twiddleFactors
    MMOV32    MR3, @_cla_twiddleFactors+2
    MMOV32    @_SIN1, MR2
    MMOV32    @_COS1, MR3

    MMOVIZ    MR2, #0
_CLA_CFFT_run256Pt_stage9_loop_1QBfly:
    MMOV32    MR0, @_loopCountS3_9_Q             ; MR0 = _loopCountS3_9_Q
    MCMP32    MR0, MR2                           ;
    MTESTTF   EQ                                 ; if (_loopCountS3_9_Q==0) TF = 1 else TF = 0
    MMOVXI    MR2, #1                            ; MR2  = 1
    MSUB32    MR0, MR0, MR2                      ; _loopCountS3_9_Q--
    MMOV32    @_loopCountS3_9_Q, MR0             ; _loopCountS3_9_Q = MR0

    ;; Run the 1st quadrant butterfly
    BUTTERFLY_STAGE_N_1ST_QUADRANT  _SIN1, _COS1
    
    ;; Update the twiddles
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOV16    MAR1, @_pTwiddlesStageN            ; *| MAR1 = _pTwiddlesStageN
    MMOVIZ    MR2, #0                            ;+1|MR2 = 0 (for next iteration)
    MNOP                                         ;+2|
    MNOP                                         ;+3|
    MMOV32    MR0, *MAR1[2]++                    ;-3| MR0 = _pTwiddlesStageN[0], MAR1 += 2
    MMOV32    @_SIN1, MR0                        ;-2| SIN1 = _pTwiddlesStageN[0]
    MMOV32    MR1, *MAR1[#(S9_TFSKIP - 2)]++     ;-1| MR1 = _pTwiddlesStageN[1], MAR1 += S9_TFSKIP - 2 (point to next twiddle)
    MBCNDD    _CLA_CFFT_run256Pt_stage9_loop_1QBfly, NTF   ; Branch if TF == 0
    MMOV32    @_COS1, MR1                        ;+1| COS1 = _pTwiddlesStageN[1]
    MMOV16    @_pTwiddlesStageN, MAR1            ;+2| _pTwiddlesStageN = MAR1
    MMOV16    MAR1, @_temp_MAR1                  ;+3| Restore MAR1

    ;; Reset the quadrant loop counter and twiddles for the
    ;; 2nd quadrant butterfly calculations
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOVIZ    MR0, #0
    MMOVXI    MR0, #S9_BFLY_Q                    ;  MR0 = S9_BFLY_Q 
    MMOV32    @_loopCountS3_9_Q, MR0             ;  _loopCountS3_9_Q = S9_BFLY_Q 
    MMOVI16   MAR1,  #_cla_twiddleFactors+S9_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S9_TFSKIP
    MMOV32    MR2, @_cla_twiddleFactors
    MMOV32    MR3, @_cla_twiddleFactors+2
    MMOV32    @_SIN1, MR2
    MMOV32    @_COS1, MR3
    MMOV16    MAR1, @_temp_MAR1                  ; Restore MAR1

    MMOVIZ    MR2, #0
_CLA_CFFT_run256Pt_stage9_loop_2QBfly:
    MMOV32    MR0, @_loopCountS3_9_Q             ; MR0 = _loopCountS3_9_Q
    MCMP32    MR0, MR2                           ;
    MTESTTF   EQ                                 ; if (_loopCountS3_9_Q==0) TF = 1 else TF = 0
    MMOVXI    MR2, #1                            ; MR2  = 1
    MSUB32    MR0, MR0, MR2                      ; _loopCountS3_9_Q--
    MMOV32    @_loopCountS3_9_Q, MR0             ; _loopCountS3_9_Q = MR0

    ;; Run the 2nd quadrant butterfly
    BUTTERFLY_STAGE_N_2ND_QUADRANT  _SIN1, _COS1
    
    ;; Update the twiddles
    MMOV16    @_temp_MAR1, MAR1                  ; Save off MAR1
    MMOV16    MAR1, @_pTwiddlesStageN            ; *| MAR1 = _pTwiddlesStageN
    MMOVIZ    MR2, #0                            ;+1| MR2 = 0 (for next iteration)
    MNOP                                         ;+2|
    MNOP                                         ;+3|
    MMOV32    MR0, *MAR1[2]++                    ;-3| MR0 = _pTwiddlesStageN[0], MAR1 += 2
    MMOV32    @_SIN1, MR0                        ;-2| SIN1 = _pTwiddlesStageN[0]
    MMOV32    MR1, *MAR1[#(S9_TFSKIP - 2)]++     ;-1| MR1 = _pTwiddlesStageN[1], MAR1 += S9_TFSKIP - 2 (point to next twiddle)
    MBCNDD    _CLA_CFFT_run256Pt_stage9_loop_2QBfly, NTF   ; Branch if TF == 0
    MMOV32    @_COS1, MR1                        ;+1| COS1 = _pTwiddlesStageN[1]
    MMOV16    @_pTwiddlesStageN, MAR1            ;+2| _pTwiddlesStageN = MAR1
    MMOV16    MAR1, @_temp_MAR1                  ;+3| Restore MAR1

    MMOVI16   MAR1, #_cla_twiddleFactors+S9_TFSKIP
    MMOV16    @_pTwiddlesStageN, MAR1            ; _pTwiddlesStageN -> _cla_twiddleFactors + S9_TFSKIP
    MMOV32    MR1, @_temp_MAR1                   ; MR1 = MAR1
    MMOV16    MAR1, MR1, #S9_GROUPSEP            ; MAR1 += S9_GROUPSEP
    MMOVIZ    MR2, #0                            ; MR2 = 0
    MMOV32    MR3, @_loopCountS3_9               ; MR3 = _loopCountS3_9 (changes ZF - used in branch)
    MCMP32    MR3, MR2                           ; if(_loopCountS3_9 == 0) ZF = 1 else ZF = 0
    MMOV16    MAR0, MR0, #S9_GROUPSEP            ; -3 | MAR0 += S9_GROUPSEP
    MMOVXI    MR2, #1                            ; -2 | MR2 = [0:1]
    MSUB32    MR3, MR3, MR2                      ; -1 | _loopCountS3_9--
    MBCNDD    _CLA_CFFT_run256Pt_stage9_loop, NEQ   ; Branch if _loopCountS3_9 != 0
    MMOV32    @_loopCountS3_9, MR3               ; +1 | _loopCountS3_9 = MR3
    MMOVXI    MR2, #S9_BFLY_Q                    ; +2 | MR1 = S9_BFLY_Q 
    MMOV32    @_loopCountS3_9_Q, MR2             ; +3 | _loopCountS3_9_Q = S9_BFLY_Q 

    .unasg    SN_INSEP
    .unasg    R0_NEXT   
    .unasg    I0_NEXT   
    .unasg    R1_NEXT   
    .unasg    I1_NEXT   
    .unasg    COS1
    .unasg    SIN1
    
    .endif ;;(DEBUG_STAGE_DISABLE != DISABLE_STAGE9_M )
    .endif ;;(DEBUG_STAGE_DISABLE != DISABLE_STAGE9_8_M )
    .endif ;;(DEBUG_STAGE_DISABLE != DISABLE_STAGE9_6_M )
    .endif ;;(DEBUG_STAGE_DISABLE != DISABLE_STAGE3_4_M )
    .endif ;;(DEBUG_STAGE_DISABLE != DISABLE_STAGE1_2_M )
    
    MRCNDD    UNC
    MMOV32    MR3, @__CLA_CFFT_run256Pt_sp + 0  ; Restore MR3
    MNOP
    MNOP
    .endasmfunc
;; End of file
