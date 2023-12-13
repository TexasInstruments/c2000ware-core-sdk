//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_Test_FixedPoint_CFFT/cfft.c
//!
//! \brief  Complex FFT (32-bit)
//!
//! \date   Sep 15, 2014
//! 
//! This example shows how to use the CFFT routines of the library including bit
//! reversal, FFT initialization, calculation and magnitude calculation. The 
//! CFFT module structure is as follows:
//! 
//! typedef struct {
//!   int32 *ipcbptr;
//!   int32 *tfptr;
//!   int16 size;
//!   int16 nrstage;
//!   int32 *magptr;
//!   int32 *winptr;
//!   int32 peakmag;
//!   int16 peakfrq;
//!   int16 ratio;
//!   void (*init)(void *);
//!   void (*izero)(void *);
//!   void (*calc)(void *);
//!   void (*mag)(void *);
//!   void (*win)(void *);
//! }CFFT32;
//! 
//! \b Watch \b Variables
//! - ipcbsrc      Data input buffer. After the FFT calculation it becomes the 
//!                Magnitude output buffer (Both are in Q31 format)
//! - ipcb         Data output buffer (Q31 format)
//! - cfft         CFFT32 object
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
#include "examples_setup.h"
#include "fft.h"
#include "fft_hamming_Q31.h"
//*****************************************************************************
// defines
//*****************************************************************************
#define FFT_SIZE            1024
#define ENABLE_WINDOWING    1

//*****************************************************************************
// globals
//***************************************************************************** 
// Create the FFT buffers, ipcb and ipcbsrc, in sections with the same name
#ifndef __cplusplus
#pragma DATA_SECTION(ipcb, "FFTipcb");
#else
#pragma DATA_SECTION("FFTipcb");
#endif
int32_t ipcb[2*FFT_SIZE];

#ifndef __cplusplus
#pragma DATA_SECTION(ipcbsrc, "FFTipcbsrc");
#else
#pragma DATA_SECTION("FFTipcbsrc");
#endif
int32_t ipcbsrc[2*FFT_SIZE];
                       
// Define window Co-efficient Array 
// Note: Windowing is used if ENABLE_WINDOWING is set to 1024
const long win[FFT_SIZE/2]=HAMMING1024;

// Declare and initialize the structure object.
// Use the CFFT32_<n>P_DEFUALTS in the FFT header file if
// unsure as to what values to program the object with.
CFFT32  cfft=CFFT32_1024P_DEFAULTS;

// Start of main()
int main(void)
{
    // Locals
    float RadStep = 0.1963495408494f;
    float Rad = 0.0f;
    uint32_t i = 0;
         
#ifdef _FLASH
    FIXPT_DSP_initFlash();
#endif //_FLASH
    FIXPT_DSP_initSystemClocks();
    FIXPT_DSP_initEpie();
              
    // Generate sample waveforms:
    for(i=0; i < (FFT_SIZE*2); i=i+2){
      ipcbsrc[i]  =(long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);          //Q31
#if (ENABLE_WINDOWING)
      // If windowing is enabled for the CFFT routine, the routine assumes the
      // imaginary part of the input is zero and will only apply the window to the
      // real part (the sampled real data that you get from the ADC). 
      ipcbsrc[i+1] = 0;
#else       
      ipcbsrc[i+1] = (long)(2147483648*(cos(Rad*8.345) + sin(Rad*5.789))/2);   //Q31
#endif //ENABLE_WINDOWING
      Rad = Rad + RadStep;
    }

    //Clean up input/output buffer
    for(i=0; i < (FFT_SIZE*2); i=i+2){
      ipcb[i]  =0;          
      ipcb[i+1] = 0;    
    }

    CFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);         // Real part bit-reversing
    CFFT32_brev(&ipcbsrc[1], &ipcb[1], FFT_SIZE); // Imaginary part bit-reversing
    
    cfft.ipcbptr = ipcb;                          // FFT computation buffer
    cfft.magptr  = ipcbsrc;                       // Magnitude output buffer
    cfft.winptr  = (long *)win;                   // Window coefficient array
    cfft.init(&cfft);                             // Twiddle factor pointer initialization
                                                  
    cfft.calc(&cfft);                              // Compute the FFT
                                                  
    cfft.mag(&cfft);                               // Q30 format (abs(ipcbsrc)/2^16).^2
    
    //asm("   ESTOP0");
    for(;;);
    
    // code should never reach this pointer
    return 1;

} // End: main()

//###########################################################################
// End of File
//###########################################################################
