//###########################################################################
//
// FILE:   ipc_gpio_toggle_cpu02.c
//
// TITLE:  IPC GPIO Toggle for F2837xD CPU2.
//
// This example tests the IPC of the F2837xD.
// CPU1 have controls of one input on GPIO15 and one output on GPIO11.
// CPU2 have controls of one input on GPIO14 and one output on GPIO12.
// Toggling the input on CPU1 will also toggle the output on CPU2 through IPC.
// Toggling the input on CPU2 will also toggle the output on CPU1 through IPC.
//
// \b Watch Variables \b
// - GPIO31 - output on CPU2
// - GPIO11 - input on CPU2
// - GPIO34 - output on CPU1
// - GPIO14 - input on CPU1
// - GPIO12 - square wave output on CPU02
// - GPIO15 - square wave output on CPU01
// Connect the outputs to an oscilloscope
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"

//
// Main
//
void main(void)
{
//
// Declare all variables
//
    uint32_t count;
    uint16_t state;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   // InitSysCtrl();

//
// Step 2. Initialize GPIO:
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
// This function is found in the F2837xD_PieCtrl.c file.
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
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    IPCLtoRFlagSet(IPC_FLAG17);

    state = GpioDataRegs.GPADAT.bit.GPIO11;

    EALLOW;
    GpioDataRegs.GPATOGGLE.bit.GPIO12 = 1;
    EDIS;

    while(1)
    {
        //
        // Produce a Square Wave on GPIO12. This signal will be used to drive
        // GPIO11 input on CPU2
        //
        if(count++ > 2000000)
        {
            count = 0;
            EALLOW;
            GpioDataRegs.GPATOGGLE.bit.GPIO12 = 1;
            EDIS;
        }

        //
        //Set Flag 11 when GPIO11 input changes
        //
        if(GpioDataRegs.GPADAT.bit.GPIO11 != state)
        {
            state = GpioDataRegs.GPADAT.bit.GPIO11;
            if(IPCRtoLFlagBusy(IPC_FLAG11) == 0)
            {
                IPCLtoRFlagSet(IPC_FLAG11);
            }
        }

        //
        //Toggle GPIO34 output if Flag 10 is set by CPU1
        //
        if(IPCRtoLFlagBusy(IPC_FLAG10) == 1)
        {
            EALLOW;
            GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
            EDIS;

            IPCRtoLFlagAcknowledge(IPC_FLAG10);
            IPCLtoRFlagClear(IPC_FLAG10);
        }
    }
}

//
// End of file
//
