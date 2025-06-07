//###########################################################################
//
// TITLE:  fir32_report.c
//
// Description: Compare observed output against expected output vector and 
// print a PASS/FAIL report to the console
//
//###########################################################################
// $TI Release: $
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
#include <stdio.h>
#include <math.h>
#include "DSP28x_Project.h"
#include "F2806x_Cla_defines.h"  

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

unsigned long fir_expected[OUTPUT_LEN]={
189, 787, 1404, 1601, 1703, 2139, 2593, 2446,
1917, 1473, 1171, 1391, 1951, 1877, 1243, 1098,
1708, 2169, 2039, 1767, 1415, 987, 811, 863,
1002, 1266, 1489, 1426, 1413, 1758, 1843, 1351,
1021, 1306, 1756, 1682, 1159, 918, 951, 897,
1153, 1972, 2802, 2983, 2492, 2050, 2155, 2399,
2281, 2103, 2181, 2144, 2022, 2138, 2315, 2508,
2741, 2880, 2865, 2535, 1910, 1499, 1699, 2136,
2088, 1484, 1015, 1236, 1728, 1726, 1407, 1449,
1862, 2097, 1976, 1936, 2282, 2621, 2246, 1423,
1044, 1201, 1760, 2452, 2555, 2171, 1934, 1759,
1715, 2233, 2893, 2981, 2663, 2280, 1892, 1810,
2048, 2193, 1967, 1487, 1495, 2000, 2070, 1845,
1944, 2137, 2196, 2272, 2209, 1645, 978, 935,
1171, 1073, 914, 1014, 1318, 1564, 1408, 1224,
1669, 2437, 2743, 2287, 1338, 476, 75, 0,
0, 0, 0, 0, 0
};

//
// test_report - 
//
void test_report(void)
{
	unsigned int i;
	unsigned int pass_count=0;
	unsigned int fail_count=0;
	for(i=0;i<OUTPUT_LEN;i++)
    {
		if(fir_output[i]==fir_expected[i])
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

