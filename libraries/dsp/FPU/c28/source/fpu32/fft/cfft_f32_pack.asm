;;#############################################################################
;;! \file source/fpu32/fft/cfft_f32_pack.asm
;;!
;;! \brief  Complex Fast Fourier Transform Pack (Single Precision)
;;! \author Vishal Coelho
;;! \date   08/08/2016
;;
;; DESCRIPTION:
;;
;;   Pack the N point complex FFT spectrum to get the spectrum of the 
;;   original N/2 point real data. The user can then run an inverse FFT 
;;   (N/2-point) to get the original signal
;;
;; FUNCTIONS:
;;
;;  void CFFT_f32_pack (CFFT_F32_STRUCT_Handle)
;;     where CFFT_F32_STRUCT_Handle is defined as:
;;     typedef CFFT_F32_STRUCT* CFFT_F32_STRUCT_Handle;
;;
;;    and where CFFT_F32_STRUCT is a structure defined as:
;;
;;     typedef struct {
;;     float      *InPtr;
;;     float      *OutPtr;
;;     float      *CoefPtr;
;;     float      *CurrentInPtr;
;;     float      *CurrentOutPtr;
;;     uint16_t  Stages;
;;     uint16_t  FFTSize;
;;     } CFFT_F32_STRUCT;
;;
;; ASSUMPTIONS:
;;  * The pack function is run on an N-point complex spectrum to derive an 
;;    N/2 point complex spectrum which is subject to an inverse FFT to give
;;    an N/2 point real signal
;;  * The pack function must be called with FFTSize of N/2 i.e. the size of 
;;    the inverse FFT that is run subsequent to the pack function
;;
;; ALGORITHM:
;;
;; In order to reverse the process of the forward real FFT,
;;
;;                              *
;; F (k) = 0.5.(F(k) + F(N/2 -k) )               , for k = 0 to N/2-1
;;  e
;;                              *   (j2.pi.k/N)
;; F (k) = 0.5.(F(k) - F(N/2 -k) ).e             , for k = 0 to N/2-1
;;  o
;; 
;; where F (k) are the even elements and F (k) are the odd elements
;;        e                               o
;; The input to the Inverse FFT then becomes
;;
;; Z(k) = F (k) + jF (k)                         , for k = 0 to N/2-1
;;         e         o 
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
    .cdecls C, LIST, NOWARN, "fpu_cfft.h"
;; external references
    
;; file globals

;;*****************************************************************************
;; void CFFT_f32_pack(CFFT_F32_STRUCT_Handle)
;;
;; The function takes a handle to the CFFT_F32_STRUCT object as an argument. 
;;
;; Register Usage:                                                            
;;    AR0 : twiddles skip factor          
;;   XAR1 : points to the sine
;;   XAR2 : points to the buffer (output pointer = k)
;;   XAR3 : 
;;   XAR4 : points to the object 
;;   XAR5 : points to the cosine               
;;   XAR6 : points to the buffer (input pointer = k)           
;;   XAR7 : points to the buffer (input pointer = N/2-k)          
;;     AL : 
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer       (SP)
;;   |_______|<- R7H                 (SP-2)
;;   |_______|<- R6H                 (SP-4)
;;   |_______|<- R5H                 (SP-6)
;;   |_______|<- R4H                 (SP-8)
;;   |_______|<- XAR2                (SP-10)
;;   |_______|<- XAR1                (SP-12)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg CFFT_f32_pack, _CFFT_f32_pack
    .endif

    .page
    .global _CFFT_f32_pack
    .sect   ".text"
_CFFT_f32_pack:
    .asmfunc
    .asg    *+XAR4[0],                OBJ_TWIDDLES_PTR 
    .asg    *+XAR4[2],                OBJ_CURR_INPUT_PTR
    .asg    *+XAR4[4],                OBJ_CURR_OUTPUT_PTR
    .asg    *+XAR4[6],                OBJ_STAGES 
    .asg    *+XAR4[7],                OBJ_FFTSIZE
    ; The cosines are quarter way down from the start of the table, 
    ; table_size/4 with all values being double precision hence,
    ; table_size/4 * 2
    .asg    ((TABLE_SIZE >> 2) << 1), TWIDDLES_COS_OFFSET
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    PUSH    XAR1
    PUSH    XAR2
    MOV32   *SP++, R4H
    MOV32   *SP++, R5H
    MOV32   *SP++, R6H
    MOV32   *SP++, R7H
;;-----------------------------------------------------------------------------
;; Pack
;; For the following section let N/2 = obj.FFTSize be the size of the complex 
;; IFFT and N the size of the real input
;;-----------------------------------------------------------------------------
    ADDB    XAR4, #4
    
    MOVL    ACC, OBJ_CURR_INPUT_PTR     ; ACC  = obj.p_currInput
    MOVL    XAR6, ACC                   ; XAR6 = obj.p_currInput
    ADD     ACC, OBJ_FFTSIZE << 2       ; ACC  = obj.p_currInput + 4*(N/2)
    MOVL    XAR7, ACC                   ; XAR7 = obj.p_currInput + 4*(N/2)
    ADDB    XAR7, #2                    ;      = obj.p_currInput + 4*(N/2+1)-2
    MOVL    XAR2, OBJ_CURR_OUTPUT_PTR   ; XAR2  = obj.p_currOutput
    
    ;;
    ;; Set the loop count for Z(k), k = 0 to N/2 - 1, the skip_factor
    ;; and the sine and cosine pointers
    ;;   skip_factor = table_size/size_of_real_data * 2(single precision)
    ;; For example, for a 1024 point real IFFT we run a 1024 point pack
    ;; followed by a 512 point complex inverse FFT
    ;;  size_of_complexIFFT (obj.FFTSize) = 512, stages_icfft (obj.stages) = 9,
    ;;  size_of_realIFFT = 512*2 = 1024,         stages_irfft = 10
    ;; If the twiddle factor table size is 1024, we have
    ;;   skip_factor = 2^10 / 2^(9+1) * 2^1
    ;;               = 2^(11-1) / 2^(9)
    ;;               = 1 << ((TABLE_SIZE_LOG2 + 1 - 1) - obj.stages)
    ;;               = (1 << ((TABLE_SIZE_LOG2 + 1 - 1)) >> obj.stages
    ;;               = 2
    ;;
    MOV     ACC, #1                     ; AH=0, AL=1
    MOV     T, OBJ_STAGES
    LSL     AL, #(TABLE_SIZE_LOG2)
    LSR     AL, T
    ; AR0 = (1 << ((TABLE_SIZE_LOG2 + 1 - 1)) >> obj.stages
    MOVZ    AR0, AL                    
    MOVL    ACC, OBJ_TWIDDLES_PTR       ; ACC  = obj.p_twiddles
    MOVL    XAR1, ACC                   ; XAR1 -> sin(2*pi*0/TABLE_SIZE)
    ; ACC/XAR5  =  obj.p_twiddles + cosine_offset
    ADD     ACC, #TWIDDLES_COS_OFFSET   
    MOVL    XAR5, ACC                   ; XAR5 -> cos(2*pi*0/TABLE_SIZE)
    MOV     AL, OBJ_FFTSIZE             ; AL = N/2
    SUBB    AL, #1                      ;    = (N/2 - 1)
    
    .lp_amode
    SETC    AMODE                       ; Set addressing mode to C2xLP
    NOP     *, ARP6                     ;               , ARP->XAR6
    ;; 
    ;; Z(k) for k = 0 to N/2 - 1
    ;;
    MOV32   R0H, *++                    ;      R0H = F_r(k) 
    MOV32   R1H, *++, ARP7              ;      R1H = F_i(k)
                                        ;                 , ARP->XAR7
    MOV32   R3H, *--                    ;      R3H = F_i(N/2-k)
    RPTB    _CFFT_f32_pack_loop, AL
    ADDF32  R6H, R1H, R3H               ; *|   R6H(IA)= F_i(k)+F_i(N/2-k)
 || MOV32   R2H, *--, ARP5              ;  |   R2H = F_r(N/2-k) 
                                        ;                 , ARP->XAR5
    SUBF32  R1H, R1H, R3H               ; 1|*| R1H(IS)= F_i(k)-F_i(N/2-k)
 || MOV32   R5H, *0++, ARP1             ;  | | R5H(C) = cos(2*pi*k/N) or C(k)
                                        ;  | |            , XAR5 += skip_factor
                                        ;  | |            , ARP -> XAR1
    ADDF32  R7H, R0H, R2H               ; *|1| R7H(RA)= F_r(k)+F_r(N/2-k)                                     
 || MOV32   R4H, *0++                   ;  | | R4H(S) = sin(2*pi*k/N) or S(k)
                                        ;  | |            , XAR1 += skip_factor
    ; R2H(C*IA) = C(k)*(F_i(k)+F_i(N/2-k))
    MPYF32  R2H, R5H, R6H               ; 1|*|                                        
 || SUBF32  R0H, R0H, R2H               ;  | | R0H(RS)= F_r(k)-F_r(N/2-k) 
    NOP     *, ARP6                     ;  |1|            , ARP->XAR6
    ; R3H(S*RS) = S(k)*(F_r(k)-F_r(N/2-k))
    ; R7H(RA - C*IA) = (F_r(k)+F_r(N/2-k))-(C(k)*(F_i(k)+F_i(N/2-k)))
    MPYF32  R3H, R4H, R0H               ; *|
 || SUBF32  R7H, R7H, R2H               ;  |    
    ; R5H(C*RS) = C(k)*(F_r(k)-F_r(N/2-k))                                   
    MPYF32  R5H, R5H, R0H               ; 1|*|
 || MOV32   R0H, *++, ARP7              ;  | | R0H = F_r(k+1) 
                                        ;                 , ARP->XAR7
    ; R4H(S*IA) = S(k)*(F_i(k)+F_i(N/2-k))
    ; R7H(RA - C*IA - S*RS)
    ;=(F_r(k)+F_r(N/2-k))-(C(k)*(F_i(k)+F_i(N/2-k)))-(S(k)*(F_r(k)-F_r(N/2-k)))
    MPYF32  R4H, R4H, R6H               ; *|1|
 || SUBF32  R7H, R7H, R3H               ;  | |
    ; R5H(IS + C*RS) = (F_i(k)-F_i(N/2-k))+(C(k)*(F_r(k)-F_r(N/2-k)))
    ADDF32  R5H, R1H, R5H               ; 1|*|                
 || MOV32   R3H, *--, ARP6              ;  | | R3H = F_r(N/2-k-1)
                                        ;                 , ARP->XAR6
    ; R7H = 1/2 * (RA - C*IA - S*RS)
    MPYF32  R7H, #0.5, R7H              ; *|1|
    ; R5H(IS + C*RS - S*IA)
    ;=(F_i(k)-F_i(N/2-k))+(C(k)*(F_r(k)-F_r(N/2-k)))-(S(k)*(F_i(k)+F_i(N/2-k)))
    SUBF32  R5H, R5H, R4H               ; 1|*|
 || MOV32   R1H, *++, ARP2              ;  | | R1 = F_i(k+1)
                                        ;                 , ARP->XAR2
    
    MOV32   *++, R7H                    ;  |1| Save Z_r(k)
    ; R5H = 1/2 * (IS + C*RS - S*IA)
    MPYF32  R5H, #0.5, R5H              ; *|
    NOP                                 ; 1|
    MOV32   *++, R5H, ARP7              ;      Save Z_i(k), ARP->XAR7
_CFFT_f32_pack_loop:
    .c28_amode
    CLRC    AMODE                       ; Set addressing mode to C28x
;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
    MOV32   R7H, *--SP
    MOV32   R6H, *--SP
    MOV32   R5H, *--SP
    MOV32   R4H, *--SP
    POP     XAR2
    POP     XAR1
    LRETR
    .endasmfunc
    .unasg  OBJ_TWIDDLES_PTR
    .unasg  OBJ_CURR_INPUT_PTR
    .unasg  OBJ_CURR_OUTPUT_PTR
    .unasg  OBJ_STAGES
    .unasg  OBJ_FFTSIZE
    .unasg  TWIDDLES_COS_OFFSET

;; End of File
