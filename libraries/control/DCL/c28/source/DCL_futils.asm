; DCL_futils.asm - fast update function utilities for FPU32
;
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


; set symbols below to '1' to enable assembly
FU_PID  	.set    1
FU_PI   	.set    1
FU_PI2  	.set    1
FU_DF11 	.set    1
FU_DF13 	.set    1
FU_DF22 	.set    1
FU_DF23 	.set    1
FU_GSM  	.set    1
FU_NLPID	.set	1

   	  .if $defined(__TI_EABI__)
        .if __TI_EABI__
        .asg    DCL_fupdatePID, _DCL_fupdatePID
        .asg    DCL_fupdatePI, _DCL_fupdatePI
        .asg    DCL_fupdatePI2, _DCL_fupdatePI2
        .asg    DCL_fupdateDF11, _DCL_fupdateDF11
        .asg    DCL_fupdateDF13, _DCL_fupdateDF13
        .asg    DCL_fupdateDF22, _DCL_fupdateDF22
        .asg    DCL_fupdateDF23, _DCL_fupdateDF23
        .asg    DCL_fupdateGSM, _DCL_fupdateGSM
        .asg    DCL_fupdateNLPID, _DCL_fupdateNLPID
       .endif
      .endif

        .sect   "dclfuncs"

;--- PID ---------------------------------------------------------------------

        .if FU_PID = 1
        .global _DCL_fupdatePID
        .align  2

; C prototype: void DCL_fupdatePID(DCL_PID *p)
; argument 1 = *p : 32-bit DCL_PID structure address [XAR4]
; return = void [R0H]

_DCL_fupdatePID:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #26           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          PID_EXIT, EQ        ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &Kp
        SETC        INTM                ; block interrupts
        RPT         #11                 ; repeat 12 times
||      PREAD       *XAR4++, *XAR7      ; SPS copy
        ADDB        XAR4, #8            ; XAR4 = &Umax
        ADDB        XAR7, #12           ; XAR7 = &SPS.Umax
        MOVL        ACC, *XAR7++        ; SPS.Umax -> ACC
        MOVL        *XAR4++, ACC        ; update Umax
        MOVL        ACC, *XAR7          ; SPS.Umin -> ACC
        MOVL        *XAR4, ACC          ; update Umin
PID_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_PID

;--- PI ----------------------------------------------------------------------

        .if FU_PI = 1
        .global _DCL_fupdatePI
        .align  2

; C prototype: void DCL_fupdatePI(DCL_PI *p)
; argument 1 = *p : 32-bit DCL_PI structure address [XAR4]
; return = void [R0H]

_DCL_fupdatePI:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #18           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          PI_EXIT, EQ         ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &Kp
        SETC        INTM                ; block interrupts
        MOVL        ACC, *XAR7++        ; SPS.Kp -> ACC
        MOVL        *XAR4++, ACC        ; update KpUmax
        MOVL        ACC, *XAR7++        ; SPS.Ki -> ACC
        MOVL        *XAR4++, ACC        ; update Ki
        ADDB        XAR4, #2            ; XAR4 = &Umax
        MOVL        ACC, *XAR7++        ; SPS.Umax -> ACC
        MOVL        *XAR4++, ACC        ; update Umax
        MOVL        ACC, *XAR7++        ; SPS.Umin -> ACC
        MOVL        *XAR4++, ACC        ; update Umin
        ADDB        XAR4, #2            ; XAR4 = &Imax
        MOVL        ACC, *XAR7++        ; SPS.Imax -> ACC
        MOVL        *XAR4++, ACC        ; update Imax
        MOVL        ACC, *XAR7          ; SPS.Imin -> ACC
        MOVL        *XAR4, ACC          ; update Imin
PI_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_PI

;--- PI2 ----------------------------------------------------------------------

        .if FU_PI2 = 1
        .global _DCL_fupdatePI2
        .align  2

; C prototype: void DCL_fupdatePI2(DCL_PI2 *p)
; argument 1 = *p : 32-bit DCL_PI structure address [XAR4]
; return = void [R0H]

_DCL_fupdatePI2:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #18           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          PI2_EXIT, EQ        ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &Kp
        SETC        INTM                ; block interrupts
        MOVL        ACC, *XAR7++        ; SPS.Kp -> ACC
        MOVL        *XAR4++, ACC        ; update KpUmax
        MOVL        ACC, *XAR7++        ; SPS.Ki -> ACC
        MOVL        *XAR4++, ACC        ; update Ki
        ADDB        XAR4, #8            ; XAR4 = &Umax
        MOVL        ACC, *XAR7++        ; SPS.Umax -> ACC
        MOVL        *XAR4++, ACC        ; update Umax
        MOVL        ACC, *XAR7          ; SPS.Umin -> ACC
        MOVL        *XAR4, ACC          ; update Umin
PI2_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_PI2

;--- DF11 ----------------------------------------------------------------------

        .if FU_DF11 = 1
        .global _DCL_fupdateDF11
        .align  2

; C prototype: void DCL_fupdateDF11(DCL_DF11 *p)
; argument 1 = *p : 32-bit DCL_DF11 structure address [XAR4]
; return = void [R0H]

_DCL_fupdateDF11:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #12           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          DF11_EXIT, EQ       ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &b0
        SETC        INTM                ; block interrupts
        RPT         #5                  ; repeat 6 times
||      PREAD       *XAR4++, *XAR7      ; SPS copy
DF11_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_DF11

;--- DF13 ----------------------------------------------------------------------

        .if FU_DF13 = 1
        .global _DCL_fupdateDF13
        .align  2

; C prototype: void DCL_fupdateDF13(DCL_DF13 *p)
; argument 1 = *p : 32-bit DCL_DF13 structure address [XAR4]
; return = void [R0H]

_DCL_fupdateDF13:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #34           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          DF13_EXIT, EQ       ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &b0
        SETC        INTM                ; block interrupts
        RPT         #15                 ; repeat 16 times
||      PREAD       *XAR4++, *XAR7      ; SPS copy
DF13_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_DF13

;--- DF22 ----------------------------------------------------------------------

        .if FU_DF22 = 1
        .global _DCL_fupdateDF22
        .align  2

; C prototype: void DCL_fupdateDF22(DCL_DF22 *p)
; argument 1 = *p : 32-bit DCL_DF22 structure address [XAR4]
; return = void [R0H]

_DCL_fupdateDF22:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #16           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          DF22_EXIT, EQ       ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &b0
        SETC        INTM                ; block interrupts
        RPT         #9                  ; repeat 10 times
||      PREAD       *XAR4++, *XAR7      ; SPS copy
DF22_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_DF22

;--- DF23 ----------------------------------------------------------------------

        .if FU_DF23 = 1
        .global _DCL_fupdateDF23
        .align  2

; C prototype: void DCL_fupdateDF23(DCL_DF23 *p)
; argument 1 = *p : 32-bit DCL_DF23 structure address [XAR4]
; return = void [R0H]

_DCL_fupdateDF23:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #22           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          DF23_EXIT, EQ       ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &b0
        SETC        INTM                ; block interrupts
        RPT         #13                 ; repeat 14 times
||      PREAD       *XAR4++, *XAR7      ; SPS copy
DF23_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_DF23

;--- GSM ----------------------------------------------------------------------

        .if FU_GSM = 1
        .global _DCL_fupdateGSM
        .align  2

; C prototype: void DCL_fupdateGSM(DCL_GSM *p)
; argument 1 = *p : 32-bit DCL_GSM structure address [XAR4]
; return = void [R0H]

_DCL_fupdateGSM:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #38           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          GSM_EXIT, EQ        ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &m[0]
        SETC        INTM                ; block interrupts
        RPT         #33                 ; repeat 34 times
||      PREAD       *XAR4++, *XAR7      ; SPS copy
GSM_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_GSM

;--- NLPID -------------------------------------------------------------------

        .if FU_NLPID = 1
        .global _DCL_fupdateNLPID
        .align  2

; C prototype: void DCL_fupdateNLPID(DCL_NLPID *p)
; argument 1 = *p : 32-bit DCL_NLPID structure address [XAR4]
; return = void [R0H]

_DCL_fupdateNLPID:
        .asmfunc
        PUSH        ST0                 ; save flags
        PUSH        XAR0                ; save XAR0
        PUSH        XAR7                ; save XAR7
        PUSH        ST1                 ; preserve INTM
        MOVL        XAR7, @XAR4         ; XAR7 = &p
        ADDB        XAR7, #44           ; XAR7 = &CSS
        MOVL        XAR0, *XAR7         ; XAR0 = &tpt
        MOVL        ACC, *+XAR0[4]      ; ACC = CSS.sts
        AND         ACC, #1             ; mask bit 0
        BF          NLPID_EXIT, EQ      ; skip if zero
        TCLR        *+XAR0[4], #0       ; clear STS_UPDATE_PENDING flag
        MOVL        XAR0, XAR7          ; XAR0 = &CSS
        SUBB        XAR0, #2            ; XAR0 = &SPS
        MOVL        XAR7, *XAR0         ; XAR7 = &Kp
        SETC        INTM                ; block interrupts
        RPT         #27                 ; repeat 28 times
||      PREAD       *XAR4++, *XAR7      ; SPS copy
        ADDB        XAR4, #10           ; XAR4 = &Umax
        ADDB        XAR7, #28           ; XAR7 = &SPS.Umax
        MOVL        ACC, *XAR7++        ; SPS.Umax -> ACC
        MOVL        *XAR4++, ACC        ; update Umax
        MOVL        ACC, *XAR7          ; SPS.Umin -> ACC
        MOVL        *XAR4, ACC          ; update Umin
NLPID_EXIT:
        POP         ST1                 ; restore INTM
        POP         XAR7                ; restore XAR7
        POP         XAR0                ; restore XAR0
        POP         ST0                 ; restore flags
        LRETR
        .endasmfunc

        .endif      ; FU_NLPID

;-----------------------------------------------------------------------------

        .end

; end of file
