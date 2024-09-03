//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Division: signed int (32-bit) / signed short (16-bit)
//! \author Vishal Coelho (adapted from original by Prasanth V.)
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
FASTRTS_FILENUM(21)

//*****************************************************************************
// FID_i32byi16_t
//*****************************************************************************
void FID_i32byi16_t(const int32_t num, const int16_t den, 
                           int32_t *p_quo, int16_t *p_rem)
{
    int16_t i;
    static int16_t iter = 1;

    // R3H = denominator (sign-extend)
    R3.H.i32 = den;
    // R1H = numerator
    R1.H.i32 = num;
    
    // Take the absolute value of the numerator and denominator 
    // flag.TF = sign(num) ^ sign(den)
    // flag.NI = sign(num)
    // Zero out R2.H
    ABSI32DIV32(&R3.H, &R1.H, &R2.H, &status_flag);    

    for(i = 0; i < 8; i++)
    {
        SUBC4UI32 (&R3.H, &R1.H, &R2.H, &status_flag);
    }
    
    // if flag.TF == 1, quotient = -quotient
    // if flag.NI == 1, remainder = -remainder
    NEGI32DIV32(&R1.H, &R2.H, &status_flag);
    
    // Save the quotient and remainder
    *p_rem = (int16_t)(R2.H.i32);
    *p_quo = R1.H.i32;
    
#ifdef _DEBUG
    printf("#%4u: %11d / %11d -> Q = %11d, R = %11d\n", 
            iter, num, den, *p_quo, *p_rem);
#endif //_DEBUG

    iter++;
}

//*****************************************************************************
// FID_i32byi16_m
//*****************************************************************************
void FID_i32byi16_m(const int32_t num, const int16_t den, 
                           int32_t *p_quo, int16_t *p_rem)
{
    int16_t i;
    static int16_t iter = 1;

    // R3H = denominator (sign-extend)
    R3.H.i32 = den;
    // R1H = numerator
    R1.H.i32 = num;
    
    // Take the absolute value of the numerator and denominator 
    // flag.TF = sign(num) ^ sign(den)
    // flag.NI = sign(num)
    // Zero out R2.H
    ABSI32DIV32(&R3.H, &R1.H, &R2.H, &status_flag);    

    for(i = 0; i < 8; i++)
    {
        SUBC4UI32 (&R3.H, &R1.H, &R2.H, &status_flag);
    }
    
    // if flag.TF == 1 and flag.ZI == 0, quotient += 1, 
    //                                   remainder = divisor - remainder
    // if flag.TF == 1, quotient = -quotient
    // if flag.NI ^ flag.TF == 1, remainder = -remainder
    MNEGI32DIV32(&R3.H, &R1.H, &R2.H, &status_flag);
    
    // Save the quotient and remainder
    *p_rem = (int16_t)(R2.H.i32);
    *p_quo = R1.H.i32;
    
#ifdef _DEBUG
    printf("#%4u: %11d / %11d -> Q = %11d, R = %11d\n", 
            iter, num, den, *p_quo, *p_rem);
#endif //_DEBUG

    iter++;
}

//*****************************************************************************
// FID_i32byi16_e
//*****************************************************************************
void FID_i32byi16_e(const int32_t num, const int16_t den, 
                           int32_t *p_quo, int16_t *p_rem)
{
    int16_t i;
    static int16_t iter = 1;

    // R3H = denominator (sign-extend)
    R3.H.i32 = den;
    // R1H = numerator
    R1.H.i32 = num;
    
    // Take the absolute value of the numerator and denominator 
    // flag.TF = sign(num) ^ sign(den)
    // flag.NI = sign(num)
    // Zero out R2.H
    ABSI32DIV32(&R3.H, &R1.H, &R2.H, &status_flag);    

    for(i = 0; i < 8; i++)
    {
        SUBC4UI32 (&R3.H, &R1.H, &R2.H, &status_flag);
    }
    
    // if flag.NI == 1 and flag.ZI == 0, quotient += 1, 
    //                                   remainder = divisor - remainder
    // if flag.TF == 1, quotient = -quotient
    ENEGI32DIV32(&R3.H, &R1.H, &R2.H, &status_flag);
    
    // Save the quotient and remainder
    *p_rem = (int16_t)(R2.H.i32);
    *p_quo = R1.H.i32;
    
#ifdef _DEBUG
    printf("#%4u: %11d / %11d -> Q = %11d, R = %11d\n", 
            iter, num, den, *p_quo, *p_rem);
#endif //_DEBUG

    iter++;
}



// End of File
