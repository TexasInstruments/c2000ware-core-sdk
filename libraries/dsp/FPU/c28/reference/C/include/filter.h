#ifndef _FILTER_H_
#define _FILTER_H_
//#############################################################################
//! \file   reference/C/include/$FILENAME$
//! \brief  The Filter Module Header File
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
#include "dsp_assert.h"
#include "dsp.h"

//!
//! \defgroup DSP_FILTER The Filter Module

//! 
//! \ingroup DSP_FILTER
//@{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************


//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief a function pointer with a void pointer argument returning nothing
//!
typedef void (*v_pfn_v)(void *);

//! \brief the FIR filter structure
//!
typedef struct _FIR{
    uint16_t nTaps;        //!< Number of filter taps
    uint16_t order;        //!< Order of the filter (nTaps - 1)
    fsize_t input;         //!< The input to the filter
    fsize_t output;        //!< The output from the filter
    fsize_t *delayLine;    //!< Pointer to the delay line
    fsize_t *coefficients; //!< Pointer to the coefficients
    v_pfn_v run;           //!< Pointer to the function that implements an FIR
}FIR;

//! \brief Handle (pointer) type for the FIR Object
//!
typedef FIR *FIRHandle;

//! \brief the IIR filter structure
//!
typedef struct _IIR{
    uint16_t nSOS;         //!< Number of Second Order Stages
    uint16_t order;        //!< Order of the filter (nTaps - 1)
    fsize_t input;         //!< The input to the filter
    fsize_t output;        //!< The output from the filter
    fsize_t *delayLine;    //!< Pointer to the delay line
    fsize_t *coefficients; //!< Pointer to the coefficients
    fsize_t *scaleValues;  //!< Pointer to the scale values
    v_pfn_v run;           //!< Pointer to the function that implements an FIR
}IIR;

//! \brief Handle (pointer) type for the FIR Object
//!
typedef IIR *IIRHandle;
//*****************************************************************************
//globals
//*****************************************************************************

//*****************************************************************************
// 'inline' function
//*****************************************************************************
//! \brief Set the Number of Taps and order of the filter
//! \param[in] fh , handle to the 'FIR' object
//! \param[in] nTaps , Number of Taps
//! The order of the filter is one less than the number of taps
//!
static inline void FIR_setnTaps(FIRHandle fh, const uint16_t nTaps)
{
    fh->nTaps = nTaps;
    //fh->order = nTaps - 1U;
}

//! \brief Get the Number of Taps
//! \param[in] fh , handle to the 'FIR' object
//! \return nTaps , Number of Taps
//!
static inline uint16_t FIR_getnTaps(FIRHandle fh)
{
    return(fh->nTaps);
}

//! \brief Set the order of the filter and number of Taps
//! \param[in] fh , handle to the 'FIR' object
//! \param[in] order , Order of the filter
//! The order of the filter is one less than the number of taps
//!
static inline void FIR_setOrder(FIRHandle fh, const uint16_t order)
{
    fh->order = order;
    //fh->nTaps = order + 1U;
}

//! \brief Get the order of the filter
//! \param[in] fh , handle to the 'FIR' object
//! \return order , Order of the filter
//!
static inline uint16_t FIR_getOrder(FIRHandle fh)
{
    return(fh->order);
}

//! \brief Set the input
//! \param[in] fh , handle to the 'FIR' object
//! \param[in] input , input to the filter
//!
static inline void FIR_setInput(FIRHandle fh, const fsize_t input)
{
    fh->input = input;
}

//! \brief Get the input
//! \param[in] fh , handle to the 'FIR' object
//! \return input , input to the filter
//!
static inline fsize_t FIR_getInput(FIRHandle fh)
{
    return(fh->input);
}

//! \brief Set the output
//! \param[in] fh , handle to the 'FIR' object
//! \param[in] output , output from the filter
//!
static inline void FIR_setOutput(FIRHandle fh, const fsize_t output)
{
    fh->output = output;
}

//! \brief Get the output
//! \param[in] fh , handle to the 'FIR' object
//! \return output , output from the filter
//!
static inline fsize_t FIR_getOutput(FIRHandle fh)
{
    return(fh->output);
}

//! \brief Set the delay line pointer
//! \param[in] fh , handle to the 'FIR' object
//! \param[in] pdl , pointer to the delay line
//!
static inline void FIR_setDelayLinePtr(FIRHandle fh, fsize_t *pdl)
{
    fh->delayLine = pdl;
}

//! \brief Get the delay line pointer
//! \param[in] fh , handle to the 'FIR' object
//! \return pdl , pointer to the delay line
//!
static inline fsize_t * FIR_getDelayLinePtr(FIRHandle fh)
{
    return(fh->delayLine);
}

//! \brief Set the coefficients pointer
//! \param[in] fh , handle to the 'FIR' object
//! \param[in] pc , pointer to the coefficients
//!
static inline void FIR_setCoefficientsPtr(FIRHandle fh, fsize_t *pc)
{
    fh->coefficients = pc;
}

//! \brief Get the coefficients pointer
//! \param[in] fh , handle to the 'FIR' object
//! \return pc , pointer to the coefficients
//!
static inline fsize_t * FIR_getCoefficientsPtr(FIRHandle fh)
{
    return(fh->coefficients);
}

//! \brief Set the run function
//! \param[in] fh , handle to the 'FIR' object
//! \param[in] pfn , pointer to the run function
//!
static inline void FIR_setRunFunction(FIRHandle fh, const v_pfn_v pfn)
{
    fh->run = pfn;
}

//! \brief Get the run function
//! \param[in] fh , handle to the 'FIR' object
//! \return pfn , pointer to the run function
//!
static inline v_pfn_v FIR_getRunFunction(FIRHandle fh)
{
    return(fh->run);
}

//! \brief Set the Number of Second Order Stages (Biquads)
//! \param[in] fh , handle to the 'IIR' object
//! \param[in] nSOS , Number of Second Order Stages (Biquads)
//!
static inline void IIR_setnSOS(IIRHandle fh, const uint16_t nSOS)
{
    fh->nSOS = nSOS;
}

//! \brief Get the Number of Second Order Stages (Biquads)
//! \param[in] fh , handle to the 'IIR' object
//! \return nSOS , Number of Second Order Stages (Biquads)
//!
static inline uint16_t IIR_getnSOS(IIRHandle fh)
{
    return(fh->nSOS);
}

//! \brief Set the order of the filter and number of Taps
//! \param[in] fh , handle to the 'IIR' object
//! \param[in] order , Order of the filter
//!
static inline void IIR_setOrder(IIRHandle fh, const uint16_t order)
{
    fh->order = order;
}

//! \brief Get the order of the filter
//! \param[in] fh , handle to the 'IIR' object
//! \return order , Order of the filter
//!
static inline uint16_t IIR_getOrder(IIRHandle fh)
{
    return(fh->order);
}

//! \brief Set the input
//! \param[in] fh , handle to the 'IIR' object
//! \param[in] input , input to the filter
//!
static inline void IIR_setInput(IIRHandle fh, const fsize_t input)
{
    fh->input = input;
}

//! \brief Get the input
//! \param[in] fh , handle to the 'IIR' object
//! \return input , input to the filter
//!
static inline fsize_t IIR_getInput(IIRHandle fh)
{
    return(fh->input);
}

//! \brief Set the output
//! \param[in] fh , handle to the 'IIR' object
//! \param[in] output , output from the filter
//!
static inline void IIR_setOutput(IIRHandle fh, const fsize_t output)
{
    fh->output = output;
}

//! \brief Get the output
//! \param[in] fh , handle to the 'IIR' object
//! \return output , output from the filter
//!
static inline fsize_t IIR_getOutput(IIRHandle fh)
{
    return(fh->output);
}

//! \brief Set the delay line pointer
//! \param[in] fh , handle to the 'IIR' object
//! \param[in] pdl , pointer to the delay line
//!
static inline void IIR_setDelayLinePtr(IIRHandle fh, fsize_t *pdl)
{
    fh->delayLine = pdl;
}

//! \brief Get the delay line pointer
//! \param[in] fh , handle to the 'IIR' object
//! \return pdl , pointer to the delay line
//!
static inline fsize_t * IIR_getDelayLinePtr(IIRHandle fh)
{
    return(fh->delayLine);
}

//! \brief Set the coefficients pointer
//! \param[in] fh , handle to the 'IIR' object
//! \param[in] pc , pointer to the coefficients
//!
static inline void IIR_setCoefficientsPtr(IIRHandle fh, fsize_t *pc)
{
    fh->coefficients = pc;
}

//! \brief Get the coefficients pointer
//! \param[in] fh , handle to the 'IIR' object
//! \return pc , pointer to the coefficients
//!
static inline fsize_t * IIR_getCoefficientsPtr(IIRHandle fh)
{
    return(fh->coefficients);
}

//! \brief Set the Scale Value pointer
//! \param[in] fh , handle to the 'IIR' object
//! \param[in] ps , pointer to the scaling values
//!
static inline void IIR_setScaleValPtr(IIRHandle fh, fsize_t *ps)
{
    fh->scaleValues = ps;
}

//! \brief Get the Scale Value pointer
//! \param[in] fh , handle to the 'IIR' object
//! \return ps , pointer to the scaling values
//!
static inline fsize_t * IIR_getScaleValPtr(IIRHandle fh)
{
    return(fh->scaleValues);
}

//! \brief Set the run function
//! \param[in] fh , handle to the 'IIR' object
//! \param[in] pfn , pointer to the run function
//!
static inline void IIR_setRunFunction(IIRHandle fh, const v_pfn_v pfn)
{
    fh->run = pfn;
}

//! \brief Get the run function
//! \param[in] fh , handle to the 'IIR' object
//! \return pfn , pointer to the run function
//!
static inline v_pfn_v IIR_getRunFunction(IIRHandle fh)
{
    return(fh->run);
}
//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief Run an FIR filter
//! \param hnd handle to an FIR object
//!
extern void FILTER_runFIR(FIRHandle hnd);
                              
//! \brief Run an IIR filter
//! \param hnd handle to an IIR object
//!
extern void FILTER_runIIR(IIRHandle hnd);
                              

#ifdef __cplusplus
}
#endif //extern "C"

//@} //ingroup

#endif // end of _FILTER_H_ definition
