;;#############################################################################
;;! \file source/vector/mpy_SP_RMxRM_2.asm
;;!
;;! \brief  C-Callable multiplication of two real matrices
;;! \author David M. Alter
;;! \date   09/17/15
;; HISTORY:
;;   09/17/15 - original (D. Alter)
;;
;; DESCRIPTION:  y[] = w[] * x[]
;;                where   w[] is of dimension m x n
;;                        x[] is of dimension n x p
;;                        y[] is of dimension m x p
;;
;; Note that in C, a two-dimensional array has elements stored sequentially 
;; down the column. For example, this array:
;;                             | 1 2 |
;;                             | 3 4 |
;;
;; will be stored in memory as [1, 3, 2, 4].  It could be declared in C as 
;; x[4] or x[2][2].
;;
;; FUNCTION: 
;;   extern void mpy_SP_RMxRM_2(float *y, const float *w, const float *x,
;;                      const uint16_t m, const uint16_t n, const uint16_t p)
;;
;; USAGE:       mpy_SP_RMxRM_2(y, w, x, m, n, p);
;;
;; PARAMETERS:  float* y = pointer to result matrix
;;              float* w = pointer to 1st src matrix
;;              float* x = pointer to 2nd src matrix
;;              m = dimension m of matrices
;;              n = dimension n of matrices
;;              p = dimension p of matrices
;;
;; RETURNS:     none
;;
;; BENCHMARK: 2.5*m*n*p + overhead  (cycles)
;;   Note that the overhead is significant for small dimensions.
;;   For example, 
;;         m=2 n=8, p=2 takes ~199 cycles (versus 2.5*m*n*p = 80).
;;         m=8, n=8, p=8 takes ~2479 cycles (versus 2.5*m*n*p = 1280).
;;         m=64, n=64, p=64 takes ~725663 cycles (versus 2.5*m*n*p = 655360).
;;   This benchmark equation is best used to guage relative performance against
;;   other matrix multiply functions rather than for trying to determine exact
;;   execution cycles.
;;
;; NOTES:
;;  1) n must be even and at least 4.  If not, use mpy_SP_RMxRM().
;;  2) There are no restrictions on the values of m and p with this function.
;;
;; ***PASSED PARAMETERS***
;;  XAR4 = &y[0,0]
;;  XAR5 = &w[0,0]
;;    AH = n
;;    AL = m
;;  *-SP[4] = &x[0,0]
;;  *-SP[5] = p
;;
;; ***REGISTER USAGE***
;;   AR0 = row index adder (2*m)
;;   AR1 = inner loop count seed (n/2-2)
;;  XAR2 = &w (working register)
;;  XAR3 = &x (working register)
;;  XAR4 = &y (working register)
;;  XAR5 = &w[0,0]
;;   AR6 = middle loop counter (p iterations)
;;   AR7 = outer loop counter (m iterations)
;;     T = middle loop count seed (p-1)
;;
;; ***STACK USAGE***
;; -SP[13] = p
;; -SP[12] = &x[0,0]
;; -SP[10] = return PC
;; -SP[8]  = saved XAR1
;; -SP[6]  = saved XAR2
;; -SP[4]  = saved XAR3
;; -SP[2]  = &y[0,0]
;; -SP[0]  = next free location
;;
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
        .if __TI_EABI__
        .asg mpy_SP_RMxRM_2, _mpy_SP_RMxRM_2
        .endif
    
        .global _mpy_SP_RMxRM_2
        .text

_mpy_SP_RMxRM_2:
        MOVL        *SP++, XAR1     ;Save XAR1 (save-on-entry register)
        MOVL        *SP++, XAR2     ;Save XAR2 (save-on-entry register)
        MOVL        *SP++, XAR3     ;Save XAR3 (save-on-entry register)
                                    
        MOVL        *SP++, XAR4     ;Store &y[0,0] on stack
                                    
        LSR         AH, #1          ;AH = n/2
        ADDB        AH, #-2         ;Subtract 2 (-1-1) since RPTB is 'N-1', 
                                    ;and also inner loop is pipelined
        MOV         AR1, AH         ;AR1 = inner loop count seed (n/2 - 2)
                                    
        MOV         AH, AL          ;AH = AL = m
        ADDB        AL, #-1         ;Subtract 1 from m since BANZ is 'N-1'
        MOV         AR7, AL         ;AR7 = outer loop counter (m-1)
                                    
        MOV         AL, *-SP[13]    ;AL = p
        ADDB        AL, #-1         ;Subtract 1 from m since BANZ is 'N-1'
        MOV         T, AL           ;T = middle loop count seed (p-1)
                                    
        LSL         AH, #1          ;AH = 2*m (because floating pt is 2 word 
                                    ;addresses)
        MOV         AR0, AH         ;AR0 = results row index adder (2*m)

;---------------------------------------------------------------
;--- Outer loop
;---------------------------------------------------------------
loop1:

; Middle loop preparation
        MOVL        XAR3, *-SP[12]  ;XAR3 = &x
        MOVL        XAR4, *-SP[2]   ;XAR4 = &y
        MOV         AR6, T          ;Load middle loop counter with seed
    
        SETC        AMODE           ;C2xLP addressing mode
        .lp_amode

;-----------------------------------------------------
;--- Middle loop
;-----------------------------------------------------
loop2:

; Inner loop preparation
        MOVL        XAR2, XAR5      ;XAR2 = &w
        ZERO        R3H             ;Zero out the result accumulation 
                                    ;(iteration i)
        NOP         *, ARP2         ;ARP = XAR2

;-------------------------------------------
;--- Inner loop
;-------------------------------------------

;prolog
        MOV32       R0H, *0++, ARP3 ;(iteration i) R0H=w, XAR2+=AR0, ARP=XAR3
        MOV32       R1H, *++, ARP2  ;(iteration i) R1H=x, ARP=XAR2
        MPYF32      R2H, R0H, R1H   ;(iteration i)
        MOV32       R0H, *0++, ARP3 ;(iteration i+1) R0H=w, XAR2+=AR0, ARP=XAR3

        ADDF32      R3H, R3H, R2H   ;(iteration i)
    ||  MOV32       R1H, *++, ARP2  ;(iteration i+1) R1H=x, ARP=XAR2

;loop
        RPTB        end_loop3, AR1
        MPYF32      R2H, R0H, R1H   ;(iteration i+1)
    ||  MOV32       R0H, *0++, ARP3 ;(iteration i) R0H=w, XAR2+=AR0, ARP=XAR3
        MOV32       R1H, *++, ARP2  ;(iteration i) R1H=x, ARP=XAR2
        ADDF32      R3H, R3H, R2H   ;(iteration i+1)
    ||  MPYF32      R2H, R0H, R1H   ;(iteration i)
        MOV32       R0H, *0++, ARP3 ;(iteration i+1) R0H=w, XAR2+=AR0, ARP=XAR3
        ADDF32      R3H, R3H, R2H   ;(iteration i)
    ||  MOV32       R1H, *++, ARP2  ;(iteration i+1) R1H=x, ARP=XAR2

end_loop3:

;epilog
        MPYF32      R2H, R0H, R1H   ;(iteration i+1)
        NOP                         ;(iteration i+1)
        ADDF32      R3H, R3H, R2H   ;(iteration i+1)

;-------------------------------------------
;--- End of inner loop
;-------------------------------------------

        NOP         *, ARP4
        MOV32       *0++, R3H       ;Store the result
        BANZ        loop2, AR6--    ;Middle loop branch
;-----------------------------------------------------
;--- End of middle loop
;-----------------------------------------------------

        CLRC        AMODE           ;C28 addressing mode
        .c28_amode  
    
        MOVB        ACC, #2         ;ACC = 2 (2 words per floating pt value)
        ADDL        XAR5, ACC       ;Advance &x to the next row
        ADDL        *-SP[2], ACC    ;Advance &y to the next row
    
        BANZ        loop1, AR7--    ;Outer loop branch
;---------------------------------------------------------------
;--- End of outer loop
;---------------------------------------------------------------

;Finish up
        SUBB        SP, #2          ;De-allocate local frame
        MOVL        XAR3, *--SP     ;Restore XAR3 (save-on-entry register)
        MOVL        XAR2, *--SP     ;Restore XAR2 (save-on-entry register)
        MOVL        XAR1, *--SP     ;Restore XAR1 (save-on-entry register)
        LRETR                       ;return

;end of function mpy_SP_RMxRM_2()
;**********************************************************************

        .end

;;#############################################################################
;;  End of File
;;#############################################################################
