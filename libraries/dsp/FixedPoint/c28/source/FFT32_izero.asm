;;#############################################################################
;;! \file source/FFT32_izero.asm
;;!
;;! \brief  Zero out the imaginary part of the complex input to the FFT
;;!
;;! \date   Jan 11, 2010
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
    .asg FFT32_izero, _FFT32_izero
    .endif


    .def      _FFT32_izero

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
;;
;;=============================================================================
;; Routine Type  : C Callable        
;; Description   :
;; void FFT32_izero(CFFT32_handle) 
;; This function zeros the imaginary part of the complex input, in the case of 
;; Complex FFT modules.
;; 

           
_FFT32_izero:
; Fill the imaginary part of the samples with ZERO 
    MOVL      XAR5,*XAR4      ; XAR5=ipcbptr
    MOV       ACC,*+XAR4[4]   ; ACC=size
    SUBB      ACC,#1          ; AL=size-1
                              
    MOVL      XAR6,XAR5       ; XAR6=ipcbptr
                              
    ADDB      XAR5,#2         ; XAR5=ipcbptr+2
    ADDB      XAR6,#3         ; XAR5=ipcbptr+3
    MOVB      XAR0,#4         ; XAR0=0
                              
    NOP       *,ARP5          
    RPT       AL              
 || MOV       *0++,#0         ; Clear MSW of imaginary part
                              
    NOP       *,ARP6          
    RPT       AL              
 || MOV       *0++,#0         ; Clear LSW of imaginart part
                
    LRETR 
;;#############################################################################
;;  End of File
;;#############################################################################
