/* DCLC28.h - C2000 Digital Control Library header file (32-bit fixed point)
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

#ifndef _C_DCLC28_H
#define _C_DCLC28_H

#ifdef __cplusplus
extern "C" {
#endif

//! \file           DCLC28.h
//! \brief          Contains the public interface to the
//!                 fixed-point Digital Controller Library functions

#include "DCL.h"
#include <stdint.h>

#define Q24_PLUS_1  0x01000000
#define Q24_MINUS_1 0xFF000000


//--- Linear PID controller ---------------------------------------------------

//! \brief          Defines the DCL_PID32 shadow parameter set
//!
typedef struct dcl_pid32_sps {
    int32_t Kp;       //!< Proportional gain
    int32_t Ki;       //!< Integral gain
    int32_t Kd;       //!< Derivative gain
    int32_t c1;       //!< D-term filter coefficient 1
    int32_t c2;       //!< D-term filter coefficient 2
    int32_t Umax;     //!< Upper saturation limit
    int32_t Umin;     //!< Lower saturation limit
} DCL_PID32_SPS;

//! \brief          Defines default values to initialize the DCL_PID shadow structure
//!
#define PID32_SPS_DEFAULTS { Q24_PLUS_1, 0L, 0L, Q24_PLUS_1, 0L, \
                             Q24_PLUS_1, Q24_MINUS_1 }

//! \brief          Defines the fixed-point linear PID32 controller structure
//!
typedef struct dcl_pid32 {
    int32_t Kp;        //!< Proportional gain
    int32_t Ki;        //!< Integral gain
    int32_t Kd;        //!< Derivative gain
    int32_t c1;        //!< D-term filter coefficient 1
    int32_t c2;        //!< D-term filter coefficient 2
    int32_t d2;        //!< D-term filter intermediate storage 1
    int32_t d3;        //!< D-term filter intermediate storage 2
    int32_t i10;       //!< I-term intermediate storage
    int32_t i14;       //!< Intermediate saturation storage
    int32_t Umax;      //!< Upper saturation limit
    int32_t Umin;      //!< Lower saturation limit
    DCL_PID32_SPS *sps;  //!< Pointer to the shadow parameter set
    DCL_CSS *css;      //!< Pointer to the common support structure
} DCL_PID32;

//! \brief          Defines default values to initialize the PID structure
//!
#define DCL_PID32_DEFAULTS {  Q24_PLUS_1, 0L, 0L, Q24_PLUS_1, 0L, 0L, 0L, 0L, \
                              Q24_PLUS_1, Q24_PLUS_1, Q24_MINUS_1, \
                              NULL_ADDR, NULL_ADDR }

//! \brief          Resets PID internal storage data
//! \param[in] p    Pointer to the DCL_PID32 structure
//! \return         None
//!
static inline void DCL_resetPID32(DCL_PID32 *p)
{
    uint16_t v;

    v = DCL_DISABLE_INTS;
    p->d2 = p->d3 = p->i10 = 0L;
    p->i14 = Q24_PLUS_1;
    DCL_RESTORE_INTS(v);
}

//! \brief          Loads PID tuning parameters
//! \param[in] p    Pointer to the DCL_PID32 active controller structure
//! \return         None
//!
static inline void DCL_updatePID32(DCL_PID32 *p)
{
    uint16_t v;

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->Kp = p->sps->Kp;
        p->Ki = p->sps->Ki;
        p->Kd = p->sps->Kd;
        p->c1 = p->sps->c1;
        p->c2 = p->sps->c2;
        p->Umax = p->sps->Umax;
        p->Umin = p->sps->Umin;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads PID32 tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_PID32 controller structure
//! \return         None
//!
extern void DCL_fupdatePID32(DCL_PID32 *p);

//! \brief          Executes a parallel form PID controller on the C28x
//! \param[in] p    Pointer to the DCL_PID32 structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
extern int32_t DCL_runPID_A1(DCL_PID32 *p, int32_t rk, int32_t yk);


//--- Linear PI controller ----------------------------------------------------

//! \brief          Defines the PI32 shadow parameter set
//!
typedef struct dcl_pi32_sps {
    int32_t Kp;       //!< Proportional gain
    int32_t Ki;       //!< Integral gain
    int32_t Umax;     //!< Upper saturation limit
    int32_t Umin;     //!< Lower saturation limit
} DCL_PI32_SPS;

//! \brief          Defines default values to initialize the PI32 shadow structure
//!
#define PI32_SPS_DEFAULTS { Q24_PLUS_1, 0L, Q24_PLUS_1, Q24_MINUS_1 }

//! \brief          Defines the PI32 controller structure
//!
typedef struct dcl_pi32 {
    int32_t Kp;       //!< Proportional gain
    int32_t Ki;       //!< Integral gain
    int32_t i6;       //!< Saturation storage
    int32_t i10;      //!< I storage
    int32_t Umax;     //!< Upper saturation limit
    int32_t Umin;     //!< Lower saturation limit
    DCL_PI32_SPS *sps;  //!< Pointer to the shadow parameter set
    DCL_CSS *css;       //!< Pointer to the common support structure
} DCL_PI32;

//! \brief  Defines default values to initialize the active PI structure
//!
#define DCL_PI32_DEFAULTS { Q24_PLUS_1, 0L, Q24_PLUS_1, 0L, \
                            Q24_PLUS_1, Q24_MINUS_1, \
                            NULL_ADDR, NULL_ADDR }

//! \brief          Resets PI32 internal storage data
//! \param[in] p    Pointer to the DCL_PI32 active controller structure
//! \return         None
//!
static inline void DCL_resetPI32(DCL_PI32 *p)
{
    int16_t v;

    v = DCL_DISABLE_INTS;
    p->i10 = 0L;
    p->i6 = Q24_PLUS_1;
    DCL_RESTORE_INTS(v);
}

//! \brief          Loads active PI32 controller parameters
//! \param[in] p    Pointer to the DCL_PI32 active controller structure
//! \return         None
//!
static inline void DCL_updatePI32(DCL_PI32 *p)
{
    uint16_t v;

    if (p->css->sts & STS_UPDATE_PENDING)
    {
        v = DCL_DISABLE_INTS;
        p->Kp = p->sps->Kp;
        p->Ki = p->sps->Ki;
        p->Umax = p->sps->Umax;
        p->Umin = p->sps->Umin;
        DCL_RESTORE_INTS(v);
        DCL_CLEAR_UPDATE_REQUEST(p);
    }
}

//! \brief          Loads PI32 tuning parameters
//!                 Implemented as assembly module
//! \param[in] p    Pointer to the active DCL_PI32 controller structure
//! \return         None
//!
extern void DCL_fupdatePI32(DCL_PI32 *p);

//! \brief          Executes a series form PI_FP controller on the C28x
//! \param[in] p    Pointer to the DCL_PI structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
extern int32_t DCL_runPI_A1(DCL_PI32 *p, int32_t rk, int32_t yk);

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // extern "C"

#endif // _C_DCLC28_H
