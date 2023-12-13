//#############################################################################
//
// FILE:   FPUfastRTS_Example.c
//
// TITLE:  FPUfastRTS FPU32 Example
//
// FPUfastRTS SysCfg Example
//
// This example is a FPUfastRTS example project setup for SysConfig.
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
    C2000Ware_libraries_init();

    //
    // Parameter initialization
    //
    float32_t param0 = 0.5;
    float32_t param1 = 2.0;

    //
    // Arc Cosine
    //
    float32_t acosResult = acosf(param0);

    //
    // Arc Sine
    //
    param0 = 0.5;
    float32_t asinResult = asinf(param0);

    //
    // Arc Tangent
    //
    param0 = 0.5;
    float32_t atanResult = atanf(param0);

    //
    // Arc Tangent 2 (4-quadrant inverse tangent)
    //
    param0 = 1.0;
    float32_t atan2Result = atan2f(param0, param1);

    //
    // Cosine
    //
    param0 = 0.5;
    float32_t cosResult = cosf(param0);

    //
    // Division (uses '/' operator)
    //
    param0 = 1.0;
    float32_t divResult = param0/param1;

    //
    // Exponential
    //
    param0 = 1.0;
    float32_t expResult = expf(param0);

    //
    // Inverse Square Root
    //
    param0 = 2.0;
    float32_t isqrtResult = isqrtf(param0);

    //
    // Logarithm
    //
    param0 = 1233.2323;
    float32_t logResult = logf(param0);

    //
    // Power
    //
    param0 = 0.5;
    float32_t powResult = powf(param0, param1);

    //
    // Sine
    //
    param0 = 0.5;
    float32_t sinResult = sinf(param0);

    //
    // Square Root
    //
    param0 = 9.0;
    float32_t sqrtResult = sqrtf(param0);

    while(1);
}
