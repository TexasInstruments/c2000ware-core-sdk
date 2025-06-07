;;*****************************************************************************
;;! \file source/vcu2/vcu2_icfft_64.asm
;;!
;;! \brief  64-pt complex inverse FFT
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
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; FFT Routine defines
NSTAGES             .set    6
NSAMPLES            .set    (1 << NSTAGES)
NSKIP               .set    2*(512 / NSAMPLES) 	 ;vcu0 largest table is stage9 i.e. 512 twiddles(used in unpack)
                                                 ;the 2 in the numerator is for the size of the twiddle in words
STAGE1              .set    1
STAGE3              .set    3
STAGE5              .set    5
STAGE7              .set    7

;; Argument structure defines
ARG_INBUFFER        .set    0
ARG_OUTBUFFER       .set    2
ARG_TFTABLE         .set    4
ARG_NSAMPLES        .set    6
ARG_NSTAGES         .set    7
ARG_TFSKIP          .set    8


;; Stack defines
;;
;;   |_______|
;;   |_______|<- Stack Pointer(SP) <---SP
;;   |_______|<- STK_ARG_PTR  (SP-2)
;;   |_______|<- STK_TFPTR    (SP-4)
;;
LOCAL_FRAME_SIZE    .set    4
STK_ARG_PTR         .set    2
STK_TFPTR		    .set 	4


;;*****************************************************************************
;; macros
;;*****************************************************************************
;;
;; MACRO   : 'ICFFT_CONTEXT_SAVE'
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on entry into FFT routine
;;
ICFFT_CONTEXT_SAVE    .macro
    PUSH      XAR1
    PUSH      XAR2
    PUSH      XAR3
    ADDB      SP, #LOCAL_FRAME_SIZE              ; allocate stack space for local frame
    .endm
;;
;; MACRO   : 'ICFFT_CONTEXT_RESTORE'
;; SIZE    : Number of WORDS/Number of Cycles 14
;; USAGE   : Called on exit from FFT routine
;;
ICFFT_CONTEXT_RESTORE    .macro
    SUBB      SP, #LOCAL_FRAME_SIZE              ; deallocate stack space for local frame
    POP       XAR3
    POP       XAR2
    POP       XAR1
    .endm

    .if  __TI_EABI__
        .asg ICFFT_run64Pt, _ICFFT_run64Pt        
    .endif
;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _ICFFT_run64Pt
	.ref	_vcu0_twiddleFactors
	.ref	_vcu2_twiddleFactors
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;;
;; \brief Calculate the 64 pt Complex Inverse FFT
;;
;; \param Handle to the structure, ICFFT_Obj(passed in XAR4)
;; - *+XAR4[0]:  int16_t *pInBuffer -> input pointer
;; - *+XAR4[2]:  int16_t *pOutBuffer -> work(Output) buffer pointer
;; - *+XAR4[4]:  int16_t *pTwiddleFactors-> twiddle factor table pointer
;; - *+XAR4[6]:  int16_t nSamples-> Number of data points
;; - *+XAR4[7]:  int16_t nStages-> Number of FFT stages
;; - *+XAR4[8]:  int16_t twiddleSkipStep-> Twiddle factor table search step
;;
;; \note
;; - This algorithm works on two buffers of size 2*N(32-bit complex) in ping-pong fashion
;; - N must be a power of 2 for this algorithm
;; - Must be of size N >= 16(2^4)
;; - Assumes CPACK=1 style complex packing i.e. [Lo:Hi] => [Real:Imag], CPACK bit is ignored
;; - Sign extension is automatically done for right shift operations
;; - VSTATUS.RND=1, rounding is done for the right shift operation
;; - OVFR is set if signed overflow is detected for add/sub calculation in which destination is VRxL
;; - OVFI is set if signed overflow is detected for add/sub calculation in which destination is VRxH
;; - 16-bit signed results (before the shift right) are saturated if SAT = 1
;; - Make sure that input and output buffer pointer points to two diffrent
;;   RAM blocks to avoid arbitration between reads and writes
;;
;; \return FFT of the input in the output buffer pointed to by ICFFT_Obj.pOutBuffer
;;
_ICFFT_run64Pt:
    ICFFT_CONTEXT_SAVE
    MOVL       *-SP[STK_ARG_PTR], XAR4

;; Computation Prep
    VSETCPACK                                    ; Set the CPACK bit to 1
    ;SETC      SXM                               ; sign extension mode
                                                 ; ISS says SXM is automatically done so check that it is
    VSATON                                       ; Turn ON Saturation
;;
;; Stages 1 and 2 Combined
;;
;; Notes:
;; - These stages use trivial twiddle factors: 1,-1,j and -j.
;; - C27x AMODE is required in this stage to facilitate the use of
;;   the bit-reversed addressing mode with simultaneous ARP update i.e
;;     VMOV32 mem32,VRx,ARPn
;; - Setting up the bit-reversed index in AR0
;;   Assume N = 64, Since we have complex data its 2N or
;;   128(2^7) words to index i.e. we need 7 bits to address all locations(0-127)
;;   we represent 1 as : b'0000001' -> 0x0001
;;   bit reversed 1 as : b'1000000' -> 0x0040
;;   N represented in hex is already 0x0040, so we load this directly to AR0
;; - Stages 1 and 2 arent affected by the SHR or SHL modifiers, results from all
;;   operations are shifted right by 1 bit
;;
;; Register Usage:
;;   XAR0:         offset address(bit-reversed indexing)
;;   XAR1:         output storage pointer
;;   XAR2:         input pointer
;;
;;                 Stage 1    Stage 2
;; --XAR1,*BR0++---o----*-----o--------*--XAR2++-->
;;                  \  /       \      /
;;                   \/         \    /
;;                   /\          \  /
;;                  /  \          \/
;; --XAR1,*BR0++---o----*-----o---/\---*--XAR2++--->
;;                             \ /  \ /
;;                              \    \
;;                             / \  / \
;; --XAR1,*BR0++---o----*-----o---\/---*--XAR2++-->
;;                  \  /          /\
;;                   \/          /  \
;;                   /\         /    \
;;                  /  \       /      \
;; --XAR1,*BR0++---o----*-----o--------*--XAR2++--->
;;
_ICFFT_run64Pt_stages1and2Combined:

;; local defines
S12_NBFLY           .set (NSAMPLES / (2*2))      ; Number of 2x2 butterflies
S12_LOOP_COUNT      .set S12_NBFLY - 2           ; Stage 1/2 loop count

    MOVZ      AR0,  *+XAR4[ARG_NSAMPLES]         ; AR0 := bit-reversed index 1
    MOVL      XAR2, *+XAR4[ARG_INBUFFER]         ; XAR2 -> input buffer
    MOVL      XAR1, *+XAR4[ARG_OUTBUFFER]        ; XAR1 -> output buffer

    .lp_amode                                    ; override assembler mode to C28x + C2xLP sysntax
    SETC      AMODE                              ; set AMODE to C2xLP addressing

    NOP       *,ARP2                             ; ARP -> XAR2
    VMOV32    VR0, *BR0++                        ; VR0 := *(AR2 bradd AR0++) | VR0 := I0:R0

    VMOV32    VR1, *BR0++                        ; VR1 := *(AR2 bradd AR0++) | VR1 := I1:R1

    VCFFT7    VR1, VR0, #0                       ; VR2 = I2:R2 <- XAR1
 || VMOV32    VR2, *BR0++                        ;[VR0H:VR0L] := [R0 - R1:R0 + R1] :=�[VR0L - VR1L:VR0L + VR1L]
                                                 ;[VR1H:VR1L] := [I0 - I1:I0 + I1] := [VR0H - VR1H:VR0H + VR1H]


    VMOV32    VR3, *BR0++                        ; VR3 := I3:R3 <- XAR1

    VCFFT8    VR3, VR2, #0                       ;[VR2H:VR2L] := [R2 - R3:R2 + R3] :=�[VR2L - VR3L:VR2L + VR3L]
                                                 ;[VR3H:VR3L] := [I2 - I3:I2 + I3] := [VR2H - VR3H:VR2H + VR3H]

    VCFFT9    VR5, VR4, VR3, VR2, VR1, VR0, #0   ;[VR4H:VR4L] := [I0':R0'] :=�[(I0+I1) + (I2+I3):(R0+R1) + (R2+R3)] := [VR1L + VR3L:VR0L + VR2L]
                                                 ;[VR5H:VR5L] := [I2':R2'] := [(I0+I1) - (I2+I3):(R0+R1) - (R2+R3)] := [VR1L � VR3L:VR0L � VR2L]

    .align    2                                  ; align at 32-bit boundary to remove penalty
    RPTB      _ICFFT_run64Pt_stages1and2CombinedLoop, #S12_LOOP_COUNT

    VCFFT10   VR7, VR6, VR3, VR2, VR1, VR0, #0   ; VR0 := I0:R0 <- *(AR2 bradd AR0++)
 || VMOV32    VR0, *BR0++                        ;[VR6H:VR6L] := [I1':R1'] :=�[(I0-I1) - (R2-R3):(R0-R1) + (I2-I3)] := [VR1H � VR2H:VR0H + VR3H]
                                                 ;[VR7H:VR7L] := [I3':R3'] := [(I0-I1) + (R2-R3):(R0-R1) - (I2-I3)] := [VR1H + VR2H:VR0H � VR3H]


    VMOV32    VR1, *BR0++                        ; VR1 := I1:R1 <- *(AR2 bradd AR0++)

    VCFFT7    VR1, VR0, #0                       ; VR2 := I2:R2 <- *(AR2 bradd AR0++)
 || VMOV32    VR2, *BR0++                        ;[VR0H:VR0L] := [R0 - R1:R0 + R1] :=�[VR0L - VR1L:VR0L + VR1L]
                                                 ;[VR1H:VR1L] := [I0 - I1:I0 + I1] := [VR0H - VR1H:VR0H + VR1H]


    VMOV32    VR3, *BR0++                        ; VR3 := I3:R3 <- *(AR2 bradd AR0++)

    VCFFT8    VR3, VR2, #0                       ; Save I0':R0' -> XAR1
 || VMOV32    *XAR1++, VR4                       ;[VR2H:VR2L] := [R2 - R3:R2 + R3] :=�[VR2L - VR3L:VR2L + VR3L]
                                                 ;[VR3H:VR3L] := [I2 - I3:I2 + I3] := [VR2H - VR3H:VR2H + VR3H]

    VMOV32    *XAR1++, VR6                       ; Save I1':R1' -> XAR1
    VCFFT9    VR5, VR4, VR3, VR2, VR1, VR0, #0   ; Save I2':R2' -> XAR1
 || VMOV32    *XAR1++, VR5                       ;[VR4H:VR4L] := [I0':R0'] :=�[(I0+I1) + (I2+I3):(R0+R1) + (R2+R3)] := [VR1L + VR3L:VR0L + VR2L]
                                                 ;[VR5H:VR5L] := [I2':R2'] := [(I0+I1) - (I2+I3):(R0+R1) - (R2+R3)] := [VR1L � VR3L:VR0L � VR2L]

    VMOV32    *++, VR7, ARP2                     ; Save I3':R3' -> XAR1 | ARP -> XAR2
    ;VMOV32    *XAR1++, VR7, ARP2                ; Save I3':R3' -> XAR1 | ARP -> XAR2
                                                 ;this form causes ARP to be XAR1 not XAR2

_ICFFT_run64Pt_stages1and2CombinedLoop:

    VCFFT10   VR7, VR6, VR3, VR2, VR1, VR0, #0   ;[VR6H:VR6L] := [I1':R1'] :=�[(I0-I1) - (R2-R3):(R0-R1) + (I2-I3)] := [VR1H � VR2H:VR0H + VR3H]
                                                 ;[VR7H:VR7L] := [I3':R3'] := [(I0-I1) + (R2-R3):(R0-R1) - (I2-I3)] := [VR1H + VR2H:VR0H � VR3H]

    VMOV32    *XAR1++, VR4                       ; Save I0':R0' -> XAR1
    VMOV32    *XAR1++, VR6                       ; Save I1':R1' -> XAR1
    VMOV32    *XAR1++, VR5                       ; Save I2':R2' -> XAR1
    VMOV32    *XAR1++, VR7                       ; Save I3':R3' -> XAR1

_ICFFT_run64Pt_stages1and2CombinedEnd:
    .c28_amode                                   ; change the assembler mode back to C28x
    CLRC      AMODE                              ; set AMODE back to C28x addressing
                                                 ; C28_AMODE allows *XARn[#3bit] addressing
;;=============================================================================
;;
;; Stages 3 and 4 Combined
;;
;; Notes:
;; - These stages will use twiddle factors from the table, which are organized
;;   as follows. Twiddles for stages 3 and 4 are interleaved
;;   exp(2*pi*k1/N3) , k1 = {0,1,...N3/2-1}, N3 = 2^3
;;   exp(2*pi*k2/N4) , k2 = {0,1,...N3/2-1}, N4 = 2^4
;;      Cos(2*pi*  0/  8) : Sin(2*pi*  0/  8)
;;      Cos(2*pi*  0/ 16) : Sin(2*pi*  0/ 16)
;;      Cos(2*pi*  1/  8) : Sin(2*pi*  1/  8)
;;      Cos(2*pi*  1/ 16) : Sin(2*pi*  1/ 16)
;;      Cos(2*pi*  2/  8) : Sin(2*pi*  2/  8)
;;      Cos(2*pi*  2/ 16) : Sin(2*pi*  2/ 16)
;;      Cos(2*pi*  3/  8) : Sin(2*pi*  3/  8)
;;      Cos(2*pi*  3/ 16) : Sin(2*pi*  3/ 16)
;;
;; - Stages 3 and 4 are affected by the SHR or SHL modifiers, results from all
;;   operations are shifted right by SHR or left by SHL values
;; - XAR2, the output buffer from the previous stage is now the input to this stage
;;
;; Register Usage:
;;   XAR0:         butterfly lower ouput storage offset
;;   XAR1:         butterfly lower input storage offset
;;   XAR2:         pointer to even inputs(output of previous stage)
;;   XAR3:         pointer to twiddle factors
;;   XAR4:         pointer to odd inputs(output of previous stage)
;;   XAR5:         loop variable
;;   XAR6:         pointer to even outputs
;;   XAR7:         pointer to odd outputs
;;
;;                    Stage n        Stage n+1
;; --XAR2-------------o----*---------o--------*------XAR6--->
;;                     \  /           \      /
;;                      \/             \    /
;;                      /\              \  /
;;                     /  \              \/
;; --XAR2[AR1]---XAR3-o----*---------o---/\---*--XAR6[AR0]--->
;;                                    \ /  \ /
;;                                     \    \
;;                                    / \  / \
;; --XAR4-------------o----*---XAR3--o---\/---*------XAR7--->
;;                     \  /              /\
;;                      \/              /  \
;;                      /\             /    \
;;                     /  \           /      \
;; --XAR4[AR1]---XAR3-o----*---XAR3--o--------*--XAR7[AR0]--->
;;
_ICFFT_run64Pt_stages3and4Combined:

;; local defines
S34_INPUT_OFFSET     .set  ARG_OUTBUFFER
S34_OUTPUT_OFFSET    .set  ARG_INBUFFER

S34_NBFLYS           .set  1<<(STAGE3-1)         ; Number of butterflys per group (2^(s-1))
S34_NGROUPS          .set  NSAMPLES/(2*S34_NBFLYS)
                                                 ; Number of groups for this stage
S34_INSEP            .set  2*(S34_NBFLYS)        ; Input Seperation = (NBFLYs) * 2(size of complex inputs)
S34_OUTSEP           .set  S34_INSEP-2           ; Output Seperation
S34_GROUPSEP         .set  4*S34_NBFLYS          ; Seperation between the groups =  NBFLYs * 2(inputs per butterfly) * 2(size of complex inputs)
S34_TFOFFSET         .set  0                     ; Twiddle factor table offset for stages 3 and 4
S56_TFOFFSET         .set  S34_TFOFFSET+4*S34_NBFLYS
                                                 ; Twiddle factor table offset for stages 5 and 6

S34_INNER_LOOP_COUNT .set  S34_NBFLYS-2          ; Repeat over the number of butterflies-2(last bfly done outside the loop, RPTB loops n+1 times)
S34_OUTER_LOOP_COUNT .set  NSAMPLES/(4*S34_NBFLYS) - 1
                                                 ; Outer loop count = N/(2(inputs per bfly)*2(words/input)*NBFLYS) - 1
S34_POST_INCREMENT   .set 2*3*S34_NBFLYS         ; Post-increment for all the data pointers

    VSETSHR   #15                                ; SHR=15, does Q30 to Q15 conversion for VCFFTx Multiplications
    VRNDON                                       ; RND=1, turns on rounding during conversion from Q30 to Q15
    ;VSATON                                       ; Turn ON Saturation

;;                               XAR2                                                    XAR6
;; ---+-+----o--*---+----o-----*-----++-o-----------*--------o-----------------------*--+----------+-->>
;;  G1| 2     \/    |     \   /      ||  \         /          \                     /   .          |
;;    | |     /\    |      \ /       ||   \       /            \                   /    .XAR6++    |
;; ---+-v----o--*---|----o--X--*-----||-o--\-----/--*--------o--------------------/--*--+----------|-->>
;;                  4     \/ \/      ||  \  \   /  /          \  \               /  /   |          |
;;                  |     /\ /\      8|   \  \ /  /            \  \             /  /    |          |
;; ---+------o--*---v----o--X--*-----||-o--\--X--/--*--------o--\--------------/--/--*--6----------|-->>
;;  G2|       \/           / \       A|  \  \/ \/  /          \  \  \         /  /  /   |          |
;;    |       /\          /   \      R|   \ /\ /\ /            \  \  \       /  /  /    A          |
;; ---+------o--*--------o-----*-----1|-o--X--X--X--*--------o--\--\--------/--/--/--*--R----------|-->>
;;                                   ||  \/ \/ \/ \/          \  \  \  \   /  /  /  /   0          |
;;                          XAR2[AR1]||  /\ /\ /\ /\           \  \  \  \ /  /  /  /    |XAR6[AR0] |
;; ---+------o--*--------o-----*-----v|-o--X--X--X--*--------o--\--\--\--X--/--/--/--*--v----------|-->>
;;  G3|       \/          \   /       |   / \/ \/ \           \  \  \  \/ \/  /  /  /              |
;;    |       /\           \ /       16  /  /\ /\  \           \  \  \ /\ /\ /  /  /               16
;; ---+------o--*--------o--X--*------|-o--/--X--\--*--------o--\--\--X--X--X--/--/--*-------------|-->>
;;                        \/ \/       |   /  / \  \           \  \  \/ \/ \/ \/  /  /              |
;;                        /\ /\       |  /  /   \  \           \  \ /\ /\ /\ /\ /  /               |
;; ---+------o--*--------o--X--*------|-o--/-----\--*--------o--\--X--X--X--X--X--/--*-------------|-->>
;;  G4|       \/           / \        |   /       \           \  \/ \/ \/ \/ \/ \/  /              |
;;    |       /\          /   \       |  /         \           \ /\ /\ /\ /\ /\ /\ /               |
;; ---+------o--*--------o-----*------|-o-----------*--------o--X--X--X--X--X--X--X--*-------------|-->>
;;                                    |                       \/ \/ \/ \/ \/ \/ \/ \/              |
;;                               XAR4 |                       /\ /\ /\ /\ /\ /\ /\ /\    XAR7      |
;; ---+-+----o--*---+----o-----*-----+v-o-----------*--------o--X--X--X--X--X--X--X--*--+----------v-->>
;;  G5| 2     \/    |     \   /      |   \         /           / \/ \/ \/ \/ \/ \/ \    .
;;    | |     /\    |      \ /       |    \       /           /  /\ /\ /\ /\ /\ /\  \   .XAR7++
;; ---+-v----o--*---|----o--X--*-----|--o--\-----/--*--------o--/--X--X--X--X--X--\--*--+------------->>
;;                  4     \/ \/      |   \  \   /  /           /  / \/ \/ \/ \/ \  \    |
;;                  |     /\ /\      8    \  \ /  /           /  /  /\ /\ /\ /\  \  \   6
;; ---+------o--*---v----o--X--*-----|--o--\--X--/--*--------o--/--/--X--X--X--\--\--*--|------------->>
;;  G6|       \/           / \       A   \  \/ \/  /           /  /  / \/ \/ \  \  \    A
;;    |       /\          /   \      R    \ /\ /\ /           /  /  /  /\ /\  \  \  \   R
;; ---+------o--*--------o-----*-----1--o--X--X--X--*--------o--/--/--/--X--\--\--\--*--0------------->>
;;                                   |   \/ \/ \/ \/           /  /  /  / \  \  \  \    |
;;                          XAR4[AR1]|   /\ /\ /\ /\          /  /  /  /   \  \  \  \   |XAR7[AR0]
;; ---+------o--*--------o-----*-----v--o--X--X--X--*--------o--/--/--/-----\--\--\--*--v------------->>
;;  G7|       \/          \   /           / \/ \/ \            /  /  /       \  \  \
;;    |       /\           \ /           /  /\ /\  \          /  /  /         \  \  \
;; ---+------o--*--------o--X--*--------o--/--X--\--*--------o--/--/-----------\--\--*---------------->>
;;                        \/ \/           /  / \  \            /  /             \  \
;;                        /\ /\          /  /   \  \          /  /               \  \
;; ---+------o--*--------o--X--*--------o--/-----\--*--------o--/-----------------\--*---------------->>
;;  G8|       \/           / \            /       \            /                   \
;;    |       /\          /   \          /         \          /                     \
;; ---+------o--*--------o-----*--------o-----------*--------o-----------------------*---------------->>
;;           S1            S2                S3                         S4


    ;;-------------------------------------------------------------------------
    ;; This pointer points to the begining of the input data array at
    ;; the begining of every s & s+1 stage calculation.
    ;; Note that previous stage's output array is input for this stage
    ;MOVL      XAR4, *-SP[STK_ARG_PTR]           ; Restore the pointer argument to XAR4
                                                 ; XAR4 is not used in stage 1 & 2
    MOVL      XAR2, *+XAR4[S34_INPUT_OFFSET]     ; XAR2 -> I0:R0 pointer
    ;;-------------------------------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;; For stage s & s+1
    ;; These are the separation index for inputs and outputs
    ;;  input_separation = 2* 2^(s-1)
    ;;  For Stage 3 & 4, input_separation = 2 * 2^(3-1) = 8
    ;;  For Stage 5 & 6, input_separation = 2 * 2^(5-1) = 32
    ;;  For Stage 7 & 8, input_separation = 2 * 2^(7-1) = 128
    ;; And so on ....
    MOVL      XAR1, #S34_INSEP

    ;; ar0 is added with an XARn pointer which is post incremented (+2)
    ;; and hence ar0 = xar1-2
    MOVL      XAR0, #S34_OUTSEP
    ;;-------------------------------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;;This pointer points to the begining of the 1st output of the combined
    ;; s & s+1 stage butterfly. Note that the input buffer of the previous
    ;; stage is used as output buffer for this stage due to ping-pong scheme
    MOVL      XAR6, *+XAR4[S34_OUTPUT_OFFSET]    ; XAR6 -> first output
                                                 ; I0'':R0'' pointer
    ;;-------------------------------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;;This pointer points to the 3rd output of the combined s & s+1 stage butterfly.
    ;;This pointer should be initialized as below
    ;;For Stage 3 & 4 = 2 * 2 * 2^(3-1) = 16
    ;;For Stage 5 & 6 = 2 * 2 * 2^(5-1) = 64
    ;;For Stage 7 & 8 = 2 * 2 * 2^(7-1) = 256
    ;;And so on ...
    MOVL      XAR7, XAR6
    ADDB      XAR7, #S34_GROUPSEP                ; I2'':R2'' pointer
    ;;-------------------------------------------------------------------------

    ;;--------------------------------------------------
    ;;Initialize this pointer to the begining of the twiddle-factor
    ;;table for stage s & s+1
    ;;For Stage 3 & 4: 0 to  [0 + 4 * 2^(3-1) - 1] = 0 to 15
    ;;For Stage 5 & 6: 16 to  [16 + 4 * 2^(5-1) - 1] = 16 to 79
    ;;For Stage 7 & 8: 80 to [80 + 4 * 2^(7-1) - 1] = 80 to 335
    ;;And so on ....
    MOVL      XAR3, #_vcu2_twiddleFactors
    ;;ADDB      XAR3, #S34_TFOFFSET
    MOVL	  *-SP[STK_TFPTR], XAR3
    ;;--------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;; This pointer points to the begining of the 2nd set of butterflies used in
    ;; the 1st of the combined stages
    ;; Second Butterfly offset for stage s & s+1
    ;;  = 2 * input_separation = 2 * 2 * 2^(s-1)
    ;;  For Stage 3 & 4 = 2 * 2 * 2^(3-1) = 16
    ;;  For Stage 5 & 6 = 2 * 2 * 2^(5-1) = 64
    ;;  For Stage 7 & 8 = 2 * 2 * 2^(7-1) = 256
    ;; And so on ...
    ;;
    MOVL      XAR4, XAR2
    ADDB      XAR4, #S34_GROUPSEP                ; I2:R2 pointer
    ;;-------------------------------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;;Outer loop
    ;; For Stage s & s+1, combined
    ;; no_of_inner_but = 2^(s-1) = 2^(3-1) = 4
    ;; no_of_outer_loop = size/(2*no_of_inner_but*2)-1 = 64/(2*4*2) = 4-1 = 3
    MOVL      XAR5, #S34_OUTER_LOOP_COUNT        ; Initialize outer loop counter
                                                 ; used in BANZ
    ;;-------------------------------------------------------------------------

_ICFFT_run64Pt_stages3and4OuterLoop:

	MOVL	  XAR3, *-SP[STK_TFPTR]			     ; Reset the twiddle factor table pointer

    ;.lp_amode                                   ; override assembler mode to C28x + C2xLP sysntax
    ;SETC      AMODE                             ; set AMODE to C2xLP addressing

    ; Inner Butterfly Loop
    VMOV32    VR5, *+XAR4[AR1]                   ; VR5 = I3:R3
    VMOV32    VR6, *+XAR2[AR1]                   ; VR6 = I1:R1
    VMOV32    VR7, *XAR4++                       ; VR7 = I2:R2
    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(1):Cos(1)
    VCFFT1    VR2, VR5, VR4                      ;[VR2H:VR2L] = [I3*Cos(1) - R3*Sin(1): R3*Cos(1) + I3*Sin(1)]

    VMOV32    VR5, *XAR2++                       ; VR5 = I0:R0
    VCFFT2    VR7, VR6, VR4, VR2, VR1, VR0, #0   ;[VR2H:VR2L] = [I1*Cos(1) - R1*Sin(1): R1*Cos(1) + I1*Sin(1)]
                                                 ;[VR0H:VR0L] = [I2':R2'] = [I2 + VR2H : R2 + VR2L]
                                                 ;[VR1H:VR1L] = [I3':R3'] = [I2 - VR2H : R2 - VR2L]

    .align    2                                  ; align at 32-bit boundary to remove penalty
    RPTB      _ICFFT_run64Pt_stages3and4InnerLoop, #S34_INNER_LOOP_COUNT
    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(2):Cos(2)
    VCFFT3    VR5, VR4, VR3, VR2, VR0, #0        ; VR5 = I3:R3
 || VMOV32    VR5, *+XAR4[AR1]                   ;[VR2H:VR2L] = [I2'*Cos(2) - R2'*Sin(2): R2'*Cos(2) + I2'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0':R0'] = [I0 + VR2H : R0 + VR2L]
                                                 ;[VR3H:VR3L] = [I1':R1'] = [I0 - VR2H : R0 - VR2L]

    VMOV32    VR6, *+XAR2[AR1]                   ; VR6 = I1:R1
    VCFFT4    VR4, VR2, VR1, VR0, #0             ; VR7 = I2:R2
 || VMOV32    VR7,  *XAR4++                      ;[VR2H:VR2L] = [R3'*Cos(2) + I3'*Sin(2): I3'*Cos(2) - R3'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0'':R0'�] = [I0' + VR2H: R0' + VR2L]
                                                 ;[VR1H:VR1L] = [I2'':R2'�] = [I0' - VR2H: R0' - VR2L]

    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(1):Cos(1)
    VMOV32    *XAR6++, VR0                       ; [I0'':R0''] = VR0

    VCFFT5    VR5, VR4, VR3, VR2, VR1, VR0, #0   ;[I2'':R2''] = VR1
 || VMOV32    *XAR7++, VR1                       ;[VR2H:VR2L] = [I3*Cos(1) - R3*Sin(1):R3*Cos(1) + I3*Sin(1)]
                                                 ;[VR0H:VR0L] = [I1'�:R1'�] = [I1' - VR2H: R1' + VR2L]
                                                 ;[VR1H:VR1L] = [I3'�:R3'�] = [I1' + VR2H: R1' - VR2L]
    VMOV32    VR5, *XAR2++                       ; VR5 = I0:R0
    VMOV32    *+XAR6[AR0], VR0                   ;[I1'':R1''] = VR0

    VCFFT2    VR7, VR6, VR4, VR2, VR1, VR0, #0   ;[I3'':R3''] = VR1
 || VMOV32    *+XAR7[AR0], VR1                   ;[VR2H:VR2L] = [I1*Cos(1) - R1*Sin(1):R1*Cos(1) + I1*Sin(1)]
                                                 ;[VR0H:VR0L] = [I2':R2'] = [I2 + VR2H: R2 + VR2L]
                                                 ;[VR1H:VR1L] = [I3':R3'] = [I2 - VR2H: R2 - VR2L]
_ICFFT_run64Pt_stages3and4InnerLoop:

    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(2):Cos(2)
    VCFFT3    VR5, VR4, VR3, VR2, VR0, #0        ;[VR2H:VR2L] = [I2'*Cos(2) - R2'*Sin(2):R2'*Cos(2) + I2'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0':R0'] = [I0 + VR2H: R0 + VR2L]
                                                 ;[VR1H:VR1L] = [I1':R1'] = [I0 - VR2H: R0 - VR2L]

    NOP
    VCFFT4    VR4, VR2, VR1, VR0, #0             ;[VR2H:VR2L] = [R3'*Cos(2) + I3'*Sin(2):I3'*Cos(2) - R3'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0'�:R0'�] = [I0' + VR2H: R0' + VR2L]
                                                 ;[VR1H:VR1L] = [I2'':R2''] = [I0' - VR2H: R0' - VR2L]

    NOP
    VMOV32    *XAR6++, VR0                       ;[I0'':R0''] = VR0
    VCFFT6    VR3, VR2, VR1, VR0, #0             ;[I2'':R2''] = VR1
 || VMOV32    *XAR7++, VR1                       ;[VR0H:VR0L] = [I1'':R1'�] = [I1' - VR2H: R1' + VR2L]
                                                 ;[VR1H:VR1L] = [I3'':R3''] = [I1' + VR2H: R1' - VR2L]

    NOP
    VMOV32    *+XAR6[AR0], VR0                   ;[I1'':R1''] = VR0
    VMOV32    *+XAR7[AR0], VR1                   ;[I3'':R3''] = VR1

    ;;--------------------------------------------------
    ;;Increment all these pointers with 2 * 3*2^(s-1)
    ;;for Stage 3 & 4, increment by 2 * 3 * 2^(3-1) = 24
    ;;for Stage 5 & 6, increment by 2 * 3 * 2^(5-1) = 96
    ;;for Stage 7 & 8, increment by 2 * 3 * 2^(7-1) = 384

    ADDB      XAR2, #S34_POST_INCREMENT
    ADDB      XAR4, #S34_POST_INCREMENT
    ADDB      XAR6, #S34_POST_INCREMENT
    ADDB      XAR7, #S34_POST_INCREMENT
    ;;--------------------------------------------------

    BANZ      _ICFFT_run64Pt_stages3and4OuterLoop, AR5--

_ICFFT_run64Pt_stages3and4CombinedEnd:
    ;.c28_amode                                  ; change the assembler mode back to C28x
    ;CLRC      AMODE                             ; set AMODE back to C28x addressing
                                                 ; C28_AMODE allows *XARn[#3bit] addressing
                                                 ; Stage 1 & 2 require AMODE others dont
;;=============================================================================
;;
;; Stages 5 and 6 Combined
;;
;; Notes:
;; - These stages will use twiddle factors from the table, which are organized
;;   as follows. Twiddles for stages 5 and 6 are interleaved
;;   exp(2*pi*k1/N5) , k1 = {0,1,...N5/2-1}, N5 = 2^5
;;   exp(2*pi*k2/N6) , k2 = {0,1,...N5/2-1}, N6 = 2^6
;; - Stages 5 and 6 are affected by the SHR or SHL modifiers, results from all
;;   operations are shifted right by SHR or left by SHL values
;; - XAR2, the pointer to the inputs, now points back to the input table
;;
;; Register Usage:
;;   XAR0:         butterfly lower ouput storage offset
;;   XAR1:         butterfly lower input storage offset
;;   XAR2:         pointer to even inputs(output of previous stage)
;;   XAR3:         pointer to twiddle factors
;;   XAR4:         pointer to odd inputs(output of previous stage)
;;   XAR5:         loop variable
;;   XAR6:         pointer to even outputs
;;   XAR7:         pointer to odd outputs
;;
;;                    Stage n        Stage n+1       x(0)         x(n), n = {1, N-1}
;; --XAR2-------------o----*---------o--------*------XAR6--------XAR7[AR0]---------->
;;                     \  /           \      /                         ^    
;;                      \/             \    /                          |        
;;                      /\              \  /                           AR0 = 2*AR0
;;                     /  \              \/                                
;; --XAR2[AR1]---XAR3-o----*---------o---/\---*--XAR7[AR0]-------XAR6[AR0]---------->
;;                                    \ /  \ /                             
;;                                     \    \                              
;;                                    / \  / \                             
;; --XAR4-------------o----*---XAR3--o---\/---*------XAR7--------XAR7-- ------------>
;;                     \  /              /\                                
;;                      \/              /  \                               
;;                      /\             /    \                              
;;                     /  \           /      \                             
;; --XAR4[AR1]---XAR3-o----*---XAR3--o--------*--XAR6[AR0]-------XAR6-- ------------>
;;
_ICFFT_run64Pt_stages5and6Combined:

;; local defines
S56_INPUT_OFFSET     .set  ARG_INBUFFER
S56_OUTPUT_OFFSET    .set  ARG_OUTBUFFER

S56_NBFLYS           .set  1<<(STAGE5-1)         ; Number of butterflys per group (2^(s-1))
S56_NGROUPS          .set  NSAMPLES/(2*S56_NBFLYS)
                                                 ; Number of groups for this stage
S56_INSEP            .set  2*(S56_NBFLYS)        ; Input Seperation = (NBFLYs) * 2(size of complex inputs)
S56_OUTSEP           .set  S56_INSEP             ; Output Seperation
S56_GROUPSEP         .set  4*S56_NBFLYS          ; Seperation between the groups =  NBFLYs * 2(inputs per butterfly) * 2(size of complex inputs)
S78_TFOFFSET         .set  S56_TFOFFSET+4*S56_NBFLYS
                                                 ; Twiddle factor table offset for stages 7 and 8

S56_INNER_LOOP_COUNT .set  S56_NBFLYS-3          ; Repeat over the number of butterflies-2(first + last bfly done outside the loop, RPTB loops n+1 times)
S56_OUTER_LOOP_COUNT .set  NSAMPLES/(4*S56_NBFLYS) - 1
                                                 ; Outer loop count = N/(2(inputs per bfly)*2(words/input)*NBFLYS) - 1
S56_POST_INCREMENT   .set 2*3*S56_NBFLYS         ; Post-increment for all the data pointers

                                                 ; Set once in stage 3 & 4, dont set again
    ;VSETSHR   #15                               ; SHR=15, does Q30 to Q15 conversion for VCFFTx Multiplications
    ;VRNDON                                      ; RND=1, turns on rounding during conversion from Q30 to Q15
    ;VSATON                                      ; Turn ON Saturation

    ;;-------------------------------------------------------------------------
    ;; This pointer points to the begining of the input data array at
    ;; the begining of every s & s+1 stage calculation.
    ;; Note that previous stage's output array is input for this stage
    MOVL      XAR4, *-SP[STK_ARG_PTR]            ; Restore the pointer argument to XAR4
    MOVL      XAR2, *+XAR4[S56_INPUT_OFFSET]     ; XAR2 -> I0:R0 pointer
    ;;-------------------------------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;; For stage s & s+1
    ;; These are the separation index for inputs and outputs
    ;;  input_separation = 2* 2^(s-1)
    ;;  For Stage 3 & 4, input_separation = 2 * 2^(3-1) = 8
    ;;  For Stage 5 & 6, input_separation = 2 * 2^(5-1) = 32
    ;;  For Stage 7 & 8, input_separation = 2 * 2^(7-1) = 128
    ;; And so on ....
    MOVL      XAR1, #S56_INSEP

    ;; ar0 is added with an XARn pointer which is post incremented (+2)
    ;; and hence ar0 = xar1-2
    MOVL      XAR0, #S56_OUTSEP
    ;;-------------------------------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;;This pointer points to the begining of the 1st output of the combined
    ;; s & s+1 stage butterfly. Note that the input buffer of the previous
    ;; stage is used as output buffer for this stage due to ping-pong scheme
    MOVL      XAR6, *+XAR4[S56_OUTPUT_OFFSET]    ; XAR6 -> first output
                                                 ; I0'':R0'' pointer
    ;;-------------------------------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;;This pointer points to the 3rd output of the combined s & s+1 stage butterfly.
    ;;This pointer should be initialized as below
    ;;For Stage 3 & 4 = 2 * 2 * 2^(3-1) = 16
    ;;For Stage 5 & 6 = 2 * 2 * 2^(5-1) = 64
    ;;For Stage 7 & 8 = 2 * 2 * 2^(7-1) = 256
    ;;And so on ...
    MOVL      XAR7, XAR6
    ADDB      XAR7, #S56_GROUPSEP                ; I2'':R2'' pointer
    ;;-------------------------------------------------------------------------

    ;;--------------------------------------------------
    ;;Initialize this pointer to the begining of the twiddle-factor
    ;;table for stage s & s+1
    ;;For Stage 3 & 4: 0 to  [0 + 4 * 2^(3-1) - 1] = 0 to 15
    ;;For Stage 5 & 6: 16 to  [16 + 4 * 2^(5-1) - 1] = 16 to 79
    ;;For Stage 7 & 8: 80 to [80 + 4 * 2^(7-1) - 1] = 80 to 335
    ;;And so on ....
    MOVL      XAR3, #_vcu2_twiddleFactors
    ADDB      XAR3, #S56_TFOFFSET
    MOVL	  *-SP[STK_TFPTR], XAR3
    ;;--------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;; This pointer points to the begining of the 2nd set of butterflies used in
    ;; the 1st of the combined stages
    ;; Second Butterfly offset for stage s & s+1
    ;;  = 2 * input_separation = 2 * 2 * 2^(s-1)
    ;;  For Stage 3 & 4 = 2 * 2 * 2^(3-1) = 16
    ;;  For Stage 5 & 6 = 2 * 2 * 2^(5-1) = 64
    ;;  For Stage 7 & 8 = 2 * 2 * 2^(7-1) = 256
    ;; And so on ...
    ;;
    MOVL      XAR4, XAR2
    ADDB      XAR4, #S56_GROUPSEP                ; I2:R2 pointer
    ;;-------------------------------------------------------------------------

    ;;-------------------------------------------------------------------------
    ;;Outer loop
    ;; For Stage s & s+1, combined
    ;; no_of_inner_but = 2^(s-1) = 2^(3-1) = 4
    ;; no_of_outer_loop = size/(2*no_of_inner_but*2)-1 = 64/(2*16*2) = 1-1 = 0
    ;  MOVL XAR5, #S56_OUTER_LOOP_COUNT          ; Initialize outer loop counter
                                                 ; used in BANZ
                                                 ; not required here
    ;;-------------------------------------------------------------------------

_ICFFT_run64Pt_stages5and6OuterLoop:

	MOVL	  XAR3, *-SP[STK_TFPTR]			     ; Reset the twiddle factor table pointer

    ;.lp_amode                                   ; override assembler mode to C28x + C2xLP sysntax
    ;SETC      AMODE                             ; set AMODE to C2xLP addressing

    ; Inner Butterfly Loop
    VMOV32    VR5, *+XAR4[AR1]                   ; VR5 = I3:R3
    VMOV32    VR6, *+XAR2[AR1]                   ; VR6 = I1:R1
    VMOV32    VR7, *XAR4++                       ; VR7 = I2:R2
    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(1):Cos(1)
    VCFFT1    VR2, VR5, VR4                      ;[VR2H:VR2L] = [I3*Cos(1) - R3*Sin(1): R3*Cos(1) + I3*Sin(1)]

    VMOV32    VR5, *XAR2++                       ; VR5 = I0:R0
    VCFFT2    VR7, VR6, VR4, VR2, VR1, VR0, #0   ;[VR2H:VR2L] = [I1*Cos(1) - R1*Sin(1): R1*Cos(1) + I1*Sin(1)]
                                                 ;[VR0H:VR0L] = [I2':R2'] = [I2 + VR2H : R2 + VR2L]
                                                 ;[VR1H:VR1L] = [I3':R3'] = [I2 - VR2H : R2 - VR2L]

    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(2):Cos(2)
    VCFFT3    VR5, VR4, VR3, VR2, VR0, #0        ; VR5 = I3:R3
 || VMOV32    VR5, *+XAR4[AR1]                   ;[VR2H:VR2L] = [I2'*Cos(2) - R2'*Sin(2): R2'*Cos(2) + I2'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0':R0'] = [I0 + VR2H : R0 + VR2L]
                                                 ;[VR3H:VR3L] = [I1':R1'] = [I0 - VR2H : R0 - VR2L]

    VMOV32    VR6, *+XAR2[AR1]                   ; VR6 = I1:R1
    VCFFT4    VR4, VR2, VR1, VR0, #0             ; VR7 = I2:R2
 || VMOV32    VR7,  *XAR4++                      ;[VR2H:VR2L] = [R3'*Cos(2) + I3'*Sin(2): I3'*Cos(2) - R3'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0'':R0'�] = [I0' + VR2H: R0' + VR2L]
                                                 ;[VR1H:VR1L] = [I2'':R2'�] = [I0' - VR2H: R0' - VR2L]
	NOP


    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(1):Cos(1)
    VMOV32    *+XAR6[0], VR0                     ; [I0'':R0''] = VR0

    VCFFT5    VR5, VR4, VR3, VR2, VR1, VR0, #0   ;[I2'':R2''] = VR1
 || VMOV32    *+XAR7[0], VR1                     ;[VR2H:VR2L] = [I3*Cos(1) - R3*Sin(1):R3*Cos(1) + I3*Sin(1)]
                                                 ;[VR0H:VR0L] = [I1'�:R1'�] = [I1' - VR2H: R1' + VR2L]
                                                 ;[VR1H:VR1L] = [I3'�:R3'�] = [I1' + VR2H: R1' - VR2L]
	NOP


    VMOV32    VR5, *XAR2++                       ; VR5 = I0:R0
    VMOV32    *+XAR7[AR0], VR0                   ;[I1'':R1''] = VR0

    VCFFT2    VR7, VR6, VR4, VR2, VR1, VR0, #0   ;[I3'':R3''] = VR1
 || VMOV32    *+XAR6[AR0], VR1                   ;[VR2H:VR2L] = [I1*Cos(1) - R1*Sin(1):R1*Cos(1) + I1*Sin(1)]
                                                 ;[VR0H:VR0L] = [I2':R2'] = [I2 + VR2H: R2 + VR2L]
                                                 ;[VR1H:VR1L] = [I3':R3'] = [I2 - VR2H: R2 - VR2L]
	ADDB      XAR6, #S56_OUTSEP                  ; XAR6 += S56_OUTSEP
	ADDB      XAR0, #(S56_OUTSEP-2)              ; AR0 := AR0 + S56_OUTSEP-2(double the offset)

    .align    2                                  ; align at 32-bit boundary to remove penalty
    RPTB      _ICFFT_run64Pt_stages5and6InnerLoop, #S56_INNER_LOOP_COUNT
    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(2):Cos(2)
    VCFFT3    VR5, VR4, VR3, VR2, VR0, #0        ; VR5 = I3:R3
 || VMOV32    VR5, *+XAR4[AR1]                   ;[VR2H:VR2L] = [I2'*Cos(2) - R2'*Sin(2): R2'*Cos(2) + I2'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0':R0'] = [I0 + VR2H : R0 + VR2L]
                                                 ;[VR3H:VR3L] = [I1':R1'] = [I0 - VR2H : R0 - VR2L]

    VMOV32    VR6, *+XAR2[AR1]                   ; VR6 = I1:R1
    VCFFT4    VR4, VR2, VR1, VR0, #0             ; VR7 = I2:R2
 || VMOV32    VR7,  *XAR4++                      ;[VR2H:VR2L] = [R3'*Cos(2) + I3'*Sin(2): I3'*Cos(2) - R3'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0'':R0'�] = [I0' + VR2H: R0' + VR2L]
                                                 ;[VR1H:VR1L] = [I2'':R2'�] = [I0' - VR2H: R0' - VR2L]
	NOP


    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(1):Cos(1)
    VMOV32    *+XAR7[AR0], VR0                   ; [I0'':R0''] = VR0

    VCFFT5    VR5, VR4, VR3, VR2, VR1, VR0, #0   ;[I2'':R2''] = VR1
 || VMOV32    *--XAR7, VR1                       ;[VR2H:VR2L] = [I3*Cos(1) - R3*Sin(1):R3*Cos(1) + I3*Sin(1)]
                                                 ;[VR0H:VR0L] = [I1'�:R1'�] = [I1' - VR2H: R1' + VR2L]
                                                 ;[VR1H:VR1L] = [I3'�:R3'�] = [I1' + VR2H: R1' - VR2L]
	NOP


    VMOV32    VR5, *XAR2++                       ; VR5 = I0:R0
    VMOV32    *+XAR6[AR0], VR0                   ;[I1'':R1''] = VR0

    VCFFT2    VR7, VR6, VR4, VR2, VR1, VR0, #0   ;[I3'':R3''] = VR1
 || VMOV32    *--XAR6, VR1                       ;[VR2H:VR2L] = [I1*Cos(1) - R1*Sin(1):R1*Cos(1) + I1*Sin(1)]
                                                 ;[VR0H:VR0L] = [I2':R2'] = [I2 + VR2H: R2 + VR2L]
                                                 ;[VR1H:VR1L] = [I3':R3'] = [I2 - VR2H: R2 - VR2L]
_ICFFT_run64Pt_stages5and6InnerLoop:

    VMOV32    VR4, *XAR3++                       ; VR4 = Sin(2):Cos(2)
    VCFFT3    VR5, VR4, VR3, VR2, VR0, #0        ;[VR2H:VR2L] = [I2'*Cos(2) - R2'*Sin(2):R2'*Cos(2) + I2'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0':R0'] = [I0 + VR2H: R0 + VR2L]
                                                 ;[VR1H:VR1L] = [I1':R1'] = [I0 - VR2H: R0 - VR2L]

    NOP
    VCFFT4    VR4, VR2, VR1, VR0, #0             ;[VR2H:VR2L] = [R3'*Cos(2) + I3'*Sin(2):I3'*Cos(2) - R3'*Sin(2)]
                                                 ;[VR0H:VR0L] = [I0'�:R0'�] = [I0' + VR2H: R0' + VR2L]
                                                 ;[VR1H:VR1L] = [I2'':R2''] = [I0' - VR2H: R0' - VR2L]

    NOP


    VMOV32    *+XAR7[AR0], VR0                   ;[I0'':R0''] = VR0
    VCFFT6    VR3, VR2, VR1, VR0, #0             ;[I2'':R2''] = VR1
 || VMOV32    *--XAR7, VR1                       ;[VR0H:VR0L] = [I1'':R1'�] = [I1' - VR2H: R1' + VR2L]
                                                 ;[VR1H:VR1L] = [I3'':R3''] = [I1' + VR2H: R1' - VR2L]

    NOP

    VMOV32    *+XAR6[AR0], VR0                   ;[I1'':R1''] = VR0
    VMOV32    *--XAR6, VR1                       ;[I3'':R3''] = VR1


    ;;--------------------------------------------------
    ;;Increment all these pointers with 2 * 3*2^(s-1)
    ;;for Stage 3 & 4, increment by 2 * 3 * 2^(3-1) = 24
    ;;for Stage 5 & 6, increment by 2 * 3 * 2^(5-1) = 96
    ;;for Stage 7 & 8, increment by 2 * 3 * 2^(7-1) = 384

    ;ADDB      XAR2, #S56_POST_INCREMENT
    ;ADDB      XAR4, #S56_POST_INCREMENT
    ;ADDB      XAR6, #S56_POST_INCREMENT
    ;ADDB      XAR7, #S56_POST_INCREMENT
    ;not required for the last of the combined stages
    ;;--------------------------------------------------

    ;BANZ      _ICFFT_run64Pt_stages5and6OuterLoop, AR5--
    ;not required for the last of the combined stages

_ICFFT_run64Pt_stages5and6CombinedEnd:
    ;.c28_amode                                  ; change the assembler mode back to C28x
    ;CLRC      AMODE                             ; set AMODE back to C28x addressing
                                                 ; C28_AMODE allows *XARn[#3bit] addressing
;;=============================================================================

    ICFFT_CONTEXT_RESTORE
    LRETR

;; End of file
