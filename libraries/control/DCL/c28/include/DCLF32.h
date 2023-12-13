/* DCLF32.h - C2000 Digital Control Library
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

#ifndef _C_DCLF32_H
#define _C_DCLF32_H

#ifdef __cplusplus
extern "C" {
#endif

//! \file           DCLF32.h
//! \brief          Contains the public interface to the FPU32
//!                 Digital Controller Library functions

#ifdef __TMS320C28XX__
#include <math.h>
#endif

#include "DCL.h"
#include <complex.h>
#include <stdint.h>


//--- Linear PID controller --------------------------------------------------

#pragma CODE_SECTION(DCL_updatePID,"dclfuncs")
#pragma CODE_SECTION(DCL_runPID_C2,"dclfuncs")
#pragma CODE_SECTION(DCL_runPID_C4,"dclfuncs")

//! \brief          Defines the DCL_PID shadow parameter set
//!
typedef struct dcl_pid_sps {
    float32_t Kp;       //!< Proportional gain
    float32_t Ki;       //!< Integral gain
    float32_t Kd;       //!< Derivative gain
    float32_t Kr;       //!< Set point weight
    float32_t c1;       //!< D path filter coefficient 1
    float32_t c2;       //!< D path filter coefficient 2
    float32_t Umax;     //!< Upper saturation limit
    float32_t Umin;     //!< Lower saturation limit
} DCL_PID_SPS;

//! \brief          Defines default values to initialize the DCL_PID shadow structure
//!
#define PID_SPS_DEFAULTS { 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f }

//! \brief          Defines the DCL_PID active controller structure
//!
typedef struct dcl_pid {
    float32_t Kp;       //!< Proportional gain
    float32_t Ki;       //!< Integral gain
    float32_t Kd;       //!< Derivative gain
    float32_t Kr;       //!< Set point weight
    float32_t c1;       //!< D path filter coefficient 1
    float32_t c2;       //!< D path filter coefficient 2
    float32_t d2;       //!< D path filter intermediate storage 1
    float32_t d3;       //!< D path filter intermediate storage 2
    float32_t i10;      //!< I path intermediate storage
    float32_t i14;      //!< Intermediate saturation storage
    float32_t Umax;     //!< Upper saturation limit
    float32_t Umin;     //!< Lower saturation limit
    DCL_PID_SPS *sps;   //!< Pointer to the shadow parameter set
    DCL_CSS *css;       //!< Pointer to the common support structure
} DCL_PID;

//! \brief          Defines default values to initialize the DCL_PID structure
//!
#define PID_DEFAULTS {  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, \
                        0.0f, 1.0f, 1.0f, -1.0f, \
                        NULL_ADDR, NULL_ADDR }

//! \brief          Resets PID internal storage data
//! \param[in] p    Pointer to the DCL_PID structure
//! \return         None
//!
static inline void DCL_resetPID(DCL_PID *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->d2 = p->d3 = p->i10 = 0.0f;
    p->i14 = 1.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Loads PID tuning parameters
//! \param[in] p    Pointer to the active DCL_PID controller structure
//! \return         None
//!
static inline void DCL_updatePID(DCL_PID *p)
{
    uint16_t v;

#ifdef DCL_ERROR_HANDLING_ENABLED
    float32_t tau = (2.0f - p->sps->c1 * p->css->T) / (2.0f * p->sps->c1);
    float32_t ec2 = p->sps->c1 * (p->css->T - 2.0f * tau) / 2.0f;
    p->css->err |= !F32_IS_VALUE(p->sps->c2, ec2) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (p->sps->Umax <= p->sps->Umin) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (p->css->T <= 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= ((p->sps->Kp < 0.0f) || (p->sps->Ki < 0.0f) || (p->sps->Kd < 0.0f) || (p->sps->Kr < 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->Kp = p->sps->Kp;
        p->Ki = p->sps->Ki;
        p->Kd = p->sps->Kd;
        p->Kr = p->sps->Kr;
        p->c1 = p->sps->c1;
        p->c2 = p->sps->c2;
        p->Umax = p->sps->Umax;
        p->Umin = p->sps->Umin;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads PID tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_PID controller structure
//! \return         None
//!
extern void DCL_fupdatePID(DCL_PID *p);

//! \brief          Loads the derivative path filter shadow coefficients
//!                 Note: new coefficients take effect when DCL_updatePID() is called
//! \param[in] p    Pointer to the DCL_PID structure
//! \param[in] fc   The desired filter bandwidth in Hz
//! \return         None
//!
static inline void DCL_setPIDfilterBW(DCL_PID *p, float32_t fc)
{
    float32_t tau;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((fc >= 1.0f / (2.0f * p->css->T)) || (fc <= 0.0f)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    tau = 1.0f / (2.0f * CONST_PI_32 * fc);
    p->sps->c1 = 2.0f / (p->css->T + 2.0f * tau);
    p->sps->c2 = (p->css->T - 2.0f * tau) / (p->css->T + 2.0f * tau);
}

//! \brief          Loads the PID derivative path filter active coefficients
//!                 Note: new coefficients take effect immediately.  SPS &
//!                 CSS contents are unaffected.
//! \param[in] p    Pointer to the DCL_PID structure
//! \param[in] fc   The desired filter bandwidth in Hz
//! \param[in] T    The controller update rate in seconds
//! \return         None
//!
static inline void DCL_setActivePIDfilterBW(DCL_PID *p, float32_t fc, float32_t T)
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

//! \brief          Returns the active derivative path filter bandwidth in Hz
//! \param[in] p    Pointer to the DCL_PID structure
//! \return         The filter bandwidth in Hz
//!
static inline float32_t DCL_getPIDfilterBW(DCL_PID *p)
{
    float32_t tau = ((2.0f - p->c1 * p->css->T) / (2.0f * p->c1));
    return(1.0f / (2.0f * CONST_PI_32 * tau));
}

//! \brief          Configures a series PID controller in ZPK form
//!                 Note: parameters take effect after call to DCL_updatePID()
//!                 Only z1, z2 & p2 considered.  p1 = 0 assumed.
//! \param[in] p    Pointer to the active DCL_PID controller structure
//! \param[in] q    Pointer to the DCL_ZPK3 structure
//! \return         None
//!
static inline void DCL_loadSeriesPIDasZPK(DCL_PID *p, DCL_ZPK3 *q)
{

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (!F32_IS_VALUE(cimagf(q->z1) + cimagf(q->z2), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (!F32_IS_VALUE(cimagf(q->p2), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (crealf(q->p2) > DCL_C2_LIMIT_32) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (q->K < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t beta1 = -(float32_t) crealf(q->z1 + q->z2);
    float32_t beta0 = (float32_t) crealf(q->z1 * q->z2);
    float32_t alpha1 = -(float32_t) crealf(q->p1 + q->p2);
    float32_t alpha0 = (float32_t) crealf(q->p1 * q->p2);
    float32_t T = p->css->T;
    float32_t a0p = 4.0f + (alpha1 * 2.0f * T) + (alpha0 * T * T);
    float32_t b0 = q->K * (4.0f + (beta1 * 2.0f * T) + (beta0 * T * T)) / a0p;
    float32_t b1 = q->K * (-8.0f + (2.0f * beta0 * T * T)) / a0p;
    float32_t b2 = q->K * (4.0f - (beta1 * 2.0f * T) + (beta0 * T * T)) / a0p;
    float32_t a2 = (4.0f - (alpha1 * 2.0f * T) + (alpha0 * T * T)) / a0p;
    float32_t c2 = -a2;
    float32_t tau = (p->css->T / 2.0f) * (1.0f - c2) / (1.0f + c2);
    p->sps->c1 = 2.0f / (p->css->T + 2.0f*tau);
    p->sps->c2 = c2;
    float32_t det = (c2 + 1.0f);
    det *= det;
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (F32_IS_ZERO(det)) ? ERR_PARAM_INVALID : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif
    float32_t k1 = (c2*b0 - b1 - (2.0f + c2)*b2) / det;
    float32_t k2 = (c2 + 1.0f) * (b0 + b1 + b2) / det;
    float32_t k3 = (c2*c2*b0 - c2*b1 + b2) / det;
    p->sps->Kp = k1;
    p->sps->Ki = k2 / k1;
    p->sps->Kd = k3 / (k1*p->sps->c1);

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = det;
#endif

}

//! \brief          Configures a parallel PID controller in ZPK form
//!                 Note: parameters take effect after call to DCL_updatePID()
//!                 Only z1, z2 & p2 considered.  p1 = 0 assumed.
//! \param[in] p    Pointer to the active DCL_PID controller structure
//! \param[in] q    Pointer to the DCL_ZPK3 structure
//! \return         None
//!
static inline void DCL_loadParallelPIDasZPK(DCL_PID *p, DCL_ZPK3 *q)
{

    #ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (!F32_IS_VALUE(cimagf(q->z1) + cimagf(q->z2), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (!F32_IS_VALUE(cimagf(q->p2), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (crealf(q->p2) > DCL_C2_LIMIT_32) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (q->K < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t beta1 = -(float32_t) crealf(q->z1 + q->z2);
    float32_t beta0 = (float32_t) crealf(q->z1 * q->z2);
    float32_t alpha1 = -(float32_t) crealf(q->p1 + q->p2);
    float32_t alpha0 = (float32_t) crealf(q->p1 * q->p2);
    float32_t T = p->css->T;
    float32_t a0p = 4.0f + (alpha1 * 2.0f * T) + (alpha0 * T * T);
    float32_t b0 = q->K * (4.0f + (beta1 * 2.0f * T) + (beta0 * T * T)) / a0p;
    float32_t b1 = q->K * (-8.0f + (2.0f * beta0 * T * T)) / a0p;
    float32_t b2 = q->K * (4.0f - (beta1 * 2.0f * T) + (beta0 * T * T)) / a0p;
    float32_t a2 = (4.0f - (alpha1 * 2.0f * T) + (alpha0 * T * T)) / a0p;
    float32_t c2 = -a2;
    float32_t tau = (p->css->T / 2.0f) * (1.0f - c2) / (1.0f + c2);
    p->sps->c1 = 2.0f / (p->css->T + 2.0f*tau);
    p->sps->c2 = c2;
    float32_t det = (c2 + 1.0f);
    det *= det;
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (F32_IS_ZERO(det)) ? ERR_PARAM_INVALID : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif
    p->sps->Kp = (c2*b0 - b1 - (2.0f + c2)*b2) / det;
    p->sps->Ki = (c2 + 1.0f) * (b0 + b1 + b2) / det;
    p->sps->Kd = (c2*c2*b0 - c2*b1 + b2) / (det * p->sps->c1);

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = det;
#endif

}

//! \brief          Executes an ideal form PID controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_PID structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
extern float32_t DCL_runPID_C1(DCL_PID *p, float32_t rk, float32_t yk, float32_t lk);

//! \brief          Executes an ideal form PID controller on the FPU32
//! \param[in] p    Pointer to the DCL_PID structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
static inline float32_t DCL_runPID_C2(DCL_PID *p, float32_t rk, float32_t yk, float32_t lk)
{
    float32_t v1, v4, v5, v8, v9, v10, v12;

    v5 = (p->Kr * rk) - yk;
    v8 = ((rk - yk) * p->Ki * p->Kp * p->i14) + p->i10;
    p->i10 = v8;
    v1 = yk * p->Kd * p->c1;
    v4 = v1 - p->d2 - p->d3;
    p->d2 = v1;
    p->d3 = v4 * p->c2;
    v9 = ((v5 - v4) * p->Kp) + v8;
    v10 = (v9 > p->Umax) ? p->Umax : v9;
    v10 = (v10 < p->Umin) ? p->Umin : v10;
    v12 = (v10 == v9) ? 1.0f : 0.0f;
    p->i14 = v12 * lk;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v4;
#endif

    return(v10);
}

//! \brief          Executes an parallel form PID controller on the FPU32
//! \param[in] p    Pointer to the DCL_PID structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
static inline float32_t DCL_runPID_C3(DCL_PID *p, float32_t rk, float32_t yk, float32_t lk)
{
    float32_t v1, v4, v5, v6, v8, v9, v10, v12;

    v5 = rk - yk;
    v6 = v5 * p->Kp;
    v8 = v5 * p->Ki * p->i14 + p->i10;
    p->i10 = v8;
    v1 = v5 * p->Kd * p->c1;
    v4 = v1 - p->d2 - p->d3;
    p->d2 = v1;
    p->d3 = v4 * p->c2;
    v9 = v6 + v8 + v4;
    v10 = (v9 > p->Umax) ? p->Umax : v9;
    v10 = (v10 < p->Umin) ? p->Umin : v10;
    v12 = (v10 == v9) ? 1.0f : 0.0f;
    p->i14 = v12 * lk;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v8;
#endif

    return(v10);
}

//! \brief          Executes a parallel form PID controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_PID structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
extern float32_t DCL_runPID_C4(DCL_PID *p, float32_t rk, float32_t yk, float32_t lk);


//--- Linear PI controller ---------------------------------------------------

#pragma CODE_SECTION(DCL_updatePI,"dclfuncs")
#pragma CODE_SECTION(DCL_runPI_C2,"dclfuncs")
#pragma CODE_SECTION(DCL_runPI_C3,"dclfuncs")
#pragma CODE_SECTION(DCL_runPI_C5,"dclfuncs")
#pragma CODE_SECTION(DCL_runPI_C6,"dclfuncs")

//! \brief          Defines the DCL_PI shadow parameter set
//!
typedef struct dcl_pi_sps {
    float32_t Kp;       //!< Proportional gain
    float32_t Ki;       //!< Integral gain
    float32_t Umax;     //!< Upper control saturation limit
    float32_t Umin;     //!< Lower control saturation limit
    float32_t Imax;     //!< Upper integrator saturation limit
    float32_t Imin;     //!< Lower integrator saturation limit
} DCL_PI_SPS;

//! \brief          Defines default values to initialize the DCL_PI shadow structure
//!
#define PI_SPS_DEFAULTS { 1.0f, 0.0f, 1.0f, -1.0f, 1.0f, -1.0f }

//! \brief          Defines the DCL_PI controller structure
//!
typedef struct dcl_pi {
    float32_t Kp;       //!< Proportional gain
    float32_t Ki;       //!< Integral gain
    float32_t i10;      //!< I storage
    float32_t Umax;     //!< Upper control saturation limit
    float32_t Umin;     //!< Lower control saturation limit
    float32_t i6;       //!< Saturation storage
    float32_t i11;      //!< I storage
    float32_t Imax;     //!< Upper integrator saturation limit
    float32_t Imin;     //!< Lower integrator saturation limit
    DCL_PI_SPS *sps;    //!< Pointer to the shadow parameter set
    DCL_CSS *css;       //!< Pointer to the common support structure
} DCL_PI;

//! \brief  Defines default values to initialize the PI structure
//!
#define PI_DEFAULTS { 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, \
                      NULL_ADDR, NULL_ADDR }

//! \brief          Resets PID internal storage data
//! \param[in] p    Pointer to the DCL_PI structure
//! \return         None
//!
static inline void DCL_resetPI(DCL_PI *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->i10 = 0.0f;
    p->i6 = 1.0f;
    p->i11 = 0.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Loads active PI controller parameters
//! \param[in] p    Pointer to the active DCL_PI controller structure
//! \return         None
//!
static inline void DCL_updatePI(DCL_PI *p)
{
    uint16_t v;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (p->sps->Umax <= p->sps->Umin) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (p->css->T <= 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->Kp < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->Ki < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->Kp = p->sps->Kp;
        p->Ki = p->sps->Ki;
        p->Umax = p->sps->Umax;
        p->Umin = p->sps->Umin;
        p->Imax = p->sps->Imax;
        p->Imin = p->sps->Imin;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads PI tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_PI controller structure
//! \return         None
//!
extern void DCL_fupdatePI(DCL_PI *p);

//! \brief          Configures a series PI controller in "zero-pole-gain" form
//!                 Note: new settings take effect after DCL_updatePI()
//!                 Only z1 considered in DCL_ZPK3, other poles & zeros ignored
//!                 Zero frequency assumed to be in radians/sec.
//! \param[in] p    Pointer to the DCL_PI controller structure
//! \param[in] q    Pointer to the ZPK3 structure
//! \return         None
//!
static inline void DCL_loadSeriesPIasZPK(DCL_PI *p, DCL_ZPK3 *q)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (q->K < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (crealf(q->z1) > (1.0f / (2.0f * p->css->T))) ? ERR_PARAM_WARN : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t z1 = (float32_t) crealf(q->z1);
    float32_t T = p->css->T;
    p->sps->Kp = q->K * (1.0f + T * z1 / 2.0f);
    p->sps->Ki = (-2.0f * T * z1) / (2.0f + T * z1);

}

//! \brief          Configures a parallel PI controller in "zero-pole-gain" form
//!                 Note: new settings take effect after DCL_updatePI()
//!                 Zero frequency assumed to be in radians/sec.
//! \param[in] p    Pointer to the active DCL_PI controller structure
//! \param[in] q    Pointer to the ZPK3 structure
//! \return         None
//!
static inline void DCL_loadParallelPIasZPK(DCL_PI *p, DCL_ZPK3 *q)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (q->K < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (crealf(q->z1) > (1.0f / (2.0f * p->css->T))) ? ERR_PARAM_WARN : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t z1 = (float32_t) crealf(q->z1);
    float32_t T = p->css->T;
    p->sps->Kp = q->K * (1.0f + T * z1 / 2.0f);
    p->sps->Ki = -q->K * T * z1;
}

//! \brief          Executes a series form PI controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_PI structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
extern float32_t DCL_runPI_C1(DCL_PI *p, float32_t rk, float32_t yk);

//! \brief          Executes an inline series form PI controller on the FPU32
//! \param[in] p    Pointer to the DCL_PI structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
static inline float32_t DCL_runPI_C2(DCL_PI *p, float32_t rk, float32_t yk)
{
    float32_t v2, v4, v5, v9;

    v2 = p->Kp * (rk - yk);
    v4 = p->i10 + (p->Ki * p->i6 * v2);
    v5 = v2 + v4;
    v9 = (v5 > p->Umax) ? p->Umax : v5;
    v9 = (v9 < p->Umin) ? p->Umin : v9;
    p->i10 = v4;
    p->i6 = (v5 == v9) ? 1.0f : 0.0f;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v5;
#endif

    return(v9);
}

//! \brief          Executes a parallel form PI controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_PI structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
static inline float32_t DCL_runPI_C3(DCL_PI *p, float32_t rk, float32_t yk)
{
    float32_t v1, v2, v4, v5, v9;

    v1 = rk - yk;
    v2 = p->Kp * v1;
    v4 = (v1 * p->Ki * p->i6) + p->i10;
    p->i10 = v4;
    v5 = v2 + v4;
    v9 = (v5 > p->Umax) ? p->Umax : v5;
    v9 = (v9 < p->Umin) ? p->Umin : v9;
    p->i6 = (v5 == v9) ? 1.0f : 0.0f;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v5;
#endif

    return(v9);
}

//! \brief          Executes a parallel form PI controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_PI structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
extern float32_t DCL_runPI_C4(DCL_PI *p, float32_t rk, float32_t yk);

//! \brief          Executes an parallel form PI controller on the FPU32
//!                 Contains enhanced AWR logic
//! \param[in] p    Pointer to the DCL_PI structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
static inline float32_t DCL_runPI_C5(DCL_PI *p, float32_t rk, float32_t yk)
{
    float32_t v1, v5, v7, v8;
    uint16_t l11, l12, l14, l17, l18, l19;

    v1 = rk - yk;
    v5 = (v1 * p->Ki * p->i6) + p->i10;
    p->i10 = v5;
    v7 = (v1 * p->Kp) + v5;
    v8 = (v7 > p->Umax) ? p->Umax : v7;
    v8 = (v8 < p->Umin) ? p->Umin : v8;
    l17 = ((v7 - v8) == 0) ? 1U : 0U;
    l11 = (v5 >= p->Imax) ? 1U : 0U;
    l12 = (v5 <= p->Imin) ? 1U : 0U;
    l19 = (v5 > 0) ? 1U : 0U;
    l14 = (v1 > 0) ? 1U : 0U;
    l18 = l17 & (!(l11 | l12) | (l19 ^ l14));
    p->i6 = (l18 == 0U) ? 0.0f : 1.0f;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v7;
#endif

    return(v8);
}

//! \brief          Executes a series form PI controller with Tustin integrator
//!                 on the FPU32.
//! \param[in] p    Pointer to the DCL_PI structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
static inline float32_t DCL_runPI_C6(DCL_PI *p, float32_t rk, float32_t yk)
{
    float32_t v2, v4, v5, v8, v9;

    v2 = (rk - yk) * p->Kp;
    v8 = v2 * p->Ki * p->i6;
    v4 = v8 + p->i11 + p->i10;
    v5 = v2 + v4;
    p->i10 = v4;
    p->i11 = v8;
    v9 = (v5 > p->Umax) ? p->Umax : v5;
    v9 = (v9 < p->Umin) ? p->Umin : v9;
    p->i6 = (v5 == v9) ? 1.0f : 0.0f;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v4;
#endif

    return(v9);
}

//! \brief          Executes a series form PI controller with Tustin integrator
//!                 on the FPU32. Implemented as assembly module.
//! \param[in] p    Pointer to the DCL_PI structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
extern float32_t DCL_runPI_C7(DCL_PI *p, float32_t rk, float32_t yk);


//--- Linear PI2 controller --------------------------------------------------

#pragma CODE_SECTION(DCL_updatePI2,"dclfuncs")
#pragma CODE_SECTION(DCL_runPI2_C1,"dclfuncs")

//! \brief          Defines the DCL_PI2 shadow parameter set
//!
typedef struct dcl_pi2_sps {
    float32_t Kp;       //!< Proportional gain
    float32_t Ki;       //!< Integral gain
    float32_t Umax;     //!< Upper saturation limit
    float32_t Umin;     //!< Lower saturation limit
} DCL_PI2_SPS;

#define PI2_SPS_DEFAULTS { 1.0f, 0.0f, 1.0f, -1.0f }

//! \brief          Defines the DCL_PI2 controller structure
//!
typedef struct dcl_pi2 {
    float32_t Kp;       //!< Proportional gain
    float32_t Ki;       //!< Integral gain
    float32_t i6;       //!< Integrator 1 storage
    float32_t i9;       //!< Integrator 2 storage
    float32_t i12;      //!< Saturation 1 storage
    float32_t i13;      //!< Saturation 2 storage
    float32_t Umax;     //!< Upper saturation limit
    float32_t Umin;     //!< Lower saturation limit
    DCL_PI2_SPS *sps;   //!< Pointer to the shadow parameter set
    DCL_CSS *css;       //!< Pointer to the common support structure
} DCL_PI2;

//! \brief  Defines default values to initialize the DCL_PI2 structure
//!
#define PI2_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, \
        NULL_ADDR, NULL_ADDR }

//! \brief          Resets the integrators of the PI2 controller
//! \param[in] p    Pointer to the DCL_PI2 structure
//! \return         None
//!
static inline void DCL_resetPI2(DCL_PI2 *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->i6 = p->i9 = 0.0f;
    p->i12 = p->i13 = 1.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Loads active controller parameters
//! \param[in] p    Pointer to the DCL_PI2 controller structure
//! \return         None
//!
static inline void DCL_updatePI2(DCL_PI2 *p)
{
    uint16_t v;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (p->sps->Umax <= p->sps->Umin) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (p->css->T <= 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->Kp < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (p->sps->Ki < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->Ki = p->sps->Ki;
        p->Kp = p->sps->Kp;
        p->Umax = p->sps->Umax;
        p->Umin = p->sps->Umin;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads PI2 tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_PI2 controller structure
//! \return         None
//!
extern void DCL_fupdatePI2(DCL_PI2 *p);

//! \brief          Executes an inline series form PI2 controller on the FPU32
//! \param[in] p    Pointer to the DCL_PI2 structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback
//! \return         The control effort
//!
static inline float32_t DCL_runPI2_C1(DCL_PI2 *p, float32_t rk, float32_t yk)
{
    float32_t v1, v2, v5, v8, v10, v11, v14;
    uint16_t l1, l2, l3, l4, l5, l6;

    v1 = rk - yk;
    v2 = p->Kp * v1;
    v5 = (v1 * p->Ki * p->i12) + p->i6;
    p->i6 = v5;
    v8 = (v5 * p->i13) + p->i9;
    p->i9 = v8;
    v10 = v2 + v8;
    v11 = (v10 > p->Umax) ? p->Umax : v10;
    v11 = (v11 < p->Umin) ? p->Umin : v11;
    v14 = v10 - v11;
    l1 = (v1 > 0.0f) ? 1U : 0U;
    l2 = (v14 > 0.0f) ? 1U : 0U;
    l3 = (v14 == 0.0f) ? 1U : 0U;
    l4 = (v5 > 0.0f) ? 1U : 0U;
    l5 = l3 | (l1 ^ l2);
    l6 = l3 | (l4 ^ l2);
    p->i12 = (l5 == 1U) ? 1.0f : 0.0f;
    p->i13 = (l6 == 1U) ? 1.0f : 0.0f;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = v8;
#endif

    return(v11);
}


//--- Direct Form 1 - 1st order ----------------------------------------------

#pragma CODE_SECTION(DCL_updateDF11,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF11_C2,"dclfuncs")

//! \brief          Defines the DCL_DF11 shadow parameter set
//!
typedef struct dcl_df11_sps {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t a1;   //!< a1
} DCL_DF11_SPS;

#define DF11_SPS_DEFAULTS { 0.5f, 0.5f, 1.0f }

//! \brief          Defines the DCL_DF11 controller structure
//!
typedef struct dcl_df11 {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t a1;   //!< a1
    float32_t d1;   //!< e(k-1)
    float32_t d2;   //!< u(k-1)
    DCL_DF11_SPS *sps;   //!< Pointer to the shadow parameter set
    DCL_CSS *css;   //!< Pointer to the common support structure
} DCL_DF11;

//! \brief          Defines default values to initialize the DCL_DF11 structure
//!
#define DF11_DEFAULTS { 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, \
                        NULL_ADDR, NULL_ADDR }

//! \brief          Resets the DCL_DF11 controller
//! \param[in] p    Pointer to the DCL_DF11 structure
//! \return         None
//!
static inline void DCL_resetDF11(DCL_DF11 *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->d1 = p->d2 = 0.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Updates active coefficients in the DF11 structure
//! \param[in] p    Pointer to the DCL_DF11 controller structure
//! \return         None
//!
static inline void DCL_updateDF11(DCL_DF11 *p)
{
    uint16_t v;

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->b0 = p->sps->b0;
        p->b1 = p->sps->b1;
        p->a1 = p->sps->a1;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads DF11 tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_DF11 controller structure
//! \return         None
//!
extern void DCL_fupdateDF11(DCL_DF11 *p);

//! \brief          Determines stability of the shadow DF11 compensator
//! \param[in] p    Pointer to the DCL_DF11 controller structure
//! \return         'true' if the pole has magnitude less than 1, 'false' otherwise
//!
static inline bool DCL_isStableDF11(DCL_DF11 *p)
{
    return(DCL_isStablePn1(p->sps->a1));
}

//! \brief          Loads the DF11 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF11()
//!                 Only real z1 & p1 considered: all other roots ignored
//! \param[in] p    Pointer to the DCL_DF11 controller structure
//! \param[in] q    Pointer to the ZPK3 structure
//! \return         None
//!
static inline void DCL_loadDF11asZPK(DCL_DF11 *p, DCL_ZPK3 *q)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= !(F32_IS_VALUE(cimagf(q->z1), 0.0f)) ? ERR_PARAM_WARN : ERR_NONE;
    p->css->err |= !(F32_IS_VALUE(cimagf(q->p1), 0.0f)) ? ERR_PARAM_WARN : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t a0p = 2.0f - (float32_t) crealf(q->p1) * p->css->T;

    p->sps->b0 = q->K * (2.0f - (float32_t) crealf(q->z1) * p->css->T) / a0p;
    p->sps->b1 = q->K * (-2.0f - (float32_t) crealf(q->z1) * p->css->T) / a0p;
    p->sps->a1 = (-2.0f - (float32_t) crealf(q->p1) * p->css->T) / a0p;
}

//! \brief          Loads compensator coefficients to emulate series form PI
//!                 Note: new settings take effect after DCL_updateDF11()
//! \param[in] p    Pointer to the DCL_DF11 controller structure
//! \param[in] Kp   Proportional gain
//! \param[in] Ki   Integral gain
//! \param[in] T    Sampling period in seconds
//! \return         None
//!
static inline void DCL_loadDF11asPI(DCL_DF11 *p, float32_t Kp, float32_t Ki)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (Kp < 0.0f) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (Ki < 0.0f) ? ERR_PARAM_INVALID : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    p->sps->b0 = Kp * (Ki * p->css->T + 2.0f) / 2.0f;
    p->sps->b1 = Kp * (Ki * p->css->T - 2.0f) / 2.0f;
    p->sps->a1 = -1.0f;
}

//! \brief          Executes a 1st order Direct Form 1 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF11 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF11_C1(DCL_DF11 *p, float32_t ek);

//! \brief          Executes a 1st order Direct Form 1 controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF11 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float32_t DCL_runDF11_C2(DCL_DF11 *p, float32_t ek)
{
    p->d2 = (ek * p->b0) + (p->d1 * p->b1) - (p->d2 * p->a1);
    p->d1 = ek;

    return(p->d2);
}


//--- Direct Form 1 - 3rd order ----------------------------------------------

#pragma CODE_SECTION(DCL_updateDF13,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF13_C4,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF13_C5,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF13_C6,"dclfuncs")

//! \brief          Defines the DCL_DF13 shadow parameter set
//!
typedef struct dcl_df13_sps {
    float32_t b0;  //!< b0
    float32_t b1;  //!< b1
    float32_t b2;  //!< b2
    float32_t b3;  //!< b3
    float32_t a0;  //!< a0
    float32_t a1;  //!< a1
    float32_t a2;  //!< a2
    float32_t a3;  //!< a3
} DCL_DF13_SPS;

#define DF13_SPS_DEFAULTS { 0.25f, 0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f, 0.0f }

//! \brief          Defines the DCL_DF13 controller structure
//!
typedef struct dcl_df13 {
    // coefficients
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t b2;   //!< b2
    float32_t b3;   //!< b3
    float32_t a0;   //!< a0
    float32_t a1;   //!< a1
    float32_t a2;   //!< a2
    float32_t a3;   //!< a3

    //data
    float32_t d0;   //!< e(k)
    float32_t d1;   //!< e(k-1)
    float32_t d2;   //!< e(k-2)
    float32_t d3;   //!< e(k-3)
    float32_t d4;   //!< u(k)
    float32_t d5;   //!< u(k-1)
    float32_t d6;   //!< u(k-2)
    float32_t d7;   //!< u(k-3)

    DCL_DF13_SPS *sps;   //!< Pointer to the shadow parameter set
    DCL_CSS *css;   //!< Pointer to the common support structure
} DCL_DF13;

//! \brief          Defines default values to initialize the DCL_DF13 structure
//!
#define DF13_DEFAULTS { 0.25f, 0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 0.0f, 0.0f, \
                        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, \
                        NULL_ADDR, NULL_ADDR }

//! \brief          Resets internal controller data to zero
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \return         None
//!
static inline void DCL_resetDF13(DCL_DF13 *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->d0 = p->d1 = p->d2 = p->d3 = p->d4 = p->d5 = p->d6 = p->d7 = 0.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Copies coefficients from one DF13 structure to another
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \return         None
//!
static inline void DCL_updateDF13(DCL_DF13 *p)
{
    uint16_t v;

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->b0 = p->sps->b0;
        p->b1 = p->sps->b1;
        p->b2 = p->sps->b2;
        p->b3 = p->sps->b3;
        p->a0 = p->sps->a0;
        p->a1 = p->sps->a1;
        p->a2 = p->sps->a2;
        p->a3 = p->sps->a3;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads DF13 tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_DF13 controller structure
//! \return         None
//!
extern void DCL_fupdateDF13(DCL_DF13 *p);

//! \brief          Determines stability of the shadow compensator
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \return         'true' if all poles have magnitude less than 1, 'false' otherwise
//!
static inline bool DCL_isStableDF13(DCL_DF13 *p)
{
    return(DCL_isStablePn3(1.0f, p->sps->a1, p->sps->a2, p->sps->a3));
}

//! \brief          Loads the DF13 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF13()
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \param[in] q    Pointer to the DCL_ZPK3 structure
//! \return         None
//!
static inline void DCL_loadDF13asZPK(DCL_DF13 *p, DCL_ZPK3 *q)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (!F32_IS_VALUE((cimagf(q->z1) + cimagf(q->z2) + cimagf(q->z3)), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (!F32_IS_VALUE((cimagf(q->p1) + cimagf(q->p2) + cimagf(q->p3)), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t beta2 = -(float32_t) crealf(q->z1 + q->z2 + q->z3);
    float32_t beta1 = (float32_t) crealf((q->z1 * q->z2) + (q->z2 * q->z3) + (q->z1 * q->z3));
    float32_t beta0 = -(float32_t) crealf(q->z1 * q->z2 * q->z3);

    float32_t alpha2 = -(float32_t) crealf(q->p1 + q->p2 + q->p3);
    float32_t alpha1 = (float32_t) crealf((q->p1 * q->p2) + (q->p2 * q->p3) + (q->p1 * q->p3));
    float32_t alpha0 = -(float32_t) crealf(q->p1 * q->p2 * q->p3);

    float32_t T = p->css->T;

    float32_t a0p = 8.0f + (alpha2 * 4.0f * T) + (alpha1 * 2.0f * T * T) + (alpha0 * T * T * T);

    p->sps->b0 = q->K * (8.0f + (beta2 * 4.0f * T) + (beta1 * 2.0f * T * T) + (beta0 * T * T * T)) / a0p;
    p->sps->b1 = q->K * (-24.0f - (beta2 * 4.0f * T) + (beta1 * 2.0f * T * T) + (3.0f * beta0 * T * T * T)) / a0p;
    p->sps->b2 = q->K * (24.0f - (beta2 * 4.0f * T) - (beta1 * 2.0f * T * T) + (3.0f * beta0 * T * T * T)) / a0p;
    p->sps->b3 = q->K * (-8.0f + (beta2 * 4.0f * T) - (beta1 * 2.0f * T * T) + (beta0 * T * T * T)) / a0p;

    p->sps->a0 = 1.0f;
    p->sps->a1 = (-24.0f - (alpha2 * 4.0f * T) + (alpha1 * 2.0f * T * T) + (3.0f * alpha0 * T * T * T)) / a0p;
    p->sps->a2 = (24.0f - (alpha2 * 4.0f * T) - (alpha1 * 2.0f * T * T) + (3.0f * alpha0 * T * T * T)) / a0p;
    p->sps->a3 = (-8.0f + (alpha2 * 4.0f * T) - (alpha1 * 2.0f * T * T) + (alpha0 * T * T * T)) / a0p;
}

//! \brief          Executes a full 3rd order Direct Form 1 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF13_C1(DCL_DF13 *p, float32_t ek);

//! \brief          Executes an immediate 3rd order Direct Form 1 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \param[in] ek   The servo error
//! \param[in] vk   The partial pre-computed control effort
//! \return         The control effort
//!
extern float32_t DCL_runDF13_C2(DCL_DF13 *p, float32_t ek, float32_t vk);

//! \brief          Executes a partial pre-computed 3rd order Direct Form 1 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//! \return         The control effort
//!
extern float32_t DCL_runDF13_C3(DCL_DF13 *p, float32_t ek, float32_t uk);

//! \brief          Executes a full 3rd order Direct Form 1 controller on the FPU32
//!                 Implemented as inline C function
//!                 Note: d0 not used
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float32_t DCL_runDF13_C4(DCL_DF13 *p, float32_t ek)
{
    p->d4 = (ek * p->b0) + (p->d1 * p->b1) + (p->d2 * p->b2) + (p->d3 * p->b3) - (p->d5 * p->a1) - (p->d6 * p->a2) - (p->d7 * p->a3);
    p->d3 = p->d2;
    p->d2 = p->d1;
    p->d1 = ek;
    p->d7 = p->d6;
    p->d6 = p->d5;
    p->d5 = p->d4;

    return(p->d4);
}

//! \brief          Executes an immediate 3rd order Direct Form 1 controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \param[in] ek   The servo error
//! \param[in] vk   The partial pre-computed control effort
//! \return         The control effort
//!
static inline float32_t DCL_runDF13_C5(DCL_DF13 *p, float32_t ek, float32_t vk)
{
    p->d4 = (ek * p->b0) + vk;

    return(p->d4);
}

//! \brief          Executes a partial pre-computed 3rd order Direct Form 1 controller on the FPU32
//!                 Implemented as inline C function
//!                 Note: d0 not used
//! \param[in] p    Pointer to the DCL_DF13 controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//! \return         The control effort
//!
static inline float32_t DCL_runDF13_C6(DCL_DF13 *p, float32_t ek, float32_t uk)
{
    float32_t v9;

    v9 = (ek * p->b1) + (p->d1 * p->b2) + (p->d2 * p->b3) - (uk * p->a1) - (p->d5 * p->a2) - (p->d6 * p->a3);
    p->d2 = p->d1;
    p->d1 = ek;
    p->d6 = p->d5;
    p->d5 = uk;

    return(v9);
}


//--- Direct Form 2 - 2nd order ----------------------------------------------

#pragma CODE_SECTION(DCL_updateDF22,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF22_C4,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF22_C5,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF22_C6,"dclfuncs")

//! \brief          Defines the DCL_DF22 shadow parameter set
//!
typedef struct dcl_df22_sps {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t b2;   //!< b2
    float32_t a1;   //!< a1
    float32_t a2;   //!< a2
} DCL_DF22_SPS;

#define DF22_SPS_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f }

//! \brief          Defines the DCL_DF22 controller structure
//!
typedef struct dcl_df22 {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t b2;   //!< b2
    float32_t a1;   //!< a1
    float32_t a2;   //!< a2
    float32_t x1;   //!< x1
    float32_t x2;   //!< x2
    DCL_DF22_SPS *sps;  //!< Pointer to the shadow parameter set
    DCL_CSS *css;   //!< Pointer to the common support structure
} DCL_DF22;

//! \brief          Defines default values to initialize the DCL_DF22 structure
//!
#define DF22_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, \
                        NULL_ADDR, NULL_ADDR }

//! \brief          Resets internal DF22 controller data to zero
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \return         None
//!
static inline void DCL_resetDF22(DCL_DF22 *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->x1 = p->x2 = 0.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Updates active coefficients from shadow set
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \return         None
//!
static inline void DCL_updateDF22(DCL_DF22 *p)
{
    uint16_t v;

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->b0 = p->sps->b0;
        p->b1 = p->sps->b1;
        p->b2 = p->sps->b2;
        p->a1 = p->sps->a1;
        p->a2 = p->sps->a2;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads DF22 tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_DF22 controller structure
//! \return         None
//!
extern void DCL_fupdateDF22(DCL_DF22 *p);

//! \brief          Determines stability of the shadow compensator
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \return         'true' if both poles have magnitude less than 1, 'false' otherwise
//!
static inline bool DCL_isStableDF22(DCL_DF22 *p)
{
    return(DCL_isStablePn2(1.0f, p->sps->a1, p->sps->a2));
}

//! \brief          Loads the DF22 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF22()
//!                 Only z1, z2, p1 & p2 considered: z3 & p3 ignored
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] q    Pointer to the DCL_ZPK3 structure
//! \return         None
//!
static inline void DCL_loadDF22asZPK(DCL_DF22 *p, DCL_ZPK3 *q)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (!F32_IS_VALUE((cimagf(q->z1) + cimagf(q->z2)), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (!F32_IS_VALUE((cimagf(q->p1) + cimagf(q->p2)), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t beta1 = -(float32_t) crealf(q->z1 + q->z2);
    float32_t beta0 = (float32_t) crealf(q->z1 * q->z2);
    float32_t alpha1 = -(float32_t) crealf(q->p1 + q->p2);
    float32_t alpha0 = (float32_t) crealf(q->p1 * q->p2);

    float32_t T = p->css->T;
    float32_t a0p = 4.0f + (alpha1 * 2.0f * T) + (alpha0 * T * T);

    p->sps->b0 = q->K * (4.0f + (beta1 * 2.0f * T) + (beta0 * T * T)) / a0p;
    p->sps->b1 = q->K * (-8.0f + (2.0f * beta0 * T * T)) / a0p;
    p->sps->b2 = q->K * (4.0f - (beta1 * 2.0f * T) + (beta0 * T * T)) / a0p;
    p->sps->a1 = (-8.0f + (2.0f * alpha0 * T * T)) / a0p;
    p->sps->a2 = (4.0f - (alpha1 * 2.0f * T) + (alpha0 * T * T)) / a0p;
}

//! \brief          Loads the DF22 shadow coefficients from damping ratio and un-damped
//!                 natural frequency using sample rate in CSS.
//!                 Note: new settings take effect after DCL_updateDF22()
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] z    The damping ratio
//! \param[in] wn   The un-damped natural frequency in rad/s
//! \return         None
//!
static inline void DCL_loadDF22asZwn(DCL_DF22 *p, float32_t z, float32_t wn)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (z < 0.0f) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (wn < 0.0f) ? ERR_PARAM_INVALID : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t T = p->css->T;
    float32_t v1 = wn*wn*T*T;
    float32_t a2p = 1.0f / (4.0f + 4.0f*z*wn*T + v1);
    p->sps->b0 = v1 * a2p;
    p->sps->b1 = 2.0f * p->sps->b0;
    p->sps->b2 = p->sps->b0;
    p->sps->a1 = (2.0f*v1 - 8.0f) * a2p;
    p->sps->a2 = (4.0f - 4.0f*z*wn*T + v1) * a2p;
}

//! \brief          Loads the shadow DF22 compensator coefficients to emulate a parallel form PID
//!                 Note: new settings take effect after DCL_updateDF22()
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] Kp   Proportional gain
//! \param[in] Ki   Integral gain
//! \param[in] Kd   Derivative gain
//! \param[in] fc   Derivative path filter bandwidth in Hz
//! \return         None
//!
static inline void DCL_loadDF22asParallelPID(DCL_DF22 *p, float32_t Kp, float32_t Ki, float32_t Kd, float32_t fc)
{
    float32_t   Kdp, tau, c1, c2;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (Kp < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (Ki < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (Kd < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (fc < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (fc > (1.0f / (2.0f * p->css->T))) ? ERR_PARAM_WARN : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    tau = 1.0f / (2.0f * CONST_PI_32 * fc);
    c1 = 2.0f / (p->css->T + 2.0f*tau);
    c2 = c1 * (p->css->T - 2.0f*tau) / 2.0f;
    Kdp = Kd * c1;
    p->sps->b0 = Kp + Ki + Kdp;
    p->sps->b1 = Kp*(c2 - 1) + Ki*c2 - 2.0f*Kdp;
    p->sps->b2 = -c2*Kp + Kdp;
    p->sps->a1 = c2 - 1;
    p->sps->a2 = -c2;
}

//! \brief          Loads the shadow DF22 compensator coefficients to emulate a series form PID
//!                 Note: new settings take effect after DCL_updateDF22()
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] Kp   Proportional gain
//! \param[in] Ki   Integral gain
//! \param[in] Kd   Derivative gain
//! \param[in] fc   Derivative path filter bandwidth in Hz
//! \return         None
//!
static inline void DCL_loadDF22asSeriesPID(DCL_DF22 *p, float32_t Kp, float32_t Ki, float32_t Kd, float32_t fc)
{
    float32_t   Kdp, tau, c1, c2;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (Kp < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (Ki < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= (Kd < 0.0f) ? ERR_PARAM_RANGE : ERR_NONE;
    p->css->err |= ((fc < 0.0f) || (fc > (1.0f / (2.0f * p->css->T)))) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    tau = 1 / (2.0f * CONST_PI_32 * fc);
    c1 = 2.0f / (p->css->T + 2.0f*tau);
    c2 = c1 * (p->css->T - 2.0f*tau) / 2.0f;
    Kdp = Kd * c1;
    p->sps->b0 = Kp * (1 + Ki + Kdp);
    p->sps->b1 = Kp * (c2 - 1 + Ki*c2 - 2*Kdp);
    p->sps->b2 = Kp * (-c2 + Kdp);
    p->sps->a1 = c2 - 1;
    p->sps->a2 = -c2;
}

//! \brief          Executes a full 2nd order Direct Form 2 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF22_C1(DCL_DF22 *p, float32_t ek);

//! \brief          Executes an immediate 2nd order Direct Form 2 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF22_C2(DCL_DF22 *p, float32_t ek);

//! \brief          Executes a partial pre-computed 2nd order Direct Form 2 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//!
extern void DCL_runDF22_C3(DCL_DF22 *p, float32_t ek, float32_t uk);

//! \brief          Executes a full 2nd order Direct Form 2 controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float32_t DCL_runDF22_C4(DCL_DF22 *p, float32_t ek)
{
    float32_t v7;

    v7 = (ek * p->b0) + p->x1;
    p->x1 = (ek * p->b1) + p->x2 - (v7 * p->a1);
    p->x2 = (ek * p->b2) - (v7 * p->a2);

    return(v7);
}

//! \brief          Executes an immediate 2nd order Direct Form 2 controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float32_t DCL_runDF22_C5(DCL_DF22 *p, float32_t ek)
{
    return((ek * p->b0) + p->x1);
}

//! \brief          Executes a partial pre-computed 2nd order Direct Form 2 controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF22 controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//!
static inline void DCL_runDF22_C6(DCL_DF22 *p, float32_t ek, float32_t uk)
{
    p->x1 = (ek * p->b1) + p->x2 - (uk * p->a1);
    p->x2 = (ek * p->b2) - (uk * p->a2);
}


//--- Direct Form 2 - 3rd order ----------------------------------------------

#pragma CODE_SECTION(DCL_updateDF23,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF23_C4,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF23_C5,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF23_C6,"dclfuncs")

//! \brief          Defines the DCL_DF23 shadow parameter set
//!
typedef struct dcl_df23_sps {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t b2;   //!< b2
    float32_t b3;   //!< b3
    float32_t a1;   //!< a1
    float32_t a2;   //!< a2
    float32_t a3;   //!< a3
} DCL_DF23_SPS;

#define DF23_SPS_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }

//! \brief          Defines the DCL_DF23 controller structure
//!
typedef struct dcl_df23 {
    // coefficients
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t b2;   //!< b2
    float32_t b3;   //!< b3
    float32_t a1;   //!< a1
    float32_t a2;   //!< a2
    float32_t a3;   //!< a3

    // data
    float32_t x1;   //!< x1
    float32_t x2;   //!< x2
    float32_t x3;   //!< x3

    DCL_DF23_SPS *sps; //!< Pointer to the shadow parameter set
    DCL_CSS *css;   //!< Pointer to the common support structure
} DCL_DF23;

//! \brief          Defines default values to initialize the DCL_DF23 structure
//!
#define DF23_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, \
                        0.0f, 0.0f, 0.0f, NULL_ADDR, NULL_ADDR }

//! \brief          Resets internal DF23 controller data to zero
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \return         None
//!
static inline void DCL_resetDF23(DCL_DF23 *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->x1 = p->x2 = p->x3 = 0.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Copies coefficients from one DF23 structure to another
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \return         None
//!
static inline void DCL_updateDF23(DCL_DF23 *p)
{
    uint16_t v;

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->b0 = p->sps->b0;
        p->b1 = p->sps->b1;
        p->b2 = p->sps->b2;
        p->b3 = p->sps->b3;
        p->a1 = p->sps->a1;
        p->a2 = p->sps->a2;
        p->a3 = p->sps->a3;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads DF23 tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_DF23 controller structure
//! \return         None
//!
extern void DCL_fupdateDF23(DCL_DF23 *p);

//! \brief          Determines stability of the shadow compensator
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \return         'true' if all poles have magnitude less than 1, 'false' otherwise
//!
static inline bool DCL_isStableDF23(DCL_DF23 *p)
{
    return(DCL_isStablePn3(1.0f, p->sps->a1, p->sps->a2, p->sps->a3));
}

//! \brief          Loads the DF23 shadow coefficients from a ZPK3 description
//!                 Note: new settings take effect after DCL_updateDF23()
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \param[in] q    Pointer to the DCL_ZPK3 structure
//! \return         None
//!
static inline void DCL_loadDF23asZPK(DCL_DF23 *p, DCL_ZPK3 *q)
{
#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (!F32_IS_VALUE((cimagf(q->z1) + cimagf(q->z2) + cimagf(q->z3)), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    p->css->err |= (!F32_IS_VALUE((cimagf(q->p1) + cimagf(q->p2) + cimagf(q->p3)), 0.0f)) ? ERR_PARAM_INVALID : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    float32_t beta2 = -(float32_t) crealf(q->z1 + q->z2 + q->z3);
    float32_t beta1 = (float32_t) crealf((q->z1 * q->z2) + (q->z2 * q->z3) + (q->z1 * q->z3));
    float32_t beta0 = -(float32_t) crealf(q->z1 * q->z2 * q->z3);

    float32_t alpha2 = -(float32_t) crealf(q->p1 + q->p2 + q->p3);
    float32_t alpha1 = (float32_t) crealf((q->p1 * q->p2) + (q->p2 * q->p3) + (q->p1 * q->p3));
    float32_t alpha0 = -(float32_t) crealf(q->p1 * q->p2 * q->p3);

    float32_t T = p->css->T;
    float32_t a0p = 8.0f + (alpha2 * 4.0f * T) + (alpha1 * 2.0f * T * T) + (alpha0 * T * T * T);

    p->sps->b0 = q->K * (8.0f + (beta2 * 4.0f * T) + (beta1 * 2.0f * T * T) + (beta0 * T * T * T)) / a0p;
    p->sps->b1 = q->K * (-24.0f - (beta2 * 4.0f * T) + (beta1 * 2.0f * T * T) + (3.0f * beta0 * T * T * T)) / a0p;
    p->sps->b2 = q->K * (24.0f - (beta2 * 4.0f * T) - (beta1 * 2.0f * T * T) + (3.0f * beta0 * T * T * T)) / a0p;
    p->sps->b3 = q->K * (-8.0f + (beta2 * 4.0f * T) - (beta1 * 2.0f * T * T) + (beta0 * T * T * T)) / a0p;

    p->sps->a1 = (-24.0f - (alpha2 * 4.0f * T) + (alpha1 * 2.0f * T * T) + (3.0f * alpha0 * T * T * T)) / a0p;
    p->sps->a2 = (24.0f - (alpha2 * 4.0f * T) - (alpha1 * 2.0f * T * T) + (3.0f * alpha0 * T * T * T)) / a0p;
    p->sps->a3 = (-8.0f + (alpha2 * 4.0f * T) - (alpha1 * 2.0f * T * T) + (alpha0 * T * T * T)) / a0p;
}

//! \brief          Executes a full 3rd order Direct Form 2 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF23_C1(DCL_DF23 *p, float32_t ek);

//! \brief          Executes an immediate 3rd order Direct Form 2 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF23_C2(DCL_DF23 *p, float32_t ek);

//! \brief          Executes a partial pre-computed 3rd order Direct Form 2 controller on the FPU32
//!                 Implemented as an external assembly module
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//!
extern void DCL_runDF23_C3(DCL_DF23 *p, float32_t ek, float32_t uk);

//! \brief          Executes a full 3rd order Direct Form 2 controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float32_t DCL_runDF23_C4(DCL_DF23 *p, float32_t ek)
{
    float32_t v7;

    v7 = (ek * p->b0) + p->x1;
    p->x1 = (ek * p->b1) + p->x2 - (v7 * p->a1);
    p->x2 = (ek * p->b2) + p->x3 - (v7 * p->a2);
    p->x3 = (ek * p->b3) - (v7 * p->a3);

    return(v7);
}

//! \brief          Executes an immediate 3rd order Direct Form 2 controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float32_t DCL_runDF23_C5(DCL_DF23 *p, float32_t ek)
{
    return((ek * p->b0) + p->x1);
}

//! \brief          Executes a partial pre-computed 3rd order Direct Form 2 controller on the FPU32
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF23 controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//!
static inline void DCL_runDF23_C6(DCL_DF23 *p, float32_t ek, float32_t uk)
{
    p->x1 = (ek * p->b1) + p->x2 - (uk * p->a1);
    p->x2 = (ek * p->b2) + p->x3 - (uk * p->a2);
    p->x3 = (ek * p->b3) - (uk * p->a3);
}


//--- Direct Form 2 - clamp --------------------------------------------------

//! \brief          Saturates a control variable and returns 1 if either limit is exceeded.
//!                 Implemented as an external assembly module.
//!
//! \details        Can be used to saturate a pre-computed Direct Form 2 controller.
//!                 If the immediate result is in range it can be used, otherwise
//!                 it can be clamped and the next partial pre-computation skipped.
//!                 An example of use with a pre-computed DF22 controller follows:
//!
//! \code
//! uk = DCL_runDF22_C2(&arma2, rk);                // immediate result from pre-computed controller
//! i = DCL_runClamp_C1(&uk, 1.0f, -1.0f);          // clamp immediate result to +/-1.0
//! // ...use uk here...
//! if (0 == i)                                     // if immediate result is in range...
//! {
//!     DCL_runDF22_C3(&arma2, rk, uk);             // ...pre-compute the next partial result
//! }
//! \endcode
//!
//! \param[in] data The address of the data variable
//! \param[in] Umax The upper limit
//! \param[in] Umin The lower limit
//! \return         Returns 0 if (Umin < data < Umax), else 1
//!
extern int16_t DCL_runClamp_C1(float32_t *data, float32_t Umax, float32_t Umin);

//! \brief          Saturates a control variable and returns 1 if either limit is exceeded
//! \param[in] data The address of the data variable
//! \param[in] Umax The upper limit
//! \param[in] Umin The lower limit
//! \return         Returns 0 if (Umin < data < Umax), else 1
//!
static inline int16_t DCL_runClamp_C2(float32_t *data, float32_t Umax, float32_t Umin)
{
    float32_t iv = *(data);

    *(data) = (*(data) > Umax) ? Umax : *(data);
    *(data) = (*(data) < Umin) ? Umin : *(data);

    return(((iv < Umax) && (iv > Umin)) ? 0 : 1);
}

//--- Gain Scheduler Module --------------------------------------------------

#pragma CODE_SECTION(DCL_updateGSM,"dclfuncs")
#pragma CODE_SECTION(DCL_runGSM_C1,"dclfuncs")

//! \brief          Number of piecewise linear sections
//!
#define GSM_N   8

//! \brief          Defines the shadow DCL_GSM structure
//!
typedef struct dcl_gsm_sps {
    float32_t   m[GSM_N];       //!< sector gain array
    float32_t   c[GSM_N+1];     //!< sector offset array
} DCL_GSM_SPS;

#define GSM_SPS_DEFAULTS { { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, \
        { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f } }

//! \brief          Defines the DCL_GSM structure
//!                 Consists of gains and offsets for each linear section
//!
typedef struct dcl_gsm {
    float32_t   m[GSM_N];       //!< sector gain array
    float32_t   c[GSM_N+1];     //!< sector offset array
    float32_t   h;              //!< interval size
    DCL_GSM_SPS *sps;           //!< Pointer to the shadow parameter set
    DCL_CSS *css;               //!< Pointer to the common support structure
} DCL_GSM;

//! \brief          Defines default values for the GSM structure (GSM_N=8)
//!
#define GSM_DEFAULTS { { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }, \
                       { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f }, \
                         1.0f/GSM_N, NULL_ADDR, NULL_ADDR }

//! \brief          Resets the active GSM parameters to unity gain
//!                 SPS is unaffected
//! \param[in] p    Pointer to the active DCL_GSM controller structure
//! \return         None
//!
static inline void DCL_resetGSM(DCL_GSM *p)
{
    uint16_t j, v;

    v = DCL_DISABLE_INTS;
    for (j=0; j<GSM_N; j++)
    {
        p->m[j] = 1.0f;
        p->c[j] = (float32_t) j * p->h;
    }
    p->c[GSM_N] = 1.0f;
    DCL_RESTORE_INTS(v);
}

//! \brief          Loads the active GSM parameters
//! \param[in] p    Pointer to the active DCL_GSM controller structure
//! \return         None
//!
static inline void DCL_updateGSM(DCL_GSM *p)
{
    uint16_t j, v;

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        for (j=0; j<GSM_N; j++)
        {
            p->m[j] = p->sps->m[j];
            p->c[j] = p->sps->c[j];
        }
        p->c[GSM_N] = p->sps->c[GSM_N];
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads GSM tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_GSM controller structure
//! \return         None
//!
extern void DCL_fupdateGSM(DCL_GSM *p);

//! \brief          Computes the shadow scheduler gains from the offset selection
//!                 Active gains are unaffected until DCL_updateGSM() is called
//! \param[in] p    Pointer to DCL_GSM structure
//! \return         None
//!
static inline void DCL_loadGSMgains(DCL_GSM *p)
{
    int16_t j;

    for (j=0; j<GSM_N; j++)
    {
        p->sps->m[j] = (p->sps->c[j+1] - p->sps->c[j]) * (float32_t) GSM_N;
    }
}

//! \brief          Computes the shadow scheduler offsets from the gain selection
//!                 Active offsets are unaffected until DCL_updateGSM() is called
//! \param[in] p    Pointer to DCL_GSM structure
//! \return         None
//!
static inline void DCL_loadGSMoffsets(DCL_GSM *p)
{
    int16_t j;

    for (j=0; j<=GSM_N; j++)
    {
        p->sps->c[j] = p->sps->c[j-1] + (p->sps->m[j-1] * p->h);
    }
    p->sps->c[0] = 0.0f;
}

//! \brief          Runs the Gain Scheduler Module
//! \param[in] p    Pointer to DCL_GSM structure
//! \param[in] x    Input
//! \return         Control effort
//!
static inline float32_t DCL_runGSM_C1(DCL_GSM *p, float32_t x)
{
    int16_t sector;
    float32_t sgnx, modx, rval;

    sgnx = (x >= 0.0f) ? 1.0f : -1.0f;
    modx = fabsf(x);

    if (modx >= 1.0f)
    {
        rval = p->c[GSM_N] * sgnx;
    }
    else
    {
        sector = (int16_t) (modx * (float32_t) GSM_N);
        rval = (p->m[sector] * (modx - (sector * p->h)) + p->c[sector]) * sgnx;
    }

    return(rval);
}

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCLF32_H

/* end of file */
