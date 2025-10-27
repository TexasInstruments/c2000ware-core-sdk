//#############################################################################
//! \file /28P55x_icftt_fpu32.c
//!
//! \brief  Demo code for the Inverse Complex FFT
//!
//! This example shows how to compute the Inverse FFT on an N point complex
//! data
//!
//
//  Group:             C2000
//  Target Family:     F28P55x
//
//#############################################################################
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
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
//! \addtogroup CFFT_EXAMPLES Complex Fast Fourier Transform

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define CFFT_STAGES     8
#define CFFT_SIZE       (1 << CFFT_STAGES)
#define EPSILON         0.01
//#define USE_TABLE   // If using pre-defined FFT Twiddle Factor Table
                      // Check "Use Predefined Twiddle Factors" in sysconfig to enable the support

//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("CFFTdata1")
#pragma DATA_SECTION("CFFTdata2")
#pragma DATA_SECTION("CFFTdata3")
#else
#pragma DATA_SECTION(CFFTin1Buff,"CFFTdata1")
#pragma DATA_SECTION(CFFTmagBuff,"CFFTdata2")
#pragma DATA_SECTION(CFFToutBuff,"CFFTdata3")
#endif //__cplusplus

//! \brief FFT Calculation Buffer
//! \note The input buffer needs to be aligned to a 4N word boundary (N is the size of fft), in this case 4*2^7 = 512
//! \note If the number of FFT stages is odd, the result of the FFT will
//! be written to this buffer
//!
float32_t CFFTin1Buff[CFFT_SIZE*2];
float32_t* in1Ptr = CFFTin1Buff;

//! \brief Magnitude Calculation Buffer
//!
float32_t CFFTmagBuff[CFFT_SIZE*2];
float32_t* magPtr = CFFTmagBuff;

//! \brief FFT Calculation Buffer
//! \note If the number of FFT stages is even, the result of the FFT will
//! be written to this buffer
//!
float32_t CFFToutBuff[CFFT_SIZE*2];
float32_t* outPtr = CFFToutBuff;

float32_t CFFTgoldenOut[CFFT_SIZE*2] = {
    #include "data_input_icfft.h"
};

float32_t CFFTTwiddleCoef[CFFT_SIZE];
float32_t* twiddlePtr = CFFTTwiddleCoef;

float32_t RadStep = 0.1963495408494f; // Step to generate test bench waveform
float32_t Rad = 0.0f;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Inverse Complex FFT example
//! \return returns a 1
//!
//! The test functions include CFFT_f32,CFFT_f32_mag and ICFFT_f32.
//! Data section alignment (#pragma ...) is not necessary for CFFT_f32u
//! but necessary for testing CFFT_f32.
//!
//! Minimum CFFT_Stages is 3. When CFFT_Stages is more than 9, the
//! quantization error would be significant. The results can be compared
//! against MATLAB code under 2837x_CFFT/matlab/CFFTforC28xNew. The inverse
//! FFT should give the original input
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
//! -# OutPtr           Output or middle stage of ping-pong buffer
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
int icfft_fpu32_test(void)
{
    // Clear input buffers:
    memset(in1Ptr, 0, CFFT_SIZE*2*sizeof(float32_t));
    memset(magPtr, 0, CFFT_SIZE*2*sizeof(float32_t));
    memset(outPtr, 0, CFFT_SIZE*2*sizeof(float32_t));

    // Generate sample waveforms:
    //       CFFTin1Buff[0] = real[0]
    //       CFFTin1Buff[1] = imag[0]
    //       CFFTin1Buff[2] = real[1]
    //       ………
    //       CFFTin1Buff[N] = real[N/2]
    //       CFFTin1Buff[N+1] = imag[N/2]
    //       ………
    //       CFFTin1Buff[2N-3] = imag[N-2]
    //       CFFTin1Buff[2N-2] = real[N-1]
    //       CFFTin1Buff[2N-1] = imag[N-1]
    int i;
    Rad = 0.0f;
    for(i = 0; i < (CFFT_SIZE*2); i=i+2)
    {
        CFFTin1Buff[i]   = sinf(Rad) + cosf(Rad*2.3567);       // Real Part
        CFFTin1Buff[i+1] = cosf(Rad*8.345) + sinf(Rad*5.789);  // Imaginary Part
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

    // Note: All setup & initialization for cfft are taken care of by sysconfig

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
    // Note: CFFT_f32/CFFT_f32t requires proper alignment of input buffer, to a memory address of 4N words (N is the size of fft).
    // If alignment is not possible the user can use the alternative, albeit slower, function CFFT_f32u / CFFT_f32ut
#ifdef USE_TABLES
    CFFT_f32t(myCFFT0_handle);                   // Calculate FFT using pre-defined twiddle factor table
#else
    CFFT_f32(myCFFT0_handle);                    // Calculate FFT using custom table
#endif //USE_TABLES

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
    myCFFT0_handle->CurrentInPtr  = CFFToutBuff; // Mag function input pointer
    myCFFT0_handle->CurrentOutPtr = CFFTmagBuff; // Mag function output pointer
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu in the project properties
    // Calculate magnitude, result stored in CurrentOutPtr
    CFFT_f32_mag_TMU0(myCFFT0_handle);
#else
    // Calculate magnitude, result stored in CurrentOutPtr
    CFFT_f32_mag(myCFFT0_handle);
#endif
    // Magnitude Result:
    //       CurrentOutPtr[0] = Mag[0]
    //       CurrentOutPtr[1] = Mag[1]
    //       CurrentOutPtr[2] = Mag[2]
    //       ………
    //       CurrentOutPtr[N-1] = Mag[N-1]

    // Perform the iCFFT to recover the input data
    myCFFT0_handle->InPtr  = CFFToutBuff;        // ICFFT input pointer
    myCFFT0_handle->OutPtr = CFFTin1Buff;        // ICFFT output pointer
#ifdef USE_TABLES
    ICFFT_f32t(myCFFT0_handle);                  // Calculate the ICFFT
#else
    ICFFT_f32(myCFFT0_handle);                   // Calculate the ICFFT
#endif //USE_TABLES

    // Check the output
    for(i = 0; i < 2*CFFT_SIZE; i++){
        if(fabsf(CFFTgoldenOut[i] - myCFFT0_handle->CurrentInPtr[i]) <= EPSILON){
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

    icfft_fpu32_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
