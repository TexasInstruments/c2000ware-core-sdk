;;#############################################################################
;;! \file source/fpu64/fft/cfft_f64_scaled_mag.asm
;;!
;;! \brief  Scaled Complex Fast Fourier Transform Magnitude (Double Precision)
;;! \author Vishal Coelho
;;! \date   07/28/2016
;;
;;  Revision History:
;;+----------+---------------+------------------------------------------------+
;;| DATE     | AUTHOR        | CHANGE                                         |
;;+----------+---------------+------------------------------------------------+
;;| 05/03/19 | Ritvik Sadana | Replaced CFFT_f64_s_mag with CFFT_f64s_mag to  |
;;|          |               | keep function name consistent with fpu32.      |
;;+----------+---------------+------------------------------------------------+
;;
;; DESCRIPTION:
;;
;;   Calculates the scaled magnitude for the 64-bit double precision floating 
;;   point complex FFT.
;;
;; FUNCTIONS:
;;
;;  void CFFT_f64s_mag (CFFT_F64_Handle)
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
;;  * CFFT_f64() has been called prior to this function
;;  * FFTSize is a power of 2 (atleast 32)
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

;; external references
    
;; file globals

;;*****************************************************************************
;; void CFFT_f64s_mag(CFFT_f64_Handle) 
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
;;   XAR6 : points to the buffer (input pointer)          
;;   XAR7 :           
;;     AL : 
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer       (SP)
;;   |_______|<- ISF_H               (SP-2)------> Local Frame
;;   |_______|<- ISF_L               (SP-4)----'
;;   |_______|<- R7H                 (SP-6)
;;   |_______|<- R6H                 (SP-8)
;;   |_______|<- R5H                 (SP-10)
;;   |_______|<- R4H                 (SP-12)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg CFFT_f64s_mag, _CFFT_f64s_mag
    .endif

    .page
    .global _CFFT_f64s_mag
    .sect   ".text"
_CFFT_f64s_mag:
    .asmfunc
    .asg    *+XAR4[0], OBJ_CURR_INPUT_PTR
    .asg    *+XAR4[2], OBJ_CURR_OUTPUT_PTR
    .asg    *+XAR4[4], OBJ_STAGES 
    .asg    *+XAR4[5], OBJ_FFTSIZE
    .asg    #1023    , DP_EXP_BIAS
    .asg    #0x7FF0  , DP_EXP_MASK
    .asg    *-SP[2]  , ISF_H
    .asg    *-SP[4]  , ISF_L
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
    MOVL        XAR6, OBJ_CURR_INPUT_PTR
    MOV         ACC, OBJ_FFTSIZE << #15 ; AH = FFTSize/2
    MOVZ        AR0, AH

    ;-------------------------------------------------------------------------
    ; We need to scale down the magnitude by 1/(N/2), i.e. 1/(2^(stages-1)). 
    ; The scale factor is a double precision value of the form 
    ;                    (-1)^S.(1.M)x2^(E-1023)
    ; where M is the 52 bit mantissa, E the 11 bit exponent, and S the sign of 
    ; the value. 
    ; Since N is some power of 2 the inverse scaling factor (ISF) will
    ; be a negative power of 2. For example, for a 1024 (2^10) point FFT the 
    ; ISF is (2^-(10-1))^2 or 0.000003814697265625
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
    ZAPA                                ; ACC = 0, P = 0
    MOV         AH, DP_EXP_BIAS         ; AL = dp_exponent_bias
    SUB         AH, OBJ_STAGES          ; AH = dp_exponent_bias - 2*#stages
    SUB         AH, OBJ_STAGES          ;
    ADD         AH, #2                  ;    = dp_exponent_bias-(2*#stages-2)
    LSL         ACC, #4                 ; shift biased expoenent to its place
    AND         ACC, DP_EXP_MASK << 16  ; mask off everything but the exponent
    MOVL        ISF_L, P                ; Save the ISF to the stack
    MOVL        ISF_H, ACC
    
_CFFT_f64s_mag_loop:
    MOV32       R0L, *XAR6++            ;        R0 = Re[i]
    MOV32       R0H, *XAR6++                     
    MPYF64      R0, R0, R0              ; *|     R0 = Re[i]*Re[i]
 || MOV32       R1L, *XAR6++            ;  |     R1 = Im[i]
    MOV32       R1H, *XAR6++            ; 1|      
    MPYF64      R1, R1, R1              ; 2|*|   R1 = Im[i]*Im[i]
 || MOV32       R4L, *XAR6++            ;  | |   R4 = Re[i+1] 
    MOV32       R4H, *XAR6++            ;  |1|   
    MPYF64      R4, R4, R4              ; *|2|   R4 = Re[i+1]*Re[i+1]
 || MOV32       R5L, *XAR6++            ;  |     R5 = Im[i+1]
    MOV32       R5H, *XAR6++            ; 1|     
    MPYF64      R5, R5, R5              ; 2|*|   R5 = Im[i+1]*Im[i+1]
    ADDF64      R0, R1, R0              ; *|1|   R0 = Re[i]^2 + Im[i]^2
    MOV32       R7L, ISF_L              ; 1|2|   R7 = ISF
    ADDF64      R4, R5, R4              ; 2|*|   R4 = Re[i+1]^2 + Im[i+1]^2
    MOV32       R7H, ISF_H              ;  |1|
    MPYF64      R0, R0, R7              ; *|2|   R0 = ISF*(Re[i]^2 + Im[i]^2)
    ; R4 = ISF*(Re[i+1]^2 + Im[i+1]^2)
    MPYF64      R4, R4, R7              ; 1|*| 
    NOP                                 ; 2|1| 
    ; R1 = Ye[i] = Estimate(1/sqrt(X[i]/(N/2)^2))
    EISQRTF64   R1, R0                  ; *|2|
    ; R5 = Ye[i+1] = Estimate(1/sqrt(X[i+1]/(N/2)^2))
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
    BANZ        _CFFT_f64s_mag_loop, AR0--
    
;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
    SUBB        SP, LF_SIZE
    MOV32       R7H, *--SP
    MOV32       R6H, *--SP
    MOV32       R5H, *--SP
    MOV32       R4H, *--SP
    LRETR
    .endasmfunc
    .unasg      OBJ_CURR_INPUT_PTR
    .unasg      OBJ_CURR_OUTPUT_PTR
    .unasg      OBJ_STAGES 
    .unasg      OBJ_FFTSIZE
    .unasg      DP_EXP_BIAS
    .unasg      DP_EXP_MASK
    .unasg      ISF_H
    .unasg      ISF_L
    .unasg      LF_SIZE
;; End of File
