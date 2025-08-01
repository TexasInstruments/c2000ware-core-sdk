//###########################################################################
//
// FILE:   f28e12x_mcpwm.c
//
// TITLE:  f28e12x MCPwm Initialization & Support Functions.
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "f28e12x_device.h"
#include "f28e12x_examples.h"

//
// InitMcpwmGpio - Initializes the MCPWM GPIO pins
//
void InitMcpwmGpio(void)
{
    //
    // Configure the GPIO pins
    //
    InitMcpwm1Gpio();
    InitMcpwm3Gpio();
}


// 
// InitMcwpm1Gpio - Initializes the MCPWM1 GPIO pins
//
void InitMcpwm1Gpio(void)
{
    EALLOW;

    //
    // MCPWM1_1A
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;          // Disable Pull-up on GPIO0 (MCPWM1-1A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;         // Configure GPIO0 as MCPWM1-1A

    // GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;          // Disable Pull-up on GPIO4 (MCPWM1-1A)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0xF;       // Configure GPIO4 as MCPWM1-1A

    // GpioCtrlRegs.GPAPUD.bit.GPIO30 = 1;         // Disable Pull-up on GPIO30 (MCPWM1-1A)
    // GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0xB;      // Configure GPIO30 as MCPWM1-1A

    // GpioCtrlRegs.GPHPUD.bit.GPIO224 = 1;        // Disable Pull-up on GPIO224 (MCPWM1-1A)
    // GpioCtrlRegs.GPHMUX1.bit.GPIO224 = 0x9;     // Configure GPIO224 as MCPWM1-1A

    //
    // MCPWM1_1B
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;          // Disable Pull-up on GPIO1 (MCPWM1-1B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;         // Configure GPIO1 as MCPWM1-1B

    // GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;          // Disable Pull-up on GPIO5 (MCPWM1-1B)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0xF;       // Configure GPIO5 as MCPWM1-1B

    // GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;          // Disable Pull-up on GPIO9 (MCPWM1-1B)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0x9;       // Configure GPIO9 as MCPWM1-1B

    // GpioCtrlRegs.GPHPUD.bit.GPIO226 = 1;        // Disable Pull-up on GPIO226 (MCPWM1-1B)
    // GpioCtrlRegs.GPHMUX1.bit.GPIO226 = 0x9;     // Configure GPIO226 as MCPWM1-1B

    //
    // MCPWM1_2A
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO2   = 1;        // Disable Pull-up on GPIO2 (MCPWM1-2A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2   = 1;       // Configure GPIO2 as MCPWM1-2A

    // GpioCtrlRegs.GPAPUD.bit.GPIO6   = 1;        // Disable Pull-up on GPIO6 (MCPWM1-2A)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO6   = 0xf;     // Configure GPIO6 as MCPWM1-2A

    // GpioCtrlRegs.GPAPUD.bit.GPIO7   = 1;        // Disable Pull-up on GPIO7 (MCPWM1-2A)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO7   = 0x2;     // Configure GPIO7 as MCPWM1-2A

    // GpioCtrlRegs.GPAPUD.bit.GPIO29  = 1;        // Disable Pull-up on GPIO29 (MCPWM1-2A)
    // GpioCtrlRegs.GPAMUX2.bit.GPIO29  = 0x2;     // Configure GPIO29 as MCPWM1-2A

    // GpioCtrlRegs.GPBPUD.bit.GPIO41  = 1;        // Disable Pull-up on GPIO41 (MCPWM1-2A)
    // GpioCtrlRegs.GPBMUX1.bit.GPIO41  = 0x5;     // Configure GPIO41 as MCPWM1-2A

    // GpioCtrlRegs.GPHPUD.bit.GPIO230  = 1;       // Disable Pull-up on GPIO230 (MCPWM1-2A)
    // GpioCtrlRegs.GPHMUX1.bit.GPIO230  = 0x6;    // Configure GPIO230 as MCPWM1-2A

    // GpioCtrlRegs.GPHPUD.bit.GPIO242  = 1;       // Disable Pull-up on GPIO242 (MCPWM1-2A)
    // GpioCtrlRegs.GPHMUX2.bit.GPIO242  = 0x3;    // Configure GPIO242 as MCPWM1-2A


    //
    // MCPWM1_2B
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO3  = 1;         // Disable Pull-up on GPIO3 (MCPWM1-2B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1;        // Configure GPIO3 as MCPWM1-2B

    // GpioCtrlRegs.GPAPUD.bit.GPIO7  = 1;         // Disable Pull-up on GPIO7 (MCPWM1-2B)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO7  = 0xF;      // Configure GPIO7 as MCPWM1-2B

    // GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;         // Disable Pull-up on GPIO10 (MCPWM1-2B)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0x2;      // Configure GPIO10 as MCPWM1-2B

    // GpioCtrlRegs.GPBPUD.bit.GPIO40 = 1;         // Disable Pull-up on GPIO40 (MCPWM1-2B)
    // GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0x5;      // Configure GPIO40 as MCPWM1-2B

    // GpioCtrlRegs.GPHPUD.bit.GPIO227 = 1;         // Disable Pull-up on GPIO227 (MCPWM1-2B)
    // GpioCtrlRegs.GPHMUX1.bit.GPIO227 = 0x6;      // Configure GPIO227 as MCPWM1-2B

    // GpioCtrlRegs.GPHPUD.bit.GPIO228 = 1;         // Disable Pull-up on GPIO228 (MCPWM1-2B)
    // GpioCtrlRegs.GPHMUX1.bit.GPIO228 = 0x9;      // Configure GPIO228 as MCPWM1-2B

    //
    // MCPWM1_3A
    //
    // GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;          // Disable Pull-up on GPIO0 (MCPWM1-3A)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0xF;       // Configure GPIO0 as MCPWM1-3A

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;          // Disable Pull-up on GPIO4 (MCPWM1-3A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0x1;       // Configure GPIO4 as MCPWM1-3A

    // GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;          // Disable Pull-up on GPIO6 (MCPWM1-3A)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0xA;       // Configure GPIO6 as MCPWM1-3A

    // GpioCtrlRegs.GPHPUD.bit.GPIO227 = 1;        // Disable Pull-up on GPIO227 (MCPWM1-3A)
    // GpioCtrlRegs.GPHMUX1.bit.GPIO227 = 0x3;     // Configure GPIO227 as MCPWM1-3A


    //
    // MCPWM1_3B
    //
    // GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;          // Disable Pull-up on GPIO0 (MCPWM1-3B)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0xF;       // Configure GPIO0 as MCPWM1-3B

    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;          // Disable Pull-up on GPIO5 (MCPWM1-3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0x1;       // Configure GPIO5 as MCPWM1-3B

    // GpioCtrlRegs.GPHPUD.bit.GPIO230 = 1;        // Disable Pull-up on GPIO230 (MCPWM1-3B)
    // GpioCtrlRegs.GPHMUX1.bit.GPIO230 = 0x3;     // Configure GPIO230 as MCPWM1-3B


    EDIS;
}

//
// InitMcpwm3Gpio - Initialize MCPWM3 GPIOs
//
void InitMcpwm3Gpio(void)
{

    EALLOW;
    
    //
    // MCPWM3_1A
    //
    // GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;          // Disable Pull-up on GPIO7 (MCPWM3-1A)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0x1;         // Configure GPIO7 as MCPWM3-1A
    // GpioCtrlRegs.GPAGMUX1.bit.GPIO7 = 0x2;         // Configure GPIO7 as MCPWM3-1A

    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;          // Disable Pull-up on GPIO12 (MCPWM3-1A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0x1;       // Configure GPIO12 as MCPWM3-1A

    // GpioCtrlRegs.GPAPUD.bit.GPIO28 = 1;         // Disable Pull-up on GPIO28 (MCPWM3-1A)
    // GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0x3;      // Configure GPIO28 as MCPWM3-1A

    // GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;        // Disable Pull-up on GPIO41 (MCPWM3-1A)
    // GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0x1;     // Configure GPIO41 as MCPWM3-1A


    //
    // MCPWM3_1B
    //
    // GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;          // Disable Pull-up on GPIO11 (MCPWM3-1B)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0x9;         // Configure GPIO11 as MCPWM3-1B

    // GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1;          // Disable Pull-up on GPIO13 (MCPWM3-1B)
    // GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0x1;       // Configure GPIO13 as MCPWM3-1B

    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 1;          // Disable Pull-up on GPIO29 (MCPWM3-1B)
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0x3;       // Configure GPIO29 as MCPWM3-1B

    EDIS;

}

//
// End of File
//
