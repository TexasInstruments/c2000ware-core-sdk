;;#############################################################################
;;! \file source/iir5biq16.asm
;;!
;;! \brief  16-bit IIR filter
;;!
;;! \date   Jan 11, 2011
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
    .asg IIR5BIQ16_init, _IIR5BIQ16_init
    .asg IIR5BIQ16_calc, _IIR5BIQ16_calc
    .endif

    .def      _IIR5BIQ16_init
    .def      _IIR5BIQ16_calc

;;=============================================================================
;; Routine Type  : C Callable
;; Description   :
;; void IIR5BIQ16_calc(IIR5BIQ16_handle) 
;;
;; This routine implements the IIR filter using cascade biquad structure
;;=============================================================================
;;typedef struct { <------------ XAR4
;;   void (*init)(void *);   /*  + 0  Ptr to Init funtion           */
;;   void (*calc)(void *);   /*  + 2  Ptr to calc fn                */  
;;   int16_t *coeff_ptr;     /*  + 4  Pointer to Filter coefficient */
;;   int16_t *dbuffer_ptr;   /*  + 5  Delay buffer ptr              */
;;   uint16_t nbiq;          /*  + 6  No of biquad                  */
;;   int16_t input;          /*  + 7  Latest Input sample           */
;;   int16_t isf;            /*  + 8  Input Scale Factor            */ 
;;   uint16_t qfmat;         /*  + 9  Coefficients Q Format         */
;;   int16_t output;         /*  +10  Filter Output                 */
;;}IIR5BIQ16;     
;;=============================================================================

_IIR5BIQ16_init:
    ADDB      XAR4,#6               ; XAR4->dbuffer_ptr
    MOVL      XAR6,*+XAR4[0]        ; XAR6=dbuffer_ptr
    MOV       ACC,*+XAR4[2]<<1      ; ACC=2*nbiq
    SUB       ACC,#1                ; ACC=(2*nbiq)-1
    MOVZ      AR0,AL                ; AR0=(2*nbiq)-1
    ADDL      ACC,*XAR4             ; ACC=dbuffer_ptr + (2*nbiq) - 1
    MOVL      *XAR4,ACC             ; XAR4->dbuffer_ptr, 
                                    ; dbuffer_ptr=dbuffer_ptr + (2*nbiq) - 1
                                    
    MOV       *+XAR4[3],#0          ; input=0
    MOVB      ACC,#16               
    SUB       ACC,*+XAR4[5]         
    MOV       *+XAR4[5],AL          ; qfmat=16-qfmat
    MOV       *+XAR4[6],#0          ; output=0
              
    RPT       AR0
 || MOV       *XAR6++,#0
    
    LRETR

                   
_IIR5BIQ16_calc:
    SETC      SXM,OVM          
    ZAPA                            ; Zero the ACC, P registers and OVC counter
                    
    ADDB      XAR4,#4               ; XAR4->coeff_ptr
    MOVL      XAR7,*XAR4++          ; XAR4->dbuffer_ptr, XAR7=coeff_ptr->a21
    MOVL      XAR6,*XAR4++          ; XAR4->order, XAR6=dbuffer_ptr->d1(n-2)  
    MOVZ      AR0,*XAR4++           ; XAR4->input, AR0=nbiq
                    
    MOV       T,*XAR4++             ; XAR4->isf, T=input
    MPY       ACC,T,*XAR4++         ; XAR4->qfmat, ACC=input*isf
    ADDB      XAR6,#1       
    SUBB      XAR0,#1               ; AR0=nbiq-1
                                      
; kth Biquad Computation, where k=1:nbiq
biqd:       
    MOV       T,*--XAR6             ; T=dk(n-2)
    MPY       P,T,*XAR7++           ; P= dk(n-2)*a2k
    MOV       T,*--XAR6             ; T=dk(n-1)
    MPYA      P,T,*XAR7++           ; ACC=input*isf + dk(n-2)*a2k
                                    ; P=dk(n-1)*a1k
                        
    MOV       T,*+XAR6[1]           ; T=dk(n-2)
    MPYA      P,T,*XAR7++           ; ACC=input*isf + dk(n-2)*a2k + dk(n-1)*a1k
                                    ; P=dk(n-2)*b2k
                    
    MOV       T,*XAR4               ; T=qfmat
    LSLL      ACC,T                 ; ACC=input*isf + dk(n-2)*a2k + dk(n-1)*a1k (Q15)
                                
    MOVZ      AR5,AH                ; AR5=dk(n)=input*isf + dk(n-2)*a2k + dk(n-1)*a1k (Q15)
                    
    MOV       ACC,#0                ; ACC=0 
    MOVAD     T,*XAR6               ; T=dk(n-1), dk(n-2)=dk(n-1), ACC=dk(n-2)*b2k
    MPY       P,T,*XAR7++           ; P=dk(n-1)*b1k, 
    MOV       T,AR5                 ; T=dk(n)
    MPYA      P,T,*XAR7++           ; ACC=dk(n-1)*b1k + dk(n-2)*b2k, P=dk(n)*b0k
    ADDL      ACC,P     
    MOV       *XAR6,T               ; dk(n-1)=dk(n)
    BANZ      biqd,AR0--        
                    
    MOV       T,*XAR4++             ; T=qfmat, XAR4->output
    LSLL      ACC,T     
    ROR       ACC       
    MOV       *XAR4,AH              ; output=Filtered Output in Q14 format 
    CLRC      OVM       
    LRETR                           ; !!!Do not shift it left to store in Q15 format
                                    ; If you do so, and if the output is >1, then it will
                                    ; become negative..instead of the most desirable Saturation
    
;;#############################################################################
;;  End of File
;;#############################################################################
