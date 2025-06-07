#ifndef _TEST_RFFT_H_
#define _TEST_RFFT_H_
//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_Test_RFFT/test_rfft.h
//!
//! \brief  real FFT test case
//! \date   Sep 22, 2014
//!
//
//  Group: 			C2000
//  Target Family:	F2837x
//
//#############################################################################
//
//
//$Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>
#include <string.h>
//!
//! \addtogroup TEST_RFFT  Real Fast-Fourier Transform
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define NUMBER_TESTS		18
#define TEST_1				1 // Check the bit reversal routine
#define TEST_2				2 // Check if bit reversal routine exceeds memory bounds

// Tests 3:18, change FFT_ALIGN in the linker command file to 2N, N being the number of samples
// For e.g. for N = 32, set FFT_ALIGN to 0x40 (64)
#define TEST_3				3 // 32 pt FFT, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_4				4 // 64 pt FFT, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_5				5 // 128 pt FFT, golden result from MATLAB "FixedPointCFFT.m"
// Tests 6-10 are "_FLASH" build tests only and will not work in the "RAM" build configuration
#define TEST_6				6 // 256 pt FFT, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_7				7 // 512 pt FFT, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_8				8 // 1024 pt FFT, golden result from MATLAB "FixedPointCFFT.m"
// For this test, exclude F28335_FIXPT_FFT_lnk.cmd from the project and use
//F28335_FIXPT_RFFT_2048_lnk.cmd instead.
#define TEST_9				9 // 2048 pt FFT, golden result from MATLAB "FixedPointCFFT.m"
// N = 4096 requires 2 buffers of size 8192 words each and another 8192 words of ebss space to work
#define TEST_10				10 // 4096 pt FFT, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_11				11 // 32 pt FFT mag, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_12				12 // 64 pt FFT mag, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_13				13 // 128 pt FFT mag, golden result from MATLAB "FixedPointCFFT.m"
// Tests 14-18 are "_FLASH" build tests only and will not work in the "RAM" build configuration
#define TEST_14				14 // 256 pt FFT mag, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_15				15 // 512 pt FFT mag, golden result from MATLAB "FixedPointCFFT.m"
#define TEST_16				16 // 1024 pt FFT mag, golden result from MATLAB "FixedPointCFFT.m"
// For this test, exclude F28335_FIXPT_FFT_lnk.cmd from the project and use
//F28335_FIXPT_RFFT_2048_lnk.cmd instead.
#define TEST_17				17 // 2048 pt FFT mag, golden result from MATLAB "FixedPointCFFT.m"
// N = 4096 requires 2 buffers of size 8192 words each and another 8192 words of ebss space to work
#define TEST_18				18 // 4096 pt FFT mag, golden result from MATLAB "FixedPointCFFT.m"


#define RUN_TEST            TEST_1
#if RUN_TEST == TEST_1
#define FFT_SIZE            128
#elif RUN_TEST == TEST_2
#define FFT_SIZE            32
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_11))
#define FFT_SIZE            32
#define TOLERANCE			(1UL << 15) // tolerance of 15 bits variation i.e 2^-16 = 0.0000152587890625
#elif ((RUN_TEST == TEST_4) || (RUN_TEST == TEST_12))
#define FFT_SIZE            64
#define TOLERANCE			(1UL << 15) // tolerance of 15 bits variation i.e 2^-16 = 0.0000152587890625
#elif ((RUN_TEST == TEST_5) || (RUN_TEST == TEST_13))
#define FFT_SIZE            128
#define TOLERANCE			(1UL << 15) // tolerance of 15 bits variation i.e 2^-16 = 0.0000152587890625
#elif ((RUN_TEST == TEST_6) || (RUN_TEST == TEST_14))
#define FFT_SIZE            256
#define TOLERANCE			(1UL << 15) // tolerance of 15 bits variation i.e 2^-16 = 0.0000152587890625
#elif ((RUN_TEST == TEST_7) || (RUN_TEST == TEST_15))
#define FFT_SIZE            512
#define TOLERANCE			(1UL << 15) // tolerance of 15 bits variation i.e 2^-16 = 0.0000152587890625
#elif ((RUN_TEST == TEST_8) || (RUN_TEST == TEST_16))
#define FFT_SIZE            1024
#define TOLERANCE			(1UL << 15) // tolerance of 15 bits variation i.e 2^-16 = 0.0000152587890625
#elif ((RUN_TEST == TEST_9) || (RUN_TEST == TEST_17))
#define FFT_SIZE            2048
#define TOLERANCE			(1UL << 15) // tolerance of 15 bits variation i.e 2^-16 = 0.0000152587890625
#elif ((RUN_TEST == TEST_10) || (RUN_TEST == TEST_18))
#define FFT_SIZE            4096
#define TOLERANCE			(1UL << 15) // tolerance of 15 bits variation i.e 2^-16 = 0.0000152587890625
#endif
//*****************************************************************************
// typedefs - variables defined in the header only for doxygen purposes.
//            they dont need to be global(extern)
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief Input computation buffer
//! \note Buffer needs to be aligned on a 2*FFT_SIZE long word
//! boundary for the bit reversal to work correctly
//!
extern int32_t ipcb[];

//! \brief FFT computation buffer
//!
extern int32_t ipcbsrc[];
//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Run test
//! \param test test number to run
//!
//! - Step 1: Initialize the object
//! - Step 2: Run the sequence of tests
//! - Step 3: update pass/fail metrics
//!
uint16_t FIXPT_DSP_runTest();

//! \brief pass/fail report generation
//! \param test test number to run
//! \param array to keep track of the pass/fails
//!
uint16_t FIXPT_DSP_genReport();

#ifdef __cplusplus
}
#endif // extern "C"

// @} //addtogroup

#endif //end of _TEST_RFFT_H_ definition
