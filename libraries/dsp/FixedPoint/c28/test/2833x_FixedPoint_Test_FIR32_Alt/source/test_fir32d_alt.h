#ifndef _TEST_FIR32D_ALT_H_
#define _TEST_FIR32D_ALT_H_
//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_Test_FIR32D/test_fir32d_alt.h
//!
//! \brief  Alternate 32-bit FIR test case
//! \date   Sep 22, 2014
//!
//
//  Group: 			C2000
//  Target Family:	F2837x
//
//#############################################################################
//
//
//$Copyright: Copyright (C) 2014-2023 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include <stdint.h>
#include <string.h>
//!
//! \addtogroup TEST_FIR Finite Impulse Response Filter
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define NUMBER_TESTS		9
//Tests 1-2 merely check if the init() works properly.
#define TEST_1				1 //check if init function clears out dbuffer properly and whether memory corruption takes place
                              // dbuffer at odd address, odd order filter
#define TEST_2				2 //check if init function clears out dbuffer properly and whether memory corruption takes place
							  // dbuffer at even address, even order filter
#define TEST_3				3 // odd order filter < 127, multi freq input
#define TEST_4				4 // odd order filter < 127, impulse input
#define TEST_5				5 // even order filter < 127, impulse input
#define TEST_6				6 // even order filter < 127, multi freq input
#define TEST_7				7 // odd order filter = 127, multi freq input
#define TEST_8				8 // odd order filter = 511, multi freq input
#define TEST_9				9 // even order filter = 512, multi freq input
#define TEST_10				10 // not a test, used for benchmarking
#define RUN_TEST			TEST_10

#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) )
#define FIR_ORDER       43
#define SIGNAL_LENGTH   128
#define TOLERANCE		(1 << 6) // 2^-25 or 0.0000000298023223876953125 or 6 LSbs of error
#elif ((RUN_TEST == TEST_2) || (RUN_TEST == TEST_5) || (RUN_TEST == TEST_6))
#define FIR_ORDER       44
#define SIGNAL_LENGTH   128
#define TOLERANCE		(1 << 6) // 2^-25 or 0.0000000298023223876953125 or 6 LSbs of error
#elif (RUN_TEST == TEST_7)
#define FIR_ORDER       127
#define SIGNAL_LENGTH   256
#define TOLERANCE		(1 << 7) // 2^-24 or 0.000000059604644775390625 or 7 LSbs of error
#elif (RUN_TEST == TEST_8)
#define FIR_ORDER       511
#define SIGNAL_LENGTH   512
#define TOLERANCE		(1 << 9) // 2^-22 or 0.0000002384185791015625 or 8 LSbs of error
#elif (RUN_TEST == TEST_9)
#define FIR_ORDER       512
#define SIGNAL_LENGTH   1024
#define TOLERANCE		(1 << 9) // 2^-22 or 0.0000002384185791015625 or 8 LSbs of error
#elif (RUN_TEST == TEST_10)
#define FIR_ORDER       1023
#define SIGNAL_LENGTH   1024
#define TOLERANCE		(1 << 5) // 2^-10 or 0.0009765625 or 5 LSbs of error
#endif

#define FIR_ORDER_REV   FIR_ORDER
//*****************************************************************************
// typedefs - variables defined in the header only for doxygen purposes.
//            they dont need to be global(extern)
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief Input buffer
//! \note Buffer needs to be aligned on a 256 word
//! boundary for the circular addressing mode to work correctly
//!
extern int32_t sigIn[SIGNAL_LENGTH];

//! \brief Output buffer
//! \note Buffer needs to be aligned on a 256 word
//! boundary for the circular addressing mode to work correctly
//!
extern int32_t sigOut[SIGNAL_LENGTH];
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

#endif //end of _TEST_FIR32D_ALT_H_ definition
