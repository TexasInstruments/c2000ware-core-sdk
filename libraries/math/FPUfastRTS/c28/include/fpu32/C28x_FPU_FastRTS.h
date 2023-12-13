#ifndef _C28X_FPU_FAST_RTS_H_
#define _C28X_FPU_FAST_RTS_H_
//#############################################################################
//
//! \file   C28x_FPU_FastRTS.h
//!
//! \brief  Prototypes and Definitions for the Single Precision C28x Fast RTS 
//!         Library
//!
//! These prototypes are for functions not found in the standard
//! RTS library.
//!
//! For standard functions, include the appropriate header file as
//! usual.  For example: math.h
//
//  Group:          C2000
//  Target Device:  C28x+FPU32/FPU64
//
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


//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>

//!
//! \defgroup FASTRTS_F32 Fast RTS (FPU32) Library Definitions and Types
//!
//! \ingroup FASTRTS_F32 
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#ifndef __TI_EABI__
#define sincos  sincosf
#define isqrt   isqrtf
#endif

//*****************************************************************************
// typedefs
//*****************************************************************************
// c2000 types for IEEE754 (same as defined in <device>/inc/hw_types.h)
#ifndef C2000_IEEE754_TYPES
#define C2000_IEEE754_TYPES
#ifdef __TI_EABI__
typedef float         float32_t;
typedef double        float64_t;
#else // TI COFF
typedef float         float32_t;
typedef long double   float64_t;
#endif // __TI_EABI__
#endif // C2000_IEEE754_TYPES

//*****************************************************************************
// the function prototypes
//*****************************************************************************

//! \brief Single Precision Floating Point Sine and Cosine (radians)
//! 
//! Returns both the sine and cosine of a floating-point argument X (in
//! radians) using table look-up and Taylor series expansion between the
//! look-up table entries.
//!
//! \param[in]  X single precision floating point argument
//! \param[out] PtrSin pointer to the sine of the argument
//! \param[out] PtrCin pointer to the cosine of the argument
//! \return none
//!
//! \note 
//! -# This is not a standard C Math function; it requires the 
//! "C28x_FPU_FastRTS.h" header instead of "math.h"
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 44 <td> Cycle count includes the call and return
//! </table>
//
void sincosf(float32_t radian, float32_t* PtrSin, float32_t* PtrCos);

//! \brief Single-Precision Floating-Point 1.0/Square Root
//! \param[in] X single precision floating point argument
//! \return 1.0 /square root of a floating-point argument X using a Newton-
//! Raphson algorithm.
//!
//! \attention
//! -# isqrt(FLT_MAX) and isqrt(FLT_MIN) set the LUF flag.
//! -# isqrt(-FLT_MIN) will set both the LUF and LVF flags.
//! -# isqrt(0.0) sets the LVF flag.
//! -# If X is negative, isqrt(X) will set LVF and return 0.0.
//!
//! \note 
//! -# This function is not included in the standard RTS library. It is
//! typically computed as \e 1.0L/sqrt(X) . To use this function 
//! you must modify your code to instead call isqrt(X). 
//! -# When migrating from an IQmath project, you can modify the IQmath
//! header file to use isqrt(X) when configured for FLOAT_MATH.
//! -# This is not a standard C Math function; it requires the 
//! "C28x_FPU_FastRTS.h" header instead of "math.h"
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 26 <td> Cycle count includes the call and return
//! </table>
//
float32_t isqrtf(float32_t X);

//! \brief Single-Precision Floating-Point ASIN (radians)
//! \param[in] X single precision floating point argument
//! must be in the range \f$[-{\1}, {\1}]\f$
//! \return the arc tangent of a floating-point argument X. The return value
//! is an angle in the range \f$[-{\pi}, {\pi}]\f$ radians.
//!
//! \note
//! -# This is a standard C math function and requires "math.h" to be
//! included
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment
//! <tr><td> 55 <td> Cycle count includes the call and return
//! </table>
//
float32_t asinf (float32_t X);

//! \brief Single-Precision Floating-Point ACOS (radians)
//! \param[in] X single precision floating point argument
//! must be in the range \f$[-{\1}, {\1}]\f$
//! \return the arc tangent of a floating-point argument X. The return value
//! is an angle in the range \f$[-{\pi}, {\pi}]\f$ radians.
//!
//! \note
//! -# This is a standard C math function and requires "math.h" to be
//! included
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment
//! <tr><td> 60 <td> Cycle count includes the call and return
//! </table>
//
float32_t acosf (float32_t X);

//! \brief Single-Precision Floating-Point ATAN (radians)
//! \param[in] X single precision floating point argument
//! \return the arc tangent of a floating-point argument X. The return value
//! is an angle in the range \f$[-{\pi}, {\pi}]\f$ radians.
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 49 <td> Cycle count includes the call and return
//! </table>
//
float32_t atanf (float32_t X);

//! \brief Single-Precision Floating-Point ATAN2 (radians)
//! \param[in] Y first single precision floating point argument
//! \param[in] X second single precision floating point argument
//! \return the 4-quadrant arctangent of floating-point arguments X/Y. The
//! return value is an angle in the range \f$[-{\pi}, {\pi}]\f$ 
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 50 <td> Cycle count includes the call and return
//! </table>
//
float32_t atan2f (float32_t Y, float32_t X);

//! \brief Single-Precision Floating-Point Cosine (radians)
//! \param[in] X single precision floating point argument
//! \return the cosine of a floating-point argument X (in radians) using table
//! look-up and Taylor series expansion between the look-up table entries.
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 38 <td> Cycle count includes the call and return
//! </table>
//
float32_t cosf (float32_t X);

//! \brief Single-Precision Floating-Point Division
//! 
//! Replaces the single-precision division operation from the standard RTS
//! library. This function uses a Newton-Raphson algorithm.
//!
//! In C code, an expression of the type \code Z = Y/X \endcode will 
//! invoke FS$$DIV
//!
//! \param[in] X single precision floating point numerator
//! \param[in] Y single precision floating point denominator
//! \return the quotient
//!
//! \attention
//! -# This division routine computes y/x by first estimating (1/x), performing
//! a few iterations of Newton-Raphson approximation to improve the precision 
//! of 1/x, and then finally multiplying that estimate by y; it essentially 
//! computes y/x as (1/x)*y. If 1/x is not perfectly representable in the 
//! floating point format it can lead to inaccuracies in the final result. The
//! user is encouraged to use the standard runtime support library division 
//! routine if accuracy takes priority over speed.
//! -# These are the special cases for division
//!
//! <table>
//! <caption id="multi_row">Special Cases for Division</caption>
//! <tr><th>  Case                    <th> Result      <th>  Flags  
//! <tr><td> (0.0/0.0)                <td> = +infinity <td>         
//! <tr><td> (+FLT_MAX/+FLT_MAX)      <td> =  0.0      <td> LUF = 1 
//! <tr><td> (-FLT_MAX/+FLT_MAX)      <td> = -0.0      <td> LUF = 1 
//! <tr><td> (+FLT_MAX/-FLT_MAX)      <td> =  0.0      <td> LUF = 1 
//! <tr><td> (-FLT_MAX/-FLT_MAX)      <td> = -0.0      <td> LUF = 1 
//! <tr><td> (+FLT_MIN/+FLT_MAX)      <td> =  0.0      <td> LUF = 1 
//! <tr><td> (-FLT_MIN/+FLT_MAX)      <td> = -0.0      <td> LUF = 1 
//! <tr><td> (+FLT_MIN/-FLT_MAX)      <td> =  0.0      <td> LUF = 1 
//! <tr><td> (-FLT_MIN/-FLT_MAX)      <td> = -0.0      <td> LUF = 1 
//! </table>
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 25 <td> Cycle count includes the call and return
//! </table>
//
float32_t FS$$DIV (float32_t X, float32_t Y);

//! \brief Single-Precision Floating-Point Sine (radians)
//! \param[in] X single precision floating point argument
//! \return the sine of a floating-point argument X (in radians) using table
//! look-up and Taylor series expansion between the look-up table entries.
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 38 <td> Cycle count includes the call and return
//! </table>
//
float32_t sinf (float32_t X);

//! \brief Single-Precision Floating-Point Square Root
//! \param[in] X single precision floating point argument
//! \return the square root of a floating-point argument X using a Newton-
//!  Raphson algorithm.
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! \attention
//! -# sqrt(FLT_MAX) and sqrt(FLT_MIN) set the LUF flag.
//! -# sqrt(-FLT_MIN) will set both the LUF and LVF flags.
//! -# sqrt(0.0) sets the LVF flag.
//! -# If X is negative, sqrt(X) will set LVF and return 0.0.
//! -# This square root routine computes \f$\sqrt{x}\f$ by first estimating 
//! \f$\frac{1}{\sqrt{x}}\f$, performing a few iterations of Newton-Raphson 
//! approximation to improve the precision of \f$\frac{1}{\sqrt{x}}\f$, and 
//! then finally multiplying that estimate by x; it essentially computes 
//! \f$\sqrt{x}\f$ as \f$\frac{1}{\sqrt{x}} \times x\f$. If 
//! \f$\frac{1}{\sqrt{x}}\f$ is not perfectly representable in the floating 
//! point format it can lead to inaccuracies in the final result. The user is 
//! encouraged to use the standard runtime support library division routine if 
//! accuracy takes priority over speed.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 29 <td> Cycle count includes the call and return
//! </table>
//
float32_t sqrtf (float32_t X);

//! \brief Single-Precision Floating-Point Exponent 
//! \param[in] X single precision floating point argument
//! \return the exponent of a floating-point argument X using table
//! look-up and Taylor series expansion of the fractional part of the argument.
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# the input domain is limited to +-log(FLT_MAX) (< +-89)
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 61 <td> Cycle count includes the call and return
//! </table>
//
float32_t expf (float32_t X);

//! \brief Single-Precision Floating-Point Natural Logarithm 
//! \param[in] X single precision floating point argument
//! \return the natural logarithm of a floating-point argument X 
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# the input must be greater than or equal to 1
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 51 <td> Cycle count includes the call and return
//! </table>
//
float32_t logf (float32_t X);

//! \brief Single-Precision Floating-Point Power Function
//! \param[in] X single precision floating point base argument
//! \param[in] Y single precision floating point exponent argument
//! \return X^Y
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//! -# the input X must be greater than or equal to 1
//! -# For COFF executables float and double are both single precision
//! 32-bit floating point types, therefore, the double and float variant of 
//! this function may be used interchangeably.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 109 <td> Cycle count includes the call and return
//! </table>
//
float32_t powf(float32_t X, float32_t Y);

//! \brief Fast memory copy function
//! \param[in] Dst Destination address pointer
//! \param[in] Src Source address pointer
//! \param[in] num_words Number of 16-bit words
//! \return void
//!
//
void memcpy_fastrts(void *dst,void *src, uint16_t num_words);

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif   // - end of _C28X_FPU_FAST_RTS_H_

// End of File
