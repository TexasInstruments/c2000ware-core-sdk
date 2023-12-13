//###########################################################################
//
// FILE:	Example_2806xExternalInterrupt.c
//
// TITLE:	External Interrupt Example
//
//! \addtogroup f2806x_example_list
//! <h1>External Interrupt (external_interrupt)</h1>
//!
//! This program sets up GPIO0 as XINT1 and GPIO1 as XINT2.  Two other
//! GPIO signals are used to trigger the interrupt (GPIO32 triggers
//! XINT1 and GPIO33 triggers XINT2). XINT1 input is synched to SYSCLKOUT
//! XINT2 has a long qualification - 6 samples at 510*SYSCLKOUT each.
//! GPIO34 will go high outside of the interrupts and low within the
//! interrupts. This signal can be monitored on a scope. On the f28069
//! controlSTICK, GPIO-34 also toggles a red LED.
//! Each interrupt is fired in sequence - XINT1 first and then XINT2.
//!
//! Monitor GPIO34 with an oscilloscope. GPIO34 will be high outside of
//! the ISRs and low within each ISR.
//!
//! \b External \b Connections \n
//!  - Connect GPIO32 to GPIO0. GPIO0 is assigned to XINT1
//!  - Connect GPIO33 to GPIO1. GPIO1 is assigned to XINT2
//! 
//! \b Watch \b Variables \n
//!  - Xint1Count - XINT1 interrupt count
//!  - Xint2Count - XINT2 interrupt count
//!  - LoopCount  - idle loop count
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
__interrupt void xint1_isr(void);
__interrupt void xint2_isr(void);

//
// Globals
//
volatile Uint32 Xint1Count;
volatile Uint32 Xint2Count;
Uint32 LoopCount;

//
// Define
//
#define DELAY (CPU_RATE/1000*6*510)  //Qual period at 6 samples

//
// Main
//
void main(void)
{
    Uint32 TempX1Count;
    Uint32 TempX2Count;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO:
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
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2806x_PieCtrl.c file.
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
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;	// This is needed to write to EALLOW protected registers
    PieVectTable.XINT1 = &xint1_isr;
    PieVectTable.XINT2 = &xint2_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in F2806x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example

    //
    // Step 5. User specific code, enable interrupts
    //

    //
    // Clear the counters
    //
    Xint1Count = 0;     // Count XINT1 interrupts
    Xint2Count = 0;     // Count XINT2 interrupts
    LoopCount = 0;      // Count times through idle loop

    //
    // Enable XINT1 and XINT2 in the PIE: Group 1 interrupt 4 & 5
    // Enable INT1 which is connected to WAKEINT
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Group 1 INT4
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Group 1 INT5
    IER |= M_INT1;                              // Enable CPU INT1
    EINT;                                       // Enable Global Interrupts

    //
    // GPIO32 & GPIO33 are outputs, start GPIO32 high and GPIO33 low
    //
    EALLOW;
    GpioDataRegs.GPBSET.bit.GPIO32 = 1;         // Load the output latch
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;        // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;         // output

    GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1;       // Load the output latch
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;        // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;         // output
    EDIS;

    //
    // GPIO0 and GPIO1 are inputs
    //
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;        // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;         // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;       // XINT1 Synch to SYSCLKOUT only

    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;        // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;         // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 2;       // XINT2 Qual using 6 samples
    
    //
    // Each sampling window is 510*SYSCLKOUT
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0xFF;
    EDIS;

    //
    // GPIO0 is XINT1, GPIO1 is XINT2
    //
    EALLOW;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0;   // XINT1 is GPIO0
    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 1;   // XINT2 is GPIO1
    EDIS;

    //
    // Configure XINT1 and XINT2
    //
    XIntruptRegs.XINT1CR.bit.POLARITY = 0;      // Falling edge interrupt
    XIntruptRegs.XINT2CR.bit.POLARITY = 1;      // Rising edge interrupt

    //
    // Enable XINT1 and XINT2
    //
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable XINT1
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2

    //
    // GPIO34 will go low inside each interrupt.  Monitor this on a scope
    //
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;        // GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;         // output
    EDIS;

    //
    // Step 6. IDLE loop
    //
    for(;;)
    {
        TempX1Count = Xint1Count;
        TempX2Count = Xint2Count;

        //
        // Trigger both XINT1
        //
        GpioDataRegs.GPBSET.bit.GPIO34 = 1;   // GPIO34 is high
        GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1; // Lower GPIO32, trigger XINT1
        while(Xint1Count == TempX1Count)
        {
            
        }

        //
        // Trigger both XINT2
        //
        GpioDataRegs.GPBSET.bit.GPIO34 = 1;   // GPIO34 is high
        DELAY_US(DELAY);                      // Wait for Qual period
        GpioDataRegs.GPBSET.bit.GPIO33 = 1;   // Raise GPIO33, trigger XINT2
        while(Xint2Count == TempX2Count)
        {
            
        }

        //
        // Check that the counts were incremented properly and get ready
        // to start over.
        //
        if(Xint1Count == TempX1Count+1 && Xint2Count == TempX2Count+1)
        {
            LoopCount++;
            GpioDataRegs.GPBSET.bit.GPIO32 = 1;   // raise GPIO32
            GpioDataRegs.GPBCLEAR.bit.GPIO33 = 1; // lower GPIO33
        }
        else
        {
            __asm("      ESTOP0"); // stop here
        }
    }
}

//
// xint1_isr - Step 7. Insert all local Interrupt Service Routines (ISRs) 
// and functions here: If local ISRs are used, reassign vector addresses in 
// vector table as shown in Step 5
//
__interrupt void
xint1_isr(void)
{
    GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
    Xint1Count++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// xint2_isr - 
//
__interrupt void
xint2_isr(void)
{
    GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
    Xint2Count++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// End of File
//

