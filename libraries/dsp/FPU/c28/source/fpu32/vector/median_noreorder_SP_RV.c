//#############################################################################
//! \file median_noreorder_SP_RV.c
//!
//! \brief  Median of a real valued array of floats (no reordering).
//! \author David M. Alter
//! \date   07/01/11
//
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


#include "fpu_vector.h"

//===========================================================================
// Function: float median_noreorder_SP_RV(const float *, uint16_t)
//===========================================================================
//
// Median of a real valued array of floats. Input array is preserved.
//
// Dependencies:      median_SP_RV(), memcpy_fast()
// Usage:             z = median_noreorder_SP_CV(x, N);
// Passed Parameters: float *x = pointer to array of real input values
//                    uint16_t N = size of x array
// Return value:      float z = the median of x[]
// Notes:
// 1) This function simply makes a local copy of the input array, and then
//    calls median_SP_CV() using the copy.
// 2) The length of the copy of the input array is allocated at compile time
//    by the constant 'K' defined in the code.  If the passed parameter N
//    is greater than K, memory corruption will result.  A better way to do
//    this is to dynamically allocate the copy array at run time using
//    malloc().  This is work for the future. 
//
//---------------------------------------------------------------------------

#define        K    256         // WARNING: K must be at least as large as N.

//***************************************************************************
float median_noreorder_SP_RV(const float *x, const uint16_t N)
{
    float x_copy[K], y;

    memcpy_fast(x_copy, x, N<<1);     // Copy 2*N 16-bit words on C28x
    y = median_SP_RV(x_copy, N);      // Call median()
    return(y);
} // end of median_noreorder_SP_RV()

// End of file
