#ifndef _FASTRTS_H_
#define _FASTRTS_H_
//#############################################################################
//! \file   reference/C/include/$FILENAME$
//! \brief  Fast RTS Header File
//! \author Vishal Coelho 
//! \date   19-Aug-2015
//! 
//
//  Group:            C2000
//  Txet Family:    $DEVICE$
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
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
#define PI            (3.141592653589793)
#define TWOPI         (6.283185307179586)
#define PI_O_2        (1.570796326794897)
#define THREEPI_O_2   (4.712388980384690)
#define INVTWOPI      (0.159154943091895)
#define ITABLE_SIZE   (1.0/(fsize_t)SINCOS_TBLSIZE)
#else //USE_FPU32 == 1
#define PI            (3.141592653589793F)
#define TWOPI         (6.283185307179586F)
#define PI_O_2        (1.570796326794897F)
#define THREEPI_O_2   (4.712388980384690F)
#define INVTWOPI      (0.159154943091895F)
#define ITABLE_SIZE   (1.0F/(fsize_t)SINCOS_TBLSIZE)
#endif //USE_FPU64 == 1


#define RAD_STEP     (TWOPI*ITABLE_SIZE)
#define RAD_ISTEP    ((fsize_t)SINCOS_TBLSIZE * INVTWOPI)

//! The Sine/Cosine Lookup Table size 
//! \note The user must change this value to match the size argument of
//! the MATLAB function FPU_FastRTS_genTableSineCosine()
//! 
#define SINCOS_TBLSIZE    (512U) 

//! The Arctangent Lookup Table size 
//! \note The user must change this value to match the size argument of
//! the MATLAB function FPU_FastRTS_genTableArctangent()
//! \note The table is arranged as 3-tuples, there are ARCTAN2_TBLSIZE + 1
//! 3-tuples
//! 
#define ARCTAN2_TBLSIZE   (64U) 

//! The Natural Logarithm Lookup Table size 
//! \note The user must change this value to match the size argument of
//! the MATLAB function FPU_FastRTS_genTableLog()
//! \note The table is arranged as 3-tuples, there are LOG_TBLSIZE + 1
//! 3-tuples
//! 
#define LOG_TBLSIZE   (32U) 

//*****************************************************************************
// typedefs
//*****************************************************************************

#if USE_FPU64 == 1
typedef double        fsize_t; //!< Use double precision
typedef long long     isize_t; //!< 64-bit signed integers
#else //USE_FPU32 == 1
typedef float         fsize_t; //!< Use single precision
typedef long          isize_t; //!< 32-bit signed integers
#endif //USE_FPU64 == 1

//! \brief Pointer to a function that takes an argument of fsize_t and 
//! returns a value of type fsize_t
typedef fsize_t (*PFF)(fsize_t);

//! \brief a function pointer with a void pointer argument returning nothing
//!
typedef void (*v_pfn_v)(void *);

//! \brief Primitive for the sincos()
//!
typedef struct{
    fsize_t c;   //!< The Cosine 
    fsize_t s;   //!< The Sine
}sincos_t;

//*****************************************************************************
//globals
//*****************************************************************************
//! \brief The Sine/Cosine Lookup Table
//!
extern const fsize_t FastRTS_SinCosTbl[];

//! \brief The Arctangent Lookup Table
//!
extern const fsize_t FastRTS_Arctan2Tbl[];

//! \brief The Exponent Lookup Table
//!
extern const fsize_t FastRTS_expTable[];

//! \brief The Natural Logarithm Lookup Table
//!
extern const fsize_t FastRTS_logTable[];

//! \brief Constants in the Exponent calculation
//!
extern const fsize_t FPUINV1; 
extern const fsize_t FPUINV2; 
extern const fsize_t FPUINV3; 
extern const fsize_t FPUINV4; 
extern const fsize_t FPUINV5; 
extern const fsize_t FPUINV6; 
extern const fsize_t FPUINV7; 
extern const fsize_t FPUINV8; 
extern const fsize_t FPUINV9; 
extern const fsize_t FPUINV10;
extern const fsize_t FPUINV11;
extern const fsize_t FPUINV12;
extern const fsize_t FPUINV13;
extern const fsize_t FPUINV14;
extern const fsize_t FPULOG10;

//! \brief Constants in the Natural Logarithm calculation
//!
extern const fsize_t FPULOG2;            
extern const fsize_t FPUINVLOG10;        
extern const fsize_t FPUEXPBIAS;         
extern const isize_t FPULOG_TABLE_MASK1; 
extern const isize_t FPULOG_TABLE_MASK2; 

#if USE_FPU64 == 1
static PFF fabs_t  = fabs;
#else //USE_FPU32 == 1
static PFF fabs_t  = fabsf;
#endif //USE_FPU64 == 1

//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief The Cosine Function
//! \param[in] theta , Angle in radians
//! \param[in] tbl , Lookup Table
//! \return The cosine of the angle
extern fsize_t FastRTS_cos(const fsize_t theta, const fsize_t *tbl);

//! \brief The Sine Function
//! \param[in] theta , Angle in radians
//! \param[in] tbl , Lookup Table
//! \return The sine of the angle
extern fsize_t FastRTS_sin(const fsize_t theta, const fsize_t *tbl);

//! \brief The Sine/Cosine Function
//! \param[in] theta , Angle in radians
//! \param[in] tbl , Lookup Table
//! \return The sine and cosine of the angle
extern sincos_t FastRTS_sincos(const fsize_t theta, const fsize_t *tbl);

//! \brief The Square Root Function
//! \param[in] x , the operand
//! \return The square root of the operand
extern fsize_t FastRTS_sqrt(const fsize_t x);

//! \brief The Inverse Square Root Function
//! \param[in] x , the operand
//! \return The square root of the operand
extern fsize_t FastRTS_isqrt(const fsize_t x);

//! \brief The Division Function
//! \param[in] num , Numerator
//! \param[in] den , Denominator
//! \return The quotient
extern fsize_t FastRTS_div(const fsize_t num, const fsize_t den);

//! \brief The Arctangent function
//! \param[in] x the arc subtended by the angle theta
//! \param[in] tbl , Lookup Table
//! \return theta , the angle subtended by the arc of length x
extern fsize_t FastRTS_atan(const fsize_t x, const fsize_t *tbl);

//! \brief The Arctangent(y,x) function
//! \param[in] y , numerator of the ratio y/x which is the length of the arc
//!                subtended by the angle theta
//! \param[in] x , denominator of the ratio y/x which is the length of the arc
//!                subtended by the angle theta
//! \param[in] tbl , Lookup Table
//! \return theta , the angle subtended by the arc of length y/x
extern fsize_t FastRTS_atan2(const fsize_t y, const fsize_t x, 
                      const fsize_t *tbl);

//! \brief The Exponent function
//! \param[in] x , argument whose exponent is to be calculated
//! \return e^x , the exponent of the argument
extern fsize_t FastRTS_exp(const fsize_t x);

//! \brief The Natural Logarithm function
//! \param[in] x , argument whose logarithm is to be calculated
//! \return log(x) , the natural logarithm of the argument
extern fsize_t FastRTS_log(const fsize_t x);

//! \brief The Power function
//! \param[in] x , the base
//! \param[in] y , the exponent
//! \return x^y , the yth power of x
extern fsize_t FastRTS_powf(const fsize_t x, const fsize_t y);

#ifdef __cplusplus
}
#endif //extern "C"

//@} //ingroup

#endif // end of _FASTRTS_H_ definition
