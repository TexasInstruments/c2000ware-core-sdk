//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Fast Fourier Transform Windowing
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################



//*****************************************************************************
// the includes
//*****************************************************************************
#include "fft.h"
#include <math.h>

//*****************************************************************************
// defines
//*****************************************************************************
DSP_FILENUM(30)

//*****************************************************************************
// FFT_bitReverseIndex()
//*****************************************************************************
uint32_t FFT_bitReverseIndex(uint32_t idx, uint16_t nbits)
{    
    // Locals
    // exchange every adjacent bit
    idx = ((idx & 0xAAAAAAAA) >> 1)  | ((idx & 0x55555555) << 1);
    // exchange every bit pair       
    idx = ((idx & 0xCCCCCCCC) >> 2)  | ((idx & 0x33333333) << 2);
    // exchange every nibble         
    idx = ((idx & 0xF0F0F0F0) >> 4)  | ((idx & 0x0F0F0F0F) << 4);
    // exchange every byte           
    idx = ((idx & 0xFF00FF00) >> 8)  | ((idx & 0x00FF00FF) << 8);
    // exchange every word
    idx = ((idx & 0xFFFF0000) >> 16) | ((idx & 0x0000FFFF) << 16);
    // Shift right to get only nbits
    idx >>= (32 - nbits);
    
    return(idx);    
}

// End of File
