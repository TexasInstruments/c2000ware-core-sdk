***********************************************************************
* Function: __IQNtoa_get_frac_c
*
* Description: Called by _IQNtoa().  Not for user use.
*
* DSP: TMS320F28x
*
* Author: David M. Alter
*
* Include files: stdio.h
*
* Function Prototype: extern char _IQNtoa_get_frac_c(unsigned long);
*
* Usage: character = _IQNtoa_get_frac_c(value);
*
* Input Parameters:
*    value = fraction in I0Q32 format
*
* Return Value:
*    character = the 1st base-10 digit in the fraction
*
* Notes:
*  1) This is an internal function to the IQmath library.  It is not
*     intended to be called by the user.
*
* History: December 23, 2004 - original (DA)
*
***********************************************************************
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

		.def __IQNtoa_get_frac_c
		.sect "IQmath"

__IQNtoa_get_frac_c:

		MOVB	XAR0, #10				;XAR0 = 10
		MOVL	XT, XAR0				;XT = 10
		QMPYUL	P, XT, @ACC				;P = XT*ACC upper 32-bits
		MOVL	@ACC, P					;ACC = the value we want
		LRETR							;return

		.end
		
;----------------------------------------------------------------------
; End of file
;----------------------------------------------------------------------
