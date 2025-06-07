//###########################################################################
//
// TITLE:   atan_report.c
//
// Description: Compare observed output against expected output vector and 
// print a PASS/FAIL report to the console
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
#include <stdio.h>
#include <math.h>
#include "DSP28x_Project.h"
#include "F2806x_Cla_defines.h"  

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

float atan_expected[BUFFER_SIZE]={
 1.5395565,  1.5385494,  1.5374753,  1.5363272, 
 1.5350972,  1.5337762,  1.5323538,  1.5308176, 
 1.5291537,  1.5273454,  1.5253731,  1.5232133, 
 1.5208379,  1.5182133,  1.5152978,  1.5120405, 
 1.5083776,  1.5042281,  1.4994888,  1.4940244, 
 1.4876550,  1.4801364,  1.4711276,  1.4601392, 
 1.4464413,  1.4288993,  1.4056476,  1.3734008, 
 1.3258177,  1.2490457,  1.1071488,  0.7853982, 
 0.0000000, -0.7853982, -1.1071488, -1.2490457, 
-1.3258177, -1.3734008, -1.4056476, -1.4288993, 
-1.4464413, -1.4601392, -1.4711276, -1.4801364, 
-1.4876550, -1.4940244, -1.4994888, -1.5042281, 
-1.5083776, -1.5120405, -1.5152978, -1.5182133, 
-1.5208379, -1.5232133, -1.5253731, -1.5273454, 
-1.5291537, -1.5308176, -1.5323538, -1.5337762, 
-1.5350972, -1.5363272, -1.5374753, -1.5385494
};

//
// test_report - 
//
void
test_report(void)
{
    unsigned int i;
    unsigned int pass_count=0;
    unsigned int fail_count=0;
    float fError[BUFFER_SIZE];
    
    for(i=0;i<BUFFER_SIZE;i++)
    {
        fError[i] = fabs(atan_expected[i]-y[i]);
        if( fError[i] < 0.01)
        {
            pass_count++;
        }
        else
        {
        fail_count++;
        }
    }
    if(fail_count)
    { 
        printf("FAIL , Pass Count = %d Fail Count = %d\n",pass_count,fail_count);
    }
    else
    {
        puts("PASS\n");     
    }
}

//
// End of File
//

