;;#############################################################################
;;! \file source/fft/CFFT_f32_phase.asm
;;!
;;! \brief  Complex FFT phase calculations
;;! \author David M. Alter
;;! \date   11/03/14
;;
;; DESCRIPTION:
;;
;;   Calculates the phase for the 32-bit floating point complex FFT.
;;
;; HISTORY:
;;   11/03/14 - minor optimization of v1.40.00.00 function. (D. Alter)
;;
;; FUNCTIONS:
;;
;;    void CFFT_f32_phase (CFFT_F32_STRUCT_Handle)
;;
;;     where CFFT_F32_STRUCT_Handle is defined as:
;;     typedef volatile CFFT_F32_STRUCT* CFFT_F32_STRUCT_Handle;
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
;;
;;
;; ALGORITHM:
;;
;;     Calculate the complex FFT phase. The data is organized as follows in
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
;;
;; BENCHMARK: 56 cycles/complex value + overhead, if using rts2800_fpu32_fast_supplement.lib
;;            library v1.00 to do the atan2() function.
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
;CFFT_InPtr              .set        (0*2)
;CFFT_OutPtr             .set        (1*2)
;CFFT_CoefPtr              .set        (2*2)
;CFFT_CurrentInPtr      .set        (3*2)
;CFFT_CurrentOutPtr     .set        (4*2)
;CFFT_Stages            .set        (5*2)
;CFFT_FFTSize           .set        (CFFT_Stages+1)

;===========================================================================
; Function: void CFFT_f32_phase(CFFT_F32_STRUCT_Handle)
;===========================================================================
        .if __TI_EABI__
        .asg CFFT_f32_phase, _CFFT_f32_phase
        .asg atan2f, _atan2f
        .endif

        .global _CFFT_f32_phase
        .ref _atan2f
        .text

_CFFT_f32_phase:

        PUSH     XAR1                   ; Save XAR1 (save-on-entry register)
        PUSH     XAR2                   ; Save XAR2 (save-on-entry register)
        PUSH     XAR3                   ; Save XAR3 (save-on-entry register)

        ADDB     XAR4, #6
        MOVL     XAR1, *+XAR4[2]        ; XAR1 = &CurrentOutPtr
        MOVL     XAR2, *+XAR4[0]        ; XAR2 = &CurrentInPtr

        MOV      AL, *+XAR4[5]          ; AL = FFTSize
        SUBB     AL, #1                 ; Init loop counter to "N-1"
        MOV      AR3, AL                ; AR3 = calc_magnitude counter

;----------------------------------------------------------------------
;     Begin phase calculations
;----------------------------------------------------------------------

;--- Main loop

_cfft_f32_calc_phase:

        MOV32    R1H, *XAR2++           ; R1H = Re[i]
        MOV32    R0H, *XAR2++           ; R0H = Im[i]
        LCR      _atan2f                ; R0H = phase[i] = atan2f(Im[i], Re[i])
        MOV32    *XAR1++,R0H            ; Store phase[i]
        BANZ     _cfft_f32_calc_phase, AR3--

;--- Finish up
        POP      XAR3                    ; Restore XAR3
        POP      XAR2                    ; Restore XAR2
        POP      XAR1                    ; Restore XAR1
        LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
