;;#############################################################################
;;! \file source/fpu64/atan2_f64.asm
;;!
;;! \brief  Fast arctangent2 function for the C28x + FPU64
;;! \author Vishal Coelho   
;;! \date   03/04/2016
;;
;; DESCRIPTION:
;;
;;   This function computes a 64-bit floating point arctangent given two
;;   numerical inputs.  This function uses the FPU64 math tables to
;;   compute the atan.  
;;
;; FUNCTIONS:
;;
;;  float64 atan2 (float64 Y, float64 X) 
;;  
;; ASSUMPTIONS:
;;
;;     * FPU64atan2Table is linked into the project.
;;
;; ALGORITHM:
;;   Step(1):   if( abs(X) >= abs(Y) )
;;                  Numerator   = abs(Y)
;;                  Denominator = abs(X)
;;              else
;;                  Numerator   = abs(X)
;;                  Denominator = abs(Y)
;;
;;   Step(2):   Ratio = Numerator/Denominator
;;
;;              Note: Ratio range = 0.0 to 1.0
;;
;;   Step(3):   Use the upper 6-bits of the "Ratio" value as an
;;              index into the table to obtain the coefficients
;;              for a second order equation:
;;
;;              _FPU64atan2Table:
;;                   CoeffA0[0]
;;                   CoeffA1[0]
;;                   CoeffA2[0]
;;                      .
;;                      .
;;                   CoeffA0[63]
;;                   CoeffA1[63]
;;                   CoeffA2[63]
;;
;;   Step(4):   Calculate the angle using the folowing equation:
;;
;;              arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;;              arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;;
;;   Step(5):   The final angle is determined as follows:
;;
;;              if( X >= 0 and Y >= 0 and abs(X) >= abs(Y) )
;;                  Angle = arctan(abs(Y)/abs(X))
;;              if( X >= 0 and Y >= 0 and abs(X) <  abs(Y) )
;;                  Angle = PI/2 - arctan(abs(X)/abs(Y))
;;              if( X < 0  and Y >= 0 and abs(X) <  abs(Y) )
;;                  Angle = PI/2 + arctan(abs(X)/abs(Y))
;;              if( X < 0  and Y >= 0 and abs(X) >= abs(Y) )
;;                  Angle = PI - arctan(abs(Y)/abs(X))
;;              if( Y < 0 )
;;                  Angle = -Angle
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
    .asg    FPU64atan2HalfPITable, _FPU64atan2HalfPITable
    .asg    FPU64atan2Table, _FPU64atan2Table
    .asg    atan2, _atan2l
    .endif
    .ref    _FPU64atan2HalfPITable
    .ref    _FPU64atan2Table
       
;;*****************************************************************************
;; Register Usage:
;;    AR0 : index into the arctan table
;;   XAR1 : 
;;   XAR2 : points to table entries A0.L
;;   XAR3 : points to table entries A0.H
;;   XAR4 : points to table entries A1.L
;;   XAR5 : points to table entries A1.H
;;   XAR6 : points to table entries A2.L
;;   XAR7 : points to table entries A2.H & PI/2
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- R1H                              (SP-2) ------>Local Frame
;;   |_______|<- R0H                              (SP-4) ----+
;;   |_______|<- R4H                              (SP-6)
;;   |_______|<- XAR3                             (SP-8)
;;   |_______|<- XAR2                             (SP-10)
;;   |_______|<- rpc calling function             (SP-12)
;;*****************************************************************************
    .page
    .global   _atan2l
    .sect     ".text"
_atan2l:        
    .asmfunc             
    .asg      XAR2, P_A0_L
    .asg      XAR3, P_A0_H
    .asg      XAR4, P_A1_L
    .asg      XAR5, P_A1_H
    .asg      XAR6, P_A2_L
    .asg      XAR7, P_A2_H
    .asg      XAR7, PI_O_2
    .if CONVERT_F32_TO_F64 == 1
    F32TOF64  R0, R0H             ; convert argument to double precision
    .endif
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    PUSH      XAR2
    PUSH      XAR3
    MOV32     *SP++, R4H

;;-----------------------------------------------------------------------------
;; atan2
;;-----------------------------------------------------------------------------
    ; Perform Step (1): 
    ; R0 = Y (on entry)
    ; R1 = X (on entry)
    ABSF64    R3, R0              ; R3 = abs(Y)
    ABSF64    R4, R1              ; R4 = abs(X)
    MINF64    R3, R4              ; R3 = Numerator = min(abs(Y),abs(X))
 || MOV64     R4, R3              ; R4 = Denominator = max(abs(Y),abs(X))
    ;<<VC160304 looks like a NOP is required here for EINVF64 to work properly>>
    .if       1
    NOP
    .endif
    ; Perform Step (2) and (3):
    EINVF64   R2, R4              ; *| R2 = Ye = Estimate(1/Numerator)
    TESTTF    LEQ                 ; 1| Set TF if abs(X) >= abs(Y)
    MPYF64    R0, R2, R4          ; *| R0H = Ye*B
 || MOV32     *SP++, R0H          ;  | Store Y (*-SP[4] = Y.H)
    MPYF64    R1, R2, R3          ; 1|*| R1 = 16-bit accurate estimate
 || MOV32     *SP++, R1H          ;  | | Store X (*-SP[2] = X.H)
    ; Points to A2.L                2|1|
    MOVL      P_A2_L, #_FPU64atan2Table+8
    SUBF64    R0, #2.0, R0        ; *|2| R0 = 2.0 - Ye*B
    MPYF64    R1, R1, #64.0       ; 1|*| 64 = Elements In Table
    ; Points to A2.H                2|1|
    MOVL      P_A2_H, #_FPU64atan2Table+10
    ; R2 = Ye = Ye*(2.0 - Ye*B)  (first estimate)
    MPYF64    R2, R2, R0          ; *|2| 
    ; R1H = int32_t(64*ratio) (32-bit accurate)
    F64TOUI32 R1H, R1             ; 1|*|
    ; Points to A1.L                2|1|
    MOVL      P_A1_L, #_FPU64atan2Table+4
    MPYF64    R0, R2, R4          ; *|   R0= Ye*B
    ; Points to A1.H                1|
    MOVL      P_A1_H, #_FPU64atan2Table+6
    MOV32     ACC, R1H            ; 2|   ACC = int(64*Ratio)
    SUBF64    R0, #2.0, R0        ; *|   R0 = 2.0 - Ye*B
    NOP                           ; 1|
    MPY       P, @AL, #12         ; 2|   P = 12 * int(64*Ratio)
    MPYF64    R2, R2, R0          ; *|   R2 = Ye = Ye*(2.0 - Ye*B)
    MOVZ      AR0, @PL            ; 1|   AR0 = _FPU64atan2Table index
    ; Points to A0.L                2|
    MOVL      P_A0_L, #_FPU64atan2Table
    MPYF64    R0, R2, R4          ; *|   R0= Ye*B    
    ; Points to A0.H                1|
    MOVL      P_A0_H, #_FPU64atan2Table+2
    NOP                           ; 2|
    SUBF64    R0, #2.0, R0        ; *|   R0 = 2.0 - Ye*B
    NOP                           ; 1|
    NOP                           ; 2|
    MPYF64    R2, R2, R0          ; *|   R2 = Ye = Ye*(2.0 - Ye*B)
    NOP                           ; 1|
    NOP                           ; 2|
    MPYF64    R0, R2, R4          ; *|   R0= Ye*B    
    NOP                           ; 1|
    NOP                           ; 2|
    SUBF64    R0, #2.0, R0        ; *|   R0 = 2.0 - Ye*B
    NOP                           ; 1|
    NOP                           ; 2|
    MPYF64    R2, R2, R0          ; *|   R2 = Ye = Ye*(2.0 - Ye*B)
    MOV32     R4L, *+P_A0_L[AR0]  ; 1|   R4 = A0
    MOV32     R4H, *+P_A0_H[AR0]  ; 2|
    
    MPYF64    R0, R3, R2          ; *|   R0 = Ratio = A*Ye = A/B
    ; Perform Step (4):
    ; arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
    MOV32     R1L, *+P_A2_L[AR0]  ; 1|   R1 = A2
    MOV32     R1H, *+P_A2_H[AR0]  ; 2|
    MPYF64    R3, R1, R0          ; *|   R3 = A2*Ratio
 || MOV32     R1L, *+P_A1_L[AR0]  ;  |   R1 = A1
    MOV32     R1H, *+P_A1_H[AR0]  ; 1|   
    ; *XAR7[2] == pi/2            ; 2|
    MOVL      XAR7, #_FPU64atan2HalfPITable
    ADDF64    R3, R1, R3          ; *|   R3 = A1 + A2*Ratio
    MOV32     R1L, *+PI_O_2[4]    ; 1|   R1 = pi/2 (no flag change)
    MOV32     R1H, *+PI_O_2[6]    ; 2| 
    MPYF64    R3, R0, R3          ; *|   R3 = Ratio*(A1 + A2*Ratio)
    NOP                           ; 1|
    NOP                           ; 2|
    ; R0 = arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
    ADDF64    R0, R4, R3          ; *|   
    ; <<VC160304
    ; we only care about the leading 32-bits as they contain the sign and 
    ; exponent; the sign bit will set/clear the NF while the exponent sets
    ; the ZF when its value is 0 - we dont care about a non-zero mantissa in 
    ; this case since we treat subnormal numbers as 0 anyway
    ;  VC160304>>
    MOV32     R2H, *--SP          ; 1| R2H = X.H(set/clear NF,ZF for use below)
    ; Perform Step (5):
    NEGF64    R3, R1, UNC         ; 2| R3 = -pi/2 (no flag change)
    MOV64     R0, R2, EQ          ; if(X == 0), R0 = 0
    NEGF64    R0, R0, GEQ         ; if(X >= 0) flip sign of R0(atan(Ratio))  
    NEGF64    R0, R0, TF          ; if (abs(X) >= abs(Y)) flip sign of 
                                  ; atan(Ratio)                            
    NEGF64    R3, R3, LT          ; if(X < 0) R3 = pi/2
    ADDF64    R3, R3, R1          ; *|   R3 = R3 + pi/2
                                  ;  |       if (X < 0) R3 = pi
                                  ;  |       if (X > 0) R3 = 0
    MOV32     R2H, *--SP          ; 1|   R2H = Y.H (set/clear NF,ZF)
;;-----------------------------------------------------------------------------
;; Context Restore (and final operations)
;;-----------------------------------------------------------------------------  
    MOV32     R4H, *--SP, UNC     ; 2|
    MOV64     R3, R1, NTF         ; if(abs(X) < abs(Y) R3 = pi/2
    ADDF64    R0, R0, R3          ; 2|*| R0 = Angle
    ; Restore save on entry registers
    POP       XAR3                ;  |1|
    POP       XAR2                ;  |2|
    NEGF64    R0, R0, LT          ; if (Y < 0) Angle = -Angle

    LRETR                   
    .unasg    P_A0_L
    .unasg    P_A0_H
    .unasg    P_A1_L
    .unasg    P_A1_H
    .unasg    P_A2_L
    .unasg    P_A2_H    
    .unasg    PI_O_2
    .endasmfunc

;;*****************************************************************************
;; This function will run the function above taking the address of the input  
;; and output as arguments         
;; 
;; Register Usage:
;;   XAR4 : points to the destination argument
;;   XAR5 : points to the first source argument
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer (SP)
;;   |_______|<- XAR4          (SP-2)
;;   |_______|<- rpc           (SP-4)
;;   |_______|<- p_src2        (SP-6)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg    run_atan2, _run_atan2
    .endif
    .global _run_atan2
    .sect   ".text"
_run_atan2: .asmfunc
    PUSH    XAR4
    MOV32   R0L, *+XAR5[0]
    MOV32   R0H, *+XAR5[2]
    MOVL    XAR5, *-SP[6]   ; XAR5 -> pointer to the second source argument
    MOV32   R1L, *+XAR5[0]
    MOV32   R1H, *+XAR5[2]
    LCR     #_atan2l
    POP     XAR4
    MOV32   *+XAR4[0], R0L
    MOV32   *+XAR4[2], R0H
    LRETR
    .endasmfunc
;; End of File
