//#############################################################################
//
// FILE:   spi_DMA.c
//
// TITLE:  C28x-SPI source file when using DMA with SPI
// <h1> C28x-SPI source file when using DMA with SPI </h1>
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

//Global variables
uint16_t DMATXbuff[BUFFER_SIZE];
uint16_t DMARXbuff[BUFFER_SIZE];

#pragma DATA_SECTION(DMATXbuff, "ramgs0");  // map the TX data to memory
#pragma DATA_SECTION(DMARXbuff, "ramgs0");  // map the RX data to memory

struct SPI_DMA_handle SPI_DMA_Handle;

struct DMA_CH SPITXDMA;
struct DMA_CH SPIRXDMA;


void SPI_DMA_ByteTransaction(uint16_t data, struct SPI_DMA_handle *pSPI_DMA_Handle)
{
    //wordSize for a byte is 8 (because 1 byte = 8 bits)
    uint16_t wordSize = 8U;
    ASSERT(data < (1<<wordSize));

    //Fill the TXbuffer with data to be transmitted
    uint16_t *pbuffer       = pSPI_DMA_Handle->pSPITXDMA->pbuffer;
    uint16_t currentpointer = pSPI_DMA_Handle->pSPITXDMA->currentpointer;

    pbuffer[currentpointer++] = data;

    pSPI_DMA_Handle->pSPITXDMA->currentpointer = currentpointer;
}


void SPI_DMA_NBytesTransaction(uint16_t *pTXbuffer, uint16_t numOfbytes, struct SPI_DMA_handle *pSPI_DMA_Handle)
{
    uint16_t *pbuffer       = pSPI_DMA_Handle->pSPITXDMA->pbuffer;
    uint16_t currentpointer = pSPI_DMA_Handle->pSPITXDMA->currentpointer;

    uint16_t i=0;
    for(i=0;i<numOfbytes;i++)
    {
        if(pTXbuffer == NULL)
        {
            //Fill the TXbuffer with dummy data to be transmitted
            //Here the dummy data is 0xFFFF
            pbuffer[currentpointer++] = 0xFFFF;
        }
        else
        {
            //Fill the TXbuffer
            pbuffer[currentpointer++] = pTXbuffer[i];
        }
    }

    pSPI_DMA_Handle->pSPITXDMA->currentpointer = currentpointer;
}

void SPI_DMA_16bitWordTransaction(uint16_t data, struct SPI_DMA_handle *pSPI_DMA_Handle)
{
    //wordSize is 16
    uint16_t wordSize = 16U;
    ASSERT(data < ((uint32_t)1<<wordSize));

    //Fill the TXbuffer with data to be transmitted
    uint16_t *pbuffer       = pSPI_DMA_Handle->pSPITXDMA->pbuffer;
    uint16_t currentpointer = pSPI_DMA_Handle->pSPITXDMA->currentpointer;

    pbuffer[currentpointer++] = (data & 0xFF00) >> 8;
    pbuffer[currentpointer++] = (data & 0xFF);

    pSPI_DMA_Handle->pSPITXDMA->currentpointer = currentpointer;
}

void SPI_DMA_24bitWordTransaction(uint32_t data, struct SPI_DMA_handle *pSPI_DMA_Handle)
{
    //wordSize is 24
    uint16_t wordSize = 24U;
    ASSERT(data < ((uint32_t)1<<wordSize));

    //Fill the TXbuffer with data to be transmitted
    uint16_t *pbuffer       = pSPI_DMA_Handle->pSPITXDMA->pbuffer;
    uint16_t currentpointer = pSPI_DMA_Handle->pSPITXDMA->currentpointer;

    pbuffer[currentpointer++]  = (data & 0xFF0000) >> 16U;
    pbuffer[currentpointer++]  = (data & 0x00FF00) >> 8U;
    pbuffer[currentpointer++]  = (data & 0x0000FF);

    pSPI_DMA_Handle->pSPITXDMA->currentpointer = currentpointer;
}

void SPI_DMA_StartTransaction(struct SPI_DMA_handle *pSPI_DMA_Handle, uint16_t charlength, uint16_t txdly)
{
    uint16_t i = 0;
    ASSERT((charlength >= 1U) && (charlength <= 16U));

    pSPI_DMA_Handle->TransactionStatus = SPI_DMA_TRANSACTION_STARTED;

    uint32_t spibase        = pSPI_DMA_Handle->spibase;
    uint32_t dmaTXbase      = pSPI_DMA_Handle->pSPITXDMA->dmach;
    uint32_t dmaRXbase      = pSPI_DMA_Handle->pSPIRXDMA->dmach;
    uint16_t *pTXbuffer     = pSPI_DMA_Handle->pSPITXDMA->pbuffer;
    uint16_t *pRXbuffer     = pSPI_DMA_Handle->pSPIRXDMA->pbuffer;
    uint16_t currentpointer = pSPI_DMA_Handle->pSPITXDMA->currentpointer;

    ASSERT(SPI_isBaseValid(spibase));

    uint16_t maxTransactionSize = currentpointer;
    pSPI_DMA_Handle->pSPITXDMA->maxTransactionSize =  maxTransactionSize;

/********************************************************************************/
// SPI configuration
/********************************************************************************/

    SPI_setcharLength(spibase, charlength);

    uint16_t TXbuff_pos = 0;

    for(i=1;i<=maxTransactionSize;i++)
    {
        pTXbuffer[TXbuff_pos] = pTXbuffer[TXbuff_pos] << (16 - charlength);

        TXbuff_pos++;
    }

    //Reset the TX / RX FIFO buffers to default state
    SPI_disableFIFO(spibase); //Disable FIFO register
    SPI_enableFIFO(spibase);  //Enable FIFO register

    //Configure the FIFO Transmit Delay
    SPI_setTxFifoTransmitDelay(spibase, txdly);

    uint16_t burst_size = 0;
    uint16_t transfer_size = 1;

    //Determine the number of 16-level words from number of words to be transmitted / received
    uint16_t numofSixteenWords = maxTransactionSize / SPI_FIFO_TXFULL;
    //Determine the number of remaining words from number of words to be transmitted / received
    uint16_t remainingWords    = maxTransactionSize % SPI_FIFO_TXFULL;

    if(numofSixteenWords)
    {
        SPI_setFIFOInterruptLevel(spibase, SPI_FIFO_TXEMPTY, SPI_FIFO_RXFULL);
        burst_size      = 16U;
        transfer_size   = numofSixteenWords;
    }
    else
    {
        SPI_setFIFOInterruptLevel(spibase, SPI_FIFO_TXEMPTY, (SPI_RxFIFOLevel)remainingWords);
        burst_size      = remainingWords;
        transfer_size   = 1;
    }

    SPI_enableInterrupt(spibase, SPI_INT_RXFF);

    // Initialize DMA
    DMA_initController();

/********************************************************************************/
// DMA TX Channel configuration
/********************************************************************************/
    ASSERT(DMA_isBaseValid(dmaTXbase));

    uint32_t dmaTX_IntNum = selectDMA_PIE_Interrupt(dmaTXbase);
    Interrupt_register(dmaTX_IntNum, &dmaTXISR);

    uint16_t *psrcAddr  = pTXbuffer;
    uint16_t *pdestAddr = (uint16_t *)(spibase + SPI_O_TXBUF);

    DMA_configAddresses(dmaTXbase, pdestAddr, psrcAddr);
    DMA_configBurst(dmaTXbase, burst_size, 1, 0);
    DMA_configTransfer(dmaTXbase, transfer_size, 1, 0);
    DMA_configMode(dmaTXbase, DMA_TRIGGER_SOFTWARE, DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_ENABLE |
                                                  DMA_CFG_SIZE_16BIT);


    DMA_setEmulationMode(DMA_EMULATION_FREE_RUN);

    // DMA SW trigger to start SPI transaction using DMA
    DMA_enableTrigger(dmaTXbase);

/********************************************************************************/
// DMA RX Channel configuration
/********************************************************************************/
    ASSERT(DMA_isBaseValid(dmaRXbase));

    uint32_t dmaRX_IntNum = selectDMA_PIE_Interrupt(dmaRXbase);
    Interrupt_register(dmaRX_IntNum, &dmaRXISR);

    psrcAddr  = (uint16_t *)(spibase + SPI_O_RXBUF);
    pdestAddr = pRXbuffer;

    //Enable RXFIFO interrupt to ensure DMA RX channel is triggered
    SPI_enableInterrupt(spibase, SPI_INT_RXFF);

    DMA_configAddresses(dmaRXbase, pdestAddr, psrcAddr);
    DMA_configBurst(dmaRXbase, BURST, 0, 1);
    DMA_configTransfer(dmaRXbase, TRANSFER, 0, 1);
    DMA_configMode(dmaRXbase, DMA_TRIGGER_SPIARX, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA RX interrupts
    //
    DMA_setInterruptMode(dmaRXbase, DMA_INT_AT_END);
    DMA_enableInterrupt(dmaRXbase);
    DMA_enableTrigger(dmaRXbase);


    pSPI_DMA_Handle->pSPITXDMA->currentpointer  = burst_size;
    pSPI_DMA_Handle->pSPIRXDMA->currentpointer  = burst_size;

    //Chip select pulled LOW
    CS_LOW;
    //DMA SW trigger to initiate SPI transaction
    DMA_forceTrigger(dmaTXbase);

}

//
// Function used to select correct dma channel based base address provided
//
uint32_t selectDMA_PIE_Interrupt(uint32_t dmachbase)
{

    uint32_t DMA_Channel = 0;

    switch(dmachbase)
    {
        case DMA_CH1_BASE:
            DMA_startChannel(DMA_CH1_BASE);
            DMA_Channel = INT_DMA_CH1;
            Interrupt_enable(DMA_Channel);
            break;

        case DMA_CH2_BASE:
            DMA_startChannel(DMA_CH2_BASE);
            DMA_Channel = INT_DMA_CH2;
            Interrupt_enable(DMA_Channel);
            break;

        case DMA_CH3_BASE:
            DMA_startChannel(DMA_CH3_BASE);
            DMA_Channel = INT_DMA_CH3;
            Interrupt_enable(DMA_Channel);
            break;

        case DMA_CH4_BASE:
            DMA_startChannel(DMA_CH4_BASE);
            DMA_Channel = INT_DMA_CH4;
            Interrupt_enable(DMA_Channel);
            break;

        case DMA_CH5_BASE:
            DMA_startChannel(DMA_CH5_BASE);
            DMA_Channel = INT_DMA_CH5;
            Interrupt_enable(DMA_Channel);
            break;

        case DMA_CH6_BASE:
            DMA_startChannel(DMA_CH6_BASE);
            DMA_Channel = INT_DMA_CH6;
            Interrupt_enable(DMA_Channel);
            break;
    }

    return(DMA_Channel);
}

//
// DMA TX ISR
// Not used in this example.
//
__interrupt void dmaTXISR(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    return;
}

//
// DMA RX ISR
//
 __interrupt void dmaRXISR(void)
{
    uint32_t spibase        = SPI_DMA_Handle.spibase;
    uint32_t dmaTXbase      = SPI_DMA_Handle.pSPITXDMA->dmach;
    uint32_t dmaRXbase      = SPI_DMA_Handle.pSPIRXDMA->dmach;

    uint16_t remainingWords = SPI_DMA_Handle.pSPITXDMA->maxTransactionSize - SPI_DMA_Handle.pSPITXDMA->currentpointer;

    uint16_t burst_size = 0;

    uint16_t srcAddr  = HWREGH(dmaTXbase + DMA_O_SRC_ADDR_ACTIVE);
    uint16_t destAddr = HWREGH(dmaRXbase + DMA_O_DST_ADDR_ACTIVE);

    DMA_configSourceAddress(dmaTXbase, (const void *)srcAddr);
    DMA_configDestAddress(dmaRXbase, (const void *)destAddr);

    //If the remainingWords is non-zero and less than FIFO level (16U), then reconfigure
    //DMA burst and RX FIFO level
    if(remainingWords > 0 && remainingWords < 16)
    {
        burst_size = remainingWords;
        SPI_DMA_Handle.pSPITXDMA->currentpointer += remainingWords;

        SPI_setFIFOInterruptLevel(spibase, SPI_FIFO_TXEMPTY, (SPI_RxFIFOLevel)remainingWords);
        DMA_configBurst(dmaTXbase, burst_size, 1, 0);
        DMA_configBurst(dmaRXbase, burst_size, 0, 1);

    }
    if(remainingWords >= 16)
    {
        SPI_DMA_Handle.pSPITXDMA->currentpointer += 16U;
    }
    //If no remainingWords, pull chip select high and stop DMA CH6
    if(remainingWords == 0)
    {
        CS_HIGH; //Chip select pulled high

        //Reset currentpointer for both TX / RX
        SPI_DMA_Handle.pSPITXDMA->currentpointer     = 0;
        SPI_DMA_Handle.pSPIRXDMA->currentpointer     = 0;

        //Stop both TX / RX DMA channels
        DMA_stopChannel(dmaTXbase);
        DMA_stopChannel(dmaRXbase);

        //Increment function pointer to execute next function
        SPI_DMA_Handle.FunctionCount++;
        if(SPI_DMA_Handle.TransactionType == SPI_DMA_READ_STATUS_REGISTER)
        {
            //Execute the same function until we received expected output
            if(SPI_DMA_Handle.pSPIRXDMA->pbuffer[SPI_DMA_Handle.offsetRXbuff] != SPI_DMA_Handle.expectedOutput)
            {
                SPI_DMA_Handle.FunctionCount--;
            }
        }

        if(SPI_DMA_Handle.TransactionType == SPI_DMA_READ_TRANSACTION)
        {
            uint16_t numRXbytes = SPI_DMA_Handle.pSPITXDMA->maxTransactionSize - SPI_DMA_Handle.offsetRXbuff;

            int16_t i = numRXbytes-1;
            uint16_t *pReceiveBuffer = SPI_DMA_Handle.pSPIRXDMA->pbuffer + SPI_DMA_Handle.offsetRXbuff;
            SPI_DMA_Handle.pSPIRXDMA->pbuffer = pReceiveBuffer;

            //When the number of RXbytes is less than 4
            //package data into RX data based on endianess
            while(i>=0 && numRXbytes<=4)
            {
                if(SPI_DMA_Handle.endianess == SPI_DATA_BIG_ENDIAN)
                {
                    SPI_DMA_Handle.RXdata |= (uint32_t)pReceiveBuffer[i] << (i * SPI_DMA_Handle.charlength);
                }
                else
                {
                    SPI_DMA_Handle.RXdata |= (uint32_t)pReceiveBuffer[numRXbytes-i-1] << (i * SPI_DMA_Handle.charlength);
                }
                i--;
            }
        }

        //If function pointer in not equal to NULL.
        //Execute next function
        if(SPI_DMA_Handle.pFunction[SPI_DMA_Handle.FunctionCount] != NULL)
        {
            SPI_DMA_Handle.pFunction[SPI_DMA_Handle.FunctionCount]();
        }
        else
        {
            SPI_DMA_Handle.TransactionStatus = SPI_DMA_TRANSACTION_COMPLETE;
        }
    }
    else
    {   //We still have remaining transactions
        DMA_forceTrigger(dmaTXbase);
    }

    //Acknowledge CPU interrupt flag
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    return;
}

//
// Function used to update SPI_DMA_Handle function pointer
// and start executing first function in function pointer array
//
void RunCommandSequence(functionPointer *pFunction)
{
     SPI_DMA_Handle.FunctionCount     = 0;

     uint16_t i;
     //Fill function pointer array in SPI_DMA_Handle
     for(i=0;i<5U;i++)
     {
         SPI_DMA_Handle.pFunction[i]   = *pFunction[i];
     }

     //Execute the first function in function pointer array
     SPI_DMA_Handle.pFunction[0]();
}

//
// Function used to update SPI_DMA_Handle parameters
//
void setupSPI_DMA_Handler(uint32_t spibase, uint16_t charlength, uint32_t dmaTXbase, uint32_t dmaRXbase)
{

///////////////////////////////////////////
//  SPI configuration   //
///////////////////////////////////////////
      SPI_DMA_Handle.spibase    = spibase;
      SPI_DMA_Handle.charlength = charlength;
      SPI_DMA_Handle.pSPITXDMA  = &SPITXDMA;
      SPI_DMA_Handle.pSPIRXDMA  = &SPIRXDMA;

 ///////////////////////////////////////////
 //  DMA Transmit channel configuration   //
 ///////////////////////////////////////////
     SPITXDMA.dmach          = dmaTXbase;
     SPITXDMA.pbuffer        = &DMATXbuff[0];
     SPITXDMA.currentpointer = 0;

 ///////////////////////////////////////////
 //  DMA Receive channel configuration    //
 ///////////////////////////////////////////
     SPIRXDMA.dmach          = dmaRXbase;
     SPIRXDMA.pbuffer        = &DMARXbuff[0];
     SPIRXDMA.currentpointer = 0;
}



