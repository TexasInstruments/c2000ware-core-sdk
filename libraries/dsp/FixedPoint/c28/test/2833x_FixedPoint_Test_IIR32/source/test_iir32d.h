#ifndef _TEST_IIR32D_H_
#define _TEST_IIR32D_H_
//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_Test_IIR32D/test_iir32d.h
//!
//! \brief  32-bit IIR test case
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
//! \addtogroup TEST_IIR Infinite Impulse Response Filter
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
// Filter Symbolic Constants
#define NUMBER_TESTS		5
#define TEST_1				1 //check if init function clears out dbuffer (even address)properly and whether memory corruption takes place
#define TEST_2				2 //check if init function clears out dbuffer (odd address) properly and whether memory corruption takes place
#define TEST_3				3 // butterworth LPF 11 Biquads
#define TEST_4				4 // chebyshev (type 1) LPF 5 Biquads
#define TEST_5				5 // chebyshev (type 2) HPF 6 Biquads
#define RUN_TEST			TEST_5

#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_2))
#define IIR32_NBIQ      	20
#define SIGNAL_LENGTH   	128
#elif ((RUN_TEST == TEST_3))
#define SIGNAL_LENGTH   	256
#define TOLERANCE			(1 << 3) // 2^-28 or 0.0000000037252902984619140625 or 3 LSbs of error
#elif ((RUN_TEST == TEST_4))
#define SIGNAL_LENGTH   	512
#define TOLERANCE			(1 << 6) // 2^-25 or 0.0000000298023223876953125 or 5 LSbs of error
#elif ((RUN_TEST == TEST_5))
#define SIGNAL_LENGTH   	512
#define TOLERANCE			(1 << 8) // 2^-23 or 0.00000011920928955078125 or 8 LSbs of error
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

#endif //end of _TEST_IIR32D_H_ definition
