#ifndef _FASTRTS_CORDIC_H_
#define _FASTRTS_CORDIC_H_
//#############################################################################
//! \file   reference/C/include/$FILENAME$
//! \brief  Fast RTS CORDIC (Coordinate Rotation Digital Computer) Header File
//! \author Vishal Coelho 
//! \date   10-Aug-2016
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


//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "fastrts.h"

//!
//! \defgroup FASTRTS_CORDIC CORDIC Routines

//! 
//! \ingroup FASTRTS_CORDIC
//@{
    
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
// Convert a unsigned integer to IQMAX representation where I is 3 bits 
// and Q is width(isize_t) - 3 bits wide, and the argument |a| must be <= 4.
// Since sizeof returns the size in bytes we multiply by 8 (<< 3) to get the 
// number of bits
// NOTE: initially isize_t was intmax_t, i.e. the max supported integer size 
// on the lcoal machine, but is now limited to either 32 or 64-bits to 
// facilitate conversion to float or double respectively
#define IQMAX(a) (isize_t)a << ((sizeof(isize_t) << 3) - (isize_t)3U)

// Convert an IQMAX to float (or double)
#define IQMAXTOF(a) ((fsize_t)(a) / \
        (fsize_t)((isize_t)1 << ((sizeof(isize_t) << 3) - (isize_t)3U)))

// Convert a float (or double) to IQMAX
#define FTOIQMAX(a) (isize_t)((a) * \
             (fsize_t)((isize_t)1 << ((sizeof(isize_t) << 3) - (isize_t)3U)))
                 
// Return the sign of a given variable
#define SIGN(x) ((x >= (__typeof__(x))0)? (__typeof__(x))1: (__typeof__(x))-1)

// Access hex table value as either float or double
// Get the nth entry of the table pointed to by 't'
#define GET_TBL_HEX_VAL(t, n) (*((fsize_t *)(t + n)))

// Maximum number of CORDIC iterations possible
#define MAX_CORDIC_ITERATIONS   (64U)

#if USE_FPU64 == 1
#define THETA_MAX       ( 1.743228662047234)
#define COS_THETA_MAX   (-0.171579118813211)
#define SIN_THETA_MAX   ( 0.985170343639760)
#else //USE_FPU32 == 1
#define THETA_MAX       ( 1.743228662047234F)
#define COS_THETA_MAX   (-0.171579118813211F)
#define SIN_THETA_MAX   ( 0.985170343639760F)
#endif //USE_FPU64 == 1

//*****************************************************************************
// typedefs
//*****************************************************************************
//! CORDIC structure
//!
typedef struct _CORDIC_t_
{
    isize_t x_i;               //!< x coordinate
    isize_t y_i;               //!< y coordinate
    isize_t z_i;               //!< mode dependent angle (or angular error)
    uint16_t N;                //!< number of CORDIC iterations (max = 64)
    const fsize_t *atanTable;  //!< Pointer to the atan(2^-i) table
    const fsize_t *scaleTable; //!< Pointer to the 1/sqrt(1 + 2^(-2i)) table
    void (*runKernel)(void *); //!< CORDIC kernel
}CORDIC_t;


//! Handle to a CORDIC object
//!
typedef CORDIC_t *hnd_CORDIC_t;

//*****************************************************************************
//globals
//*****************************************************************************
//! \brief CORDIC Arctangent table
//!
extern const fsize_t FastRTS_CORDIC_atanTbl[];

//! \brief CORDIC Scale table
//!
extern const fsize_t FastRTS_CORDIC_scaleTbl[];
//*****************************************************************************
// 'static inline' functions
//*****************************************************************************
//! \brief Set the x_i parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] x_i, value
//!
static inline void FastRTS_CORDIC_setx_i(hnd_CORDIC_t hc, const isize_t x_i)
{
    hc->x_i = x_i;
}

//! \brief Get the x_i parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return x_i, value
//!
static inline isize_t FastRTS_CORDIC_getx_i(hnd_CORDIC_t hc)
{
    return(hc->x_i);
}

//! \brief Set the y_i parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] y_i, value
//!
static inline void FastRTS_CORDIC_sety_i(hnd_CORDIC_t hc, const isize_t y_i)
{
    hc->y_i = y_i;
}

//! \brief Get the y_i parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return y_i, value
//!
static inline isize_t FastRTS_CORDIC_gety_i(hnd_CORDIC_t hc)
{
    return(hc->y_i);
}

//! \brief Set the z_i parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] z_i, value
//!
static inline void FastRTS_CORDIC_setz_i(hnd_CORDIC_t hc, const isize_t z_i)
{
    hc->z_i = z_i;
}

//! \brief Get the z_i parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return z_i, value
//!
static inline isize_t FastRTS_CORDIC_getz_i(hnd_CORDIC_t hc)
{
    return(hc->z_i);
}

//! \brief Set the N parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] N, number of CORDIC iterations
//!
static inline void FastRTS_CORDIC_setN(hnd_CORDIC_t hc, const uint16_t N)
{
    hc->N = N;
}

//! \brief Get the N parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return N, value
//!
static inline uint16_t FastRTS_CORDIC_getN(hnd_CORDIC_t hc)
{
    return(hc->N);
}

//! \brief Set the atanTable pointer parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] p_at, pointer to the arctangent CORDIC table
//!
static inline void FastRTS_CORDIC_setAtanTblPtr(hnd_CORDIC_t hc, 
    const fsize_t *p_at)
{
    hc->atanTable = p_at;
}

//! \brief Get the address of the atanTable pointer parameter of the 
//! CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return p_at, address of the arctangent CORDIC table
//!
static inline const fsize_t * FastRTS_CORDIC_getAtanTblPtr(hnd_CORDIC_t hc)
{
    return(hc->atanTable);
}

//! \brief Set the scaleTable pointer parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] p_st, pointer to the scale factor CORDIC table
//!
static inline void FastRTS_CORDIC_setScaleTblPtr(hnd_CORDIC_t hc, 
    const fsize_t *p_st)
{
    hc->scaleTable = p_st;
}

//! \brief Get the address of the scaleTable pointer parameter of the 
//! CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return p_st, address of the scale factor CORDIC table
//!
static inline const fsize_t * FastRTS_CORDIC_getScaleTblPtr(hnd_CORDIC_t hc)
{
    return(hc->scaleTable);
}


//! \brief Set the runKernel function pointer parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] pfn, pointer to the kernel function
//!
static inline void FastRTS_CORDIC_setRunKernelPtr(hnd_CORDIC_t hc, 
    const v_pfn_v pfn)
{
    hc->runKernel = pfn;
}

//! \brief Get the address of the runKernel function parameter of the 
//! CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return pfn, pointer to the kernel function
//!
static inline v_pfn_v FastRTS_CORDIC_getRunKernelPtr(hnd_CORDIC_t hc)
{
    return(hc->runKernel);
}

//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief CORDIC Rotation Mode
//! \param[in] hc , handle to the CORDIC object
//! 
extern void FastRTS_CORDIC_rotationKernel(hnd_CORDIC_t hc);

//! \brief CORDIC Vectoring Mode
//! \param[in] hc , handle to the CORDIC object
//! 
extern void FastRTS_CORDIC_vectoringKernel(hnd_CORDIC_t hc);

//! \brief The Sine Function (CORDIC)
//! \param[in] theta , Angle in radians
//! \return The sine of the angle
//!
extern fsize_t FastRTS_CORDIC_sin(const fsize_t theta);

//! \brief The Cosine Function (CORDIC)
//! \param[in] theta , Angle in radians
//! \return The cosine of the angle
//!
extern fsize_t FastRTS_CORDIC_cos(const fsize_t theta);

//! \brief The arctangent-2 Function (CORDIC)
//! \param[in] y , y co-ordinate
//! \param[in] x , x co-ordinate
//! \return The angle of the vector
//!
extern fsize_t FastRTS_CORDIC_atan2(const fsize_t y, const fsize_t x);
#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif //end of _FASTRTS_CORDIC_H_ definition
