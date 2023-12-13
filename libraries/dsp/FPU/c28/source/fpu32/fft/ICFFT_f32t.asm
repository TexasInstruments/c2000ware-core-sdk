;;#############################################################################
;;! \file source/fft/ICFFT_f32t.asm
;;!
;;! \brief  Complex Inverse FFT using fixed size twiddle factor tables
;;! \author David M. Alter
;;! \date   07/06/11
;;
;; DESCRIPTION:
;;
;; Modified from CFFT_f32.asm from C28x FPU DSP Library v1.20
;; D. Alter     Jul 06, 2011
;; 
;; This function computes an inverse complex FFT using twiddle tables stored
;; in ROM (or device memory). The input buffer must be aligned to a multiple
;; of the FFT size.  If it is not aligned then the output buffer will yield
;; invalid results.
;; 
;; The heart of the computation is the regular complex FFT.  The inverse CFFT
;; is computed using the CFFT via the following algorithm:
;; 
;; 1) Swap the real and imag parts of each member of the input array
;; 2) Perform the complex FFT
;; 3) Swap the real and imag parts of each member of the CFFT output array
;; 4) Scale by 1/FFTSize
;; 
;; No additional overhead is incured for step 1 above as the original CFFT
;; algorithm has been modified at the bit-reversing/stage1-2 step to access
;; the input data accordingly.  For steps 3 and 4, the data is actually swapped
;; and scaled in a seperate post loop.
;;
;; FUNCTIONS:
;;
;;    void ICFFT_f32t (CFFT_F32_STRUCT_Handle)
;;
;;     where CFFT_F32_STRUCT_Handle is defined as:
;;     typedef CFFT_F32_STRUCT* CFFT_F32_STRUCT_Handle;
;;
;;    and where CFFT_F32_STRUCT is a structure defined as:
;;
;;    typedef struct {
;;        float    *InPtr;
;;        float    *OutPtr;
;;        float    *CoefPtr;
;;        float    *CurrentInPtr;
;;        float    *CurrentOutPtr;
;;        uint16_t  Stages;
;;        uint16_t  FFTSize;
;;    }CFFT_F32_STRUCT;
;;
;; ASSUMPTIONS:
;;
;;     * FFTSize must be a power of 2 (32, 64, 128, etc)
;;     * FFTSize must be greater or equal to 32
;;     * Largest complex IFFT possible using the tables is 1024 points
;;     * FFTStages must be log2(FFTSize)
;;     * In, Out, Coef, CurrentIn, CurrentOut are FFTSize in length
;;       (each member is two 32-bit words (real and imaginary parts)
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

        .asg        "+XAR2[0]",D0o
        .asg        "+XAR2[2]",D1o
        .asg        "+XAR2[4]",D2o
        .asg        "+XAR2[6]",D3o
        .asg        "+XAR3[0]",D4o
        .asg        "+XAR3[2]",D5o
        .asg        "+XAR3[4]",D6o
        .asg        "+XAR3[6]",D7o

;        .cdecls    C,LIST,"FPU.h"

;----------------------------------------------------------------------
;     Offsets for local variables stored in memory
;----------------------------------------------------------------------
    .if __TI_EABI__
    .asg    ".bss", .ebss
    .asg    CFFTF32_vars, _CFFTF32_vars
    .endif 
_CFFTF32_vars_InPtr         .usect .ebss,2,1,1
_CFFTF32_vars_OutPtr        .usect .ebss,2,1,1
_CFFTF32_vars_CoefPtr       .usect .ebss,2,1,1
_CFFTF32_vars_CurrentInPtr  .usect .ebss,2,1,1
_CFFTF32_vars_CurrentOutPtr .usect .ebss,2,1,1
_CFFTF32_vars_CurrentSinPtr .usect .ebss,2,1,1
_CFFTF32_vars_CurrentCosPtr .usect .ebss,2,1,1
_CFFTF32_vars_Stages        .usect .ebss,1,1,0
_CFFTF32_vars_DataPtrInc    .usect .ebss,1,1,0
_CFFTF32_vars_CoefPtrInc    .usect .ebss,1,1,0
_CFFTF32_vars_StageCounter  .usect .ebss,1,1,0
_CFFTF32_vars_OuterCounter  .usect .ebss,1,1,0
_CFFTF32_vars_InnerCounter  .usect .ebss,1,1,0

;----------------------------------------------------------------------
;     CFFT_F32_STRUCT member offsets from XAR4
;----------------------------------------------------------------------
CFFT_InPtr              .set        (0*2)
CFFT_OutPtr             .set        (1*2)
CFFT_CoefPtr            .set        (2*2)
CFFT_CurrentInPtr       .set        (3*2)
CFFT_CurrentOutPtr      .set        (4*2)
CFFT_Stages             .set        (5*2)
CFFT_DataPtrInc         .set        (CFFT_Stages+1)

;===========================================================================
; Function: void ICFFT_f32t(CFFT_F32_STRUCT *cfft)
;===========================================================================
; _FPU_ICFFTF32vars1Stages1and2andBitReverse_casm();
; _FPU_ICFFTF32vars1Stages3Up();
;
        .if __TI_EABI__
        .asg ICFFT_f32t, _ICFFT_f32t
        .endif
    
        .global     _ICFFT_f32t
        .sect       .text

_ICFFT_f32t:

        PUSH         XAR0
        
        ADDB         SP,#2
        MOVL         *-SP[2],XAR4
           
        .lp_amode
        SETC        AMODE

        ; Initialize DP that points to CFFTF32 variables:
        MOVW        DP,#_CFFTF32_vars_InPtr
        MOVB        XAR0,#CFFT_InPtr
        MOVL        ACC,*+XAR4[AR0]
        MOVL        @@_CFFTF32_vars_InPtr,ACC

        MOVB        XAR0,#CFFT_OutPtr
        MOVL        ACC,*+XAR4[AR0]
        MOVL        @@_CFFTF32_vars_OutPtr,ACC
        
        MOVB        XAR0,#CFFT_CoefPtr
        MOVL        ACC,*+XAR4[AR0]
        MOVL        @@_CFFTF32_vars_CoefPtr,ACC

        MOVL        XAR0,#CFFT_Stages
        MOV         AL,*+XAR4[AR0]
        MOV         @@_CFFTF32_vars_Stages,AL
       
        .C28_amode
        CLRC        AMODE
           
        LCR         _FPU_ICFFTF32vars1Stages1and2andBitReverse_casm
        MOVL        XAR4,*-SP[2]
        LCR         _FPU_ICFFTF32vars1Stages3Up_casm
        SUBB        SP,#2

        .lp_amode
        SETC        AMODE

        ; Final output saved in memory pointed by CurrentInPtr 
        MOVB        XAR0,#CFFT_CurrentInPtr
        MOVL        ACC,@@_CFFTF32_vars_CurrentInPtr
        MOVL        *+XAR4[AR0],ACC

        MOVB        XAR0,#CFFT_CurrentOutPtr
        MOVL        ACC,@@_CFFTF32_vars_CurrentOutPtr
        MOVL        *+XAR4[AR0],ACC
       
        .C28_amode
        CLRC        AMODE
       
        POP         XAR0
        LRETR

;;-----------------------------------------------------------------------------
;; Inverse Complex FFT F32 Stages 1 and 2 with bit reverse addressing:
;;-----------------------------------------------------------------------------
;;              +--------------------------------------+
;; InPtr OutPtr | Stages 1 & 2                         |
;;              +-----+--------------------------------+
;; XAR1-> XAR2-> R(0) | D0'  = (D0 + D2)  + (D4 + D6)  | 
;;               I(0) | D1'  = (D1 + D3)  + (D5 + D7)  | 
;;               R(1) | D2'  = (D0 - D2)  + (D5 - D7)  | 
;;               I(1) | D3'  = (D1 - D3)  - (D4 - D6)  | 
;;               R(2) | D4'  = (D0 + D2)  - (D4 + D6)  | 
;;               I(2) | D5'  = (D1 + D3)  - (D5 + D7)  | 
;;               R(3) | D6'  = (D0 - D2)  - (D5 - D7)  | 
;;               I(3) | D7'  = (D1 - D3)  + (D4 - D6)  | 
;;              +-----+--------------------------------+
;;                64  <- Outer loop repeat times for  256-point Complex FFT
;;               128  <- Outer loop repeat times for  512-point Complex FFT
;;               256  <- Outer loop repeat times for 1024-point Complex FFT
;;---------------------------------------------------------------------------
;;
;; C Call:     void FPU_CFFTF32_Stages1and2_casm(void);
;;
;;             Note: Data in input and output buffers is stored as follows:
;;                       Re(0) <- *InPtr, *OutPtr
;;                       Im(0)
;;                       Re(1)
;;                       Im(1)
;;                       ...
;;
;;----------------------------------------------------------------------------
        .text
_FPU_ICFFTF32vars1Stages1and2andBitReverse_casm:
        PUSH        XAR0
        PUSH        XAR1
        PUSH        XAR2
        MOV32       *SP++,R0H
        MOV32       *SP++,R1H
        MOV32       *SP++,R2H
        MOV32        *SP++,R3H
        MOV32        *SP++,R4H
        MOV32        *SP++,R5H
        MOV32        *SP++,R6H
        MOV32        *SP++,R7H

        ; Initialize DP that points to CFFTF32 variables:
        MOVW        DP,#_CFFTF32_vars_InPtr

        ; Initialize input and output pointers and do pointer swap for following stages:
        MOVL        XAR1,@_CFFTF32_vars_InPtr            ; fft.InPtr.  XAR1 points to R(0).
        MOVL        XAR2,@_CFFTF32_vars_OutPtr
        MOVL        @_CFFTF32_vars_CurrentOutPtr,XAR1
        MOVL        @_CFFTF32_vars_CurrentInPtr,XAR2
        ADDB        XAR1, #2                            ; Make XAR1 point to I(0), not R(0)

        ; Initialize Loop Counter (AL) and Bit Reverse Index (AR0):
        ; AL = (2^Stages >> 2) - 1
        ;    =  63 (execute loop  64 times for  256-point CFFT)
        ;    = 127 (execute loop 128 times for  512-point CFFT)
        ;    = 255 (execute loop 256 times for 1024-point CFFT)
        ; AR0 = (2^Stages << 1)
        ;    =  512 (for  256-point CFFT)
        ;    = 1024 (for  512-point CFFT)
        ;    = 2048 (for 1024-point CFFT)
        MOV            T,@_CFFTF32_vars_Stages
        MOVB        AL,#1
        LSL            AL,T
        LSL            AL,#1
        MOVZ        AR0,@AL
        LSR            AL,#3
        SUBB        AL,#1


        RPTB        ICFFTF32vars1Stages1and2BitReverseLoop,@AL
        NOP            *, ARP1                ; ARP = AR1
        MOV32        R0H,*--                ; R0H = D0
        MOV32        R1H,*BR0++            ; R1H = D1
        ADDB        XAR1, #2
        MOV32        R2H,*--                ; R2H = D2
        ADDF32        R7H,R0H,R2H            ; R7H = (D0 + D2)
        ||MOV32        R3H,*BR0++            ; R3H = D3
        ADDB        XAR1, #2
        ADDF32        R6H,R1H,R3H            ; R6H = (D1 + D3)
        ||MOV32        R4H,*--                ; R4H = D4
        SUBF32        R0H,R0H,R2H            ; R0H = (D0 - D2)
        ||MOV32        R5H,*BR0++            ; R5H = D5
        ADDB        XAR1, #2
        SUBF32        R2H,R1H,R3H            ; R2H = (D1 - D3)
        ||MOV32        R1H,*--                ; R1H = D6
        ADDF32        R3H,R4H,R1H            ; R3H = (D4 + D6)
        SUBF32        R4H,R4H,R1H            ; R4H = (D4 - D6)
        ADDF32        R1H,R7H,R3H            ; R1H = (D0 + D2) + (D4 + D6)
        SUBF32        R7H,R7H,R3H            ; R7H = (D0 + D2) - (D4 + D6)
        ||MOV32        R3H,*BR0++            ; R3H = D7
        ADDB        XAR1, #2
        ADDF32        R1H,R5H,R3H            ; R1H = (D5 + D7)
        ||MOV32        *XAR2++,R1H
        SUBF32        R5H,R5H,R3H            ; R5H = (D5 - D7)
        ADDF32        R3H,R6H,R1H            ; R3H = (D1 + D3) + (D5 + D7)
        SUBF32        R6H,R6H,R1H            ; R6H = (D1 + D3) - (D5 + D7)
        ADDF32        R1H,R0H,R5H            ; R1H = (D0 - D2) + (D5 - D7)
        ||MOV32        *XAR2++,R3H
        SUBF32        R3H,R0H,R5H            ; R3H = (D0 - D2) - (D5 - D7)
        SUBF32        R5H,R2H,R4H            ; R5H = (D1 - D3) - (D4 - D6)
        ||MOV32        *XAR2++,R1H
        ADDF32        R0H,R2H,R4H            ; R0H = (D1 - D3) + (D4 - D6)
        MOV32        *XAR2++,R5H
        MOV32        *XAR2++,R7H
        MOV32        *XAR2++,R6H
        MOV32        *XAR2++,R3H
        MOV32        *XAR2++,R0H
ICFFTF32vars1Stages1and2BitReverseLoop:

        MOV32        R7H,*--SP
        MOV32        R6H,*--SP
        MOV32        R5H,*--SP
        MOV32        R4H,*--SP
        MOV32        R3H,*--SP
        MOV32        R2H,*--SP
        MOV32        R1H,*--SP
        MOV32        R0H,*--SP
        POP            XAR2
        POP            XAR1
        POP            XAR0
        LRETR        

;;-----------------------------------------------------------------------------
;; Inverse Complex FFT F32 Stages 3 and Up:
;;-----------------------------------------------------------------------------
;;               +--------+--------+--------+--------+--------+--------+--------+---------+----
;; InPtr  OutPtr | Satge3 | Stage4 | Stage5 | Stage6 | Stage7 | Stage8 | Stage9 | Stage10 | ...
;;               +--------+--------+--------+--------+--------+--------+--------+---------+----
;; XAR2-> XAR6->   R(0)   | R(0)   | R(0)   | R(0)   | R(0)   | R(0)   | R(0)   | R(0)    | D0' = D0  + (D2*Cos(0) + D3*Sin(0))
;;   |      |      I(0)   | I(0)   | I(0)   | I(0)   | I(0)   | I(0)   | I(0)   | I(0)    | D1' = D1  + (D3*Cos(0) - D2*Sin(0))  
;;   |      |        .                                                     
;;  \|/    \|/       4        8        16       32       64       128      256      512     <- InnerLoop Repeat Times
;;                   .                                                        
;;                 R(3)   | R(7)   | R(15)  | R(31)  | R(63)  | R(127) | R(255) | R(511)  | D0' = D0  + (D2*Cos(n) + D3*Sin(n))  
;;                 I(3)   | I(7)   | I(15)  | I(31)  | I(63)  | I(127) | I(255) | I(511)  | D1' = D1  + (D3*Cos(n) - D2*Sin(n))  
;; XAR3-> XAR7->   R(4)   | R(8)   | R(16)  | R(32)  | R(64)  | R(128) | R(256) | R(512)  | D2' = D0  - (D2*Cos(0) + D3*Sin(0))
;;   |      |      I(4)   | I(8)   | I(16)  | I(32)  | I(64)  | I(128) | I(256) | I(512)  | D3' = D1  - (D3*Cos(0) - D2*Sin(0)) 
;;   |      |        .
;;  \|/    \|/       .                                                              
;;                   .                                                       
;;                 R(7)   | R(15)  | R(31)  | R(63)  | R(127) | R(255) | R(511) | R(1023) | D2' = D0  - (D2*Cos(n) + D3*Sin(n))
;;                 I(7)   | I(15)  | I(31)  | I(63)  | I(127) | I(255) | I(511) | I(1023) | D3' = D1  - (D3*Cos(n) - D2*Sin(n)) 
;;                ------------------------------------------------------------------------+----
;;                   32       16        8        4        2        1        0        0      <- OuterLoop repeat times for  256-point CFFT
;;                   64       32       16        8        4        2        1        0      <- OuterLoop repeat times for  512-point CFFT
;;                  128       64       32       16        8        4        2        1      <- OuterLoop repeat times for 1024-point CFFT
;;-----------------------------------------------------------------------------
;; Complex FFT Coefficient (twiddle) Table:
;;-----------------------------------------------------------------------------
;;  FFT   Stage   Iter Address     Table Value                  TablePointers
;; SIZE                  x16
;;------+------+------+-------+------------------------------------------------
;;  256 |   8  |    1 |     0 | SIN(   0*pi/128 )                   <-XAR5
;;      .      .      .       .
;;      |      |      |   128 | SIN(  64*pi/128 ) = COS(  0*pi/128) <-XAR4
;;      .      .      .       .
;;      |      |  128 |   254 | SIN( 127*pi/128 ) = COS( 63*pi/128)
;;      |      |      |   256 | SIN( 128*pi/128 ) = COS( 64*pi/128)
;;      .      .      .       .
;;      |      |      |   382 | SIN( 191*pi/128 ) = COS(127*pi/128)
;;------+------+------+-------+------------------------------------------------
;;  512 |   9  |    1 |     0 | SIN(   0*pi/256 )                   <-XAR5
;;      .      .      .       .
;;      |      |      |   256 | SIN( 128*pi/256 ) = COS(  0*pi/256) <-XAR4
;;      .      .      .       .
;;      |      |  256 |   510 | SIN( 255*pi/256 ) = COS(127*pi/256)
;;      |      |      |   512 | SIN( 256*pi/256 ) = COS(128*pi/256)
;;      .      .      .       .
;;      |      |      |   766 | SIN( 383*pi/256 ) = COS(255*pi/256)
;;------+------+------+-------+------------------------------------------------
;; 1024 |  10  |    1 |     0 | SIN(   0*pi/512 )                   <-XAR5
;;      .      .      .       .
;;      |      |      |   512 | SIN( 256*pi/512 ) = COS(  0*pi/512) <-XAR4
;;      .      .      .       .
;;      |      |  512 |  1022 | SIN( 511*pi/512 ) = COS(255*pi/512)
;;      |      |      |  1024 | SIN( 512*pi/512 ) = COS(256*pi/512)
;;      .      .      .       .
;;      |      |      |  1534 | SIN( 767*pi/512 ) = COS(511*pi/512)
;;------+------+------+-------+------------------------------------------------
;;                         Stage:   3   4   5   6   7   8   9  10
;; Coef Step For  256-point CFFT:  64  32  16   8   4   2   -   -
;; Coef Step For  512-point CFFT: 128  64  32  16   8   4   2   -
;; Coef Step For 1024-point CFFT: 256 128  64  32  16   8   4   2
;;-----------------------------------------------------------------------------
;;
;; C Call:     void FPU_ICFFTF32vars1Stage3Up_casm(void);
;;
;;             Note: Data in input and output buffers is stored as follows:
;;                       Re(0) <- *InPtr, *OutPtr
;;                       Im(0)
;;                       Re(1)
;;                       Im(1)
;;                       ...
;;
;;-----------------------------------------------------------------------------
        .text
_FPU_ICFFTF32vars1Stages3Up_casm:
        PUSH        XAR0
        PUSH        XAR1
        PUSH        XAR2
        PUSH        XAR3
        PUSH        XAR4
        PUSH        XAR5
        PUSH        XAR6
        PUSH        XAR7
        MOV32        *SP++,R0H
        MOV32        *SP++,R1H
        MOV32        *SP++,R2H
        MOV32        *SP++,R3H
        MOV32        *SP++,R4H
        MOV32        *SP++,R5H
        MOV32        *SP++,R6H
        MOV32        *SP++,R7H

        .lp_amode
        SETC        AMODE

        ; Initialize DP that points to CFFTF32 variables:
        MOVW        DP,#_CFFTF32_vars_InPtr
        
        ; Initialize data input and output pointers starting from stage 3:
        MOVL        XAR3,@@_CFFTF32_vars_CurrentInPtr
        MOVL        XAR7,@@_CFFTF32_vars_CurrentOutPtr
        MOVL        XAR2,@@_CFFTF32_vars_CurrentInPtr
        MOVL        XAR6,@@_CFFTF32_vars_CurrentOutPtr

        ; Initialize "StageCounter" value starting from stage 3:
        ; StageCounter = (Stages -2) - 1 = Stages - 3
        ;              =  7 (execute StageLoop 8 times for 1024-point CFFT)
        ;              =  6 (execute StageLoop 7 times for  512-point CFFT)
        ;              =  5 (execute StageLoop 6 times for  128-point CFFT)
        MOV            AL,@@_CFFTF32_vars_Stages
        SUBB        AL,#3                        
        MOV            @@_CFFTF32_vars_StageCounter,AL

        ; Initialize "OuterCounter" value starting from stage 3:
        ; OuterCounter = (2^Stages) >> 3) - 1
        ;              = 127 (for 1024-point CFFT)
        ;              =  63 (for  512-point CFFT)
        ;              =  31 (for  256-point CFFT)
        MOV            T,@@_CFFTF32_vars_Stages
        MOVB        AL,#1
        LSL            AL,T
        LSR            AL,#3
        SUBB        AL,#1
        MOV            @@_CFFTF32_vars_OuterCounter,AL

        ; Initialize "CoefPtrInc" value starting from stage 3:
        ; CoefPtrInc = (2^Stages) >> 3) = (OuterCounter + 1)*2
        ;            = 256 (for 1024-point CFFT)
        ;            = 128 (for  512-point CFFT)
        ;            =  64 (for  256-point CFFT)
        ; Since we use a 1024 pre-generated twiddle factor table, "CoefPtrInc"
        ; always starts at 256
        MOV         ACC, #256
        MOV         @@_CFFTF32_vars_CoefPtrInc,AL

        ; Initialize "CurrentCosPtr" value:
        ; CurrentCosPtr = XAR4 =  CoefPtr + CoefPtrInc*2
        ;            = 128 (for 1024-point CFFT)
        ;            =  64 (for  512-point CFFT)
        ;            =  32 (for  256-point CFFT)
        MOVL        XAR5,@@_CFFTF32_vars_CoefPtr
        MOVL        XAR4,@@_CFFTF32_vars_CoefPtr
        MOVL        @@_CFFTF32_vars_CurrentSinPtr,XAR5
        LSL            AL,#1
        MOVZ        AR0,@AL
        NOP            *,ARP4
        NOP            *0++
        MOVL        @@_CFFTF32_vars_CurrentCosPtr,XAR4

        ; Initialize other values starting from stage 3:
        MOV            @@_CFFTF32_vars_InnerCounter,#2
        MOV            @@_CFFTF32_vars_DataPtrInc,#18


ICFFTF32vars1Stages3UpStageLoop:
        ; Load "DataPtrInc" value and initialize XAR3 and XAR7 data pointers:
        MOVZ        AR0,@@_CFFTF32_vars_DataPtrInc
        NOP            *,ARP3
        NOP            *0++,ARP7            ; XAR3 = XAR3 + DataPtrInc
        NOP            *0++,ARP3            ; XAR7 = XAR7 + DataPtrInc
        MOVZ        AR0,@@_CFFTF32_vars_CoefPtrInc
        SUBB        XAR3,#2                ; XAR3 = XAR3 + DataPtrInc - 2
        SUBB        XAR7,#2                ; XAR7 = XAR7 + DataPtrInc - 2

        ; Initialize OuterCounter (AR1):
        MOVZ        AR1,@@_CFFTF32_vars_OuterCounter
        ; Initialize InnerCounter (AL):
        MOV            AL,@@_CFFTF32_vars_InnerCounter

        .align        2
        MOV32        R1H,*++,ARP4        ; XAR3->D2_1
ICFFTF32vars1Stages3UpOuterLoop:
        MOV32        R2H,*0++,ARP3        ; XAR4->COS_1
        MPYF32        R7H,R1H,R2H            ;                : R7H = D2_1*COS_1
        ||MOV32        R0H,*++,ARP5        ; XAR3->D3_1
        MOV32        R3H,*0++,ARP3        ; XAR5->SIN_1
        MPYF32        R6H,R0H,R3H            ;                : R6H = D3_1*SIN_1
        MPYF32        R5H,R1H,R3H            ;                : R5H = D2_1*SIN_1

        RPTB        ICFFTF32vars1Stages3UpInnerLoop,@AL
        ADDF32        R7H,R7H,R6H            ;                : R7H = (D2_1*COS_1 + D3_1*SIN_1)
        ||MOV32        R1H,*++,ARP2        ; XAR3->D2_2
        MPYF32        R6H,R0H,R2H            ;                : R6H = D3_1*COS_1
        ||MOV32        R3H,*++,ARP4        ; XAR2->D0_1
        ADDF32        R4H,R3H,R7H            ;                : R4H = D0_1 + (D2_1*COS_1 + D3_1*SIN_1)
        ||MOV32        R2H,*0++,ARP3        ; XAR4->COS_2
        SUBF32        R6H,R6H,R5H            ;                : R6H = (D3_1*COS_1 - D2_1*SIN_1)
        ||MOV32        R0H,*++,ARP6        ; XAR3->D3_2
        SUBF32        R4H,R3H,R7H            ;                : R4H = D0_1 - (D2_1*COS_1 + D3_1*SIN_1)
        ||MOV32        *++,R4H,ARP2        ; XAR6->D0_1
        MPYF32        R7H,R1H,R2H            ;                : R7H = D2_2*COS_2
        ||MOV32        R3H,*++,ARP7        ; XAR2->D1_1
        ADDF32        R4H,R3H,R6H            ;                : R4H = D1_1 + (D3_1*COS_1 - D2_1*SIN_1)
        ||MOV32        *++,R4H,ARP5        ; XAR7->D2_1
        SUBF32        R5H,R3H,R6H            ;                : R5H = D1_1 - (D3_1*COS_1 - D2_1*SIN_1)
        ||MOV32        R3H,*0++,ARP6        ; XAR5->SIN_2
        MPYF32        R6H,R0H,R3H            ;                : R6H = D3_2*SIN_2
        ||MOV32        *++,R4H,ARP7        ; XAR6->D1_1
        MPYF32        R5H,R1H,R3H            ;                : R5H = D2_2*SIN_2
        ||MOV32        *++,R5H,ARP3        ; XAR7->D3_1
ICFFTF32vars1Stages3UpInnerLoop:

        MOVZ        AR0,@@_CFFTF32_vars_DataPtrInc
        MOVL        XAR4,@@_CFFTF32_vars_CurrentCosPtr
        MOVL        XAR5,@@_CFFTF32_vars_CurrentSinPtr

        ADDF32        R7H,R7H,R6H            ;                : R7H = (D2_2*COS_2 + D3_2*SIN_2)
        ||MOV32        R6H,*--,ARP2        ; XAR3 = XAR3 - 2
        MPYF32        R6H,R0H,R2H            ;                : R6H = D3_2*COS_2
        ||MOV32        R3H,*++,ARP3        ; XAR2->D0_2
        ADDF32        R4H,R3H,R7H            ;                : R4H = D0_2 + (D2_2*COS_2 + D3_2*SIN_2)
        SUBF32        R6H,R6H,R5H            ;                : R6H = (D3_2*COS_2 - D2_2*SIN_2)
        ||MOV32        R5H,*0++,ARP6        ; XAR3 = XAR3 + DataPtrInc
        SUBF32        R4H,R3H,R7H            ;                : R4H = D0_2 - (D2_2*COS_2 + D3_2*SIN_2)
        ||MOV32        *++,R4H,ARP2        ; XAR6->D0_2
        MOV32        R3H,*0++,ARP7        ; XAR2->D1_2, XAR2 = XAR2 + DataPtrInc
        ADDF32        R4H,R3H,R6H            ;                : R4H = D1_2 + (D3_2*COS_2 - D2_2*SIN_2)
        ||MOV32        *++,R4H,ARP3        ; XAR7->D2_2
        SUBF32        R5H,R3H,R6H            ;                : R5H = D1_2 - (D3_2*COS_2 - D2_2*SIN_2)
        ||MOV32        R1H,*++,ARP6        ; XAR3->D2_1
        MOV32        *0++,R4H,ARP7        ; XAR6->D1_2, XAR6 = XAR6 + DataPtrInc
        MOV32        *0++,R5H,ARP4        ; XAR7->D3_2, XAR7 = XAR7 + DataPtrInc
        MOVZ        AR0,@@_CFFTF32_vars_CoefPtrInc
        BANZ        ICFFTF32vars1Stages3UpOuterLoop,AR1--

        ; Calculate new "DataPtrInc" for next stage:    
        ; DataPtrInc = (DataPtrInc * 2) - 2
        ;            =   34     (for Stage 4)
        ;            =   66     (for Stage 5)
        ;            =  130     (for Stage 6)
        ;            =  258     (for Stage 7)
        ;            =  514     (for Stage 8)
        ;            = 1026     (for Stage 9)
        ;            = 2050     (for Stage 10)
        MOV            AL,@@_CFFTF32_vars_DataPtrInc
        LSL            AL,#1
        SUBB        AL,#2
        MOV            @@_CFFTF32_vars_DataPtrInc,AL

        ; Calculate new "CoefPtrInc" for next stage:    
        ; CoefPtrInc = CoefPtrInc / 2
        ;                         Stage:   4   5   6   7   8   9  10
        ; Coef Step For  256-point CFFT:  32  16   8   4   2   -   -
        ; Coef Step For  512-point CFFT:  64  32  16   8   4   2   -
        ; Coef Step For 1024-point CFFT: 128  64  32  16   8   4   2
        MOV            AL,@@_CFFTF32_vars_CoefPtrInc
        LSR            AL,#1
        MOV            @@_CFFTF32_vars_CoefPtrInc,AL

        ; Initialize and swap input and output data pointers for next stage:
        ; XAR2 = CurrentOutPtr  
        ; XAR3 = CurrentOutPtr  (XAR2 and XAR3 point to output data from previous stage calculations)
        ; XAR6 = CurrentInPtr
        ; XAR7 = CurrentInPtr   (XAR6 and XAR7 point to input data from previous stage calculations)
        ; CurrentInPtr  = XAR2
        ; CurrentOutPtr = XAR6  (swap pointers to indicate which is current output buffer)
        MOVL        XAR7,@@_CFFTF32_vars_CurrentInPtr
        MOVL        XAR6,@@_CFFTF32_vars_CurrentInPtr
        MOVL        XAR3,@@_CFFTF32_vars_CurrentOutPtr
        MOVL        XAR2,@@_CFFTF32_vars_CurrentOutPtr
        MOVL        @@_CFFTF32_vars_CurrentInPtr,XAR2
        MOVL        @@_CFFTF32_vars_CurrentOutPtr,XAR6

        ; Calculate new "InnerCounter" value for next stage:
        ; InnerCounter = (InnerCounter + 1) * 2
        ;              =   6 (for Stage 4)
        ;              =  14 (for Stage 5)
        ;              =  30 (for Stage 6)
        ;              =  62 (for Stage 7)
        ;              = 126 (for Stage 8)
        ;              = 254 (for Stage 9)
        ;              = 510 (for Stage 10)
        ; Note: Number of butterfly's executed for Inner Loop = InnerCounter+2
        MOV            AL,@@_CFFTF32_vars_InnerCounter
        ADDB        AL,#1
        LSL            AL,#1
        MOV            @@_CFFTF32_vars_InnerCounter,AL

        ; Calculate new "OuterCounter" value for next stage:
        ; OuterCounter = ((OuterCounter+1) >> 1) - 1
        ;                 256-point : 512-point : 1024-point CFFT 
        ;               =    15          31          63     (for Stage 4)
        ;               =     7          15          31     (for Stage 5)
        ;               =     3           7          15     (for Stage 6)
        ;               =     1           3           7     (for Stage 7)
        ;               =     0           1           3     (for Stage 8)
        ;               =     -           0           1     (for Stage 9)
        ;               =     -           -           0     (for Stage 10)
        ; Note: Number of Outer Loops executed = OUTER_COUNTER + 1
        MOV            AL,@@_CFFTF32_vars_OuterCounter
        ADDB        AL,#1
        LSR            AL,#1
        SUBB        AL,#1
        MOV            @@_CFFTF32_vars_OuterCounter,AL

        DEC            @@_CFFTF32_vars_StageCounter
        BF            ICFFTF32vars1Stages3UpStageLoop,GEQ

        .C28_amode
        CLRC        AMODE

        ;----------------------------------------------------------------------------
        ; Swap the real and imaginary pieces of each output value in memory and scale
        ;----------------------------------------------------------------------------
        
        ; Compute the scaling factor, 1/FFTSize (R2H)
        ; Initialize Swap Loop Counter (AL).  Loop is unrolled once to eliminate delay slots.
        ; AL = (2^Stages >> 1) - 1
        ;    = 127 (execute loop 128 times for  256-point CFFT)
        ;    = 255 (execute loop 256 times for  512-point CFFT)
        ;    = 511 (execute loop 512 times for 1024-point CFFT)
        MOV            T,@_CFFTF32_vars_Stages
        MOVB        ACC,#1
        LSL            ACC,T                ; ACC = (2^Stages)
        MOV32        R2H, ACC            ; R2H = (2^Stages), used to compute scaling factor
        LSR            AL,#1                ; AL = (2^Stages >> 1)
        SUBB        AL,#1                ; AL = (2^Stages) - 1
        NOP                                ; delay slot for MOV32
        NOP                                ; delay slot for MOV32
        I16TOF32    R1H, R2H            ; R1H = (2^Stages) = FFTSize
        NOP

        ; Need to invert R1H.  Use the prescribed FPU division algorithm.
        ; ALGORITHM for Y = 1/B
        ;   Ye1 = Estimate(1/B);
        ;   Ye2 = Ye1*(2.0 - Ye1*B)
        ;     Y = Ye2*(2.0 - Ye2*B)
        EINVF32     R2H, R1H            ; R2H = Ye1 = Estimate(1/B)
        NOP
        MPYF32      R3H, R2H, R1H       ; R3H = Ye1*B
        NOP
        SUBF32      R3H, #2.0, R3H      ; R3H = 2.0 - Ye1*B       
        NOP        
        MPYF32      R2H, R2H, R3H       ; R2H = Ye2 = Ye1*(2.0 - Ye*B)
        NOP
        MPYF32      R3H, R2H, R1H       ; R3H = Ye2*B
        NOP
        SUBF32      R3H, #2.0, R3H      ; R3H = 2.0 - Ye2*B
        NOP
        MPYF32      R2H, R2H, R3H       ; R2H = Y = Ye2*(2.0 - Ye2*B)
        
        ; Do the swap and scaling loop
        ; XAR2 and XAR3 are already pointing to the output array, as left by the IFFT computation.
        ; R2H contains the scaling factor 1/FFTSize that we need to multiply by.
        ; Loop is unrolled once and scrambled to eliminate delay slots for the MPYF32 instructions.
        RPTB        ICFFTF32vars1Stages3UpOutputSwapScaleLoop,@AL
        MOV32        R0H, *XAR2++        ; R0H = re(i)
        MPYF32        R3H, R0H, R2H        ; R3H = scaled re(i)
        MOV32        R1H, *XAR2++        ; R1H = im(i) (delay slot for MPYF32)
        MPYF32        R4H, R1H, R2H        ; R4H = scaled im(i)
        MOV32        R0H, *XAR2++        ; R0H = re(i+1) (delay slot for MPYF32)
        MOV32        *XAR3++, R4H        ; store scaled im(i) to re(i)
        MPYF32        R5H, R0H, R2H        ; R5H = scaled re(i+1)
        MOV32        R1H, *XAR2++        ; R1H = im(i+1) (delay slot for MPYF32)
        MPYF32        R6H, R1H, R2H        ; R6H = scaled im(i+1)
        MOV32        *XAR3++, R3H        ; store scaled re(i) to im(i) (delay slot for MPYF32)
        MOV32        *XAR3++, R6H        ; store scaled im(i+1) to re(i+1)
        MOV32        *XAR3++, R5H        ; store scaled re(i+1) to im(i+1)
ICFFTF32vars1Stages3UpOutputSwapScaleLoop:

        ; Return
        MOV32        R7H,*--SP
        MOV32        R6H,*--SP
        MOV32        R5H,*--SP
        MOV32        R4H,*--SP
        MOV32        R3H,*--SP
        MOV32        R2H,*--SP
        MOV32        R1H,*--SP
        MOV32        R0H,*--SP
        POP            XAR7
        POP            XAR6
        POP            XAR5
        POP            XAR4
        POP            XAR3
        POP            XAR2
        POP            XAR1
        POP            XAR0
        LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
