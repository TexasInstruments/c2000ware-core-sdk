//#############################################################################
//! \file /dsp_MaxIndex_f28p55x.c
//!
//! \brief  Find the index of the maximum value in an array
//
//  Group:             C2000
//  Target Family:     F28P55X
//
//#############################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
//! \addtogroup VECTOR_EXAMPLES Maximum Array Index

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE            100U
#define MAX_POSITION    45U
#define MAX_VALUE       3.1321782f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the max index function
//!
float32_t x[SIZE] = {
    #include "data_input_maxidx.h"
};

//! \brief Index of the maximum array value
//!
uint16_t index = SIZE + 1;

uint16_t pass = 0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Max Index example
//! \return 1
//!
//!  Watch Variables:
//!
//! -# index Index of the max value in the array
//!
int max_idx_test(void)
{
    //=========================================================================
    // Max Index test
    //=========================================================================
    index = maxidx_SP_RV_2(x, SIZE);

    // Check the output
    if((index == MAX_POSITION) && (x[index] == MAX_VALUE)){
        pass++;
    }else{
        fail++;
    }

    // sort the array and run the test again
    qsort_SP_RV(x, SIZE);

    index = maxidx_SP_RV_2(x, SIZE);

    // Check the output
    if((index == (SIZE - 1)) && (x[index] == MAX_VALUE)){
        pass++;
    }else{
        fail++;
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

    max_idx_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
