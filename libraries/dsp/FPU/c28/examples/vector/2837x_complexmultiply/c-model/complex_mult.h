#ifndef _COMPLEX_MULT_H_
#define _COMPLEX_MULT_H_
//#############################################################################
//! \file /2837x_ComplexMultiply/C-model/complex_mult.h
//!
//! \brief  Complex Multiply Example
//! \author David M. Alter
//! \date   06/27/11
//
//  Group:             C2000
//  Target Family:    F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// typedefs
//*****************************************************************************
typedef struct {
    float dat[2];
} complex_float;

//*****************************************************************************
// function prototypes
//*****************************************************************************
complex_float complex_mult(complex_float , complex_float );

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _COMPLEX_MULT_H_ definition

// End of file
