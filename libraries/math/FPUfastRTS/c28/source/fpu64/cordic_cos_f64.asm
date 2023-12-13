;;#############################################################################
;;! \file source/fpu64/cordic_cos_f64.asm
;;!
;;! \brief  CORDIC cos function for the C28x + FPU64
;;! \author Vishal Coelho   
;;! \date   12/16/2016
;;
;; DESCRIPTION:
;;
;;  This function computes a 64-bit floating point cos given a
;;  radian input.  This function uses the CORDIC rotation mode to
;;  compute the cos.  
;;
;; FUNCTIONS:
;;
;;  float64u_t CORDIC_F64_cos(hnd_CORDIC_t hC, float64u_t theta)
;;  
;;  where CORDIC_F64_Handle is defined as:
;;  typedef CORDIC_F64 *CORDIC_F64_Handle;
;;
;;  and CORDIC_F64 is a structure,
;;  typedef struct _CORDIC_F64_
;;  {
;;    int64_t *x_i;              //!< pointer to x coordinate
;;    int64_t *y_i;              //!< pointer to y coordinate
;;    int64_t *z_i;              //!< pointer to mode dependent angle (or
;;                               //!  angular error)
;;    uint16_t N;                //!< number of CORDIC iterations (max = 64)
;;    const int64_t *atanTable;  //!< Pointer to the atan(2^-i) table
;;    void (*runKernel)(void *); //!< CORDIC kernel
;;  }CORDIC_F64;
;;
;; ASSUMPTIONS:
;;
;;  * CORDIC_F64 tables and constants are linked into the project.
;;  * the runKernel is set to the rotation kernel
;;  * N >= 26 as the scale factor does not change beyond 
;;    IQ61(1/sqrt(1 + 2^(-2* 25)))
;;
;; ALGORITHM:
;;
;; The cos value is calculated as follows:
;;
;;  1. The argument theta is converted to IQ61 (from float)
;;  2. set z  to theta in the object and call the rotation kernel
;;          0
;;  3. The x  is the cosine of the angle. Convert this angle back to float
;;          i
;;     and return
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
    .asg    CORDIC_F64_PI_O_2, _CORDIC_F64_PI_O_2
    .asg    CORDIC_F64_PI, _CORDIC_F64_PI
    .asg    CORDIC_F64_3PI_O_2, _CORDIC_F64_3PI_O_2
    .asg    CORDIC_F64_2PI, _CORDIC_F64_2PI
    .asg    CORDIC_F64_scaleFactor, _CORDIC_F64_scaleFactor
    .asg    CORDIC_F64_cos, _CORDIC_F64_cos
    .endif
    .ref    _CORDIC_F64_PI_O_2
    .ref    _CORDIC_F64_PI
    .ref    _CORDIC_F64_3PI_O_2
    .ref    _CORDIC_F64_2PI
    .ref    _CORDIC_F64_scaleFactor
;;*****************************************************************************
;; Register Usage:
;;    AR0 : index into the scale tablea
;;   XAR4 : pointer to the object
;;   XAR5 : pointer to the angle, theta | pointer to x_i
;;   XAR6 : return value address        | pointer to y_i 
;;   XAR7 : kernel pointer              | pointer to z_i 
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- XAR6                             (SP-2)
;;   |_______|<- rpc calling function             (SP-4)
;;

;;*****************************************************************************
    .page
    .global   _CORDIC_F64_cos
    .sect     ".text"
_CORDIC_F64_cos:  
    .asmfunc
    .asg    *+XAR5[0] , ARG_THETA_L
    .asg    *+XAR5[2] , ARG_THETA_H
    .asg    XAR5      , X_I
    .asg    XAR6      , Y_I
    .asg    XAR7      , Z_I
    .asg    XAR7      , KERNELPTR
    .asg    *XAR4++   , OBJ_PTR_XI
    .asg    *XAR4++   , OBJ_PTR_YI
    .asg    *XAR4++   , OBJ_PTR_ZI
    .asg    *+XAR4[0] , OBJ_N
    .asg    *+XAR4[2] , OBJ_PTR_ATANTBL
    .asg    *+XAR4[4] , OBJ_PTR_KERNEL
;;-----------------------------------------------------------------------------
;; The Cosine Function
;;----------------------------------------------------------------------------- 
    PUSH        XAR6                    ;    save the address of the return 
                                        ;    value on the stack
    MOV32       R0L, ARG_THETA_L        ;    R0 = theta
    MOV32       R0H, ARG_THETA_H
    MOVL        X_I, OBJ_PTR_XI         ;    XAR5 -> x_i
    MOVL        Y_I, OBJ_PTR_YI         ;    XAR6 -> y_i
    MOVL        Z_I, OBJ_PTR_ZI         ;    XAR7 -> z_i
    ABSF64      R0, R0                  ;    R0 = |theta|
    MOVW        DP, #_CORDIC_F64_scaleFactor
                                        ;    ACC:P = scaleFactor
    MOVL        P, @_CORDIC_F64_scaleFactor        
    MOVL        ACC, @_CORDIC_F64_scaleFactor + 2
_CORDIC_F64_sin_pi_o_2:
    MOV32       R2L, @_CORDIC_F64_PI_O_2;    R2 = pi/2
    MOV32       R2H, @_CORDIC_F64_PI_O_2 + 2
    CMPF64      R0, R2                  ;    if (|theta|<=pi/2) 
    MOVST0		ZF, NF                  ;      jmp convertArg
    BF          _CORDIC_F64_sin_convertArg, LEQ
_CORDIC_F64_sin_pi:
    MOV32       R2L, @_CORDIC_F64_PI    ;    R2 = pi
    MOV32       R2H, @_CORDIC_F64_PI + 2
    CMPF64      R0, R2                  ;    elseif (|theta|<=pi)
    MOVST0		ZF, NF
    BF         _CORDIC_F64_sin_3pi_o_2, GT
    SUBF64      R0, R2, R0              ;    R0 = pi - |theta|
    NEG64       ACC:P                   ;    ACC:P = -scaleFactor
    BF          _CORDIC_F64_sin_convertArg, UNC
_CORDIC_F64_sin_3pi_o_2:
                                        ;    R1 = 3*pi/2
    MOV32       R1L, @_CORDIC_F64_3PI_O_2    
    MOV32       R1H, @_CORDIC_F64_3PI_O_2 + 2
    CMPF64      R0, R1                  ;    elseif (|theta|<=3*pi/2)
    MOVST0		ZF, NF
    BF         _CORDIC_F64_sin_2pi, GT
    SUBF64      R0, R0, R2              ;    R0 = |theta| - pi
    NEG64       ACC:P                   ;    ACC:P = -scaleFactor
    BF          _CORDIC_F64_sin_convertArg, UNC
_CORDIC_F64_sin_2pi:
                                        ;    R2 = 2*pi
    MOV32       R2L, @_CORDIC_F64_2PI    
    MOV32       R2H, @_CORDIC_F64_2PI + 2
    SUBF64      R0, R2, R0              ; *| R0 = 2*pi - |theta|
_CORDIC_F64_sin_convertArg:
    MOVL        *+X_I[0], P             ; 1| set x_i to scaleFactor
    MOVL        *+X_I[2], ACC           ; 2|
    MPYF64      R0, R0, #0x43C0         ; *| R0 = R0*2^61
    ZERO        R1                      ; 1|
    MOV32       *+Y_I[0], R1H           ; 2| zero out y_i
    F64TOI64    R0, R0                  ; *| R0 = IQ61(theta)
    MOV32       *+Y_I[2], R1H           ; 1|
    MOV32       *+Z_I[0], R0L           ;    z_i = IQ61(theta)
    MOV32       *+Z_I[2], R0H           
    MOVL        KERNELPTR, OBJ_PTR_KERNEL    
                                        ;    XAR7 -> kernel
    SUBB        XAR4, #6                ;    rewind object pointer
    
    ;; Call the rotation kernel
    LCR         *KERNELPTR
                                        ;    XAR6 -> x_i (IQ61)
    MOV32       R0L, *+X_I[0]           ;    R0 = IQ61(cos(theta))
    MOV32       R0H, *+X_I[2]
    I64TOF64    R0, R0                  ; *| R0 = cos(theta) * 2^61
    NOP                                 ; 1| 
    MPYF64      R0, R0, #0x3C20         ; *| R0 = R0 * 2^-61
    NOP                                 ; 1|
    POP         XAR6                    ; 2| XAR6 -> addr(return value)
    MOV32       *+XAR6[0], R0L              
    MOV32       *+XAR6[2], R0H
    LRETR                          
    .endasmfunc
    .unasg  ARG_THETA_L
    .unasg  ARG_THETA_H
    .unasg  X_I
    .unasg  Y_I
    .unasg  Z_I
    .unasg  KERNELPTR
    .unasg  OBJ_PTR_XI
    .unasg  OBJ_PTR_YI
    .unasg  OBJ_PTR_ZI
    .unasg  OBJ_N
    .unasg  OBJ_PTR_ATANTBL
    .unasg  OBJ_PTR_KERNEL

;; End of File
