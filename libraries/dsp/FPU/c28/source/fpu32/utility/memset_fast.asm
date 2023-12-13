;;#############################################################################
;;! \file source/vector/memset_fast.asm
;;!
;;! \brief Optimized memory set, int->dest
;;! \author David M. Alter
;;! \date   07/15/11
;;
;; HISTORY:
;;   07/15/11 - original (D. Alter)
;;
;; DESCRIPTION: Optimized memory set, int->dest.
;;
;; FUNCTION:    extern void memset_fast(void*, int16, Uint16);
;;
;; USAGE:       memset_fast(dst, value, N);
;;
;; PARAMETERS:  void* dst = pointer to destination
;;              int16 value = initialization value
;;              N = number of 16-bit words to initialize
;;
;; RETURNS:     none
;;
;; BENCHMARK:   1 cycle per copy + ~20 cycles of overhead (including
;;   the call and return).  This assumes src and dst are located in
;;   different internal RAM blocks.
;;
;; NOTES:
;;   1) The function checks for the case of N=0 and just returns if true.
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
        .asg memset_fast, _memset_fast
        .endif
    
        .global _memset_fast
        .text

_memset_fast:
        ADDB        AH, #-1         ;Repeat "N-1" times
        BF          done, NC        ;Branch if N was zero
        RPT         @AH
    ||  MOV         *XAR4++, AL     ;Initialize the memory

;Finish up
done:
        LRETR                       ;return

;end of function memset_fast()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
