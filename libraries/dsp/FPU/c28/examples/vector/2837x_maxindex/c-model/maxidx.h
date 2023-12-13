#ifndef _MAXIDX_H_
#define _MAXIDX_H_
//#############################################################################
//! \file /2837x_MaxIndex/C-model/maxidx.h
//!
//! \brief  Index of the Maximum Value in a Vector
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
uint16_t maxidx(float *, uint16_t );

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _MAXIDX_H_ definition

// End of file
