//###########################################################################
//
// FILE:   Example_2823xEcanA_to_B_Xmit.c
//
// TITLE:  eCAN-A to eCAN-B Transmit Loop Example
//
//! \addtogroup f2823x_example_list
//! <h1>eCAN-A to eCAN-B Transmit Loop (ecan_a_to_b_xmit)</h1>
//!
//! This example TRANSMITS data to another CAN module using MAILBOX5
//! This program could either loop forever or transmit "n" # of times,
//! where "n" is the TXCOUNT value. \n
//!
//! This example can be used to check CAN-A and CAN-B. Since CAN-B is
//! initialized in DSP2823x_ECan.c, it will acknowledge all frames
//! transmitted by the node on which this code runs. Both CAN ports of
//! the 2823x DSP need to be connected to each other (via CAN transceivers)
//!
//! \b External \b Connections \n
//! - eCANA is on GPIO31 and GPIO30
//! - eCANB is on GPIO8 and GPIO10
//! - Connect GPIO31 to GPIO8
//! - Connect GPIO30 to GPIO10
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
// Defines
//
#define TXCOUNT  100            // Transmission will take place (TXCOUNT) times

//
// Globals
//
long      i;
long 	  loopcount = 0;

//
// Main
//
void main(void)
{
    //
    // Create a shadow register structure for the CAN control registers. 
    // This is needed, since only 32-bit access is allowed to these registers. 
    // 16-bit access to these registers could potentially corrupt the register 
    // contents or return false data.
    //
    struct ECAN_REGS ECanaShadow;

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
    // Just initialize eCAN pins for this example
    // This function is in DSP2823x_ECan.c
    //
    InitECanGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
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

    //
    // No interrupts used in this example.
    //

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2823x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example

    //
    // In this case just initialize eCAN-A and eCAN-B
    // This function is in DSP2823x_ECan.c
    //
    InitECan();

    //
    // Step 5. User specific code
    //

    //
    // Write to the MSGID field
    //
    ECanaMboxes.MBOX25.MSGID.all = 0x95555555;          // Extended Identifier

    //
    // Configure Mailbox under test as a Transmit mailbox
    //
    ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
    ECanaShadow.CANMD.bit.MD25 = 0;
    ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

    //
    // Enable Mailbox under test
    //
    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME25 = 1;
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;

    //
    // Write to DLC field in Master Control reg
    //
    ECanaMboxes.MBOX25.MSGCTRL.bit.DLC = 8;

    //
    // Write to the mailbox RAM field
    //
    ECanaMboxes.MBOX25.MDL.all = 0x55555555;
    ECanaMboxes.MBOX25.MDH.all = 0x55555555;

    //
    // Begin transmitting
    //
    for(i=0; i < TXCOUNT; i++)
    {
        ECanaShadow.CANTRS.all = 0;
        ECanaShadow.CANTRS.bit.TRS25 = 1;     // Set TRS for mailbox under test
        ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

        do
        {
            ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
        } while(ECanaShadow.CANTA.bit.TA25 == 0 );// Wait for TA5 bit to be set

        ECanaShadow.CANTA.all = 0;
        ECanaShadow.CANTA.bit.TA25 = 1;     	         // Clear TA5
        ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;

        loopcount ++;
    }
    __asm(" ESTOP0");  // Stop here
}

//
// End of File
//

