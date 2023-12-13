;----------------------------------------------------------------------------------
;    FILE:            PWMDRV_1ch_UpDwnCnt.asm
;
;    Description:    Single (A output) channel PWM driver macro
;
;    Version:         2.0
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
;  05/15/10    | Release 1.0          (SC)
;--------------------------------------------------------------------------------
;=============================
PWMDRV_1ch_UpDwnCnt_INIT    .macro    n
;=============================
; variable declarations
_PWMDRV_1ch_UpDwnCnt_Duty:n:        .usect "PWMDRV_1ch_UpDwnCnt_Section",2,1,1    ; input terminal
_PWMDRV_1ch_UpDwnCnt_Period:n:    .usect "PWMDRV_1ch_UpDwnCnt_Section",2,1,1    ; internal data to store PWM period value

;Publish Terminal Pointers for access from the C environment
;===========================================================
        .def     _PWMDRV_1ch_UpDwnCnt_Duty:n:
        .def     _PWMDRV_1ch_UpDwnCnt_Period:n:
                
; set terminal pointer to ZeroNet
        MOVL    XAR2, #ZeroNet
        MOVW    DP, #_PWMDRV_1ch_UpDwnCnt_Duty:n:
        MOVL    @_PWMDRV_1ch_UpDwnCnt_Duty:n:, XAR2
        
        MOVW    DP,#_EPwm:n:Regs.TBPRD
        MOVL    ACC,@_EPwm:n:Regs.TBPRD
        MOV        AL,#0
        MOVW    DP, #_PWMDRV_1ch_UpDwnCnt_Duty:n:
        MOVL    @_PWMDRV_1ch_UpDwnCnt_Period:n:,ACC 

        .endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_1ch_UpDwnCnt    .macro    n
;=============================
       MOVW     DP, #_PWMDRV_1ch_UpDwnCnt_Duty:n:                ; load DP for net pointer
       MOVL       XAR0, @_PWMDRV_1ch_UpDwnCnt_Duty:n:              ; Load net pointer address to XAR0
       MOVL        XT,@_PWMDRV_1ch_UpDwnCnt_Period:n:
     
       QMPYL     ACC,XT,*XAR0                           ; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                             
       SFR        ACC,#8                                    ; ACC>>8: AL = duty,  
      
       MOVW     DP,#_EPwm:n:Regs.CMPA
       MOV     @_EPwm:n:Regs.CMPA.half.CMPA,AL
        
       .endm

; end of file

