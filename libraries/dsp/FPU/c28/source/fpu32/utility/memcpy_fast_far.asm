;;#############################################################################
;;! \file source/vector/memcpy_fast_far.asm
;;!
;;! \brief Optimized memory copy, src->dest.
;;! \author David M. Alter
;;! \date   10/21/14
;;
;; AUTHOR:      David M. Alter, Texas Instruments Inc.
;;
;; HISTORY:
;;   10/21/14 - original (D. Alter)
;;
;; DESCRIPTION: Optimized memory copy, src->dest.
;;
;; FUNCTION: 
;;   extern void memcpy_fast_far(volatile void* dst, volatile const void* src,
;;                               Uint16 N);
;;
;; USAGE:       memcpy_fast_far(dst, src, N);
;;
;; PARAMETERS:  volatile void* dst = pointer to destination
;;              volatile const void* src = pointer to source
;;              N = number of 16-bit words to copy
;;
;; RETURNS:     none
;;
;; BENCHMARK: The performance of this function differs depending on the
;;    address alignment of the src and dst addresses (pointers).
;;    - If both pointers have the same alignment (even or odd address),
;;    then 32-bit copies are used for the bulk of the transfers.  This
;;    allows performance to approach 1 cycle/word (16-bit word) plus
;;    overhead.
;;    - If the two pointers have different alignments (one even aligned,
;;    the other odd aligned) then 16-bit transfers must be used.  This
;;    provides performance approaching 2 cycles/word (16-bit word) plus
;;    overhead.
;;    The above benchmarks assume that the src and dst are located in
;;    different internal RAM blocks (so there are no RAM stalls).
;;
;; NOTES:
;;   1) The function checks for the case of N=0 and just returns if true.
;;   2) This function is restricted to C28x devices with the FPU.
;;   3) This function is intended for data above 22 bits address.
;;      For input data at or below 22 bits address, use memcpy_fast
;;      instead for better performance.
;;   4) PREAD and PWRITE are used in the function, but this is OK with
;;      above 22-bit address since the program bus is used for stack
;;      access (below 22 bits).  The data bus is used for the >22-bit
;;      address access.
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
    .asg memcpy_fast_far, _memcpy_fast_far
    .endif
    
    .global _memcpy_fast_far
    .text

_memcpy_fast_far:
; Need to check 32-bit alignment of src and dst pointers for 32-bit transfers.
; There are found cases:
; Case 1: both pointers aligned
; Case 2: neither pointer aligned
; Case 3: src pointer aligned, dst pointer not aligned
; Case 4: src pointer not aligned, dst pointer aligned


; Test src pointer alignment
    TBIT    AR5, #0          ;Test if src pointer is aligned
    SBF     line1a, NTC      ;Branch if aligned

; src pointer not aligned.  Test dst pointer.
    TBIT    AR4, #0          ;Test if dst pointer is aligned
    SBF     line1b, NTC      ;Branch if aligned

;--------------
; Case 2 is true - neither pointer aligned
; Copy the first 16-bit word to align both pointers
    ADDB    AL, #-1          ;Decrement the copy number
    BF      done3, NC        ;Branch if N was zero
    MOV     AH, *XAR5++      ;Read the src
    MOV     *XAR4++, AH      ;Store to dst
    BF      line3a, UNC      ;Proceed with 32-bit copies

;--------------
line1b:
; Case 4 is true - src pointer not aligned, dst pointer aligned.
    BF      line2a, UNC      ;Proceed with 16-bit copies

;--------------
line1a:
; src pointer aligned.  Test dst pointer.
    TBIT    AR4, #0          ;Test bit 0 of dst pointer
    SBF     line1c, NTC      ;Branch if aligned

;--------------
; Case 3 is true - src pointer aligned, dst pointer not aligned.
; Proceed with 16-bit copies.

;--------------------------------------
line2a:
; 16-bit copies.
; These are used when the src and dst pointers have different alignments
; (i.e., one is aligned, the other is not aligned).
; Copy as many 8x16-bit word blocks as possible.
; 8x16-bit length blocks are used so we can meet minimum size of RPTB.
    MOV     PL, AL           ;Save current copy number
    LSR     AL, #3           ;Divide by 8
    
    ADDB    AL, #-1          ;Repeat "N-1" times
    BF      line2b, NC       ;Branch if N was zero
    
    RPTB    line2b, @AL
    MOV     AH, *XAR5++       ;Read src #1
    MOV     *XAR4++, AH       ;Write dst #1
    MOV     AH, *XAR5++       ;Read src #2
    MOV     *XAR4++, AH       ;Write dst #2
    MOV     AH, *XAR5++       ;Read src #3
    MOV     *XAR4++, AH       ;Write dst #3
    MOV     AH, *XAR5++       ;Read src #4
    MOV     *XAR4++, AH       ;Write dst #4
    MOV     AH, *XAR5++       ;Read src #5
    MOV     *XAR4++, AH       ;Write dst #5
    MOV     AH, *XAR5++       ;Read src #6
    MOV     *XAR4++, AH       ;Write dst #6
    MOV     AH, *XAR5++       ;Read src #7
    MOV     *XAR4++, AH       ;Write dst #7
    MOV     AH, *XAR5++       ;Read src #8
    MOV     *XAR4++, AH       ;Write dst #8

line2b:
; Do the remaining elements as 16-bit copies.  There could be up to 7 of them.
    MOV     AL, PL           ;Restore the saved copy number
    AND     AL, #0007h       ;Isolate 1st 3 bits of the copy number 
                             ;(0 - 15 copies)
    MOVL    XAR7, #0         ;Zero out XAR7
    MOV     AR7, SP          ;AR7 = SP
    ADD     SP, AL           ;Advance stack pointer beyond copy area
    
    ADDB    AL, #-1          ;Repeat "N-1" times
    BF      done2, NC        ;Branch if N was zero
    RPT     @AL
 || PWRITE  *XAR7, *XAR5++   ;Copy src words to the stack
    RPT     @AL
 || PREAD   *XAR4++, *XAR7   ;Copy stack words to the dst
    
    SUB     SP, AL           ;Restore the stack pointer (part 1)
    SUB     SP, #1           ;Restore the stack pointer (part 2)

;Finish up
done2:
    LRETR                    ;return

;--------------
line1c:
; Case 1 is true - both pointers aligned.
; Proceed with 32-bit copies.

;--------------------------------------
line3a:
; 32-bit copies.
; Copy as many 8x32-bit word blocks as possible.
; 8x32-bit (16x16-bit) length blocks are used so we can meet minimum size of 
; RPTB.
    MOV     PL, AL           ;Save current copy number
    LSR     AL, #4           ;Divide by 16
        
    ADDB    AL, #-1          ;Repeat "N-1" times
    BF      line3b, NC       ;Branch if N was zero
    
    RPTB    line3b, @AL
    MOVL    ACC, *XAR5++     ;Read src #1
    MOVL    *XAR4++, ACC     ;Write dst #1
    MOVL    ACC, *XAR5++     ;Read src #2
    MOVL    *XAR4++, ACC     ;Write dst #2
    MOVL    ACC, *XAR5++     ;Read src #3
    MOVL    *XAR4++, ACC     ;Write dst #3
    MOVL    ACC, *XAR5++     ;Read src #4
    MOVL    *XAR4++, ACC     ;Write dst #4
    MOVL    ACC, *XAR5++     ;Read src #5
    MOVL    *XAR4++, ACC     ;Write dst #5
    MOVL    ACC, *XAR5++     ;Read src #6
    MOVL    *XAR4++, ACC     ;Write dst #6
    MOVL    ACC, *XAR5++     ;Read src #7
    MOVL    *XAR4++, ACC     ;Write dst #7
    MOVL    ACC, *XAR5++     ;Read src #8
    MOVL    *XAR4++, ACC     ;Write dst #8

line3b:
; Do the remaining elements as 16-bit copies.  There could be up to 15 of them.
    MOV     AL, PL           ;Restore the saved copy number
    AND     AL, #000Fh       ;Isolate 1st 4 bits of the copy number 
                             ;(0 - 15 copies)
    MOVL    XAR7, #0         ;Zero out XAR7
    MOV     AR7, SP          ;AR7 = SP
    ADD     SP, AL           ;Advance stack pointer beyond copy area
    
    ADDB    AL, #-1          ;Repeat "N-1" times
    BF      done3, NC        ;Branch if N was zero
    RPT     @AL
 || PWRITE  *XAR7, *XAR5++   ;Copy src words to the stack
    RPT     @AL              
 || PREAD   *XAR4++, *XAR7   ;Copy stack words to the dst
                             
    SUB     SP, AL           ;Restore the stack pointer (part 1)
    SUB     SP, #1           ;Restore the stack pointer (part 2)

;Finish up
done3:
    LRETR                    ;return

;end of function memcpy_fast_far()
**********************************************************************

    .end
;;#############################################################################
;;  End of File
;;#############################################################################
