/* DCLF64.h - Digital Control Library (64-bit floating point)
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

#ifndef _C_DCLF64_H
#define _C_DCLF64_H

#ifdef __cplusplus
extern "C" {
#endif

//! \file   		DCLF64.h
//! \brief  		Contains the public interface to the
//!         		64-bit PID controller functions

#include "DCL.h"

//--- PIDF64 controller -----------------------------------------------

#pragma CODE_SECTION(DCL_updatePIDF64,"dclfuncs")
#pragma CODE_SECTION(DCL_runPIDF64_S1,"dclfuncs")

//! \brief          Defines the shadow PIDF64 controller structure
//!
typedef struct dcl_pidf64_sps {
    float64_t Kp;       //!< Proportional gain
    float64_t Ki;       //!< Integral gain
    float64_t Kd;       //!< Derivative gain
    float64_t Kr;       //!< Set point weight
    float64_t c1;       //!< D-term filter coefficient 1
    float64_t c2;       //!< D-term filter coefficient 2
    float64_t Umax;     //!< Upper saturation limit
    float64_t Umin;     //!< Lower saturation limit
} DCL_PIDF64_SPS;

//! \brief          Defines default values to initialize the DCL_PIDF64 shadow structure
//!
#define PIDF64_SPS_DEFAULTS { 1.0L, 0.0L, 0.0L, 1.0L, 1.0L, 0.0L, 1.0L, -1.0L }

//! \brief          Defines the active PIDF64 controller structure
//!
typedef struct dcl_pidf64 {
    // active parameters
    float64_t Kp;       //!< Proportional gain
    float64_t Ki;       //!< Integral gain
    float64_t Kd;       //!< Derivative gain
    float64_t Kr;       //!< Set point weight
    float64_t c1;       //!< D-term filter coefficient 1
    float64_t c2;       //!< D-term filter coefficient 2
    float64_t d2;       //!< D-term filter intermediate storage 1
    float64_t d3;       //!< D-term filter intermediate storage 2
    float64_t i10;      //!< I-term intermediate storage
    float64_t i14;      //!< Intermediate saturation storage
    float64_t i16;      //!< Spare
    float64_t Umax;     //!< Upper saturation limit
    float64_t Umin;     //!< Lower saturation limit
    DCL_PIDF64_SPS *sps;  //!< Pointer to shadow parameter set
    DCL_CSS *css;       //!< Pointer to common support structure
} DCL_PIDF64;

//! \brief          Defines default values to initialize the DCL_PIDF64 active structure
//!
#define PIDF64_DEFAULTS {  1.0L, 0.0L, 0.0L, 1.0L, 1.0L, 0.0L, 0.0L, 0.0L, \
                           0.0L, 1.0L, 0.0L, 1.0L, -1.0L, NULL_ADDR, NULL_ADDR }

//! \brief          Resets the PIDF64 internal storage data
//! \param[in] p    Pointer to the DCL_PIDF64 structure
//! \return         None
//!
static inline void DCL_resetPIDF64(DCL_PIDF64 *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->d2 = p->d3 = p->i10 = 0.0L;
    p->i14 = 1.0L;
    DCL_RESTORE_INTS(v);
}

//! \brief          Copies shadow controller parameters to the active
//!                 DCL_PIDF64 structure while global interrupts disabled
//! \param[in] p    Pointer to the DCL_PIDF64 controller structure
//! \return         None
//!
static inline void DCL_updatePIDF64(DCL_PIDF64 *p)
{
    uint16_t v;

    if (p->css->sts == STS_UPDATE_PENDING)
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

//! \brief          Loads the derivative path filter shadow coefficients
//!                 Note: changes will not become effective until update called
//! \param[in] p    Pointer to the DCL_PIDF64 structure
//! \param[in] fc   The desired filter bandwidth in Hz
//! \param[in] T    The sample period in seconds
//! \return         None
//!
static inline void DCL_setPIDF64filterBW(DCL_PIDF64 *p, float64_t fc)
{
    float64_t tau;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((fc >= 1.0L / (2.0L * p->css->T)) || (fc <= 0.0L)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    tau = 1.0L / (2.0L * CONST_PI_64 * fc);
    p->sps->c1 = 2.0L / (p->css->T + 2.0L * tau);
    p->sps->c2 = (p->css->T - 2.0L * tau) / (p->css->T + 2.0L * tau);
}

//! \brief          Loads the PIDF64 derivative path filter active coefficients
//!                 Note: new coefficients take effect immediately.  SPS &
//!                 CSS contents are unaffected.
//! \param[in] p    Pointer to the DCL_PIDF64 structure
//! \param[in] fc   The desired filter bandwidth in Hz
//! \param[in] T    The controller update rate in seconds
//! \return         None
//!
static inline void DCL_setActivePIDF64filterBW(DCL_PIDF64 *p, float64_t fc, float64_t T)
{
    float64_t tau;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= ((fc >= 1.0L / (2.0L * T)) || (fc <= 0.0L)) ? ERR_PARAM_RANGE : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
#endif

    tau = 1.0L / (2.0L * CONST_PI_64 * fc);
    p->c1 = 2.0L / (T + 2.0L * tau);
    p->c2 = (T - 2.0L * tau) / (T + 2.0L * tau);
}

//! \brief          Returns the active derivative path filter bandwidth in Hz
//! \param[in] p    Pointer to the DCL_PIDF64 structure
//! \return         The filter bandwidth in Hz
//!
static inline float64_t DCL_getPIDF64filterBW(DCL_PIDF64 *p)
{
    float64_t tau;

    tau = ((2.0L - p->c1 * p->css->T) / (2.0L * p->c1));
    return(1.0L / (2.0L * CONST_PI_64 * tau));
}

//! \brief          Executes an inline series form PIDF64 controller
//! \param[in] p    Pointer to the DCL_PIDF64 structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
static inline float64_t DCL_runPIDF64_S1(DCL_PIDF64 *p, float64_t rk, float64_t yk, float64_t lk)
{
    float64_t v1, v4, v5, v8, v9, v10, v12;

#ifdef DCL_ERROR_HANDLING_ENABLED
    p->css->err |= (p->css->sts & STS_CONTROLLER_RUNNING) ? ERR_CONTROLLER : ERR_NONE;
    if (p->css->err)
    {
        DCL_GET_ERROR_LOC(p->css);
        DCL_RUN_ERROR_HANDLER(p->css);
    }
    DCL_CONTROLLER_BEGIN(p);
#endif

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
    v12 = (v10 == v9) ? 1.0 : 0.0;
    p->i14 = v12 * lk;

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = (float32_t) v5;
#endif

#ifdef DCL_ERROR_HANDLING_ENABLED
    DCL_CONTROLLER_END(p);
#endif

    return(v10);
}

//--- DF22F64 controller -----------------------------------------------------

#pragma CODE_SECTION(DCL_updateDF22F64,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF22F64_S1,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF22F64_S2,"dclfuncs")
#pragma CODE_SECTION(DCL_runDF22F64_S3,"dclfuncs")

//! \brief          Defines the DCL_DF22F64 shadow parameter set
//!
typedef struct dcl_df22f64_sps {
    float64_t b0;   //!< b0
    float64_t b1;   //!< b1
    float64_t b2;   //!< b2
    float64_t a1;   //!< a1
    float64_t a2;   //!< a2
} DCL_DF22F64_SPS;

#define DF22F64_SPS_DEFAULTS { 1.0, 0.0, 0.0, 0.0, 0.0 }

//! \brief          Defines the DCL_DF22F64 controller structure
//!
typedef struct dcl_df22f64 {
    float64_t b0;   //!< b0
    float64_t b1;   //!< b1
    float64_t b2;   //!< b2
    float64_t a1;   //!< a1
    float64_t a2;   //!< a2
    float64_t x1;   //!< x1
    float64_t x2;   //!< x2
    DCL_DF22F64_SPS *sps;  //!< Pointer to the shadow parameter set
    DCL_CSS *css;   //!< Pointer to the common support structure
} DCL_DF22F64;

//! \brief          Defines default values to initialize the DCL_DF22F64
//! structure
//!
#define DF22F64_DEFAULTS { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, \
                        NULL_ADDR, NULL_ADDR }

//! \brief          Resets internal DF22F64 controller data to zero
//! \param[in] p    Pointer to the DCL_DF22F64 controller structure
//! \return         None
//!
static inline void DCL_resetDF22F64(DCL_DF22F64 *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->x1 = p->x2 = 0.0;
    DCL_RESTORE_INTS(v);
}

//! \brief          Updates active coefficients from shadow set
//! \param[in] p    Pointer to the DCL_DF22F64 controller structure
//! \return         None
//!
static inline void DCL_updateDF22F64(DCL_DF22F64 *p)
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

//! \brief          Executes a full 2nd order Direct Form 2 controller on the
//!                 FPU64.  Implemented as inline C function.
//! \param[in] p    Pointer to the DCL_DF22F64 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float64_t DCL_runDF22F64_S1(DCL_DF22F64 *p, float64_t ek)
{
    float64_t v7;

    v7 = (ek * p->b0) + p->x1;
    p->x1 = (ek * p->b1) + p->x2 - (v7 * p->a1);
    p->x2 = (ek * p->b2) - (v7 * p->a2);

#ifdef DCL_TESTPOINTS_ENABLED
    p->css->tpt = (float32_t) p->x2;
#endif

    return(v7);
}

//! \brief          Executes an immediate 2nd order Direct Form 2 controller
//!                 on the FPU64.  Implemented as inline C function.
//! \param[in] p    Pointer to the DCL_DF22F64 controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float64_t DCL_runDF22F64_S2(DCL_DF22F64 *p, float64_t ek)
{
    return((ek * p->b0) + p->x1);
}

//! \brief          Executes a partial pre-computed 2nd order Direct Form 2
//!                 controller on the FPU64. Implemented as inline C function.
//! \param[in] p    Pointer to the DCL_DF22F64 controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//!
static inline void DCL_runDF22F64_S3(DCL_DF22F64 *p, float64_t ek, float64_t uk)
{
    p->x1 = (ek * p->b1) + p->x2 - (uk * p->a1);
    p->x2 = (ek * p->b2) - (uk * p->a2);
}

//----------------------------------------------------------------------------

//! \brief          Saturates a control variable and returns 1 if either limit
//!                 is exceeded
//! \param[in] data The address of the data variable
//! \param[in] Umax The upper limit
//! \param[in] Umin The lower limit
//! \return         Returns 0 if (Umin < data < Umax), else 1
//!
static inline int16_t DCL_runClamp_S1(float64_t *data, float64_t Umax, float64_t Umin)
{
    float64_t iv = *(data);

    *(data) = (*(data) > Umax) ? Umax : *(data);
    *(data) = (*(data) < Umin) ? Umin : *(data);

    return(((iv < Umax) && (iv > Umin)) ? 0 : 1);
}

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCLF64_H

/* end of file */
