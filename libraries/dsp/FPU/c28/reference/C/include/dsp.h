#ifndef _DSP_H_
#define _DSP_H_
//#############################################################################
//! \file   reference/C/include/$FILENAME$
//! \brief  DSP Header File
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################


#define CONCAT(x,y)          x##y
#define XCONCAT(x,y)         CONCAT(x,y)
#define STRINGIZE(s)         #s
#define XSTRINGIZE(s)        STRINGIZE(s)

//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

//!
//! \defgroup C_REF_MOD C Reference Module

//! 
//! \ingroup C_REF_MOD
//@{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#if USE_FPU64 == 1
typedef double        fsize_t; //!< Use double precision
#define PI            (3.141592653589793)
#define TWOPI         (6.283185307179586)
#define PI_O_2        (1.570796326794897)
#define INVTWOPI      (0.159154943091895)
#else //USE_FPU32 == 1
typedef float         fsize_t; //!< Use single precision
#define PI            (3.141592653589793F)
#define TWOPI         (6.283185307179586F)
#define PI_O_2        (1.570796326794897F)
#define INVTWOPI      (0.159154943091895F)
#endif //USE_FPU64 == 1

//! The Twiddle Factor Table size 
//! \note The user must change this value to match the size argument of
//! the MATLAB function FPU_DSP_genTwiddleFactorTable()
//! 
#define TWIDDLEFACTOR_TBLSIZE    (1024U) 

//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief The error type enumeration
//!
typedef enum{
    ERRORTYPE_ABSOLUTE = 0, //!< Absolute error
    ERRORTYPE_RELATIVE = 1, //!< Relative error
}errorType;

//! \brief Pointer to a function that takes an argument of fsize_t and 
//! returns a value of type fsize_t
typedef fsize_t (*PFF)(fsize_t);

//! \brief Primitive for the sincos type
//!
typedef struct{
    fsize_t c;   //!< The Cosine 
    fsize_t s;   //!< The Sine
}sincos_t;

//! \brief Primitive for the complex type
//!
typedef struct{
    fsize_t r;   //!< The Real Part 
    fsize_t i;   //!< The Imaginary Part
}complex_t;

//*****************************************************************************
//globals
//*****************************************************************************
//! \brief The Twiddle Factors Table
//!
extern const fsize_t FFT_twiddleFactors[];

#if USE_FPU64 == 1
static PFF fabs_t  = fabs;
#else //USE_FPU32 == 1
static PFF fabs_t  = fabsf;
#endif //USE_FPU64 == 1


//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************

#ifdef __cplusplus
}
#endif //extern "C"

//@} //ingroup

#endif // end of _DSP_H_ definition
