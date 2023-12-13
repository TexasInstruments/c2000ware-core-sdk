;;#############################################################################
;;! \file source/fft/RFFT_adc_f32_win.asm
;;!
;;! \brief  Real FFT (ADC input) Windowing Function
;;! \author Vishal Coelho
;;! \date   Sep 30, 2016
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
     .asg         RFFT_adc_f32_win, _RFFT_adc_f32_win
     .endif
        
     .global      _RFFT_adc_f32_win
;;
;;=============================================================================
;;! \fn RFFT_adc_f32_win
;;! \brief Real FFT (ADC input) Windowing Function
;;! \param pBuffer (XAR4), pointer to the ADC buffer that needs to be windowed
;;! \param pWindow (XAR5), pointer to the windowing table
;;! \param size    (AL),   size of the buffer (size of the RFFT)
;;
;; This function windows a 2N-point real valued data sequence stored as an 
;; N point complex sequence in the location pointed to by "pBuffer". It is to
;; be used with the real FFT module
;;
;; A 2N-pt real FFT is carried out by first doing an N point complex FFT 
;; followed by post processing (unwrapping) to get the correct answer. The 
;; windows are of size N (they are symmetrical).
;;
;; This routine will apply the window in two steps
;;
;; Step 1: Forward walk through win
;;    Loop for i = 0 to N - 1 {
;;      p -> pBuffer,  q -> win
;;      a = *p (u16) , b = *q (u16)
;;      c = *(p+1) (u16), d = *(q+1)(u16)
;;        temp1 = (A x B)>>16 (u16)
;;        temp2 = (C x D)>>16 (u16)
;;      *p   = temp1 , *(p+1) = temp2
;;      p    = p + 1 
;;      q    = q + 1
;;     }
;;
;; Step 2: Backward walk through win
;;    Loop for i = N to 2N - 1 {
;;      p -> pBuffer(from the last step),  q -> win(N/2)
;;      a = *p (u16) , b = *q (u16)
;;      c = *(p+1) (u16), d = *(q+1)(u16)
;;        temp1 = (A x B)>>16 (u16)
;;        temp2 = (C x D)>>16 (u16)
;;      *p   = temp1 , *(p+1) = temp2
;;      p    = p + 1 
;;      q    = q - 1
;;     }
;;
;; Register Usage
;; XAR4 -> pBuffer
;; XAR5 -> pWindow
;; AL   =  size
;; AR7  =  loop counter 1/2
;; R0H  =  window element
;; R1H  =  buffer element
;; R2H  =  window element
;; R3H  =  buffer element
;; Registers Save on Entry = 0
;;=============================================================================
;; 
    .text
_RFFT_adc_f32_win:
    .asmfunc
    CLRC    SXM                 ; Turn off sign extension
    SPM		0					; No shift of the product
    ; size -> size of RFFT i.e. 2N-point
    LSR     AL, #2              ; AL   = (size/4)
    MOVZ    AR7, AL             ; AR7  = (size/2)
    SUBB    XAR7,#1             ; AR7  = (size/2)-1

    .align  2
    RPTB    _RFFT_adc_f32_win_loop1, AR7
    MOV     T, *XAR4            ;  T   = d[i].real
    MOV     PL, *XAR5++         ;  P   = win[i++]
    MPYU    ACC, T, PL          ; ACC  = d[i].real*win[i++]
    SFR     ACC, #16            ; ACC  = d[i].real*win[i++] >> 16 
    MOV     *XAR4++, ACC        ;
    MOV     T, *XAR4            ; T    = d[i].imag
	MOV     PL, *XAR5++         ; P    = win[i++]
    MPYU    ACC, T, PL          ; ACC  = d[i].imag*win[i++]
    SFR     ACC, #16            ; ACC  = d[i].imag*win[i++] >> 16 
    MOV     *XAR4++, ACC        ;
_RFFT_adc_f32_win_loop1:                        
    ; At the end of this loop, XAR5 points to the
    ; N/2 th element of the real input
    .align    2
    RPTB    _RFFT_adc_f32_win_loop2, AR7
    MOV     T, *XAR4            ; T    = d[i].real
    MOV     PL, *--XAR5         ; P    = win[i], i--
    MPYU    ACC, T, PL          ; ACC  = d[i].real*win[i]
    SFR     ACC, #16            ; ACC  = d[i].real*win[i] >> 16 
    MOV     *XAR4++, ACC        ;
    MOV     T, *XAR4            ; T    = d[i].imag
    MOV     PL, *--XAR5         ; P    = win[i], i--
    MPYU    ACC, T, PL          ; ACC  = d[i].imag*win[i]
    SFR     ACC, #16            ; ACC  = d[i].imag*win[i] >> 16 
    MOV     *XAR4++, ACC        ;
_RFFT_adc_f32_win_loop2:
    LRETR
    .endasmfunc

;;#############################################################################
;;  End of File
;;#############################################################################
