//###########################################################################
//
// FILE:  vinverse_shared_data.c
//
// TITLE: Vector Inverse Shared Data
//
// DESCRIPTION: Declare shared memory variables and assign them to specific
// CLA-accessible memory locations
//
//! \addtogroup f2805x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1 (RAML2)
//!    - vector2 - Input/Output vector for task 2
//!  - CLA1 to CPU Message RAM
//!    - vector1_inverse - Inverse of input vector1
//!  - CPU to CLA1 Message RAM
//!    - vector1 - Input vector to task 1
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
// CLA Input Data
//
// Note - Vector2 is both input and output
#pragma DATA_SECTION(vector1,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(vector2,"Cla1DataRam1");
float  vector1[5] = {1.0,4.0,8.0,.5,.25};
float  vector2[10] = {-.25,-.5,-.125,-2.0,-4.0,-8.0,8.0,4.0,.25,.125};
// CLA Output Data
//
#pragma DATA_SECTION(vector1_inverse,"Cla1ToCpuMsgRAM");
float   vector1_inverse[LENGTH1];

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
