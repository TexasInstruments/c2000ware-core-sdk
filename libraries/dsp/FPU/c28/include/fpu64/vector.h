#ifndef _VECTOR_H_
#define _VECTOR_H_
//#############################################################################
//! \file   include/fpu64/vector.h
//!
//! \brief  Prototypes and Definitions for the DSP Library Vector Module
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
// includes
//*****************************************************************************
#include <stdint.h>
#include "dsp.h"

//!
//! \defgroup DSP_VECTOR_F64 Vector Operations (Double Precision)

//!
//! \addtogroup DSP_VECTOR_F64
// @{ 

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#ifdef NULL
#undef NULL
#define NULL    0
#else
#define NULL    0
#endif
//*****************************************************************************
// typedefs
//*****************************************************************************
//! Structure for the double precision complex data type
//! 
typedef struct { 
    float64_t real;   //!< Real part of the data point
    float64_t imag;   //!< Imaginary part of the data point
}complexf64_t;

//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief Absolute Value of a Complex Vector (Double Precision).
//!
//! This module computes the absolute value of a complex vector. If N is even,
//! use abs_SP_CV_2() for better performance.
//! \f[y[i]&=& \sqrt(x_{re}[i]^{2} + x_{im}[i]^{2}) \f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 73*N + 8 <td> Cycle count includes the call and return
//! </table>
//
extern void abs_DP_CV(float64_t *y, const complexf64_t *x, const uint16_t N);

//! \brief Absolute Value of an Even Length Complex Vector (Double Precision).
//!
//! This module computes the absolute value of an even length complex vector.
//! \f[ y[i]&=& \sqrt(x_{re}[i]^{2} + x_{im}[i]^{2})\f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//! \attention N must be even
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles      <th> Comment 
//! <tr><td> 79*N/2 + 17 <td> Cycle count includes the call and return
//! </table>
//
extern void abs_DP_CV_2(float64_t *y, const complexf64_t *x,
                        const uint16_t N);

//! \brief Addition (Element-Wise) of a Complex Scalar to a Complex Vector
//!  (Double Precision).
//!
//! This module adds a complex scalar element-wise to a complex vector.
//! \f[y_{re}[i]&=& x_{re}[i] + c_{re}\f]
//! \f[y_{im}[i]&=& x_{im}[i] + c_{im}\f]
//! \param y pointer to the complex output vector
//! \param x pointer to the complex input vector
//! \param c pointer to the complex input scalar
//! \param N length of the x and y vectors
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment  
//! <tr><td> 8*N + 21 <td> Cycle count includes the call and return
//! </table>
//
extern void add_DP_CSxCV(complexf64_t *y, const complexf64_t *x, 
                         const complexf64_t *c, const uint16_t N);
                         

//! \brief Addition of Two Complex Vectors (Double Precision).
//!
//! This module adds two complex vectors.
//! \f[y_{re}[i]&=& w_{re}[i] + x_{re}[i]\f]
//! \f[y_{im}[i]&=& w_{im}[i] + x_{im}[i]\f]
//! \param y pointer to the complex output vector
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w, x and y vectors
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles    <th> Comment 
//! <tr><td> 12*N + 15 <td> Cycle count includes the call and return
//! </table>
//
extern void add_DP_CVxCV(complexf64_t *y, const complexf64_t *w,
                         const complexf64_t *x, const uint16_t N);

//! \brief Inverse Absolute Value of a Complex Vector (Double Precision).
//!
//! This module computes the inverse absolute value of a complex vector.
//! \f[y[i]&=& \frac{1}{\sqrt(x_{re}[i]^{2} + x_{im}[i]^{2})}\f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//! \attention N must be at least 2
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 69*N + 8 <td> Cycle count includes the call and return
//! </table>
//
extern void iabs_DP_CV(float64_t *y, const complexf64_t *x, 
                       const uint16_t N);

//! \brief Inverse Absolute Value of an Even Length Complex Vector
//! (Double Precision).
//!
//! This module calculates the inverse absolute value of an even
//! length complex vector.
//! \f[y[i]&=& \frac{1}{\sqrt(x_{re}[i]^{2} + x_{im}[i]^{2})}\f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//! \attention N must be even
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles      <th> Comment 
//! <tr><td> 74*N/2 + 17 <td> Cycle count includes the call and return
//! </table>
//
extern void iabs_DP_CV_2(float64_t *y, const complexf64_t *x, 
                         const uint16_t N);
       
//! \brief Multiply-and-Accumulate of a Real Vector (integer) and a 
//! Complex Vector (Double Precision).
//!
//! This module multiplies and accumulates a 16-bit integer real vector and a
//! floating pt. complex vector.
//! \f[y_{re} &=& sum(x[i]*w_{re}[i]) \f]
//! \f[y_{im} &=& sum(x[i]*w_{im}[i]) \f]
//! \param w pointer to the complex input vector
//! \param x pointer to the real input vector
//! \param N length of the w and x vectors
//! \return complex double precision accumulation result
//! \attention N must be a minimum of 5
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td>          <td> Cycle count includes the call and return
//! <tr><td> 6*N + 36 <td> N is even 
//! <tr><td> 6*N + 29 <td> N is odd 
//! </table>
//
extern complexf64_t mac_DP_i16RVxCV(const complexf64_t *w, const int16_t *x,
		const uint16_t N);
        
//! \brief Multiply-and-Accumulate of a Complex Vector and a Complex Vector
//!   (Double Precision).
//!
//! This module multiplies and accumulates a complex vector and another
//! complex vector.
//! \f[y_{re} &=& \sum(w_{re}[i]* x_{re}[i] - w_{im}[i] * x_{im}[i]) \f]
//! \f[y_{im} &=& \sum(w_{re}[i]* x_{im}[i] + w_{im}[i] * x_{re}[i]) \f]
//! \param y complex result
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w and x vectors
//! \attention N must be a minimum of 3
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 9*N + 27 <td> Cycle count includes the call and return
//! </table>
//
extern complexf64_t mac_DP_CVxCV(const complexf64_t *w,
                         const complexf64_t *x, const uint16_t N);
                         
                         
//! \brief Multiply-and-Accumulate of a Real Vector and a Complex Vector
//!   (Double Precision).
//!
//! This module multiplies and accumulates a real vector and a complex vector.
//! \f[y_{re} &=& \sum(x[i]*w_{re}[i]) \f]
//! \f[y_{im} &=& \sum(x[i]*w_{im}[i]) \f]
//! \param y complex result
//! \param w pointer to the complex input vector
//! \param x pointer to the real input vector
//! \param N length of the w and x vectors
//! \attention N must be a minimum of 5
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td>          <td> Cycle count includes the call and return
//! <tr><td> 6*N + 34 <td> N is even 
//! <tr><td> 6*N + 28 <td> N is odd 
//! </table>
//
extern complexf64_t mac_DP_RVxCV(const complexf64_t *w, const float64_t *x, 
                           const uint16_t N);

//! \brief Index of Maximum Value of an Even Length Real Array 
//! (Double Precision).
//!
//! \param x pointer to the input vector
//! \param N length of the x vector
//! \attention
//! -# N must be even
//! -# If more than one instance of the max value exists in x[], the
//! function will return the index of the first occurrence (lowest index
//! value)
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 4*N + 22 <td> Cycle count includes the call and return
//! </table>
//
extern uint16_t maxidx_DP_RV_2(const float64_t *x, const uint16_t N);

//! \brief Mean of Real and Imaginary Parts of a Complex Vector
//! (Double Precision).
//!
//! This module calculates the mean of real and imaginary parts of a
//! complex vector.
//! \f[y_{re} &=& \frac{\Sigma x_{re}}{N} \f]
//! \f[y_{im} &=& \frac{\Sigma x_{im}}{N} \f]
//! \param x pointer to the input vector
//! \param N length of the x vector
//! \attention N must be even
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 5*N + 37 <td> Cycle count includes the call and return
//! </table>
//
extern complexf64_t mean_DP_CV_2(const complexf64_t *x, const uint16_t N);

//! \brief Complex Multiply of Two Double Precision Numbers.
//!
//! This module multiplies two double precision complex values.
//! \f[y_{re} &=& w_{re}*x_{re} - w_{im}*x_{im}\f]
//! \f[y_{im} &=& w_{re}*x_{im} + w_{im}*x_{re}\f]
//! \param w pointer to the first complex input
//! \param x pointer to the second complex input
//! \return complex product of the first and second complex input
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles <th> Comment 
//! <tr><td> 28     <td> Cycle count includes the call and return
//! </table>
//
extern complexf64_t mpy_DP_CSxCS(const complexf64_t *w, const complexf64_t *x);

//! \brief Complex Multiply of Two Complex Vectors (Double Precision).
//!
//! This module performs complex multiplication on two input complex vectors.
//! \f[y_{re}[i] &=& w_{re}[i]*x_{re}[i] - w_{im}[i]*x_{im}[i] \f]
//! \f[y_{im}[i] &=& w_{re}[i]*x_{im}[i] + w_{im}[i]*x_{re}[i] \f]
//! \param y pointer to the complex product of the first and second complex
//! vectors
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w, x and y vectors
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles    <th> Comment 
//! <tr><td> 20*N + 16 <td> Cycle count includes the call and return
//! </table>
//
extern void mpy_DP_CVxCV(complexf64_t *y, const complexf64_t *w, 
                         const complexf64_t *x, const uint16_t N);
               
//! \brief Multiplication of a Complex Vector and the Complex Conjugate of 
//! another Vector (Double Precision).
//!
//! This module multiplies a complex vector (w) and the complex conjugate of 
//! another complex vector (x).
//! \f[x^{*}_{re}[i] &=& x_{re}[i]\f]
//! \f[x^{*}_{im}[i] &=& - x_{im}[i]\f]
//! \f[y_{re}[i] &=& w_{re}[i]*x_{re}[i] - w_{im}[i]*x^{*}_{im}[i]\f]
//! \f[          &=& w_{re}[i]*x_{re}[i] + w_{im}[i]*x_{im}[i]\f]
//! \f[y_{im}[i] &=& w_{re}[i]*x^{*}_{im}[i] + w_{im}[i]*x_{re}[i]\f]
//! \f[          &=& w_{im}[i]*x_{re}[i] - w_{re}[i]*x_{im}[i]\f]
//! \param y pointer to the complex conjugate product of the first and 
//! second complex vectors
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w, x and y vectors
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles    <th> Comment 
//! <tr><td> 20*N + 16 <td> Cycle count includes the call and return
//! </table>
//
extern void mpy_DP_CVxCVC(complexf64_t *y, const complexf64_t *w,
                          const complexf64_t *x, const uint16_t N);

//! \brief Multiplication of Two Real Matrices (Double Precision).
//!
//! This module multiplies two real matrices.
//! \f[y[] &=& w[]*x[] \f]
//! \param y pointer to result matrix
//! \param w pointer to 1st source matrix
//! \param x pointer to 2nd source matrix
//! \param m number of rows in the first and output matrices
//! \param n number of columns in the first and rows in the second matrix
//! \param p number of columns in the second and output matrices
//! \attention 
//! -# There are no restrictions on the values for n, m, and pwith this 
//!    function.
//! -# If n is even and at least 4, you can use mpy_DP_RMxRM_2() for better 
//!    performance if desired.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 8*m*n*p + overhead <td> Cycle count includes the call and return
//! <tr><td> m=2 n=8, p=2 takes ~362 cycles     <td> versus 8*m*n*p = 256
//! <tr><td> m=8, n=8, p=8 takes ~5162 cycles    <td> versus 8*m*n*p = 4096
//! <tr><td> m=16, n=16, p=16 takes ~36794 cycles <td> versus 
//! 8*m*n*p = 32768
//! </table>
//          
extern void mpy_DP_RMxRM(float64_t *y, const float64_t *w, 
 const float64_t *x, const uint16_t m,  const uint16_t n, const uint16_t p);
                            
//! \brief Multiplication of Two Real Matrices (n even, Double Precision).
//!
//! This module multiplies two real matrices.
//! \f[y[] &=& w[]*x[] \f]
//! \param y pointer to result matrix
//! \param w pointer to 1st source matrix
//! \param x pointer to 2nd source matrix
//! \param m number of rows in the first and output matrices
//! \param n number of columns in the first and rows in the second matrix
//! \param p number of columns in the second and output matrices
//! \attention 
//! -# n must be even and at least 4.  If not, use mpy_DP_RMxRM().
//! -# There are no restrictions on the values of m and p with this function.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 4.5*m*n*p + overhead <td> Cycle count includes the call and return
//! <tr><td> m=2 n=8, p=2 takes ~287 cycles     <td> versus 4.5*m*n*p = 144
//! <tr><td> m=8, n=8, p=8 takes ~3947 cycles    <td> versus 4.5*m*n*p = 2304
//! <tr><td> m=16, n=16, p=16 takes ~26299 cycles <td> versus 
//! 4.5*m*n*p = 18432
//! </table>
//                            
extern void mpy_DP_RMxRM_2(float64_t *y, const float64_t *w, 
 const float64_t *x, const uint16_t m, const uint16_t n, const uint16_t p);                          
                          
                          
                          
//! \brief Multiplication of a Real scalar and a Real Vector 
//! (Double Precision).
//!
//! This module multiplies a real scalar and a real vector.
//! \f[y[i] &=& c*x[i] \f]
//! \param y pointer to the product of the scalar and a real vector
//! \param x pointer to the real input vector
//! \param c scalar multiplier
//! \param N length of the x and y vectors
//! \attention N must be even and a minimum of 4.
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 4*N + 18 <td> Cycle count includes the call and return
//! </table>
//
extern void mpy_DP_RSxRV_2(float64_t *y, const float64_t *x, 
                 const float64_t c, const uint16_t N);
 
//! \brief Multiplication of a Real Scalar, a Real Vector, and another Real
//! Vector (Double Precision).
//!
//! This module multiplies a real scalar with a real vector and another real
//! vector.
//! \f[y[i] &=& c*w[i]*x[i] \f]
//! \param y pointer to the product of the scalar and two real vectors
//! \param w pointer to the first real input vector
//! \param x pointer to the second real input vector
//! \param c scalar multiplier
//! \param N length of the w, x and y vectors
//! \attention N must be even and a minimum of 4.
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 6*N + 27 <td> Cycle count includes the call and return
//! </table>
//
extern void mpy_DP_RSxRVxRV_2(float64_t *y, const float64_t *w, 
          const float64_t *x, const float64_t c, const uint16_t N);
          
//! \brief Multiplication of a Real Vector and a Complex Vector
//! (Double Precision).
//!
//! This module multiplies a real vector and a complex vector.
//! \f[y_{re}[i] &=& x[i]*w_{re}[i] \f]
//! \f[y_{im}[i] &=& x[i]*w_{im}[i] \f]
//! \param y pointer to the product of the real and complex vectors
//! \param w pointer to the complex input vector
//! \param x pointer to the real input vector
//! \param N length of the w, x and y vectors
//! \attention N must be at least 2
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles    <th> Comment 
//! <tr><td> 10*N + 15 <td> Cycle count includes the call and return
//! </table>
//
extern void mpy_DP_RVxCV(complexf64_t *y, const complexf64_t *w,
                         const float64_t *x, const uint16_t N);
                         
//! \brief Multiplication of a Real Vector and a Real Vector.
//!
//! This module multiplies two real vectors (Double Precision).
//! \f[y[i] &=& w[i]*x[i]\f]
//! \param y pointer to the product of two real vectors
//! \param w pointer to the first real input vector
//! \param x pointer to the second real input vector
//! \param N length of the w, x and y vectors
//! \attention N must be even and a minimum of 4.
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 6*N + 17 <td> Cycle count includes the call and return
//! </table>
//
extern void mpy_DP_RVxRV_2(float64_t *y, const float64_t *w, 
                           const float64_t *x, const uint16_t N);

//! \brief Rounding (Unbiased) of a Floating Point Scalar (Double Precision).
//!
//! numerical examples:
//! rnd_DP_RS(+4.4) = +4.0 \\
//! rnd_DP_RS(-4.4) = -4.0 \\
//! rnd_DP_RS(+4.5) = +5.0 \\
//! rnd_DP_RS(-4.5) = -5.0 \\
//! rnd_DP_RS(+4.6) = +5.0 \\
//! rnd_DP_RS(-4.6) = -5.0 \\
//! \param x input value
//! \return rounded
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles <th> Comment 
//! <tr><td> 26     <td> Cycle count includes the call and return
//! </table>
//
extern float64_t rnd_DP_RS(const float64_t x);   

//! \brief Subtraction of a Complex Scalar from a Complex Vector
//! (Double Precision).
//!
//! This module subtracts a complex scalar from a complex vector.
//! \f[y_{re}[i] &=& x_{re}[i] - c_{re} \f]
//! \f[y_{im}[i] &=& x_{im}[i] - c_{im} \f]
//! \param y pointer to the difference of a complex scalar from a complex
//! vector
//! \param x pointer to the complex input vector
//! \param c pointer to the complex input scalar
//! \param N length of the x and y vectors
//! \attention N must be at least 2
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles   <th> Comment 
//! <tr><td> 8*N + 21 <td> Cycle count includes the call and return
//! </table>
//
extern void sub_DP_CSxCV(complexf64_t *y, const complexf64_t *x,
                         const complexf64_t *c, const uint16_t N);

//! \brief Subtraction of a Complex Vector and another Complex Vector
//! (Double Precision).
//!
//! This module subtracts a complex vector from another complex vector.
//! \f[y_{re}[i] &=& w_{re}[i] - x_{re}[i] \f]
//! \f[y_{im}[i] &=& w_{im}[i] - x_{im}[i] \f]
//! \param y pointer to the difference of two complex vectors
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w, x and y vectors
//! \attention N must be at least 2
//! \note The output vector must be placed in a separate RAM block to
//! avoid memory stalls from writes that immediately follow reads to
//! the same physical RAM block
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Cycles    <th> Comment 
//! <tr><td> 12*N + 15 <td> Cycle count includes the call and return
//! </table>
//
extern void sub_DP_CVxCV(complexf64_t *y, const complexf64_t *w,
                         const complexf64_t *x, const uint16_t N);

// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _VECTOR_H_

// End of File
