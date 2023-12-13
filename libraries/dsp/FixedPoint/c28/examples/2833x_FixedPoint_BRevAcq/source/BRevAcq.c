//#############################################################################
//! \file $FOLDER_EXAMPLES$/$DEVICE$_Test_FixedPoint_FIR32_Alt/test_cfft32.c
//!
//! \brief  Complex FFT (32-bit)
//!
//! \date   Sep 15, 2014
//! 
//! This example shows how to use the real time bit reversal routine for the RFFT.
//! This routine will acquire FFT_SIZE real data samples in real time and store it as 
//! an FFT_SIZE/2 point complex data sequence in bit-revesred order to perform an FFT_SIZE point
//! real FFT computation.
//! The structure used by this routine is defined as follows:
//! 
//! typedef struct {
//!  int acqflag;
//!  int count;
//!  long input; 
//!  long *tempptr;
//!  long *buffptr;
//!  int size;
//!  void (*update)(void *); 
//! }RFFT32_brev_RT_ACQ; 
//! 
//! \b Watch \b Variables
//! - ipcbsrc      Data input buffer. After the FFT calculation it becomes the 
//!                Magnitude output buffer (Both are in Q31 format)
//! - ipcb         Data output buffer (Q31 format)
//! - acq         CFFT32 object
//! 
//! In CCS, you can invoke the "SetupDebugEnv.js" script from the 
//! Scripting console to have these variables set up in the Watch window
//! and create graphs to show the input/output vectors
//
//  Group:            C2000
//  Target Family:    C28x
//
//#############################################################################
// $Copyright: Copyright (C) 2014-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "examples_setup.h"
#include "fft.h"
   
//*****************************************************************************
// defines
//*****************************************************************************
#define FFT_SIZE    1024

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

// Create an instance of RFFT32_brev_RT_ACQ module
// Use the RFFT32_brev_RT_ACQ_DEFAULTS in the FFT header file if
// unsure as to what values to program the object with.
RFFT32_brev_RT_ACQ acq = RFFT32_brev_RT_ACQ_DEFAULTS;

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
    Rad = 0.0f;
    for(i=0; i < (FFT_SIZE*2); i=i+2){
      ipcbsrc[i]  =(long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);          //Q31
      ipcbsrc[i+1] = (long)(2147483648*(cos(Rad*8.345) + sin(Rad*5.789))/2);   //Q31
      Rad = Rad + RadStep;
    }

    //Clean up input/output buffer
    for(i=0; i < (FFT_SIZE*2); i=i+2){
      ipcb[i]  =0;          
      ipcb[i+1] = 0;    
    }

    //Header structure initialization
    acq.buffptr = ipcb;            //Output buffer
    acq.tempptr = ipcb;            //Temporary buffer, normally pointing to the same as buffptr
    acq.size    = FFT_SIZE;        //Buffer size
    acq.count   = FFT_SIZE;        //Every time one element bit-reversed, count minus 1
    acq.acqflag = 1;               //Acquisition flag, initialized as 1
    
    for(i=0; i < FFT_SIZE; i++){
      acq.input = ipcbsrc[i];      // Input data
      acq.update(&acq);            // Point by point bit-reversing
    }        

    //asm("   ESTOP0");
    for(;;);
    
    // code should never reach this pointer
    return 1;
} // End: main()

//###########################################################################
// End of File
//###########################################################################
