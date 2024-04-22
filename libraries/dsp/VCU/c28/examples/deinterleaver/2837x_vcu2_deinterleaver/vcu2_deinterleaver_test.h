#ifndef _VCU2_DEINTERLEAVER_TEST_H_
#define _VCU2_DEINTERLEAVER_TEST_H_
//#############################################################################
//! \file f2837x/F2837x_internal_testcases/VCUII/vcu2_deinterleaver/vcu2_deinterleaver_test.h
//!
//! \brief  OFDM Deinterleaver
//!
//! \date   Feb 21, 2013
//! 
//
//  Group: 			C2000
//  Target Family:	F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "DEINTERLEAVER.h"
//!
//! \addtogroup VCUII_DEFINITIONS  De-interleaver
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define  MAX_NUM_BITS        4096
#define  MAX_NUM_WORDS       (MAX_NUM_BITS/16)
#define  MIN_N               4
#define  MAX_N               250 //511
#define  MIN_M               36  //6
#define  MAX_M               72
//*****************************************************************************
// typedefs - variables defined in the header only for doxygen purposes.
//            they dont need to be global(extern)
//*****************************************************************************


//*****************************************************************************
// globals
//*****************************************************************************
//! \brief Input sequence
//! 
extern uint16_t testInput[MAX_NUM_WORDS];

//! \brief DE-interleaved bits
//!
extern uint16_t deinterleavedOutput[MAX_NUM_BITS];

//! \brief interleaved bits
//!
extern uint16_t interleavedOutput[MAX_NUM_BITS];

//! \brief golden output
//!
extern uint16_t goldenOutput[MAX_NUM_BITS];
//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Run test
//!
Bool_e VCU2_runTest(void);

//! \brief TODO
//!
Bool_e VCU2_genReport(void);

//! \brief clears out a buffer
//! \param[in] buf_p pointer to the source buffer
//!
void test_init(uint16_t * buf_p);

//! \brief divide by zero interrupt service routine
//!
interrupt void DEINTERLEAVER_divEIsr(void);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //addtogroup

#endif //end of _VCU2_DEINTERLEAVER_TEST_H_ definition
