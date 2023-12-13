/* DCL_refgen64.h - Reference generator module header file (double precision)
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

#ifndef _C_DCL_REFGEN64_H
#define _C_DCL_REFGEN64_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DCL.h"

//! \brief          Region related symbols for function placement
//
#pragma CODE_SECTION(DCL_runRefgen64,"dclfuncs")
#pragma CODE_SECTION(DCL_getRefgen64PhaseA,"dclfuncs")
#pragma CODE_SECTION(DCL_getRefgen64PhaseB,"dclfuncs")
#pragma CODE_SECTION(DCL_getRefgen64PhaseC,"dclfuncs")

//! \brief          Defines the minimum normalized increment
//!
#define DCL_REFGEN64_MIN_INC      1.0e-10

//! \brief          Defines the REFGEN operating modes
//!
enum dcl_rgen64_modes {
    REFGEN64_OFF = 0,
    REFGEN64_STATIC,
    REFGEN64_SINE,
    REFGEN64_SQUARE,
    REFGEN64_SAW,
    REFGEN64_TRIANGLE,
    REFGEN64_PULSE,
    REFGEN64_SINE2,
    REFGEN64_SINE3
};

//! \brief          Defines the DCL_REFGEN64 structure
//!
typedef volatile struct dcl_refgen64 {
    float64_t   rtgt;       //!< Target ramp value
    float64_t   rinc;       //!< Ramp increment
    float64_t   amtgt;      //!< Target amplitude value
    float64_t   aminc;      //!< Amplitude increment
    float64_t   fmtgt;      //!< Frequency ramp value
    float64_t   fminc;      //!< Frequency increment
    float64_t   thinc;      //!< Angular increment
    float64_t   duty;       //!< Pulse duty cycle
    float64_t   umax;       //!< Maximum allowable output
    float64_t   umin;       //!< Minimum allowable output
    float64_t   yr;         //!< Ramp generator output
    float64_t   ampl;       //!< Dynamic amplitude
    float64_t   freq;       //!< Dynamic frequency
    float64_t   theta;      //!< Normalized angle - phase A
    float64_t   thetb;      //!< Normalized angle - phase B
    float64_t   thetc;      //!< Normalized angle - phase C
    float64_t   ya;         //!< Phase A output
    float64_t   yb;         //!< Phase B output
    float64_t   yc;         //!< Phase C output
    int16_t     mode;       //!< Operating mode
    int16_t     spare;      //!< Spare for alignment
    DCL_CSS     *css;       //!< Pointer to the common support structure
} DCL_REFGEN64;

//! \brief          Defines default values to initialize the DCL_REFGEN64 structure
//!
#define DCL_REFGEN64_DEFAULTS { 0.0,  0.0, \
                              0.0,  0.0, \
                              0.0,  0.0,  0.0, \
                              0.0,  1.0,  1.0,  1.0, -1.0, \
                              0.0,  0.0,  0.0,  0.0, \
                              0.0,  0.0,  0.0, \
                              REFGEN64_OFF, 0, NULL_ADDR }

//----------------------------------------------------------------------------

//! \brief          Resets DCL_REFGEN64 dynamic data
//! \param[in] p    Pointer to the DCL_REFGEN64 structure
//! \return         None
//!
static inline void DCL_resetRefgen64(DCL_REFGEN64 *p)
{
    p->ampl = 0.0;
    p->freq = 0.0;
    p->rinc = 0.0;
    p->theta = 0.0;
    p->thetb = 0.0;
    p->thetc = 0.0;
    p->thinc = 0.0;
    p->yr = 0.0;
    p->ya = 0.0;
    p->yb = 0.0;
    p->yc = 0.0;
}


//! \brief          Loads the REFGEN64 ramp parameters
//!
//! \param[in] p    Pointer to the DCL_REFGEN64 structure
//! \param[in] tgt  The new static reference target
//! \param[in] tr   The time interval to reach the new target
//! \return         Void
//!
static inline void DCL_setRefgen64Ramp(DCL_REFGEN64 *p, float64_t tgt, float64_t tr)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (tr < 0.0) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    // compute ramp increment
    tr = (tr < p->css->T) ? p->css->T : tr;
    p->rtgt = tgt;
    p->rinc = p->css->T * (tgt - p->yr) / tr;

    // clamp minimum ramp increment
    if (!(0.0 == p->rinc) && (fabs(p->rinc) < DCL_REFGEN64_MIN_INC))
    {
#ifdef DCL_ERROR_HANDLING_ENABLED
        p->css->err = ERR_COMPUTATION;
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
#endif
        if (signbit(p->rinc))
        {
            p->rinc = -DCL_REFGEN64_MIN_INC;
        }
        else
        {
            p->rinc = DCL_REFGEN64_MIN_INC;
        }
    }
}


//! \brief          Loads the REFGEN dynamic amplitude
//!
//! \param[in] p    Pointer to the DCL_REFGEN64 structure
//! \param[in] ampl The new target amplitude
//! \param[in] tr   The time interval to reach the new target
//! \return         Void
//!
static inline void DCL_setRefgen64Ampl(DCL_REFGEN64 *p, float64_t ampl, float64_t tr)
{
    float64_t v;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (tr < 0.0) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    // compute amplitude increment
    v = (float64_t) p->css->T;
    tr = (tr < v) ? v : tr;
    p->amtgt = ampl;
    p->aminc = v * (ampl - p->ampl) / tr;

    // clamp minimum amplitude increment
    if ((p->aminc > 0.0) && (fabs(p->aminc) < DCL_REFGEN64_MIN_INC))
    {
#ifdef DCL_ERROR_HANDLING_ENABLED
        p->css->err = ERR_COMPUTATION;
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
#endif
        if (signbit(p->aminc))
        {
            p->aminc = -DCL_REFGEN64_MIN_INC;
        }
        else
        {
            p->aminc = DCL_REFGEN64_MIN_INC;
        }
    }
}


//! \brief          Loads the REFGEN64 frequency
//!
//! \param[in] p    Pointer to the DCL_REFGEN64 structure
//! \param[in] freq The new frequency in Hz
//! \param[in] tr   The time interval to reach the new target
//! \return         Void
//!
static inline void DCL_setRefgen64Freq(DCL_REFGEN64 *p, float64_t freq, float64_t tr)
{
    float64_t v;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (tr < 0.0) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    // compute frequency increment
    v = (float64_t) p->css->T;
    tr = (tr < v) ? v : tr;
    p->fmtgt = freq;
    p->fminc = v * (freq - p->freq) / tr;

    // clamp minimum frequency increment
    if ((p->fminc > 0.0) && (fabs(p->fminc) < DCL_REFGEN64_MIN_INC))
    {
#ifdef DCL_ERROR_HANDLING_ENABLED
        p->css->err = ERR_COMPUTATION;
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
#endif
        if (signbit(p->fminc))
        {
            p->fminc = -DCL_REFGEN64_MIN_INC;
        }
        else
        {
            p->fminc = DCL_REFGEN64_MIN_INC;
        }
    }
}


//! \brief          Loads the REFGEN64 pulse duty cycle
//! \param[in] p    Pointer to the DCL_REFGEN64 structure
//! \param[in] duty The new per-unit duty cycle
//! \return         None
//!
static inline void DCL_setRefgen64Duty(DCL_REFGEN64 *p, float64_t duty)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((duty < 0.0) || (duty > 1.0)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    p->duty = duty;
}

//! \brief          Loads the REFGEN64 output clam limits
//! \param[in] p    Pointer to the DCL_REFGEN64 structure
//! \param[in] max  The upper limit
//! \param[in] min  The lower limit
//! \return         None
//!
static inline void DCL_setRefgen64Clamp(DCL_REFGEN64 *p, float64_t max, float64_t min)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (max < min) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    p->umax = max;
    p->umin = min;
}


//! \brief          Sets the REFGEN64 operating mode
//! \param[in] p    Pointer to the DCL_REFGEN64 structure
//! \param[in] mode The new operating mode
//! \return         None
//!
static inline void DCL_setRefgen64Mode(DCL_REFGEN64 *p, int16_t mode)
{
    p->mode = mode;
}


//! \brief          Runs the REFGEN64 module
//! \param[in] p    Pointer to the DCL_REFGEN64 structure
//! \return         None
//!
static inline void DCL_runRefgen64(DCL_REFGEN64 *p)
{
    float64_t v;

    // static offset generator
    if (!F64_IS_ZERO(p->rinc))
    {
        if (fabs(p->rinc) > fabs(p->rtgt - p->yr))
        {
            p->yr = p->rtgt;
            p->rinc = 0.0;
            DCL_ADJUSTMENT_COMPLETE(p);
        }
        else
        {
#ifdef DCL_ERROR_HANDLING_ENABLED
            v = p->yr;
#endif
            p->yr += p->rinc;
#ifdef DCL_ERROR_HANDLING_ENABLED
            if (F64_IS_ZERO(v - p->yr))
            {
                p->css->err = ERR_COMPUTATION;
                DCL_GET_ERROR_LOC(p->css);
                DCL_RUN_ERROR_HANDLER(p->css);
            }
#endif
            DCL_ADJUSTMENT_RUNNING(p);
        }
    }

    // amplitude modulator
    if (!F64_IS_ZERO(p->aminc))
    {
        if (fabs(p->aminc) > fabs(p->amtgt - p->ampl))
        {
            p->ampl = p->amtgt;
            p->aminc = 0.0;
        }
        else
        {
#ifdef DCL_ERROR_HANDLING_ENABLED
            v = p->ampl;
#endif
            p->ampl += p->aminc;
#ifdef DCL_ERROR_HANDLING_ENABLED
            if (F64_IS_ZERO(v - p->ampl))
            {
                p->css->err = ERR_COMPUTATION;
                DCL_GET_ERROR_LOC(p->css);
                DCL_RUN_ERROR_HANDLER(p->css);
            }
#endif
        }
    }

    // frequency modulator
    if (!F64_IS_ZERO(p->fminc))
    {
        if (fabs(p->fminc) > fabs(p->fmtgt - p->freq))
        {
            p->freq = p->fmtgt;
            p->fminc = 0.0;
        }
        else
        {
#ifdef DCL_ERROR_HANDLING_ENABLED
            v = p->freq;
#endif
            p->freq += p->fminc;
#ifdef DCL_ERROR_HANDLING_ENABLED
            if (F64_IS_ZERO(v - p->freq))
            {
                p->css->err = ERR_COMPUTATION;
                DCL_GET_ERROR_LOC(p->css);
                DCL_RUN_ERROR_HANDLER(p->css);
            }
#endif
        }
    }

    // angle increment
    if (p->freq > 0.0)
    {
        p->thinc = p->css->T * p->freq;
        if (p->thinc < DCL_REFGEN64_MIN_INC)
        {
#ifdef DCL_ERROR_HANDLING_ENABLED
            p->css->err = ERR_COMPUTATION;
            DCL_GET_ERROR_LOC(p->css);
            DCL_RUN_ERROR_HANDLER(p->css);
#endif
            p->thinc = DCL_REFGEN64_MIN_INC;
        }
    }
    else
    {
        p->thinc = 0.0;
    }

    p->theta += p->thinc;
    p->theta -= (p->theta >= 1.0) ? 1.0 : 0.0;

    // dynamic signal generator
    switch (p->mode) {

        case REFGEN64_STATIC:
            p->ya = 0.0;
            p->yb = 0.0;
            p->yc = 0.0;
            break;

        case REFGEN64_SINE:
            p->ya = sin(CONST_2PI_64 * p->theta);
            p->yb = 0.0;
            p->yc = 0.0;
            break;

        case REFGEN64_SQUARE:
            p->ya = (p->theta > 0.5) ? 1.0 : 0.0;
            p->yb = 0.0;
            p->yc = 0.0;
            break;

        case REFGEN64_SAW:
            p->ya = p->theta;
            p->yb = 0.0;
            p->yc = 0.0;
            break;

        case REFGEN64_TRIANGLE:
            if (p->theta < 0.5)
            {
                p->ya = 2.0 * p->theta;
            }
            else
            {
                p->ya = 1.0 - 2.0 * (p->theta - 0.5);
            }
            p->yb = 0.0;
            p->yc = 0.0;
            break;

        case REFGEN64_PULSE:
            p->ya = (p->theta > p->duty) ? 0.0 : 1.0;
            p->yb = 0.0;
            p->yc = 0.0;
            break;

        case REFGEN64_SINE2:
            p->ya = sin(CONST_2PI_64 * p->theta);
            p->yb = cos(CONST_2PI_64 * p->theta);
            p->yc = 0.0;
            break;

        case REFGEN64_SINE3:
            p->thetb = p->theta + 0.3333333333333;
            p->thetc = p->theta + 0.6666666666667;
            p->thetb -= (p->thetb >= 1.0) ? 1.0 : 0.0;
            p->thetc -= (p->thetc >= 1.0) ? 1.0 : 0.0;

            p->ya = sin(CONST_2PI_64 * p->theta);
            p->yb = sin(CONST_2PI_64 * p->thetb);
            p->yc = sin(CONST_2PI_64 * p->thetc);
            break;

        case REFGEN64_OFF:
        default:
            p->yr = 0.0;
            p->ya = 0.0;
            p->yb = 0.0;
            p->yc = 0.0;
    }

    // output sum & saturation
#if (__TI_COMPILER_VERSION__ > 19005000)
    v = __fmin64(p->ampl * p->ya + p->yr, p->umax);
    p->ya = __fmax64(v, p->umin);
    v = __fmin64(p->ampl * p->yb + p->yr, p->umax);
    p->yb = __fmax64(v, p->umin);
    v = __fmin64(p->ampl * p->yc + p->yr, p->umax);
    p->yc = __fmax64(v, p->umin);
#else
    v = fmin(p->ampl * p->ya + p->yr, p->umax);
    p->ya = fmax(v, p->umin);
    v = fmin(p->ampl * p->yb + p->yr, p->umax);
    p->yb = fmax(v, p->umin);
    v = fmin(p->ampl * p->yc + p->yr, p->umax);
    p->yc = fmax(v, p->umin);
#endif
}


//! \brief          Returns the phase reference output
//! \param[in] p    Pointer to the active DCL_REFGEN64 structure
//! \return         The phase A reference output
//!
static inline float64_t DCL_getRefgen64PhaseA(DCL_REFGEN64 *p)
{
    return(p->ya);
}


//! \brief          Returns the phase reference output
//! \param[in] p    Pointer to the active DCL_REFGEN64 structure
//! \return         The phase B reference output
//!
static inline float64_t DCL_getRefgen64PhaseB(DCL_REFGEN64 *p)
{
    return(p->yb);
}


//! \brief          Returns the phase reference output
//! \param[in] p    Pointer to the active DCL_REFGEN64 structure
//! \return         The phase C reference output
//!
static inline float64_t DCL_getRefgen64PhaseC(DCL_REFGEN64 *p)
{
    return(p->yc);
}

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCL_REFGEN64_H

/* end of file */
