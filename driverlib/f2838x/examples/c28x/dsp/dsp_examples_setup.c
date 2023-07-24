//#############################################################################
//
//! \file   dsp_examples_setup.c
//!
//! \brief  DSP Examples Common Code
//! \author Ritvik Sadana
//! \date   Jan 8, 2018
//
//  Group:          C2000

//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2022 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "dsp_examples_setup.h"
#include "sysctl.h"
#include "fpu.h"


//*****************************************************************************
// the defines
//*****************************************************************************
#if defined(ADC_INPUT)
#define TEST_SIZE       (256U) //must be same as dsp_rfft_adc.c
                               //fpu32 examples, set to 512U
                               //fpu64 examples, set to 512U
#endif //defined(ADC_INPUT)

//*****************************************************************************
// the globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("FpuRegsFile")
#else
#pragma DATA_SECTION(FpuRegs,"FpuRegsFile");
#endif
//! \brief FPU Register object
//
volatile struct FPU_REG FpuRegs;


// End of File
