;;#############################################################################
;;! \file source/vector/mac_SP_CVxCV.asm
;;!
;;! \brief  C-Callable multiply-and-accumulate of a complex vector and a 
;;              complex vector
;;! \author Vishal Coelho
;;! \date   07/18/16
;;
;; HISTORY:
;;    - original (V. Coelho)
;;
;; DESCRIPTION: C-Callable multiply-and-accumulate of a complex vector and a 
;;              complex vector
;;               y_re = sum(w_re[i]*x_re[i] - w_im[i]*x_im[i])
;;               y_im = sum(w_re[i]*x_im[i] + w_im[i]*x_re[i])
;;
;; FUNCTION: 
;;   extern complex_float mac_SP_CVxCV(const complex_float *w,
;;                          const complex_float *x, const uint16_t N)
;;
;; USAGE:       y = mac_SP_CVxCV(w, x, N);
;;
;; PARAMETERS:  complex_float *w  = first input complex array
;;              complex_float *x  = second input complex array
;;              uint16_t N        = length of w and x arrays
;; 
;; RETURNS:     complex_float y = complex result
;; 
;; BENCHMARK:   5*N + 24 cycles (including the call and return)
;; 
;; NOTES:
;;   1) N must be at least 3, and can be odd or even.
;;   2) The inputs and return value are of type 'complex_float':
;; 
;;      typedef struct {
;;         float32 dat[2];
;;      } complex_float;
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
    .if __TI_EABI__
    .asg mac_SP_CVxCV, _mac_SP_CVxCV
    .endif
    
    .global _mac_SP_CVxCV
    .text
    
_mac_SP_CVxCV:
    MOV32   *SP++, R7H              ; save R7H to the stack
    MOV32   *SP++, R6H              ; save R6H to the stack
    MOV32   *SP++, R5H              ; save R5H to the stack
    MOV32   *SP++, R4H              ; save R4H to the stack
    
    SUBB    AL, #3                  ; AL = N-3 (-1 for RPTB, -2 since two
                                    ; iterations are done seperately from the
                                    ; main loop)        
    MOV32   R0H, *XAR4++            ;      R0H = w_re[0]
    MOV32   R1H, *XAR5++            ;      R1H = x_re[0]
    MPYF32  R3H, R0H, R1H           ; *|   R3H = w_re[0]*x_re[0]
 || MOV32   R4H, *XAR4++            ;  |   R4H = w_im[0]
    MPYF32  R7H, R4H, R1H           ; 1|*| R7H = w_im[0]*x_re[0]
 || MOV32   R5H, *XAR5++            ;  | | R5H = x_im[0]
    MPYF32  R2H, R4H, R5H           ; *|1| R2H = w_im[0]*x_im[0]
 || MOV32   R1H, *XAR5++            ;  | | R1H = x_re[i]   
    MPYF32  R6H, R0H, R5H           ; 1|*| R6H = w_re[0]*x_im[0]
 || MOV32   R0H, *XAR4++            ;  | | R0H = w_re[i]
    NEGF32  R2H, R2H                ;  |1| R2H = -(w_im[0]*x_im[0]) 
    
    ;; Main Loop
    .align  2
    RPTB    _mac_SP_CVxCV_loop, AL
    ; R3H = (w_re[i]*x_re[i])-(w_im[i]*x_im[i]), R2H = w_re[i]*x_re[i]
    MACF32  R3H, R2H, R2H, R0H, R1H ; *| 
 || MOV32   R4H, *XAR4++            ;  |   R4H = w_im[i]
    ; R7H = (w_im[i]*x_re[i])+(w_re[i]*x_im[i]), R6H = w_im[i]*x_re[i]
    MACF32  R7H, R6H, R6H, R4H, R1H ; 1|*|
 || MOV32   R5H, *XAR5++            ;  | | R5H = x_im[i]
    ; R3H += (w_re[i]*x_re[i]), R2H = w_im[i]*x_im[i]
    MACF32  R3H, R2H, R2H, R4H, R5H ; *|1|
 || MOV32   R1H, *XAR5++            ;  | | R1H = x_re[i+1]
    ; R7H += (w_im[i]*x_re[i]), R6H = w_re[i]*x_im[i]
    MACF32  R7H, R6H, R6H, R0H, R5H ; 1|*|
 || MOV32   R0H, *XAR4++            ;  | | R0H = w_re[i+1]
    NEGF32  R2H, R2H                ;  |1| R2H = -(w_im[i]*x_im[i])
_mac_SP_CVxCV_loop:

    ;; Last Iteration
    ; R3H = (w_re[i]*x_re[i])-(w_im[i]*x_im[i]), R2H = w_re[i]*x_re[i]
    MACF32  R3H, R2H, R2H, R0H, R1H ; *| 
 || MOV32   R4H, *XAR4++            ;  |   R4H = w_im[i]
    ; R7H = (w_im[i]*x_re[i])+(w_re[i]*x_im[i]), R6H = w_im[i]*x_re[i]
    MACF32  R7H, R6H, R6H, R4H, R1H ; 1|*|
 || MOV32   R5H, *XAR5++            ;  | | R5H = x_im[i]
    ; R3H += (w_re[i]*x_re[i]), R2H = w_im[i]*x_im[i]
    MACF32  R3H, R2H, R2H, R4H, R5H ; *|1|
 || MOV32   R4H, *--SP              ;  | | restore R4H
    ; R7H += (w_im[i]*x_re[i]), R6H = w_re[i]*x_im[i]
    MACF32  R7H, R6H, R6H, R0H, R5H ; 1|*|
 || MOV32   R5H, *--SP              ;  | | restore R5H
    NEGF32  R2H, R2H                ;  |1| R2H = -(w_im[i]*x_im[i])
    ADDF32  R3H, R3H, R2H           ; *| | R3H += -(w_im[i]*x_im[i]) {y_re}
    ADDF32  R7H, R7H, R6H           ; 1|*| R7H += (w_re[i]*x_im[i])  {y_im}
 || MOV32   R6H, *--SP              ;  | | restore R6H    
 	.if		__TI_EABI__
    MOV32   R0H, R3H                ;  |1| save y_re
    MOV32   R1H, R7H                ;  | | save y_im
    .else
    MOV32   *+XAR6[0], R3H          ;  |1| save y_re
    MOV32   *+XAR6[2], R7H          ;  | | save y_im
    .endif
    MOV32   R7H, *--SP              ;  | | restore R7H
    
    LRETR               ; return

;end of function _mac_SP_CVxCV()
;*********************************************************************

    .end

;;#############################################################################
;;  End of File
;;#############################################################################
