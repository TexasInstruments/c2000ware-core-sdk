//###########################################################################
//
// TITLE:   matrix_transpose_report.c
//
// Description: Compare observed output against expected output vector and
// PASS/FAIL report to the console
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
#include <stdio.h>
#include <math.h>
#include "DSP28x_Project.h"
#include "F2806x_Cla_defines.h"  

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

float z_expected[][N]={{1,4,7},{2,5,8},{3,6,9}};

//
// test_report - 
//
void test_report(void)
{
    unsigned int i,j;
    unsigned int pass_count=0;
    unsigned int fail_count=0;
    float fError[M][N];
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            fError[i][j] = fabs(z_expected[i][j]-z[i][j]);
            if( fError[i][j] == 0)
            {
                pass_count++;
            }
            else
            {
                fail_count++;
            }
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

//
// End of File
//

