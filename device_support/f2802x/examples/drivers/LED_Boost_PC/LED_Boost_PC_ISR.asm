;;###########################################################################
;;
;; FILE:   f2802x_examples/LED_Boost_PC/LED_Boost_PC_ISR.asm
;;
;; TITLE:  Interrupt service routines for LED BoosterPack
;;
;;###########################################################################
;; $TI Release:  $
;; $Release Date:  $
;; $Copyright:
;// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
;//
;// Redistribution and use in source and binary forms, with or without 
;// modification, are permitted provided that the following conditions 
;// are met:
;// 
;//   Redistributions of source code must retain the above copyright 
;//   notice, this list of conditions and the following disclaimer.
;// 
;//   Redistributions in binary form must reproduce the above copyright
;//   notice, this list of conditions and the following disclaimer in the 
;//   documentation and/or other materials provided with the   
;//   distribution.
;// 
;//   Neither the name of Texas Instruments Incorporated nor the names of
;//   its contributors may be used to endorse or promote products derived
;//   from this software without specific prior written permission.
;// 
;// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;// $
;;###########################################################################

        ;Gives peripheral addresses visibility in assembly
        .cdecls   C,LIST,"DSP28x_Project.h"

        ;Include C header file - sets INCR_BUILD (used in conditional builds)
        .cdecls C,NOLIST, "LED_Boost_PC_Settings.h"

        ;Include files for the Power Library Maco's being used by the system
        .include "ADCDRV_1ch.asm"
        .include "CNTL_2P2Z.asm"
        .include "PWMDRV_DualUpDwnCnt.asm"
        .include "PWMDRV_1ch_UpDwnCnt.asm"
        
        .global _comp

;**********************************************************************************
; Declare Public functions for External Reference
;**********************************************************************************
        ; label to DP initialisation function
        .def _DPL_Init    

;**********************************************************************************
; Variable declaration
;**********************************************************************************    
; All Terminal modules initially point to the ZeroNet to ensure a known
; start state. Pad extra locations to accomodate unwanted ADC results.
        ; dummy variable for pointer initialisation
ZeroNet    .usect "ZeroNet_Section",2,1,1    ; output terminal 1

                .text
;---------------------------------------------------------
; ISR Initialisation
;---------------------------------------------------------
_DPL_Init:

; Clear the ZeroNet
    MOVL     XAR2,#ZeroNet
    RPT        #7 ; 8 times
    ||MOV    *XAR2++, #0

    ;---------------------------------------------------------
    .if(INCR_BUILD = 1) ; Open-Loop
        ADCDRV_1ch_INIT 1
        ADCDRV_1ch_INIT 2
        PWMDRV_DualUpDwnCnt_INIT 1    ; EPWM1AB
        ADCDRV_1ch_INIT 3
        PWMDRV_1ch_UpDwnCnt_INIT 2    ; EPWM2A
        ADCDRV_1ch_INIT 9
        ADCDRV_1ch_INIT 10
        ADCDRV_1ch_INIT 11
        ADCDRV_1ch_INIT 12
    .endif
    ;---------------------------------------------------------
    .if(INCR_BUILD = 2) ; Closed-Loop 2P2Z
        ; Initialize the time slicer

        ADCDRV_1ch_INIT 1
        CNTL_2P2Z_INIT 1
        ADCDRV_1ch_INIT 2
        CNTL_2P2Z_INIT 2
        PWMDRV_DualUpDwnCnt_INIT 1    ; EPWM1AB

        ADCDRV_1ch_INIT 3
        CNTL_2P2Z_INIT 3
        PWMDRV_1ch_UpDwnCnt_INIT 2    ; EPWM2A

        ADCDRV_1ch_INIT 9
        ADCDRV_1ch_INIT 10
        ADCDRV_1ch_INIT 11
        ADCDRV_1ch_INIT 12
    .endif
    ;---------------------------------------------------------
    .if(INCR_BUILD = 3) ; Closed-Loop PID
    .endif
    ;---------------------------------------------------------

    LRETR

        .sect "ramfuncs"
        ; label to DP ISR Run function
        .def    _DPL_ISR

;---------------------------------------------------------
; ISR Run
;---------------------------------------------------------
_DPL_ISR:    ;(13 cycles to get to here from ISR trigger)
    ;CONTEXT_SAVE
    ASP
    PUSH AR1H:AR0H ; 32-bit
    PUSH XAR2 ; 32-bit
    PUSH XAR3 ; 32-bit
    PUSH XAR4 ; 32-bit
;-- Comment these to save cycles --------
    PUSH XAR5 ; 32-bit
    PUSH XAR6 ; 32-bit
    PUSH XAR7 ; 32-bit
;----------------------------------------
    PUSH XT      ; 32-bit
;    SPM       0                          ; set C28 mode
;    CLRC      AMODE       
;    CLRC      PAGE0,OVM 
    NOP        

    ;---------------------------------------------------------
    .if(INCR_BUILD = 1) ; Open-Loop
        ADCDRV_1ch 1
        ADCDRV_1ch 2
        PWMDRV_DualUpDwnCnt 1

        ADCDRV_1ch 3
        PWMDRV_1ch_UpDwnCnt 2

    .endif
    ;---------------------------------------------------------
    .if(INCR_BUILD = 2) ; Closed-Loop 2P2Z

        ADCDRV_1ch 1
        ADCDRV_1ch 2
        ADCDRV_1ch 3
        
        LCR #_comp
        
        CNTL_2P2Z 1
        CNTL_2P2Z 2
        PWMDRV_DualUpDwnCnt 1

        CNTL_2P2Z 3
        PWMDRV_1ch_UpDwnCnt 2

        ADCDRV_1ch 9
        ADCDRV_1ch 10
        ADCDRV_1ch 11
        ADCDRV_1ch 12
    .endif
    ;---------------------------------------------------------
    .if(INCR_BUILD = 3) ; Closed-Loop PID
    .endif
    ;---------------------------------------------------------

;===================================
EXIT_ISR
;===================================
; Interrupt management before exit
    MOVW     DP,#_EPwm1Regs.ETCLR
    MOV     @_EPwm1Regs.ETCLR,#0x01            ; Clear EPWM1 Int flag
    MOVW     DP,#_PieCtrlRegs.PIEACK            
    MOV     @_PieCtrlRegs.PIEACK, #0x4        ; Acknowledge PIE interrupt Group 3

; Restore context & return
    POP XT
;-- Comment these to save cycles ---
    POP XAR7
    POP XAR6
    POP XAR5
;-----------------------------------
    POP XAR4
    POP XAR3
    POP XAR2
    POP AR1H:AR0H
    NASP
    IRET

