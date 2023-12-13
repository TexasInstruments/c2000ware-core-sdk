;;#############################################################################
;;! \file source/fft/RFFT_f32u.asm
;;!
;;! \brief  Real FFT (Unaligned)
;;! \author C2000
;;! 
;; DESCRIPTION:
;;
;;  This function calculates a real FFT.  The input buffer does not have to
;;  be aligned.  If alignment can be done, then use the RFFT_f32 function to
;;  improve performance.
;; 
;; FUNCTIONS:
;; 
;;    void RFFT_f32u(RFFT_F32_STRUCT_Handle)
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
;;     * FFTStages must be log2(FFTSize)
;;     * InBuf, OutBuf, CosSinBuf are FFTSize in length
;;     * MagBuf and PhaseBuf are FFTSize/2 in length
;;     * MagBuf and PhaseBuf are not used by this function.
;;       They are only used by the magitude and phase calculation functions.
;; 
;; ALGORITHUM:
;; 
;; 1) Bit reverse input data and calculate stages 1, 2 & 3:
;; 
;;  In Buf (read in bit reverse order)                             Out Buf
;;  +----+                                                          +----+
;;  | I1 | (((I1 + I2) + (I3 + I4)) + ((I5 + I6) + (I7 + I8)))/8 -> | I1'|
;;  | I2 | ((I1 - I2) + COS*((I5 - I6) + (I8 - I7))          )/8 -> | I2'|
;;  | I3 | ((I1 + I2) - (I3 + I4)                            )/8 -> | I3'|
;;  | I4 | ((I1 - I2) - COS*((I5 - I6) + (I8 - I7))          )/8 -> | I4'|
;;  | I5 | (((I1 + I2) + (I3 + I4)) - ((I5 + I6) + (I7 + I8)))/8 -> | I5'|
;;  | I6 | (COS*((I8 - I7) - (I5 - I6)) - (I4 - I3)          )/8 -> | I6'|
;;  | I7 | ((I7 + I8) - (I5 + I6)                            )/8 -> | I7'|
;;  | I8 | (COS*((I8 - I7) - (I5 - I6)) + (I4 - I3)          )/8 -> | I8'|
;;     .
;;     .
;;    \|/
;; Repeat above FFTSize/8 (i.e. if FFTSize = 1024, Repeat = 128 times)
;; 
;; Note: COS = COS( 1*2*PI/8) = SIN( 1*2*PI/8)
;; 
;; 2) Calculate stages 4 and up:
;; 
;; 
;;             Out Buf   4   5   6   7   8   9   10  <- Stages
;; +-        +---------+ -   -   -   -   -   -   --
;; |         |    Y1   | 0   0   0   0   0   0    0  <-   Y1 + Y3
;; |         |---------|
;; |         |  X(I1)  | 1   1   1   1   1   1    1  <-   X(I1) + [X(I3)*COS + X(I4)*SIN]
;; |         |---------|
;; |         |    .    |
;; |         |    .    | 3   7  15  31  63 127  255  <-   Inner Loop Repeat Times
;; |         |   \./   |
;; |  I      |---------|
;; |  N      |    Y2   | 4   8  16  32  64 128  256  <-   Y2
;; |  N      |---------|
;; |  E      |   /.\   |
;; |  R      |    .    |
;; |         |    .    |
;; |  L      |---------|
;; |  O      |  X(I2)  | 7  15  31  63 127 255  511 <-   X(I1) - [X(I3)*COS + X(I4)*SIN]
;; |  O      |---------|
;; |  P      |    Y3   | 8  16  32  64 128 256  512 <-   Y1 - Y3
;; |         |---------|
;; |         |  X(I3)  | 9  17  33  65 129 257  513 <-   [X(I4)*COS - X(I3)*SIN] - X(I2)
;; |         |---------|
;; |         |    .    |
;; |         |    .    |
;; |         |   \./   |
;; |         |---------|
;; |         |    Y4   |12  24  48  96 192 384  768 <-   -Y4
;; |         |---------|
;; |         |   /.\   |
;; |         |    .    |
;; |         |    .    |
;; |         |---------|
;; |         |  X(I4)  |15  31  63 127 255 511 1023 <-   [X(I4)*COS - X(I3)*SIN] + X(I2)
;; +-        |---------|
;;           |         |16  32  64 128 256 512 1024
;;                      -- --- --- --- --- --- ----
;;                .      1                          <-   Outer Loop Repeat Times (16   FFT)
;;                .      2   1                      <-   Outer Loop Repeat Times (32   FFT)
;;                .      4   2   1                  <-   Outer Loop Repeat Times (64   FFT)
;;                .      8   4   2   1              <-   Outer Loop Repeat Times (128  FFT)
;;                .     16   8   4   2   1          <-   Outer Loop Repeat Times (256  FFT)
;;                .     32  16   8   4   2   1      <-   Outer Loop Repeat Times (512  FFT)
;;                .     64  32  16   8   4   2    1 <-   Outer Loop Repeat Times (1024 FFT)
;;                .
;;                .
;;               \|/
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

;===========================================================================
; Function: void RFFT_f32u(RFFT_F32_STRUCT_Handle)
;===========================================================================
       .if __TI_EABI__
       .asg         RFFT_f32u, _RFFT_f32u
       .endif
    
       .global      _RFFT_f32u
       .ref         _rfft_f32_Stages4andUp
       .sect       .text

_RFFT_f32u:
       ADDB SP,#2
       MOVL *-SP[2],XAR4
       LCR  _rfft_f32u_Stages1and2and3andBitReverse
       MOVL XAR4,*-SP[2]
       LCR  _rfft_f32_Stages4andUp
       SUBB SP,#2
       LRETR

;===========================================================================
; Function: void rfft_f32u_Stages1and2and3andBitReverse(RFFT_F32_STRUCT_Handle)
;===========================================================================
;---------------------------------------------------------------------------
;
; DESCRIPTION:
;
;     This function bit reverses the input and computes stages 1, 2 and 3
;     This function does not have any alignment requirements for the input
;     buffer.
;
; ON ENTRY:
;
;     XAR4 = Starting address of the RFFT_F32_STRUCT structure
;
; REGISTER USAGE:
;
;     AR0, XAR1, XAR2, XAR4, XAR5, AR3, AR6, XAR7, ACC,
;     R0H, R1H, R2H, R3H, R4H, R5H, R6H, R7H
;
; On Exit:
;
;     RFFT_F32_STRUCT OutBuf contains the computed result
;
;---------------------------------------------------------------------------
;offsets to the stack which holds the bit reversed elements
;---------------------------------------------------------------------------

I1         .set 06H
I2         .set 08H
I3         .set 0AH
I4         .set 0CH
I5         .set 0EH
I6         .set 10H
I7         .set 12H
I8         .set 14H
cossinBuf  .set 04H
;------------------------------------------------------------------------------
;Offset to the stack which holds intermediate results of FFT computation
;------------------------------------------------------------------------------
           .global  _rfft_f32u_Stages1and2and3andBitReverse
           .text

_rfft_f32u_Stages1and2and3andBitReverse:
;----------------------------------------------------------------------
;     Save all save-on-entry registers used
;----------------------------------------------------------------------
        PUSH     XAR1
        PUSH     XAR2
        PUSH     XAR3
        MOV32    *SP++,R4H
        MOV32    *SP++,R5H
        MOV32    *SP++,R6H
        MOV32    *SP++,R7H
        ADDB     SP,#14h

        MOVL     XAR2,*+XAR4[0]         ; &Inbuf
        MOVL     XAR5,*+XAR4[2]         ; &Outbuf
        MOVL     XAR3,*+XAR4[2]
        ADDB     XAR3,#8                ; &Outbuf[4]
        MOVL     XAR7,*+XAR4[4]         ; &CosSinbuf

        MOV      AR0,#0Ah
        MOV      AH,*+XAR4[AR0]         ; FFT SIZE
        MOV      AR0,AH
        LSR      AH,3
        SUBB     AH,#1                  ; (Size / 8) - 1
        MOVL     XAR1,#0000h            ; index if memory is not aligned

        RPTB    _rfft_32_Last, AH
;------------------------------------------------------------------------------
; Code assumes no aligment
;------------------------------------------------------------------------------
        NOP     *,ARP1
        MOVL    ACC,*+XAR2[AR1]
        MOVL    *-SP[I1],ACC            ;I1
        NOP     *,ARP1
        NOP     *BR0++
        MOVL    ACC,*+XAR2[AR1]
        MOVL    *-SP[I2],ACC            ;I2

        NOP     *,ARP1
        NOP     *BR0++
        MOVL    ACC,*+XAR2[AR1]
        MOVL    *-SP[I3],ACC            ;I3

        NOP     *,ARP1
        NOP     *BR0++
        MOVL    ACC,*+XAR2[AR1]
        MOVL    *-SP[I4],ACC            ;I4

        NOP     *,ARP1
        NOP     *BR0++
        MOVL    ACC,*+XAR2[AR1]
        MOVL    *-SP[I5],ACC            ;I5

        NOP     *,ARP1
        NOP     *BR0++
        MOVL    ACC,*+XAR2[AR1]
        MOVL    *-SP[I6],ACC            ;I6

        NOP     *,ARP1
        NOP     *BR0++
        MOVL    ACC,*+XAR2[AR1]
        MOVL    *-SP[I7],ACC            ;I7

        NOP     *,ARP1
        NOP     *BR0++
        MOVL    ACC,*+XAR2[AR1]
        MOVL    *-SP[I8],ACC            ;I8

        NOP     *,ARP1
        NOP     *BR0++
;-------------------------------------------------------------------------------
; Computations for stages 1 2, and 3
;   OutBufIndex++ = (I1 + I2) + (I3 + I4) + (I5 + I6) + (I7 + I8);      (A)  <- XAR5
;   OutBufIndex++ = (I1 - I2) + COS x ((I5 - I6) + (I8 - I7));          (B)
;   OutBufIndex++ = (I1 + I2) - (I3 + I4);                              (C)
;   OutBufIndex++ = (I1 - I2) - COS x ((I5 - I6) + (I8 - I7));          (D)
;   OutBufIndex++ = ((I1 + I2) + (I3 + I4)) - ((I5 + I6) + (I7 + I8));  (E)  <- XAR3
;   OutBufIndex++ = COS x ((I8 - I7) - (I5 - I6)) - (I4 - I3);          (F)
;   OutBufIndex++ = (I7 + I8) - (I5 + I6);                              (G)
;   OutBufIndex++ = COS x ((I8 - I7) - (I5 - I6)) + (I4 - I3);          (H)
;-------------------------------------------------------------------------------
        MOV32       R0H, *-SP[I8]           ; R0H   = I8
        MOV32       R1H, *-SP[I7]           ; R1H   = I7
        SUBF32      R2H, R0H, R1H           ; R2H   = I8-I7
     || MOV32       R3H, *-SP[I5]           ; R3H   = I5
        ADDF32      R0H, R1H, R0H           ; R0H   = I7+I8
     || MOV32       R4H, *-SP[I6]           ; R4H   = I6
        SUBF32      R1H, R3H, R4H           ; R1H   = I5-I6
     || MOV32       R5H, *-SP[I1]           ; R5H   = I1
        ADDF32      R3H, R3H, R4H           ; R3H   = I5+I6
        ADDF32      R4H, R1H, R2H           ; R4H   = (I5-I6) + (I8-I7)
     || MOV32       R6H,*XAR7               ; R6H   = COS
        SUBF32      R7H, R0H, R3H           ; R7H   = (I7+I8) - (I5+I6)  (G)
        MPYF32      R4H, R6H, R4H           ; R4H   = COS x ((I5-I6) + (I8-I7))
     || SUBF32      R2H, R2H, R1H           ; R2H   = (I8-I7) - (I5-I6)
        ADDF32      R0H, R3H, R0H           ; R0H   = (I5+I6) + (I7+I8)
     || MOV32       *+XAR3[4], R7H          ; store G
        MPYF32      R2H, R6H, R2H           ; R2H   = COS x ((I8-I7) - (I5-I6))
     || MOV32       R7H, *-SP[I2]           ; R7H   = I2
        SUBF32      R6H, R5H, R7H           ; R6H   = I1-I2
        ADDF32      R5H, R5H, R7H           ; R5H   = I1+I2
     || MOV32       R1H, *-SP[I4]           ; R1H   = I4
        ADDF32      R3H, R6H, R4H           ; R3H   = (I1-I2) + COS x ((I5-I6) + (I8-I7))  (B)
     || MOV32       R7H, *-SP[I3]           ; R7H   = I3
        SUBF32      R6H, R6H, R4H           ; R6H   = (I1-I2) - COS x ((I5-I6) + (I8-I7))  (D)
        SUBF32      R3H, R1H, R7H           ; R3H   = I4-I3
     || MOV32       *+XAR5[2], R3H          ; store B
        ADDF32      R4H, R7H, R1H           ; R4H   = I3+I4
     || MOV32       *+XAR5[6], R6H          ; store D
        SUBF32      R1H, R2H, R3H           ; R1H = COS x ((I8-I7) - (I5-I6)) - (I4-I3)  (F)
        ADDF32      R2H, R2H, R3H           ; R2H = COS x ((I8-I7) - (I5-I6)) + (I4-I3)  (H)
        ADDF32      R6H, R5H, R4H           ; R6H   = (I1+I2) + (I3+I4)
     || MOV32       *+XAR3[2], R1H          ; save F
        SUBF32      R1H, R5H, R4H           ; R1H   = (I1+I2) - (I3+I4)   (C)
     || MOV32       *+XAR3[6], R2H          ; save H
        SUBF32      R3H, R6H, R0H           ; R3H   = (I1+I2) + (I3+I4) - ((I5+I6) + (I8+I7)) (E)
        ADDF32      R0H, R6H, R0H           ; R0H   = (I1+I2) + (I3+I4) + (I5+I6) + (I8+I7) (A)
     || MOV32       *+XAR5[4], R1H          ; store C
        MOV32       *+XAR3[0], R3H          ; store E
        MOV32       *+XAR5[0], R0H          ; store A
        ADDB        XAR5, #16
        ADDB        XAR3, #16


_rfft_32_Last:
        SUBB        SP,#14h
        MOV32       R7H,*--SP
        MOV32       R6H,*--SP
        MOV32       R5H,*--SP
        MOV32       R4H,*--SP
        POP         XAR3
        POP         XAR2
        POP         XAR1
        LRETR


;;#############################################################################
;;  End of File
;;#############################################################################
