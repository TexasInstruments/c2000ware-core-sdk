;;#############################################################################
;;! \file source/fpu64/fft/rfft_f64_phase.asm
;;!
;;! \brief  Real Fast Fourier Transform Phase (Double Precision)
;;! \author Vishal Coelho
;;! \date   07/05/2016
;;
;; DESCRIPTION:
;;
;;   Calculates the phase for the 64-bit double precision floating point 
;;   real FFT.
;;
;; FUNCTIONS:
;;
;;  void RFFT_f64_phase (CFFT_F64_Handle)
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
;;   void (*init)(void *);       //!< Pointer to the initialization function
;;   void (*calc)(void *);       //!< Pointer to the calculation function
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
;;     Calculate the complex FFT phase. The data is organized as follows in
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
    .if __TI_EABI__
    .asg    RFFT_f64_phase, _RFFT_f64_phase
    .asg    atan2, _atan2l
    .endif
    
;; the includes

;; external references
    .ref    _atan2l
;; file globals

;;*****************************************************************************
;; void RFFT_f64_phase(CFFT_f64_Handle) 
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

    .page
    .global _RFFT_f64_phase
    .sect   ".text"
_RFFT_f64_phase:
    .asmfunc
    .asg    *+XAR4[0], OBJ_CURR_INPUT_PTR
    .asg    *+XAR4[2], OBJ_CURR_OUTPUT_PTR
    .asg    *+XAR4[4], OBJ_STAGES 
    .asg    *+XAR4[5], OBJ_FFTSIZE
;;-----------------------------------------------------------------------------
;; Context Save <<TODO: see what RxH registers are used by the atan function 
;;                and whether we need to save these regs>>
;;-----------------------------------------------------------------------------
    MOV32   *SP++, R4H
    MOV32   *SP++, R5H
    MOV32   *SP++, R6H
    MOV32   *SP++, R7H
;;-----------------------------------------------------------------------------
;; The Complex FFT Phase
;;-----------------------------------------------------------------------------
    ADDB    XAR4, #6
    MOVL    XAR5, OBJ_CURR_OUTPUT_PTR
    MOVL    XAR6, OBJ_CURR_INPUT_PTR; XAR6 -> input[0]
    MOVL    ACC, OBJ_CURR_INPUT_PTR ; ACC  -> input[0]
    ADD     ACC, OBJ_FFTSIZE << #2  ; ACC  -> input[N]
    MOVL    XAR7, ACC               ; XAR7 -> input[N]
    MOV     ACC, OBJ_FFTSIZE << #15 ; AH  = FFTSize/2
    SUB     AH, #2                  ; AH  = FFTSize/2 - 2
    MOVZ    AR0, AH                 ; AR0 = FFTSize/2 - 2
    
    ; phase[0] is done out of the loop
    MOV32   R1L, *XAR6++            ; R1 = Re[0]
    MOV32   R1H, *XAR6++
    PUSH    XAR7
    PUSH	XAR6
    PUSH	XAR5
    PUSH	XAR0
    ZERO    R0
    LCR     _atan2l                 ; R0 = phase[0] = atan2l(0, Re[0])
    POP		XAR0
    POP		XAR5
    POP		XAR6
    POP     XAR7
    MOV32   *XAR5++, R0L
    MOV32   *XAR5++, R0H
    
    ; phase[i], i = 1 : N/2 - 1
    .align  2
_RFFT_f64_phase_loop:
    MOV32   R1L, *XAR6++            ; R1 = Re[i]
    MOV32   R1H, *XAR6++
    MOV32   R0H, *--XAR7            ; R0 = Im[i]
    MOV32   R0L, *--XAR7
    PUSH	XAR6
    PUSH	XAR7
    PUSH	XAR5
    PUSH	XAR0
    LCR     _atan2l                 ; R0 = phase[i] = atan2l(Im[i], Re[i])
    POP		XAR0
    POP		XAR5
    POP		XAR7
    POP		XAR6
    MOV32   *XAR5++, R0L
    MOV32   *XAR5++, R0H
    BANZ    _RFFT_f64_phase_loop, AR0--
    
    ; phase[N/2] is done out of the loop
    MOV32   R1L, *XAR6++            ; R1 = Re[N/2]
    MOV32   R1H, *XAR6++
    ZERO    R0
    PUSH	XAR6
    PUSH	XAR5
    LCR     _atan2l                 ; R0 = phase[N/2] = atan2l(0, Re[N/2])
    POP		XAR5
    POP		XAR6
    MOV32   *XAR5++, R0L
    MOV32   *XAR5++, R0H
    
;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
    MOV32   R7H, *--SP
    MOV32   R6H, *--SP
    MOV32   R5H, *--SP
    MOV32   R4H, *--SP
    LRETR   
    .endasmfunc
    .unasg  OBJ_CURR_INPUT_PTR
    .unasg  OBJ_CURR_OUTPUT_PTR
    .unasg  OBJ_STAGES 
    .unasg  OBJ_FFTSIZE

;; End of File
