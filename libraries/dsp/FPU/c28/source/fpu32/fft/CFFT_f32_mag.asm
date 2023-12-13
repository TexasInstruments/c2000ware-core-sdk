;;#############################################################################
;;! \file source/fft/CFFT_f32_mag.asm
;;!
;;! \brief  Complex FFT magnitude calculations
;;! \author David M. Alter
;;! \date   11/20/14
;;
;; DESCRIPTION:
;;
;;   Calculates the magnitude for the 32-bit floating point complex FFT.
;;
;; HISTORY:
;;   11/20/14 - optimized v1.40.00.00 function. (D. Alter)
;;
;; FUNCTIONS:
;;
;;    void CFFT_f32_mag (CFFT_F32_STRUCT_Handle)
;;
;;     where CFFT_F32_STRUCT_Handle is defined as:
;;     typedef CFFT_F32_STRUCT* CFFT_F32_STRUCT_Handle;
;;
;;    and where CFFT_F32_STRUCT is a structure defined as:
;;
;;     typedef struct {
;;     float      *InPtr;
;;     float      *OutPtr;
;;     float      *CoefPtr;
;;     float      *CurrentInPtr;
;;     float      *CurrentOutPtr;
;;     uint16_t  Stages;
;;     uint16_t  FFTSize;
;;     } CFFT_F32_STRUCT;
;;
;; ASSUMPTIONS:
;;
;;     * CFFT_f32() has been called prior to this function
;;     * FFTSize must be at least 2 and even.
;;
;;
;; ALGORITHM:
;;
;;     Calculate the complex FFT magnitude. The data is organized as follows in
;;     the output buffer after calculating FFT:
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
;; The loop was spatially unrolled once to eliminate FPU delay slots.
;;
;; BENCHMARK: 18 cycles/complex value + overhead
;;
;;  On Entry:   XAR4 = &CFFT_F32_STRUCT
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
; Function: void CFFT_f32_mag(CFFT_F32_STRUCT_Handle)
;===========================================================================
        .if __TI_EABI__
        .asg CFFT_f32_mag, _CFFT_f32_mag
        .endif

        .global _CFFT_f32_mag
        .text

_CFFT_f32_mag:

        MOV32    *SP++, R4H            ; Save R4H (save-on-entry register)
        MOV32    *SP++, R5H            ; Save R5H (save-on-entry register)
        MOV32    *SP++, R6H            ; Save R6H (save-on-entry register)
        MOV32    *SP++, R7H            ; Save R7H (save-on-entry register)

        ADDB     XAR4, #6
        MOVL     XAR5, *+XAR4[2]      ; XAR5 = &CurrentOutPtr
        MOVL     XAR6, *+XAR4[0]      ; XAR6 = &CurrentInPtr
        MOV      AL, *+XAR4[5]        ; AL = FFTSize
        LSR      AL, #1               ; AL = FFTSize/2
        SUBB     AL, #1               ; Init loop counter to "N-1"

;----------------------------------------------------------------------
;     Begin magnitude calculations
;----------------------------------------------------------------------

;--- Main loop

_cfft_f32_calc_mag:

        RPTB _cfft_f32_mag_end, @AL

    ;--- Compute magnitude squared

        MOV32    R0H, *XAR6++         ; R0H = Re[i]
        MPYF32   R0H, R0H, R0H        ; R0H = Re[i]*Re[i]
     || MOV32    R1H, *XAR6++         ; R1H = Im[i]

        MOV32    R4H, *XAR6++         ; R4H = Re[i+1]
        MPYF32   R4H, R4H, R4H        ; R4H = Re[i+1]*Re[i+1]
     || MOV32    R5H, *XAR6++         ; R5H = Im[i+1]

        MPYF32   R1H, R1H, R1H        ; R1H = Im[i]*Im[i]
        MPYF32   R5H, R5H, R5H        ; R5H = Im[i+1]*Im[i+1]

        ADDF32   R0H, R1H, R0H        ; R0H = (Re[i]*Re[i]) + (Im[i]*Im[i])
        ADDF32   R4H, R5H, R4H        ; R4H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])

    ;--- Do the sqrt

        EISQRTF32   R1H, R0H          ; R1H = Ye[i] = Estimate(1/sqrt(X[i]))
        EISQRTF32   R5H, R4H          ; R5H = Ye[i+1] = Estimate(1/sqrt(X[i+1]))

        MPYF32      R2H, R0H, #0.5    ; R2H = X[i]*0.5
        MPYF32      R6H, R4H, #0.5    ; R6H = X[i+1]*0.5

        MPYF32      R3H, R1H, R1H     ; R3H = Ye[i]*Ye[i]
        MPYF32      R7H, R5H, R5H     ; R7H = Ye[i+1]*Ye[i+1]

        MPYF32      R3H, R3H, R2H     ; R3H = Ye[i]*Ye[i]*X*0.5
        MPYF32      R7H, R7H, R6H     ; R7H = Ye[i+1]*Ye[i+1]*X[i+1]*0.5

        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[i]*Ye[i]*X[i]*0.5
        SUBF32      R7H, #1.5, R7H    ; R7H = 1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5

        MPYF32      R1H, R1H, R3H     ; R1H = Ye[i] = Ye[i]*(1.5 - Ye[i]*Ye[i]*X[i]*0.5)
        MPYF32      R5H, R5H, R7H     ; R6H = Ye[i+1] = Ye[i+1]*(1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5)

        MPYF32      R3H, R1H, R2H     ; R3H = Ye[i]*X[i]*0.5
        MPYF32      R7H, R5H, R6H     ; R7H = Ye[i+1]*X[i+1]*0.5

        MPYF32      R3H, R1H, R3H     ; R3H = Ye[i]*Ye[i]*X[i]*0.5
        MPYF32      R7H, R5H, R7H     ; R7H = Ye[i+1]*Ye[i+1]*X[i+1]*0.5

        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[i]*Ye[i]*X*0.5
        CMPF32      R0H, #0.0         ; Check if X[i] == 0
        MPYF32      R1H, R1H, R3H     ; R1H = Ye[i] = Ye[i]*(1.5 - Ye[i]*Ye[i]*X[i]*0.5)

        SUBF32      R7H, #1.5, R7H    ; R7H = 1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5
        MOV32       R1H, R0H, EQ      ; If X[i] is zero, change the Ye[i] estimate to 0
        CMPF32      R4H, #0.0         ; Check if X[i+1] == 0
        MPYF32      R5H, R5H, R7H     ; R5H = Ye[i+1] = Ye[i+1]*(1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5)

        MPYF32      R0H, R0H, R1H     ; R0H = Y[i] = X[i]*Ye[i] = sqrt(X[i])
        MOV32       R5H, R4H, EQ      ; If X[i+1] is zero, change the Ye[i+1] estimate to 0
        MPYF32      R4H, R4H, R5H     ; R4H = Y[i+1] = X[i+1]*Ye[i+1] = sqrt(X[i+1])

    ;--- Store the result
        MOV32    *XAR5++, R0H         ; Store mag[i]
        MOV32    *XAR5++, R4H         ; Store mag[i+1]

_cfft_f32_mag_end:

;--- Finish up
        MOV32     R7H, *--SP          ; Restore R7H
        MOV32     R6H, *--SP          ; Restore R6H
        MOV32     R5H, *--SP          ; Restore R5H
        MOV32     R4H, *--SP          ; Restore R4H
        LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
