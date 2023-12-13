;;#############################################################################
;;! \file source/fpu32/fft/cfft_f32_brev.asm
;;!
;;! \brief  Bit Reverse Reorder an Array (Single Precision)
;;! \author Vishal Coelho
;;! \date   04/27/2017
;;
;; DESCRIPTION:
;;
;;   Bit reverse reorder the N point complex FFT input array either 
;;   in place (input & output pointer point to the same array) or 
;;   off-place (input & output pointer point to the different arrays)
;;
;; FUNCTIONS:
;;
;;  void CFFT_f32_brev (CFFT_F32_STRUCT_Handle)
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
;;  * The input must be aligned to a 4N (sizeof(float)*2(complex)) word 
;;    boundary
;;
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
;; void CFFT_f32_brev(CFFT_F32_STRUCT_Handle)
;;
;; The function takes a handle to the CFFT_F32_STRUCT object as an argument. 
;;
;; Register Usage:                                                            
;;    AR0 : bit reverse index 
;;   XAR1 : 
;;   XAR2 : 
;;   XAR3 : 
;;   XAR4 : points to the object 
;;   XAR5 : points to the input         
;;   XAR6 : points to the output   
;;   XAR7 : loop counter
;;     AL : size of the array/ copy of bit reverse index
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer       (SP)
;;   |_______|<- rpc                 (SP-2)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg CFFT_f32_brev, _CFFT_f32_brev
    .endif
        
    .page
    .global _CFFT_f32_brev
    .sect   ".text"
_CFFT_f32_brev:
    .asmfunc
    .asg    *XAR4++  ,  OBJ_INPUT_PTR
    .asg    *XAR4++  ,  OBJ_OUTPUT_PTR
    .asg    *+XAR4[0],  OBJ_TWIDDLES_PTR 
    .asg    *+XAR4[2],  OBJ_CURR_INPUT_PTR
    .asg    *+XAR4[4],  OBJ_CURR_OUTPUT_PTR
    .asg    *+XAR4[6],  OBJ_STAGES 
    .asg    *+XAR4[7],  OBJ_FFTSIZE

;;-----------------------------------------------------------------------------
;; Bit Reversal
;;-----------------------------------------------------------------------------
    MOVL    XAR5, OBJ_INPUT_PTR         ; XAR5 = p->input    
    MOVL    XAR6, OBJ_OUTPUT_PTR        ; XAR6 = p->output (same as input)
    MOVZ    AR7, OBJ_FFTSIZE            ; XAR7 = N
    SUBB    XAR7, #1                    ; XAR7 = N - 1
    MOV     ACC, OBJ_FFTSIZE<<#1        ; AL   = 2*N (halfway point of array)
    MOVL    XAR0, XAR5                  ; XAR0 = p->input
    NOP     *, ARP6                     ;                             ARP->XAR6
    CMPR    0                           ; if XAR0(5)==XAR6 then in-place (TC=1)
                                        ;                  else off-place(TC=0)
    BF      _CFFT_f32_brev_offplace, NTC
_CFFT_f32_brev_loop:
    MOVL    XT, *+XAR5[0]               ; XT  = x[i].re
    MOVL    P, *+XAR6[0]                ; P   = y[i].re,              ARP->XAR6
    MOVL    XAR0, XAR5                  ; XAR0 = p->input
    CMPR    2                           ; if XAR0(5) < XAR6 then no swap(TC=1) 
                                        ;                   else    swap(TC=0)
    BF      _CFFT_f32_brev_noswap, TC
    MOVL    *+XAR5[0], P
    MOVL    *+XAR6[0], XT
    MOVL    XT, *+XAR5[2]               ; XT  = x[i].im
    MOVL    P, *+XAR6[2]                ; P   = y[i].im
    MOVL    *+XAR5[2], P
    MOVL    *+XAR6[2], XT               ;                            ARP-> XAR6
    
_CFFT_f32_brev_noswap:
    ADDB    XAR5, #4                    ; XAR5 -> x[i+1].re
    MOVZ    AR0, AL                     ; XAR0 = 2*N
    NOP     *BR0++                      ; XAR6 = XAR6 rcadd XAR0
    BANZ    _CFFT_f32_brev_loop, AR7--
    LRETR                   
    
_CFFT_f32_brev_offplace
    MOVZ    AR0, AL                     ; XAR0 = 2*N
_CFFT_f32_brev_loop2:
    MOVL    XT, *XAR5++                 ; XT   = x[i].re
    MOVL    P, *XAR5++                  ; P    = x[i].im
    MOVL    *+XAR6[0], XT               
    MOVL    *+XAR6[2], P                ;                             ARP->XAR6
    NOP     *BR0++                      ; XAR6 = XAR6 rcadd XAR0
    BANZ    _CFFT_f32_brev_loop2, AR7--
    LRETR
    
    .endasmfunc
    .unasg  OBJ_INPUT_PTR
    .unasg  OBJ_OUTPUT_PTR
    .unasg  OBJ_TWIDDLES_PTR 
    .unasg  OBJ_CURR_INPUT_PTR
    .unasg  OBJ_CURR_OUTPUT_PTR
    .unasg  OBJ_STAGES 
    .unasg  OBJ_FFTSIZE

;; End of File
