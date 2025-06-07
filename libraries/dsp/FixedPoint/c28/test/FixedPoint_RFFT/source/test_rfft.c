//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_Test_RFFT/test_rfft.c
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
//! - rfft         RFFT32 object
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
//$Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
//*****************************************************************************
// includes
//*****************************************************************************
#include "test_rfft.h"
#include "device.h"
#include "fft.h"
#include "interrupt.h"
//*****************************************************************************
// defines
//*****************************************************************************
#define XXSTRINGIZE(s)	XSTRINGIZE(s)  // calls xstringize(s), if s is a macro it
                                       // will expand s first
#define XSTRINGIZE(s)	STRINGIZE(s)  // calls stringize(s), if s is a macro it
                                      // will expand s first
#define STRINGIZE(s)	#s			  // TREAT s as a literal, if s is a macro
                                      // it wont be expanded
#define XCONCAT(x,y,z) CONCAT(x,y,z)  // expand x and y then call concat on the
                                      // expanded macros x and y
#define CONCAT(x,y,z)	x ## y ## z   // concats x and y but doesnt expand
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
#if (RUN_TEST == TEST_2)
int32_t ipcbsrc[4*FFT_SIZE]= {
#else
int32_t ipcbsrc[FFT_SIZE]= {
#endif
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_input.txt))
};

#ifndef __cplusplus
#pragma DATA_SECTION(ipcb, "FFTipcb");
#else
#pragma DATA_SECTION("FFTipcb");
#endif
#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) ||\
	 (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || (RUN_TEST == TEST_9) ||\
	 (RUN_TEST == TEST_10)|| (RUN_TEST == TEST_11)|| (RUN_TEST == TEST_12) || (RUN_TEST == TEST_13) ||\
	 (RUN_TEST == TEST_14)|| (RUN_TEST == TEST_15)|| (RUN_TEST == TEST_16) || (RUN_TEST == TEST_17) ||\
	 (RUN_TEST == TEST_18))
int32_t ipcb[FFT_SIZE+2];
#elif RUN_TEST == TEST_2
int32_t ipcb[4*FFT_SIZE];
#endif

#if RUN_TEST == TEST_1
const int32_t goldOut[FFT_SIZE] = {
	#include "test1_data_bitreversed.txt"
};
#elif RUN_TEST == TEST_2
const int32_t goldOut[4*FFT_SIZE] = {
	#include "test2_data_bitreversed.txt"
};
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) ||\
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || (RUN_TEST == TEST_9) ||\
	   (RUN_TEST == TEST_10))
const int32_t goldOut[FFT_SIZE] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_output.txt))
};
#elif ((RUN_TEST == TEST_11)|| (RUN_TEST == TEST_12) || (RUN_TEST == TEST_13) ||\
	  (RUN_TEST == TEST_14)|| (RUN_TEST == TEST_15)|| (RUN_TEST == TEST_16) || (RUN_TEST == TEST_17) ||\
	  (RUN_TEST == TEST_18))
// For RFFT, the magnitude output is always N/2+1- the spectrum is symmetric about the nyquist bin, hence we
// need only calculate the first N/2+1 points that correspond to the frequency bins 0Hz to fs/2Hz in bins
// of mfs/N (m = 0:N/2) Hz
const int32_t goldOut[FFT_SIZE] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_output.txt))
};
#endif

#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) ||\
     (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || (RUN_TEST == TEST_9) ||\
	 (RUN_TEST == TEST_10)|| (RUN_TEST == TEST_11)|| (RUN_TEST == TEST_12) || (RUN_TEST == TEST_13) ||\
	 (RUN_TEST == TEST_14)|| (RUN_TEST == TEST_15)|| (RUN_TEST == TEST_16) || (RUN_TEST == TEST_17) ||\
	 (RUN_TEST == TEST_18))
int32_t err[FFT_SIZE];
#elif RUN_TEST == TEST_2
int32_t err[4*FFT_SIZE];
#endif

// Declare and initialize the structure object.
// Use the RFFT32_<n>P_DEFUALTS in the FFT header file if
// unsure as to what values to program the object with.
#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_2))
RFFT32  rfft=RFFT32_1024P_DEFAULTS;
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_11))
RFFT32  rfft=RFFT32_32P_DEFAULTS;
#elif ((RUN_TEST == TEST_4) || (RUN_TEST == TEST_12))
RFFT32  rfft=RFFT32_64P_DEFAULTS;
#elif ((RUN_TEST == TEST_5) || (RUN_TEST == TEST_13))
RFFT32  rfft=RFFT32_128P_DEFAULTS;
#elif ((RUN_TEST == TEST_6) || (RUN_TEST == TEST_14))
RFFT32  rfft=RFFT32_256P_DEFAULTS;
#elif ((RUN_TEST == TEST_7) || (RUN_TEST == TEST_15))
RFFT32  rfft=RFFT32_512P_DEFAULTS;
#elif ((RUN_TEST == TEST_8) || (RUN_TEST == TEST_16))
RFFT32  rfft=RFFT32_1024P_DEFAULTS;
#elif ((RUN_TEST == TEST_9) || (RUN_TEST == TEST_17))
RFFT32  rfft=RFFT32_2048P_DEFAULTS;
#elif ((RUN_TEST == TEST_10) || (RUN_TEST == TEST_18))
RFFT32  rfft=RFFT32_4096P_DEFAULTS;
#endif

RFFT32_Handle handleRFFT32;

uint16_t pass = 0, fail = 0;
//*****************************************************************************
// function definitions
//*****************************************************************************
uint16_t FIXPT_DSP_runTest()
{
	// Locals

	//Initialize CFFT object
	rfft.ipcbptr = ipcb;
	// FFT computation buffer
	rfft.magptr  = ipcbsrc;                       // Magnitude output buffer

	// Initialize the handle
	handleRFFT32 = (RFFT32_Handle)&rfft;

#if RUN_TEST == TEST_1
	// Basic test of bit reversal. input/output vectors generated in MATLAB
	// zero out ipcb
	memset(ipcb, 0, sizeof(ipcb));

	// Step 3: Bit reverse order the input
	RFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);         // bit-reversing
#elif RUN_TEST == TEST_2
	// Check if bit reversal writes to memory outside its bounds, we check FFT_SIZE*4 word locations
	// above and FFT_SIZE*4 word locations below for memory corruption

	// zero out ipcb
	memset(ipcb, 0xDEAD, sizeof(ipcb));

	// Step 3: Bit reverse order the input
	RFFT32_brev(&ipcbsrc[FFT_SIZE], &ipcb[FFT_SIZE], FFT_SIZE);         //bit-reversing

#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) ||\
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || (RUN_TEST == TEST_9) ||\
	   (RUN_TEST == TEST_10))

	// zero out ipcb
	memset(ipcb, 0, sizeof(ipcb));
	// Bit reverse order the input
	RFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);
	// Initialize and run the FFT routines
	rfft.init(handleRFFT32);           // Twiddle factor pointer initialization
	rfft.calc(handleRFFT32);           // Compute the FFT
    rfft.split(&rfft);                 // Post processing to get the correct spectrum
#elif ((RUN_TEST == TEST_11)|| (RUN_TEST == TEST_12) || (RUN_TEST == TEST_13) ||\
	   (RUN_TEST == TEST_14)|| (RUN_TEST == TEST_15) || (RUN_TEST == TEST_16) || (RUN_TEST == TEST_17) ||\
	   (RUN_TEST == TEST_18))
	// 32-pt FFT
	// zero out ipcb
	memset(ipcb, 0, sizeof(ipcb));
	// Bit reverse order the input
	RFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);
	// Initialize and run the FFT routines
	rfft.init(handleRFFT32);           // Twiddle factor pointer initialization
	rfft.calc(handleRFFT32);           // Compute the FFT
    rfft.split(&rfft);                 // Post processing to get the correct spectrum
	// Calculate the magnitude
	rfft.mag(handleRFFT32);            // Q30 format (abs(ipcbsrc)/2^16).^2
#endif
	return(1);
}

uint16_t FIXPT_DSP_genReport()
{
	//Locals
	int16_t i;
	uint16_t goldPass = 0; // Each test must define an expected pass value

#if RUN_TEST == TEST_1
	goldPass =  FFT_SIZE;
	// Check that bit reversal was done correctly
	for(i = 0; i < goldPass; i++ ){
		err[i] = labs(goldOut[i] - ipcb[i]);
		if(err[i] == 0){
			pass++;
		}else{
			fail++;
		}
	}

#elif RUN_TEST == TEST_2
	goldPass =  4*FFT_SIZE;
	// Check that bit reversal was done correctly
	for(i = 0; i < goldPass; i++ ){
		err[i] = labs(goldOut[i] - ipcb[i]);
		if(err[i] == 0){
			pass++;
		}else{
			fail++;
		}
	}
#elif  ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) ||\
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || (RUN_TEST == TEST_9) ||\
	   (RUN_TEST == TEST_10))
	goldPass =  FFT_SIZE;
	// Check that bit reversal was done correctly
	for(i = 0; i < goldPass; i++ ){
		err[i] = labs(goldOut[i] - ipcb[i]);
		if(err[i] < TOLERANCE){
			pass++;
		}else{
			fail++;
		}
	}
#elif  ((RUN_TEST == TEST_11) || (RUN_TEST == TEST_12) || (RUN_TEST == TEST_13) ||\
	   (RUN_TEST == TEST_14) || (RUN_TEST == TEST_15) || (RUN_TEST == TEST_16) || (RUN_TEST == TEST_17) ||\
	   (RUN_TEST == TEST_18))
	goldPass =  FFT_SIZE/2 + 1;
	// Check that bit reversal was done correctly
	for(i = 0; i < goldPass; i++ ){
		err[i] = labs(goldOut[i] - ipcbsrc[i]);
		if(err[i] < TOLERANCE){
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
    float RadStep = 0.1963495408494f;
    float Rad = 0.0f;
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
