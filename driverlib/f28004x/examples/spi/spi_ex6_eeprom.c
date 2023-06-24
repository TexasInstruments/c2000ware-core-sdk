//#############################################################################
//
// FILE:   spi_ex6_eeprom.c
//
// TITLE:  SPI EEPROM
//
//! \addtogroup driver_example_list
//! <h1>SPI EEPROM</h1>
//!
//! This program will write 8 bytes to EEPROM and read them back. The device
//! communicates with the EEPROM via SPI and specific opcodes. This example is
//! written to work with the SPI Serial EEPROM AT25128/256.
//!
//! \b External \b Connections \n
//!  - Connect external SPI EEPROM
//!  - Connect GPIO16 (PICO) to external EEPROM SI pin
//!  - Connect GPIO17 (POCI) to external EEPROM SO pin
//!  - Connect GPIO56 (CLK) to external EEPROM SCK pin
//!  - Connect GPIO11 (CS) to external EEPROM CS pin
//!  - Connect the external EEPROM VCC and GND pins
//!
//! \b Watch \b Variables \n
//!  - writeBuffer - Data that is written to external EEPROM
//!  - readBuffer  - Data that is read back from EEPROM
//!  - error       - Error count
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Defines
//
#define EEPROM_ADDR                 0x0000
#define NUM_BYTES                   8

//
// SPI EEPROM status
//
#define MSG_STATUS_READY_M          0x0001 // EEPROM is ready (not busy)
#define MSG_STATUS_WRITE_READY_M    0x0002 // EEPROM
#define MSG_STATUS_BUSY             0xFFFF // EEPROM is busy (internal write)

//
// Opcodes for the EEPROM (8-bit)
//
#define RDSR                        0x05
#define READ                        0x03
#define WRITE                       0x02
#define WREN                        0x06
#define WRDI                        0x04
#define WRSR                        0x01

//
// Defines for Chip Select toggle.
//
#define CS_LOW                      GPIO_writePin(SPI_CS_GPIO, 0)
#define CS_HIGH                     GPIO_writePin(SPI_CS_GPIO, 1)

//
// Globals
//
uint16_t writeBuffer[8] = {100, 101, 102, 103, 104, 105, 106, 107};
uint16_t readBuffer[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//
// Function Prototypes
//
uint16_t readStatusRegister(uint16_t statusRegister);
void writeData(uint16_t address, uint16_t * data, uint16_t length, uint16_t txdly);
void readData(uint16_t address, uint16_t * data, uint16_t length,  uint16_t txdly);
void enableWrite(void);

#define DUMMY_DATA 0
#define NO_DELAY   0

uint16_t SPI_readByte_EEPROM(uint32_t base, uint16_t address);
uint16_t SPI_read16bits_EEPROM(uint32_t base, SPI_endianess endianness, uint16_t address);
uint32_t SPI_read24bits_EEPROM(uint32_t base, SPI_endianess endianness, uint16_t address);
uint32_t SPI_read32bits_EEPROM(uint32_t base, SPI_endianess endianness, uint16_t address);

void done(void);

uint32_t base = SPIA_BASE;

#define BUFFER_SIZE 64

//
// Main
//
void main(void)
{
    uint16_t i;
    uint16_t pass = 0;
    uint16_t fail = 0;


    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Board initialization
    //
    Board_init();

    uint16_t TXbuff[BUFFER_SIZE];
    uint16_t RXbuff[BUFFER_SIZE];

    for(i=0; i<BUFFER_SIZE;i++)
    {
        TXbuff[i] = i+1;
        RXbuff[i] = 0;
    }

    CS_HIGH;

    //
    // Enable write on the EEPROM
    //
    enableWrite();

    // Wait until the EEPROM is ready to write data
    while((readStatusRegister(RDSR) & MSG_STATUS_WRITE_READY_M) == MSG_STATUS_WRITE_READY_M)
    {
    }

    writeData(EEPROM_ADDR, &TXbuff[0], BUFFER_SIZE, NO_DELAY);

    //
    // Wait until the EEPROM is ready to write data
    //
    while((readStatusRegister(RDSR) & MSG_STATUS_READY_M) == MSG_STATUS_READY_M)
    {
    }

    uint32_t RXdata = 0;

    RXdata = SPI_readByte_EEPROM(base, EEPROM_ADDR);

    if(RXdata == 0x1)
    {
        pass++;
    }
    else
    {
        fail++;
        ESTOP0;
    }

    RXdata = SPI_read16bits_EEPROM(base, SPI_DATA_LITTLE_ENDIAN, EEPROM_ADDR);

    if(RXdata == 0x0201)
    {
       pass++;
    }
    else
    {
       fail++;
       ESTOP0;
    }

    RXdata = SPI_read16bits_EEPROM(base, SPI_DATA_BIG_ENDIAN, EEPROM_ADDR);

    if(RXdata == 0x0102)
    {
       pass++;
    }
    else
    {
       fail++;
       ESTOP0;
    }

    RXdata = SPI_read24bits_EEPROM(base, SPI_DATA_LITTLE_ENDIAN, EEPROM_ADDR);

    if(RXdata == 0x030201)
    {
       pass++;
    }
    else
    {
       fail++;
       ESTOP0;
    }

    RXdata = SPI_read24bits_EEPROM(base, SPI_DATA_BIG_ENDIAN, EEPROM_ADDR);

    if(RXdata == 0x010203)
    {
       pass++;
    }
    else
    {
       fail++;
       ESTOP0;
    }

    RXdata = SPI_read32bits_EEPROM(base, SPI_DATA_LITTLE_ENDIAN, EEPROM_ADDR);

    if(RXdata == 0x04030201)
    {
       pass++;
    }
    else
    {
       fail++;
       ESTOP0;
    }

    RXdata = SPI_read32bits_EEPROM(base, SPI_DATA_BIG_ENDIAN, EEPROM_ADDR);

    if(RXdata == 0x01020304)
    {
       pass++;
    }
    else
    {
       fail++;
       ESTOP0;
    }

    // Read from the EEPROM
    readData(EEPROM_ADDR, &RXbuff[0], BUFFER_SIZE,NO_DELAY);

    // Check received data for correctness
    for(i = 0; i < BUFFER_SIZE; i++)
    {
        if(TXbuff[i] != RXbuff[i])
        {
            fail++;
        }
    }

    if((pass == 7) && (fail == 0))
    {
       done();
    }
    else
    {
       ESTOP0;
    }

}

void done(void)
{
    while(1);
}
uint16_t SPI_readByte_EEPROM(uint32_t base, uint16_t address)
{
    uint16_t RXdata = 0;

    CS_LOW;

    // Send the READ opcode.
    SPI_transmitByte(base, READ);

    // Send EEPROM address to write data
    SPI_transmit16Bits(base, address);

    // Receive data byte from EEPROM by sending dummy byte
    RXdata = SPI_receiveByte(base, DUMMY_DATA);

    CS_HIGH;

    return(RXdata);
}

uint16_t SPI_read16bits_EEPROM(uint32_t base, SPI_endianess endianness, uint16_t address)
{
    uint16_t RXdata = 0;

    CS_LOW;

    // Send the READ opcode.
    SPI_transmitByte(base, READ);

    // Send EEPROM address to write data
    SPI_transmit16Bits(base, address);

    // Receive data 16-bit word from EEPROM by sending two dummy bytes
    RXdata = SPI_receive16Bits(base, endianness, DUMMY_DATA, NO_DELAY);

    CS_HIGH;

    return RXdata;
}

uint32_t SPI_read24bits_EEPROM(uint32_t base, SPI_endianess endianness, uint16_t address)
{
    uint32_t RXdata = 0;

    CS_LOW;

    // Send the READ opcode.
    SPI_transmitByte(base, READ);

    // Send EEPROM address to write data
    SPI_transmit16Bits(base, address);

    // Receive data 24-bit word from EEPROM by sending three dummy bytes
    RXdata = SPI_receive24Bits(base, endianness, DUMMY_DATA, NO_DELAY);

    CS_HIGH;

    return RXdata;
}

uint32_t SPI_read32bits_EEPROM(uint32_t base, SPI_endianess endianness, uint16_t address)
{
    uint32_t RXdata = 0;

    CS_LOW;

    // Send the READ opcode.
    SPI_transmitByte(base, READ);

    // Send EEPROM address to write data
    SPI_transmit16Bits(base, address);

    // Receive data 32-bit word from EEPROM by sending four dummy bytes
    RXdata = SPI_receive32Bits(base, endianness, DUMMY_DATA, NO_DELAY);

    CS_HIGH;

    return RXdata;
}

//
// Function to send RDSR opcode and return the status of the EEPROM
//
uint16_t readStatusRegister(uint16_t statusRegister)
{
    uint16_t temp;
    uint32_t base = SPIA_BASE;

    // Pull chip select low.
    CS_LOW;

    // Send RDSR opcode
    SPI_transmitByte(base, statusRegister);

    // Send dummy data to read status register.
    temp = SPI_receiveByte(base, 0x0);

    // Pull chip select high.
    CS_HIGH;

    // Read the status from the receive buffer
    return(temp);
}

//
// Function to send the WREN opcode
//
void enableWrite(void)
{
    uint32_t base = SPIA_BASE;
    // Pull chip select low.
    CS_LOW;

    // Send the WREN opcode.
    SPI_transmitByte(base, WREN);

    // Pull chip select high.
    CS_HIGH;
}

//
// Function to write data to the EEPROM
// - address is the byte address of the EEPROM
// - data is a pointer to an array of data being sent
// - length is the number of characters in the array to send
//
void writeData(uint16_t address, uint16_t *data, uint16_t length, uint16_t txdly)
{
    uint32_t base = SPIA_BASE;

    // Pull chip select low.
    CS_LOW;

    // Send the WRITE opcode.
    SPI_transmitByte(base, WRITE);

    // Send EEPROM address to write data
    SPI_transmit16Bits(base, address);

    // Send data to be programmed
    SPI_transmitNBytes(base, data, length, txdly);

    // Pull chip select high.
    CS_HIGH;
}

//
// Function to read data from the EEPROM
// - address is the byte address of the EEPROM
// - data is a pointer to an array of data being received
// - length is the number of characters in the array to receive
//
void readData(uint16_t address, uint16_t *data, uint16_t length, uint16_t txdly)
{
    uint32_t base = SPIA_BASE;

    CS_LOW;

    // Send the READ opcode.
    SPI_transmitByte(base, READ);

    // Send EEPROM address to write data
    SPI_transmit16Bits(base, address);

    // Receive length number of bytes
    SPI_receiveNBytes(base, data, length, txdly);


    CS_HIGH;
}

//
// End of File
//

