//#############################################################################
//! \file  2837x_ComplexMultiply/C-model/complex_mult.c
//!
//! \brief  Complex multiply of two floating point complex numbers.
//! \author David M. Alter
//! \date   06/07/11
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

#include "complex_mult.h"                // Main include file

/**********************************************************************
* Function: complex_mult()
*
* Description: Complex multiply of two floating point complex numbers.
**********************************************************************/
complex_float complex_mult(complex_float a, complex_float b)
{
    complex_float z;

    z.dat[0] = a.dat[0]*b.dat[0] - a.dat[1]*b.dat[1];        // real 
    z.dat[1] = a.dat[0]*b.dat[1] + a.dat[1]*b.dat[0];        // imag 

    return( z ); 

} // end complex_mult()

// End of file
