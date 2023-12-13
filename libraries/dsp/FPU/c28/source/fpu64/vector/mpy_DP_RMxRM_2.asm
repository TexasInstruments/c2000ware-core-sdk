;;#############################################################################
;;! \file source/fpu64/vector/mpy_DP_RMxRM_2.asm
;;!
;;! \brief  C-Callable multiplication of two double precision real matrices
;;! \author Vishal Coelho (adapted from SP version by David Alter)
;;! \date   04/12/2017
;;
;; DESCRIPTION: C-Callable multiplication of two real matrices y[] = w[] * x[]
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
;; FUNCTIONS:
;;   extern void mpy_DP_RMxRM_2(long double *y, long double *w, long double *x,
;;                       const uint16_t m, const uint16_t n, const uint16_t p)
;;  
;; PARAMETERS:  long double* y = pointer to result matrix
;;              long double* w = pointer to 1st src matrix
;;              long double* x = pointer to 2nd src matrix
;;              m = dimension m of matrices
;;              n = dimension n of matrices
;;              p = dimension p of matrices
;;
;; RETURNS:    none
;;
;; BENCHMARK:  4.5*m*n*p + overhead  (cycles)
;;   Note that the overhead is significant for small dimensions.
;;   For example, 
;;         m=2 n=8, p=2 takes ~TODO cycles (versus 4.5*m*n*p = 144).
;;         m=8, n=8, p=8 takes ~TODO cycles (versus 4.5*m*n*p = 2304).
;;         m=64, n=64, p=64 takes ~TODO cycles (versus 4.5*m*n*p = 1179648).
;;   This benchmark equation is best used to guage relative performance against
;;   other matrix multiply functions rather than for trying to determine exact
;;   execution cycles.
;;
;; NOTES:
;;  1) n must be even and at least 4.  If not, use mpy_DP_RMxRM().
;;  2) There are no restrictions on the values of m and p with this function.
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

;; the includes

;; external references

;;*****************************************************************************
;; void mpy_DP_RMxRM_2(long double *y, long double *w, long double *x,
;;                   const uint16_t m, const uint16_t n, const uint16_t p)
;;
;; C-Callable multiplication of two real matrices,
;;                y[] = w[] * x[]
;;
;; Register Usage:
;;     AH  :  m, dimension m of matrices   (argument + working)
;;     AL  :  n, dimension n of matrices   (argument + working)
;;   XAR2  : *w, pointer to 1st src matrix (working)
;;   XAR3  : *x, pointer to 2nd src matrix (working)
;;   XAR4  : *y, pointer to result matrix  (argument + working)
;;   XAR5  : *w, pointer to 1st src matrix (argument)
;;    AR6  : middle loop counter (p iterations)
;;    AR7  : outer loop counter (m interations)
;;      T  : middle loop count seed (p-1)
;;
;;   
;; Stack Usage:
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- XAR4 &y[0,0]                     (SP-2)--> Local Frame
;;   |_______|<- XAR3                             (SP-4)
;;   |_______|<- XAR2                             (SP-6)
;;   |_______|<- XAR1                             (SP-8)
;;   |_______|<- rpc calling function             (SP-10)
;;   |_______|<- &x[0,0]                          (SP-12)
;;   |_______|<- p                                (SP-13)

;;*****************************************************************************
    .if __TI_EABI__
    .asg mpy_DP_RMxRM_2, _mpy_DP_RMxRM_2
    .endif
    
    .page
    .global _mpy_DP_RMxRM_2
    .sect   ".text"
_mpy_DP_RMxRM_2:
    .asmfunc
    .asg    *-SP[2] , STK_PTR_Y
    .asg    *-SP[12], STK_PTR_X
    .asg    *-SP[13], STK_P
    MOVL    *SP++, XAR1     ; Save XAR1 (save-on-entry register)
    MOVL    *SP++, XAR2     ; Save XAR2 (save-on-entry register)
    MOVL    *SP++, XAR3     ; Save XAR3 (save-on-entry register)
                              
    MOVL    *SP++, XAR4     ; Store &y[0,0] on stack
                              
    LSR     AH, #1          ; AH = n/2
    ADDB    AH, #-2         ; Subtract 2 (-1-1) since RPTB is 'N-1', 
                            ; and also inner loop is pipelined
    MOV     AR1, AH         ; AR1 = inner loop count seed (n-1)
                              
    MOV     AH, AL          ; AH = AL = m
    ADDB    AL, #-1         ; Subtract 1 from m since BANZ is 'N-1'
    MOV     AR7, AL         ; AR7 = outer loop counter (m-1)
                              
    MOV     AL, STK_P       ; AL = p
    ADDB    AL, #-1         ; Subtract 1 from m since BANZ is 'N-1'
    MOV     T, AL           ; T = middle loop count seed (p-1)
                            
    LSL     AH, #2          ; AH = 4*m-2 (because double is 4 word
	SUBB	AH, #2          ;         addresses and we increment
                            ;         after reading low 32-bits)
    MOV     AR0, AH         ; AR0 = results row index adder (4*m-2)

;---------------------------------------------------------------
;--- Outer loop
;---------------------------------------------------------------
_mpy_DP_RMxRM_2_loop1:

; Middle loop preparation
    MOVL    XAR3, STK_PTR_X ; XAR3 = &x
    MOVL    XAR4, STK_PTR_Y ; XAR4 = &y
    MOV     AR6, T          ; Load middle loop counter with seed
                              
    SETC    AMODE           ; C2xLP addressing mode
    .lp_amode                  

;-----------------------------------------------------
;--- Middle loop
;-----------------------------------------------------
_mpy_DP_RMxRM_2_loop2:

; Inner loop preparation
    MOVL    XAR2, XAR5      ; XAR2 = &w
    ZERO    R3              ; Zero out the result accumulation
    NOP     *, ARP2         ; ARP = XAR2

;-------------------------------------------
;--- Inner loop
;-------------------------------------------
;prolog
    MOV32   R0L, *++        ;(iteration i) R0=w
    MOV32   R0H, *0++, ARP3 ;                   XAR2+=AR0  , ARP=XAR3
    MOV32   R1L, *++        ;(iteration i) R1=x           
    MOV32   R1H, *++, ARP2  ;                              , ARP=XAR2
    MPYF64  R2, R0, R1      ; *|(iteration i)
    MOV32   R0L, *++        ; 1|(iteration i+1) R0=w,
    MOV32   R0H, *0++, ARP3 ; 2|                XAR2+=AR0  , ARP=XAR3
    ADDF64  R3, R3, R2      ; *|(iteration i)
 || MOV32   R1L, *++        ;  |(iteration i+1) R1=x
    MOV32   R1H, *++, ARP2  ; 1|                           , ARP=XAR2
;loop                       ; 2|
    RPTB    _mpy_DP_RMxRM_2_end_loop3, AR1
    MPYF64  R2, R0, R1      ; *| (iteration i+1)
 || MOV32   R0L, *++        ;  | (iteration i) R0=w,
    MOV32   R0H, *0++, ARP3 ; 1| (iteration i)   XAR2+=AR0 , ARP=XAR3
    MOV32   R1L, *++        ; 2| (iteration i) R1=x
    MOV32   R1H, *++, ARP2  ;    (iteration i)             , ARP=XAR2
    ADDF64  R3, R3, R2      ; *| (iteration i+1)
 || MPYF64  R2, R0, R1      ;  | (iteration i)
    MOV32   R0L, *++        ; 1| (iteration i+1) R0=w,
    MOV32   R0H, *0++, ARP3 ; 2| (iteration i+1) XAR2+=AR0 , ARP=XAR3
    ADDF64  R3, R3, R2      ; *| (iteration i)
 || MOV32   R1L, *++        ;  | (iteration i+1) R1=x
    MOV32   R1H, *++, ARP2  ; 1| (iteration i+1)           , ARP=XAR2 
    NOP                     ; 2|
_mpy_DP_RMxRM_2_end_loop3:                          

;epilog
    MPYF64  R2, R0, R1      ; *| (iteration i+1)
    NOP                     ; 1| (iteration i+1)
    NOP                     ; 2| (iteration i+1)
    ADDF64  R3, R3, R2      ; *| (iteration i+1)
;-------------------------------------------
;--- End of inner loop
;-------------------------------------------
    NOP     *, ARP4         ; 1|                 , ARP=XAR4
    NOP                     ; 2|
    MOV32   *++, R3L        ; Store the result (XAR4+=AR0)
    MOV32   *0++, R3H
                            ; Middle loop branch
    BANZ    _mpy_DP_RMxRM_2_loop2, AR6--    
;-----------------------------------------------------
;--- End of middle loop
;-----------------------------------------------------
    
    CLRC    AMODE           ; C28 addressing mode
    .c28_amode  
    
    MOVB    ACC, #4         ; ACC = 4 (4 words per double value)
    ADDL    XAR5, ACC       ; Advance &x to the next row
    ADDL    STK_PTR_Y, ACC  ; Advance &y to the next row
                            ; Outer loop branch  
    BANZ    _mpy_DP_RMxRM_2_loop1, AR7--    
;---------------------------------------------------------------
;--- End of outer loop
;---------------------------------------------------------------

;Finish up
    SUBB    SP, #2          ; De-allocate local frame
    MOVL    XAR3, *--SP     ; Restore XAR3 (save-on-entry register)
    MOVL    XAR2, *--SP     ; Restore XAR2 (save-on-entry register)
    MOVL    XAR1, *--SP     ; Restore XAR1 (save-on-entry register)
    LRETR
    .endasmfunc
    .unasg  STK_PTR_Y
    .unasg  STK_PTR_X
    .unasg  STK_P
  
;; End of File
