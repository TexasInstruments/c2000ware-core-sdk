#ifndef _FASTRTS_EXAMPLES_SETUP_H_
#define _FASTRTS_EXAMPLES_SETUP_H_
//#############################################################################
//
//! \file   fastrts_examples_setup.h
//!
//! \brief  Fast RTS Examples Common Code
//! \author Ritvik Sadana
//! \date   Feb 2, 2018
//
//  Group:          C2000
//  Target Device:  TMS320F28004x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>
#include <float.h>
#include <math.h>
#include "device.h"
#include "fpu.h"

//!
//! \defgroup FASTRTS_EXAMPLES_SETUP Fast RTS Examples (f28004x) Setup Code

//!
//! \ingroup FASTRTS_EXAMPLES_SETUP
//@{

#ifdef __cplusplus

extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief The integer type of the error used in the FID error metrics
//! calculations
//!
typedef enum _FASTRTS_error_t_{
	ERRORTYPE_UI16 = 0,
	ERRORTYPE_I16  = 1,
	ERRORTYPE_UI32 = 2,
	ERRORTYPE_I32  = 3,
	ERRORTYPE_UI64 = 4,
	ERRORTYPE_I64  = 5,
}FASTRTS_error_t;

//*****************************************************************************
//globals
//*****************************************************************************
#if defined(_FLASH)
extern uint16_t RamfuncsRunStart, RamfuncsLoadStart, RamfuncsLoadSize;
#if defined(__TMS320C28XX_FPU64__)
extern uint16_t FPU64mathTablesRunStart, FPU64mathTablesLoadStart,
                FPU64mathTablesLoadSize;
#else
extern uint16_t FPUmathTablesRunStart, FPUmathTablesLoadStart,
                FPUmathTablesLoadSize;
#endif
#endif //defined(_FLASH)

// Each test will define these variables
extern uint16_t pass, fail;

extern uint64_t toleranceLSBMantissa;

#if USE_FID == 0
#if defined(__TMS320C28XX_FPU64__)
extern const float64_t test_input[];
extern const float64_t test_golden[];
extern float64_t test_output[];
#elif defined (__TMS320C28XX_FPU32__)
extern const float32_t test_input[];
extern const float32_t test_golden[];
extern float32_t test_output[];
#else
#error "--float_support=fpu64 option must be set to build the FPU64        \
    version of the library. --float_support=fpu32 must be set to build the \
    FPU32 version of the DSP library"
#endif //defined(__TMS320C28XX_FPU64__)
#else //USE_FID == 1
#if !defined(__TMS320C28XX_FPU64__)
#error "--float_support=fpu32 is not a valid option for Fast Integer \
    division (FID) operations. They only work with double precision hardware"
#endif // defined(__TMS320C28XX_FPU32__)

#if UI32BYUI32 == 1
extern const uint32_t test_dividend[], test_divisor[];
extern const uint32_t test_quotient[], test_remainder[];
extern uint32_t test_output_quo[], test_output_rem[];
extern uint32_t test_error_quo[], test_error_rem[];
#elif I32BYI32 == 1
extern const int32_t test_dividend[], test_divisor[];
extern const int32_t test_quotient[], test_remainder[];
extern int32_t test_output_quo[], test_output_rem[];
extern int32_t test_error_quo[], test_error_rem[];
#elif I32BYUI32 == 1
extern const int32_t test_dividend[];
extern const uint32_t test_divisor[];
extern const int32_t test_quotient[], test_remainder[];
extern int32_t test_output_quo[], test_output_rem[];
extern int32_t test_error_quo[], test_error_rem[];
#elif UI64BYUI32 == 1
extern const uint64_t test_dividend[], test_quotient[];
extern const uint32_t test_divisor[], test_remainder[];;
extern uint64_t test_output_quo[], test_error_quo[];
extern uint32_t test_output_rem[], test_error_rem[];
#elif I64BYI32 == 1
extern const int64_t test_dividend[], test_quotient[];
extern const int32_t test_divisor[], test_remainder[];;
extern int64_t test_output_quo[], test_error_quo[];
extern int32_t test_output_rem[], test_error_rem[];
#elif I64BYUI32 == 1
extern const int64_t test_dividend[], test_quotient[], test_remainder[];
extern const uint32_t test_divisor[];
extern int64_t test_output_quo[], test_error_quo[];
extern int64_t test_output_rem[], test_error_rem[];
#elif I64BYUI64 == 1
extern const int64_t test_dividend[], test_quotient[], test_remainder[];
extern const uint64_t test_divisor[];
extern int64_t test_output_quo[], test_error_quo[];
extern int64_t test_output_rem[], test_error_rem[];
#elif UI64BYUI64 == 1
extern const uint64_t test_dividend[], test_quotient[];
extern const uint64_t test_divisor[], test_remainder[];;
extern uint64_t test_output_quo[], test_error_quo[];
extern uint64_t test_output_rem[], test_error_rem[];
#elif I64BYI64 == 1
extern const int64_t test_dividend[], test_quotient[];
extern const int64_t test_divisor[], test_remainder[];;
extern int64_t test_output_quo[], test_error_quo[];
extern int64_t test_output_rem[], test_error_rem[];
#elif UI16BYUI16 == 1
extern const uint16_t test_dividend[], test_divisor[];
extern const uint16_t test_quotient[], test_remainder[];
extern uint16_t test_output_quo[], test_output_rem[];
extern uint16_t test_error_quo[], test_error_rem[];
#elif I16BYI16 == 1
extern const int16_t test_dividend[], test_divisor[];
extern const int16_t test_quotient[], test_remainder[];
extern int16_t test_output_quo[], test_output_rem[];
extern int16_t test_error_quo[], test_error_rem[];
#elif UI32BYUI16 == 1
extern const uint32_t test_dividend[], test_quotient[];
extern const uint16_t test_divisor[], test_remainder[];
extern uint32_t test_output_quo[], test_error_quo[];
extern uint16_t test_output_rem[], test_error_rem[];
#elif I32BYI16 == 1
extern const int32_t test_dividend[], test_quotient[];
extern const int16_t test_divisor[], test_remainder[];;
extern int32_t test_output_quo[], test_error_quo[];
extern int16_t test_output_rem[], test_error_rem[];
#elif F64BYF64 == 1
extern const float64_t test_dividend[], test_quotient[];
extern const float64_t test_divisor[];
extern float64_t test_output_quo[], test_error_quo[];
#else
#warn "Need to choose an integer division type in fastrts_examples_setup.h"
#endif
#endif //USE_FID


//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Setup system controls
//! 
extern void FastRTS_Example_setupSysCtrl( void );


//! \brief Setup flash
//! 
extern void FastRTS_Example_setupFlash( void );

//! \brief Run a particular Fast RTS routine
//! 
extern void FastRTS_runTest( void );

//! \brief Function indicating end of test (Autobot regression)
//! 
extern void done( void );

//! \brief Error calculation
//!
//! This function computes the double precision error between the output
//! obtained from running one of the library routines on the target
//! devices and the golden reference obtained from running a similar
//! routine in MATLAB on an x86 platform.
//!
//! The error is stored to an array and then compared against a user provided
//! tolerance value. If the error is found to be within bounds the function
//! returns a 1, else a -1. It also calculates how many ULPs of difference
//! exist between the output and golden and returns it in a user passed
//! variable. If the ULPs are within tolerance the function returns 2
//!
//! \param[in]  p_out , pointer to the calculated output
//! \param[in]  p_gold , pointer to the golden reference
//! \param[out] p_lderr , pointer to the double precision error
//! \param[out] p_ullerr , pointer to the unsigned long long error
//! \param[in]  ldtol , double precision tolerance
//! \param[in]  ulltol , Erroneous ULPs
//!
//! \returns
//! - 1  , if the double precision error is within tolerable limits
//! - 2  , additionally if the ULP of the error is withing limits
//! - -1 , if either check fails
//!
int16_t FastRTS_Example_calcError(const float64_t *p_out,
                                  const float64_t *p_gold,
                                  const float64_t *p_lderr,
                                  const uint64_t  *p_ullerr,
                                  const float64_t *p_ldtol,
                                  const uint64_t  ulltol);
 
//! \brief Error calculation for the FID examples
//!
//! This function computes the error between the output
//! obtained from running one of the FID library routines on the target
//! devices and the golden reference obtained from running a similar
//! routine in MATLAB on an x86 platform.
//!
//! The error is stored to an array and then compared against a user provided
//! tolerance value. If the error is found to be within bounds the function
//! returns a 1, else a -1.
//!
//! \param[in]  p_out , pointer to the calculated output
//! \param[in]  p_gold , pointer to the golden reference
//! \param[out] p_err , pointer to the error
//! \param[in]  p_tol , pointer to the tolerance
//! \param[in]  et , the type of the error
//!
//! \returns
//! - 1  , if the double precision error is within tolerable limits
//! - -1 , if the check fails
//! 
int16_t FID_Example_calcError(const void *p_out,
                              const void *p_gold,
                              const void *p_err,
                              const void *p_tol,
                              const FASTRTS_error_t et);
#ifdef __cplusplus
{
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _FASTRTS_EXAMPLES_SETUP_H_ definition

// End of File
