//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Sine
//! \author Vishal Coelho 
//! \date   19-Aug-2015
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
FASTRTS_FILENUM(2)

#if USE_FPU64 == 1
#define A0            ( 1.0)
#define A1            (-0.5)
#define A2            (-0.166666666666667)
#define A3            ( 0.041666666666667)
#define A4            ( 0.008333333333333)
#else //USE_FPU32 == 1
#define A0            ( 1.0F)
#define A1            (-0.5F)
#define A2            (-0.166666666666667F)
#endif //USE_FPU64 == 1
//*****************************************************************************
// FastRTS_sin
//*****************************************************************************
fsize_t FastRTS_sin(const fsize_t theta, const fsize_t *tbl)
{
    // Locals
    int32_t k;
    fsize_t x, kf, res;
    const fsize_t *S = &tbl[0];
    const fsize_t *C = &tbl[SINCOS_TBLSIZE/4U];
    
    // Calculate the floating point index into the table
    kf = theta * RAD_ISTEP;
    // Calculate the signed integer index into the table
    k = (int32_t)(kf);
    // Calculate the fractional portion of theta that lies
    // between two table indices
    x = (kf - k) * RAD_STEP;
    // Negative values must wrap around and access the table from the end
    k = k & (SINCOS_TBLSIZE - 1U);
#if USE_FPU64 == 1
    // The sine is given by the Taylor Series Expansion of the sine
    res = S[k] + x*(A0*C[k] + 
                 x*(A1*S[k] + 
                 x*(A2*C[k] + 
                 x*(A3*S[k] + 
                 x*(A4*C[k])))));
#else //USE_FPU32 == 1
    // The sine is given by the Taylor Series Expansion of the sine
    res = S[k] + x*(A0*C[k] + x*(A1*S[k] + A2*x*C[k]));
#endif //USE_FPU64 == 1
#ifdef _DEBUG
    // Debugging message
    printf("theta=%f, kf=%f, k=%d, x=%f, C[k]=%f, S[k]=%f, res=%f\n", 
           theta, kf, k, x, C[k], S[k], res);
#endif
    return(res);
}

// End of File
