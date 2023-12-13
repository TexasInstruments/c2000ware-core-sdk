/* DCLCLA.h - C2000 Digital Controller Library header file
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

#ifndef _C_DCLCLA_H
#define _C_DCLCLA_H

//! \file           DCLCLA.h
//! \brief          Contains the public interface to the
//!                 Digital Controller Library CLA functions

#include "DCL.h"


//--- Linear PID controller ---------------------------------------------------

//! \brief          Defines the DCL_PID_CLA controller structure
//!
typedef struct {
    float32_t Kp;       //!< Proportional gain
    float32_t Ki;       //!< Integral gain
    float32_t Kd;       //!< Derivative gain
    float32_t Kr;       //!< Set point weight
    float32_t c1;       //!< D-term filter coefficient 1
    float32_t c2;       //!< D-term filter coefficient 2
    float32_t d2;       //!< D-term filter intermediate storage 1
    float32_t d3;       //!< D-term filter intermediate storage 2
    float32_t i10;      //!< I-term intermediate storage
    float32_t i14;      //!< Intermediate saturation storage
    float32_t Umax;     //!< Upper saturation limit
    float32_t Umin;     //!< Lower saturation limit
} DCL_PID_CLA;

//! \brief          Defines default values to initialize the DCL_PID structure
//!
#define PID_CLA_DEFAULTS {  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, \
                            0.0f, 0.0f, 1.0f, -1.0f }

//! \brief          Executes an ideal form PID controller on the CLA
//! \param[in] p    Pointer to the DCL_PID_CLA structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
extern float32_t DCL_runPID_L1(DCL_PID_CLA *p, float32_t rk, float32_t yk, float32_t lk);

//! \brief          Executes a parallel form PID controller on the CLA
//! \param[in] p    Pointer to the DCL_PID_CLA structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \param[in] lk   External output clamp flag
//! \return         The control effort
//!
extern float32_t DCL_runPID_L2(DCL_PID_CLA *p, float32_t rk, float32_t yk, float32_t lk);


//--- Linear PI controller ----------------------------------------------------

//! \brief          Defines the DCL_PI_CLA controller structure
//!
typedef struct {
    float32_t Kp;       //!< Proportional gain
    float32_t Ki;       //!< Integral gain
    float32_t i10;      //!< I storage
    float32_t Umax;     //!< Upper control saturation limit
    float32_t Umin;     //!< Lower control saturation limit
    float32_t i6;       //!< Saturation storage
    float32_t i11;      //!< I storage
    float32_t Imax;     //!< Upper integrator saturation limit
    float32_t Imin;     //!< Lower integrator saturation limit
} DCL_PI_CLA;

//! \brief  Defines default values to initialize the PI_CLA structure
//!
#define PI_CLA_DEFAULTS { 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f }

//! \brief          Executes a series form PI controller on the CLA
//! \param[in] p    Pointer to the DCL_PI_CLA structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
extern float32_t DCL_runPI_L1(DCL_PI_CLA *p, float32_t rk, float32_t yk);

//! \brief          Executes a parallel form PI controller on the CLA
//! \param[in] p    Pointer to the DCL_PI_CLA structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
extern float32_t DCL_runPI_L2(DCL_PI_CLA *p, float32_t rk, float32_t yk);

//! \brief 			Executes an inline series form PI controller on the CLA
//! 				Implemented as inline C function
//! \param[in] p 	Pointer to the DCL_PI structure
//! \param[in] rk 	The controller set-point reference
//! \param[in] yk 	The measured feedback value
//! \return 		The control effort
//!
static inline float32_t DCL_runPI_L3(DCL_PI_CLA *p, float32_t rk, float32_t yk)
{
    float32_t v2, v4, v5, v9;

    asm(" MSETFLG   RNDF32=1");
	v2 = p->Kp * (rk - yk);
	v4 = p->i10 + (p->Ki * p->i6 * v2);
	v5 = v2 + v4;
	v9 = (v5 > p->Umax) ? p->Umax : v5;
	v9 = (v9 < p->Umin) ? p->Umin : v9;
	p->i10 = v4;
	p->i6 = (v5 == v9) ? 1.0f : 0.0f;

	return(v9);
}

//! \brief 			Executes an parallel form PI controller on the CLA
//! 				Implemented as inline C function
//! \param[in] p 	Pointer to the DCL_PI structure
//! \param[in] rk 	The controller set-point reference
//! \param[in] yk 	The measured feedback value
//! \return 		The control effort
//!
static inline float32_t DCL_runPI_L4(DCL_PI_CLA *p, float32_t rk, float32_t yk)
{
	float32_t v1, v2, v4, v5, v9;

    asm(" MSETFLG   RNDF32=1");
	v1 = rk - yk;
	v2 = p->Kp * v1;
	v4 = (v1 * p->Ki * p->i6) + p->i10;
	p->i10 = v4;
	v5 = v2 + v4;
	v9 = (v5 > p->Umax) ? p->Umax : v5;
	v9 = (v9 < p->Umin) ? p->Umin : v9;
	p->i6 = (v5 == v9) ? 1.0f : 0.0f;

	return(v9);
}

//! \brief          Executes a series form PI controller with Tustin integrator
//!                 on the CLA.
//! \param[in] p    Pointer to the DCL_PI_CLA structure
//! \param[in] rk   The controller set-point reference
//! \param[in] yk   The measured feedback value
//! \return         The control effort
//!
static inline float32_t DCL_runPI_L5(DCL_PI_CLA *p, float32_t rk, float32_t yk)
{
    float32_t v2, v4, v5, v8, v9;

    asm(" MSETFLG   RNDF32=1");
    v2 = (rk - yk) * p->Kp;
    v8 = v2 * p->Ki * p->i6;
    v4 = v8 + p->i11 + p->i10;
    v5 = v2 + v4;
    p->i10 = v4;
    p->i11 = v8;
    v9 = (v5 > p->Umax) ? p->Umax : v5;
    v9 = (v9 < p->Umin) ? p->Umin : v9;
    p->i6 = (v5 == v9) ? 1.0f : 0.0f;

    return(v9);
}


//--- Direct Form 1 - 1st order -----------------------------------------------

//! \brief          Defines the DCL_DF11 controller structure
//!
typedef struct {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t a1;   //!< a1
    float32_t d1;   //!< e(k-1)
    float32_t d2;   //!< u(k-1)
} DCL_DF11_CLA;

//! \brief          Defines default values to initialize the DCL_DF11_CLA structure
//!
#define DF11_CLA_DEFAULTS { 0.5f, 0.5f, 1.0f, 0.0f, 0.0f }

//! \brief          Executes a 1st order Direct Form 1 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF11_CLA controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF11_L1(DCL_DF11_CLA *p, float32_t ek);


//--- Direct Form 1 - 3rd order -----------------------------------------------

//! \brief          Defines the DCL_DF13_CLA controller structure
//!
typedef struct {
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
} DCL_DF13_CLA;

//! \brief          Defines default values to initialize the DCL_DF13_CLA structure
//!
#define DF13_CLA_DEFAULTS { 0.25f, 0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, \
                        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }

//! \brief          Executes a full 3rd order Direct Form 1 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF13_CLA controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF13_L1(DCL_DF13_CLA *p, float32_t ek);

//! \brief          Executes an immediate 3rd order Direct Form 1 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF13_CLA controller structure
//! \param[in] ek   The servo error
//! \param[in] vk   The partial pre-computed control effort
//! \return         The control effort
//!
extern float32_t DCL_runDF13_L2(DCL_DF13_CLA *p, float32_t ek, float32_t vk);

//! \brief          Executes a partial pre-computed 3rd order Direct Form 1 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF13_CLA controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//! \return         The control effort
//!
extern float32_t DCL_runDF13_L3(DCL_DF13_CLA *p, float32_t ek, float32_t uk);

//! \brief          Executes a full 3rd order Direct Form 1 controller on the CLA
//!                 Implemented as inline C function
//!                 Note: d0 not used
//! \param[in] p    Pointer to the DCL_DF13_CLA controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
static inline float32_t DCL_runDF13_L4(DCL_DF13_CLA *p, float32_t ek)
{
    asm(" MSETFLG   RNDF32=1");
    p->d4 = (ek * p->b0) + (p->d1 * p->b1) + (p->d2 * p->b2) + (p->d3 * p->b3) - (p->d5 * p->a1) - (p->d6 * p->a2) - (p->d7 * p->a3);
    p->d3 = p->d2;
    p->d2 = p->d1;
    p->d1 = ek;
    p->d7 = p->d6;
    p->d6 = p->d5;
    p->d5 = p->d4;

    return(p->d4);
}

//! \brief          Executes an immediate 3rd order Direct Form 1 controller on the CLA
//!                 Implemented as inline C function
//! \param[in] p    Pointer to the DCL_DF13_CLA controller structure
//! \param[in] ek   The servo error
//! \param[in] vk   The partial pre-computed control effort
//! \return         The control effort
//!
static inline float32_t DCL_runDF13_L5(DCL_DF13_CLA *p, float32_t ek, float32_t vk)
{
    asm(" MSETFLG   RNDF32=1");
    p->d4 = (ek * p->b0) + vk;

    return(p->d4);
}

//! \brief          Executes a partial pre-computed 3rd order Direct Form 1 controller on the CLA
//!                 Implemented as inline C function
//!                 Note: d0 not used
//! \param[in] p    Pointer to the DCL_DF13_CLA controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//! \return         The control effort
//!
static inline float32_t DCL_runDF13_L6(DCL_DF13_CLA *p, float32_t ek, float32_t uk)
{
    float32_t v9;

    asm(" MSETFLG   RNDF32=1");
    v9 = (ek * p->b1) + (p->d1 * p->b2) + (p->d2 * p->b3) - (uk * p->a1) - (p->d5 * p->a2) - (p->d6 * p->a3);
    p->d2 = p->d1;
    p->d1 = ek;
    p->d6 = p->d5;
    p->d5 = uk;

    return(v9);
}


//--- Direct Form 2 - 2nd order -----------------------------------------------

//! \brief          Defines the DCL_DF22_CLA controller structure
//!
typedef struct {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t b2;   //!< b2
    float32_t a1;   //!< a1
    float32_t a2;   //!< a2
    float32_t x1;   //!< x1
    float32_t x2;   //!< x2
} DCL_DF22_CLA;

//! \brief          Defines default values to initialize the DCL_DF22_CLA structure
//!
#define DF22_CLA_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }

//! \brief          Executes a full 2nd order Direct Form 2 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF22_CLA controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF22_L1(DCL_DF22_CLA *p, float32_t ek);

//! \brief          Executes an immediate 2nd order Direct Form 2 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF22_CLA controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF22_L2(DCL_DF22_CLA *p, float32_t ek);

//! \brief          Executes a partial pre-computed 2nd order Direct Form 2 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF22_CLA controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//!
extern void DCL_runDF22_L3(DCL_DF22_CLA *p, float32_t ek, float32_t uk);

//! \brief 			Executes a full 2nd order Direct Form 2 controller on the CLA
//! 				Implemented as inline C function
//! \param[in] p 	Pointer to the DCL_DF22 controller structure
//! \param[in] ek 	The servo error
//! \return 		The control effort
//!
static inline float32_t DCL_runDF22_L4(DCL_DF22_CLA *p, float32_t ek)
{
	float32_t v7;

    asm(" MSETFLG   RNDF32=1");
	v7 = (ek * p->b0) + p->x1;
	p->x1 = (ek * p->b1) + p->x2 - (v7 * p->a1);
	p->x2 = (ek * p->b2) - (v7 * p->a2);

	return(v7);
}


//--- Direct Form 2 - 3rd order -----------------------------------------------

//! \brief          Defines the DCL_DF23_CLA controller structure
//!
typedef struct {
    float32_t b0;   //!< b0
    float32_t b1;   //!< b1
    float32_t b2;   //!< b2
    float32_t b3;   //!< b3
    float32_t a1;   //!< a1
    float32_t a2;   //!< a2
    float32_t a3;   //!< a3
    float32_t x1;   //!< x1
    float32_t x2;   //!< x2
    float32_t x3;   //!< x3
} DCL_DF23_CLA;

//! \brief          Defines default values to initialize the DCL_DF23_CLA structure
//!
#define DF23_CLA_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }

//! \brief          Executes a full 3rd order Direct Form 2 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF23_CLA controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF23_L1(DCL_DF23_CLA *p, float32_t ek);

//! \brief          Executes an immediate 3rd order Direct Form 2 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF23_CLA controller structure
//! \param[in] ek   The servo error
//! \return         The control effort
//!
extern float32_t DCL_runDF23_L2(DCL_DF23_CLA *p, float32_t ek);

//! \brief          Executes a partial pre-computed 2nd order Direct Form 2 controller on the CLA
//! \param[in] p    Pointer to the DCL_DF23_CLA controller structure
//! \param[in] ek   The servo error
//! \param[in] uk   The controller output in the previous sample interval
//!
extern void DCL_runDF23_L3(DCL_DF23_CLA *p, float32_t ek, float32_t uk);


//--- Direct Form 2 - clamp ---------------------------------------------------

//! \brief          Saturates a control variable and returns 1.0f if either limit is exceeded
//!
//! \details        Can be used to saturate a pre-computed Direct Form 2 controller.
//!                 If the immediate result is in range it can be used, otherwise
//!                 it can be clamped and the next partial pre-computation skipped.
//!                 An example of use with a pre-computed DF22 controller follows:
//!
//! \code
//! uk = DCL_runDF22_L2(&arma2, rk);                // immediate result from pre-computed controller
//! f = DCL_runClamp_L1(&uk, 1.0f, -1.0f);          // clamp immediate result to +/-1.0
//! // ...use uk here...
//! if (0.5f > f)                                   // if immediate result is in range...
//! {
//!     DCL_runDF22_L3(&arma2, rk, uk);             // ...pre-compute the next partial result
//! }
//! \endcode
//!
//! \param[in] data The address of the data variable
//! \param[in] Umax The upper limit
//! \param[in] Umin The lower limit
//! \return         Returns 0.0f if (Umin < data < Umax), else 1.0f
//!
extern float32_t DCL_runClamp_L1(float32_t *data, float32_t Umax, float32_t Umin);

#endif // _C_DCLCLA_H

/* end of file */
