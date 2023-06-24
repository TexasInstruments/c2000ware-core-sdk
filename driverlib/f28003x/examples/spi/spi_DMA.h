//#############################################################################
//
// FILE:   spi_DMA.h
//
// TITLE:  C28x-SPI header file when using DMA with SPI
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
#include<stdarg.h>
#include "driverlib.h"
#include "device.h"

#include "board.h"

#ifndef SPI_DMA_H
#define SPI_DMA_H

//
// Defines
//
#define EEPROM_ADDR                 0x0000

#define FIFO_LVL    16       // FIFO interrupt level
#define BURST       16        // 16 words / burst
#define TRANSFER    1        // 4 burts / transfer


#define NULL ((void *)0x0)

//
// Defines for Chip Select toggle.
//
#define CS_LOW                      GPIO_writePin(SPI_CS_GPIO, 0)
#define CS_HIGH                     GPIO_writePin(SPI_CS_GPIO, 1)

typedef enum
{
    SPI_DMA_TRANSACTION_IDLE     = 0x0000,
    SPI_DMA_TRANSACTION_STARTED  = 0x0BAD,
    SPI_DMA_TRANSACTION_COMPLETE = 0x55AA,
}SPI_TransactionStatus;

typedef enum
{
    SPI_DMA_WRITE_ENABLE         = 0x0000,
    SPI_DMA_READ_STATUS_REGISTER = 0x0001,
    SPI_DMA_WRITE_TRANSACTION    = 0x0002,
    SPI_DMA_READ_TRANSACTION     = 0x0003,
}SPI_TransactionType;

#define BUFFER_SIZE 64

#define DUMMY_DATA 0xFF
#define NO_DELAY   0


extern uint16_t DMATXbuff[BUFFER_SIZE];
extern uint16_t DMARXbuff[BUFFER_SIZE];

extern struct DMA_CH SPITXDMA;
extern struct DMA_CH SPIRXDMA;

struct DMA_CH
{
    uint32_t dmach;
    uint16_t *pbuffer;
    uint16_t currentpointer;
    uint16_t maxTransactionSize;
};


typedef void (*functionPointer)(void);

struct SPI_DMA_handle
{
    uint32_t spibase;                       //Specifies SPI base address
    uint16_t charlength;                    //Specifies SPI character length
    struct DMA_CH *pSPITXDMA;               //Pointer to SPITXDMA
    struct DMA_CH *pSPIRXDMA;               //Pointer to SPIRXDMA


    functionPointer pFunction[5U];          //Array of function pointer which executes
                                            //different command sequence
    uint16_t FunctionCount;                 //Counter which specifies which function
                                            //command sequence
    SPI_TransactionType TransactionType;    //Stores the type of EEPROM transaction
    SPI_TransactionStatus TransactionStatus;//Stores the status of SPI transaction

    uint16_t expectedOutput;                //Output expected from EEPROM
    uint16_t offsetRXbuff;                  //Offset pointer for RXbuffer
    uint32_t RXdata;                        //Stores received data
    SPI_endianess endianess;                //Stores endianess of transaction
};

struct EEPROM_Transaction
{
    uint16_t EEPROMAddress;
    uint16_t numofBytes;
    uint16_t *pbuff;
};

extern struct SPI_DMA_handle SPI_DMA_Handle;
extern struct EEPROM_Transaction EEPROM_Transaction;


//*****************************************************************************
//! This macro can be used to fill up the transmit buffer to transmit a byte.
//!
//! \param data   specifies the data to be transmitted
//! \param pSPI_DMA_Handle specifies SPI / DMA transaction parameters
//!
//! \return None.
//
//*****************************************************************************
#define SPI_DMA_TransmitByte(data, pSPI_DMA_Handle)  SPI_DMA_ByteTransaction(data, pSPI_DMA_Handle)

//*****************************************************************************
//! This macro can be used to fill up the transmit buffer to transmit 16-bits
//!
//! \param data   specifies the data to be transmitted
//! \param pSPI_DMA_Handle specifies SPI / DMA transaction parameters
//!
//! \return None.
//
//*****************************************************************************
#define SPI_DMA_Transmit16bitWord(data, pSPI_DMA_Handle) SPI_DMA_16bitWordTransaction(data, pSPI_DMA_Handle)

//*****************************************************************************
//! This macro can be used to fill up the transmit buffer to transmit N-bytes
//!
//! \param pTXbuffer   specifies the start address of transmit buffer
//! \param numOfbytes  specifies the number of bytes to be transmitted
//! \param pSPI_DMA_Handle specifies SPI / DMA transaction parameters
//!
//! \return None.
//
//*****************************************************************************
#define SPI_DMA_Transmit_NBytes(pTXbuffer, numOfbytes, pSPI_DMA_Handle) SPI_DMA_NBytesTransaction(pTXbuffer, numOfbytes, pSPI_DMA_Handle)

#define SPI_DMA_ReceiveByte(dummyData, pSPI_DMA_Handle)      SPI_DMA_ByteTransaction(dummyData, pSPI_DMA_Handle)
#define SPI_DMA_Receive16bitWord(dummydata, pSPI_DMA_Handle) SPI_DMA_16bitWordTransaction(dummydata, pSPI_DMA_Handle)

//*****************************************************************************
//! This macro can be used to receive N-bytes
//!
//! \param numOfbytes  specifies the number of bytes to be transmitted
//! \param pSPI_DMA_Handle specifies SPI / DMA transaction parameters
//!
//! \return None.
//
//*****************************************************************************
#define SPI_DMA_Receive_NBytes(numOfbytes, pSPI_DMA_Handle)   SPI_DMA_NBytesTransaction(NULL, numOfbytes, pSPI_DMA_Handle)


extern void SPI_DMA_ByteTransaction(uint16_t data, struct SPI_DMA_handle *pSPI_DMA_Handle);
extern void SPI_DMA_16bitWordTransaction(uint16_t data, struct SPI_DMA_handle *pSPI_DMA_Handle);

//*****************************************************************************
//! This function can be used to configure SPI_DMA_Handle structure
//!
//! \param spibase    specifies the SPI module base address.
//! \param endianess  specifies whether endianess of received data
//! \param charlength specifies character length of SPI transaction
//! \param dmaTXbase  specifies the DMA base address to act DMA TX channel
//! \param dmaRXbase  specifies the DMA base address to act DMA RX channel
//!
//! SPI_DMA_Handle configuration made by this function are:
//!    1) SPI module, DMA TX / RX channel
//!    2) Reset current pointer for TX / RX transaction
//!    3) Configure TXbuff and RXbuff
//!
//! \return None.
//
//*****************************************************************************
void setupSPI_DMA_Handler(uint32_t spibase, uint16_t charlength, uint32_t dmaTXbase, uint32_t dmaRXbase);

//*****************************************************************************
//! This function configures DMA / SPI based on pSPI_DMA_Handle and starts
//! SPI transaction using DMA
//!
//! \param pSPI_DMA_Handle specifies the SPI module base address.
//! \param charLength specifies the SPI character length
//! \param txDelay specifies the number of serial clock cycles delay time after
//!        completion of perious word
//!
//! \return None.
//
//*****************************************************************************
extern void SPI_DMA_StartTransaction(struct SPI_DMA_handle *pSPI_DMA_Handle, uint16_t charlength, uint16_t txdly);
extern void SPI_DMA_NBytesTransaction(uint16_t *pTXbuffer, uint16_t numOfbytes, struct SPI_DMA_handle *pSPI_DMA_Handle);
extern uint32_t selectDMA_PIE_Interrupt(uint32_t dmabase);

extern void RunCommandSequence(functionPointer *pFunction);

__interrupt void dmaTXISR(void);
__interrupt void dmaRXISR(void);

#endif
