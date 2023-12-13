;;#############################################################################
;;! \file source/fpu32/atan2_f32.asm
;;!
;;! \brief  Fast atan2 function for the C28x + Floating-Point Unit.
;;! \author N/A
;;! \date   N/A
;;
;; DESCRIPTION:
;;
;;    This function computes a 32-bit floating point atan2 given a
;;    Y, X input.  This function uses the FPU math tables to
;;    compute the atan2 resulting angle.
;;
;; FUNCTIONS:
;;
;;    float32 atan2f (float32 Y, float32 X)
;;
;; ASSUMPTIONS:
;;
;;     * FPU32atan2Table and FPU32atan2Table are linked into the project.
;;
;; ALGORITHM:
;;             The algorithm steps to calculate the "atan2" of the given
;;             input X and Y is as follows:
;;
;;             Step(1):   if( abs(X) >= abs(Y) )
;;                            Numerator   = abs(Y)
;;                            Denominator = abs(X)
;;                        else
;;                            Numerator   = abs(X)
;;                            Denominator = abs(Y)
;;
;;             Step(2):   Ratio = Numerator/Denominator
;;
;;                        Note: Ratio range = 0.0 to 1.0
;;
;;             Step(3):   Use the upper 6-bits of the "Ratio" value as an
;;                        index into the table to obtain the coefficients
;;                        for a second order equation:
;;
;;                        _FPU32atan2Table:
;;                             CoeffA0[0]
;;                             CoeffA1[0]
;;                             CoeffA2[0]
;;                                .
;;                                .
;;                             CoeffA0[63]
;;                             CoeffA1[63]
;;                             CoeffA2[63]
;;
;;             Step(4):   Calculate the angle using the folowing equation:
;;
;;                        arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;;                        arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;;
;;             Step(5):   The final angle is determined as follows:
;;
;;                        if( X >= 0 and Y >= 0 and abs(X) >= abs(Y) )
;;                            Angle = arctan(abs(Y)/abs(X))
;;                        if( X >= 0 and Y >= 0 and abs(X) <  abs(Y) )
;;                            Angle = PI/2 - arctan(abs(X)/abs(Y))
;;                        if( X < 0  and Y >= 0 and abs(X) <  abs(Y) )
;;                            Angle = PI/2 + arctan(abs(X)/abs(Y))
;;                        if( X < 0  and Y >= 0 and abs(X) >= abs(Y) )
;;                            Angle = PI - arctan(abs(Y)/abs(X))
;;                        if( Y < 0 )
;;                            Angle = -Angle
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

       .page
       .if __TI_EABI__
       .asg    FPU32atan2HalfPITable, _FPU32atan2HalfPITable
       .asg    FPU32atan2Table, _FPU32atan2Table
       .asg    atan2f, _atan2
       .endif
       .global _atan2
       .ref _FPU32atan2HalfPITable
       .ref _FPU32atan2Table
       .text
    
       .if (__TI_EABI__ = 0)
       ; For TI COFF double and float are the same size, so atan2f() and 
       ; atan2() should be the same function
       .global _atan2f
_atan2f:
       .endif
_atan2:
       .asmfunc
       MOV32    *SP++,R4H            ; Save on entry register
                                     ; R0H = Y on entry
                                     ; R1H = X on entry
; Perform Step (1):
       ABSF32    R3H, R0H            ; (1) R3H = abs(Y)
       ABSF32    R4H, R1H            ; (1) R4H = abs(X)
       MINF32    R3H, R4H            ; (1) R3H = Numerator = min(abs(Y),abs(X))
    || MOV32     R4H, R3H            ; (1) R4H = Denominator = max(abs(Y),abs(X))
; Perform Step (2) and (3):
       EINVF32   R2H, R4H            ; (2) R2H = Ye = Estimate(1/Numerator)
       TESTTF    LEQ                 ; (5) Set TF if abs(X) >= abs(Y)
       MPYF32    R0H, R2H, R4H       ; (2) R0H = Ye*B
    || MOV32     *SP++, R0H          ; Store Y (*-SP[2] = Y)
       MPYF32    R1H, R2H, R3H       ; (3) R1H = 16-bit accurate estimate
    || MOV32    *SP++,R1H            ; Store X (*-SP[4] = Y, *-SP[2] = X)
       SUBF32    R0H, #2.0, R0H      ; (2) R0H = 2.0 - Ye*B
       MPYF32    R1H, R1H, 64.0      ; (3) 64 = Elements In Table
       MPYF32    R2H, R2H, R0H       ; (2) R2H = Ye = Ye*(2.0 - Ye*B)  (first estimate)
       F32TOUI16 R1H, R1H            ; (3) R1H = int(64*ratio) (16-bit accurate)
       MPYF32    R0H, R2H, R4H       ; (2) R0H = Ye*B
       MOVL      XAR7, #_FPU32atan2Table+4   ; (3) Point to A2
       SUBF32    R0H, #2.0, R0H      ; (2) R0H = 2.0 - Ye*B
       MOVL      XAR6, #_FPU32atan2Table+2   ; Point to A1
       MOV32     ACC, R1H            ; (3) ACC = int(64*Ratio)
       MPY       P, @AL, #6          ; (3) P = 6 * int(64*Ratio)
       MOVZ      AR0, @PL            ; (3) AR0 = _FPU32atan2Table index
       MPYF32    R2H, R2H, R0H       ; (2) R2H = Ye = Ye*(2.0 - Ye*B)
       MOVL      XAR5, #_FPU32atan2Table     ; Point to A0
       MPYF32    R0H, R3H, R2H       ; (2) R0H = Ratio = A*Ye = A/B
; Perform Step (4):
; arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
       MOV32     R1H, *+XAR7[AR0]    ; (4) R1H = A2
       MPYF32    R3H, R1H, R0H       ; (4) R3H = A2*Ratio
    || MOV32     R1H, *+XAR6[AR0]    ; (4) R1H = A1
       MOVL      XAR7, #_FPU32atan2HalfPITable ; (5) *XAR7[2] == pi/2
       ADDF32    R3H, R1H, R3H       ; (4) R3H = A1 + A2*Ratio
    || MOV32     R4H, *+XAR5[AR0]    ; (4) R4H = A0
       MOV32     R1H, *+XAR7[2], UNC ; (5) R1H = pi/2 (no flag change)
       MPYF32    R3H, R0H, R3H       ; (4) R3H = Ratio*(A1 + A2*Ratio)
       NOP
       ADDF32    R0H, R4H, R3H       ; (4) R0H = arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
    || MOV32     R2H, *--SP          ; (5) R2H = X (set/clear NF,ZF for use below)
; Perform Step (5):
       NEGF32    R3H, R1H, UNC       ; (5) R3H = -pi/2 (no flag change)
       MOV32     R0H, R2H, EQ        ; (5) if (X == 0), R0H = 0
       NEGF32    R0H, R0H, GEQ       ; (5) if (X >= 0) R0H flip sign of atan(Ratio)
       NEGF32    R0H, R0H, TF        ; (5) if (abs(X) >= abs(Y)) flip sign of atan(Ratio)
       NEGF32    R3H, R3H, LT        ; (5) if (X < 0) R3H = pi/2
       ADDF32    R3H, R3H, R1H       ; (5) R3H = R3H + pi/2
                                     ;     if (X < 0) R3H = pi
                                     ;     if (X > 0) R3H = 0
   ||  MOV32     R2H, *--SP          ; (5) R2H = Y (set/clear NF,ZF)
       MOV32     R4H, *--SP, UNC     ; Restore save on entry register (no flag change)
       MOV32     R3H, R1H, NTF       ; (5) if(abs(X) < abs(Y) R3H = pi/2
       ADDF32    R0H, R0H, R3H       ; R0H = Angle
       NOP
       NEGF32    R0H, R0H, LT        ; if (Y < 0) Angle = -Angle
       LRETR
       .endasmfunc

    
;; End of File
