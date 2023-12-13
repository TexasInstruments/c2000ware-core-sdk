#ifndef _VECTOR_H_
#define _VECTOR_H_
//#############################################################################
//! \file   reference/C/include/$FILENAME$
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
#include "dsp_assert.h"
#include "dsp.h"

//!
//! \defgroup DSP_VECTOR The Vector Module

//! 
//! \ingroup DSP_VECTOR
//@{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************


//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
//globals
//*****************************************************************************


//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief Absolute value (magnitude) of a complex vector
//! \param[out] y real output magnitude vector
//! \param[in]  x complex input vector
//! \param[in]  n size of the vector
//! \f[ y[i] = \sqrt{(x_{re}[i]^{2} + x_{im}[i]^{2})} \f]
//!
extern void VECTOR_absCV(fsize_t *y, const complex_t *x,
                              const uint16_t n);
                              
//! \brief Inverse Absolute value (magnitude) of a complex vector
//! \param[out] y real output inverse magnitude vector
//! \param[in]  x complex input vector
//! \param[in]  n size of the vector
//! \f[ y[i] = \frac{1}{\sqrt{(x_{re}[i]^{2} + x_{im}[i]^{2})}} \f]
//!
extern void VECTOR_iabsCV(fsize_t *y, const complex_t *x,
                              const uint16_t n);
                              
//! \brief Add a complex scalar to a complex vector
//! \param[out] y complex output vector
//! \param[in]  x complex input vector
//! \param[in]  c complex input scalar
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y_{re}[i] = x_{re}[i] + c_{re}
//! y_{im}[i] = x_{im}[i] + c_{im}
//! \f}
//!
extern void VECTOR_addCStoCV(complex_t *y, const complex_t *x,
                      const complex_t c, const uint16_t n);
                      
//! \brief Add a complex scalar to a complex vector
//! \param[out] y complex output vector
//! \param[in]  w complex input vector
//! \param[in]  x complex input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y_{re}[i] = w_{re}[i] + x_{re}[i]
//! y_{im}[i] = w_{im}[i] + x_{im}[i]
//! \f}
//!
extern void VECTOR_addCVtoCV(complex_t *y, const complex_t *w,
                      const complex_t *x, const uint16_t n);

//! \brief Multiply-and-Accumulate of a Complex Vector and a Complex Vector
//! \param[in]  w complex input vector #1
//! \param[in]  x complex input vector #2
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y_{re} = \sigma_{i=0}^{N-1} (w_{re}[i]* x_{re}[i] - w_{im}[i] * x_{im}[i])
//! y_{im} = \sigma_{i=0}^{N-1} (w_{re}[i]* x_{im}[i] + w_{im}[i] * x_{re}[i])
//! \f}
//! \return y complex output value
//! 
extern complex_t VECTOR_macCVbyCV(const complex_t *w, const complex_t *x,
                      const uint16_t n);
                      
//! \brief Multiply-and-Accumulate of a Real Vector and a Complex Vector
//! \param[in]  w complex input vector
//! \param[in]  x real input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y_{re} = \sigma (w_{re}[i] \times x[i])
//! y_{im} = \sigma (w_{im}[i] \times x[i])
//! \f}
//! \return y complex output vector
//! 
extern complex_t VECTOR_macRVbyCV(const complex_t *w, const fsize_t *x,
                      const uint16_t n);
                    
//! \brief Index of Maximum Value of a Real Array
//! \param[in]  x real input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! idx = max(x)
//! \f}
//! \return idx index of the maximum value in the array
//! 
extern uint16_t VECTOR_maxidxRV(const fsize_t *x, const uint16_t n);

//! \brief Mean of Real and Imaginary Parts of a Complex Vector
//! \param[in]  x complex input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! m_{re} = \frac{\sigma x_{re}}{n}
//! m_{im} = \frac{\sigma x_{im}}{n}
//! \f}
//! \return m mean of the real and imaginary parts
//! 
extern complex_t VECTOR_meanCV(const complex_t *x, const uint16_t n);

//! \brief Median of a Real Valued Array of Floats
//! \param[in]  x complex input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! m = median(x)
//! \f}
//! \return m median of the array
//! 
extern fsize_t VECTOR_medianRV(fsize_t *x, const uint16_t n);

//! \brief Median of a Real Valued Array of Floats (Preserved Inputs)
//! \param[in]  x complex input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! m = median(x)
//! \f}
//! \return m median of the array
//! 
extern fsize_t VECTOR_medianNoreorderRV(const fsize_t *x, const uint16_t n);

//! \brief Complex Multiply of Two Complex Values
//! \param[in]  w complex input vector
//! \param[in]  x complex input vector
//! \f{eqnarray}
//! y_{re} = w_{re} * x_{re} - w_{im} * x_{im}
//! y_{im} = w_{re} * x_{im} - w_{im} * x_{re}
//! \f}
//! \return y complex product of two complex values
//!
extern complex_t VECTOR_mpyCSbyCS(const complex_t w, const complex_t x);

//! \brief Complex Multiply of Two Complex Vectors
//! \param[in]  w complex input vector
//! \param[in]  x complex input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y[i]_{re} = w[i]_{re} * x[i]_{re} - w[i]_{im} * x[i]_{im}
//! y[i]_{im} = w[i]_{re} * x[i]_{im} - w[i]_{im} * x[i]_{re}
//! \f}
//! \return y complex product of two complex vectors
//!
extern void VECTOR_mpyCVbyCV(complex_t *y, const complex_t *w,
                      const complex_t *x, const uint16_t n);

//! \brief Multiplication of a Complex Vector and the Complex Conjugate of
//!         another Vector
//! \param[in]  w complex input vector
//! \param[in]  x complex input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y[i]_{re} = w[i]_{re} * x[i]_{re} + w[i]_{im} * x[i]_{im}
//! y[i]_{im} = - w[i]_{re} * x[i]_{im} - w[i]_{im} * x[i]_{re}
//! \f}
//! \return y complex product of a complex vector and conjugate of another
//!
extern void VECTOR_mpyCVbyCVC(complex_t *y, const complex_t *w,
                      const complex_t *x, const uint16_t n);
               
//! \brief Multiplication of Two Real Matrices.
//!
//! \param y pointer to result matrix
//! \param w pointer to 1st source matrix
//! \param x pointer to 2nd source matrix
//! \param m number of rows in the first and output matrices
//! \param n number of columns in the first and rows in the second matrix
//! \param p number of columns in the second and output matrices
//! \f{eqnarray}
//! y[] &=& w[] \times x[]
//! \f}
//! \return y product of a matrix multiplication
//!       
extern void VECTOR_mpyRMbyRM(fsize_t *y, const fsize_t *w, 
                             const fsize_t *x, const uint16_t m, 
                            const uint16_t n, const uint16_t p);
                            
//! \brief Multiplication of a Real scalar and a Real Vector
//! \param[in]  x real input vector
//! \param[in]  c real input scalar
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y[i] = c \times x[i]
//! \f}
//! \return y real product of a real scalar and a real vector
//!
extern void VECTOR_mpyRSbyRV(fsize_t *y, const fsize_t *x,
                      const fsize_t c, const uint16_t n);

//! \brief Multiplication of a Real Scalar, a Real Vector, and another Real
//! Vector
//! \param[in]  w real input vector
//! \param[in]  x real input vector
//! \param[in]  c real input scalar
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y[i] = c \times w[i] \times x[i]
//! \f}
//! \return y real product of a real scalar and two real vectors (element by 
//! element)
//!                      
extern void VECTOR_mpyRSbyRVbyRV(fsize_t *y, const fsize_t *w, 
                      const fsize_t *x, const fsize_t c, const uint16_t n);
          

//! \brief Multiplication of a Real Vector and a Complex Vector
//! \param[in]  w complex input vector
//! \param[in]  x real input vector
//! \param[in]  n size of the vector
//! \f{eqnarray}
//! y[i]_{re} = w[i]_{re} * x[i]
//! y[i]_{im} = w[i]_{im} * x[i]
//! \f}
//! \return y complex product of a real vector and a complex vector
//!
extern void VECTOR_mpyRVbyCV(complex_t *y, const complex_t *w,
                      const fsize_t *x, const uint16_t n);

//! \brief Sorts a real array
//! \param x input array
//! \param[in] nmemb size of a array
//! 
extern void VECTOR_qsortRV(void *base, const uint16_t nmemb);

//! \brief Rounding (Unbiased) of a Scalar
//! \param[in] x input value
//! \return  y rounded value
//! 
extern fsize_t VECTOR_roundRS(const fsize_t x);

//! \brief Subtraction of a Complex Scalar from a Complex Vector
//! \param[out]  y complex difference vector
//! \param[in]   x complex input vector (minuend)
//! \param[in]   c complex input scalar (subtrahend)
//! \param[in]   n size of the vector
//! \f{eqnarray}
//! y_{re}[i] = x_{re}[i] - c_{re}
//! y_{im}[i] = x_{im}[i] - c_{im}
//! \f}
//!
extern void VECTOR_subCSfromCV(complex_t *y, const complex_t *x, 
                        const complex_t c, const uint16_t n);
                        
//! \brief Subtraction of a Complex Vector and another Complex Vector
//! \param[out]  y complex difference vector
//! \param[in]   w complex input vector (minuend)
//! \param[in]   x complex input vector (subtrahend)
//! \param[in]   n size of the vector
//! \f{eqnarray}
//! y_{re}[i] = w_{re}[i] - x_{re}[i]
//! y_{im}[i] = w_{im}[i] - x_{im}[i]
//! \f}
//!                       
extern void VECTOR_subCVfromCV(complex_t *y, const complex_t *w, 
                    const complex_t *x, const uint16_t n);
                    
#ifdef __cplusplus
}
#endif //extern "C"

//@} //ingroup

#endif // end of _VECTOR_H_ definition
