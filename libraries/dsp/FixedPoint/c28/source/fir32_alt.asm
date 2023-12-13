;;#############################################################################
;;! \file source/fir32_alt.asm
;;!
;;! \brief  Alternate 32-bit FIR filter
;;!
;;! \date   Aug 29, 2014
;;! 
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
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; globals
;;*****************************************************************************
    ; Module definition for external reference

 	.if __TI_EABI__
    .asg FIR32_alt_init, _FIR32_alt_init
    .asg FIR32_alt_calc, _FIR32_alt_calc
    .endif

    .def      _FIR32_alt_init
    .def      _FIR32_alt_calc
   
;; Module Structure
;; typedef struct { <------------ XAR4
;;     long *coeff_ptr;        /*  +0  Pointer to Filter coefficient */
;;     long * dbuffer_ptr;     /*  +2  Delay buffer ptr              */
;;     int    cbindex;         /*  +4  Circular Buffer Index         */
;;     int order;              /*  +5  Order of the Filter           */
;;     int input;              /*  +6  Latest Input sample           */ 
;;     int output;             /*  +7  Filter Output                 */
;;     void (*init)(void *);   /*  +8  Ptr to Init funtion           */
;;     void (*calc)(void *);   /*  +10 Ptr to calc fn                */  
;;   }FIR32;
;;
ARG_DBUFFER_PTR   .set    0
ARG_CBINDEX       .set    2
ARG_ORDER         .set    3
ARG_INPUT         .set    4
ARG_OUTPUT        .set    6
   
;;
;;=============================================================================
;;! \fn FIR_alt_init
;;! \brief Initialization function for the alternate FIR function
;;! \param FIR32_handle pointer to an FIR32 object
;;
;; This routine will zero out the dbuffer
;;
;;=============================================================================
;; 
_FIR32_alt_init:
	ADDB  	  XAR4, #2                           ; XAR4 -> dbuffer_ptr
    MOV       *+XAR4[ARG_INPUT],#0               ; input=0
    MOV       *+XAR4[ARG_OUTPUT],#0              ; output=0
              
    MOVL      XAR6,*+XAR4[ARG_DBUFFER_PTR]       ; XAR6=dbuffer_ptr
    ZAPA										 ; ACC = P = 0
    MOV       ACC,*+XAR4[ARG_ORDER] << 1         ; AL= order * 2
    ADDB	  AL, #1                             ; AL = order * 2 + 1

    RPT       AL                                 ; repeat order * 2 + 2 times
 || MOV       *XAR6++,#0                         ; clear out the dbuffer elements
    
    LRETR
    
;;
;;=============================================================================
;;! \fn FIR_alt_calc
;;! \brief Alternate FIR function
;;! \param FIR32_handle pointer to an FIR32 object
;;
;; This routine will use the LP addressing mode for circular buffer addressing
;; i.e *+XAR6[AR1%++] instead of *AR6%++, allowing for greater than 256 tap filters
;; Transfer Function :
;;                                  
;; \note The filter coefficients need to be stored in the following order for the
;; filter to work correctly i.e. (filter size is L = Order + 1)
;;
;; Index       
;;         +---------+
;;  0      | h(L-1)  |
;;  2      | h(L-2)  |
;;  4      | h(L-3)  |
;;  6      | h(L-4)  |
;;  ...    | ...     |
;;  L-3    | h(2)    |
;;  L-2    | h(1)    |
;;  L-1    | h(0)    |
;;         +---------+
;;
;; Register usage:
;; AR0       : repeat block counter (order)
;; AR1H/AR1L : buffer size-1/index pointer
;; XAR7      : coefficient pointer
;; XAR6      : delay line pointer (circular buffer)
;; 
;;=============================================================================
;; 

ConstTable: 
PosSatVal:    .long    0x00FFFFFF   ; Corresponds to >> 6 
NegSatVal:    .long    0xFF000000   ; Corresponds to >> 6 

FILTER_SIZE   .set     44

_FIR32_alt_calc:
    PUSH      XAR1                               ; Context Save
    SETC      SXM, OVM                           ; Turn on sign extension and 
                                                 ; overflow mode to saturate
    SPM       0                                  ; no scaling for the product (P) register
                                                 ; changing this to SPM 1, will shift P left by 1
                                                 ; during the accumulation giving a Q31 result
    MOVL      XAR7, *XAR4++                      ; XAR7 = coeff_ptr, XAR4 -> dbuffer_ptr
    MOVL      XAR6, *+XAR4[ARG_DBUFFER_PTR]      ; XAR6 = dbuffer_ptr
    MOV	      AH,   *+XAR4[ARG_ORDER]            ; ACC  = [order : 0]
    MOV       AR0,  AH                           ; AR0  = order (for RPT)
    LSL	      AH,   #1                           ;      = [order*2: 0] (<< 1 to get the 32-bit size)
    MOV       AL,   *+XAR4[ARG_CBINDEX]          ; ACC  = [order+1*2 : cbindex]
    MOVL      XAR1, ACC                          ; XAR1 = [order+1*2 : cbindex]
    MOVL      ACC,  *+XAR4[ARG_INPUT]            ; ACC  = input
    
    .lp_amode
    SETC      AMODE                              ; C2xLP addressing mode to allow 
                                                 ; *+XAR6[AR1%++]
    MOVL      *+XAR6[AR1%++], ACC                ; *XAR6[AR1] = input, AR1+=2
    ZAPA
    ;; <<VC140828 - debug only
    ;;.asg	  0, N
    ;;.loop
    ;;QMACL     P,*+XAR6[AR1%++],*XAR7++           ; ACC = ACC + P << PM = ACC + P << 0
    ;;                                             ; P = (signed[*+XAR6[AR1%++]] * signed[*XAR7++]) >> 32
    ;;.eval    N + 1, N                            ; increment N
    ;;.break   N = FILTER_SIZE
    ;;.endloop
    ;; VC140828>>

    RPT       AR0                                ; Repeat order/2 + 1 times
 || QMACL     P,*+XAR6[AR1%++],*XAR7++           ; ACC = ACC + P << PM = ACC + P << 0
                                                 ; P = (signed[*+XAR6[AR1%++]] * signed[*XAR7++]) >> 32
                                                 ; Let A = input(decimal) B = coeff(decimal)
                                                 ;     C = A << 31 (Q31)  D = B << 31 (Q31)
                                                 ;     P = (C * D) >> 32
                                                 ;       = (A*2^31 * B^2^31) * 2^-32
                                                 ;       = (A * B) * 2^30 -> Q30
                                                 ;   ACC = ACC + P << 0 (Q30)
    
    .c28_amode
    CLRC      AMODE                              ; Back to C28x addressing mode
    ADDL      ACC, P                             ; ACC += P
    
    MOVL      *+XAR4[ARG_OUTPUT],ACC             ; Store saturated result (Q30)
    MOV       *+XAR4[ARG_CBINDEX], AR1           ; Store AR1(index for the next sample)
    SPM       0
    POP       XAR1                               ; Restore
    CLRC      SXM, OVM                           ; Clear sign extension and saturate mode
    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
