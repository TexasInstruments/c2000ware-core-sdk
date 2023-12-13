;******************************************************************************
;******************************************************************************
; 
; FILE: rifft_64_data.asm
; 
; DESCRIPTION: Input test data for the IFFT
; 
;******************************************************************************
;
;
;  $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
;              http://www.ti.com/ ALL RIGHTS RESERVED $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;******************************************************************************
        ;.cdecls   C,LIST,"fft.h"
;############################################################################
;
;/*! \page RIFFT_64_DATA (Input test data to the IFFT)
;
; The input test data is the FFT of a two tone function. We run the ifft to 
; recover the original signal
;*/
;############################################################################

        .sect .econst
        .align  128
        .global _RIFFT16_64p_in_data,_RIFFT16_64p_out_data

; FFT input data   
_RIFFT16_64p_in_data: 
        .word   0, 0,  -8134, 1084,  -8140, -42,  -8057, -1023
        .word   -7863, -2079,  -7579, -2955,  -7230, -3796,  -6650, -4732
        .word   -6182, -5455,  -5320, -6205,  -4559, -6690,  -3574, -7420
        .word   -2621, -7682,  -1791, -7929,  -730, -8132,  127, -8184
        .word   1132, -8104,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0
        .word   0, 0,  0, 0,  0, 0,  0, 0


; FFT output data, two-tone
_RIFFT16_64p_out_data:
        .word   -619, -358,  36, 444,  736, 830,  722, 483
        .word   223, 42,  -15, 36,  133, 205,  210, 151
        .word   65, 2,  -9, 29,  86, 123,  118, 76
        .word   21, -14,  -12, 21,  62, 85,  76, 40
        .word   0, -21,  -14, 16,  48, 62,  50, 19
        .word   -11, -23,  -11, 16,  40, 46,  29, 0
        .word   -23, -27,  -10, 18,  38, 38,  18, -12
        .word   -33, -35,  -17, 8,  26, 23,  4, -21
        .word   -36, -32,  -11, 12,  23, 14,  -9, -34
        .word   -46, -37,  -15, 8,  16, 4,  -21, -44
        .word   -50, -37,  -11, 9,  11, -7,  -35, -57
        .word   -58, -39,  -10, 8,  3, -23,  -56, -77
        .word   -72, -45,  -11, 7,  -4, -38,  -77, -96
        .word   -85, -49,  -11, 3,  -20, -69,  -118, -135
        .word   -110, -55,  -6, 3,  -43, -125,  -200, -222
        .word   -175, -84,  -9, -16,  -138, -348,  -566, -683
