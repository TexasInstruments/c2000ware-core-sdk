;;#############################################################################
;;! \file source/fpu64/fft/rfft_f64_unaligned.asm
;;!
;;! \brief  Unaligned Real Fast Fourier Transform (Double Precision)
;;! \author Vishal Coelho
;;! \date   07/27/2016
;;
;;  Revision History:
;;+----------+---------------+------------------------------------------------+
;;| DATE     | AUTHOR        | CHANGE                                         |
;;+----------+---------------+------------------------------------------------+
;;| 05/04/19 | Ritvik Sadana | Replaced RFFT_f64_u_calc with RFFT_f64u to     |
;;|          |               | keep function name consistent with fpu32.      |
;;+----------+---------------+------------------------------------------------+
;;
;; DESCRIPTION:
;;
;;  This function computes a real FFT.  The input buffer need not be
;;  aligned to a multiple (x4) of the FFT size. If it is possible to align the
;;  buffer to a x4 word boundary the faster RFFT_f64 function may be used 
;;  instead.
;;
;; FUNCTIONS:
;;  void RFFT_f64u (CFFT_F64_Handle)
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
;;  * FFTSize must be greater or equal to 32 and lesser or equal to 16384
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
;; The following 8 words of .ebss memory are blocked, i.e. they will all be 
;; assigned to the same page. This allows for the DP (data page) pointer to be
;; loaded once at the start of each of the sub functions used in this routine.
;; 
;; See https://e2e.ti.com/support/development_tools/compiler/int-compiler/f/85/p/526014/1918093#1918093
;; for a discussion on blocking.

;; Since these variables are on one page, and there are only 5, their offset 
;; is guaranteed to be within the 6-bit Direct DP addressing mode of the C28x.
;; So it is OK to interchangeably use the @@ (7-bit DP) and @ (6-bit DP)
;; addressing modes of the C2xLP and C28x respectively
;;
    .if __TI_EABI__
    .asg    ".bss", .ebss
    .asg    RFFTF64_U_vars, _RFFTF64_U_vars
    .endif 
_RFFTF64_U_vars_InPtr             .usect .ebss,2,1,1
_RFFTF64_U_vars_OutPtr            .usect .ebss,2,1,1
_RFFTF64_U_vars_TwiddlesPtr       .usect .ebss,2,1,1
_RFFTF64_U_vars_Stages            .usect .ebss,1,1,0
_RFFTF64_U_vars_FFTSize           .usect .ebss,1,1,0

;;*****************************************************************************
;; void RFFT_f64u(CFFT_f64_Handle) 
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
    .asg    RFFT_f64u, _RFFT_f64u
    .endif
    
    .page
    .global _RFFT_f64u
    .sect   ".text"
_RFFT_f64u:
    .asmfunc
    .asg    #2                             , LF_SIZE    
    .asg    *-SP[2]                        , LF_XAR4    
    .asg    *XAR4++                        , OBJ_INPTR  
    .asg    *XAR4++                        , OBJ_OUTPTR 
    .asg    *XAR4++                        , OBJ_TFPTR
    .asg    *+XAR4[4]                      , OBJ_STAGES 
    .asg    *+XAR4[5]                      , OBJ_FFTSIZE
    .asg    @_RFFTF64_U_vars_InPtr         , STAGE_1_2_3_INPUT_PTR
    .asg    @_RFFTF64_U_vars_OutPtr        , STAGE_1_2_3_OUTPUT_PTR
    .asg    @_RFFTF64_U_vars_TwiddlesPtr   , STAGE_4UP_TWIDDLES_PTR
    .asg    @_RFFTF64_U_vars_Stages        , FFT_STAGES
    .asg    @_RFFTF64_U_vars_FFTSize       , FFT_SIZE
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    PUSH    XAR1
    PUSH    XAR2
    PUSH    XAR3
    MOV32   *SP++, R4H
    MOV32   *SP++, R5H
    MOV32   *SP++, R6H
    MOV32   *SP++, R7H
;;-----------------------------------------------------------------------------
;; The complex FFT
;;-----------------------------------------------------------------------------
    ADDB    SP, LF_SIZE               ; create the local frame

    MOVL    XAR0, OBJ_INPTR           ; XAR0 = obj.p_input, save to stack
    ; Only have to load DP once as the global .ebss variables are on a
    ; single page
    MOVW    DP, #_RFFTF64_U_vars_InPtr
    MOVL    STAGE_1_2_3_INPUT_PTR, XAR0
    MOVL    XAR0,  OBJ_OUTPTR         ; XAR0 = obj.p_output, save to stack
    MOVL    STAGE_1_2_3_OUTPUT_PTR, XAR0
    MOVL    XAR0,  OBJ_TFPTR          ; XAR0 = obj.p_twiddles, save to stack
    MOVL    STAGE_4UP_TWIDDLES_PTR, XAR0
    MOVL    LF_XAR4, XAR4             ; save current index into the object
                                      ; to the local frame
    MOVZ    AR0,  OBJ_STAGES          ; AR0 = obj.stages, save to stack
    MOV     FFT_STAGES, AR0             
    MOVZ    AR0,  OBJ_FFTSIZE         ; AR0 = obj.FFTSize, save to stack
    MOV     FFT_SIZE, AR0
    
    LCR     _RFFT_f64u_stages1and2and3withBitReverse
    LCR     _RFFT_f64u_stages4andUp
    
    MOVL    XAR4, LF_XAR4             ; restore the object pointer
    
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
    .unasg  OBJ_STAGES 
    .unasg  OBJ_FFTSIZE
    .unasg  STAGE_1_2_3_INPUT_PTR
    .unasg  STAGE_1_2_3_OUTPUT_PTR
    .unasg  STAGE_4UP_TWIDDLES_PTR
    .unasg  FFT_STAGES
    .unasg  FFT_SIZE
    
;;*****************************************************************************
;; void RFFT_f64_stages1and2and3withBitReverse(void) 
;;
;; Stages 1, 2 (the trivial stages) and 3 with bit reverse addressing
;;
;; NOTE: 
;; - This function is not exposed in the C header and is local to this file
;; - Input buffer needn't be aligned
;;
;; Register Usage:                                                            
;;   XAR0 : 2*FFT size / output pointer increment                
;;   XAR1 : index for bit reversing
;;   XAR2 : pointer to the input
;;   XAR3 : pointer to output[2]
;;   XAR4 : pointer to output[6]
;;   XAR5 : pointer to output[0] 
;;   XAR6 : pointer to output[4]
;;   XAR7 : pointer to the twiddle factors
;;     AL : loop counter
;;     AH :
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                (SP)
;;   |_______|<- Copy of XAR0                 (SP-2) --> Local Frame
;;   |_______|<- rpc calling function         (SP-4)
;;
;;*****************************************************************************
    .page
    .sect   ".text"
_RFFT_f64u_stages1and2and3withBitReverse:
    .asmfunc
    .asg    @_RFFTF64_U_vars_InPtr        , STAGE_1_2_3_INPUT_PTR
    .asg    @_RFFTF64_U_vars_OutPtr       , STAGE_1_2_3_OUTPUT_PTR
    .asg    @_RFFTF64_U_vars_FFTSize      , FFT_SIZE
    .asg    @_RFFTF64_U_vars_TwiddlesPtr  , STAGE_1_2_3_TWIDDLES_PTR
    .asg    *-SP[2]                       , LF_XAR0
    .asg    #2                            , LF_SIZE
    
    .c28_amode
    CLRC    AMODE                       ; Set addressing mode to C28x
;;-----------------------------------------------------------------------------
;; Stages 1, 2 and 3
;;
;; NOTE: Instead of referring to the real part as Rn we choose Dn to avoid 
;; confusing them with the Rn FPU registers
;;
;;                 Stage 1    Stage 2
;; ---D0+jI0-o----*--D0`+jI0`--o--------*--D0^+jI0^--------o---------------*---D0^^+jI0^^--->
;;            \  /              \      /                    \             /    
;;             \/                \    /                      \           /     
;;             /\                 \  /                        \         /      
;;            /  \                 \/                          \       /       
;; ---D1+jI1-o----*--D1`+jI1`--o---/\---*--D1^+jI1^--------o----\-----/----*---D1^^+jI1^^--->
;;                              \ /  \ /                    \    \   /    /    
;;                               \    \                      \    \ /    /     
;;                              / \  / \                      \    /    /      
;; ---D2+jI2-o----*--D2`+jI2`--o---\/---*--D2^+jI2^--------o---\--/-\--/---*---D2^^+jI2^^--->
;;            \  /                 /\                       \   \/   \/   /    
;;             \/                 /  \                       \  /\   /\  /     
;;             /\                /    \                       \/  \ /  \/      
;;            /  \              /      \                      /\   \   /\      
;; ---D3+jI3-o----*--D3`+jI3`--o--------*--D3^+jI3^--------o-/--\-/-\-/--\-*---D3^^+jI3^^--->
;;                                                          /    \   \    \    
;; ---D4+jI4-o----*--D4`+jI4`--o--------*--D4^+jI4^--W8,0--o-\--/-(-1)\--/-*---D4^^+jI4^^--->
;;            \  /              \      /                      \/   \   \/      
;;             \/                \    /                       /\  / \  /\      
;;             /\                 \  /                       /  \/   \/  \     
;;            /  \                 \/                       /   /\   /\   \    
;; ---D5+jI5-o----*--D5`+jI5`--o---/\---*--D5^+jI5^--W8,1--o---/--(-1)-\---*---D5^^+jI5^^--->
;;                              \ /  \ /                      /    \    \      
;;                               \    \                      /    / \    \     
;;                              / \  / \                    /    /   \    \    
;; ---D6+jI6-o----*--D6`+jI6`--o---\/---*--D6^+jI6^--W8,2--o----/-(-1)\----*---D6^^+jI6^^--->
;;            \  /                 /\                          /       \       
;;             \/                 /  \                        /         \      
;;             /\                /    \                      /           \     
;;            /  \              /      \                    /             \    
;; ---D7+jI7-o----*--D7`+jI7`--o--------*--D7^+jI7^--W8,3--o------(-1)-----*---D7^^+jI7^^--->
;;
;; Each twiddle WN,k is of the form (e^-j2*pi*k/N) or (C-jS)
;;
;;   +-----+---------+-----+-----------------+-----+----------------+
;;   |   Stage 1     |   Stage 2             |   Stage 3            |
;;   +-----+---------+-----+-----------------+-----+----------------+
;;   | D0` |  D0+D1  | D0^ | (D0+D1)+(D2+D3) | D0^^| D0^+C*D4^+S*I1^|
;;   | I0` |  I0+I1  | I0^ | (I0+I1)+(I2+I3) | I0^^| I0^+C*I4^-S*D1^|
;;   | D1` |  D0-D1  | D1^ | (D0-D1)+(I2-I3) | D1^^| D1^+C*D5^+S*I5^|
;;   | I1` |  I0-I1  | I1^ | (I0-I1)-(D2-D3) | I1^^| I1^+C*I5^-S*D5^|
;;   | D2` |  D2+D3  | D2^ | (D0+D1)-(D2+D3) | D2^^| D2^+C*D6^+S*I6^|
;;   | I2` |  I2+I3  | I2^ | (I0+I1)-(I2+I3) | I2^^| I2^+C*I6^-S*D6^|
;;   | D3` |  D2-D3  | D3^ | (D0-D1)-(I2-I3) | D3^^| D3^+C*D7^+S*I7^|
;;   | I3` |  I2-I3  | I3^ | (I0-I1)+(D2-D3) | I3^^| I3^+C*I7^-S*D7^|
;;   | D4` |  D4+D5  | D4^ | (D4+D5)+(D6+D7) | D4^^| D0^-C*D4^-S*I1^|
;;   | I4` |  I4+I5  | I4^ | (I4+I5)+(I6+I7) | I4^^| I0^-C*I4^+S*D1^|
;;   | D5` |  D4-D5  | D5^ | (D4-D5)+(I6-I7) | D5^^| D1^-C*D5^-S*I5^|
;;   | I5` |  I4-I5  | I5^ | (I4-I5)-(D6-D7) | I5^^| I1^-C*I5^+S*D5^|
;;   | D6` |  D6+D7  | D6^ | (D4+D5)-(D6+D7) | D6^^| D2^-C*D6^-S*I6^|
;;   | I6` |  I6+I7  | I6^ | (I4+I5)-(I6+I7) | I6^^| I2^-C*I6^+S*D6^|
;;   | D7` |  D6-D7  | D7^ | (D4-D5)-(I6-I7) | D7^^| D3^-C*D7^-S*I7^|
;;   | I7` |  I6-I7  | I7^ | (I4-I5)+(D6-D7) | I7^^| I3^-C*I7^+S*D7^|
;;   +-----+---------+-----+-----------------+-----+----------------+
;;
;; Since the input is real only, we set all the 'In' to 0
;;
;;   +-----+------------------------------------------------------------------------+
;;   |   Stage 3  Simplifications                                                   |
;;   +-----+----------------+----------------+--------------------------------+-----+
;;   | D0^^| D0^+C*D4^+S*I1^|C=1,S=0         |(D0+D1)+(D2+D3)+(D4+D5)+(D6+D7) | (A) |
;;   | I0^^| I0^+C*I4^-S*D1^|C=1,S=0         |0                               |  -  |
;;   | D1^^| D1^+C*D5^+S*I5^|C=S=0.707       |(D0-D1)+|C|*((D4-D5)+(D7-D6))   | (B) |
;;   | I1^^| I1^+C*I5^-S*D5^|C=S=0.707       ||C|*((D7-D6)-(D4-D5))+(D3-D2)   | (H) |
;;   | D2^^| D2^+C*D6^+S*I6^|C=0,S=1         |(D0+D1)-(D2+D3)                 | (C) |
;;   | I2^^| I2^+C*I6^-S*D6^|C=0,S=1         |(D6+D7)-(D4+D5)                 | (G) |
;;   | D3^^| D3^+C*D7^+S*I7^|C=-0.707,S=0.707|(D0-D1)-|C|*((D4-D5)+(D7-D6))   | (D) |
;;   | I3^^| I3^+C*I7^-S*D7^|C=-0.707,S=0.707||C|*((D7-D6)-(D4-D5))-(D3-D2)   | (F) |
;;   | D4^^| D0^-C*D4^-S*I1^|C=1,S=0         |(D0+D1)+(D2+D3)-(D4+D5)-(D6+D7) | (E) |
;;   | I4^^| I0^-C*I4^+S*D1^|C=1,S=0         |0                               |  -  |
;;   | D5^^| D1^-C*D5^-S*I5^|C=S=0.707       |(D0-D1)-|C|*((D4-D5)+(D7-D6))   | (D) |
;;   | I5^^| I1^-C*I5^+S*D5^|C=S=0.707       |-(|C|*((D7-D6)-(D4-D5))-(D3-D2))|-(F) |
;;   | D6^^| D2^-C*D6^-S*I6^|C=0,S=1         |(D0+D1)-(D2+D3)                 | (C) |
;;   | I6^^| I2^-C*I6^+S*D6^|C=0,S=1         |-((D6+D7)-(D4+D5))              |-(G) |
;;   | D7^^| D3^-C*D7^-S*I7^|C=-0.707,S=0.707|(D0-D1)+|C|*((D4-D5)+(D7-D6))   | (B) |
;;   | I7^^| I3^-C*I7^+S*D7^|C=-0.707,S=0.707|-(|C|*((D7-D6)-(D4-D5))+(D3-D2))|-(H) |
;;   +-----+----------------+----------------+--------------------------------+-----+
;;
;; - We only store the unique non-zero entries A, B, C, D, E, F, G, H in that 
;; order
;; - Notice the output is complex conjugate about the midpoint, i.e.
;;   F(k) = F(N-k)*
;;   For example, F(1) = (B)+j(H) F(8-1)=F(7)=(B)+j(-(H))
;;                F(2) = (C)+j(G) F(8-2)=F(6)=(C)+j(-(G))
;;   This is true for all subsequent stages of the FFT. Thus, for any given
;;   FFT stage n <= log2(N), there are 
;;      - N/(2^(n-1)) butterflies
;;      - 2^n outputs per butterfly
;;   We save only the first half (2^(n-1)+1)of the outputs per butterfly since 
;;   the latter half is conjugate symmetric and not required in the computation
;;   of the next stage
;;-----------------------------------------------------------------------------
    ADDB    SP, LF_SIZE
    MOVW    DP,   #_RFFTF64_U_vars_InPtr
    MOVL    XAR2, STAGE_1_2_3_INPUT_PTR     ; XAR2 -> input buffer
    MOVL    XAR5, STAGE_1_2_3_OUTPUT_PTR    ; XAR5 -> output buffer
    MOVL    XAR3, STAGE_1_2_3_OUTPUT_PTR    ; XAR3 -> output buffer[2]
    ADDB    XAR3, #8
    MOVL    XAR4, STAGE_1_2_3_OUTPUT_PTR    ; XAR4 -> output buffer[6]
    ADDB    XAR4, #24
    MOVL    XAR6, STAGE_1_2_3_OUTPUT_PTR    ; XAR6 -> output buffer[4]
    ADDB    XAR6, #16
    MOVL    XAR7, STAGE_1_2_3_TWIDDLES_PTR  ; XAR7 -> twiddle table
    MOV     ACC, FFT_SIZE << #1             ; ACC = FFT size * 2
    MOVZ    AR0, AL                         ; XAR0 = [0:2*FFT size]
    MOVL    LF_XAR0, ACC                    ; save XAR0 to local frame
                                            ; since FFT_SIZE <= 2^14, AH = 0
    LSR     AL, #4
    SUBB    AL, #1                          ; AL = (FFT size/8)-1
    MOVL    XAR1, #0x0000                   ; start with an index of 0
    .align  2
    RPTB    _RFFT_f64u_stages1and2and3withBitReverse_loop, AL
;;   +-----+----------------------------------------------------+
;;   |   Stage 3  Simplifications                   | Save order|
;;   +-----+-----+----------------------------------------------+
;;   | D0^^| (D0+D1)+(D2+D3)+(D4+D5)+(D6+D7)  | (A) |    3      |
;;   | D1^^| (D0-D1)+|C|*((D7-D6)+(D4-D5))    | (B) |    7      |
;;   | D2^^| (D0+D1)-(D2+D3)                  | (C) |    1      |
;;   | D3^^| (D0-D1)-|C|*((D7-D6)+(D4-D5))    | (D) |    5      |
;;   | D4^^| (D0+D1)+(D2+D3)-((D4+D5)+(D6+D7))| (E) |    4      |
;;   | I3^^| |C|*((D7-D6)-(D4-D5))-(D3-D2)    | (F) |    8      |
;;   | I2^^| (D6+D7)-(D4+D5)                  | (G) |    2      |
;;   | I1^^| |C|*((D7-D6)-(D4-D5))+(D3-D2)    | (H) |    6      |
;;   +-----+-----+----------------------------------------------+
    MOV32   R0L, *+XAR2[AR1]    ;  | | | R0L = D0.L,                 ARP->XAR2
    ADRK    #2                  ;  | | | XAR2 += 2      
    MOV32   R0H, *+XAR2[AR1]    ;  | | | R0  = D0  ,                 ARP->XAR2
    NOP     *, ARP1             ;  | | |           ,                 ARP->XAR1
    NOP     *BR0++              ;  | | |           ,         XAR1 <rcadd>= AR0
                                                        
    MOV32   R1H, *+XAR2[AR1]    ;  | | | R1H = D1.H,                 ARP->XAR2
    SBRK    #2                  ;  | | | XAR2 -= 2      
    MOV32   R1L, *+XAR2[AR1]    ;  | | | R1  = D0  ,                 ARP->XAR2
    NOP     *, ARP1             ;  | | |           ,                 ARP->XAR1
    NOP     *BR0++              ;  | | |           ,         XAR1 <rcadd>= AR0
                                                        
    ADDF64  R2, R0, R1          ; *| | | R2  = D0+D1    
 || MOV32   R3L, *+XAR2[AR1]    ;  | | | R3L = D2.L,                 ARP->XAR2
    ADRK    #2                  ; 1| | | XAR2 += 2      
    MOV32   R3H, *+XAR2[AR1]    ; 2| | | R3  = D2  ,                 ARP->XAR2
    NOP     *, ARP1             ;  | | |           ,                 ARP->XAR1
    NOP     *BR0++              ;  | | |           ,         XAR1 <rcadd>= AR0
                                                        
    SUBF64  R0, R0, R1          ; *| | | R0  = D0-D1    
 || MOV32   R1H, *+XAR2[AR1]    ;  | | | R1H = D3.H,                 ARP->XAR2
    SBRK    #2                  ; 1| | | XAR2 -= 2      
    MOV32   R1L, *+XAR2[AR1]    ; 2| | | R1  = D3  ,                 ARP->XAR2
    NOP     *, ARP1             ;  | | |           ,                 ARP->XAR1
    NOP     *BR0++              ;  | | |           ,         XAR1 <rcadd>= AR0
                                         
    ADDF64  R4, R3, R1          ; *| | | R4  = D2+D3 
 || MOV32   R5L, *+XAR2[AR1]    ;  | | | R5L = D4.L,                 ARP->XAR2
    ADRK    #2                  ; 1| | | XAR2 += 2      
    MOV32   R5H, *+XAR2[AR1]    ; 2| | | R5  = D4  ,                 ARP->XAR2
    NOP     *, ARP1             ;  | | |           ,                 ARP->XAR1
    NOP     *BR0++              ;  | | |           ,         XAR1 <rcadd>= AR0
                                         
    SUBF64  R1, R1, R3          ; *| | | R1  = D3-D2
 || MOV32   R3H, *+XAR2[AR1]    ;  | | | R3H = D5.H,                 ARP->XAR2
    SBRK    #2                  ; 1| | | XAR2 -= 2      
    MOV32   R3L, *+XAR2[AR1]    ; 2| | | R3  = D5  ,                 ARP->XAR2
    NOP     *, ARP1             ;  | | |           ,                 ARP->XAR1
    NOP     *BR0++              ;  | | |           ,         XAR1 <rcadd>= AR0
                                         
    ADDF64  R6, R5, R3          ; *| | | R6  = D4+D5
 || MOV32   R7L, *+XAR2[AR1]    ;  | | | R7L = D6.L,                 ARP->XAR2
    ADRK    #2                  ; 1| | | XAR2 += 2      
    MOV32   R7H, *+XAR2[AR1]    ; 2| | | R7  = D6  ,                 ARP->XAR2
    NOP     *, ARP1             ;  | | |           ,                 ARP->XAR1
    NOP     *BR0++              ;  | | |           ,         XAR1 <rcadd>= AR0
    
    SUBF64  R5, R5, R3          ;  |*| | R5  = D4-D5
    SUBF64  R3, R2, R4          ; *|1| | R3  = (D0+D1)-(D2+D3)
    ADDF64  R2, R2, R4          ; 1|2|*| R2  = (D0+D1)+(D2+D3)
 || MOV32   R4H, *+XAR2[AR1]    ;  | | | R4H = D7.H,                 ARP->XAR2
    SBRK    #2                  ; 2| |1| XAR2 -= 2      
    MOV32   R4L, *+XAR2[AR1]    ;  | |2| R4  = D7  ,                 ARP->XAR2
    NOP     *, ARP1             ;  | | |           ,                 ARP->XAR1
    NOP     *BR0++              ;  | | |           ,         XAR1 <rcadd>= AR0
    
    MOV32   *XAR3++, R3L        ;  | | | save R3L
    ADDF64  R3, R7, R4          ; *| | | R3  = D6+D7 
 || MOV32   *XAR3++, R3H        ;  | | | save R3H
    SUBF64  R4, R4, R7          ; 1|*| | R4  = D7-D6
    MOVB    XAR0, #26           ; 2|1| | AR0 = #26
    ADDF64  R7, R3, R6          ;  |2|*| R7  = (D6+D7)+(D4+D5)
    SUBF64  R3, R3, R6          ; *| |1| R3  = (D6+D7)-(D4+D5)
    NOP                         ; 1| |2| NOP
    ADDF64  R6, R2, R7          ; 2|*| | R6  = (D0+D1)+(D2+D3)+(D6+D7)+(D4+D5)
    SUBF64  R2, R2, R7          ; *|1| | R2  = (D0+D1)+(D2+D3)-(D6+D7)-(D4+D5)
 || MOV32   *XAR4++, R3L        ;  | | | save R3L
    ADDF64  R3, R4, R5          ; 1|2|*| R3  = (D7-D6)+(D4-D5)
 || MOV32   *XAR4++, R3H        ;  | | | save R3H
    SUBF64  R4, R4, R5          ; 2|*|1| R4  = (D7-D6)-(D4-D5)
 || MOV32   R5L, *+XAR7[0]      ;  | | | R5L = COS.L
    MOV32   R5H, *+XAR7[2]      ;  |1|2| R5  = COS
    MPYF64  R3, R5, R3          ; *|2| | R3  = COS*((D7-D6)+(D4-D5))
 || MOV32   *XAR5++, R6L        ;  | | | save R6L
    MPYF64  R4, R5, R4          ; 1|*| | R4  = COS*((D7-D6)-(D4-D5))
 || MOV32   *XAR5++, R6H        ;  | | | save R6H
    MOV32   *XAR6++, R2L        ; 2|1| | save R2L
    SUBF64  R5, R0, R3          ; *|2| | R5  = (D0-D1)-COS*((D7-D6)+(D4-D5))
 || MOV32   *XAR6++, R2H        ;  | | | save R2H
    ADDF64  R6, R4, R1          ; 1|*| | R6  = COS*((D7-D6)-(D4-D5))+(D3-D2)
    ADDF64  R0, R0, R3          ; 2|1|*| R0  = (D0-D1)+COS*((D7-D6)+(D4-D5))
    SUBF64  R1, R4, R1          ; *|2|1| R1  = COS*((D7-D6)-(D4-D5))-(D3-D2)
 || MOV32   *XAR3++, R5L        ;  | | | save R5L,                    ARP->XAR3
    MOV32   *0++, R5H           ; 1| |2| save R5H, XAR3 += 26
    MOV32   *XAR4++, R6L        ; 2| | | save R6L,                    ARP->XAR4
    MOV32   *0++, R6H           ;  | | | save R6H, XAR4 += 26
    MOV32   *XAR5++, R0L        ;  | | | save R0L,                    ARP->XAR5
    MOV32   *0++, R0H           ;  | | | save R0H, XAR5 += 26
    MOV32   *XAR6++, R1L        ;  | | | save R1L,                    ARP->XAR6
    MOV32   *0++, R1H           ;  | | | save R1H, XAR6 += 26
    MOVL    XAR0, LF_XAR0       ;  | | | XAR0 = [0:2*FFT size]
_RFFT_f64u_stages1and2and3withBitReverse_loop:
    SUBB    SP, LF_SIZE
    LRETR
    .endasmfunc
    .unasg  STAGE_1_2_3_INPUT_PTR
    .unasg  STAGE_1_2_3_OUTPUT_PTR
    .unasg  FFT_SIZE
    .unasg  TWIDDLES_PTR

;;*****************************************************************************
;; void RFFT_f64_stages4andUp(void) 
;;
;; Stages 4 and up
;;
;; NOTE: 
;; - This function is not exposed in the C header and is local to this file
;;
;; Register Usage:                                                            
;;   XAR0 : 
;;   XAR1 : X3 pointer
;;   XAR2 : X1 pointer
;;   XAR3 : Inner Loop Counter
;;   XAR4 : X2 pointer
;;   XAR5 : X4 pointer
;;   XAR6 : Outer Loop Counter
;;   XAR7 : Cos/Sin pointer
;;     AL : 
;;     AH :
;;
;; Stack Usage:
;;
;;   |_______|<- stack pointer                        (SP)
;;   |_______|<-I1OFFSET                              (SP-1)
;;   |_______|<-I2I4OFFSET                            (SP-2)
;;   |_______|<-IDX_I                                 (SP-3)
;;   |_______|<-IDX_K                                 (SP-4)
;;   |_______|<-IDX_L                                 (SP-5)
;;   |_______|<-IDX_SZBL                              (SP-6)
;;   |_______|<-IDX_M                                 (SP-8)
;;   |_______|<-TEMPX1                                (SP-10)
;;   |_______|<-OUTBUF                                (SP-12)
;;   |_______|<-TWIDDLEBUF                           (SP-14)
;;   |_______|<- rpc calling function                 (SP-16)
;;
;;*****************************************************************************

;;-----------------------------------------------------------------------------
;;     Offsets for local variables stored on the stack
;;-----------------------------------------------------------------------------
X1X3OFFSET      .set        1           ; 16-bit
X2X4OFFSET      .set        2           ; 16-bit
IDX_I           .set        3           ; 16-bit
IDX_K           .set        4           ; 16-bit
IDX_L           .set        5           ; 16-bit
IDX_SZBL        .set        6           ; 16-bit
IDX_M           .set        8           ; 16-bit
TEMPX1          .set        (IDX_M+2*1) ; 32-bit
OUTBUF          .set        12
TWIDDLEBUF      .set        14
FRMSZ           .set        TWIDDLEBUF

    .page
    .sect   ".text"
_RFFT_f64u_stages4andUp:
    .asmfunc
    .asg    XAR1,                           X3ptr
    .asg    XAR2,                           X1ptr
    .asg    AR3,                            InnerLoopCnt
    .asg    XAR4,                           X2ptr
    .asg    XAR5,                           X4ptr
    .asg    AR6,                            OuterLoopCnt
    .asg    XAR7,                           COSptr
    .asg    XAR7,                           SINptr
    .asg    @_RFFTF64_U_vars_InPtr,         STAGE_4_UP_INPUT_PTR    
    .asg    @_RFFTF64_U_vars_OutPtr,        STAGE_4_UP_OUTPUT_PTR    
    .asg    @_RFFTF64_U_vars_TwiddlesPtr,   STAGE_4_UP_TWIDDLES_PTR
    .asg    @_RFFTF64_U_vars_Stages,        STAGE_4_UP_FFT_STAGES     
    .asg    @_RFFTF64_U_vars_FFTSize,       STAGE_4_UP_FFT_SIZE
    
    .c28_amode
    CLRC    AMODE                       ; Set addressing mode to C28x
    ADDB    SP,#FRMSZ
;;-----------------------------------------------------------------------------
;;      Initialize loop counters and offsets
;;      Note: Index k has changed from 3 to 2 due to loop unrolling.
;;-----------------------------------------------------------------------------
    MOV     *-SP[X1X3OFFSET], #52       ; I1 & I3 pointer offset
    MOV     *-SP[X2X4OFFSET], #76       ; I2 & I4 pointer offset
    MOV     *-SP[IDX_K], #(2-1)         ; Inner loop count
    MOV     *-SP[IDX_L], #(16*4)        ; 16 64-bit values calculated each
                                        ; inner loop for the first stage
;;-----------------------------------------------------------------------------
;;      Check the FFTStages and compute stage, outer loop count
;;-----------------------------------------------------------------------------
    MOVW    DP, #_RFFTF64_U_vars_InPtr    ; Load the DP once
    MOV     AL, STAGE_4_UP_FFT_STAGES
    SUB     AL, #3                      ; If (fft->FFTStages <= 3) exit
    B       _RFFT_f64u_stages4andUp_end, LEQ
    MOV     *-SP[IDX_I], AL             ; IDX_I = FFTStages - 3 = i for 
                                        ; stages loop control
    MOV     AL, STAGE_4_UP_FFT_SIZE
    ASR     AL, #4
    MOV     *-SP[IDX_SZBL], AL          ; IDX_SZBL = FFTSize/16
    DEC     AL
    MOV     AR6, AL                     ; IDX_M = FFTSize/16-1 = m for 
                                        ; outer loop control
;;-----------------------------------------------------------------------------
;;    Initialize pointers
;;-----------------------------------------------------------------------------
    MOVL    ACC, STAGE_4_UP_TWIDDLES_PTR
    MOVL    *-SP[TWIDDLEBUF], ACC
    ADDB    ACC, #16
    MOVL    *-SP[TEMPX1], ACC               ; TEMPX1 = &TwiddleBuf[4]
        
    MOVL    X1ptr, STAGE_4_UP_OUTPUT_PTR    ; X1ptr = &OutBuf[0]
    MOVL    *-SP[OUTBUF], X1ptr
    MOVL    X2ptr, *-SP[OUTBUF]             ; X2ptr = &OutBuf[0]
    ADDB    X2ptr, #32                      ; X2ptr = &OutBuf[8]
    MOVL    X4ptr, *-SP[OUTBUF]             ; X4ptr = &OutBuf[0]
    ADDB    X4ptr, #64                      ; X4ptr = &OutBuf[16]    
    MOVL    X3ptr, X2ptr                    ; X3ptr = &OutBuf[8]
    
    MOV     InnerLoopCnt, #(2-1)            ; Inner loop count for 4th stage

;;-----------------------------------------------------------------------------
;; Stage 4 and Up    
;;-----------------------------------------------------------------------------
_RFFT_f64u_stages4andUp_stageLoop:
;;-----------------------------------------------------------------------------
;;
;; NOTE: Instead of referring to the real part as Rn we choose Dn to avoid 
;; confusing them with the Rn FPU registers
;;
;; Shown below is the butterfly group from stage 4. The calculations here are
;; identical for future stages.
;;
;; D0-----------------o---------------o----(D0+D5)-------------------------------->
;;                     \             /                                        
;; D1+jI1-------------o-\-----------/-o----(D1+(D6*C1+I6*S1))+j((I6*C1-D6*S1)+I1)->
;;                     \ \         / /  
;; D2+jI2-------------o-\-\-------/-/-o----(D2+(D7*C2+I7*S2))+j((I7*C2-D7*S2)+I2)->
;;                     \ \ \     / / /  
;; D3+jI3-------------o-\-\-\---/-/-/-o----(D3+(D8*C3+I8*S3))+j((I8*C3-D8*S3)+I3)->
;;                     \ \ \ \ / / / /  
;; D4-----------------o-\-\-\-X-/-/-/-o----(D4-jD9)------------------------------->
;;                     \ \ \ X X / / /  
;; D3-jI3-------------o-\-\-X-X-X-/-/-o----(D3-(D8*C3+I8*S3))+j((I8*C3-D8*S3)-I3)->
;;                     \ \ X X X X / /  
;; D2-jI2-------------o-\-X-X-X-X-X-/-o----(D2-(D7*C2+I7*S2))+j((I7*C2-D7*S2)-I2)->
;;                     \ X X X X X X /  
;; D1-jI1-------------o-X-X-X-X-X-X-X-o----(D1-(D6*C1+I6*S1))+j((I6*C1-D6*S1)-I1)->
;;                     X X X X X X X X  
;; D5------(  1-j0 )--o-X-X-X-X-X-X-X-o----(D0-D5)-------------------------------->
;;                     / X X X X X X \  
;; D6+jI6--( C1-jS1)--o-/-X-X-X-X-X-\-o----(D1-(D6*C1+I6*S1))-j((I6*C1-D6*S1)-I1)->
;;                     / / X X X X \ \  
;; D7+jI7--( C2-jS2)--o-/-/-X-X-X-\-\-o----(D2-(D7*C2+I7*S2))-j((I7*C2-D7*S2)-I2)->
;;                     / / / X X \ \ \  
;; D8+jI8--( C3-jS3)--o-/-/-/-X-\-\-\-o----(D3-(D8*C3+I8*S3))-j((I8*C3-D8*S3)-I3)->
;;                     / / / / \ \ \ \  
;; D9------(  0-1j )--o-/-/-/---\-\-\-o----(D4+jD9)------------------------------->
;;                     / / /     \ \ \  
;; D8-jI8--(-C3-jS3)--o-/-/-------\-\-o----(D3+(D8*C3+I8*S3))-j((I8*C3-D8*S3)+I3)->
;;                     / /         \ \  
;; D7-jI7--(-C2-jS2)--o-/-----------\-o----(D2+(D7*C2+I7*S2))-j((I7*C2-D7*S2)+I2)->
;;                     /             \  
;; D6-jI6--(-C1-jS1)--o---------------o----(D1+(D6*C1+I6*S1))-j((I6*C1-D6*S1)+I1)->
;;
;; Notice we need only save the first 9 complex outputs, the rest are complex
;; conjugates about the 8th entry. 
;;
;; The inputs from stage 3 were stored in this order
;; +--+-----------+--------------------+--+------------+
;; |IN| Ptr (Xn)  |OUT                 |Yn|Pointer dir |
;; +--+-----------+--------------------+--+------------+
;; |D0|<- X1ptr ->| D0+D5              |Y1|      *     |
;; |D1|<- X1ptr ->| D1+(D6*COS+I6*SIN) |Y1|      |     |
;; |D2|<- X1ptr ->| D2+(D7*COS+I7*SIN) |Y1|      |     |
;; |D3|<- X1ptr ->| D3+(D8*COS+I8*SIN) |Y1|      v     |
;; |D4|           | D4 (pass through)  |- |            |
;; |I3|<- X2ptr ->| D3-(D8*COS+I8*SIN) |Y2|      ^     |
;; |I2|<- X2ptr ->| D2-(D7*COS+I7*SIN) |Y2|      |     |
;; |I1|<- X2ptr ->| D1-(D6*COS+I6*SIN) |Y2|      *     |
;; +--+-----------+--------------------+--+------------+
;; |D5|<- X3ptr ->| D0-D5              |Y3|      *     |
;; |D6|<- X3ptr ->| (I6*COS-D6*SIN)-I1 |Y3|      |     |
;; |D7|<- X3ptr ->| (I7*COS-D7*SIN)-I2 |Y3|      |     |
;; |D8|<- X3ptr ->| (I8*COS-D8*SIN)-I3 |Y3|      v     |
;; |D9|<- X4ptr ->|  -D9 (negate, save)|Y4|     .-.    |
;; |I8|<- X4ptr ->| (I8*COS-D8*SIN)+I3 |Y4|     | v    |
;; |I7|<- X4ptr ->| (I7*COS-D7*SIN)+I2 |Y4|     |      |
;; |I6|<- X4ptr ->| (I6*COS-D6*SIN)+I1 |Y4|     *      |
;; +--+-----------+--------------------+--+------------+
;; Outer Loop: IDX_M
;;      Stage 4: M = 1 to FFTSize/16
;;      Stage 5: M = 1 to FFTSize/32
;;      Stage 6: M = 1 to FFTSize/64  etc..
;; 
;; Calculate the following M times (Xn the input, Yn the output):
;; 
;;      X1 = *X1ptr;
;;      X3 = *X3ptr;
;;      *X1ptr++ = Y1 = (X1 + X3)
;;      *X3ptr++ = Y3 = (X1 - X3)
;;      for(j=1; j <= k; j ++)
;;      {
;;         X1       = *X1ptr;
;;         X2       = *X2ptr;
;;         X3       = *X3ptr;
;;         X4       = *X4ptr;
;;         COS      = *COSptr++;
;;         SIN      = *COSptr++;
;;         *X1ptr++ = Y1 = X1 + (X3*COS + X4*SIN);        (A)
;;         *X2ptr-- = Y2 = X1 - (X3*COS + X4*SIN);        (B)
;;         *X3ptr++ = Y3 = (X4*COS - X3*SIN) - X2;        (C)
;;         *X4ptr-- = Y4 = (X4*COS - X3*SIN) + X2;        (D)
;;      }
;;      *X4ptr = Y4 = -X4 (*X4ptr)
;;-----------------------------------------------------------------------------
_RFFT_f64u_stages4andUp_outerLoop:
    MOVL    COSptr, *-SP[TEMPX1]
    MOV32   R1L, *+X1ptr[0]         ;  | | | R1L = X1.L
    MOV32   R1H, *+X1ptr[2]         ;  | | | R1  = X1                       (1)
    MOV32   R3L, *+X3ptr[0]         ;  | | | R3L = X3.L
    MOV32   R3H, *+X3ptr[2]         ;  | | | R3  = X3                       (1)
    ADDF64  R2, R1, R3              ; *| | | R2  = X1+X3                    (1)
 || MOV32   R0L, *COSptr++          ;  | | | R0L = COS.L
    SUBF64  R4, R1, R3              ; 1|*| | R4  = X1-X3                    (1)
 || MOV32   R0H, *COSptr++          ;  | | | R0  = COS                      (1)
    MOV32   R3L, *+X3ptr[4]         ; 2|1| | R3L = X3.L                     
    MOV32   R3H, *+X3ptr[6]         ;  |2| | R3  = X3                       (2)
    MOV32   *X1ptr++, R2L           ;  | | | 
    MPYF64  R1, R3, R0              ; *| | | R1  = X3*COS
 || MOV32   *X1ptr++, R2H           ;  | | | save Y1                        (1)
    MOV32   R6H, *--X4ptr           ; 1| | | R6H = X4.H
    MOV32   R6L, *--X4ptr           ; 2| | | R6  = X4                       (1)
    MPYF64  R2, R6, R0              ; *| | | R2  = X4*COS
 || MOV32   R7L, *SINptr++          ;  | | | R7L = SIN.L
    MOV32   R7H, *SINptr++          ; 1| | | R7  = SIN                      (1)
    MPYF64  R3, R3, R7              ; 2|*| | R3  = X3*SIN
 || MOV32   *X3ptr++, R4L           ;  | | | 
    MOV32   *X3ptr++, R4H           ;  |1| | save Y3                        (1)
    .align  2
    RPTB    _RFFT_f64u_stages4andUp_innerLoop, InnerLoopCnt
    MPYF64  R4, R6, R7              ; *|2| | R4  = X4*SIN
 || MOV32   R6H, *--X2ptr           ;  | | | R6H = X2.H
    MOV32   R6L, *--X2ptr           ; 1| | | R6  = X2                       (1)
    SUBF64  R7, R2, R3              ; 2|*| | R7  = X4*COS - X3*SIN
 || MOV32   R0L, *COSptr++          ;  | | | R0L = COS.L
    MOV32   R0H, *COSptr++          ;  |1| | R0  = COS                      (2)
    ADDF64  R3, R1, R4              ; *|2| | R3  = X3*COS + X4*SIN
 || MOV32   R5L, *+X3ptr[4]         ;  | | | R5L = X3.L
    MOV32   R5H, *+X3ptr[6]         ; 1| | | R5  = X3                       (3)
    SUBF64  R2, R7, R6              ; 2|*| | R2  = (X4*COS - X3*SIN) - X2   (1)
 || MOV32   R4L, *+X1ptr[0]         ;  | | | R4L = X1.L
    MOV32   R4H, *+X1ptr[2]         ;  |1| | R4  = X1                       (2)
    ADDF64  R7, R7, R6              ; *|2| | R7  = (X4*COS - X3*SIN) + X2   (1)
 || MOV32   R6H, *--X4ptr           ;  | | | R6H = X4.H
    MOV32   R6L, *--X4ptr           ; 1| | | R6  = X4                       (2)
    MOV32   *X3ptr++, R2L           ; 2| | | 
    ADDF64  R2, R4, R3              ; *| | | R2  = X1 + (X3*COS + X4*SIN)   (1)
 || MOV32   *X3ptr++, R2H           ;  | | | save Y3                        (2)
    SUBF64  R4, R4, R3              ; 1|*| | R4  = X1 - (X3*COS + X4*SIN)   (1)
 || MOV32   *+X4ptr[4], R7L         ;  | | | 
    MOV32   *+X4ptr[6], R7H         ; 2|1| | save Y4                        (1)
    MPYF64  R1, R5, R0              ; *|2| | R1  = X3*COS
 || MOV32   *X1ptr++, R2L           ;  | | |
    MOV32   *X1ptr++, R2H           ; 1| | | save Y1                        (2)
    MPYF64  R2, R6, R0              ; 2|*| | R2  = X4*COS
 || MOV32   R7L, *SINptr++          ;  | | | R7L = SIN.L
    MOV32   R7H, *SINptr++          ;  |1| | R7  = SIN                      (2)
    MPYF64  R3, R5, R7              ; *|2| | R3  = X3*SIN
 || MOV32   *+X2ptr[0], R4L         ;  | | |
    MOV32   *+X2ptr[2], R4H         ; 1| | | save Y2                        (1)
_RFFT_f64u_stages4andUp_innerLoop:

    MPYF64  R4, R6, R7              ; 2|*| | R4  = X4*SIN
 || MOV32   R6H, *--X2ptr           ;  | | | R6H = X2.H
    MOV32   R6L, *--X2ptr           ;  |1| | R6  = X2                       (2)
    SUBF64  R7, R2, R3              ; *|2| | R7  = X4*COS - X3*SIN
 || MOV32   R0H, *--X4ptr           ;  | | | R0H = X4.H
    MOV32   R0L, *--X4ptr           ; 1| | | R0  = X4                       (3)
    ADDF64  R3, R1, R4              ; 2|*| | R3  = X3*COS + X4*SIN
    NEGF64  R0, R0                  ;  |1| | R0  = -X4
    SUBF64  R2, R7, R6              ; *|2| | R2  = (X4*COS - X3*SIN) - X2   (2)
 || MOV32   *X4ptr++, R0L           ;  | | |
    MOV32   *X4ptr++, R0H           ; 1| | | save Y4                        (2)
    ADDF64  R7, R7, R6              ; 2|*| | R7  = (X4*COS - X3*SIN) + X2   (2)
 || MOV32   R4L, *+X1ptr[0]         ;  | | | R4L = X1.L
    MOV32   R4H, *+X1ptr[2]         ;  |1| | R4  = X1                       (3)
    MOV32   *+X3ptr[0], R2L         ;  |2| |
    ADDF64  R2, R4, R3              ; *| | | R2  = X1 + (X3*COS + X4*SIN)   (2)
 || MOV32   *+X3ptr[2], R2H         ;  | | | save Y3                        (3)
    SUBF64  R4, R4, R3              ; 1|*| | R4  = X1 - (X3*COS + X4*SIN)   (2)
 || MOV32   *+X4ptr[0], R7L         ;  | | |
    MOV32   *+X4ptr[2], R7H         ; 2|1| | save Y4                        (3)
    MOV32   *+X1ptr[0], R2L         ;  |2| | 
    MOV32   *+X1ptr[2], R2H         ;  | | | save Y1                        (3)
    MOV32   *+X2ptr[0], R4L         ;  | | | 
    MOV32   *+X2ptr[2], R4H         ;  | | | save Y2                        (2)
    
    MOVU    ACC, *-SP[X1X3OFFSET]   ; ACC = X1X3OFFSET
    ADDL    X1ptr, ACC              ; X1ptr += X1X3OFFSET
    ADDL    X3ptr, ACC              ; X3ptr += X1X3OFFSET
    MOVU    ACC, *-SP[X2X4OFFSET]   ; ACC = X2X4OFFSET
    ADDL    X2ptr, ACC              ; X2ptr += X2X4OFFSET
    ADDL    X4ptr, ACC              ; X4ptr += X2X4OFFSET
    
    BANZ    _RFFT_f64u_stages4andUp_outerLoop, OuterLoopCnt--
;------------------------------------------------------------------------------
;   End of Outer Loop
;   Adjust loop counts and pointer offsets
;------------------------------------------------------------------------------
    MOVU    ACC, *-SP[IDX_SZBL]     ; IDX_SZBL = IDX_SZBL/2
    ASR     AL, #1                    
    MOV     *-SP[IDX_SZBL], AL        
    DEC     AL                        
    MOV     AR6, AL                 ; Outer Loop Count = IDX_SZBL - 1
                                      
    MOVL    ACC, XAR3               ; Inner Loop Count
    LSL     ACC, #1                 
    ADDB    ACC, #3
    MOVL    XAR3, ACC
    
    MOVU    ACC, *-SP[X1X3OFFSET]   ; X1X3OFFSET = X1X3OFFSET*2 - 4
    LSL     ACC, #1
    SUBB    ACC, #4
    MOV     *-SP[X1X3OFFSET], AL
    
    MOVU    ACC, *-SP[X2X4OFFSET]   ; X2X4OFFSET = X2X4OFFSET*2 + 4
    LSL     ACC, #1
    ADDB    ACC, #4
    MOV     *-SP[X2X4OFFSET], AL
    
;------------------------------------------------------------------------------
;   Update pointers for the next iteration of FFTStage loop
;------------------------------------------------------------------------------
    MOVL    COSptr, *-SP[TWIDDLEBUF] ; COSptr = &TwiddleBuf[0] 
    MOVL    X1ptr,  *-SP[OUTBUF]     ; X1ptr  = &output buffer[0]    
    MOVL    X2ptr,  *-SP[OUTBUF]
    MOVL    X3ptr,  *-SP[OUTBUF]
    MOVL    X4ptr,  *-SP[OUTBUF]
    
    MOVU    ACC, *-SP[IDX_L]
    ADDL    COSptr, ACC
    SUBB    COSptr, #16             ; COSptr = &TwiddleBuf[L/2 - 4]
    MOVL    *-SP[TEMPX1], COSptr
    
    ADDL    X2ptr, ACC              ; X2ptr = &output buffer[L]
    MOVL    X3ptr, X2ptr            ; X3ptr = &output buffer[L]
    LSL     ACC, #1
    MOV     *-SP[IDX_L], AL         ; IDX_L = L*2
    ADDL    X4ptr, ACC              ; X4ptr = &output buffer[2*L]
    
    DEC     *-SP[IDX_I]             ; IDX_I--
    BF      _RFFT_f64u_stages4andUp_stageLoop, NEQ

_RFFT_f64u_stages4andUp_end:
    SUBB    SP, #FRMSZ
    LRETR
    .endasmfunc
    .unasg  X3ptr
    .unasg  X1ptr
    .unasg  InnerLoopCnt
    .unasg  X2ptr
    .unasg  X4ptr
    .unasg  OuterLoopCnt
    .unasg  COSptr
    .unasg  SINptr
    .unasg  STAGE_4_UP_INPUT_PTR    
    .unasg  STAGE_4_UP_OUTPUT_PTR    
    .unasg  STAGE_4_UP_TWIDDLE_PTR
    .unasg  STAGE_4_UP_FFT_STAGES     
    .unasg  STAGE_4_UP_FFT_SIZE
;; End of File
   
