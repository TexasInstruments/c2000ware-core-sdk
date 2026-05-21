//#############################################################################
//
// FILE:   i2c_ex8_alt_clock_stretching_controller_tx.c
// 
//! This example works alongside the i2c_ex8_alt_clock_stretching_target_rx
//! example. They are intended to be run on two different devices
//! simultaneously. This project configures the I2C module in 
//! controller-transmitter mode, with FIFO disabled. The TX_DATA_RDY interrupt
//! ISR transmits one byte at a time and increments the txDataIndex variable.
//! The arbitration lost interrupt is added for error detection. 
//!
//! For the sake of the example, data received that begins with 0xA_ is
//! considered "valid" and data received that begins with 0xB_ is considered
//! "invalid". 
//!
//! If NACK_ON_INVALID_DATA in the target code is set to 0, 18 data bytes are
//!     sent by the controller and all are ACK'd by the target. 
//! If NACK_ON_INVALID_DATA in the target code is set to 1, the first 16 bytes
//!     sent by the controller will be ACK'd and considered valid. When the 
//!     17th byte (0xB0) is sent, this data byte is NACK'd since it is
//!     considered invalid.
//!     The NACK interrupt ISR issues a STOP condition in this case to abort the
//!     transmission upon receiving a NACK from the target and the program won't
//!     transmit the 18th byte.
//!
//!
//!  \b External \b Connections \n
//!  - Connect GPIO35/SDA to GPIO35/SDA on target device
//!  - Connect GPIO37/SCL to GPIO37/SCL on target device
//!  - Connect pull-up resistors to both SDA and SCL connections
//!
//! \b Watch \b Variables \n
//!  - \b txDataIndex - Counter variable tracking number of bytes transmitted
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2026 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Defines
//
#define TOT_NUM_I2C_DATA 18

//
// Globals
//
uint16_t txDataIndex = 0;

//
// Function Prototypes
//
__interrupt void INT_myI2C0_ISR(void);


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

    //
    // Enable START and STOP condition. STOP condition will send when after
    // 18 data bytes have transmitted.
    //
    I2C_sendStartCondition(myI2C0_BASE);

    I2C_sendStopCondition(myI2C0_BASE);

    //
    // Loop forever.
    //
    while(1)
    {

    }
}

//
// I2C A Transmit & Receive ISR - used for transmits and error checking
//

__interrupt void INT_myI2C0_ISR(void)
{
    //
    // Check source of interrupt
    //
    I2C_InterruptSource interruptSource = I2C_getInterruptSource(myI2C0_BASE);
    switch (interruptSource)
    {
    case I2C_INTSRC_TX_DATA_RDY:
        //
        // Transmit 1 data byte
        //
        I2C_putData(myI2C0_BASE, 0xA0 + txDataIndex);
        txDataIndex++;
        break;
    case I2C_INTSRC_ARB_LOST:
        //
        // Error on the bus
        //
        ESTOP0;
        break;
    case I2C_INTSRC_NO_ACK:
        //
        // If target side code has NACK_ON_INVALID_DATA define set to 1,
        // controller program should stop here.
        //
        I2C_clearStatus(myI2C0_BASE, I2C_STS_NO_ACK);
        I2C_sendStopCondition(myI2C0_BASE);

        ESTOP0;
        break;
    }
    Interrupt_clearACKGroup(INT_myI2C0_INTERRUPT_ACK_GROUP);
}
//
// End of File
//
