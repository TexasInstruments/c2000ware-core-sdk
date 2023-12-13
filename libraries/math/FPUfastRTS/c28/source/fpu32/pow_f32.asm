;;#############################################################################
;;! \file source/fpu32/pow_f32.asm
;;!
;;! \brief  Fast single precision power function for the C28x + FPU32
;;! \author Vishal Coelho   
;;! \date   02/07/2017
;;
;; DESCRIPTION:
;;
;;   This function computes the 32-bit floating point power, powf(x, y)
;;
;; FUNCTIONS:
;;
;;   This funciton will be called whenever the standard C library function
;;   powf() is called.
;;   
;;   float32 X,Y,Z;
;;   ...
;;   <X & Y initalized>
;;   ...
;;   Z = powf(X, Y); 
;;  
;; ASSUMPTIONS:
;;
;; ALGORITHM:
;;
;; We calculate x^y as exp(y*log(x))
;;
;;  1. calculate the absolute of x, |x|
;;  2. A floating point number is represented as X=[S]1.M*2^E where S is the 
;;     sign bit, M the mantissa, and E the biased exponent. The natural
;;     logarithm of such a number is given by
;;  
;;       log(X) = log(1.M) + E*log(2)$$
;;  
;;  3. Separate the exponent of the input, store it as a float.
;;  4. Separate the mantissa (1.M), and then the fractional portion Xm = M
;;  5. Subtract the bias from the exponent and multiply by log(2)
;;  6. Calculate log(1.M) using the polynomial approximation 
;;  
;;       log(1 + M) = a0 + M*(a1 + M*a2)$$
;;  
;;  7. The result is $x' = log(1+M) + E*log(2)$, where E is now the unbiased exponent
;;  8. calculate the absolute of x', |x'|
;;  9. Separate the integer and fractional portion of the input
;; 10. Get e^integer(x') from the table
;; 11. Calculate e^(fraction) by using the Taylor series expansion for
;;     exponents
;;       x
;;     e   = 1 + x*(1+x/2*(1+x/3*(1+x/4*(1+x/5*(1+x/6*(1+x/7)+...)))))
;;    
;; 12. The result,  $e^{x'} = e^{integer}*e^{fraction}$
;; 13. If x' was negative, calculate the inverse of the result
;;
;;  Group:            C2000
;;  Target Family:    C28x+FPU32
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


;; external references
    .if __TI_EABI__
    .asg    FPU32LOG2, _FPU32LOG2
    .asg    FPU32logTable, _FPU32logTable
    .asg    FPU32expTable, _FPU32expTable
    .asg    FPU32expTableCoeff, _FPU32expTableCoeff
    .asg    powf, _pow
    .endif
    .ref    _FPU32logTable
    .ref    _FPU32LOG2
    .ref    _FPU32expTable
    .ref    _FPU32expTableCoeff
    
;;*****************************************************************************
;; Register Usage:
;;   XAR0: pointer to the lookup table | R0H : x, base
;;   XAR1: pointer to the exp coeffs   | R1H : y, exponent
;;   XAR2: storing the lookup tabe index
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- LF_X_EXP_U                       (SP-1)-----> Local Frame
;;   |_______|<- LF_ABS_X_H                       (SP-2)    |
;;   |_______|<- LF_ABS_X_L|LF_ABS_X|LF_X_MANT    (SP-3)----
;;   |_______|<- R4H                              (SP-5)
;;   |_______|<- rpc calling function             (SP-7)
;;
;;*****************************************************************************
    .page
    .global _pow
    .sect   ".text"
    
LOG_TBL_SZ  .set    0x4200  ;32(entries)
    
    .if (__TI_EABI__ = 0)
    ; For TI COFF double and float are the same size, so powf() and 
    ; pow() should be the same function
    .global _powf
_powf:
    .endif
_pow:   
    .asmfunc
    .asg          3, LF_SIZE
	.asg    *-SP[1], LF_X_EXP_U
    .asg    *-SP[2], LF_ABS_X_H
    .asg    *-SP[3], LF_ABS_X_L
    .asg    *-SP[3], LF_ABS_X
    .asg    *-SP[3], LF_X_MANT

;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    ; The stack pointer is aligned to an even address by the calling function
    MOV32   	*SP++,R4H
	; [20200310] these two instructions added to protect XAR1 & XAR2
    PUSH		XAR1
    PUSH		XAR2
    ADDB        SP, #LF_SIZE        
;;-----------------------------------------------------------------------------
;; The log(x) algorithm
;;-----------------------------------------------------------------------------
    MOV32       R4H, R1H             ; save y
    MOV32       LF_ABS_X, R0H        ;
    ;-----PIPELINE STALL=3 CYC-------;
    MOV         ACC, LF_ABS_X_H << 9 ; AH = x.exp
    SUB         AH, #127             ;    = x.exp - SP_BIAS

    ;; ANDing the argument with 0x3FFFFFFF will zero out the sign bit, which 
    ;; is equivalent to doing the absolute operation, and the most significant 
    ;; exponent bit while ORing with 0x3F800000 will set the exponent to 
    ;; 127 (single) or 1023 (double)
    ;;
    ;; Consider 10 = 1.25x2^3. In single precision float the leading 1 of the 
    ;; significand is implicit and the exponent is biased around 127, so its 
    ;; physical representation is 
    ;;   31|30           23|22                                        0|
    ;;   +-+---------------+-------------------------------------------+
    ;;   |0|1|0|0|0|0|0|1|0|0|1|0                 ...........         0|
    ;;   +-+---------------+-------------------------------------------+
    ;;    S| biased exp    | mantissa                                  |
    ;;     | E = 127+3=131 | 0.25                                      |
    ;;
    ;; X & 0x3FFFFFFF
    ;;   31|30           23|22                                        0|
    ;;   +-+---------------+-------------------------------------------+
    ;;   |0|0|0|0|0|0|0|1|0|0|1|0                 ...........         0|
    ;;   +-+---------------+-------------------------------------------+
    ;;    S| biased exp    | mantissa                                  |
    ;;     | E = 2         | 0.25                                      |
    ;; (X & 0x3FFFFFFF) | 0x3F800000
    ;;   31|30           23|22                                        0|
    ;;   +-+---------------+-------------------------------------------+
    ;;   |0|0|1|1|1|1|1|1|1|0|1|0                 ...........         0|
    ;;   +-+---------------+-------------------------------------------+
    ;;    S| biased exp    | mantissa                                  |
    ;;     | E = 127       | 0.25                                      |    
    ;; Now the value of this float (after removing exponent bias)
    ;;   = 1.25 * 2^(127-127(BIAS)) = 1.25
    ;; We have extracted just the mantissa (or significand)
    AND         LF_ABS_X_H, #0x3FFF  ; (x&0x3FFFFFFF)|0x3F800000
    OR          LF_ABS_X_H, #0x3F80  
    ;-----PIPELINE STALL=3 CYC-------;
    MOV32       R0H, LF_X_MANT       ;     R0H = |x|.mant
    FRACF32     R0H, R0H             ; *|      = frac(|x|.mant) or Xm
    MOV         LF_X_EXP_U, AH       ; 1|
    MPYF32      R2H, R0H, #LOG_TBL_SZ
                                     ; *|   R2H = |x|.mant*TBL_SZ*3*szof(float)
    I16TOF32    R1H, LF_X_EXP_U      ; 1|*| R1H = exp_unbiased
    F32TOUI16   R2H, R2H             ; *|1| R2H = (int)(Xm*32.0)
    MOVW		DP, #_FPU32LOG2		 ; 1|
	MOV16		LF_X_MANT, R2H	     ;
    MOV			AL, #_FPU32logTable+6
    .if __TI_EABI__
    ;; The assembler does the addition of FPU32logTable and 6 prior to
    ;; taking the high word
    MOV			AH, #$HI16(FPU32logTable)+6
    .else
	MOV			AH, #((_FPU32logTable+6)>>16)
	.endif
	ADD			ACC, LF_X_MANT << #2 ;      ACC += 4*(int)(Xm*32.0)
	ADD			ACC, LF_X_MANT << #1 ;          += 2*(int)(Xm*32.0)
									 ;      ACC  -> FPU32logTable[idx].A2+2
    MOVL	    XAR0, ACC			 ;      XAR0 -> FPU32logTable[idx].A2+2
    MOV32       R2H, *--XAR0         ;      R2H = A2
    MPYF32      R3H, R0H, R2H        ; *|   R3H = Xm*A2
    MOV32       R2H, *--XAR0         ; 1|   R2H = A1
	ADDF32      R3H, R2H, R3H        ; *|   R3H = A1 + Xm*A2
    MOV32       R2H, @_FPU32LOG2       ; 1|   R2H = log(2)
    MPYF32      R3H, R0H, R3H        ; *|   R3H = Xm*(A1+Xm*A2)
 || MOV32       R0H, *--XAR0         ;  |   R0H = A0
    MPYF32      R1H, R2H, R1H        ; 1|*| R1H = log(2)*exp_unbiased
    ADDF32      R3H, R0H, R3H        ; *|1| R3H = A0 + Xm*(A1+Xm*A2)
    SUBB        SP, #LF_SIZE         ; 1|   deallocate local frame
    ADDF32      R0H, R1H, R3H        ; *|   R0H = log_exp+log_mant   
    NOP                              ; 1|
;;-----------------------------------------------------------------------------
;; y*log(x)
;;-----------------------------------------------------------------------------    
    MPYF32      R0H, R4H, R0H        ; *|   R0H = y*log(x)
    NOP                              ; 1|
;;-----------------------------------------------------------------------------
;; The exp(y*log(x)) algorithm
;;-----------------------------------------------------------------------------
	MOV32		R4H, R0H			 ;      R4H = x   (may set ZF, NF)
    TESTTF      LT                   ;      (x < 0.0)? TF = 1: TF = 0
    ABSF32      R4H, R0H             ;      R4H = |x|
    FRACF32     R1H, R4H             ; *|   R1H = frac(|x|) or x_f
    MOVL        XAR1, #_FPU32expTableCoeff
                                     ; 1|   XAR1 -> FPU32expTableCoeff[0]
    MOV32       R2H, *XAR1++         ;      R2H = 1/7
    MPYF32      R2H, R2H, R1H        ; *|   R2H = x_f/7
 || MOV32       R3H, *XAR1++         ;  |   R3H = 1/6
    MPYF32      R3H, R1H, R3H        ; 1|*| R3H = x_f/6
 || MOV32       R0H, *XAR1++         ;  | | R0H = 1/5
    ADDF32      R2H, #1.0, R2H       ; *|1| R2H = 1+x_f/7
    MPYF32      R4H, #2.0, R4H       ; 1|*| R4H = 2*x_i
    MPYF32      R2H, R3H, R2H        ; *|1| R2H = x_f/6*(1+x_f/7)
    MPYF32      R0H, R1H, R0H        ; 1|*| R0H = x_f/5
 || MOV32       R3H, *XAR1++         ;  | | R3H = 1/4
    ADDF32      R2H, #1.0, R2H       ; *|1| R2H = 1+x_f/6*(1+x_f/7)  
    F32TOI32    R4H, R4H             ; 1|*| R4H = 2*x_i
    MPYF32      R2H, R0H, R2H        ; *|1| R2H = x_f/5*(1+x_f/6*(1+x_f/7))
    MPYF32      R3H, R1H, R3H        ; 1|*| R3H = x_f/4
 || MOV32       R0H, *XAR1++         ;  | | R0H = 1/3
    ADDF32      R2H, #1.0, R2H       ; *|1| R2H = 1+x_f/5*(1+x_f/6*(1+x_f/7))
    MOV32        XAR2, R4H            ; 1|   ACC = sizeof(float)*x_i
    MOVL        XAR0, #_FPU32expTable   ; 1|   XAR0 -> FPU32expTable[0]
    ; R2H = x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7)))
    MPYF32      R2H, R3H, R2H        ; *|   
    MPYF32      R0H, R1H, R0H        ; 1|*| R0H = x_f/3
    ; R2H = 1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7)))
    ADDF32      R2H, #1.0, R2H       ; *|1| 
    MOV32       R3H, *XAR1++         ; 1|   R3H = 1/2
    ;  R2H = x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7))))
    MPYF32      R2H, R0H, R2H        ; *|
    MPYF32      R3H, R1H, R3H        ; 1|*| R3H = x_f/2
    ; R2H = 1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7))))
    MOVL        ACC, XAR0                  ; *|1|
    ADDF32      R2H, #1.0, R2H       ; *|1| 
    ; R2H = x_f/2*(1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7)))))
    ADDL         ACC, @XAR2  ; 1|   ACC->FPU32expTable[x_i]
    MPYF32      R2H, R3H, R2H        ; *|   
    MOVL        XAR0, ACC            ; 1|   XAR0->FPU32expTable[x_i]
    ; R2H = 1+x_f/2*(1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7)))))
    ADDF32      R2H, #1.0, R2H       ; *|
	; [20200310] these two instructions added to protect XAR1 & XAR2
    POP         XAR2                 ; 1|   restore XAR2
    POP         XAR1                 ; 1|   restore XAR1
    MOV32       R4H, *--SP           ; 1|   restore R4H
    ; R2H = x_f*(1+x_f/2*(1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7))))))
    MPYF32      R2H, R1H, R2H        ; *|
    MOV32       R1H, *XAR0           ; 1|   R1H = FPU32expTable[x_i]
    ; R2H = 1+x_f*(1+x_f/2*(1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7))))))
    ADDF32      R2H, #1.0, R2H       ; *|
    NOP                              ; 1|
    MPYF32      R2H, R1H, R2H        ; *|   R2H = e^x =  e^(x_i)*e^(x_f)
    NOP                              ; 1|   
    EINVF32     R1H, R2H             ; *|   R1H = Ye = 1/e^x
    NOP                              ; 1|   
    MPYF32      R3H, R1H, R2H        ; *|   R3H = Ye*e^x
    NOP                              ; 1|   
    SUBF32      R3H, #2.0, R3H       ; *|   R3H = 2.0 - Ye*e^x
    NOP                              ; 1|   
    MPYF32      R1H, R1H, R3H        ; *|   R1H = Yee = Ye*(2.0 - Ye*e^x)
    NOP                              ; 1|   
    MPYF32      R3H, R1H, R2H        ; *|   R3H = Yee*e^x
    NOP                              ; 1|   
    SUBF32      R3H, #2.0, R3H       ; *|   R3H = 2.0 - Yee*e^x
    NOP                              ; 1|   
    MPYF32      R0H, R1H, R3H        ; *|   R0H = Yeee = Yee*(2.0-Yee*e^x)
    NOP                              ; 1|
    MOV32       R0H, R2H, NTF        ;  |   R0H = e^x if TF = 0
    LRETR
    .endasmfunc
    .unasg  LF_SIZE
	.unasg  LF_X_EXP_U
    .unasg  LF_ABS_X_H
    .unasg  LF_ABS_X_L
    .unasg  LF_ABS_X
    .unasg  LF_X_MANT   
    
;; End of File
