;;*****************************************************************************
;;! \file source/vcu2/vcu2_crc_utils.asm
;;!
;;! \brief  8-bit CRC
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
;;
;;*****************************************************************************
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; CRC Routine defines


;;*****************************************************************************
;; macros
;;*****************************************************************************

;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _CRC_reset
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text

;; \brief Workaround to the silicon issue of first VCU calculation on power up being
;; erroneous
;; 
;; Details Due to the internal power-up state of the VCU module, it is possible 
;; that the first CRC result will be incorrect. This condition applies to the 
;; first result from each of the eight CRC instructions. 
;; This rare condition can only occur after a power-on reset, but will not
;; necessarily occur on every power on. A warm reset will not cause this condition 
;; to reappear.
;; Workaround(s) The application can reset the internal VCU CRC logic by 
;; performing a CRC calculation of a single byte in the initialization routine. 
;; This routine only needs to perform one CRC calculation and can use any of the 
;; CRC instructions
;; 
;; 
_CRC_reset:
    MOVB      XAR7, #0
    VCRC8L_1  *XAR7
    VCRCCLR
    LRETR

;; End of file
