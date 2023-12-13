;;#############################################################################
;;! \file source/RFFT32_mag.asm
;;!
;;! \brief  Magnitude function for the real FFT
;;!
;;! \date   Nov 2, 2010
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
      .asg RFFT32_mag, _RFFT32_mag
       .endif

    .def      _RFFT32_mag

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
;;=============================================================================
;; Routine Type  : C Callable        
;; Description   :
;; void RFFT32_mag(RFFT32_Handle) 
;; This function computes the magnitude square of the Real FFT output. Allows in-place
;; and off-place storage of the magnitude square results. The spectrum goes from
;; DC to Nyquist frequency; the mag spectrum is symmetric about the Nyquist frequency
;; 

_RFFT32_mag:
    SETC      SXM
              
    MOVL      XAR7,*XAR4      ; XAR5=ipcbptr
    MOVL      XAR6,*+XAR4[6]  ; XAR6=magptr
              
    MOVZ      AR0,*+XAR4[4]   ; AR0=size
    
MAG_LP:     
    ZAPA                      ; ACC=0, P=0
    QMACL     P,*XAR7,*XAR7++ ; Q15*Q15=Q30
    QMACL     P,*XAR7,*XAR7++ ; Q15*Q15+Q30=Q30
    ADDL      ACC,P
    MOVL      *XAR6++,ACC     ; Store in Q30
    BANZ      MAG_LP,AR0--
            
; Find maximum magnitude
    ADDB      XAR4,#4         ; XAR4->size
    MOVB      ACC,#0
    MOVL      *+XAR4[6],ACC   ; peakmag=0
    MOVZ      AR0,*XAR4       ; AR0=size
    MOVL      XAR5,*+XAR4[2]  ; XAR5=magptr
              
    MOV       ACC,#0
            
;Find the maximum value among the FFT Magnitudes    
    RPT       AR0
 || MAXL      ACC,*XAR5++
              
    MOVL      *+XAR4[6],ACC   ; update peak magnitude
    MOVB      XAR7,#0         ; XAR7=0
    MOVL      XAR5,*+XAR4[2]  ; XAR5=magptr
;Find the spectral bin corresponding to maximum magnitude.  
NEXT_BIN:               
    MAXL      ACC,*XAR5++
    NOP       *XAR7++
    SBF       NEXT_BIN,NEQ    
              
    NOP       *--XAR7
    ADDB      XAR4,#8         ; XAR4->peakfrq
    MOV       *XAR4,AR7       ; update peak magnitude     
    LRETR      
    
;;#############################################################################
;;  End of File
;;#############################################################################
