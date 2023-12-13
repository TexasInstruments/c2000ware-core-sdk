;;#############################################################################
;;! \file source/fpu32/div_f32.asm
;;!
;;! \brief  Fast 32-bit floating-point division for the C28x + Floating-Point 
;;!         Unit.
;;! \author N/A
;;! \date   N/A
;;
;; DESCRIPTION:
;;
;;    This function computes a 32-bit floating point division A/B.
;;
;; FUNCTIONS:
;;
;;    This funciton (FS$$DIV) will be called when 32-bit floating point 
;;    division is performed.  That is:
;;    
;;    float32 A,B,Y;
;;    ...
;;    <A & B initalized>
;;    ...
;;    Y = A/B;  // Call to FS$$DIV
;;
;; ASSUMPTIONS:
;; 
;;
;; ALGORITHM:
;;
;;              Ye = Estimate(1/B);
;;              Ye = Ye*(2.0 - Ye*B)
;;              Ye = Ye*(2.0 - Ye*B)
;;              Y  = A*Ye
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

        .page
        .text
        .if __TI_EABI__
        .asg    __c28xabi_divf, FS$$DIV
        .endif
		.global     FS$$DIV

FS$$DIV:

        EINVF32     R2H, R1H            ; R2H = Ye = Estimate(1/B)
        CMPF32      R0H, #0.0           ; Check if A == 0
        MPYF32      R3H, R2H, R1H       ; R3H = Ye*B
        NOP
        SUBF32      R3H, #2.0, R3H      ; R3H = 2.0 - Ye*B       
        NOP        
        MPYF32      R2H, R2H, R3H       ; R2H = Ye = Ye*(2.0 - Ye*B)
        NOP
; Next line: if commented out: 0.0/0.0 = 0.0
;            if not commented: 0.0/0.0 = infinity
;       MOV32       R2H, R0H, EQ        ; If A == 0.0, Ye = 0.0
        MPYF32      R3H, R2H, R1H       ; R3H = Ye*B
        CMPF32      R1H, #0.0           ; Check if B == 0.0
        SUBF32      R3H, #2.0, R3H      ; R3H = 2.0 - Ye*B
        NEGF32      R0H, R0H, EQ        ; Fixes sign for A/0.0
        MPYF32      R2H, R2H, R3H       ; R2H = Ye = Ye*(2.0 - Ye*B)
        NOP
        MPYF32      R0H, R0H, R2H       ; R0H = Y = A*Ye = A/B
        LRETR
       	.endasmfunc
    
;; End of File
