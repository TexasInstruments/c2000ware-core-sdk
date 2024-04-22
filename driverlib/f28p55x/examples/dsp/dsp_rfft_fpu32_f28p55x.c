//#############################################################################
//! \file dsp_rfft_fpu32_f28p55x.c
//!
//!
//! This example shows how to compute the FFT on an N point real data, as
//! well as compute the magnitude and phase of the output signal
//!
//
//  Group:             C2000
//  Target Family:     F28P55x
//
//#############################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################



//*****************************************************************************
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

#include "string.h"
#include "math.h"
#include "stdio.h"


//!
//! \addtogroup RFFT_EXAMPLES Real Fast Fourier Transform

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define RFFT_STAGES     8
#define RFFT_SIZE       (1 << RFFT_STAGES)
#define EPSILON         0.01
//#define USE_TABLE   // If using pre-defined FFT Twiddle Factor Table
                      // Check "Use Predefined Twiddle Factors" in sysconfig to enable the support

//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata1")
#pragma DATA_SECTION("RFFTdata2")
#pragma DATA_SECTION("RFFTdata3")
#else
#pragma DATA_SECTION(RFFTin1Buff,"RFFTdata1")
#pragma DATA_SECTION(RFFTmagBuff,"RFFTdata2")
#pragma DATA_SECTION(RFFTphBuff,"RFFTdata3")
#pragma DATA_SECTION(RFFToutBuff,"RFFTdata4")
#endif //__cplusplus

//! \brief FFT Calculation Buffer
//! \note The input buffer needs to be aligned to a 2N word boundary
//! \note If the number of FFT stages is odd, the result of the FFT will
//! be written to this buffer
//!
float32_t RFFTin1Buff[RFFT_SIZE];
float32_t* inPtr = RFFTin1Buff;

//! \brief Magnitude Calculation Buffer
//!
float32_t RFFTmagBuff[RFFT_SIZE/2+1];
float32_t* magPtr = RFFTmagBuff;

//! \brief Phase Calculation Buffer
//!
float32_t RFFTphBuff[RFFT_SIZE/2];
float32_t* phPtr = RFFTphBuff;

//! \brief FFT Calculation Buffer
//! \note If the number of FFT stages is even, the result of the FFT will
//! be written to this buffer
//!
float32_t RFFToutBuff[RFFT_SIZE];
float32_t* outPtr = RFFToutBuff;

float32_t RFFTgoldenOut[RFFT_SIZE] = {
    #include "data_output_rfft1.h"
};

float32_t RFFTgoldenMagnitude[RFFT_SIZE/2+1] = {
    #include "data_output_rfft2.h"
};

float32_t RFFTgoldenPhase[RFFT_SIZE/2] = {
    #include "data_output_rfft3.h"
};

float32_t RFFTTwiddleCoef[RFFT_SIZE];
float32_t* twiddlePtr = RFFTTwiddleCoef;

float32_t RadStep = 0.1963495408494f;
float32_t Rad = 0.0f;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Real FFT example
//! \return returns a 1
//!
//! This program shows how to compute a real FFT and associated spectrum
//! magnitude and phase.  The input buffer must be aligned to a 2N word
//! boundary if using RFFT_f32.
//! Data section alignment (#pragma ...) is not necessary for RFFT_f32u
//! but necessary when running RFFT_f32.  However, using the unaligned version
//! will reduce cycle performance of the algorithm.
//!
//! The minimum number of stages is 3. When the number of stages is more
//! than 9, the quantization error would be significant and not recommended.
//! The results of the computation can be compared against MATLAB code under
//! 2837x_RFFT/matlab/RFFTforC28x.
//!
//! RFFT_F32_STRUCT is a structure defined as:
//!
//!    typedef struct {
//!      float  *InBuf;
//!      float  *OutBuf;
//!      float  *CosSinBuf;
//!      float  *MagBuf;
//!      float  *PhaseBuf;
//!      uint16_t FFTSize;
//!      uint16_t FFTStages;
//!    } RFFT_F32_STRUCT;
//!
//!  ASSUMPTIONS:
//!
//! -# FFTSize must be a power of 2 (32, 64, 128, etc)
//! -# FFTSize must be greater or equal to 32
//! -# FFTStages must be log2(FFTSize)
//! -# InBuf, OutBuf, CosSinBuf are FFTSize in length
//! -# Magnitude buffer is FFTSize/2+1 in length
//! -# Phase buffer is FFTSize/2 in length
//!
//!  Watch Variables:
//!
//! -# InBuf        Input buffer
//! -# OutBuf       Output buffer
//! -# CosSinBuf    Twiddle factor buffer
//! -# MagBuf       Magnitude buffer
//! -# PhaseBuf     Phase buffer
//!
//!--------------------------------------------------------------------------
//!  Input buffer structure:
//!     InBuf[0] = input[0]
//!     InBuf[1] = input[1]
//!     InBuf[2] = input[2]
//!     â¦â¦â¦
//!     InBuf[N/2] = input[N/2]
//!     InBuf[N/2+1] = input[N/2+1]
//!     â¦â¦â¦
//!     InBuf[N-3] = input[N-3]
//!     InBuf[N-2] = input[N-2]
//!     InBuf[N-1] = input[N-1]
//!
int rfft_fpu32_test(void)
{
    // Clear input buffers:
    memset(inPtr, 0, RFFT_SIZE*sizeof(float32_t));
    memset(magPtr, 0, (RFFT_SIZE/2+1)*sizeof(float32_t));
    memset(phPtr, 0, RFFT_SIZE/2*sizeof(float32_t));
    memset(outPtr, 0, RFFT_SIZE/2*sizeof(float32_t));

    // Generate sample waveforms:
    //       CFFTin1Buff[0] = real[0]
    //       CFFTin1Buff[1] = imag[0]
    //       CFFTin1Buff[2] = real[1]
    //       â¦â¦â¦
    //       CFFTin1Buff[N] = real[N/2]
    //       CFFTin1Buff[N+1] = imag[N/2]
    //       â¦â¦â¦
    //       CFFTin1Buff[2N-3] = imag[N-2]
    //       CFFTin1Buff[2N-2] = real[N-1]
    //       CFFTin1Buff[2N-1] = imag[N-1]
    int i;
    Rad = 0.0f;
    for(i = 0; i < RFFT_SIZE; i++)
    {
        RFFTin1Buff[i]   = sinf(Rad) + cosf(Rad*2.3567); //Real input signal
        Rad = Rad + RadStep;
    }

    //
    // Off-Place Algorithm
    //
    // Note: In this version, RFFTinBuff and RFFToutBuff are used in
    //       ping-pong fashion. The input data is first stored in CFFTin1Buff
    //       where the FFT, including bit reversed ordering, is initially done.
    //       At each successive stage of the FFT the cfft.CurrentInPtr pointer
    //       will point to the buffer that is the input for that stage. In this
    //       manner the "CurrentInPtr" and "CurrentOutPtr" are exchanged at the
    //       start of each stage. Depending on the number of FFT stages, the
    //       final output will be in either RFFTin1Buff (#Stages is odd) or
    //       RFFToutBuff (#stages is even).
    // Note: All setup & initialization for cfft are taken care of by sysconfig

    // Note: RFFT_f32 requires proper alignment of input buffer, to a memory address of 2N words (N is the size of fft).
    // If alignment is not possible the user can use the alternative, albeit slower, function RFFT_f32u
    RFFT_f32(myRFFT0_handle);                   //Calculate real FFT

    // Check the output
    for(i = 0; i < RFFT_SIZE; i++){
        if(fabsf(RFFTgoldenOut[i] - myRFFT0_handle->OutBuf[i]) <= EPSILON){
            pass++;
        }
        else{
            fail++;
        }
    }
    //   OutBuf[0] = real[0]
    //   OutBuf[1] = real[1]
    //   OutBuf[2] = real[2]
    //   â¦â¦â¦
    //   OutBuf[N/2] = real[N/2]
    //   OutBuf[N/2+1] = imag[N/2-1]
    //   â¦â¦â¦
    //   OutBuf[N-3] = imag[3]
    //   OutBuf[N-2] = imag[2]
    //   OutBuf[N-1] = imag[1]
    //
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project properties
    RFFT_f32_mag_TMU0(myRFFT0_handle);            //Calculate magnitude
#else
    RFFT_f32_mag(myRFFT0_handle);                 //Calculate magnitude
#endif
    // Check the output
    for(i = 0; i <= RFFT_SIZE/2; i++){
        if(fabsf(RFFTgoldenMagnitude[i] - myRFFT0_handle->MagBuf[i]) <= EPSILON){
            pass++;
        }
        else{
            fail++;
        }
    }
    //   MagBuf[0] = magnitude[0]
    //   MagBuf[1] = magnitude[1]
    //   MagBuf[2] = magnitude[2]
    //   â¦â¦â¦
    //   MagBuf[N/2] = magnitude[N/2]
    //   MagBuf[N/2+1] = magnitude[N/2+1]

#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project properties
    RFFT_f32_phase_TMU0(myRFFT0_handle);           //Calculate phase
#else
    RFFT_f32_phase(myRFFT0_handle);                //Calculate phase
#endif
    // Check the output
    for(i = 0; i < RFFT_SIZE/2; i++){
        if(fabsf(RFFTgoldenPhase[i] - myRFFT0_handle->PhaseBuf[i]) <= EPSILON){
            pass++;
        }
        else{
            fail++;
        }
    }

    printf("Total of %d tests pass, and %d failure",pass,fail);

    return 1;
}

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    rfft_fpu32_test();
    
    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
