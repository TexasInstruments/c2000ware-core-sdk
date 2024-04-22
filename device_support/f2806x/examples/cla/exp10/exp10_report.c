//###########################################################################
//
// TITLE:  exp10_report.c
//
// Description: Compare observed output against expected output vector and 
// print a PASS/FAIL report to the console
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Golden Test Values
//
float exp10_expected[BUFFER_SIZE]={
10, 9.646616, 9.305720, 8.976871, 8.659643, 
8.353625, 8.058422, 7.773650, 7.498942, 7.233942, 
6.978306, 6.731704, 6.493816, 6.264335, 6.042964, 
5.829415, 5.623413, 5.424691, 5.232991, 5.048066, 
4.869675, 4.697589, 4.531584, 4.371445, 4.216965, 
4.067945, 3.924190, 3.785515, 3.651741, 3.522695, 
3.398208, 3.278121, 3.162278, 3.050528, 2.942727, 
2.838736, 2.738420, 2.641648, 2.548297, 2.458244, 
2.371374, 2.287573, 2.206734, 2.128752, 2.053525, 
1.980957, 1.910953, 1.843423, 1.778279, 1.715438, 
1.654817, 1.596339, 1.539927, 1.485508, 1.433013, 
1.382372, 1.333521, 1.286397, 1.240938, 1.197085, 
1.154782, 1.113974, 1.074608, 1.036633 };

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
        fError[i] = fabs(exp10_expected[i]-y[i]);
        if(fError[i] < 0.01)
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
        printf("FAIL , Pass count = %d, Fail count = %d\n",pass_count,fail_count);
    }
    else
    {
        puts("PASS\n");
    }
}

//
// End of File
//

