//###########################################################################
//
// FILE:  iir2p2z_report.c
//
// TITLE: 2 Pole 2 Zero Infinite Impulse Response Filter Report
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


float iir_expected[NUM_SAMPLES]={
0, 0.008754415, 0.02288298, 0.02726187,
0.03795755, 0.05661327, 0.06815149, 0.08971455,
0.1159805, 0.1349670, 0.1645004, 0.1938129,
0.2159233, 0.2481003, 0.2754995, 0.2969926,
0.3276609, 0.3500223, 0.3688507, 0.3954768,
0.4113952, 0.4267188, 0.4478308, 0.4569381,
0.4684406, 0.4831003, 0.4855416, 0.4930161,
0.5005732, 0.4967500, 0.4999563, 0.5000126,
0.4904927, 0.4891656, 0.4816235, 0.4671103,
0.4610198, 0.4461307, 0.4274355, 0.4164503,
0.3948304, 0.3728325, 0.3569719, 0.3295808,
0.3051807, 0.2846532, 0.2527421, 0.2268174,
0.2020469, 0.1670849, 0.1404567, 0.1120952,
0.07568341, 0.04909494, 0.01802110, -0.01820113,
-0.04409146, -0.07679208, -0.1112392, -0.1358536,
-0.1689253, -0.2001516, -0.2229802, -0.2550509,
-0.2818236, -0.3024068, -0.3320566, -0.3534117,
-0.3713224, -0.3971615, -0.4124396, -0.4272688,
-0.4480195, -0.4568799, -0.4682287, -0.4828055,
-0.4852195, -0.4927015, -0.5002885, -0.4965075,
-0.4997604, -0.4998623, -0.4903836, -0.4890918,
-0.4815782, -0.4670869, -0.4610124, -0.4461341,
-0.4274456, -0.4164638, -0.3948451, -0.3728467,
-0.3569847, -0.3295917, -0.3051894, -0.2846599,
-0.2527469, -0.2268206, -0.2020488, -0.1670859,
-0.1404569, -0.1120951, -0.07568294, -0.04909432,
-0.01802043, 0.01820178, 0.04409203, 0.07679256,
0.1112396, 0.1358539, 0.1689255, 0.2001518,
0.2229803, 0.2550510, 0.2818236, 0.3024068,
0.3320566, 0.3534117, 0.3713224, 0.3971614,
0.4124396, 0.4272687, 0.4480195, 0.4568799,
0.4682287, 0.4828055, 0.4852195, 0.4927014
};

void test_report(void)
{
    unsigned int i;
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    float fError[NUM_SAMPLES];
    for(i = 0; i < NUM_SAMPLES; i++)
    {
        fError[i] = fabs(iir_expected[i]-fBiquadOutput[i]);
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
        printf("FAIL , Pass Count = %d Fail Count = %d\n", pass_count,
                fail_count);
    }
    else
    {
        puts("PASS\n");
    }
}

