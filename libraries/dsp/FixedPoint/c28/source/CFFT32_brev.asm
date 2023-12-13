;;#############################################################################
;;! \file source/CFFT32_brev.asm
;;!
;;! \brief  Bit Reversal routine for the complex 32-bit FFT
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
                .if __TI_EABI__
                .asg CFFT32_brev, _CFFT32_brev
                .endif

                .def _CFFT32_brev
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
;;============================================================================== 
;; \fn  void CFFT32_brev(int32_t *src, int32_t *dst, uint16_t size)
;; \brief Bit Reversal routine for the complex 32-bit FFT
;;
;; This function bit reverses the N-point real sequence stored in 
;; alternate memory locations, that is, 
;; src(0)    = x(0)    | src(1)    = 0
;; src(2)    = x(1)    | src(3)    = 0
;; ...                 | ...         
;; src(2N-2) = x(N-1)  | src(2N-1) = 0 
;; If src=dst, then in-place bit reversal is performed.
;; The destination array should be aligned to 2N long words, where N is the size
;; of the complex FFT. 
;;
;; \param src (XAR4) pointer to the source array or buffer
;; \param dst (XAR5) pointer to the destination array or buffer
;; \param size(  AL) size of the buffer (must be a power of 2)
;;============================================================================== 
;;
_CFFT32_brev:
                                   ; XAR4->src, XAR5->dst, AL=size
    MOVL      XAR0,XAR4            ; XAR0->src
    NOP       *,ARP5               
                                   
    CMPR      0                    ; TC=1, if src==dst
    BF        off_place,NTC        ; If not equal, jump to off place bit rev
                                   
; IN-PLACE BIT-REVERSAL            
in_place:                          
    MOVZ      AR7,AL               ; AR0=size
    SUBB      XAR7,#1              ; XAR7=size-1
    LSL       ACC,#1               ; ACC=2*size
    MOVZ      AR6,AL               ; AR0=2*size
                                   
next_data1:                        
    MOVL      XT,*XAR4             ; XT=*src
    MOVL      P,*XAR5              ; P=*dst
    MOVL      XAR0,XAR4            ; XAR0=src
    CMPR      2                    ; check src<dst
    BF        noswap,TC            ; if src<dst, do not swap *src & *dst
                                   
    MOVL      *XAR4,P              ; *src=*dst
    MOVL      *XAR5,XT             ; *dst=*src
                                   
noswap:                            
    ADDB      XAR4,#4              ; XAR4=src+2
    MOVZ      AR0,AR6              ; AR0=2*size
    NOP       *BR0++               ; dst=br(dst+2*size)
    BANZ      next_data1,AR7--     ; ARP=AR3, AR3->src+2, AR7=AR7-1
    LRETR                          
                                   
; OFF-PLACE BIT-REVERSAL                 
off_place:                         
    MOVZ      AR7,AL               ; AR0=size
    SUBB      XAR7,#1              ; XAR7=size-1
    LSL       ACC,#1               ; ACC=2*size
    MOVZ      AR0,AL               ; AR0=2*size
                                   
next_data2:                        
    MOVL      ACC,*XAR4++          ; XAR4=src+1, ACCL=*src
    ADDB      XAR4,#2              ; XAR4=src+2
    NOP       *,ARP5               ; ARP=XAR5
    MOVL      *BR0++,ACC           ; XAR5=br(dst+size)
    BANZ      next_data2,AR7--                 
    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
