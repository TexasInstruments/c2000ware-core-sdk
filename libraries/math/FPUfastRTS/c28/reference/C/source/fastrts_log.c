//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  natural logarithm
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
FASTRTS_FILENUM(29)

//*****************************************************************************
// FastRTS_log
//*****************************************************************************
fsize_t FastRTS_log(const fsize_t x)
{
    // Locals
    fsize_t x_a    = fabs_t(x);
    //  A floating point number is represented as 
    //       X=[S]1.M*2^E 
    // where S is the  sign bit, M the mantissa, and E the biased exponent. 
    // The natural logarithm of such a number is given by
    //      log(X)= log(1.M)+ E*log(2)
    union fisize_t{
        fsize_t f;
        isize_t i;
    }x_exp, x_mant, x_mant_bk;
    
    x_exp.f  = x_a;
    x_mant.f = x_a;
    
    // Separate the exponent of X and store as a float
#if USE_FPU32==1
    x_exp.f =  (fsize_t)(x_exp.i >> (FLT_MANT_DIG - 1)) - FPUEXPBIAS;
#else //USE_FPU64==1
    x_exp.f =  (fsize_t)(x_exp.i >> (DBL_MANT_DIG - 1)) - FPUEXPBIAS;    
#endif //USE_FPU32
    
    fsize_t  log_exp = x_exp.f * FPULOG2;
    
    // Separate the mantissa (1.M), and then the fractional portion Xm = M
    // ANDing the argument with FPULOG_TABLE_MASK1 will zero out the sign
    // and most significant exponent bit, while ORing with FPULOG_TABLE_MASK2
    // will set the exponent to 127 (single) or 1023 (double)
    //
    // Consider 10 = 1.25x2^3. In single precision float the leading 1 of the 
    // significand is implicit and the exponent is biased around 127, so its 
    // physical representation is 
    //   31|30           23|22                                        0|
    //   +-+---------------+-------------------------------------------+
    //   |0|1|0|0|0|0|0|1|0|0|1|0                 ...........         0|
    //   +-+---------------+-------------------------------------------+
    //    S| biased exp    | mantissa                                  |
    //     | E = 127+3=131 | 0.25                                      |
    //
    // X & 0x3FFFFFFF
    //   31|30           23|22                                        0|
    //   +-+---------------+-------------------------------------------+
    //   |0|0|0|0|0|0|0|1|0|0|1|0                 ...........         0|
    //   +-+---------------+-------------------------------------------+
    //    S| biased exp    | mantissa                                  |
    //     | E = 2         | 0.25                                      |
    // (X & 0x3FFFFFFF) | 0x3F800000
    //   31|30           23|22                                        0|
    //   +-+---------------+-------------------------------------------+
    //   |0|0|1|1|1|1|1|1|1|0|1|0                 ...........         0|
    //   +-+---------------+-------------------------------------------+
    //    S| biased exp    | mantissa                                  |
    //     | E = 127       | 0.25                                      |    
    // Now the value of this float (after removing exponent bias)
    //   = 1.25 * 2^(127-127(BIAS)) = 1.25
    // We have extracted just the mantissa (or significand)
    x_mant.i = (x_mant.i & (isize_t)FPULOG_TABLE_MASK1) | 
                           (isize_t)FPULOG_TABLE_MASK2;
    // Get the fractional part of the mantissa
    x_mant_bk  = x_mant; // backup
    x_mant.f = x_mant.f - 1.0;
    
    // The value of log(1.M) = A0 + M*(A1 + M*A2), where M is the 
    // fractional part of the mantissa extracted in the previous step
    // The values A0, A1, A2 are a triplet that is obtained from the 
    // lookup table; the table has LOG_TBLSIZE such triplets
    isize_t i = (isize_t)(x_mant.f * LOG_TBLSIZE);
    i *= 3;
    
    fsize_t A0 = FastRTS_logTable[i];
    fsize_t A1 = FastRTS_logTable[i + 1];
    fsize_t A2 = FastRTS_logTable[i + 2];
    
    fsize_t log_mant = A0 + x_mant.f*(A1 + x_mant.f*A2);
    
    fsize_t log_x    = log_exp + log_mant;
    
#ifdef _DEBUG
    // Debugging message
    printf("x=%f, x_exp=%f, x_mant=%f, log_exp=%f, log_mant=%f, log_x=%f\n", 
           x, x_exp.f, x_mant_bk.f, log_exp, log_mant, log_x);
#endif
    return(log_x);
}

// End of File
