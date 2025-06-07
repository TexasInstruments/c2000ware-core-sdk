//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_FixedPoint_FIR16_Alt/fir16d_alt.c
//!
//! \brief  Alternate 16-bit FIR Filter Example
//!
//! \date   Aug 12, 2014
//! 
//! This example shows an alternate 16-bit FIR implementation. The alternate
//! version can have up to 2^16 or 65536 filter taps.
//! The header structure of 16 bit filter is shown as follows:
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
//!     }FIR16; 
//! 
//! Users can also use default templates defined within fir.h to initialize 
//! the FIR16 header structure.
//!                 
//! FIR16  fir= FIR16_ALT_DEFAULTS;
//! 
//! The MATLAB Filter Design and Analysis Tool (FDATool) is a useful tool 
//! for designing filters and generating fixed point coefficients. Refer
//! to the appendix of the Fixed Point DSP Libray User's Guide for more
//! information.
//! 
//! \b Watch \b Variables
//! - fir   FIR16 object
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
#define SIGNAL_LENGTH   128
#define TOLERANCE       (1L << 5) // 0.009765 in Q15

#if(FIR_ORDER & 0x01)   // odd
#define FIR_ORDER_REV   (FIR_ORDER + 1) // even
#else
#define FIR_ORDER_REV   (FIR_ORDER + 2) // even
#endif

//*****************************************************************************
// globals
//*****************************************************************************                                        
// Create an Instance of FIR16 module and place the object in "firfilt" section 
#ifndef __cplusplus
#pragma DATA_SECTION(fir, "firfilt");
#else
#pragma DATA_SECTION("firfilt");
#endif
FIR16 fir= FIR16_ALT_DEFAULTS;
                                            
// Define the Delay buffer for the "FIR_ORDER"th order filter
// and place it in "firldb" section. Since we define it as int32_t,
// The size of the buffer is:
// FIR_ORDER even -> (FIR_ORDER+1)/2+1 e.g. FIR_ORDER = 32, size = 17 dwords
//           odd  -> (FIR_ORDER+1)/2   e.g. FIR_ORDER = 31, size = 16 dwords
// For the alternate FIR implementation, the delay line buffer need
// not be aligned to a specific boundary
#ifndef __cplusplus
#pragma DATA_SECTION(dbuffer,"firldb");
#else
#pragma DATA_SECTION("firfilt");
#endif
int32_t dbuffer[(FIR_ORDER+1)/2];

// Input/output buffer 
#ifndef __cplusplus
#pragma DATA_SECTION(sigIn, "sigIn");
#else
#pragma DATA_SECTION("sigIn");
#endif
int16_t sigIn[SIGNAL_LENGTH] = {
    #include "data_input.txt"
};

#ifndef __cplusplus
#pragma DATA_SECTION(sigOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int16_t sigOut[SIGNAL_LENGTH];                               
         
#ifndef __cplusplus
#pragma DATA_SECTION(goldOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int16_t goldOut[SIGNAL_LENGTH] = {
    #include "data_output.txt"
}; 

// Error between computed output and MATLAB output
int16_t err[SIGNAL_LENGTH];

// Define Constant Coefficient Array  and place it in the "coefffilt"
// section. You can either reorder the coefficients at run time (done 
// in this example) or just store them reordered.
// Index       LSW       MSW
//         +---------+---------+
//  0      | h(L-1)  | h(L/2-1)|
//  2      | h(L-2)  | h(L/2-2)|
//  4      | h(L-3)  | h(L/2-3)|
//  6      | h(L-4)  | h(L/2-4)|
//  ...    | ...     | ...     |
//  L/2-3  | h(L/2+2)| h(2)    |
//  L/2-2  | h(L/2+1)| h(1)    |
//  L/2-1  | h(L/2)  | h(0)    |
//         +---------+---------+
// The size of the array is:
// FIR_ORDER even -> (FIR_ORDER+1)+1 e.g. FIR_ORDER = 32, size = 34 words
//           odd  -> (FIR_ORDER+1)   e.g. FIR_ORDER = 31, size = 32 words
// The reason being that we use the DMAC operation which will multiply
// the coefficients in 32-bit chunks, we don't want an odd size coefficient
// buffer and risk corrupting the delay line
#ifndef __cplusplus
#pragma DATA_SECTION(coeff, "coefffilt");
#else
#pragma DATA_SECTION("coefffilt");
#endif
const int16_t coeff[FIR_ORDER+1] = {
    #include "coeffs.txt"
};

#ifndef __cplusplus
#pragma DATA_SECTION(revCoeff, "coefffilt");
#else
#pragma DATA_SECTION("coefffilt");
#endif
int16_t revCoeff[FIR_ORDER+2];

// Start of main()     
int main(void)
{
    //Locals
    uint32_t i, pass = 0, fail = 0;
    
#ifdef _FLASH
    FIXPT_DSP_initFlash();
#endif //_FLASH
    FIXPT_DSP_initSystemClocks();
    FIXPT_DSP_initEpie();

    // if the order of the coefficients is even, you will have 
    // an odd number of taps; zero out the location right after the
    // last tap
    if((FIR_ORDER & 0x01) == 0){
      revCoeff[FIR_ORDER_REV-1] = 0;
    }
    // Reorder the coefficients
    // FIR_ORDER even -> (FIR_ORDER+1)+1 e.g. FIR_ORDER = 32, size = 34 words
    //           odd  -> (FIR_ORDER+1)   e.g. FIR_ORDER = 31, size = 32 words
    for(i = 0; i < FIR_ORDER + 1; i = i + 2){
        revCoeff[FIR_ORDER_REV-i-1] = coeff[i/2+FIR_ORDER_REV/2];
        revCoeff[FIR_ORDER_REV-i-2] = coeff[i/2];
    }

    // Initialize FIR16 object
	fir.order       = FIR_ORDER;
	fir.dbuffer_ptr = &dbuffer[0];
	fir.coeff_ptr   = (int32_t *)&revCoeff[0];
	fir.init(&fir);

    // FIR calculation
    for(i = 0; i < SIGNAL_LENGTH; i++){
      fir.input = sigIn[i]; // Q15 format
      fir.calc(&fir);
      sigOut[i]=fir.output;
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
