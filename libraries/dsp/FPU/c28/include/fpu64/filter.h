#ifndef _FILTER_H_
#define _FILTER_H_
//#############################################################################
//! \file   include/fpu64/filter.h
//!
//! \brief  Prototypes and Definitions for the DSP Library Filter Module
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
// includes
//*****************************************************************************
#include <stdint.h>
#include "dsp.h"

//!
//! \defgroup DSP_FILTER_F64 Filters (Double Precision)

//!
//! \addtogroup DSP_FILTER_F64
// @{ 

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#ifdef NULL
#undef NULL
#define NULL    0
#else
#define NULL    0
#endif

//*****************************************************************************
// typedefs
//*****************************************************************************
//! Structure for the double precision Finite Impulse Response filter
//! 
typedef struct { 
    float64_t *p_coeff;    //!<  Pointer to the filter coefficients
    float64_t *p_dbuffer;  //!<  Delay buffer pointer
    float64_t *p_input;    //!<  Pointer to the latest input sample
    float64_t *p_output;   //!<  Pointer to the filter output
    uint16_t order;          //!<  Order of the filter
    void (*init)(void *);    //!<  Pointer to the initialization function
    void (*calc)(void *);    //!<  Pointer to the calculation function
}FIR_f64;

//! Handle to the FIR filter structure' object
//!
typedef FIR_f64  *FIR_f64_Handle;

//! Structure for the double precision Infinite Impulse Response filter
//! 
typedef struct { 
    float64_t *p_coeff_A;  //!<  Pointer to the denominator coefficients
    float64_t *p_coeff_B;  //!<  Pointer to the numerator coefficients
    float64_t *p_dbuffer;  //!<  Delay buffer pointer
    float64_t *p_input;    //!<  Pointer to the latest input sample
    float64_t *p_output;   //!<  Pointer to the filter output
    float64_t *p_scale;    //!<  Pointer to the biquad(s) scale values
    uint16_t order;          //!<  Order of the filter
    void (*init)(void *);    //!<  Pointer to the initialization function
    void (*calc)(void *);    //!<  Pointer to the calculation function
}IIR_f64;

//! Handle to the IIR filter structure' object
//!
typedef IIR_f64  *IIR_f64_Handle;
//*****************************************************************************
// 'inline' function
//*****************************************************************************
//! \brief Set the coefficients pointer
//! \param[in] fh  handle to the 'FIR_f64' object
//! \param[in] pc  pointer to the coefficients
//!
static inline void FIR_f64_setCoefficientsPtr(FIR_f64_Handle fh,
        const float64_t *pc)
{
    fh->p_coeff = (float64_t *)pc;
}

//! \brief Get the coefficients pointer
//! \param[in] fh  handle to the 'FIR_f64' object
//! \return pc  pointer to the coefficients
//!
static inline float64_t * FIR_f64_getCoefficientsPtr(FIR_f64_Handle fh)
{
    return(fh->p_coeff);
}

//! \brief Set the delay line pointer
//! \param[in] fh  handle to the 'FIR_f64' object
//! \param[in] pdl  pointer to the delay line
//!
static inline void FIR_f64_setDelayLinePtr(FIR_f64_Handle fh,
        const float64_t *pdl)
{
    fh->p_dbuffer = (float64_t *)pdl;
}

//! \brief Get the delay line pointer
//! \param[in] fh  handle to the 'FIR_f64' object
//! \return pdl  pointer to the delay line
//!
static inline float64_t * FIR_f64_getDelayLinePtr(FIR_f64_Handle fh)
{
    return(fh->p_dbuffer);
}

//! \brief Set the input pointer
//! \param[in] fh  handle to the 'FIR_f64' object
//! \param[in] pi  pointer to the current input
//!
static inline void FIR_f64_setInputPtr(FIR_f64_Handle fh,
        const float64_t *pi)
{
    fh->p_input = (float64_t *)pi;
}

//! \brief Get the input pointer
//! \param[in] fh  handle to the 'FIR_f64' object
//! \return pi  pointer to the current input
//!
static inline float64_t * FIR_f64_getInputPtr(FIR_f64_Handle fh)
{
    return(fh->p_input);
}

//! \brief Set the output pointer
//! \param[in] fh  handle to the 'FIR_f64' object
//! \param[in] po  pointer to the current output
//!
static inline void FIR_f64_setOutputPtr(FIR_f64_Handle fh,
        const float64_t *po)
{
    fh->p_output = (float64_t *)po;
}

//! \brief Get the output pointer
//! \param[in] fh  handle to the 'FIR_f64' object
//! \return po  pointer to the current output
//!
static inline float64_t * FIR_f64_getOutputPtr(FIR_f64_Handle fh)
{
    return(fh->p_output);
}


//! \brief Set the order of the filter
//! \param[in] fh  handle to the 'FIR_f64' object
//! \param[in] order  Order of the filter
//!
static inline void FIR_f64_setOrder(FIR_f64_Handle fh, const uint16_t order)
{
    fh->order = order;
}

//! \brief Get the order of the filter
//! \param[in] fh  handle to the 'FIR_f64' object
//! \return order  Order of the filter
//!
static inline uint16_t FIR_f64_getOrder(FIR_f64_Handle fh)
{
    return(fh->order);
}

//! \brief Set the init function
//! \param[in] fh  handle to the 'FIR_f64' object
//! \param[in] pfn  pointer to the init function
//!
static inline void FIR_f64_setInitFunction(FIR_f64_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->init = pfn;
}

//! \brief Get the init function
//! \param[in] fh  handle to the 'FIR_f64' object
//! \return pfn  pointer to the init function
//!
static inline v_pfn_v FIR_f64_getInitFunction(FIR_f64_Handle fh)
{
    return(fh->init);
}

//! \brief Set the calc function
//! \param[in] fh  handle to the 'FIR_f64' object
//! \param[in] pfn  pointer to the calc function
//!
static inline void FIR_f64_setCalcFunction(FIR_f64_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->calc = pfn;
}

//! \brief Get the calc function
//! \param[in] fh  handle to the 'FIR_f64' object
//! \return pfn  pointer to the calc function
//!
static inline v_pfn_v FIR_f64_getCalcFunction(FIR_f64_Handle fh)
{
    return(fh->calc);
}

//! \brief Set the denominator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] pca  pointer to the denominator coefficients
//!
static inline void IIR_f64_setCoefficientsAPtr(IIR_f64_Handle fh,
        const float64_t *pca)
{
    fh->p_coeff_A = (float64_t *)pca;
}

//! \brief Get the denominator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return pca  pointer to the denominator coefficients
//!
static inline float64_t * IIR_f64_getCoefficientsAPtr(IIR_f64_Handle fh)
{
    return(fh->p_coeff_A);
}

//! \brief Set the numerator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] pcb  pointer to the numerator coefficients
//!
static inline void IIR_f64_setCoefficientsBPtr(IIR_f64_Handle fh,
        const float64_t *pcb)
{
    fh->p_coeff_B = (float64_t *)pcb;
}

//! \brief Get the numerator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return pca  pointer to the numerator coefficients
//!
static inline float64_t * IIR_f64_getCoefficientsBPtr(IIR_f64_Handle fh)
{
    return(fh->p_coeff_B);
}

//! \brief Set the delay line pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] pdl  pointer to the delay line
//!
static inline void IIR_f64_setDelayLinePtr(IIR_f64_Handle fh,
        const float64_t *pdl)
{
    fh->p_dbuffer = (float64_t *)pdl;
}

//! \brief Get the delay line pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return pdl  pointer to the delay line
//!
static inline float64_t * IIR_f64_getDelayLinePtr(IIR_f64_Handle fh)
{
    return(fh->p_dbuffer);
}

//! \brief Set the input pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] pi  pointer to the current input
//!
static inline void IIR_f64_setInputPtr(IIR_f64_Handle fh,
        const float64_t *pi)
{
    fh->p_input = (float64_t *)pi;
}

//! \brief Get the input pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return pi  pointer to the current input
//!
static inline float64_t * IIR_f64_getInputPtr(IIR_f64_Handle fh)
{
    return(fh->p_input);
}

//! \brief Set the output pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] po  pointer to the current output
//!
static inline void IIR_f64_setOutputPtr(IIR_f64_Handle fh,
        const float64_t *po)
{
    fh->p_output = (float64_t *)po;
}

//! \brief Get the output pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return po  pointer to the current output
//!
static inline float64_t * IIR_f64_getOutputPtr(IIR_f64_Handle fh)
{
    return(fh->p_output);
}

//! \brief Set the scale value pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] psv  pointer to the scale values for the biquads
//!
static inline void IIR_f64_setScalePtr(IIR_f64_Handle fh,
        const float64_t *psv)
{
    fh->p_scale = (float64_t *)psv;
}

//! \brief Get the scale value pointer
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return psv  pointer to the scale values for the biquads
//!
static inline float64_t * IIR_f64_getScalePtr(IIR_f64_Handle fh)
{
    return(fh->p_scale);
}

//! \brief Set the order of the filter
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] order  Order of the filter
//!
static inline void IIR_f64_setOrder(IIR_f64_Handle fh, const uint16_t order)
{
    fh->order = order;
}

//! \brief Get the order of the filter
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return order  Order of the filter
//!
static inline uint16_t IIR_f64_getOrder(IIR_f64_Handle fh)
{
    return(fh->order);
}

//! \brief Set the init function
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] pfn  pointer to the init function
//!
static inline void IIR_f64_setInitFunction(IIR_f64_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->init = pfn;
}

//! \brief Get the init function
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return pfn  pointer to the init function
//!
static inline v_pfn_v IIR_f64_getInitFunction(IIR_f64_Handle fh)
{
    return(fh->init);
}

//! \brief Set the calc function
//! \param[in] fh  handle to the 'IIR_f64' object
//! \param[in] pfn  pointer to the calc function
//!
static inline void IIR_f64_setCalcFunction(IIR_f64_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->calc = pfn;
}

//! \brief Get the calc function
//! \param[in] fh  handle to the 'IIR_f64' object
//! \return pfn  pointer to the calc function
//!
static inline v_pfn_v IIR_f64_getCalcFunction(IIR_f64_Handle fh)
{
    return(fh->calc);
}
//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief Finite Impulse Response Filter.
//!
//! This routine implements the non-recursive difference equation of an
//! all-zero filter (FIR), of order N. All the coefficients of all-zero filter
//! are assumed to be less than 1 in magnitude.
//! \param hndFIR_f64 Handle to the FIR_f64 object
//! \attention
//! -# The delay and coefficients buffer must be assigned a minimum of 
//! 4 x (order + 1) words.
//! For example, if the filter order is 31, it will have 32 taps or 
//! coefficients each a 64-bit floating point value. A minimum of 
//! (4 * 32) = 128 words will need to be allocated for the delay and 
//! coefficients buffer.
//! -# In the code example the buffer is assigned to the \b .ebss
//! section while the coefficients are assigned to the \b .econst section.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Number of Taps (Order + 1) <th> Cycles 
//! <tr><td> 28                         <td> 217
//! <tr><td> 59                         <td> 403
//! <tr><td> 117                        <td> 751
//! </table>
//
extern void FIR_f64_calc(FIR_f64_Handle hndFIR_f64);

//! \brief Finite Impulse Response Filter Initialization.
//!
//! Zeros out the delay line 
//! \param hndFIR_f64 Handle to the FIR_f64 object
//! \attention Please see the description of FIR_f64_calc for more details
//! on the space requirements for the delay line and coefficients
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Number of Taps (Order + 1) <th> Cycles 
//! <tr><td> 28                         <td> 130
//! <tr><td> 59                         <td> 254
//! <tr><td> 117                        <td> 486
//! </table>
//
extern void FIR_f64_init(FIR_f64_Handle hndFIR_f64);

//! \brief Infinite Impulse Response Filter.
//!
//! This routine implements the Transposed Direct form II recursive 
//! difference equation of an N pole-zero filter(IIR). 
//! \param hndIIR_f64 Handle to the IIR_f64 object
//! \attention
//! -# The delay line buffer must be 4*(n_biquads*n_delay_elements_per_biquad),
//! since there are 4 delay elements per biquad that are double precision
//! (64-bits) we require a total of 16*n_biquads words
//! For example, if the filter is an 8th order filter it would require 4 
//! biquads (each biqaud is a 2nd order construct) hence 16*4 = 64 words
//! If the filter were a 9th order filter, it would require 5 biquads; the 
//! first four would be quadratic while the last is linear. The last biquad
//! will be implemented with the B[2] and A[2] coefficients zero.
//! We would require a total of 16*5 = 80 words
//! -# In the code example the buffer is assigned to the \b .ebss
//! section while the coefficients are assigned to the \b .econst section.
//! 
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Filter Order <th> Number of Biquads <th> Cycles 
//! <tr><td> 2            <td> 1                 <td> 89
//! <tr><td> 6            <td> 3                 <td> 173
//! <tr><td> 12           <td> 6                 <td> 299
//! </table>
//
extern void IIR_f64_calc(IIR_f64_Handle hndIIR_f64);

//! \brief Infinite Impulse Response Filter Initialization.
//!
//! Zeros out the delay line 
//! \param hndIIR_f64 Handle to the IIR_f64 object
//! \attention Please see the description of IIR_f64_calc for more details
//! on the space requirements for the delay line and coefficients
//! 
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Filter Order <th> Number of Biquads <th> Cycles 
//! <tr><td> 2            <td> 1                 <td> 38
//! <tr><td> 6            <td> 3                 <td> 70
//! <tr><td> 12           <td> 6                 <td> 118
//! </table>
//
extern void IIR_f64_init(IIR_f64_Handle hndIIR_f64);

// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FILTER_H_

// End of File
