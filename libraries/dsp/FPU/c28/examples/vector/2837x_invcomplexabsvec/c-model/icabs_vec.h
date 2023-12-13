#ifndef _ICABS_VEC_H_
#define _ICABS_VEC_H_
//#############################################################################
//! \file /2837x_InvComplexAbsVec/C-model/icabs_vec.h
//!
//! \brief  Inverse Absolute of a Complex Vector
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

void icabs_vec(const complex_float* , float* , const uint16_t );

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _ICABS_VEC_H_ definition

// End of file
