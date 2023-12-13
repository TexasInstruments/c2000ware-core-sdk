;;*****************************************************************************
;;! \file source/vcu2/reed_solomon/vcu2_reedsolomon_calcsyndrome.asm
;;!
;;! \brief  Calculate the syndromes of the received code using
;;!         Horner's method
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
;;   |_______|<- STK_GFPARAM     (SP-4)

;;
LOCAL_FRAME_SIZE            .set    4
STK_PDATA                   .set    2
STK_GFPARAM                 .set    4
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
;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _REEDSOLOMON_DECODER_calcSyndrome
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;; \brief Syndrome calculation function (Horner's Method)
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
;; \param[in] pData  (XAR5) pointer to the data
;; \param[in] nBytes (AL)   number of bytes
;;
_REEDSOLOMON_DECODER_calcSyndrome:
;; Local Defines
CODEGENPOLY      .set    0x1D

;;
;; Register Usage:
;;   XAR0: Outer loop counter
;;   XAR1: index into structure
;;   XAR2: number of roots/ polynomial
;;   XAR3: pointer to the roots
;;   XAR4: pointer to the decoder object
;;   XAR5: pointer to the data
;;   XAR6: RPTB counter
;;   XAR7: Points to syndrome
;;   T   : number of bytes (n)
;;   AH  : number of roots
;;   AL  : number of bytes (n)
    REEDSOLOMON_DECODER_CONTEXT_SAVE
    MOV       AR1, #ARG_PSYNDROME
    MOVL      XAR7, *+XAR4[AR1]
    MOVL      *-SP[STK_PDATA], XAR5              ; save off pData
    MOV       AH, *+XAR4[ARG_NROOTS]             ; AH = NROOTS
    MOV       T, AL                              ; AL = nBytes
    AND       T, #0x3                            ; nBytes multiple of 4?
    LSR       AL, 2                              ; nBytes >> 2
    ADDB      AL, #-1
    MOVZ      AR6, @AL                           ; AR6 = loop counter
    MOVZ      AR2, AH                            ; save T2
    LSR       AH, #2                             ; T2 / 4
    SUB       AH, #1                             ; subtract 1
    MOVZ      AR0, @AH                           ; counter for outer loop
    MOV       AH, AR2                            ; reload T2
    SUB       AH, #1
    LSL       AH, #8
    ADD       AH, #CODEGENPOLY                   ; polynomial = x^8+x^4+x^3+x^2+1
    MOV       *-SP[STK_GFPARAM], AH              ; Save to stack

    EDIS
    VGFINIT   *-SP[STK_GFPARAM]                  ; Initialize polynomial in VCU2

    VCLEARALL                                    ; Clear all VCU Registers
    MOV       AR1, #ARG_PPACKEDALPHA
    MOVL      XAR3, *+XAR4[AR1]                  ; point to root table

_REEDSOLOMON_DECODER_calcSyndrome_outerLoop:
    VPACK4    VR0, *XAR5, #0                     ; VR0[31:0] = R0_R0_R0_R0 (pack byte 0 of data)
    EDIS                                         
    VMOV32    VR1, *XAR3++                       ; VR1[31:0] = alpha**4, alpha**3, alpha**2, alpha**1
    VCLEAR    VR2                                ; In place of NOP
                                                 ; Initialize S_0123

;;=============================================================================
;; Computing the syndromes
;; 
;; The syndromes are the remainders from dividing the received polynomial 
;; (with embedded error) by all the factors (roots) of the code generator poly
;;    R(x)/(x + alpha**i) = Q_i(x) + S_i/(x + alpha**i)
;;    S_i = Q_i(x)*(x + alpha**i) + R(x)
;;  When x = alpha**i we get
;;    S_i = R(alpha**i) and this is a number not a polynomial
;;  Let a[i] be the ith root alpha**i, T = 2t - 1
;;  the array indexing begins from 0 but the first root is alpha**1 (a[0])
;;    S_0   = R[N-1]*(a[0])^N-1 + R[N-2]*(a[0])^N-2 + ... + R[0]
;;    S_1   = R[N-1]*(a[1])^N-1 + R[N-2]*(a[1])^N-2 + ... + R[0]
;;    S_2   = R[N-1]*(a[2])^N-1 + R[N-2]*(a[2])^N-2 + ... + R[0]
;;    ...                                                    
;;    S_T   = R[N-1]*(a[T])^N-1 + R[N-2]*(a[T])^N-2 + ... + R[0]
;;    S_i   = (((R[N-1]*a[i] + R[N-2])a[i] + R[N-3])a[i] + ... + R[0])
;;  The operations can be pipelined as follows
;;            0         0         0         0         -> VR2 (accumulator)
;;         *  a[1]      a[2]      a[3]      a[4]      -> VR1 (roots)
;;         -------------------------------------------
;;         +  R[N-1]    R[N-1]    R[N-1]    R[N-1]    -> VR0 packed data bytes
;;         =                                          -> VR2 
;;         *  a[1]      a[2]      a[3]      a[4]      -> VR1 (roots)
;;         -------------------------------------------
;;         +  R[N-2]    R[N-2]    R[N-2]    R[N-2]    -> VR0 packed data bytes
;;         =                                          -> VR2 
;;         *  a[1]      a[2]      a[3]      a[4]      -> VR1 (roots)
;;         -------------------------------------------
;;         ...
;;         +  R[1]      R[1]      R[1]      R[1]     -> VR0 packed data bytes
;;         =                                          -> VR2 
;;         *  a[1]      a[2]      a[3]      a[4]      -> VR1 (roots)
;;         -------------------------------------------
;;         +  R[0]      R[0]      R[0]      R[0]     -> VR0 packed data bytes
;;         =  S_1       S_2       S_3       S_4      -> VR2 (packed syndromes)
;;=============================================================================
    .align 2
    RPTB      _REEDSOLOMON_DECODER_calcSyndrome_innerLoop, AR6
    VGFMAC4   VR2, VR1, VR0                      ; VR2[Bx] = (VR2[Bx]*VR1[Bx])^VR0[Bx]
 || VPACK4    VR0, *+XAR5[0], #1                 ; VR0[31:0] = R1_R1_R1_R1 (pack next byte of data)
    VGFMAC4   VR2, VR1, VR0                      ; VR2[Bx] = (VR2[Bx]*VR1[Bx])^VR0[Bx]
 || VPACK4    VR0, *+XAR5[0], #2                 ; VR0[31:0] = R2_R2_R2_R2 (pack next byte of data)
    VGFMAC4   VR2, VR1, VR0                      ; VR2[Bx] = (VR2[Bx]*VR1[Bx])^VR0[Bx]
 || VPACK4    VR0, *XAR5++, #3                   ; VR0[31:0] = R3_R3_R3_R3 (pack next byte of data)
    VGFMAC4   VR2, VR1, VR0                      ; VR2[Bx] = (VR2[Bx]*VR1[Bx])^VR0[Bx]
 || VPACK4    VR0, *+XAR5[0], #0
    NOP
_REEDSOLOMON_DECODER_calcSyndrome_innerLoop:
    ;;-------------------------------------------------------------------------
    ;; Process any remaining bytes (n % 4)
    ;;-------------------------------------------------------------------------
    CMP       T, #0                              ; if no bytes left store syndrome
    SBF       _REEDSOLOMON_DECODER_calcSyndrome_store, EQ  
    VGFMAC4   VR2, VR1, VR0 
 || VPACK4    VR0, *+XAR5[0], #1                 ; one extra byte

    CMP       T, #1                              ; if no bytes left store syndrome
    SBF       _REEDSOLOMON_DECODER_calcSyndrome_store, EQ  
    VGFMAC4   VR2, VR1, VR0 
 || VPACK4    VR0, *+XAR5[0], #2                 ; two extra bytes
  
    CMP       T, #2                              ; if no bytes left store syndrome
    SBF       _REEDSOLOMON_DECODER_calcSyndrome_store, EQ  
    VGFMAC4   VR2, VR1, VR0                      ; three extra bytes

    ;;-------------------------------------------------------------------------
    ;; store 4 syndromes at a time
    ;;-------------------------------------------------------------------------
_REEDSOLOMON_DECODER_calcSyndrome_store:
    VMOV32    *XAR7++, VR2                       ; save to Object->pSyndrome
    MOVL      XAR5, *-SP[STK_PDATA]              ; restore pData
                                                 ; if all syndromes not done: loop back
    BANZ      _REEDSOLOMON_DECODER_calcSyndrome_outerLoop, AR0--  
                                                 ; else return
    REEDSOLOMON_DECODER_CONTEXT_RESTORE
    LRETR

;;  End of File
    
