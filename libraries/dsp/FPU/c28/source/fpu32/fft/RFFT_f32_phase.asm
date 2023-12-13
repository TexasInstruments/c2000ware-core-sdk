;;#############################################################################
;;! \file source/fft/RFFT_f32_phase.asm
;;!
;;! \brief  Real FFT phase calculations
;;! \author David M. Alter
;;! \date   Feb 4, 2015
;;
;; DESCRIPTION:
;;
;;   Calculates the phase for the 32-bit floating point real FFT.
;;
;; FUNCTIONS:
;;
;;    void RFFT_f32_phase (RFFT_F32_STRUCT_Handle)
;;
;;     where RFFT_F32_STRUCT_Handle is defined as:
;;     typedef volatile RFFT_F32_STRUCT* RFFT_F32_STRUCT_Handle;
;;
;;    and where RFFT_F32_STRUCT is a structure defined as:
;;
;;    typedef struct {
;;      float    *InBuf;
;;      float    *OutBuf;
;;      float    *CosSinBuf;
;;      float    *MagBuf;
;;      float    *PhaseBuf;
;;      uint16_t FFTSize;
;;      uint16_t FFTStages;
;;    } RFFT_F32_STRUCT;
;;
;; ASSUMPTIONS:
;;
;;     * FFTSize must be a power of 2 (32, 64, 128, etc)
;;     * FFTSize must be greater or equal to 32
;;     * FFTStages must be ln(FFTSize)/ln(2)
;;     * InBuf, OutBuf, CosSinBuf are FFTSize in length
;;     * MagBuf and PhaseBuf are FFTSize/2 in length
;;     * RFFT_f32() or RFFT_f32u() has been called prior to this function
;;
;;
;; ALGORITHM:
;;
;;     Calculate the real FFT phase. The data is organized as follows in
;;     the output buffer after calculating FFT:
;;
;;  +----------------------------+
;;  |  R(0) = DC                 | 0
;;  |  R(1)                      |
;;  |  R(2)                      | Real Component
;;  |  R(3)                      |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  R(FFTSize/2) = fs/2       |
;;  |  I(FFTSize/2 - 1)          |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  I(4)                      | Imaginary Component
;;  |  I(3)                      |
;;  |  I(2)                      |
;;  |  I(1)                      | FFTSize - 1
;;  +----------------------------+
;;
;; BENCHMARK: 58 cycles/complex value + overhead, if using 
;;            rts2800_fpu32_fast_supplement.lib library v1.00 to do the 
;;            atan2() function.
;;
;;  On Entry:   XAR4 = &RFFT_F32_STRUCT
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
;     RFFT_F32_STRUCT structure offsets from XAR4
;----------------------------------------------------------------------
;RFFT_InBuf              .set        (0*2)
;RFFT_OutBuf             .set        (1*2)
;RFFT_CosSinBuf              .set        (2*2)
;RFFT_MagBuf            .set        (3*2)
;RFFT_PhaseBuf          .set        (4*2)
;RFFT_FFTSize             .set        (5*2)
;RFFT_FFTStages         .set        (RFFT_FFTSize+1)
;----------------------------------------------------------------------
    .if __TI_EABI__
    .asg    RFFT_f32_phase, _RFFT_f32_phase
    .asg    atan2f, _atan2f
    .endif
    
    .global _RFFT_f32_phase
    .ref _atan2f
    .text

_RFFT_f32_phase:

        PUSH     XAR1                   ; Save XAR1 (save-on-entry register)
        PUSH     XAR2                   ; Save XAR2 (save-on-entry register)
        PUSH     XAR3                   ; Save XAR3 (save-on-entry register)

        MOVL     XAR2, *+XAR4[2]        ; XAR1 = Rptr = &OutBuf[0]
        ADDB     XAR4, #8               ; Move the structure pointer up
        MOVL     XAR1, *+XAR4[0]        ; XAR2 = &Phasebuf

;--- Calculate pointer to imaginary part results
        MOV      ACC, *+XAR4[2] << 1    ; ACC = 2*FFTSize
        ADDL     ACC, XAR2              ; Add OutBuff address
        MOVL     XAR3, ACC              ; XAR3 = Iptr = &OutBuf[last value]

;--- Calculate main loop count
        MOV      AL, *+XAR4[2]          ; AL = FFTSize
        LSR      AL, #1                 ; AL = FFTSize/2
        SUBB     AL, #2                 ; phase[0] handled separately (subtract 1)
                                        ; loop counter is "N-1" (subtract 1)
        MOV      AR4, AL                ; AR4 = calc_phase counter

;---------------------------------------------------------------------------
;   Begin phase calculations
;---------------------------------------------------------------------------

;--- phase[0] is handled separately since no Im part
        MOVIZF32 R0H, #0                ; R0H = 0.0
        MOV32    *XAR1++, R0H           ; Store phase[0]
        ADDB     XAR2, #2               ; Increment Rptr to next value

_rfft_f32_calc_phase:
        MOV32    R1H, *XAR2++           ; R1H = Re[i]
        MOV32    R0H, *--XAR3           ; R0H = Im[i]
        PUSH     XAR4                   ; Save AR4 (save-on-call register)
        LCR      _atan2f                ; R0H = phase[i] = atan2f(Im[i], Re[i]);
        POP      XAR4                   ; Restore AR4
        MOV32    *XAR1++,R0H            ; Store phase[i]
        BANZ     _rfft_f32_calc_phase,AR4--

;--- Finish up
        POP      XAR3                    ; Restore XAR3
        POP      XAR2                    ; Restore XAR2
        POP      XAR1                    ; Restore XAR1
        LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
