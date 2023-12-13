;;*****************************************************************************
;;! \file source/vcu2/vcu2_deinterleaver.asm
;;!
;;! \brief  OFDM De-interleaver
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
;;*****************************************************************************
;;
;;
;;*****************************************************************************
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; DEINTERLEAVER Routine defines


;; Argument structure defines
ARG_OFF_INBUF           .set    0
ARG_OFF_OUTBUF          .set    2
ARG_OFF_SYMBOL          .set    4
ARG_OFF_N               .set    6
ARG_OFF_M               .set    7
ARG_OFF_B               .set    8
ARG_OFF_V               .set    9
ARG_OFF_U               .set    10
ARG_OFF_A               .set    11
ARG_OFF_N_I             .set    12
ARG_OFF_N_J             .set    13
ARG_OFF_M_I             .set    14
ARG_OFF_M_J             .set    15


;; Stack defines
;;
;;   |_______|
;;   |_______|<- Stack Pointer(SP) <---SP
;;   |_______|<- STK_ARG   (SP-2)
;;   |_______|<- STK_B     (SP-4)
;;   |_______|<- STK_V     (SP-5)
;;   |_______|<- STK_A     (SP-6)
;;   |_______|<- STK_U     (SP-7)
;;
LOCAL_FRAME_SIZE .set    7
STK_ARG          .set    2
STK_B            .set    4
STK_V            .set    5
STK_A            .set    6
STK_U            .set    7

;;*****************************************************************************
;; macros
;;*****************************************************************************
;;
;; MACRO   : 'DEINTERLEAVER_CONTEXT_SAVE'
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on entry into DEINTERLEAVER routine
;;
DEINTERLEAVER_CONTEXT_SAVE    .macro
    PUSH      XAR1
    PUSH      XAR2
    PUSH      XAR3
    ADDB      SP, #LOCAL_FRAME_SIZE          ; allocate stack space for local frame
                                             ; save VRx to stack
    .endm
;;
;; MACRO   : 'DEINTERLEAVER_CONTEXT_RESTORE'
;; SIZE    : Number of WORDS/Number of Cycles 4
;; USAGE   : Called on exit from DEINTERLEAVER routine
;;
DEINTERLEAVER_CONTEXT_RESTORE    .macro
    SUBB      SP, #LOCAL_FRAME_SIZE              ; deallocate stack space for local frame
    POP       XAR3
    POP       XAR2
    POP       XAR1
    .endm

;;*****************************************************************************
;; globals
;;*****************************************************************************
    .if __TI_EABI__
    .asg DEINTERLEAVER_run, _DEINTERLEAVER_run
    .endif

    .global _DEINTERLEAVER_run

;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text
;;
;; \brief De-interleave the symbols to get the original bits
;;
;; This piece of code implements the below algorithm:
;;
;; for (I=0;I<m; I++)
;; {
;;   i = (a * I  - u * J) % m;
;;   j = (b * J  - v * i) % n;
;;   Y(i+j*m) = X(I);
;; }
;; - *+XAR4[0]: uint16_t  *pInBuffer ->  Pointer to the input buffer
;; - *+XAR4[2]: uint16_t  *pOutBuffer ->  Pointer to the input buffer
;; - *+XAR4[4]: uint16_t n ->  number of OFDM symbols in each interleaving block
;; - *+XAR4[5]: uint16_t m ->  number of sub carriers in each OFDM symbol
;; - *+XAR4[6]: uint16_t n_i ->  Circular shift of the rows
;; - *+XAR4[7]: uint16_t n_j ->  Circular shift of the rows
;; - *+XAR4[8]: uint16_t m_i ->  Circular shift of the columns
;; - *+XAR4[9]: uint16_t m_j ->  Circular shift of the columns
;;
;; \return De-interleaved bits(pointer to bits in the structure)
;;
;; Register Usage:
;; XAR0: index into the structure for elements at an OFF >7 from  structure base
;;       /index into the output buffer
;; XAR1: pointer to the output
;; XAR2: loop counter
;; XAR3: pointer to the input
;; XAR4: pointer to the structure
;; XAR5: symbol J
;; XAR6:
;; XAR7:
;; AL:
;; AH:
;; P:
;; T:
;;
_DEINTERLEAVER_run:
    DEINTERLEAVER_CONTEXT_SAVE
    MOVL      XAR1, *+XAR4[ARG_OFF_OUTBUF]       ; XAR1 -> output
    MOVL      XAR3, *+XAR4[ARG_OFF_INBUF]        ; XAR3 -> output
    MOVL      XAR5, *+XAR4[ARG_OFF_SYMBOL]       ; XAR5 -> symbol
    MOVZ      AR2, *+XAR4[ARG_OFF_M]
    SUBB      XAR2, #3                           ; loop_counter = m - 3
    MOV       AR0, #ARG_OFF_B                    ; Save b,v to local frame
    MOVL      ACC, *+XAR4[AR0]
    MOVL      *-SP[STK_B], ACC
    MOV       AR0, #ARG_OFF_A                    ; Save a,u to local frame
    MOVL      ACC, *+XAR4[AR0]
    MOVL      *-SP[STK_A], ACC
    MOVL      XAR0, #0
    VSETCPACK                                    ; [Lo : Hi] -> [Real : Imag] packing

_DEINTERLEAVER_run_outerLoop:
    VCLEARALL                                    ; Initializes VR0L = I = 0

    ;;-------------------------------------------------------------------------
    ;; First Iteration
    ;;
    VMOV32    VR4, *+XAR4[ARG_OFF_M]             ; VR4H = m, VR4L = n
    VMOV16    VR0H, *+XAR5[0]                    ; VR0H = J, VR0L = I
    VMOV32    VR1, *-SP[STK_A]                   ; VR1H = u, VR1L = a
    VMOV32    VR6, VR0                           ; save current {J,I} in VR6
    VCMPY     VR3, VR2, VR1, VR0                 ; VR3 = a*I - u*J | VR2 = a*J + u*I
    VMOV16    VR0L, *+XAR5[0]                    ; DS1 | VR0L = J
    VMOD32    VR0H, VR3, VR4H                    ; VR0H = (VR3 % VR4H) = i = (a*I - u*J) % m
    VMOV32    VR1, *-SP[STK_B]                   ; DS1 | VR1H := v, VR1L := b
    NOP                                          ; DS2
    NOP                                          ; DS3
    NOP                                          ; DS4
    NOP                                          ; DS5
    NOP                                          ; DS6
    NOP                                          ; DS7
    NOP                                          ; DS8
    ;;-------------------------------------------------------------------------
    ;; Second Iteration
    ;;
    VCMPY     VR3, VR2, VR1, VR0                 ; VR3 = b*J - v*i | VR2 = b*i + v*J
    VMOV16    VR5L, VR0H                         ; DS1 | VR5L = i    Save current i
    VMOD32    VR5H, VR3, VR4L                    ; VR5H = (VR3 % VR4L) = j =  (b*J - v*i) % n
 || VMOV32    VR0, VR6                           ; VR0 = {J,I}
                                                 ; compute j = (b * J �- v * i) % n; load back saved {J,I}
    VINC      VR0L                               ; DS1 | increment I
 || VMOV32    VR1, *-SP[STK_A]                   ;     | VR1H = u, VR1L = a  ; load u, a
    VCMPY     VR3, VR2, VR1, VR0                 ; DS2 | VR3 = a*I - u*J compute a * I - u * J
    VMOV32    VR1, *-SP[STK_B]                   ; DS3 | DS1 | VR1H = v, VR1L = b  load v, b
    MOV       AL, *XAR3++                        ; DS4 |  AL = X(I)   load X(I)
    NOP                                          ; DS5
    NOP                                          ; DS6
    VMOV32    VR6, VR0                           ; DS7 | Save {J,I} in VR6
    VMOV16    VR0L, *+XAR5[0]                    ; DS8 | VR0L = J    load J
    VMOD32    VR0H, VR3, VR4H                    ; VR0H = (VR3 % VR04H) = i = (a*I - u*J) % m;
    VMPYADD   VR5, VR5L, VR5H, VR4H              ; DS1 | VR5 = VR5L + VR5H*VR4H = i + j*m    compute i + j*m
    NOP                                          ; DS2 | DS1
    NOP                                          ; DS3 | DS2 -> One Extra NOP for BLDD
    VMOV32    XAR0, VR5                          ; DS4 | move VR5 to AR0
    ;;VMOV32 @XAR0,*(0:0x120a)
    NOP                                          ; DS5
    NOP                                          ; DS6
    NOP                                          ; DS7
    ;;-------------------------------------------------------------------------
    ;; Remaining but one Iterations (20 cycles)
    ;;
    RPTB      _DEINTERLEAVER_run_innerLoop, AR2  ; DS8 | Set Loop Start, Loop m-3 times
    VCMPY     VR3, VR2, VR1, VR0                 ; VR3 = b*J - v*i  compute b * J �- v * i
    VMOV16    VR5L, VR0H                         ; DS1 | VR5L = i    Save current i
    VMOD32    VR5H, VR3, VR4L                    ; VR5H = (VR3 % VR4L) = j = (b*J - v*i) % n
 || VMOV32    VR0, VR6                           ; VR0 = {J,I} load back saved J,I
    VINC      VR0L                               ; DS1 | increment I
 || VMOV32    VR1, *-SP[STK_A]                   ;     | VR1H = u, VR1L = a   load u, a
    MOV       *+XAR1[AR0], AL                    ; DS2 |  Save previous Y(i+j*m)
    VCMPY     VR3, VR2, VR1, VR0                 ; DS3 |  VR3 = a*I - u*J compute a * I - u * J
    VMOV32    VR1, *-SP[STK_B]                   ; DS4 | DS1 | VR1H = v, VR1L = b  load v, b
    MOV       AL, *XAR3++                        ; DS5 | AL = X(I)   load X(I)
    NOP                                          ; DS6
    VMOV32    VR6, VR0                           ; DS7 | VR6 = {J,I} save current {J,I}
    VMOV16    VR0L, *+XAR5[0]                    ; DS8 | VR0L = J    load J
    VMOD32    VR0H, VR3, VR4H                    ; VR0H = (VR3 % VR4H) = i = (a*I - u*J) % m;
    VMPYADD   VR5, VR5L, VR5H, VR4H              ; DS1 | VR5 = VR5L + VR5H*VR4H = i + j*m, compute i + j*m
    NOP                                          ; DS2 | DS1
    NOP                                          ; DS3 | DS2 -> One Extra NOP for BLDD
    VMOV32    XAR0, VR5                          ; DS4 | move VR5 to AR0
    ;;VMOV32 @XAR0,*(0:0x120a)
    NOP                                          ; DS5
    NOP                                          ; DS6
    NOP                                          ; DS7
    NOP                                          ; DS8
_DEINTERLEAVER_run_innerLoop:
    ;;-------------------------------------------------------------------------
    ;; Last iteration
    ;;
    VCMPY     VR3, VR2, VR1, VR0                 ; VR3 = b*J - v*i  compute b * J �- v * i
    VMOV16    VR5L, VR0H                         ; DS1 | VR5L = i    Save current i
    VMOD32    VR5H, VR3, VR4L                    ; VR5H = (VR3 % VR4L) = j = (b*J - v*i) % n;
    NOP                                          ; DS1
    MOV       *+XAR1[AR0], AL                    ; DS2 | Save previous Y(i+j*m)
    NOP                                          ; DS3
    NOP                                          ; DS4
    MOV       AL, *XAR3++                        ; DS5 | AL = X(I)   load X(I)
    NOP                                          ; DS6
    NOP                                          ; DS7
    NOP                                          ; DS8
    VMPYADD   VR5, VR5L, VR5H, VR4H              ; VR5 = VR5L + VR5H*VR4H = i + j*m compute i + j*m
    NOP                                          ; DS1
    NOP                                          ; DS2 -> One Extra NOP for BLDD
    VMOV32    XAR0, VR5                          ; move VR5 to AR0
    ;;VMOV32 @XAR0,*(0:0x120a)
    NOP                                          ;
    NOP                                          ;
    NOP                                          ;
    MOV       *+XAR1[AR0], AL                    ; Save Y(i+j*m)

    DEINTERLEAVER_CONTEXT_RESTORE
    LRETR

;; End of file
