//###########################################################################
//
// FILE:   lpm_haltwake_dc_cpu02.c
//
// TITLE:  Halt entry and Exit Example for F2837xD CPU2
//
//  <h1>Low Power Modes: Halt Mode and Wakeup (lpm_haltwake_dc_cpu02)</h1>
//
//  This example puts CPU2 into IDLE mode in preparation for CPU1 putting
//  the device into HALT mode.
//
//  GPIO12 is configured as the monitor pin for CPU2. Before the device
//  enters HALT mode, GPIO12 will be set High. After the device wakes up
//  GPIO12 can be observed to go low.
//
//  To observe when CPU2 wakes from HALT mode, monitor GPIO12 with an
//  oscilloscope (Cleared to 0 in WAKEINT ISR)
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

#ifdef _FLASH
//
// These are defined by the linker (see device linker command file)
//
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
#endif

//
// Function Prototypes
//
__interrupt void local_WAKE_ISR(void);

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2837xD_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the F2837xD_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
//    InitGpio(); // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.WAKE_INT = &local_WAKE_ISR;
    EDIS;

    //
    // Step 4. Initialize all the Device Peripherals:
    //
    // Not applicable for this example.

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Enable CPU INT1 which is connected to WakeInt:
    //
    IER |= M_INT1;

    //
    // Enable WAKEINT in the PIE: Group 1 interrupt 4
    //
    PieCtrlRegs.PIEIER1.bit.INTx8 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Enable global Interrupts:
    //
    EINT;   // Enable Global interrupt INTM

    //
    // Ensure there are no subsequent flash accesses to wake up the pump and
    // bank Power down the flash bank and pump
    //
    SeizeFlashPump();
    FlashOff();
    ReleaseFlashPump();

    //
    // Sync with CPU1 before entering HALT.
    // CPU2 must be in IDLE before CPU1 enters HALT mode.
    //
    IpcSync(5);

    //
    // CPU2 will actually enter IDLE before CPU1 puts the device into
    // HALT mode.
    //
    GpioDataRegs.GPASET.bit.GPIO12 = 1;  // set GPIO12 high while in HALT mode
    HALT();                              // enter enter HALT mode

    ESTOP0;

    //
    // loop forever
    //
    while(1);
}

//
// local_WAKE_ISR - Wake up ISR
//
interrupt void local_WAKE_ISR(void)
{
    GpioDataRegs.GPACLEAR.bit.GPIO12 = 1;   // GPIO12 is cleared to 0 upon
                                            // exiting HALT.
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
//  End of file
//
