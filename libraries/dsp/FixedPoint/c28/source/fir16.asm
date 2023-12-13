;;#############################################################################
;;! \file source/fir16.asm
;;!
;;! \brief  16-bit FIR filter
;;!
;;! \date   May 11, 2010
;;! 
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
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; globals
;;*****************************************************************************
    ; Module definition for external reference

    .if __TI_EABI__
    .asg FIR16_init, _FIR16_init
    .asg FIR16_calc, _FIR16_calc
    .endif

    .def      _FIR16_init
    .def      _FIR16_calc
   
;;
;;=============================================================================
;; Routine Type  : C Callable
;; Description   :
;; void FIR16_calc(FIR16_handle) 
;;       
;; This routine implements the non-recursive difference equation of an 
;; all-zero filter(FIR), of order N. All the coefficients of all-zero 
;; filter are assumed to be less than 1 in magnitude.
;;=============================================================================
;;
;; Algorithm:   Y  = sat(X0*C0 + X1*C1 + X2*C2 + ... Xn*Cn) >> 15
;;              Xn = Xn-1
;;                 .
;;                 .
;;              X2 = X1
;;              X1 = X0
;;
;;              X0 = input, Q15
;;              X1,..,Xn = Data, Q15
;;              C0,..,Cn = Coef, Q15
;;              Y  = output, Q15 
;;              n  = N - 1 (N = number of taps, must always be an even number)
;;
;;              This program uses the Dual-MAC capability of the C28x. The data
;;              and coef structures must be organized into 32-bit words as follows:
;;
;;                       31         16 15          0  
;;                       +------------+------------+
;;              *Data -> |     N-2    |   Index    | 0 lowest address
;;                       |          SatMax         | 2
;;                       |          SatMin         | 4
;;                       |   unused   |  (N/2)-1   | 6
;;                       +------------+------------+    
;;                       | .          | .          | 0
;;                       | .          | .          | 2    
;;                tail-> | .          | X(1)       | 4    
;;                head-> | X((n+1)/2) | X(0)       | 6<- index value before 
;;                       | X(n)       | X((n-1)/2) | 8   executing FIR
;;                       | X(n-1)     | .          | .
;;                       | .          | .          | .
;;                       +------------+------------+
;;
;;                       31         16 15          0  
;;                       +------------+------------+   
;;              *Coef -> | C(n)       | C((n-1)/2) | 0 lowest address
;;                       | C(n-1)     | .          | 2
;;                       | .          | .          | 4
;;                       | .          | C(2)       | .
;;                       | .          | C(1)       | .
;;                       | C((n+1)/2) | C(0)       | . 
;;                       +------------+------------+
;;          
;;              * For maximum performance, locate Data & Coef
;;                structures in seperate RAM blocks.
;;              * The Data & Coef pointers must always point to the lowest 
;;                address of the array and always aligned to even address
;;
;;              Before calling FIR, need to initialize following data parameters:
;;
;;                 Index = 0 
;;                     N = Number of filter taps (must always be even)
;;                   N-2 = Size of data buffer (must always be an even number)
;;               (N/2)-1 = number of times to repeat Dual MAC operation
;;                SatMax = 0x00FFFFFF (corresponds to SPM of -6)
;;                SatMin = 0xFF000000 (corresponds to SPM of -6)
;;               
;;                Note: Don't forget to clear all data values
;==============================================================================         
;;  Function Input: This function accepts the handle of the below structure
;;
;; typedef struct { <------------ XAR4
;;     int32_t *coeff_ptr;      /*  +0  Pointer to Filter coefficient */
;;     int32_t * dbuffer_ptr;   /*  +2  Delay buffer ptr              */
;;     int16_t cbindex;         /*  +4  Circular Buffer Index         */
;;     int16_t order;           /*  +5  Order of the Filter           */
;;     int16_t input;           /*  +6  Latest Input sample           */ 
;;     int16_t output;          /*  +7  Filter Output                 */
;;     void (*init)(void *);    /*  +8  Ptr to Init funtion           */
;;     void (*calc)(void *);    /*  +10 Ptr to calc fn                */  
;; }FIR16;     
;;
_FIR16_init:
    MOV       *+XAR4[6],#0          ; XAR4->ouput, input=0
    MOV       *+XAR4[7],#0          ; output=0
                                    
    MOVL      XAR6,*+XAR4[2]        ; XAR6=dbuffer_ptr            
    MOV       AL,*+XAR4[5]          ; AL=order
    MOV       AH,AL                 ; AH=order
    TBIT      AL,#0                      
    ADDB      AL,#1                 ; AL=order+1        
    MOV       AL,AH,TC              ; AL=order, if odd
                                    
    MOV       AH,AL                 
    SUBB      AH,#1                 
    MOV       *+XAR4[4],AH          ; cbindex = order, even
                                    ;         = order-1, odd
              
    RPT       AL
 || MOV       *XAR6++,#0
    
    LRETR

ConstTable: 
PosSatVal:    .long    0x00FFFFFF   ; Corresponds to >> 6 
NegSatVal:    .long    0xFF000000   ; Corresponds to >> 6 

;;FILTER_ORDER  .set	   43
;;RPT_COUNT     .set     (FILTER_ORDER/2)

_FIR16_calc:
    PUSH      XAR1                  ; Context Save           
                                    
    SETC      SXM,OVM               ; AR4=FIR16_handle->coeff_ptr 
    SPM       -6                    ; Create guard band of >> 6
                                    
    MOVL      XAR7,*XAR4            ; XAR4->coeff_ptr, XAR7=coeff_ptr    
    MOVZ      AR1,*+XAR4[4]         ; XAR4->coeff_ptr, AR1=cbindex
                                    
    MOVL      XAR6,*+XAR4[2]        ; XAR4->coeff_ptr, XAR6=dbuffer_ptr          
    MOVL      ACC,*XAR6             ; ACC = -:X 
    MOV       AH,@AL                ; ACC = X:X 
    MOV       AL,*+XAR4[6]          ; ACC = X:Input  
                                    
    MOVL      *XAR6%++,ACC          ; Store in data array and inc circ address 
    MOVL      *+XAR4[2],XAR6        ; XAR4->coeff_ptr, update the dbuffer pointer
                                    
    MOV       ACC,*+XAR4[5]<<15     ; AR0=cbindex
    MOVZ      AR0,AH                ; AR0=order/2
                                    
    ZAPA                            ; Zero the ACC, P registers and OVC counter
    ;; <<VC140828 - debug only
    ;;.asg	  0, N
    ;;.loop
    ;;DMAC      ACC:P,*XAR6%++,*XAR7++  ; XT = *+XAR6[AR1%++], Temp = *XAR7++
    ;;                                  ; ACC = (XT.MSW*Temp.MSW) << PM (>> -6)
    ;;                                  ; P   = (XT.LSW*Temp.LSW) << PM (>> -6)
    ;;.eval    N + 1, N                 ; increment N
    ;;.break   N = (RPT_COUNT+1)
    ;;.endloop
    ;; VC140828>> 
    
    RPT       AR0
 || DMAC      ACC:P,*XAR6%++,*XAR7++
              
    ADDL      ACC,P                 ; Add the two sums with shift 
                                    
    MOVW      DP,#PosSatVal         
    MINL      ACC,@PosSatVal        ; Saturate result 
                                    
    MOVW      DP,#NegSatVal         
    MAXL      ACC,@NegSatVal        
                                    
    MOVH      *+XAR4[7],ACC<<7      ; Store saturated result (Q15) 
              
    SPM       0
              
    POP       XAR1 
    CLRC      OVM
    LRETR      
    
;;#############################################################################
;;  End of File
;;#############################################################################
