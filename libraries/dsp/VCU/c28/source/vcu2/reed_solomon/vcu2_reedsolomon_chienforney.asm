;;*****************************************************************************
;;! \file source/vcu2/reed_solomon/vcu2_reedsolomon_chienforney.asm
;;!
;;! \brief  Chien search and Forney Algorithm
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
;;   |_______|<- STK_PARG        (SP-2)
;;   |_______|<- STK_DELTA       (SP-4)
;;   |_______|<- STK_GAMMA       (SP-6)
;;   |_______|<- STK_ODDPOLY     (SP-8)
;;   |_______|<- STK_EVENPOLY    (SP-10)
;;
LOCAL_FRAME_SIZE            .set    10
STK_PARG                    .set    2
STK_DELTA                   .set    4
STK_GAMMA                   .set    6
STK_ODDPOLY                 .set    8
STK_EVENPOLY                .set    10

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
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on exit from  Reed solomon decoder routine
;;
REEDSOLOMON_DECODER_CONTEXT_RESTORE    .macro
    SUBB      SP, #LOCAL_FRAME_SIZE              ; deallocate stack space for local frame
    POP       XAR3
    POP       XAR2
    POP       XAR1
    .endm

;;
;; MACRO   : 'GFINV'
;; SIZE    : Number of WORDS/Number of Cycles 15
;; USAGE   : Galois Field Inversion
;; For any field element x, x^(2^m-1) = 1
;; => inverse of x = x^-1 = x^(2^m-2)
;;
GFINV:  .macro
    VMOVZI    VR0, #1
    
    ; 2^m-2 times, this is for m=8 
    VGFMPY4   VR2, VR2, VR2
    VGFMPY4   VR0, VR0, VR2
    
    VGFMPY4   VR2, VR2, VR2
    VGFMPY4   VR0, VR0, VR2
    
    VGFMPY4   VR2, VR2, VR2
    VGFMPY4   VR0, VR0, VR2
    
    VGFMPY4   VR2, VR2, VR2
    VGFMPY4   VR0, VR0, VR2
    
    VGFMPY4   VR2, VR2, VR2
    VGFMPY4   VR0, VR0, VR2
    
    VGFMPY4   VR2, VR2, VR2
    VGFMPY4   VR0, VR0, VR2
    
    VGFMPY4   VR2, VR2, VR2
    VGFMPY4   VR2, VR0, VR2

    .endm
;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _REEDSOLOMON_DECODER_chienForney
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;; \brief Chien Search and Forney's Algorithm
;;
;; This function implements Chien search to find roots
;; of the error locator polynomial and Forney's algorithm to compute error
;; values using the error locator and error evaluator polynomials
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
;; \param[in] nBytes (AL)   number of bytes
;;
_REEDSOLOMON_DECODER_chienForney:
;; Local Defines

;;
;; Register Usage:
;;   XAR0: index into the structure
;;   XAR1: byte counter
;;   XAR2: pointer to the betas
;;   XAR3: pointer to the error locations
;;   XAR4: pointer to the decoder object/
;;         pointer to the lambdas
;;   XAR5: pointer to the omegas
;;   XAR6: loop counter
;;   XAR7: counter for shortened code update
;;   T   : 
;;   AL  : number of bytes
;;   AH  : 
;;  VR1  :
;;  VR3  :
;;  VR4  :
;;  VR5  :
;;  VR6  :
;;  VR7  :
    REEDSOLOMON_DECODER_CONTEXT_SAVE
    MOVB      AH, #255                           
    SUB       AH, AL                             ; k = 255 - nBytes
    MOV       T, AH                              
    AND       T, #0x1                            ; loop udpates 2 @ a time
    LSR       AH, #1                             
    ADDB      AH, #-1                            
    MOVZ      AR7, @AH                           ; AR7 = counter for shortened code update

    ADDB      AL, #-1                            
    MOVZ      AR6, @AL                           ; AR6 = loop counter
    
    MOV       AR0, #ARG_PPACKEDBETA
    MOVL      XAR2, *+XAR4[AR0]                  ; XAR2 = beta pointer
    MOV       AR0, #ARG_PERRLOC
    MOVL      XAR3, *+XAR4[AR0]                  ; XAR3 = err pointer
    MOV       AR0, #ARG_POMEGA
    MOVL      XAR5, *+XAR4[AR0]                  ; XAR5 = omega pointer
    MOVL      *-SP[#STK_PARG], XAR4              ; save structure pointer to stack
    MOV       AR0, #ARG_PLAMBDA
    MOVL      XAR4, *+XAR4[AR0]                  ; XAR4 = lambda pointer
;;=============================================================================
;;  Update lambdaEval and gammEval only for shortened code
;;=============================================================================
    
    VMOV32    VR3, *+XAR4[0]                     ; VR3[31:0] = lambdaEval3_2_1_0 
    VMOV32    VR4, *+XAR4[2]                     ; VR4[31:0] = lambdaEval7_6_5_4 
    VMOV32    VR5, *+XAR4[4]                     ; VR5[31:0] = X_X_X_lambdaEval8
                                                 
    VMOV32    VR6, *+XAR5[0]                     ; VR6[31:0] = gamma3_2_1_0               
    VMOV32    VR7, *+XAR5[2]                     ; VR7[31:0] = gamma7_6_5_4
                                                 
    VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0               
    VMOV32    VR1, *+XAR2[0]                     ; VR1[31:0] = beta3_2_1_0              
                                                 ; VR1 = use LSB only for root update, can optimize later!!!
                                                 
    .align 2                                     
    RPTB _REEDSOLOMON_DECODER_chienForney_updateLoop, AR7                    
                                                 
    VGFMPY4   VR3, VR0, VR3                      ; Update lambdaEval_3_2_1_0
 || VMOV32    VR0, *+XAR2[2]                     ; VR0[31:0] = beta7_6_5_4
                                                 
    VGFMPY4   VR4, VR0, VR4                      ; Update lambdaEval_7_6_5_4
 || VMOV32    VR0, *+XAR2[4]                     ; VR0[31:0] = X_X_X_beta8
                                                 
    VGFMPY4   VR5, VR0, VR5                      ; Update X_X_X_lambdaEval8
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VGFMPY4   VR6, VR0, VR6                      ; Update gammaEval_3_2_1_0
 || VMOV32    VR0, *+XAR2[2]                     ; VR0[31:0] = beta7_6_5_4
                                                 
    VGFMPY4   VR7, VR0, VR7                      ; Update gammaEval_7_6_5_4
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VGFMPY4   VR1, VR0, VR1                      ; Update root
                                                 
    VGFMPY4   VR3, VR0, VR3                      ; Update lambdaEval_3_2_1_0
 || VMOV32    VR0, *+XAR2[2]                     ; VR0[31:0] = beta7_6_5_4
                                                 
    VGFMPY4   VR4, VR0, VR4                      ; Update lambdaEval_7_6_5_4
 || VMOV32    VR0, *+XAR2[4]                     ; VR0[31:0] = X_X_X_beta8
                                                 
    VGFMPY4   VR5, VR0, VR5                      ; Update X_X_X_lambdaEval8
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VGFMPY4   VR6, VR0, VR6                      ; Update gammaEval_3_2_1_0
 || VMOV32    VR0, *+XAR2[2]                     ; VR0[31:0] = beta7_6_5_4
                                                 
    VGFMPY4   VR7, VR0, VR7                      ; Update gammaEval_7_6_5_4
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VGFMPY4   VR1, VR0, VR1                      ; Update root
                                                
_REEDSOLOMON_DECODER_chienForney_updateLoop:
                                                 ; initialize counters 
    MOVL      XAR1, #0                           ; byte counter = 0 
    MOVL      XAR4, #0                           ; numroots = 0
                                                 
    CMP       T, #0                              
    SBF       _REEDSOLOMON_DECODER_chienForney_loop, EQ
;;=============================================================================
;; if odd  
;;=============================================================================

    VGFMPY4   VR3, VR0, VR3                      ; Update lambdaEval_3_2_1_0
 || VMOV32    VR0, *+XAR2[2]                     ; VR0[31:0] = beta7_6_5_4
                                                 
    VGFMPY4   VR4, VR0, VR4                      ; Update lambdaEval_7_6_5_4
 || VMOV32    VR0, *+XAR2[4]                     ; VR0[31:0] = X_X_X_beta8
                                                 
    VGFMPY4   VR5, VR0, VR5                      ; Update X_X_X_lambdaEval8
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VGFMPY4   VR6, VR0, VR6                      ; Update gammaEval_3_2_1_0
 || VMOV32    VR0, *+XAR2[2]                     ; VR0[31:0] = beta7_6_5_4
                                                 
    VGFMPY4   VR7, VR0, VR7                      ; Update gammaEval_7_6_5_4
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VGFMPY4   VR1, VR0, VR1                      ; Update root
;;=============================================================================
;; Evaluate lambda/omega @ each data byte position
;;=============================================================================

_REEDSOLOMON_DECODER_chienForney_loop:

;;=============================================================================
;; Evaluate poly (lambdaEval and gammaEval are stored in VR registers)
;;=============================================================================
    VGFMPY4   VR6, VR0, VR6                      ; Update gammaEval_3_2_1_0
 || VMOV32    VR0, *+XAR2[2]                     ; VR0[31:0] = beta7_6_5_4
                                                 
    VGFMPY4   VR7, VR0, VR7                      ; Update gammaEval_7_6_5_4
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VGFMPY4   VR3, VR0, VR3                      ; Update lambdaEval_3_2_1_0
 || VMOV32    VR0, *+XAR2[2]                     ; VR0[31:0] = beta7_6_5_4
                                                 
    VGFMPY4   VR4, VR0, VR4                      ; Update lambdaEval_7_6_5_4
 || VMOV32    VR0, *+XAR2[4]                     ; VR0[31:0] = X_X_X_beta8	
                                                 
    VGFMPY4   VR5, VR0, VR5                      ; Update X_X_X_lambdaEval8
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VCLEAR    VR2                                
    VGFACC    VR2, VR3, #1010B                   ; odd poly
    VGFACC    VR2, VR4, #1010B                   ; odd poly
    VMOV32    *-SP[STK_ODDPOLY], VR2             ; save odd poly to the stack
                                                 
    VCLEAR    VR2                                
    VGFACC    VR2, VR3, #0101B                   ; even poly
    VGFACC    VR2, VR4, #0101B                   ; even poly
    VGFACC    VR2, VR5, #0001B                   
                                                 
    VMOV32    *-SP[STK_EVENPOLY], VR2                       
    MOVL      ACC, *-SP[STK_EVENPOLY]  
;;=============================================================================
;; if (lambdapoly == 0), then error
;;=============================================================================
    CMP       AL, *-SP[STK_ODDPOLY]              ; even poly = odd poly?
    SBF       _REEDSOLOMON_DECODER_chienForney_nonZero, NEQ

    GFINV                                        ; GFINV (oddpoly)
                                                 ; MACRO using VR0 as tmp, ip/op: VR2
    VCLEAR    VR0                                
    VGFACC    VR0, VR6, #1111B                   ; gamma poly
    VGFACC    VR0, VR7, #1111B                   ; gamma poly
                                                 
    VGFMPY4   VR2, VR2, VR0                      ; GFMPY (gamma_poly, GFINV(odd_poly)
    VLSHL32   VR2, #8                            ; shift to multiply with correct root
    VGFMPY4   VR2, VR2, VR1                      ; val = gamma_poly *root / odd_poly
 || VMOV32    VR0, *+XAR2[0]                     ; VR0[31:0] = beta3_2_1_0
                                                 
    VMOV32    *-SP[STK_ODDPOLY], VR2                       
    MOV       ACC, *-SP[STK_ODDPOLY] << #8       ; AH = VR2
    AND       AH, #0xFF                          
    MOV       *XAR3++, AR1                       ; store error byte position
    MOV       *XAR3++, AH                        ; store error value
    ADDB      XAR4, #1                           ; numroots++
    
_REEDSOLOMON_DECODER_chienForney_nonZero:
    VGFMPY4   VR1, VR0, VR1                      ; Update root
    ADDB      XAR1, #1                           ; byte counter++
    BANZ      _REEDSOLOMON_DECODER_chienForney_loop, AR6--
;;=============================================================================
;; Check for decode ok/fail
;; No roots of lambda should repeat, # of roots should = degree of lambda
;;=============================================================================
    MOV       *+XAR3[0], AR4                     ; save number of error last

    REEDSOLOMON_DECODER_CONTEXT_RESTORE
    LRETR
;;  End of File
    
