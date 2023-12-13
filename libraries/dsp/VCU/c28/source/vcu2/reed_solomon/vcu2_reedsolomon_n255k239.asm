;;*****************************************************************************
;;! \file source/vcu2/reed_solomon/vcu2_reedsolomon_n255k239.asm
;;!
;;! \brief  Reed Solomon Decoder (n,k = 255, 239)
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
;;   |_______|<- STK_NBYTES      (SP-2)
;;   |_______|<- STK_PDATA       (SP-4)

;;
LOCAL_FRAME_SIZE            .set    4
STK_NBYTES                  .set    2
STK_PDATA                   .set    4
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
    .if __TI_EABI__
    .asg REEDSOLOMON_DECODER_runN255K239, _REEDSOLOMON_DECODER_runN255K239
    .asg REEDSOLOMON_DECODER_initN255K239, _REEDSOLOMON_DECODER_initN255K239
    .endif
    .global _REEDSOLOMON_DECODER_runN255K239
    .global _REEDSOLOMON_DECODER_initN255K239
    .ref    _REEDSOLOMON_DECODER_calcSyndrome
    .ref    _REEDSOLOMON_DECODER_berlekampMassey
    .ref    _REEDSOLOMON_DECODER_chienForney
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;; \brief Runs the Reed Solomon Decoder (n,k = 255, 239)
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
;; \param[in] nBytes (AL)   number of bytes in the message
;;
_REEDSOLOMON_DECODER_runN255K239:
;; Local Defines


;;
;; Register Usage:
;;   XAR0:
;;   XAR1:
;;   XAR2:
;;   XAR3:
;;   XAR4: pointer to the structure
;;   XAR5: pointer to the data
;;   XAR6:
;;   XAR7:
;;     AL: number of message bytes
;;     AH:
    REEDSOLOMON_DECODER_CONTEXT_SAVE
    MOV	      *-SP[STK_NBYTES], AL
    MOVL      *-SP[STK_PDATA], XAR5
    LCR       _REEDSOLOMON_DECODER_calcSyndrome
	MOVL      XAR5, *-SP[STK_PDATA]
    LCR       _REEDSOLOMON_DECODER_berlekampMassey
    MOV	      AL, *-SP[STK_NBYTES]
	MOVL      XAR5, *-SP[STK_PDATA]
    LCR       _REEDSOLOMON_DECODER_chienForney
    REEDSOLOMON_DECODER_CONTEXT_RESTORE
    LRETR
;;*****************************************************************************
;; \brief Initializes the Reed Solomon Decoder object
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
;; \param[in] pSyndrome    (XAR5) pointer to the syndromes
;; \param[in] pLambda      (*-SP[4]) pointer to the syndromes
;; \param[in] pOmega       (*-SP[6]) pointer to the syndromes
;; \param[in] pPackedAlpha (*-SP[8])Pointer to the roots of the generator polynomial \f$ x + \alpha^{i}\f$
;; \param[in] pPackedBeta  (*-SP[10])Pointer to the roots of the generator polynomial \f$ x + \beta^{i}\f$
;; \param[in] pRS_expTable (*-SP[12])pointer to the lookup table that converts index to decimal form
;; \param[in] pRS_logTable (*-SP[14])pointer to the lookup table that converts decimal to index form
;; \param[in] pErrorLoc    (*-SP[16])Pointer to the error (location, value) pairs

_REEDSOLOMON_DECODER_initN255K239:
;; Local Defines
STK_PLAMBDA                 .set    (LOCAL_FRAME_SIZE + 6 + 4  )
STK_POMEGA                  .set    (LOCAL_FRAME_SIZE + 6 + 6  )
STK_PPACKEDALPHA            .set    (LOCAL_FRAME_SIZE + 6 + 8  )
STK_PPACKEDBETA             .set    (LOCAL_FRAME_SIZE + 6 + 10 )
STK_PRSEXPTABLE             .set    (LOCAL_FRAME_SIZE + 6 + 12 )
STK_PRSLOGTABLE             .set    (LOCAL_FRAME_SIZE + 6 + 14 )
STK_PERRORLOC               .set    (LOCAL_FRAME_SIZE + 6 + 16 )

;;
;; Register Usage:
;;   XAR0:  index into the structure
;;   XAR1:  Pointer to the pPackedAlpha, pPackedBeta,
;;          RS_expTable, RS_logTable,
;;          lambda, omega,error location 2-tuples
;;   XAR2:
;;   XAR3:
;;   XAR4:  pointer to the structure
;;   XAR5:  pointer to the syndromes
;;   XAR6:
;;   XAR7:
;;
    REEDSOLOMON_DECODER_CONTEXT_SAVE
    MOV       *+XAR4[ARG_N], #RS_BLOCK_N
    MOV       *+XAR4[ARG_K], #RS_BLOCK_K
    MOV       *+XAR4[ARG_T], #RS_BLOCK_T
    MOV       *+XAR4[ARG_NROOTS], #RS_NROOTS
    MOV       AR0, #ARG_PSYNDROME
    MOVL      *+XAR4[AR0], XAR5
    MOV       AR0, #ARG_PLAMBDA
    MOVL      XAR1, *-SP[STK_PLAMBDA]
    MOVL      *+XAR4[AR0], XAR1  
    MOV       AR0, #ARG_POMEGA
    MOVL      XAR1, *-SP[STK_POMEGA]
    MOVL      *+XAR4[AR0], XAR1
    MOV       AR0, #ARG_PPACKEDALPHA
    MOVL      XAR1, *-SP[STK_PPACKEDALPHA]
    MOVL      *+XAR4[AR0], XAR1  
    MOV       AR0, #ARG_PPACKEDBETA
    MOVL      XAR1, *-SP[STK_PPACKEDBETA]
    MOVL      *+XAR4[AR0], XAR1        
    MOV       AR0, #ARG_PRSEXPTABLE
    MOVL      XAR1, *-SP[STK_PRSEXPTABLE]
    MOVL      *+XAR4[AR0], XAR1
    MOV       AR0, #ARG_PRSLOGTABLE
    MOVL      XAR1, *-SP[STK_PRSLOGTABLE]
    MOVL      *+XAR4[AR0], XAR1
    MOV       AR0, #ARG_PERRLOC
    MOVL      XAR1, *-SP[STK_PERRORLOC]
    MOVL      *+XAR4[AR0], XAR1
    REEDSOLOMON_DECODER_CONTEXT_RESTORE
    LRETR

;;  End of File    
