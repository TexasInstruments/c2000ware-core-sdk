;;###########################################################################
;;
;; FILE:    IQNcosPU.asm
;;
;; TITLE:   C Callable IQ Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.4  | 17 May 2002 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNcosPU
;;===========================================================================
;;
;; C Usage:    extern long _IQNcosPU(long PU);
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC = Per Unit in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4, XAR0
;;             XT, P
;;
;; On Exit:    ACC = cos(PU) result in IQ format
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The "cos" value is calculated as follows:
;;
;;             1) The offset into a 512 word sin/cos table is calculated:
;;
;;                 k = 0x1FF & (int(PU*512))
;;                 
;;
;;             2) The fractional component between table samples is
;;                calculated:
;;
;;                 x = fract(PU*512) * (2*pi)/512
;;
;;             3) The output sine value is calculated as follows:
;;
;;                 cos(Radian) = C(k) + x*(-S(k) + x*(-0.5*C(k) + 0.166*x*S(k)))
;;
;;                 where  S(k) = Sin table value at offset "k"
;;                        C(k) = Cos table value at offset "k"
;;
;;             Using the above method, with a 512x32 full wave sin/cos table,
;;             will give an accuracy of approximately 29 bits.
;;
;;---------------------------------------------------------------------------
;; Benchmark:
;; 
;; Assumptions:  * Code executes from 0-wait SARAM block.
;;               * _IQsin/cosTable located in seperate SARAM or ROM block.
;;
;; Cycles = 37  (      Q == 30, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 38  (29 >= Q >= 26, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 37  (25 >= Q >= 14, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 38  (13 >= Q >= 0,  tables in 0-wait SARAM, includes LCR/LRETR)
;;
;; Cycles = 39  (      Q == 30, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 40  (29 >= Q >= 26, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 39  (25 >= Q >= 14, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 40  (13 >= Q >= 0,  tables in 1-wait ROM,   includes LCR/LRETR)
;;
;;===========================================================================


K1      .set    02AAAh                  ; 1/6 in Q16

IQNcosPU  .macro  q_value
		MOV     *SP++,#0x3F6B			; (2*pi)/512 = 0x03243F6B (Q32)
		MOV		*SP++,#0x0324
        MOVL    XAR6,#_IQcosTable           
        MOVL    XAR7,#_IQsinTable           

        SETC	OVM						; turn overflow mode on
        ABS     ACC                     ; abs(Rad), TC = sign
        MPYB 	P,T,#0
        
        .if q_value >= 26
        ASR64   ACC:P,#16
        ASR64   ACC:P,#(q_value - 25)   ; ACC = Integer, P = fract
        .endif       
        .if (q_value <= 25) & (q_value >= 10)
        ASR64   ACC:P,#(q_value - 9)    ; ACC = Integer, P = fract
        .endif
        .if q_value <= 8
        LSL64   ACC:P,#(9 - q_value)    ; ACC = Integer, P = fract
        .endif

        AND     @AL,#0x1FF
        LSL     AL,#1
        MOVZ    AR0,@AL                 ; AR0 = Index into "sin/cos" table = k
        
        MOVL    XT,*--SP                ; XT = (2*pi)/512                (Q32)
        QMPYUL  P,XT,@P                 ; P  = x                         (Q32) 
        MOVB    ACC,#0
        MOVL    XT,@P                   ; XT = x                         (Q32)
        
        MOVL    XAR4,*+XAR6[AR0]        ; XAR4 = C(k)                    (Q30)
        MOVL    XAR5,*+XAR7[AR0]        ; XAR5 = S(k)                    (Q30)
        
        SUBL    ACC,@XAR4               ; ACC = -C(k)                    (Q30)
        ASR64   ACC:P,#1                ; ACC = -0.5*C(k)                (Q30)
        QMPYL   P,XT,@XAR5              ; P   = x*S(k)                   (Q30)
        CLRC	OVM						; Turn overflow mode off
        MPY     P,@PH,#K1               ; P   = 0.166*x*S(k)             (Q30)
        ADDL    ACC,P                   ; ACC = -0.5*C(k) + 0.166*x*S(k) (Q30)
        
        QMPYL   ACC,XT,@ACC             ; ACC = x*(-0.5*C(k) + 0.166*x*S(k))                    (Q30)
        SUBL    ACC,@XAR5               ; ACC = -S(k) + x*(-0.5*C(k) + 0.166*x*S(k))            (Q30)
        QMPYL   ACC,XT,@ACC             ; ACC = x*(-S(k) + x*(-0.5*C(k) + 0.166*x*S(k)))        (Q30)
        ADDL    ACC,@XAR4               ; ACC = C(k) + x*(-S(k) + x*(-0.5*C(k) + 0.166*x*S(k))) (Q30)           
    
        .if  (q_value <= 29) & (q_value >= 14)
        ASR64   ACC:P,#(30 - q_value)   ; Scale back to required IQ value
        .endif
        .if  q_value <= 13
        ASR64   ACC:P,#16
        ASR64   ACC:P,#(14 - q_value)   ; Scale back to required IQ value
        .endif
        LRETR
        .endm

        ;; The value "GLOBAL_Q" needs to be supplied by the assembler
        ;; using the "-dGLOBAL_Q=q_value" directive:
        .sect   "IQmath"
        .ref    _IQsinTable
        .ref    _IQcosTable
        .if GLOBAL_Q == 30
        .def    _IQ30cosPU
_IQ30cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 29
        .def    _IQ29cosPU
_IQ29cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 28      
        .def    _IQ28cosPU
_IQ28cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 27      
        .def    _IQ27cosPU
_IQ27cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 26
        .def    _IQ26cosPU
_IQ26cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 25
        .def    _IQ25cosPU
_IQ25cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 24      
        .def    _IQ24cosPU
_IQ24cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 23
        .def    _IQ23cosPU
_IQ23cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 22
        .def    _IQ22cosPU
_IQ22cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 21
        .def    _IQ21cosPU
_IQ21cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 20      
        .def    _IQ20cosPU
_IQ20cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 19
        .def    _IQ19cosPU
_IQ19cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 18
        .def    _IQ18cosPU
_IQ18cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 17
        .def    _IQ17cosPU
_IQ17cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 16
        .def    _IQ16cosPU
_IQ16cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 15
        .def    _IQ15cosPU
_IQ15cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 14
        .def    _IQ14cosPU
_IQ14cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 13
        .def    _IQ13cosPU
_IQ13cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 12
        .def    _IQ12cosPU
_IQ12cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 11
        .def    _IQ11cosPU
_IQ11cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 10
        .def    _IQ10cosPU
_IQ10cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 9
        .def    _IQ9cosPU
_IQ9cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 8
        .def    _IQ8cosPU
_IQ8cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 7       
        .def    _IQ7cosPU
_IQ7cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 6
        .def    _IQ6cosPU
_IQ6cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 5
        .def    _IQ5cosPU
_IQ5cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 4
        .def    _IQ4cosPU
_IQ4cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 3
        .def    _IQ3cosPU
_IQ3cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 2
        .def    _IQ2cosPU
_IQ2cosPU:
        IQNcosPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 1
        .def    _IQ1cosPU
_IQ1cosPU:
        IQNcosPU  GLOBAL_Q
        .endif
                    
;;###########################################################################
;; No More.
;;###########################################################################
