//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  exponent
//! \author Vishal Coelho 
//! \date   04-Jan-2017
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
FASTRTS_FILENUM(28)

//*****************************************************************************
// FastRTS_exp
//*****************************************************************************
fsize_t FastRTS_exp(const fsize_t x)
{
    // Locals
    fsize_t x_a    = fabs_t(x);
    // Separate the integer and fractional portion of the input
    isize_t x_i    = (isize_t)floor(x_a);
    fsize_t x_f    = x_a - floor(x_a);
    // Get e^integer(x) from the table
    fsize_t e_intx = FastRTS_expTable[x_i];
    // Calculate e^(fraction) by using the Taylor series expansion for
    // exponents
    //   x
    // e   = 1 + x*(1+x/2*(1+x/3*(1+x/4*(1+x/5*(1+x/6*(1+x/7)+...)))))
    // 
    fsize_t e_fracx = 1 + x_f*(1 + x_f*FPUINV2  *
                              (1 + x_f*FPUINV3  *
                              (1 + x_f*FPUINV4  *
                              (1 + x_f*FPUINV5  *
                              (1 + x_f*FPUINV6  *
#if USE_FPU32 == 1                              
                              (1 + x_f*FPUINV7))))));
#else  //USE_FPU64 == 1 
                              (1 + x_f*FPUINV7  *
                              (1 + x_f*FPUINV8  *
                              (1 + x_f*FPUINV9  *
                              (1 + x_f*FPUINV10 *
                              (1 + x_f*FPUINV11 *
                              (1 + x_f*FPUINV12 *
                              (1 + x_f*FPUINV13 *
                              (1 + x_f*FPUINV14)))))))))))));
#endif //USE_FPU32 == 1 
                    
    //  The result,  e^{x} = e^{integer}*e^{fraction}
    fsize_t e_x = e_intx * e_fracx;
    
    // If x was negative, calculate the inverse of the result
    if(x < 0.0)
    {
        e_x = 1/e_x;
    }

#ifdef _DEBUG
    // Debugging message
    printf("x=%f, x_i=%d, x_f=%f, e_intx=%e, e_fracx=%f, e_x=%e\n", 
           x, x_i, x_f, e_intx, e_fracx, e_x);
#endif
    return(e_x);
}

// End of File
