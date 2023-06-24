//#############################################################################
//
// FILE:   boot_ex1_errorstatuspin.c
//
// TITLE:  Boot Error Status Pin Example with DCSM OTP
//
//! \addtogroup driver_example_list
//! <h1> Boot Error Status Pin Example with DCSM OTP</h1>
//!
//! This example demonstrates how to configure the boot modes, boot mode select
//! pins, and error status pin.
//!
//! NOTE: DCSM OTP (one time programmable) memory is used to configure the boot
//! modes, boot mode select pins, and error status pin. Once the DCSM OTP
//! sections are programmed, they cannot be erased and programmed again.
//!
//! This example is designed to show how to configure boot control as well as
//! the function of the error status pin. Once the error status pin is enabled,
//! an NMI will be triggered by software and the error status pin will go high.
//! Then the NMI ISR will clear error status and drive the error status pin
//! low and return to the main loop where the NMI will be triggered again. More
//! details are available in the "ROM Code and Peripheral Booting" chapter of
//! the Technical Reference Manual.
//!
//! \b External \b Connections \n
//!  - Scope the error status pin used according to what is programmed into
//!    GPREG2. The error status pin may be either GPIO 24, GPIO 28, or GPIO 29.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern uint16_t RamfuncsLoadStart;
extern uint16_t RamfuncsLoadSize;
extern uint16_t RamfuncsRunStart;
#endif

//
// Globals
//
volatile uint32_t counter = 0;

//
// Function Prototypes
//
__interrupt void nmiISR(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Disable global interrupts.
    //
    DINT;

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Map the ISR to the NMI interrupt.
    //
    Interrupt_register(INT_NMI, nmiISR);

    //
    // Clear all NMI flags and enable the nmi interrupt.
    //
    SysCtl_clearAllNMIFlags();
    Interrupt_enable(INT_NMI);
    

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop Forever
    //
    for(;;)
    {
        //
        // Force the NMI by software which causes the error status
        // pin low.
        //
        SysCtl_forceNMIFlags(SYSCTL_NMI_SWERR);

        //
        // Delay for a 500000 microseconds.
        //
        DEVICE_DELAY_US(500000);
    }
}

//
// nmiISR - Non-Maskable Interrupt which should have been triggered by software
//          in the main loop.
//
__interrupt void
nmiISR(void)
{
    //
    // Increment the counter each time the ISR is entered.
    //
    counter++;

    //
    // Delay for a 500 microseconds.
    //
    DEVICE_DELAY_US(500);

    //
    // Clear the NMI flag and NMIINT to cause the error status
    // pin to go high.
    //
    SysCtl_clearNMIStatus(SYSCTL_NMI_SWERR);
}

//
// End of File
//
