;;#############################################################################
;;! \file source/vector/rnd_SP_RS.asm
;;!
;;! \brief  C-Callable unbiased rounding of a floating point scalar
;;! \author David M. Alter
;;! \date   07/20/11
;;! 
;; FUNCTION:    extern float32 rnd_SP_RS(const float32 x);
;;
;; USAGE:       y = rnd_SP_RS(x);
;;
;; PARAMETERS:  float32 x = input value
;;
;; RETURNS:     float32 y = result
;;
;; BENCHMARK:   18 cycles (including the call and return)
;;
;; NOTES:
;;   1) numerical examples:
;;      rnd_SP_RS(+4.4) = +4.0
;;      rnd_SP_RS(-4.4) = -4.0
;;      rnd_SP_RS(+4.5) = +5.0
;;      rnd_SP_RS(-4.5) = -5.0
;;      rnd_SP_RS(+4.6) = +5.0
;;      rnd_SP_RS(-4.6) = -5.0
;;   2) The C version of this, y = floor(x+0.5) takes 78 cycles using
;;      the rts2800_fpu32 library in c28x cgtools v6.0.1.
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
        .asg    rnd_SP_RS, _rnd_SP_RS
        .endif
    
        .global _rnd_SP_RS
        .text

_rnd_SP_RS:
        CMPF32  R0H, #0.0         ;determine if x is positive or negative
        MOVST0  NF                ;copy NF flag to N bit in ST0
        BF      negative, LT      ;branch if x is negative

;x is positive
        ADDF32  R0H, #0.5, R0H    ;add 0.5 to x
        NOP                       ;delay slot for ADDF32
        FRACF32 R1H, R0H          ;R1H = fraction of R0H
        NOP                       ;delay slot for FRACF32
        SUBF32  R0H, R0H, R1H     ;subtract the fraction from x+0.5
        LRETR                     ;return

;x is negative
negative:
        ADDF32  R0H, #-0.5, R0H   ;subtract 0.5 from x
        NOP                       ;delay slot for ADDF32
        FRACF32 R1H, R0H          ;R1H = fraction of R0H
        NOP                       ;delay slot for FRACF32
        SUBF32  R0H, R0H, R1H     ;subtract the fraction from x+0.5
        LRETR                     ;return

;end of function rnd_SP_RS()
;*********************************************************************

       .end
       

;;#############################################################################
;;  End of File
;;#############################################################################
