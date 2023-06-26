//###########################################################################
//
// FILE:  vmaxfloat_shared_data.c
//
// TITLE: Vector Maximum Shared Data
//
// Description: Declare shared memory variables and assign them to specific 
// CLA-accessible memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 to CPU Message RAM
//!    - max1 - Maximum value in vector 1
//!    - index1 - Index of the maximum value in vector 1
//!    - max2 - Maximum value in vector 2
//!    - index2 - Index of the maximum value in vector 2
//!    - max3 - Maximum value in vector 3
//!    - index3 - Index of the maximum value in vector 3
//!    - max4 - Maximum value in vector 4
//!    - min4 - Minimum value in vector 4
//!  - CPU to CLA1 Message RAM
//!    - vector1 - Input vector to task 1
//!    - vector2 - Input vector to task 2
//!    - vector3 - Input vector to task 3
//!    - vector4 - Input vector to task 4
//!    - length1 - Length of vector 1
//!    - length2 - Length of vector 2
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#pragma DATA_SECTION(length1,"CpuToCla1MsgRAM");
float  vector1[] = {1.0,-11.3,6.2,10.8,2.5,7.3,13.2,3.1};
int32  length1 = 8;
//
//Length 3 and 4 are #defined in vmaxfloat_shared.h
//

//
// CLA Output Data
//
#pragma DATA_SECTION(max1,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(index1,"Cla1ToCpuMsgRAM");
float32 max1;
int32   index1;

//
// Task 2 (C) Variables
//

//
// CLA Input Data
//
#pragma DATA_SECTION(vector2,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(length2,"CpuToCla1MsgRAM");
float  vector2[] = {-3.6,-11.3,-16.2,-10.8,-2.5,-12.5,-33.3};
int32  length2 = 7;

//
// CLA Output Data
//
#pragma DATA_SECTION(max2,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(index2,"Cla1ToCpuMsgRAM");
float32 max2;
int32   index2;

//
// Task 3 (C) Variables
//

//
// CLA Input Data
//
#pragma DATA_SECTION(vector3,"CpuToCla1MsgRAM");
float  vector3[] = {12.2,2.3,9.6,9.2,6.2,10.8,2.5,-13.3};

//
// CLA Output Data
//
#pragma DATA_SECTION(max3,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(index3,"Cla1ToCpuMsgRAM");
int32   index3;
float32 max3;

//
// Task 4 (C) Variables
//

//
// CLA Input Data
//
#pragma DATA_SECTION(vector4,"CpuToCla1MsgRAM");
float  vector4[] = {1.1,9.9,7.7,-5.5,-2.2,4.4,-8.8,0.0,6.6,-4.4};

//
// CLA Output Data
//
#pragma DATA_SECTION(max4,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(min4,"Cla1ToCpuMsgRAM");
float32 max4, min4;

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
#pragma DATA_SECTION(i,"Cla1ToCpuMsgRAM");
int32   i;

//
// End of File
// 

