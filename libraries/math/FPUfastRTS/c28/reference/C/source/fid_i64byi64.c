//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Division: signed (64-bit) / signed (64-bit)
//! \author Vishal Coelho (adapted from original by Prasanth V.)
//! \date   12-Apr-2016
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
FASTRTS_FILENUM(16)

//*****************************************************************************
// FID_i64byi64_t
//*****************************************************************************
void FID_i64byi64_t(const int64_t num, const int64_t den, 
                           int64_t *p_quo, int64_t *p_rem)
{
    int16_t i;
    static int16_t iter = 1;

    // R3 = denominator
    R3.i64 = den;
    // R1 = numerator
    R1.i64 = num;
    
    // Take the absolute value of the numerator and denominator 
    // flag.TF = sign(num) ^ sign(den)
    // flag.NI = sign(num)
    // Zero out R2
    ABSI64DIV64(&R3, &R1, &R2, &status_flag);    

    for(i = 0; i < 32; i++)
    {
        SUBC2UI64 (&R3, &R1, &R2, &status_flag);
    }
    
    // if flag.TF == 1, quotient = -quotient
    // if flag.NI == 1, remainder = -remainder
    NEGI64DIV64(&R1, &R2, &status_flag);
    
    // Save the quotient and remainder
    *p_rem = R2.i64;
    *p_quo = R1.i64;
    
#ifdef _DEBUG
    printf("#%4u: %20ld / %20ld -> Q = %20ld, R = %20ld\n", 
            iter, num, den, *p_quo, *p_rem);
#endif //_DEBUG

    iter++;
}

//*****************************************************************************
// FID_i64byi64_m
//*****************************************************************************
void FID_i64byi64_m(const int64_t num, const int64_t den, 
                           int64_t *p_quo, int64_t *p_rem)
{
     int16_t i;
    static int16_t iter = 1;

    // R3 = denominator
    R3.i64 = den;
    // R1 = numerator
    R1.i64 = num;
    
    // Take the absolute value of the numerator and denominator 
    // flag.TF = sign(num) ^ sign(den)
    // flag.NI = sign(num)
    // Zero out R2
    ABSI64DIV64(&R3, &R1, &R2, &status_flag);    

    for(i = 0; i < 32; i++)
    {
        SUBC2UI64 (&R3, &R1, &R2, &status_flag);
    }
    
    // if flag.TF == 1 and flag.ZI == 0, quotient += 1, 
    //                                   remainder = divisor - remainder
    // if flag.TF == 1, quotient = -quotient
    // if flag.NI ^ flag.TF == 1, remainder = -remainder
    MNEGI64DIV64(&R3, &R1, &R2, &status_flag);
    
    // Save the quotient and remainder
    *p_rem = R2.i64;
    *p_quo = R1.i64;
    
#ifdef _DEBUG
    printf("#%4u: %20ld / %20ld -> Q = %20ld, R = %20ld\n", 
            iter, num, den, *p_quo, *p_rem);
#endif //_DEBUG

    iter++;
}

//*****************************************************************************
// FID_i64byi64_e
//*****************************************************************************
void FID_i64byi64_e(const int64_t num, const int64_t den, 
                           int64_t *p_quo, int64_t *p_rem)
{
     int16_t i;
    static int16_t iter = 1;

    // R3 = denominator
    R3.i64 = den;
    // R1 = numerator
    R1.i64 = num;
    
    // Take the absolute value of the numerator and denominator 
    // flag.TF = sign(num) ^ sign(den)
    // flag.NI = sign(num)
    // Zero out R2
    ABSI64DIV64(&R3, &R1, &R2, &status_flag);    

    for(i = 0; i < 32; i++)
    {
        SUBC2UI64 (&R3, &R1, &R2, &status_flag);
    }
    
    // if flag.NI == 1 and flag.ZI == 0, quotient += 1, 
    //                                   remainder = divisor - remainder
    // if flag.TF == 1, quotient = -quotient
    ENEGI64DIV64(&R3, &R1, &R2, &status_flag);
    
    // Save the quotient and remainder
    *p_rem = R2.i64;
    *p_quo = R1.i64;
    
#ifdef _DEBUG
    printf("#%4u: %20ld / %20ld -> Q = %20ld, R = %20ld\n", 
            iter, num, den, *p_quo, *p_rem);
#endif //_DEBUG

    iter++;
}



// End of File
