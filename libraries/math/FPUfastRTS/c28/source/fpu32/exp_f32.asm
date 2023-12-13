;;#############################################################################
;;! \file source/fpu32/exp_f32.asm
;;!
;;! \brief  Fast single precision exponent for the C28x + FPU32
;;! \author Vishal Coelho   
;;! \date   01/19/2017
;;
;; DESCRIPTION:
;;
;;   This function computes the 32-bit floating point exp(x)
;;
;; FUNCTIONS:
;;
;;   This funciton will be called whenever the standard C library function
;;   exp() is called.
;;   
;;   float32 X,Y;
;;   ...
;;   <X initalized>
;;   ...
;;   Y = expf(X); 
;;  
;; ASSUMPTIONS:
;;
;; ALGORITHM:
;;
;; 1. calculate the absolute of x, |x|
;; 2. Separate the integer and fractional portion of the input
;; 3. Get e^integer(x) from the table
;; 4. Calculate e^(fraction) by using the Taylor series expansion for
;;    exponents
;;      x
;;    e   = 1 + x*(1+x/2*(1+x/3*(1+x/4*(1+x/5*(1+x/6*(1+x/7)+...)))))
;;    
;; 5. The result,  $e^{x} = e^{integer}*e^{fraction}$
;; 6. If x was negative, calculate the inverse of the result
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


;; external references
    .if __TI_EABI__
    .asg    expf, _exp
    .asg    FPU32expTable, _FPU32expTable
    .asg    FPU32expTableCoeff, _FPU32expTableCoeff
    .endif
    
    .ref    _FPU32expTable
    .ref    _FPU32expTableCoeff
    
;;*****************************************************************************
;; Register Usage:
;;   XAR0: pointer to the lookup table        | R0H : x, argument
;;   XAR1: pointer to the exp coeffs          | R1H : x_f
;;   XAR2: storing the lookup tabe index      | R2H :
;;                                            | R3H :
;;                                            | R4H : x_i, index into lookup table
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- R4H                              (SP-2)
;;   |_______|<- rpc calling function             (SP-4)
;;
;;*****************************************************************************
    .page
    .global _exp
    .sect   ".text"
    .if (__TI_EABI__ = 0)
    ; For TI COFF double and float are the same size, so expf() and 
    ; exp() should be the same function
    .global _expf
_expf:
    .endif
_exp:   .asmfunc
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    MOV32   	*SP++,R4H
	; [20200310] these two instructions added to protect XAR1 & XAR2
    PUSH		XAR1
    PUSH		XAR2
;;-----------------------------------------------------------------------------
;; The algorithm
;;-----------------------------------------------------------------------------
	MOV32		R4H, R0H			;      R4H = x   (may set ZF, NF)
    TESTTF      LT                  ;      (x < 0.0)? TF = 1: TF = 0
    ABSF32      R4H, R0H            ;      R4H = |x|
    FRACF32     R1H, R4H            ; *|   R1H = frac(|x|) or x_f
    MOVL        XAR1, #_FPU32expTableCoeff
                                    ; 1|   XAR1 -> FPU32expTableCoeff[0]
    MOV32       R2H, *XAR1++        ;      R2H = 1/7
    MPYF32      R2H, R2H, R1H       ; *|   R2H = x_f/7
 || MOV32       R3H, *XAR1++        ;  |   R3H = 1/6
    MPYF32      R3H, R1H, R3H       ; 1|*| R3H = x_f/6
 || MOV32       R0H, *XAR1++        ;  | | R0H = 1/5
    ADDF32      R2H, #1.0, R2H      ; *|1| R2H = 1+x_f/7
    MPYF32      R4H, #2.0, R4H      ; 1|*| R4H = 2*x_i
    MPYF32      R2H, R3H, R2H       ; *|1| R2H = x_f/6*(1+x_f/7)
    MPYF32      R0H, R1H, R0H       ; 1|*| R0H = x_f/5
 || MOV32       R3H, *XAR1++        ;  | | R3H = 1/4
    ADDF32      R2H, #1.0, R2H      ; *|1| R2H = 1+x_f/6*(1+x_f/7)  
    F32TOI32    R4H, R4H            ; 1|*| R4H = 2*x_i
    MPYF32      R2H, R0H, R2H       ; *|1| R2H = x_f/5*(1+x_f/6*(1+x_f/7))
    MPYF32      R3H, R1H, R3H       ; 1|*| R3H = x_f/4
 || MOV32       R0H, *XAR1++        ;  | | R0H = 1/3
    ADDF32      R2H, #1.0, R2H      ; *|1| R2H = 1+x_f/5*(1+x_f/6*(1+x_f/7))
    MOV32       XAR2, R4H            ; 1|   XAR2 = sizeof(float)*x_i
    MOVL        XAR0, #_FPU32expTable   ; 1|   XAR0 -> FPU32expTable[0]
    ; R2H = x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7)))
    MPYF32      R2H, R3H, R2H       ; *|   
    MPYF32      R0H, R1H, R0H       ; 1|*| R0H = x_f/3
    ; R2H = 1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7)))
    ADDF32      R2H, #1.0, R2H      ; *|1| 
    MOV32       R3H, *XAR1++        ; 1|   R3H = 1/2
    ;  R2H = x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7))))
    MPYF32      R2H, R0H, R2H       ; *|
    MPYF32      R3H, R1H, R3H       ; 1|*| R3H = x_f/2
    ; R2H = 1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7))))
    MOVL        ACC, XAR0                  ; *|1|
    ADDF32      R2H, #1.0, R2H      ; *|1| 
    ADDL         ACC, @XAR2  ; 1|   ACC->FPU32expTable[x_i]
    ; R2H = x_f/2*(1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7)))))
    MPYF32      R2H, R3H, R2H       ; *|   
    MOVL        XAR0, ACC           ; 1|   XAR0->FPU32expTable[x_i]
    ; R2H = 1+x_f/2*(1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7)))))
    ADDF32      R2H, #1.0, R2H      ; *|
	; [20200310] these two instructions added to protect XAR1 & XAR2
    POP			XAR2	          	; 1|   restore XAR2
    POP			XAR1	          	; 1|   restore XAR1
    MOV32       R4H, *--SP          ; 1|   restore R4H
    ; R2H = x_f*(1+x_f/2*(1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7))))))
    MPYF32      R2H, R1H, R2H       ; *|
    MOV32       R1H, *XAR0          ; 1|   R1H = FPU32expTable[x_i]
    ; R2H = 1+x_f*(1+x_f/2*(1+x_f/3*(1+x_f/4*(1+x_f/5*(1+x_f/6*(1+x_f/7))))))
    ADDF32      R2H, #1.0, R2H      ; *|
    NOP                             ; 1|
    MPYF32      R2H, R1H, R2H       ; *|   R2H = e^x =  e^(x_i)*e^(x_f)
    NOP                             ; 1|   
    EINVF32     R1H, R2H            ; *|   R1H = Ye = 1/e^x
    NOP                             ; 1|   
    MPYF32      R3H, R1H, R2H       ; *|   R3H = Ye*e^x
    NOP                             ; 1|   
    SUBF32      R3H, #2.0, R3H      ; *|   R3H = 2.0 - Ye*e^x
    NOP                             ; 1|   
    MPYF32      R1H, R1H, R3H       ; *|   R1H = Yee = Ye*(2.0 - Ye*e^x)
    NOP                             ; 1|   
    MPYF32      R3H, R1H, R2H       ; *|   R3H = Yee*e^x
    NOP                             ; 1|   
    SUBF32      R3H, #2.0, R3H      ; *|   R3H = 2.0 - Yee*e^x
    NOP                             ; 1|   
    MPYF32      R0H, R1H, R3H       ; *|   R0H = Yeee = Yee*(2.0-Yee*e^x)
    NOP                             ; 1|
    MOV32       R0H, R2H, NTF       ;  |   R0H = e^x if TF = 0
    LRETR
    .endasmfunc

    
;; End of File
