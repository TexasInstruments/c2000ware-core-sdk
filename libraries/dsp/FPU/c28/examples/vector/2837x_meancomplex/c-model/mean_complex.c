//#############################################################################
//! \file  2837x_MeanComplex/C-model/mean_complex.c
//!
//! \brief  Unbiased rounding of a floating point real number
//! \author David M. Alter
//! \date   07/08/11
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

#include "mean_complex.h"                // Main include file
#include <math.h>                       // Needed for sqrt()

/**********************************************************************
* Function: mean_complex()
*
* Description: Mean of real and imaginary parts of a complex vector
**********************************************************************/
complex_float mean_complex(complex_float* x, uint16_t N)
{
    complex_float y;
    uint16_t i;

    y.dat[0] = 0;                        // zero the real part
    y.dat[1] = 0;                        // zero the imag part

    for(i=0; i<N; i++)
    {
        y.dat[0] = y.dat[0] + x[i].dat[0];
        y.dat[1] = y.dat[1] + x[i].dat[1];
    }

    y.dat[0] = y.dat[0]/N;
    y.dat[1] = y.dat[1]/N;

    return(y);

} // end of mean_complex()

// End of file
