//#############################################################################
//! \file  2837x_InvComplexAbsVec\C-model\icabs_vec.c
//!
//! \brief  Inverse absolute value of a complex vector
//! \author David Alter
//! \date   06/28/11
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

#include "icabs_vec.h"                // Main include file
#include <math.h>                   // Needed for sqrt()

/**********************************************************************
* Function: icabs_vec()
*
* Description: Inverse absolute value of a complex vector
**********************************************************************/
void icabs_vec(const complex_float* x, float* y, const uint16_t N)
{
    uint16_t i;

    for(i=0; i<N; i++)
    {
        y[i] = 1.0/sqrt(x[i].dat[0]*x[i].dat[0] + x[i].dat[1]*x[i].dat[1]);
    }

} // end of icabs_vec()

// End of file
