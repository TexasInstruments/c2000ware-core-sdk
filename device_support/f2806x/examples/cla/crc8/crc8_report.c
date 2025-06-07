//###########################################################################
//
// TITLE:  crc8_report.c
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

//
// test_report - 
//
void
test_report(void)
{
    Uint16 fail_flag = 0x0000;
    Uint16 const gold1 = 0x0043;   
    Uint16 const gold2 = 0x009f;
    Uint16 const gold3 = 0x00CE;
    Uint16 const gold4 = 0x00c0;

    if(gold1 != crc8_msg1)
    {
        fail_flag = 1;
    }
    if(gold2 != crc8_msg2)
    {
        fail_flag = 2;
    }
    if(gold3 != crc8_msg3)
    {
        fail_flag = 3; 
    }
    if(gold4 != crc8_msg4)
    {
        fail_flag = 4;           
    }

    if(fail_flag == 0)
    {
        puts("PASS\n");
    }
    else
    {
        printf("FAIL  fail_flag = 0x%d\n",fail_flag);
    }
}

//
// End of File
//

