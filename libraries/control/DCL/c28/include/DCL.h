/* DCL.h - C2000 Digital Control Library
 *
 */
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

#ifndef _C_DCL_H
#define _C_DCL_H

#ifdef __cplusplus
extern "C" {
#endif

//! \file           DCL.h
//! \brief          Contains the public interface to the common
//!                 Digital Controller Library functions

//! \brief          Library version number formatted for numerical comparison
//!
#define DCL_VERSION 3050000

#ifndef C2000_IEEE754_TYPES
#define C2000_IEEE754_TYPES
#ifdef __TI_EABI__
typedef float float32_t;
typedef double float64_t;
#else
typedef float float32_t;
typedef long double float64_t;
#endif      // __TI_EABI__
#endif      // C2000_IEEE754_TYPES

#ifndef __TMS320C28XX_CLA__

#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

//! \brief          Local definitions of mathematical constants
//!
#define CONST_PI_32     3.14159265358979323846f
#define CONST_2PI_32    2.0f * CONST_PI_32

#define CONST_PI_64     3.1415926535897932384626433832795028841971693993751058209749445923078164062L
#define CONST_2PI_64    2.0L * CONST_PI_64

//! \brief          Defines 32-bit null address for pointer initialization
//!
#define NULL_ADDR   0x00000000

//! \brief          Define the acceptable FPU numerical tolerances
//!
#define DEFAULT_FPU32_TOL   1.0e-06f
#define DEFAULT_FPU64_TOL   1.0e-10f

//! \brief          Determines numerical proximity to specified value
//!
#define F32_IS_VALUE(x,y)   (((x < (y + DEFAULT_FPU32_TOL)) && (x > (y - DEFAULT_FPU32_TOL))) ? 1 : 0)
#define F64_IS_VALUE(x,y)   (((x < (y + DEFAULT_FPU64_TOL)) && (x > (y - DEFAULT_FPU64_TOL))) ? 1 : 0)

//! \brief          Determines numerical proximity to zero
//!
#define F32_IS_ZERO(x)      F32_IS_VALUE(x,0.0f)
#define F64_IS_ZERO(x)      F64_IS_VALUE(x,0.0L)

//! \brief          Returns a random floating point result between -1.0 and +1.0
//!                 where 'a' is a single or double precision float.
//!                 Useful for initialization of arrays and matrices during test.
//!					Ensure compiler switch "--fp_mode = relaxed" is set to ensure h/w division.
//!
//! \code
//! float32_t s = DCL_randf(1.0f);
//!
#define DCL_randf(a)         (a * ((float32_t) rand() / (float32_t) (RAND_MAX >> 1) - 1.0f))
#define DCL_randf64(a)       (a * ((float64_t) rand() / (float64_t) (RAND_MAX >> 1) - 1.0L))

//! \brief          Defines the lower limit on derivative filter coefficient c2
//!                 in order for fc to lie below the Nyquist frequency
//!
#define DCL_C2_LIMIT_32    ((2.0f - CONST_PI_32) / (2.0f + CONST_PI_32))
#define DCL_C2_LIMIT_64    ((2.0L - CONST_PI_64) / (2.0L + CONST_PI_64))

//! \brief          Define the default control period in seconds
//!
#define DCL_DEFAULT_T_F32 100.0e-06f
#define DCL_DEFAULT_T_F64 100.0e-06L

//! \brief          Build the library with controller test points enabled
//!
#define DCL_TESTPOINTS_ENABLED

//! \brief          Build the library with break points enabled
//!
#define DCL_BREAK_POINTS_ENABLED

//! \brief          Defines a debug break point
//!
#ifdef DCL_BREAK_POINTS_ENABLED
#define DCL_BREAK_POINT asm(" ESTOP0")
#else
#define DCL_BREAK_POINT ;
#endif

//! \brief          Boundary instructions for atomic code blocks
//!                 Global interrupt mask is set at start of atomic block and
//!                 restored to its' original value at the end
//!
#ifdef __TMS320C28XX__
#define DCL_DISABLE_INTS    DCL_disableInts()
#define DCL_RESTORE_INTS(v) DCL_restoreInts(v)

//! \brief          Sets global interrupts mask
//! \return         Original ST1 register value
//!
static inline int16_t DCL_disableInts(void)
{
    return __disable_interrupts();
}

//! \brief          Restores global interrupts if they were previously enabled
//! \param[in] v    Original ST1 register value
//! \return         None
//!
static inline void DCL_restoreInts(int16_t v)
{
    if (0 == (v & 0x1))
    {
        __enable_interrupts();
    }
}

#else
#define DCL_DISABLE_INTS    0
#define DCL_RESTORE_INTS(v) ;
#warning "CPU not recognized.  Parameter updates may not be atomic."
#endif

//--- Controller Common Support Structure ------------------------------------

//! \brief          Defines the controller common support structure
//!
//! \details        The CSS is accessed via a pointer in most of the DCL
//!                 controller structs.  It contains data used for testing and
//!                 configuring the controller, as well as for error checking.
//!
typedef struct dcl_css {
    float32_t tpt;      //!< Test point
    float32_t T;        //!< Controller period in seconds
    uint32_t sts;       //!< Status word
    uint32_t err;       //!< Error code
    uint32_t loc;       //!< Error location
} DCL_CSS;

//! \brief          Default values to initialize the CSS structure
//!
#define DCL_CSS_DEFAULTS { 0.0f, DCL_DEFAULT_T_F32, 0UL, 0UL, 0UL }

//! \brief          Loads the controller period in the CSS
//!                 CSS pointer must be configured first
//! \param[in] p    Pointer to the controller structure
//! \param[in] a    Sample period in seconds
//! \return         None
//!
#define DCL_SET_CONTROLLER_PERIOD(p,a)  ((p)->css->T = a)

//! \brief          Re-definition of legacy controller period call
//!
#define	DCL_SET_SAMPLE_RATE		DCL_SET_CONTROLLER_PERIOD


//--- Status word ------------------------------------------------------------

//! \brief          Defines the library enumerated status bits
//!
//! \details        To perform a safe parameter update, the user first loads new
//!                 parameters into the controller shadow parameter set, then sets
//!                 the STS_UPDATE_PENDING bit in the controller status word.  The
//!                 next call to the update function performs the "shadow-to-
//!                 active" set copy while global interrupts are disabled.
//!
enum dcl_status_bits {
    STS_NONE = 0UL,                     //!< Status empty
    STS_UPDATE_PENDING = (1U << 0),    //!< Parameter update pending
    STS_CONTROLLER_RUNNING = (1U << 1), //!< Controller operation in progress
    STS_ADJUSTMENT_RUNNING = (1U << 2) //!< Parameter adjustment in progress
};

//! \brief          Macros to set the update flag in the status word to initiate
//!                 controller parameter update on next DCL_update() call, and to
//!                 clear the flag on completion.
//!
#define DCL_REQUEST_UPDATE(p)           ((p)->css->sts |= STS_UPDATE_PENDING)
#define DCL_CLEAR_UPDATE_REQUEST(p)     ((p)->css->sts &= ~STS_UPDATE_PENDING)

//! \brief          Macro to determine whether a parameter update is pending
//!                 based on the STS_UPDATE_PENDING bit in the status word.
#define DCL_UPDATE_WAITING(p)           (0U != ((p)->css->sts & STS_UPDATE_PENDING))

//! \brief          Macros placed at the beginning and end of the controller
//!                 so that other functions know a control operation is in
//!                 progress.  Typically only used with complex controllers
//!                 which may not be atomic.
//!
#define DCL_CONTROLLER_BEGIN(p)         ((p)->css->sts |= STS_CONTROLLER_RUNNING)
#define DCL_CONTROLLER_END(p)           ((p)->css->sts &= ~STS_CONTROLLER_RUNNING)

//! \brief          Macro to determine whether a controller is being executed
//!                 based on the DCL_CONTROLLER_RUNNING bit in the status word.
#define DCL_CONTROLLER_IN_PROGRESS(p)   (0U != ((p)->css->sts & STS_CONTROLLER_RUNNING))

//! \brief          Macros to set the flag in the status word to denote
//!                 that parameter adjustment is in progress, and to
//!                 clear the flag when the target is reached.
//!
#define DCL_ADJUSTMENT_RUNNING(p)       ((p)->css->sts |= STS_ADJUSTMENT_RUNNING)
#define DCL_ADJUSTMENT_COMPLETE(p)      ((p)->css->sts &= ~STS_ADJUSTMENT_RUNNING)

//! \brief          Macro to determine whether parameter adjustment is underway
//!                 based on the DCL_ADJUSTMENT_RUNNING bit in the status word.
#define DCL_ADJUSTMENT_IN_PROGRESS(p)   (0U != ((p)->css->sts & STS_ADJUSTMENT_RUNNING))


//--- Error handling ---------------------------------------------------------

//! \brief          Build the library with error handling enabled
//!
#define DCL_ERROR_HANDLING_ENABLED

//! \brief          Defines the library enumerated error codes
//!                 These will be applied as bit masks in the error handler
//!
enum dcl_error_codes {
    ERR_NONE = 0U,                     //!< No error
    ERR_PARAM_RANGE = (1U << 0),       //!< Parameter range exceeded
    ERR_PARAM_INVALID = (1U << 1),     //!< Parameter not valid
    ERR_PARAM_WARN = (1U << 2),        //!< Parameter warning
    ERR_INPUT_RANGE = (1U << 3),       //!< Input range exceeded
    ERR_OVERFLOW = (1U << 4),          //!< Numerical overflow
    ERR_UNDERFLOW = (1U << 5),         //!< Numerical underflow
    ERR_VERSION = (1U << 6),           //!< Incorrect DCL version
    ERR_DEVICE = (1U << 7),            //!< Device not supported
    ERR_CONTROLLER = (1U << 8),        //!< Controller operation not completed
    ERR_TIMING = (1U << 9),            //!< Timing error
    ERR_COMPUTATION = (1U << 10)       //!< Computation error
};

//! \brief          Macro to clear stored error code in CSS
//!
#define DCL_CLEAR_ERROR_CODE(p)     (p->css->err = ERR_NONE)

//! \brief          Macro to store code location of error in CSS
//!
#define DCL_GET_ERROR_LOC(n)        (n->loc = (ERR_NONE == n->err) ? NULL_ADDR : __LINE__)

//! \brief          Define error handling routine
//!
#define DCL_RUN_ERROR_HANDLER(n)    DCL_runErrorHandler(n)

//! \brief          Prototype for external basic error handler [DCL_error.c]
//! \param[in] p    Pointer to DCL_CSS structure
//! \return         None
//!
extern void DCL_runErrorHandler(DCL_CSS *p);


//--- Polynomial stability functions -----------------------------------------

//! \brief          Determines stability of a first order real polynomial
//!                 P(z) = z + a1
//! \param[in] a1   Coefficient a1
//! \return         'true' if the root has magnitude less than 1, 'false' otherwise
//!
static inline bool DCL_isStablePn1(float32_t a1)
{
    return(((a1 * a1) < 1.0f) ? true : false);
}

//! \brief          Determines stability of a second order polynomial with real coefficients
//!                 P(z) = a0 z^2 + a1 z + a2
//! \param[in] a1   Coefficient a1
//! \param[in] a2   Coefficient a2
//! \return         'true' if both roots have magnitude less than 1, 'false' otherwise
//!
static inline bool DCL_isStablePn2(float32_t a0, float32_t a1, float32_t a2)
{
    float32_t b0, b1, c0;

    b0 = a0 - a2 * a2 / a0;
    b1 = a1 - a1 * a2 / a0;
    c0 = b0 - b1 * b1 / b0;

    if ((a0 > 0.0f) && (b0 > 0.0f) && (c0 > 0.0f))
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

//! \brief          Determines stability of a third order polynomial with real coefficients
//!                 P(z) = a0 z^3 + a1 z^2 + a2 z + a3
//! \param[in] a1   Coefficient a1
//! \param[in] a2   Coefficient a2
//! \param[in] a3   Coefficient a3
//! \return         'true' if all roots have magnitude less than 1, 'false' otherwise
//!
static inline bool DCL_isStablePn3(float32_t a0, float32_t a1, float32_t a2, float32_t a3)
{
    float32_t b0, b1, b2, c0, c1, d0;

    b0 = a0 - a3 * a3 / a0;
    b1 = a1 - a2 * a3 / a0;
    b2 = a2 - a1 * a3 / a0;
    c0 = b0 - b2 * b2 / b0;
    c1 = b1 - b1 * b2 / b0;
    d0 = c0 - c1 * c1 / c0;

    if ((a0 > 0.0f) && (b0 > 0.0f) && (c0 > 0.0f) && (d0 > 0.0f))
    {
        return(true);
    }
    else
    {
        return(false);
    }
}


//--- ZPK3 structure ---------------------------------------------------------

//! \brief          Defines the DCL_ZPK3 controller structure.
//!
//! \details        Allows controllers to be defined in terms of complex pole
//!                 and zero frequencies.  The common structure consists of
//!                 three complex zeros, three complex poles, and a real gain.
//!                 All frequencies must be specified in radians/sec.
//!
typedef struct dcl_zpk3 {
    float complex z1;
    float complex z2;
    float complex z3;
    float complex p1;
    float complex p2;
    float complex p3;
    float32_t K;
} DCL_ZPK3;

//! \brief          Defines default values to initialize the DCL_ZPK3 structure
//!
#define ZPK3_DEFAULTS { 0.0f + 0.0f*I, 0.0f + 0.0f*I, 0.0f + 0.0f*I, \
                        0.0f + 0.0f*I, 0.0f + 0.0f*I, 0.0f + 0.0f*I, \
                        1.0f }

//! \brief          Determines stability of a ZPK3 representation by checking pole magnitude
//! \param[in] q    Pointer to DCL_ZPK3 structure
//! \return         'true' if all poles have magnitude less than 1, 'false' otherwise
//!
static inline bool DCL_isStableZpk3(DCL_ZPK3 *q)
{
    return(((cabsf(q->p1) < 1.0f) && (cabsf(q->p2) < 1.0f) && (cabsf(q->p3) < 1.0f)) ? true : false);
}


//----------------------------------------------------------------------------

#endif // __TMS320C28XX_CLA__

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCL_H

/* end of file */
