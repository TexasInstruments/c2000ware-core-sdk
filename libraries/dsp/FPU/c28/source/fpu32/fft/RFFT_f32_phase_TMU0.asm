;;#############################################################################
;;! \file source/fft/RFFT_f32_phase_TMU0.asm
;;!
;;! \brief  Real FFT phase calculations using TMU0
;;! \author David M. Alter
;;! \date   11/13/14
;;
;; DESCRIPTION:
;;
;;   Calculates the phase for the 32-bit floating point real FFT.
;;   Requires a C28x device with TMU0 or higher.
;;   On non-TMU devices, use the RFFT_f32_phase() function.
;;
;; FUNCTIONS:
;;
;;    void RFFT_f32_phase_TMU0 (RFFT_F32_STRUCT_Handle)
;;
;;     where RFFT_F32_STRUCT_Handle is defined as:
;;     typedef RFFT_F32_STRUCT* RFFT_F32_STRUCT_Handle;
;;
;;    and where RFFT_F32_STRUCT is a structure defined as:
;;
;;    typedef struct {
;;      float   *InBuf;
;;      float   *OutBuf;
;;      float   *CosSinBuf;
;;      float   *MagBuf;
;;      float   *PhaseBuf;
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
;; CODE OPTIMIZATION:
;;
;; Basic sequence looks like this:
;;
;;       MOV32    R0H, *XAR6++           ; R0H = Re
;;       MOV32    R1H, *--XAR7           ; R1H = Im
;;       QUADF32  R3H,R2H,R1H,R0H        ; if(Im <= Re) R2H= R1H/R0H, else R2H = -R0H/R1H.  also R3H = 0.0, +/-0.25, +/-0.5
;;       NOP
;;       NOP
;;       NOP
;;       NOP
;;       ATANPUF32 R5H,R2H               ; R5H = ATANPU(R2H) (per unit)
;;       NOP
;;       NOP
;;       NOP
;;       ADDF32 R6H,R5H,R3H              ; R6H = R3H + ATANPU(R5H) = atan2 value (per unit)
;;       NOP
;;       NOP
;;       MPY2PIF32 R7H,R6H               ; R7H = ATANPU2 * 2pi = atan2 value (radians)
;;       NOP
;;       MOV32    *XAR5++,R7H            ; Store phase
;;
;; The loop was temporally unrolled to eliminate the many delay slots.
;; Additionally, the loop was spatially unrolled once since ADDF32 is using
;; an output register from two instructions back.  Need to alternate the QUADF32
;; output between R3H and R4H to have the temporal unrolling work correctly.
;;
;; BENCHMARK: 7 cycles/complex value + overhead
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
    .asg    RFFT_f32_phase_TMU0, _RFFT_f32_phase_TMU0
    .endif

    .global _RFFT_f32_phase_TMU0
    .text

_RFFT_f32_phase_TMU0:

        MOV32    *SP++,R6H              ; Save R6H (save-on-entry register)

        MOVL     XAR6, *+XAR4[2]        ; XAR6 = Rptr = &OutBuf[0]
        ADDB     XAR4, #8               ; Move the structure pointer up
        MOVL     XAR5, *+XAR4[0]        ; XAR5 = &Phasebuf

;--- Calculate pointer to imaginary part results
        MOV      ACC, *+XAR4[2] << 1    ; ACC = 2*FFTSize
        ADDL     ACC, XAR6              ; Add OutBuff address
        MOVL     XAR7, ACC              ; XAR7 = Iptr = &OutBuf[last value]

;--- Calculate main loop count
        MOV      AL, *+XAR4[2]          ; AL = FFTSize
        LSR      AL, #2                 ; AL = FFTSize/4
        SUBB     AL, #4                 ; phase[0:1] handled seperately (subtract 1)
                                        ; loop unrolling (subtract 2)
                                        ; loop counter is "N-1" (subtract 1)

;---------------------------------------------------------------------------
;   Begin phase calculations
;---------------------------------------------------------------------------

;--- phase[0] is handled seperately since no Im part
        MOVIZF32 R0H, #0                ; R0H = 0.0
        MOV32    *XAR5++, R0H           ; Store phase[0]
        ADDB     XAR6, #2               ; Increment Rptr to next value

_rfft_f32_calc_phase:

;--- Loop prologue

  ;--- Iteration 1
        MOV32     R0H, *XAR6++          ; R0H = Re[0]
        MOV32     R1H, *--XAR7          ; R1H = Im[0]

   ;--- Iteration 2
        QUADF32   R3H,R2H,R1H,R0H       ; if(Im <= Re) R2H= R1H/R0H, else R2H = -R0H/R1H.  Also R3H = 0.0, +/-0.25, +/-0.5
        MOV32     R0H, *XAR6++          ; R0H = Re[1]
        MOV32     R1H, *--XAR7          ; R1H = Im[1]
        MOV32     *SP++,R5H             ; Save R5H (save-on-entry register)
        MOV32     *SP++,R4H             ; Save R4H (save-on-entry register)

   ;--- Iteration 3
        ATANPUF32 R5H,R2H               ; R5H = ATANPU(R2H) (per unit)
        QUADF32   R4H,R2H,R1H,R0H       ; if(Im <= Re) R2H= R1H/R0H, else R2H = -R0H/R1H.  Also R4H = 0.0, +/-0.25, +/-0.5
        MOV32     R0H, *XAR6++          ; R0H = Re[2]
        MOV32     R1H, *--XAR7          ; R1H = Im[2]
        MOV32     *SP++,R7H             ; Save R7H (save-on-entry register)

   ;--- Iteration 4
        ADDF32    R6H,R5H,R3H           ; R6H = R3H + ATANPU(R2H) = atan2 value (per unit)
        ATANPUF32 R5H,R2H               ; R5H = ATANPU(R2H) (per unit)
        QUADF32   R3H,R2H,R1H,R0H       ; if(Im <= Re) R2H= R1H/R0H, else R2H = -R0H/R1H.  Also R3H = 0.0, +/-0.25, +/-0.5
        MOV32     R0H, *XAR6++          ; R0H = Re[3]
        MOV32     R1H, *--XAR7          ; R1H = Im[3]

   ;--- Iteration 5
        MPY2PIF32 R7H,R6H               ; R7H = ATANPU2 * 2pi = atan2 value (radians)
        ADDF32    R6H,R5H,R4H           ; R6H = R4H + ATANPU(R2H) = atan2 value (per unit)
        ATANPUF32 R5H,R2H               ; R5H = ATANPU(R2H) (per unit)
        QUADF32   R4H,R2H,R1H,R0H       ; if(Im <= Re) R2H= R1H/R0H, else R2H = -R0H/R1H.  Also R4H = 0.0, +/-0.25, +/-0.5
        MOV32     R0H, *XAR6++          ; R0H = Re[4]
        MOV32     R1H, *--XAR7          ; R1H = Im[4]

;--- Loop body
_cfft_f32_calc_phase:
        RPTB _cfft_f32_phase_end, @AL

        MOV32     *XAR5++,R7H           ; Store phase[i+1]
        MPY2PIF32 R7H,R6H               ; R7H = ATANPU2 * 2pi = atan2 value (radians)
        ADDF32    R6H,R5H,R3H           ; R6H = R3H + ATANPU(R2H) = atan2 value (per unit)
        ATANPUF32 R5H,R2H               ; R5H = ATANPU(R2H) (per unit)
        QUADF32   R3H,R2H,R1H,R0H       ; if(Im <= Re) R2H= R1H/R0H, else R2H = -R0H/R1H.  Also R3H = 0.0, +/-0.25, +/-0.5
        MOV32     R0H, *XAR6++          ; R0H = Re[i+1]
        MOV32     R1H, *--XAR7          ; R1H = Im[i+1]

        MOV32     *XAR5++,R7H           ; Store phase[i]
        MPY2PIF32 R7H,R6H               ; R7H = ATANPU2 * 2pi = atan2 value (radians)
        ADDF32    R6H,R5H,R4H           ; R6H = R4H + ATANPU(R2H) = atan2 value (per unit)
        ATANPUF32 R5H,R2H               ; R5H = ATANPU(R2H) (per unit)
        QUADF32   R4H,R2H,R1H,R0H       ; if(Im <= Re) R2H= R1H/R0H, else R2H = -R0H/R1H.  Also R4H = 0.0, +/-0.25, +/-0.5
        MOV32     R0H, *XAR6++          ; R0H = Re[i]
        MOV32     R1H, *--XAR7          ; R1H = Im[i]

_cfft_f32_phase_end:

;--- Loop epilogue.

   ;--- Iteration N-4
        MOV32     *XAR5++,R7H           ; Store phase[N-4]
        MPY2PIF32 R7H,R6H               ; R7H = ATANPU2 * 2pi = atan2 value (radians)
        ADDF32    R6H,R5H,R3H           ; R6H = R3H + ATANPU(R2H) = atan2 value (per unit)
        ATANPUF32 R5H,R2H               ; R5H = ATANPU(R2H) (per unit)
        QUADF32   R3H,R2H,R1H,R0H       ; if(Im <= Re) R2H= R1H/R0H, else R2H = -R0H/R1H.  Also R3H = 0.0, +/-0.25, +/-0.5
        NOP
        NOP
   ;--- Iteration N-3
        MOV32     *XAR5++,R7H           ; Store phase[N-3]
        MPY2PIF32 R0H,R6H               ; R0H = ATANPU2 * 2pi = atan2 value (radians)
        ADDF32    R6H,R5H,R4H           ; R6H = R4H + ATANPU(R2H) = atan2 value (per unit)
        ATANPUF32 R5H,R2H               ; R5H = ATANPU(R2H) (per unit)
        MOV32     R7H,*--SP             ; Restore R7H
   ;--- Iteration N-2
        MOV32     *XAR5++,R0H           ; Store phase[N-2]
        MPY2PIF32 R0H,R6H               ; R0H = ATANPU2 * 2pi = atan2 value (radians)
        ADDF32    R6H,R5H,R3H           ; R6H = R3H + ATANPU(R2H) = atan2 value (per unit)
        MOV32     R4H,*--SP             ; Restore R4H
   ;--- Iteration N-1
        MOV32     *XAR5++,R0H           ; Store phase[N-1]
        MPY2PIF32 R0H,R6H               ; R7H = ATANPU2 * 2pi = atan2 value (radians)
        MOV32     R5H,*--SP             ; Restore R5H
   ;--- Iteration N
        MOV32     *XAR5++,R0H           ; Store phase[N]

;--- Finish up
        MOV32     R6H,*--SP             ; Restore R6H
        LRETR


;;#############################################################################
;;  End of File
;;#############################################################################
