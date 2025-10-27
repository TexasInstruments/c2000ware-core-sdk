//#############################################################################
//
// FILE:   transfer_ex5_raw_fsi_tx.c
//
// TITLE:  Transfer: FSI Custom Logger Solution
//
//! \addtogroup driver_example_list
//! <h1> GUI based solution for data logging (one direction) </h1>
//!
//! This example demonstrates how to use SysConfig to enable data logging
//! on our C28x devices. 
//!
//! In this example, we are using FSI to export data out of the device.
//! This will export raw FSI frames in no packaged format. This example can 
//! be used with transfer_ex5_comslogger_rtlog_export_sci example to view the 
//! FSI frames via SCI.
//! If you're using a launchpad, you can enable board components to select
//! the correct FSI base to visualize the data through the COM port.
//!
//
//#############################################################################
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "board.h"
#include "c2000ware_libraries.h"


volatile uint16_t myFSITX0_transferInProgress = 0;
uint16_t data[myFSITX0_nWords] = {
          48,49,50,51,
          52,53,54,55,
          56,57,58,59,
          60,61,62,63
};

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
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();


    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        DEVICE_DELAY_US(1000000);


        while(myFSITX0_transferInProgress == 1);
        FSI_writeTxBuffer(myFSITX0_BASE, (const uint16_t *)data, myFSITX0_nWords, 0);
        //
        // Start Transfer
        //
        FSI_startTxTransmit(myFSITX0_BASE);
        myFSITX0_transferInProgress = 1;

    }
}


interrupt void INT_myFSITX0_1_ISR() {
    myFSITX0_transferInProgress = 0;
    FSI_clearTxEvents(myFSITX0_BASE, FSI_TX_EVTMASK);

    //
    // Issue PIE ack
    //
    Interrupt_clearACKGroup(INT_myFSITX0_1_INTERRUPT_ACK_GROUP);
}


//
// End of File
//
