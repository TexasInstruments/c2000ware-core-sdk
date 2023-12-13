;;#############################################################################
;;! \file source/RFFT32_split.asm
;;!
;;! \brief  Split function for the Real FFT
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
      .if __TI_EABI__
      .asg RFFT32_split, _RFFT32_split
       .endif


    .def _RFFT32_split
;; Module Structure
;; typedef struct { <------------- XAR4
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
;;     void (*calc)(void *);  /* +16 Pointer to the calculation ()        */
;;     void (*split)(void *); /* +18 Pointer to the split(0               */
;;     void (*mag)(void *);   /* +20 Pointer to the magnitude ()          */
;;     void (*win)(void *);   /* +22 Pointer to the windowing ()          */
;; }RFFT32;
;;============================================================================== 
;; Routine Type  : C Callable  
;; Description   :
;; void RFFT32_split(RFFT32_Handle handle)
;; 
;; This function performs split operation to obtain 65 spectral bins of
;; 128-point real valued sequence from the 64-point complex FFT output
;===============================================================================
; Computation Buffer  for k=1:(N/2)-1) & N=64
;==============================================================================         
;
; Non Bitrev I/P    COMPLEX FFT(N) O/P    E/O SEPERATION                Final FFT output
; ___________       ______________        ____________                  ___________
; |__g(0)____|      |__R(0)______|        |___RP(0)__| =R(0)            |__GR(0)__| = {RP(0)+IP(0)}/2
; |__g(1)____|      |__I(0)______|        |___IP(0)__| =I(0)            |__GI(0)__| = 0
; |__g(2)____|      |__R(k)______|        |___RP(k)__|                  |_________|
; |__g(3)____|      |__I(k)______|        |___IM(k)__|                  |_________|
; |__________|      |____________|        |__________|                  |_________|
; |__________|      |____________|        |__________|                  |_________|
; |__________|      |____________|        |__________|                  |_________|
; |__________|      |__R(N/2)____|        |_RP(N/2___| =R(N/2)          |_GR(N/2)_| =RP(N/2)/2
; |__________|      |__R(N/2)____|        |_IP(N/2)__| =I(N/2)          |_GI(N/2)_| =-IP(N/2)/2
; |__________|      |____________|        |__________|                  |_________|
; |__________|      |____________|        |__________|                  |_________|
; |__________|      |____________|        |__________|                  |_________|
; |__________|      |____________|        |__________|                  |_________|
; |__________|      |___R(N-k)___|        |___RM(k)__|                  |_GR(N-1)_|
; |_g(2*N-1)_|      |___I(N-k)___|        |___IP(k)__|                  |_GI(N-1)_|
;                                                                       |__GR(N)__|={RP(0)-IP(0)}/2
;                                                                       |__GI(N)__|=0
;
;===========================================================================
;                      Note:   IM(0)=RM(0)=0
;                              RM(N/2)=IM(N/2)=0                            
;===========================================================================
; EVEN/ODD FFT SEPERATION
;===========================================================================
; RP(K) = [R(K) +  R(N-k)]/2
; RM(K) = [R(K) -  R(N-K)]/2
; IP(K) = [I(K) + I(N-K)]/2 
; IM(K) = [I(K) - I(N-K)]/2    K=1:N/2
;=========================================================================
; EVEN/ODD FFT MERGE
;========================================================================= 
; GR(K)={RP(K) - WI(K)*RM(K) + WR(K)*IP(K)}/2
; GI(K)={IM(K) - WI(K)*IP(K) - WR(K)*RM(K)}/2
; GR(N-K)={RP(K) + WI(K)*RM(K) - WR(K)*IP(K)}/2
; GI(N-K)={-IM(K) - WI(K)*IP(K) - WR(K)*RM(K)}/2 
; 
; WR(k) <-- Cosine table (AR5)
; WI(K) <-- Sine table   (AR2)     
;======================================================================                       
                    
_RFFT32_split:
    PUSH    XAR1            ; Context Save
    PUSH    XAR2
    PUSH    XAR3 
   
    SETC    SXM
    SPM     -1

    MOV     ACC,*+XAR4[4]<<2; ACC=4*size
    MOVL    XAR2,*XAR4      ; XAR2=ipcbptr ----->R(0)
    ADDL    ACC,*XAR4       ; XAR3=ipcbptr+4*size
    MOVL    XAR3,ACC        ; XAR3 ------>GR(N)

    MOVL    XAR5,*+XAR4[2]  ; XAR5=tfptr -----> WI
    MOVL    XAR6,*+XAR4[2]  ; XAR6=tfptr    
    
    MOV     T,*XAR4         ; T=size

    MOV     ACC,*+XAR4[4]<<15  ; AH=size/2
    MOVZ    AR7,AH          ; XAR7=size/2
    SUBB    XAR7,#2         ; XAR7=(size/2)-2
    ADDB    XAR4,#13        
    MOV     T,*XAR4         ; T=ratio
    MOVZ    AR0,*XAR4       ; AR0=ratio
    SUBB    XAR4,#13        
    MPY     ACC,T,AH        ; ACC=ratio*size/2
    ADDL    ACC,*+XAR4[2]   ; 
    MOVL    XAR6,ACC        ; WRWIOST=tfptr+ratio*N/2 ----> COS(Angle)
    
    NOP     *,ARP5          ; XAR5 ----> WI SIN(Angle)--->increment
    NOP     *0++
    NOP     *,ARP6
    NOP     *0--            ; XAR6 ----> WR COS(Angle)--->decrement
        
    MOV     TL,#0
    MOV     T,#0
; DC and Nyquist Bins
    ZAPA                    ; ACC=0,P=0
    MOVL    ACC,*XAR2       ; ACC=RP(0), where RP(0)=R(0)
    SFR     ACC,#1          ; ACC=RP(0)/2
    MOVL    P,*+XAR2[2]     ; P=IP(0), where IP(0)=I(0)
    SUBL    ACC,P<<PM       ; ACC={RP(0)-IP(0)}/2 in Q31
    MOVL    *XAR3++,ACC     ; GR(N)={RP(0)-IP(0)}/2 in Q31
    MOVL    *XAR3++,XT      ; GI(N)=0
    SUBB    XAR3,#8         ; XAR3->R(N-K)

    ADDL    ACC,P           ; ACC={RP(0)+IP(0)}/2 in Q31
    MOVL    *XAR2++,ACC     ; GR(0)={RP(0)+IP(0)}/2
    MOVL    *XAR2++,XT      ; XAR2->R(k), GI(0)=IM(0)-RM(0), Where IM(0)=RM(0)=0            
    
; Rest of bins                              
nextbin:                            ; XAR2->R(k), Where k=1:N/2-1 
    MOVL    ACC,*XAR2       ; ACC=R(k)
    SFR     ACC,#1          ; ACC=R(k)/2
    MOVL    P,*XAR3         ; P=R(N-k)
    SUBL    ACC,P<<PM       ; ACC={R(k)-R(N-k)}/2
    
    MOVL    *XAR3,ACC       ; R(k)=RM(k)={R(k)-R(N-k)}/2
    ADDL    ACC,P           ; ACC={R(k)+R(N-k)}/2
    MOVL    *XAR2,ACC       ; R(N-k)=RP(k)={R(k)+R(N-k)}/2
    
    MOVL    ACC,*+XAR2[2]   ; ACC=I(k)
    SFR     ACC,#1          ; ACC=I(k)/2
    MOVL    P,*+XAR3[2]     ; P=I(N-k)
    SUBL    ACC,P<<PM       ; ACC={I(k)-I(N-k)}/2
    
    MOVL    *+XAR2[2],ACC   ; I(k)=IM(k)={I(k)-I(N-k)}/2
    ADDL    ACC,P           ; ACC={I(k)+I(N-k)}/2
    MOVL    *+XAR3[2],ACC   ; I(N-k)=IP(k)={I(k)+I(N-k)}/2
    
    MOVL    XT,*XAR5        ; XT=WI(k)
    NOP     *0++
    QMPYL   ACC,XT,*+XAR3[2]; ACC=WI(k)*IP(k)
    QMPYL   P,XT,*XAR3      ; P=WI(k)*RM(k)
    MOVL    XAR1,ACC        ; XAR1=WI(k)*IP(k)

    MOVL    XT,*XAR6        ; XT=WR(k)
    NOP     *0--
    QMPYL   ACC,XT,*+XAR3[2]; P=WR(k)*IP(k)
    SUBL    ACC,P           ; ACC=WR(k)*IP(k)-WI(k)*RM(k)
    
    .if(TF_QFMAT==Q30)
    LSL     ACC,#1          
    .endif

    MOVL    P,*XAR2         ; P=RP(k)
    ADDL    ACC,P<<PM       ; ACC=RP(k)+WR(k)*IP(k)-WI(k)*RM(k) in Q30
    MOVL    *XAR2++,ACC     ; GR(k)={RP(k)+WR(k)*IP(k)-WI(k)*RM(k)}/2 in Q31
    NEG     ACC             ;
    ADDL    ACC,P           ; ACC=GR(N-k)=RP(k)-WR(k)*IP(k)+WI(k)*RM(k) in Q30
    QMPYL   P,XT,*XAR3      ; P=WR(k)*RM(k)         
    MOVL    *XAR3,ACC       ; ACC=GR(N-k)={RP(k)-WR(k)*IP(k)+WI(k)*RM(k)}/2 in Q31
    
    MOVL    ACC,XAR1        ; ACC=WI(k)*IP(k)
    NEG     ACC             ; ACC=-WI(k)*IP(k)
    SUBL    ACC,P           ; ACC=-WI(k)*IP(k)-WR(k)*RM(k)

    .if(TF_QFMAT==Q30)
    LSL     ACC,#1          ; ACC=(QI*WR-QR*WI) (Q30)
    .endif

    MOVL    P,*XAR2         ; P=IM(k)
    ADDL    ACC,P<<PM       ; ACC=IM(K)-WI(k)*IP(k)-WR(k)*RM(k) in Q30
    MOVL    *XAR2++,ACC     ; GI(k)={IM(k)-WI(k)*IP(k)-WR(k)*RM(k)}/2 in Q31
    SUBL    ACC,P           ; ACC=-IM(K)-WI(k)*IP(k)-WR(k)*RM(k) in Q30
    MOVL    *+XAR3[2],ACC   ; GI(N-k)={-IM(k)-WI(k)*IP(k)-WR(k)*RM(k)}/2 in Q31
    SUBB    XAR3,#4         
    BANZ    nextbin,AR7--   
    
    MOVL    ACC,*XAR2       ; ACC=R(N/2)
    SFR     ACC,#1          ; ACC=R(N/2)/2
    MOVL    *XAR2,ACC       ; GR(N/2)=R(N/2)/2

    MOVL    ACC,*+XAR2[2]   ; ACC=I(N/2)
    NEG     ACC             ; ACC=-I(N/2)
    SFR     ACC,#1          ; ACC=-I(N/2)/2
    MOVL    *+XAR2[2],ACC   ; GI(N/2)=-I(N/2)/2         

    SPM     0               
    POP     XAR3            ; Context Restore
    POP     XAR2
    POP     XAR1 
    LRETR
;;#############################################################################
;;  End of File
;;#############################################################################
