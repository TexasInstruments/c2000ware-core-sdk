//###########################################################################
//
// FILE:  asin_report.c
//
// TITLE: ASIN Table-Lookup Algorithm Report
//
// DESCRIPTION: Compare observed output against expected output vector and
// print a PASS/FAIL report to the console
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F2805x_Cla_defines.h"

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME, _shared.h))

float asin_expected[BUFFER_SIZE]={
1.570796, 1.393789, 1.320141, 1.263401, 1.215375,
1.172892, 1.134327, 1.098718, 1.065436, 1.034046,
1.004232, 0.9757544, 0.9484279, 0.9221048, 0.8966658,
0.8720123, 0.8480621, 0.8247454, 0.8020028, 0.7797828,
0.7580408, 0.7367374, 0.7158381, 0.6953120, 0.6751316,
0.6552721, 0.6357113, 0.6164289, 0.5974064, 0.5786270,
0.5600753, 0.5417370, 0.5235988, 0.5056486, 0.4878751,
0.4702678, 0.4528166, 0.4355124, 0.4183464, 0.4013104,
0.3843968, 0.3675981, 0.3509074, 0.3343180, 0.3178237,
0.3014185, 0.2850964, 0.2688521, 0.2526802, 0.2365756,
0.2205333, 0.2045484, 0.1886164, 0.1727327, 0.1568929,
0.1410927, 0.1253278, 0.1095943, 0.09388787, 0.07820469,
0.06254076, 0.04689218, 0.03125509, 0.01562564
};

void test_report(void)
{
    unsigned int i;
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    float fError[BUFFER_SIZE];
    for(i = 0; i < BUFFER_SIZE; i++)
    {
        fError[i] = fabs(asin_expected[i] - y[i]);
        if( fError[i] < 0.1)
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
        printf("FAIL , Pass Count = %d Fail Count = %d\n", pass_count,
                fail_count);
    }
    else
    {
        puts("PASS\n");
    }
}

