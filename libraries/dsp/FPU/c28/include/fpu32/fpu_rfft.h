#ifndef _FPU_RFFT_H_
#define _FPU_RFFT_H_
//#############################################################################
//! \file   include/fpu_rfft.h
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
//! \defgroup DSP_RFFT_F32 Real Fast Fourier Transforms

//!
//! \ingroup DSP_RFFT_F32
// @{
    
#ifdef __cplusplus
extern "C" {
#endif
//*****************************************************************************
// typedefs
//*****************************************************************************

//! \brief Structure for the Real FFT
//!
typedef struct {
  float  *InBuf;		//!< Pointer to the input buffer
  float  *OutBuf;		//!< Pointer to the output buffer
  float  *CosSinBuf;    //!< Pointer to the twiddle factors
  float  *MagBuf;       //!< Pointer to the magnitude buffer
  float  *PhaseBuf;     //!< Pointer to the phase buffer
  uint16_t   FFTSize;   //!< Size of the FFT (number of real data points)
  uint16_t   FFTStages; //!< Number of FFT stages
} RFFT_F32_STRUCT;

//! \brief Handle to the Real FFT object
//!
typedef RFFT_F32_STRUCT* RFFT_F32_STRUCT_Handle;

//! \brief Structure for the Real FFT with ADC input
//!
typedef struct {
  uint16_t   *InBuf;    //!< Pointer to the input buffer
  void	     *Tail;     //!< Null pointer to the OutBuf of RFFT_F32_STRUCT
} RFFT_ADC_F32_STRUCT;

//! \brief Handle to the Real FFT (with ADC input) structure
//!
typedef RFFT_ADC_F32_STRUCT* RFFT_ADC_F32_STRUCT_Handle;

//*****************************************************************************
// globals
//*****************************************************************************
//
//! \brief Twiddle Factor Table for a 2048-pt (max) Real FFT
//!
//!  Note:
//!  1. RFFT_f32_twiddleFactors name is deprecated and only supported for
//!     legacy reasons. Users are encouraged to use FPU32RFFTtwiddleFactors
//!     as the table symbol.
//!  2. The RFFT_f32_twiddleFactors is an alias for the new table. It is not
//!     a separate table.
//
//*****************************************************************************
extern float RFFT_f32_twiddleFactors[1020];
extern float FPU32RFFTtwiddleFactors[1020];

//*****************************************************************************
// 'inline' function
//*****************************************************************************

//! \brief Set the input buffer pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \param[in] pi  pointer to the input buffer
//!
static inline void RFFT_f32_setInputPtr(RFFT_F32_STRUCT_Handle fh,
        const float *pi)
{
    fh->InBuf = (float *)pi;
}

//! \brief Get the input buffer pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \return pi  pointer to the input buffer
//!
static inline float * RFFT_f32_getInputPtr(RFFT_F32_STRUCT_Handle fh)
{
    return(fh->InBuf);
}

//! \brief Set the output buffer pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \param[in] po  pointer to the output buffer
//!
static inline void RFFT_f32_setOutputPtr(RFFT_F32_STRUCT_Handle fh,
        const float *po)
{
    fh->OutBuf= (float *)po;
}

//! \brief Get the output buffer pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \return po  pointer to the output buffer
//!
static inline float * RFFT_f32_getOutputPtr(RFFT_F32_STRUCT_Handle fh)
{
    return(fh->OutBuf);
}

//! \brief Set the twiddles pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \param[in] pt  pointer to the twiddles
//!
static inline void RFFT_f32_setTwiddlesPtr(RFFT_F32_STRUCT_Handle fh,
        const float *pc)
{
    fh->CosSinBuf = (float *)pc;
}

//! \brief Get the twiddles pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \return pt  pointer to the twiddles
//!
static inline float * RFFT_f32_getTwiddlesPtr(RFFT_F32_STRUCT_Handle fh)
{
    return(fh->CosSinBuf);
}

//! \brief Set the magnitude buffer pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \param[in] pm  pointer to the magnitude buffer
//!
static inline void RFFT_f32_setMagnitudePtr(RFFT_F32_STRUCT_Handle fh,
        const float *pm)
{
    fh->MagBuf = (float *)pm;
}


//! \brief Get the magnitude buffer pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \return pm  pointer to the magnitude buffer
//!
static inline float * RFFT_f32_getMagnitudePtr(RFFT_F32_STRUCT_Handle fh)
{
    return(fh->MagBuf);
}

//! \brief Set the phase buffer pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \param[in] pp  pointer to the phase buffer
//!
static inline void RFFT_f32_setPhasePtr(RFFT_F32_STRUCT_Handle fh,
        const float *pp)
{
    fh->PhaseBuf = (float *)pp;
}


//! \brief Get the phase buffer pointer
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \return pp  pointer to the phase buffer
//!
static inline float * RFFT_f32_getPhasePtr(RFFT_F32_STRUCT_Handle fh)
{
    return(fh->PhaseBuf);
}

//! \brief Set the number of FFT stages
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \param[in] st  number of FFT stages
//!
static inline void RFFT_f32_setStages(RFFT_F32_STRUCT_Handle fh,
                      const uint16_t st)
{
    fh->FFTStages = st;
}

//! \brief Get the number of FFT stages
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \return st  number of FFT stages
//!
static inline uint16_t RFFT_f32_getStages(RFFT_F32_STRUCT_Handle fh)
{
    return(fh->FFTStages);
}

//! \brief Set the size of the FFT
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \param[in] sz  size of the FFT
//!
static inline void RFFT_f32_setFFTSize(RFFT_F32_STRUCT_Handle fh,
                      const uint16_t sz)
{
    fh->FFTSize = sz;
}

//! \brief Get the size of the FFT
//! \param[in] fh  handle to the 'RFFT_F32_STRUCT' object
//! \return sz  size of the FFT
//!
static inline uint16_t RFFT_f32_getFFTSize(RFFT_F32_STRUCT_Handle fh)
{
    return(fh->FFTSize);
}

//! \brief Set the input buffer pointer
//! \param[in] fh  handle to the 'RFFT_ADC_F32_STRUCT' object
//! \param[in] pi  pointer to the input buffer
//!
static inline void RFFT_ADC_f32_setInBufPtr(RFFT_ADC_F32_STRUCT_Handle fh,
                      const uint16_t * pi)
{
    fh->InBuf = (uint16_t *)pi;
}

//! \brief get the input buffer pointer
//! \param[in] fh  handle to the 'RFFT_ADC_F32_STRUCT' object
//! \return    pi  pointer to the input buffer
//!
static inline uint16_t *RFFT_ADC_f32_getInBufPtr(RFFT_ADC_F32_STRUCT_Handle fh)
{
    return(fh->InBuf);
}

//! \brief Set the tail pointer
//! \param[in] fh  handle to the 'RFFT_ADC_F32_STRUCT' object
//! \param[in] pt  pointer to the tail
//!
static inline void RFFT_ADC_f32_setTailPtr(RFFT_ADC_F32_STRUCT_Handle fh,
                      const void * pt)
{
    fh->Tail = (void *)pt;
}

//! \brief Get the tail pointer
//! \param[in] fh  handle to the 'RFFT_ADC_F32_STRUCT' object
//! \return    pt  pointer to the tail
//!
static inline void *RFFT_ADC_f32_getTailPtr(RFFT_ADC_F32_STRUCT_Handle fh)
{
    return(fh->Tail);
}

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Real Fast Fourier Transform (RFFT).
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$)
//! This routine computes the 32-bit single precision FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) real input. This function reorders
//! the input in bit-reversed format as part of the stage 1,2 and 3
//! computations. The routine uses two buffers in ping-pong fashion i.e. after
//! each FFT stage the output and input buffers become the input and output
//! buffers respectively for the next stage.
//! This algorithm only allocates memory, and performs computation, for the
//! non-zero elements of the input (the real part). The complex conjugate
//! nature of the spectrum (for real only data) affords savings in space
//! and computaion, therefore the algorithm only calculates the spectrum from
//! the 0th bin to the nyquist bin (included).
//!
//! Another approach to calculate the real FFT would be to treat the real
//! N-point data as N/2 complex, run the forward complex N/2 point FFT
//! followed by an "unpack" function
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit
//! float), for computation; the input buffer must be aligned to a memory
//! address of 2N words (16-bit). Refer to the RFFT linker command file to see
//! an example of this.
//! -# If alignment is not possible the user can use the alternative, albeit 
//! slower, function RFFT_f32u
//! \sa \ref SSEC_RFFT_F32_USING_CFFT_F32
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1281
//! <tr><td> 128     <td> 2779
//! <tr><td> 256     <td> 6149
//! <tr><td> 512     <td> 13674
//! <tr><td> 1024    <td> 30356
//! </table>
//
extern void RFFT_f32(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT (Unaligned).
//!
//! This routine computes the 32-bit single precision FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) real input. This function reorders
//! the input in bit-reversed format as part of the stage 1,2 and 3
//! computations. The routine uses two buffers in ping-pong fashion i.e. after
//! each FFT stage the output and input buffers become the input and output
//! buffers respectively for the next stage.
//! This algorithm only allocates memory, and performs computation, for the
//! non-zero elements of the input (the real part). The complex conjugate
//! nature of the spectrum (for real only data) affords savings in space
//! and computaion, therefore the algorithm only calculates the spectrum from
//! the 0th bin to the nyquist bin (included).
//!
//! Another approach to calculate the real FFT would be to treat the real
//! N-point data as N/2 complex, run the forward complex N/2 point FFT
//! followed by an "unpack" function
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit
//! float), for computation; the input buffer need not be aligned to a boundary
//! -# If alignment is possible it is recommended to use the faster routine, 
//! RFFT_f32
//! \sa \ref SSEC_RFFT_F32_USING_CFFT_F32
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1393
//! <tr><td> 128     <td> 3003
//! <tr><td> 256     <td> 6597
//! <tr><td> 512     <td> 14570
//! <tr><td> 1024    <td> 32148
//! </table>
//
extern void RFFT_f32u(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT with ADC Input.
//!
//! This routine computes the 32-bit single precision FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) real 12-bit ADC input. This function
//! reorders the input in bit-reversed format as part of the stage 1,2 and 3
//! computations. The routine uses two buffers in ping-pong fashion i.e. after
//! each FFT stage the output and input buffers become the input and output
//! buffers respectively for the next stage.
//! This algorithm only allocates memory, and performs computation, for the
//! non-zero elements of the input (the real part). The complex conjugate
//! nature of the spectrum (for real only data) affords savings in space
//! and computaion, therefore the algorithm only calculates the spectrum from
//! the 0th bin to the nyquist bin (included).
//!
//! Another approach to calculate the real FFT would be to treat the real
//! N-point data as N/2 complex, run the forward complex N/2 point FFT
//! followed by an "unpack" function
//!
//! \param hndRFFT_ADC_F32 Pointer to the RFFT_ADC F32 object
//! \attention
//! -# The routine requires the use of two buffers, the input of size 2N
//! and type uint16_t, the output of size N and type float, for
//! computation; the input buffer must be aligned to a memory
//! address of N words (16-bit). Refer to the RFFT linker command file to
//! see an example of this.
//! -# If alignment is not possible the user can use the alternative, albeit 
//! slower, function RFFT_adc_f32u
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1295
//! <tr><td> 128     <td> 2769
//! <tr><td> 256     <td> 6059
//! <tr><td> 512     <td> 13360
//! <tr><td> 1024    <td> 29466
//! </table>
//
extern void RFFT_adc_f32(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32);

//! \brief Real FFT with ADC Input (Unaligned).
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
//! and computaion, therefore the algorithm only calculates the spectrum from
//! the 0th bin to the nyquist bin (included).
//!
//! Another approach to calculate the real FFT would be to treat the real
//! N-point data as N/2 complex, run the forward complex N/2 point FFT
//! followed by an "unpack" function
//!
//! \param hndRFFT_ADC_F32 Pointer to the RFFT_ADC F32 object
//! \attention
//! -# The routine requires the use of two buffers, the input of size 2N
//! and type uint16_t, the output of size N and type float, for
//! computation; the input buffer need not be aligned to any boundary.
//! -# If alignment is possible it is recommended to use the faster function 
//! RFFT_adc_f32
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1415
//! <tr><td> 128     <td> 3009
//! <tr><td> 256     <td> 6539
//! <tr><td> 512     <td> 14320
//! <tr><td> 1024    <td> 31386
//! </table>
//
extern void RFFT_adc_f32u(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32);

//! \brief Windowing function for the 32-bit real FFT 
//! \param pBuffer  pointer to the buffer that needs to be windowed
//! \param pWindow  pointer to the windowing table
//! \param size     size of the buffer
//! This function applies the window to a 2N point real data buffer that
//! has not been reordered in the bit-reversed format
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 308
//! <tr><td> 128     <td> 596
//! <tr><td> 256     <td> 1172
//! <tr><td> 512     <td> 2324
//! <tr><td> 1024    <td> 4628
//! </table>
//
extern void RFFT_f32_win(float *pBuffer, const float *pWindow, 
                         const uint16_t size);

//! \brief Windowing function for the 32-bit real FFT with ADC Input
//! \param pBuffer  pointer to the uint16_t buffer that needs to be windowed
//! \param pWindow  pointer to the float windowing table
//! \param size     size of the buffer
//! This function applies the window to a 2N point real data buffer that
//! has not been reordered in the bit-reversed format
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
extern void RFFT_adc_f32_win(uint16_t *pBuffer, const uint16_t *pWindow,
                             const uint16_t size);

//! \brief Real FFT Magnitude.
//!
//! This module computes the real FFT magnitude. The output from RFFT_f32_mag
//! matches the magnitude output from the FFT found in common mathematics 
//! software and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the RFFT_f32s_mag
//! function can be used. In fixed-point algorithms scaling is performed to
//! avoid overflowing data. Floating-point calculations do not need this 
//! scaling to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! RFFT_f32_mag_TMU0() instead for better performance.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 635
//! <tr><td> 128     <td> 1243
//! <tr><td> 256     <td> 2459
//! <tr><td> 512     <td> 4888
//! <tr><td> 1024    <td> 9752
//! </table>
//
extern void RFFT_f32_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT Magnitude (Scaled).
//!
//! This module computes the scaled real FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the
//! normalization performed by the fixed-point TMS320C28x IQmath FFT library
//! for overflow avoidance. Floating-point calculations do not need this
//! scaling to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead. The output from RFFT_f32s_mag matches the magnitude
//! output from the FFT found in common mathematics software and Code Composer
//! Studio FFT graphs.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! RFFT_f32s_mag_TMU0() instead for better performance.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 723
//! <tr><td> 128     <td> 1336
//! <tr><td> 256     <td> 2557
//! <tr><td> 512     <td> 4990
//! <tr><td> 1024    <td> 9859
//! </table>
//
extern void RFFT_f32s_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT Phase.
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! RFFT_f32_phase_TMU0() instead for better performance.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 1949
//! <tr><td> 128     <td> 3933
//! <tr><td> 256     <td> 7901
//! <tr><td> 512     <td> 16835
//! <tr><td> 1024    <td> 31707
//! </table>
//
extern void RFFT_f32_phase(RFFT_F32_STRUCT_Handle hndRFFT_F32);

#if defined(__TMS320C28XX_TMU__)
//! \brief Real FFT Magnitude using the TMU0 module.
//!
//! This module computes the real FFT magnitude. The output from RFFT_f32_mag
//! matches the magnitude output from the FFT found in common mathematics 
//! software and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the RFFT_f32s_mag
//! function can be used. In fixed-point algorithms scaling is performed to
//! avoid overflowing data. Floating-point calculations do not need this 
//! scaling to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use RFFT_f32_mag() instead.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 161
//! <tr><td> 128     <td> 289
//! <tr><td> 256     <td> 545
//! <tr><td> 512     <td> 1055
//! <tr><td> 1024    <td> 2079
//! </table>
//
extern void RFFT_f32_mag_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT Magnitude using the TMU0 module (Scaled).
//!
//! This module computes the scaled real FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the
//! normalization performed by the fixed-point TMS320C28x IQmath FFT library
//! for overflow avoidance. Floating-point calculations do not need this 
//! scaling to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead. The output from RFFT_f32s_mag matches the magnitude
//! output from the FFT found in common mathematics software and Code Composer
//! Studio FFT graphs.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use RFFT_f32s_mag() instead.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 268
//! <tr><td> 128     <td> 466
//! <tr><td> 256     <td> 856
//! <tr><td> 512     <td> 1375
//! <tr><td> 1024    <td> 2661
//! </table>
//
extern void RFFT_f32s_mag_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT Phase using TMU0 module.
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use RFFT_f32_phase() instead.
//!
//! <table>
//! <caption id="multi_row">Performance Data</caption>
//! <tr><th> Samples <th> Cycles 
//! <tr><td> 64      <td> 279
//! <tr><td> 128     <td> 535
//! <tr><td> 256     <td> 1047
//! <tr><td> 512     <td> 2068
//! <tr><td> 1024    <td> 4116
//! </table>
//
extern void RFFT_f32_phase_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);
#endif //__TMS320C28XX_TMU__

//! \brief Generate twiddle factors for the Real FFT.
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention This function is written in C and compiled without optimization 
//! turned on.
//
extern void RFFT_f32_sincostable(RFFT_F32_STRUCT_Handle hndRFFT_F32);

// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_RFFT_H_

// End of File
