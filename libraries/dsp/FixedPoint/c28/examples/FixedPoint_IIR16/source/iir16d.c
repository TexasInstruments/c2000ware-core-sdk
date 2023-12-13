//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_FixedPoint_IIR16/iir16d.c
//!
//! \brief  16-bit IIR Filter Example
//!
//! \date   Aug 12, 2014
//! 
//! This examples shows how to implement a 16-bit IIR filter using the optimized
//! IIR library routines. The IIR structure is as follows:
//! 
//! typedef struct { 
//!   void (*init)(void *);  
//!   void (*calc)(void *);  
//!   int *coeff_ptr;         
//!   int *dbuffer_ptr;       
//!   int nbiq;               
//!   int input;            
//!   int isf;                
//!   int qfmat;              
//!   int output;             
//! }IIR5BIQ16; 
//! 
//! Users can also use default templates defined within filter.h to initialize 
//! the IIR16 header structure.
//!                 
//! IIR16  iir= IIR16_DEFAULTS;
//! 
//! The MATLAB Filter Design and Analysis Tool (FDATool) is a useful tool 
//! for designing filters and generating fixed point coefficients. Refer
//! to the appendix of the Fixed Point DSP Libray User's Guide for more
//! information.
//! The eziir16.m MATLAB script ($FOLDER_EXAMPLES$/$DEVICE$_FixedPoint_IIR16/matlab/
//! eziir16.m) can be used to generate the filter coefficients in a way as to prevent
//! overflow of the output. Please refer to SPRA509 (Overflow Avoidance Techniques in 
//! Cascaded IIR Filter Implementations on the TMS320 DSP's) for a better understanding
//! of what the process is. The script will generate a Q-format and Input Scaling Factor
//! for the coefficients, QFMAT and ISF respectively, that will be used in the IIR5BIQ16
//! object initialization.
//!
//! \b Watch \b Variables
//! - iir  IIR16 object
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
// $Copyright: Copyright (C) 2014-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

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
#define SIGNAL_LENGTH   100
     
//*****************************************************************************
// globals
//*****************************************************************************
// Create an Instance of IIR5BIQD16 module and place the object in 
// "iirfilt" section
#ifndef __cplusplus
#pragma DATA_SECTION(iir, "iirfilt");
#else
#pragma DATA_SECTION("iirfilt");
#endif
IIR5BIQ16  iir = IIR5BIQ16_DEFAULTS;
                                                                  
// Modify the delay buffer size to be commensurate with the number of biquads 
// in the filter. Size of the Delay buffer = 2*nbiq i.e. two delay elements
// per biquad
// Define the Delay buffer for the cascaded 6 biquad IIR filter and place it 
// in "iirfilt" section
#ifndef __cplusplus
#pragma DATA_SECTION(dbuffer, "iirldb");
#else
#pragma DATA_SECTION("iirldb");
#endif
int dbuffer[2*IIR16_LPF_NBIQ];

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

// For each biquad there are 6 coefficients: a0, a1, a2, b0, b0, b2. 
// a0 is always 1, therefore, we need 5 coefficients for each biquad
// xn------>(x)--->(+)--------------->yn
//      |    ^      ^             |
//      |    |      |q4           |
//      |    b(0)  (z)            |
//      |           ^             |
//      |           |q3           |
//      |-->(x)--->(+)<-----(x)---|
//      |    ^      ^        ^    |
//      |    |      |q2      |    |
//      |    b(1)  (z)       a(1) |
//      |           ^             |
//      |           |q1           |
//      --->(x)--->(+)<-----(x)----
//           ^               ^
//           |               |
//           b(2)            a(2)
// Size of the coefficient array = 5 * nbiq
const int coeff[5*IIR16_LPF_NBIQ] = IIR16_LPF_COEFF;

   
// Start of main()     
int main(void)
{    
    // Locals
    int32_t xn = 0, yn = 0;
    float RadStep = 0.1963495408494f;
    float Rad = 0.0f;
    uint32_t i = 0;
       
    Device_init();
    DINT;                       //Globally disable maskable CPU interrupts
    Interrupt_initModule();             //Clear and disable all PIE interrupts
    Interrupt_initVectorTable();            //Populate the PIE interrupt vector table with shell ISRs
    
    for(i=0; i < SIGNAL_LENGTH; i++){
      sigIn[i]  =0; 
      sigOut[i] =0;
    }

    
    // IIR Filter Initialization
    iir.dbuffer_ptr  = (int16_t *)dbuffer;
    iir.coeff_ptr    = (int16_t *)coeff; 
    iir.qfmat        = IIR16_LPF_QFMAT;
    iir.nbiq         = IIR16_LPF_NBIQ; 
    iir.isf          = IIR16_LPF_ISF; 
    iir.init(&iir);
    
    for(i=0; i < SIGNAL_LENGTH; i++){
      xn = (int)(32768*(sin(Rad) + cos(Rad*2.3567))/2);          //Q15
      sigIn[i]  = xn;
      iir.input = xn;           
      iir.calc(&iir);
      yn        = iir.output;
      sigOut[i] = yn;
      Rad       = Rad + RadStep;
    }                   

    //asm("   ESTOP0");
    for(;;);

    // code should never reach this pointer
    return 1;

} /* End: main() */


//###########################################################################
// End of File
//###########################################################################
