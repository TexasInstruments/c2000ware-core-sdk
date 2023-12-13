;;#############################################################################
;; FILE: CLAsincos.asm
;; 
;; DESCRIPTION: CLA sincos function
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

    .cdecls C,LIST,"CLAmath.h"
	.include "CLAeabi.asm"

;;----------------------------------------------------------------------------
;; Description: Implement sine + cosine using taylor series expansion:
;;  
;;   rad = K + X
;;  
;;   Cos(rad) = Cos(K) - Sin(K)*X 
;;                     - Cos(K)*X^2/2! 
;;                     + Sin(K)*X^3/3! 
;;                     + Cos(K)*X^4/4! 
;;                     - Sin(K)*X^5/5!
;;  
;;            = Cos(K) + X*(-1.0*Sin(K) 
;;                     + X*(-0.5*Cos(K) 
;;                     + X*(0.166666*Sin(K) 
;;                     + X*(0.04166666*Cos(K) 
;;                     + X*(-0.00833333*Sin(K))))))
;;  
;;            = Cos(K) + X*(-Sin(K) 
;;                     + X*(Coef0*Cos(K) 
;;                     + X*(Coef1_pos*Sin(K) 
;;                     + X*(Coef2*Cos(K) 
;;                     + X*(Coef3_neg*Sin(K)))))) 
;;  
;;  
;;   Sin(rad) = Sin(K) + Cos(K)*X 
;;                     - Sin(K)*X^2/2! 
;;                     - Cos(K)*X^3/3! 
;;                     + Sin(K)*X^4/4! 
;;                     + Cos(K)*X^5/5!
;;  
;;            = Sin(K) + X*(Cos(K) 
;;                     + X*(-0.5*Sin(K) 
;;                     + X*(-0.166666*Cos(K) 
;;                     + X*(0.04166666*Sin(K) 
;;                     + X*(0.00833333*Cos(K))))))
;;  
;;            = Sin(K) + X*(Cos(K) 
;;                     + X*(Coef0*Sin(K) 
;;                     + X*(Coef1*Cos(K) 
;;                     + X*(Coef2*Sin(K) 
;;                     + X*(Coef3*Cos(K))))))
;;   
;; Equation:    y1 = sin(rad)
;;              y2 = cos(rad)
;;
;; Regs Used:   MR0, MR1, MR2, MR3, MAR0, MAR1
;;
;; Inputs   :   rad (MR0), *y1 (MAR0), *y2 (MAR1)
;;
;; // TABLE_SIZE = 128
;; CLAsincosTable.Sin0   =  0.0;               // sin(  0 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Sin1   =  0.04906767432742;  // sin(  1 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin31  =  0.9987954562052;   // sin( 31 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos0   =  1.0;               // sin( 32 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin33  =  0.9987954562052;   // sin( 33 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin63  =  0.04906767432742;  // sin( 63 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin64  =  0.0;               // sin( 64 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Sin65  = -0.04906767432742;  // sin( 65 * 2*pi/TABLE_SIZE) 
;; ... 
;; CLAsincosTable.Sin95  = -0.9987954562052;   // sin( 95 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin96  = -1.0;               // sin( 96 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin97  = -0.9987954562052;   // sin( 97 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin127 = -0.04906767432742;  // sin(127 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos96  =  0.0;               // sin(  0 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Cos97  =  0.04906767432742;  // sin(  1 * 2*pi/TABLE_SIZE) 
;; ... 
;; CLAsincosTable.Cos127 =  0.9987954562052;   // sin( 31 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos128 =  1.0;               // sin( 32 * 2*pi/TABLE_SIZE) 
;;
;; CLAsincosTable.TABLE_SIZEDivPi        =  40.74366543152;               
;; CLAsincosTable.TwoPiDivTABLE_SIZE     =  0.04908738521234;  
;; CLAsincosTable.TABLE_MASK             =  0x000000FE;
;;       
;; CLAsincosTable.Coef0                  = -0.5;
;; CLAsincosTable.Coef1                  = -0.1666666666666;
;; CLAsincosTable.Coef1_pos              =  0.1666666666666;
;; CLAsincosTable.Coef2                  =  4.1666666666666e-2;
;; CLAsincosTable.Coef3                  =  8.3333333333333e-3;
;; CLAsincosTable.Coef3_neg              = -8.3333333333333e-3;
;;
;; Output:  y1 (y_sin) and y2 (y_cos) f32 value in memory
;;
;; Benchmark:   Cycles = 43
;;              Instructions = 43
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- sincos temporary variable 2       (SP+6)
;;   |_______|<- sincos temporary variable 1       (SP+4)
;;   |_______|<- *y2                               (SP+3)
;;   |_______|<- *y1                               (SP+2)
;;   |_______|<- MR3                               (SP+0)
;;
;;---------------------------------------------------------------------------- 

    .def    _CLAsincos    
    .sect   "Cla1Prog:_CLAsincos"
    .align  2
    .def    __cla_CLAsincos_sp
__cla_CLAsincos_sp .usect  ".scratchpad:Cla1Prog:_CLAsincos",8,0,1

_CLAsincos:
    .asmfunc
    .asg    __cla_CLAsincos_sp + 0, _save_MR3
    .asg    __cla_CLAsincos_sp + 2, _ptr_y1
    .asg    __cla_CLAsincos_sp + 3, _ptr_y2
    .asg    __cla_CLAsincos_sp + 4, _sincos_tmp1
    .asg    __cla_CLAsincos_sp + 6, _sincos_tmp2
; Context Save
    MMOV32    @_save_MR3, MR3
    MMOV16    @_ptr_y1, MAR0
    MMOV16    @_ptr_y2, MAR1
    
; MR0 = rad
; MR1 = TABLE_SIZE/(2*Pi) 
; MR1 = rad*TABLE_SIZE/(2*Pi)
; MR2 = TABLE_MASK
; MR3 = K = integer(rad*TABLE_SIZE/(2*Pi))
; MR3 = K & TABLE_MASK
; MR3 = K * 2
    MMOV32    MR1,@_CLAsincosTable_TABLE_SIZEDivTwoPi  
    MMPYF32   MR1,MR0,MR1                              
 || MMOV32    MR2,@_CLAsincosTable_TABLE_MASK          
    MF32TOI32 MR3,MR1                                  
    MAND32    MR3,MR3,MR2                              
    MLSL32    MR3,#1                                   

; MAR0 = address of Cos(K)
; MR1 = frac(TABLE_SIZE*rad/2*Pi)
; MR0 = 2*Pi/TABLE_SIZE
; MR1 = X = frac(TABLE_SIZE*rad/2*Pi) * (2*Pi/TABLE_SIZE)
; MR0 = Coef3
    MMOV16    MAR0,MR3,#_CLAsincosTable_Cos0           
    MFRACF32  MR1,MR1                                  
    MMOV32    MR0,@_CLAsincosTable_TwoPiDivTABLE_SIZE  
    MMPYF32   MR1,MR1,MR0                              
 || MMOV32    MR0,@_CLAsincosTable_Coef3               

; MR2 = Cos(K)
; MR3 = Coef3*Cos(K)
; MR2 = Sin(K)
; MR3 = X*Coef3*Cos(K)  
; MR0 = Coef3_neg 
    MMOV32    MR2,*MAR0[#-64]++                
    MMPYF32   MR3,MR0,MR2                      
 || MMOV32    MR2,*MAR0[#+64]++                
    MMPYF32   MR3,MR3,MR1                      
 || MMOV32    MR0, @_CLAsincosTable_Coef3_neg    

; MR3 = Coef3_neg*Sin(K) 
; tmp1 = X*Coef3*Cos(K)  
; MR3 = X*Coef3_neg*Sin(K)
; MR0 = Coef2   
; MR2 = Coef2*Sin(K)
; tmp2 = X*Coef3*Sin(K) 
    MMPYF32   MR3,MR0,MR2                     
 || MMOV32    @_sincos_tmp1, MR3                   
    MMPYF32   MR3,MR3,MR1                     
 || MMOV32    MR0,@_CLAsincosTable_Coef2      
    MMPYF32   MR2,MR0,MR2                     
 || MMOV32    @_sincos_tmp2, MR3                   

; MR3 = X*Coef3*Cos(K)          
; MR3 = Coef2*Sin(K) + X*Coef3*Cos(K)
; MR2 = Cos(K)   
; MR3 = X*Coef2*Sin(K) + X^2*Coef3*Cos(K)  
; MR0 = Coef2*Cos(K) 
; tmp1 = X*Coef2*Sin(K) + X^2*Coef3*Cos(K)  
    MMOV32    MR3, @_sincos_tmp1                     
    MADDF32   MR3,MR3,MR2                       
 || MMOV32    MR2,*MAR0[#-64]++                 
    MMPYF32   MR3,MR3,MR1                       
    MMPYF32   MR0, MR0, MR2                     
 || MMOV32    @_sincos_tmp1, MR3                            
      
; MR3 = X*Coef3*Sin(K)      
; MR3 = Coef2*Cos(K) + X*Coef3_neg*Sin(K)
; MR3 = X*Coef2*Cos(K) - X^2*Coef3*Sin(K)   
; MR0 = Coef1   
; MR2 = Coef1*Cos(K)
; tmp2 = X*Coef2*Cos(K) - X^2*Coef3*Sin(K)
    MMOV32    MR3, @_sincos_tmp2                     
    MADDF32   MR3, MR0, MR3                     
    MMPYF32   MR3, MR3, MR1                        
 || MMOV32    MR0,@_CLAsincosTable_Coef1        
    MMPYF32   MR2,MR0,MR2                       
 || MMOV32    @_sincos_tmp2, MR3                     

; MR3 = X*Coef2*Sin(K) + X^2*Coef3*Cos(K)  (G)+(F)      
; MR3 = Coef1*Cos(K) + X*Coef2*Sin(K) + X^2*Coef3*Cos(K)      
; MR2 = Sin(K)   
; MR3 = X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)   
; MR0 = Coef1_pos
; MR0 = Coef1_pos*Sin(K)
; tmp1 = X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)   
    MMOV32    MR3, @_sincos_tmp1                    
    MADDF32   MR3,MR3,MR2                      
 || MMOV32    MR2,*MAR0[#+64]++                
    MMPYF32   MR3,MR3,MR1                                                                    
 || MMOV32    MR0, @_CLAsincosTable_Coef1_pos  
    MMPYF32   MR0, MR0, MR2                    
 || MMOV32    @_sincos_tmp1, MR3                    

; MR3 = X*Coef2*Cos(K) + X^2*Coef3_neg*Sin(K) (B)-(A) 
; MR3 = Coef1-pos*Sin(K) + X*Coef2*Cos(K) + X^2*Coef3_neg*Sin(K)
; MR3 = X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) + X^3*Coef3_neg*Sin(K)  
; MR0 = Coef0 
; MR2 = Coef0*Sin(K)
; tmp2 = X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) + X^3*Coef3_neg*Sin(K) 
; MR3 = X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)
    MMOV32    MR3, @_sincos_tmp2                     
    MADDF32   MR3, MR0, MR3                     
    MMPYF32   MR3, MR1, MR3                       
 || MMOV32    MR0,@_CLAsincosTable_Coef0        

    MMPYF32   MR2,MR0,MR2                       
 || MMOV32    @_sincos_tmp2, MR3                      
      
    MMOV32    MR3, @_sincos_tmp1                     
                                                  

; MR3 = Coef0*Sin(K) + X*Coef1*Cos(K) + X^2*Coef2*Sin(K) 
;     + X^3*Coef3*Cos(K)  
;                                                  
; MR2 = Cos(K)
;
; MR3 = X*Coef0*Sin(K) + X^2*Coef1*Cos(K) 
;     + X^3*Coef2*Sin(K) + X^4*Coef3*Cos(K)
;        
; MR3 = Cos(K) + X^1*Coef0*Sin(K) + X^2*Coef1*Cos(K) 
;     + X^3*Coef2*Sin(K) + X^4*Coef3*Cos(K)
;
; MR3 = X*Cos(K) + X^2*Coef0*Sin(K) + X^3*Coef1*Cos(K) 
;     + X^4*Coef2*Sin(K) + X^5*Coef3*Cos(K)
    MADDF32   MR3, MR2, MR3                     
 || MMOV32    MR2,*MAR0[#-64]++                 

    MMPYF32   MR3,MR3,MR1                       
    MADDF32   MR3,MR3,MR2
    MMOV16    MAR1, @_ptr_y1
    MMPYF32   MR3,MR3,MR1                       

; MR0 = Coef0*Cos(K)      
; MR2 = Sin(K)

; MR3 = Sin(K) + X*Cos(K) + X^2*Coef0*Sin(K) 
;     + X^3*Coef1*Cos(K) + X^4*Coef2*Sin(K) + X^5*Coef3*Cos(K)
; Store Y1 = Sin(rad)
;
; MR3 = X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) + X^3*Coef3_neg*Sin(K)   
    MMPYF32   MR0, MR0, MR2                   
 || MMOV32    MR2,*MAR0[#+64]++               

    MADDF32   MR3,MR2,MR3                     
    MMOV32    *MAR1[#0]++, MR3                      
    
    MMOV32    MR3, @_sincos_tmp2                   

; MR3 = Coef0*Cos(K) +  X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) 
;       + X^3*Coef3_neg*Sin(K)            
;     
; MR3 = X*Coef0*Cos(K) +  X^2*Coef1_pos*Sin(K) 
;       + X^3*Coef2*Cos(K) + X^4*Coef3_neg*Sin(K)
;   
; MR3 = -Sin(K)+X*Coef0*Cos(K) +  X^2*Coef1_pos*Sin(K) 
;       + X^3*Coef2*Cos(K) + X^4*Coef3_neg*Sin(K)
;     
; MR2 = Cos(K)
; MR3 = -X*Sin(K) + X^2*Coef0*Cos(K) + X^3*Coef1_pos*Sin(K)
;       + X^4*Coef2*Cos(K) + X^5*Coef3_neg*Sin(K)   
;
; MR3 = Cos(K) - X*Sin(K) + X^2*Coef0*Cos(K) + X^3*Coef1_pos*Sin(K)
;       + X^4*Coef2*Cos(K) + X^5*Coef3_neg*Sin(K)  
; Store Y2 = Cos(rad)      
    MADDF32   MR3, MR0, MR3                                                     
    MMPYF32   MR3, MR1, MR3
    MMOV16    MAR1, @_ptr_y2
    MSUBF32   MR3, MR3, MR2                    
 || MMOV32    MR2,*MAR0[#0]++                  
    MMPYF32   MR3, MR1, MR3     
; Context Restore and Final Operations
    MRCNDD    UNC
    MADDF32   MR3, MR2, MR3                                 
    MMOV32    *MAR1[#0]++, MR3      
    MMOV32    MR3,@_save_MR3 
    .unasg  _save_MR3
    .unasg  _ptr_y1
    .unasg  _ptr_y2
    .endasmfunc

;; End of File
 
