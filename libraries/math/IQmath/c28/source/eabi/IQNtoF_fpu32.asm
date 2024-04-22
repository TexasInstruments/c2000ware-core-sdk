;;###########################################################################
;;
;; FILE:   IQNtoF_fpu32.asm
;;
;; TITLE:  C Callable IQ to Float Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.5  | 01 May 2008 | L. H  | Original Release.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNtoF
;;===========================================================================
;;
;; C Usage:    extern float _IQtoF(long A);   // no round or sat
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC    = A in IQ format
;;
;; Regs Used:  XT, P
;;
;; On Exit:    ACC    = IEEE 754 floating-point equivalent of A
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  This operation converts an IQ number to the equivalent
;;             IEEE 754 Single-Precision floating-point format. This
;;             format is shown below:
;;
;;              31  30        23 22                                 0
;;             +-----------------------------------------------------+
;;             | s |      e     |                 f                  |
;;             +-----------------------------------------------------+
;;
;;             Value = (-1)^s * 2^(e-127) * 1.f
;;
;;             where: e = 1 to 254, f = 0.000000000 to ~1.0
;;                    e = 0, f = 0, s = 0, Value = 0.0
;;                    e = 0 and f != 0 case cannot occur in IQ math
;;                    e = 255 case cannot occur in IQ math
;;
;;---------------------------------------------------------------------------
;; Benchmark:
;;
;; Cycles = 22 (includes LCR/LRETR)
;;
;;---------------------------------------------------------------------------

IQNtoF .macro   q_value
       CSB  ACC
       LSLL     ACC,T
       MOVL     P,@ACC
       XOR      @PL,#0xFFFF
       XOR      @PH,#0x7FFF
       MOVL     @P,ACC,GEQ
       MOVB     AH,#(127 + (30-q_value))
       SUBR     @T,AH
       MOVL     ACC,@P
       MOVB     @T,#0,EQ
       ASR64    ACC:P,#14
       AND      @AH,#0xFF00
       ADD      AH,@T
       LSL64    ACC:P,#7
       MOV32    R0H, ACC
       LRETR
       .endm

       ;; The value "GLOBAL_Q" needs to be supplied by the assembler
       ;; using the "-dGLOBAL_Q=q_value" directive:
       .sect    "IQmath"
       .if GLOBAL_Q == 30
       .def _IQ30toF
_IQ30toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 29
       .def _IQ29toF
_IQ29toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 28
       .def _IQ28toF
_IQ28toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 27
       .def _IQ27toF
_IQ27toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 26
       .def _IQ26toF
_IQ26toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 25
       .def _IQ25toF
_IQ25toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 24
       .def _IQ24toF
_IQ24toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 23
       .def _IQ23toF
_IQ23toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 22
       .def _IQ22toF
_IQ22toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 21
       .def _IQ21toF
_IQ21toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 20
       .def _IQ20toF
_IQ20toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 19
       .def _IQ19toF
_IQ19toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 18
       .def _IQ18toF
_IQ18toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 17
       .def _IQ17toF
_IQ17toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 16
       .def _IQ16toF
_IQ16toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 15
       .def _IQ15toF
_IQ15toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 14
       .def _IQ14toF
_IQ14toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 13
       .def _IQ13toF
_IQ13toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 12
       .def _IQ12toF
_IQ12toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 11
       .def _IQ11toF
_IQ11toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 10
       .def _IQ10toF
_IQ10toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 9
       .def _IQ9toF
_IQ9toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 8
       .def _IQ8toF
_IQ8toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 7
       .def _IQ7toF
_IQ7toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 6
       .def _IQ6toF
_IQ6toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 5
       .def _IQ5toF
_IQ5toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 4
       .def _IQ4toF
_IQ4toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 3
       .def _IQ3toF
_IQ3toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 2
       .def _IQ2toF
_IQ2toF:
       IQNtoF   GLOBAL_Q
       .endif

       .if GLOBAL_Q == 1
       .def _IQ1toF
_IQ1toF:
       IQNtoF   GLOBAL_Q
       .endif

;;###########################################################################
;; No More.
;;###########################################################################
