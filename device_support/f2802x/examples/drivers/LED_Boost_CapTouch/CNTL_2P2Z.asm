;----------------------------------------------------------------------------------
;    FILE:            CNTL_2P2Z.asm
;
;    Description:    2nd Order Control Law Macro Module
;
;    Version:         3.0
;
;   Target:          F2802x / F2803x 
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date         | Description
;----------------------------------------------------------------------------------
;   | Release 3.0  (MB)
;----------------------------------------------------------------------------------
;=============================
CNTL_2P2Z_INIT    .macro n
;=============================
; allocate memory space for data & terminal pointers
_CNTL_2P2Z_Ref:n:    .usect     "CNTL_2P2Z_Section",2,1,1        ; reference input terminal
_CNTL_2P2Z_Fdbk:n:    .usect     "CNTL_2P2Z_Section",2,1,1        ; feedback input terminal
_CNTL_2P2Z_Out:n:    .usect     "CNTL_2P2Z_Section",2,1,1        ; output terminal
_CNTL_2P2Z_Coef:n:    .usect     "CNTL_2P2Z_Section",2,1,1        ; coefficients & saturation limits (14 words)
_CNTL_2P2Z_DBUFF:n:    .usect  "CNTL_2P2Z_Section",10,1,1        ; internal Data BUFF

; publish terminal pointers for access from the C environment
        .def     _CNTL_2P2Z_Ref:n:
        .def     _CNTL_2P2Z_Fdbk:n:
        .def     _CNTL_2P2Z_Out:n:
        .def     _CNTL_2P2Z_Coef:n:
        .def     _CNTL_2P2Z_DBUFF:n:

; set terminal pointers to ZeroNet
        MOVL    XAR2, #ZeroNet
        MOVW    DP, #_CNTL_2P2Z_Ref:n:
        MOVL    @_CNTL_2P2Z_Ref:n:, XAR2
        MOVW    DP, #_CNTL_2P2Z_Fdbk:n:
        MOVL    @_CNTL_2P2Z_Fdbk:n:, XAR2
        MOVW    DP, #_CNTL_2P2Z_Out:n:
        MOVL    @_CNTL_2P2Z_Out:n:, XAR2

; zero data buffer
        MOVW    DP, #_CNTL_2P2Z_DBUFF:n:
        MOVL     XAR2,#_CNTL_2P2Z_DBUFF:n:
        RPT        #9     ; 10 times
    ||    MOV     *XAR2++, #0
    
        .endm

;----------------------------------------------------------------------------------
;=============================
CNTL_2P2Z    .macro n
;=============================
; set up address pointers
        MOVW    DP, #_CNTL_2P2Z_Ref:n:
        MOVL     XAR0, @_CNTL_2P2Z_Ref:n:        ; net pointer to Ref (XAR0)
        MOVW    DP,#_CNTL_2P2Z_Fdbk:n:
        MOVL    XAR1, @_CNTL_2P2Z_Fdbk:n:        ; net pointer to Fdbk (XAR1)
        MOVW    DP,#_CNTL_2P2Z_DBUFF:n:
        MOVL    XAR4, #_CNTL_2P2Z_DBUFF:n:        ; pointer to the DBUFF array (used internally by the module)
        
; calculate error (Ref - Fdbk)
        MOVL    ACC, *XAR0                        ; ACC = Ref    (Q24) = Q(24)
        SUBL    ACC, *XAR1                        ; ACC = Ref(Q24) - Fdbk(Q24)= error(Q24)
        LSL     ACC, #6                            ; Logical left shift by 6,  Q{24}<<6 -> Q{30}
;store error in DBUFF 
        MOVL    *+XAR4[4], ACC                    ; e(n) = ACC = error Q{30}        
        
        MOVW    DP,#_CNTL_2P2Z_Out:n:
        MOVL    XAR2, @_CNTL_2P2Z_Out:n:        ; net pointer to Out (XAR2)
        MOVW    DP,#_CNTL_2P2Z_Coef:n:
        MOVL    XAR3, @_CNTL_2P2Z_Coef:n:        ; net pointer to Coef (XAR3)
        ZAPA        
; compute 2P2Z filter
        MOV        AR0,#8
        MOVL    XT, *+XAR4[AR0]                    ; XT  = e(n-2)
        QMPYL    P, XT, *XAR3++                    ; P   = e(n-2)Q30*B2{Q26} = I8Q24
        MOVDL    XT, *+XAR4[6]                    ; XT  = e(n-1), e(n-2) = e(n-1)
        QMPYAL    P, XT, *XAR3++                     ; P   = e(n-1)Q30*B1{Q26} = Q24, ACC=e(n-2)*B2
        MOVDL    XT, *+XAR4[4]                     ; XT  = e(n), e(n-1) = e(n) 
        QMPYAL    P, XT, *XAR3++                     ; P   = e(n)Q30*B0{Q26}= Q24, ACC = e(n-2)*B2 + e(n-1)*B1 
        MOVL    XT,*+XAR4[2]                    ; XT  = u(n-2)
        QMPYAL    P, XT, *XAR3++                    ; P   = u(n-2)*A2, ACC = e(n-2)*B2 + e(n-1)*B1 + e(n)*B0
        MOVDL    XT,*+XAR4[0]                     ; XT  = u(n-1), u(n-2) = u(n-1)
        QMPYAL    P, XT, *XAR3++                     ; P   = u(n-1)*A1, ACC = e(n-2)*B2 + e(n-1)*B1 + e(n)*B0 + u(n-2)*A2
        ADDL    ACC, @P                            ; ACC = e(n-2)*B2 + e(n-1)*B1 + e(n)*B0 + u(n-2)*A2 + u(n-1)*A1 

; scale u(n):Q24, saturate (max>u(n)>min0), and save history
        
        MINL    ACC, *XAR3++                     ; saturate to < max (Q24)
        MAXL    ACC, *XAR3                         ; saturate to > min (Q24)

; write controller result to output terminal (Q24)
        MOVL    *XAR2, ACC                        ; output control effort to terminal net

; Convert the u(n) to Q30 format and store in the data buffer
        LSL     ACC, #6                            ; Logical left shift by 6, Q{24}<<6 -> Q{30}
        MOVL    *XAR4, ACC                        ; u(n-1) = u(n) = ACC 

        .endm
            
; end of file

