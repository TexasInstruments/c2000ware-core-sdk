//###########################################################################
//
// FILE:    gpio_ex1_setup.c
//
// TITLE:   Device GPIO Setup
//! <h1> Device GPIO Setup </h1>
//! \addtogroup bitfield_example_list
//!
//! Configures the F28E12X GPIO configurations
//! This code is verbose to illustrate how the GPIO could be setup.
//! In a real application, lines of code can be combined for improved
//! code size and efficiency.
//! This example only sets-up the GPIO.
//! Nothing is actually done with the pins after setup.
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "f28x_project.h"

//
// Function Prototypes
//
void setup1GPIO(void);

//
// Main
//

void main(void)
{
    //
    //Step 1. Initialize System Control:
    //PLL, WatchDog,enabe Peripheral Clocks
    //This example function is found in the f28p55x_sysctrl.c file.
    //
    InitSysCtrl();

    //
    //Step 2. Initialize GPIO
    //
    InitGpio();

    //
    //Step 3. Clear all __interrupts and initialize PIE vector table:
    //Disable CPU __interrupts
    //
    DINT;

    //
    //Initialize the PIE control registers to their default state.
    //The default state is all PIE interrupts disabled and flags
    //are cleared.
    //
    InitPieCtrl();

    //
    //Disable CPU interrupts and clear all CPU interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    //Initialize the PIE vector table with pointers to the shell Interrupt
    //Service Routines (ISR).
    //
    InitPieVectTable();

    //
    //Step 4. User specific code:
    //


    //
    //This example is a basic pinout
    //
    setup1GPIO();

    while(1)
    {
        ESTOP0;
    }
}

//
// setup1GPIO - Is an example that demonstrates the basic pinout
//
void setup1GPIO(void)
{
    //
    // Example 1: Basic Pinout.
    // This basic pinout includes:
    // PWM1-3, ECAP1, ECAP2, TZ1-TZ4, SPI-A, EQEP1, SCI-A, CAN-A, I2C
    // and a number of I/O pins
    // These can be combined into single statements for improved
    // code efficiency.
    //

    //
    // Enable PWM1-3 on GPIO0-GPIO5
    //
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pullup on GPIO0
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // Enable pullup on GPIO1
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // Enable pullup on GPIO2
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // Enable pullup on GPIO3
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // Enable pullup on GPIO4
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // Enable pullup on GPIO5
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // GPIO0 = PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;  // GPIO1 = PWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;  // GPIO2 = PWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;  // GPIO3 = PWM2B
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;  // GPIO4 = PWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;  // GPIO5 = PWM3B

    //
    // Enable EQEP1 on GPIO's 6,7,12,13
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;   // Enable pullup on GPIO7
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pullup on GPIO12
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pullup on GPIO13
    GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;  // GPIO6 = EQEP1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;  // GPIO7 = EQEP1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // GPIO12 = EQEP1S
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 2;  // GPIO13 = EQEP1I

    //
    // Enable eCAP1 on GPIO7
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pullup on GPIO7
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;  // Synch to SYSCLKOUT
    InputXbarRegs.INPUT7SELECT.bit.SELECT = 7;       // INPUT7 = GPIO7
    ECap1Regs.ECCTL0.bit.INPUTSEL = 7;    // Select eCAP1 TO INPUTXBAR8

    //
    // Enable Trip Zone inputs on GPIO12 - GPIO13
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pullup on GPIO12
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pullup on GPIO13
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // asynch input
    InputXbarRegs.INPUT1SELECT.bit.SELECT = 12;      // GPIO12 = TZ1
    InputXbarRegs.INPUT2SELECT.bit.SELECT = 13;      // GPIO13 = TZ2

    //
    // Enable SPI-A
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pullup on GPIO16
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pullup on GPIO13
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pullup on GPIO12
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pullup on GPIO29
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3; // asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;  // GPIO16 = SPIPICOA
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // GPIO13 = SPIPOCIA
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // GPIO12 = SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29 = SPIPTEA

    //
    // Set input qualification period for GPIO28
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=1;  // Qual period = SYSCLKOUT/2
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28=2;   // 6 samples

    //
    // Make GPIO29 wakeup from STANDBY Low Power Modes
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0; // GPIO29 = GPIO29
    GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;  // GPIO29 = input
    CpuSysRegs.GPIOLPMSEL0.bit.GPIO29=1; // GPIO29 will wake the device
    CpuSysRegs.LPMCR.bit.QUALSTDBY = 2;  // Qualify GPIO29 by 2 OSCCLK
                                         // cycles before waking the device
                                         // from STANDBY

    //
    // Enable SCI-A on GPIO35 - GPIO37
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;   // Enable pullup on GPIO35
    GpioCtrlRegs.GPBQSEL1.bit.GPIO35 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;  // GPIO35 = SCIRXDA
    GpioCtrlRegs.GPBPUD.bit.GPIO37 = 0;   // Enable pullup on GPIO37
    GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 1;  // GPIO37 = SCITXDA


    //
    // Enable I2C-A on GPIO32 - GPIO33
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pullup on GPIO19
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;  // GPIO19 = SDAA
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pullup on GPIO18
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;  // GPIO18 = SCLA

    EDIS;
}

//
// End of File
//
