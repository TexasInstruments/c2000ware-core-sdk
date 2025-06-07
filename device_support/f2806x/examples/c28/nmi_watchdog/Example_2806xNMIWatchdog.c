//###########################################################################
//
// FILE:	Example_2806xNMIWatchdog.c
//
// TITLE:	NMI Watchdog Example
//
//! \addtogroup f2806x_example_list
//! <h1>Handling NMI Watchdog (nmi_watchdog)</h1>
//!
//! This example demonstrates how to capture a clock fail NMI when a missing
//! clock is detected.
//!
//! There are two variations of this example that can be selected by setting
//! the respective "define" below.
//! - \b EXAMPLE1 captures the clock fail in the ISR and then re-enables the
//!      INTOSC before returning to the application (No device reset)
//! - \b EXAMPLE2 captures the clock fail in the ISR and waits for the device
//!      to reset. \b IMPORTANT make sure to configure emulation boot mode to
//!      "boot to RAM". This can be done via GEL script
//!      (In CCS, go to Scripts->EMU Boot Mode Select->EMU_BOOT_SARAM)
//!
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
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Defines - Set respective define for which example variation is desired
//
#define EXAMPLE1    1 // Clock Fail is captured and corrected in ISR (no device reset)
#define EXAMPLE2    0 // Clock Fail is captured and NMIWD times out, reseting the device.
                      // IMPORTANT for EXAMPLE2: Emulation boot must be set to "boot to RAM"

//
// Function Prototypes
//
interrupt void NMI_isr(void);

//
// Main
//
void main(void)
{
#if EXAMPLE2
    //
    // Upon NMIWD reset, trap device here (Missing clock status will be set)
    //
    if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
    {
        ESTOP0;

        //
        // Clear missing clock status (to exit PLL limp mode)
        // and turn INTOSC1 back on
        //
        EALLOW;
        SysCtrlRegs.PLLSTS.bit.MCLKCLR = 1;
        SysCtrlRegs.CLKCTL.bit.INTOSC1OFF = 0;
        EDIS;
    }
#endif

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This sets up PLL using INTOSC1
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the F2806x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Configures clockfail-NMI interrupt
    //
    EALLOW;
    NmiIntruptRegs.NMICFG.bit.CLOCKFAIL = 1;    // Enables CLOCKFAIL condition to generate NMI
    NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL = 1; // Clears CLOCKFAIL flag in the NMIFLG register
    NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;    // Clears NMIINT flag in the NMIFLG register
    NmiIntruptRegs.NMIWDPRD = 0xFFFF;
    EDIS;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2806x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Map NMI ISR to PIE
    //
    EALLOW;
    PieVectTable.NMI = &NMI_isr;
    EDIS;

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Configure GPIO34 as a GPIO output pin (for LED)
    //
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

    //
    // Choose what happens when missing clock condition is detected
    //
    SysCtrlRegs.CLKCTL.bit.NMIRESETSEL = 1; // 0 - MCLKRSn driven straight away
                                            // 1 - NMI-WD reset fires MCLKRSn

    //
    // Turn off the INTOSC1 to simulate failure condition
    //
    SysCtrlRegs.CLKCTL.bit.INTOSC1OFF = 1;

    EDIS;

    //
    // Wait for interrupt
    //
    while(1)
    {
        //
        // Toggle LED
        //
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

        DELAY_US(80000);
    }
}

//
// NMI_isr - Interrupt service routine to capture missing clock condition
//
interrupt void NMI_isr(void)
{
    //
    // Check it verify this NMI is because of a clock fail
    //
    if(NmiIntruptRegs.NMIFLG.bit.CLOCKFAIL !=1)
    {
        ESTOP0; // Halt debugger
    }

#if EXAMPLE2
    //
    // Wait for NMIWD to reset the device
    //
    while(1)
    {
    }
#endif

#if EXAMPLE1
    //
    // Clear NMIFLGs to stop NMIWD counter
    //
    EALLOW;
    NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL = 1;
    NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;

    //
    // Clear missing clock status (to exit PLL limp mode)
    // and turn INTOSC1 back on
    //
    SysCtrlRegs.PLLSTS.bit.MCLKCLR = 1;
    SysCtrlRegs.CLKCTL.bit.INTOSC1OFF = 0;
    EDIS;
#endif
}



//
// End of File
//

