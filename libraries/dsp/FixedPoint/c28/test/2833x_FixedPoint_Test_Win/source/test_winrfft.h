#ifndef _TEST_WINRFFT_H_
#define _TEST_WINRFFT_H_
//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_Test_Win/test_winrfft.h
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
#define NUMBER_TESTS		2
#define TEST_1				1  //! hamming window, check RFFT32_win()
#define TEST_2				2  //! hamming window, check CFFT32_win()
#define TEST_3				3  //! hamming window, check CFFT32_dual_win()

#define RUN_TEST		 	TEST_3

#if RUN_TEST == TEST_1
#define FFT_SIZE            32
#define TOLERANCE			(1 << 2)  //! 2 LSbs
#elif RUN_TEST == TEST_2
#define FFT_SIZE            32
#define TOLERANCE			(1 << 2)  //! 2 LSbs
#elif RUN_TEST == TEST_3
#define FFT_SIZE            1024
#define TOLERANCE			(1 << 2)  //! 2 LSbs

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

#endif //end of _TEST_WINRFFT_H_ definition
