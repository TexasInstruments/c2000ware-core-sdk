//#############################################################################
//! \file /2837x_RFFT_Unaligned_ScaledMagnitude/main.c
//!
//! \brief  Demo code for the Real FFT (Unaligned) with scaled magnitude
//! \author Vishal Coelho (Modified the original)
//! \date   03/26/2015 
//! 
//! This example shows how to compute the FFT (unalgined) on an N point real 
//! data, as well as compute the scaled magnitude and phase of the output 
//! signal 
//!
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "fpu_rfft.h"
#include "math.h"
#include "examples_setup.h"

//!
//! \addtogroup RFFT_EXAMPLES Real Fast Fourier Transform

// @{
//*****************************************************************************
// defines
//*****************************************************************************
#define RFFT_STAGES     8
#define RFFT_SIZE       (1 << RFFT_STAGES) 
#define EPSILON         0.01

//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata1")
#else
#pragma DATA_SECTION(RFFTin1Buff,"RFFTdata1")
#endif //__cplusplus
//! \brief FFT Calculation Buffer
//! \note If the number of FFT stages is odd, the result of the FFT will
//! be written to this buffer
//! 
float RFFTin1Buff[RFFT_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata2")
#else
#pragma DATA_SECTION(RFFTmagBuff,"RFFTdata2")
#endif //__cplusplus
//! \brief Magnitude Calculation Buffer
//!
float RFFTmagBuff[RFFT_SIZE/2+1];               

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata3")
#else
#pragma DATA_SECTION(RFFToutBuff,"RFFTdata3")
#endif //__cplusplus
//! \brief FFT Calculation Buffer
//! \note If the number of FFT stages is even, the result of the FFT will
//! be written to this buffer
//!
float RFFToutBuff[RFFT_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata4")
#else
#pragma DATA_SECTION(RFFTF32Coef,"RFFTdata4")
#endif //__cplusplus
//! \brief Twiddle Factors
//!
float RFFTF32Coef[RFFT_SIZE];

float RFFTgoldenOut[RFFT_SIZE] = {
    #include "data_output_1.h"
};

float RFFTgoldenMagnitude[RFFT_SIZE/2+1] = {
    #include "data_output_2.h"
};

float RFFTgoldenPhase[RFFT_SIZE/2] = {
    #include "data_output_3.h"
};

float RadStep = 0.1963495408494f;  // Step to generate test bench waveform
float Rad = 0.0f;


//! \brief Object of the structure RFFT_F32_STRUCT
//!
RFFT_F32_STRUCT rfft;

//! \brief Handle to the RFFT_F32_STRUCT object
//!
RFFT_F32_STRUCT_Handle hnd_rfft = &rfft;

uint16_t pass = 0;
uint16_t fail = 0;

#ifdef USE_TABLES
//Linker defined variables
extern uint16_t  FFTTwiddlesRunStart;
extern uint16_t  FFTTwiddlesLoadStart;
extern uint16_t  FFTTwiddlesLoadSize;
#endif //USE_TABLES
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

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
//! 2837x_RFFT_Unaligned_ScaledMagnitude/matlab/RFFTforC28x.
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
//!     ………
//!     InBuf[N/2] = input[N/2]
//!     InBuf[N/2+1] = input[N/2+1]
//!     ………
//!     InBuf[N-3] = input[N-3]
//!     InBuf[N-2] = input[N-2]
//!     InBuf[N-1] = input[N-1]
//!
int16_t main(void)
{
    // Locals
    uint16_t i;

#ifdef FLASH
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
    memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
            (uint32_t)&RamfuncsLoadSize );
    FPU_initFlash();
#ifdef USE_TABLES
    memcpy((uint32_t *)&FFTTwiddlesRunStart, (uint32_t *)&FFTTwiddlesLoadStart,
            (uint32_t)&FFTTwiddlesLoadSize );
#endif //USE_TABLES
#endif //FLASH
    
    FPU_initSystemClocks();
    
    FPU_initEpie();

    // Clear input buffers:
    for(i=0; i < RFFT_SIZE; i++){
        RFFTin1Buff[i] = 0.0f;
    }
    
    // Generate sample waveforms:
    Rad = 0.0f;
    for(i=0; i < RFFT_SIZE; i++){
        RFFTin1Buff[i]   = sin(Rad) + cos(Rad*2.3567); //Real input signal
        Rad = Rad + RadStep;
    }
   
    hnd_rfft->FFTSize   = RFFT_SIZE;
    hnd_rfft->FFTStages = RFFT_STAGES;   
    hnd_rfft->InBuf     = &RFFTin1Buff[0];  //Input buffer
    hnd_rfft->OutBuf    = &RFFToutBuff[0];  //Output buffer
    hnd_rfft->MagBuf    = &RFFTmagBuff[0];  //Magnitude buffer
#ifdef USE_TABLES
    hnd_rfft->CosSinBuf = RFFT_f32_twiddleFactors;  //Twiddle factor buffer
#else
    hnd_rfft->CosSinBuf = &RFFTF32Coef[0];  //Twiddle factor buffer
    RFFT_f32_sincostable(hnd_rfft);         //Calculate twiddle factor
#endif //USE_TABLES

    for (i=0; i < RFFT_SIZE; i++){
          RFFToutBuff[i] = 0;               //Clean up output buffer
    }                                       
                                            
    for (i=0; i <= RFFT_SIZE/2; i++){       
         RFFTmagBuff[i] = 0;                //Clean up magnitude buffer
    }                                       
                                            
    RFFT_f32u(hnd_rfft);                    //Calculate real FFT
    // Check the output
    for(i = 0; i < RFFT_SIZE; i++){
        if(fabs(RFFTgoldenOut[i] - hnd_rfft->OutBuf[i]) <= EPSILON){
            pass++;
        }else{
            fail++;
        }
    }
    //   OutBuf[0] = real[0]
    //   OutBuf[1] = real[1]
    //   OutBuf[2] = real[2]
    //   ………
    //   OutBuf[N/2] = real[N/2]
    //   OutBuf[N/2+1] = imag[N/2-1]
    //   ………
    //   OutBuf[N-3] = imag[3]
    //   OutBuf[N-2] = imag[2]
    //   OutBuf[N-1] = imag[1]
    //    
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           // properties
    RFFT_f32s_mag_TMU0(hnd_rfft);           //Calculate magnitude
#else
    RFFT_f32s_mag(hnd_rfft);                //Calculate magnitude
#endif
    // Check the output
    for(i = 0; i <= RFFT_SIZE/2; i++){
        if(fabs(RFFTgoldenMagnitude[i] - hnd_rfft->MagBuf[i]) <= EPSILON){
            pass++;
        }else{
            fail++;
        }
    }
    //   MagBuf[0] = magnitude[0]
    //   MagBuf[1] = magnitude[1]
    //   MagBuf[2] = magnitude[2]
    //   ………
    //   MagBuf[N/2] = magnitude[N/2]
    //   MagBuf[N/2+1] = magnitude[N/2+1]

    hnd_rfft->PhaseBuf = &RFFTmagBuff[0];    //Use magnitude buffer
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           // properties
    RFFT_f32_phase_TMU0(hnd_rfft);           //Calculate phase
#else
    RFFT_f32_phase(hnd_rfft);                //Calculate phase
#endif
    // Check the output
    for(i = 0; i < RFFT_SIZE/2; i++){
        if(fabs(RFFTgoldenPhase[i] - hnd_rfft->PhaseBuf[i]) <= EPSILON){
            pass++;
        }else{
            fail++;
        }
    }
    // End of test
    done();
    // Execution never reaches this point
    return 1;
}

// End of main

// @} //addtogroup

// End of file
