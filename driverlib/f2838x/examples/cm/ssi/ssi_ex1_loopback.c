//#############################################################################
//
// FILE:   ssi_ex1_loopback.c
//
// TITLE:  SSI loopback example
//
//! \addtogroup driver_example_cm_list
//! <h1>SSI Loopback example with interrupts</h1>
//!
//! This example showcases how to use SSI to transfer and receive data in
//! loopback mode
//! cm_common_config_c28x example needs to be run on C28x1 before running this
//! example on the CM core
//!
//! \b Configuration:
//!  - Frame format : TI mode
//!  - Baud rate    : 625000
//!  - Data width   : 12 bits
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b txData   - Data transmitted
//!  - \b rxData   - Data received
//!  - \b errCount - Error count
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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

#include "cm.h"

uint32_t txData[4], rxData[4];
uint8_t  errCount = 0xFF;

void ssiISR(void);

//
// Main
//
void main(void)
{
    uint8_t i;

    //
    // Enable clocks
    //
    CM_init();

    //
    // Configure SSI in master mode, baud rate = 62500, dataWidth = 12
    //
    SSI_setConfig(SSI0_BASE, CM_CLK_FREQ, SSI_FRF_TI, SSI_MODE_MASTER, 625000, 12);

    //
    // Enable the SSI0 module.
    //
    SSI_enableModule(SSI0_BASE);

    //
    // Enable loopback mode
    //
    SSI_enableLoopback(SSI0_BASE);

    //
    // Read any residual data from the SSI port.  This makes sure the receive
    // FIFOs are empty, so we don't read any unwanted junk.  This is done here
    // because the TI SSI mode is full-duplex, which allows you to send and
    // receive at the same time.  The SSI_readDataNonBlocking function returns
    // "true" when data was returned, and "false" when no data was returned.
    // The "non-blocking" function checks if there is any data in the receive
    // FIFO and does not "hang" if there isn't.
    //
    while(SSI_readDataNonBlocking(SSI0_BASE, rxData))
    {
    }

    //
    // Enable Rx interrupt
    //
    SSI_registerInterrupt(INT_SSI0, ssiISR);
    SSI_enableInterrupt(SSI0_BASE, SSI_INT_RXFF);

    //
    // Initialize the data to send.
    //
    txData[0] = 0xAAA;
    txData[1] = 0x555;
    txData[2] = 0x333;
    txData[3] = 0xCCC;

    //
    // Send data.
    //
    for(i = 0; i < 4; i++)
    {
        SSI_writeData(SSI0_BASE, txData[i]);
    }

    //
    // Loop forever. Optional
    //
    while(1);
}

void ssiISR(void)
{
    uint8_t i;

    errCount = 0;

    //
    // Clear the SSI Rx interrupt flag
    //
    SSI_clearInterruptStatus(SSI0_BASE, SSI_INT_RXFF);

    for(i = 0; i < 4; i++)
    {
        //
        // Receive the data using the "blocking" function. This function
        // will wait until there is data in the receive FIFO before returning.
        //
        SSI_readData(SSI0_BASE, &rxData[i]);

        //
        // Mask off the unwanted bits (Datawidth = 12)
        //
        rxData[i] = rxData[i] & 0xFFF;

        //
        // Check the received data
        //
        if(rxData[i] != txData[i])
        {
            errCount++;
        }
    }
}
