//###########################################################################
//
// FILE:   f28p65x_epwm.c
//
// TITLE:  f28p65x EPwm Initialization & Support Functions.
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#include "f28p65x_device.h"
#include "f28p65x_examples.h"

//
// InitEPwmGpio - Initialize all EPWM modules' GPIOs
//
void InitEPwmGpio(void)
{
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();
    InitEPwm4Gpio();
    InitEPwm5Gpio();
    InitEPwm6Gpio();
    InitEPwm7Gpio();
    InitEPwm8Gpio();
    InitEPwm9Gpio();
    InitEPwm10Gpio();
    InitEPwm11Gpio();
    InitEPwm12Gpio();
    InitEPwm13Gpio();
    InitEPwm14Gpio();
    InitEPwm15Gpio();
    InitEPwm16Gpio();
}

//
// InitEPwm1Gpio - Initialize EPWM1 GPIOs
//
void InitEPwm1Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;   // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;   // Disable pull-up on GPIO1 (EPWM1B)
//    GpioCtrlRegs.GPEPUD.bit.GPIO145 = 1; // Disable pull-up on GPIO145 (EPWM1A)
//    GpioCtrlRegs.GPEPUD.bit.GPIO146 = 1; // Disable pull-up on GPIO146 (EPWM1B)

    //
    // Configure EPWM-1 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM1 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
//    GpioCtrlRegs.GPEMUX2.bit.GPIO145 = 1; // Configure GPIO145 as EPWM1A
//    GpioCtrlRegs.GPEMUX2.bit.GPIO146 = 1; // Configure GPIO0146 as EPWM1B

    EDIS;
}

//
// InitEPwm2Gpio - Initialize EPWM2 GPIOs
//
void InitEPwm2Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;   // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;   // Disable pull-up on GPIO3 (EPWM2B)
//    GpioCtrlRegs.GPEPUD.bit.GPIO147 = 1; // Disable pull-up on GPIO147 (EPWM2A)
//    GpioCtrlRegs.GPEPUD.bit.GPIO148 = 1; // Disable pull-up on GPIO148 (EPWM2B)

    //
    // Configure EPwm-2 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM2 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
//    GpioCtrlRegs.GPEMUX2.bit.GPIO147 = 1; // Configure GPIO147 as EPWM2A
//    GpioCtrlRegs.GPEMUX2.bit.GPIO148 = 1; // Configure GPIO148 as EPWM2B

    EDIS;
}

//
// InitEPwm3Gpio - Initialize EPWM3 GPIOs
//
void InitEPwm3Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;   // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;   // Disable pull-up on GPIO5 (EPWM3B)
//    GpioCtrlRegs.GPEPUD.bit.GPIO149 = 1; // Disable pull-up on GPIO149 (EPWM3A)
//    GpioCtrlRegs.GPEPUD.bit.GPIO150 = 1; // Disable pull-up on GPIO150 (EPWM3B)

    //
    // Configure EPwm-3 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM3 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B
//    GpioCtrlRegs.GPEMUX2.bit.GPIO149 = 1; // Configure GPIO149 as EPWM3A
//    GpioCtrlRegs.GPEMUX2.bit.GPIO150 = 1; // Configure GPIO150 as EPWM3B

    EDIS;
}

//
// InitEPwm4Gpio - Initialize EPWM4 GPIOs
//
void InitEPwm4Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;   // Disable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;   // Disable pull-up on GPIO7 (EPWM4B)
//    GpioCtrlRegs.GPEPUD.bit.GPIO151 = 1; // Disable pull-up on GPIO151 (EPWM4A)
//    GpioCtrlRegs.GPEPUD.bit.GPIO152 = 1; // Disable pull-up on GPIO152 (EPWM4B)

     //
     // Configure EPWM-4 pins using GPIO regs. This specifies which of the
     // possible GPIO pins will be EPWM4 functional pins.
     // Comment out other unwanted lines.
     //
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B
//    GpioCtrlRegs.GPEMUX2.bit.GPIO151 = 1; // Configure GPIO151 as EPWM4A
//    GpioCtrlRegs.GPEMUX2.bit.GPIO152 = 1; // Configure GPIO152 as EPWM4B

    EDIS;
}

//
// InitEPwm5Gpio - Initialize EPWM5 GPIOs
//
void InitEPwm5Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;   // Disable pull-up on GPIO8 (EPWM5A)
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;   // Disable pull-up on GPIO9 (EPWM5B)
//    GpioCtrlRegs.GPEPUD.bit.GPIO153 = 1; // Disable pull-up on GPIO153 (EPWM5A)
//    GpioCtrlRegs.GPEPUD.bit.GPIO154 = 1; // Disable pull-up on GPIO154 (EPWM5B)

    //
    // Configure EPWM-5 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM5 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;   // Configure GPIO8 as EPWM5A
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;   // Configure GPIO9 as EPWM5B
//    GpioCtrlRegs.GPEMUX2.bit.GPIO153 = 1; // Configure GPIO153 as EPWM5A
//    GpioCtrlRegs.GPEMUX2.bit.GPIO154 = 1; // Configure GPIO0154 as EPWM5B

    EDIS;
}

//
// InitEPwm6Gpio - Initialize EPWM6 GPIOs
//
void InitEPwm6Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;  // Disable pull-up on GPIO10 (EPWM6A)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;  // Disable pull-up on GPIO11 (EPWM6B)
//    GpioCtrlRegs.GPEPUD.bit.GPIO155 = 1; // Disable pull-up on GPIO155 (EPWM6A)
//    GpioCtrlRegs.GPEPUD.bit.GPIO156 = 1; // Disable pull-up on GPIO156 (EPWM6B)

    //
    // Configure EPWM-6 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM6 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;  // Configure GPIO10 as EPWM6A
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;  // Configure GPIO11 as EPWM6B
//    GpioCtrlRegs.GPEMUX2.bit.GPIO155 = 1; // Configure GPIO155 as EPWM6A
//    GpioCtrlRegs.GPEMUX2.bit.GPIO156 = 1; // Configure GPIO156 as EPWM6B

    EDIS;
}

//
// InitEPwm7Gpio - Initialize EPWM7 GPIOs
//
void InitEPwm7Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;  // Disable pull-up on GPIO12 (EPWM7A)
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1;  // Disable pull-up on GPIO13 (EPWM7B)
//    GpioCtrlRegs.GPEPUD.bit.GPIO157 = 1; // Disable pull-up on GPIO157 (EPWM7A)
//    GpioCtrlRegs.GPEPUD.bit.GPIO158 = 1; // Disable pull-up on GPIO158 (EPWM7B)

    //
    // Configure EPWM-7 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM7 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as EPWM7A
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // Configure GPIO13 as EPWM7B
//    GpioCtrlRegs.GPEMUX2.bit.GPIO157 = 1; // Configure GPIO157 as EPWM7A
//    GpioCtrlRegs.GPEMUX2.bit.GPIO158 = 1; // Configure GPIO158 as EPWM7B

    EDIS;
}

//
// InitEPwm8Gpio - Initialize EPWM8 GPIOs
//
void InitEPwm8Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1;  // Disable pull-up on GPIO14 (EPWM8A)
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1;  // Disable pull-up on GPIO15 (EPWM8B)
//    GpioCtrlRegs.GPEPUD.bit.GPIO159 = 1; // Disable pull-up on GPIO159 (EPWM8A)
//    GpioCtrlRegs.GPFPUD.bit.GPIO160 = 1; // Disable pull-up on GPIO160 (EPWM8B)

    //
    // Configure EPWM-8 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM8 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // Configure GPIO14 as EPWM8A
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // Configure GPIO15 as EPWM8B
//    GpioCtrlRegs.GPEMUX2.bit.GPIO159 = 1; // Configure GPIO159 as EPWM8A
//    GpioCtrlRegs.GPFMUX1.bit.GPIO160 = 1; // Configure GPIO160 as EPWM8B

    EDIS;
}

//
// InitEPwm9Gpio - Initialize EPWM9 GPIOs
//
void InitEPwm9Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPFPUD.bit.GPIO161 = 1; // Disable pull-up on GPIO161 (EPWM9A)
    GpioCtrlRegs.GPFPUD.bit.GPIO162 = 1; // Disable pull-up on GPIO162 (EPWM9B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1;  // Disable pull-up on GPIO16 (EPWM9A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1;  // Disable pull-up on GPIO17 (EPWM9B)

    //
    // Configure EPWM-9 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM9 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPFMUX1.bit.GPIO161 = 1; // Configure GPIO161 as EPWM9A
    GpioCtrlRegs.GPFMUX1.bit.GPIO162 = 1; // Configure GPIO162 as EPWM9B

//    //
//    // Alternate mapping for EPWM-9. Uncomment if required. Write 0 to
//    // GPAMUx register before configuring GPAGMux to avoid glitches.
//    //
//    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;  // Configure GPAMUX to 0 for GPIO16
//    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;  // Configure GPAMUX to 0 for GPIO17
//
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 1; // Configure GPAGMUX for EPWM9A
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO17 = 1; // Configure GPAGMUX for EPWM9B
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;  // Configure GPAMUX for EPWM9A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;  // Configure GPAMUX for EPWM9B

    EDIS;
}

//
// InitEPwm10Gpio - Initialize EPWM10 GPIOs
//
void InitEPwm10Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPFPUD.bit.GPIO163 = 1; // Disable pull-up on GPIO163 (EPWM10A)
    GpioCtrlRegs.GPFPUD.bit.GPIO164 = 1; // Disable pull-up on GPIO164 (EPWM10B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1;  // Disable pull-up on GPIO18 (EPWM10A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1;  // Disable pull-up on GPIO19 (EPWM10B)

    //
    // Configure EPWM-10 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM10 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPFMUX1.bit.GPIO163 = 1; // Configure GPIO163 as EPWM10A
    GpioCtrlRegs.GPFMUX1.bit.GPIO164 = 1; // Configure GPIO164 as EPWM10B

//    //
//    // Alternate mapping for EPWM-10. Uncomment if required. Write 0 to
//    // GPAMUx register before configuring GPAGMux to avoid glitches.
//    //
//    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;  // Configure GPAMUX to 0 for GPIO18
//    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;  // Configure GPAMUX to 0 for GPIO19
//
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 1; // Configure GPAGMUX for EPWM10A
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 1; // Configure GPAGMUX for EPWM10B
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;  // Configure GPAMUX for EPWM10A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;  // Configure GPAMUX for EPWM10B

    EDIS;
}

//
// InitEPwm11Gpio - Initialize EPWM11 GPIOs
//
void InitEPwm11Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPFPUD.bit.GPIO165 = 1; // Disable pull-up on GPIO165 (EPWM11A)
    GpioCtrlRegs.GPFPUD.bit.GPIO166 = 1; // Disable pull-up on GPIO166 (EPWM11B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1;  // Disable pull-up on GPIO20 (EPWM11A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 1;  // Disable pull-up on GPIO21 (EPWM11B)

    //
    // Configure EPWM-11 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM11 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPFMUX1.bit.GPIO165 = 1; // Configure GPIO165 as EPWM11A
    GpioCtrlRegs.GPFMUX1.bit.GPIO166 = 1; // Configure GPIO166 as EPWM11B

//    //
//    // Alternate mapping for EPWM-11. Uncomment if required. Write 0 to
//    // GPAMUx register before configuring GPAGMux to avoid glitches.
//    //
//    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;  // Configure GPAMUX to 0 for GPIO20
//    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;  // Configure GPAMUX to 0 for GPIO21
//
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO20 = 1; // Configure GPAGMUX for EPWM11A
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO21 = 1; // Configure GPAGMUX for EPWM11B
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;  // Configure GPAMUX for EPWM11A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;  // Configure GPAMUX for EPWM11B

    EDIS;
}

//
// InitEPwm12Gpio - Initialize EPWM12 GPIOs
//
void InitEPwm12Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPFPUD.bit.GPIO167 = 1; // Disable pull-up on GPIO167 (EPWM12A)
    GpioCtrlRegs.GPFPUD.bit.GPIO168 = 1; // Disable pull-up on GPIO168 (EPWM12B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 1;  // Disable pull-up on GPIO22 (EPWM12A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 1;  // Disable pull-up on GPIO23 (EPWM12B)

    //
    // Configure EPWM-12 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM12 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPFMUX1.bit.GPIO167 = 1; // Configure GPIO167 as EPWM12A
    GpioCtrlRegs.GPFMUX1.bit.GPIO168 = 1; // Configure GPIO168 as EPWM12B

//    //
//    // Alternate mapping for EPWM-12. Uncomment if required. Write 0 to
//    // GPAMUx register before configuring GPAGMux to avoid glitches.
//    //
//    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;  // Configure GPAMUX to 0 for GPIO22
//    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;  // Configure GPAMUX to 0 for GPIO23
//
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO22 = 1; // Configure GPAGMUX for EPWM12A
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO23 = 1; // Configure GPAGMUX for EPWM12B
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;  // Configure GPAMUX for EPWM12A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;  // Configure GPAMUX for EPWM12B

    EDIS;
}

//
// InitEPwm13Gpio - Initialize EPWM13 GPIOs
//
void InitEPwm13Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPEPUD.bit.GPIO130 = 1; // Disable pull-up on GPIO130 (EPWM13A)
    GpioCtrlRegs.GPEPUD.bit.GPIO131 = 1; // Disable pull-up on GPIO131 (EPWM13B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 1;  // Disable pull-up on GPIO24 (EPWM13A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 1;  // Disable pull-up on GPIO25 (EPWM13B)

    //
    // Configure EPWM-13 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM13 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPEMUX1.bit.GPIO130 = 1; // Configure GPIO130 as EPWM13A
    GpioCtrlRegs.GPEMUX1.bit.GPIO131 = 1; // Configure GPIO131 as EPWM13B

//    //
//    // Alternate mapping for EPWM-13. Uncomment if required. Write 0 to
//    // GPAMUx register before configuring GPAGMux to avoid glitches.
//    //
//    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;  // Configure GPAMUX to 0 for GPIO24
//    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;  // Configure GPAMUX to 0 for GPIO25
//
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO24 = 3; // Configure GPAGMUX for EPWM13A
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO25 = 3; // Configure GPAGMUX for EPWM13B
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;  // Configure GPAMUX for EPWM13A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;  // Configure GPAMUX for EPWM13B

    EDIS;
}

//
// InitEPwm14Gpio - Initialize EPWM14 GPIOs
//
void InitEPwm14Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPEPUD.bit.GPIO132 = 1; // Disable pull-up on GPIO132 (EPWM14A)
    GpioCtrlRegs.GPEPUD.bit.GPIO134 = 1; // Disable pull-up on GPIO134 (EPWM14B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 1;  // Disable pull-up on GPIO26 (EPWM14A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 1;  // Disable pull-up on GPIO27 (EPWM14B)

    //
    // Configure EPWM-14 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM14 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPEMUX1.bit.GPIO132 = 1; // Configure GPIO132 as EPWM14A
    GpioCtrlRegs.GPEMUX1.bit.GPIO134 = 1; // Configure GPIO134 as EPWM14B

//    //
//    // Alternate mapping for EPWM-14. Uncomment if required. Write 0 to
//    // GPAMUx register before configuring GPAGMux to avoid glitches.
//    //
//    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;  // Configure GPAMUX to 0 for GPIO26
//    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;  // Configure GPAMUX to 0 for GPIO27
//
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = 3; // Configure GPAGMUX for EPWM14A
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO27 = 3; // Configure GPAGMUX for EPWM14B
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;  // Configure GPAMUX for EPWM14A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;  // Configure GPAMUX for EPWM14B

    EDIS;
}

//
// InitEPwm15Gpio - Initialize EPWM15 GPIOs
//
void InitEPwm15Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPEPUD.bit.GPIO141 = 1; // Disable pull-up on GPIO141 (EPWM15A)
    GpioCtrlRegs.GPEPUD.bit.GPIO142 = 1; // Disable pull-up on GPIO142 (EPWM15B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 1;  // Disable pull-up on GPIO28 (EPWM15A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 1;  // Disable pull-up on GPIO29 (EPWM15B)

    //
    // Configure EPWM-15 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM15 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPEMUX1.bit.GPIO141 = 1; // Configure GPIO141 as EPWM15A
    GpioCtrlRegs.GPEMUX1.bit.GPIO142 = 1; // Configure GPIO142 as EPWM15B

//    //
//    // Alternate mapping for EPWM-15. Uncomment if required. Write 0 to
//    // GPAMUx register before configuring GPAGMux to avoid glitches.
//    //
//    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 0;  // Configure GPAMUX to 0 for GPIO28
//    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0;  // Configure GPAMUX to 0 for GPIO29
//
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO28 = 3; // Configure GPAGMUX for EPWM15A
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO29 = 3; // Configure GPAGMUX for EPWM15B
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // Configure GPAMUX for EPWM15A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // Configure GPAMUX for EPWM15B

    EDIS;
}

//
// InitEPwm16Gpio - Initialize EPWM16 GPIOs
//
void InitEPwm16Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPCPUD.bit.GPIO91 = 1; // Disable pull-up on GPIO91 (EPWM16A)
    GpioCtrlRegs.GPCPUD.bit.GPIO92 = 1; // Disable pull-up on GPIO92 (EPWM16B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 1;  // Disable pull-up on GPIO28 (EPWM16A)
//    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;  // Disable pull-up on GPIO29 (EPWM16B)

    //
    // Configure EPWM-16 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM16 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPCMUX2.bit.GPIO91 = 1; // Configure GPIO141 as EPWM16A
    GpioCtrlRegs.GPCMUX2.bit.GPIO92 = 1; // Configure GPIO142 as EPWM16B

//    //
//    // Alternate mapping for EPWM-16. Uncomment if required. Write 0 to
//    // GPAMUx register before configuring GPAGMux to avoid glitches in Mux.
//    //
//    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;  // Configure GPAMUX to 0 for GPIO30
//    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;  // Configure GPAMUX to 0 for GPIO31
//
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO30 = 3; // Configure GPAGMUx for EPWM16A
//    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 3; // Configure GPAGMux for EPWM16B
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;  // Configure GPAMUx for EPWM16A
//    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;  // Configure GPAMux for EPWM16B

    EDIS;
}

//
// InitEPwm17Gpio - Initialize EPWM17 GPIOs
//
void InitEPwm17Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPCPUD.bit.GPIO93 = 1; // Disable pull-up on GPIO93 (EPWM17A)
    GpioCtrlRegs.GPCPUD.bit.GPIO94 = 1; // Disable pull-up on GPIO94 (EPWM17B)
    //
    // Configure EPWM-17 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM17 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPCMUX2.bit.GPIO93 = 1; // Configure GPIO93 as EPWM17A
    GpioCtrlRegs.GPCMUX2.bit.GPIO94 = 1; // Configure GPIO94 as EPWM17B

    EDIS;
}

//
// InitEPwm18Gpio - Initialize EPWM18 GPIOs
//
void InitEPwm18Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPCPUD.bit.GPIO95 = 1; // Disable pull-up on GPIO95 (EPWM18A)
    GpioCtrlRegs.GPDPUD.bit.GPIO96 = 1; // Disable pull-up on GPIO96 (EPWM18B)
    //
    // Configure EPWM-18 pins using GPIO regs. This specifies which of the
    // possible GPIO pins will be EPWM18 functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPCMUX2.bit.GPIO95 = 1; // Configure GPIO95 as EPWM18A
    GpioCtrlRegs.GPDMUX1.bit.GPIO96 = 1; // Configure GPIO96 as EPWM18B

    EDIS;
}
//
// End of File
//
