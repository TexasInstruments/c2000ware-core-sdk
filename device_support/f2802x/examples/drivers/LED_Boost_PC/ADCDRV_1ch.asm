;----------------------------------------------------------------------------------
;    FILE:            ADCDRV_1ch.asm
;
;    Description:    Single channel ADC Result register interface macro
;
;    Version:         3.0
;
;   Target:          F2802x / F2803x
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date          | Description
;--------------------------------------------------------------------------------
;   | Release 3.0  (MB)
;--------------------------------------------------------------------------------
;================================
ADCDRV_1ch_INIT    .macro n
;================================
_ADCDRV_1ch_Rlt:n:    .usect "ADCDRV_1ch_Section",2,1,1    ; output terminal 1

; publish Terminal Pointers for access from the C environment
        .def     _ADCDRV_1ch_Rlt:n:

        MOVL    XAR2, #ZeroNet                        ; "ZeroNet" is initialised to 0 in ISR
        MOVW    DP, #_ADCDRV_1ch_Rlt:n:>>6
        MOVL    @_ADCDRV_1ch_Rlt:n:, XAR2            ; zero output terminal pointer
        .endm

;--------------------------------------------------------------------------------
;=============================
ADCDRV_1ch        .macro    n
;=============================
         MOVW    DP, #_ADCDRV_1ch_Rlt:n:                ; Load Data Page
        MOVL    XAR0,@_ADCDRV_1ch_Rlt:n:            ; Load Rlt Data Page Pointer in XAR0
        
        MOVW     DP, #_AdcResult                     ; load Data Page to read ADC results
        MOV     ACC,@_AdcResult.ADCRESULT:n:<<12    ; read and shift the 12 bit ADC result by 12 bits to get Q24 value
       
        MOVL    *XAR0,ACC                            ; store result in output pointer location
        .endm
; end of file

