//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_FixedPoint_FIR32/fir32d.c
//!
//! \brief  32-bit FIR Filter Example
//! \author Vishal Coelho 
//!
//! \date   Aug 12, 2014
//! 
//! This examples shows how to implement a 32-bit FIR filter using the optimized
//! FIR library routines. This version of the FIR filter has a limitation of 128 
//! taps (filter order max 127). If a higher order filter is required, refer to the
//! FIR32_Alt example.
//! The structure of 32 bit filter is shown as follows:
//! 
//! typedef struct { 
//!   long *coeff_ptr;        
//!   long * dbuffer_ptr;        
//!   int    cbindex;            
//!   int order;              
//!   long input;               
//!   long output;             
//!   void (*init)(void *);   
//!   void (*calc)(void *);    
//! }FIR32; 
//! 
//! Users can also use default templates defined within fir.h to initialize 
//! the FIR32 header structure.
//!                 
//! FIR32  fir= FIR32_DEFAULTS;
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
#define SIGNAL_LENGTH   128
                                        
//*****************************************************************************
// globals
//*****************************************************************************                                        
// Create an Instance of FIR32 module and place the object in "firfilt" section 
#ifndef __cplusplus
#pragma DATA_SECTION(fir, "firfilt");
#else
#pragma DATA_SECTION("firfilt");
#endif
FIR32 fir= FIR32_DEFAULTS;
                                            
// Define the Delay buffer for the "FIR_ORDER"th order filter
// and place it in "firldb" section. 
// Its size should be FIR_ORDER+1
// The delay line buffer must be aligned to a 256 word boundary
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
int32_t sigIn[SIGNAL_LENGTH];

#ifndef __cplusplus
#pragma DATA_SECTION(sigOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int32_t sigOut[SIGNAL_LENGTH];                                
         
// Define Constant Coefficient Array  and place it in the "coefffilt"
// section. The size of the array is FIR_ORDER+1
#ifndef __cplusplus
#pragma DATA_SECTION(coeff, "coefffilt");
#else
#pragma DATA_SECTION("coefffilt");
#endif
const int32_t coeff[FIR_ORDER+1] = FIR32_LPF32_TEST;

int main(void)
{    
    // Locals
    int32_t xn = 0, yn = 0;
    float RadStep = 0.1963495408494f;
    float Rad = 0.0f;
    uint32_t i = 0;
       
#ifdef _FLASH
    FIXPT_DSP_initFlash();
#endif //_FLASH
    FIXPT_DSP_initSystemClocks();
    FIXPT_DSP_initEpie();
    
    // Initialize FIR32 object
    fir.order       = FIR_ORDER; 
    fir.dbuffer_ptr = dbuffer;
    fir.coeff_ptr   =(int32_t *)coeff; 
    fir.init(&fir);       
        
    // Clean up input/output buffer
    for(i=0; i < SIGNAL_LENGTH; i++){
      sigIn[i]  =0;          
      sigOut[i] =0;
    }

    for(i=0; i < SIGNAL_LENGTH; i++){
      xn=(long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);     //Q31
      // Impulse function
      //if(i == 0){
      //  xn = (1 << 31);
      //}else{
      //  xn = 0;
      //}
      sigIn[i]  = xn;             //Input data buffer 
      fir.input = xn;             //Input data
      fir.calc(&fir);             //FIR convolution operation
      yn        = fir.output;     //Output data
      sigOut[i] = yn;             //Output data buffer
      Rad       = Rad + RadStep;  //Update simulated signal parameter
    }              

    //asm("   ESTOP0");
    for(;;);

    // code should never reach this pointer
    return 1;

} /* End: main() */


//###########################################################################
// End of File
//###########################################################################
