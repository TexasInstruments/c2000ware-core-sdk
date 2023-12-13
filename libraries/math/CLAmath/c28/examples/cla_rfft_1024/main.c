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
#include "rfft_1024_shared.h"
#include "device.h"
#include <float.h>
#include <stdio.h>

//!
//! \addtogroup RFFT_EXAMPLES Real Fast Fourier Transform (N = 1024) Example

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define NSTAGES			9               // 512
#define NSAMPLES 		(1<<NSTAGES)
#define ERR_EPSILON     0.001f
#define TEST_NUMBER		4
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
#if	TEST_NUMBER == 1
	#include "rfft_1024_data_in1.h"
#elif TEST_NUMBER == 2
    #include "rfft_1024_data_in2.h"
#elif TEST_NUMBER == 3
    #include "rfft_1024_data_in3.h"
#elif TEST_NUMBER == 4
    #include "rfft_1024_data_in4.h"
#endif //TEST_MODE
};

#ifdef __cplusplus
#pragma DATA_SECTION("IOBuffer")
#else
#pragma DATA_SECTION(IOBuffer2,"IOBuffer")
#endif //__cplusplus
// \brief Output of the unpack routine
//
float IOBuffer2[2*NSAMPLES + 2];

// \brief Expected Output
//
const float goldenOutput[2*NSAMPLES + 2] = {

#if TEST_NUMBER == 1
	#include "rfft_1024_data_out1.h"
#elif TEST_NUMBER == 2
    #include "rfft_1024_data_out2.h"
#elif TEST_NUMBER == 3
    #include "rfft_1024_data_out3.h"
#elif TEST_NUMBER == 4
    #include "rfft_1024_data_out4.h"
#endif //TEST_NUMBER
};

// \brief Error
//
float error[2*NSAMPLES];
float maxError, minError;

uint16_t pass = 0;
uint16_t fail = 0;
uint16_t index;
uint32_t cycleCountStart =0 , cycleCountEnd = 0, cycleCount = 0;

char buffer[200];
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the 1024-sample RFFT example
//! \return returns a 1
//!
//! This example shows how to use the cla dsp supported CFFT routines from the
//! library to perform a real FFT. The input is placed in a section IOBuffer 
//! that needs to be aligned to the size of the input in words to allow the 
//! bit reverse addressing in stage 1 of the FFT to work properly.
//!
int main( void )
{
    //
    // Clear out the final result buffer
    //
    for(index = 0; index < 2*NSAMPLES + 2  ; index++)
    {
        IOBuffer2[index] = 0.0;
    }


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

    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);
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

	// Step 2: Compare the CLA vs Matlab
    //
    maxError = 0;
    minError = FLT_MAX;

    for(index = 0; index < 2*NSAMPLES + 2; index++)
    {
      error[index] = fabs(IOBuffer2[index] - goldenOutput[index]);
	  if(index == 0)
	  {
		  maxError = minError = error[index];
	  }
	  else
	  {
		  if(maxError < error[index])
		  {
			  maxError = error[index];
		  }
		  if(minError > error[index])
		  {
			  minError = error[index];
		  }
	  }
	  if( error[index] > ERR_EPSILON )
	  {
          fail++;
	  }
	  else
	  {
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
