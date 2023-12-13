//#############################################################################
//! \file /2837x_WindowedCFFT/main.c
//!
//! \brief  Demo code for the Complex Windowed FFT
//! \author Vishal Coelho
//! \date   03/20/2015
//! 
//! This example shows how to compute the FFT on an N point complex data, with
//! a window applied to it, and then compute the magnitude and phase of the 
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
#include "fpu_cfft.h"
#include "fpu_fft_barthann.h"
#include "math.h"
#include "examples_setup.h"

//!
//! \addtogroup CFFT_EXAMPLES Complex Fast Fourier Transform

// @{
//*****************************************************************************
// defines
//*****************************************************************************
#define CFFT_STAGES         7
#define CFFT_SIZE           (1 << CFFT_STAGES)
#define EPSILON             0.02
#define TEST_INPUT_REAL     0
#define TEST_INPUT_COMPLEX  (~TEST_INPUT_REAL)
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("CFFTdata1")
#else
#pragma    DATA_SECTION(CFFTin1Buff,"CFFTdata1")
#endif //__cplusplus
//! \brief FFT Calculation Buffer
//! \note The input buffer needs to be aligned to a 4N word boundary
//! \note If the number of FFT stages is odd, the result of the FFT will
//! be written to this buffer
//! \note If your input is real than be sure to enable TEST_INPUT_REAL,
//! and select the first set in "data_input.h"
//! 
float   CFFTin1Buff[CFFT_SIZE*2];

#ifdef __cplusplus
#pragma DATA_SECTION("CFFTdata2")
#else
#pragma DATA_SECTION(CFFTin2Buff,"CFFTdata2")
#endif //__cplusplus
//! \brief Magnitude Calculation Buffer
//!
float    CFFTin2Buff[CFFT_SIZE*2];

#ifdef __cplusplus
#pragma DATA_SECTION("CFFTdata3")
#else
#pragma DATA_SECTION(CFFToutBuff,"CFFTdata3")
#endif //__cplusplus
//! \brief FFT Calculation Buffer
//! \note If the number of FFT stages is even, the result of the FFT will
//! be written to this buffer
//!
float    CFFToutBuff[CFFT_SIZE*2];

#ifdef __cplusplus
#pragma DATA_SECTION("CFFTdata4")
#else
#pragma DATA_SECTION(CFFTF32Coef,"CFFTdata4")
#endif //__cplusplus
//! \brief Twiddle Factors
//!
float    CFFTF32Coef[CFFT_SIZE];

//! \brief Golden Output
//! \note If your input is real than be sure to enable TEST_INPUT_REAL,
//! and select the first set in "data_output_1.h"
//!
float CFFTgoldenOut[CFFT_SIZE*2] = {
    #include "data_output_1.h"
};


//! \brief Golden Magnitude
//! \note If your input is real than be sure to enable TEST_INPUT_REAL,
//! and select the first set in "data_output_2.h"
//!
float CFFTgoldenMagnitude[CFFT_SIZE] = {
    #include "data_output_2.h"
};

//! \brief Golden Phase
//! \note If your input is real than be sure to enable TEST_INPUT_REAL,
//! and select the first set in "data_output_3.h"
//!
float CFFTgoldenPhase[CFFT_SIZE] = {
    #include "data_output_3.h"
};

float RadStep = 0.1963495408494f;
float Rad = 0.0f;

const float CFFTwindow[CFFT_SIZE/2] = BARTHANN128;

//! \brief Object of the structure CFFT_F32_STRUCT
//!
CFFT_F32_STRUCT cfft;

//! \brief Handle to the CFFT_F32_STRUCT object
//!
CFFT_F32_STRUCT_Handle hnd_cfft = &cfft;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Complex FFT (windowed) example
//! \return returns a 1
//!
//! The test functions include CFFT_f32, CFFT_f32_win (CFFT_f32_win_dual),
//! CFFT_f32_mag and CFFT_f32_phase.
//! Data section alignment (#pragma ...) is not necessary for CFFT_f32u
//! but necessary for testing CFFT_f32.
//!
//! Minimum CFFT_Stages is 3. When CFFT_Stages is more than 9, the
//! quantization error would be significant. The results can be compared 
//! against MATLAB code under 2837x_WindowedCFFT/matlab/CFFTWindowedforC28x.m
//!
//! Use the 2837x_WindowedCFFT/matlab/C28xFPULib_Window_Generator.m to generate
//! the windows
//!
//! CFFT_F32_STRUCT is a structure defined as:
//!
//!     typedef struct {
//!        float    *InPtr;
//!        float    *OutPtr;
//!        float    *CoefPtr;
//!        float    *CurrentInPtr;
//!        float    *CurrentOutPtr;
//!        short    Stages;
//!        uint16_t  FFTSize;
//!       }CFFT_F32_STRUCT;
//!
//!  Watch Variables:
//!
//! -# InPtr           Input/output or middle stage of ping-pong buffer
//! -# OutPtr          Output or middle stage of ping-pong buffer
//! -# CurrentInPtr    Output buffer for CFFT result
//! -# CurrentOutPtr   N-1 stage CFFT result/Magnitude/Phase output buffer
//! -# CoefPtr         Twiddle factor buffer
//!
//! ------------------------------------------------------------------------
//!             | Stage 3     | Stage 4     |..| StageN(odd) | StageN(even)
//! ------------------------------------------------------------------------
//! InPtr(buf1) |CurrentInPtr |CurrentOutPtr|..|CurrentInPtr |CurrentOutPtr
//! ------------------------------------------------------------------------
//! OutPtr(buf2)|CurrentOutPtr|CurrentInPtr |..|CurrentOutPtr|CurrentInPtr
//! ------------------------------------------------------------------------
//! Result Buf  |    buf1     |    buf2       |..|        buf1    |    buf2
//! ------------------------------------------------------------------------
//!
//!  -# FFTSize must be a power of 2 (32, 64, 128, etc)
//!  -# FFTSize must be greater or equal to 32
//!  -# FFTStages must be log2(FFTSize)
//!  -# InPtr, OutPtr, CoefPtr, CurrentInPtr, CurrentOutPtr are FFTSize*2 in
//!     length.
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
#endif //FLASH

    FPU_initSystemClocks();

    FPU_initEpie();
    
    // Clear input buffers:
    for(i=0; i < (CFFT_SIZE*2); i=i+2){
        CFFTin1Buff[i] = 0.0f;
        CFFTin1Buff[i+1] = 0.0f;
        CFFTin2Buff[i] = 0.0f;
        CFFTin2Buff[i+1] = 0.0f;
        CFFToutBuff[i] = 0.0f;
        CFFToutBuff[i+1] = 0.0f;
    }

    // Generate sample waveforms:
    //   CFFTin1Buff[0] = real[0]
    //   CFFTin1Buff[1] = imag[0]
    //   CFFTin1Buff[2] = real[1]
    //   ………
    //   CFFTin1Buff[N] = real[N/2]
    //   CFFTin1Buff[N+1] = imag[N/2]
    //   ………
    //   CFFTin1Buff[2N-3] = imag[N-2]
    //   CFFTin1Buff[2N-2] = real[N-1]
    //   CFFTin1Buff[2N-1] = imag[N-1]
    Rad = 0.0f;
    for(i=0; i < (CFFT_SIZE*2); i=i+2){
        CFFTin1Buff[i]   = sin(Rad) + cos(Rad*2.3567);       // Real Part
#if    (TEST_INPUT_REAL == 1)
        CFFTin1Buff[i+1] = 0;                                // Imaginary Part
#else //(TEST_INPUT_COMPLEX == 1)
        CFFTin1Buff[i+1] = cos(Rad*8.345) + sin(Rad*5.789);  // Imaginary Part
#endif //(TEST_INPUT_REAL == 1)

        CFFTin2Buff[i]   = CFFTin1Buff[i];   // Not used in calculation
        CFFTin2Buff[i+1] = CFFTin1Buff[i+1]; // Not used in calculation
        Rad = Rad + RadStep;
    }

    //
    // Off-Place Algorithm
    //
    // Note: In this version, CFFTin1Buff and CFFToutBuff are used in
    //       ping-pong fashion. The input data is first stored in CFFTin1Buff
    //       where the FFT, including bit reversed ordering, is initially done.
    //       At each successive stage of the FFT the cfft.CurrentInPtr pointer 
    //       will point to the buffer that is the input for that stage. In this
    //       manner the "CurrentInPtr" and "CurrentOutPtr" are exchanged at the
    //       start of each stage. Depending on the number of FFT stages, the 
    //       final output will be in either CFFTin1Buff (#Stages is odd) or 
    //       CFFToutBuff (#stages is even).
    hnd_cfft->CoefPtr = CFFTF32Coef;  //Twiddle factor table
    //Input/output (middle stage) of ping-pong buffer
    hnd_cfft->InPtr   = CFFTin1Buff;  
    //Output or middle stage of ping-pong buffer
    hnd_cfft->OutPtr  = CFFToutBuff;  
    hnd_cfft->Stages  = CFFT_STAGES;  // FFT stages
    hnd_cfft->FFTSize = CFFT_SIZE;    // FFT size

    CFFT_f32_sincostable(hnd_cfft);   // Calculate twiddle factor

    // Apply the window
#if    (TEST_INPUT_REAL == 1)
    CFFT_f32_win(&CFFTin1Buff[0], (float *)&CFFTwindow, CFFT_SIZE);
#else //(TEST_INPUT_COMPLEX == 1)
    CFFT_f32_win_dual(&CFFTin1Buff[0], (float *)&CFFTwindow, CFFT_SIZE);
#endif //(TEST_INPUT_REAL == 1)

    //=========================================================================
    // CFFT result:
    //     CurrentInPtr[0] = real[0]
    //     CurrentInPtr[1] = imag[0]
    //     CurrentInPtr[2] = real[1]
    //     ………
    //     CurrentInPtr[N] = real[N/2]
    //     CurrentInPtr[N+1] = imag[N/2]
    //     ………
    //     CurrentInPtr[2N-3] = imag[N-2]
    //     CurrentInPtr[2N-2] = real[N-1]
    //     CurrentInPtr[2N-1] = imag[N-1]
    //
    //=========================================================================

    CFFT_f32(hnd_cfft);                    // Calculate FFT

    // Check the output
    for(i = 0; i < 2*CFFT_SIZE; i++){
        if(fabs(CFFTgoldenOut[i] - hnd_cfft->CurrentInPtr[i]) <= EPSILON){
            pass++;
        }else{
            fail++;
        }
    }
    //
    // Note: The input buffer for the magnitude calculation is pointed to by
    //       cfft.CurrentInPtr, while the output is stored in the memory 
    //       pointed to by cfft.CurrentOutPtr. If the user does not changed
    //       the value of cfft.CurrentOutPtr after calling the magnitude 
    //       calculation function, the output buffer is overwritten when the
    //       phase calculation function is called
    //
    //       If number of Stages is ODD, 
    //           currentInPtr=CFFTin1Buff, currentOutPtr=CFFToutBuff
    //       If number of Stages is EVEN, 
    //           currentInPtr=CFFToutBuff, currentOutPtr=CFFTin1Buff
    //

    // Calculate Magnitude:
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           // properties
    // Calculate magnitude, result stored in CurrentOutPtr
    CFFT_f32_mag_TMU0(hnd_cfft);     
#else
    // Calculate magnitude, result stored in CurrentOutPtr    
    CFFT_f32_mag(hnd_cfft);          
#endif
    // Check the output
    for(i = 0; i < CFFT_SIZE; i++){
        if(fabs(CFFTgoldenMagnitude[i] - hnd_cfft->CurrentOutPtr[i]) <= 
                EPSILON){
            pass++;
        }else{
            fail++;
        }
    }
    // Magnitude Result:
    //  CurrentOutPtr[0] = Mag[0]
    //  CurrentOutPtr[1] = Mag[1]
    //  CurrentOutPtr[2] = Mag[2]
    //  ………
    //  CurrentOutPtr[N-1] = Mag[N-1]

    // Calculate Phase:
    // To avoid overwriting the magnitude, change the output buffer for 
    // the phase()
    hnd_cfft->CurrentOutPtr=CFFTin2Buff; 
                                         
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           //properties
    // Calculate phase, result stored in CurrentOutPtr
    CFFT_f32_phase_TMU0(hnd_cfft);        
#else
    // Calculate phase, result stored in CurrentOutPtr    
    CFFT_f32_phase(hnd_cfft);              
#endif
    // Check the output
    for(i = 0; i < CFFT_SIZE; i++){
        if(fabs(CFFTgoldenPhase[i] - hnd_cfft->CurrentOutPtr[i]) <= EPSILON){
            pass++;
        }else{
            fail++;
        }
    }
    // Phase Result:
    //  CurrentOutPtr[0] = Phase[0]
    //  CurrentOutPtr[1] = Phase[1]
    //  CurrentOutPtr[2] = Phase[2]
    //  ………
    //  CurrentOutPtr[N-1] = Phase[N-1]

    // End of test
    done();
    // Execution never reaches this point
    return 1;
}

// End of main

// @} //addtogroup

// End of file
