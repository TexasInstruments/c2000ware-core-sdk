#ifndef _DSP_EXAMPLES_SETUP_H_
#define _DSP_EXAMPLES_SETUP_H_
//#############################################################################
//
//! \file   dsp_examples_setup.h
//!
//! \brief  DSP Examples Common Code
//!
//! \date   Jan 8, 2016
//
//  Group:          C2000

//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2020 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>
#include <float.h>
#include <math.h>
#include "device.h"
#include "inc/hw_types.h"

//!
//! \defgroup DSP_EXAMPLES_SETUP DSP Examples Setup Code

//!
//! \ingroup DSP_EXAMPLES_SETUP
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//globals
//*****************************************************************************
#if defined(_FLASH)
extern uint16_t RamfuncsRunStart, RamfuncsLoadStart, RamfuncsLoadSize;
#endif //defined(_FLASH)

//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief Setup system controls
//! 
extern void DSP_Example_setupSysCtrl( void );

//! \brief Function to disable pin locks and enable pullups on GPIOs.
//!
extern void DSP_Example_initGPIO(void);

//! \brief Setup flash
//! 
extern void DSP_Example_setupFlash( void );

//! \brief Run a particular Fast RTS routine
//! 
extern void DSP_runTest( void );

extern void done( void );

#ifdef __cplusplus
}
#endif // extern "C"
//@}  // ingroup

#endif  // end of  _DSP_EXAMPLES_SETUP_H_ definition

// End of File
