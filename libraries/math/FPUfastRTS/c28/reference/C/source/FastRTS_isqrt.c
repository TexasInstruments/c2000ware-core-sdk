//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Inverse Square Root
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
// C2000Ware v6.00.00.00
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
FASTRTS_FILENUM(5)


#if USE_FPU64 == 1
#define A0            ( 1.5)
#define A1            ( 0.5)
#else //USE_FPU32 == 1
#define A0            ( 1.5F)
#define A1            ( 0.5F)
#endif //USE_FPU64 == 1
//*****************************************************************************
// FastRTS_isqrt
//*****************************************************************************
fsize_t FastRTS_isqrt(const fsize_t x)
{
    // Locals
    fsize_t xn;
    
    // Calculate the estimate of the inverse square root
    // NOTE: this is a call to the sqrt of the std C library, and is therefore
    // a very accurate estimate ...need to replace this with an algorithm to
    // give the rough 1/sqrt(x)
    xn = 1/sqrt(x);
    // Do the newton raphson iterations, 2 for single precision, 4 for 
    // double precision. Each iteration improves precision quadratically
    // i.e. each time you do it you double the number of accurate bits
    xn = xn*(A0 - xn*xn*x*A1);
    xn = xn*(A0 - xn*xn*x*A1);
#if USE_FPU64 == 1
    xn = xn*(A0 - xn*xn*x*A1);
    xn = xn*(A0 - xn*xn*x*A1);
#endif //USE_FPU64 == 1
#ifdef _DEBUG
    // Debugging message
    printf("x=%f, res=%f\n", x, xn);
#endif
    return(xn);
}

// End of File
