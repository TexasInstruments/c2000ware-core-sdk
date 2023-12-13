;;#############################################################################
;;! \file source/vector/iabs_SP_CV_2.asm
;;!
;;! \brief  C-Callable index of maximum value of an even length  real array
;;! \author David M. Alter
;;! \date   07/20/11
;;
;; HISTORY:
;;   07/20/11 - original (D. Alter)
;;
;; DESCRIPTION: C-Callable inverse absolute value of an even length complex 
;;              vector.
;;
;; FUNCTION: 
;;   extern void iabs_SP_CV_2(float32 *y, const complex_float *x, 
;;                           const Uint16 N);
;;
;; USAGE:       iabs_SP_CV_2(y, x, N);
;;
;; PARAMETERS:  float32 *y = output array
;;              complex_float *x = input array
;;              Uint16 N = length of x and y arrays (must be even)
;;
;; RETURNS:     none
;;
;; BENCHMARK:   15*N+22 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be even.
;;   2) The type 'complex_float' is defined as
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
        .asg iabs_SP_CV_2, _iabs_SP_CV_2
        .endif
    
        .global _iabs_SP_CV_2
        .text

_iabs_SP_CV_2:
;Save the utilized save on entry registers
        MOV32       *SP++, R4H          ;save R4H on stack
        MOV32       *SP++, R5H          ;save R5H on stack
        MOV32       *SP++, R6H          ;save R6H on stack
        MOV32       *SP++, R7H          ;save R7H on stack

;---Main loop.  Unroll once to eliminate delay slots.  Code that follows
;---has the two loop iterations heavily interleaved.  Code comments use
;---the notation x1, x2 to differentiate between loop iterations.
        LSR         AL, #1              ;Divide N by 2
        ADDB        AL, #-1             ;Subtract 1 from N since RPTB is 'n-1' 
                                        ;times
        RPTB        end_loop, @AL       
                                        
;Compute the magnitude squared          
        MOV32       R0H, *XAR5++        ;R0H = x1_re
        MPYF32      R1H, R0H, R0H       ;R1H = x1_re * x1_re
        || MOV32    R2H, *XAR5++        ;R2H = x1_im
    
        MOV32       R4H, *XAR5++        ;R4H = x2_re
        MPYF32      R5H, R4H, R4H       ;R5H = x2_re * x2_re]
        || MOV32    R6H, *XAR5++        ;R6H = x2_im
                                        
        MPYF32      R3H, R2H, R2H       ;R3H = x1_im * x_im1
        MPYF32      R7H, R6H, R6H       ;R7H = x2_im * x_im2
        ADDF32      R0H, R1H, R3H       ;R0H = (x1_re * x1_re) + (x1_im * x1_im)
        ADDF32      R4H, R5H, R7H       ;R4H = (x2_re * x2_re) + (x2_im * x2_im)

;Compute 1/sqrt.  Use the code from the DSP28 Fast FPU Library!
        EISQRTF32   R1H,R0H             ;R1H = Ye1 = Estimate(1/sqrt(X1))        
        EISQRTF32   R5H,R4H             ;R5H = Ye2 = Estimate(1/sqrt(X2))        
        MPYF32      R2H,R0H,#0.5        ;R2H = X1*0.5
        MPYF32      R6H,R4H,#0.5        ;R6H = X2*0.5
        MPYF32      R3H,R1H,R1H         ;R3H = Ye1*Ye1
        MPYF32      R7H,R5H,R5H         ;R7H = Ye2*Ye2
        MPYF32      R3H,R3H,R2H         ;R3H = Ye1*Ye1*X1*0.5
        MPYF32      R7H,R7H,R6H         ;R7H = Ye2*Ye2*X2*0.5
        SUBF32      R3H,#1.5,R3H        ;R3H = 1.5 - Ye1*Ye1*X1*0.5
        SUBF32      R7H,#1.5,R7H        ;R7H = 1.5 - Ye2*Ye2*X2*0.5
        MPYF32      R1H,R1H,R3H         ;R1H = Ye1 = Ye1*(1.5 - Ye1*Ye1*X1*0.5)
        MPYF32      R5H,R5H,R7H         ;R5H = Ye2 = Ye2*(1.5 - Ye2*Ye2*X2*0.5)
                                        
        MPYF32      R3H,R1H,R2H         ;R3H = Ye1*X1*0.5
        MPYF32      R7H,R5H,R6H         ;R4H = Ye2*X2*0.5
        MPYF32      R3H,R1H,R3H         ;R3H = Ye1*Ye1*X1*0.5
        MPYF32      R7H,R5H,R7H         ;R7H = Ye2*Ye2*X2*0.5
        SUBF32      R3H,#1.5,R3H        ;R3H = 1.5 - Ye1*Ye1*X1*0.5
        SUBF32      R7H,#1.5,R7H        ;R7H = 1.5 - Ye2*Ye2*X2*0.5
        MPYF32      R0H,R1H,R3H         ;R0H = Ye1 = Ye1*(1.5 - Ye1*Ye1*X1*0.5)
        MPYF32      R4H,R5H,R7H         ;R4H = Ye2 = Ye2*(1.5 - Ye2*Ye2*X2*0.5)
                                        
        MOV32       *XAR4++, R0H        ;store the first result to memory
        MOV32       *XAR4++, R4H        ;store the second result to memory

end_loop:

;Restore the utilized save on entry register
        MOV32       R7H, *--SP          ;restore R7H from stack
        MOV32       R6H, *--SP          ;restore R6H from stack
        MOV32       R5H, *--SP          ;restore R5H from stack
        MOV32       R4H, *--SP          ;restore R4H from stack

;Finish up
        LRETR                           ;return

;end of function iabs_SP_CV_2()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
