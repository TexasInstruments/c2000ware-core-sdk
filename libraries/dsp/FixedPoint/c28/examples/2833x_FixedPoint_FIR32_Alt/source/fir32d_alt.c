//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_FixedPoint_FIR32_Alt/fir32d_alt.c
//!
//! \brief  Alternate 32-bit FIR Filter Example
//!
//! \date   Aug 12, 2014
//! 
//! This module shows an alternate 32-bit FIR implementation. The alternate
//! version can have upto 2^16 or 65536 filter taps.
//! The header structure of 32 bit filter is shown as follows:
//! 
//! typedef struct { 
//!     int32_t *coeff_ptr;        
//!     int32_t * dbuffer_ptr;
//!     int	cbindex;
//!     int order; 
//!     int input;   
//!     int output; 
//!     void (*init)(void *);
//!     void (*calc)(void *);
//!     }FIR32; 
//! 
//! Users can also use default templates defined within fir.h to initialize 
//! the FIR32 header structure.
//!                 
//! FIR32  fir= FIR32_ALT_DEFAULTS;
//! 
//! The MATLAB Filter Design and Analysis Tool (FDATool) is a useful tool 
//! for designing filters and generating fixed point coefficients. Refer
//! to the appendix of the Fixed Point DSP Libray User's Guide for more
//! information.
//! 
//! \b Watch \b Variables
//! - fir   FIR32 object
//! 
//! In CCS, you can invoke the "SetupDebugEnv.js" script from the 
//! Scripting console to have these variables set up in the Watch window
//! and create graphs to show the input/output vectors
//
//  Group:            C2000
//  Target Family:    C28x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "examples_setup.h"
#include <filter.h>
 
//*****************************************************************************
// defines
//*****************************************************************************
// Filter Symbolic Constants
#define FIR_ORDER       43
#define FIR_ORDER_REV   FIR_ORDER
#define SIGNAL_LENGTH   128
#define TOLERANCE       (1UL << 20) // 0.009765 in Q31

//*****************************************************************************
// globals
//*****************************************************************************                                        
// Create an Instance of FIR32 module and place the object in "firfilt" section 
#ifndef __cplusplus
#pragma DATA_SECTION(fir, "firfilt");
#else
#pragma DATA_SECTION("firfilt");
#endif
FIR32 fir= FIR32_ALT_DEFAULTS;
                                            
// Define the Delay buffer for the "FIR_ORDER"th order filter
// and place it in "firldb" section. 
// Its size should be FIR_ORDER+1
// For the alternate FIR implementation, the delay line buffer need
// not be aligned to a specific boundary
#ifndef __cplusplus
#pragma DATA_SECTION(dbuffer,"firldb");
#else
#pragma DATA_SECTION("firfilt");
#endif
int32_t dbuffer[FIR_ORDER+1];

// Input/output buffer 
#ifndef __cplusplus
#pragma DATA_SECTION(sigIn, "sigIn");
#else
#pragma DATA_SECTION("sigIn");
#endif
int32_t sigIn[SIGNAL_LENGTH] = {
    #include "data_input.txt"
};

#ifndef __cplusplus
#pragma DATA_SECTION(sigOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int32_t sigOut[SIGNAL_LENGTH];                               
         
#ifndef __cplusplus
#pragma DATA_SECTION(goldOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int32_t goldOut[SIGNAL_LENGTH] = {
    #include "data_output.txt"
}; 

// Error between computed output and MATLAB output
int32_t err[SIGNAL_LENGTH];

// Define Constant Coefficient Array  and place it in the "coefffilt"
// section. You can either reverse the order of the coefficients at 
// run time (done in this example) or just store them in reversed order.
// Index       
//         +---------+
//  0      | h(L-1)  |
//  2      | h(L-2)  |
//  4      | h(L-3)  |
//  6      | h(L-4)  |
//  ...    | ...     |
//  L-3    | h(2)    |
//  L-2    | h(1)    |
//  L-1    | h(0)    |
//         +---------+
// The size of the array is FIR_ORDER+1
//
#ifndef __cplusplus
#pragma DATA_SECTION(coeff, "coefffilt");
#else
#pragma DATA_SECTION("coefffilt");
#endif
const int32_t coeff[FIR_ORDER+1] = {
    #include "coeffs.txt"
};

#ifndef __cplusplus
#pragma DATA_SECTION(revCoeff, "coefffilt");
#else
#pragma DATA_SECTION("coefffilt");
#endif
int32_t revCoeff[FIR_ORDER+1];

// Start of main()     
int main( void )
{
    // Locals
    uint32_t i, pass = 0, fail = 0;
    
       
#ifdef _FLASH
    FIXPT_DSP_initFlash();
#endif //_FLASH
    FIXPT_DSP_initSystemClocks();
    FIXPT_DSP_initEpie();

    // Reorder the coefficients
    for(i = 0; i < FIR_ORDER_REV + 1; i++){
        revCoeff[FIR_ORDER_REV-i] = coeff[i];
    }

    // Initialize FIR32 object
	fir.order       = FIR_ORDER;
	fir.dbuffer_ptr = &dbuffer[0];
	fir.coeff_ptr   = (int32_t *)&revCoeff[0];
	fir.init(&fir);

    // FIR calculation
    for(i = 0; i < SIGNAL_LENGTH; i++){
      fir.input = sigIn[i]; // Q31 format
      fir.calc(&fir);
      sigOut[i]=fir.output; // Q30 format
    }

    // Error checking
    for(i = 0; i < SIGNAL_LENGTH; i++){
        err[i] = abs(sigOut[i] - goldOut[i]);
        if(err[i] > TOLERANCE){
          fail++;
        }else{
          pass++;
        }
    }
    
    //asm("   ESTOP0");
    for(;;);

    // code should never reach this pointer
    return 1;

} /* End: main() */


//###########################################################################
// End of File
//###########################################################################
