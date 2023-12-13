;;#############################################################################
;;! \file source/fpu64/fft/rfft_f64_scaled_mag.asm
;;!
;;! \brief  Real Fast Fourier Transform Scaled Magnitude (Double Precision)
;;! \author Vishal Coelho
;;! \date   07/29/2016
;;
;;  Revision History:
;;+----------+---------------+------------------------------------------------+
;;| DATE     | AUTHOR        | CHANGE                                         |
;;+----------+---------------+------------------------------------------------+
;;| 05/04/19 | Ritvik Sadana | Replaced RFFT_f64_s_mag with RFFT_f64s_mag to  |
;;|          |               | keep function name consistent with fpu32.      |
;;+----------+---------------+------------------------------------------------+
;;
;; DESCRIPTION:
;;
;;   Calculates the scaled magnitude for the 64-bit double precision floating
;;   point real FFT.
;;
;; FUNCTIONS:
;;
;;  void RFFT_f64s_mag (CFFT_F64_Handle)
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
;;  * RFFT_f64() has been called prior to this function
;;  * FFTSize is a power of 2 (atleast 32)
;;
;; ALGORITHM:
;;
;;     Calculate the complex FFT magnitude. The data is organized as follows in
;;     the output buffer after calculating FFT:
;;
;;  +----------------------------+
;;  |  R(0)                      | 0
;;  |  R(1)                      |
;;  |  R(2)                      | 
;;  |  R(3)                      |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .  R(FFTSize/2 - 1)          .
;;  |  R(FFTSize/2) = fs/2       |
;;  |  I(FFTSize/2 - 1)          |
;;  .  I(FFTSize/2 - 2)          .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  I(N-4)                    | 
;;  |  I(N-3)                    |
;;  |  I(N-2)                    |
;;  |  I(N-1)                    | FFTSize - 1
;;  +----------------------------+
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
    
;; defines

;; file globals
	.if __TI_EABI__
	.sect   ".const"
	.else
	.sect   ".econst"
	.endif
_ONE_O_SQRT_2:
    .field  0x667F3BC8, 32   ;1/sqrt(2) = 0.707106781186547
    .field  0x3FE6A09E, 32

;;*****************************************************************************
;; void RFFT_f64s_mag(CFFT_f64_Handle)
;;
;; The function takes a handle to the CFFT_f64 object as an argument. 
;;
;; Register Usage:                                                            
;;   XAR0 :            
;;   XAR1 : 
;;   XAR2 : 
;;   XAR3 :           
;;   XAR4 : points to the object                              
;;   XAR5 : points to the buffer (output pointer)                    
;;   XAR6 : points to the input buffer[1]       
;;   XAR7 : points to the input buffer[N-1]                
;;     AL : 
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer       (SP)
;;   |_______|<- ISF_H_H             (SP-1)----+-> Local Frame
;;   |_______|<- ISF_H, ISF_H_L      (SP-2)    |
;;   |_______|<- ISF_L               (SP-4)    |
;;   |_______|<- ISF2_H_H            (SP-5)    |
;;   |_______|<- ISF2_H, ISF2_H_L    (SP-6)    |
;;   |_______|<- ISF2_L              (SP-8)----'
;;   |_______|<- R7H                 (SP-10)
;;   |_______|<- R6H                 (SP-12)
;;   |_______|<- R5H                 (SP-14)
;;   |_______|<- R4H                 (SP-16)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg    RFFT_f64s_mag, _RFFT_f64s_mag
    .endif
    
    .page
    .global _RFFT_f64s_mag
    .sect   ".text"
_RFFT_f64s_mag:
    .asmfunc
    .asg    *+XAR4[0], OBJ_CURR_INPUT_PTR
    .asg    *+XAR4[2], OBJ_CURR_OUTPUT_PTR
    .asg    *+XAR4[4], OBJ_STAGES 
    .asg    *+XAR4[5], OBJ_FFTSIZE
    .asg    #1023    , DP_EXP_BIAS
    .asg    #0x7FF0  , DP_EXP_MASK
    .asg    *-SP[1]  , ISF_H_H
    .asg    *-SP[2]  , ISF_H_L
    .asg    *-SP[2]  , ISF_H
    .asg    *-SP[4]  , ISF_L
    .asg    *-SP[5]  , ISF2_H_H
    .asg    *-SP[6]  , ISF2_H_L
    .asg    *-SP[6]  , ISF2_H
    .asg    *-SP[8]  , ISF2_L
    .asg    #4       , LF_SIZE
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    MOV32      *SP++, R4H
    MOV32      *SP++, R5H
    MOV32      *SP++, R6H
    MOV32      *SP++, R7H
    ADDB        SP, LF_SIZE
;;-----------------------------------------------------------------------------
;; The Complex FFT Magnitude
;;-----------------------------------------------------------------------------
    ADDB        XAR4, #6
    MOVL        XAR5, OBJ_CURR_OUTPUT_PTR
    MOVL        XAR6, OBJ_CURR_INPUT_PTR; XAR6 -> input[0]
    MOVL        ACC, OBJ_CURR_INPUT_PTR ; ACC  -> input[0]
    ADD         ACC, OBJ_FFTSIZE << #2  ; ACC  -> input[N]
    MOVL        XAR7, ACC               ; XAR7 -> input[N]
    MOV         ACC, OBJ_FFTSIZE << #14 ; AH  = FFTSize/4
    SUB         AH, #1                  ; AH  = FFTSize/4 - 1
    MOVZ        AR0, AH                 ; AR0 = FFTSize/4 - 1

    ;--------------------------------------------------------------------------
    ; We need to scale down the final output by 1/(N/2), i.e. 1/(2^(stages-1)). 
    ; The scale factor is a double precision value of the form 
    ;                    (-1)^S.(1.M)x2^(E-1023)
    ; where M is the 52 bit mantissa, E the 11 bit exponent, and S the sign of 
    ; the value. 
    ; Since N is some power of 2 the inverse scaling factor (ISF) will
    ; be a negative power of 2. For example, for a 1024 (2^10) point FFT the 
    ; ISF is 2^-(10-1) or 0.001953125
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
    ;
    ; We need an additional scaling factor for Y[0] and Y[N/2] which are 
    ; handled outside the loop, we need to multiply them directly with 
    ; sqrt(1/(N/2)). We can do this without taking the actual square root 
    ; as follows
    ; sqrt(1/(N/2)) = (1/2^(s-1))^0.5
    ;               = 2^(-0.5*(s-1))
    ; for odd number of stages s-1 is even and we get 2^-p, p = (s-1)/2
    ; for even number of stages s-1 is odd and we get 2^-(p+0.5), 
    ;                                                       p = flr((s-1)/2)
    ;  i.e. for even number of stages 2^-p * 0.707106781186547
    ;--------------------------------------------------------------------------
    ZAPA                                ; ACC = 0, P = 0
    MOV         AH, DP_EXP_BIAS         ; AH = dp_exponent_bias (1023)
    MOV         AL, OBJ_STAGES          ; AL = #stages (s)
    DEC         AL                      ;    = s - 1
    SUB         AH, AL                  ; AH = 1023 - (s - 1)
    LSR         AL, #1                  ; AL = (s - 1)/2
    NEG         AL                      ;    = -(s - 1)/2
    ADD         AL, DP_EXP_BIAS         ;    = 1023 - (s - 1)/2
    LSL         ACC, #4                 ; shift biased expoenent to its place
    MOVL        ISF_L, P                ; Save the ISF to the stack
    MOV         ISF_H_L, #0
    MOV         ISF_H_H, AH
    
    MOVL        ISF2_L, P               ; Save the ISF2 to the stack
    MOV         ISF2_H_L, #0
    MOV         ISF2_H_H, AL
    
    TBIT        OBJ_STAGES, #0          ; if #stages even, TC = 0 else TC = 1
    ZERO        R1                      ; R1 = 0.0
    MOV32       R1H, ISF2_H             ;    = ISF2 (ISF2_L will be 0)
    BF          _RFFT_f64s_mag_oddStages, TC
_RFFT_f64s_mag_evenStages:
    MOVW        DP, #_ONE_O_SQRT_2
    MOV32       R2L, @_ONE_O_SQRT_2     ; R2 = 1/sqrt(2)
    MOV32       R2H, @_ONE_O_SQRT_2 + 2
    MPYF64      R1, R1, R2              ; *| R1 = ISF2*(1/sqrt(2))
    NOP                                 ; 1|
    NOP                                 ; 2|
                                        ;   new ISF2 is not saved to the stack
                                        ;   as its only used once for Re[0]
                           
_RFFT_f64s_mag_oddStages:

    
    ; mag[0] is done out of the loop
    MOV32       R0L, *XAR6++            ;        R0 = Re[0]
    MOV32       R0H, *XAR6++   
    ABSF64      R0, R0                  ;        R0 = |Re[0]|
    MPYF64      R0, R0, R1              ; *|     R0 = ISF2*|Re[0]|
    NOP                                 ; 1|
    NOP                                 ; 2|
    MOV32       *XAR5++, R0L
    MOV32       *XAR5++, R0H
    ; mag[i], i = 1 : N/2 - 1
_RFFT_f64s_mag_loop:
    MOV32       R0L, *XAR6++            ;        R0 = Re[i]
    MOV32       R0H, *XAR6++                     
    MPYF64      R0, R0, R0              ; *|     R0 = Re[i]*Re[i]
 || MOV32       R1H, *--XAR7            ;  |     R1 = Im[i]
    MOV32       R1L, *--XAR7            ; 1|      
    MPYF64      R1, R1, R1              ; 2|*|   R1 = Im[i]*Im[i]
 || MOV32       R4L, *XAR6++            ;  | |   R4 = Re[i+1] 
    MOV32       R4H, *XAR6++            ;  |1|   
    MPYF64      R4, R4, R4              ; *|2|   R4 = Re[i+1]*Re[i+1]
 || MOV32       R5H, *--XAR7            ;  |     R5 = Im[i+1]
    MOV32       R5L, *--XAR7            ; 1|     
    MPYF64      R5, R5, R5              ; 2|*|   R5 = Im[i+1]*Im[i+1]
    ADDF64      R0, R1, R0              ; *|1|   R0 = Re[i]^2 + Im[i]^2
    MOV32       R7L, ISF_L              ; 1|2|   R7 = ISF
    ADDF64      R4, R5, R4              ; 2|*|   R4 = Re[i+1]^2 + Im[i+1]^2
    MOV32       R7H, ISF_H              ;  |1|
    MPYF64      R0, R0, R7              ; *|2|   R0 = ISF*(Re[i]^2 + Im[i]^2)
    ; R4 = ISF*(Re[i+1]^2 + Im[i+1]^2)
    MPYF64      R4, R4, R7              ; 1|*|
    NOP                                 ; 2|1|
    ; R1 = Ye[i] = Estimate(1/sqrt(X[i]/(N/2)))
    EISQRTF64   R1, R0                  ; *|2|
    ; R5 = Ye[i+1] = Estimate(1/sqrt(X[i+1]/(N/2)))
    EISQRTF64   R5, R4                  ; 1|*|
    MPYF64      R2, R0, #0.5            ; *|1|   R2 = X[i]*0.5
    MPYF64      R6, R4, #0.5            ; 1|*|   R6 = X[i+1]*0.5
    
    .asg        1, N
    .loop
    MPYF64      R3, R1, R1              ; 2|1|*| R3 = Ye[i]*Ye[i]
    MPYF64      R7, R5, R5              ; *|2|1| R7 = Ye[i+1]*Ye[i+1]
    NOP                                 ; 1| |2|
    MPYF64      R3, R3, R2              ; 2|*|   R3 = Ye[i]*Ye[i]*X*0.5
    ; R7 = Ye[i+1]*Ye[i+1]*X[i+1]*0.5
    MPYF64      R7, R7, R6              ; *|1|
    NOP                                 ; 1|2|
    ; R3 = 1.5 - Ye[i]*Ye[i]*X[i]*0.5     
    SUBF64      R3, #1.5, R3            ; 2|*|
    ; R7 = 1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5
    SUBF64      R7, #1.5, R7            ; *|1|
    NOP                                 ; 1|2|
    ; R1 = Ye[i] = Ye[i]*(1.5 - Ye[i]*Ye[i]*X[i]*0.5)
    MPYF64      R1, R1, R3              ; 2|*|
    ; R5 = Ye[i+1] = Ye[i+1]*(1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5)
    MPYF64      R5, R5, R7              ; *|1|
    NOP                                 ; 1|2|
    .eval       N+1, N
    .break      N == 4
    .endloop
    
    MPYF64      R3, R1, R2              ; 2|*| R3 = Ye[i]*X[i]*0.5
    MPYF64      R7, R5, R6              ; *|1| R7 = Ye[i+1]*X[i+1]*0.5
    NOP                                 ; 1|2|
    MPYF64      R3, R1, R3              ; 2|*| R3 = Ye[i]*Ye[i]*X[i]*0.5
    MPYF64      R7, R5, R7              ; *|1| R7 = Ye[i+1]*Ye[i+1]*X[i+1]*0.5
    NOP                                 ; 1|2|
    SUBF64      R3, #1.5, R3            ; 2|*| R3 = 1.5 - Ye[i]*Ye[i]*X*0.5
    CMPF64      R0, #0.0                ;  |1| if X[i] == 0, set ZF
    NOP                                 ;  |2|
    ; R1 = Ye[i] = Ye[i]*(1.5 - Ye[i]*Ye[i]*X[i]*0.5)
    MPYF64      R1, R1, R3              ; *|   
    ; R7 = 1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5
    SUBF64      R7, #1.5, R7            ; 1|*|
    NOP                                 ; 2|1|
    ; If X[i] is zero, change the Ye[i] estimate to 0
    MOV64       R1, R0, EQ              ;  |2|
    CMPF64      R4, #0.0                ;      if X[i+1] == 0, set ZF
    ; R5 = Ye[i+1] = Ye[i+1]*(1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5)
    MPYF64      R5, R5, R7              ; *| 
    ; R0 = Y[i] = X[i]*Ye[i] = sqrt(X[i])
    MPYF64      R0, R0, R1              ; 1|*| 
    NOP                                 ; 2|1|
    ; If X[i+1] is zero, change the Ye[i+1] estimate to 0
    MOV64       R5, R4, EQ              ;  |2|
    ; R4 = Y[i+1] = X[i+1]*Ye[i+1] = sqrt(X[i+1])
    MPYF64      R4, R4, R5              ; *|   
    ; Store the result
    MOV32       *XAR5++, R0L            ; 1|
    MOV32       *XAR5++, R0H            ; 2|
    MOV32       *XAR5++, R4L
    MOV32       *XAR5++, R4H
    BANZ        _RFFT_f64s_mag_loop, AR0--
    ; mag[N/2] is done out of the loop.
    ; Note that the last iteration of the repeat block does
    ; sqrt(2)*|Re[N/2]| which must be corrected. There is
    ; no advantage in shortening the repeat block loop and then doing the
    ; last two entries X[N/2-1] and X[N/2] out of the block
    ;
    ; There are two ways to handle this - either read back the N/2th entry
    ; and write its absolute value back to the output, this will work
    ; only if the input and output arrays are different
    ;
    ; If the input and output arrays are the same, i.e. the operation
    ; is done inplace you will have to multiply by the inverse square
    ; root of 2, 1/sqrt(2) = 0.707106781186547 (0x3FE6A09E667F3BC8)
    ;
    MOV32       R0H, *--XAR6            ; R0 = Re[N/2]
    MOV32       R0L, *--XAR6
    .if RFFT_MAG_IN_PLACE == 0U
    ABSF64      R0, R0                  ; R0 = |Re[N/2]|
    .else ; RFFT_MAG_IN_PLACE == 1
    MOVW        DP, #_ONE_O_SQRT_2
    MOV32       R1L, @_ONE_O_SQRT_2     ; R1 = 1/sqrt(2)
    MOV32       R1H, @_ONE_O_SQRT_2 + 2
    MPYF64      R0, R0, R1              ; R0 = sqrt(2)*|Re[N/2]|/sqrt(2)
    NOP
    NOP
    .endif
    MOV32       R7L, ISF2_L             ;        R7 = ISF2
    MOV32       R7H, ISF2_H             ;
    MPYF64      R0, R0, R7              ; *|     R0 = ISF2*|Re[0]|
;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
    SUBB        SP, LF_SIZE             ; 1|
    MOV32       R7H, *--SP              ; 2|
    MOV32       *--XAR5, R0H
    MOV32       *--XAR5, R0L
    MOV32       R6H, *--SP
    MOV32       R5H, *--SP
    MOV32       R4H, *--SP
    LRETR
    .endasmfunc
    .unasg  OBJ_CURR_INPUT_PTR
    .unasg  OBJ_CURR_OUTPUT_PTR
    .unasg  OBJ_STAGES 
    .unasg  OBJ_FFTSIZE
    .unasg  DP_EXP_BIAS
    .unasg  DP_EXP_MASK
    .unasg  ISF_H_H
    .unasg  ISF_H_L
    .unasg  ISF_H
    .unasg  ISF_L
    .unasg  ISF2_H_H
    .unasg  ISF2_H_L
    .unasg  ISF2_H
    .unasg  ISF2_L
    .unasg  LF_SIZE
;; End of File
