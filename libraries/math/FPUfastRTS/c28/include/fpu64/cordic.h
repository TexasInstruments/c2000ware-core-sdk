#ifndef _CORDIC_H_
#define _CORDIC_H_
//#############################################################################
//
//! \file   cordic.h
//!
//! \brief  COordinate Rotation DIgital Computer (CORDIC)
//! \author Vishal Coelho
//! \date   Nov 14, 2016
//
//  Group:          C2000
//  Target Device:  C28x+FPU32/FPU64
//
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
#include <stdint.h>

//!
//! \defgroup CORDIC_F64 COordinate Rotation DIgital Computer (CORDIC) 
//! Definitions and Types
//!
//! \ingroup CORDIC_F64 
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
// Maximum number of CORDIC iterations possible
#define MAX_CORDIC_ITERATIONS   (64U)


//*****************************************************************************
// typedefs
//*****************************************************************************
//! CORDIC structure
//!
typedef struct _CORDIC_F64_
{
    int64_t *x_i;              //!< pointer to x coordinate
    int64_t *y_i;              //!< pointer to y coordinate
    int64_t *z_i;              //!< pointer to mode dependent angle (or angular
                               //!  error)
    uint16_t N;                //!< number of CORDIC iterations (max = 64)
    const int64_t *atanTable;  //!< Pointer to the atan(2^-i) table
    void (*runKernel)(void *); //!< CORDIC kernel
}CORDIC_F64;


//! Handle to a CORDIC object
//!
typedef CORDIC_F64 *CORDIC_F64_Handle;

//*****************************************************************************
//globals
//*****************************************************************************
//! \brief CORDIC Arctangent table
//!
extern const long long CORDIC_F64_atanTable[];

//! \brief CORDIC Scale Factor
//!
extern const long long CORDIC_F64_scaleFactor;

//*****************************************************************************
// 'static inline' functions
//*****************************************************************************
//! \brief Set the x_i pointer of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] x_i, pointer to x_i
//!
static inline void CORDIC_F64_setx_i(CORDIC_F64_Handle hc, int64_t *x_i)
{
    hc->x_i = x_i;
}

//! \brief Get the x_i pointer of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return x_i, pointer to x_i
//!
static inline int64_t * CORDIC_F64_getx_i(CORDIC_F64_Handle hc)
{
    return(hc->x_i);
}

//! \brief Set the y_i pointer of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] y_i, pointer to y_i
//!
static inline void CORDIC_F64_sety_i(CORDIC_F64_Handle hc, int64_t *y_i)
{
    hc->y_i = y_i;
}

//! \brief Get the y_i pointer of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return y_i, pointer to y_i
//!
static inline int64_t * CORDIC_F64_gety_i(CORDIC_F64_Handle hc)
{
    return(hc->y_i);
}

//! \brief Set the z_i pointer of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] z_i, pointer to z_i
//!
static inline void CORDIC_F64_setz_i(CORDIC_F64_Handle hc, int64_t *z_i)
{
    hc->z_i = z_i;
}

//! \brief Get the z_i pointer of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return z_i, pointer to z_i
//!
static inline int64_t * CORDIC_F64_getz_i(CORDIC_F64_Handle hc)
{
    return(hc->z_i);
}

//! \brief Set the N parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] N, number of CORDIC iterations
//!
static inline void CORDIC_F64_setN(CORDIC_F64_Handle hc, const uint16_t N)
{
    hc->N = N;
}

//! \brief Get the N parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return N, value
//!
static inline uint16_t CORDIC_F64_getN(CORDIC_F64_Handle hc)
{
    return(hc->N);
}

//! \brief Set the atanTable pointer parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] p_at, pointer to the arctangent CORDIC table
//!
static inline void CORDIC_F64_setAtanTblPtr(CORDIC_F64_Handle hc,
    const int64_t *p_at)
{
    hc->atanTable = p_at;
}

//! \brief Get the address of the atanTable pointer parameter of the
//! CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return p_at, address of the arctangent CORDIC table
//!
static inline const int64_t * CORDIC_F64_getAtanTblPtr(CORDIC_F64_Handle hc)
{
    return(hc->atanTable);
}

//! \brief Set the runKernel function pointer parameter of the CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \param[in] pfn, pointer to the kernel function
//!
static inline void CORDIC_F64_setRunKernelPtr(CORDIC_F64_Handle hc,
    const v_pfn_v pfn)
{
    hc->runKernel = pfn;
}

//! \brief Get the address of the runKernel function parameter of the
//! CORDIC object
//! \param[in] hc , handle to the CORDIC object
//! \return pfn, pointer to the kernel function
//!
static inline v_pfn_v CORDIC_F64_getRunKernelPtr(CORDIC_F64_Handle hc)
{
    return(hc->runKernel);
}

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief CORDIC Rotation Mode
//! \param[in] hC , handle to the CORDIC object
//! \return none
//!
//! \note TODO
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> TODO <td> TODO
//! </table>
//
extern void CORDIC_F64_rotationKernel(CORDIC_F64_Handle hC);

//! \brief CORDIC Sine
//! \param[in] hC , handle to the CORDIC object
//! \param[in] theta, argument angle in radians [-2pi, 2pi]
//! \return    Sine of the angle
//!
//! This function sets the object's x_i to a predetermined scale factor,
//! y_i to 0 and z_i to IQ61(theta) before calling the rotation kernel
//!
//! \note 
//! -# The object kernel pointer must be set to the rotation kernel prior to 
//! calling this function
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> TODO <td> TODO
//! </table>
//
extern float64u_t CORDIC_F64_sin(CORDIC_F64_Handle hC, float64u_t theta);

//! \brief CORDIC Cosine
//! \param[in] hC , handle to the CORDIC object
//! \param[in] theta, argument angle in radians [-2pi, 2pi]
//! \return    Cosine of the angle
//!
//! This function sets the object's x_i to a predetermined scale factor,
//! y_i to 0 and z_i to IQ61(theta) before calling the rotation kernel
//!
//! \note 
//! -# The object kernel pointer must be set to the rotation kernel prior to 
//! calling this function
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th>Cycles <th> Comment 
//! <tr><td> TODO <td> TODO
//! </table>
//
extern float64u_t CORDIC_F64_cos(CORDIC_F64_Handle hC, float64u_t theta);


#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _CORDIC_H_ definition

// End of File
