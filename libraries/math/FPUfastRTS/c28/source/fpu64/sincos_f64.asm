;;#############################################################################
;;! \file source/fpu64/sincos_f64.asm
;;!
;;! \brief  Fast sincos function for the C28x + FPU64
;;! \author Vishal Coelho   
;;! \date   02/29/2016
;;
;;+---------------------------------------------------------------------------+
;;| DATE   | AUTHOR | CHANGE                                                  |
;;+---------------------------------------------------------------------------+
;;| 170213 | V.C.   | Using 5 term taylor series expansion for better error   |
;;|        |        | tolerance                                               |
;;+---------------------------------------------------------------------------+
;;
;; DESCRIPTION:
;;
;;   This function computes a 64-bit floating point sin and cos given a
;;   radian input.  This function uses the FPU math tables to
;;   compute the values.  
;;
;; FUNCTIONS:
;;
;;  void sincos(float64u_t radian, float64u_t* PtrSin, float64u_t* PtrCos) 
;;  
;; ASSUMPTIONS:
;;
;;     * FPU64sinTable and FPU64cosTable are linked into the project.
;;     * angle is in radians
;;
;; ALGORITHM:
;;
;;       The sin and cos values are calculated as follows:
;;
;;       1) The offset into a 512 entry sin/cos table is calculated:
;;
;;          k = 0x1FF & (int(angle*512/(2*pi)))
;;
;;
;;       2) The fractional component between table samples is
;;          calculated:
;;
;;          x = fract(angle*512/2*pi) * (2*pi)/512
;;
;;       3) The output sine value is calculated as follows:
;;
;;          sin(Radian) = S(k) + x*( 1.0*C(k)               + 
;;                               x*(-0.5*S(k)               + 
;;                               x*(-0.166666666666667*C(k) + 
;;                               x*( 0.041666666666667*S(k) + 
;;                               x*( 0.008333333333333*C(k))))));
;;          cos(Radian) = C(k) + x*(-1.0*S(k)               + 
;;                               x*(-0.5*C(k)               + 
;;                               x*( 0.166666666666667*S(k) + 
;;                               x*( 0.041666666666667*C(k) + 
;;                               x*(-0.008333333333333*S(k))))));
;;
;;          where  S(k) = Sin table value at offset "k"
;;                 C(k) = Cos table value at offset "k"
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
    .cdecls C, LIST, "fastrts.h"

;; external references
    .if __TI_EABI__
    .asg    FPU64sinTable, _FPU64sinTable
    .asg    FPU64cosTable, _FPU64cosTable
    .asg    FPU64sincos_TABLE_SIZE_O_TWOPI, _FPU64sincos_TABLE_SIZE_O_TWOPI
    .asg    FPU64sincos_TWOPI_O_TABLE_SIZE, _FPU64sincos_TWOPI_O_TABLE_SIZE
    .asg    FPU64sincos_Coef1, _FPU64sincos_Coef1
    .asg    FPU64sincos_Coef2, _FPU64sincos_Coef2
    .asg    FPU64sincos_Coef3, _FPU64sincos_Coef3
    .asg    FPU64sincos_Coef4, _FPU64sincos_Coef4
    .asg    sincos, _sincosl
    .endif
    .ref    _FPU64sinTable
    .ref    _FPU64cosTable
    .ref    _FPU64sincos_TABLE_SIZE_O_TWOPI
    .ref    _FPU64sincos_TWOPI_O_TABLE_SIZE
    .ref    _FPU64sincos_Coef1
    .ref    _FPU64sincos_Coef2
    .ref    _FPU64sincos_Coef3
    .ref    _FPU64sincos_Coef4
;;*****************************************************************************
;; void sincos(long double angle, long double *sinptr, long double *cosptr)
;; Register Usage:
;;    AR0 : index into the sin/cos tables
;;   XAR1 : points to the head of the cosine table
;;   XAR2 : points to the head of the cosine table + 2
;;   XAR4 : points to the sine of the angle
;;   XAR5 : points to the cosine of the angle
;;   XAR6 : points to the head of the sine table
;;   XAR7 : points to the head of the sine table + 2
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- R4H                              (SP-2)
;;   |_______|<- XAR2                             (SP-4)
;;   |_______|<- XAR1                             (SP-6)
;;   |_______|<- rpc calling function             (SP-8)
;;
;;*****************************************************************************
    .page
    .global   _sincosl
    .sect     ".text"
_sincosl:     .asmfunc             ; R0 = angle (on entry)
    .asg      XAR1, P_COS_L
    .asg      XAR2, P_COS_H
    .asg      XAR6, P_SIN_L
    .asg      XAR7, P_SIN_H
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    PUSH      XAR1
    PUSH      XAR2
;;-----------------------------------------------------------------------------
;; sincos
;;-----------------------------------------------------------------------------
    .if CONVERT_F32_TO_F64 == 1
    F32TOF64  R0, R0H              ; convert argument to double precision
    .endif
    MOVW      DP,  #_FPU64sincos_TABLE_SIZE_O_TWOPI
    ; R1 = 512/(2*pi) = 512/6.283185307179586 
    ;                 = 81.487330863050417    
    ;                 = 0x40545f306dc9c883    
    MOV32     R1L, @_FPU64sincos_TABLE_SIZE_O_TWOPI
    MOV32     R1H, @_FPU64sincos_TABLE_SIZE_O_TWOPI + 2
       
    MPYF64    R0, R0, R1           ; *|     R0 = angle * 512/(2*pi)
 || MOV32     *SP++, R4H           ;  | Save R4H to the stack
    MOV32     R2L, @_FPU64sincos_TWOPI_O_TABLE_SIZE
                                   ; 1|     R2 = (2*pi)/512
                                   ;  |        = 0.012271846303085
                                   ; 2|        = 0x3f8921fb54442d18
    MOV32     R2H, @_FPU64sincos_TWOPI_O_TABLE_SIZE + 2
    F64TOI64  R1, R0               ; *|     R1 = int(angle * 512/(2*pi))
    MOV32     *SP++, R5H           ; 1| Save R5H to the stack
    MOVL      P_COS_L, #_FPU64cosTable
    MOVL      P_COS_H, #_FPU64cosTable+2
    MOVL      P_SIN_L, #_FPU64sinTable
    MOVL      P_SIN_H, #_FPU64sinTable+2
    MOV32     ACC, R1L             ; ACC = int(angle *512/(2*pi))
    AND       @AL, #0x1FF
    LSL       AL, #2
    MOVZ      AR0,@AL              ; AR0 = Index into "sin/cos" table = k
    FRACF64   R0, R0               ; *|     R0 = fract(angle*512/(2*pi))
                                   ; 1|     R1 = 8.3333333333333e-3 
                                   ;           = 0x3f81111111111111
    MOV32     R1L, @_FPU64sincos_Coef4
    MOV32     R1H, @_FPU64sincos_Coef4 + 2
      
    ; R0 = x = frac(angle*512/(2*pi)) * (2*pi)/512 
    MPYF64    R0, R0, R2           ; *| 
 || MOV32     R3L, *+P_COS_L[AR0]  ;  |     R3 = C(k)  
    MOV32     R3H, *+P_COS_H[AR0]  ; 1|     
    MPYF64    R2, R1, R3           ; 2|*|   R2 = 8.3333333333333e-3*C(k)
 || MOV32     R4L, *+P_SIN_L[AR0]  ;  | |   R4 = S(k)
    MOV32     R4H, *+P_SIN_H[AR0]  ;  |1|   
    MPYF64    R1, R1, R4           ; *|2|   R1 = 8.3333333333333e-3*S(k)
 || MOV32     R5L, @_FPU64sincos_Coef3
                                   ;  | |   R5 = 4.1666666666666e-2
                                   ;  | |      = 0x3fa5555555555555
    MPYF64    R2, R0, R2           ; 1|*|   R2 = x*8.3333333333333e-3*C(k)
 || MOV32     R5H, @_FPU64sincos_Coef3 + 2
    MPYF64    R4, R5, R4           ; 2|1|*| R4 = 0.041666666666667*S(k)
    MPYF64    R3, R5, R3           ; *|2|1| R3 = 4.1666666666666e-2*C(k)
 || MOV32     R5L, @_FPU64sincos_Coef2
                                   ;  | |   R5 = 0.166666666666667
                                   ;  | |      = 0x3fc5555555555555
    MPYF64    R1, R0, R1           ; 1|*|2| R1 = x*8.3333333333333e-3*S(k)
 || MOV32     R5H, @_FPU64sincos_Coef2 + 2
    ; R2 = 0.041666666666667*S(k) + x*8.3333333333333e-3*C(k)
    ADDF64    R2, R4, R2           ; 2|1|*| 
 || MOV32     R4L, *+P_COS_L[AR0]  ;  | | | R4 = C(k)
    MOV32     R4H, *+P_COS_H[AR0]  ;  |2|1|
    ; R1 = 4.1666666666666e-2*C(k)- x*8.3333333333333e-3*S(k)
    SUBF64    R1, R3, R1           ; *| |2| 
    MPYF64    R3, R5, R4           ; 1|*| | R3 = 0.166666666666667*C(k)
 || MOV32     R4L, *+P_SIN_L[AR0]  ;  | | | R4 = S(k)
    ; R2 = x*(0.041666666666667*S(k) + x*8.3333333333333e-3*C(k))
    MPYF64    R2, R0, R2           ; 2|1|*|
 || MOV32     R4H, *+P_SIN_H[AR0]  ;  | | |
    MPYF64    R4, R4, R5           ; *|2|1| R4 = 0.166666666666667*S(k)
 || MOV32     R5L, @_FPU64sincos_Coef1
                                   ;  | | | R5 = 0.5
                                   ;  | | |    = 0x3fe0000000000000
    ; R1 = x*(4.1666666666666e-2*C(k)- x*8.3333333333333e-3*S(k))
    MPYF64    R1, R0, R1           ; 1|*|2| 
 || MOV32     R5H, @_FPU64sincos_Coef1 + 2
    ; R2 = -0.166666666666667*C(k) + x*(0.041666666666667*S(k)
    ;                              + x*8.3333333333333e-3*C(k))
    SUBF64    R2, R2, R3           ; 2|1|*| 
 || MOV32     R3L, *+P_SIN_L[AR0]  ;  | | | R3 = S(k)
    MOV32     R3H, *+P_SIN_H[AR0]  ;  |2|1| 
    ; R1 = 0.166666666666667*S(k) + x*(4.1666666666666e-2*C(k) 
    ;                             - x*8.3333333333333e-3*S(k))
    ADDF64    R1, R4, R1           ; *| |2|
 || MPYF64    R3, R5, R3           ;  | | | R3 = 0.5*S(k)
    ; R2 = x*(-0.166666666666667*C(k) + x*(0.041666666666667*S(k)
    ;                                 + x*8.3333333333333e-3*C(k)))
    MPYF64    R2, R0, R2           ; 1|*| | 
 || MOV32     R4L, *+P_COS_L[AR0]  ;  | | | R4 = C(k)
    MOV32     R4H, *+P_COS_H[AR0]  ; 2|1| |
    ; R1 = x*(0.166666666666667*S(k) + x*(4.1666666666666e-2*C(k) 
    ;                                - x*8.3333333333333e-3*S(k)))
    MPYF64    R1, R0, R1           ; *|2| |
    ; R2 = -0.5*S(k) + x*(-0.166666666666667*C(k)
    ;                + x*(0.041666666666667*S(k) 
    ;                + x*8.3333333333333e-3*C(k)))
    SUBF64    R2, R2, R3           ; 1|*| | 
 || MPYF64    R4, R4, R5           ;  | | | R4 = 0.5*C(k)
    MOV32     R3L, *+P_COS_L[AR0]  ; 2|1| | R3 = C(k)
    MOV32     R3H, *+P_COS_H[AR0]  ;  |2| | 
    ; R1 = -0.5*C(k) + x*(0.166666666666667*S(k) 
    ;                + x*(4.1666666666666e-2*C(k) 
    ;                - x*8.3333333333333e-3*S(k)))
    ; R2 = x*(-0.5*S(k) + x*(-0.166666666666667*C(k)
    ;                   + x*(0.041666666666667*S(k) 
    ;                   + x*8.3333333333333e-3*C(k))))
    SUBF64    R1, R1, R4           ; *| | | 
 || MPYF64    R2, R0, R2           ;  | | | 
    MOV32     R4L, *+P_SIN_L[AR0]  ; 1| | | R4 = S(k)
    MOV32     R4H, *+P_SIN_H[AR0]  ; 2| | |
    ; R1 = x*(-0.5*C(k) + x*(0.166666666666667*S(k) 
    ;                   + x*(4.1666666666666e-2*C(k) 
    ;                   - x*8.3333333333333e-3*S(k))))  
    ; R2 = C(k) + x*(-0.5*S(k) + x*(-0.166666666666667*C(k)
    ;                          + x*(0.041666666666667*S(k) 
    ;                          + x*8.3333333333333e-3*C(k))))    
    MPYF64    R1, R0, R1           ; *| | | 
 || ADDF64    R2, R3, R2           ;  | | | 
    MOV32     R5H, *--SP           ; 1| | | restore R5H
    NOP                            ; 2| | |
    ; R1 = -S(k) + x*(-0.5*C(k) + x*(0.166666666666667*S(k) 
    ;                           + x*(4.1666666666666e-2*C(k) 
    ;                           - x*8.3333333333333e-3*S(k)))) 
    ; R2 = x*(C(k) + x*(-0.5*S(k) + x*(-0.166666666666667*C(k)
    ;                             + x*(0.041666666666667*S(k) 
    ;                             + x*8.3333333333333e-3*C(k)))))
    SUBF64    R1, R1, R4           ; *| | | 
 || MPYF64    R2, R0, R2           ;  | | | 
    NOP                            ; 1| | |
    NOP                            ; 2| | |
    ; R2 = S(k) + x*(1.0*C(k) 
    ;           + x*(-0.5*S(k) 
    ;           + x*(-0.166666666666667*C(k)
    ;           + x*(0.041666666666667*S(k) 
    ;           + x*8.3333333333333e-3*C(k)))))
    ; R1 = x*(-S(k) + x*(-0.5*C(k) + x*(0.166666666666667*S(k) 
    ;                              + x*(4.1666666666666e-2*C(k) 
    ;                              - x*8.3333333333333e-3*S(k)))))
    ADDF64    R2, R4, R2           ; *| | | 
 || MPYF64    R1, R0, R1           ;  | | | 
    MOV32     *--SP, R4H           ; 1| | | restore R4H
    POP       XAR2                 ; 2| | | restore XAR2
    ; R1 = C(k) + x*(-1.0*S(k) 
    ;           + x*(-0.5*C(k) 
    ;           + x*(0.166666666666667*S(k) 
    ;           + x*(4.1666666666666e-2*C(k) 
    ;           - x*8.3333333333333e-3*S(k)))))
    ADDF64    R1, R3, R1           ; *| | | 
 || MOV32     *+XAR4[0], R2L       ;  | | |  Save sin(angle) to memory
    MOV32     *+XAR4[2], R2H       ; 1| | |
    POP       XAR1                 ; 2| | | restore XAR1
    MOV32     *+XAR5[0], R1L       ;  | | |  Save cos(angle) to memory
    MOV32     *+XAR5[2], R1H       ;  | | |
    LRETR     
    .unasg    P_COS_L
    .unasg    P_COS_H
    .unasg    P_SIN_L
    .unasg    P_SIN_H    
    .endasmfunc

;;*****************************************************************************
;; This function will run the function above taking the address of the input  
;; and output as arguments         
;; 
;; Register Usage:
;;   XAR4 : points to the input angle (in radians)
;;   XAR5 : points to the sine of the angle
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- rpc calling function             (SP-2)
;;   |_______|<- pointer to the cos(angle)        (SP-4)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg    run_sincos, _run_sincos
    .endif
    .global _run_sincos
    .sect   ".text"
_run_sincos:   .asmfunc
    MOV32   R0L, *+XAR4[0]
    MOV32   R0H, *+XAR4[2]
    MOVL    XAR4, XAR5
    MOVL    XAR5, *-SP[4]
    LCR     #_sincosl
    LRETR
    .endasmfunc
;; End of File
