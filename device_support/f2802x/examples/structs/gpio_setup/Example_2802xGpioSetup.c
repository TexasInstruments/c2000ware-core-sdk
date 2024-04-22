//###########################################################################
//
// FILE:    Example_2802xGpioSetup.c
//
// TITLE:   f2802x Device GPIO Setup
//
// ASSUMPTIONS:
//
//    This program requires the f2802x header files.
//
//    Two different examples are included. Select the example
//    to execute before compiling using the #define statements
//    found at the top of the code.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2802x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp,
//
//    $Boot_Table
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:   EMU_KEY        EMU_BMODE
//                   (0xD00)	     (0xD01)
//      ---------------------------------------
//      Wait		 !=0x55AA        X
//      I/O		     0x55AA	         0x0000
//      SCI		     0x55AA	         0x0001
//      Wait 	     0x55AA	         0x0002
//      Get_Mode	 0x55AA	         0x0003
//      SPI		     0x55AA	         0x0004
//      I2C		     0x55AA	         0x0005
//      OTP		     0x55AA	         0x0006
//      Wait		 0x55AA	         0x0007
//      Wait		 0x55AA	         0x0008
//      SARAM		 0x55AA	         0x000A	  <-- "Boot to SARAM"
//      Flash		 0x55AA	         0x000B
//	    Wait		 0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
//
// DESCRIPTION:
//
//
//    Configures the 2802x GPIO into two different configurations
//    This code is verbose to illustrate how the GPIO could be setup.
//    In a real application, lines of code can be combined for improved
//    code size and efficiency.
//
//    This example only sets-up the GPIO.. nothing is actually done with
//    the pins after setup.
//
//    In general:
//
//     All pullup resistors are enabled.  For EPwms this may not be desired.
//     Input qual for communication ports (eCAN, SPI, SCI, I2C) is asynchronous
//     Input qual for Trip pins (TZ) is asynchronous
//     Input qual for eCAP is synch to SYSCLKOUT
//     Input qual for some I/O's and interrupts may have a sampling window
//
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Defines that select the example to compile in.  Only one example should be
// set as 1 the rest should be set as 0.
//
#define EXAMPLE1 1  // Basic pinout configuration example
#define EXAMPLE2 0  // Communication pinout example

//
// Function Prototypes
//
void Gpio_setup1(void);
void Gpio_setup2(void);

//
// Main
//
void main(void)
{
    //
    // WARNING: Always ensure you call memcpy before running any functions from
    // RAM InitSysCtrl includes a call to a RAM based function and without a
    // call to memcpy first, the processor will go "into the weeds"
    //
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2802x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the f2802x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio(); Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2802x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in f2802x_DefaultIsr.c.
    // This function is found in f2802x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //

    //
    // Step 5. User specific code:
    //
#if EXAMPLE1
    //
    // This example is a basic pinout
    //
    Gpio_setup1();
#endif

#if EXAMPLE2
    //
    // This example is a communications pinout
    //
    Gpio_setup2();
#endif
}

//
// Gpio_setup1 - Basic Pinout.
//
void
Gpio_setup1(void)
{
    // 
    // This basic pinout includes:
    // PWM1-3, TZ1-TZ4, SPI-A, EQEP1, SCI-A, I2C
    // and a number of I/O pins
    //

    //
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
    // Enable an GPIO output on GPIO6&7, set it high
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO6
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   // GPIO6 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;   // Enable pullup on GPIO7
    GpioDataRegs.GPASET.bit.GPIO7 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;  // GPIO7 = GPIO7
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;   // GPIO7 = output

    //
    // Enable Trip Zone input on GPIO12
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pullup on GPIO12
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // asynch input
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // GPIO12 = TZ1

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
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;  // GPIO16 = SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;  // GPIO17 = SPIS0MIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;  // GPIO18 = SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;  // GPIO19 = SPISTEA

    //
    // Enable SCI-A on GPIO28 - GPIO29
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pullup on GPIO28
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // GPIO28 = SCIRXDA
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pullup on GPIO29
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29 = SCITXDA

    //
    // Make GPIO34 an input
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;  // Enable pullup on GPIO34
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO34 = GPIO34
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;  // GPIO34 = input
    EDIS;
}

//
// Gpio_setup2 - Communications Pinout.
//
void
Gpio_setup2(void)
{
    // 
    // This basic communications pinout includes:
    // PWM1-3, SPI-A, SCI-A and a number of I/O pins
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
    // Enable an GPIO output on GPIO6&7
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO6
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   // GPIO6 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;   // Enable pullup on GPIO7
    GpioDataRegs.GPASET.bit.GPIO7 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;  // GPIO7 = GPIO7
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;   // GPIO7 = output

    //
    // Enable SPI-A on GPIO16 - GPIO19
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pullup on GPIO16 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pullup on GPIO17 (SPIS0MIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pullup on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pullup on GPIO19 (SPISTEA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // asynch input
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;  // GPIO16 = SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;  // GPIO17 = SPIS0MIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;  // GPIO18 = SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;  // GPIO19 = SPISTEA

    //
    // Enable SCI-A on GPIO28 - GPIO29
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pullup on GPIO28
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // GPIO28 = SCIRXDA
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pullup on GPIO29
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29 = SCITXDA

    //
    // Enable CAN-A on GPIO30 - GPIO31
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;   // Enable pullup on GPIO30
    GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;  // GPIO30 = CANTXA
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;   // Enable pullup on GPIO31
    GpioCtrlRegs.GPAQSEL2.bit.GPIO31 = 3; // asynch input
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;  // GPIO31 = CANRXA


    /* Applicable only on those packages with GPIO32 and GPIO33 pinned out
    //
    // Enable I2C-A on GPIO32 - GPIO33
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pullup on GPIO32
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pullup on GPIO33
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3; // asynch input
    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3; // asynch input
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;  // GPIO32 = SDAA
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;  // GPIO33 = SCLA
    */

    //
    // Make GPIO34 an input
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;   // Enable pullup on GPIO34
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;  // GPIO34 = GPIO34
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;   // GPIO34 = input

    EDIS;
}

//
// End of File
//

