//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Division: double (64-bit) / double (64-bit)
//! \author Vishal Coelho
//! \date   15-Apr-2016
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
#include "fid.h"
#include "fastrts_assert.h"
//*****************************************************************************
// defines
//*****************************************************************************
FASTRTS_FILENUM(22)

//*****************************************************************************
// FID_f64byf64
//*****************************************************************************
void FID_f64byf64(const double num, const double den, 
                        double *p_quo)
{
    int16_t i;
    static int16_t iter = 1;

    // R3 = denominator
    R3.f64 = den;
    // R1 = numerator
    R2.f64 = num;
    
    // extract the sign and exponent of the quotient
    PREDIVF64(&R0.H, &R2, &R1, &R3, &status_flag);    

    for(i = 0; i < 19; i++)
    {
        SUBC3F64 (&R2, &R1, &R3, &status_flag);
    }
    
    // Round and re-insert the sign and exponent of the quotient
    POSTDIVF64(&R1, &R0.H, &status_flag);
    
    // Save the quotient
    *p_quo = R1.f64;
    
#ifdef _DEBUG
    printf("#%4u: %20e / %20e -> Q = %20e\n", iter, num, den, *p_quo);
#endif //_DEBUG

    iter++;
}


// End of File
