#ifndef _FASTRTS_H_
#define _FASTRTS_H_
//#############################################################################
//
//! \file   fastrts_.h
//!
//! \brief  Fast RTS Definitions and Types
//! \author Vishal Coelho
//! \date   Dec 25, 2015
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
//! \defgroup FASTRTS_F64 Fast RTS Definitions and Types
//!
//! \ingroup FASTRTS_F64 
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
//! FAST RTS Library Version
#define LIBRARY_VERSION     "2.05.00.00"

#define COMPILER_FPU64_SUPPORT  0U
#define CONVERT_F32_TO_F64      0U

//! Determines if 0/0 results in a result of infinity
#define ZERO_BY_ZERO_EQ_INF     1U
//! Determines if 0/0 results in a result of zero
#define ZERO_BY_ZERO_EQ_ZER0    (!ZERO_O_ZERO_EQ_INF)

//! This line prevents conflicts with the data types and macros declared in
//! FPU DSP library
#ifndef _RTS_IN_USE_
#define _RTS_IN_USE_

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

#if defined(__TMS320C28XX_FPU64__)
//! \brief 64-bit Double Precision Float
//! The union of a double precision value, an unsigned long long and a signed
//! long long allows for manipulation of the hex representation of the floating
//! point value as well as signed and unsigned arithmetic to determine error 
//! metrics.
//! This data type is only defined if the compiler option --float_support is 
//! set to fpu64
//! 
typedef union
{
    uint64_t    ui64; //!< Unsigned long long representation
    int64_t     i64;  //!< Signed long long represntaion 
    float64_t   f64;  //!< Double precision (64-bit) representation
}float64u_t;
#endif //defined(__TMS320C28XX_FPU64__)

#if (defined(__TMS320C28XX_FPU32__) || defined(__TMS320C28XX_FPU64__))
//! \brief 32-bit Double Precision Float
//! The union of a double precision value, an unsigned long and a signed
//! long allows for manipulation of the hex representation of the floating
//! point value as well as signed and unsigned arithmetic to determine error 
//! metrics.
//! This data type is only defined if the compiler option --float_support is 
//! set to fpu32
//!
typedef union
{
    uint32_t    ui32; //!< Unsigned long representation
    int32_t     i32;  //!< Signed long represntaion 
    float       f32;  //!< Single precision (32-bit) representation
}float32u_t;
#endif //defined(__TMS320C28XX_FPU32__)

//! \brief a function pointer with a void pointer argument returning nothing
//!
typedef void (*v_pfn_v)(void *);

#if !(defined(__TMS320C28XX_FPU32__) || defined(__TMS320C28XX_FPU64__))
#error "--float_support=fpu64 option must be set to build the FPU64        \
    version of the library. --float_support=fpu32 must be set to build the \
    FPU32 version of the DSP library"
#endif // (defined(__TMS320C28XX_FPU32__) || defined(__TMS320C28XX_FPU64__))

#endif // _RTS_IN_USE

//*****************************************************************************
//globals
//*****************************************************************************

//*****************************************************************************
// the function prototypes
//*****************************************************************************
#if defined(__TMS320C28XX_FPU64__)
void run_sin(float64u_t *pdest, float64u_t *psrc);
void run_cos(float64u_t *pdest, float64u_t *psrc);
void run_isqrt(float64u_t *pdest, float64u_t *psrc);
void run_sqrt(float64u_t *pdest, float64u_t *psrc);
void run_div(float64u_t *pdest, float64u_t *psrc1, float64u_t *psrc2);
void run_sincos(float64u_t *pangle, float64u_t *psin, float64u_t *pcos);
void run_atan(float64u_t *pdest, float64u_t *psrc);
void run_atan2(float64u_t *pdest, float64u_t *psrc1, float64u_t *psrc2);
#endif //__TMS320C28XX_FPU64__

#if defined(FOR_DOXYGEN_USE_ONLY)
#if defined(__TMS320C28XX_FPU64__)
//! \brief Double Precision Floating Point Sine and Cosine (radians)
//! 
//! Returns both the sine and cosine of a floating-point argument X (in
//! radians) using table look-up and Taylor series expansion between the
//! look-up table entries.
//!
//! \param[in]  X double precision floating point argument
//! \param[out] PtrSin pointer to the sine of the argument
//! \param[out] PtrCin pointer to the cosine of the argument
//! \return none
//!
//! \note This is not a standard C Math function; it requires the 
//! "fastrts.h" header instead of "math.h"
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 73 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
void sincos(float64u_t radian, float64u_t* PtrSin, float64u_t* PtrCos);
#else
void sincosl(float64u_t radian, float64u_t* PtrSin, float64u_t* PtrCos);
#endif

//! \brief Single-Precision Floating-Point 1.0/Square Root
//! \param[in] X double precision floating point argument
//! \return 1.0 /square root of a floating-point argument X using a Newton-
//! Raphson algorithm.
//!
//! \attention
//! -# isqrt(FLT_MAX) and isqrt(FLT_MIN) set the LUF flag.
//! -# isqrt(-FLT_MIN) will set both the LUF and LVF flags.
//! -# isqrt(0.0) sets the LVF flag.
//! -# If X is negative, isqrt(X) will set LVF and return 0.0.
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
//! \note 
//! -# This function is not included in the standard RTS library. It is
//! typically computed as \e 1.0L/sqrt(X) . To use this function 
//! you must modify your code to instead call isqrt(X). 
//! -# When migrating from an IQmath project, you can modify the IQmath
//! header file to use isqrt(X) when configured for FLOAT_MATH.
//! -# This is not a standard C Math function; it requires the 
//! "fastrts.h" header instead of "math.h"
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 59 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
float64u_t isqrt(float64u_t X);
#else
float64u_t isqrtl(float64u_t X);
#endif


//! \brief Single-Precision Floating-Point ATAN (radians)
//! \param[in] X double precision floating point argument
//! \return the arc tangent of a floating-point argument X. The return value
//! is an angle in the range \f$[-{\pi}, {\pi}]\f$ radians.
//!
//! \note This is a standard C math function and requires "math.h" to be 
//! included
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 78 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
float64u_t atan (float64u_t X);
#else
float64u_t atanl (float64u_t X);
#endif


//! \brief Single-Precision Floating-Point ATAN2 (radians)
//! \param[in] Y first double precision floating point argument
//! \param[in] X second double precision floating point argument
//! \return the 4-quadrant arctangent of floating-point arguments X/Y. The
//! return value is an angle in the range \f$[-{\pi}, {\pi}]\f$ 
//!
//! \note This is a standard C math function and requires "math.h" to be 
//! included
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 81 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
float64u_t atan2 (float64u_t Y, float64u_t X);
#else
float64u_t atan2l (float64u_t Y, float64u_t X);
#endif


//! \brief Single-Precision Floating-Point Cosine (radians)
//! \param[in] X double precision floating point argument
//! \return the cosine of a floating-point argument X (in radians) using table
//! look-up and Taylor series expansion between the look-up table entries.
//!
//! \note This is a standard C math function and requires "math.h" to be 
//! included
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 63 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
float64u_t cos (float64u_t X);
#else
float64u_t cosl (float64u_t X);
#endif


//! \brief Single-Precision Floating-Point Division
//! 
//! Replaces the single-precision division operation from the standard RTS
//! library. This function uses a Newton-Raphson algorithm.
//!
//! In C code, an expression of the type \code Z = Y/X \endcode will 
//! invoke FS$$DIV
//!
//! \param[in] X double precision floating point numerator
//! \param[in] Y double precision floating point denominator
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
//! <tr><td> (+DBL_MAX/+DBL_MAX)      <td> =  0.0      <td> LUF = 1 
//! <tr><td> (-DBL_MAX/+DBL_MAX)      <td> = -0.0      <td> LUF = 1 
//! <tr><td> (+DBL_MAX/-DBL_MAX)      <td> =  0.0      <td> LUF = 1 
//! <tr><td> (-DBL_MAX/-DBL_MAX)      <td> = -0.0      <td> LUF = 1 
//! <tr><td> (+DBL_MIN/+DBL_MAX)      <td> =  0.0      <td> LUF = 1 
//! <tr><td> (-DBL_MIN/+DBL_MAX)      <td> = -0.0      <td> LUF = 1 
//! <tr><td> (+DBL_MIN/-DBL_MAX)      <td> =  0.0      <td> LUF = 1 
//! <tr><td> (-DBL_MIN/-DBL_MAX)      <td> = -0.0      <td> LUF = 1 
//! </table>
//!
//! \note 
//! -# This is a standard C math function and requires "math.h" to be 
//! included
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 51 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
float64u_t __c28xabi_div (float64u_t X, float64u_t Y);
#else
float64u_t FD$$DIV (float64u_t X, float64u_t Y);
#endif


//! \brief Single-Precision Floating-Point Sine (radians)
//! \param[in] X double precision floating point argument
//! \return the sine of a floating-point argument X (in radians) using table
//! look-up and Taylor series expansion between the look-up table entries.
//!
//! \note This is a standard C math function and requires "math.h" to be 
//! included
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 63 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
float64u_t sin (float64u_t X);
#else
float64u_t sinl (float64u_t X);
#endif


//! \brief Single-Precision Floating-Point Square Root
//! \param[in] X double precision floating point argument
//! \return the square root of a floating-point argument X using a Newton-
//!  Raphson algorithm.
//!
//! \note This is a standard C math function and requires "math.h" to be 
//! included
//!
//! \attention
//! -# sqrt(FLT_MAX) and sqrt(FLT_MIN) set the LUF flag.
//! -# sqrt(-FLT_MIN) will set both the LUF and LVF flags.
//! -# sqrt(0.0) sets the LVF flag.
//! -# If X is negative, sqrt(X) will set LVF and return 0.0.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> 63 <td> Cycle count includes the call and return
//! </table>
//
#ifdef __TI_EABI__
float64u_t sqrt (float64u_t X);
#else
float64u_t sqrtl (float64u_t X);
#endif

#endif //__TMS320C28XX_FPU64__
#endif //FOR_DOXYGEN_USE_ONLY

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _FASTRTS_H_definition

// End of File
