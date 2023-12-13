;;#############################################################################
;;! \file source/fpu64/fid_i32byi32.asm
;;!
;;! \brief  Signed Integer (32-bit) Division
;;! \author Vishal Coelho  
;;! \date   03/30/2016 
;;
;; DESCRIPTION:
;;
;;   This function performs a 32-bit signed division (truncated, modulo or
;;   euclidean)
;;
;; FUNCTIONS:
;;
;; void FID_i32byi32_t(int32_t *p_num_rem, int32_t *p_den_quo)
;; void FID_i32byi32_m(int32_t *p_num_rem, int32_t *p_den_quo)
;; void FID_i32byi32_e(int32_t *p_num_rem, int32_t *p_den_quo)
;;  
;; ASSUMPTIONS:
;;
;; ALGORITHM:
;;
;;  The algorithm used is a slow division method (Restoring division)
;;  see https://en.wikipedia.org/wiki/Division_algorithm#Restoring_division
;;
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
;; Truncated Division
;;
;;  Let N be the dividend, D the divisor, T a temporary variable and P 
;;  the partial remainder of each iteration, i the bit index and loop iterator
;;    F.TF = sign(num) ^ sign(den)
;;    F.NI = sign(num)
;;    N = |N| , D = |D|
;;    R = 0 -- start with a remainder of 0
;; loop i = 31:-1:0
;;    T = (R << 1) + N(i) - D -- shift up remainder, tack on MSb of numerator
;;                            -- subtract divisor
;;    if(T >= 0)              -- if the difference is positive 
;;      R = T & 0xFFFFFFFF    ---- remainder = T        
;;      N = N << 1 + 1        ---- shift numerator up and add 1 (quotient)
;;    else                    -- else                  
;;      R = (R << 1) + N(31)  ---- shift up remainder, tack on MSb of numerator
;;      N = N << 1            ---- shift up numerator 
;;    end
;; endloop                    -- after 32 such iterations N has the quotient
;;                            -- and R the remainder
;; if(F.TF == 1), Q = -Q      -- The quotient is in the variable that 
;;                            -- previously held the numerator
;; if(F.NI == 1), R = -R      -- In truncating division remainder follows the 
;;                            -- sign of the dividend
;; Register Usage:
;;   R1H : dividend (quotient)
;;   R2H : remainder
;;   R3H : divisor 
;;   XAR4: pointer to dividend (numerator) and subsequently remainders 
;;   XAR5: pointer to divisor (denominator) and subsequently quotient 
;; 
;; cycles = 4(call) + 14(body) + 4(return)
;;        = 22
;;*****************************************************************************
    .page
    .if __TI_EABI__
    .asg    FID_i32byi32_t, _FID_i32byi32_t
    .endif
    .global _FID_i32byi32_t
    .sect   ".text"
_FID_i32byi32_t:
    .asmfunc
    MOV32       R1H, *+XAR4[0] ; R1H = dividend
    MOV32       R3H, *+XAR5[0] ; R3H = divisor
    ABSI32DIV32 R2H, R1H, R3H
    .asg        1, N
    .loop
    SUBC4UI32   R2H, R1H, R3H   
    .break  N == 8 
    .eval   N + 1, N
    .endloop
    NEGI32DIV32 R1H, R2H
    MOV32       *+XAR5[0], R1H  ; Save quotient
    MOV32       *+XAR4[0], R2H  ; Save remainder
    LRETR
    .unasg  N
    .endasmfunc

;;*****************************************************************************
;; Modulo (Floored) Division
;;
;;    F.TF = sign(num) ^ sign(den)
;;    F.NI = sign(num)
;;    N = |N| , D = |D|
;;    R = 0 -- start with a remainder of 0
;; loop i = 31:-1:0
;;    T = (R << 1) + N(i) - D -- shift up remainder, tack on MSb of numerator
;;                            -- subtract divisor
;;    if(T >= 0)              -- if the difference is positive 
;;      R = T & 0xFFFFFFFF    ---- remainder = T        
;;      N = N << 1 + 1        ---- shift numerator up and add 1 (quotient)
;;    else                    -- else                  
;;      R = (R << 1) + N(i)   ---- shift up remainder, tack on MSb of numerator
;;      N = N << 1            ---- shift up numerator 
;;    end
;; endloop                    -- after 32 such iterations N has the quotient
;;                            -- and R the remainder
;; if(rem != 0)F.ZI = 0
;; if(F.TF == 1 && F.ZI==0), 
;;  Q += 1                    -- The quotient is in the variable that 
;;  R  = D - R                -- previously held the numerator
;; if(F.TF == 1) Q = -Q
;; if(F.NI ^ F.TF) R = -R     -- In module division remainder follows the 
;;                            -- sign of the divisor
;; Register Usage:
;;   R1H : dividend (quotient)
;;   R2H : remainder
;;   R3H : divisor 
;;   XAR4: pointer to dividend (numerator) and subsequently remainders 
;;   XAR5: pointer to divisor (denominator) and subsequently quotient 
;; 
;; cycles = 4(call) + 14(body) + 4(return)
;;        = 22
;;*****************************************************************************
    .page
    .if __TI_EABI__
    .asg    FID_i32byi32_m, _FID_i32byi32_m
    .endif
    .global _FID_i32byi32_m
    .sect   ".text"
_FID_i32byi32_m:
    .asmfunc
    MOV32        R1H, *+XAR4[0] ; R1H = dividend
    MOV32        R3H, *+XAR5[0] ; R3H = divisor
    ABSI32DIV32  R2H, R1H, R3H
    .asg    1, N
    .loop
    SUBC4UI32    R2H, R1H, R3H   
    .break  N == 8 
    .eval   N + 1, N
    .endloop
    MNEGI32DIV32 R1H, R2H, R3H
    MOV32        *+XAR5[0], R1H  ; Save quotient
    MOV32        *+XAR4[0], R2H  ; Save remainder
    LRETR
    .unasg  N
    .endasmfunc
    

;;*****************************************************************************
;; Euclidean Division
;;
;;    F.TF = sign(num) ^ sign(den)
;;    F.NI = sign(num)
;;    N = |N| , D = |D|
;;    R = 0 -- start with a remainder of 0
;; loop i = 31:-1:0
;;    T = (R << 1) + N(i) - D -- shift up remainder, tack on MSb of numerator
;;                            -- subtract divisor
;;    if(T >= 0)              -- if the difference is positive 
;;      R = T & 0xFFFFFFFF    ---- remainder = T        
;;      N = N << 1 + 1        ---- shift numerator up and add 1 (quotient)
;;    else                    -- else                  
;;      R = (R << 1) + N(i)   ---- shift up remainder, tack on MSb of numerator
;;      N = N << 1            ---- shift up numerator 
;;    end
;; endloop                    -- after 32 such iterations N has the quotient
;;                            -- and R the remainder
;; if(rem != 0)F.ZI = 0
;; if(F.NI == 1 && F.ZI==0), 
;;  Q += 1                    -- The quotient is in the variable that 
;;  R  = D - R                -- previously held the numerator
;; if(F.TF == 1) Q = -Q       -- In euclidean division remainder is always 
;;                            -- positive
;; Register Usage:
;;   R1H : dividend (quotient)
;;   R2H : remainder
;;   R3H : divisor 
;;   XAR4: pointer to dividend (numerator) and subsequently remainders 
;;   XAR5: pointer to divisor (denominator) and subsequently quotient 
;; 
;; cycles = 4(call) + 14(body) + 4(return)
;;        = 22
;;*****************************************************************************
    .page
    .if __TI_EABI__
    .asg    FID_i32byi32_e, _FID_i32byi32_e
    .endif
    .global _FID_i32byi32_e
    .sect   ".text"
_FID_i32byi32_e:
    .asmfunc
    MOV32        R1H, *+XAR4[0] ; R1H = dividend
    MOV32        R3H, *+XAR5[0] ; R3H = divisor
    ABSI32DIV32  R2H, R1H, R3H
    .asg    1, N
    .loop
    SUBC4UI32    R2H, R1H, R3H   
    .break  N == 8 
    .eval   N + 1, N
    .endloop
    ENEGI32DIV32 R1H, R2H, R3H
    MOV32        *+XAR5[0], R1H  ; Save quotient
    MOV32        *+XAR4[0], R2H  ; Save remainder
    LRETR
    .unasg  N
    .endasmfunc
;; End of File
