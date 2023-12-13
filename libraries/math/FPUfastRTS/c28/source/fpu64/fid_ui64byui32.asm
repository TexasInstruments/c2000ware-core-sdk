;;#############################################################################
;;! \file source/fpu64/fid_ui64byui32.asm
;;!
;;! \brief  Unsigned Long (64-bit) / Unsigned integer (32-bit) 
;;! \author Vishal Coelho  
;;! \date   04/07/2016 
;;
;; DESCRIPTION:
;;
;;   This function performs a 64-bit/32-bit unsigned division (truncated)
;;
;; FUNCTIONS:
;;
;; void FID_ui64byui32(uint64_t *p_num_rem, uint64_t *p_den_quo)
;;  
;; ASSUMPTIONS:
;;
;; ALGORITHM:
;;
;;  The algorithm used is a slow division method (Restoring division)
;;  see https://en.wikipedia.org/wiki/Division_algorithm#Restoring_division
;;
;;  Let N be the dividend, D the divisor, T a temporary variable and P 
;;  the partial remainder of each iteration, i the bit index and loop iterator
;;  
;; First we process the high double word of the numerator
;; outer_loop:                -- twice, upper and lower dwords of the numerator
;;    R = 0                   -- start with a remainder of 0
;; loop i = 31:-1:0
;;    T = (R << 1) + N(i) - D -- shift up remainder, tack on MSb of numerator
;;                            -- subtract divisor
;;    if(T >= 0)              -- if the difference is positive 
;;      R = T & 0xFFF...FFUL  ---- remainder = T        
;;      N = N << 1 + 1        ---- shift numerator up and add 1 (quotient)
;;    else                    -- else                  
;;      R = (R << 1) + N(63)  ---- shift up remainder, tack on MSb of numerator
;;      N = N << 1            ---- shift up numerator 
;;    end
;; endloop                    -- after 31 such iterations N has the quotient
;;                            -- and R the remainder
;; swap                       -- swap the high and low dwords of the 
;;                            -- numerator/quotient
;; end_outer_loop
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



;;*****************************************************************************
;; Register Usage:
;;   R1H:R0H  : dividend (quotient)
;;   R2H      : remainder
;;   R3H      : divisor 
;;   XAR4     : pointer to dividend (numerator) and subsequently remainders 
;;   XAR5     : pointer to divisor (denominator) and subsequently quotient 
;;
;; cycles = 4(call) + 26(body) + 4(return)
;;        = 34
;;*****************************************************************************
    .page
    .if __TI_EABI__
    .asg    FID_ui64byui32, _FID_ui64byui32
    .endif
    .global _FID_ui64byui32
    .sect   ".text"
_FID_ui64byui32:
    .asmfunc
    MOV32       R0H, *+XAR4[0] ; [R1H:R0H] = dividend
    MOV32       R1H, *+XAR4[2]
    MOV32       R3H, *+XAR5[0] ; R3H = divisor
    ZERO        R2
    MOV32       *+XAR4[2], R2H ; Zero high dword of remainder
    .asg        1, N
    .loop
    SUBC4UI32   R2H, R1H, R3H   
    .break  N == 8
    .eval   N + 1, N
    .endloop
    SWAPF       R1, R0
    .asg        1, N
    .loop
    SUBC4UI32   R2H, R1H, R3H   
    .break  N == 8
    .eval   N + 1, N
    .endloop
    SWAPF       R1, R0
    MOV32       *+XAR5[0], R0H
    MOV32       *+XAR5[2], R1H  ; Save quotient
    MOV32       *+XAR4[0], R2H  ; Save remainder
    LRETR
    .unasg  N
    .endasmfunc

;; End of File
