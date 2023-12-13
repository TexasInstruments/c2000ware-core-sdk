;;#############################################################################
;;! \file source/fpu64/fft/icfft_f64.asm
;;!
;;! \brief  Inverse Complex Fast Fourier Transform (Double Precision)
;;! \author Vishal Coelho
;;! \date   02/08/2016
;;
;;  Revision History:
;;+----------+---------------+------------------------------------------------+
;;| DATE     | AUTHOR        | CHANGE                                         |
;;+----------+---------------+------------------------------------------------+
;;| 05/03/19 | Ritvik Sadana | Replaced ICFFT_f64_s_calc with ICFFT_f64 to    |
;;|          |               | keep function name consistent with fpu32.      |
;;+----------+---------------+------------------------------------------------+
;;
;; DESCRIPTION:
;;
;;  This function computes a complex inverse FFT.  The input buffer must be 
;;  aligned to a multiple (x4) of the FFT size. If it is not aligned then the 
;;  output buffer will yield invalid results. If you do not wish to align the 
;;  input buffer then use the ICFFT_f64u function. Using this function 
;;  will reduce cycle performance of the algorithm.
;;
;; The heart of the computation is the regular complex FFT.  The inverse CFFT
;; is computed using the CFFT via the following algorithm:
;; 
;; 1) Swap the real and imag parts of each member of the input array
;; 2) Perform the complex FFT
;; 3) Swap the real and imag parts of each member of the CFFT output array
;; 4) Scale by 1/FFTSize
;; 
;; The inverse FFT is given by:
;;    x(n) = sum_k=0_to_N-1 (X(k).e^(+j2.pi.k.n/N))..........................1
;; Note that 
;;    -jX(k) = -j(X_r(k)+jX_i(k))
;;           =   (X_i(k)-jX_r(k))
;;           =   (swap_r_i(X(k)))* <----X_s_r_i*(k) or X^*(k)
;; and 
;;    jX^*(k) =  j(X_i(k)-jX_r(k))
;;            =   (X_r(k)+jX_i(k))
;;
;; Multiplying and dividing the right hand side of 1 by -j          
;;    x(n) = sum_k=0_to_N-1 j(-jX(k).e^(+j2.pi.k.n/N))
;;         = sum_k=0_to_N-1 j((swap_r_i(X(k)))*.e^(+j2.pi.k.n/N)) 
;;         = j.(sum_k=0_to_N-1 ((swap_r_i(X(k))).e^(-j2.pi.k.n/N)))*
;;         = j.(CFFT(swap_r_i(X(k))))*
;;         = swap_r_i((CFFT(swap_r_i(X(k)))))
;;
;; therefore swapping the real & imaginariy parts, running the forward FFT, 
;; then swapping the real and imaginary parts of the final output gives the 
;; same result as the inverse FFT
;;
;; Alternatively, this can also be done by running the forward FFT, then 
;; scaling and rearranging the output of the final stage as follows:
;; 
;;    x(0) = x_fs(0)/N
;;    x(n) = x_fs(N-n)/N, n = 1 : N-1
;;    x_fs is the output of the final stage and N the size of the FFT
;;
;; The inverse FFT,
;;    x(n) = sum_k=0_to_N-1 (X(k).e^(+j2.pi.k.n/N))
;; Let n = N-n for n = 1 to N-1
;;    x(0)   = sum_k=0_to_N-1 (X(k))
;;    x(N-n) = sum_k=0_to_N-1 (X(k).e^(+j2.pi.k.(N-n)/N)), n = 1 to N-1/FFTSize
;;           = sum_k=0_to_N-1 (X(k).e^(-j2.pi.k.n/N).e^(j2.pi.k.N/N))
;;           = sum_k=0_to_N-1 (X(k).e^(-j2.pi.k.n/N).1)
;;    x(N-n) = sum_k=0_to_N-1 (X(k).e^(-j2.pi.k.n/N))
;; Take the forward FFT of X(k), the first element stays in the first location
;; while the rest are stored in reverse order
;;
;; FUNCTIONS:
;;
;;  void ICFFT_f64 (CFFT_F64_Handle) (using the swap method)
;;  
;;   where CFFT_F64_Handle is defined as:
;;   typedef CFFT_f64_Struct* CFFT_F64_Handle;
;;  
;;  and where CFFT_f64_Struct is a structure defined as:
;;  
;;  typedef struct {
;;   long double *p_input;       //!< Pointer to the input buffer
;;   long double *p_output;      //!< Pointer to the output buffer
;;   long double *p_twiddles;    //!< Pointer to the twiddle factors
;;   long double *p_currInput;   //!< Points to input buffer at each FFT stage
;;   long double *p_currOutput;  //!< Points to output buffer at each FFT stage
;;   uint16_t    stages;         //!< Number of FFT stages
;;   uint16_t    FFTSize;        //!< FFT size (number of complex data points)
;;   void (*init)(void *);       //!<  Pointer to the initialization function
;;   void (*calc)(void *);       //!<  Pointer to the calculation function
;;   void (*mag)(void *);        //!< Pointer to the magnitude function
;;   void (*phase)(void *);      //!< Pointer to the phase function
;;   void (*win)(void *);        //!< Pointer to the windowing function
;;  }CFFT_f64_Struct;
;;
;; ASSUMPTIONS:
;;
;;  * FFTSize must be a power of 2 (32, 64, 128, etc)
;;  * FFTSize must be greater or equal to 32 and lesser than or equal to 4096
;;  * FFTStages must be log2(FFTSize)
;;  * The input, output buffers are FFTSize in length
;;  * MagBuf and PhaseBuf are FFTSize/2 in length
;;  * MagBuf and PhaseBuf are not used by this function.
;;    They are only used by the magnitude and phase calculation functions.
;;  * .ebss must be in the lower 6 bits of addressable memory. This 
;;    restriction is due to C28x type direct memory addressing used in 
;;    stage 1 & 2
;;  * This function is not re-entrant on account of the use of global 
;;    variables and the fact that DP addressing method is used, where 
;;    DP is loaded one time
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

;; the includes
    .cdecls C, LIST, NOWARN, "fpu64/fpu64_fft.h"
;; external references
    
;; file globals
;;
;; NOTE:
;; The following 27 words of .ebss memory are blocked, i.e. they will all be 
;; assigned to the same page. This allows for the DP (data page) pointer to be
;; loaded once at the start of each of the sub functions used in this routine.
;; 
;; See https://e2e.ti.com/support/development_tools/compiler/int-compiler/f/85/p/526014/1918093#1918093
;; for a discussion on blocking.
;;
;; Since these variables are on one page, and there are only 15, their offset 
;; is guaranteed to be within the 6-bit Direct DP addressing mode of the C28x.
;; So it is OK to interchangeably use the @@ (7-bit DP) and @ (6-bit DP)
;; addressing modes of the C2xLP and C28x respectively
;;
    .if __TI_EABI__
    .asg    ".bss", .ebss
    .asg    ICFFTF64_vars, _ICFFTF64_vars
    .endif 
_ICFFTF64_vars_InPtr             .usect .ebss,2,1,1
_ICFFTF64_vars_OutPtr            .usect .ebss,2,1,1
_ICFFTF64_vars_TwiddlesPtr       .usect .ebss,2,1,1
_ICFFTF64_vars_CurrentInPtr      .usect .ebss,2,1,1
_ICFFTF64_vars_CurrentOutPtr     .usect .ebss,2,1,1
_ICFFTF64_vars_CurrentSinPtr     .usect .ebss,2,1,1
_ICFFTF64_vars_CurrentCosPtr     .usect .ebss,2,1,1
; scale factor is aligned to a long double boundary
; so there will be a 2 word hole
_ICFFTF64_vars_scaleFactor       .usect .ebss,4,1,2
_ICFFTF64_vars_Stages            .usect .ebss,1,1,0
_ICFFTF64_vars_FFTSize           .usect .ebss,1,1,0
_ICFFTF64_vars_DataPtrInc        .usect .ebss,1,1,0
_ICFFTF64_vars_TwiddlesPtrInc    .usect .ebss,1,1,0
_ICFFTF64_vars_StageCounter      .usect .ebss,1,1,0
_ICFFTF64_vars_OuterCounter      .usect .ebss,1,1,0
_ICFFTF64_vars_InnerCounter      .usect .ebss,1,1,0


;;*****************************************************************************
;; void ICFFT_f64(CFFT_f64_Handle) 
;;
;; The function takes a handle to the CFFT_f64 object as an argument. 
;;
;; Register Usage:                                                            
;;   XAR0 : elements of the object               
;;   XAR1 : 
;;   XAR2 : 
;;   XAR3 :                                     
;;   XAR4 : pointer to the object                                    
;;   XAR5 :                                     
;;   XAR6 :                                     
;;   XAR7 :                                     
;;     AL : 

;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- XAR4                             (SP-2) --> Local Frame
;;   |_______|<- R7H                              (SP-4)
;;   |_______|<- R6H                              (SP-6)
;;   |_______|<- R5H                              (SP-8)
;;   |_______|<- R4H                              (SP-10)
;;   |_______|<- XAR3                             (SP-12)
;;   |_______|<- XAR2                             (SP-14)
;;   |_______|<- XAR1                             (SP-16)
;;   |_______|<- rpc calling function             (SP-18)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg ICFFT_f64, _ICFFT_f64
    .endif
    
    .page
    .global _ICFFT_f64
    .sect   ".text"
_ICFFT_f64:
    .asmfunc
    .asg    #2                              , LF_SIZE    
    .asg    *-SP[2]                         , LF_XAR4    
    .asg    *XAR4++                         , OBJ_INPTR  
    .asg    *XAR4++                         , OBJ_OUTPTR 
    .asg    *XAR4++                         , OBJ_TFPTR
    .asg    *+XAR4[0]                       , OBJ_CURR_INPUT_PTR
    .asg    *+XAR4[2]                       , OBJ_CURR_OUTPUT_PTR
    .asg    *+XAR4[4]                       , OBJ_STAGES 
    .asg    *+XAR4[5]                       , OBJ_FFTSIZE
    .asg    @_ICFFTF64_vars_InPtr           , STAGE_1_2_INPUT_PTR
    .asg    @_ICFFTF64_vars_OutPtr          , STAGE_1_2_OUTPUT_PTR
    .asg    @_ICFFTF64_vars_TwiddlesPtr     , STAGE_3UP_TWIDDLES_PTR
    .asg    @_ICFFTF64_vars_Stages          , FFT_STAGES
    .asg    @_ICFFTF64_vars_FFTSize         , FFT_SIZE
    .asg    @_ICFFTF64_vars_CurrentInPtr    , STAGE_3UP_CURR_INPUT_PTR 
    .asg    @_ICFFTF64_vars_CurrentOutPtr   , STAGE_3UP_CURR_OUTPUT_PTR
    .asg    @_ICFFTF64_vars_scaleFactor     , INV_SCALE_FACTOR
    .asg    #1023                           , DP_EXP_BIAS
    .asg    #0x7FF0                         , DP_EXP_MASK
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    PUSH    XAR1
    PUSH    XAR2
    PUSH    XAR3
    MOV32   *SP++,R4H
    MOV32   *SP++,R5H
    MOV32   *SP++,R6H
    MOV32   *SP++,R7H
;;-----------------------------------------------------------------------------
;; The complex FFT
;;-----------------------------------------------------------------------------
    ADDB    SP, LF_SIZE               ; create the local frame

    MOVL    XAR0, OBJ_INPTR           ; XAR0 = obj.p_input, save to stack
    ; Only have to load DP once as the global .ebss variables are on a
    ; single page
    MOVW    DP, #_ICFFTF64_vars_InPtr
    MOVL    STAGE_1_2_INPUT_PTR, XAR0
    MOVL    XAR0,  OBJ_OUTPTR         ; XAR0 = obj.p_output, save to stack
    MOVL    STAGE_1_2_OUTPUT_PTR, XAR0
    MOVL    XAR0,  OBJ_TFPTR          ; XAR0 = obj.p_twiddles, save to stack
    MOVL    STAGE_3UP_TWIDDLES_PTR, XAR0
    MOVL    LF_XAR4, XAR4             ; save current index into the object
                                      ; to the local frame
    ZAPA                              ; ACC:P = 0
    MOVZ    AR0,  OBJ_STAGES          ; AR0 = obj.stages, save to stack
    MOV     FFT_STAGES, AR0           ;
    ;-------------------------------------------------------------------------
    ; We need to scale down the final output by N, i.e. 2^stages. The scale
    ; factor is a double precision value of the form (-1)^S.(1.M)x2^(E-1023)
    ; where M is the 52 bit mantissa, E the 11 bit exponent, and S the sign of 
    ; the value. 
    ; Since N is some power of 2 the inverse scaling factor (ISF) will
    ; be a negative power of 2. For example, for a 1024 (2^10) point FFT the 
    ; ISF is 2^-10 or 0.0009765625
    ; The ISF will be of the form (-1)^0.(1.0)x2^(E-1023)
    ; S and M are 0. All that is required is to calculate E, bias it and shift
    ; it to its oorrect posiiton
    ;
    ; ACC:P = 0
    ; AH    = dp_exponent_bias (1023)
    ; AH    = dp_exponent_bias (1023)-stages.....a 10 bit number
    ; AH    <<= 4 ...shift the 10-bit difference up 4 places to occupy bits
    ;                52 to 62
    ; AH    &= dp_exponent_mask (0x7FF0)
    ; store ACC:P to memory
    ;-------------------------------------------------------------------------
    MOV     AH, DP_EXP_BIAS           ; AH = dp_exponent_bias
    SUB     AH, OBJ_STAGES            ; AH = dp_exponent_bias - #stages
    LSL     ACC, #4                   ; shift biased expoenent to its place
    AND     ACC, DP_EXP_MASK << 16    ; mask off everything but the exponent
    MOVL    INV_SCALE_FACTOR, P       ; Save the inverse scaling factor to mem
    MOVL    INV_SCALE_FACTOR + 2, ACC
   
    MOVZ    AR0,  OBJ_FFTSIZE         ; AR0 = obj.FFTSize, save to stack
    MOV     FFT_SIZE, AR0
    


    LCR     _ICFFT_f64_s_stages1and2withBitReverse
    LCR     _ICFFT_f64_s_stages3andUp
    
    MOVL    XAR4, LF_XAR4             ; restore the object pointer
    
    ; The final output saved in memory pointed by CurrentInPtr. Save the
    ; pointers to the object
    MOVL    ACC, STAGE_3UP_CURR_INPUT_PTR
    MOVL    OBJ_CURR_INPUT_PTR, ACC

    MOVL    ACC, STAGE_3UP_CURR_OUTPUT_PTR
    MOVL    OBJ_CURR_OUTPUT_PTR, ACC
    
    SUBB    SP, LF_SIZE               ; delete the local frame
;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
    MOV32   R7H,*--SP
    MOV32   R6H,*--SP
    MOV32   R5H,*--SP
    MOV32   R4H,*--SP
    POP     XAR3
    POP     XAR2
    POP     XAR1
    LRETR
    .endasmfunc
    .unasg  LF_SIZE    
    .unasg  LF_XAR4    
    .unasg  OBJ_INPTR  
    .unasg  OBJ_OUTPTR 
    .unasg  OBJ_TFPTR
    .unasg  OBJ_CURR_INPUT_PTR
    .unasg  OBJ_CURR_OUTPUT_PTR
    .unasg  OBJ_STAGES 
    .unasg  OBJ_FFTSIZE
    .unasg  STAGE_1_2_INPUT_PTR
    .unasg  STAGE_1_2_OUTPUT_PTR
    .unasg  STAGE_3UP_TWIDDLES_PTR
    .unasg  FFT_STAGES
    .unasg  FFT_SIZE
    .unasg  STAGE_3UP_CURR_INPUT_PTR 
    .unasg  STAGE_3UP_CURR_OUTPUT_PTR  
    .unasg  INV_SCALE_FACTOR
    .unasg  DP_EXP_BIAS
    .unasg  DP_EXP_MASK
;;*****************************************************************************
;; void ICFFT_f64_stages1and2withBitReverse(void) 
;;
;; Stages 1 and 2 (the trivial stages) with bit reverse addressing
;;
;; NOTE: 
;; - This function is not exposed in the C header and is local to this file
;; - AR0 (16-bit) stores N << 4, so the maximum size of N is 12-bits or (4096)
;;
;; Register Usage:                                                            
;;   XAR0 : index (for bit reverse addressing)                 
;;   XAR1 : pointer to the input buffer        
;;   XAR2 : pointer to the output buffer       
;;   XAR3 :                                     
;;   XAR4 :                                     
;;   XAR5 :                                     
;;   XAR6 :                                     
;;   XAR7 :                                     
;;     AL : loop count
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                (SP)
;;   |_______|<- rpc calling function         (SP-2)
;;
;;*****************************************************************************

    .page
    .sect   ".text"
_ICFFT_f64_s_stages1and2withBitReverse:
    .asmfunc
    .asg    @_ICFFTF64_vars_InPtr            , STAGE_1_2_INPUT_PTR
    .asg    @_ICFFTF64_vars_OutPtr           , STAGE_1_2_OUTPUT_PTR
    .asg    @_ICFFTF64_vars_FFTSize          , FFT_SIZE
    .asg    @_ICFFTF64_vars_CurrentInPtr     , CURR_INPUT_PTR
    .asg    @_ICFFTF64_vars_CurrentOutPtr    , CURR_OUTPUT_PTR

    .c28_amode
    CLRC    AMODE                       ; Set addressing mode to C28x
;;-----------------------------------------------------------------------------
;; Stage 1 and 2
;;
;; NOTE: Instead of referring to the real part as Rn we choose Dn to avoid 
;; confusing them with the Rn FPU registers
;;
;;                 Stage 1    Stage 2
;; ---I0+jD0-o----*--D0`+jI0`--o--------*--D0^+jI0^->
;;            \  /              \      /           
;;             \/                \    /            
;;             /\                 \  /             
;;            /  \                 \/              
;; ---I1+jD1-o----*--D1`+jI1`--o---/\---*--D1^+jI1^->
;;                              \ /  \ /
;;                               \    \
;;                              / \  / \
;; ---I2+jD2-o----*--D2`+jI2`--o---\/---*--D2^+jI2^->
;;            \  /                 /\              
;;             \/                 /  \             
;;             /\                /    \            
;;            /  \              /      \           
;; ---I3+jD3-o----*--D3`+jI3`--o--------*--D3^+jI3^->
;
;;   +-----+---------+-----+-----------------+
;;   |   Stage 1     |   Stage 2             |
;;   +-----+---------+-----+-----------------+
;;   | D0` |  I0+I1  | D0^ | (I0+I1)+(I2+I3) |
;;   | I0` |  D0+D1  | I0^ | (D0+D1)+(D2+D3) |
;;   | D1` |  I0-I1  | D1^ | (I0-I1)+(D2-D3) |
;;   | I1` |  D0-D1  | I1^ | (D0-D1)-(I2-I3) |
;;   | D2` |  I2+I3  | D2^ | (I0+I1)-(I2+I3) |
;;   | I2` |  D2+D3  | I2^ | (D0+D1)-(D2+D3) |
;;   | D3` |  I2-I3  | D3^ | (I0-I1)-(D2-D3) |
;;   | I3` |  D2-D3  | I3^ | (D0-D1)+(I2-I3) |
;;   +-----+---------+-----+-----------------+
;;-----------------------------------------------------------------------------
    ZEROA                               ; R0 to R7 = 0.0
    MOVL    XAR1, STAGE_1_2_INPUT_PTR   ; XAR1 -> input buffer
    MOVL    XAR2, STAGE_1_2_OUTPUT_PTR  ; XAR2 -> output buffer
    MOVL    CURR_OUTPUT_PTR, XAR1
    MOVL    CURR_INPUT_PTR, XAR2
    MOV     ACC, FFT_SIZE << #2         ; ACC = N << #2 (N is the FFT size)
    MOVZ    AR0, AL                     ; AR0 = N << #2 (4*N) 
    LSR     AL, #4                      ; AL  = N >> #4 (N/4) 
    SUBB    AL, #1                      ; AL  = N/4 - 1
    .align  2
    RPTB    _ICFFT_f64_s_stages1and2withBitReverse_loop, AL
    MOV32   R1H, *+XAR1[6]              ;        R1 = I0
    MOV32   R1L, *+XAR1[4]              ;        
    MOV32   R0H, *+XAR1[2]              ;        R0 = D0, ARP -> XAR1
    MOV32   R0L, *BR0++                 ;               , XAR1 <rcadd>= AR0
                                                 
    MOV32   R3H, *+XAR1[6]              ;        R3 = I1
    MOV32   R3L, *+XAR1[4]              ;
    ADDF64  R7, R1, R3                  ; *|     R7(D0`)=I0+I1
 || MOV32   R2H, *+XAR1[2]              ;  |     R2 = D1, ARP -> XAR1
    MOV32   R2L, *BR0++                 ; 1|          , XAR1 <rcadd>= AR0
    ADDF64  R6, R0, R2                  ; 2|*|   R6(I0`)=D0+D1
 || MOV32   R5H, *+XAR1[6]              ;  | |   R5 = I2
    MOV32   R5L, *+XAR1[4]              ;  |1|
    SUBF64  R0, R0, R2                  ; *|2|   R0(I1`)=D0-D1
 || MOV32   R4H, *+XAR1[2]              ;  |     R4 = D2, ARP -> XAR1
    MOV32   R4L, *BR0++                 ; 1|            , XAR1 <rcadd>= AR0 
    SUBF64  R2, R1, R3                  ; 2|*|   R2(D1`)=I0-I1
 || MOV32   R1H, *+XAR1[6]              ;  | |   R1 = I3
    MOV32   R1L, *+XAR1[4]              ;  |1|   
    ADDF64  R3, R5, R1                  ; *|2|   R3(D2`)=I2+I3
    SUBF64  R5, R5, R1                  ; 1|*|   R5(D3`)=I2-I3
    NOP                                 ; 2|1|
    ADDF64  R1, R7, R3                  ; *|2|   R1(D0^)=(I0+I1)+(I2+I3)
    SUBF64  R7, R7, R3                  ; 1|*|   R7(D2^)=(I0+I1)-(I2+I3)
 || MOV32   R3H, *+XAR1[2]              ;  | |   R3 = D3, ARP -> XAR1
    MOV32   R3L, *BR0++                 ; 2|1|           , XAR1 <rcadd>= AR0
    MOV32   *XAR2++, R1L                ;  |2|   store R1(D0^)
    ADDF64  R1, R4, R3                  ; *|     R1(I2`)=D2+D3
 || MOV32   *XAR2++, R1H                ;  |             , ARP -> XAR1
    NOP                                 ; 1|
    SUBF64  R4, R4, R3                  ; 2|*|   R4(I3`)=D2-D3
    ADDF64  R3, R6, R1                  ; *|1|   R3(I0^)=(D0+D1)+(D2+D3)
    SUBF64  R6, R6, R1                  ; 1|2|*| R6(I2^)=(D0+D1)-(D2+D3)
    ADDF64  R1, R2, R4                  ; 2|*|1| R1(D1^)=(I0-I1)+(D2-D3)
    SUBF64  R4, R2, R4                  ; *|1|2| R4(D3^)=(I0-I1)-(D2-D3)
 || MOV32   *XAR2++, R3L                ;  | | | store R3(I0^)
    SUBF64  R2, R0, R5                  ; 1|2|*| R2(I1^)=(D0-D1)-(I2-I3)
 || MOV32   *XAR2++, R3H                ;  | |
    MOV32   *XAR2++, R1L                ; 2| |1| store R1(D1^)
    MOV32   *XAR2++, R1H                ;  | |2|
    ADDF64  R0, R0, R5                  ; *|     R0(I3^)=(D0-D1)+(I2-I3)
 || MOV32   *XAR2++, R2L                ;  |     store R2(I1^)  
    MOV32   *XAR2++, R2H                ; 1|  
    MOV32   *XAR2++, R7L                ; 2|     store R7(D2^)
    MOV32   *XAR2++, R7H
    MOV32   *XAR2++, R6L                ;        store R6(I2^)
    MOV32   *XAR2++, R6H                         
    MOV32   *XAR2++, R4L                ;        store R4(D3^)
    MOV32   *XAR2++, R4H                         
    MOV32   *XAR2++, R0L                ;        store R0(I3^)
    MOV32   *XAR2++, R0H
_ICFFT_f64_s_stages1and2withBitReverse_loop:
    LRETR
    .endasmfunc
    .unasg  STAGE_1_2_INPUT_PTR
    .unasg  STAGE_1_2_OUTPUT_PTR
    .unasg  FFT_SIZE
    
;;*****************************************************************************
;; void ICFFT_f64_stages3andUp(void) 
;;
;; Stages 3 and up
;;
;; NOTE: 
;; - This function is not exposed in the C header and is local to this file
;; - 
;;
;; Register Usage:                                                            
;;   XAR0 :                 
;;   XAR1 : outer loop counter
;;   XAR2 : Current input buffer pointer (top of the butterfly)
;;   XAR3 : Current input buffer pointer (bottom of the butterfly)
;;   XAR4 : Points to the sine of the twiddle factor
;;   XAR5 : Points to the cosine of the twiddle factor
;;   XAR6 : Current output buffer pointer (top of the butterfly)
;;   XAR7 : Current output buffer pointer (bottom of the butterfly)
;;     AL : inner loop counter
;;
;; Stack Usage:
;;
;;   |_______|<- stack pointer                        (SP)
;;   |_______|<- XAR2                                 (SP-2)
;;   |_______|<- XAR1                                 (SP-4)
;;   |_______|<- XAR0                                 (SP-6)
;;   |_______|<- rpc calling function                 (SP-7)
;;
;;*****************************************************************************

    .page
    .sect   ".text"
_ICFFT_f64_s_stages3andUp:
    .asmfunc
    .asg    @@_ICFFTF64_vars_TwiddlesPtr     , TWIDDLES_PTR
    .asg    @@_ICFFTF64_vars_CurrentInPtr    , CURR_INPUT_PTR 
    .asg    @@_ICFFTF64_vars_CurrentOutPtr   , CURR_OUTPUT_PTR
    .asg    @@_ICFFTF64_vars_CurrentSinPtr   , CURR_SIN_PTR  
    .asg    @@_ICFFTF64_vars_CurrentCosPtr   , CURR_COS_PTR
    .asg    @@_ICFFTF64_vars_Stages          , FFT_STAGES   
    .asg    @@_ICFFTF64_vars_FFTSize         , FFT_SIZE   
    .asg    @@_ICFFTF64_vars_DataPtrInc      , DATA_PTR_INC
    .asg    @@_ICFFTF64_vars_TwiddlesPtrInc  , TWIDDLES_PTR_INC
    .asg    @@_ICFFTF64_vars_StageCounter    , STAGE_COUNTER
    .asg    @@_ICFFTF64_vars_OuterCounter    , OUTER_COUNTER
    .asg    @@_ICFFTF64_vars_InnerCounter    , INNER_COUNTER
    .asg    @@_ICFFTF64_vars_scaleFactor     , INV_SCALE_FACTOR
    .lp_amode
    SETC    AMODE               ; Set addressing mode to C2xLP
;;-----------------------------------------------------------------------------
;; Stage 3 and Up
;;
;; NOTE: Instead of referring to the real part as Rn we choose Dn to avoid 
;; confusing them with the Rn FPU registers

;;                    Stage n
;; --D0+jI0--------o-------*---(D0+D1*C+I1*S)+j(I0+I1*C-D1*S)--->
;;                  \     /
;;                   \   /
;;                    \ /
;;                     \
;;                    / \
;;                   /   \
;;                  /     \
;; --D1+jI1---C-jS-o--<-1>-*---(D0-D1*C-I1*S)+j(I0-I1*C+D1*S)--->
;;
;; InPtr  OutPtr | Stage3 | Stage4 | Stage5 | Stage6 | Stage7 | Stage8 | Stage9 | Stage10 | ...
;;               +--------+--------+--------+--------+--------+--------+--------+---------+----
;; XAR2-> XAR6->   R(0)   | R(0)   | R(0)   | R(0)   | R(0)   | R(0)   | R(0)   | R(0)    | D0' = D0  + (D1*Cos(0) + I1*Sin(0))
;;   |      |      I(0)   | I(0)   | I(0)   | I(0)   | I(0)   | I(0)   | I(0)   | I(0)    | I0' = I0  + (I1*Cos(0) - D1*Sin(0))  
;;   |      |        .                                                     
;;  \|/    \|/       4        8        16       32       64       128      256      512     <- InnerLoop Repeat Times
;;                   .                                                        
;;                 R(3)   | R(7)   | R(15)  | R(31)  | R(63)  | R(127) | R(255) | R(511)  | D0' = D0  + (D1*Cos(n) + I1*Sin(n))  
;;                 I(3)   | I(7)   | I(15)  | I(31)  | I(63)  | I(127) | I(255) | I(511)  | I0' = I0  + (I1*Cos(n) - D1*Sin(n))  
;; XAR3-> XAR7->   R(4)   | R(8)   | R(16)  | R(32)  | R(64)  | R(128) | R(256) | R(512)  | D1' = D0  - (D1*Cos(0) + I1*Sin(0))
;;   |      |      I(4)   | I(8)   | I(16)  | I(32)  | I(64)  | I(128) | I(256) | I(512)  | I1' = I0  - (I1*Cos(0) - D1*Sin(0)) 
;;   |      |        .
;;  \|/    \|/       .                                                              
;;                   .                                                       
;;                 R(7)   | R(15)  | R(31)  | R(63)  | R(127) | R(255) | R(511) | R(1023) | D1' = D0  - (D1*Cos(n) + I1*Sin(n))
;;                 I(7)   | I(15)  | I(31)  | I(63)  | I(127) | I(255) | I(511) | I(1023) | I1' = I0  - (I1*Cos(n) - D1*Sin(n)) 
;;                ------------------------------------------------------------------------+----
;;                   32       16        8        4        2        1        0        0      <- OuterLoop repeat times for  256-point CFFT
;;                   64       32       16        8        4        2        1        0      <- OuterLoop repeat times for  512-point CFFT
;;                  128       64       32       16        8        4        2        1      <- OuterLoop repeat times for 1024-point CFFT
;;
;;-----------------------------------------------------------------------------
;; Complex FFT Coefficient (twiddle) Table:
;;-----------------------------------------------------------------------------
;;  FFT   Stage   Iter Address     Table Value                  TablePointers
;; SIZE                  x16
;;------+------+------+-------+------------------------------------------------
;;  256 |   8  |    1 |     0 | SIN(   0*pi/512 )                   <-XAR5
;;      .      .      .       .
;;      |      |      |  1024 | SIN( 256*pi/512 ) = COS(  0*pi/512) <-XAR4
;;      .      .      .       .
;;      |      |  128 |  2044 | SIN( 511*pi/512 ) = COS(255*pi/512)
;;      |      |      |  2048 | SIN( 512*pi/512 ) = COS(256*pi/512)
;;      .      .      .       .
;;      |      |      |  3068 | SIN( 767*pi/512 ) = COS(511*pi/512)
;;------+------+------+-------+------------------------------------------------
;;  512 |   9  |    1 |     0 | SIN(   0*pi/512 )                   <-XAR5
;;      .      .      .       .
;;      |      |      |  1024 | SIN( 256*pi/512 ) = COS(  0*pi/512) <-XAR4
;;      .      .      .       .
;;      |      |  256 |  2044 | SIN( 511*pi/512 ) = COS(255*pi/512)
;;      |      |      |  2048 | SIN( 512*pi/512 ) = COS(256*pi/512)
;;      .      .      .       .
;;      |      |      |  3068 | SIN( 767*pi/512 ) = COS(511*pi/512)
;;------+------+------+-------+------------------------------------------------
;; 1024 |  10  |    1 |     0 | SIN(   0*pi/512 )                   <-XAR5
;;      .      .      .       .
;;      |      |      |  1024 | SIN( 256*pi/512 ) = COS(  0*pi/512) <-XAR4
;;      .      .      .       .
;;      |      |  512 |  2044 | SIN( 511*pi/512 ) = COS(255*pi/512)
;;      |      |      |  2048 | SIN( 512*pi/512 ) = COS(256*pi/512)
;;      .      .      .       .
;;      |      |      |  3068 | SIN( 767*pi/512 ) = COS(511*pi/512)
;;------+------+------+-------+------------------------------------------------
;;                         Stage:   3   4   5   6   7   8   9  10
;; Coef Step For  256-point CFFT: 510 254 126  62  30  14   -   -
;; Coef Step For  512-point CFFT: 510 254 126  62  30  14   6   -
;; Coef Step For 1024-point CFFT: 510 254 126  62  30  14   6   2
;;-----------------------------------------------------------------------------
   
    ; Initialize the data input and output pointers starting from stage 32
    MOVL    XAR3, CURR_INPUT_PTR
    MOVL    XAR7, CURR_OUTPUT_PTR
    MOVL    XAR2, CURR_INPUT_PTR
    MOVL    XAR6, CURR_OUTPUT_PTR
    
    ; Initialize "StageCounter" value starting from stage 3:
    ; StageCounter = (Stages -2) - 1 - 1 = Stages - 4
    ;              =  6 (execute StageLoop 8 times for 1024-point CFFT)
    ;              =  5 (execute StageLoop 7 times for  512-point CFFT)
    ;              =  4 (execute StageLoop 6 times for  128-point CFFT)
    MOV     AL, FFT_STAGES
    SUBB    AL, #4                        
    MOV     STAGE_COUNTER, AL
    
    ; Initialize "OuterCounter" value starting from stage 3:
    ; OuterCounter = ((2^Stages) >> 3) - 1
    ;              = 127 (for 1024-point CFFT)
    ;              =  63 (for  512-point CFFT)
    ;              =  31 (for  256-point CFFT)
    MOV     AL, FFT_SIZE
    LSR     AL, #3
    SUBB    AL, #1
    MOV     OUTER_COUNTER, AL
    

    ; Initialize "TwiddlesPtrInc" value starting from stage 3:
    ; TwiddlePtrInc = (table_size/2^curr_stage)*sizeof(long double) - 2
    ;               = 1024/8 * 4 - 2
    ;               = 2^10/2^3 * 2^2 - 2
    ;               = 2^(10 - 3 + 2) - 2
    ;               = 510
    ; The -2 at the end is due to the fact that when we read the sine we 
    ; read the low dword (using *++) and then the high dword (using *0++) which
    ; incremnets by the twiddle pointer increment landing us at the high dword
    ; of the next twiddle. The -2 ensures we land at the low dword.
    MOVB    AL, #1
    LSL     AL, #(TABLE_SIZE_LOG2 - 3 + 2)
    SUBB    AL, #2
    MOV     TWIDDLES_PTR_INC, AL
    
    ; Initialize "CurrentCosPtr" value:
    ; CurrentCosPtr = XAR4 = TwiddlePtr[table_size/4]
    ;                      = TwiddlesPtr + (table_size/4 * sizeof(long double))
    ;                      = TwiddlePtr + 256*4
    MOVL    ACC, TWIDDLES_PTR
    MOVL    XAR5, ACC
    MOVL    CURR_SIN_PTR, XAR5
    ADD     ACC, #1 << 10       ; cosines start at twiddles[table_size/4]
    MOVL    XAR4, ACC           ; table_size/4 * sizeof(long double)
    MOVL    CURR_COS_PTR, XAR4  ; 256 * 4
    
    ; Initialize other values starting from stage 3:
    MOV     INNER_COUNTER, #2
    MOV     DATA_PTR_INC,  #34

    .lp_amode
    SETC    AMODE               ; Set addressing mode to C2xLP
_ICFFT_f64_s_stages3andUp_loop:
    ; Load "DataPtrInc" value and initialize XAR3 and XAR7 data pointers:
    MOVZ    AR0, DATA_PTR_INC
    NOP     *, ARP3
    NOP     *0++, ARP7          ; XAR3 = XAR3 + DataPtrInc, ARP -> XAR7
    NOP     *0++, ARP3          ; XAR7 = XAR7 + DataPtrInc, ARP -> XAR3
    MOVZ    AR0, TWIDDLES_PTR_INC
    SUBB    XAR3, #2            ; XAR3 = XAR3 + DataPtrInc - 2
    SUBB    XAR7, #2            ; XAR7 = XAR7 + DataPtrInc - 2

    ; Initialize OuterCounter (AR1):
    MOVZ        AR1, OUTER_COUNTER
    ; Initialize InnerCounter (AL):
    MOV         AL, INNER_COUNTER
        
    .align  2
    MOV32   R1L, *++            ; R1 = D1_1
    MOV32   R1H, *++, ARP4      ; ARP -> XAR4
_ICFFT_f64_s_stages3andUp_outerLoop:
    MOV32   R2L, *++            ;      R2 = COS_1
    MOV32   R2H, *0++, ARP3     ;                            , ARP -> XAR3
    MPYF64  R7, R1, R2          ; *|   R7 = D1_1*COS_1
 || MOV32   R0L, *++            ;  |   R0 = I1_1
    MOV32   R0H, *++, ARP5      ; 1|                         , ARP -> XAR5
    MOV32   R3L, *++            ; 2|   R3 = SIN_1
    MOV32   R3H, *0++, ARP3     ;                            , ARP -> XAR3
    MPYF64  R6, R0, R3          ; *|   R6 = I1_1*SIN_1
    MPYF64  R5, R1, R3          ; 1|*| R5 = D1_1*SIN_1
                                ; 2|1| RPTB (4 cyc) falls in this delay slot
                                ;  |2| RPTB (4 cyc) falls in this delay slot
    .align  2
    RPTB    _ICFFT_f64_s_stages3andUp_innerLoop, AL
    ADDF64  R7, R7, R6          ; *|   R7 = D1_1*COS_1 + I1_1*SIN_1
 || MOV32   R1L, *++            ;  |   R1 = D1_2
    MOV32   R1H, *++, ARP2      ; 1|                         , ARP -> XAR2
    MPYF64  R6, R0, R2          ; 2|*| R6 = I1_1*COS_1
 || MOV32   R3L, *++            ;  | | R3 = D0_1
    MOV32   R3H, *++, ARP4      ;  |1|                       , ARP -> XAR4
    ADDF64  R4, R3, R7          ; *|2| R4 = D0_1 + (D1_1*COS_1 + I1_1*SIN_1)
 || MOV32   R2L, *++            ;  |   R2 = COS_2
    MOV32   R2H, *0++, ARP3     ; 1|                         , ARP -> XAR3
    SUBF64  R6, R6, R5          ; 2|*| R6 = I1_1*COS_1 - D1_1*SIN_1
 || MOV32   R0L, *++            ;  | | R0 = I1_2
    MOV32   R0H, *++, ARP6      ;  |1|                       , ARP -> XAR6
    MOV32   *++, R4L            ;  |2| Save R4
    SUBF64  R4, R3, R7          ; *| | R4 = D0_1 - (D1_1*COS_1 + I1_1*SIN_1)
 || MOV32   *++, R4H, ARP2      ;  |                         , ARP -> XAR2
    MPYF64  R7, R1, R2          ; 1|*| R7 = D1_2*COS_2
 || MOV32   R3L, *++            ;  | | R3 = I0_1
    MOV32   R3H, *++, ARP7      ; 2|1|                       , ARP -> XAR7
    MOV32   *++, R4L            ;  |2| Save R4
    ADDF64  R4, R3, R6          ; *|   R4 = I0_1 + (I1_1*COS_1 - D1_1*SIN_1)
 || MOV32   *++, R4H, ARP5      ;  |                         , ARP -> XAR5
    SUBF64  R5, R3, R6          ; 1|*| R5 = I0_1 - (I1_1*COS_1 - D1_1*SIN_1)
 || MOV32   R3L, *++            ;  | | R3 = SIN_2
    MOV32   R3H, *0++, ARP6     ; 2|1|                         , ARP -> XAR6
    MPYF64  R6, R0, R3          ; *|2| R6 = I1_2* SIN_2
 || MOV32   *++, R4L            ;  | | Save R4
    MOV32   *++, R4H, ARP7      ; 1|                       , ARP -> XAR7
    MOV32   *++, R5L            ; 2|   Save R5
    MPYF64  R5, R1, R3          ; *|   R5 = D1_2*SIN_2
 || MOV32   *++, R5H, ARP3      ;  |                         , ARP -> XAR3
                                ; 1|   ADDF64  R7, R7, R6 (RPTB, line 1)  
                                ;  | ||MOV32   R1L, *++            
                                ; 2|   MOV32   R1H, *++, ARP2 (RPTB, line 2)    
_ICFFT_f64_s_stages3andUp_innerLoop:
    MOVZ    AR0, DATA_PTR_INC
    MOVL    XAR4, CURR_COS_PTR
    MOVL    XAR5, CURR_SIN_PTR
    
    ADDF64  R7, R7, R6          ; *|   R7 =  D1_2*COS_2 + I1_2*SIN_2 
 || MOV32   R6H, *--, ARP2      ;  |   XAR3 -= 2 (dummy move), ARP -> XAR2
    MPYF64  R6, R0, R2          ; 1|*| R6 = I1_2*COS_2
 || MOV32   R3L, *++            ;  | | R3 = D0_2
    MOV32   R3H, *++, ARP3      ; 2|1|                       , ARP -> XAR3
    ADDF64  R4, R3, R7          ; *|2| R4 = D0_2 + (D1_2*COS_2 + I1_2*SIN_2)
    SUBF64  R6, R6, R5          ; 1|*| R6 = I1_2*COS_2 - D1_2*SIN_2
    NOP     *0++, ARP6          ; 2|1| XAR3 += DataPtrInc (dummy move)
                                ;  | |                       , ARP -> XAR6
    MOV32   *++, R4L            ;  |2|  Save R4
    SUBF64  R4, R3, R7          ; *|  R4 = D0_2 - (D1_2*COS_2 + I1_2*SIN_2)
 || MOV32   *++, R4H, ARP2      ;  |                         , ARP -> XAR2
    MOV32   R3L, *++            ;      R3 = I0_2
    MOV32   R3H, *0++, ARP7     ;                            , ARP -> XAR7
    MOV32   *++, R4L            ;  |   Save R4
    ADDF64  R4, R3, R6          ; *|   R4 = I0_2 + (I1_2*COS_2 - D1_2*SIN_2)
 || MOV32   *++, R4H, ARP3      ;  |                         , ARP -> XAR3
    SUBF64  R5, R3, R6          ; 1|*| R5 = I0_2 - (I1_2*COS_2 - D1_2*SIN_2)
 || MOV32   R1L, *++            ;  | | R1 = D1_1
    MOV32   R1H, *++, ARP6      ; 2|1|                       , ARP -> XAR6
    MOV32   *++, R4L            ;  |2| Save R4
    MOV32   *0++, R4H, ARP7     ;                            , ARP -> XAR7
    MOV32   *++, R5L            ;      Save R5
    MOV32   *0++, R5H, ARP4     ;                            , ARP -> XAR4
    MOVZ    AR0, TWIDDLES_PTR_INC
    BANZ    _ICFFT_f64_s_stages3andUp_outerLoop, AR1--
    

    ; Calculate new "DataPtrInc" for next stage:    
    ; DataPtrInc = (8 * 2^(stage-1)) + 2
    ; DataPtrInc = (2^3 * 2^(stage-1) + 2)
    ; DataPtrInc = (2^(stage+2) + 2)
    ; DataPtrInc = 2*DataPtrInc - 2
    ;            =   66     (for Stage 4)
    ;            =  130     (for Stage 5)
    ;            =  258     (for Stage 6)
    ;            =  514     (for Stage 7)
    ;            = 1026     (for Stage 8)
    ;            = 2050     (for Stage 9)
    ;            = 4098     (for Stage 10)
    MOV     AL, DATA_PTR_INC
    LSL     AL, #1
    SUBB    AL, #2
    MOV     DATA_PTR_INC, AL

    ; Calculate new "TwiddlePtrInc" for next stage:
    ; TwiddlePtrInc = TwiddlePtrInc / 2 - 1
    ;                         Stage:   4   5   6   7   8   9  10
    ; Twiddle Step For  256-point CFFT:  64  32  16   8   4   -   -
    ; Twiddle Step For  512-point CFFT: 128  64  32  16   8   4   -
    ; Twiddle Step For 1024-point CFFT: 256 128  64  32  16   8   4
    MOV     AL, TWIDDLES_PTR_INC
    LSR     AL, #1
    SUBB    AL, #1
    MOV     TWIDDLES_PTR_INC, AL
        
    ; Initialize and swap input and output data pointers for next stage:
    ; XAR2 = CurrentOutPtr  
    ; XAR3 = CurrentOutPtr  (XAR2 and XAR3 point to output data from previous stage calculations)
    ; XAR6 = CurrentInPtr
    ; XAR7 = CurrentInPtr   (XAR6 and XAR7 point to input data from previous stage calculations)
    ; CurrentInPtr  = XAR2
    ; CurrentOutPtr = XAR6  (swap pointers to indicate which is current output buffer)
    MOVL    XAR7, CURR_INPUT_PTR
    MOVL    XAR6, CURR_INPUT_PTR
    MOVL    XAR3, CURR_OUTPUT_PTR
    MOVL    XAR2, CURR_OUTPUT_PTR
    MOVL    CURR_INPUT_PTR, XAR2
    MOVL    CURR_OUTPUT_PTR, XAR6
        
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
    MOV     AL, INNER_COUNTER
    ADDB    AL, #1
    LSL     AL, #1
    MOV     INNER_COUNTER, AL
    
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
    MOV     AL, OUTER_COUNTER
    ADDB    AL, #1
    LSR     AL, #1
    SUBB    AL, #1
    MOV     OUTER_COUNTER, AL
            
    DEC     STAGE_COUNTER
    BF      _ICFFT_f64_s_stages3andUp_loop, GEQ

    
    ;--------------------------------------------------------------------------
    ; The final stage is done seperately. In this stage each butterfly will
    ; divide by N and also swap the output prior to storing it
    ;                    Stage log2(N)
    ; --D0+jI0--------o-------*---((I0+I1*C-D1*S)+j(D0+D1*C+I1*S))/N--->
    ;                  \     /
    ;                   \   /
    ;                    \ /
    ;                     \
    ;                    / \
    ;                   /   \
    ;                  /     \
    ; --D1+jI1---C-jS-o--<-1>-*---((I0-I1*C+D1*S)+j(D0-D1*C-I1*S))/N--->
    ;--------------------------------------------------------------------------
_ICFFT_f64_s_stages3andUp_finalStage:
    ; Load "DataPtrInc" value and initialize XAR3 and XAR7 data pointers:
    MOVZ    AR0, DATA_PTR_INC
    NOP     *, ARP3
    NOP     *0++, ARP7          ; XAR3 = XAR3 + DataPtrInc, ARP -> XAR7
    NOP     *0++, ARP3          ; XAR7 = XAR7 + DataPtrInc, ARP -> XAR3
    MOVZ    AR0, TWIDDLES_PTR_INC
    SUBB    XAR3, #2            ; XAR3 = XAR3 + DataPtrInc - 2
    SUBB    XAR7, #2            ; XAR7 = XAR7 + DataPtrInc - 2

;;    ; Initialize OuterCounter (AR1):
;;    MOVZ        AR1, OUTER_COUNTER
    ; Initialize InnerCounter (AL):
    MOV         AL, INNER_COUNTER

    .align  2
    MOV32   R1L, *++            ; R1 = D1_1
    MOV32   R1H, *++, ARP4      ; ARP -> XAR4

    MOV32   R2L, *++            ;      R2 = COS_1
    MOV32   R2H, *0++, ARP3     ;                            , ARP -> XAR3
    MPYF64  R7, R1, R2          ; *|   R7 = D1_1*COS_1
 || MOV32   R0L, *++            ;  |   R0 = I1_1
    MOV32   R0H, *++, ARP5      ; 1|                         , ARP -> XAR5
    MOV32   R3L, *++            ; 2|   R3 = SIN_1
    MOV32   R3H, *0++, ARP3     ;                            , ARP -> XAR3
    MPYF64  R6, R0, R2          ; *|   R6 = I1_1*COS_1
    MPYF64  R5, R1, R3          ; 1|*| R5 = D1_1*SIN_1
                                ; 2|1| RPTB (4 cyc) falls in this delay slot
                                ;  |2| RPTB (4 cyc) falls in this delay slot
    .align  2
    RPTB    _ICFFT_f64_s_stages3andUp_finalStage_innerLoop, AL
    SUBF64  R6, R6, R5          ; *|   R6 = I1_1*COS_1 - D1_1*SIN_1
 || MOV32   R1L, *++            ;  |   R1 = D1_2
    MPYF64  R5, R0, R3          ; 1|*| R5 = I1_1*SIN_1
 || MOV32   R1H, *++, ARP2      ;  | |                       , ARP -> XAR2
    MOV32   R3L, *++            ; 2|1| R3 = D0_1
    MOV32   R3H, *++, ARP2      ;  |2|                       , ARP -> XAR2
    ADDF64  R7, R7, R5          ; *|   R7 = D1_1*COS_1 + I1_1*SIN_1
 || MOV32   R4L, *++            ;  |   R4 = I0_1
    MOV32   R4H, *++, ARP4      ; 1|                         , ARP -> XAR4
    ADDF64  R5, R4, R6          ; 2|*| R5 = I0_1 + (I1_1*COS_1 - D1_1*SIN_1)
 || MOV32   R2L, *++            ;  | | R2 = COS_2
    MOV32   R2H, *0++, ARP3     ;  |1|                       , ARP -> XAR3
    SUBF64  R4, R4, R6          ; *|2| R4 = I0_1 - (I1_1*COS_1 - D1_1*SIN_1)
 || MOV32   R0L, *++            ;  |   R0 = I1_2
    MOV32   R0H, *++, ARP6      ; 1|                         , ARP -> XAR6
    ADDF64  R6, R3, R7          ; 2|*| R6 = D0_1 + (D1_1*COS_1 + I1_1*SIN_1)
 || MOV32   *++, R5L            ;  | | Save R5
    MOV32   *++, R5H, ARP5      ;  |1|                       , ARP -> XAR5
    SUBF64  R7, R3, R7          ; *|2| R7 = D0_1 - (D1_1*COS_1 + I1_1*SIN_1)
 || MOV32   R3L, *++            ;  | | R3 = SIN_2  
    MOV32   R3H, *0++, ARP7     ; 1|                         , ARP -> XAR7 
    MPYF64  R5, R1, R3          ; 2|*| R5 = D1_2*SIN_2
 || MOV32   *++, R4L            ;  | | Save R4
    MOV32   *++, R4H, ARP6      ;  |1|                       , ARP -> XAR6
    MOV32   *++, R6L            ;  |2| Save R6
    MPYF64  R6, R0, R2          ; *|   R6 = I1_2*COS_2
 || MOV32   *++, R6H, ARP7      ;  |                         , ARP -> XAR7
    MOV32   *++, R7L            ; 1|   Save R7
    MPYF64  R7, R1, R2          ; 2|*| R7 = D1_2*COS_2
 || MOV32   *++, R7H, ARP3      ;  | |                       , ARP -> XAR3
                                ;  |1|   SUBF64  R6, R6, R5 (RPTB, line 1)                                        
                                ;  | | ||MOV32   R1L, *++            
                                ;  |2|   MOV32   R1H, *++, ARP2  (RPTB, line 2)  
_ICFFT_f64_s_stages3andUp_finalStage_innerLoop:
    MOVZ    AR0, DATA_PTR_INC
;;    MOVL    XAR4, CURR_COS_PTR
;;    MOVL    XAR5, CURR_SIN_PTR
 
    SUBF64  R6, R6, R5          ; *|     R6 = I1_2*COS_2 - D1_2*SIN_2
 || MOV32   R4H, *--, ARP2      ;  |     XAR3 -= 2 (dummy move), ARP -> XAR2     
    MPYF64  R5, R0, R3          ; 1|*|   R5 = I1_2*SIN_2
 || MOV32   R3L, *++            ;  | |   R3 = D0_2
    MOV32   R3H, *++, ARP2      ; 2|1|                         , ARP -> XAR2
    MOV32   R4L, *++            ;  |2|   R4 = I0_2
    ADDF64  R7, R7, R5          ; *|     R7 = D1_2*COS_2 + I1_2*SIN_2
 || MOV32   R4H, *++, ARP3      ;  |                           , ARP -> XAR3
    ADDF64  R5, R4, R6          ; 1|*|   R5 = I0_2 + (I1_2*COS_2 - D1_2*SIN_2)
    SUBF64  R4, R4, R6          ; 2|1|*| R4 = I0_2 - (I1_2*COS_2 - D1_2*SIN_2)
    NOP     *0++, ARP6          ;  |2|1| XAR3 += DataPtrInc (dummy move)
                                ;  | | |                       , ARP -> XAR6
    ADDF64  R6, R3, R7          ; *| |2| R6 = D0_2 + (D1_2*COS_2 + I1_2*SIN_2)
 || MOV32   *++, R5L            ;  | |   Save R5
    MOV32   *++, R5H, ARP7      ; 1| |                         , ARP -> XAR7
    SUBF64  R7, R3, R7          ; 2|*|   R7 = D0_2 - (D1_2*COS_2 + I1_2*SIN_2)
;; || MOV32   R1L, *++            ;  | |   R1 = D1_2
;;    MOV32   R1H, *++, ARP7      ;  |1|                         , ARP -> XAR7
 || MOV32   *++, R4L            ;  | |   Save R4               
    MOV32   *++, R4H, ARP6      ;  |1|                         , ARP -> XAR6
    MOV32   *++, R6L            ;  |2|   Save R6               
    MOV32   *++, R6H, ARP7      ;  |                           , ARP -> XAR7
    MOV32   *++, R7L            ;  |     Save R7               
    MOV32   *++, R7H, ARP4      ;  |                           , ARP -> XAR4
;;    MOVZ    AR0, TWIDDLES_PTR_INC
;;    BANZ    _ICFFT_f64_s_stages3andUp_finalStage, AR1--
    
    ; Swap input and output data pointers:
    ; XAR2 = CurrentOutPtr  
    ; XAR6 = CurrentInPtr
    ; CurrentInPtr  = XAR2
    ; CurrentOutPtr = XAR6  (swap pointers to indicate which is current output buffer)
    MOVL    XAR6, CURR_INPUT_PTR
    MOVL    XAR2, CURR_OUTPUT_PTR
    MOVL    CURR_INPUT_PTR, XAR2
    MOVL    CURR_OUTPUT_PTR, XAR6

    ; Scale the final output by the inverse scaling factor
    ; XAR2 points to the buffer to be scaled
    MOV     AL, FFT_SIZE 
    SUBB    AL, #1
    MOV32   R0L, INV_SCALE_FACTOR
    MOV32   R0H, INV_SCALE_FACTOR + 2
    .c28_amode
    CLRC    AMODE                       ; Set addressing mode to C28x  
    .align  2
    RPTB    _ICFFT_f64_s_stages3andUp_finalStage_scaling, AL
    MOV32   R1L, *+XAR2[0]      ;  |    R1 = x_r(i)
    MOV32   R1H, *+XAR2[2]      ;  |
    MPYF64  R1, R1, R0          ; *|    R1 = x_r(i)*ISF
    MOV32   R2L, *+XAR2[4]      ; 1|    R2 = x_i(i)
    MOV32   R2H, *+XAR2[6]      ; 2|
    MPYF64  R2, R2, R0          ; *|    R2 = x_i(i)*ISF
    MOV32   *XAR2++, R1L        ; 1|    Save R1
    MOV32   *XAR2++, R1H        ; 2|
    MOV32   *XAR2++, R2L        ;  |    Save R2
    MOV32   *XAR2++, R2H        ;  |
_ICFFT_f64_s_stages3andUp_finalStage_scaling:

;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
    ;; POP     XAR2
    ;; POP     XAR1
    ;; POP     XAR0
    LRETR
    .endasmfunc
    .unasg  LF_SIZE
    .unasg  STAGE_COUNTER
    .unasg  INNER_COUNTER
    .unasg  OUTER_COUNTER
    .unasg  DATA_PTR_INC
    .unasg  TWIDDLES_PTR_INC
    .unasg  CURR_SIN_PTR
    .unasg  CURR_COS_PTR
    .unasg  FFT_STAGES
    .unasg  FFT_SIZE
    .unasg  CURR_INPUT_PTR
    .unasg  CURR_OUTPUT_PTR
    .unasg  TWIDDLES_PTR
    .unasg  INV_SCALE_FACTOR
;; End of File
