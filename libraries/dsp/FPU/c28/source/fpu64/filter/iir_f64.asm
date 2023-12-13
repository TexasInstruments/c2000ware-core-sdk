;;#############################################################################
;;! \file source/fpu64/filter/iir_f64.asm
;;!
;;! \brief  Infinite Impulse Response Filter (Double Precision)
;;! \author Vishal Coelho
;;! \date   02/17/2016
;;
;;  This routine implements the Transposed Direct form II recursive 
;;  difference equation of an N pole-zero filter(IIR).   
;;
;; FUNCTIONS:
;;  void IIR_f64_init(IIR_f64_Handle) 
;;  void IIR_f64_calc(IIR_f64_Handle) 
;;  
;;  where IIR_f64_Handle is a pointer to a structure defined as:
;;
;;  typedef struct { 
;;      long double *p_coeff_A;  //!<  Pointer to the denominator coefficients
;;      long double *p_coeff_B;  //!<  Pointer to the numerator coefficients
;;      long double *p_dbuffer;  //!<  Delay buffer pointer
;;      long double *p_input;    //!<  Pointer to the latest input sample
;;      long double *p_output;   //!<  Pointer to the filter output
;;      long double *p_scale;    //!<  Pointer to the biquad(s) scale values
;;      uint16_t order;          //!<  Order of the filter
;;      void (*init)(void *);    //!<  Pointer to the initialization function
;;      void (*calc)(void *);    //!<  Pointer to the calculation function
;;  }IIR_f64;
;;
;; Difference Equation :
;;
;; The operations for each biquad, in order, is as follows 
;; 1. yn   = S*xn*B[0] + D[3] 
;; 2. D[2] = S*xn*B[1] + yn*A[1] + D[1]
;; 3. D[3] = D[2]
;; 4. D[0] = S*xn*B[2] + yn*A[2]
;; 5. D[1] = D[0]
;;      where
;;              yn =output sample of the filter at index n 
;;              xn =input sample of the filter at index n 
;;              D[x]=intermediate values stored in the delay buffer
;;              S = scale factor for a given biquad
;;
;; Transfer Function :
;;   The difference equation is split up into multiple Second-Order Sections
;;   (SOS). Each SOS represents a Biquad with the following transfer function                                 
;;                                  -1        -2
;;              Y(z)   b(0) + b(1) z  + b(2) z  
;;            ----- = ----------------------- 
;;             X(z)                -1       -2
;;                    a(0) + a(1) z  + a(2) z 
;;
;;   For a detailed treatment of Direct II Forms see
;;   [1]Digital Signal Processing, Proakis, J. G. and Manolakis, D. G.
;;      - Chapter 7
;;   [2]Understanding Digital Signal Processing 3rd ed, Lyons, R. G.
;;
;;     Network Diagram  : 
;;
;; xn------>(x)--->(+)--------------->yn
;;      |    ^      ^             |
;;      |    |      |D[3]         |
;;      |    B[0]  (z)            |
;;      |           ^             |
;;      |           |D[2]         |
;;      |-->(x)--->(+)<-----(x)---|
;;      |    ^      ^        ^    |
;;      |    |      |D[1]    |    |
;;      |    B[1]  (z)       A[1] |
;;      |           ^             |
;;      |           |D[0]         |
;;      --->(x)--->(+)<-----(x)----
;;           ^               ^
;;           |               |
;;           B[2]            A[2]
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

;; external references

;;*****************************************************************************
;; void IIR_f64_init(IIR_f64_Handle) 
;;
;; The initialization function will zero out the delay line buffer and the 
;; inputs. It takes a handle to the IIR_f64 object as an
;; argument
;;
;; Register Usage:
;;     AL  : loop counter
;;   XAR4  : arg(IIR_f64_Handle) 
;;   XAR5  : pointer to the delay line buffer
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg IIR_f64_init, _IIR_f64_init
    .endif
    
    .page
    .global _IIR_f64_init
    .sect   ".text"
_IIR_f64_init:
    .asmfunc
    ; The object pointer is incremented by 4 on entry to give the following
    ; offsets
    .asg    *XAR4++,   PTR_DBUFFER
    .asg    *+XAR4[0], PTR_INPUT
    .asg    *+XAR4[2], PTR_OUTPUT
    .asg    *+XAR4[6], ORDER
    ZAPA                        ; ACC:P = 0
    ADDB    XAR4, #4            ; XAR4 -> obj.p_dbuffer
    MOVL    XAR5, PTR_DBUFFER   ; XAR5 -> dbuffer
    MOV     ACC, ORDER << #3    ; ACC = order/2 * 4(delay elements per biquad)
                                ;       * 4 (double precision)
    ADDB    AL, #3              ; ACC = order*4 - 1
    RPT     AL                  ; Repeat nTaps (ACC+1) times
 || MOV     *XAR5++, #0         ; zero out delay line
    LRETR
    .endasmfunc
    .unasg  PTR_DBUFFER
    .unasg  PTR_INPUT
    .unasg  PTR_OUTPUT
    .unasg  ORDER
    
;;*****************************************************************************
;; void IIR_f64_calc(IIR_f64_Handle) 
;;
;; The function takes a handle to the IIR_f64 object as an argument. It gets
;; the current input from the object, runs the filter, and returns the output
;; to the object.
;;
;; Register Usage:
;;   XAR0: skip value for DL addressing   
;;   XAR1: points to input/output         
;;   XAR2:                                
;;   XAR3: points to the scale values     
;;   XAR4: points to the object           
;;   XAR5: points to the delay line       
;;   XAR6: points to coefficients A (den) 
;;   XAR7: points to coefficients B (num) 
;;     AH: repeat block counter           
;;      P:                                
;;   
;; Stack Usage:
;;
;;   |_______|<- Stack Pointer                    (SP)
;;   |_______|<- R7H                              (SP-2)
;;   |_______|<- R6H                              (SP-4)
;;   |_______|<- XAR3                             (SP-6)
;;   |_______|<- XAR1                             (SP-8)
;;   |_______|<- rpc calling function             (SP-10)
;;
;;*****************************************************************************
    .if __TI_EABI__
    .asg IIR_f64_calc, _IIR_f64_calc
    .endif
    
    .page
    .global _IIR_f64_calc
    .sect   ".text"
_IIR_f64_calc:
    .asmfunc
    .asg    *XAR4++,   PTR_COEFF_A
    .asg    *XAR4++,   PTR_COEFF_B
    .asg    *XAR4++,   PTR_DBUFFER
    .asg    *+XAR4[0], PTR_INPUT
    .asg    *+XAR4[2], PTR_OUTPUT
    .asg    *+XAR4[4], PTR_SCALE
    .asg    *+XAR4[6], ORDER
    
;;-----------------------------------------------------------------------------
;; Context Save
;;-----------------------------------------------------------------------------
    PUSH    XAR1
    PUSH    XAR3
    MOV32   *SP++, R6H
    MOV32   *SP++, R7H
    
    
    MOVL    XAR6, PTR_COEFF_A   ; XAR6 -> coefficients A (denominator)
    ADDB    XAR6, #4            ;      -> A[1]
    MOVL    XAR7, PTR_COEFF_B   ; XAR7 -> coefficients B (numerator)
    MOVL    XAR5, PTR_DBUFFER   ; XAR5 -> delay line buffer
    ADDB    XAR5, #14           ; XAR5 -> D[3].H
    MOVL    XAR3, PTR_SCALE     ; XAR3 -> stage scale factors
    MOVL    XAR1, PTR_INPUT     ; XAR1 -> input

;;-----------------------------------------------------------------------------
;; Biquad
;;-----------------------------------------------------------------------------
    ZAPA                        ; ACC:P = 0
    MOV     ACC, ORDER << 15    ; AH = order/2
    SUBB    AH, #1              ;    = order/2-1 (#biquads)
    MOV32   R3L, *+XAR1[0]      ; R3 = xn
    MOV32   R3H, *+XAR1[2]      ;
    MOVL    XAR1, PTR_OUTPUT    ; XAR1 -> output
    MOVB    XAR0, #8

    .lp_amode
    SETC    AMODE                ; C2xLP addressing mode
    .align  2
    RPTB    _IIR_f64_calc_biquad, AH
    MOV32   R1L, *XAR3++         ;      R1 = S[0]
    MOV32   R1H, *XAR3++         ;                      , XAR3->S[1]
    MPYF64  R0, R1, R3           ; *|   R0 = S[0]*xn
 || MOV32   R1L, *XAR7++         ;  |   R1 = B[0]       , ARP->XAR7
    MOV32   R1H, *++, ARP5       ; 1|                   , ARP->XAR5 XAR7->B[1]
    MOV32   R3H, *--             ; 2|   R3 = D[3]
    MPYF64  R2, R0, R1           ; *|   R2 = S[0]*xn*B[0]
 || MOV32   R3L, *0--            ;  |                   , XAR5->D[1]
    MOV32   R1L, *XAR7++         ; 1|   R1 = B[1]
    MOV32   R1H, *XAR7++         ; 2|                   , XAR7->B[2]
    ; R3 = S[0]*xn*B[0]+D[3], R7 = S[0]*xn*B[1]
    MACF64  R3, R2, R7, R0, R1   ; *|   
 || MOV32   R6L, *XAR5++         ;  |   R6 = D[1]
    MOV32   R6H, *XAR5++         ; 1|                   , XAR5->D[2]
    MOV32   R2L, *XAR6++         ; 2|   R2 = A[1]
    MOV32   R2H, *XAR6++         ;                      , XAR6->A[2]
    ; R7 = S[0]*xn*B[1]+D[1], R6 = yn*A[1]
    MACF64  R7, R6, R6, R3, R2   ; *| 
 || MOV32   R1L, *XAR7++         ;  |   R1 = B[2]
    MOV32   R1H, *XAR7++         ; 1|                   , XAR7->B'[0]
    NOP                          ; 2|
    ; R7 = S[0]*xn*B[1]+yn*A[1]+D[1], R1 = S[0]*xn*B[2]
    MACF64  R7, R6, R1, R0, R1   ; *|
 || MOV32   R2L, *XAR6++         ;  |   R2 = A[2]       , ARP->XAR6
    MOV32   R2H, *++, ARP5       ; 1|                   , ARP->XAR5 XAR6->A'[0]
    MPYF64  R2, R3, R2           ; 2|*| R2 = yn*A[2]
    MOV32   *, R7L               ;  |1| Save R7 to D[2]
    MOVDD32 R7L, *XAR5++         ;  |2| D[3].L=D[2].L   , ARP->XAR5
    ADDF64  R1, R1, R2           ; *|   R1 = S[0]*xn*B[2]+A[2]
    MOV32   *, R7H               ; 1|
    MOVDD32 R7H, *0--            ; 2|   D[3].H=D[2].H   , XAR5->D[0].H
    MOV32   *, R1H               ;      Save R1 to D[0]
    MOVDD32 R1H, *--             ;      D[1].H=D[0].H
    MOV32   *, R1L               ;
    MOVDD32 R1L, *               ;      D[1].L=D[0].L   , XAR5->D[0]
   ; Prepare for the next Biquad
    ADDB    XAR6, #4             ; XAR6->A'[1]
    ADDB    XAR5, #30            ; XAR1->D'[3].H
_IIR_f64_calc_biquad:  
    .c28_amode
    CLRC    AMODE                ; C28x addressing mode
    ; Store the output of the final biquad
    MOV32   *+XAR1[0], R3L
    MOV32   *+XAR1[2], R3H
;;-----------------------------------------------------------------------------
;; Context Restore
;;-----------------------------------------------------------------------------
    MOV32   R7H, *--SP
    MOV32   R6H, *--SP
    POP     XAR3
    POP     XAR1
    LRETR
    
    .endasmfunc
    .unasg  PTR_COEFF_A
    .unasg  PTR_COEFF_B
    .unasg  PTR_DBUFFER
    .unasg  PTR_INPUT
    .unasg  PTR_OUTPUT
    .unasg  PTR_SCALE
    .unasg  ORDER
    
;; End of File
