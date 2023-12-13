;;#############################################################################
;;! \file source/vector/mpy_SP_RVxCV.asm
;;!
;;! \brief  C-Callable multiplication of a real vector and a complex vector
;;! \author David M. Alter
;;! \date   07/14/11
;;
;; HISTORY:
;;   07/14/11 - original (D. Alter)
;;
;; DESCRIPTION: C-Callable multiplication of a real vector and a complex vector
;;              y_re[i] = x[i]*w_re[i]
;;              y_im[i] = x[i]*w_im[i]
;;
;; FUNCTION:   
;;   extern void mpy_SP_RVxCV(complex_float *y, const complex_float *w, 
;;                            const float32 *x, const Uint16 N)
;;
;; USAGE:       mpy_SP_RVxCV(y, x, c, N);
;;
;; PARAMETERS:  complex_float *y = result complex array
;;              complex_float *w = input complex array
;;              float32 *x  = input real array
;;              Uint16 N = length of w, x, and y arrays
;;
;; RETURNS:     none
;;
;; BENCHMARK:   5*N + 15 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be at least 2.
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
        .asg mpy_SP_RVxCV, _mpy_SP_RVxCV
        .endif
    
        .global _mpy_SP_RVxCV
        .text
_mpy_SP_RVxCV:
        MOVL        XAR6, *-SP[4]   ;XAR6 = &x
        ADDB        AL, #-2         ;Subtract 2 from N since RPTB is 'n-1' 
                                    ;times, and last iteration done separately
                                   
        MOV32       R0H, *XAR5++    ;load first w_re value
                                   
;---Main loop                      
        RPTB        end_loop, @AL  
                                   
        MOV32       R1H, *XAR6++    ;load next x value
                                   
        MPYF32      R2H, R1H, R0H   ;y_re[i] = x[i]*w_re[i]
        || MOV32    R0H, *XAR5++    ;load next w_im
                                   
        MPYF32      R3H, R1H, R0H   ;y_re[i] = x[i]*w_re[i]
        || MOV32    R0H, *XAR5++    ;load next w_re
                                   
        MOV32       *XAR4++, R2H    ;store y_re[i]
        MOV32       *XAR4++, R3H    ;store y_im[i]
end_loop:

;--- Last iteration done seperately to avoid possible pointer overrun into 
;    undefined memory
        MOV32       R1H, *XAR6      ;load next x value
                                    
        MPYF32      R2H, R1H, R0H   ;y_re[i] = x[i]*w_re[i]
        || MOV32    R0H, *XAR5      ;load next w_im
                                    
        MPYF32      R3H, R1H, R0H   ;y_re[i] = x[i]*w_re[i]
                                    
        MOV32       *XAR4++, R2H    ;store y_re[i]
        MOV32       *XAR4, R3H      ;store y_im[i]
                                    
;Finish up                          
        LRETR                       ;return

;end of function _mpy_SP_RVxCV()
;*********************************************************************

       .end

;;#############################################################################
;;  End of File
;;#############################################################################
