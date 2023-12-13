/* DCL_refgen.h - Reference generator module header file
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

#ifndef _C_DCL_REFGEN_H
#define _C_DCL_REFGEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DCL.h"

//! \brief          Region related symbols for function placement
//
#pragma CODE_SECTION(DCL_runRefgen,"dclfuncs")
#pragma CODE_SECTION(DCL_getRefgenPhaseA,"dclfuncs")
#pragma CODE_SECTION(DCL_getRefgenPhaseB,"dclfuncs")
#pragma CODE_SECTION(DCL_getRefgenPhaseC,"dclfuncs")

//! \brief          Defines the minimum normalized increment
//!
#define DCL_REFGEN_MIN_INC      1.0e-06f

//! \brief          Defines the REFGEN operating modes
//!
enum dcl_rgen_modes {
    REFGEN_OFF = 0,
    REFGEN_STATIC,
    REFGEN_SINE,
    REFGEN_SQUARE,
    REFGEN_SAW,
    REFGEN_TRIANGLE,
    REFGEN_PULSE,
    REFGEN_SINE2,
    REFGEN_SINE3
};

//! \brief          Defines the DCL_REFGEN structure
//!
typedef volatile struct dcl_refgen {
    float32_t   rtgt;       //!< Target ramp value
    float32_t   rinc;       //!< Ramp increment
    float32_t   amtgt;      //!< Target amplitude value
    float32_t   aminc;      //!< Amplitude increment
    float32_t   fmtgt;      //!< Frequency ramp value
    float32_t   fminc;      //!< Frequency increment
    float32_t   thinc;      //!< Angular increment
    float32_t   duty;       //!< Pulse duty cycle
    float32_t   umax;       //!< Maximum allowable output
    float32_t   umin;       //!< Minimum allowable output
    float32_t   yr;         //!< Ramp generator output
    float32_t   ampl;       //!< Dynamic amplitude
    float32_t   freq;       //!< Dynamic frequency
    float32_t   theta;      //!< Normalized angle - phase A
    float32_t   thetb;      //!< Normalized angle - phase B
    float32_t   thetc;      //!< Normalized angle - phase C
    float32_t   ya;         //!< Phase A output
    float32_t   yb;         //!< Phase B output
    float32_t   yc;         //!< Phase C output
    int16_t     mode;       //!< Operating mode
    int16_t     spare;      //!< Spare for alignment
    DCL_CSS     *css;       //!< Pointer to the common support structure
} DCL_REFGEN;

//! \brief          Defines default values to initialize the DCL_REFGEN structure
//!
#define DCL_REFGEN_DEFAULTS { 0.0f,  0.0f, \
                              0.0f,  0.0f, \
                              0.0f,  0.0f,  0.0f, \
                              0.0f,  1.0f,  1.0f,  1.0f, -1.0f, \
                              0.0f,  0.0f,  0.0f,  0.0f, \
                              0.0f,  0.0f,  0.0f, \
                              REFGEN_OFF, 0, NULL_ADDR }

//----------------------------------------------------------------------------

//! \brief          Resets DCL_REFGEN dynamic data
//! \param[in] p    Pointer to the DCL_REFGEN structure
//! \return         None
//!
static inline void DCL_resetRefgen(DCL_REFGEN *p)
{
    p->ampl = 0.0f;
    p->freq = 0.0f;
    p->rinc = 0.0f;
    p->theta = 0.0f;
    p->thetb = 0.0f;
    p->thetc = 0.0f;
    p->thinc = 0.0f;
    p->yr = 0.0f;
    p->ya = 0.0f;
    p->yb = 0.0f;
    p->yc = 0.0f;
}


//! \brief          Loads the REFGEN ramp parameters
//!
//! \param[in] p    Pointer to the DCL_REFGEN structure
//! \param[in] tgt  The new static reference target
//! \param[in] tr   The time interval to reach the new target
//! \return         Void
//!
static inline void DCL_setRefgenRamp(DCL_REFGEN *p, float32_t tgt, float32_t tr)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (tr < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
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
    if (!(0.0f == p->rinc) && (fabsf(p->rinc) < DCL_REFGEN_MIN_INC))
    {
#ifdef DCL_ERROR_HANDLING_ENABLED
        p->css->err = ERR_COMPUTATION;
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
#endif
        if (signbit(p->rinc))
        {
            p->rinc = -DCL_REFGEN_MIN_INC;
        }
        else
        {
            p->rinc = DCL_REFGEN_MIN_INC;
        }
    }
}


//! \brief          Loads the REFGEN dynamic amplitude
//!
//! \param[in] p    Pointer to the DCL_REFGEN structure
//! \param[in] ampl The new target amplitude
//! \param[in] tr   The time interval to reach the new target
//! \return         Void
//!
static inline void DCL_setRefgenAmpl(DCL_REFGEN *p, float32_t ampl, float32_t tr)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (tr < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    // compute amplitude increment
    tr = (tr < p->css->T) ? p->css->T : tr;
    p->amtgt = ampl;
    p->aminc = p->css->T * (ampl - p->ampl) / tr;

    // clamp minimum amplitude increment
    if ((p->aminc > 0.0f) && (fabsf(p->aminc) < DCL_REFGEN_MIN_INC))
    {
#ifdef DCL_ERROR_HANDLING_ENABLED
        p->css->err = ERR_COMPUTATION;
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
#endif
        if (signbit(p->aminc))
        {
            p->aminc = -DCL_REFGEN_MIN_INC;
        }
        else
        {
            p->aminc = DCL_REFGEN_MIN_INC;
        }
    }
}


//! \brief          Loads the REFGEN frequency
//!
//! \param[in] p    Pointer to the DCL_REFGEN structure
//! \param[in] freq The new frequency in Hz
//! \param[in] tr   The time interval to reach the new target
//! \return         Void
//!
static inline void DCL_setRefgenFreq(DCL_REFGEN *p, float32_t freq, float32_t tr)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (tr < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    // compute frequency increment
    tr = (tr < p->css->T) ? p->css->T : tr;
    p->fmtgt = freq;
    p->fminc = p->css->T * (freq - p->freq) / tr;

    // clamp minimum frequency increment
    if ((p->fminc > 0.0f) && (fabsf(p->fminc) < DCL_REFGEN_MIN_INC))
    {
#ifdef DCL_ERROR_HANDLING_ENABLED
        p->css->err = ERR_COMPUTATION;
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
#endif
        if (signbit(p->fminc))
        {
            p->fminc = -DCL_REFGEN_MIN_INC;
        }
        else
        {
            p->fminc = DCL_REFGEN_MIN_INC;
        }
    }
}


//! \brief          Loads the REFGEN pulse duty cycle
//! \param[in] p    Pointer to the DCL_REFGEN structure
//! \param[in] duty The new per-unit duty cycle
//! \return         None
//!
static inline void DCL_setRefgenDuty(DCL_REFGEN *p, float32_t duty)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((duty < 0.0f) || (duty > 1.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    p->duty = duty;
}

//! \brief          Loads the REFGEN output clam limits
//! \param[in] p    Pointer to the DCL_REFGEN structure
//! \param[in] max  The upper limit
//! \param[in] min  The lower limit
//! \return         None
//!
static inline void DCL_setRefgenClamp(DCL_REFGEN *p, float32_t max, float32_t min)
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


//! \brief          Sets the REFGEN operating mode
//! \param[in] p    Pointer to the DCL_REFGEN structure
//! \param[in] mode The new operating mode
//! \return         None
//!
static inline void DCL_setRefgenMode(DCL_REFGEN *p, int16_t mode)
{
    p->mode = mode;
}


//! \brief          Runs the REFGEN module
//! \param[in] p    Pointer to the DCL_REFGEN structure
//! \return         None
//!
static inline void DCL_runRefgen(DCL_REFGEN *p)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    float32_t v;
#endif

    // static offset generator
    if (!F32_IS_ZERO(p->rinc))
    {
        if (fabsf(p->rinc) > fabsf(p->rtgt - p->yr))
        {
            p->yr = p->rtgt;
            p->rinc = 0.0f;
            DCL_ADJUSTMENT_COMPLETE(p);
        }
        else
        {
#ifdef DCL_ERROR_HANDLING_ENABLED
            v = p->yr;
#endif
            p->yr += p->rinc;
#ifdef DCL_ERROR_HANDLING_ENABLED
            if (F32_IS_ZERO(v - p->yr))
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
    if (!F32_IS_ZERO(p->aminc))
    {
        if (fabsf(p->aminc) > fabsf(p->amtgt - p->ampl))
        {
            p->ampl = p->amtgt;
            p->aminc = 0.0f;
        }
        else
        {
#ifdef DCL_ERROR_HANDLING_ENABLED
            v = p->ampl;
#endif
            p->ampl += p->aminc;
#ifdef DCL_ERROR_HANDLING_ENABLED
            if (F32_IS_ZERO(v - p->ampl))
            {
                p->css->err = ERR_COMPUTATION;
                DCL_GET_ERROR_LOC(p->css);
                DCL_RUN_ERROR_HANDLER(p->css);
            }
#endif
        }
    }

    // frequency modulator
    if (!F32_IS_ZERO(p->fminc))
    {
        if (fabsf(p->fminc) > fabsf(p->fmtgt - p->freq))
        {
            p->freq = p->fmtgt;
            p->fminc = 0.0f;
        }
        else
        {
#ifdef DCL_ERROR_HANDLING_ENABLED
            v = p->freq;
#endif
            p->freq += p->fminc;
#ifdef DCL_ERROR_HANDLING_ENABLED
            if (F32_IS_ZERO(v - p->freq))
            {
                p->css->err = ERR_COMPUTATION;
                DCL_GET_ERROR_LOC(p->css);
                DCL_RUN_ERROR_HANDLER(p->css);
            }
#endif
        }
    }

    // angle increment
    if (p->freq > 0.0f)
    {
        p->thinc = p->css->T * p->freq;
        if (p->thinc < DCL_REFGEN_MIN_INC)
        {
#ifdef DCL_ERROR_HANDLING_ENABLED
            p->css->err = ERR_COMPUTATION;
            DCL_GET_ERROR_LOC(p->css);
            DCL_RUN_ERROR_HANDLER(p->css);
#endif
            p->thinc = DCL_REFGEN_MIN_INC;
        }
    }
    else
    {
        p->thinc = 0.0f;
    }

    p->theta += p->thinc;
    p->theta -= (p->theta >= 1.0f) ? 1.0f : 0.0f;

    // dynamic signal generator
    switch (p->mode) {

        case REFGEN_STATIC:
            p->ya = 0.0f;
            p->yb = 0.0f;
            p->yc = 0.0f;
            break;

        case REFGEN_SINE:
        #ifdef __TMS320C28XX_TMU__
            p->ya = __sinpuf32(p->theta);
        #else
            p->ya = sinf(CONST_2PI_32 * p->theta);
        #endif
            p->yb = 0.0f;
            p->yc = 0.0f;
            break;

        case REFGEN_SQUARE:
            p->ya = (p->theta > 0.5f) ? 1.0f : 0.0f;
            p->yb = 0.0f;
            p->yc = 0.0f;
            break;

        case REFGEN_SAW:
            p->ya = p->theta;
            p->yb = 0.0f;
            p->yc = 0.0f;
            break;

        case REFGEN_TRIANGLE:
            if (p->theta < 0.5f)
            {
                p->ya = 2.0f * p->theta;
            }
            else
            {
                p->ya = 1.0f - 2.0f * (p->theta - 0.5f);
            }
            p->yb = 0.0f;
            p->yc = 0.0f;
            break;

        case REFGEN_PULSE:
            p->ya = (p->theta > p->duty) ? 0.0f : 1.0f;
            p->yb = 0.0f;
            p->yc = 0.0f;
            break;

        case REFGEN_SINE2:
        #ifdef __TMS320C28XX_TMU__
            p->ya = __sinpuf32(p->theta);
            p->yb = __cospuf32(p->theta);
        #else
            p->ya = sinf(CONST_2PI_32 * p->theta);
            p->yb = cosf(CONST_2PI_32 * p->theta);
        #endif
            p->yc = 0.0f;
            break;

        case REFGEN_SINE3:
            p->thetb = p->theta + 0.3333333333333f;
            p->thetc = p->theta + 0.6666666666667f;
            p->thetb -= (p->thetb >= 1.0f) ? 1.0f : 0.0f;
            p->thetc -= (p->thetc >= 1.0f) ? 1.0f : 0.0f;

         #ifdef __TMS320C28XX_TMU__
             p->ya = __sinpuf32(p->theta);
             p->yb = __sinpuf32(p->thetb);
             p->yc = __sinpuf32(p->thetc);
         #else
             p->ya = sinf(CONST_2PI_32 * p->theta);
             p->yb = sinf(CONST_2PI_32 * p->thetb);
             p->yc = sinf(CONST_2PI_32 * p->thetc);
         #endif
            break;

        case REFGEN_OFF:
        default:
            p->yr = 0.0f;
            p->ya = 0.0f;
            p->yb = 0.0f;
            p->yc = 0.0f;
    }

    // output sum & saturation
    p->ya = __fsat(p->ampl * p->ya + p->yr, p->umax, p->umin);
    p->yb = __fsat(p->ampl * p->yb + p->yr, p->umax, p->umin);
    p->yc = __fsat(p->ampl * p->yc + p->yr, p->umax, p->umin);
}


//! \brief          Returns the phase reference output
//! \param[in] p    Pointer to the active DCL_REFGEN structure
//! \return         The phase A reference output
//!
static inline float32_t DCL_getRefgenPhaseA(DCL_REFGEN *p)
{
    return(p->ya);
}


//! \brief          Returns the phase reference output
//! \param[in] p    Pointer to the active DCL_REFGEN structure
//! \return         The phase B reference output
//!
static inline float32_t DCL_getRefgenPhaseB(DCL_REFGEN *p)
{
    return(p->yb);
}


//! \brief          Returns the phase reference output
//! \param[in] p    Pointer to the active DCL_REFGEN structure
//! \return         The phase C reference output
//!
static inline float32_t DCL_getRefgenPhaseC(DCL_REFGEN *p)
{
    return(p->yc);
}

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCL_REFGEN_H

/* end of file */
