//#############################################################################
//
// FILE:        main.c
//
// Description: This example shows how to use the C2000 Real-Time CLA
//              complex FFT algorithms to perform a real FFT
//
//#############################################################################
// 
// 
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "f2837x_fft_examples_setup.h"
#include "cfft_512_shared.h"
#include "device.h"
#include <float.h>
#include <stdio.h>

//!
//! \addtogroup CFFT_EXAMPLES Complex Fast Fourier Transform (N = 512) Example

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define NSTAGES			9
#define NSAMPLES 		(1<<NSTAGES)
#define ERR_EPSILON     0.001f
#define TEST_NUMBER     1
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("IOBuffer")
#else
#pragma DATA_SECTION(IOBuffer,"IOBuffer")
#endif //__cplusplus
// \brief Test Input Data
//
float IOBuffer[2*NSAMPLES] = {

#if TEST_NUMBER == 1
	#include "cfft_512_data_in1.h"
#elif TEST_NUMBER == 2
    #include "cfft_512_data_in2.h"
#elif TEST_NUMBER == 3
    #include "cfft_512_data_in3.h"
#elif TEST_NUMBER == 4
    #include "cfft_512_data_in4.h"
#endif
};

// \brief Expected Output
//
const float goldenOutput[2*NSAMPLES] = {

#if TEST_NUMBER == 1
    #include "cfft_512_data_out1.h"
#elif TEST_NUMBER == 2
    #include "cfft_512_data_out2.h"
#elif TEST_NUMBER == 3
    #include "cfft_512_data_out3.h"
#elif TEST_NUMBER == 4
    #include "cfft_512_data_out4.h"
#endif
};

// \brief Error
//
float error[2*NSAMPLES];
float maxError, minError;

uint16_t pass = 0;
uint16_t fail = 0;
uint16_t i;
uint32_t cycleCountStart =0 , cycleCountEnd = 0, cycleCount = 0;

char buffer[200];
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the 512-sample CFFT example
//! \return returns a 1
//!
//! This example shows how to use the cla dsp supported CFFT routines from the
//! library. The input is placed in a section IOBuffer that needs to be
//! aligned to the size of the input in words to allow the bit reverse
//! addressing in stage 1 of the FFT to work properly.
//!
int main( void )
{

	CLA_DSP_initSystemClocks();

	CLA_DSP_initEpie();
	
    CLA_DSP_configClaMemory();

    CLA_DSP_initCpu1Cla1();

    //*************************************************************************
    // Running the FFT
    //*************************************************************************
    //! \b Running \b the \b FFT
    //! The FFT is called in task 1 of the CLA. The user can either configure
    //! task 1 to respond to a peripheral trigger source or force it in 
    //! software as is done in this example
    //! \code
    //*************************************************************************
	// Step 1: Force task 1

    CPUTimer_startTimer(CPUTIMER0_BASE);
    cycleCountStart = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    cycleCountEnd = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    cycleCount = cycleCountStart - cycleCountEnd;

    cycleCountStart = CPUTimer_getTimerCount(CPUTIMER0_BASE);

    asm("  IACK  #0x0001");
    asm("  RPT #3 || NOP");
    while (CLA_getTaskRunStatus(CLA1_BASE, CLA_TASK_1) == 1);

    cycleCountEnd = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    cycleCount = cycleCountStart - cycleCountEnd - cycleCount;

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************

	// Step 2: Verify the result
    maxError = 0;
    minError = FLT_MAX;
	for(i = 0; i < 2*NSAMPLES; i++){
	  error[i] = fabs(IOBuffer[i] - goldenOutput[i]);
	  if(i == 0){
		  maxError = minError = error[i];
	  }else{
		  if(maxError < error[i]){
			  maxError = error[i];
		  }
		  if(minError > error[i]){
			  minError = error[i];
		  }
	  }
	  if( error[i] > ERR_EPSILON ){
          fail++;
	  }else{
		  pass++;
	  }
	}

	sprintf(buffer, "Test: %d, pass: %d, fail: %d, tolerance: %e, max Err: %e min Err: %e cycles: %ld",
			TEST_NUMBER, pass, fail, ERR_EPSILON, maxError, minError, cycleCount);
	puts(buffer);

	asm(" ESTOP0");
    return 1;
}
// End of main

//*****************************************************************************
// ISR
//*****************************************************************************
__interrupt void cla1Isr1 ()
{
	// Acknowledge the end-of-task interrupt for task 1
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);
//	asm(" ESTOP0");
}

__interrupt void cla1Isr2 ()
{
	asm(" ESTOP0");

}

__interrupt void cla1Isr3 ()
{
	asm(" ESTOP0");

}

__interrupt void cla1Isr4 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr5 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr6 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr7 ()
{
	asm(" ESTOP0");
}

__interrupt void cla1Isr8 ()
{
	asm(" ESTOP0");
}

// @} //addtogroup

// End of file
