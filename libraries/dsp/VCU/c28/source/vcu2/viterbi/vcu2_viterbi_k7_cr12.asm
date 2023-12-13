;;*****************************************************************************
;;! \file source/vcu2/vcu2_viterbi_k7_cr12_plc.asm
;;!
;;! \brief  Viterbi Decoding K = 7, CR = 1/2
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
	.cdecls  C, LIST, "vcu2_types.h"
;;*****************************************************************************
;; defines
;;*****************************************************************************
;; VITERBI Routine defines
CONSTRAINT_LENGTH           .set    7
NSTATES                     .set    1 << (CONSTRAINT_LENGTH - 1)
FRAME_LENGTH                .set    64
BLOCK_SIZE                  .set    64
NSTAGES_DECODING_DEPTH      .set    64
MODE_DECODEALL              .set    0
MODE_OVERLAPINIT            .set    1
MODE_OVERLAPDECODE          .set    2
MODE_OVERLAPLAST            .set    3


;; Argument structure defines
ARG_INBUFFER                .set    0
ARG_OUTBUFFER               .set    2
ARG_TRANSHIST               .set    4
ARG_BMSELINIT               .set    6
ARG_SMETRICINIT             .set    8
ARG_NBITS                   .set    9
ARG_CONSTRAINT              .set    10
ARG_NSTATES                 .set    11
ARG_CODERATE                .set    12
ARG_MODE                    .set    13
ARG_TRANS_S1                .set    14
ARG_TRANS_S2                .set    16
ARG_TRANS_W1                .set    18
ARG_TRANS_W2                .set    20
ARG_TRANS_TMP               .set    22

;; Stack defines
;;
;;   |_______|
;;   |_______|<- Stack Pointer   (SP) <---SP
;;   |_______|<- STK_ARG_PTR     (SP-2)
;;   |_______|<- STK_ARG_MODE    (SP-4)
;;   |_______|<- STK_ARG_NBITS   (SP-6)
;;
LOCAL_FRAME_SIZE            .set    6
STK_ARG_PTR                 .set    2
STK_ARG_MODE                .set    4
STK_ARG_NBITS               .set    6
;;*****************************************************************************
;; macros
;;*****************************************************************************
;;
;; MACRO   : 'VITERBI_DECODER_CONTEXT_SAVE'
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on entry into viterbi decoder routine
;;
VITERBI_DECODER_CONTEXT_SAVE    .macro
    PUSH      XAR1
    PUSH      XAR2
    PUSH      XAR3
    ADDB      SP, #LOCAL_FRAME_SIZE              ; allocate stack space for local frame
    .endm
;;
;; MACRO   : 'VITERBI_DECODER_CONTEXT_RESTORE'
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on exit from viterbi decoder routine
;;
VITERBI_DECODER_CONTEXT_RESTORE    .macro
    SUBB      SP, #LOCAL_FRAME_SIZE              ; deallocate stack space for local frame
    POP       XAR3
    POP       XAR2
    POP       XAR1
    .endm
;;*****************************************************************************
;; globals
;;*****************************************************************************
    .if __TI_EABI__
    .asg VITERBI_DECODER_runK7CR12, _VITERBI_DECODER_runK7CR12
    .asg VITERBI_DECODER_initK7CR12, _VITERBI_DECODER_initK7CR12
    .asg VITERBI_DECODER_rescaleK7CR12, _VITERBI_DECODER_rescaleK7CR12
    .endif

    .global _VITERBI_DECODER_runK7CR12
    .global _VITERBI_DECODER_initK7CR12
    .global _VITERBI_DECODER_rescaleK7CR12

_rescaleBuffer .usect ".ebss", 64, 1, 1
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;;
;; \brief
;;
;; \param Handle to the structure, VITERBI_DECODER_DECODER_Obj(passed in XAR4)
;; - *+XAR4[0]: *pInBuffer          -> Input buffer pointer
;; - *+XAR4[2]: *pOutBuffer         -> Output buffer pointer
;; - *+XAR4[4]: *pTransitionHistory -> Transition History bits pointer
;; - *+XAR4[6]: *pBMSELInit         -> Initialization value for the BMSEL register
;; - *+XAR4[8]: stateMetricInit     -> Initialization value for the state metrics
;; - *+XAR4[9]: nBits               -> Number of bits to be decoded
;; - *+XAR4[10]: constraintLength   -> Constraint Length, i.e. K
;; - *+XAR4[11]: nStates            -> #states = 2^(K - 1)
;; - *+XAR4[12]: codeRate           -> The symbol code rate
;; - *+XAR4[13]: mode               -> Viterbi mode enumerator
;; - *+XAR4[14]: *pTransitionStart1 -> Points to the start of the tranistion history buffer
;; - *+XAR4[16]: *pTransitionStart2 -> Points to the mid of the tranistion history buffer
;; - *+XAR4[18]: *pTransitionWrap1  -> Points to the mid of the tranistion history buffer
;; - *+XAR4[20]: *pTransitionWrap2  -> Points to the end of the tranistion history buffer
;; - *+XAR4[22]: *pTransitionTemp   -> Points to a temporary(scratch) tranistion history buffer
;; \note
;; - The transition history buffer will have 5 pointers associated with it
;;  - pTransitionHistory(hist_p): start of the transition history buffer
;;  - pTransitionStart1(S1_p): points to where the transition update should start
;;  - pTransitionStart2(S2_p: points to the mid point of the overlap(S1_p + 4*nUnencodedBits)
;;  - pTransitionWrap1(W1_p): points to where trace overlap 2 should go (wrap, S1_p + 4*nUnencodedBits)
;;  - pTransitionWrap2(W2_p): points to the end of the overlap(S1_p + 2*4*nUnencodedBits)
;;
;;   CBITS  = 128(coded bits per block)
;;   UBITS  = CBITS/2 = 64(uncoded bits per block)
;;   UWORDS = 4 (4 words required to store UBITS)
;;
;;   Transition history(bits per stage)--->
;;                <-------64 bits----->
;;                +----+----+----+----+   ^
;;  S1_p->hist_p->|    |    |    |    |   |
;;          ^     |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;      4*UBITS   |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;          v     |    |    |    |    |   |
;;    S2_p->W1_p->|    |    |    |    | 128 stages
;;          ^     |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;      4*UBITS   |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;          |     |    |    |    |    |   |
;;          v     |    |    |    |    |   |
;;          W2_p->|    |    |    |    |   |
;;                +----+----+----+----+   v
;;
;; \return Decoded bits in the output buffer pointed by the VITERBI_DECODER_DECODER_Obj.pOutBuffer
;;
_VITERBI_DECODER_runK7CR12:
    VITERBI_DECODER_CONTEXT_SAVE
    ;V.C.130217- suppose you have an input sequence 0x03020100, you would encode
    ; in the seqence 00, 01, 02 and 03. You decode in the exact opposite
    ; sequence 03, 02, 01 and 00 but with OPACK you pack from MSb of VR0 and
    ; end up with 0x00010203.
    ;
    ; Disabling OPACK, decode in order 03, 02, 01 and 00.  PACK from lower end of VR0
    ; meaning your output looks like 0xc0408000, i.e. bit-reversed at each byte
    ;
    ; Using BITFLIP will reverse the register end to end so you endup with 0x00010203
    ; anyways, but we can use the Galois field instruction VREB to set it to 0x03020100
    ; (enable OPACK in this case)
    ;
	VSETOPACK                                    ; VSTATUS.OPACK = 1, start packing the decoded
                                                 ; bits from trace back into VT1 starting from the
                                                 ; MSb, this obviates the need to manually flip the
                                                 ; result each time
    SETC      SXM                                ; Sign extension mode
    SETC      OVM                                ; Overflow mode(no saturation)

;;=============================================================================
;;
;; Register Usage
;;  XAR0: Index into the structure members that exceed index of 7 from start of structure
;;        /traceback overlap inner loop counter
;;        /temp pointer to structure in the pointer swaps
;;  XAR1: Pointer to the input LLR
;;        /Index into the structure members that exceed index of 7 from start of structure
;;  XAR2: Branch Metric Select
;;  XAR3: Pointer to the Transition History Array(as well as S1_p, W1_p depending on modes)
;;        /used in pointer swaps
;;  XAR4: Pointer to the viterbi structure
;;  XAR5: Output array
;;        /used in pointer swaps
;;  XAR6: Loop counter
;;  XAR7: points to the temporary transition bit array
;;        /Loop counter for metric update when nBits < 8
;;    AL: Number of Input bits
;;    AH:
;;

    MOV       AR0, #ARG_MODE
    MOV       AL, *+XAR4[AR0]                    ; Save the mode to the stack
    MOV       *-SP[STK_ARG_MODE], AL

    MOVL      XAR5, *+XAR4[ARG_OUTBUFFER]        ; XAR5 -> output_array

    MOV       AR0, #ARG_NBITS
    MOV       AL, *+XAR4[AR0]
    LSR       AL, #1                             ; AL = nBits/2
    MOV       *-SP[STK_ARG_NBITS], AL            ; Save the number of bits to the stack

    CMP       AL, #0                             ; Check if the number of output bits are not zero
    BF        _VITERBI_DECODER_runK7CR12_nonZeroACS, NEQ ; if so jump to the metric calculations

                                                 ; Since nBits ==  0 at this point
    MOV       AR0, #ARG_TRANS_W1                 ; We need only proceed to traceback, Load the
    MOVL      XAR3, *+XAR4[AR0]                  ; the Wrap pointer(to the transition history buffer)
                                                 ; and proceed to the decode phase directly
    BF        _VITERBI_DECODER_runK7CR12_overlapDecode, UNC

_VITERBI_DECODER_runK7CR12_nonZeroACS:
	MOVZ	  AR7, AL						     ; AR7 = (nBits/2)
    LSR       AL, #1                             ; AL = (nBits/2)/2. We process two stages per RPTB
    SUBB      AL, #2                             ; loop_counter = nBits/4 - 1 - 1.
    MOVZ      AR6, AL                            ; we process 2 bits per stage and 2 stages per iteration of the RPTB which will
                                                 ; itself iterates N+1 hence the first -1. The last two stages are performed outside the RPTB
                                                 ; hence the second -1
    MOVL      XAR1,*+XAR4[ARG_INBUFFER]
    MOVL      XAR3,*+XAR4[ARG_TRANSHIST]
                                                 ; if(mode==0/1) jump to metric calculations
                                                 ; We wont be using the S1_p in this case
    CMP       *-SP[STK_ARG_MODE], #MODE_OVERLAPDECODE
    BF        _VITERBI_DECODER_runK7CR12_metricUpdate, LT
                                                 ;else if(mode==2/3) we need to start saving transition bits to
    MOV       AR0, #ARG_TRANS_S1                 ;address pointed to be S1_p
    MOVL      XAR3, *+XAR4[AR0]

_VITERBI_DECODER_runK7CR12_metricUpdate:
    MOVL      XAR2, *+XAR4[ARG_BMSELINIT]        ; Initialize the BMSEL register for butterfly 0 to K-1
    VMOV32    VR2, *XAR2++                       ; Initialize BMSEL for butterfly 0 to 7
    VMOV32    VR3, *XAR2++                       ; Initialize BMSEL for butterfly 8 to 15
    VMOV32    VR4, *XAR2++                       ; Initialize BMSEL for butterfly 16 to 23
    VMOV32    VR5, *XAR2++                       ; Initialize BMSEL for butterfly 24 to 31


    VITBM2    VR0, *XAR1++                       ; Calculate and store BMs in VR0L and VR0H

    MOV 	  AL, AR7						     ; AL = AR7 i.e. (nBits/2)
    CMPB      AL, #8                             ; if(AL < 8) jump to metric(less than 8) calculations
    BF        _VITERBI_DECODER_runK7CR12_lessThan8MetricUpdate, LT
    ANDB      AL, #0x1							 ; if(AL is odd)jump to metric(odd bits) calculations
    BF        _VITERBI_DECODER_runK7CR12_oddBitsMetricUpdate, NEQ
    										     ; else proceed with regular 2 stage RPTB metric updates
    .align 2
    RPTB      _VITERBI_DECODER_runK7CR12_metricUpdateLoop, AR6
    VITSTAGE                                     ; Compute NSTATES/2 butterflies in parallel,
 || VITBM2    VR0, *XAR1++                       ; compute branch metrics for next butterfly
    VMOV32    *XAR3++, VT1                       ; Store VT1
    VMOV32    *XAR3++, VT0                       ; Store VT0
    VITSTAGE                                     ; Compute NSTATES/2 butterflies in parallel,
 || VITBM2    VR0, *XAR1++                       ; compute branch metrics for next butterfly
    VMOV32    *XAR3++, VT1                       ; Store VT1
    VMOV32    *XAR3++, VT0                       ; Store VT0
_VITERBI_DECODER_runK7CR12_metricUpdateLoop:
    VITSTAGE                                     ; Compute NSTATES/2 butterflies in parallel,
 || VITBM2    VR0, *XAR1++                       ; compute branch metrics for next butterfly
    VMOV32    *XAR3++, VT1                       ; Store VT1
    VMOV32    *XAR3++, VT0                       ; Store VT0
    VITSTAGE                                     ; Compute NSTATES/2 butterflies in parallel,
    VMOV32    *XAR3++, VT1                       ; Store VT1
    VMOV32    *XAR3++, VT0                       ; Store VT0
_VITERBI_DECODER_runK7CR12_metricUpdateEnd:
	BF		  _VITERBI_DECODER_runK7CR12_lessThan8MetricUpdateEnd, UNC
_VITERBI_DECODER_runK7CR12_oddBitsMetricUpdate:
_VITERBI_DECODER_runK7CR12_lessThan8MetricUpdate:
	SUBB	  XAR7, #1							 ; AR7 = (nBits/2) - 1
_VITERBI_DECODER_runK7CR12_lessThan8MetricUpdateLoop:
    VITSTAGE                                     ; Compute NSTATES/2 butterflies in parallel,
 || VITBM2    VR0, *XAR1++                       ; compute branch metrics for next butterfly
    VMOV32    *XAR3++, VT1                       ; Store VT1
    VMOV32    *XAR3++, VT0                       ; Store VT0
	BANZ      _VITERBI_DECODER_runK7CR12_lessThan8MetricUpdateLoop, AR7--
_VITERBI_DECODER_runK7CR12_lessThan8MetricUpdateEnd:
                                                 ; if(mode==1), we are processing first block so no trace/decode
    CMP       *-SP[STK_ARG_MODE], #MODE_OVERLAPINIT
    BF        _VITERBI_DECODER_runK7CR12_toggleSPointers, EQ

    ZAPA                                         ; else if(mode==2/3), we have calculated state metrics proceed to trace/decode
    CMP       *-SP[STK_ARG_MODE], #MODE_DECODEALL
    BF        _VITERBI_DECODER_runK7CR12_overlapDecode, NEQ
                                                 ; else if(mode==0), we need to traceback in 1-shot(32-bit word per output bit)
    MOV       AL, *-SP[STK_ARG_NBITS]            ; loop_counter = UBITS - (K-1) - 1 (last -1 is to account for loop iteration)
    MOVZ      AR6, AL                            ; UBITS = nBits/2
    SUBB      XAR6, #((CONSTRAINT_LENGTH-1)+1)   ; K = constraint length

    LSL       AL, #1                             ; AL = 2(sizeof 32-bits) * (nBits/2)
    MOV       AR0, #ARG_TRANS_TMP
    MOVL      XAR7, *+XAR4[AR0]                  ; XAR7 -> pTransitionTemp[nBits]
    ADDL      XAR7, ACC

    RPT       #((CONSTRAINT_LENGTH-1)*2 - 1 )    ; Zero out the last (K-1)*2 output bits
 || MOV       *--XAR7, AH                        ;
                                                 ; XAR7 -> pTransitionTemp[nBits - (K-1)]
    VCLEAR    VR0
    VCLEAR    VR1

_VITERBI_DECODER_runK7CR12_tracebackLoop1:
    VMOV32    VT0, *--XAR3
    VMOV32    VT1, *--XAR3
    VTRACE    *--XAR7, VR0, VT0, VT1
    BANZ      _VITERBI_DECODER_runK7CR12_tracebackLoop1, AR6--
                                                 ; The end of MODE_DECODEALL, proceed to exit
    BF        _VITERBI_DECODER_runK7CR12_toggleWPointers, UNC

                                                 ; mode == 2/3
_VITERBI_DECODER_runK7CR12_overlapDecode:
    MOV       AL, *-SP[STK_ARG_NBITS]            ; loop_counter = (nBits/2 - 1)
    MOVZ      AR6, AL
    SUBB      XAR6, #1

	;V.C.130218-not needed
    ;MOV       AR0, #ARG_TRANS_TMP
    ;MOVL      XAR7, *+XAR4[AR0]

    VCLEAR    VR0
    VCLEAR    VR1
                                                 ; if(mode==2) go to trace/decode of regular sized block
    CMP       *-SP[STK_ARG_MODE], #MODE_OVERLAPLAST
    BF        _VITERBI_DECODER_runK7CR12_tracebackLoopOverlap1, NEQ
                                                 ; else(mode==3) trace/decode of irregular sized block
                                                 ; note: loop_counter =  64-(K-1)-1, but when nBits = 0 AR6 = -1
                                                 ; so we must compensate for the -1 by making loop_counter = 64-(K-1)
    ADDB      XAR6, #(BLOCK_SIZE - (CONSTRAINT_LENGTH-1))
    MOV       AL, AR6                            ; loop_counter = [((nBits/2 - 1) + (nBits/2 - (K-1))] {prev_blk + cur_blk -2*(K-1) -1(loop)}
    AND       AL, #0x1F                          ;
    MOV       AR0, AL                            ; inner_loop_counter = loop_counter % 32
                                                 ; mode == 3 OVERLAPLAST
_VITERBI_DECODER_runK7CR12_tracebackLoopOverlap0:
    VMOV32    VT0, *--XAR3
    VMOV32    VT1, *--XAR3
    VTRACE    VR1, VR0, VT0, VT1
                                                 ;if(trace<32 bits) goto overlap0 end
    BANZ      _VITERBI_DECODER_runK7CR12_tracebackLoopOverlap0End, AR0--
    VREVB     VR1								 ; Reverse VR1
    VMOV32    *--XAR5, VR1                       ;else(32-bits were traced and accumulated) store to output memory
    MOVB      XAR0, #31                          ; inner_loop_counter += 32

_VITERBI_DECODER_runK7CR12_tracebackLoopOverlap0End:
    MOV       AL, AR6                            ;if(loop_counter!=(nBits/2 - (K-1))) goto end1 of overlap 0
    CMPB      AL, #(BLOCK_SIZE - (CONSTRAINT_LENGTH-1))
    BF		  _VITERBI_DECODER_runK7CR12_tracebackLoopOverlap0End1, NEQ

    MOV       AR1, #ARG_TRANS_W1                 ;else(loop_counter==(nBits/2 - (K-1)))switch trans history pointer from S1 to W1
    MOVL      XAR3, *+XAR4[AR1]
                                                 ;if(loop_counter!=0) goto overlap 0
_VITERBI_DECODER_runK7CR12_tracebackLoopOverlap0End1:
    BANZ      _VITERBI_DECODER_runK7CR12_tracebackLoopOverlap0, AR6--
                                                 ;else(loop_counter==0) goto toggle S pointers
    BF        _VITERBI_DECODER_runK7CR12_toggleSPointers, UNC
                                                 ; mode == 2  OVERLAPDECODE
_VITERBI_DECODER_runK7CR12_tracebackLoopOverlap1:
                                                 ; For any viterbi stage K
    VMOV32    VT0, *--XAR3
    VMOV32    VT1, *--XAR3
    VTRACE    VR1, VR0, VT0, VT1
                                                 ;if(loop_counter!=0) goto overlap 1
    BANZ      _VITERBI_DECODER_runK7CR12_tracebackLoopOverlap1, AR6--
                                                 ;else(loop_counter==0), trace/decode from 2nd half of block
    MOV       AR0, #ARG_TRANS_W1                 ;The 2nd half of the block actually produces decode bits to output
    MOVL      XAR3, *+XAR4[AR0]                  ;when overlapping is used

    VMOV32    VT0, *--XAR3
    .align  2                                    ;Decoding the first 32-bits, 6 of which are already in VR1 from overlap 1
    NOP                                          ;odd aligning the repeat block
    RPTB      _VITERBI_DECODER_runK7CR12_tracebackLoopOverlap2, #12
    VMOV32    VT1, *--XAR3
    VTRACE    VR1, VR0, VT0, VT1
 || VMOV32    VT0, *--XAR3
    VMOV32    VT1, *--XAR3
    VTRACE    VR1, VR0, VT0, VT1
 || VMOV32    VT0, *--XAR3
_VITERBI_DECODER_runK7CR12_tracebackLoopOverlap2:
	VREVB     VR1								 ; Reverse VR1
    VMOV32    *+XAR5[2], VR1

    .align  2                                    ;Decoding the second 32-bits
    NOP                                          ;odd aligning the repeat block
    RPTB      _VITERBI_DECODER_runK7CR12_tracebackLoopOverlap3, #15
    VMOV32    VT1, *--XAR3
    VTRACE    VR1, VR0, VT0, VT1
 || VMOV32    VT0, *--XAR3
    VMOV32    VT1, *--XAR3
    VTRACE    VR1, VR0, VT0, VT1
 || VMOV32    VT0, *--XAR3
_VITERBI_DECODER_runK7CR12_tracebackLoopOverlap3:
	VREVB     VR1								 ; Reverse VR1
    VMOV32    *XAR5, VR1

_VITERBI_DECODER_runK7CR12_toggleWPointers:
    MOVL      XAR0, XAR4
    ADDB      XAR0, #ARG_TRANS_W1
    MOVL      XAR3, *XAR0++
    MOVL      XAR5, *XAR0
    MOVL      *XAR0, XAR3
    MOVL      *--XAR0, XAR5

_VITERBI_DECODER_runK7CR12_toggleSPointers:
    MOVL      XAR0, XAR4
    ADDB      XAR0, #ARG_TRANS_S1
    MOVL      XAR3, *XAR0++
    MOVL      XAR5, *XAR0
    MOVL      *XAR0, XAR3
    MOVL      *--XAR0, XAR5

    VITERBI_DECODER_CONTEXT_RESTORE
    LRETR

;;*****************************************************************************
;;
;; \brief Initializes the constraint length and state metrics
;;
;; \param Handle to the structure, VITERBI_DECODER_Obj(passed in XAR4)
;; - *+XAR4[0]: *pInBuffer          -> Input buffer pointer
;; - *+XAR4[2]: *pOutBuffer         -> Output buffer pointer
;; - *+XAR4[4]: *pTransitionHistory -> Transition History bits pointer
;; - *+XAR4[6]: *pBMSELInit         -> Initialization value for the BMSEL register
;; - *+XAR4[8]: stateMetricInit     -> Initialization value for the state metrics
;; - *+XAR4[9]: nBits               -> Number of bits to be decoded
;; - *+XAR4[10]: constraintLength   -> Constraint Length, i.e. K
;; - *+XAR4[11]: nStates            -> #states = 2^(K - 1)
;; - *+XAR4[12]: codeRate           -> The symbol code rate
;; - *+XAR4[13]: mode               -> Viterbi mode enumerator
;; - *+XAR4[14]: *pTransitionStart1 -> Points to the start of the tranistion history buffer
;; - *+XAR4[16]: *pTransitionStart2 -> Points to the mid of the tranistion history buffer
;; - *+XAR4[18]: *pTransitionWrap1  -> Points to the mid of the tranistion history buffer
;; - *+XAR4[20]: *pTransitionWrap2  -> Points to the end of the tranistion history buffer
;; - *+XAR4[22]: *pTransitionTemp   -> Points to a temporary(scratch) tranistion history buffer
;;
_VITERBI_DECODER_initK7CR12:
    VTCLEAR										 ; Clear the transition bits
    VSETK     #CONSTRAINT_LENGTH                 ; Set constraint length
    MOV       AR0, #ARG_SMETRICINIT
    VSMINIT   *+XAR4[AR0]                        ; Initialize the state metrics
    LRETR

;;*****************************************************************************
;;
;; \brief Rescale the state metrics to prevent overflow
;;
;; \param Handle to the structure, VITERBI_DECODER_Obj(passed in XAR4)
;; - *+XAR4[0]: *pInBuffer          -> Input buffer pointer
;; - *+XAR4[2]: *pOutBuffer         -> Output buffer pointer
;; - *+XAR4[4]: *pTransitionHistory -> Transition History bits pointer
;; - *+XAR4[6]: *pBMSELInit         -> Initialization value for the BMSEL register
;; - *+XAR4[8]: stateMetricInit     -> Initialization value for the state metrics
;; - *+XAR4[9]: nBits               -> Number of bits to be decoded
;; - *+XAR4[10]: constraintLength   -> Constraint Length, i.e. K
;; - *+XAR4[11]: nStates            -> #states = 2^(K - 1)
;; - *+XAR4[12]: codeRate           -> The symbol code rate
;; - *+XAR4[13]: mode               -> Viterbi mode enumerator
;; - *+XAR4[14]: *pTransitionStart1 -> Points to the start of the tranistion history buffer
;; - *+XAR4[16]: *pTransitionStart2 -> Points to the mid of the tranistion history buffer
;; - *+XAR4[18]: *pTransitionWrap1  -> Points to the mid of the tranistion history buffer
;; - *+XAR4[20]: *pTransitionWrap2  -> Points to the end of the tranistion history buffer
;; - *+XAR4[22]: *pTransitionTemp   -> Points to a temporary(scratch) tranistion history buffer
;;
;; \notes
;; - CAUTION: VCU regs being memory mapped is internal info, find alternative to this function
;;
;;=============================================================================
;;
;; Register Usage
;;  XAR0:
;;  XAR1:
;;  XAR2: loop counter
;;  XAR3:
;;  XAR4: Pointer to the viterbi structure
;;  XAR5: Pointer to state metrics
;;  XAR6: copy of XAR5
;;  XAR7:
;;    AL: min metric
;;    AH:
;;
_VITERBI_DECODER_rescaleK7CR12:
    PUSH      XAR2                               ; save off XAR2
    SETC	  SXM, OVM						     ; set sign extension and overflow mode

    MOV		  AL, #0x7FFF						 ; AL will store the minimum metric

	MOVL	  XAR5, #_rescaleBuffer      		 ; Load address of rescale buffer into XAR5
	MOVL      XAR6, XAR5
	MOVL      XAR7, XAR5

	VMOV32    *XAR5++, VSM63: VSM62
	VMOV32    *XAR5++, VSM61: VSM60
	VMOV32    *XAR5++, VSM59: VSM58
	VMOV32    *XAR5++, VSM57: VSM56
	VMOV32    *XAR5++, VSM55: VSM54
	VMOV32    *XAR5++, VSM53: VSM52
	VMOV32    *XAR5++, VSM51: VSM50
	VMOV32    *XAR5++, VSM49: VSM48
	VMOV32    *XAR5++, VSM47: VSM46
	VMOV32    *XAR5++, VSM45: VSM44
	VMOV32    *XAR5++, VSM43: VSM42
	VMOV32    *XAR5++, VSM41: VSM40
	VMOV32    *XAR5++, VSM39: VSM38
	VMOV32    *XAR5++, VSM37: VSM36
	VMOV32    *XAR5++, VSM35: VSM34
	VMOV32    *XAR5++, VSM33: VSM32
 	VMOV32    *XAR5++, VSM31: VSM30
	VMOV32    *XAR5++, VSM29: VSM28
	VMOV32    *XAR5++, VSM27: VSM26
	VMOV32    *XAR5++, VSM25: VSM24
	VMOV32    *XAR5++, VSM23: VSM22
	VMOV32    *XAR5++, VSM21: VSM20
	VMOV32    *XAR5++, VSM19: VSM18
	VMOV32    *XAR5++, VSM17: VSM16
	VMOV32    *XAR5++, VSM15: VSM14
	VMOV32    *XAR5++, VSM13: VSM12
	VMOV32    *XAR5++, VSM11: VSM10
	VMOV32    *XAR5++, VSM9: VSM8
	VMOV32    *XAR5++, VSM7: VSM6
	VMOV32    *XAR5++, VSM5: VSM4
	VMOV32    *XAR5++, VSM3: VSM2
	VMOV32    *XAR5++, VSM1: VSM0

	RPT		  #(NSTATES - 1)
 || MIN	      AL, *--XAR5

 	MOV		  AR2, #((NSTATES >> 3)-1)
_VITERBI_DECODER_rescaleK7CR12_loop:
 	SUB		  *XAR6++ , AL
 	SUB		  *XAR6++ , AL
 	SUB		  *XAR6++ , AL
 	SUB		  *XAR6++ , AL
 	SUB		  *XAR6++ , AL
 	SUB		  *XAR6++ , AL
 	SUB		  *XAR6++ , AL
 	SUB		  *XAR6++ , AL
 	BANZ 	  _VITERBI_DECODER_rescaleK7CR12_loop, AR2--

 	VMOV32    VSM63: VSM62, *XAR7++
	VMOV32    VSM61: VSM60, *XAR7++
	VMOV32    VSM59: VSM58, *XAR7++
	VMOV32    VSM57: VSM56, *XAR7++
	VMOV32    VSM55: VSM54, *XAR7++
	VMOV32    VSM53: VSM52, *XAR7++
	VMOV32    VSM51: VSM50, *XAR7++
	VMOV32    VSM49: VSM48, *XAR7++
	VMOV32    VSM47: VSM46, *XAR7++
	VMOV32    VSM45: VSM44, *XAR7++
	VMOV32    VSM43: VSM42, *XAR7++
	VMOV32    VSM41: VSM40, *XAR7++
	VMOV32    VSM39: VSM38, *XAR7++
	VMOV32    VSM37: VSM36, *XAR7++
	VMOV32    VSM35: VSM34, *XAR7++
	VMOV32    VSM33: VSM32, *XAR7++
 	VMOV32    VSM31: VSM30, *XAR7++
	VMOV32    VSM29: VSM28, *XAR7++
	VMOV32    VSM27: VSM26, *XAR7++
	VMOV32    VSM25: VSM24, *XAR7++
	VMOV32    VSM23: VSM22, *XAR7++
	VMOV32    VSM21: VSM20, *XAR7++
	VMOV32    VSM19: VSM18, *XAR7++
	VMOV32    VSM17: VSM16, *XAR7++
	VMOV32    VSM15: VSM14, *XAR7++
	VMOV32    VSM13: VSM12, *XAR7++
	VMOV32    VSM11: VSM10 , *XAR7++
	VMOV32    VSM9: VSM8  , *XAR7++
	VMOV32    VSM7: VSM6  , *XAR7++
	VMOV32    VSM5: VSM4  , *XAR7++
	VMOV32    VSM3: VSM2  , *XAR7++
	VMOV32    VSM1: VSM0  , *XAR7
    POP       XAR2
    LRETR

;;  End of File    
