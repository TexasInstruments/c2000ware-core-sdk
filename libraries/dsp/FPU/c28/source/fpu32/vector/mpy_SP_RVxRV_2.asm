;;#############################################################################
;;! \file source/vector/mpy_SP_RVxRV_2.asm
;;!
;;! \brief  C-Callable multiplication of a real vector and a real vector
;;! \author David M. Alter
;;! \date   07/15/11
;;
;; HISTORY:
;;    - original (D. Alter)
;;
;; DESCRIPTION: C-Callable multiplication of a real vector and a real vector
;;              y[i] = w[i]*x[i]
;;
;; FUNCTION: 
;;   extern void mpy_SP_RVxRV_2(float32 *y, const float32 *w, const float32 *x, 
;;                              const Uint16 N)
;;
;; USAGE:       mpy_SP_RVxRV_2(y, w, x, N);
;;
;; PARAMETERS:  float32 *y = result real array
;;              float32 *w = input real array #1
;;              float32 *x  = input real array #2
;;              Uint16 N = length of w, x and y arrays
;;
;; RETURNS:     none
;;
;; BENCHMARK:   3*N + 17 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be even and at least 4.
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
        .asg mpy_SP_RVxRV_2, _mpy_SP_RVxRV_2
        .endif
    
        .global _mpy_SP_RVxRV_2
        .text
_mpy_SP_RVxRV_2:
        MOVL        XAR6, *-SP[4]    ;XAR6 = &x
        LSR         AL, #1           ;divide N by 2
        ADDB        AL, #-2          ;subtract 2 from N since RPTB is 'n-1' 
                                     ;times and last iteration done separately
                                     
        MOV32       R0H, *XAR5++     ;load first w
        MOV32       R1H, *XAR6++     ;load first x
                                     
;---Main loop                        
        RPTB        end_loop, @AL    
                                     
        MPYF32       R2H, R0H, R1H   ;y[i] = w[i]*x[i]
        || MOV32     R0H, *XAR5++    ;load next w
        MOV32        R1H, *XAR6++    ;load next x
        MOV32        *XAR4++, R2H    ;store y[i]
                                     
        MPYF32       R2H, R0H, R1H   ;y[i] = w[i]*x[i]
        || MOV32     R0H, *XAR5++    ;load next w
        MOV32        R1H, *XAR6++    ;load next x
        MOV32        *XAR4++, R2H    ;store y[i]

end_loop:

;--- Last iteration done seperately to avoid possible pointer overrun into 
;    undefined memory
        MPYF32       R2H, R0H, R1H   ;y[i] = w[i]*x[i]
        || MOV32     R0H, *XAR5++    ;load next w
        MOV32        R1H, *XAR6++    ;load next x
        MOV32        *XAR4++, R2H    ;store y[i]
                                     
        MPYF32       R2H, R0H, R1H   ;y[i] = w[i]*x[i]
        NOP                          ;delay slot
        MOV32        *XAR4++, R2H    ;store y[i]
                                     
;Finish up                           
        LRETR                        ;return
                                     
;end of function _mpy_SP_RVxRV_2()
;*********************************************************************

       .end

;;#############################################################################
;;  End of File
;;#############################################################################
