;;#############################################################################
;;! \file source/FFT32_calc.asm
;;!
;;! \brief  Complex FFT (radix-2 DIT) Calculation Function
;;!
;;! \date   Feb 26, 2002
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
    .include "sel_q.asm"
;;*****************************************************************************
;; globals
;;*****************************************************************************
    ; Module definition for external reference
    .if __TI_EABI__
    .asg FFT32_calc, _FFT32_calc
    .endif

    .def      _FFT32_calc

;; Module Structure
;; typedef struct { <--------- XAR4
;;     int32_t *ipcbptr;      /* +0  Pointer to input buffer              */
;;     int32_t *tfptr         /* +2  Pointer to twiddle factors           */
;;     int16_t size;          /* +4  Size of the FFT                      */
;;     int16_t nrstage;       /* +5  Number of FFT stages (log2(size))    */
;;     int16_t *magptr;       /* +6  Pointer to the magnitude buffer      */
;;     int16_t *winptr;       /* +8  Pointer to the sampling window       */
;;     int16_t peakmag;       /* +10 Peak magnitude value                 */
;;     int16_t peakfrq;       /* +11 Peak Frequency                       */
;;     int16_t ratio;         /* +12 Twiddles Skip factor                 */
;;     void (*init)(void);    /* +14 Pointer to the initialization ()     */
;;     void (*izero)(void *); /* +16 Pointer to the zero-out imaginary () */
;;     void (*calc)(void *);  /* +18 Pointer to the calculation ()        */
;;     void (*mag)(void *);   /* +20 Pointer to the magnitude ()          */
;;     void (*win)(void *);   /* +22 Pointer to the windowing ()          */
;;}CFFT32;
;;=============================================================================
;; Routine Type  : C Callable  
;; Description   :
;; void FFT32_calc(FFT32_handle) 
;; This function implements complex FFT using radix-2 DIT algo
;;
COS45K_LSW      .set    799Bh
COS45K_MSW      .set    5A82h
;===============================================================================
; FFT - Computation Routine  (FFT128R_calc)
;===============================================================================
;   * This routine takes the 128 point complex data sequence, in bit reversed form  
;   * It implements Decimation in time FFT algorithm
;   * Performs inplace computation
;   * Output in-order data "IPCB"----> Xr(0),Xi(0),Xr(1),Xi(1)...Xr(127)&Xi(127)
;===============================================================================            
;----------------------------------------------------
; MACRO 'ZEROI'     
; Number of WORDS/Number of Cycles 12
; USAGE: Called if the TWIDDLE FACTOR: 1
; 
; P=PR+jPI, Q=QR+jQI, W=WR-jWI
; P'=P+W*Q and Q'=P-W*Q
;
; POINTERS AT ENTRY
; AR6->(PR,PI,PR+1,PI+1,PR+2,PI+2,....)
; AR2->(QR,QI,QR+1,QI+1,QR+2,QR+2,....)
; COMPUTATION PERFORMED: INPLACE COMPUTATION
; AR6   ->      PR'=(PR+QR)/2 
; AR2   ->      QR'=(PR-QR)/2
; AR6+1 ->      PI'=(PI+QI)/2
; AR2+1 ->      QI'=(PI-QI)/2
; PR and PR', PI and PI', QR and QR', QI and QI' are
; stored in the same locations
; POINTERS AT EXIT
; AR6->(PR+1,PI+1,....) 
; AR2->(QR+1,QI+1,....)
;------------------------------------------------------
;                                                   (Content of REG after exec.)
ZEROI   .macro                      ;                   AR6     AR2              
    MOVL      ACC,*XAR6             ; ACC:=PR           PR      QR  
    SFR       ACC,#1                ; ACC:=PR/2         PR      QR
    MOVL      P,*XAR2               ; P=QR              PR      QR
    ADDL      ACC,P<<PM             ; ACC=PR+QR/2       PR      QR
    MOVL      *XAR6++,ACC           ; PR':=(PR+QR)/2    PI      QR  
    SUBL      ACC,P                 ; ACC:=(PR-QR)/2    PI      QR  
    MOVL      *XAR2++,ACC           ; QR':=(PR-QR)/2    PI      QI  
                                    
    MOVL      ACC,*XAR6             ; ACC:=PI           PI      QI  
    SFR       ACC,#1                ; ACC:=PI/2         PI      QI
    MOVL      P,*XAR2               ; P=QI              PI      QI
    ADDL      ACC,P<<PM             ; ACC:=(PI+QI)/2    PI      QI 
    MOVL      *XAR6++,ACC           ; PI':=(PI+QI)/2    PR+1    QI  
    SUBL      ACC,P                 ; ACC:=(PI-QI)/2    PR+1    QI  
    MOVL      *XAR2++,ACC           ; QR':=(PI-QI)/2    PR+1    QR+1     
    .endm

;----------------------------------------------------
; MACRO 'PBY2I'     
; Number of WORDS/Number of Cycles 12
; USAGE: Called if the TWIDDLE FACTOR: -j 
; 
; P=PR+jPI, Q=QR+jQI, W=WR-jWI
; P'=P+W*Q and Q'=P-W*Q
;
; POINTERS AT ENTRY
; AR6->(PR,PI,PR+1,PI+1,PR+2,PI+2,....)
; AR2->(QR,QI,QR+1,QI+1,QR+2,QR+2,....)
; COMPUTATION PERFORMED: INPLACE COMPUTATION
; AR6   ->      PR'=(PR+QI)/2 
; AR2   ->      QR'=(PR-QI)/2
; AR6+1 ->      PI'=(PI-QR)/2
; AR2+1 ->      QI'=(PI+QR)/2
; PR and PR', PI and PI', QR and QR', QI and QI' are
; stored in the same locations 
; POINTERS AT EXIT
; AR6->(PR+1,PI+1,....) 
; AR2->(QR+1,QI+1,....)
;------------------------------------------------------         
;                                                   (Content of REG after exec.)
PBY2I   .macro                      ;                   AR6     AR2  
    MOVL      XAR5,*XAR2++          ; XAR5=QR           PR      QI
    MOVL      ACC,*XAR6             ; ACC:=PR           PR      QI
    SFR       ACC,#1                ; ACC:=PR/2         PR      QI
    MOVL      P,*XAR2               ; P:=QI             PR      QI
    ADDL      ACC,P<<PM             ; ACC:=(PR+QI)/2    PR      QI  
    MOVL      *XAR6++,ACC           ; PR':=(PR+QI)/2    PI      QI     
    SUBL      ACC,P                 ; ACC:=(PR-QI)/2    PI      QI     
    MOVL      *--XAR2,ACC           ; QR':=(PR-QI)/2    PI      QR
    ADDB      XAR2,#2               ;                   PI      QI
                                    
    MOVL      ACC,*XAR6             ; ACC:=PI           PI      QI
    SFR       ACC,#1                ; ACC:=PI/2         PI      QI
    MOVL      P,XAR5                ; P=QR              PI      QI
    SUBL      ACC,P<<PM             ; ACC=(PI-QR)/2     PI      QI
    MOVL      *XAR6++,ACC           ; ACC:=(PI-QR)/2    PR+1    QI    
    ADDL      ACC,P                 ; ACC:=(PI+QR)/2    PR+1    QI 
    MOVL      *XAR2++,ACC           ; QI':=(PI+QR)/2    PR+1    QR+1
                      
    .endm  

;----------------------------------------------------
; MACRO 'PBY4I'          SPM set to 1bit right shift, XT=w
; Number of WORDS/Number of Cycles 16
; USAGE: Called if the TWIDDLE FACTOR: COS(45)-jSIN(45)=0.707-j0.707 
; 
; P=PR+jPI, Q=QR+jQI, W=WR-jWI
; P'=P+W*Q and Q'=P-W*Q
;
; POINTERS AT ENTRY
; TREG=W=|SIN(45)|=|COS(45)|=05a82h
; AR6->(PR,PI,PR+1,PI+1,PR+2,PI+2,....)
; AR2->(QR,QI,QR+1,QI+1,QR+2,QR+2,....)
; CALCULATION PERFORMED: INPLACE COMPUTATION
; AR6   ->      PR'=(PR+QI*W+QR*W)/2  
; AR2   ->      QR'=(PR-QI*W-QR*W)/2
; AR6+1 ->      PI'=(PI+QI*W-QR*W)/2
; AR2+1 ->      QI'=(PI-QI*W+QR*W)/2
; PR and PR', PI and PI', QR and QR', QI and QI' are
; stored in the same locations
; POINTERS AT EXIT
; AR6->(PR+1,PI+1,....) 
; AR2->(QR+1,QI+1,....)
;------------------------------------------------------         
;                                                           (Content of REG after exec.)
PBY4I   .macro                      ;                       PREG    AR6  AR2         
                                    ;                       -       PR   QR 
    MOVL      ACC,*XAR6             ; ACC=PR                -       PR   QR  
    SFR       ACC,#1                ; ACC=PR/2              -       PR   QR  
    QMPYL     P,XT,*XAR2            ; PREG=W*QR/2           W*QR/2  PR   QR  
    SUBL      ACC,P                 ; ACC=(PR-W*QR)/2       W*QR/2  PR   QR
    MOVL      XAR5,P                ; XAR5=W*QR/2
    QMPYL     P,XT,*+XAR2[2]        ; ACC=(PR-W*QR)/2       W*QI/2  PR   QR
    SUBL      ACC,P                 ; ACC=(PR-W*QI-W*QR)/2  W*QI/2  PR   QR 
    MOVL      *XAR2++,ACC           ; QR'=(PR-W*QI-W*QR)/2  W*QI/2  PR   QI
    NEG       ACC                   ; ACC=-(PR-W*QI-W*QR)/2 W*QI/2  PR   QI
    ADDL      *XAR6++,ACC           ; PR'=(PR+W*QI+W*QR)/2  W*QI/2  PI   QI
                                    
    MOVL      ACC,*XAR6             ; ACC=PI                W*QI/2  PI   QI
    SFR       ACC,#1                ; ACC=PI/2              W*QI/2  PI   QI
    SUBL      ACC,P                 ; ACC=(PI-W*QI)/2       W*QI/2  PI   QI
    ADDL      ACC,XAR5              ; ACC=(PI-W*QI+W*QR)/2  W*QR/2  PI   QI
    MOVL      *XAR2++,ACC           ; QI'=(PI-W*QI+W*QR)/2  W*QR/2  PI   QR+1
    NEG       ACC                   ; ACC=-(PI-W*QI+W*QR)/2 W*QR/2  PI   QR+1
    ADDL      *XAR6++,ACC           ; PI'=(PI+W*QI-W*QR)/2  W*QR/2  PR+1 QR+1           
    .endm


;----------------------------------------------------
; MACRO 'P3BY4I'    SPM set to 1bit right shift, XT=w    
; Number of WORDS/Number of Cycles 16
; USAGE: Called if the TWIDDLE FACTOR: COS(90+45)-jSIN(90+45)=-0.707-j0.707 
; 
; P=PR+jPI, Q=QR+jQI, W=WR-jWI
; P'=P+W*Q and Q'=P-W*Q
;
; POINTERS AT ENTRY 
; TREG=W=|SIN(135)|=|COS(135)|=05a82h
; AR6->(PR,PI,PR+1,PI+1,PR+2,PI+2,....)
; AR2->(QR,QI,QR+1,QI+1,QR+2,QR+2,....)
; CALCULATION PERFORMED: INPLACE COMPUTATION
; AR6   ->      PR'=(PR+QI*W-QR*W)/2  
; AR2   ->      QR'=(PR-QI*W+QR*W)/2
; AR6+1 ->      PI'=(PI-QI*W-QR*W)/2
; AR2+1 ->      QI'=(PI+QI*W+QR*W)/2
; PR and PR', PI and PI', QR and QR', QI and QI' are
; stored in the same locations 
; POINTERS AT EXIT
; AR6->(PR+1,PI+1,....) 
; AR2->(QR+1,QI+1,....)
;------------------------------------------------------         
;                                                           (Content of REG after exec.)
P3BY4I  .macro                      ;                       AR5     PREG    AR6  AR2 
                                    ;                       -       PR   QR 
    MOVL      ACC,*XAR6             ; ACC=PR                -       PR   QR  
    SFR       ACC,#1                ; ACC=PR/2              -       PR   QR  
    QMPYL     P,XT,*XAR2            ; PREG=W*QR/2           W*QR/2  PR   QR 
    ADDL      ACC,P                 ; ACC=(PR+W*QR)/2       W*QR/2  PR   QR
    MOVL      XAR5,P                ; XAR5=W*QR/2           W*QR/2  PR   QR
    QMPYL     P,XT,*+XAR2[2]        ; ACC=(PR+W*QR)/2       W*QI/2  PR   QR
    SUBL      ACC,P                 ; ACC=(PR-W*QI+W*QR)/2  W*QI/2  PR   QR 
    MOVL      *XAR2++,ACC           ; QR'=(PR-W*QI+W*QR)/2  W*QI/2  PR   QI
    NEG       ACC                   ; ACC=-(PR-W*QI+W*QR)/2 W*QI/2  PR   QI
    ADDL      *XAR6++,ACC           ; PR'=(PR+W*QI-W*QR)/2  W*QI/2  PI   QI
                                    
    MOVL      ACC,*XAR6             ; ACC=PI                W*QI/2  PI   QI
    SFR       ACC,#1                ; ACC=PI/2              W*QI/2  PI   QI
    ADDL      ACC,P                 ; ACC=(PR+W*QI)/2       W*QI/2  PI   QI
    ADDL      ACC,XAR5              ; ACC=(PI+W*QI+W*QR)/2  W*QR/2  PI   QI
    NOP       *,ARP2                
    MOVL      *0++,ACC              ; QI'=(PI+W*QI+W*QR)/2  W*QR/2  PI   QR+1
    NEG       ACC                   ; ACC=-(PI+W*QI+W*QR)/2 W*QR/2  PI   QR+1
    ADDL      *XAR6,ACC             ; PI'=(PI-W*QI-W*QR)/2  W*QR/2  PI   QR+1
    NOP       *0++                  ;                       W*QR/2  PR+1 QR+1
    .endm  


;----------------------------------------------------
; MACRO 'BFLY'       SPM set to 1bit right shift
; Number of WORDS/Number of Cycles 21
; USAGE: General Butterfly RADIX 2 -> TWIDDLE FACTOR W=WR-jWI 
; 
; P=PR+jPI, Q=QR+jQI, W=WR-jWI
; P'=P+W*Q and Q'=P-W*Q
;
; REGISTER USED: XAR0,XAR2,XAR3,XAR4,XAR5,XAR6,ACC,XT,P 
;
; POINTERS AT ENTRY
; AR6->(PR,PI,PR+1,PI+1,PR+2,PI+2,....)
; AR2->(QR,QI,QR+1,QI+1,QR+2,QR+2,....)
; AR3-> Real Part of Twiddle Factor: WR(COSx)
; AR4-> Imaginary Part of Twiddle Factor: WI(SINx)
; AR5-> Temporary Variable
; CALCULATION PERFORMED: INPLACE COMPUTATION 
; AR6   ->      PR'=(PR+QR*WR+QI*WI)/2  
; AR2   ->      QR'=(PR-QR*WR-QI*WI)/2
; AR6+1 ->      PI'=(PI+QI*WR-QR*WI)/2
; AR2+1 ->      QI'=(PI-QI*WR+QR*WI)/2
; PR and PR', PI and PI', QR and QR', QI and QI' are
; stored in the same locations
; POINTERS AT EXIT
; AR6->(PR+1,PI+1,....) 
; AR2->(QR+1,QI+1,....)
; AR3-> Real Part of Next Twiddle Factor
; AR4-> Imaginary Part ofNext Twiddle Factor
;------------------------------------------------------            
    
BFLY    .macro  p                   ;                         XT    AR6     AR2     AR3     AR4  
                                    ;                         -     PR      QR      WR      WI 
    MOVL      XT,*XAR3              ; XT=WR                   WR    PR      QR      WR      WI
    NOP       *0++                  ;                         WR    PR      QR      WR+n    WI
    QMPYL     P,XT,*XAR2++          ; P=QR*WR                 WR    PR      QI      WR+n    WI
    QMPYL     ACC,XT,*,ARP4         ; ACC=QI*WR               WR    PR      QI      WR+n    WI
    MOVL      *-SP[TEMP],P          ; TEMP=QR*WR              WR    PR      QI      WR+n    WI
                                    
    MOVL      XT,*0++               ; XT=WI                   WR    PR      QI      WR+n    WI+n
    QMPYL     P,XT,*--XAR2          ; P=WI*QR                 WR    PR      QR      WR+n    WI+n
    SUBL      ACC,P                 ; ACC=(QI*WR-QR*WI)       WR    PR      QR      WR+n    WI+n
                                    
    .if(TF_QFMAT==Q30)              
    LSL       ACC,#1                ; ACC=(QI*WR-QR*WI) (Q30)
    .endif                          
                                    
    MOVL      XAR5,ACC              ; XAR5=(QI*WR-QR*WI) (Q30)
                                    
    QMPYL     ACC,XT,*+XAR2[2]      ; ACC=WI*QI              WR    PR      QR      WR+n    WI+n
    ADDL      ACC,*-SP[TEMP]        ; ACC=(QR*WR+QI*WI)      WR    PR      QR      WR+n    WI+n
                                    
    .if(TF_QFMAT==Q30)              
    LSL       ACC,#1                ; ACC=(QR*WR+QI*WI) in Q30
    .endif                          
                                    
    MOVL      P,*XAR6               ; P=PR                    WR    PR      QR      WR+n    WI+n
    ADDL      ACC,P<<PM             ; ACC=(PR+QR*WR+QI*WI)/2  WR    PR      QR      WR+n    WI+n
    MOVL      *XAR6++,ACC           ; PR'=(PR+QR*WR+QI*WI)/2  WR    PI      QR      WR+n    WI+n
                                    
    SUBL      P,ACC                 ; P=(PR-QR*WR-QI*WI)/2    WR    PI      QR      WR+n    WI+n
    MOVL      *XAR2++,P             ; QR'=(PR-QR*WR-QI*WI)/2  WR    PI      QI      WR+n    WI+n
                                    
    MOVL      ACC,XAR5              ; ACC=(QI*WR-QR*WI)/2     WR    PI      QI      WR+n    WI+n
    MOVL      P,*XAR6               ; P=PI                    WR    PI      QI      WR+n    WI+n
    ADDL      ACC,P<<PM             ; ACC=(PI+QI*WR-QR*WI)/2  WR    PI      QI      WR+n    WI+n
    MOVL      *XAR6++,ACC           ; (PI+QI*WR-QR*WI)/2      WR    PR+1    QI      WR+n    WI+n
                                    
    SUBL      P,ACC                 ; P=(PI-QI*WR+QR*WI)/2    WR    PR+1    QI      WR+n    WI+n
    MOVL      *XAR2++,P             ; QI'=(PI-QI*WR+QR*WI)/2  WR    PR+1    QR+1    WR+n    WI+n
    .endm
    
                                                                                                                                                
;----------------------------------------------------
; MACRO 'COMBO'  SPM set to 1bit right shift   
; Number of WORDS/Number of Cycles 33
; USAGE: RADIX 4 USED AT THE FIRST STAGE
;
; REGISTER USED: XAR0,XAR1,XAR2,XAR3,XAR4,XAR5,XAR6,ACC,XT,P 
;
; POINTERS AT ENTRY 
; AR6->(R1,I1)
; AR2->(R2,I2)
; AR3->(R3,I3)
; AR4->(R4,I4)
; AR5-> Temporary Variable
; CALCULATION PERFORMED: INPLACE COMPUTATION 
; AR6   ->      R1'=(R1+R2+R3+R4)/4
; AR2   ->      R2'=(R1-R2+I3-I4)/4
; AR3   ->      R3'=(R1+R2-R3-R4)/4
; AR4   ->      R4'=(R1-R2-I3+I4)/4
; AR6+1 ->      I1'=(I1+I2+I3+I4)/4
; AR2+1 ->      I2'=(I1-I2-R3+R4)/4
; AR3+1 ->      I3'=(I1+I2-I3-I4)/4
; AR4+1 ->      I4'=(I1-I2+R3-R4)/4
; POINTERS AT EXIT
; AR6->(R5,I5) 
; AR2->(R6,I6)
; AR3->(R7,I7) 
; AR4->(R8,I8)
;---------------------------------------------------         
;                                                           (Content of REG after exec.)                      
COMBO   .macro                      ;                       AR6 AR2 AR3 AR4  
    MOVL      ACC,*XAR3             ; ACC=R3                R1  R2  R3  R4  
    SFR       ACC,#1                ; ACC=R3/2
    MOVL      P,*XAR4               ; P=R4
    SUBL      ACC,P<<PM             ; ACC=(R3-R4)/2
    MOVL      XT,ACC                ; T=(R3-R4)/2
    ADDL      ACC,P                 ; ACC=(R3+R4)/2
    MOVL      XAR1,ACC              ; XAR1=(R3+R4)/2
                                    
    MOVL      ACC,*XAR6             ; ACC=R1               
    SFR       ACC,#1                ; ACC=R1/2
    MOVL      P,*XAR2               ; P=R2
    SUBL      ACC,P<<PM             ; ACC=R1-R2/2
    MOVL      *-SP[TEMP],ACC        ; temp=(R1-R2)/2
    ADDL      ACC,*XAR2             ; ACC=(R1+R2)/2
                                    
    SFR       ACC,#1                ; ACC=(R1+R2)/4
    MOVL      P,XAR1                ; P=(R3+R4)/2
    ADDL      ACC,P<<PM             ; ACC=(R1+R2+R3+R4)/4
    MOVL      *XAR6++,ACC           ; R1'=(R1+R2+R3+R4)/4
    SUBL      ACC,P                 ; ACC=(R1+R2-R3-R4)/4
    MOVL      *XAR3++,ACC           ; R3'=(R1+R2-R3-R4)/4
                                    
    MOVL      ACC,*XAR3             ; ACC=I3
    SFR       ACC,#1                ; ACC=I3/2
    MOVL      P,*+XAR4[2]           ; P=I4
    SUBL      ACC,P<<PM             ; ACC=(I3-I4)/2
    MOVL      XAR1,ACC              ; XAR1=(I3-I4)/2
    ADDL      ACC,P                 ; ACC=(I3+I4)/2
    MOVL      XAR5,ACC              ; XAR5=(I3+I4)/2
                                    
    MOVL      ACC,*-SP[TEMP]        ; ACC=(R1-R2)/2
    SFR       ACC,#1                ; ACC=(R1-R2)/4
    MOVL      P,XAR1                ; P=(I3-I4)/2
    ADDL      ACC,P<<PM             ; ACC=(R1-R2+I3-I4)/4
    MOVL      *XAR2++,ACC           ; R2'=(R1-R2+I3-I4)/4
    SUBL      ACC,P                 ; ACC=(R1-R2-I3+I4)/4
    MOVL      *XAR4++,ACC           ; R4'=(R1-R2-I3+I4)/4
                                    
    MOVL      ACC,*XAR6             ; ACC=I1
    SFR       ACC,#1                ; ACC=I1/2
    MOVL      P,*XAR2               ; P=I2
    SUBL      ACC,P<<PM             ; ACC=(I1-I2)/2
    MOVL      *-SP[TEMP],ACC        ; temp=(I1-I2)/2
    ADDL      ACC,P                 ; ACC=(I1+I2)/2
                                    
    SFR       ACC,#1                ; ACC=(I1+I2)/4
    MOVL      P,XAR5                ; P=(I3+I4)/2
    ADDL      ACC,P<<PM             ; ACC=(I1+I2+I3+I4)/4
    MOVL      *XAR6,ACC             ; I1'=(I1+I2+I3+I4)/4
    NOP       *0++                  
    SUBL      ACC,P                 ; ACC=(I1+I2-I3-I4)/4
    MOVL      *XAR3,ACC             ; I3'=(I1+I2-I3-I4)/4
    NOP       *0++


    MOVL      ACC,*-SP[TEMP]        ; ACC=(I1-I2)/2
    SFR       ACC,#1                ; ACC=(I1-I2)/4
    MOVL      P,XT                  ; P=(R3-R4)/2
    ADDL      ACC,P<<PM             ; ACC=ACC=(I1-I2+R3-R4)/4
    MOVL      *XAR4,ACC             ; I4'=(I1-I2+R3-R4)/4
    NOP       *0++                  
    SUBL      ACC,P                 ; ACC=(I1-I2-R3+R4)/4
    MOVL      *XAR2,ACC             ; I2'=(I1-I2-R3+R4)/4
    NOP       *0++
    .endm

            
;====================================================================
; Function Local Frame
;====================================================================
;   |_______|
;   |_______|<- Stack Pointer                           (SP) <---SP 
;   |_______|<- GLCB                                    (SP-1)
;   |_______|<- BLC  (Butterfly loop counter)           (SP-2)
;   |_______|<- GLC  (Group loop counter)               (SP-3)
;   |_______|<- SLC  (Stage loop counter)               (SP-4)
;   |_______|<- TOST (Twiddle offset, for decimation)   (SP-5)
;   |_______|<- DOST (Data offset)                      (SP-6) 
;   |_______|<- TEMP                                    (SP-7) & (SP-8)                                               
;===================================================================
FFT_LOCAL_FRAME     .set    10
GLCB                .set    1
BLC                 .set    2
GLC                 .set    3
SLC                 .set    4
TOST                .set    5
DOST                .set    6
TEMP                .set    8
WRWIOST             .set    9

             
_FFT32_calc:
    PUSH      XAR1            ; Context Save
    PUSH      XAR2
    PUSH      XAR3 
    ADDB      SP,#FFT_LOCAL_FRAME  ; Create Local Frame
                      
    SETC      SXM
    SPM       -1              ; SPM set to 1bit right shift   
                      
    MOVL      XAR7,XAR4       ; XAR7->FFT_handle             
    MOVL      XAR2,*XAR7      ; XAR2=ipcbptr
    MOVL      XAR3,XAR2       ; XAR3=ipcbptr
    MOVL      XAR4,XAR2       ; XAR4=ipcbptr
              
    MOVL      XAR6,XAR2       ; XAR6=ipcbptr 
    ADDB      XAR2,#4         ; XAR2=ipcbptr+4
    ADDB      XAR3,#8         ; XAR3=ipcbptr+8
    ADDB      XAR4,#12        ; XAR4=ipcbptr+12
    MOVB      XAR0,#14        ; XAR0=14
                                                                                                          
;-----------------------------------------------------------------
; Stage 1 & 2 - Using the RADIX 4 COMBO Macro
;-----------------------------------------------------------------
;;              +--------------------------------------+
;; InPtr OutPtr | Stages 1 & 2                         |
;;              +-----+--------------------------------+
;; XAR6-> XAR6-> R(1) | R1'  = (R1 + R2)  + (R3 + R4)  | 
;;               I(1) | I1'  = (I1 + I2)  + (I3 + I4)  | 
;;               R(2) | R2'  = (R1 - R2)  + (I3 - I4)  | 
;;               I(2) | I2'  = (I1 - I2)  - (R3 - R4)  | 
;;               R(3) | R3'  = (R1 + R2)  - (R3 + R4)  | 
;;               I(3) | I3'  = (I1 + I2)  - (I3 + I4)  | 
;;               R(4) | R4'  = (R1 - R2)  - (I3 - I4)  | 
;;               I(4) | I4'  = (I1 - I2)  + (R3 - R4)  | 
;;              +-----+--------------------------------+
;;               XAR6->R1, XAR2->R2, XAR3->R3, XAR4->R4
;;                   
;;------------------------------------------------------------------------
    MOVL      *-SP[2],XAR7    ; (SP-2)=FFT_handle
    MOV       ACC,*+XAR7[4]<<14
    SUB       ACC,#1<<14
    MOV       AR7,AH          ; Loop (N/4 - 1) times
          
STAGE1_2_LP:
    MOVL      ACC,*XAR3       ; ACC=R3                R1  R2  R3  R4  
    SFR       ACC,#1          ; ACC=R3/2
    MOVL      P,*XAR4         ; P=R4
    SUBL      ACC,P<<PM       ; ACC=(R3-R4)/2
    MOVL      XT,ACC          ; T=(R3-R4)/2
    ADDL      ACC,P           ; ACC=(R3+R4)/2
    MOVL      XAR1,ACC        ; XAR1=(R3+R4)/2
              
    MOVL      ACC,*XAR6       ; ACC=R1               
    SFR       ACC,#1          ; ACC=R1/2
    MOVL      P,*XAR2         ; P=R2
    SUBL      ACC,P<<PM       ; ACC=R1-R2/2
    MOVL      *-SP[TEMP],ACC  ; temp=(R1-R2)/2
    ADDL      ACC,*XAR2       ; ACC=(R1+R2)/2
              
    SFR       ACC,#1          ; ACC=(R1+R2)/4
    MOVL      P,XAR1          ; P=(R3+R4)/2
    ADDL      ACC,P<<PM       ; ACC=(R1+R2+R3+R4)/4
    MOVL      *XAR6++,ACC     ; R1'=(R1+R2+R3+R4)/4
    SUBL      ACC,P           ; ACC=(R1+R2-R3-R4)/4
    MOVL      *XAR3++,ACC     ; R3'=(R1+R2-R3-R4)/4
              
    MOVL      ACC,*XAR3       ; ACC=I3
    SFR       ACC,#1          ; ACC=I3/2
    MOVL      P,*+XAR4[2]     ; P=I4
    SUBL      ACC,P<<PM       ; ACC=(I3-I4)/2
    MOVL      XAR1,ACC        ; XAR1=(I3-I4)/2
    ADDL      ACC,P           ; ACC=(I3+I4)/2
    MOVL      XAR5,ACC        ; XAR5=(I3+I4)/2
              
    MOVL      ACC,*-SP[TEMP]  ; ACC=(R1-R2)/2
    SFR       ACC,#1          ; ACC=(R1-R2)/4
    MOVL      P,XAR1          ; P=(I3-I4)/2
    ADDL      ACC,P<<PM       ; ACC=(R1-R2+I3-I4)/4
    MOVL      *XAR2++,ACC     ; R2'=(R1-R2+I3-I4)/4
    SUBL      ACC,P           ; ACC=(R1-R2-I3+I4)/4
    MOVL      *XAR4++,ACC     ; R4'=(R1-R2-I3+I4)/4
              
    MOVL      ACC,*XAR6       ; ACC=I1
    SFR       ACC,#1          ; ACC=I1/2
    MOVL      P,*XAR2         ; P=I2
    SUBL      ACC,P<<PM       ; ACC=(I1-I2)/2
    MOVL      *-SP[TEMP],ACC  ; temp=(I1-I2)/2
    ADDL      ACC,P           ; ACC=(I1+I2)/2
              
    SFR       ACC,#1          ; ACC=(I1+I2)/4
    MOVL      P,XAR5          ; P=(I3+I4)/2
    ADDL      ACC,P<<PM       ; ACC=(I1+I2+I3+I4)/4
    MOVL      *XAR6,ACC       ; I1'=(I1+I2+I3+I4)/4
    NOP       *0++
    SUBL      ACC,P           ; ACC=(I1+I2-I3-I4)/4
    MOVL      *XAR3,ACC       ; I3'=(I1+I2-I3-I4)/4
    NOP       *0++
              
              
    MOVL      ACC,*-SP[TEMP]  ; ACC=(I1-I2)/2
    SFR       ACC,#1          ; ACC=(I1-I2)/4
    MOVL      P,XT            ; P=(R3-R4)/2
    ADDL      ACC,P<<PM       ; ACC=ACC=(I1-I2+R3-R4)/4
    MOVL      *XAR4,ACC       ; I4'=(I1-I2+R3-R4)/4
    NOP       *0++
    SUBL      ACC,P           ; ACC=(I1-I2-R3+R4)/4
    MOVL      *XAR2,ACC       ; I2'=(I1-I2-R3+R4)/4
    NOP       *0++
    BANZ      STAGE1_2_LP,AR7--  

;------------------------------------------------------------------
; Stage 3 - Using ZEROI, PBY4I,PBY2I,P3BY4I Macros
;------------------------------------------------------------------
    MOVL      XAR7,*-SP[2]    ; XAR7=FFT_handle
    MOVL      XAR6,*XAR7      ; XAR6=ipcbptr 
    MOVL      XAR2,*XAR7      ; XAR2=ipcbptr
    ADDB      XAR2,#16        ; XAR2=ipcbptr+16
    MOVB      XAR0,#18
              
    MOV       AL,#COS45K_LSW
    MOV       AH,#COS45K_MSW
    MOVL      XT,ACC          ; XT=COS(45) in Q31 format
              
    MOV       ACC,*+XAR7[4]<<13
    SUB       ACC,#1<<13
    MOV       AR1,AH          ; Loop (N/8 - 1) times
       
STAGE3_LP: 
;;----------------------------------------------------------------
;;  ZEROI
;;---------------------------------------------------------------- 
    MOVL      ACC,*XAR6       ; ACC:=PR           PR      QR  
    SFR       ACC,#1          ; ACC:=PR/2         PR      QR
    MOVL      P,*XAR2         ; P=QR              PR      QR
    ADDL      ACC,P<<PM       ; ACC=PR+QR/2       PR      QR
    MOVL      *XAR6++,ACC     ; PR':=(PR+QR)/2    PI      QR  
    SUBL      ACC,P           ; ACC:=(PR-QR)/2    PI      QR  
    MOVL      *XAR2++,ACC     ; QR':=(PR-QR)/2    PI      QI  
              
    MOVL      ACC,*XAR6       ; ACC:=PI           PI      QI  
    SFR       ACC,#1          ; ACC:=PI/2         PI      QI
    MOVL      P,*XAR2         ; P=QI              PI      QI
    ADDL      ACC,P<<PM       ; ACC:=(PI+QI)/2    PI      QI 
    MOVL      *XAR6++,ACC     ; PI':=(PI+QI)/2    PR+1    QI  
    SUBL      ACC,P           ; ACC:=(PI-QI)/2    PR+1    QI  
    MOVL      *XAR2++,ACC     ; QR':=(PI-QI)/2    PR+1    QR+1

;-------------------------------------------------------------------            
;   PBY4I
;-------------------------------------------------------------------
    MOVL      ACC,*XAR6       ; ACC=PR                -       PR   QR  
    SFR       ACC,#1          ; ACC=PR/2              -       PR   QR  
    QMPYL     P,XT,*XAR2      ; PREG=W*QR/2           W*QR/2  PR   QR  
    SUBL      ACC,P           ; ACC=(PR-W*QR)/2       W*QR/2  PR   QR
    MOVL      XAR5,P          ; XAR5=W*QR/2
    QMPYL     P,XT,*+XAR2[2]  ; ACC=(PR-W*QR)/2       W*QI/2  PR   QR
    SUBL      ACC,P           ; ACC=(PR-W*QI-W*QR)/2  W*QI/2  PR   QR 
    MOVL      *XAR2++,ACC     ; QR'=(PR-W*QI-W*QR)/2  W*QI/2  PR   QI
    NEG       ACC             ; ACC=-(PR-W*QI-W*QR)/2 W*QI/2  PR   QI
    ADDL      *XAR6++,ACC     ; PR'=(PR+W*QI+W*QR)/2  W*QI/2  PI   QI
              
    MOVL      ACC,*XAR6       ; ACC=PI                W*QI/2  PI   QI
    SFR       ACC,#1          ; ACC=PI/2              W*QI/2  PI   QI
    SUBL      ACC,P           ; ACC=(PI-W*QI)/2       W*QI/2  PI   QI
    ADDL      ACC,XAR5        ; ACC=(PI-W*QI+W*QR)/2  W*QR/2  PI   QI
    MOVL      *XAR2++,ACC     ; QI'=(PI-W*QI+W*QR)/2  W*QR/2  PI   QR+1
    NEG       ACC             ; ACC=-(PI-W*QI+W*QR)/2 W*QR/2  PI   QR+1
    ADDL      *XAR6++,ACC     ; PI'=(PI+W*QI-W*QR)/2  W*QR/2  PR+1 QR+1 

;------------------------------------------------------------------            
;   PBY2I
;------------------------------------------------------------------            
    MOVL      XAR5,*XAR2++    ; XAR5=QR           PR      QI
    MOVL      ACC,*XAR6       ; ACC:=PR           PR      QI
    SFR       ACC,#1          ; ACC:=PR/2         PR      QI
    MOVL      P,*XAR2         ; P:=QI             PR      QI
    ADDL      ACC,P<<PM       ; ACC:=(PR+QI)/2    PR      QI  
    MOVL      *XAR6++,ACC     ; PR':=(PR+QI)/2    PI      QI     
    SUBL      ACC,P           ; ACC:=(PR-QI)/2    PI      QI     
    MOVL      *--XAR2,ACC     ; QR':=(PR-QI)/2    PI      QR
    ADDB      XAR2,#2         ;                   PI      QI
              
    MOVL      ACC,*XAR6       ; ACC:=PI           PI      QI
    SFR       ACC,#1          ; ACC:=PI/2         PI      QI
    MOVL      P,XAR5          ; P=QR              PI      QI
    SUBL      ACC,P<<PM       ; ACC=(PI-QR)/2     PI      QI
    MOVL      *XAR6++,ACC     ; ACC:=(PI-QR)/2    PR+1    QI    
    ADDL      ACC,P           ; ACC:=(PI+QR)/2    PR+1    QI 
    MOVL      *XAR2++,ACC     ; QI':=(PI+QR)/2    PR+1    QR+1

;--------------------------------------------------------------------            
;   P3BY4I                  ; AR7 at end, Use *0+ modify
;--------------------------------------------------------------------
            
    MOVL      ACC,*XAR6       ; ACC=PR                -       PR   QR  
    SFR       ACC,#1          ; ACC=PR/2              -       PR   QR  
    QMPYL     P,XT,*XAR2      ; PREG=W*QR/2           W*QR/2  PR   QR 
    ADDL      ACC,P           ; ACC=(PR+W*QR)/2       W*QR/2  PR   QR
    MOVL      XAR5,P          ; XAR5=W*QR/2           W*QR/2  PR   QR
    QMPYL     P,XT,*+XAR2[2]  ; ACC=(PR+W*QR)/2       W*QI/2  PR   QR
    SUBL      ACC,P           ; ACC=(PR-W*QI+W*QR)/2  W*QI/2  PR   QR 
    MOVL      *XAR2++,ACC     ; QR'=(PR-W*QI+W*QR)/2  W*QI/2  PR   QI
    NEG       ACC             ; ACC=-(PR-W*QI+W*QR)/2 W*QI/2  PR   QI
    ADDL      *XAR6++,ACC     ; PR'=(PR+W*QI-W*QR)/2  W*QI/2  PI   QI
              
    MOVL      ACC,*XAR6       ; ACC=PI                W*QI/2  PI   QI
    SFR       ACC,#1          ; ACC=PI/2              W*QI/2  PI   QI
    ADDL      ACC,P           ; ACC=(PR+W*QI)/2       W*QI/2  PI   QI
    ADDL      ACC,XAR5        ; ACC=(PI+W*QI+W*QR)/2  W*QR/2  PI   QI
    NOP       *,ARP2
    MOVL      *0++,ACC        ; QI'=(PI+W*QI+W*QR)/2  W*QR/2  PI   QR+1
    NEG       ACC             ; ACC=-(PI+W*QI+W*QR)/2 W*QR/2  PI   QR+1
    ADDL      *XAR6,ACC       ; PI'=(PI-W*QI-W*QR)/2  W*QR/2  PI   QR+1
    NOP       *0++            ;                       W*QR/2  PR+1 QR+1
              
    BANZ      STAGE3_LP,AR1--
                                                                                            
;--------------------------------------------------------
; Stage 4 to LOG2(N) - Using BFLY Macro
;--------------------------------------------------------   
; Initialization
; 1. Initialize the Butterfly loop(BLC), Group loop(GLC) & Stage loop counter(SLC)
; 2. Initialize the Data offset(DOST) and twiddle factor offset (TOST)          
    MOV       ACC,*+XAR7[4]<<12 ; AH=(N/16)
    MOV       *-SP[GLCB],AH   ; GLCB=N/16
    MOV       *-SP[GLC],AH    ; GLC=N/16
    MOVB      *-SP[BLC],#8,UNC; BLC=8

; Twiddle factor offset
    LSL       ACC,#1
    MOV       T,AH            ; T=N/8
    ADDB      XAR7,#13
    MPY       ACC,T,*XAR7     ; ACC=ratio*N/8
    SUBB      XAR7,#13            
    MOV       *-SP[TOST],AL   ; TOST=ratio*N/8
              
    MOV       ACC,*+XAR7[5]   ; ACC=nrstage
    SUB       ACC,#3          ; ACC=nrstage-3
    MOV       *-SP[SLC],AL    ; SLC=nrState-3
    MOVB      *-SP[DOST],#32,UNC ; DOST=32
              
    MOV       ACC,*+XAR7[4]<<15  ; AH=N/2
    ADDB      XAR7,#13        
    MOV       T,*XAR7         ; T=ratio
    SUBB      XAR7,#13        
    MPY       ACC,T,AH        ; ACC=ratio*N/2
    ADDL      ACC,*+XAR7[2]   ; 
    MOVL      *-SP[WRWIOST],ACC  ; WRWIOST=tfptr+ratio*N/2 ----> COS(Angle)


SLP:                          ; Stage loop 
    MOVL      XAR6,*XAR7      ; XAR6=ipcbptr ----->  P          
    MOVL      ACC,*XAR7       ; ACC=ipcbptr
    ADD       ACC,*-SP[DOST]  ; ACC=ipcbptr+DOST
    MOVL      XAR2,ACC        ; XAR2->ipcbptr+DOST -----> Q
              
    MOVZ      AR0,*-SP[TOST]  ; AR0=TOST

            
GLP:                          ; Group loop
    MOVL      XAR3,*-SP[WRWIOST]
    MOVL      XAR4,*+XAR7[2]  ; XAR4=tfptr ---> SIN(Angle)
              
    MOVZ      AR1,*-SP[BLC]   ; AR1=BLC
    SUBB      XAR1,#1
BLP:
;-------------------------------------------------------------  
;   Butterfly loop
;   BFLY    7
;-------------------------------------------------------------
    BFLY      7
    BANZ      BLP,AR1--       ; Butterfly loop                      

; Operations performed between the group
; 1. Manipulating the P & Q pointer to point to the next group
; 2. Reinitializing the WI and WR twiddle factor pointer  
; 3. Decrementing the Group Count by 1, till all the group in the stage is computed
; 4. Reinitializing the Butterfly loop index for next group
                                    ; ARP=AR2
    MOVU      ACC,*-SP[DOST]  ; ACC=DOST
    ADDL      XAR6,ACC        
    ADDL      XAR2,ACC        
    DEC       *-SP[GLC]
    BF        GLP,NEQ         ; Group Loop 
  
; Operation Performed, between the stage
; 1. Multiply the data offset by 2
; 2. Divide the Group count by 2
; 3. Divide the Twiddle offset by 2
; 4. Multiply the butterfly count by 2
; 5. Decrementing the stage count by 1, till all the stage gets over
; 6. Reinitializing the P & Q data pointer to the first group of next stage         
    MOV       ACC,*-SP[DOST]<<1
    MOV       *-SP[DOST],AL   ; DOST=DOST*2
              
    MOV       ACC,*-SP[BLC]<<1
    MOV       *-SP[BLC],AL    ; BLC=BLC*2
              
    MOV       ACC,*-SP[TOST]<<15
    MOV       *-SP[TOST],AH   ; TOST=TOST/2
              
    MOV       ACC,*-SP[GLCB]<<15
    MOV       *-SP[GLCB],AH   ; GLCB=GLCB/2
    MOV       *-SP[GLC],AH    ; GLC=GLCB/2
              
    DEC       *-SP[SLC]
    BF        SLP,NEQ         ; Stage loop
               
    SPM       0               ; SPM set to 0
              
    SUBB      SP,#FFT_LOCAL_FRAME ; Clear local frame
    POP       XAR3            ; Context Restore
    POP       XAR2
    POP       XAR1 
    LRETR
;;#############################################################################
;;  End of File
;;#############################################################################
