//###########################################################################
//
// FILE:  shellsort_shared_data.c
//
// TITLE: Shell Sort Shared data
//
// Description: Declare shared memory variables and assign them to specific 
// CLA-accessible memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1 (RAML2)
//!    - vector3 - Input/Output to task 3(in-place sorting)
//!  - CLA1 to CPU Message RAM
//!    - vector1_sorted - Sorted output Task 1
//!    - vector2_sorted - Sorted output Task 2
//!  - CPU to CLA1 Message RAM
//!    - vector1 - Input vector to task 1
//!    - vector2 - Input vector to task 2
//
//###########################################################################
// $TI Release:  $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

//
// Globals (Ensure that all data is placed in the data rams)
//

//
// Task 1 (C) Variables
//

//
// CLA Input Data
//
#pragma DATA_SECTION(vector1,"CpuToCla1MsgRAM");
float  vector1[5] =  {1.0,-11.3,6.2,10.8,2.5};

//             
// CLA Output Data
//
#pragma DATA_SECTION(vector1_sorted,"Cla1ToCpuMsgRAM");
float   vector1_sorted[LENGTH1];

//
// Task 2 (C) Variables
//

//
// CLA Input Data
//
#pragma DATA_SECTION(vector2,"CpuToCla1MsgRAM");
float  vector2[10] = {-10.1,-9.9,-8.8,1.0,2.2,3.3,0.0,4.4,8.8,9.9}; 

//
// CLA Output Data
//
#pragma DATA_SECTION(vector2_sorted,"Cla1ToCpuMsgRAM");
float   vector2_sorted[LENGTH2];

//
// Task 3 (C) Variables
//

//
// CLA Input Data
//

//
// Note: vector3 is input and output (in-place sort)
//
#pragma DATA_SECTION(vector3,"Cla1DataRam1");
int32  vector3[9] =  {-9,-8,1,2,3,0,4,8,9};

//
// CLA Output Data
//

//
// vector3_sorted is vector3 (in place sort);
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

//
// End of File
//

