#ifndef _FPU_FILTER_H_
#define _FPU_FILTER_H_
//#############################################################################
//! \file   include/fpu_filter.h
//!
//! \brief  Prototypes and Definitions for the C28x FPU Library
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
#include "fpu_types.h"

//!
//! \defgroup DSP_FILTER_F32 Filters

//!
//! \addtogroup DSP_FILTER_F32
// @{ 

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
//#define NULL    0
#if (USE_LEGACY_NAMES==0U)
//! FIR_FP is the legacy name of the FIR structure
#define FIR_FP          FIR_f32          
//! FIR_FP_Handle is the legacy name of the FIR structure handle
#define FIR_FP_Handle   FIR_f32_Handle  
//! FIR_FP_init is the legacy name of the FIR initialization function
#define FIR_FP_init     FIR_f32_init 
//! FIR_FP_calc is the legacy name of the FIR calculation function
#define FIR_FP_calc     FIR_f32_calc    
#endif // USE_LEGACY_NAMES

//*****************************************************************************
// typedefs
//*****************************************************************************
//! Structure for the Finite Impulse Response Filter
//!
typedef struct { 
    float *coeff_ptr;        //!<  Pointer to Filter coefficient
    float *dbuffer_ptr;      //!<  Delay buffer pointer
    int16_t cbindex;         //!<  Circular Buffer Index
    int16_t order;           //!<  Order of the Filter
    float input;             //!<  Latest Input sample
    float output;            //!<  Filter Output
    void (*init)(void *);    //!<  Pointer to Initialization function
    void (*calc)(void *);    //!<  Pointer to the calculation function
    }FIR_f32;

//! Handle to the Filter Structure Object
typedef FIR_f32     *FIR_f32_Handle;

//! The default FIR object initializer
#define FIR_f32_DEFAULTS { (float *)NULL, \
             (float *)NULL,  \
             0,              \
             50,             \
             0,              \
             0,              \
             (void (*)(void *))FIR_f32_init,\
             (void (*)(void *))FIR_f32_calc}    

//! Structure defintion for the Infinite Impulse Response Filter
//!             
typedef struct { 
    float *p_coeff_A;        //!<  Pointer to the denominator coefficients
    float *p_coeff_B;        //!<  Pointer to the numerator coefficients
    float *p_dbuffer;        //!<  Delay buffer pointer
    float *p_input;          //!<  Pointer to the latest input sample
    float *p_output;         //!<  Pointer to the filter output
    float *p_scale;          //!<  Pointer to the biquad(s) scale values
    uint16_t order;          //!<  Order of the filter
    void (*init)(void *);    //!<  Pointer to the initialization function
    void (*calc)(void *);    //!<  Pointer to the calculation function
}IIR_f32;

//! Handle to the Filter Structure Object
typedef IIR_f32 *IIR_f32_Handle;

//*****************************************************************************
// 'inline' function
//*****************************************************************************
//! \brief Set the coefficients pointer
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] pc  pointer to the coefficients
//!
static inline void FIR_f32_setCoefficientsPtr(FIR_f32_Handle fh,
        const float *pc)
{
    fh->coeff_ptr = (float *)pc;
}

//! \brief Get the coefficients pointer
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pc  pointer to the coefficients
//!
static inline float * FIR_f32_getCoefficientsPtr(FIR_f32_Handle fh)
{
    return(fh->coeff_ptr);
}

//! \brief Set the delay line pointer
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] pdl  pointer to the delay line
//!
static inline void FIR_f32_setDelayLinePtr(FIR_f32_Handle fh,
        const float *pdl)
{
    fh->dbuffer_ptr = (float *)pdl;
}

//! \brief Get the delay line pointer
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pdl  pointer to the delay line
//!
static inline float * FIR_f32_getDelayLinePtr(FIR_f32_Handle fh)
{
    return(fh->dbuffer_ptr);
}

//! \brief Set the input
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] in  current input
//!
static inline void FIR_f32_setInput(FIR_f32_Handle fh,
        const float in)
{
    fh->input = in;
}

//! \brief Get the input
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pin  current input pointer
//!
static inline float FIR_f32_getInput(FIR_f32_Handle fh)
{
    return(fh->input);
}

//! \brief Set the output
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] out  current output
//!
static inline void FIR_f32_setOutput(FIR_f32_Handle fh,
        const float out)
{
    fh->output = out;
}

//! \brief Get the output
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return out  current output
//!
static inline float FIR_f32_getOutput(FIR_f32_Handle fh)
{
    return(fh->output);
}


//! \brief Set the order of the filter
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] order  Order of the filter
//!
static inline void FIR_f32_setOrder(FIR_f32_Handle fh, const uint16_t order)
{
    fh->order = order;
}

//! \brief Get the order of the filter
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return order  Order of the filter
//!
static inline uint16_t FIR_f32_getOrder(FIR_f32_Handle fh)
{
    return(fh->order);
}

//! \brief Set the init function
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] pfn  pointer to the init function
//!
static inline void FIR_f32_setInitFunction(FIR_f32_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->init = pfn;
}

//! \brief Get the init function
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pfn  pointer to the init function
//!
static inline v_pfn_v FIR_f32_getInitFunction(FIR_f32_Handle fh)
{
    return(fh->init);
}

//! \brief Set the calc function
//! \param[in] fh  handle to the 'FIR_f32' object
//! \param[in] pfn  pointer to the calc function
//!
static inline void FIR_f32_setCalcFunction(FIR_f32_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->calc = pfn;
}

//! \brief Get the calc function
//! \param[in] fh  handle to the 'FIR_f32' object
//! \return pfn  pointer to the calc function
//!
static inline v_pfn_v FIR_f32_getCalcFunction(FIR_f32_Handle fh)
{
    return(fh->calc);
}

//! \brief Set the denominator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pca  pointer to the denominator coefficients
//!
static inline void IIR_f32_setCoefficientsAPtr(IIR_f32_Handle fh,
        const float *pca)
{
    fh->p_coeff_A = (float *)pca;
}

//! \brief Get the denominator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pca  pointer to the denominator coefficients
//!
static inline float * IIR_f32_getCoefficientsAPtr(IIR_f32_Handle fh)
{
    return(fh->p_coeff_A);
}

//! \brief Set the numerator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pcb  pointer to the numerator coefficients
//!
static inline void IIR_f32_setCoefficientsBPtr(IIR_f32_Handle fh,
        const float *pcb)
{
    fh->p_coeff_B = (float *)pcb;
}

//! \brief Get the numerator coefficients pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pca  pointer to the numerator coefficients
//!
static inline float * IIR_f32_getCoefficientsBPtr(IIR_f32_Handle fh)
{
    return(fh->p_coeff_B);
}

//! \brief Set the delay line pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pdl  pointer to the delay line
//!
static inline void IIR_f32_setDelayLinePtr(IIR_f32_Handle fh,
        const float *pdl)
{
    fh->p_dbuffer = (float *)pdl;
}

//! \brief Get the delay line pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pdl  pointer to the delay line
//!
static inline float * IIR_f32_getDelayLinePtr(IIR_f32_Handle fh)
{
    return(fh->p_dbuffer);
}

//! \brief Set the input pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pi  pointer to the current input
//!
static inline void IIR_f32_setInputPtr(IIR_f32_Handle fh,
        const float *pi)
{
    fh->p_input = (float *)pi;
}

//! \brief Get the input pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pi  pointer to the current input
//!
static inline float * IIR_f32_getInputPtr(IIR_f32_Handle fh)
{
    return(fh->p_input);
}

//! \brief Set the output pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] po  pointer to the current output
//!
static inline void IIR_f32_setOutputPtr(IIR_f32_Handle fh,
        const float *po)
{
    fh->p_output = (float *)po;
}

//! \brief Get the output pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return po  pointer to the current output
//!
static inline float * IIR_f32_getOutputPtr(IIR_f32_Handle fh)
{
    return(fh->p_output);
}

//! \brief Set the scale value pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] psv  pointer to the scale values for the biquads
//!
static inline void IIR_f32_setScalePtr(IIR_f32_Handle fh,
        const float *psv)
{
    fh->p_scale = (float *)psv;
}

//! \brief Get the scale value pointer
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return psv  pointer to the scale values for the biquads
//!
static inline float * IIR_f32_getScalePtr(IIR_f32_Handle fh)
{
    return(fh->p_scale);
}

//! \brief Set the order of the filter
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] order  Order of the filter
//!
static inline void IIR_f32_setOrder(IIR_f32_Handle fh, const uint16_t order)
{
    fh->order = order;
}

//! \brief Get the order of the filter
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return order  Order of the filter
//!
static inline uint16_t IIR_f32_getOrder(IIR_f32_Handle fh)
{
    return(fh->order);
}

//! \brief Set the init function
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pfn  pointer to the init function
//!
static inline void IIR_f32_setInitFunction(IIR_f32_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->init = pfn;
}

//! \brief Get the init function
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pfn  pointer to the init function
//!
static inline v_pfn_v IIR_f32_getInitFunction(IIR_f32_Handle fh)
{
    return(fh->init);
}

//! \brief Set the calc function
//! \param[in] fh  handle to the 'IIR_f32' object
//! \param[in] pfn  pointer to the calc function
//!
static inline void IIR_f32_setCalcFunction(IIR_f32_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->calc = pfn;
}

//! \brief Get the calc function
//! \param[in] fh  handle to the 'IIR_f32' object
//! \return pfn  pointer to the calc function
//!
static inline v_pfn_v IIR_f32_getCalcFunction(IIR_f32_Handle fh)
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
//! \param hndFIR_f32 Handle to the FIR_f32 object
//! \attention
//! -# The delay and coefficients buffer must be aligned to a minimum of 
//! 2 x (order + 1) words.
//! For example, if the filter order is 31, it will have 32 taps or 
//! coefficients each a 32-bit floating point value. A minimum of 
//! (2 * 32) = 64 words will need to be allocated for the delay and 
//! coefficients buffer.
//! -# To align the buffer, use the DATA_SECTION pragma to assign the buffer to
//! a code section and then align the buffer to the proper offset in the linker
//! command file. In the code example the buffer is assigned to the \b firldb 
//! section while the coefficients are assigned to the \b coefffilt section.
//! -# This routine requires the --c2xlp_src_compatible option to be enabled 
//! in the file specific properties when accepting 24x assembly instructions.
//! This option is ONLY used if you are migrating C24x code to the C28x, and is
//! not available for compilers after v6.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Number of Taps (Order + 1) <th> Cycles 
//! <tr><td> 28                         <td> 103
//! <tr><td> 59                         <td> 165
//! <tr><td> 117                        <td> 281
//! </table>
//
extern void FIR_f32_calc(FIR_f32_Handle hndFIR_f32);

//! \brief Finite Impulse Response Filter Initialization.
//!
//! Zeros out the delay line 
//! \param hndFIR_f32 Handle to the FIR_f32 object
//! \attention
//! -# The delay and coefficients buffer must be aligned to a minimum of 
//! 2 x (order + 1) words.
//! For example, if the filter order is 31, it will have 32 taps or 
//! coefficients each a 32-bit floating point value. A minimum of (2 * 32) = 64 
//! words will need to be allocated for the delay and coefficients buffer.
//! -# The delay buffer needs to be aligned to word boundary of 2 * number of 
//! taps
//! -# To align the buffer, use the DATA_SECTION pragma to assign the buffer to
//! a code section and then align the buffer to the proper offset in the linker
//! command file. In the code example the buffer is assigned to the \b firldb
//! section while the coefficients are assigned to the \b coefffilt section.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Number of Taps (Order + 1) <th> Cycles 
//! <tr><td> 28                         <td>  79
//! <tr><td> 59                         <td> 141
//! <tr><td> 117                        <td> 257
//! </table>
//
extern void FIR_f32_init(FIR_f32_Handle hndFIR_f32);

//! \brief Infinite Impulse Response Filter.
//!
//! This routine implements the Transposed Direct form II recursive 
//! difference equation of an N pole-zero filter(IIR). 
//! \param hndIIR_f32 Handle to the IIR_f32 object
//! \attention
//! -# The delay line buffer must be 2*(n_biquads*n_delay_elements_per_biquad),
//! since there are 4 delay elements per biquad that are single precision
//! (32-bits) we require a total of 8*n_biquads words
//! For example, if the filter is an 8th order filter it would require 4 
//! biquads (each biqaud is a 2nd order construct) hence 8*4 = 32 words
//! If the filter were a 9th order filter, it would require 5 biquads; the 
//! first four would be quadratic while the last is linear. The last biquad
//! will be implemented with the B[2] and A[2] coefficients zero.
//! We would require a total of 8*5 = 40 words
//! -# In the code example the buffer is assigned to the \b .ebss
//! section while the coefficients are assigned to the \b .econst section.
//! 
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Filter Order <th> Number of Biquads <th> Cycles 
//! <tr><td> 2            <td> 1                 <td>  68
//! <tr><td> 6            <td> 3                 <td> 116
//! <tr><td> 12           <td> 6                 <td> 188
//! </table>
//
extern void IIR_f32_calc(IIR_f32_Handle hndIIR_f32);

//! \brief Infinite Impulse Response Filter Initialization.
//!
//! Zeros out the delay line 
//! \param hndIIR_f32 Handle to the IIR_f32 object
//! \attention Please see the description of IIR_f32_calc for more details
//! on the space requirements for the delay line and coefficients
//! 
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Filter Order <th> Number of Biquads <th> Cycles 
//! <tr><td> 2            <td> 1                 <td> 30
//! <tr><td> 6            <td> 3                 <td> 46
//! <tr><td> 12           <td> 6                 <td> 70
//! </table>
//
extern void IIR_f32_init(IIR_f32_Handle hndIIR_f32);

// @} //addtogroup

/*********** Sample FIR Co-efficients **************************/

/* 5th order LPF co-efficients for FIR_f32 module   */
#define FIR_F32_LPF6 {\
    -0.0805727691,  0.1966465116,  0.4776741266,  0.4776741266, \
    0.1966465116, -0.0805727691}

/* 31st order LPF co-efficients for FIR_f32 module  */  
#define FIR_F32_LPF32 {\
-0.0009375925, -0.0018498098,  0.0028200552,  0.0037323495, \
-0.0056770989, -0.0075621097,  0.0106198033,  0.0136981048, \
-0.0185259376, -0.0237575006,  0.0318195596,  0.0418184102, \
-0.0582660958, -0.0851156115,  0.1475527734,  0.4489050806, \
 0.4489050806,  0.1475527734, -0.0851156115, -0.0582660958, \
 0.0418184102,  0.0318195596, -0.0237575006, -0.0185259376, \
 0.0136981048,  0.0106198033, -0.0075621097, -0.0056770989, \
 0.0037323495,  0.0028200552, -0.0018498098, -0.0009375925,}

/* 50th order LPF co-efficients for FIR_f32 module  */
#define FIR_F32_LPF50 {\
-7.5203931190e-04, -3.4963795920e-03, -2.5768701450e-03, -2.9541992120e-03,\
-1.9022732740e-03,  7.5785334050e-05,  2.9216345870e-03,  6.0432236640e-03,\
 8.6036063730e-03,  9.6314987170e-03,  8.2863057030e-03,  4.1323564950e-03,\
-2.6098575910e-03, -1.0932658800e-02, -1.9081210720e-02, -2.4793250490e-02,\
-2.5703735650e-02, -1.9845590000e-02, -6.1563691120e-03,  1.5153512360e-02,\
 4.2456313970e-02,  7.2834178810e-02,  1.0249938820e-01,  1.2741793690e-01,\
 1.4401510360e-01,  1.4983779190e-01,  1.4401510360e-01,  1.2741793690e-01,\
 1.0249938820e-01,  7.2834178810e-02,  4.2456313970e-02,  1.5153512360e-02,\
-6.1563691120e-03, -1.9845590000e-02, -2.5703735650e-02, -2.4793250490e-02,\
-1.9081210720e-02, -1.0932658800e-02, -2.6098575910e-03,  4.1323564950e-03,\
 8.2863057030e-03,  9.6314987170e-03,  8.6036063730e-03,  6.0432236640e-03,\
 2.9216345870e-03,  7.5785334050e-05, -1.9022732740e-03, -2.9541992120e-03,\
-2.5768701450e-03, -3.4963795920e-03, -7.5203931190e-04, }

/* 63rd order LPF co-efficients for FIR_f32 module  */  
#define FIR_F32_LPF64 {\
 1.2839649800e-02,  2.2292095240e-03,  1.9878095480e-03,  1.4185620240e-03,\
 5.1166024060e-04, -7.1911053960e-04, -2.2336612460e-03, -3.9673773570e-03,\
-5.8279242370e-03, -7.6969428920e-03, -9.4345659020e-03, -1.0890865700e-02,\
-1.1906139550e-02, -1.2328188870e-02, -1.2016832830e-02, -1.0844063950e-02,\
-8.7080327790e-03, -5.5583743380e-03, -1.4110758200e-03,  3.7384047170e-03,\
 9.7692636770e-03,  1.6556531190e-02,  2.3915413770e-02,  3.1625773760e-02,\
 3.9436016230e-02,  4.7077395020e-02,  5.4273974150e-02,  6.0760140420e-02,\
 6.6282063720e-02,  7.0633381610e-02,  7.3633328080e-02,  7.5161464510e-02,\
 7.5161464510e-02,  7.3633328080e-02,  7.0633381610e-02,  6.6282063720e-02,\
 6.0760140420e-02,  5.4273974150e-02,  4.7077395020e-02,  3.9436016230e-02,\
 3.1625773760e-02,  2.3915413770e-02,  1.6556531190e-02,  9.7692636770e-03,\
 3.7384047170e-03, -1.4110758200e-03, -5.5583743380e-03, -8.7080327790e-03,\
-1.0844063950e-02, -1.2016832830e-02, -1.2328188870e-02, -1.1906139550e-02,\
-1.0890865700e-02, -9.4345659020e-03, -7.6969428920e-03, -5.8279242370e-03,\
-3.9673773570e-03, -2.2336612460e-03, -7.1911053960e-04,  5.1166024060e-04,\
 1.4185620240e-03,  1.9878095480e-03,  2.2292095240e-03,  1.2839649800e-02,}
    
    
/* 127th order LPF co-efficients for FIR_f32 module */  
#define FIR_F32_LPF128 {\
-5.0361973080e-07, -8.4154989960e-06, -1.0349400330e-05, -5.8855544010e-06,\
 9.1910196720e-06,  2.8685428330e-05,  3.7397850970e-05,  1.9508090190e-05,\
-2.6992138370e-05, -8.0040139440e-05, -9.9044016680e-05, -4.9611899160e-05,\
 6.4349056630e-05,  1.8490898950e-04,  2.2145068210e-04,  1.0800584280e-04,\
-1.3433356070e-04, -3.7753640210e-04, -4.4174649520e-04, -2.1128321530e-04,\
 2.5497740720e-04,  7.0462777510e-04,  8.1000913630e-04,  3.8161687550e-04,\
-4.5005651190e-04, -1.2273221510e-03, -1.3913452860e-03, -6.4770405880e-04,\
 7.5010029830e-04,  2.0240161100e-03,  2.2691879420e-03,  1.0463795620e-03,\
-1.1943303980e-03, -3.1960245690e-03, -3.5522116810e-03, -1.6261441630e-03,\
 1.8349840540e-03,  4.8805172560e-03,  5.3903660740e-03,  2.4554035630e-03,\
-2.7475596870e-03, -7.2813183070e-03, -8.0133378510e-03, -3.6424295980e-03,\
 4.0559638290e-03,  1.0745704170e-02,  1.1828300540e-02,  5.3872759450e-03,\
-5.9996559280e-03, -1.5976045280e-02, -1.7699496820e-02, -8.1367669630e-03,\
 9.1444076970e-03,  2.4733832110e-02,  2.7942722660e-02,  1.3180750420e-02,\
-1.5270783570e-02, -4.3150499460e-02, -5.1665931940e-02, -2.6430377740e-02,\
 3.4355875100e-02,  1.1681985110e-01,  1.9554567340e-01,  2.4352604150e-01,\
 2.4352604150e-01,  1.9554567340e-01,  1.1681985110e-01,  3.4355875100e-02,\
-2.6430377740e-02, -5.1665931940e-02, -4.3150499460e-02, -1.5270783570e-02,\
 1.3180750420e-02,  2.7942722660e-02,  2.4733832110e-02,  9.1444076970e-03,\
-8.1367669630e-03, -1.7699496820e-02, -1.5976045280e-02, -5.9996559280e-03,\
 5.3872759450e-03,  1.1828300540e-02,  1.0745704170e-02,  4.0559638290e-03,\
-3.6424295980e-03, -8.0133378510e-03, -7.2813183070e-03, -2.7475596870e-03,\
 2.4554035630e-03,  5.3903660740e-03,  4.8805172560e-03,  1.8349840540e-03,\
-1.6261441630e-03, -3.5522116810e-03, -3.1960245690e-03, -1.1943303980e-03,\
 1.0463795620e-03,  2.2691879420e-03,  2.0240161100e-03,  7.5010029830e-04,\
-6.4770405880e-04, -1.3913452860e-03, -1.2273221510e-03, -4.5005651190e-04,\
 3.8161687550e-04,  8.1000913630e-04,  7.0462777510e-04,  2.5497740720e-04,\
-2.1128321530e-04, -4.4174649520e-04, -3.7753640210e-04, -1.3433356070e-04,\
 1.0800584280e-04,  2.2145068210e-04,  1.8490898950e-04,  6.4349056630e-05,\
-4.9611899160e-05, -9.9044016680e-05, -8.0040139440e-05, -2.6992138370e-05,\
 1.9508090190e-05,  3.7397850970e-05,  2.8685428330e-05,  9.1910196720e-06,\
-5.8855544010e-06, -1.0349400330e-05, -8.4154989960e-06, -5.0361973080e-07,}


/* 255th order LPF co-efficients for FIR_f32 module*/
#define FIR_F32_LPF256 {\
-1.8082486900e-10, -8.3152790210e-10, -1.3506141760e-09, -8.0812773140e-10,\
 1.8871173510e-09,  6.1408687020e-09,  8.7328073660e-09,  4.6682653300e-09,\
-8.8180964750e-09, -2.7041595630e-08, -3.5969922150e-08, -1.8527675390e-08,\
 3.0848244850e-08,  9.1680234960e-08,  1.1723442840e-07,  5.8974940490e-08,\
-9.0449574940e-08, -2.6313000490e-07, -3.2726495650e-07, -1.6173993340e-07,\
 2.3401274520e-07,  6.6967595560e-07,  8.1537734790e-07,  3.9725074430e-07,\
-5.5003812350e-07, -1.5530424660e-06, -1.8587631980e-06, -8.9475622640e-07,\
 1.1966824330e-06,  3.3405972320e-06,  3.9412771000e-06,  1.8776036090e-06,\
-2.4412147470e-06, -6.7477158150e-06, -7.8638231570e-06, -3.7121740210e-06,\
 4.7137141340e-06,  1.2915747900e-05,  1.4891493270e-05,  6.9724947020e-06,\
-8.6767022370e-06, -2.3589276680e-05, -2.6940600950e-05, -1.2521628380e-05,\
 1.5311356040e-05,  4.1333612900e-05,  4.6805835150e-05,  2.1609650500e-05,\
-2.6019530200e-05, -6.9790003180e-05, -7.8424149250e-05, -3.5986544390e-05,\
 4.2739371570e-05,  1.1396245830e-04,  1.2716864880e-04,  5.8026955230e-05,\
-6.8070999990e-05, -1.8052752420e-04, -2.0016334020e-04, -9.0863082730e-05,\
 1.0540846420e-04,  2.7815802600e-04,  3.0661071650e-04,  1.3852263510e-04,\
-1.5907530910e-04, -4.1785626670e-04, -4.5812921600e-04, -2.0607188340e-04,\
 2.3446521660e-04,  6.1330373860e-04,  6.6911266190e-04,  2.9977058880e-04,\
-3.3819739470e-04, -8.8125746700e-04, -9.5714943020e-04, -4.2725869570e-04,\
 4.7831103440e-04,  1.2420648710e-03,  1.3435874130e-03,  5.9781654270e-04,\
-6.6454982150e-04, -1.7204389440e-03, -1.8544123740e-03, -8.2278024640e-04,\
 9.0883136730e-04,  2.3467652500e-03,  2.5217537770e-03,  1.1162633310e-03,\
-1.2260798830e-03, -3.1594373290e-03, -3.3866043670e-03, -1.4964704170e-03,\
 1.6357579730e-03,  4.2091854850e-03,  4.5038890090e-03,  1.9881615880e-03,\
-2.1647673570e-03, -5.5673290040e-03, -5.9522208760e-03, -2.6274400300e-03,\
 2.8531441930e-03,  7.3421779090e-03,  7.8535396610e-03,  3.4715342340e-03,\
-3.7658882790e-03, -9.7137158740e-03, -1.0415488850e-02, -4.6203802340e-03,\
 5.0196954980e-03,  1.3014130290e-02,  1.4032759700e-02,  6.2699439000e-03,\
-6.8514184090e-03, -1.7942406240e-02, -1.9569339230e-02, -8.8682193310e-03,\
 9.8296413200e-03,  2.6269955560e-02,  2.9354233290e-02,  1.3711811970e-02,\
-1.5743294730e-02, -4.4151373210e-02, -5.2521537990e-02, -2.6723828170e-02,\
 3.4582778810e-02,  1.1721494790e-01,  1.9578456880e-01,  2.4356070160e-01,\
 2.4356070160e-01,  1.9578456880e-01,  1.1721494790e-01,  3.4582778810e-02,\
-2.6723828170e-02, -5.2521537990e-02, -4.4151373210e-02, -1.5743294730e-02,\
 1.3711811970e-02,  2.9354233290e-02,  2.6269955560e-02,  9.8296413200e-03,\
-8.8682193310e-03, -1.9569339230e-02, -1.7942406240e-02, -6.8514184090e-03,\
 6.2699439000e-03,  1.4032759700e-02,  1.3014130290e-02,  5.0196954980e-03,\
-4.6203802340e-03, -1.0415488850e-02, -9.7137158740e-03, -3.7658882790e-03,\
 3.4715342340e-03,  7.8535396610e-03,  7.3421779090e-03,  2.8531441930e-03,\
-2.6274400300e-03, -5.9522208760e-03, -5.5673290040e-03, -2.1647673570e-03,\
 1.9881615880e-03,  4.5038890090e-03,  4.2091854850e-03,  1.6357579730e-03,\
-1.4964704170e-03, -3.3866043670e-03, -3.1594373290e-03, -1.2260798830e-03,\
 1.1162633310e-03,  2.5217537770e-03,  2.3467652500e-03,  9.0883136730e-04,\
-8.2278024640e-04, -1.8544123740e-03, -1.7204389440e-03, -6.6454982150e-04,\
 5.9781654270e-04,  1.3435874130e-03,  1.2420648710e-03,  4.7831103440e-04,\
-4.2725869570e-04, -9.5714943020e-04, -8.8125746700e-04, -3.3819739470e-04,\
 2.9977058880e-04,  6.6911266190e-04,  6.1330373860e-04,  2.3446521660e-04,\
-2.0607188340e-04, -4.5812921600e-04, -4.1785626670e-04, -1.5907530910e-04,\
 1.3852263510e-04,  3.0661071650e-04,  2.7815802600e-04,  1.0540846420e-04,\
-9.0863082730e-05, -2.0016334020e-04, -1.8052752420e-04, -6.8070999990e-05,\
 5.8026955230e-05,  1.2716864880e-04,  1.1396245830e-04,  4.2739371570e-05,\
-3.5986544390e-05, -7.8424149250e-05, -6.9790003180e-05, -2.6019530200e-05,\
 2.1609650500e-05,  4.6805835150e-05,  4.1333612900e-05,  1.5311356040e-05,\
-1.2521628380e-05, -2.6940600950e-05, -2.3589276680e-05, -8.6767022370e-06,\
 6.9724947020e-06,  1.4891493270e-05,  1.2915747900e-05,  4.7137141340e-06,\
-3.7121740210e-06, -7.8638231570e-06, -6.7477158150e-06, -2.4412147470e-06,\
 1.8776036090e-06,  3.9412771000e-06,  3.3405972320e-06,  1.1966824330e-06,\
-8.9475622640e-07, -1.8587631980e-06, -1.5530424660e-06, -5.5003812350e-07,\
 3.9725074430e-07,  8.1537734790e-07,  6.6967595560e-07,  2.3401274520e-07,\
-1.6173993340e-07, -3.2726495650e-07, -2.6313000490e-07, -9.0449574940e-08,\
 5.8974940490e-08,  1.1723442840e-07,  9.1680234960e-08,  3.0848244850e-08,\
-1.8527675390e-08, -3.5969922150e-08, -2.7041595630e-08, -8.8180964750e-09,\
 4.6682653300e-09,  8.7328073660e-09,  6.1408687020e-09,  1.8871173510e-09,\
-8.0812773140e-10, -1.3506141760e-09, -8.3152790210e-10, -1.8082486900e-10,}

/* 511th order LPF co-efficients for FIR_f32 module */  
#define FIR_F32_LPF512 {\
 1.5366772420e-03, -3.1265773580e-04, -3.6620986070e-04, -4.2624506750e-04,\
-4.4552556940e-04, -3.9897102400e-04, -2.8469192330e-04, -1.3570292500e-04,\
 2.4069706800e-06,  7.9712488510e-05,  7.2710259700e-05, -1.4868024660e-05,\
-1.4177299450e-04, -2.5478427410e-04, -2.9924057890e-04, -2.5218218800e-04,\
-1.2210835120e-04,  4.1659779530e-05,  1.7924915300e-04,  2.3195783430e-04,\
 1.8011311480e-04,  3.7679044910e-05, -1.3445687360e-04, -2.6774249270e-04,\
-3.0653100110e-04, -2.2751484360e-04, -5.7254892450e-05,  1.3800534360e-04,\
 2.8112938160e-04,  3.1062896600e-04,  2.1161373300e-04,  1.8231185090e-05,\
-1.9226010770e-04, -3.3563654870e-04, -3.4849866640e-04, -2.2172898750e-04,\
 2.7932469490e-07,  2.2890744730e-04,  3.7270589380e-04,  3.6796150380e-04,\
 2.1264099630e-04, -3.7077930760e-05, -2.8113074950e-04, -4.2070497880e-04,\
-3.9395567730e-04, -2.0592521470e-04,  7.3972150860e-05,  3.3257255560e-04,\
 4.6583957740e-04,  4.1263317690e-04,  1.8979668680e-04, -1.1986734900e-04,\
-3.9100673170e-04, -5.1343539960e-04, -4.2979631690e-04, -1.6876660810e-04,\
 1.7138499240e-04,  4.5271177080e-04,  5.6021841010e-04,  4.4198546680e-04,\
 1.4018993530e-04, -2.3033772600e-04, -5.1894830540e-04, -6.0684431810e-04,\
-4.4935729240e-04, -1.0411562110e-04,  2.9655016260e-04,  5.8866286420e-04,\
 6.5199035450e-04,  4.5066923490e-04,  5.9798207080e-05, -3.6953037490e-04,\
-6.6156755200e-04, -6.9465278650e-04, -4.4477239130e-04, -6.3375955510e-06,\
 4.5007374140e-04,  7.3712284210e-04,  7.3416862870e-04,  4.3105075020e-04,\
-5.6564036640e-05, -5.3784198830e-04, -8.1455742470e-04, -7.6929130590e-04,\
-4.0825316680e-04,  1.2961155150e-04,  6.3281517940e-04,  8.9326506710e-04,\
 7.9925509640e-04,  3.7598676860e-04, -2.1290653970e-04, -7.3432800130e-04,\
-9.7221042960e-04, -8.2261161880e-04, -3.3266886020e-04,  3.0701310610e-04,\
 8.4233056990e-04,  1.0504223170e-03,  8.3821109730e-04,  2.7747399870e-04,\
-4.1250794310e-04, -9.5653929750e-04, -1.1270459510e-03, -8.4495125340e-04,\
-2.0962757120e-04,  5.2942964250e-04,  1.0762673340e-03,  1.2009154310e-03,\
 8.4150978360e-04,  1.2817145030e-04, -6.5805349730e-04, -1.2008317280e-03,\
-1.2705730040e-03, -8.2637293960e-04, -3.1932711860e-05,  7.9840136460e-04,\
 1.3294470260e-03,  1.3346933990e-03,  7.9796451610e-04, -8.0058598540e-05,\
-9.5078087180e-04, -1.4613348760e-03, -1.3918422630e-03, -7.5490417660e-04,\
 2.0869511350e-04,  1.1151914950e-03,  1.5956527790e-03,  1.4406156260e-03,\
 6.9581362190e-04, -3.5465223480e-04, -1.2911494120e-03, -1.7308398380e-03,\
-1.4787906550e-03, -6.1864202140e-04,  5.1931728380e-04,  1.4789485140e-03,\
 1.8661186330e-03,  1.5050419610e-03,  5.2186945690e-04, -7.0338562360e-04,\
-1.6781854210e-03, -2.0000112710e-03, -1.5172283170e-03, -4.0362530850e-04,\
 9.0798485330e-04,  1.8887098410e-03,  2.1311144810e-03,  1.5132231640e-03,\
 2.6191581860e-04, -1.1341570640e-03, -2.1101837050e-03, -2.2578192870e-03,\
-1.4906791040e-03, -9.4481023550e-05,  1.3832362600e-03,  2.3425191180e-03,\
 2.3784984370e-03,  1.4471571190e-03, -1.0111072330e-04, -1.6565744300e-03,\
-2.5854052510e-03, -2.4914005770e-03, -1.3798897850e-03,  3.2744588680e-04,\
 1.9556165210e-03,  2.8384041510e-03,  2.5941035710e-03,  1.2852711370e-03,\
-5.8819074180e-04, -2.2828623190e-03, -3.1020359600e-03, -2.6849620040e-03,\
-1.1601699520e-03,  8.8669196700e-04,  2.6403584050e-03,  3.3760208170e-03,\
 2.7611323170e-03,  1.0000101760e-03, -1.2277270430e-03, -3.0313828030e-03,\
-3.6606837530e-03, -2.8197497600e-03, -7.9937669220e-04,  1.6173768090e-03,\
 3.4603935200e-03,  3.9571449160e-03,  2.8578261840e-03,  5.5213773160e-04,\
-2.0628105850e-03, -3.9327945560e-03, -4.2666057120e-03, -2.8713194190e-03,\
-2.4997862060e-04,  2.5738363620e-03,  4.4562169350e-03,  4.5912321660e-03,\
 2.8554275630e-03, -1.1789538980e-04, -3.1636881180e-03, -5.0414353610e-03,\
-4.9346401360e-03, -2.8042627960e-03,  5.6577468060e-04,  3.8504342080e-03,\
 5.7033216580e-03,  5.3020534110e-03,  2.7096574190e-03, -1.1139704150e-03,\
-4.6601528300e-03, -6.4639919440e-03, -5.7018222290e-03, -2.5605142580e-03,\
 1.7917327350e-03,  5.6312237870e-03,  7.3566329670e-03,  6.1470652000e-03,\
 2.3406527470e-03, -2.6433386370e-03, -6.8227876910e-03, -8.4331352260e-03,\
-6.6588716580e-03, -2.0248284560e-03,  3.7395444230e-03,  8.3309244360e-03,\
 9.7791804000e-03,  7.2730388490e-03,  1.5712674940e-03, -5.2008908240e-03,\
-1.0322242040e-02, -1.1546259750e-02, -8.0544976520e-03, -9.0471399020e-04,\
 7.2504994460e-03,  1.3112223710e-02,  1.4027953150e-02,  9.1326814140e-03,\
-1.2672258890e-04, -1.0352934710e-02, -1.7377879470e-02, -1.7874922600e-02,\
-1.0804970750e-02,  1.8844022420e-03,  1.5662357210e-02,  2.4881962690e-02,\
 2.4872578680e-02,  1.3937847690e-02, -5.4891151380e-03, -2.7049291880e-02,\
-4.2090248320e-02, -4.2302932590e-02, -2.2550765420e-02,  1.7043987290e-02,\
 7.0507064460e-02,  1.2720665340e-01,  1.7456042770e-01,  2.0147448780e-01,\
 2.0147448780e-01,  1.7456042770e-01,  1.2720665340e-01,  7.0507064460e-02,\
 1.7043987290e-02, -2.2550765420e-02, -4.2302932590e-02, -4.2090248320e-02,\
-2.7049291880e-02, -5.4891151380e-03,  1.3937847690e-02,  2.4872578680e-02,\
 2.4881962690e-02,  1.5662357210e-02,  1.8844022420e-03, -1.0804970750e-02,\
-1.7874922600e-02, -1.7377879470e-02, -1.0352934710e-02, -1.2672258890e-04,\
 9.1326814140e-03,  1.4027953150e-02,  1.3112223710e-02,  7.2504994460e-03,\
-9.0471399020e-04, -8.0544976520e-03, -1.1546259750e-02, -1.0322242040e-02,\
-5.2008908240e-03,  1.5712674940e-03,  7.2730388490e-03,  9.7791804000e-03,\
 8.3309244360e-03,  3.7395444230e-03, -2.0248284560e-03, -6.6588716580e-03,\
-8.4331352260e-03, -6.8227876910e-03, -2.6433386370e-03,  2.3406527470e-03,\
 6.1470652000e-03,  7.3566329670e-03,  5.6312237870e-03,  1.7917327350e-03,\
-2.5605142580e-03, -5.7018222290e-03, -6.4639919440e-03, -4.6601528300e-03,\
-1.1139704150e-03,  2.7096574190e-03,  5.3020534110e-03,  5.7033216580e-03,\
 3.8504342080e-03,  5.6577468060e-04, -2.8042627960e-03, -4.9346401360e-03,\
-5.0414353610e-03, -3.1636881180e-03, -1.1789538980e-04,  2.8554275630e-03,\
 4.5912321660e-03,  4.4562169350e-03,  2.5738363620e-03, -2.4997862060e-04,\
-2.8713194190e-03, -4.2666057120e-03, -3.9327945560e-03, -2.0628105850e-03,\
 5.5213773160e-04,  2.8578261840e-03,  3.9571449160e-03,  3.4603935200e-03,\
 1.6173768090e-03, -7.9937669220e-04, -2.8197497600e-03, -3.6606837530e-03,\
-3.0313828030e-03, -1.2277270430e-03,  1.0000101760e-03,  2.7611323170e-03,\
 3.3760208170e-03,  2.6403584050e-03,  8.8669196700e-04, -1.1601699520e-03,\
-2.6849620040e-03, -3.1020359600e-03, -2.2828623190e-03, -5.8819074180e-04,\
 1.2852711370e-03,  2.5941035710e-03,  2.8384041510e-03,  1.9556165210e-03,\
 3.2744588680e-04, -1.3798897850e-03, -2.4914005770e-03, -2.5854052510e-03,\
-1.6565744300e-03, -1.0111072330e-04,  1.4471571190e-03,  2.3784984370e-03,\
 2.3425191180e-03,  1.3832362600e-03, -9.4481023550e-05, -1.4906791040e-03,\
-2.2578192870e-03, -2.1101837050e-03, -1.1341570640e-03,  2.6191581860e-04,\
 1.5132231640e-03,  2.1311144810e-03,  1.8887098410e-03,  9.0798485330e-04,\
-4.0362530850e-04, -1.5172283170e-03, -2.0000112710e-03, -1.6781854210e-03,\
-7.0338562360e-04,  5.2186945690e-04,  1.5050419610e-03,  1.8661186330e-03,\
 1.4789485140e-03,  5.1931728380e-04, -6.1864202140e-04, -1.4787906550e-03,\
-1.7308398380e-03, -1.2911494120e-03, -3.5465223480e-04,  6.9581362190e-04,\
 1.4406156260e-03,  1.5956527790e-03,  1.1151914950e-03,  2.0869511350e-04,\
-7.5490417660e-04, -1.3918422630e-03, -1.4613348760e-03, -9.5078087180e-04,\
-8.0058598540e-05,  7.9796451610e-04,  1.3346933990e-03,  1.3294470260e-03,\
 7.9840136460e-04, -3.1932711860e-05, -8.2637293960e-04, -1.2705730040e-03,\
-1.2008317280e-03, -6.5805349730e-04,  1.2817145030e-04,  8.4150978360e-04,\
 1.2009154310e-03,  1.0762673340e-03,  5.2942964250e-04, -2.0962757120e-04,\
-8.4495125340e-04, -1.1270459510e-03, -9.5653929750e-04, -4.1250794310e-04,\
 2.7747399870e-04,  8.3821109730e-04,  1.0504223170e-03,  8.4233056990e-04,\
 3.0701310610e-04, -3.3266886020e-04, -8.2261161880e-04, -9.7221042960e-04,\
-7.3432800130e-04, -2.1290653970e-04,  3.7598676860e-04,  7.9925509640e-04,\
 8.9326506710e-04,  6.3281517940e-04,  1.2961155150e-04, -4.0825316680e-04,\
-7.6929130590e-04, -8.1455742470e-04, -5.3784198830e-04, -5.6564036640e-05,\
 4.3105075020e-04,  7.3416862870e-04,  7.3712284210e-04,  4.5007374140e-04,\
-6.3375955510e-06, -4.4477239130e-04, -6.9465278650e-04, -6.6156755200e-04,\
-3.6953037490e-04,  5.9798207080e-05,  4.5066923490e-04,  6.5199035450e-04,\
 5.8866286420e-04,  2.9655016260e-04, -1.0411562110e-04, -4.4935729240e-04,\
-6.0684431810e-04, -5.1894830540e-04, -2.3033772600e-04,  1.4018993530e-04,\
 4.4198546680e-04,  5.6021841010e-04,  4.5271177080e-04,  1.7138499240e-04,\
-1.6876660810e-04, -4.2979631690e-04, -5.1343539960e-04, -3.9100673170e-04,\
-1.1986734900e-04,  1.8979668680e-04,  4.1263317690e-04,  4.6583957740e-04,\
 3.3257255560e-04,  7.3972150860e-05, -2.0592521470e-04, -3.9395567730e-04,\
-4.2070497880e-04, -2.8113074950e-04, -3.7077930760e-05,  2.1264099630e-04,\
 3.6796150380e-04,  3.7270589380e-04,  2.2890744730e-04,  2.7932469490e-07,\
-2.2172898750e-04, -3.4849866640e-04, -3.3563654870e-04, -1.9226010770e-04,\
 1.8231185090e-05,  2.1161373300e-04,  3.1062896600e-04,  2.8112938160e-04,\
 1.3800534360e-04, -5.7254892450e-05, -2.2751484360e-04, -3.0653100110e-04,\
-2.6774249270e-04, -1.3445687360e-04,  3.7679044910e-05,  1.8011311480e-04,\
 2.3195783430e-04,  1.7924915300e-04,  4.1659779530e-05, -1.2210835120e-04,\
-2.5218218800e-04, -2.9924057890e-04, -2.5478427410e-04, -1.4177299450e-04,\
-1.4868024660e-05,  7.2710259700e-05,  7.9712488510e-05,  2.4069706800e-06,\
-1.3570292500e-04, -2.8469192330e-04, -3.9897102400e-04, -4.4552556940e-04,\
-4.2624506750e-04, -3.6620986070e-04, -3.1265773580e-04,  1.5366772420e-03,}

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_FILTER_H_

// End of File
