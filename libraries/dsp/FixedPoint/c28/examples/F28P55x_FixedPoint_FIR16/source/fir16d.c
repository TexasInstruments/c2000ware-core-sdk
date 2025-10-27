//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_FixedPoint_FIR16/fir16d.c
//!
//! \brief  16-bit FIR Filter Example
//! 
//! This examples shows how to implement a 16-bit FIR filter using the optimized
//! FIR library routines. This version of the FIR filter has a limitation of 256 
//! taps (filter order max 255). If a higher order filter is required, refer to the
//! FIR16_Alt example.
//! 
//! typedef struct { 
//!     int32_t *coeff_ptr;        
//!     int32_t * dbuffer_ptr;
//!     int    cbindex;
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
//! FIR16  fir= FIR16_DEFAULTS;
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
//###########################################################################
// $Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "device.h"
#include <filter.h>
#include "math.h"
//*****************************************************************************
// defines
//*****************************************************************************
// Filter Symbolic Constants
#define FIR_ORDER       32
#define SIGNAL_LENGTH   128

#if(FIR_ORDER & 0x01)   // odd
#define FIR_ORDER_REV   (FIR_ORDER + 1) // even
#else
#define FIR_ORDER_REV   (FIR_ORDER + 2) // even
#endif

#define EPSILON         0.0001f
//*****************************************************************************
// globals
//*****************************************************************************                                        
// Create an Instance of FIR16 module and place the object in "firfilt" section 
#ifndef __cplusplus
#pragma DATA_SECTION(fir, "firfilt");
#else
#pragma DATA_SECTION("firfilt");
#endif
FIR16 fir= FIR16_DEFAULTS;
                                            
// Define the Delay buffer for the "FIR_ORDER"th order filter
// and place it in "firldb" section. Since we define it as int32_t,
// The size of the buffer is:
// FIR_ORDER even -> (FIR_ORDER+1)/2+1 e.g. FIR_ORDER = 32, size = 17 dwords
//           odd  -> (FIR_ORDER+1)/2   e.g. FIR_ORDER = 31, size = 16 dwords
// The delay line buffer must be aligned to a 256 word boundary
#ifndef __cplusplus
#pragma DATA_SECTION(dbuffer,"firldb");
#else
#pragma DATA_SECTION("firfilt");
#endif
int32_t dbuffer[(FIR_ORDER+3)/2];

// Input/output buffer 
#ifndef __cplusplus
#pragma DATA_SECTION(sigIn, "sigIn");
#else
#pragma DATA_SECTION("sigIn");
#endif
int16_t sigIn[SIGNAL_LENGTH];

#ifndef __cplusplus
#pragma DATA_SECTION(sigOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int16_t sigOut[SIGNAL_LENGTH];                               
         
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

//
//Pointers to coefficient vectors
//
int16_t coeff[FIR_ORDER+2];

int16_t revCoeff[FIR_ORDER+2];                                   

int pass = 0, fail=0;
// Start of main()     
int main(void)
{    
    // Locals
    int32_t xn = 0, yn = 0;
    float RadStep = 0.1963495408494f;
    float Rad = 0.0f;
    uint32_t i = 0;
/*
#ifdef _FLASH
    FIXPT_DSP_initFlash();
#endif //_FLASH
    FIXPT_DSP_initSystemClocks();
    FIXPT_DSP_initEpie();
*/

    Device_init();
    DINT;                       //Globally disable maskable CPU interrupts
    Interrupt_initModule();             //Clear and disable all PIE interrupts
    Interrupt_initVectorTable();            //Populate the PIE interrupt vector table with shell ISRs

    // Load the coefficients in normal order. If
    // FIR_ORDER even -> number of taps are odd, after copying the coefficients 
    //                   zero out the last element of coeffs
    //           odd  -> number of taps are even, simply copy the  coefficients
    for(i = 0; i < FIR_ORDER + 2; i++){
        coeff[i] = FIR16_LPF32_TEST[i];
    }
    coeff[FIR_ORDER] = 0;
    coeff[FIR_ORDER + 1] = 0;

      // if the order of the coefficients is even, you will have 
    // an odd number of taps; zero out the location right after the
    // last tap
    if((FIR_ORDER & 0x01) == 0){
      revCoeff[FIR_ORDER_REV-1] = 0;
    }
    // Reorder the coefficients
    // FIR_ORDER even -> (FIR_ORDER+1)+1 e.g. FIR_ORDER = 32, size = 34 words
    //           odd  -> (FIR_ORDER+1)   e.g. FIR_ORDER = 31, size = 32 words
    for(i = 0; i < FIR_ORDER + 2; i = i + 2){
        revCoeff[FIR_ORDER_REV-i-1] = coeff[i/2+FIR_ORDER_REV/2];
        revCoeff[FIR_ORDER_REV-i-2] = coeff[i/2];
    }

    for(i=0; i < SIGNAL_LENGTH; i++){
        sigIn[i]  =0; 
        sigOut[i] =0;
    }

    // Initialize FIR16 object
	fir.order       = FIR_ORDER;
	fir.dbuffer_ptr = &dbuffer[0];
	fir.coeff_ptr   = (int32_t *)&revCoeff[0];
	fir.init(&fir);

    // FIR calculation
    for(i = 0; i < SIGNAL_LENGTH; i++){
      xn=(int)(32768*(sin(Rad) + cos(Rad*2.3567))/2);          //Q15
      // Impulse function
      //if(i == 0){
      //  xn = (1 << 15);
      //}else{
      //  xn = 0;
      //}
      sigIn[i]   = xn;
      fir.input  = sigIn[i]; // Q15 format
      fir.calc(&fir);
      yn         = fir.output;
      sigOut[i]  = yn;
      Rad        = Rad + RadStep;
    }
      
    // Check the output
    for(i = 0; i < SIGNAL_LENGTH; i++){
        if(fabsf(FIR16_LPF32_TESTOUT[i] - sigOut[i]) <= EPSILON){
            pass++;
        }
        else
        {
            fail++;
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
