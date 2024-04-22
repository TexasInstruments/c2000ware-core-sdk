//###########################################################################
//
// FILE:  fir32_shared_data.c
//
// TITLE: Finite Impulse Response Filter Shared Data
//
// DESCRIPTION: Declare shared memory variables and assign them to specific
// CLA-accessible memory locations
//
//! \addtogroup f2805x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1 (RAML2)
//!    - fCoeffs - Filter Coefficients
//!    - fDelayLine - Delay line memory elements
//!  - CLA1 to CPU Message RAM
//!    - xResult - Result of the FIR operation
//!  - CPU to CLA1 Message RAM
//!    - xAdcInput - Simulated ADC input
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME, _shared.h))

//
// Global Data
// Ensure that all data is placed in the data rams
//

//
// Task 1 (C) Variables
//
#pragma DATA_SECTION(xAdcInput,"CpuToCla1MsgRAM");
long xAdcInput;
#pragma DATA_SECTION(xResult,"Cla1ToCpuMsgRAM");
long xResult;
#pragma DATA_SECTION(fCoeffs,"Cla1DataRam1");
float fCoeffs[FILTER_LEN] = {0.0625, 0.25, 0.375, 0.25, 0.0625};
#pragma DATA_SECTION(fDelayLine,"Cla1DataRam1");
float fDelayLine[FILTER_LEN] = {0,0,0,0,0};

unsigned long adc_input[INPUT_LEN] = {
        3036, 452, 2449, 973, 3824, 2852, 804, 2550,
        430, 482, 3233, 2174, 768, 514, 1301, 4046,
        524, 2624, 1506, 375, 1091, 533, 1296, 698,
        2251, 1347, 844, 1660, 3268, 379, 891, 1056,
        1988, 2678, 355, 430, 1997, 33, 1029, 1625,
        3647, 3068, 3162, 460, 3149, 1733, 3657, 304,
        3272, 2389, 843, 3213, 1622, 2685, 2880, 2802,
        3008, 3031, 1590, 1194, 1118, 2961, 2276, 1648,
        211, 962, 2260, 2472, 153, 2176, 756, 4025,
        299, 3010, 938, 3950, 2758, 446, 869, 1647,
        363, 3975, 2629, 1772, 1760, 2588, 317, 2542,
        3270, 3551, 1984, 2846, 1850, 519, 3743, 633,
        3862, 354, 622, 3105, 2498, 550, 2894, 1562,
        2800, 1501, 3203, 1772, 244, 404, 2285, 660,
        541, 1512, 412, 2685, 1294, 582, 1284, 3105,
        2960, 2806, 1205, 0, 0, 0, 0, 0
    };
unsigned long fir_output[OUTPUT_LEN];

//
// Task 2 (C) Variables
//

//
// Task 3 (C) Variables
//

//
// Task 4 (C) Variables
//

//
// Task 5 (C) Variables
//

//
// Task 6 (C) Variables
//

//
// Task 7 (C) Variables
//

//
// Task 8 (C) Variables
//

//
// Common (C) Variables
//


