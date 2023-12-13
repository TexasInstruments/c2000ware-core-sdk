;;###########################################################################
;;
;; FILE:    IQNcos.asm
;;
;; TITLE:   C Callable IQ Math Function
;;
;;###########################################################################
;;
;; Ver  |     Date    | Who   | Description of changes
;; =====|=============|=======|==============================================
;; 1.2  | 11 Oct 2001 | A. T. | Original Release.
;; -----|-------------|-------|----------------------------------------------
;; 1.3  | 19 Nov 2001 | A. T. | No changes.
;; -----|-------------|-------|----------------------------------------------
;; 1.4  | 17 May 2002 | A. T. | Improved accuracy from 16 to about 29 bits
;;      |             |       | (thanks to Settu for writing original code).
;;      |             |       | Modified code so that calculation constants
;;      |             |       | are embedded in code and not in table.
;; -----|-------------|-------|----------------------------------------------
;;      |             |       |
;;
;;###########################################################################
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

;;===========================================================================
;; Function:   _IQNcos
;;===========================================================================
;;
;; C Usage:    extern long _IQNcos(long Rad);
;;
;;---------------------------------------------------------------------------
;;
;; On Entry:   ACC = Radian in IQ format
;;
;; Regs Used:  XAR7, XAR6, XAR5, XAR4, XAR0
;;             XT, P
;;
;; On Exit:    ACC = cos(Radian) result in IQ format
;;
;; Q range:    30 to 1
;;
;;---------------------------------------------------------------------------
;; Algorithm:  The "cos" value is calculated as follows:
;;
;;             1) The offset into a 512 word sin/cos table is calculated:
;;
;;                 k = 0x1FF & (int(Radian*512/(2*pi)))
;;                 
;;
;;             2) The fractional component between table samples is
;;                calculated:
;;
;;                 x = fract(Radian*512/2*pi) * (2*pi)/512
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
;; Cycles = 43  (      Q == 30, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 44  (29 >= Q >= 25, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 43  (24 >= Q >= 14, tables in 0-wait SARAM, includes LCR/LRETR)
;;        = 44  (13 >= Q >= 0,  tables in 0-wait SARAM, includes LCR/LRETR)
;;
;; Cycles = 45  (      Q == 30, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 46  (29 >= Q >= 25, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 45  (24 >= Q >= 14, tables in 1-wait ROM,   includes LCR/LRETR)
;;        = 46  (13 >= Q >= 0,  tables in 1-wait ROM,   includes LCR/LRETR)
;;
;;===========================================================================


K1      .set    02AAAh                  ; 1/6 in Q16

IQNcos  .macro  q_value
		MOV     *SP++,#0x3F6B			; (2*pi)/512 = 0x03243F6B (Q32)
		MOV		*SP++,#0x0324
		MOV		*SP++,#0xC1B7			; 512/(2*pi) = 0x517CC1B7 (I8Q24)
		MOV		*SP++,#0x517C
        MOVL    XAR6,#_IQcosTable           
        MOVL    XAR7,#_IQsinTable           

        SETC	OVM						; turn overflow mode on
        ABS     ACC                     ; abs(Rad), TC = sign

        MOVL    XT,*--SP                ; XT = 512/(2*pi) (I8Q24)
        IMPYL   P,XT,@ACC
        QMPYL   ACC,XT,@ACC             ; ACC:P = Rad * 512 / (2pi)
        
        .if q_value >= 25
        ASR64   ACC:P,#16
        ASR64   ACC:P,#(q_value - 24)   ; ACC = Integer, P = fract
        .endif       
        .if (q_value <= 24) & (q_value >= 9)
        ASR64   ACC:P,#(q_value - 8)    ; ACC = Integer, P = fract
        .endif
        .if q_value <= 7
        LSL64   ACC:P,#(8 - q_value)    ; ACC = Integer, P = fract
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
        .def    __IQ30cos
__IQ30cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 29
        .def    __IQ29cos
__IQ29cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 28      
        .def    __IQ28cos
__IQ28cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 27      
        .def    __IQ27cos
__IQ27cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 26
        .def    __IQ26cos
__IQ26cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 25
        .def    __IQ25cos
__IQ25cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 24      
        .def    __IQ24cos
__IQ24cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 23
        .def    __IQ23cos
__IQ23cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 22
        .def    __IQ22cos
__IQ22cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 21
        .def    __IQ21cos
__IQ21cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 20      
        .def    __IQ20cos
__IQ20cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 19
        .def    __IQ19cos
__IQ19cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 18
        .def    __IQ18cos
__IQ18cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 17
        .def    __IQ17cos
__IQ17cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 16
        .def    __IQ16cos
__IQ16cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 15
        .def    __IQ15cos
__IQ15cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 14
        .def    __IQ14cos
__IQ14cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 13
        .def    __IQ13cos
__IQ13cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 12
        .def    __IQ12cos
__IQ12cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 11
        .def    __IQ11cos
__IQ11cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 10
        .def    __IQ10cos
__IQ10cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 9
        .def    __IQ9cos
__IQ9cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 8
        .def    __IQ8cos
__IQ8cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 7       
        .def    __IQ7cos
__IQ7cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 6
        .def    __IQ6cos
__IQ6cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 5
        .def    __IQ5cos
__IQ5cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 4
        .def    __IQ4cos
__IQ4cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 3
        .def    __IQ3cos
__IQ3cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 2
        .def    __IQ2cos
__IQ2cos:
        IQNcos  GLOBAL_Q
        .endif

        .if GLOBAL_Q == 1
        .def    __IQ1cos
__IQ1cos:
        IQNcos  GLOBAL_Q
        .endif
                    
;;###########################################################################
;; No More.
;;###########################################################################
