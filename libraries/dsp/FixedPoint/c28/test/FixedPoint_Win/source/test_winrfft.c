//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_Test_RFFT/test_rfft.c
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
//$Copyright: Copyright (C) 2014-2023 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
//*****************************************************************************
// includes
//*****************************************************************************
#include "test_winrfft.h"
#include "fft.h"
#include "fft_hamming_Q31.h"
#include "device.h"
//*****************************************************************************
// defines
//*****************************************************************************
#define XSTRINGIZE(s)	STRINGIZE(s)  // calls stringize(s), if s is a macro it
                                      // will expand s first
#define STRINGIZE(s)	#s			  // TREAT s as a literal, if s is a macro
                                      // it wont be expanded
#define XCONCAT(x,y) CONCAT(x,y)      // expand x and y then call concat on the
                                      // expanded macros x and y
#define CONCAT(x,y)	x ## y            // concats x and y but doesnt expand
                                      // x and y if they are macros

#define YYCONCAT(x,y,z) YCONCAT(x,y,z)  // expand x and y then call concat on the
                                        // expanded macros x and y
#define YCONCAT(x,y,z)	x ## y ## z     // concats x and y but doesnt expand
                                        // x and y if they are macros
//*****************************************************************************
// globals
//***************************************************************************** 
// Create the FFT buffers, ipcb and ipcbsrc, in sections with the same name
#ifndef __cplusplus
#pragma DATA_SECTION(ipcbsrc, "FFTipcbsrc");
#else
#pragma DATA_SECTION("FFTipcbsrc");
#endif
#if (RUN_TEST == TEST_1)
int32_t ipcbsrc[FFT_SIZE];
#elif ((RUN_TEST == TEST_2) || (RUN_TEST == TEST_3))
int32_t ipcbsrc[2*FFT_SIZE];
#endif


#ifndef __cplusplus
#pragma DATA_SECTION(ipcb, "FFTipcb");
#else
#pragma DATA_SECTION("FFTipcb");
#endif
#if (RUN_TEST == TEST_1)
int32_t ipcb[FFT_SIZE];
#elif ((RUN_TEST == TEST_2) || (RUN_TEST == TEST_3))
int32_t ipcb[2*FFT_SIZE];
#endif

// Declare and initialize the structure object.
// Use the RFFT32_<n>P_DEFUALTS in the FFT header file if
// unsure as to what values to program the object with.
#if (RUN_TEST == TEST_1)
RFFT32  rfft = YYCONCAT(RFFT32_,FFT_SIZE,P_DEFAULTS);
RFFT32_Handle handleRFFT32;
#elif ((RUN_TEST == TEST_2) || (RUN_TEST == TEST_3))
CFFT32  cfft = YYCONCAT(CFFT32_,FFT_SIZE,P_DEFAULTS);
CFFT32_Handle handleCFFT32;
#endif

// Define window Co-efficient Array 
// Note: Windowing is not used in this example
const long win[FFT_SIZE/2] = XCONCAT(HAMMING,FFT_SIZE);

#if (RUN_TEST == TEST_1)
int32_t err[FFT_SIZE];
#elif ((RUN_TEST == TEST_2) || (RUN_TEST == TEST_3))
int32_t err[2*FFT_SIZE];
#endif

uint16_t pass = 0, fail = 0;
//*****************************************************************************
// function definitions
//*****************************************************************************
uint16_t FIXPT_DSP_runTest()
{
	// Locals
	int16_t i;
#if RUN_TEST == TEST_1
	// zero out ipcb, set ipcbsrc to all ones
	memset(ipcb, 0, sizeof(ipcb));
	for(i = 0; i < FFT_SIZE; i++){
		ipcbsrc[i] = 0x7FFFFFFF;
	}

	//Initialize CFFT object
	rfft.ipcbptr = ipcb;
	// FFT computation buffer
	rfft.magptr  = ipcbsrc;
	// Assign window
	rfft.winptr = (int32_t *)win;

	// Initialize the handle
	handleRFFT32 = (RFFT32_Handle)&rfft;

	// Bit reverse order the input
	RFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);         // bit-reversing

	// Apply the window to bit-reversed input
	rfft.win(handleRFFT32);

	//Bit reverse the windowed input to get it back to regular order
	RFFT32_brev(ipcb, ipcb, FFT_SIZE);
#elif RUN_TEST == TEST_2
	// zero out ipcb, set ipcbsrc to all ones
	memset(ipcb, 0, sizeof(ipcb));

	for(i = 0; i < 2*FFT_SIZE; i = i + 2){
		ipcbsrc[i]   = 0x7FFFFFFF;
		ipcbsrc[i+1] = 0x1;
	}

	//Initialize CFFT object
	cfft.ipcbptr = ipcb;
	// FFT computation buffer
	cfft.magptr  = ipcbsrc;
	// Assign window
	cfft.winptr = (int32_t *)win;

	// Initialize the handle
	handleCFFT32 = (CFFT32_Handle)&cfft;

	// Bit reverse order the input
	CFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);
	CFFT32_brev(&ipcbsrc[1], &ipcb[1], FFT_SIZE);

	// Apply the window to bit-reversed input
	cfft.win(handleCFFT32);

	//Bit reverse the windowed input to get it back to regular order
	CFFT32_brev(ipcb, ipcb, FFT_SIZE);
	CFFT32_brev(&ipcb[1], &ipcb[1], FFT_SIZE);
#elif RUN_TEST == TEST_3
	// zero out ipcb, set ipcbsrc to all ones
	memset(ipcb, 0, sizeof(ipcb));

	for(i = 0; i < 2*FFT_SIZE; i++){
		ipcbsrc[i]   = 0x7FFFFFFF;
	}

	//Initialize CFFT object
	cfft.ipcbptr = ipcb;
	// FFT computation buffer
	cfft.magptr  = ipcbsrc;
	// Assign window
	cfft.winptr = (int32_t *)win;
	// change the windowing function to dual
	cfft.win = CFFT32_win_dual;

	// Initialize the handle
	handleCFFT32 = (CFFT32_Handle)&cfft;

	// Bit reverse order the input
	CFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);
	CFFT32_brev(&ipcbsrc[1], &ipcb[1], FFT_SIZE);

	// Apply the window to bit-reversed input
	cfft.win(handleCFFT32);

	//Bit reverse the windowed input to get it back to regular order
	CFFT32_brev(ipcb, ipcb, FFT_SIZE);
	CFFT32_brev(&ipcb[1], &ipcb[1], FFT_SIZE);
#endif
	return(1);

}

uint16_t FIXPT_DSP_genReport()
{
	//Locals
	int16_t i,j = 0;
	uint16_t goldPass = 0; // Each test must define an expected pass value

#if RUN_TEST == TEST_1
	goldPass = FFT_SIZE;
	for(i = 0; i < FFT_SIZE/2; i++ ){
		err[i]   = labs(win[i] - ipcb[i]);
		if(err[i] < TOLERANCE){
			pass++;
		}else{
			fail++;
		}
	}
	for(i = FFT_SIZE/2; i < FFT_SIZE; i++ ){
		err[i]   = labs(win[FFT_SIZE - i - 1] - ipcb[i]);
		if(err[i] < TOLERANCE){
			pass++;
		}else{
			fail++;
		}
	}

#elif RUN_TEST == TEST_2
	goldPass = FFT_SIZE;
	for(i = 0, j = 0; i < FFT_SIZE; i = i + 2, j++ ){
		err[i]   = labs(win[j] - ipcb[i]);
		err[i+1] = labs(0x1 - ipcb[i+1]);
		if((err[i] < TOLERANCE) && (err[i+1] == 0)){
			pass++;
		}else{
			fail++;
		}
	}
	for(i = 0, j = FFT_SIZE/2; i < FFT_SIZE; i = i + 2, j++ ){
		err[i+FFT_SIZE]   = labs(win[FFT_SIZE - j - 1] - ipcb[i + FFT_SIZE]);
		err[i+FFT_SIZE+1] = labs(0x1 - ipcb[i + FFT_SIZE + 1]);
		if((err[i] < TOLERANCE) && (err[i+1] == 0)){
			pass++;
		}else{
			fail++;
		}
	}
#elif RUN_TEST == TEST_3
	goldPass = 2*FFT_SIZE;
	for(i = 0, j = 0; i < FFT_SIZE; i = i + 2, j++ ){
		err[i]   = labs(win[j] - ipcb[i]);
		err[i+1] = labs(win[j] - ipcb[i+1]);
		if((err[i] < TOLERANCE) && (err[i+1] < TOLERANCE)) {
			pass++;
		}else{
			fail++;
		}
	}
	for(i = 0, j = FFT_SIZE/2; i < FFT_SIZE; i = i + 2, j++){
		err[i+FFT_SIZE]   = labs(win[FFT_SIZE - j - 1] - ipcb[i + FFT_SIZE]);
		err[i+FFT_SIZE+1] = labs(win[FFT_SIZE - j - 1] - ipcb[i + FFT_SIZE + 1]);
		if((err[i+FFT_SIZE] < TOLERANCE) && (err[i+FFT_SIZE+1] < TOLERANCE)) {
			pass++;
		}else{
			fail++;
		}
	}
#endif

	if((pass == goldPass) && (fail == 0)){
		return(1);
	}
	return(0);
}

int main()
{
//    float RadStep = 0.1963495408494f;
//    float Rad = 0.0f;
    uint32_t i = 0;

    Device_init();
        DINT;                       //Globally disable maskable CPU interrupts
        Interrupt_initModule();             //Clear and disable all PIE interrupts
        Interrupt_initVectorTable();            //Populate the PIE interrupt vector table with shell ISRs

    //Clean up input/output buffer
    for(i=0; i < (FFT_SIZE+2); i=i+2){
      ipcb[i]   = 0;
      ipcb[i+1] = 0;
    }

    FIXPT_DSP_runTest();
    FIXPT_DSP_genReport();

    for(;;);
    return 1;
}
//###########################################################################
// End of File
//###########################################################################
