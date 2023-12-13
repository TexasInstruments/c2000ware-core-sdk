//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_Test_CFFT/test_cfft.c
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
//$Copyright: Copyright (C) 2014-2023 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
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
// includes
//*****************************************************************************
#include "test_cfft.h"
#include "fft.h"
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
int32_t ipcbsrc[8*FFT_SIZE]= {
#else
const int32_t ipcbsrc[2*FFT_SIZE]= {
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
int32_t ipcb[2*FFT_SIZE];
#elif RUN_TEST == TEST_2
int32_t ipcb[8*FFT_SIZE];
#endif


#if RUN_TEST == TEST_1
const int32_t goldOut[2*FFT_SIZE] = {
	#include "test1_data_bitreversed.txt"
};
#elif RUN_TEST == TEST_2
const int32_t goldOut[8*FFT_SIZE] = {
	#include "test2_data_bitreversed.txt"
};
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) ||\
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || (RUN_TEST == TEST_9) ||\
	   (RUN_TEST == TEST_10)|| (RUN_TEST == TEST_11)|| (RUN_TEST == TEST_12) || (RUN_TEST == TEST_13) ||\
	   (RUN_TEST == TEST_14)|| (RUN_TEST == TEST_15)|| (RUN_TEST == TEST_16) || (RUN_TEST == TEST_17) ||\
	   (RUN_TEST == TEST_18))
const int32_t goldOut[2*FFT_SIZE] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_output.txt))
};
#endif

#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) ||\
     (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || (RUN_TEST == TEST_9) ||\
	 (RUN_TEST == TEST_10)|| (RUN_TEST == TEST_11)|| (RUN_TEST == TEST_12) || (RUN_TEST == TEST_13) ||\
	 (RUN_TEST == TEST_14)|| (RUN_TEST == TEST_15)|| (RUN_TEST == TEST_16) || (RUN_TEST == TEST_17) ||\
	 (RUN_TEST == TEST_18))
int32_t err[2*FFT_SIZE];
#elif RUN_TEST == TEST_2
int32_t err[8*FFT_SIZE];
#endif

// Declare and initialize the structure object.
// Use the CFFT32_<n>P_DEFUALTS in the FFT header file if
// unsure as to what values to program the object with.
#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_2))
CFFT32  cfft=CFFT32_1024P_DEFAULTS;
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_11))
CFFT32  cfft=CFFT32_32P_DEFAULTS;
#elif ((RUN_TEST == TEST_4) || (RUN_TEST == TEST_12))
CFFT32  cfft=CFFT32_64P_DEFAULTS;
#elif ((RUN_TEST == TEST_5) || (RUN_TEST == TEST_13))
CFFT32  cfft=CFFT32_128P_DEFAULTS;
#elif ((RUN_TEST == TEST_6) || (RUN_TEST == TEST_14))
CFFT32  cfft=CFFT32_256P_DEFAULTS;
#elif ((RUN_TEST == TEST_7) || (RUN_TEST == TEST_15))
CFFT32  cfft=CFFT32_512P_DEFAULTS;
#elif ((RUN_TEST == TEST_8) || (RUN_TEST == TEST_16))
CFFT32  cfft=CFFT32_1024P_DEFAULTS;
#elif ((RUN_TEST == TEST_9) || (RUN_TEST == TEST_17))
CFFT32  cfft=CFFT32_2048P_DEFAULTS;
#elif ((RUN_TEST == TEST_10) || (RUN_TEST == TEST_18))
CFFT32  cfft=CFFT32_4096P_DEFAULTS;
#endif

CFFT32_Handle handleCFFT32;

extern uint16_t pass, fail;
//*****************************************************************************
// function definitions
//*****************************************************************************
uint16_t FIXPT_DSP_runTest()
{
	// Locals

	//Initialize CFFT object
	cfft.ipcbptr = ipcb;                          // FFT computation buffer
	cfft.magptr  = (int32_t *)ipcbsrc;                       // Magnitude output buffer
//	cfft.winptr  = (long *)win;                   // Window coefficient array

	// Initialize the handle
	handleCFFT32 = (CFFT32_Handle)&cfft;

#if RUN_TEST == TEST_1
	// Basic test of bit reversal. input/output vectors generated in MATLAB

	// zero out ipcb
	memset(ipcb, 0, sizeof(ipcb));

	// Step 3: Bit reverse order the input
	CFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);         // Real part bit-reversing
	CFFT32_brev(&ipcbsrc[1], &ipcb[1], FFT_SIZE); // Imaginary part bit-reversing
#elif RUN_TEST == TEST_2
	// Check if bit reversal writes to memory outside its bounds, we check FFT_SIZE*4 word locations
	// above and 2*FFT_SIZE*4 word locations below for memory corruption

	// zero out ipcb
	memset(ipcb, 0xDEAD, sizeof(ipcb));

	// Step 3: Bit reverse order the input
	CFFT32_brev(&ipcbsrc[2*FFT_SIZE], &ipcb[2*FFT_SIZE], FFT_SIZE);         // Real part bit-reversing
	CFFT32_brev(&ipcbsrc[2*FFT_SIZE + 1], &ipcb[2*FFT_SIZE + 1], FFT_SIZE); // Imaginary part bit-reversing

#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) ||\
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || (RUN_TEST == TEST_9) ||\
	   (RUN_TEST == TEST_10))
	// 32-pt FFT
	// zero out ipcb
	memset(ipcb, 0, sizeof(ipcb));
	// Bit reverse order the input
	CFFT32_brev(ipcbsrc, ipcb, FFT_SIZE);         // Real part bit-reversing
	CFFT32_brev(&ipcbsrc[1], &ipcb[1], FFT_SIZE); // Imaginary part bit-reversing
	// Initialize and run the FFT routines
	cfft.init(handleCFFT32);                             // Twiddle factor pointer initialization
	cfft.calc(handleCFFT32);                              // Compute the FFT

#elif ((RUN_TEST == TEST_11)|| (RUN_TEST == TEST_12) || (RUN_TEST == TEST_13) ||\
	   (RUN_TEST == TEST_14)|| (RUN_TEST == TEST_15) || (RUN_TEST == TEST_16) || (RUN_TEST == TEST_17) ||\
	   (RUN_TEST == TEST_18))
	// 32-pt FFT
	// zero out ipcb
	memset(ipcb, 0, sizeof(ipcb));
	// Bit reverse order the input
	CFFT32_brev((int32_t *)ipcbsrc, ipcb, FFT_SIZE);         // Real part bit-reversing
	CFFT32_brev((int32_t *)&ipcbsrc[1], &ipcb[1], FFT_SIZE); // Imaginary part bit-reversing
	// Initialize and run the FFT routines
	cfft.init(handleCFFT32);                             // Twiddle factor pointer initialization
	cfft.calc(handleCFFT32);                              // Compute the FFT
	// Step 6: Calculate the magnitude
	cfft.mag(handleCFFT32);                               // Q30 format (abs(ipcbsrc)/2^16).^2
#endif
	return(1);
}

uint16_t FIXPT_DSP_genReport()
{
	//Locals
	int16_t i;
	uint16_t goldPass = 0; // Each test must define an expected pass value

#if RUN_TEST == TEST_1
	goldPass =  2*FFT_SIZE;
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
	goldPass =  8*FFT_SIZE;
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
	goldPass =  2*FFT_SIZE;
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
	goldPass =  FFT_SIZE;
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
//###########################################################################
// End of File
//###########################################################################
