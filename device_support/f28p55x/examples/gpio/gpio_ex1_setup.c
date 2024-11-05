//###########################################################################
//
// FILE:    gpio_ex1_setup.c
//
// TITLE:   Device GPIO Setup
//! <h1> Device GPIO Setup </h1>
//! \addtogroup bitfield_example_list
//!
//! Configures the F28P55X GPIO into two different configurations
//! This code is verbose to illustrate how the GPIO could be setup.
//! In a real application, lines of code can be combined for improved
//! code size and efficiency.
//! This example only sets-up the GPIO.
//! Nothing is actually done with the pins after setup.
//
//#############################################################################
//
//
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
// Defines
// Select the example to compile in.  Only one example should be set as 1
// the rest should be set as 0.
//
#define EXAMPLE1 1  // Basic pinout configuration example
#define EXAMPLE2 0  // Communication pinout example

//
// Function Prototypes
//
void setup1GPIO(void);
void setup2GPIO(void);

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
#if EXAMPLE1

    //
    //This example is a basic pinout
    //
    setup1GPIO();

#endif

#if EXAMPLE2

    //
    // This example is a communications pinout
    //
    setup2GPIO();

#endif

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
    // Enable an GPIO output on GPIO6, set it high
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO6
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   // GPIO6 = output

    //
    // Enable eCAP1 on GPIO7
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pullup on GPIO7
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;  // Synch to SYSCLKOUT
    InputXbarRegs.INPUT7SELECT = 7;       // INPUT7 = GPIO7
    ECap1Regs.ECCTL0.bit.INPUTSEL = 7;    // Select eCAP1 TO INPUT7

    //
    // Enable GPIO outputs on GPIO8 - GPIO11, set it high
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // Enable pullup on GPIO8
    GpioDataRegs.GPASET.bit.GPIO8 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;  // GPIO8 = GPIO8
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;   // GPIO8 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pullup on GPIO9
    GpioDataRegs.GPASET.bit.GPIO9 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;  // GPIO9 = GPIO9
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;   // GPIO9 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;  // Enable pullup on GPIO10
    GpioDataRegs.GPASET.bit.GPIO10 = 1;  // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0; // GPIO10 = GPIO10
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;   // GPIO10 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;  // Enable pullup on GPIO11
    GpioDataRegs.GPASET.bit.GPIO11 = 1;  // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; // GPIO11 = GPIO11
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;  // GPIO11 = output

    //
    // Enable Trip Zone inputs on GPIO12 - GPIO14
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pullup on GPIO12
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pullup on GPIO13
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;   // Enable pullup on GPIO14
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // asynch input
    InputXbarRegs.INPUT1SELECT = 12;      // GPIO12 = TZ1
    InputXbarRegs.INPUT2SELECT = 13;      // GPIO13 = TZ2
    InputXbarRegs.INPUT3SELECT = 14;      // GPIO14 = TZ3

    //
    // Enable SPI-A on GPIO16 - GPIO19
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pullup on GPIO16
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pullup on GPIO17
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pullup on GPIO18
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pullup on GPIO19
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;  // GPIO16 = SPIPICOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;  // GPIO17 = SPIPOCIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;  // GPIO18 = SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;  // GPIO19 = SPIPTEA

    //
    // Enable EQEP1 on GPIO's 20,21,22,23
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pullup on GPIO20
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pullup on GPIO21
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;   // Enable pullup on GPIO22
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pullup on GPIO23
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0; // Synch to SYSCLKOUT
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;  // GPIO20 = EQEP1A
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;  // GPIO21 = EQEP1B
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;  // GPIO22 = EQEP1S
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 2;  // GPIO23 = EQEP1I

    //
    // Enable eCAP1 on GPIO24
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pullup on GPIO24
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0; // Synch to SYSCLKOUT
    InputXbarRegs.INPUT8SELECT = 24;      // INPUT8 = GPIO24
    ECap1Regs.ECCTL0.bit.INPUTSEL=8;      // Select eCAP1 TO INPUT8

    //
    // Set input qualification period for GPIO25 & GPIO26
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=1;  // Qual period = SYSCLKOUT/2
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25=2;   // 6 samples
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26=2;   // 6 samples

    //
    // Make GPIO25 the input source for XINT1
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;  // GPIO25 = GPIO25
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;   // GPIO25 = input
    GPIO_SetupXINT1Gpio(25);              // XINT1 connected to GPIO25

    //
    // Make GPIO26 the input source for XINT2
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;  // GPIO26 = GPIO26
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;   // GPIO26 = input
    GPIO_SetupXINT2Gpio(26);              // XINT2 connected to GPIO26

    //
    // Make GPIO27 wakeup from STANDBY Low Power Modes
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0; // GPIO27 = GPIO27
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;  // GPIO27 = input
    CpuSysRegs.GPIOLPMSEL0.bit.GPIO27=1; // GPIO27 will wake the device
    CpuSysRegs.LPMCR.bit.QUALSTDBY = 2;  // Qualify GPIO27 by 2 OSCCLK
                                         // cycles before waking the device
                                         // from STANDBY

    //
    // Enable SCI-A on GPIO28 - GPIO29
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pullup on GPIO28
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // GPIO28 = SCIRXDA
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pullup on GPIO29
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29 = SCITXDA

    //
    // Enable CAN-A on GPIO30 - GPIO31
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;   // Enable pullup on GPIO30
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;  // GPIO30 = CANRXA
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;   // Enable pullup on GPIO31
    GpioCtrlRegs.GPAQSEL2.bit.GPIO31 = 3; // Asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;  // GPIO31 = CANTXA

    //
    // Enable I2C-A on GPIO32 - GPIO33
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pullup on GPIO32
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;  // GPIO32 = SDAA
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3; // Asynch input
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pullup on GPIO33
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;  // GPIO33 = SCLA

    //
    // Make GPIO34 an input
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;  // Enable pullup on GPIO34
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO34 = GPIO34
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;  // GPIO34 = input

    EDIS;
}

//
// setup2GPIO - Is an example that demonstrates the communications pinout
//
void setup2GPIO(void)
{
    //
    // Example 2:
    // Communications Pinout.
    // This basic communications pinout includes:
    // PWM1-3, CAP2, SPI-B, CAN-A, SCI-A and I2C
    // and a number of I/O pins
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
    // Enable an GPIO output on GPIO6
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO6
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   // GPIO6 = output

    //
    // Enable eCAP1 on GPIO7
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pullup on GPIO7
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;  // Synch to SYSCLKOUT
    InputXbarRegs.INPUT7SELECT = 7;       // INPUT7 = GPIO7
    ECap1Regs.ECCTL0.bit.INPUTSEL=7;      // Select eCAP1 TO INPUT7

    //
    // Enable GPIO outputs on GPIO8 - GPIO11, set it high
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // Enable pullup on GPIO8
    GpioDataRegs.GPASET.bit.GPIO8 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;  // GPIO8 = GPIO8
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;   // GPIO8 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pullup on GPIO9
    GpioDataRegs.GPASET.bit.GPIO9 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;  // GPIO9 = GPIO9
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;   // GPIO9 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;  // Enable pullup on GPIO10
    GpioDataRegs.GPASET.bit.GPIO10 = 1;  // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0; // GPIO10 = GPIO10
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;   // GPIO10 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;  // Enable pullup on GPIO11
    GpioDataRegs.GPASET.bit.GPIO11 = 1;  // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; // GPIO11 = GPIO11
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;  // GPIO11 = output

    //
    // Enable SPI-B on GPIO22 - GPIO25
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;  // Enable pull-up on GPIO22 (SPICLKB)
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;  // Enable pull-up on GPIO23 (SPIPTEB)
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;  // Enable pull-up on GPIO24 (SPIPICOB)
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;  // Enable pull-up on GPIO25 (SPIPOCIB)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3; // asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;  // GPIO22 = SPICLKB
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;  // GPIO23 = SPIPTEB
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;  // GPIO24 = SPIPICOB
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;  // GPIO25 = SPIPOCIB

    //
    // Enable SPI-A on GPIO16 - GPIO19
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;  // Enable pull-up on GPIO16 (SPIPICOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;  // Enable pull-up on GPIO17 (SPIPOCIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;  // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;  // Enable pull-up on GPIO19 (SPIPTEA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;  // GPIO16 = SPIPICOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;  // GPIO17 = SPIPOCIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;  // GPIO18 = SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;  // GPIO19 = SPIPTEA

    //
    // Enable eCAP2 on GPIO24
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pullup on GPIO24
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0; // Synch to SYSCLKOUT
    InputXbarRegs.INPUT8SELECT = 24;      // INPUT8 = GPIO24
    ECap2Regs.ECCTL0.bit.INPUTSEL=8;      // Select eCAP2 TO INPUT8

    //
    // Set input qualifcation period for GPIO25 & GPIO26
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=1;  // Qual period = SYSCLKOUT/2
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25=2;   // 6 samples
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26=2;   // 6 samples

    //
    // Make GPIO25 the input source for XINT1
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;  // GPIO25 = GPIO25
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;   // GPIO25 = input
    GPIO_SetupXINT1Gpio(25);              // XINT1 connected to GPIO25

    //
    // Make GPIO26 the input source for XINT2
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;  // GPIO26 = GPIO26
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;   // GPIO26 = input
    GPIO_SetupXINT2Gpio(26);              // XINT2 connected to GPIO26

    //
    // Make GPIO27 wakeup from HALT/STANDBY Low Power Modes
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0; // GPIO27 = GPIO27
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;  // GPIO27 = input
    CpuSysRegs.GPIOLPMSEL0.bit.GPIO27=1; // GPIO27 will wake the device
    CpuSysRegs.LPMCR.bit.QUALSTDBY = 2;  // Qualify GPIO27 by 2 OSCCLK
                                         // cycles before waking the device
                                         // from STANDBY

    //
    // Enable SCI-A on GPIO28 - GPIO29
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pullup on GPIO28
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // GPIO28 = SCIRXDA
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pullup on GPIO29
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29 = SCITXDA

    //
    // Enable CAN-A on GPIO30 - GPIO31
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;   // Enable pullup on GPIO30
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;  // GPIO30 = CANTXA
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;   // Enable pullup on GPIO31
    GpioCtrlRegs.GPAQSEL2.bit.GPIO31 = 3; // Asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;  // GPIO31 = CANRXA

    //
    // Enable I2C-A on GPIO32 - GPIO33
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pullup on GPIO32
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;  // GPIO32 = SDAA
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3; // Asynch input
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pullup on GPIO33
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;  // GPIO33 = SCLA

    //
    // Make GPIO34 an input
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;  // Enable pullup on GPIO34
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO34 = GPIO34
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;  // GPIO34 = input

    EDIS;
}

//
// End of File
//
