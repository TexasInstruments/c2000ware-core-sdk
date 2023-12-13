#ifndef _FFT_H_
#define _FFT_H_
//#############################################################################
//! \file   include/fpu64/fpu64_fft.h
//!
//! \brief  Prototypes and Definitions for the DSP Library FFT Module
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
//! \defgroup DSP_FFT_F64 Fast Fourier Transform (Double Precision)

//!
//! \addtogroup DSP_FFT_F64
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

#define TABLE_SIZE      (1024U)
#define TABLE_SIZE_LOG2 (10U)

// Set this to 1 if the input and output buffers to the RFFT magnitude
// operation are the same array. Rebuild each time this macro is changed
#define RFFT_MAG_IN_PLACE (0U)
//*****************************************************************************
// typedefs
//*****************************************************************************
//! Complex FFT structure
//! 
typedef struct {
    float64_t *p_input;       //!< Pointer to the input buffer
    float64_t *p_output;      //!< Pointer to the output buffer
    float64_t *p_twiddles;    //!< Pointer to the twiddle factors
    float64_t *p_currInput;   //!< Points to input buffer at each FFT stage
    float64_t *p_currOutput;  //!< Points to output buffer at each FFT stage
    uint16_t    stages;         //!< Number of FFT stages
    uint16_t    FFTSize;        //!< FFT size (number of complex data points)
    void (*init)(void *);       //!< Pointer to the initialization function
    void (*calc)(void *);       //!< Pointer to the calculation function
    void (*mag)(void *);        //!< Pointer to the magnitude function
    void (*phase)(void *);      //!< Pointer to the phase function
    void (*win)(void *);        //!< Pointer to the windowing function
}CFFT_f64_Struct;

//! Handle to the CFFT structure object
//!
typedef CFFT_f64_Struct  *CFFT_f64_Handle;

//! Structure for the Complex FFT with ADC input
//!
typedef struct {
  uint16_t   *p_input;    //!< Pointer to the input buffer
  void	     *p_tail;     //!< Null pointer to the p_output of CFFT_f64_Struct
} CFFT_ADC_f64_Struct;

//! Handle to the Complex FFT (with ADC input) structure object
//!
typedef CFFT_ADC_f64_Struct* CFFT_ADC_f64_Handle;

//! Re-define CFFT64 structures and functions such that RFFT64 terminology can
//! be used for better clarification
//!
#define RFFT_f64_Struct CFFT_f64_Struct
#define RFFT_ADC_f64_Struct CFFT_ADC_f64_Struct
#define RFFT_f64_Handle CFFT_f64_Handle
#define RFFT_ADC_f64_Handle CFFT_ADC_f64_Handle

#define RFFT_f64_setInputPtr CFFT_f64_setInputPtr
#define RFFT_f64_getInputPtr CFFT_f64_getInputPtr
#define RFFT_f64_setOutputPtr CFFT_f64_setOutputPtr
#define RFFT_f64_getOutputPtr CFFT_f64_getOutputPtr
#define RFFT_f64_setTwiddlesPtr CFFT_f64_setTwiddlesPtr
#define RFFT_f64_getTwiddlesPtr CFFT_f64_getTwiddlesPtr
#define RFFT_f64_setCurrInputPtr CFFT_f64_setCurrInputPtr
#define RFFT_f64_getCurrInputPtr CFFT_f64_getCurrInputPtr
#define RFFT_f64_setCurrOutputPtr CFFT_f64_setCurrOutputPtr
#define RFFT_f64_getCurrOutputPtr CFFT_f64_getCurrOutputPtr
#define RFFT_f64_setStages CFFT_f64_setStages
#define RFFT_f64_getStages CFFT_f64_getStages
#define RFFT_f64_setFFTSize CFFT_f64_setFFTSize
#define RFFT_f64_getFFTSize CFFT_f64_getFFTSize
#define RFFT_f64_setInitFunction CFFT_f64_setInitFunction
#define RFFT_f64_getInitFunction CFFT_f64_getInitFunction
#define RFFT_f64_setCalcFunction CFFT_f64_setCalcFunction
#define RFFT_f64_getCalcFunction CFFT_f64_getCalcFunction
#define RFFT_f64_setMagFunction CFFT_f64_setMagFunction
#define RFFT_f64_getMagFunction CFFT_f64_getMagFunction
#define RFFT_f64_setPhaseFunction CFFT_f64_setPhaseFunction
#define RFFT_f64_getPhaseFunction CFFT_f64_getPhaseFunction
#define RFFT_f64_setWinFunction CFFT_f64_setWinFunction
#define RFFT_f64_getWinFunction CFFT_f64_getWinFunction
#define RFFT_ADC_f64_setInBufPtr CFFT_ADC_f64_setInBufPtr
#define RFFT_ADC_f64_getInBufPtr CFFT_ADC_f64_getInBufPtr
#define RFFT_ADC_f64_setTailPtr CFFT_ADC_f64_setTailPtr
#define RFFT_ADC_f64_getTailPtr CFFT_ADC_f64_getTailPtr

//*****************************************************************************
// globals
//*****************************************************************************
//! Complex FFT Twiddle Factor Table
//! 
extern float64_t FPU64CFFTtwiddleFactors[768];
extern float64_t FPU64RFFTtwiddleFactors[1020];
//*****************************************************************************
// 'inline' function
//*****************************************************************************

//! \brief Set the input buffer pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] pi , pointer to the input buffer
//!
static inline void CFFT_f64_setInputPtr(CFFT_f64_Handle fh,
        const float64_t *pi)
{
    fh->p_input = (float64_t *)pi;
}

//! \brief Get the input buffer pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return pi , pointer to the input buffer
//!
static inline float64_t * CFFT_f64_getInputPtr(CFFT_f64_Handle fh)
{
    return(fh->p_input);
}

//! \brief Set the output buffer pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] po , pointer to the output buffer
//!
static inline void CFFT_f64_setOutputPtr(CFFT_f64_Handle fh,
        const float64_t *po)
{
    fh->p_output = (float64_t *)po;
}

//! \brief Get the output buffer pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return po , pointer to the output buffer
//!
static inline float64_t * CFFT_f64_getOutputPtr(CFFT_f64_Handle fh)
{
    return(fh->p_output);
}

//! \brief Set the twiddles pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] pt , pointer to the twiddles
//!
static inline void CFFT_f64_setTwiddlesPtr(CFFT_f64_Handle fh,
        const float64_t *pc)
{
    fh->p_twiddles = (float64_t *)pc;
}

//! \brief Get the twiddles pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return pt , pointer to the twiddles
//!
static inline float64_t * CFFT_f64_getTwiddlesPtr(CFFT_f64_Handle fh)
{
    return(fh->p_twiddles);
}

//! \brief Set the current input buffer pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] pi , pointer to the current input buffer
//!
static inline void CFFT_f64_setCurrInputPtr(CFFT_f64_Handle fh,
        const float64_t *pi)
{
    fh->p_currInput = (float64_t *)pi;
}


//! \brief Get the current input buffer pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return pi , pointer to the current input buffer
//!
static inline float64_t * CFFT_f64_getCurrInputPtr(CFFT_f64_Handle fh)
{
    return(fh->p_currInput);
}

//! \brief Set the current output buffer pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] po , pointer to the current output buffer
//!
static inline void CFFT_f64_setCurrOutputPtr(CFFT_f64_Handle fh,
        const float64_t *po)
{
    fh->p_currOutput = (float64_t *)po;
}

//! \brief Get the current output buffer pointer
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return po , pointer to the current output buffer
//!
static inline float64_t * CFFT_f64_getCurrOutputPtr(CFFT_f64_Handle fh)
{
    return(fh->p_currOutput);
}

//! \brief Set the number of FFT stages
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] st , number of FFT stages
//!
static inline void CFFT_f64_setStages(CFFT_f64_Handle fh, 
                      const uint16_t st)
{
    fh->stages = st;
}

//! \brief Get the size of the FFT
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return st , number of FFT stages
//!
static inline uint16_t CFFT_f64_getStages(CFFT_f64_Handle fh)
{
    return(fh->stages);
}

//! \brief Set the number of FFT stages
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] sz , size of the FFT
//!
static inline void CFFT_f64_setFFTSize(CFFT_f64_Handle fh, 
                      const uint16_t sz)
{
    fh->FFTSize = sz;
}

//! \brief Get the size of the FFT
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return sz , size of the FFT
//!
static inline uint16_t CFFT_f64_getFFTSize(CFFT_f64_Handle fh)
{
    return(fh->FFTSize);
}

//! \brief Set the initialization function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] pfn , pointer to the initialization function
//!
static inline void CFFT_f64_setInitFunction(CFFT_f64_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->init = pfn;
}

//! \brief Get the initialization function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return pfn , pointer to the initialization function
//!
static inline v_pfn_v CFFT_f64_getInitFunction(CFFT_f64_Handle fh)
{
    return(fh->init);
}

//! \brief Set the calculation function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] pfn , pointer to the calculation function
//!
static inline void CFFT_f64_setCalcFunction(CFFT_f64_Handle fh, 
                    const v_pfn_v pfn)
{
    fh->calc = pfn;
}

//! \brief Get the calculation function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return pfn , pointer to the calculation function
//!
static inline v_pfn_v CFFT_f64_getCalcFunction(CFFT_f64_Handle fh)
{
    return(fh->calc);
}

//! \brief Set the magnitude function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] pfn , pointer to the magnitude function
//!
static inline void CFFT_f64_setMagFunction(CFFT_f64_Handle fh,
                    const v_pfn_v pfn)
{
    fh->mag = pfn;
}

//! \brief Get the magnitude function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return pfn , pointer to the magnitude function
//!
static inline v_pfn_v CFFT_f64_getMagFunction(CFFT_f64_Handle fh)
{
    return(fh->mag);
}

//! \brief Set the phase function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] pfn , pointer to the phase function
//!
static inline void CFFT_f64_setPhaseFunction(CFFT_f64_Handle fh,
                    const v_pfn_v pfn)
{
    fh->phase = pfn;
}

//! \brief Get the phase function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return pfn , pointer to the phase function
//!
static inline v_pfn_v CFFT_f64_getPhaseFunction(CFFT_f64_Handle fh)
{
    return(fh->phase);
}

//! \brief Set the windowing function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \param[in] pfn , pointer to the windowing function
//!
static inline void CFFT_f64_setWinFunction(CFFT_f64_Handle fh,
                    const v_pfn_v pfn)
{
    fh->win = pfn;
}

//! \brief Get the windowing function
//! \param[in] fh , handle to the 'CFFT_f64_Struct' object
//! \return pfn , pointer to the windowing function
//!
static inline v_pfn_v CFFT_f64_getWinFunction(CFFT_f64_Handle fh)
{
    return(fh->win);
}


//! \brief Set the input buffer pointer
//! \param[in] fh  handle to the 'CFFT_ADC_f64_Struct' object
//! \param[in] pi  pointer to the input buffer
//!
static inline void CFFT_ADC_f64_setInBufPtr(CFFT_ADC_f64_Handle fh,
                      const uint16_t * pi)
{
    fh->p_input = (uint16_t *)pi;
}

//! \brief get the input buffer pointer
//! \param[in] fh  handle to the 'CFFT_ADC_f64_Struct' object
//! \return    pi  pointer to the input buffer
//!
static inline uint16_t *CFFT_ADC_f64_getInBufPtr(CFFT_ADC_f64_Handle fh)
{
    return(fh->p_input);
}

//! \brief Set the tail pointer
//! \param[in] fh  handle to the 'CFFT_ADC_f64_Struct' object
//! \param[in] pt  pointer to the tail
//!
static inline void CFFT_ADC_f64_setTailPtr(CFFT_ADC_f64_Handle fh,
                      const void * pt)
{
    fh->p_tail = (void *)pt;
}

//! \brief Get the tail pointer
//! \param[in] fh  handle to the 'CFFT_ADC_f64_Struct' object
//! \return    pt  pointer to the tail
//!
static inline void *CFFT_ADC_f64_getTailPtr(CFFT_ADC_f64_Handle fh)
{
    return(fh->p_tail);
}

//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief Complex Fast Fourier Transform.
//! 
//! This routine computes the 64-bit double precision FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. This function reorders
//! the input in bit-reversed format during the stage 1, 2 calculations. The
//! routine uses two buffers in ping-pong fashion i.e. after each FFT stage
//! the output and input buffers become the input and output buffers 
//! respectively for the next stage. The CFFT_f64_Struct object uses two  
//! pointers, CurrentInPtr and CurrentOutPtr to keep track of the switching. 
//! The user can determine the address of the final output by looking at the 
//! CurrentInPtr.
//! \param hndCFFT_F64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N
//! and type float64_t (64-bit), for computation; the input buffer must be
//! aligned to a memory address of 8N words (16-bit). Refer to the CFFT linker
//! command file to see an example of this.
//! -# If alignment is not possible the user can use the alternative, albeit 
//! slower, function CFFT_f64u
//! \attention The maximum size of this complex FFT is 4096
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 3805
//! <tr><td> 128     <td> 8649
//! <tr><td> 256     <td> 19571
//! <tr><td> 512     <td> 43935
//! <tr><td> 1024    <td> 98683
//! </table>
//
extern void CFFT_f64(CFFT_f64_Handle hndCFFT_f64);


//! \brief Complex Fast Fourier Transform (Unaligned).
//! 
//! This routine computes the 64-bit double precision FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. This function reorders
//! the input in bit-reversed format during the stage 1, 2 calculations. The
//! routine uses two buffers in ping-pong fashion i.e. after each FFT stage
//! the output and input buffers become the input and output buffers 
//! respectively for the next stage. The CFFT_f64_Struct object uses two pointers, 
//! CurrentInPtr and CurrentOutPtr to keep track of the switching. The user 
//! can determine the address of the final output by looking at the 
//! CurrentInPtr.
//! \param hndCFFT_F64 Pointer to the CFFT_f64_Struct object
//! \attention
//! The routine requires the use of two buffers, each of size 2N
//! and type float64_t (64-bit), for computation; the input buffer need not
//! be aligned.
//! -# If alignment is possible the user can use the alternative faster 
//! function CFFT_f64
//! \attention The maximum size of this complex FFT is 4096
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 4107
//! <tr><td> 128     <td> 9254
//! <tr><td> 256     <td> 20783
//! <tr><td> 512     <td> 46362
//! <tr><td> 1024    <td> 102648
//! </table>
//
extern void CFFT_f64u(CFFT_f64_Handle hndCFFT_f64);

//! \brief Complex FFT Magnitude.
//!
//! This module computes the complex FFT magnitude. The output from
//! CFFT_f64_mag matches the magnitude output from the FFT found in common
//! mathematics software and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the CFFT_f64s_mag function
//! can be used. In fixed-point algorithms scaling is performed to avoid
//! overflowing data.
//! Floating-point calculations do not need this scaling to avoid overflow and
//! therefore the CFFT_f64_mag function can be used instead.
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 2696
//! <tr><td> 128     <td> 5288
//! <tr><td> 256     <td> 10470
//! <tr><td> 512     <td> 20838
//! <tr><td> 1024    <td> 41574
//! </table>
//
extern void CFFT_f64_mag(CFFT_f64_Handle hndCFFT_f64);

//! \brief Complex FFT Magnitude (Scaled).
//!
//! This module computes the scaled complex FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the normalization
//! performed by the fixed-point TMS320C28x IQmath FFT library for overflow
//! avoidance. Floating-point calculations do not need this scaling to avoid
//! overflow and therefore the CFFT_f64_mag function can be used instead. The
//! output from CFFT_f64_s_mag matches the magnitude output from the FFT found
//! in common mathematics software and Code Composer Studio FFT graphs.
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 2771
//! <tr><td> 128     <td> 5427
//! <tr><td> 256     <td> 10738
//! <tr><td> 512     <td> 21362
//! <tr><td> 1024    <td> 42610
//! </table>
//
extern void CFFT_f64s_mag(CFFT_f64_Handle hndCFFT_f64);

//! \brief Complex FFT Phase.
//!
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# The phase function calls the atan2 function in the runtime-support
//! library. The phase function has not been optimized at this time.
//! -# The use of the atan2 function in the FPU fast RTS library will speed up
//! this routine.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles (fastRTS) <th> Cycles (RTS)
//! <tr><td> 64      <td> 6359             <td> N/A
//! <tr><td> 128     <td> 12695            <td> N/A
//! <tr><td> 256     <td> 25367            <td> N/A
//! <tr><td> 512     <td> 50709            <td> N/A
//! <tr><td> 1024    <td> 101397           <td> N/A
//! </table>
//
extern void CFFT_f64_phase(CFFT_f64_Handle hndCFFT_f64);

//!
//! \brief Unpack the N-point complex FFT output to get the FFT of a 2N point
//!         real sequence
//!
//! In order to get the FFT of a real N-point sequence, we treat the input as
//! an N/2-point complex sequence, take its complex FFT, use the following 
//! properties to get the N-pt Fourier transform of the real sequence
//! 
//! \f[FFT_{n}(k,f) = FFT_{N/2}(k,f_{e})+e^{\frac{-j2{\pi}k}{N}}FFT_{N/2}(k,f_{o})\f]
//! 
//! where \f$f_{e}\f$ is the even elements, \f$f_{o}\f$ the odd elements, 
//! k = 0 to \f$\frac{N}{2}-1\f$ and
//! 
//! \f[ F_{e}(k) = \frac{Z(k) + Z(\frac{N}{2}-k)^{\ast}}{2} \f]
//! \f[ F_{o}(k) = -j\frac{Z(k) - Z(\frac{N}{2}-k)^{\ast}}{2} \f]
//! 
//! We get the first N/2 points of the FFT by combining the above two equations
//! \f[ F(k) = F_{e}(k) + e^{\frac{-j2{\pi}k}{N}}F_{o}(k) \f]
//!
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \note 
//! -# The unpack routine yields the spectrum of the real input data; the 
//!    spectrum has a real part that is symmetric, and an imaginary part that 
//!    is antisymmetric about the nyquist frequency. We only need calculate 
//!    half the spectrum, up to the nyquist bin, while the latter half can be 
//!    derived from the first half using the conjugate symmetry properties of 
//!    the spectrum
//! -# The output is written to the buffer pointer to by p_currOutput
//! \sa http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM for 
//! the entire derivation
//! \sa \ref SSEC_RFFT_F64_USING_CFFT_F64
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 756
//! <tr><td> 128     <td> 1460
//! <tr><td> 256     <td> 2868
//! <tr><td> 512     <td> 5683
//! <tr><td> 1024    <td> 11315
//! </table>
//
extern void CFFT_f64_unpack(CFFT_f64_Handle hndCFFT_f64);

//!
//! \brief Pack the N/2-point complex FFT output to get the spectrum of an
//!        N-point real sequence
//!
//! In order to reverse the process of the forward real FFT,
//!
//! \f[ F_{e}(k) = \frac{F(k) + F(\frac{N}{2}-k)^{\ast}}{2} \f]
//! \f[ F_{o}(k) = \frac{F(k) - F(\frac{N}{2}-k)^{\ast}}{2} e^{\frac{j2{\pi}k}{N}} \f]
//!
//! where \f$f_{e}\f$ is the even elements, \f$f_{o}\f$ the odd elements, and
//! k = 0 to \f$\frac{N}{2}-1\f$. The array for the IFFT then becomes:
//! \f[ Z(k) = F_{e}(k) + jF_{o}(k), \ k = 0...\frac{N}{2}-1 \f]
//!
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \note The output is written to the buffer pointer to by p_currOutput
//! \sa http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM for 
//! the entire derivation
//! \sa \ref SSEC_RFFT_F64_USING_CFFT_F64
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 761
//! <tr><td> 128     <td> 1465
//! <tr><td> 256     <td> 2873
//! <tr><td> 512     <td> 5688
//! <tr><td> 1024    <td> 11320
//! </table>
//
extern void CFFT_f64_pack(CFFT_f64_Handle hndCFFT_f64);

//! \brief Inverse Complex FFT (Swap Method).
//!
//! This routine computes the 64-bit floating-point Inverse FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. It uses the forward FFT to do
//!  this by first swapping the real and imaginary parts of the input, running
//! the forward FFT and then swapping the real and imaginary parts of the
//! output to get the final answer.
//! 
//! The inverse FFT is given by:
//! 
//! \f[ x(n) = \sum_{k=0}^{N-1}(X(k) e^{j.2.pi.k.n/N}) \f]
//! 
//! Note that 
//!
//! \f[-jX(k) = -j(X_{r}(k)+jX_{i}(k))                      \f]
//! \f[    =   (X_{i}(k)-jX_{r}(k))                         \f]
//! \f[    =   (swap_{r \leftrightarrow i}(X(k)))^{\ast}    \f]
//! \f[    =    X_{sri}^{\ast}(k)                           \f]
//! and
//! \f[ jX_{sri}^{\ast}(k)  =  j(X_{i}(k)-jX_{r}(k))        \f]
//! \f[                    =   (X_{r}(k)+jX_{i}(k))         \f]
//! 
//! Multiplying and dividing the original equation by -j          
//! 
//! \f[x(n) = \sum_{k=0}^{N-1}j(-jX(k) e^{j.2.pi.k.n/N})                          \f]
//! \f[     = j(\sum_{k=0}^{N-1}(X_{sri}^{\ast}(k) e^{j.2.pi.k.n/N})              \f]
//! \f[     = j(\sum_{k=0}^{N-1}(X_{sri}(k) e^{-j.2.pi.k.n/N})^{\ast}             \f]
//! \f[     = j.(CFFT(swap_{r \leftrightarrow i}(X(k))))^{\ast}                   \f]
//! \f[     = swap_{r \leftrightarrow i}(CFFT(swap_{r \leftrightarrow i}(X(k))))  \f]
//! 
//! The routine uses two buffers in ping-pong fashion i.e. after each FFT 
//! stage the output and input buffers become the
//! input and output buffers respectively for the next stage. The CFFT_f64_Struct
//! object uses two pointers, CurrentInPtr and CurrentOutPtr to keep track of
//! the switching. The user can determine the address of the final output by
//! looking at the CurrentInPtr.
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N
//! and type float64_t (64-bit), for computation; the input buffer must be
//! aligned to a memory address of 8N words (16-bit). Refer to the FFT linker
//! command file to see an example of this.
//! -# The maximum size of this inverse complex FFT is 4096
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 4537
//! <tr><td> 128     <td> 10132
//! <tr><td> 256     <td> 22559
//! <tr><td> 512     <td> 49927
//! <tr><td> 1024    <td> 109746
//! </table>
//
extern void ICFFT_f64(CFFT_f64_Handle hndCFFT_f64);

//! \brief Unaligned Inverse Complex FFT (Swap Method).
//!
//! This routine computes the 64-bit floating-point Inverse FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. It uses the forward FFT to do
//!  this by first swapping the real and imaginary parts of the input, running
//! the forward FFT and then swapping the real and imaginary parts of the
//! output to get the final answer.
//! 
//! The inverse FFT is given by:
//! 
//! \f[ x(n) = \sum_{k=0}^{N-1}(X(k) e^{j.2.pi.k.n/N}) \f]
//! 
//! Note that 
//!
//! \f[-jX(k) = -j(X_{r}(k)+jX_{i}(k))                      \f]
//! \f[    =   (X_{i}(k)-jX_{r}(k))                         \f]
//! \f[    =   (swap_{r \leftrightarrow i}(X(k)))^{\ast}    \f]
//! \f[    =    X_{sri}^{\ast}(k)                           \f]
//! and
//! \f[ jX_{sri}^{\ast}(k)  =  j(X_{i}(k)-jX_{r}(k))        \f]
//! \f[                    =   (X_{r}(k)+jX_{i}(k))         \f]
//! 
//! Multiplying and dividing the original equation by -j          
//! 
//! \f[x(n) = \sum_{k=0}^{N-1}j(-jX(k) e^{j.2.pi.k.n/N})                          \f]
//! \f[     = j(\sum_{k=0}^{N-1}(X_{sri}^{\ast}(k) e^{j.2.pi.k.n/N})              \f]
//! \f[     = j(\sum_{k=0}^{N-1}(X_{sri}(k) e^{-j.2.pi.k.n/N})^{\ast}             \f]
//! \f[     = j.(CFFT(swap_{r \leftrightarrow i}(X(k))))^{\ast}                   \f]
//! \f[     = swap_{r \leftrightarrow i}(CFFT(swap_{r \leftrightarrow i}(X(k))))  \f]
//!
//! The routine uses two buffers in ping-pong fashion i.e. after each FFT 
//! stage the output and input buffers become the
//! input and output buffers respectively for the next stage. The CFFT_f64_Struct
//! object uses two pointers, CurrentInPtr and CurrentOutPtr to keep track of
//! the switching. The user can determine the address of the final output by
//! looking at the CurrentInPtr.
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N
//! and type float64_t (64-bit), for computation; the input buffer need not
//! be aligned to any boundary; if it is possible to align the input buffer
//! to an 8N word boundary the user may use the faster ICFFT_f64
//! function
//! -# The maximum size of this inverse complex FFT is 4096
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 4876
//! <tr><td> 128     <td> 10808
//! <tr><td> 256     <td> 23905
//! <tr><td> 512     <td> 52619
//! <tr><td> 1024    <td> 115129
//! </table>
//
extern void ICFFT_f64u(CFFT_f64_Handle hndCFFT_f64);


//! \brief Real Fast Fourier Transform (Alternate).
//!
//! This routine computes the 64-bit double precision FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) real input. This function reorders
//! the input in bit-reversed format as part of the stage 1,2 and 3
//! computations. The routine uses two buffers in ping-pong fashion i.e. after 
//! each FFT stage the output and input buffers become the input and output 
//! buffers respectively for the next stage. 
//! This algorithm only allocates memory, and performs computation, for the 
//! non-zero elements of the input (the real part). The complex conjugate 
//! nature of the spectrum (for real only data) affords savings in space 
//! and computation, therefore the algorithm only calculates the spectrum from 
//! the 0th bin to the Nyquist bin (included).
//! 
//! Another approach to calculate the real FFT would be to treat the real 
//! N-point data as N/2 complex, run the forward complex N/2 point FFT 
//! followed by an "unpack" function
//! 
//! \param hndCFFT_F64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The routine requires the use of two buffers, each of size N
//! and type float64_t (64-bit), for computation; the input buffer must be
//! aligned to a memory address of 4N words (16-bit). Refer to the RFFT linker
//! command file to see an example of this.
//! -# If alignment is not possible the user can use the alternative, albeit
//! slower, function RFFT_f64_u_calc
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//! \attention The maximum size of the real FFT is 16384
//! \sa \ref SSEC_RFFT_F64_USING_CFFT_F64
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1729
//! <tr><td> 128     <td> 3914
//! <tr><td> 256     <td> 8915
//! <tr><td> 512     <td> 20219
//! <tr><td> 1024    <td> 45476
//! </table>
//
extern void RFFT_f64(CFFT_f64_Handle hndCFFT_f64);

//! \brief Unaligned Real Fast Fourier Transform (Alternate).
//!
//! This routine computes the 64-bit double precision FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) real input. This function reorders
//! the input in bit-reversed format as part of the stage 1,2 and 3
//! computations. The routine uses two buffers in ping-pong fashion i.e. after 
//! each FFT stage the output and input buffers become the input and output 
//! buffers respectively for the next stage. 
//! This algorithm only allocates memory, and performs computation, for the 
//! non-zero elements of the input (the real part). The complex conjugate 
//! nature of the spectrum (for real only data) affords savings in space 
//! and computation, therefore the algorithm only calculates the spectrum from 
//! the 0th bin to the Nyquist bin (included).
//! 
//! Another approach to calculate the real FFT would be to treat the real 
//! N-point data as N/2 complex, run the forward complex N/2 point FFT 
//! followed by an "unpack" function
//! 
//! \param hndCFFT_F64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The routine requires the use of two buffers, each of size N
//! and type float64_t (64-bit), for computation; the input buffer need
//! not be aligned.
//! -# If alignment is possible the user can use the faster alternative
//! function RFFT_f64_calc
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//! \attention The maximum size of the real FFT is 16384
//! \sa \ref SSEC_RFFT_F64_USING_CFFT_F64
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1903
//! <tr><td> 128     <td> 4256
//! <tr><td> 256     <td> 9593
//! <tr><td> 512     <td> 21569
//! <tr><td> 1024    <td> 48170
//! </table>
//
extern void RFFT_f64u(CFFT_f64_Handle hndCFFT_f64);

//! \brief Real FFT with ADC Input.
//!
//! This routine computes the 64-bit double precision FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) real 12-bit ADC input. This function
//! reorders the input in bit-reversed format as part of the stage 1,2 and 3
//! computations. The routine uses two buffers in ping-pong fashion i.e. after
//! each FFT stage the output and input buffers become the input and output
//! buffers respectively for the next stage.
//! This algorithm only allocates memory, and performs computation, for the
//! non-zero elements of the input (the real part). The complex conjugate
//! nature of the spectrum (for real only data) affords savings in space
//! and computation, therefore the algorithm only calculates the spectrum from
//! the 0th bin to the Nyquist bin (included).
//!
//! Another approach to calculate the real FFT would be to treat the real
//! N-point data as N/2 complex, run the forward complex N/2 point FFT
//! followed by an "unpack" function
//!
//! \param hndCFFT_ADC_f64 Pointer to the CFFT_ADC_f64_Struct object
//! \attention
//! -# The routine requires the use of two buffers, the input of size 4N
//! and type uint16_t, the output of size N and type float64_t,
//! for computation; the input buffer must be aligned to a memory address of
//! N words (16-bit). Refer to the RFFT linker command file to see an example
//! of this. If it is not possible to align the input buffer to an N word 
//! boundary you may use the unaligned version RFFT_f64_u_adc_calc().
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//! \attention The maximum size of the real FFT is 16384
//! \sa \ref SSEC_RFFT_F64_USING_CFFT_F64
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles
//! <tr><td> 64      <td> 2046
//! <tr><td> 128     <td> 4551
//! <tr><td> 256     <td> 10195
//! <tr><td> 512     <td> 22780
//! <tr><td> 1024    <td> 50597
//! </table>
//
extern void RFFT_adc_f64(CFFT_ADC_f64_Handle hndCFFT_ADC_f64);

//! \brief Unaligned Real FFT with ADC Input.
//!
//! This routine computes the 64-bit double precision FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) real 12-bit ADC input. This function
//! reorders the input in bit-reversed format as part of the stage 1,2 and 3
//! computations. The routine uses two buffers in ping-pong fashion i.e. after
//! each FFT stage the output and input buffers become the input and output
//! buffers respectively for the next stage.
//! This algorithm only allocates memory, and performs computation, for the
//! non-zero elements of the input (the real part). The complex conjugate
//! nature of the spectrum (for real only data) affords savings in space
//! and computation, therefore the algorithm only calculates the spectrum from
//! the 0th bin to the nyquist bin (included).
//!
//! Another approach to calculate the real FFT would be to treat the real
//! N-point data as N/2 complex, run the forward complex N/2 point FFT
//! followed by an "unpack" function
//!
//! \param hndCFFT_ADC_f64 Pointer to the CFFT_ADC_f64_Struct object
//! \attention
//! -# The routine requires the use of two buffers, the input of size 4N
//! and type uint16_t, the output of size N and type float64_t,
//! for computation; the input buffer needn't be aligned. If it is possible
//! to align the input buffer to an N word boundary consider using the
//! faster RFFT_f64_adc_calc().
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//! \attention The maximum size of the real FFT is 16384
//! \sa \ref SSEC_RFFT_F64_USING_CFFT_F64
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles
//! <tr><td> 64      <td> 2180
//! <tr><td> 128     <td> 4813
//! <tr><td> 256     <td> 10709
//! <tr><td> 512     <td> 23806
//! <tr><td> 1024    <td> 52647
//! </table>
//
extern void RFFT_adc_f64u(CFFT_ADC_f64_Handle hndCFFT_ADC_f64);

//! \brief Windowing function for the 64-bit real FFT with ADC Input
//! \param pBuffer  pointer to the uint16_t buffer that needs to be windowed
//! \param pWindow  pointer to the float windowing table
//! \param size     size of the buffer
//! This function applies the window to a 2N point real data buffer that
//! has not been reordered in the bit-reversed format
//! \note This function is identical to _RFFT_adc_f32_win. It is replicated 
//! here so as to avoid conflicting ISA issues when including both the fpu32
//! and fpu64 libraries. 
//! \attention
//! -# The routine requires the window to be unsigned int (16-bit). The 
//! user must take the desired floating point window from the header files
//! (e.g. HANN1024 from fpu32/fpu_fft_hann.h)and convert it to Q16 by
//! multiplying by 2^16 and then flooring the value before converting it to 
//! uint16_t
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles
//! <tr><td> 64      <td> 346
//! <tr><td> 128     <td> 666
//! <tr><td> 256     <td> 1306
//! <tr><td> 512     <td> 2586
//! <tr><td> 1024    <td> 5146
//! </table>
//
extern void RFFT_adc_f64_win(uint16_t *pBuffer, const uint16_t *pWindow,
                             const uint16_t size);

//! \brief Real FFT Magnitude.
//!
//! This module computes the real FFT magnitude. The output from
//! RFFT_f64_mag matches the magnitude output from the FFT found in common
//! mathematics software and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the RFFT_f64s_mag function
//! can be used. In fixed-point algorithms scaling is performed to avoid
//! overflowing data.
//! Floating-point calculations do not need this scaling to avoid overflow and
//! therefore the RFFT_f64_mag function can be used instead.
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The macro RFFT_MAG_IN_PLACE must be set to 1 if the input and output
//! arrays are the same, i.e. the magnitude operation is done in-place.
//! If the input and output arrays are different set this macro to 0. Always
//! rebuild the library when changing this macro
//! -# The Magnitude buffer does not require memory alignment to a boundary
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1332
//! <tr><td> 128     <td> 2628
//! <tr><td> 256     <td> 5220
//! <tr><td> 512     <td> 10402
//! <tr><td> 1024    <td> 20770
//! </table>
//
extern void RFFT_f64_mag(CFFT_f64_Handle hndCFFT_f64);

//! \brief Real FFT Magnitude (Scaled).
//!
//! This module computes the scaled real FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the
//! normalization performed by the fixed-point TMS320C28x IQmath FFT library
//! for overflow avoidance. Floating-point calculations do not need this
//! scaling to avoid overflow and therefore the RFFT_f64_mag function can be
//! used instead. The output from RFFT_f64_s_mag matches the magnitude
//! output from the FFT found in common mathematics software and Code Composer
//! Studio FFT graphs.
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The macro RFFT_MAG_IN_PLACE must be set to 1 if the input and output
//! arrays are the same, i.e. the magnitude operation is done in-place.
//! If the input and output arrays are different set this macro to 0. Always
//! rebuild the library when changing this macro
//! -# The Magnitude buffer does not require memory alignment to a boundary
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1403
//! <tr><td> 128     <td> 2725
//! <tr><td> 256     <td> 5449
//! <tr><td> 512     <td> 10818
//! <tr><td> 1024    <td> 21575
//! </table>
//
extern void RFFT_f64s_mag(CFFT_f64_Handle hndCFFT_f64);

//! \brief Real FFT Phase.
//!
//! \param hndCFFT_f64 Pointer to the CFFT_f64_Struct object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# The phase function calls the atan2 function in the runtime-support
//! library. The phase function has not been optimized at this time.
//! -# The use of the atan2 function in the FPU fast RTS library will speed up
//! this routine.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles (fastRTS) <th> Cycles (RTS)
//! <tr><td> 64      <td> 3280             <td> N/A
//! <tr><td> 128     <td> 6448             <td> N/A
//! <tr><td> 256     <td> 12784            <td> N/A
//! <tr><td> 512     <td> 25454            <td> N/A
//! <tr><td> 1024    <td> 50798            <td> N/A
//! </table>
//
extern void RFFT_f64_phase(CFFT_f64_Handle hndCFFT_f64);
// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FFT_H_

// End of File
