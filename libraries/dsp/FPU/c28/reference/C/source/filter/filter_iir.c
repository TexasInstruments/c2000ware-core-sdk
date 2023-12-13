//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Infinite Impulse Response Filter
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
#include "filter.h"
#include <math.h>

//*****************************************************************************
// defines
//*****************************************************************************
DSP_FILENUM(23)

//*****************************************************************************
// FILTER_runIIR()
// ALGORITHM:
//
// Difference Equation :
//
// The operations for each biquad, in order, is as follows 
// 1. yn  = xn*b(0) + q(3) 
// 2. q(2) = xn*b(1) + yn*a(1) + q(1)
// 3. q(3) = q(2)
// 4. q(0) = xn*b(2) + yn*a(2)
// 5. q(1) = q(0)
//      where
//              yn  =output sample of the filter at index n 
//              xn  =input sample of the filter at index n 
//			   q(n) =intermediate values stored in the delay buffer
//
// Transfer Function :
//   The difference equation is split up into multiple Second-Order Sections
//   (SOS). Each SOS represents a Biquad with the following transfer function                                 
//                                  -1        -2
//              Y(z)   b(0) + b(1) z  + b(2) z  
//			  ----- = ----------------------- 
//			   X(z)	               -1       -2
//					  a(0) + a(1) z  + a(2) z 
//
//   For a detailed treatment of Direct II Forms see
//   [1]Digital Signal Processing, Proakis, J. G. and Manolakis, D. G. - Ch 7
//   [2]Understanding Digital Signal Processing 3rd ed, Lyons, R. G.
//
//     Network Diagram  : 
//
// xn------>(x)--->(+)--------------->yn
//      |    ^      ^             |
//      |    |      |q(3)         |
//      |    b(0)  (z)            |
//      |           ^             |
//      |           |q(2)         |
//      |-->(x)--->(+)<-----(x)---|
//      |    ^      ^        ^    |
//      |    |      |q(1)    |    |
//      |    b(1)  (z)       a(1) |
//      |           ^             |
//      |           |q(0)         |
//      --->(x)--->(+)<-----(x)----
//           ^               ^
//           |               |
//           b(2)            a(2)
//*****************************************************************************
void FILTER_runIIR(IIRHandle hnd)
{
    // Locals
    uint16_t j;
    fsize_t *b = IIR_getCoefficientsPtr(hnd);
    fsize_t *a = b + 3UL;
    fsize_t *q = IIR_getDelayLinePtr(hnd);
    fsize_t *s = IIR_getScaleValPtr(hnd);
    fsize_t yn = (fsize_t)0.0;
    fsize_t xn = IIR_getInput(hnd);
    
    for(j = 0U; j < IIR_getnSOS(hnd); j++)
    {
        xn   = s[j] * xn; //Multiply the scaling factor for this stage
        yn   = xn*b[0] + q[3]; 
        q[2] = xn*b[1] - yn*a[1] + q[1];
        q[3] = q[2];
        q[0] = xn*b[2] - yn*a[2];
        q[1] = q[0];
        // Set input for the next biquad
        xn   = yn;
        // Set delay line for the next biquad
        q = q + 4UL;
        // Set coefficients for the next biquad
        a = a + 6UL;
        b = b + 6UL;
    }
    
    // write the final output to the structure object
    IIR_setOutput(hnd, yn);
#ifdef _DEBUG
    printf("output = %10.7f \n", IIR_getOutput(hnd));
#endif
}

// End of File
