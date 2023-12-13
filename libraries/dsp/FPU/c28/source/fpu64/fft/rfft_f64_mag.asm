;;#############################################################################
;;! \file source/fpu64/fft/rfft_f64_mag.asm
;;!
;;! \brief  Real Fast Fourier Transform Magnitude (Double Precision)
;;! \author Vishal Coelho
;;! \date   07/05/2016
;;
;; DESCRIPTION:
;;
;;   Calculates the magnitude for the 64-bit double precision floating point 
;;   real FFT.
;;
;; FUNCTIONS:
;;
;;  void RFFT_f64_mag (CFFT_F64_Handle)
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
;; void RFFT_f64_mag(CFFT_f64_Handle) 
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
;;   |_______|<- R7H                 (SP-2)
;;   |_______|<- R6H                 (SP-4)
;;   |_______|<- R5H                 (SP-6)
;;   |_______|<- R4H                 (SP-8)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg    RFFT_f64_mag, _RFFT_f64_mag
    .endif
    
    .page
    .global _RFFT_f64_mag
    .sect   ".text"
_RFFT_f64_mag:
    .asmfunc
    .asg    *+XAR4[0], OBJ_CURR_INPUT_PTR
    .asg    *+XAR4[2], OBJ_CURR_OUTPUT_PTR
    .asg    *+XAR4[4], OBJ_STAGES 
    .asg    *+XAR4[5], OBJ_FFTSIZE
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    MOV32      *SP++, R4H
    MOV32      *SP++, R5H
    MOV32      *SP++, R6H
    MOV32      *SP++, R7H
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

    ; mag[0] is done out of the loop
    MOV32       R0L, *XAR6++            ;        R0 = Re[0]
    MOV32       R0H, *XAR6++   
    ABSF64      R0, R0                  ;        R0 = |Re[0]|
    MOV32       *XAR5++, R0L
    MOV32       *XAR5++, R0H
    ; mag[i], i = 1 : N/2 - 1
_RFFT_f64_mag_loop:
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
    NOP                                 ; 1|2|
    ADDF64      R4, R5, R4              ; 2|*|   R4 = Re[i+1]^2 + Im[i+1]^2
    ; R1 = Ye[i] = Estimate(1/sqrt(X[i]))
    EISQRTF64   R1, R0                  ; *|1|
    NOP                                 ; 1|2|
    ; R5 = Ye[i+1] = Estimate(1/sqrt(X[i+1]))
    EISQRTF64   R5, R4                  ; *|
    MPYF64      R2, R0, #0.5            ; 1|*|   R2 = X[i]*0.5
    MPYF64      R6, R4, #0.5            ; *|1|   R6 = X[i+1]*0.5
    
    .asg        1, N
    .loop
    MPYF64      R3, R1, R1              ; 1|2|*| R3 = Ye[i]*Ye[i]
    MPYF64      R7, R5, R5              ; 2|*|1| R7 = Ye[i+1]*Ye[i+1]
    NOP                                 ;  |1|2|
    MPYF64      R3, R3, R2              ; *|2|   R3 = Ye[i]*Ye[i]*X*0.5
    ; R7 = Ye[i+1]*Ye[i+1]*X[i+1]*0.5
    MPYF64      R7, R7, R6              ; 1|*|
    NOP                                 ; 2|1|
    ; R3 = 1.5 - Ye[i]*Ye[i]*X[i]*0.5
    SUBF64      R3, #1.5, R3            ; *|2|
    ; R7 = 1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5
    SUBF64      R7, #1.5, R7            ; 1|*|
    NOP                                 ; 2|1|
    ; R1 = Ye[i] = Ye[i]*(1.5 - Ye[i]*Ye[i]*X[i]*0.5)
    MPYF64      R1, R1, R3              ; *|2|
    ; R5 = Ye[i+1] = Ye[i+1]*(1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5)
    MPYF64      R5, R5, R7              ; 1|*|
    NOP                                 ; 2|1|
    .eval       N+1, N
    .break      N == 4
    .endloop
    
    MPYF64      R3, R1, R2              ; *|2| R3 = Ye[i]*X[i]*0.5
    MPYF64      R7, R5, R6              ; 1|*| R7 = Ye[i+1]*X[i+1]*0.5
    NOP                                 ; 2|1|
    MPYF64      R3, R1, R3              ; *|2| R3 = Ye[i]*Ye[i]*X[i]*0.5
    MPYF64      R7, R5, R7              ; 1|*| R7 = Ye[i+1]*Ye[i+1]*X[i+1]*0.5
    NOP                                 ; 2|1|
    SUBF64      R3, #1.5, R3            ; *|2| R3 = 1.5 - Ye[i]*Ye[i]*X*0.5
    CMPF64      R0, #0.0                ; 1|   if X[i] == 0, set ZF
    NOP                                 ; 2|
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
    BANZ        _RFFT_f64_mag_loop, AR0--
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

    MOV32       *--XAR5, R0H
    MOV32       *--XAR5, R0L
;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
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
    
;; End of File
