;;#############################################################################
;;! \file source/fpu32/memcpy_fastrts.asm
;;!
;;! \brief  Fast memcpy
;;! \author N/A  
;;! \date   N/A
;;
;;
;;DESCRIPTION:
;;
;;   This function does a fast memory copy
;;   Note: This function is not part of the normal RTS library.
;;
;;FUNCTIONS:
;;
;;   void memcpy_fastrts(void *dst, void *src, uint16_t num_words)
;;
;;ASSUMPTIONS:
;;
;;
;;ALGORITHM:
;;
;;             
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

;;		dst: 		XAR4
;;		src: 		XAR5
;;		num_bytes:  AL

        .page
        .if __TI_EABI__
        .asg        memcpy_fastrts, _memcpy_fastrts
        .endif
        .global     _memcpy_fastrts
        .text
_memcpy_fastrts:
		MOVL XAR7, @XAR5
		DEC @AL
		RPT @AL
	||	PREAD *XAR4++, *XAR7
        LRETR
        .endasmfunc
    
;; End of File
