#ifndef _EXAMPLES_SETUP_H_
#define _EXAMPLES_SETUP_H_
//#############################################################################
//! \file /examples/common/examples_setup.h
//!
//! \brief  Initialization routines for the FPU library examples
//! \author Vishal Coelho
//! \date   Feb 26, 2015
//
//  Group:             C2000

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
#include "F28x_Project.h"

//! \defgroup FPU_LIB_EXAMPLE_SETUP FPU Library Example Setup Code

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define CPU_FRQ_200MHZ          1
#define ADC_SAMPLING_FREQ       100000.0L
#define EPWM_HSPCLKDIV          1           //EPWM_CLOCK is SYSCLK/(2*2)
#define EPWM1_PERIOD            500
#define EPWM1_DUTY_CYCLE        250
#define EPWM2_PERIOD            50000
#define EPWM2_DUTY_CYCLE        25000

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Initialize system clocks
//!
void FPU_initSystemClocks(void);

//! \brief Initialize Enhanced PIE
//!
void FPU_initEpie(void);

//! \brief Initialize Flash
//!
void FPU_initFlash(void);

//! \brief Initialize ADCA
//!
void FPU_initADCA(void);

//! \brief Initialize EPWM1 and 2
//!
void FPU_initEPWM(void);

//! \brief start EPWMs
//!
void FPU_startEPWM(void);

//! \brief Disable Flash prefetch
//!
extern void InitFlash_PrefetchCacheDisable(void);

//! \brief Enable Flash prefetch
//!
extern void InitFlash_PrefetchCacheEnable(void);

//! \brief Set Flash wait states
//! \param[in] waitStates The number of wait states
//!
void SetupFlash(unsigned short waitStates);

//! \brief autobot done()
//!
void done(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _EXAMPLES_SETUP_H_ definition

// End of file
