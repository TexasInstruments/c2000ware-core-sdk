//###########################################################################
//
// FILE:   ipc_gpio_toggle_cpu01.c
//
// TITLE:  GPIO Toggle for F2837xD CPU1.
//
//! \addtogroup dual_example_list
//! <h1> IPC GPIO toggle </h1>
//!
//! This example shows GPIO input on the local CPU triggering an output on the
//! remote CPU. A GPIO input change on CPU01 causes an output change on CPU02
//! and vice versa. \n
//! CPU1 has control of GPIO31 , GPIO15 and GPIO14.\n
//! CPU2 has control of GPIO34 , GPIO12 and GPIO11.
//!
//! \b Hardware \b Connections
//!   - connect GPIO15 to GPIO11
//!   - connect GPIO14 to GPIO12
//!
//! \b Watch \b Pins
//!   - GPIO31 - output on CPU2 (LED blinking if using control card)
//!   - GPIO11 - input on CPU2
//!   - GPIO34 - output on CPU1 (LED blinking if using control card)
//!   - GPIO14 - input on CPU1
//!   - GPIO12 - square wave output on CPU02
//!   - GPIO15 - square wave output on CPU01
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
// Declare all local variables
//
    uint16_t state;
    uint32_t count;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();

#ifdef _STANDALONE
#ifdef _FLASH
    //
    // Send boot command to allow the CPU2 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
    //
    // Send boot command to allow the CPU2 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

//
// Step 2. Initialize GPIO:
//
    InitGpio();

//
// Give CPU2 Control of GPIO34 , GPIO12 and GPIO11
// GPIO34 and GPIO12 are output and GPIO11 is input
//
    GPIO_SetupPinMux(34,GPIO_MUX_CPU2,0);
    GPIO_SetupPinOptions(34, GPIO_OUTPUT,0);

    GPIO_SetupPinMux(12,GPIO_MUX_CPU2,0);
    GPIO_SetupPinOptions(12, GPIO_OUTPUT,0);

    GPIO_SetupPinMux(11,GPIO_MUX_CPU2,0);
    GPIO_SetupPinOptions(11, GPIO_INPUT,0);

//
// Give CPU1 Control of GPIO31 , GPIO15 and GPIO14
// GPIO31 and GPIO15 are output and GPIO14 is input
//
    GPIO_SetupPinMux(31,GPIO_MUX_CPU1,0);
    GPIO_SetupPinOptions(31, GPIO_OUTPUT,0);

    GPIO_SetupPinMux(15,GPIO_MUX_CPU1,0);
    GPIO_SetupPinOptions(15, GPIO_OUTPUT,0);

    GPIO_SetupPinMux(14,GPIO_MUX_CPU1,0);
    GPIO_SetupPinOptions(14, GPIO_INPUT,0);

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
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// Spin here until CPU02 is ready
//
    while(!IPCRtoLFlagBusy(IPC_FLAG17));
    IPCRtoLFlagAcknowledge(IPC_FLAG17);

    state = GpioDataRegs.GPADAT.bit.GPIO14;

    while(1)
    {
        //
        // Generate a Square Wave on GPIO15. This signal will be used to drive
        // GPIO14 input on CPU1
        //
        if(count++ > 1000000)
        {
            count = 0;

            EALLOW;
            GpioDataRegs.GPATOGGLE.bit.GPIO15 = 1;
            EDIS;
        }

        //
        //Set Flag 10 when GPIO14 input changes
        //
        if(GpioDataRegs.GPADAT.bit.GPIO14 != state)
        {
            state = GpioDataRegs.GPADAT.bit.GPIO14;

            if(IPCRtoLFlagBusy(IPC_FLAG10) == 0)
            {
                IPCLtoRFlagSet(IPC_FLAG10);
            }
        }

        //
        //Toggle GPIO31 output if Flag 11 is set by CPU2
        //
        if(IPCRtoLFlagBusy(IPC_FLAG11) == 1)
        {
            EALLOW;
            GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
            EDIS;

            IPCRtoLFlagAcknowledge(IPC_FLAG11);
            IPCLtoRFlagClear(IPC_FLAG11);
        }
    }
}

//
// End of file
//
