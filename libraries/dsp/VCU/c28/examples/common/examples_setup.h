#ifndef _VCU2_EXAMPLES_SETUP_H_
#define _VCU2_EXAMPLES_SETUP_H_
//#############################################################################
//! \file /examples_ccsv5/common/examples_setup.h
//!
//! \brief  Initialization routines for the VCU2 library examples
//!
//! \date   July 16, 2013
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
#include "F28x_Project.h"

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define CPU_FRQ_200MHZ	1

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************
// \brief Initialize system clocks
//
void VCU2_initSystemClocks(void);

// \brief Initialize Enhanced PIE
//
void VCU2_initEpie(void);

// \brief Initialize Flash
//
void VCU2_initFlash(void);

// \brief Disable Flash prefetch
//
extern void InitFlash_PrefetchCacheDisable(void);

// \brief Enable Flash prefetch
//
extern void InitFlash_PrefetchCacheEnable(void);

// \brief Set Flash wait states
// \param[in] waitStates The number of wait states
//
void SetupFlash(unsigned short waitStates);

// \brief autobot done()
//
void done(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _VCU2_EXAMPLES_SETUP_H_ definition
