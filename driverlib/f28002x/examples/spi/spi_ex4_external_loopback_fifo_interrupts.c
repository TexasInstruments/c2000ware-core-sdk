//#############################################################################
//
// FILE:   spi_ex4_external_loopback_fifo_interrupt.c
//
// TITLE:  SPI Digital Loopback with FIFO Interrupts
//
//! \addtogroup driver_example_list
//! <h1>SPI Digital External Loopback with FIFO Interrupts</h1>
//!
//! This program uses the external loopback between two SPI modules. Both
//! the SPI FIFOs and their interrupts are used. SPIA is configured as a peripheral
//! and receives data from SPI B which is configured as a controller.
//!
//! A stream of data is sent and then compared to the received stream.
//! The sent data looks like this: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  FFFE FFFF \n
//!  FFFF 0000 \n
//!  etc.. \n
//! This pattern is repeated forever.
//!
//!  \note This example project has support for migration across our C2000 
//!  device families. If you are wanting to build this project from launchpad
//!  or controlCARD, please specify in the .syscfg file the board you're using.
//!  At any time you can select another device to migrate this example.
//!
//! \b External \b Connections \n
//! Refer to SysConfig for external connections (GPIO pin numbers) specific to each device
//!
//! \b Watch \b Variables \n
//!  - \b sData - Data to send
//!  - \b rData - Received data
//!  - \b rDataPoint - Used to keep track of the last position in the receive
//!    stream for error checking
//!
//
//#############################################################################
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
volatile uint16_t sData[2];                  // Send data buffer
volatile uint16_t rData[2];                  // Receive data buffer
volatile uint16_t rDataPoint = 0;            // To keep track of where we are in the
                                    // data stream to check received data

//
// Function Prototypes
//
__interrupt void spibTxFIFOISR(void);
__interrupt void spiaRxFIFOISR(void);

//
// Main
//
void main(void)
{
    uint16_t i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
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
    // Board initialization
    //
    Board_init();

    //
    // Initialize the data buffers
    //
    for(i = 0; i < 2; i++)
    {
        sData[i] = i;
        rData[i]= 0;
    }

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    while(1)
    {
        ;
    }
}

//
// SPI B Transmit FIFO ISR
//
__interrupt void spibTxFIFOISR(void)
{
    uint16_t i;

    //
    // Send data
    //
    for(i = 0; i < 2; i++)
    {
       SPI_writeDataNonBlocking(SPIB_BASE, sData[i]);
    }

    //
    // Increment data for next cycle
    //
    for(i = 0; i < 2; i++)
    {
       sData[i] = sData[i] + 1;
    }

    //
    // Clear interrupt flag and issue ACK
    //
    SPI_clearInterruptStatus(SPIB_BASE, SPI_INT_TXFF);
    Interrupt_clearACKGroup(INT_SPIB_controller_TX_INTERRUPT_ACK_GROUP);
}

//
// SPI A Receive FIFO ISR
//
 __interrupt void spiaRxFIFOISR(void)
{
    uint16_t i;

    //
    // Read data
    //
    for(i = 0; i < 2; i++)
    {
        rData[i] = SPI_readDataNonBlocking(SPIA_BASE);
    }

    //
    // Check received data
    //
    for(i = 0; i < 2; i++)
    {
        if(rData[i] != (rDataPoint + i))
        {
            // Something went wrong. rData doesn't contain expected data.
            ESTOP0;
        }
    }

    rDataPoint++;

    //
    // Clear interrupt flag and issue ACK
    //
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
    Interrupt_clearACKGroup(INT_SPIA_peripheral_RX_INTERRUPT_ACK_GROUP);
}

 //
 // Enabled only for SysConfig functionality
 //
__interrupt void INT_SPIA_peripheral_TX_ISR(void) {
    //
    // Issue ACK
    //
    Interrupt_clearACKGroup(INT_SPIA_peripheral_TX_INTERRUPT_ACK_GROUP);
}

//
// Enabled only for SysConfig functionality
//
__interrupt void INT_SPIB_controller_RX_ISR(void) {
    //
    // Issue ACK
    //
    Interrupt_clearACKGroup(INT_SPIB_controller_RX_INTERRUPT_ACK_GROUP);

}

//
// End of file
//
