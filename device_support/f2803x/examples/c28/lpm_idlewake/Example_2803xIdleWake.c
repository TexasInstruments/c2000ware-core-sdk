//###########################################################################
//
//  FILE:  Example_2803xIdleWake.c
//
//  TITLE: Low Power Modes: Device Idle Mode and Wakeup example
//
//!  \addtogroup f2803x_example_list
//!  <h1>Low Power Modes: Device Idle Mode and Wakeup(lpm_idlewake)</h1>
//!
//!  This example puts the device into IDLE mode then
//!  wakes up the device from IDLE using XINT1
//!  which triggers on a falling edge from GPIO0.
//!
//!  This pin must be pulled from high to low by an external agent for
//!  wakeup. GPIO0 is configured as an XINT1 pin to trigger an
//!  XINT1 interrupt upon detection of a falling edge.
//!
//!  Initially, pull GPIO0 high externally. To wake device
//!  from idle mode by triggering an XINT1 interrupt,
//!  pull GPIO0 low (falling edge)
//!
//! \b External \b Connections \n
//!  - To observe the device wakeup from IDLE mode, monitor GPIO1 with
//!    an oscilloscope, which goes high in the XINT_1_ISR.
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
// Function Prototypes
//
__interrupt void XINT_1_ISR(void);      // ISR

//
// Main
//
void main()
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2803x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2803x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    EALLOW;
    GpioCtrlRegs.GPAPUD.all = 0;               // Enable all Pull-ups
    GpioCtrlRegs.GPBPUD.all = 0;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0;  // Choose GPIO0 as the XINT1 pin
    GpioCtrlRegs.GPADIR.all = 0xFFFFFFFE;      // All pins are outputs except 0
    GpioDataRegs.GPADAT.all = 0x00000000;      // All I/O pins are driven low
    EDIS;
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;       // Enable XINT1 pin
    
    //
    // Interrupt occurs on falling edge
    //
    XIntruptRegs.XINT1CR.bit.POLARITY = 0;

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2803x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2803x_DefaultIsr.c.
    // This function is found in DSP2803x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.XINT1 = &XINT_1_ISR;
    EDIS;

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not applicable for this example.
    //

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Enable CPU INT1 which is connected to WakeInt:
    //
    IER |= M_INT1;

    //
    // Enable XINT1 in the PIE: Group 1 interrupt 4
    //
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;

    //
    // Enable global Interrupts:
    //
    EINT;                   // Enable Global interrupt INTM

    //
    // Write the LPM code value
    //
    EALLOW;
    
    //
    // Only enter Idle mode when PLL is not in limp mode
    //
    if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 1) 
    {
        SysCtrlRegs.LPMCR0.bit.LPM = 0x0000;  // LPM mode = Idle
    }
    EDIS;
    
    __asm(" IDLE");          // Device waits in IDLE until XINT1 interrupts
    
    for(;;)
    {
        
    }
}

//
// XINT_1_ISR - XINT ISR
//
__interrupt void 
XINT_1_ISR(void)
{
    //
    // GPIO1 is driven high upon exiting IDLE
    //
    GpioDataRegs.GPASET.bit.GPIO1 = 1;
    
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;
    EINT;
}

//
// End of File
//

