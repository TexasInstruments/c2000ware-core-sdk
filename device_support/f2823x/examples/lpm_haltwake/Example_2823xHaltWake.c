//###########################################################################
//
// FILE:	Example_2823xHaltWake.c
//
// TITLE:	Low Power Modes: Halt Mode and Wakeup Example
//
//! \addtogroup f2823x_example_list
//! <h1>Low Power Modes: Halt Mode and Wakeup (lpm_haltwake)</h1>
//!
//!  This example puts the device into HALT mode. If the lowest
//!  possible current consumption in HALT mode is desired, the
//!  JTAG connector must be removed from the device board while
//!  the device is in HALT mode.
//!
//!  The example then wakes up the device from HALT using GPIO0.
//!  GPIO0 wakes the device from HALT mode when a high-to-low
//!  signal is detected on the pin. This pin must be pulsed by
//!  an external agent for wakeup.
//!
//!  The wakeup process begins as soon as GPIO0 is held low for the
//!  time indicated in the device datasheet. After the
//!  device wakes up, GPIO1 can be observed to go high.
//!
//!  GPIO0 is configured as the LPM wakeup pin to trigger a
//!  WAKEINT interrupt upon detection of a low pulse.
//!  Initially, pull GPIO0 high externally. To wake device
//!  from halt mode, pull GPIO0 low for at least the crystal
//!  startup time + 2 OSCLKS, then pull it high again.
//!
//! \b External \b Connections \n
//!  - To observe when device wakes from HALT mode, monitor
//!    GPIO1 with an oscilloscope (set to 1 in WAKEINT ISR)
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
// Function Prototypes
//
__interrupt void WAKE_ISR(void);  	// ISR for WAKEINT

//
// Main
//
void main()
{
    __asm("  EALLOW");

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2823x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2823x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example
    
    //
    //  Enable all pull-ups
    //
    EALLOW;
    GpioCtrlRegs.GPAPUD.all = 0;
    GpioCtrlRegs.GPBPUD.all = 0;
    
    //
    // GPIO1 set in the ISR to indicate device woken up.
    //
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
    
    GpioIntRegs.GPIOLPMSEL.bit.GPIO0 = 1;	// Choose GPIO0 pin for wakeup
    EDIS;

    //
    // Step 3. Clear all interrupts and initialize PIE vector table
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2823x_PieCtrl.c file.
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
    // The shell ISR routines are found in DSP2823x_DefaultIsr.c.
    // This function is found in DSP2823x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.WAKEINT = &WAKE_ISR;
    EDIS;

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not applicable for this example.
    //

    //
    // Step 5. User specific code, enable interrupts
    //

    //
    // Enable CPU INT1 which is connected to WakeInt
    //
    IER |= M_INT1;

    //
    // Enable WAKEINT in the PIE: Group 1 interrupt 8
    //
    PieCtrlRegs.PIEIER1.bit.INTx8 = 1;
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;
    
    //
    // Enable global Interrupts
    //
    EINT;   // Enable Global interrupt INTM

    //
    // Write the LPM code value
    //
    EALLOW;
    
    //
    // Only enter low power mode when PLL is not in limp mode.
    //
    if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 1)
    {
        SysCtrlRegs.LPMCR0.bit.LPM = 0x0002;   // LPM mode = Halt
    }
    EDIS;

    //
    // Force device into HALT
    //
    
    //
    // Device waits in IDLE until falling edge on GPIO0/XNMI pin
    // wakes device from halt mode.
    //
    __asm(" IDLE");
    
    //
    // Loop here after wake-up.
    //
    for(;;)
    {
        
    }
}

//
// ISR for WAKEINT - Will be executed when low pulse triggered on GPIO0 pin
//
__interrupt void 
WAKE_ISR(void)
{
    //
    // Toggle GPIO1 in the ISR - monitored with oscilloscope
    //
    GpioDataRegs.GPATOGGLE.bit.GPIO1 = 1;
    
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;
}

//
// End of File
//

