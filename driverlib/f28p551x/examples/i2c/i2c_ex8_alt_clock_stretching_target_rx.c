//#############################################################################
//
// FILE:   i2c_ex8_alt_clock_stretching_target_rx.c
//
//! \addtogroup driver_example_list
//! <h1>I2C Alternative Extended Clock Stretching Target RX</h1>
//! 
//! This example works alongside the i2c_ex8_alt_clock_stretching_controller_tx
//! example. They are intended to be run on two different devices
//! simultaneously. This project configures the I2C module in target-receiver
//! mode, with FIFO disabled. Alternative extended clock stretching mode is
//! enabled so that the SCL will automatically start stretching before each
//! individual address and data byte are received. The ECS interrupt
//! ISR reads one byte at a time, NACK's if needed, delays, then clears
//! the SCL_ECS bit to end clock stretching. The delay time toggles between
//! 10us and 50us for easy viewing on a logic analyzer or scope. 
//!
//! For the sake of the example, data received that begins with 0xA_ is
//! considered "valid" and data received that begins with 0xB_ is considered
//! "invalid". 
//!
//! If NACK_ON_INVALID_DATA is set to 0, 18 data bytes are sent by
//!     the controller and all are ACK'd by the target. 
//! If NACK_ON_INVALID_DATA is set to 1, the first 16 bytes sent by the
//!     controller will be ACK'd and considered valid. When the 17th byte(0xB0)
//!     is sent, this data byte is NACK'd since it is considered invalid.
//!     The controller program will send a STOP condition and abort the
//!     transmission upon receiving a NACK from the target and the 18th byte is
//!     never transmitted.
//!
//!  \b External \b Connections \n
//!  - Connect GPIO35/SDA on to GPIO35/SDA on controller device
//!  - Connect GPIO37/SCL on to GPIO37/SCL on controller device
//!  - Connect pull-up resistors to both SDA and SCL connections
//!
//! \b Watch \b Variables \n
//!  - \b rxData - Message buffer which stores the data received
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
// Set to 1 for additional NACK check - NACK the controller if
// 0xB0 or 0xB1 is received.
//
#define NACK_ON_INVALID_DATA 0

//
// Globals
//
uint16_t rxData[TOT_NUM_I2C_DATA] = {};
uint16_t addrByte = 0;
uint16_t rxDataIndex = 0;
bool stretch50 = true;
bool addrByteRX = true;

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
    // Enable Alternative Extended Clock Stretching Mode
    //
    I2C_enableAlternateExtendedAutomaticClkStretchingMode(myI2C0_BASE);

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

    }
}

//
// I2C A Transmit & Receive ISR - used for error checking
//
__interrupt void INT_myI2C0_ISR(){
    //
    // Checking source of interrupt
    //
    I2C_InterruptSource interruptSource = I2C_getInterruptSource(myI2C0_BASE); 
    switch (interruptSource)
    {
    case I2C_INTSRC_SCL_ECS:
        if(addrByteRX){
            //
            // First ECS interrupt is for the address byte, don't read in as data
            //
            addrByteRX = false;
            addrByte = I2C_getData(myI2C0_BASE);

        }
        else{
            //
            // Receive 1 data byte
            //
            rxData[rxDataIndex] = I2C_getData(myI2C0_BASE);

#if NACK_ON_INVALID_DATA == 1

            //
            // Change outcome of ACK/NACK once 0xBX is received
            //
            if((rxData[rxDataIndex] & 0x00F0) == 0xB0){
                I2C_sendNACK(myI2C0_BASE);
            }
#endif
            rxDataIndex++;
        }

        //
        // Delay - clock stretching should happen here after each byte received
        //
        if(stretch50){
            DEVICE_DELAY_US(50);
            stretch50 = false;
        }
        else{
            DEVICE_DELAY_US(10);
            stretch50 = true;
        }

        //
        // Finish clock stretching
        //
        uint16_t ecsBitCheck = HWREGH(myI2C0_BASE + I2C_O_STR) & I2C_STS_SCL_ECS;
        if (ecsBitCheck)
        {
            //
            // Clear clock stretching bit to end clock stretching
            //
            HWREGH(myI2C0_BASE + I2C_O_STR) |= I2C_STS_SCL_ECS;
        }
        else
        {
            //
            // Error - SCL_ECS should be high upon entering the ISR
            //
            ESTOP0;
        }
        break;
    case I2C_INTSRC_STOP_CONDITION:

        //
        // If NACK_ON_INVALID_DATA=0: Data packet has been fully received
        //      in rxData (18 characters).
        // If NACK_ON_INVALID_DATA=1: 17 data bytes have been received and rxData should
        //      have one empty element due to NACK of 0xB0.
        //
        ESTOP0;
        break;
    }
    Interrupt_clearACKGroup(INT_myI2C0_INTERRUPT_ACK_GROUP);
}
//
// End of File
//
