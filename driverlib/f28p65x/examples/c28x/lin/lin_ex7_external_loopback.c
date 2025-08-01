//#############################################################################
//
// FILE:   lin_ex7_external_loopback.c
//
// TITLE:   LIN External Loopback without Interrupts
//
//! \addtogroup driver_example_list
//! <h1> LIN External Loopback without interrupts(polled mode)   </h1>
//!
//!  This example configures the LINA module in commander mode and LINB module
//!  in responder mode. Commander transmits 8 byte data to the responder with
//!  a matching ID configured in responder Receive ID. The received data is
//!  then checked for accuracy.
//!
//!
//! \b External \b Connections \n
//!  - Connect LINA TX/RX with LINB TX/RX via transciever.
//!
//! \b Watch \b Variables \n
//!  - txData - An array with the data being sent
//!  - rxData - An array with the data that was received
//!  - result - The example completion status (PASS = 0xABCD, FAIL = 0xFFFF)
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.00.00
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

//
// Defines
//
#define FRAME_LENGTH    0x8
#define LIN_PASS        0xABCD
#define LIN_FAIL        0xFFFF

//
// Globals
//
volatile uint32_t level0Count = 0;
volatile uint32_t level1Count = 0;
volatile uint32_t vectorOffset = 0;
uint16_t result;
uint16_t txID = 0x1A, rxID = 0x1A;
uint16_t txData[8] = {0x11, 0x34, 0x56, 0x78, 0x9A, 0xAB, 0xCD, 0xEF};
uint16_t rxData[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


//
// Main
//
void main(void)
{
    uint32_t dataIndex;
    uint16_t error;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for LINTX/LINRX
    //
    Device_initGPIO();
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LINTXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LINRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LINTXB);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LINRXB);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LINRXA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LINRXA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LINRXA, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LINRXB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LINRXB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LINRXB, GPIO_QUAL_ASYNC);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LINTXA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LINTXA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LINTXA, GPIO_QUAL_ASYNC);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LINTXB, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LINTXB, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LINTXB, GPIO_QUAL_ASYNC);

    //
    // Initialize the LIN module
    //
    LIN_initModule(LINA_BASE);
    LIN_initModule(LINB_BASE);

    //
    // Set LIN B to responder Mode, LIN A to Commander Mode
    //
    LIN_setLINMode(LINB_BASE, LIN_MODE_LIN_RESPONDER);


    LIN_enableParity(LINA_BASE);
    LIN_enableParity(LINB_BASE);

    //
    // Set the ID to match while receiving
    //
    LIN_setIDResponderTask(LINB_BASE, rxID);
    LIN_setIDByte(LINB_BASE, rxID);

    //
    // Set the frame length (number of bytes to be transmitted)
    //
    LIN_setFrameLength(LINA_BASE, 8);
    LIN_setFrameLength(LINB_BASE, 8);

    //
    // Write data to Tx Buffer of LINA
    //
    LIN_sendData(LINA_BASE, txData);

    //
    // Set the message ID to initiate a header transmission.
    // This causes the ID to be written to the bus followed by the
    // data in the transmit buffers.
    //
    txID = LIN_generateParityID(txID);

    LIN_setIDByte(LINA_BASE, txID);

    //
    // Wait until Transmit buffer is empty and has completed transmission
    //
    while(!LIN_isTxBufferEmpty(LINA_BASE));

    //
    //Wait for the Reception
    //
    while(!LIN_isRxMatch(LINB_BASE));

    LIN_clearInterruptStatus(LINA_BASE,LIN_INT_ALL);
    LIN_clearInterruptStatus(LINB_BASE,LIN_INT_ALL);

    //
    // Read the received data in the receive buffers
    //
    LIN_getData(LINB_BASE, rxData);

    //
    // Verify the transmitted data matches the received data
    //
    for (dataIndex=0; dataIndex < 8; dataIndex++)
    {
        if (rxData[dataIndex] != txData[dataIndex])
        {
            error++;
        }
    }

    //
    // Check if any data errors occurred
    //
    if(error == 0)
    {
        result = LIN_PASS;
    }
    else
    {
      result = LIN_FAIL;
    }

    //
    // Example completed. Check "result" variable for completion status.
    //
    asm("   ESTOP0");
}

//
// End of File
//
