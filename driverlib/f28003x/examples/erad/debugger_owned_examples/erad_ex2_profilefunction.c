//#############################################################################
//
// FILE:   erad_ex2_profilefunction.c
//
// TITLE:  ERAD Function Profile Example
//
//! \addtogroup driver_example_list
//! <h1> ERAD Profile Function </h1>
//!
//! This example contains a basic FIR calculation and sorting algorithm to help
//! demonstrate the function profiling capability of the ERAD peripheral. A
//! number of FIR sums are calculated within a loop and are then sorted using
//! the insertion sort algorithm. Cycle counts of both the FIR calculations and
//! the sorting algorithm are output to the screen through the scripting console.
//! In this example, it can be seen that sorting the data takes up a majority
//! of the CPU cycles executed in this program.
//!
//! To properly use the provided ERAD script, the following variables must be
//! set in the scripting environment prior to launching the ERAD script:
//!
//! - var PROJ_NAME = "erad_debugger_ex2_profilefunction"
//! - var PROJ_WKSPC_LOC = "<proj_workspace_path>"
//! - var PROJ_CONFIG = "<name of active configuration [CPU1_FLASH|CPU1_RAM]>"
//!
//! To run the ERAD script, use the following command in the scripting console:
//!
//! - loadJSFile("<proj_workspace_path>\\erad_debugger_ex2_profilefunction\\erad_ex2_profile_function.js", 0);
//!
//! Note that the script must be run after loading and running the .out on the
//! C28x core.
//!
//! The included JavaScript file, erad_ex2_profile_function.js, uses Debug Server
//! Scripting (DSS) features. For information on using the DSS, please visit:
//! http://software-dl.ti.com/ccs/esd/documents/users_guide/sdto_dss_handbook.html
//!
//! This example uses 4 HW breakpoints and 2 counters:
//!  - HWBP_1 : PC = start address of performFIR
//!  - HWBP_2 : PC = end address of performFIR
//!  - HWBP_3 : PC = start address of sortMax
//!  - HWBP_4 : PC = end address of sortMax
//!  - CTM_1  : Used to count the performFIR execution cycles.
//!             Configured in start-stop mode with start event as HWBP_1 and
//!             stop event as HWBP_2
//!  - CTM_2  : Used to count the sortMax execution cycles.
//!             Configured in start-stop mode with start event as HWBP_3 and
//!             stop event as HWBP_4
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - FIR_iterationCounter - A counter for the number of times FIR calculation
//!    and sorting was performed
//!
//! \b Profiling \b Script \b Output
//!  - Current FIR cycle count (CTM_1)
//!  - Max FIR cycle count (maximum value of CTM_1)
//!  - Current sorting function cycle count (CTM_2)
//!  - Max sorting function cycle count (maximum value of CTM_2)
//!
//! Note that the the counters are reset after the stop event. The counter value
//! remains 0 till the next start event occurs. The javascript continuously
//! reads the counter value in a while(1) and hence the current counter may
//! return 0.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define FIR_TAPS 64
#define FIR_NUM_ITERATIONS 250

//
// Global FIR variables
//
const uint16_t FIR_coeffVals[FIR_TAPS] =
{
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
    2048, 2048, 2048, 2048,
};
uint16_t FIR_values[FIR_TAPS];
volatile uint32_t FIR_sums[FIR_NUM_ITERATIONS];
uint32_t FIR_iterationCounter;
uint32_t sortedArr[FIR_NUM_ITERATIONS];

//
// Pre-chosen Pseudo Random Generator constants
//
const uint16_t PseudoRand_multiplier = 31821;
const uint16_t PseudoRand_increment = 13849;
uint16_t PseudoRand_seed = 21845;

//
// Function Prototypes
//
uint32_t performFIR(uint16_t [], const uint16_t []);
uint16_t generatePseudoRand16(uint16_t *);
void sortMax(uint32_t [], uint32_t);

//
// Main
//
int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize FIR_values and iteration counter to 0
    //
    uint32_t i = 0;
    for(i = 0; i < FIR_TAPS; i++)
    {
        FIR_values[i] = 0;
    }

    FIR_iterationCounter = 0;

    //
    // Loop forever, performing FIR calculations and sorting results
    //
    while(1)
    {
        //
        // Perform FIR and record sum
        //
        for(i = 0; i < FIR_NUM_ITERATIONS; i++)
        {
            //
            // Set 1st FIR element to a pseudo random number and perform FIR
            //
            FIR_values[0] = generatePseudoRand16(&PseudoRand_seed);
            FIR_sums[i] = performFIR(FIR_values, FIR_coeffVals);
        }

        //
        // Copy sums array into scratch array
        //
        for(i = 0; i < FIR_NUM_ITERATIONS; i++)
        {
            sortedArr[i] = FIR_sums[i];
        }

        //
        // Sort results and grab maximum value, the last element of the sorted
        // array
        //
        sortMax(sortedArr, FIR_NUM_ITERATIONS);
        volatile uint32_t maxValue = sortedArr[FIR_NUM_ITERATIONS - 1];

        //
        // Record that FIR sums were calculated and sorting of the data was done
        //
        FIR_iterationCounter++;
    }
}

//
// generatePseudoRand16 - Generate a pseudo random 16-bit number by passing a
// start value or "seed". This generator is a linear congruential pseudo random
// generator, which is very fast. The basic calculation is:
//
// randNum(n) = ((randNum(n-1) * multiplier) + increment) modulo M
//
uint16_t
generatePseudoRand16(uint16_t *seed)
{
    //
    // Perform calculation. Mask off bottom bits in lieu of modulus operation
    //
    *seed = ((uint32_t)*seed * PseudoRand_multiplier + PseudoRand_increment)
            & 0xFFFF;
    return(*seed);
}

//
// performFIR - Calculate Finite Impulse Response (FIR)
//
uint32_t
performFIR(uint16_t values[], const uint16_t coeff[])
{
    uint32_t sum = 0;

    //
    // Loop over elements starting with Nth element and ending with 1st element
    //
    int32_t i = 0;
    for(i = FIR_TAPS - 1; i >= 0; i--)
    {
        //
        // Multiply current value by respective coefficient
        //
        sum += ((uint32_t)values[i] * (uint32_t)coeff[i]);

        //
        // Store value only after processing Nth (FIR_TAPS - 1) element
        //
        if(i < FIR_TAPS - 1)
        {
            values[i + 1] = values[i];
        }
    }
    return(sum);
}

//
// sortMax - Perform insertion sort on an array of values, sorting from least to
// greatest
//
void
sortMax(uint32_t values[], uint32_t numElements)
{
    //
    // Loop over all elements starting with index 1. This allows for at least
    // two elements to be compared
    //
    uint32_t i = 1;
    for(i = 1; i < numElements; i++)
    {
        uint32_t j = i;

        //
        // Inner loop walks elements backwards from current index
        //
        for(j = i; j > 0; j--)
        {
            //
            // If current value is less than the previous value, swap them
            //
            if(values[j] < values[j-1])
            {
                uint32_t temp = values[j-1];
                values[j-1] = values[j];
                values[j] = temp;
            }
        }
    }
}

//
// End of File
//
