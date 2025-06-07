//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_FIR32_Alt/test_fir32d_alt.c
//!
//! \brief  Alternate 32-bit FIR Filter Example
//!
//! \date   Aug 12, 2014
//! 
//! This module shows an alternate 32-bit FIR implementation. The alternate
//! version can have upto 2^16 or 65536 filter taps.
//! The header structure of 32 bit filter is shown as follows:
//! 
//! typedef struct { 
//!     int32_t *coeff_ptr;        
//!     int32_t * dbuffer_ptr;
//!     int	cbindex;
//!     int order; 
//!     int input;   
//!     int output; 
//!     void (*init)(void *);
//!     void (*calc)(void *);
//!     }FIR32; 
//! 
//! Users can also use default templates defined within fir.h to initialize 
//! the FIR32 header structure.
//!                 
//! FIR32  fir= FIR32_ALT_DEFAULTS;
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
//$Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
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
#include "test_fir32d_alt.h"
#include "filter.h"
#include "device.h"
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************                                        
// Create an Instance of FIR32 module and place the object in "firfilt" section 
#ifndef __cplusplus
#pragma DATA_SECTION(fir, "firfilt");
#else
#pragma DATA_SECTION("firfilt");
#endif
FIR32 fir= FIR32_ALT_DEFAULTS;
#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_2) || (RUN_TEST == TEST_10))
int16_t temp[SIGNAL_LENGTH*2];
int32_t *dbuffer;
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) || \
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || \
	   (RUN_TEST == TEST_9))
// Define the Delay buffer for the "FIR_ORDER"th order filter
// and place it in "firldb" section. 
// Its size should be FIR_ORDER+1
// For the alternate FIR implementation, the delay line buffer need
// not be aligned to a specific boundary
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
int32_t sigIn[SIGNAL_LENGTH]= {
#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_input.txt))
};

#ifndef __cplusplus
#pragma DATA_SECTION(sigOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int32_t sigOut[SIGNAL_LENGTH];                               

const int32_t goldOut[SIGNAL_LENGTH] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_output.txt))
};

// Error between computed output and MATLAB output
int32_t err[SIGNAL_LENGTH];

// Define Constant Coefficient Array  and place it in the "coefffilt"
// section. You can either reverse the order of the coefficients at 
// run time (done in this example) or just store them in reversed order.
// Index       
//         +---------+
//  0      | h(L-1)  |
//  2      | h(L-2)  |
//  4      | h(L-3)  |
//  6      | h(L-4)  |
//  ...    | ...     |
//  L-3    | h(2)    |
//  L-2    | h(1)    |
//  L-1    | h(0)    |
//         +---------+
// The size of the array is FIR_ORDER+1
//

#pragma DATA_SECTION("coefffilt");

int32_t coeff[FIR_ORDER+1]  = {
#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_coeffs.txt))
};


#pragma DATA_SECTION("coefffilt");

int32_t revCoeff[FIR_ORDER+1];
#endif

uint16_t pass, fail;
//*****************************************************************************
// function definitions
//*****************************************************************************
uint16_t FIXPT_DSP_runTest()
{
	//Locals
    int16_t i = 0;

#if(RUN_TEST == TEST_1)
    // Write dummy codes to temp
    memset(temp, 0xBAAD, sizeof(temp));

    dbuffer         = (int32_t *)&temp[FIR_ORDER]; // Set dbuffer to an odd address
    fir.order       = FIR_ORDER;        // odd
    fir.dbuffer_ptr = &dbuffer[0];
    fir.init(&fir);

#elif(RUN_TEST == TEST_2)
    // Write dummy codes to temp
    memset(temp, 0xBAAD, sizeof(temp));

    dbuffer         = (int32_t *)&temp[FIR_ORDER]; // Set dbuffer to an even address
    fir.order       = FIR_ORDER;        // even
    fir.dbuffer_ptr = &dbuffer[0];
    fir.init(&fir);
#elif(RUN_TEST == TEST_10)
    // Write dummy codes to temp
    memset(temp, 0xBAAD, sizeof(temp));

    dbuffer         = (int32_t *)&temp[FIR_ORDER]; // Set dbuffer to an even address
    fir.order       = FIR_ORDER;        // even
    fir.dbuffer_ptr = &dbuffer[0];
    fir.init(&fir);
    fir.calc(&fir);
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) || \
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || \
	   (RUN_TEST == TEST_9))
    	// zero out sigOut
    	memset(sigOut, 0, sizeof(sigOut));
		// Reorder the coefficients
		for(i = 0; i < FIR_ORDER_REV + 1; i++){
			revCoeff[FIR_ORDER_REV-i] = coeff[i];
		}

		// Initialize FIR32 object
		fir.order       = FIR_ORDER;
		fir.dbuffer_ptr = &dbuffer[0];
		fir.coeff_ptr   = (int32_t *)&revCoeff[0];
		fir.init(&fir);

		// FIR calculation
		for(i = 0; i < SIGNAL_LENGTH; i++){
			fir.input = sigIn[i]; // Q31 format
			fir.calc(&fir);
			sigOut[i]=fir.output; // Q30 format
		}
#endif
	return(1);

}
uint16_t FIXPT_DSP_genReport()
{
	//Locals
	int16_t i;
	uint16_t goldPass = 0; // Each test must define an expected pass value
pass = 0; fail = 0;
#if ((RUN_TEST == TEST_1)||(RUN_TEST == TEST_2))
	goldPass = 2*(FIR_ORDER + 1);
	// Check above dbuffer
	for(i = 0; i < FIR_ORDER; i++) {
		if(temp[i] == 0xBAAD){
			pass++;
		}else{
			fail++;
		}
	}
	// check dbuffer
	for(i = FIR_ORDER; i < (FIR_ORDER + goldPass); i++) {
		if(temp[i] == 0){
			pass++;
		}else{
			fail++;
		}
	}
	// Check below dbuffer
	for(i = FIR_ORDER+goldPass; i < 2*SIGNAL_LENGTH; i++) {
		if(temp[i] == 0xBAAD){
			pass++;
		}else{
			fail++;
		}
	}

#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) || \
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7) || (RUN_TEST == TEST_8) || \
	   (RUN_TEST == TEST_9))
	goldPass =  SIGNAL_LENGTH;
	// Check that bit reversal was done correctly
	for(i = 0; i < goldPass; i++ ){
		err[i] = abs(goldOut[i] - sigOut[i]);
		if(err[i] < TOLERANCE){
			pass++;
		}else{
			fail++;
		}
	}

#endif

	return(1);
}

int main()
{
Device_init();
        DINT;                       //Globally disable maskable CPU interrupts
        Interrupt_initModule();             //Clear and disable all PIE interrupts
        Interrupt_initVectorTable();            //Populate the PIE interrupt vector table with shell ISRs
/*
    //Clean up input/output buffer
    for(i=0; i < (FFT_SIZE+2); i=i+2){
      ipcb[i]   = 0;
      ipcb[i+1] = 0;
    }
*/
    FIXPT_DSP_runTest();
    FIXPT_DSP_genReport();

    for(;;);
    return 1;
}
//###########################################################################
// End of File
//###########################################################################
