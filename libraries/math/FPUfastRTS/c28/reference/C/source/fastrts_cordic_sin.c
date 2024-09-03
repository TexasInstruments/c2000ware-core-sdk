//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Sine (CORDIC)
//! \author Vishal Coelho 
//! \date   10-Nov-2016
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
FASTRTS_FILENUM(23)

//*****************************************************************************
// FastRTS_CORDIC_sin
//*****************************************************************************
fsize_t FastRTS_CORDIC_sin(const fsize_t theta)
{
    // Locals
    uint16_t i;
    bool f_needFinalRotation = false;
    fsize_t sign_z = SIGN(theta);
    CORDIC_t cordic;
    hnd_CORDIC_t h_cordic = &cordic;
    
    isize_t x_n, y_n;
    fsize_t sf;
    
    // All values are in IQMAX format
    sf              = GET_TBL_HEX_VAL(FastRTS_CORDIC_scaleTbl, 
                                      MAX_CORDIC_ITERATIONS-1);
    isize_t x_i     = FTOIQMAX(sf);
    isize_t y_i     = IQMAX(0);
    isize_t z_i;
    
    //<<VC161117: Don't need to actually do a final rotation
    // // Check if the angle lies beyond the maximum decomposable CORDIC angle
    // // theta_max
    // if(fabs_t(theta) > THETA_MAX)
    // {
    //     z_i     = FTOIQMAX(theta - sign_z*THETA_MAX);
    //     f_needFinalRotation = true;
    // }
    // else
    // {
    //     z_i     = FTOIQMAX(theta);
    // }
    //  VC161117>>

    if(fabs_t(theta) <= PI_O_2)
    {
        // First quadrant for +ive theta and fourth quadrant for -ive theta
        z_i = FTOIQMAX(fabs_t(theta));
    }
    else if(fabs_t(theta) <= PI)
    {
        // Second quadrant for +ive theta and third quadrant for -ive theta
        z_i    = FTOIQMAX(PI - fabs_t(theta));
        x_i    = -x_i;
        sign_z = -sign_z;
    }
    else if(fabs_t(theta) <= THREEPI_O_2)
    {
        // Third quadrant for +ive theta and second quadrant for -ive theta
        z_i = FTOIQMAX(fabs_t(theta) - PI);
        x_i = -x_i;
    }
    else
    {
        // Fourth quadrant for +ive theta and first quadrant for -ive theta
        z_i    = FTOIQMAX(TWOPI - fabs_t(theta));
        sign_z = -sign_z;
    }
#ifdef _DEBUG
    printf("-------------------------theta=%20.17f---------------------------"
           "----\n"
           "Starting point x_0 = %20.17f, y_0 = %20.17f, z_0 = %20.17f\n",
           theta, IQMAXTOF(x_i), IQMAXTOF(y_i), IQMAXTOF(z_i));
#endif // _DEBUG

    // Set the object parameters
    FastRTS_CORDIC_setx_i(h_cordic, x_i);
    FastRTS_CORDIC_sety_i(h_cordic, y_i);
    FastRTS_CORDIC_setz_i(h_cordic, z_i);
    FastRTS_CORDIC_setN(h_cordic, MAX_CORDIC_ITERATIONS);
    FastRTS_CORDIC_setAtanTblPtr(h_cordic, FastRTS_CORDIC_atanTbl);
    FastRTS_CORDIC_setScaleTblPtr(h_cordic, FastRTS_CORDIC_scaleTbl);
    FastRTS_CORDIC_setRunKernelPtr(h_cordic, 
                                (v_pfn_v)FastRTS_CORDIC_rotationKernel);
    
    // Call the CORDIC kernel
    h_cordic->runKernel(h_cordic);

    // Get the values of x_i, y_i, z_i computed by the kernel
    x_i = FastRTS_CORDIC_getx_i(h_cordic);
    y_i = FastRTS_CORDIC_gety_i(h_cordic);
    z_i = FastRTS_CORDIC_getz_i(h_cordic);
    
    //<<VC161117: Don't need to actually do a final rotation
    // // Do a final rotation if the original argument, theta, was greater than
    // // the maximum decomposable angle
    // if(f_needFinalRotation == true)
    // {
    //     x_n = FTOIQMAX(COS_THETA_MAX*IQMAXTOF(x_i) - 
    //                    sign_z*SIN_THETA_MAX*IQMAXTOF(y_i));
    //     y_n = FTOIQMAX(sign_z*SIN_THETA_MAX*IQMAXTOF(x_i) + 
    //                    COS_THETA_MAX*IQMAXTOF(y_i));
#ifdef _DEBUG
    //     printf("Final Rotation required, "
    //            "x_n=%20.17f, y_n=%20.17f \n",
    //             IQMAXTOF(x_n), IQMAXTOF(y_n));
#endif // _DEBUG
    // }
    // else
    // {
    //     x_n = x_i;
    //     y_n = y_i;
    // }
    //  VC161117>>
    
#ifdef _DEBUG
    printf("------------------------sin(theta)=%20.17f------------------------"
           "----\n\n", 
           sign_z*IQMAXTOF(y_i));
#endif // _DEBUG

    return(sign_z*IQMAXTOF(y_i));
}

// End of File
