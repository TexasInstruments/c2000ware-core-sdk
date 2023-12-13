//#############################################################################
//
// FILE:   uart_ex4_loopback_dma.c
//
// TITLE:  UART Digital Loopback with DMA
//
//! \addtogroup driver_example_list
//! <h1>UART Digital Loopback with DMA</h1>
//!
//! This program uses the internal loopback test mode of the UART module. Two
//! DMA interrupts and both of the UART FIFOs are used. Both DMA channels are
//! configured to transfer BUFFER_SIZE words with each burst being
//! UART_BUFFER_SIZE words.
//! Note: Only the lower 8 bits of each word will be transmitted and received
//! by the UART since the UART data register only has an 8 bit data field.
//!
//! When the UART transmit FIFO has enough space (UART_BUFFER_SIZE bytes
//! empty), the TX DMA will transfer data from the txData buffer in GSRAM
//! memory into the transmit FIFO by writing to the UART data register. The
//! data in the transmit FIFO will then be transmitted to the receive FIFO via
//! the internal loopback.
//!
//! When enough data has been placed in the receive FIFO (UART_BUFFER_SIZE data
//! bytes full), the RX DMA will transfer the data from the receive FIFO into
//! the rxData buffer in GSRAM memory by reading the UART data register.
//!
//! When BUFFER_SIZE words have been placed into rxData, a check of the
//! validity of the data will be performed and the errCount variable will
//! indicate the amount of data mismatches between txData and rxData.
//!
//!
//! \b Running \b the \b Application
//!
//! Set BUFFER_SIZE to desired words of data to transfer. This value must be
//! even numbered. Set UART_BUFFER_SIZE to 2, 4, or 8. This value must divide
//! evenly into the chosen BUFFER_SIZE.
//!
//! \b External \b Connections \b (Optional)\n
//!  - Connect UARTA_TX and UARTA_RX for external loopback.
//!    Comment out line below ENABLE_LOOPBACK_MODE
//!  - UARTA_TX is on GPIO84
//!  - UARTA_RX is on GPIO85
//!
//! \b Watch \b Variables \n
//!  - \b txData   - Data transmitted
//!  - \b rxData   - Data received
//!  - \b errCount - Error count
//!
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#include <stdint.h>
#include <stdbool.h>

#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// DMA data sections
//

//
// Map the TX data buffer to DMA accessible global shared memory.
//
#pragma DATA_SECTION(txData, "ramgs0");

//
// Map the RX data buffer to DMA accessible global shared memory.
//
#pragma DATA_SECTION(rxData, "ramgs1");

//
// Defines
//

//
// Set amount of data words to transfer from TxData to RxData.
// Must be divisible by UART_BUFFER_SIZE and even numbered.
//
#define BUFFER_SIZE      32

//
// Amount of data words that will trigger UART FIFOs.
// For the 16 byte deep UART FIFOs: set to 2, 4, or 8.
//
#define UART_BUFFER_SIZE  2

//
// Globals
//

//
// BUFFER_SIZE elements stored in memory to be transmitted by UART.
// Each element is stored as a 16-bit value, however only the lower 8 bits will
// be transmitted since only 8 bits can be written to the UART data register.
//
uint16_t txData[BUFFER_SIZE];

//
// BUFFER_SIZE elements allocated in memory to store data received by UART.
// Each element is stored as a 16-bit value, however only the lower 8 bits are
// received since only 8 bits can be read from the UART data register.
//
uint16_t rxData[BUFFER_SIZE];

//
// Number of data mismatches between txData and rxData after BUFFER_SIZE
// elements are transmitted and received.
//
uint8_t  errCount = 0;

//
// Flag to set in DMA CH5 ISR (TX_DMA_IntHandler) when BUFFER_SIZE elements
// from txData buffer are transferred to the UART data register.
//
volatile uint16_t txDone = 0;

//
// Flag to set in DMA CH6 ISR (RX_DMA_IntHandler) when BUFFER_SIZE elements
// from UART data register are transferred to the rxData buffer.
//
volatile uint16_t rxDone = 0;

//
// Function Prototypes
//

//
// Interrupt called at the end of TX DMA (DMA CH5) transfer of BUFFER_SIZE
// elements.
//
__interrupt void TX_DMA_IntHandler(void);

//
// Interrupt called at the end of RX DMA (DMA CH6) transfer of BUFFER_SIZE
// elements.
//
__interrupt void RX_DMA_IntHandler(void);



void ConfigureDMA(uint16_t burstSize, uint16_t transferSize)
{
    //
    // Refer to dma.c for the descriptions of the following functions.
    //

    //
    // Initialize DMA
    //
    DMA_initController();
    DMA_setEmulationMode(DMA_EMULATION_STOP);

    //
    // Set up pointers to txData/rxData buffers, and UARTA data register.
    //
    const void *txAddr;
    const void *rxAddr;
    const void *drAddr;
    txAddr = (const void *)txData;
    rxAddr = (const void *)rxData;

    //
    // UARTA data register.
    //
    drAddr = (const void *)(UARTA_BASE + UART_O_DR);

    //
    // Configure DMA CH5 for Tx Channel
    //

    //
    // DMA channel: 5, destAddr: drAddr, srcAddr: txAddr
    //
    DMA_configAddresses(DMA_CH5_BASE, drAddr, txAddr);

    //
    // DMA channel: 5, size: burstSize, srcStep: 1, destStep: 0
    // srcStep = 1 to iterate one element at a time through txData buffer.
    // destStep = 0 to write every element to one location: the UART data
    // register.
    //
    DMA_configBurst(DMA_CH5_BASE,burstSize,1,0);

    //
    // DMA channel: 5, size: burstSize, srcStep: 1, destStep: 0
    // srcStep = 1 to iterate one element at a time through txData buffer.
    // destStep = 0 to write every element to one location: the UART data
    // register.
    //
    DMA_configTransfer(DMA_CH5_BASE,transferSize,1,0);

    //
    // DMA channel: 5, srcWrapSize: 65535, srcStep: 0,
    // destWrapSize: 65535, destStep: 0
    // Configure wrap size to maximum srcWrapSize and destWrapSize values so
    // wrapping doesn't occur.
    //
    DMA_configWrap(DMA_CH5_BASE, 65535U, 0, 65535U, 0);

    //
    // DMA channel:     5
    // DMA trigger:     UARTATX
    //                  TX DMA will trigger when there are UART_FIFO_LEVEL
    //                  elements empty in TX FIFO. The first trigger will fire
    //                  immediately since TX FIFO is initially empty.
    // ONE SHOT MODE:   disabled
    //                  Disable so each DMA TX trigger (which indicates there
    //                  are burstSize spaces available in the TX FIFO)
    //                  transfers only burstSize data words. Enabling would
    //                  mean only one trigger is needed to transfer
    //                  (burstSize*transferSize) words which would overrun
    //                  the 16-byte TX FIFO and cause data loss.
    // CONTINUOUS MODE: disabled
    //                  Disable so TX DMA (DMA CH5) is disabled immediately
    //                  after (burstSize*transferSize) words is transferred.
    // DMA size:        16 bits
    //                  TX DMA will transfer each 16 bit value in txData one
    //                  at a time.
    //
    DMA_configMode(DMA_CH5_BASE,DMA_TRIGGER_UARTATX,
                   DMA_CFG_ONESHOT_DISABLE
                   | DMA_CFG_CONTINUOUS_DISABLE
                   | DMA_CFG_SIZE_16BIT);

    //
    // Configure TX DMA Channel 5 Interrupt
    //
    DMA_setInterruptMode(DMA_CH5_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH5_BASE);
    DMA_disableOverrunInterrupt(DMA_CH5_BASE);

    //
    // Configure DMA CH6 for Rx Channel
    //

    //
    // DMA channel: 5, destAddr: rxAddr, srcAddr: drAddr
    //
    DMA_configAddresses(DMA_CH6_BASE, rxAddr, drAddr);

    //
    // DMA channel: 6, size: burstSize, srcStep: 1, destStep: 0
    // srcStep = 1 to iterate one element at a time through rxData buffer.
    // destStep = 0 to read every element from one location: the UART data
    // register.
    //
    DMA_configBurst(DMA_CH6_BASE,burstSize,0,1);

    //
    // DMA channel: 6, size: burstSize, srcStep: 1, destStep: 0
    // srcStep = 1 to iterate one element at a time through rxData buffer.
    // destStep = 0 to read every element from one location: the UART data
    // register.
    //
    DMA_configTransfer(DMA_CH6_BASE,transferSize,0,1);

    //
    // DMA channel: 6, srcWrapSize: 65535, srcStep: 0,
    // destWrapSize: 65535, destStep: 0
    // Configure wrap size to maximum srcWrapSize and destWrapSize values so
    // wrapping doesn't occur.
    //
    DMA_configWrap(DMA_CH6_BASE, 65535U, 0, 65535U, 0);

    //
    // DMA channel:     6
    // DMA trigger:     UARTARX
    //                  RX DMA will trigger when UART_FIFO_LEVEL bytes are
    //                  filled in the RX FIFO. The first trigger will fire
    //                  once the first UART_FIFO_LEVEL data bytes are
    //                  transmitted and then received by the UART.
    // ONE SHOT MODE:   disabled
    //                  Disable so each DMA RX trigger (which indicates there
    //                  are burstSize bytes written in the RX FIFO) transfers
    //                  only burstSize data words. Enabling would mean only
    //                  one trigger is needed to transfer
    //                  (burstSize*transferSize) words which are more than
    //                  what has been written in the RX FIFO. Would cause
    //                  rxData to have intermediate zeros written if
    //                  BUFFER_SIZE is greater than the amount of spaces
    //                  in the RX FIFO (16).
    // CONTINUOUS MODE: disabled
    //                  Disable so RX DMA (DMA CH6) is disabled immediately
    //                  after (burstSize*transferSize) words is transferred.
    // DMA size:        16 bits
    //                  RX DMA will transfer each 16 bit value to rxData one
    //                  at a time.
    //
    DMA_configMode(DMA_CH6_BASE,DMA_TRIGGER_UARTARX,
                   DMA_CFG_ONESHOT_DISABLE
                   | DMA_CFG_CONTINUOUS_DISABLE
                   | DMA_CFG_SIZE_16BIT);

    //
    // Configure RX DMA Channel 6 Interrupt.
    //
    DMA_setInterruptMode(DMA_CH6_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH6_BASE);
    DMA_disableOverrunInterrupt(DMA_CH6_BASE);

    //
    // Enable DMA channel triggers.
    //
    DMA_enableTrigger(DMA_CH5_BASE);
    DMA_enableTrigger(DMA_CH6_BASE);

    //
    // Stop DMA Channels initially.
    //
    DMA_stopChannel(DMA_CH5_BASE);
    DMA_stopChannel(DMA_CH6_BASE);

}

void ConfigureUART(uint16_t burstSize)
{

    //
    // Configure UARTA
    // baud rate: 115200, dataWidth: 8, stop bits: 1, parity: none
    //
    UART_setConfig(UARTA_BASE, DEVICE_SYSCLK_FREQ, 115200,
                   (UART_CONFIG_WLEN_8 |
                    UART_CONFIG_STOP_ONE |
                    UART_CONFIG_PAR_NONE));

    //
    // Enable loopback mode. (ENABLE_LOOPBACK_MODE)
    // Comment out for physical pin connected loopback (TX -> RX)
    //
    UART_enableLoopback(UARTA_BASE);

    //
    // FIFO interrupt levels are set to generate an interrupt
    // when the TX FIFO is less than or equal to 16-burstSize elements empty
    // and the RX FIFO is greater than or equal to burstSize elements full.
    //
    switch(burstSize)
    {
        case 2:
            UART_setFIFOLevel(UARTA_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
            break;
        case 4:
            UART_setFIFOLevel(UARTA_BASE, UART_FIFO_TX2_8, UART_FIFO_RX2_8);
            break;
        case 8:
            UART_setFIFOLevel(UARTA_BASE, UART_FIFO_TX4_8, UART_FIFO_RX4_8);
            break;
        default:
            UART_setFIFOLevel(UARTA_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
            break;
    }

    //
    // Enable DMA for TX and RX events
    //
    UART_enableDMA(UARTA_BASE, UART_DMA_TX | UART_DMA_RX);

}



//
// Main
//
void main(void)
{

    //
    // disable WD, enable peripheral clocks.
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
    // Call sysconfig configured code.
    //
    Board_init();

    //
    // Configure GPIOs.
    //
    GPIO_setPinConfig(GPIO_85_UARTA_RX);
    GPIO_setPinConfig(GPIO_84_UARTA_TX);


    //
    // Calculate burst and transfer size for DMA's.
    // BUFFER_SIZE = burstSize*transferSize
    //
    uint16_t burstSize, transferSize;

    //
    // Valid FIFO level triggers:
    // UART_BUFFER_SIZE = 2: TX/RX FIFOs will trigger DMA when they are 1/8
    //                       empty/full (2 available/written spots)
    // UART_BUFFER_SIZE = 4: TX/RX FIFOs will trigger DMA when they are 1/4
    //                       empty/full (4 available/written spots)
    // UART_BUFFER_SIZE = 8: TX/RX FIFOs will trigger DMA when they are 1/2
    //                       empty/full (8 available/written spots)
    //
    if(UART_BUFFER_SIZE == 2
       || UART_BUFFER_SIZE == 4
       || UART_BUFFER_SIZE == 8){
        //
        // Set burstSize to the UART_BUFFER_SIZE to avoid overruning
        // the TX FIFO or leaving last byte in RX FIFO.
        //
        burstSize = UART_BUFFER_SIZE;
    }
    else{
        //
        // Invalid UART_BUFFER_SIZE value. Must be either 2, 4 or 8
        // to correspond to FIFO trigger levels.
        //
        ESTOP0;
        burstSize = 2;
    }
    if(BUFFER_SIZE%burstSize == 0){
        transferSize = BUFFER_SIZE / burstSize;
    }
    else{
        //
        // Invalid BUFFER_SIZE and UART_BUFFER_SIZE combination.
        // UART_BUFFER_SIZE must divide into BUFFER_SIZE evenly
        // and BUFFER_SIZE must be even numbered.
        //
        ESTOP0;
        transferSize = 16;
    }

    //
    // Configure the DMA to read/write to the TX/RX buffers.
    //
    ConfigureDMA(burstSize, transferSize);

    //
    // Configure the UART to send and receive in loopback mode.
    //
    ConfigureUART(burstSize);

    //
    // Setup DMA interrupts.
    //
    Interrupt_register(INT_DMA_CH5, &TX_DMA_IntHandler);
    Interrupt_register(INT_DMA_CH6, &RX_DMA_IntHandler);

    //
    // Enable both DMA interrupts required for this example.
    //
    Interrupt_enable(INT_DMA_CH5);
    Interrupt_enable(INT_DMA_CH6);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM).
    //
    EINT;
    ERTM;

    while(1){
        txDone = 0;
        rxDone = 0;
        uint8_t bufferIndex = 0;

        //
        // Initialize the data buffers.
        //
        for(bufferIndex = 0; bufferIndex < BUFFER_SIZE; bufferIndex++)
        {
            txData[bufferIndex] = bufferIndex&0x00FF;
            rxData[bufferIndex]= 0;
        }

        //
        // Start DMA Channels.
        //
        DMA_startChannel(DMA_CH5_BASE);
        DMA_startChannel(DMA_CH6_BASE);

        //
        // Wait until both DMA transfers are complete.
        //
        while(!txDone || !rxDone);

        //
        // Check the received data.
        //
        for(bufferIndex = 0; bufferIndex < BUFFER_SIZE; bufferIndex++)
        {
            if(txData[bufferIndex] != rxData[bufferIndex])
            {
                errCount++;
            }
        }

        //
        // When the DMA transfers are complete the program will stop here.
        //
        ESTOP0;
    }
}


//
// DMA Channel 5 ISR.
// Called when all data in txData is copied to the UART data register.
// Sets txDone flag which is checked in the main.
//
__interrupt void TX_DMA_IntHandler(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    txDone = 1;
    return;
}

//
// DMA Channel 6 ISR.
// Called when all data received by the UART data register is copied to rxData.
// Sets rxDone flag which is checked in the main.
//
__interrupt void RX_DMA_IntHandler(void)
{
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    rxDone = 1;
    return;
}

//
// End of File
//

