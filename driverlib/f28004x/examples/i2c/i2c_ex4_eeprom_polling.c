//#############################################################################
//
// FILE:   i2c_ex4_eeprom_polling.c
//
// TITLE:  I2C EEPROM Write / Read using polling
//
//! \addtogroup driver_example_list
//! <h1>I2C EEPROM</h1>
//!
//! This program will shows how to perform different EEPROM write and read
//! commands using I2C polling method
//! EEPROM used for this example is AT24C256
//!
//! \b External \b Connections \n
//!  - Connect external I2C EEPROM at address 0x50
//!  --------------------------------
//!    Signal   |  I2CA   |  EEPROM
//!  --------------------------------
//!     SCL     | GPIO37 |  SCL
//!     SDA     | GPIO35 |  SDA
//!     Make sure to connect GND pins if EEPROM and C2000 device are in different board.
//!  --------------------------------

//! //Example 1: EEPROM Byte Write
//! //Example 2: EEPROM Byte Read
//! //Example 3: EEPROM word (16-bit) write
//! //Example 4: EEPROM word (16-bit) read
//! //Example 5: EEPROM Page write
//! //Example 6: EEPROM word Paged read
//!
//! \b Watch \b Variables \n
//!  - \b TX_MsgBuffer - Message buffer which stores the data to be transmitted
//!  - \b RX_MsgBuffer - Message buffer which stores the data to be received
//!
//!
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#include "i2cLib_FIFO_polling.h"

//
// Globals
//
struct I2CHandle EEPROM;

struct I2CHandle *currentMsgPtr;                   // Used in interrupt


uint16_t passCount = 0;
uint16_t failCount = 0;

uint16_t AvailableI2C_slaves[20];
uint16_t TX_MsgBuffer[MAX_BUFFER_SIZE];
uint16_t RX_MsgBuffer[MAX_BUFFER_SIZE];
uint32_t ControlAddr;
uint16_t status;


void fail(void);
void pass(void);

void I2C_GPIO_init(void);
void I2Cinit(void);
void verifyEEPROMRead(void);

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
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize I2C pins
    //
    I2C_GPIO_init();

    //
    // Initialize PIE and clear PIE registers. Disable CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    I2Cinit();

    //I2Cs connected to I2CA will be found in AvailableI2C_slaves buffer
    //after you run I2CBusScan function.
    uint16_t *pAvailableI2C_slaves = AvailableI2C_slaves;
    status = I2CBusScan(I2CA_BASE, pAvailableI2C_slaves);

    uint16_t i;

    for(i=0;i<MAX_BUFFER_SIZE;i++)
    {
        TX_MsgBuffer[i] = 0;
        RX_MsgBuffer[i] = 0;
    }

    EEPROM.targetAddr      = 0x50;
    EEPROM.base           = I2CA_BASE;
    EEPROM.pControlAddr   = &ControlAddr;
    EEPROM.NumOfAddrBytes = 2;
    EEPROM.pTX_MsgBuffer  = TX_MsgBuffer;
    EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
    EEPROM.NumOfAttempts  = 5;
    EEPROM.Delay_us       = 10;
    EEPROM.WriteCycleTime_in_us = 6000;    //10ms for EEPROM this code was tested

    //Example 1: EEPROM Byte Write
    //Write 11 to EEPROM address 0x0
    ControlAddr = 0;
    EEPROM.NumOfDataBytes = 1;
    TX_MsgBuffer[0]       = 11;
    status = I2C_ControllerTransmitter(&EEPROM);

    //Wait for EEPROM write cycle time
    //This delay is not mandatory. User can run their application code instead.
    //It is however important to wait for EEPROM write cycle time before you initiate
    //another read / write transaction
    DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

    //Example 2: EEPROM Byte Read
    //Make sure 11 is written to EEPROM address 0x0
    ControlAddr = 0;
    EEPROM.pControlAddr   = &ControlAddr;
    EEPROM.NumOfDataBytes = 1;
    status = I2C_ControllerReceiver(&EEPROM);

    while(I2C_getStatus(EEPROM.base) & I2C_STS_BUS_BUSY);

    verifyEEPROMRead();

    //Example 3: EEPROM word (16-bit) write
    //EEPROM address 0x1 = 22 &  0x2 = 33
    ControlAddr = 1;   //EEPROM address to write
    EEPROM.NumOfDataBytes  = 2;
    TX_MsgBuffer[0]        = 0x11;
    TX_MsgBuffer[1]        = 0x22;
    EEPROM.pTX_MsgBuffer   = TX_MsgBuffer;
    status = I2C_ControllerTransmitter(&EEPROM);

    //Wait for EEPROM write cycle time
    //This delay is not mandatory. User can run their application code instead.
    //It is however important to wait for EEPROM write cycle time before you initiate
    //another read / write transaction
    DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

    //Example 4: EEPROM word (16-bit) read
     //Make sure EEPROM address 1 has 0x11 and 2 has 0x22
     ControlAddr = 1;
     EEPROM.pControlAddr   = &ControlAddr;
     EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
     EEPROM.NumOfDataBytes = 2;

     status = I2C_ControllerReceiver(&EEPROM);

     verifyEEPROMRead();


    //Example 5: EEPROM Page write
    //Program address = data pattern from address 64

    for(i=0;i<MAX_BUFFER_SIZE;i++)
    {
        TX_MsgBuffer[i] = i+64;
    }

    ControlAddr = 64;   //EEPROM address to write
    EEPROM.NumOfDataBytes  = MAX_BUFFER_SIZE;
    EEPROM.pTX_MsgBuffer   = TX_MsgBuffer;
    status = I2C_ControllerTransmitter(&EEPROM);

    //Wait for EEPROM write cycle time
    //This delay is not mandatory. User can run their application code instead.
    //It is however important to wait for EEPROM write cycle time before you initiate
    //another read / write transaction
    DEVICE_DELAY_US(EEPROM.WriteCycleTime_in_us);

    //Example 6: EEPROM word Paged read
    ControlAddr = 64;
    EEPROM.pControlAddr   = &ControlAddr;
    EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
    EEPROM.NumOfDataBytes = MAX_BUFFER_SIZE;

    status = I2C_ControllerReceiver(&EEPROM);

    verifyEEPROMRead();

    if(status)
    {
        fail();
    }
    else
    {
        pass();
    }

}

//
// pass - Function to be called if data written matches data read
//
void
pass(void)
{
    asm("   ESTOP0");
    for(;;);
}

//
// fail - Function to be called if data written does NOT match data read
//
void fail(void)
{
    asm("   ESTOP0");
    for(;;);
}

void verifyEEPROMRead(void)
{
    uint16_t i;
    while(I2C_getStatus(EEPROM.base) & I2C_STS_BUS_BUSY);

    for(i=0;i<EEPROM.NumOfDataBytes;i++)
    {
        if(RX_MsgBuffer[i] != TX_MsgBuffer[i])
        {
            //Transmitted data doesn't match received data
            //Fail condition. PC shouldn't reach here
            ESTOP0;
            fail();
        }
    }
}


void I2C_GPIO_init(void)
{
    // I2CA pins (SDAA / SCLA)
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SDAA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SDAA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SDAA, GPIO_QUAL_ASYNC);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCLA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCLA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCLA, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SDAA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCLA);
}

void I2Cinit(void)
{
    //myI2CA initialization
    I2C_disableModule(I2CA_BASE);
    I2C_initController(I2CA_BASE, DEVICE_SYSCLK_FREQ, 100000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CA_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_setTargetAddress(I2CA_BASE, 80);
    I2C_setOwnAddress(I2CA_BASE, 96); //I2CA address
    I2C_disableLoopback(I2CA_BASE);
    I2C_setBitCount(I2CA_BASE, I2C_BITCOUNT_8);
    I2C_setDataCount(I2CA_BASE, 2);
    I2C_setAddressMode(I2CA_BASE, I2C_ADDR_MODE_7BITS);
    I2C_enableFIFO(I2CA_BASE);
    I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_ARB_LOST | I2C_INT_NO_ACK);
    I2C_setFIFOInterruptLevel(I2CA_BASE, I2C_FIFO_TXEMPTY, I2C_FIFO_RX2);
    I2C_enableInterrupt(I2CA_BASE, I2C_INT_ADDR_SLAVE | I2C_INT_ARB_LOST | I2C_INT_NO_ACK | I2C_INT_STOP_CONDITION);
    I2C_setEmulationMode(I2CA_BASE, I2C_EMULATION_FREE_RUN);
    I2C_enableModule(I2CA_BASE);
}

//
// End of File
//

