;;#############################################################################
;;! \file source/vector/memcpy_fast.asm
;;!
;;! \brief Optimized memory copy, src->dest.
;;! \author David M. Alter
;;! \date   07/06/11
;;
;;
;; HISTORY:
;;   07/06/11 - original (D. Alter)
;;   10/23/14 - Added note about non-interruptibility and no support for
;;              above 22 bit address. (D. Alter)
;;
;; DESCRIPTION: Optimized memory copy, src->dest.
;;
;; FUNCTION: 
;;   extern void memcpy_fast(void* dst, const void* src, Uint16 N);
;;
;; USAGE:       memcpy_fast(dst, src, N);
;;
;; PARAMETERS:  void* dst = pointer to destination
;;              const void* src = pointer to source
;;              N = number of 16-bit words to copy
;;
;; RETURNS:     none
;;
;; BENCHMARK:   1 cycle per copy + ~20 cycles of overhead (including
;;   the call and return).  This assumes src and dst are located in
;;   different internal RAM blocks.
;;
;; NOTES:
;;   1) The function checks for the case of N=0 and just returns if true.
;;   2) This function is not interruptible.  Use memcpy_fast_far instead for 
;;      interruptibility.
;;   3) This function does not support memory above 22 bits address.
;;      For input data above 22 bits address, use memcpy_fast_far instead.
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
        .asg memcpy_fast, _memcpy_fast
        .endif
    
        .global _memcpy_fast
        .text

_memcpy_fast:
        ADDB    AL, #-1                ;Repeat "N-1" times
        BF      done, NC               ;Branch if N was zero
        MOVL    XAR7, XAR5             ;XAR7 = XAR5 = dst
        RPT     @AL
    ||  PREAD   *XAR4++, *XAR7         ;Do the copy

;Finish up
done:
        LRETR                          ;return

;end of function memcpy_fast()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
