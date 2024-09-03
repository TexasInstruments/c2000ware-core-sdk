//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Arctangent(y,x)
//! \author Vishal Coelho 
//! \date   26-Aug-2015
//! 
//
//  Group:            C2000
//  Target Family:    $DEVICE$
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "fastrts.h"
#include "fastrts_assert.h"
//*****************************************************************************
// defines
//*****************************************************************************
FASTRTS_FILENUM(8)

//*****************************************************************************
// FastRTS_atan2
//*****************************************************************************
fsize_t FastRTS_atan2(const fsize_t y, const fsize_t x, 
                      const fsize_t *tbl)
{
    // Locals
    int32_t k;
    fsize_t r, a0, a1, a2, res;
    
    // Reduce the argument to the range [-1,1]
    if(fabs_t(x) >= fabs_t(y))
    {
        r = fabs_t(y)/fabs_t(x);
    }
    else //(fabs_t(x) < fabs_t(y))
    {
        r = fabs_t(x)/fabs_t(y);
    }
    
    // Calculate the index into the lookup table, the table 
    // is a set of 3-tuples
    k = (uint16_t)(r * ARCTAN2_TBLSIZE);
    k = k * 3U;
    // Get the coefficients
    a0 = tbl[k++];
    a1 = tbl[k++];
    a2 = tbl[k++];
    // Calculate the arctangent for the first quadrant
    // 0 to +pi/4 (x,y > 0 && |x| >= |y|)
    res = a0 + r*(a1 + a2*r);
    
    if((x >= 0) && (fabs_t(x) < fabs_t(y)))
    {
        // The argument y/x lies in the first Quadrant (pi/4 to pi/2)
        // Since |y|>|x|, we calculate arctan(|x|/|y|). We use the identity,
        // arctan(y/x) = pi/2 - arctan(|x|/|y|)
        res = PI_O_2 - res;
    }
    if ((x < 0) && (fabs_t(x) < fabs_t(y)))
    {
        // The argument y/x lies in the Second quadrant (pi/2 to 3pi/4)
        // Since |y|>|x| and x<0, we calculate arctan(|x|/|y|). We use the
        // identity,
        // arctan(y/x) = pi/2 - arctan(-|x|/|y|)
        //             = pi/2 - -arctan(|x|/|y|)
        //             = pi/2 + arctan(|x|/|y|)
        res = PI_O_2 + res;
    }
    if ((x < 0) && (fabs_t(x) >= fabs_t(y)))
    {
        // The argument y/x lies in the Second quadrant (3pi/4 to pi)
        // Since |y|<=|x| and x<0, we calculate arctan(|y|/|x|). We use the
        // identity,
        // arctan(y/x) = arctan(|y|/-|x|)
        //             = -arctan(|y|/|x|)
        // We want to represent angles in the range [0,pi] as positive,
        // we must therefore "unwrap" this angle
        // arctan(y/x) = pi - arctan(|y|/|x|)
        res = PI - res;
    }
    if ( y < 0 ) 
    {
        // If the argument y/x lies in the third and fourth quadrants,
        // it is the exact mirror of what we have already calculated
        res = -res;
    }
#ifdef _DEBUG
    // Debugging message
    printf("y=%f, x=%f, r=%f, k=%d, a0=%f, a1=%f, a2=%f, res=%f\n", 
           y, x, r, k, a0, a1, a2, res);
#endif
    return(res);
}

// End of File
