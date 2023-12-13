;;*****************************************************************************
;;! \file source/vcu2/reed_solomon/vcu2_reedsolomon_invbkampmssy.asm
;;!
;;! \brief  Inversionless Berlekamp Massey Algorithm
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
;;
;;*****************************************************************************
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
	.cdecls  C, LIST, "vcu2_types.h", "vcu2_reedsolomon_decoder.h"
;;*****************************************************************************
;; defines
;;*****************************************************************************
;; REEDSOLOMON_DECODER Routine defines


;; Argument structure defines
ARG_N             .set    0
ARG_K             .set    1
ARG_T             .set    2
ARG_NROOTS        .set    3
ARG_PSYNDROME     .set    4
ARG_PLAMBDA       .set    6
ARG_POMEGA        .set    8
ARG_PPACKEDALPHA  .set    10
ARG_PPACKEDBETA   .set    12
ARG_PRSEXPTABLE   .set    14
ARG_PRSLOGTABLE   .set    16
ARG_PERRLOC       .set    18

;; Stack defines
;;
;;   |_______|
;;   |_______|<- Stack Pointer   (SP) <---SP
;;   |_______|<- STK_PDATA       (SP-2)
;;   |_______|<- STK_DELTA       (SP-4)
;;   |_______|<- STK_GAMMA       (SP-6)
;;   |_______|<- STK_K           (SP-8)
;;   |_______|<- STK_B3_2_1_0    (SP-10)
;;   |_______|<- STK_B7_6_5_4    (SP-12)
;;   |_______|<- STK_X_X_X_B8    (SP-14)
;;   |_______|<- STK_TEMP        (SP-16)
;;   |  ...  |     :                :
;;   |_______|<- STK_TEMP_END    (SP-24)

;;
LOCAL_FRAME_SIZE            .set    24
STK_PDATA                   .set    2
STK_DELTA                   .set    4
STK_GAMMA                   .set    6
STK_K                       .set    8
STK_B3_2_1_0                .set    10
STK_B7_6_5_4                .set    12
STK_X_X_X_B8                .set    14
STK_TEMP                    .set    16
STK_TEMP_END                .set    24

;;*****************************************************************************
;; macros
;;*****************************************************************************
;;
;; MACRO   : 'REEDSOLOMON_DECODER_CONTEXT_SAVE'
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on entry into Reed solomon decoder routine
;;
REEDSOLOMON_DECODER_CONTEXT_SAVE    .macro
    PUSH      XAR1
    PUSH      XAR2
    PUSH      XAR3
    ADDB      SP, #LOCAL_FRAME_SIZE              ; allocate stack space for local frame
    .endm
;;
;; MACRO   : 'REEDSOLOMON_DECODER_CONTEXT_RESTORE'
;; SIZE    : Number of WORDS/Number of Cycles 14
;; USAGE   : Called on exit from  Reed solomon decoder routine
;;
REEDSOLOMON_DECODER_CONTEXT_RESTORE    .macro
    SUBB      SP, #LOCAL_FRAME_SIZE              ; deallocate stack space for local frame
    POP       XAR3
    POP       XAR2
    POP       XAR1
    .endm
;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _REEDSOLOMON_DECODER_berlekampMassey
    
    
_REEDSOLOMON_DECODER_berlekampMassey_K:
        .long   0x1, 0x0, 0x0, 0x3, 0x0, 0x0
        .long   0x7, 0x0, 0x0, 0xF, 0x0, 0x0
        .long   0xF, 0x1, 0x0, 0xF, 0x3, 0x0
        .long   0xF, 0x7, 0x0, 0xF, 0xF, 0x0
        .long   0xF, 0xF, 0x1, 0xF, 0xF, 0x1
        .long   0xF, 0xF, 0x1, 0xF, 0xF, 0x1
        .long   0xF, 0xF, 0x1, 0xF, 0xF, 0x1
        .long   0xF, 0xF, 0x1, 0xF, 0xF, 0x1
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;; \brief Inversionless Berlekamp Massey Algorithm to find the coefficients
;;        of the error locator polynomial
;; 
;; \param[in] hndRSDecoder handle to the Reed Solomon Decoder object
;; - *+XAR4[0]:  n             ->number of codeword symbols (bytes) in a block
;; - *+XAR4[1]:  k             ->number of message symbols (bytes) in a block
;; - *+XAR4[2]:  t             ->number of correctable errors in the block
;; - *+XAR4[3]:  nRoots        ->number of roots for the code generator polynomial
;; - *+XAR4[4]:  *pSyndrome    ->pointer to the syndromes
;; - *+XAR4[6]:  *pLambda      ->pointer to the error locator polynomial coefficients
;; - *+XAR4[8]:  *pOmega       ->pointer to the error magnitude polynomial coefficients
;; - *+XAR4[10]:  *pPackedAlpha ->Pointer to the roots of the code generator polynomial \f$ x + \alpha^{i}\f$
;; - *+XAR4[12]:  *pPackedBeta ->Pointer to the first 2t elements of the GF(2^n)
;; - *+XAR4[14]: *pRS_expTable ->Pointer to the lookup table (roots of the extension Galois Field)
;;                               that converts index to decimal form
;; - *+XAR4[16]: *pRS_logTable  ->Pointer to the lookup table (roots of the extension Galois Field)
;;                               that converts decimal to index form
;; - *+XAR4[18]:  *pErrorLoc    ->Pointer to the error (location, value) pairs
;;
_REEDSOLOMON_DECODER_berlekampMassey:
;; Local Defines

;;
;; Register Usage:
;;   XAR0: Index into the structure
;;   XAR1: Counter for syndrome load
;;   XAR2: pointer to the syndrome
;;   XAR3: pointer to the lambda polynomial
;;   XAR4: pointer to the decoder object
;;   XAR5: points to a temporary buffer
;;   XAR6: loop counter
;;   XAR7: GFADD #K | pointer to the omega polynomial
;;   T   : 
;;   AL  : 
;;   AH  : 
;;  VR3  : lambdaEval3_2_1_0
;;  VR4  : lambdaEval7_6_5_4
;;  VR5  : X_X_X_lambdaEval8
;;  VR6  : gammaEval_3_2_1_0
;;  VR7  : gammaEval_7_6_5_4
    REEDSOLOMON_DECODER_CONTEXT_SAVE
    MOV       AR0, #ARG_PLAMBDA
    MOVL      XAR3, *+XAR4[AR0]                  ; XAR3 -> pLambda
    MOV       AR0, #ARG_PSYNDROME
    MOVL      XAR2, *+XAR4[AR0]                  ; XAR2 -> pSyndrome
    MOVZ      AR5, SP                            ; XAR5 -> temp buffer
    SUBB      XAR5, #STK_TEMP_END
    MOV       AL, *+XAR4[#ARG_T]                 ; AL = t (not T = 2t)
    LSR  	  AL, #1                             ;    = t/2
    SUB       AL, #1                             ;    = t/2 - 1
    MOVZ      AR6, AL                            ; loop counter = t/2 - 1
    MOVL      XAR7, #_REEDSOLOMON_DECODER_berlekampMassey_K
;;=============================================================================
;; Initialization
;;=============================================================================
    MOVB      XAR1, #0
    MOV       AL, #1
    MOV       AH, #0
    MOVL      *+XAR3[0], ACC                     ; l3_2_1_0 = 0_0_0_1
    MOVL      *-SP[STK_GAMMA], ACC               ; gamma  = 1
    MOVL      *-SP[STK_B3_2_1_0], ACC            ; B3_2_1_0 = 0_0_0_1

    MOV       AL, #0
    MOVL      *-SP[STK_K], ACC                   ; k        = 0
    MOVL      *+XAR3[2], ACC                     ; l7_6_5_4 = 0_0_0_0
    MOVL      *+XAR3[4], ACC                     ; l8 = 0
    MOVL      *-SP[STK_B7_6_5_4], ACC            ; B7_6_5_4 = 0_0_0_0
    MOVL      *-SP[STK_X_X_X_B8], ACC            ; B8 = 0

    VCLEARALL                                    ; clear all VCU registers
;;=============================================================================
;; Iterations
;;=============================================================================
_REEDSOLOMON_DECODER_berlekampMassey_iteration:
    VMOV32    VR1, *+XAR2[AR1]                   ; VR1 = s3_2_1_0
                                                 ; VR1 = s7_6_5_4
                                                 ; VR1 = s11_10_9_8
                                                 ; VR1 = s15_14_13_12
    VREVB     VR1                                ; reverse bytes
    VMOV32    *-SP[STK_TEMP], VR1                      
    MOVB      XAR0, #3                           ; loop counter
                  
_REEDSOLOMON_DECODER_berlekampMassey_loop:
;;=============================================================================                 
;; Compute Delta = sum(lambda[j] * S[k-j]), 0<j<k
;; VR1, VR2, VR3, VR4 no reuse (syndromes in reverse order + shift)
;;=============================================================================
    VMOV32    VR1, *-SP[STK_TEMP]                ; VR1 = s3_2_1_0
    VMOV32    VR5, VR2                           ; VR5 = VR2
    VMOV32    VR6, VR3                           ; VR6 = VR3
                                                 
    VSHLMB    VR4, VR6                           ; VR4, VR3, VR2 S in reverse order
    VSHLMB    VR3, VR5                           
    VSHLMB    VR2, VR1                           
                                                  
    VCLEAR    VR5                                
    VMOV32    VR0, *+XAR3[0]                     ; VR0 = l3_2_1_0
                                                 
    VGFMPY4   VR6, VR0, VR2                      
    VMOV32    VR7, *XAR7++                       ; VR7 = #K
                                                 
    VGFACC    VR5, VR6, VR7                      
 || VMOV32    VR0, *+XAR3[2]                     ; VR0 = l7_6_5_4
                                                 
    VGFMPY4   VR6, VR0, VR3                      
    VMOV32    VR7, *XAR7++                       ; VR7 = #K
                                                 
    VGFACC    VR5, VR6, VR7                      
 || VMOV32    VR0, *+XAR3[4]                     ; VR0 = X_X_X_l8
                                                 
    VGFMPY4   VR6, VR0, VR4                      
    VMOV32    VR7, *XAR7++                       ; VR7 = #K
                                                 
    VGFACC    VR5, VR6, VR7                      
                                                 
    VMOV32    *-SP[STK_DELTA], VR5               ; save delta
                                                 
    VMOV32    *-SP[STK_TEMP], VR1                ; save shifted S
;;=============================================================================
;; Compute lambda
;; VR5, VR6, VR7 stores lambdaEval 
;;============================================================================= 
                
    VMOV32    VR5, *-SP[STK_B3_2_1_0]            ; B3_B2_B1_B0
    VMOV32    VR6, *-SP[STK_B7_6_5_4]            ; B7_B6_B5_B4
    VMOV32    VR7, VR6                           
                                                 
    VSHLMB    VR6, VR5                           ; VR6 = B6_B5_B4_B3, VR5 = B2_B1_B0_NA
    VLSHR32   VR7, #24                           ; VR7 = X_X_X_B7
                                                 
    VPACK4    VR0, *-SP[STK_DELTA], #0           ; delta repeat 4
                                                 
    VGFMPY4   VR5, VR0, VR5                      ; VR5 = delta_B210X
    VGFMPY4   VR6, VR0, VR6                      ; VR6 = delta_B6543
    VGFMPY4   VR7, VR0, VR7                      ; VR7 = delta_XXXB7
                                                 
    VPACK4    VR0, *-SP[STK_GAMMA], #0           ; gamma repeat 4
                                                 
    VMOV32    VR1, *+XAR3[0]                     ; VR1 = l3_l2_l1_l0
    VGFMPY4   VR1, VR0, VR1                      ; VR1 = gamma_l3210
    VGFADD4   VR5, VR1, VR5, #0xE                ; VR5 = l_new3210
                                                 
    VMOV32    VR1, *+XAR3[2]                     ; VR1 = l4_l5_l6_l7
    VGFMPY4   VR1, VR0, VR1                      ; VR1 = gamma_l4567
    VGFADD4   VR6, VR6, VR1, #0xF                ; VR6 = l_new7654
                                                 
    VMOV32    VR1, *+XAR3[4]                     ; VR1 = X_X_X_l8
    VGFMPY4   VR1, VR0, VR1                      ; VR1 = gamma_l8
    VGFADD4   VR7, VR7, VR1, #0x1                ; VR7 = l_new8

;;=============================================================================
;; Decision 
;;============================================================================= 
    ;; if((delta != 0) && (k >= 0))
    CMP       *-SP[STK_DELTA], #0                ; delta != 0
    BF        _REEDSOLOMON_DECODER_berlekampMassey_cond1, EQ
    CMP       *-SP[STK_K], #0                    ; k >= 0
    BF        _REEDSOLOMON_DECODER_berlekampMassey_cond1, LT                  
                                                 
    MOVL      ACC, *-SP[STK_DELTA]                       
    MOVL      *-SP[STK_GAMMA], ACC               ; gamma = delta
                                                 
    MOVL      ACC, *-SP[STK_K]                       
    ADDB      AL, #1                             
    NEG       ACC                                
    MOVL      *-SP[STK_K], ACC                   ; k_new = -(k + 1);
                                                 
    MOVL       ACC, *+XAR3[0]                    ; copy l_p to B
    MOVL       *-SP[STK_B3_2_1_0], ACC                      
    MOVL       ACC, *+XAR3[2]                    
    MOVL       *-SP[STK_B7_6_5_4], ACC                     
    MOVL       ACC, *+XAR3[4]                    
    MOVL       *-SP[STK_X_X_X_B8], ACC                     

    SB        _REEDSOLOMON_DECODER_berlekampMassey_lambdaUpdate, UNC

_REEDSOLOMON_DECODER_berlekampMassey_cond1:      
    MOVL      ACC, *-SP[STK_K]
    ADD       ACC, #1
    MOVL      *-SP[STK_K], ACC                   ; k_new = k + 1
                                                 
    VMOV32    VR1, *-SP[STK_B7_6_5_4]            ; VR1 = B7_B6_B5_B4
    VLSHR32   VR1, #24                           ; VR1 = X_X_X_B7
    VMOV32    *-SP[STK_X_X_X_B8], VR1                      
                                                 
    VMOV32    VR1, *-SP[STK_B7_6_5_4]            ; VR1 = B7_B6_B5_B4
    VMOV32    VR0, *-SP[STK_B3_2_1_0]            ; VR0 = B3_B2_B1_B0
                                                 
    VSHLMB    VR1, VR0                           ; VR1 = B6543, VR0=B210_00
    NOP                                          
    VMOV32    *-SP[STK_B7_6_5_4], VR1            ; B = B6_B5_B4_B3
    VMOV32    *-SP[STK_B3_2_1_0], VR0            ; B = B2_B1_B0_0

_REEDSOLOMON_DECODER_berlekampMassey_lambdaUpdate:           
    VMOV32    *+XAR3[0], VR5        ; l = l_new
    VMOV32    *+XAR3[2], VR6
    VMOV32    *+XAR3[4], VR7
    BANZ      _REEDSOLOMON_DECODER_berlekampMassey_loop, AR0--

    ADDB      XAR1, #2
    BANZ      _REEDSOLOMON_DECODER_berlekampMassey_iteration, AR6--

;;=============================================================================
;; omega (error eval poly)
;;============================================================================= 
    MOVB      XAR1, #0                           
    MOV       AL, *+XAR4[#ARG_T]                 ; AL = t
    LSR       AL, #2                             ;    = t/4
    SUB       AL, #1                             ;    = t/4 - 1
    MOVZ      AR6, @AL                           ; AR6 = loop counter
    MOVL      XAR7, #_REEDSOLOMON_DECODER_berlekampMassey_K                   

_REEDSOLOMON_DECODER_berlekampMassey_omega:
    VMOV32    VR1, *+XAR2[AR1]                   ; VR1 = s3_2_1_0
                                                 ; VR1 = s7_6_5_4
    VREVB     VR1                                ; reverse bytes

    .align 2
    RPTB _REEDSOLOMON_DECODER_berlekampMassey_omegaLoop, #3

;;=============================================================================                 
;; Compute omega = sum(lambda[j] * S[k-j]), 0<j<k
;; VR1, VR2, VR3, VR4 no reuse (syndromes in reverse order + shift)
;;=============================================================================
    VMOV32    VR5, VR2                           ; VR5 = VR2
                                                 
    VSHLMB    VR3, VR5                           ; VR4, VR3, VR2 S in reverse order
    VSHLMB    VR2, VR1                           
                                                 
    VCLEAR    VR5                                
    VMOV32    VR0, *+XAR3[0]                     ; VR0 = l3_2_1_0
                                                 
    VGFMPY4   VR6, VR0, VR2                      
    VMOV32    VR7, *XAR7++                       ; VR7 = #K
                                                 
    VGFACC    VR5, VR6, VR7                      
 || VMOV32    VR0, *+XAR3[2]                     ; VR0 = l4_5_6_7
                                                 
    VGFMPY4   VR6, VR0, VR3                      
    VMOV32    VR7, *XAR7++                       ; VR7 = #K
    ADDB      XAR7, #2                           
                                                 
    VGFACC    VR5, VR6, VR7                      
                                                 
    VMOV16    *XAR5++, VR5L                      ; omega

_REEDSOLOMON_DECODER_berlekampMassey_omegaLoop:

    ADDB      XAR1, #2
    BANZ      _REEDSOLOMON_DECODER_berlekampMassey_omega, AR6--

;;=============================================================================
; pack omega 
;;=============================================================================
    MOV        AR0, #ARG_POMEGA
    MOVL       XAR7, *+XAR4[AR0]
    MOVZ       AR5, @SP
    SUBB       XAR5, #STK_TEMP_END               ; XAR5 -> temporary buffer

    MOVB       AL.LSB, *XAR5++
    MOVB       AL.MSB, *XAR5++
    MOVB       AH.LSB, *XAR5++
    MOVB       AH.MSB, *XAR5++

    MOV        *XAR7++, AL
    MOV        *XAR7++, AH

    MOVB       AL.LSB, *XAR5++
    MOVB       AL.MSB, *XAR5++
    MOVB       AH.LSB, *XAR5++
    MOVB       AH.MSB, *XAR5++

    MOV        *XAR7++, AL
    MOV        *XAR7, AH
    REEDSOLOMON_DECODER_CONTEXT_RESTORE
    LRETR
;;  End of File
