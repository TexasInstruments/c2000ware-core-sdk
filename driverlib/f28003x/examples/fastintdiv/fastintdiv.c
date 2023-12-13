//#############################################################################
//
// FILE:   FASTINTDIV_Example.c
//
// TITLE:  FASTINTDIV Example
//
// FASTINTDIV SysCfg Example
//
// This example is a FASTINTDIV example project setup for SysConfig.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com/
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
//#############################################################################


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

//
// Main
//
void main(void)
{
    //
    // CPU Initialization
    //
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
	Board_init();

    int16_t num0 = 20000;
    int16_t den0 = -501;
    int32_t num1 = 2000000000;
    int32_t den1 = -501;
    int32_t num2 = -2000000000;
    uint32_t den2 = 501;
    int32_t num3 = 2000000000;
    int16_t den3 = -501;

	//
	// Return type is ldiv_t:
	//
	// typedef struct {
	//        int32_t quot;
	//        int32_t rem;
	// } ldiv_t;
	//
    ldiv_t result0 = FID_COMP_I16_BY_I16_T(num0, den0);//(quotient, remainder) = (-39, 461)
    result0 = FID_COMP_I32_BY_I32_T(num1, den1);//(quotient, remainder) = (-3992015, 485)
    result0 = FID_COMP_I32_BY_U32_T(num2, den2);//(quotient, remainder) = (-3992015, -485)
    result0 = FID_COMP_I32_BY_I16_T(num3, den3);//(quotient, remainder) = (-3992015, 485)
    result0 = FID_COMP_I16_BY_I16_M(num0, den0);//(quotient, remainder) = (-40, -40)
    result0 = FID_COMP_I32_BY_I32_M(num1, den1);//(quotient, remainder) = (-3992016, -16)
    result0 = FID_COMP_I32_BY_U32_M(num2, den2);//(quotient, remainder) = (-3992016, 16)
    result0 = FID_COMP_I32_BY_I16_M(num3, den3);//(quotient, remainder) = (-3992016, -16)
    result0 = FID_COMP_I16_BY_I16_E(num0, den0);//(quotient, remainder) = (-39, 461)
    result0 = FID_COMP_I32_BY_I32_E(num1, den1);//(quotient, remainder) = (-3992015, 485)
    result0 = FID_COMP_I32_BY_I16_E(num3, den3);//(quotient, remainder) = (-3992015, 485)

    uint16_t num4 = 30000;
    uint16_t den4 = 503;
    uint32_t num5 = 3000000000;
    uint32_t den5 = 50000003;
    uint32_t num6 = 3000000000;
    uint16_t den6 = 503;

    //
    // Return type is __uldiv_t:
    //
    // typedef struct {
    //     uint32_t quot;
    //     uint32_t rem;
    // }  __uldiv_t;
    //
    __uldiv_t result1 = FID_COMP_U16_BY_U16_T(num4, den4);//(quotient, remainder) = (59, 323)
    result1 = FID_COMP_U32_BY_U32_T(num5, den5);//(quotient, remainder) = (59, 49999823)
    result1 = FID_COMP_U32_BY_U16_T(num6, den6);//(quotient, remainder) = (5964214, 358)

    int64_t num7 = -2000000000000000000;
    int64_t den7 = 500000001;
    int64_t num8 = -2000000000000000000;
    uint64_t den8 = 500000001;
    int64_t num9 = -2000000000000000000;
    uint32_t den9 = 500000001;

    //
    // Return type is lldiv_t:
    //
    // typedef struct {
    //     int64_t quot;
    //     int64_t rem;
    // } lldiv_t;
    //
    lldiv_t result2 = FID_COMP_I64_BY_I64_T(num7, den7);//(quotient, remainder) = (-3999999992, -8)
    result2 = FID_COMP_I64_BY_U64_T(num8, den8);//(quotient, remainder) = (-3999999992, -8)
    result2 = FID_COMP_I64_BY_U32_T(num9, den9);//(quotient, remainder) = (-3999999992, -8)
    result2 = FID_COMP_I64_BY_I64_M(num7, den7);//(quotient, remainder) = (-3999999993, 499999993)
    result2 = FID_COMP_I64_BY_U64_M(num8, den8);//(quotient, remainder) = (-3999999993, 499999993)
    result2 = FID_COMP_I64_BY_I64_E(num7, den7);//(quotient, remainder) = (-3999999993, 499999993)
    result2 = FID_COMP_I64_BY_U64_E(num8, den8);//(quotient, remainder) = (-3999999993, 499999993)

    uint64_t num10 = 18000000000000000000;
    uint64_t den10 = 5000000000001;

    //
    // Return type is __ulldiv_t:
    //
    // typedef struct {
    //     uint64_t quot;
    //     uint64_t rem;
    // } __ulldiv_t;
    //
    __ulldiv_t result3 = FID_COMP_U64_BY_U64_T(num10, den10);//(quotient, remainder) = (3599999, 4999996400001)

    int64_t num11 = -2000000000000000000;
    int32_t den11 = -2000000003;
    int64_t num12 = -2000000000000000000;
    uint32_t den12 = 2000000003;

    //
    // Return type is __llldiv_t:
    //
    // typedef struct {
    //     int64_t quot;
    //     int32_t rem;
    // } __llldiv_t;
    //
    __llldiv_t result4 = FID_COMP_I64_BY_I32_T(num11, den11);//(quotient, remainder) = (999999998, -1000000006)
    result4 = FID_COMP_I64_BY_I32_M(num11, den11);//(quotient, remainder) = (999999998, -1000000006)
    result4 = FID_COMP_I64_BY_U32_M(num12, den12);//(quotient, remainder) = (-999999999, 999999997)
    result4 = FID_COMP_I64_BY_I32_E(num11, den11);//(quotient, remainder) = (999999999, 999999997)
    result4 = FID_COMP_I64_BY_U32_E(num12, den12);//(quotient, remainder) = (-999999999, 999999997)

    uint64_t num13 = 18000000000000000000;
    uint32_t den13 = 3000000001;

    //
    // Return type is __ullldiv_t:
    //
    // typedef struct {
    //     uint64_t quot;
    //     uint32_t rem;
    // } __ullldiv_t;
    //
    __ullldiv_t result5 = FID_COMP_U64_BY_U32_T(num13, den13);//(quotient, remainder) = (5999999998, 2)

    while(1);
}

//
// End of File
//
