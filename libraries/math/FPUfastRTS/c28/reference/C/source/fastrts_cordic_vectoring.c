//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  CORDIC Vectoring Mode Kernel
//! \author Vishal Coelho 
//! \date   14-Nov-2016
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
#include "fastrts_cordic.h"
#include "fastrts_assert.h"
//*****************************************************************************
// defines
//*****************************************************************************
FASTRTS_FILENUM(26)

//*****************************************************************************
// FastRTS_CORDIC_vectoringKernel
//*****************************************************************************
void FastRTS_CORDIC_vectoringKernel(hnd_CORDIC_t hc)
{
    // Locals
    uint16_t i;
    isize_t x_i         = FastRTS_CORDIC_getx_i(hc);
    isize_t y_i         = FastRTS_CORDIC_gety_i(hc);
    isize_t z_i         = FastRTS_CORDIC_getz_i(hc);
    const fsize_t *p_at = FastRTS_CORDIC_getAtanTblPtr(hc);
    uint16_t N          = FastRTS_CORDIC_getN(hc);
    isize_t x_n, y_n;
    fsize_t at;
    
    for (i = 0U; i < N; i++)
    {
        at = GET_TBL_HEX_VAL(p_at, i);
        if(y_i >= 0)
        {
            // Rotate clockwise to meet the x-axis
            x_n = x_i + (y_i >> i);
            y_n = y_i - (x_i >> i);
            z_i = z_i -  FTOIQMAX(at);
        }
        else
        {
            // Rotate counter clockwise to meet the x-axis
            x_n = x_i - (y_i >> i);
            y_n = y_i + (x_i >> i);
            z_i = z_i +  FTOIQMAX(at);
        }
        // Set the x, y for the next iteration
        x_i = x_n;
        y_i = y_n;

#ifdef _DEBUG
        printf("Iteration = %d, x_i=%20.17f, y_i=%20.17f,"
               " z_i=%20.17f t_i=%20.17f\n",
               i, IQMAXTOF(x_i), IQMAXTOF(y_i), IQMAXTOF(z_i), at);
#endif // _DEBUG
    }
    // Set the object x_i, y_i, -z_i
    FastRTS_CORDIC_setx_i(hc,  x_n);
    FastRTS_CORDIC_sety_i(hc,  y_n);
    FastRTS_CORDIC_setz_i(hc, -z_i);
}

// End of File
