//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_Test_FixedPoint_RFFT/rfft.c
//!
//! \brief  Real FFT (32-bit)
//!
//! \date   Sep 15, 2014
//! 
//! This example shows how to use the RFFT routines of the library including bit
//! reversal, FFT initialization, calculation and the magnitude calculation. 
//! The RFFT module structure is as follows:
//! 
//! typedef struct {   
//!   int32_t *ipcbptr;
//!   int32_t *tfptr;
//!   int16_t size;
//!   int16_t nrstage;
//!   int32_t *magptr;
//!   int32_t *winptr;
//!   int32_t peakmag;
//!   int16_t peakfrq;
//!   int16_t ratio;
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
//! - rfft         RFFT32 object
//! 
//!
//| Alignment requirement for FFT_SIZE real FFT is FFT_SIZE 32-bit words
//! In the linker command file, specify ALIGN(2*FFT_SIZE) since it specifies in 16-bit words
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
// $Copyright: Copyright (C) 2014-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
//*****************************************************************************
// includes
//*****************************************************************************
#include "device.h"
#include "fft.h"
#include "fft_rect_Q31.h"
#include "math.h"
//*****************************************************************************
// defines
//*****************************************************************************
// Size of the Real FFT
#define FFT_SIZE    256
// log2(FFT_SIZE)
#define NUM_STAGES   8

//*****************************************************************************
// globals
//***************************************************************************** 
// Create the FFT buffers, ipcb and ipcbsrc, in sections with the same name
#ifndef __cplusplus
#pragma DATA_SECTION(ipcb, "FFTipcb");
#else
#pragma DATA_SECTION("FFTipcb");
#endif
// For a Real FFT of size FFT_SIZE, it's uniquely specified by N/2 + 1 complex values (due to conjugate symmetry), i.e. N + 2 real values
// X(0), X(1), ..X(N/2-1), X(N/2)
//
int32_t ipcb[FFT_SIZE+2];

#ifndef __cplusplus
#pragma DATA_SECTION(ipcbsrc, "FFTipcbsrc");
#else
#pragma DATA_SECTION("FFTipcbsrc");
#endif
// As described above, N/2 + 1 magnitude values suffice. A larger size is provided here
int32_t ipcbsrc[FFT_SIZE];


// Declare and initialize the structure object.
// Use the RFFT32_<n>P_DEFUALTS in the FFT header file if
// unsure as to what values to program the object with.
// The number used here should match FFT_SIZE
RFFT32  rfft = RFFT32_256P_DEFAULTS;

// Define window Co-efficient Array
const int32_t win[FFT_SIZE/2]=RECT128;

// Start of main()
int main(void)
{
    // Locals
    float RadStep = 0.1963495408494f;       // radstep = 2 pi fo/fs; k/N = f/fs, so ko = N fo/fs = FFT_SIZE.radstep/ 2pi = 8 (almost exactly)
    float Rad = 0.0f;
    uint32_t i = 0;
    int64_t fft_dc_value_int64 = 0;
    int32_t fft_dc_value_int32 = 0;
         
    Device_init();
    DINT;                       //Globally disable maskable CPU interrupts
    Interrupt_initModule();             //Clear and disable all PIE interrupts
    Interrupt_initVectorTable();            //Populate the PIE interrupt vector table with shell ISRs
              
    //Clean up buffers
    for(i=0; i < (FFT_SIZE+2); i++){
      ipcb[i]   = 0;
    }
    for(i=0; i < FFT_SIZE; i++){
      ipcbsrc[i]   = 0;
    }

    //Simulated input signal of FFT_SIZE real values
    for(i=0; i < FFT_SIZE; i++){
      //ipcb[i]  = (int32_t)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);  //Q31
      ipcb[i]  = (int32_t)(2147483648*(sin(Rad)));  //Q31, with this input, there will be a peak in the output at bin number 8 (ipcbsrc) and index 16,17 (ipcb)
      fft_dc_value_int64 += ipcb[i];
      Rad         = Rad + RadStep;
    }
    fft_dc_value_int32 = fft_dc_value_int64 >> NUM_STAGES;           // this value should match the first value of ipcb after FFT compute

    RFFT32_brev(ipcb, ipcb, FFT_SIZE); // real FFT bit reversing
    
    rfft.ipcbptr = ipcb;                  // FFT computation buffer  
    rfft.magptr  = ipcbsrc;               // Magnitude output buffer 
    rfft.winptr  = (int32_t *)win;           // Window coefficient array
    rfft.init(&rfft);                     // Twiddle factor pointer initialization
                                          
    rfft.calc(&rfft);                     // Compute the FFT
    rfft.split(&rfft);                    // Post processing to get the correct spectrum                                      
    rfft.mag(&rfft);                      // Q30 format (square of complex magnitude)
        
    //asm("   ESTOP0");
    for(;;);
    
    // code should never reach this pointer
    return 1;

} // End: main()

//###########################################################################
// End of File
//###########################################################################
