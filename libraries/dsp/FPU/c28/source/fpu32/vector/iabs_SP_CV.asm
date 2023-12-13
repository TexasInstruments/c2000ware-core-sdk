;;#############################################################################
;;! \file source/vector/iabs_SP_CV.asm
;;!
;;! \brief  C-Callable inverse absolute value of a complex vector
;;! \author David M. Alter
;;! \date   07/20/11
;;
;; HISTORY:
;;   07/20/11 - original (D. Alter)
;;
;; DESCRIPTION: C-Callable inverse absolute value of a complex vector
;;
;; FUNCTION: 
;;   extern void iabs_SP_CV(float32 *y, const complex_float *x, const Uint16 N)
;;
;; USAGE:       iabs_SP_CV(y, x, N);
;;
;; PARAMETERS:  float32 *y = results array
;;              complex_float *x = input array
;;              Uint16 N = length of x and y arrays
;;
;; RETURNS:     none
;;
;; BENCHMARK:   25*N+13 cycles (including the call and return)
;;
;; NOTES:
;;   1) The type 'complex_float' is defined as
;;
;;      typedef struct {
;;         float32 dat[2];
;;      } complex_float;
;;
;;    Element dat[0] is the real part, dat[1] is the imag part.
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
        .asg iabs_SP_CV, _iabs_SP_CV
        .endif
    
        .global _iabs_SP_CV
        .text

_iabs_SP_CV:
        ADDB        AL, #-1         ;Subtract 1 from N since RPTB is 'n-1' 
                                    ;times

;---Main loop
        RPTB        end_loop, @AL

;Compute the magnitude squared
        MOV32       R0H, *XAR5++    ;R0H = x_re
        MPYF32      R1H, R0H, R0H   ;R1H = x_re * x_re
        || MOV32    R2H, *XAR5++    ;R2H = x_im
        MPYF32      R3H, R2H, R2H   ;R3H = x_im * x_im (also delay slot for 
                                    ;MPYF32||MOV32)
        NOP                         ;delay slot
        ADDF32      R0H, R1H, R3H   ;R0H = (x_re * x_re) + (x_im * x_im)
        NOP                         ;delay slot

;Compute 1/sqrt.  Use the code from the DSP28 Fast FPU Library!
        EISQRTF32   R1H,R0H         ;R1H = Ye = Estimate(1/sqrt(X))        
        MPYF32      R2H,R0H,#0.5    ;R2H = X*0.5
        MPYF32      R3H,R1H,R1H     ;R3H = Ye*Ye
        NOP                         ;delay slot
        MPYF32      R3H,R3H,R2H     ;R3H = Ye*Ye*X*0.5
        NOP                         ;delay slot
        SUBF32      R3H,#1.5,R3H    ;R3H = 1.5 - Ye*Ye*X*0.5
        NOP                         ;delay slot
        MPYF32      R1H,R1H,R3H     ;R2H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP                         ;delay slot

        MPYF32      R3H,R1H,R2H     ;R3H = Ye*X*0.5
        NOP                         ;delay slot
        MPYF32      R3H,R1H,R3H     ;R3H = Ye*Ye*X*0.5
        NOP                         ;delay slot
        SUBF32      R3H,#1.5,R3H    ;R3H = 1.5 - Ye*Ye*X*0.5
        NOP                         ;delay slot
        MPYF32      R0H,R1H,R3H     ;R0H = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
        NOP                         ;delay slot

        MOV32       *XAR4++, R0H    ;store the result to memory

end_loop:

;Finish up
        LRETR                       ;return

;end of function iabs_SP_CV()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
