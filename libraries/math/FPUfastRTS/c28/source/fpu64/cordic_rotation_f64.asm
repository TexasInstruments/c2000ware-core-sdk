;;#############################################################################
;;! \file source/fpu64/cordic_rotation_f64.asm
;;!
;;! \brief  CORDIC Rotation Kernel for the C28x + FPU64
;;! \author Vishal Coelho   
;;! \date   11/14/2016
;;
;; DESCRIPTION:
;;
;;   This function implements the rotation kernel (CORDIC) in 64-bit double 
;;   precision floating point.
;;
;; FUNCTIONS:
;;
;;  void CORDIC_F64_rotationKernel(CORDIC_F64_Handle hC) 
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
;;
;; ALGORITHM:
;;
;;      The CORDIC algorithm is run for N iterations. We start with the 
;;      following   parameters
;;      
;;      x     = 1/K = 0.6072529350088812561694, where 
;;       0
;;                __inf           1
;;      K     =   ||       -----------------
;;                  n=0    sqrt(1 + 2^(-2n))
;; 
;;      y  = 0, z  = theta (angle in radians)
;;       0       0
;;      
;;      The *Non Restoring Decomposition* algorithm proceeds as follows:
;;                               -n
;;      x    = x  - d  * y * 2 
;;       n+1    n    n    n 
;;                             -n
;;      y    = y  + d  * x  * 2
;;       n+1    n    n    n 
;;                               -n
;;      z    = z  - d  * arctan(2  )
;;       n+1    n    n
;;      
;;                    1 if  z  >= 0, 
;;      where d   =          n
;;             n     -1 otherwise
;;                  
;;
;;      Note that |theta| <= theta     and 
;;                                max
;;
;;                  -- inf          -k 
;;      theta    =  >       arctan(2  ) = 1.7432866204723400035...
;;           max    -- k=0
;;                   
;;     Once N iterations are complete we would have rotated our initial 
;;     vector by the angle theta (within some error tolerance); the x and
;;     y components of the resultant vector are the cosine and sine of theta
;;     respectively
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
    .asg    CORDIC_F64_atanTable, _CORDIC_F64_atanTable
    .asg    CORDIC_F64_scaleTable, _CORDIC_F64_scaleTable
    .asg    CORDIC_F64_rotationKernel, _CORDIC_F64_rotationKernel
    .endif
    .ref    _CORDIC_F64_atanTable
    .ref    _CORDIC_F64_scaleTable
       
;;*****************************************************************************
;; Register Usage:
;;    AR0 : number of CORDIC iterations
;;   XAR1 : pointer to the arctan table
;;   XAR2 : temporary 32-bit storage
;;   XAR4 : pointer to the object
;;   XAR5 : pointer to x_i
;;   XAR6 : pointer to y_i
;;   XAR7 : pointer to z_i
;;  ACC:P : coordinate to be shifted, z_i
;;      T : shift amount (0 - 63)
;;
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- rpc calling function             (SP-2)
;;

;;*****************************************************************************
    .page
    .global   _CORDIC_F64_rotationKernel
    .sect     ".text"
_CORDIC_F64_rotationKernel:  
    .asmfunc
    .asg    XAR1      , ATANTBL
    .asg    XAR5      , X_I
    .asg    XAR6      , Y_I
    .asg    XAR7      , Z_I
    .asg    *XAR4++   , OBJ_PTR_XI
    .asg    *XAR4++   , OBJ_PTR_YI
    .asg    *+XAR4[0] , OBJ_PTR_ZI
    .asg    *+XAR4[2] , OBJ_N
    .asg    *+XAR4[4] , OBJ_PTR_ATANTBL
    .asg    *+XAR4[6] , OBJ_PTR_SCALETBL
;;-----------------------------------------------------------------------------
;; Context Save
;;----------------------------------------------------------------------------- 
    PUSH    XAR1
    PUSH    XAR2
    SETC    OVM                         ; allows for negation with saturation
;;-----------------------------------------------------------------------------
;; Rotation Kernel
;;-----------------------------------------------------------------------------
    
    MOVL    X_I, OBJ_PTR_XI             ; XAR5 -> x_i
    MOVL    Y_I, OBJ_PTR_YI             ; XAR6 -> y_i
    MOVL    Z_I, OBJ_PTR_ZI             ; XAR7 -> z_i
    MOVZ    AR0, OBJ_N                  ; AR0  = N
    SUBB    XAR0, #1                    ;      = N - 1
    MOVL    ATANTBL, OBJ_PTR_ATANTBL    ; XAR1 -> arctan table
    
    MOV     T, #0

_CORDIC_F64_rotationKernel_loop:
	MOVB	AL, #0xAA, OV				; dummy move clear V when set
    MOVL    P,  *+Z_I[0]                ; ACC:P = z_i
    MOVL    ACC, *+Z_I[2]              
    CMP64   ACC:P                       ; set Z if ACC:P = 0
    SB      _CORDIC_F64_rotationKernel_clockwise, LT
    
_CORDIC_F64_rotationKernel_counterClockwise:
    ;; z_i = z_i - atantbl[i]
    SUBUL   P, *ATANTBL++               ; z_i.low -= atantbl[i].low
    SUBBL   ACC, *ATANTBL++             ; z_i.hi  -= (atantbl[i].hi + ~C)
    MOVL    *+Z_I[0], P                 ; save z_n
    MOVL    *+Z_I[2], ACC
    
    ;; x_n = x_i - (y_i >> i)
    MOVL    P, *+Y_I[0]                 ; ACC:P = y_i
    MOVL    ACC, *+Y_I[2]
    ASR64   ACC:P, T                    ; ACC:P = y_i >> i
    NEG64   ACC:P                       ;       = -(y_i >> i)
    ADDUL   P, *+X_I[0]                 ;   P = -(y_i >> i).low + x_i.low
    ADDCL   ACC, *+X_I[2]               ; ACC = -(y_i >> i).hi + x_i.hi + C
    MOVL    XAR2, P                     ; save P temporarily

    ;; y_n = y_i + (x_i >> i)
    MOVL    P, *+X_I[0]                 ; ACC:P = x_i
    MOVL    *+X_I[0], XAR2
    MOVL    XAR2, ACC                   ; save ACC temporarily
    MOVL    ACC, *+X_I[2]
    MOVL    *+X_I[2], XAR2              ; save x_n (x_i for next iteration)
    ASR64   ACC:P, T                    ; ACC:P = x_i >> i
    ADDUL   P, *+Y_I[0]                 ;   P = (x_i >> i).low + y_i.low
    ADDCL   ACC, *+Y_I[2]               ; ACC = (x_i >> i).hi + y_i.hi + C
    MOVL    *+Y_I[0], P                 ; save y_n (y_i for next iteration)
    MOVL    *+Y_I[2], ACC
_CORDIC_F64_rotationKernel_counterClockwiseEnd:
    INC     T    
    BANZ    _CORDIC_F64_rotationKernel_loop, AR0--
    BF      _CORDIC_F64_rotationKernel_loopEnd, UNC
    
_CORDIC_F64_rotationKernel_clockwise:
    ;; z_i = z_i + atantbl[i]
    ADDUL   P, *ATANTBL++               ; z_i.low += atantbl[i].low
    ADDCL   ACC, *ATANTBL++             ; z_i.hi  += (atantbl[i].hi + C)
    MOVL    *+Z_I[0], P                 
    MOVL    *+Z_I[2], ACC
    
    ;; x_n = x_i + (y_i >> i)
    MOVL    P, *+Y_I[0]                 ; ACC:P = y_i
    MOVL    ACC, *+Y_I[2]
    ASR64   ACC:P, T                    ; ACC:P = y_i >> i
    ADDUL   P, *+X_I[0]                 ;   P = (y_i >> i).low + x_i.low
    ADDCL   ACC, *+X_I[2]               ; ACC = (y_i >> i).hi + x_i.hi + C
    MOVL    XAR2, P                     ; save P temporarily
    
    ;; y_n = y_i - (x_i >> i)
    MOVL    P, *+X_I[0]                 ; ACC:P = x_i
    MOVL    *+X_I[0], XAR2
    MOVL    XAR2, ACC                   ; save ACC temporarily
    MOVL    ACC, *+X_I[2]
    MOVL    *+X_I[2], XAR2              ; save new x_i
    ASR64   ACC:P, T                    ; ACC:P = x_i >> i
    NEG64   ACC:P                       ;       = -(x_i >> i)
    ADDUL   P, *+Y_I[0]                 ;   P = -(x_i >> i).low + y_i.low
    ADDCL   ACC, *+Y_I[2]               ; ACC = -(x_i >> i).hi + y_i.hi + C
    MOVL    *+Y_I[0], P                 ; save new y_i
    MOVL    *+Y_I[2], ACC
    
_CORDIC_F64_rotationKernel_clockwiseEnd:   
    INC     T    
    BANZ    _CORDIC_F64_rotationKernel_loop, AR0--

_CORDIC_F64_rotationKernel_loopEnd:
;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
    CLRC    OVM                         ; compiler expects OVM  = 0
    POP     XAR2
    POP     XAR1
    LRETR                          
    .endasmfunc
    .unasg  ATANTBL
    .unasg  X_I
    .unasg  Y_I
    .unasg  Z_I
    .unasg  OBJ_PTR_XI
    .unasg  OBJ_PTR_YI
    .unasg  OBJ_PTR_ZI
    .unasg  OBJ_N
    .unasg  OBJ_PTR_ATANTBL
    .unasg  OBJ_PTR_SCALETBL
;; End of File
