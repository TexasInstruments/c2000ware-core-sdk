//#############################################################################
//
// FILE:   spi_ex7_eeprom_dma.c
//
// TITLE:  SPI DMA EEPROM
//
//! \addtogroup driver_example_list
//! <h1>SPI DMA EEPROM</h1>
//!
//! This program will write 8 bytes to EEPROM and read them back. The device
//! communicates with the EEPROM via SPI using DMA and specific opcodes. This example is
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
//!  - SPI_DMA_Handle.RXdata  - Data that is read back from EEPROM
//!                             when number of received bytes is
//!                             less than 4
//!  - SPI_DMA_Handle.pSPIRXDMA->pbuffer - Start address of received data
//!                                        from EEPROM
//!  - error       - Error count
//!
//
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

#include "spi_DMA.h"

//
// Defines
// SPI EEPROM status
//
#define MSG_STATUS_READY_M          0x0000 // EEPROM is ready (not busy)
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
// Globals
//
struct EEPROM_Transaction EEPROM_Transaction;

//
// Function Prototypes
//
void initDMA(void);

void EEPROM_writeTransaction(uint16_t eepromAddr, uint16_t *pbuffer, uint16_t numofBytes);
void EEPROM_readTransaction(uint16_t eepromAddr, uint16_t numofBytes);

void sendWriteEnable(void);
void readStatusRegister(uint16_t statusRegister, struct SPI_DMA_handle *pSPI_DMA_Handle);

void waitforWriteReady(void);
void waitforReadReady(void);
void writeEEPROM(void);
void readEEPROM(void);

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

    Board_init();

    //Clear TX / RX buffer used by DMA
    for(i=0; i<BUFFER_SIZE;i++)
    {
       DMATXbuff[i] = 0;
       DMARXbuff[i] = 0;
    }

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

//////////////////////////////////////////////////////
//  1) Using SPIA for transaction
//  2) DMA Transmit channel  = DMA channel 3
//  3) DMA Receive channel   = DMA channel 4
//////////////////////////////////////////////////////
    setupSPI_DMA_Handler(SPI_EEPROM_BASE, 8U, DMA_CH3_BASE, DMA_CH4_BASE);

    uint16_t eepromAddr = 0x0;
    uint16_t writeBuffer[BUFFER_SIZE];

    for(i=0;i<BUFFER_SIZE;i++)
    {
        writeBuffer[i] = i;
    }

    EEPROM_writeTransaction(eepromAddr, &writeBuffer[0], BUFFER_SIZE);

    //Wait for TransactionStatus to be set to SPI_DMA_TRANSACTION_COMPLETE
    while(SPI_DMA_Handle.TransactionStatus != SPI_DMA_TRANSACTION_COMPLETE);

    ESTOP0;

    EEPROM_readTransaction(eepromAddr, 4U);

    //Wait for TransactionStatus to be set to SPI_DMA_TRANSACTION_COMPLETE
    while(SPI_DMA_Handle.TransactionStatus != SPI_DMA_TRANSACTION_COMPLETE);

    //Number of received bytes <= 4,
    //So, RXdata will contain received data
    //Receive data is also available in with start address pointed by
    //SPI_DMA_Handle.pSPIRXDMA->pbuffer
    ESTOP0;

    EEPROM_readTransaction(eepromAddr, BUFFER_SIZE);

    //Wait for TransactionStatus to be set to SPI_DMA_TRANSACTION_COMPLETE
    while(SPI_DMA_Handle.TransactionStatus != SPI_DMA_TRANSACTION_COMPLETE);

    //Number of received bytes > 4,
    //So, RXdata will not contain any data
    //Receive data is also available in with start address pointed by
    //SPI_DMA_Handle.pSPIRXDMA->pbuffer
    ESTOP0;

    uint16_t error = 0;
    for(i=0;i<BUFFER_SIZE;i++)
    {
        if(writeBuffer[i] != SPI_DMA_Handle.pSPIRXDMA->pbuffer[i])
        {
            //Data written into EEPROM doesn't match with
            //data read from EEPROM
            error++;
            ESTOP0;
        }
    }

    while(1);
}


void EEPROM_writeTransaction(uint16_t eepromAddr, uint16_t *pbuffer, uint16_t numofBytes)
{

    CS_HIGH;
    //EEPROM address
    EEPROM_Transaction.EEPROMAddress = eepromAddr;
    //Number of bytes to be programmed
    EEPROM_Transaction.numofBytes    = numofBytes;
    //Start address of data array to be programmed
    EEPROM_Transaction.pbuff         = pbuffer;

    functionPointer pFunction[5U];

//////////////////////////////////////////////////////
//  1) Send Write Enable to EEPROM
//  2) Read EEPROM Read Status Register (RDSR) and
//     wait till EEPROM is ready to be written
//  3) Write to EEPROM using TXbuff
//////////////////////////////////////////////////////
    pFunction[0] = sendWriteEnable;     //1st function to be executed
    pFunction[1] = waitforWriteReady;   //2nd function to be executed
    pFunction[2] = writeEEPROM;         //3rd function to be executed
    pFunction[3] = NULL;                //NULL function
    pFunction[4] = NULL;                //NULL function

    //Start DMA - SPI transaction mentioned in function pointer array
    //1) Execute sendWriteEnable function
    //2) Execute waitforWriteReady function
    //3) Execute writeEEPROM function
    RunCommandSequence(pFunction);
}

void EEPROM_readTransaction(uint16_t eepromAddr, uint16_t numofBytes)
{
    CS_HIGH;
    //EEPROM address
    EEPROM_Transaction.EEPROMAddress = eepromAddr;
    //Number of bytes to be programmed
    EEPROM_Transaction.numofBytes    = numofBytes;

    //Reset RXbuff pointer to default value
    SPI_DMA_Handle.pSPIRXDMA->pbuffer = &DMARXbuff[0];
    SPI_DMA_Handle.RXdata = 0;

    functionPointer pFunction[5U];

//////////////////////////////////////////////////////
//  1) Read EEPROM Read Status Register (RDSR) and
//     wait till EEPROM is ready to be read
//  2) Read EEPROM and store in RXbuff
//////////////////////////////////////////////////////
    pFunction[0] = waitforReadReady;    //1st function to be executed
    pFunction[1] = readEEPROM;          //2nd function to be executed
    pFunction[2] = NULL;                //NULL function
    pFunction[3] = NULL;                //NULL function
    pFunction[4] = NULL;                //NULL function

    //Start DMA - SPI transaction mentioned in function pointer array
    //1) Execute waitforReadReady function
    //2) Execute readEEPROM function
    RunCommandSequence(pFunction);
}

//
// Function to send the WREN opcode
//
void sendWriteEnable(void)
{
    SPI_DMA_Handle.TransactionStatus  = SPI_DMA_TRANSACTION_STARTED;
    SPI_DMA_Handle.TransactionType    = SPI_DMA_WRITE_ENABLE;

    // Send the WREN opcode.
    SPI_DMA_TransmitByte(WREN, &SPI_DMA_Handle);

    // Start SPI-DMA transaction
    SPI_DMA_StartTransaction(&SPI_DMA_Handle, SPI_DMA_Handle.charlength, NO_DELAY);
}

//
// Function to read status register and wait for EEPROM
// to be ready to write operation
//
void waitforWriteReady(void)
{
    SPI_DMA_Handle.TransactionStatus  = SPI_DMA_TRANSACTION_STARTED;
    SPI_DMA_Handle.TransactionType  = SPI_DMA_READ_STATUS_REGISTER;
    SPI_DMA_Handle.expectedOutput   = MSG_STATUS_WRITE_READY_M;

    //Read EEPROM Read Status register to check write ready bit
    readStatusRegister(RDSR, &SPI_DMA_Handle);
}

//
// Function to read status register and wait for EEPROM
// to be ready to read operation
//
void waitforReadReady(void)
{
    SPI_DMA_Handle.TransactionStatus  = SPI_DMA_TRANSACTION_STARTED;
    SPI_DMA_Handle.TransactionType = SPI_DMA_READ_STATUS_REGISTER;
    SPI_DMA_Handle.expectedOutput  = MSG_STATUS_READY_M;

    //Read EEPROM Read Status register to check read ready bit
    readStatusRegister(RDSR, &SPI_DMA_Handle);
}

//
// Function used to write to EEPROM using transmit buffer
//
void writeEEPROM(void)
{
    SPI_DMA_Handle.TransactionStatus  = SPI_DMA_TRANSACTION_STARTED;
    SPI_DMA_Handle.TransactionType = SPI_DMA_WRITE_TRANSACTION;

    uint16_t address    = EEPROM_Transaction.EEPROMAddress;
    uint16_t numOfbytes = EEPROM_Transaction.numofBytes;
    uint16_t *pdata     = EEPROM_Transaction.pbuff;


    // Send the WRITE opcode.
    SPI_DMA_TransmitByte(WRITE, &SPI_DMA_Handle);

    // Send EEPROM address to write data
    SPI_DMA_Transmit16bitWord(address, &SPI_DMA_Handle);

    // Send data to be programmed
    SPI_DMA_Transmit_NBytes(pdata, numOfbytes, &SPI_DMA_Handle);

    // Configure SPI / DMA and initiate SPI transaction
    SPI_DMA_StartTransaction(&SPI_DMA_Handle, SPI_DMA_Handle.charlength, NO_DELAY);
}



//
// Function used to read to EEPROM
// Receive buffer pointer stored in SPI_DMA_Handle.pSPIRXDMA->pbuffer
//
void readEEPROM(void)
{
    uint16_t counter = 0;

    SPI_DMA_Handle.TransactionStatus  = SPI_DMA_TRANSACTION_STARTED;
    SPI_DMA_Handle.TransactionType = SPI_DMA_READ_TRANSACTION;

    SPI_DMA_Handle.endianess = SPI_DATA_BIG_ENDIAN;

    uint16_t address    = EEPROM_Transaction.EEPROMAddress;
    uint16_t numOfbytes = EEPROM_Transaction.numofBytes;

    // Send the READ opcode.
    SPI_DMA_TransmitByte(READ, &SPI_DMA_Handle); counter++;

    // Send EEPROM address to write data
    SPI_DMA_Transmit16bitWord(address, &SPI_DMA_Handle); counter+=2;

    SPI_DMA_Handle.offsetRXbuff = counter;

    // Receive length number of bytes
    SPI_DMA_Receive_NBytes(numOfbytes, &SPI_DMA_Handle);

    // Configure SPI / DMA and initiate SPI transaction
    SPI_DMA_StartTransaction(&SPI_DMA_Handle, SPI_DMA_Handle.charlength, NO_DELAY);
}

//
// Function to send RDSR opcode and return the status of the EEPROM
//
void readStatusRegister(uint16_t statusRegister, struct SPI_DMA_handle *pSPI_DMA_Handle)
{
    uint16_t counter = 0;

    // Send RDSR opcode
    SPI_DMA_TransmitByte(statusRegister, pSPI_DMA_Handle); counter++;

    // Send dummy data to read status register.
    SPI_DMA_ReceiveByte(DUMMY_DATA, pSPI_DMA_Handle); counter++;

    // Configure SPI / DMA and initiate SPI transaction
    SPI_DMA_StartTransaction(pSPI_DMA_Handle, pSPI_DMA_Handle->charlength, NO_DELAY);

    // offset RXbuffer correction
    pSPI_DMA_Handle->offsetRXbuff = counter-1;

}


