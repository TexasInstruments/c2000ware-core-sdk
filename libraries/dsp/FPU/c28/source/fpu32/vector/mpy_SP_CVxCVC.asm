;;#############################################################################
;;! \file source/vector/mpy_SP_CVxCVC.asm
;;!
;;! \brief  C-Callable multiplication of a complex vector (w) and the complex 
;;!         conjugate of a complex vector (x)
;;! \author David M. Alter
;;! \date   07/15/11
;;
;; HISTORY:
;;   07/15/11 - original (D. Alter)
;;
;; DESCRIPTION: C-Callable multiplication of a complex vector (w) and the 
;;              complex conjugate of a complex vector (x)
;;              xconj_re[i] = x_re[i]
;;              xconj_im[i] = - x_im[i]
;;              y_re[i] = w_re[i]*x_re[i] - w_im[i]*xconj_im[i]
;;              y_im[i] = w_re[i]*xconj_im[i] + w_im[i]*x_re[i]
;;
;; FUNCTION: 
;;   extern void mpy_SP_CVxCVC(complex_float *y, const complex_float *w, 
;;                     const complex_float *x, const Uint16 N)
;;
;; USAGE:       mpy_SP_CVxCVC(y, w, x, N);
;;
;; PARAMETERS:  complex_float *y = result complex array
;;              complex_float *w = input complex array #1
;;              complex_float *x = input complex array #2
;;              Uint16 N = length of w, x, and y arrays
;;
;; RETURNS:     none
;;
;; BENCHMARK:   11*N + 16 cycles (including the call and return)
;;
;; NOTES:
;;   1) The inputs and return value is of type 'complex_float':
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
        .asg mpy_SP_CVxCVC, _mpy_SP_CVxCVC
        .endif
    
        .global _mpy_SP_CVxCVC
        .text
_mpy_SP_CVxCVC:
        MOVL        XAR6, *-SP[4]    ;XAR6 = &x
        MOV32       *SP++, R4H       ;save R4H on stack
        ADDB        AL, #-1          ;Subtract 1 from N since RPTB is 'n-1' 
                                     ;times
                                   
;---Main loop                      
        RPTB        end_loop, @AL  
                                   
        MOV32       R0H, *XAR5++     ;R0H = w_re
        MOV32       R2H, *XAR6++     ;R2H = x_re
        MPYF32      R3H, R0H, R2H    ;R3H = w_re * x_re
        || MOV32    R1H, *XAR5++     ;R1H = w_im
        MPYF32      R2H, R1H, R2H    ;R2H = w_im * x_re
        || MOV32    R4H, *XAR6++     ;R4H = x_im
        NEGF32      R4H, R4H         ;R4H = -x_im (complex conjugate of x)
        MPYF32      R1H, R1H, R4H    ;R1H = w_im * x_im
        MPYF32      R0H, R0H, R4H    ;R0H = w_re * x_im
        SUBF32      R3H, R3H, R1H    ;R3H = (w_re * x_re) - (w_im * x_im)
        ADDF32      R2H, R2H, R0H    ;R2H = (w_im * x_re) + (w_re * x_im)
        MOV32       *XAR4++, R3H     ;store y_re[i]
        MOV32       *XAR4++, R2H     ;store y_im[i]
end_loop:

;Finish up
        MOV32       R4H, *--SP       ;restore R4H from stack
        LRETR                        ;return

;end of function _mpy_SP_CVxCVC()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
