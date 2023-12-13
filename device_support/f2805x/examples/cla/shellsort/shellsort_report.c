//###########################################################################
//
// FILE:  shellsort_report.c
//
// TITLE: Shell Sort Report
//
// DESCRIPTION: Compare observed output against expected output vector and
// print a PASS/FAIL report to the console
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2023 Texas Instruments Incorporated - http://www.ti.com/
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

void test_report(void)
{
    Uint16 fail_flag = 0x0000;
    Uint16 i;
    float vector1_gold[] = {-11.3, 1.0, 2.5, 6.2, 10.8};
    float vector2_gold[] = {9.9, 8.8, 4.4, 3.3, 2.2, 1.0, 0.0, -8.8, -9.9,
                            -10.1};
    int32 vector3_gold[] = {9, 8, 4, 3, 2, 1, 0, -8, -9};

    for(i = 0; i < LENGTH1; i++)
    {
        if(vector1_sorted[i] != vector1_gold[i])
        {
            fail_flag = fail_flag | M_INT1;
        }
    }
    for(i = 0; i < LENGTH2; i++)
    {
        if(vector2_sorted[i] != vector2_gold[i])
        {
            fail_flag = fail_flag | M_INT2;
        }
    }

    //
    // Map the data memory back to the CPU so we can check the
    // results of task 3
    //
    EALLOW;
    Cla1Regs.MMEMCFG.bit.RAM0E    = 0;
    Cla1Regs.MMEMCFG.bit.RAM1E    = 0;
    EDIS;

    asm("   NOP");
    asm("   NOP");
    asm("   NOP");
    asm("   NOP");

    for(i = 0; i < LENGTH3; i++)
    {
        if(vector3[i] != vector3_gold[i])
        {
            fail_flag = fail_flag | M_INT3;
        }
    }
    if(fail_flag == 0)
    {
        puts("PASS\n");
    }
    else
    {
        printf("FAIL  fail_flag = 0x%d\n", fail_flag);
    }
}
