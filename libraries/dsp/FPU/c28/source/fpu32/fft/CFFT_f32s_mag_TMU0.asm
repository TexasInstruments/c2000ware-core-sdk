;;#############################################################################
;;! \file source/fft/CFFT_f32s_mag_TMU0.asm
;;!
;;! \brief  Complex FFT scaled magnitude calculations using TMU0
;;! \author David M. Alter, Alex Tessarolo  
;;! \date   11/06/14
;;
;; HISTORY:
;;   11/06/14 - original (D. Alter, A. Tessarolo)
;;
;; DESCRIPTION:
;;
;;   Calculates the scaled magnitude for the 32-bit floating point complex FFT.
;;   Requires a C28x device with TMU0 or higher.
;;   On non-TMU devices, use the CFFT_f32s_mag() function.
;;
;; FUNCTIONS:
;;
;;    void CFFT_f32s_mag (CFFT_F32_STRUCT_Handle)
;;
;;     where CFFT_F32_STRUCT_Handle is defined as:
;;     typedef CFFT_F32_STRUCT* CFFT_F32_STRUCT_Handle;
;;
;;    and where CFFT_F32_STRUCT is a structure defined as:
;;
;;     typedef struct {
;;     float       *InPtr;
;;     float       *OutPtr;
;;     float       *CoefPtr;
;;     float       *CurrentInPtr;
;;     float       *CurrentOutPtr;
;;     uint16_t  Stages;
;;     uint16_t  FFTSize;
;;     } CFFT_F32_STRUCT;
;;
;; ASSUMPTIONS:
;;
;;     * CFFT_f32() has been called prior to this function
;;     * Stages must be at least 3 (FFTSize >= 8)
;;     * FFTSize must be at least 8 and even.
;;
;; ALGORITHM:
;;
;;     Calculate the complex FFT scaled magnitude. The data is organized as 
;;     follows in the output buffer after calculating FFT:
;;
;;  +----------------------------+
;;  |  R(0)                      | 0
;;  |  I(0)                      |
;;  |  R(1)                      | 
;;  |  I(1)                      |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  R(FFTSize/2) = fs/2       |
;;  |  I(FFTSize/2)              |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  R(N-2)                    | 
;;  |  I(N-2)                    |
;;  |  R(N-1)                    |
;;  |  I(N-1)                    | FFTSize - 1
;;  +----------------------------+
;;
;; CODE OPTIMIZATION:
;;
;; The loop was spatially unrolled twice and temporally unrolled once to 
;; eliminate FPU delay slots.
;;
;; BENCHMARK: 5 cycles/complex value + overhead
;;
;;  On Entry:   XAR4 = &CFFT_F32_STRUCT
;;
;;  Group:            C2000
;;  Target Family:    C28x+FPU32
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

;----------------------------------------------------------------------
;     CFFT_F32_STRUCT structure offsets from XAR4
;----------------------------------------------------------------------
;CFFT_InPtr             .set        (0*2)
;CFFT_OutPtr            .set        (1*2)
;CFFT_CoefPtr           .set        (2*2)
;CFFT_CurrentInPtr      .set        (3*2)
;CFFT_CurrentOutPtr     .set        (4*2)
;CFFT_Stages            .set        (5*2)
;CFFT_FFTSize           .set        (CFFT_Stages+1)

;===========================================================================
; Function: void CFFT_f32s_mag_TMU0(CFFT_F32_STRUCT_Handle)
;===========================================================================
    .if __TI_EABI__
    .asg CFFT_f32s_mag_TMU0, _CFFT_f32s_mag_TMU0
    .endif
    
    .global _CFFT_f32s_mag_TMU0
    .text

_CFFT_f32s_mag_TMU0:
        MOV32    *SP++, R7H             ; Save R7H (save-on-entry register)
        MOV32    *SP++, R6H             ; Save R6H (save-on-entry register)
        MOV32    *SP++, R5H             ; Save R5H (save-on-entry register)
        MOV32    *SP++, R4H             ; Save R4H (save-on-entry register)

        ADDB     XAR4, #6
        MOVL     XAR5, *+XAR4[2]        ; XAR5 = &CurrentOutPtr
        MOVL     XAR6, *+XAR4[0]        ; XAR6 = &CurrentInPtr

;--- Calculate the scale factor
        MOV      AL, *+XAR4[4]          ; AL = stages
        SUBB     AL, #2                 ; AL = scale_value counter
        MOV      AR7, AL                ; AR7 = scale_value counter

        MOVIZF32 R7H,#1.0               ; R7H = 1.0

_cfft_f32s_scale_value:
        MPYF32   R7H,R7H,#0.5           ; R7H = scale
        BANZ _cfft_f32s_scale_value, AR7--

        MPYF32   R7H,R7H,R7H            ; R7H = scale*scale

;--- Compute main loop count
        MOV      AL, *+XAR4[5]          ; AL = FFTSize
        LSR      AL, #2                    ; AL = FFTSize/4
        SUBB     AL, #3                 ; Init loop counter to (N-1) minus 2 
                                        ; more for prologue/epilogue
        MOV32    *SP++, R7H             ; Save scale to stack

;----------------------------------------------------------------------
;     Begin magnitude calculations
;----------------------------------------------------------------------

;--- Loop prologue

;Iteration block 2
        MOV32     R0H, *XAR6++          ; R0H = Re[i+0]
        MPYF32    R0H, R0H, R0H         ; R0H = Re[i+0]*Re[i+0]
     || MOV32     R1H, *XAR6++          ; R1H = Im[i+0]

;Iteration block 3
        MPYF32    R1H, R1H, R1H         ; R1H = Im[i+0]*Im[i+0]
     || MOV32     R2H, *XAR6++          ; R0H = Re[i+1]
        MPYF32    R2H, R2H, R2H         ; R2H = Re[i+1]*Re[i+1]
        ADDF32    R1H, R1H, R0H         ; R1H = (Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])
     || MOV32     R3H, *XAR6++          ; R3H = Im[i+1]

;Iteration block 0
        MPYF32    R3H, R3H, R3H         ; R3H = Im[i+1]*Im[i+1]
     || MOV32     R0H, *-SP[2]          ; R0H = scale factor, iteration [i+0]
        MPYF32    R1H, R1H, R0H         ; R1H = scale*[(Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])]
     || MOV32     R4H, *XAR6++          ; R4H = Re[i+2]
        MPYF32    R4H, R4H, R4H         ; R4H = Re[i+2]*Re[i+2]
        ADDF32    R3H, R3H, R2H         ; R3H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32     R5H, *XAR6++          ; R5H = Im[i+2]
        SQRTF32   R1H, R1H              ; R1H = sqrt[(Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])]

;Iteration block 1
        MPYF32    R5H, R5H, R5H         ; R5H = Im[i+2]*Im[i+2]
     || MOV32     R2H, *-SP[2]          ; R2H = scale factor, iteration [i+1]
        MPYF32    R3H, R3H, R2H         ; R3H = scale*[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
     || MOV32     R6H, *XAR6++          ; R6H = Re[i+3]
        MPYF32    R6H, R6H, R6H         ; R6H = Re[i+3]*Re[i+3]
        ADDF32    R5H, R5H, R4H         ; R5H = (Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])
     || MOV32     R7H, *XAR6++          ; R7H = Im[i+3]
        SQRTF32   R3H, R3H              ; R3H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]

;Iteration block 2
        MPYF32    R7H, R7H, R7H         ; R7H = Im[i+3]*Im[i+3]
     || MOV32     R4H, *-SP[2]          ; R4H = scale factor, iteration [i+2]
        MPYF32    R5H, R5H, R4H         ; R5H = scale*[(Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])]
     || MOV32     R0H, *XAR6++          ; R0H = Re[i+0]
        MPYF32    R0H, R0H, R0H         ; R0H = Re[i+0]*Re[i+0]
     || MOV32     *XAR5++,R1H           ; Store mag[i+0]
        ADDF32    R7H, R7H, R6H         ; R7H = (Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])
     || MOV32     R1H, *XAR6++          ; R1H = Im[i+0]
        SQRTF32   R5H, R5H              ; R5H = sqrt[(Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])]

;Iteration block 3
        MPYF32    R1H, R1H, R1H         ; R1H = Im[i+0]*Im[i+0]
     || MOV32     R6H, *-SP[2]          ; R6H = scale factor, iteration [i+3]
        MPYF32    R7H, R7H, R6H         ; R7H = scale*[(Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])]
     || MOV32     R2H, *XAR6++          ; R2H = Re[i+1]
        MPYF32    R2H, R2H, R2H         ; R2H = Re[i+1]*Re[i+1]
     || MOV32     *XAR5++,R3H           ; Store mag[i+1]
        ADDF32    R1H, R1H, R0H         ; R1H = (Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])
     || MOV32     R3H, *XAR6++          ; R3H = Im[i+1]
        SQRTF32   R7H, R7H              ; R7H = sqrt[(Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])]


;--- Loop body
_cfft_f32s_calc_mag:

         RPTB _cfft_f32s_mag_end, @AL

;Iteration block 0
        MPYF32    R3H, R3H, R3H         ; R3H = Im[i+1]*Im[i+1]
     || MOV32     R0H, *-SP[2]          ; R0H = scale factor, iteration [i+0]
        MPYF32    R1H, R1H, R0H         ; R1H = scale*[(Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])]
     || MOV32     R4H, *XAR6++          ; R4H = Re[i+2]
        MPYF32    R4H, R4H, R4H         ; R4H = Re[i+2]*Re[i+2]
     || MOV32     *XAR5++,R5H           ; Store mag[i+2]
        ADDF32    R3H, R3H, R2H         ; R3H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32     R5H, *XAR6++          ; R5H = Im[i+2]
        SQRTF32   R1H, R1H              ; R1H = sqrt[(Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])]

;Iteration block 1
        MPYF32    R5H, R5H, R5H         ; R5H = Im[i+2]*Im[i+2]
     || MOV32     R2H, *-SP[2]          ; R2H = scale factor, iteration [i+1]
        MPYF32    R3H, R3H, R2H         ; R3H = scale*[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
     || MOV32     R6H, *XAR6++          ; R6H = Re[i+3]
        MPYF32    R6H, R6H, R6H         ; R6H = Re[i+3]*Re[i+3]
     || MOV32     *XAR5++,R7H           ; Store mag[i+3]
        ADDF32    R5H, R5H, R4H         ; R5H = (Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])
     || MOV32     R7H, *XAR6++          ; R7H = Im[i+3]
        SQRTF32   R3H, R3H              ; R3H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]

;Iteration block 2
        MPYF32    R7H, R7H, R7H         ; R7H = Im[i+3]*Im[i+3]
     || MOV32     R4H, *-SP[2]          ; R4H = scale factor, iteration [i+2]
        MPYF32    R5H, R5H, R4H         ; R5H = scale*[(Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])]
     || MOV32     R0H, *XAR6++          ; R0H = Re[i+0]
        MPYF32    R0H, R0H, R0H         ; R0H = Re[i+0]*Re[i+0]
     || MOV32     *XAR5++,R1H           ; Store mag[i+0]
        ADDF32    R7H, R7H, R6H         ; R7H = (Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])
     || MOV32     R1H, *XAR6++          ; R1H = Im[i+0]
        SQRTF32   R5H, R5H              ; R5H = sqrt[(Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])]

;Iteration block 3
        MPYF32    R1H, R1H, R1H         ; R1H = Im[i+0]*Im[i+0]
     || MOV32     R6H, *-SP[2]          ; R6H = scale factor, iteration [i+3]
        MPYF32    R7H, R7H, R6H         ; R7H = scale*[(Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])]
     || MOV32     R2H, *XAR6++          ; R2H = Re[i+1]
        MPYF32    R2H, R2H, R2H         ; R2H = Re[i+1]*Re[i+1]
     || MOV32     *XAR5++,R3H           ; Store mag[i+1]
        ADDF32    R1H, R1H, R0H         ; R1H = (Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])
     || MOV32     R3H, *XAR6++          ; R3H = Im[i+1]
        SQRTF32   R7H, R7H              ; R7H = sqrt[(Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])]

_cfft_f32s_mag_end:

;--- Loop epilogue

;Iteration block 0
        MPYF32    R3H, R3H, R3H         ; R3H = Im[i+1]*Im[i+1]
     || MOV32     R0H, *-SP[2]          ; R0H = scale factor, iteration [i+0]
        MPYF32    R1H, R1H, R0H         ; R1H = scale*[(Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])]
     || MOV32     R4H, *XAR6++          ; R4H = Re[i+2]
        MPYF32    R4H, R4H, R4H         ; R4H = Re[i+2]*Re[i+2]
     || MOV32     *XAR5++,R5H           ; Store mag[i+2]
        ADDF32    R3H, R3H, R2H         ; R3H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32     R5H, *XAR6++          ; R5H = Im[i+2]
        SQRTF32   R1H, R1H              ; R1H = sqrt[(Re[i+0]*Re[i+0]) + (Im[i+0]*Im[i+0])]

;Iteration block 1
        MPYF32    R5H, R5H, R5H         ; R5H = Im[i+2]*Im[i+2]
     || MOV32     R2H, *-SP[2]          ; R2H = scale factor, iteration [i+1]
        MPYF32    R3H, R3H, R2H         ; R3H = scale*[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
     || MOV32     R6H, *XAR6++          ; R6H = Re[i+3]
        MPYF32    R6H, R6H, R6H         ; R6H = Re[i+3]*Re[i+3]
     || MOV32     *XAR5++,R7H           ; Store mag[i+3]
        ADDF32    R5H, R5H, R4H         ; R5H = (Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])
     || MOV32     R7H, *XAR6++          ; R7H = Im[i+3]
        SQRTF32   R3H, R3H              ; R3H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]

;Iteration block 2
        MPYF32    R7H, R7H, R7H         ; R7H = Im[i+3]*Im[i+3]
     || MOV32     R4H, *-SP[2]          ; R4H = scale factor, iteration [i+2]
        MPYF32    R5H, R5H, R4H         ; R5H = scale*[(Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])]
        MOV32     *XAR5++,R1H           ; Store mag[i+0]
        ADDF32    R7H, R7H, R6H         ; R7H = (Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])
        SQRTF32   R5H, R5H              ; R5H = sqrt[(Re[i+2]*Re[i+2]) + (Im[i+2]*Im[i+2])]

;Iteration block 3
        MOV32     R6H, *-SP[2]          ; R6H = scale factor, iteration [i+3]
        MPYF32    R7H, R7H, R6H         ; R7H = scale*[(Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])]
        MOV32     *XAR5++,R3H           ; Store mag[i+1]
        SUBB      SP, #2                ; Deallocate local frame
        SQRTF32   R7H, R7H              ; R7H = sqrt[(Re[i+3]*Re[i+3]) + (Im[i+3]*Im[i+3])]

;Iteration block 0
        MOV32     *XAR5++,R5H           ; Store mag[i+2]
        MOV32    R4H,*--SP              ; Restore R4H
        MOV32    R5H,*--SP              ; Restore R5H

;Iteration block 1
        MOV32    R6H,*--SP              ; Restore R6H
        MOV32    *XAR5++,R7H            ; Store mag[i+3]

;--- Finish up
        MOV32    R7H,*--SP              ; Restore R7H

        LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
