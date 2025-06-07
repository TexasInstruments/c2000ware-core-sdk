//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_Test_FixedPoint_RFFT/rfft.c
//!
//! \brief  Real FFT (32-bit)
//!
//! \date   Sep 15, 2014
//! 
//! This example shows how to use the RFFT windowing routine of the library. It
//! also shows the bit reversal, FFT initialization, calculation and the 
//! magnitude calculation. The RFFT module structure is as follows:
//! 
//! typedef struct {   
//!   long *ipcbptr;
//!   long *tfptr;               
//!   int size;
//!   int nrstage;             
//!   long *magptr;
//!   long *winptr; 
//!   long peakmag;
//!   int peakfrq;
//!   int ratio;
//!   void (*init)(void *);
//!   void (*calc)(void *);
//!   void (*mag)(void *);
//!   void (*win)(void *);
//! }RFFT32;
//! 
//! \b Watch \b Variables
//! - ipcbsrc      Data input buffer. After the FFT calculation it becomes the 
//!                Magnitude output buffer (Both are in Q31 format)
//! - ipcb         Data output buffer (Q31 format)
//! - rfft         CFFT32 object
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
#include "device.h"
#include "fft.h"
#include "fft_hamming_Q31.h"
#include "math.h"
//*****************************************************************************
// defines
//*****************************************************************************
#define FFT_SIZE    256

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

// Declare and initialize the structure object.
// Use the RFFT32_<n>P_DEFUALTS in the FFT header file if
// unsure as to what values to program the object with.
RFFT32  rfft = RFFT32_512P_DEFAULTS;

// Define window Co-efficient Array 
// Note: Windowing is not used in this example
const long win[FFT_SIZE/2]=HAMMING512;

// Start of main()
int main(void)
{
    // Locals
    float RadStep = 0.1963495408494f;
    float Rad = 0.0f;
    uint32_t i = 0;
         
    Device_init();
    DINT;                       //Globally disable maskable CPU interrupts
    Interrupt_initModule();             //Clear and disable all PIE interrupts
    Interrupt_initVectorTable();            //Populate the PIE interrupt vector table with shell ISRs

    //Clean up input/output buffer
    for(i=0; i < (FFT_SIZE*2); i=i+2){
      ipcb[i]   = 0;          
      ipcb[i+1] = 0;    
    }
    
    //Simulated input signal
    for(i=0; i < FFT_SIZE; i++){
      ipcbsrc[i]  = (long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);  //Q31
      Rad         = Rad + RadStep;
    }


    RFFT32_brev(ipcbsrc, ipcb, FFT_SIZE); // real FFT bit reversing
    
    rfft.ipcbptr = ipcb;                  // FFT computation buffer  
    rfft.magptr  = ipcbsrc;               // Magnitude output buffer 
    rfft.winptr  = (long *)win;           // Window coefficient array
    rfft.init(&rfft);                     // Twiddle factor pointer initialization

    rfft.win(&rfft);                      // Window the input data. The windowing is
                                          // done after the input is ordered in bit-reversed
                                          // format 
    rfft.calc(&rfft);                     // Compute the FFT
                                          
    rfft.mag(&rfft);                      // Q31 format (abs(ipcbsrc)/2^16).^2
    
    //asm("   ESTOP0");
    for(;;);
    
    // code should never reach this pointer
    return 1;

} // End: main()

//###########################################################################
// End of File
//###########################################################################
