//###########################################################################
//
// FILE:  logic_report.c
//
// TITLE: Logic Test Report
//
// Description: Compare observed output against expected output and print a
// PASS/FAIL report to the console
//
//###########################################################################
// $TI Release:  $
// $Release Date: $
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
#include "DSP2803x_Cla_defines.h"

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

//
// test_report
//
void 
test_report(void)
{
    long a,b,mask,r;
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    
    //
    // implement same set of operations as the CLA
    // as a point of comparision
    //

    //
    // 1. Compute sign of an integer
    //
    a = -12;
    (-(a<0) == -1)?pass_count++:fail_count++;

    //
    // 2.Detect if two integers have opposite signs
    //
    a = -12; b =12;
    ((a^b) < 0)?pass_count++:fail_count++;

    //
    // 3.compute absolute value of 'a'
    //
    a = -13; b = 4;
    mask = a >> 31;
    r = (a + mask)^mask;
    (r == 13)? pass_count++ : fail_count++;
    mask = b >> 31;
    r = (b + mask)^mask;
    (r == 4)? pass_count++ : fail_count++;

    //
    // 4.Compute min of two integers 
    //
    a = 5; b = 2;
    r = b^((a ^ b) & -( a < b ));
    (r == 2)? pass_count++ : fail_count++;
    r = b^((a^b) & -(a>b));
    (r == 5)? pass_count++ : fail_count++;

    //
    // 5. determine if a number is a power of 2
    //
    a = 64; b = 37;
    r = ((a & (a -1)) == 0);            // do a boolean operation
    (r == 1)? pass_count++ : fail_count++;
    r = ((b & (b -1)) == 0);            // do a boolean operation
    (r == 0)? pass_count++ : fail_count++;

    if(cla_fail_count)
    {
        printf("FAIL , Pass Count = %lu Fail Count = %lu\n",
                cla_pass_count,cla_fail_count);
    }
    else
    {
        puts("PASS\n");
    }
}

//
// End of File
//

