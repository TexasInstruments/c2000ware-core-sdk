/* DCL_NLPID.h - non-linear PID controller
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

#ifndef _C_DCL_NLPID_H
#define _C_DCL_NLPID_H

#ifdef __cplusplus
extern "C" {
#endif

//! \file           DCL_NLPID.h
//! \brief          Contains the public interface to the
//!                 non-linear PID, PI, & NLF controller functions

#include "DCL.h"

//! \brief          Sets the lower bound on the linear region semi-width
//!
#define DCL_DELTA_MIN   1.0e-04f

//! \brief          Sets an upper bound on allowable controller gain, and
//!                 therefore fixes the minimum linear region semi-width
//!
#define DCL_GAMMA_MAX   100


//--- Non-linear PID controllers ---------------------------------------------

#pragma CODE_SECTION(DCL_updateNLPID,"dclfuncs")
#pragma CODE_SECTION(DCL_runNLPID_C1,"dclfuncs")
#pragma CODE_SECTION(DCL_runNLPID_C2,"dclfuncs")
#pragma CODE_SECTION(DCL_runNLF_C1,"dclfuncs")

//! \brief          Defines the shadow DCL_NLPID controller structure
//!
typedef struct dcl_nlpid_sps {
    float32_t Kp;       //!< Linear proportional gain
    float32_t Ki;       //!< Linear integral gain
    float32_t Kd;       //!< Linear derivative gain
    float32_t alpha_p;  //!< P path non-linear exponent
    float32_t alpha_i;  //!< I path non-linear exponent
    float32_t alpha_d;  //!< D path non-linear exponent
    float32_t delta_p;  //!< P path linearized range
    float32_t delta_i;  //!< I path linearized range
    float32_t delta_d;  //!< D path linearized range
    float32_t gamma_p;  //!< P path gain limit
    float32_t gamma_i;  //!< I path gain limit
    float32_t gamma_d;  //!< D path gain limit
    float32_t c1;       //!< D path filter coefficient 1
    float32_t c2;       //!< D path filter coefficient 2
    float32_t Umax;     //!< Upper saturation limit
    float32_t Umin;     //!< Lower saturation limit
} DCL_NLPID_SPS;

//! \brief          Defines default values to initialize the DCL_NLPID structure
//!
#define NLPID_SPS_DEFAULTS { 1.0f, 0.0f, 0.0f, \
                             1.0f, 1.0f, 1.0f, \
                             0.1f, 0.1f, 0.1f, \
                             1.0f, 1.0f, 1.0f, \
                             1.0f, 0.0f, \
                             1.0f, -1.0f }

//! \brief          Defines the active DCL_NLPID controller structure
//!
typedef struct dcl_nlpid {
    float32_t Kp;       //!< Linear proportional gain
    float32_t Ki;       //!< Linear integral gain
    float32_t Kd;       //!< Linear derivative gain
    float32_t alpha_p;  //!< P path non-linear exponent
    float32_t alpha_i;  //!< I path non-linear exponent
    float32_t alpha_d;  //!< D path non-linear exponent
    float32_t delta_p;  //!< P path linearized range
    float32_t delta_i;  //!< I path linearized range
    float32_t delta_d;  //!< D path linearized range
    float32_t gamma_p;  //!< P path gain limit
    float32_t gamma_i;  //!< I path gain limit
    float32_t gamma_d;  //!< D path gain limit
    float32_t c1;       //!< D path filter coefficient 1
    float32_t c2;       //!< D path filter coefficient 2
    float32_t d2;       //!< D path filter intermediate storage 1
    float32_t d3;       //!< D path filter intermediate storage 2
    float32_t i7;       //!< I path intermediate storage
    float32_t i16;      //!< Intermediate saturation storage
    float32_t i18;      //!< Spare
    float32_t Umax;     //!< Upper saturation limit
    float32_t Umin;     //!< Lower saturation limit
    DCL_NLPID_SPS *sps; //!< Pointer to shadow parameter structure
    DCL_CSS *css;       //!< Pointer to controller support structure
} DCL_NLPID;

//! \brief          Defines default values to initialize the DCL_NLPID structure
//!
#define NLPID_DEFAULTS {    1.0f, 0.0f, 0.0f, \
                            1.0f, 1.0f, 1.0f, \
                            0.1f, 0.1f, 0.1f, \
                            1.0f, 1.0f, 1.0f, \
                            1.0f, 0.0f, \
                            0.0f, 0.0f, \
                            0.0f, 1.0f, 0.0f, \
                            1.0f, -1.0f, \
                            NULL_ADDR, NULL_ADDR }

//! \brief          Resets DCL_NLPID internal storage data
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \return         None
//!
static inline void DCL_resetNLPID(DCL_NLPID *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->d2 = p->d3 = p->i7 = 0.0f;
    p->i16 = 1.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Copies control parameters from one DCL_NLPID structure to another
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \return         None
//!
static inline void DCL_updateNLPID(DCL_NLPID *p)
{
    uint16_t v;

#ifdef DCL_ERROR_HANDLING_ENABLED
    float32_t tau = (2.0f - p->sps->c1 * p->css->T) / (2.0f * p->sps->c1);
    float32_t ec2 = p->sps->c1 * (p->css->T - 2.0f * tau) / 2.0f;
    p->css->err |= ((p->sps->c2 < (ec2 - DEFAULT_FPU32_TOL)) || (p->sps->c2 > (ec2 + DEFAULT_FPU32_TOL))) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (p->sps->delta_p < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->delta_i < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->delta_d < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->Umax <= p->sps->Umin) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (p->css->T <= 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= ((p->sps->Kp < 0.0f) || (p->sps->Ki < 0.0f) || (p->sps->Kd < 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    if (p->css->sts == STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->Kp = p->sps->Kp;
        p->Ki = p->sps->Ki;
        p->Kd = p->sps->Kd;
        p->alpha_p = p->sps->alpha_p;
        p->alpha_i = p->sps->alpha_i;
        p->alpha_d = p->sps->alpha_d;
        p->delta_p = p->sps->delta_p;
        p->delta_i = p->sps->delta_i;
        p->delta_d = p->sps->delta_d;
        p->gamma_p = p->sps->gamma_p;
        p->gamma_i = p->sps->gamma_i;
        p->gamma_d = p->sps->gamma_d;
        p->c1 = p->sps->c1;
        p->c2 = p->sps->c2;
        p->Umax = p->sps->Umax;
        p->Umin = p->sps->Umin;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Copies control parameters from one DCL_NLPID structure to another
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \return         None
//!
extern void DCL_fupdateNLPID(DCL_NLPID *p);

//! \brief          Loads the shadow derivative LP filter coefficients
//!                 Note: active coefficients unchanged DCL_updateNLPID() called
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \param[in] fc   The desired filter bandwidth in Hz
//! \return         None
//!
static inline void DCL_setNLPIDfilterBW(DCL_NLPID *p, float32_t fc)
{
    float32_t tau = 1.0f / (2.0f * CONST_PI_32 * fc);

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((fc >= 1.0f / (2.0f * p->css->T)) || (fc <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    p->sps->c1 = 2.0f / (p->css->T + 2.0f * tau);
    p->sps->c2 = (p->css->T - 2.0f * tau) / (p->css->T + 2.0f * tau);
}

//! \brief          Loads the NLPID derivative path filter active coefficients
//!                 Note: new coefficients take effect immediately.  SPS &
//!                 CSS contents are unaffected.
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \param[in] fc   The desired filter bandwidth in Hz
//! \param[in] T    The controller update rate in seconds
//! \return         None
//!
static inline void DCL_setActiveNLPIDfilterBW(DCL_NLPID *p, float32_t fc, float32_t T)
{
    float32_t tau;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((fc >= 1.0f / (2.0f * T)) || (fc <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    tau = 1.0f / (2.0f * CONST_PI_32 * fc);
    p->c1 = 2.0f / (T + 2.0f * tau);
    p->c2 = (T - 2.0f * tau) / (T + 2.0f * tau);
}

//! \brief          Returns the derivative LP filter bandwidth in Hz
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \return         The filter bandwidth in Hz
//!
static inline float32_t DCL_getNLPIDfilterBW(DCL_NLPID *p)
{
    float32_t tau = ((2.0f - p->c1 * p->css->T) / (2.0f * p->c1));
    return(1.0f / (2.0f * CONST_PI_32 * tau));
}

//! \brief          Returns the linearized region gain for specified (alpha,delta)
//! \param[in] alpha    The non-linear gain
//! \param[in] delta    The linear region semi-width
//! \return         The linear region gain
//!
static inline float32_t DCL_getNLPIDgamma(float32_t alpha, float32_t delta)
{
    return((float32_t) powf(delta, (alpha - 1.0f)));
}

//! \brief          Returns the semi-width of the linear gain region for specified (alpha,gamma)
//! \param[in] alpha    The non-linear gain
//! \param[in] gamma    The linear region gain
//! \return         The linear region semi-width
//!
static inline float32_t DCL_getNLPIDdelta(float32_t alpha, float32_t gamma)
{
    return((float32_t) powf(gamma, (1.0f / (alpha - 1.0f))));
}

//! \brief          Computes the linear gain region for specified (alpha, delta)
//!                 Implemented as external assembly module
//! \param[in] alpha    The nonlinear tuning parameter (0.0f <= alpha <= 2.0f)
//! \param[in] delta    The linear region semi-width (0.0f < delta <= 1.0f)
//! \return         The linear region gain (gamma)
//!
extern float32_t DCL_calcGamma(float32_t alpha, float32_t delta);

//! \brief          Computes the linearized gains for each path
//!                 Note: active coefficients not update DCL_updateNLPID() called
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \return         None
//!
static inline void DCL_setNLPIDgamma(DCL_NLPID *p)
{
    float32_t xP = (float32_t) powf(p->sps->delta_p, (p->sps->alpha_p - 1.0f));
    float32_t xI = (float32_t) powf(p->sps->delta_i, (p->sps->alpha_i - 1.0f));
    float32_t xD = (float32_t) powf(p->sps->delta_d, (p->sps->alpha_d - 1.0f));


#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((p->sps->delta_p > 1.0f) || (p->sps->delta_p > 1.0f) || (p->sps->delta_p > 1.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->delta_p < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->delta_i < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->delta_d < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= ((xP > DCL_GAMMA_MAX) || (xI > DCL_GAMMA_MAX) || (xD > DCL_GAMMA_MAX)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    p->sps->gamma_p = xP;
    p->sps->gamma_i = xI;
    p->sps->gamma_d = xD;
}

//! \brief          Computes the linearized gains for each path and loads the
//!                 parameters in the active NLPID structure
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \return         None
//!
static inline void DCL_setActiveNLPIDgamma(DCL_NLPID *p)
{
    float32_t xP = (float32_t) powf(p->delta_p, (p->alpha_p - 1.0f));
    float32_t xI = (float32_t) powf(p->delta_i, (p->alpha_i - 1.0f));
    float32_t xD = (float32_t) powf(p->delta_d, (p->alpha_d - 1.0f));

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((p->delta_p > 1.0f) || (p->delta_p > 1.0f) || (p->delta_p > 1.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->delta_p < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->delta_i < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->delta_d < DCL_DELTA_MIN) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= ((xP > DCL_GAMMA_MAX) || (xI > DCL_GAMMA_MAX) || (xD > DCL_GAMMA_MAX)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    p->gamma_p = xP;
    p->gamma_i = xI;
    p->gamma_d = xD;
}

//! \brief          Executes a parallel form non-linear PID controller on the FPU32
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
static inline float32_t DCL_runNLPID_C1(DCL_NLPID *p, float32_t rk, float32_t yk, float32_t lk)
{
    float32_t v1, v2, v3, v4, v5, v8, v9, v10, v12, v13, v14, v15;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (p->css->sts & STS_CONTROLLER_RUNNING) ? ERR_CONTROLLER : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
    DCL_CONTROLLER_BEGIN(p);
#endif

    // pre-conditioning block
    v1 = (rk - yk) * 0.5f;
    v2 = (v1 < 0.0f) ? -1.0f : 1.0f;
    v3 = fabsf(v1);

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((p->alpha_p >= 2.0f) || (p->alpha_p <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= ((p->alpha_i >= 2.0f) || (p->alpha_i <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= ((p->alpha_d >= 2.0f) || (p->alpha_d <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (v3 > 1.0f) ? ERR_INPUT_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    // non-linear modules
    v4 = ((v3 > p->delta_p) ? (v2 * (float32_t) powf(v3, p->alpha_p)) : (v1 * p->gamma_p));
    v5 = ((v3 > p->delta_i) ? (v2 * (float32_t) powf(v3, p->alpha_i)) : (v1 * p->gamma_i));
    v9 = ((v3 > p->delta_d) ? (v2 * (float32_t) powf(v3, p->alpha_d)) : (v1 * p->gamma_d));

    // integral path
    v8 = (v5 * p->Kp * p->Ki * p->i16) + p->i7;
    p->i7 = v8;

    // derivative path
    v10 = v9 * p->Kd * p->c1;
    v12 = v10 - p->d2 - p->d3;
    p->d2 = v10;
    p->d3 = v12 * p->c2;

    // output sum & clamp
    v13 = (p->Kp * (v4 + v12)) + v8;
#ifndef __TMS320C28XX_CLA__
    v14 = __fsat(v13, p->Umax, p->Umin);
#else
    v14 = (v13 > p->Umax) ? p->Umax : v13;
    v14 = (v14 < p->Umin) ? p->Umin : v14;
#endif
    v15 = (v14 == v13) ? 1.0f : 0.0f;
    p->i16 = v15 * lk;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v4;
#endif

#ifdef DCL_ERROR_HANDLING_ENABLED
    DCL_CONTROLLER_END(p);
#endif

    return(v14);
}

//! \brief          Executes a series form non-linear PID controller on the FPU32
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
static inline float32_t DCL_runNLPID_C2(DCL_NLPID *p, float32_t rk, float32_t yk, float32_t lk)
{
    float32_t v1, v2, vd2, v3, vd3, v4, v5, v6, v8, v9, v12, v15, v16, v17;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (p->css->sts & STS_CONTROLLER_RUNNING) ? ERR_CONTROLLER : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
    DCL_CONTROLLER_BEGIN(p);
#endif

    // pre-conditioning block for P & I
    v1 = (rk - yk) * 0.5f;
    v2 = (v1 < 0.0f) ? -1.0f : 1.0f;
    v3 = fabsf(v1);

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((p->alpha_p >= 2.0f) || (p->alpha_p <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= ((p->alpha_i >= 2.0f) || (p->alpha_i <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (v3 > 1.0f) ? ERR_INPUT_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    // P & I non-linear modules
    v4 = ((v3 > p->delta_p) ? (v2 * (float32_t) powf(v3, p->alpha_p)) : (v1 * p->gamma_p));
    v5 = ((v3 > p->delta_i) ? (v2 * (float32_t) powf(v3, p->alpha_i)) : (v1 * p->gamma_i));

    // D path non-linear block
    vd2 = (yk < 0.0f) ? -1.0f : 1.0f;
    vd3 = fabsf(yk);

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((p->alpha_d >= 2.0f) || (p->alpha_d <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (vd3 > 1.0f) ? ERR_INPUT_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    v6 = ((vd3 > p->delta_d) ? (vd2 * (float32_t) powf(vd3, p->alpha_d)) : (yk * p->gamma_d));

    // integral path
    v8 = (v5 * p->Kp * p->Ki * p->i16) + p->i7;
    p->i7 = v8;

    // derivative path
    v15 = v6 * p->Kd * p->c1;
    v16 = v15 - p->d2 - p->d3;
    p->d2 = v15;
    p->d3 = v16 * p->c2;

    // output sum & clamp
    v9 = (p->Kp * (v4 - v16)) + v8;
#ifndef __TMS320C28XX_CLA__
    v17 = __fsat(v9, p->Umax, p->Umin);
#else
    v17 = (v9 > p->Umax) ? p->Umax : v9;
    v17 = (v17 < p->Umin) ? p->Umin : v17;
#endif
    v12 = (v17 == v9) ? 1.0f : 0.0f;
    p->i16 = v12 * lk;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v1;
#endif

#ifdef DCL_ERROR_HANDLING_ENABLED
    DCL_CONTROLLER_END(p);
#endif

    return(v17);
}

//! \brief          Executes a series form non-linear PID controller on the FPU32
//!                 Note: this prototype covers a future assembly implementation
//! \param[in] p    Pointer to the DCL_NLPID structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
extern float32_t DCL_runNLPID_C3(DCL_NLPID *p, float32_t rk, float32_t yk, float32_t lk);

//--- Basic non-linear function ----------------------------------------------

//! \brief          Executes the non-linear control function on the FPU32
//! \param[in] x    The input variable
//! \param[in] alpha    The non-linear exponent
//! \param[in] delta    The linear region semi-width
//! \return         The non-linear output
//!
static inline float32_t DCL_runNLF_C1(float32_t x, float32_t alpha, float32_t delta)
{
    float32_t v2 = (x < 0.0f) ? -1.0f : 1.0f;
    float32_t v3 = fabsf(x);

    return((v3 > delta) ? (v2 * (float32_t) powf(v3, alpha)) : (x * powf(delta, (alpha - 1.0f))));
}

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCL_NLPID_H

/* end of file */
