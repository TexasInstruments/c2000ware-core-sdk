//#############################################################################
//
// FILE:   i2c_ex1_controller.c
//
// TITLE:  I2C Example Controller.
//
//! \addtogroup bitfield_example_list
//! <h1>I2C controller target communication using bit-field and without FIFO </h1>
//!
//! This program shows how to use I2CA in controller configuration.
//! This example uses polling and does not use interrupts or FIFO
//!
//! \b Requires two Control Cards - one configured as Controller and other as Target \n
//! \b Controller will run the binary generated from "i2c_ex1_controller.projectspec" \n
//! \b Target will run the binary generated from "i2c_ex1_target.projectspec" \n
//! \b External \b Connections on Control Cards should be made as shown below \n
//!  ----------------------------------------------------------------
//!    Signal   |  I2CA on Board1      |  I2CA on Board 2
//!  -----------------------------------------------------------------
//!     SCL     | GPIO_PIN_SCLA        |  GPIO_PIN_SCLA
//!     SDA     | GPIO_PIN_SDAA        |  GPIO_PIN_SDAA
//!     GND     |   GND                 |   GND
//!  -----------------------------------------------------------------
//!
//! Example1: Controller Transmitter and Target Receiver
//! Example2: Controller Receiver and Target Transmitter
//! Example3: Controller Transmitter and Target Receiver
//!           followed by Controller Receiver and Target Transmitter
//! Example4: Controller Receiver and Target Transmitter
//!           followed by Controller Transmitter and Target Receiver
//!
//! \b Watch \b Variables in memory window\n
//!  - \b I2CA_TXdata
//!  - \b I2CA_RXdata
//!
//
//#############################################################################
// 
// C2000Ware v5.04.00.00
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
#include "f28x_project.h"

//
// Defines
//
#define I2C_TARGET_ADDRESS 0x6AU
#define I2C_OWN_ADDRESS 0x30U
#define MAX_BUFFER_SIZE 0x10
#define I2C_NUMBYTES    0x2U

//
// I2C GPIO pins
//
#define GPIO_PIN_SDAA        26U  // GPIO number for I2C SDAA
#define GPIO_PIN_SCLA        27U  // GPIO number for I2C SCLA

//
// Globals
//
uint16_t I2C_TXdata[MAX_BUFFER_SIZE];
uint16_t I2C_RXdata[MAX_BUFFER_SIZE];


//
// Function Prototypes
//
void I2CController_Init(uint16_t I2CTarget_OwnAddress, uint16_t I2CTarget_Address);
void I2CWrite(uint16_t targetAddr, uint16_t byteCount, bool sendStopCondition);
uint16_t I2CRead(uint16_t targetAddr, uint16_t byteCount, bool sendStopCondition);


//
// Main
//
void main(void)
{
    //
    // Locals
    //
    uint16_t index = 0U;
    uint16_t count = 0U;

    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

     //
     // Initialize GPIO
     //
     InitGpio();

     //
     //Configure I2C pins
     //
     GPIO_SetupPinMux(GPIO_PIN_SDAA, GPIO_MUX_CPU1, 11);
     GPIO_SetupPinOptions(GPIO_PIN_SDAA, GPIO_OUTPUT, GPIO_PULLUP);
     GPIO_SetupPinMux(GPIO_PIN_SCLA, GPIO_MUX_CPU1, 11);
     GPIO_SetupPinOptions(GPIO_PIN_SCLA, GPIO_OUTPUT, GPIO_PULLUP);


    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR)
    //
    InitPieVectTable();

    //
    // Set the buffer to some default non-zero value
    //
    for (index=0; index<MAX_BUFFER_SIZE;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
        I2C_TXdata[index] = 0x11 * (index+1);
    }

    //
    // Initialize I2C Module as Controller Transmitter
    //
    I2CController_Init(I2C_OWN_ADDRESS,I2C_TARGET_ADDRESS);

    //
    // Example 1 : Controller as a Transmitter , writes two bytes
    //
    I2CWrite(I2C_TARGET_ADDRESS, I2C_NUMBYTES, true);

    //
    // Wait for I2C bus to clear
    //
    while(I2caRegs.I2CMDR.bit.STP !=0x0);
    while(I2caRegs.I2CSTR.bit.BB !=0x0);

    //
    //If code reached below ESTOP0, Example 1 worked correctly
    //Observe the contents of I2CA_TXdata and I2CB_RXdata in memory browser
    // Move the PC to next line
	//
    ESTOP0;

    //
    // Example 2 : Controller as a Receiver , receives two bytes
    //
    count = I2CRead(I2C_TARGET_ADDRESS,I2C_NUMBYTES,true);

    //
    // Wait for I2C bus to clear
    //
    while(I2caRegs.I2CMDR.bit.STP !=0x0);
    while(I2caRegs.I2CSTR.bit.BB !=0x0);

    //
    //If code reached below ESTOP0, Example 2 worked correctly
    //Observe the contents of I2CA_TXdata and I2CB_RXdata in memory browser
    // Move the PC to next line
    //
    ESTOP0;

    //
    //clear the Rx buffer
    //
    for (index=0; index<count;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
    }

    //
    // Example 3 : Controller Transmitter followed by Controller Receiver
    //
    I2CWrite(I2C_TARGET_ADDRESS, I2C_NUMBYTES, false); //Write byte
    count = I2CRead(I2C_TARGET_ADDRESS,I2C_NUMBYTES,true);

    //
    // Wait for I2C bus to clear
    //
    while(I2caRegs.I2CMDR.bit.STP !=0x0);
    while(I2caRegs.I2CSTR.bit.BB !=0x0);

    //
    //If code reached below ESTOP0, Example 3 worked correctly
    //Observe the contents of I2CA_TXdata and I2CB_RXdata in memory browser
    // Move the PC to next line    
	//
    ESTOP0;

    //
    //clear the Rx buffer
    //
    for (index=0; index<count;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
    }

    //
    // Exampel 4: Controller Receiver followed by Controller Receiver
    //
    count =I2CRead(I2C_TARGET_ADDRESS, I2C_NUMBYTES, false); //Write byte
    I2CWrite(I2C_TARGET_ADDRESS,I2C_NUMBYTES,true);

    //
    // Wait for I2C bus to clear
    //
    while(I2caRegs.I2CMDR.bit.STP !=0x0);
    while(I2caRegs.I2CSTR.bit.BB !=0x0);

    //
    //If code reached below ESTOP0, Example 4 worked correctly
    //Observe the contents of I2CA_TXdata and I2CB_RXdata in memory browser
    // Move the PC to next line	
    //
    ESTOP0;

    //
    //clear the Rx buffer
    //
    for (index=0; index<count;index++)
    {
        I2C_RXdata[index] = 0xBAADU;
    }

    //
    // Loop forever.
    //
    while(1)
    {

    }

}

//
// Function to configure I2CA as Controller Transmitter.
//
void I2CController_Init(uint16_t I2C_OwnAddress, uint16_t I2CTarget_Address)
{
    EALLOW;
    //
    // Must put I2C into reset before configuring it
    //
    I2caRegs.I2CMDR.all &= ~(0x20U);

    //
    // I2C configuration. Use a 400kHz I2CCLK with a 50% duty cycle.
    //
    //I2C_initController(base, DEVICE_SYSCLK_FREQ, 400000, I2C_DUTYCYCLE_50);
    I2caRegs.I2CPSC.all = 0xB;        // Prescaler - need 7-12 Mhz on module clk
    I2caRegs.I2CCLKL = 0x7;          // NOTE: must be non zero
    I2caRegs.I2CCLKH = 0x8;           // NOTE: must be non zero


    //
    // Configure Controller as a Transmitter
    //
    I2caRegs.I2CMDR.bit.CNT = 0x1;
    I2caRegs.I2CMDR.bit.TRX = 0x1;

    //
    // Set data count
    //
    I2caRegs.I2CCNT = I2C_NUMBYTES;

    //
    // Set the bit count to 8 bits per data byte
    //
    I2caRegs.I2CMDR.bit.BC = 0x0U;

    //
    // Configure target and own address
    //
    I2caRegs.I2COAR.all = I2C_OwnAddress;      // Own address
    I2caRegs.I2CTAR.all = I2CTarget_Address;      // Target address

    //
    // Set emulation mode to FREE
    //
    I2caRegs.I2CMDR.bit.FREE = 0x1;

    //
    //Clear all status
    //
    I2caRegs.I2CSTR.all = 0xFFFF;

    //
    // Enable I2C Interrupts- RRDY
    //
    I2caRegs.I2CIER.all = 0x08;

    //
    // Take I2C out of reset
    //
    I2caRegs.I2CMDR.all |= 0x0020;


}

//
// Function to send data over I2C.
//
void I2CWrite(uint16_t targetAddr, uint16_t byteCount, bool sendStopCondition)
{

    //
    // Locals
    //
    uint16_t index = 0;

    //
    // Configure target address
    //
    I2caRegs.I2CTAR.all = targetAddr;      // Target address

    //
    // Configure I2C as Controller Transmitter
    //
    I2caRegs.I2CMDR.bit.CNT = 0x1;
    I2caRegs.I2CMDR.bit.TRX = 0x1;

    //
    //Set Data Count
    //
    I2caRegs.I2CCNT = byteCount;

    //
    // send Start condition
    //
    I2caRegs.I2CMDR.bit.STT = 0x1;

    //
    //transmit the bytes
    //
    for(index=0; index < I2C_NUMBYTES; index++)
    {
        I2caRegs.I2CDXR.all= I2C_TXdata[index];
        //
        //wait till byte is sent
        //
        while(I2caRegs.I2CSTR.bit.BYTESENT != 0x1);
        //
        //clear the byte sent
        //
        I2caRegs.I2CSTR.bit.BYTESENT = 0x1;
    }

    //
    // Send STOP condition if specified
    //
    if(sendStopCondition)
    {
        I2caRegs.I2CMDR.bit.STP = 0x1;
        while(I2caRegs.I2CMDR.bit.STP != 0x0);

        I2caRegs.I2CSTR.bit.BYTESENT = 0x1;
    }
}

//
// Function to read data over I2C. Returns the number of bytes read
//
uint16_t I2CRead(uint16_t targetAddr, uint16_t byteCount, bool sendStopCondition)
{
    //
    // Configure target address
    //
    I2caRegs.I2CTAR.all = targetAddr;

    //
    // Configure I2C in Controller Receiver mode
    //
    I2caRegs.I2CMDR.bit.CNT = 0x1;
    I2caRegs.I2CMDR.bit.TRX = 0x0;

    //
    //Set Data Count
    //
    //I2caRegs.I2CCNT = byteCount;

    //
    // send Start condition
    //
    I2caRegs.I2CMDR.bit.STT = 0x1;

    uint16_t count = 0;

    //
    // Read the received data into RX buffer
    //
    while(count < I2C_NUMBYTES)
    {
        if(I2caRegs.I2CSTR.bit.RRDY ==0x1)
        {
            I2C_RXdata[count] = I2caRegs.I2CDRR.all;
            count++;
        }
    }

    //
    // Send STOP condition
    //
    if(sendStopCondition)
    {
        I2caRegs.I2CMDR.bit.STP = 0x1;
        while(I2caRegs.I2CMDR.bit.STP != 0x0);

        I2caRegs.I2CSTR.bit.BYTESENT = 0x1;

    }
    return count;
}



//
//
// End of File
//

