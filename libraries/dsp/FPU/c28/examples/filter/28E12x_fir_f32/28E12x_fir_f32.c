//#############################################################################
//! \file /28E12x_fir_f32.c
//!
//! \brief  Demo code for the Finite Impulse Response Filter
//!
//! This example demonstrates the FIR filter module
//!
//
//  Group:             C2000
//  Target Family:     F28E12x
//
//#############################################################################
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

#include "string.h"
#include "math.h"
#include "stdio.h"


//!
//! \addtogroup FIR_EXAMPLES Finite Impulse Response Filter

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define FIR_ORDER       63              // ORDER = NUM_TAPS - 1
#define SIGNAL_LENGTH   (FIR_ORDER+1)* 4
#define EPSILON         0.1

//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("firLdb");
#pragma DATA_SECTION("sigIn");
#pragma DATA_SECTION("sigOut");
#pragma DATA_SECTION("firCoef");
#else
#pragma DATA_SECTION(dBuf, "firLdb");
#pragma DATA_SECTION(sigIn, "sigIn");
#pragma DATA_SECTION(sigOut, "sigOut");
#pragma DATA_SECTION(coeff, "firCoef");
#endif //__cplusplus

//! \brief The Delay buffer for the filter
//!
float32_t dBuf[FIR_ORDER+1];
float32_t* delayPtr = dBuf;

//! \brief Input signal
//!
float32_t sigIn[SIGNAL_LENGTH] = {
    #include "data_input_fir.h"
};
float32_t* inPtr = sigIn;

//! \brief Output signal
//!
float32_t sigOut[SIGNAL_LENGTH];
float32_t* outPtr = sigOut;

//! \brief Co-efficient Array
//! \note For best performance in standalone mode, the user
//! is encouraged to copy these coefficient from FLASH to RAM
//! at runtime
float32_t coeff[FIR_ORDER+1]= {
#include "coeffs_fir.h"
};
float32_t* coefPtr = &coeff[0];

float32_t FIRgoldenOut[SIGNAL_LENGTH] = {
    #include "data_output_fir.h"
};


//
// Calculating a digital frequency
// Let sampling frequency = 1MHz
// primary signal @ 10KHz and a secondary signal @ 40KHz
// Therefore k1 = 1K/100k = 0.01
//           k2 = 33K/100k = 0.33
// composite signal = 1/2(sin(2*pi*i*k1) + sin(2*pi*i*k2))
//                  = 1/2(sin(0.062831853071 * i) + sin(2.073451151*i))
//
float32_t    RadStep  = 0.062831853071f;
float32_t    RadStep2 = 2.073451151f;
float32_t    Rad      = 0.0f;
float32_t    Rad2     = 0.0f;

// Filter Input and Output Variables
float32_t xn,yn;
int16_t  count = 0;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the FIR example
//!
//!  Watch Variables:
//!  -# sigIn  Input buffer
//!  -# sigOut Output buffer
//!
int fir_fpu32_test(void)
{
    // Clear input buffers:
    memset(inPtr, 0, SIGNAL_LENGTH*sizeof(float32_t));
    memset(outPtr, 0, SIGNAL_LENGTH*sizeof(float32_t));

    Rad      = 0.0f;
    Rad2     = 0.0f;
    int i;
    for(i = 0; i < SIGNAL_LENGTH; i++)
    {
        xn = 0.5*sin(Rad) + 0.5*sin(Rad2); //Q15
        sigIn[i]         = xn;
        myFIR0_handle->input = xn;
        myFIR0_handle->calc(myFIR0_handle);
        yn = myFIR0_handle->output;
        sigOut[i]        = yn;
        Rad              = Rad + RadStep;
        Rad2             = Rad2 + RadStep2;
    }

    // Check the output
    for(i = 0; i < SIGNAL_LENGTH; i++){
        if(fabsf(FIRgoldenOut[i] - sigOut[i]) <= EPSILON){
            pass++;
        }else{
            fail++;
        }
    }

    printf("Total of %d tests pass, and %d failure",pass,fail);

    return 1;
}

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    fir_fpu32_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
