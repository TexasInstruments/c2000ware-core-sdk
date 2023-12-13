#ifndef _MEAN_COMPLEX_H_
#define _MEAN_COMPLEX_H_
//#############################################################################
//! \file /2837x_MeanComplex/C-model/mean_complex.h
//!
//! \brief  Mean of a Complex Vector
//! \author David M. Alter
//! \date   06/27/11
//
//  Group:            C2000
//  Target Family:    F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
#include <stdint.h>                 // C-99 Integer Types

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
complex_float mean_complex(complex_float* , uint16_t );

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _MEAN_COMPLEX_H_ definition

// End of file
