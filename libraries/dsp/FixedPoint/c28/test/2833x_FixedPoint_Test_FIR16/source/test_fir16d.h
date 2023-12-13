#ifndef _TEST_FIR16D_H_
#define _TEST_FIR16D_H_
//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_Test_FIR16D/test_fir16d.h
//!
//! \brief  16-bit FIR test case
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
#define NUMBER_TESTS		7
//Tests 1-2 merely check if the init() works properly. dbuffer is meant to be
// aligned to a 256 word boundary for proper operation
#define TEST_1				1 //check if init function clears out dbuffer properly and whether memory corruption takes place
                              // dbuffer at odd address, odd order filter
#define TEST_2				2 //check if init function clears out dbuffer properly and whether memory corruption takes place
							  // dbuffer at even address, even order filter
#define TEST_3				3 // odd order filter < 127, impulse input
#define TEST_4				4 // odd order filter < 127, multi freq input
#define TEST_5				5 // even order filter < 127, impulse input
#define TEST_6				6 // even order filter < 127, multi freq input
#define TEST_7				7 // odd order filter = 127, multi freq input
#define TEST_8				8 // not a test, used for benchmarking
#define RUN_TEST			TEST_8


// Filter Symbolic Constants
#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) )
#define FIR_ORDER       43
#define SIGNAL_LENGTH   128
#define TOLERANCE		(1 << 3) // 2^-12 or 0.000244140625 or 3 LSbs of error
#elif ((RUN_TEST == TEST_2) || (RUN_TEST == TEST_5) || (RUN_TEST == TEST_6))
#define FIR_ORDER       44
#define SIGNAL_LENGTH   128
#define TOLERANCE		(1 << 3) // 2^-12 or 0.000244140625 or 3 LSbs of error
#elif (RUN_TEST == TEST_7)
#define FIR_ORDER       127
#define SIGNAL_LENGTH   256
#define TOLERANCE		(1 << 3) // 2^-12 or 0.000244140625 or 3 LSbs of error
#elif (RUN_TEST == TEST_8)
#define FIR_ORDER       255
#define SIGNAL_LENGTH   1024
#define TOLERANCE		(1 << 5) // 2^-10 or 0.0009765625 or 5 LSbs of error
#endif

#if(FIR_ORDER & 0x01)   // odd
#define FIR_ORDER_REV   (FIR_ORDER + 1) // even
#else
#define FIR_ORDER_REV   (FIR_ORDER + 2) // even
#endif


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
extern int16_t sigIn[SIGNAL_LENGTH];

//! \brief Output buffer
//! \note Buffer needs to be aligned on a 256 word
//! boundary for the circular addressing mode to work correctly
//!
extern int16_t sigOut[SIGNAL_LENGTH];
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

#endif //end of _TEST_FIR16D_H_ definition
