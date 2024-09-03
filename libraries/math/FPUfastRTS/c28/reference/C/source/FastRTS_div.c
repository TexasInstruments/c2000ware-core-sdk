//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Division
//! \author Vishal Coelho 
//! \date   24-Aug-2015
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
FASTRTS_FILENUM(6)


#if USE_FPU64 == 1
#define A0            ( 2.0)
#else //USE_FPU32 == 1
#define A0            ( 2.0F)
#endif //USE_FPU64 == 1
//*****************************************************************************
// FastRTS_div
//*****************************************************************************
fsize_t FastRTS_div(const fsize_t num, const fsize_t den)
{
    // Locals
    fsize_t xn, res;
    
    // Calculate the estimate of 1/den
    // NOTE: this is a call to the division routine of the std C library, 
    // and is therefore a very accurate estimate ...need to replace this 
    // with an algorithm to give the rough 1/den
    xn = 1/den;
    // Do the newton raphson iterations, 2 for single precision, 4 for 
    // double precision. Each iteration improves precision quadratically
    // i.e. each time you do it you double the number of accurate bits
    xn = xn*(A0 - xn*den);
    xn = xn*(A0 - xn*den);
#if USE_FPU64 == 1
    xn = xn*(A0 - xn*den);
    xn = xn*(A0 - xn*den);
#endif //USE_FPU64 == 1
    // Get the final result (num/den) by multiplying the estimate of the 
    // inverse with num
    res = num * xn;
#ifdef _DEBUG
    // Debugging message
    printf("num=%f, den=%f, res=%f\n", num, den, res);
#endif
    return(res);
}

// End of File
