//#############################################################################
//! \file /dsp_Median_f28p55x.c
//!
//! \brief  Find the median of a scalar vector
//
//  Group:             C2000
//  Target Family:     F28P55x
//
//#############################################################################
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "stdio.h"


//!
//! \addtogroup VECTOR_EXAMPLES Index of the Maximum Value in an Array

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE            256U
#define MEDIAN_VALUE    2.637057027747737f
#define EPSILON         0.000001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the median function
//!
float32_t x[SIZE] = {
    #include "data_input_median.h"
};

//! \brief copy of the input
//!
float32_t y[SIZE];

//! \brief Median of the array
//!
float32_t median = 0.0f;

uint16_t pass = 0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Median example
//! \return 1
//!
//!  Watch Variables:
//!
//! -# median Median of the array
//!
int median_test(void)
{
    int i;
    //=========================================================================
    // Median test
    //=========================================================================
    // Copy the input "x" over to "y"
    memcpy_fast(y, x, sizeof(float)*SIZE);
    // Run the median algorithm, while re-ordering the input
    median = median_SP_RV(x, SIZE);

    //Check the output
    if(fabsf(median - MEDIAN_VALUE) < EPSILON){
        pass++;
    }else{
        fail++;
    }

    //=========================================================================
    // Median test (without reordering)
    //=========================================================================
    // Copy the "y" back over to "x"
    memcpy_fast(x, y, sizeof(float)*SIZE);
    median = median_noreorder_SP_RV(y, SIZE);

    //Check the output
    if(fabsf(median - MEDIAN_VALUE) < EPSILON){
        pass++;
    }else{
        fail++;
    }

    // Check no reordering happens
    for(i = 0; i < SIZE; i++){
        if(fabsf(x[i] - y[i]) < EPSILON){
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

    median_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
