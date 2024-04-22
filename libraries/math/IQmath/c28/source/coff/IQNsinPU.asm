;;###########################################################################
;;
;; FILE:    IQNsinPU.asm
;;
;; TITLE:   C Callable IQ Sin Per Unit Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    |  Who  | Description of changes
;; =====|=============|=======|==============================================
;; 1.4  | 17 May 2002 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################

;;===========================================================================
;; Function:   _IQNsinPU
;;===========================================================================
;;
;; C Usage:    extern long _IQNsinPU(long PU);
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC = Per Unit in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4, XAR0
;;             XT, P
;;
;; On Exit:    ACC = sin(PU) result in IQ format
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The "sinPU" value is calculated as follows:
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
;;                 sin(PU) = S(k) + x*(C(k) + x*(-0.5*S(k) - 0.166*x*C(k)))
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
;;               * _IQsin/cos Table located in seperate SARAM or ROM block.
;;
;; Cycles = 39  (      Q == 30, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 40  (29 >= Q >= 26, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 39  (25 >= Q >= 14, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 40  (13 >= Q >= 0,  tables in 0-wait SARAM, includes LCR/LRETR)
;;
;; Cycles = 41  (      Q == 30, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 42  (29 >= Q >= 26, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 41  (25 >= Q >= 14, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 42  (13 >= Q >= 0,  tables in 1-wait ROM,   includes LCR/LRETR)
;;
;;===========================================================================
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

K1      .set    02AAAh                  ; 1/6 in Q16

IQNsinPU  .macro  q_value
		MOV     *SP++,#0x3F6B			; (2*pi)/512 = 0x03243F6B       (Q32)
		MOV		*SP++,#0x0324
        MOVL    XAR6,#_IQcosTable           
        MOVL    XAR7,#_IQsinTable           

        CLRC    TC
        SETC	OVM						; turn overflow mode on
        ABSTC   ACC                     ; abs(Rad), TC = sign
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
        
        SUBL    ACC,@XAR5               ; ACC = -S(k)                    (Q30)
        ASR64   ACC:P,#1                ; ACC = -0.5*S(k)                (Q30)
        QMPYL   P,XT,@XAR4              ; P   = x*C(k)                   (Q30)
        CLRC	OVM						; Turn overflow mode off
        MPY     P,@PH,#K1               ; P   = 0.166*x*C(k)             (Q30)
        SUBL    ACC,@P                  ; ACC = -0.5*S(k) - 0.166*x*C(k) (Q30)
        
        QMPYL   ACC,XT,@ACC             ; ACC = x*(-0.5*S(k) - 0.166*x*C(k))                   (Q30)
        ADDL    ACC,@XAR4               ; ACC = C(k) + x*(-0.5*S(k) - 0.166*x*C(k))            (Q30)
        QMPYL   ACC,XT,@ACC             ; ACC = x*(C(k) + x*(-0.5*S(k) - 0.166*x*C(k)))        (Q30)
        ADDL    ACC,@XAR5               ; ACC = S(k) + x*(C(k) + x*(-0.5*S(k) - 0.166*x*C(k))) (Q30)            
        
        NEGTC   ACC                     ; Negate result if necessary
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
        .def    __IQ30sinPU
__IQ30sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 29
        .def    __IQ29sinPU
__IQ29sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 28      
        .def    __IQ28sinPU
__IQ28sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 27      
        .def    __IQ27sinPU
__IQ27sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 26
        .def    __IQ26sinPU
__IQ26sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 25
        .def    __IQ25sinPU
__IQ25sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 24      
        .def    __IQ24sinPU
__IQ24sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 23
        .def    __IQ23sinPU
__IQ23sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 22
        .def    __IQ22sinPU
__IQ22sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 21
        .def    __IQ21sinPU
__IQ21sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 20      
        .def    __IQ20sinPU
__IQ20sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 19
        .def    __IQ19sinPU
__IQ19sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 18
        .def    __IQ18sinPU
__IQ18sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 17
        .def    __IQ17sinPU
__IQ17sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 16
        .def    __IQ16sinPU
__IQ16sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 15
        .def    __IQ15sinPU
__IQ15sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 14
        .def    __IQ14sinPU
__IQ14sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 13
        .def    __IQ13sinPU
__IQ13sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 12
        .def    __IQ12sinPU
__IQ12sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 11
        .def    __IQ11sinPU
__IQ11sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 10
        .def    __IQ10sinPU
__IQ10sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 9
        .def    __IQ9sinPU
__IQ9sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 8
        .def    __IQ8sinPU
__IQ8sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 7       
        .def    __IQ7sinPU
__IQ7sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 6
        .def    __IQ6sinPU
__IQ6sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 5
        .def    __IQ5sinPU
__IQ5sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 4
        .def    __IQ4sinPU
__IQ4sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 3
        .def    __IQ3sinPU
__IQ3sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 2
        .def    __IQ2sinPU
__IQ2sinPU:
        IQNsinPU  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 1
        .def    __IQ1sinPU
__IQ1sinPU:
        IQNsinPU  GLOBAL_Q
        .endif
                    
;;###########################################################################
;; No More.
;;###########################################################################
