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
//! UART_BUFFER_SIZE words. The configurations for the UART module and both DMA
//! modules are done in the Sysconfig file.
//!
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
//! even numbered.
//! Set UART_BUFFER_SIZE to 2, 4, 8, 12 or 14. This value must divide
//! evenly into the chosen BUFFER_SIZE.
//! Change "Burst Size" and "Transfer Size" settings in Sysconfig (for both
//! myDMA0 and myDMA1) to reflect these values.
//! Burst Size = UART_BUFFER_SIZE
//! Transfer Size = BUFFER_SIZE / UART_BUFFER_SIZE
//!
//! To use 32-bit words instead of 16-bit words, change:
//! - txData and rxData data types to uint32_t.
//! - "Databus Width" setting in Sysconfig (for both myDMA0 and myDMA1) to "DMA
//!   transfers 32 bits at a time."
//! - DMA0 "Source Address Burst Step" and "Source Address Transfer Step" in
//!   Sysconfig to 2.
//! - DMA1 "Destination Address Burst Step" and "Destination Address Transfer
//!   Step" in Sysconfig to 2.
//!
//! \note This example implements the UART FIFO Buffers in NON fine-grained
//! mode
//!
//! \b External \b Connections \b (Optional)\n
//!  - Connect UARTA_TX and UARTA_RX for external loopback.
//!    Uncheck "Enable Loopback Mode" in Sysconfig myUART0 instance
//!  - UARTA_TX is on GPIO43
//!  - UARTA_RX is on GPIO32
//!
//! \b Watch \b Variables \n
//!  - \b txData   - Data transmitted
//!  - \b rxData   - Data received
//!  - \b errCount - Error count
//!
//
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
#pragma DATA_SECTION(rxData, "ramgs0");

//
// Defines
//

//
// Amount of data words that will trigger UART FIFOs.
// For the 16 byte deep UART FIFOs: set to 2, 4, 8, 12 or 14.
// !IMPORTANT! Set "Burst Size" in Sysconfig myDMA0 and myDMA1 instances to the
// chosen UART_BUFFER_SIZE.
//
#define UART_BUFFER_SIZE  2

//
// Set total amount of data words to transfer from TxData to RxData.
// Must be divisible by UART_BUFFER_SIZE and even numbered.
// !IMPORTANT! Set "Transfer Size" in Sysconfig myDMA0 and myDMA1 instances
// to the BUFFER_SIZE / UART_BUFFER_SIZE.
//
#define BUFFER_SIZE      32

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
// Set up pointers to txData/rxData buffers, and UART data register.
//
const void *txAddr = (const void *)txData;
const void *rxAddr = (const void *)rxData;
const void *drAddr = (const void *)(myUART0_BASE + UART_O_DR);


//
// Number of data mismatches between txData and rxData after BUFFER_SIZE
// elements are transmitted and received.
//
uint8_t  errCount = 0;

//
// Flag to set in DMA CH5 ISR (INT_myDMA0_ISR) when BUFFER_SIZE elements
// from txData buffer are transferred to the UART data register.
//
volatile uint16_t txDone = 0;

//
// Flag to set in DMA CH6 ISR (INT_myDMA1_ISR) when BUFFER_SIZE elements
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
__interrupt void INT_myDMA0_ISR(void);

//
// Interrupt called at the end of RX DMA (DMA CH6) transfer of BUFFER_SIZE
// elements.
//
__interrupt void INT_myDMA1_ISR(void);


void ConfigureUART()
{
    //
    // Valid FIFO level triggers:
    // UART_BUFFER_SIZE = 2: TX/RX FIFOs will trigger DMA when they are 1/8
    //                       empty/full (2 available/written spots)
    // UART_BUFFER_SIZE = 4: TX/RX FIFOs will trigger DMA when they are 1/4
    //                       empty/full (4 available/written spots)
    // UART_BUFFER_SIZE = 8: TX/RX FIFOs will trigger DMA when they are 1/2
    //                       empty/full (8 available/written spots)
    //
    // UART_BUFFER_SIZE = 12: TX/RX FIFOs will trigger DMA when they are 3/4
    //                       empty/full (12 available/written spots)
    //
    // UART_BUFFER_SIZE = 14: TX/RX FIFOs will trigger DMA when they are 7/8
    //                       empty/full (14 available/written spots)
    //
    if(UART_BUFFER_SIZE != 2
       && UART_BUFFER_SIZE != 4
       && UART_BUFFER_SIZE != 8
       && UART_BUFFER_SIZE != 12
       && UART_BUFFER_SIZE != 14){
        //
        // Invalid UART_BUFFER_SIZE value. Must be either 2, 4, 8, 12 or 14
        // to correspond to FIFO trigger levels.
        //
        ESTOP0;
    }

    //
    // FIFO interrupt levels are set to generate an interrupt
    // when the TX FIFO is less than or equal to 16-burstSize elements full
    // and the RX FIFO is greater than or equal to burstSize elements full.
    //
    switch(UART_BUFFER_SIZE)
    {
        case 2:
            UART_setFIFOLevel(myUART0_BASE, UART_FIFO_TX7_8, UART_FIFO_RX1_8);
            break;
        case 4:
            UART_setFIFOLevel(myUART0_BASE, UART_FIFO_TX6_8, UART_FIFO_RX2_8);
            break;
        case 8:
            UART_setFIFOLevel(myUART0_BASE, UART_FIFO_TX4_8, UART_FIFO_RX4_8);
            break;
        case 12:
            UART_setFIFOLevel(myUART0_BASE, UART_FIFO_TX2_8, UART_FIFO_RX6_8);
            break;
        case 14:
            UART_setFIFOLevel(myUART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX7_8);
            break;
        default:
            UART_setFIFOLevel(myUART0_BASE, UART_FIFO_TX7_8, UART_FIFO_RX1_8);
            break;
    }

    //
    // Enable DMA for TX and RX events
    //
    UART_enableDMA(myUART0_BASE, UART_DMA_TX | UART_DMA_RX);

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
    // Call Sysconfig configured code.
    //
    Board_init();


    //
    // Configure the UART FIFO.
    //
    ConfigureUART();

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
        DMA_startChannel(myDMA0_BASE);
        DMA_startChannel(myDMA1_BASE);

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
// TX DMA Channel 5 end of transfer ISR.
// Called when all data in txData is copied to the UART data register.
// Sets txDone flag which is checked in the main.
//
__interrupt void INT_myDMA0_ISR(void)
{
    Interrupt_clearACKGroup(INT_myDMA0_INTERRUPT_ACK_GROUP);
    txDone = 1;
    return;
}

//
// RX DMA Channel 6 end of transfer ISR.
// Called when all data received by the UART data register is copied to rxData.
// Sets rxDone flag which is checked in the main.
//
__interrupt void INT_myDMA1_ISR(void)
{
    Interrupt_clearACKGroup(INT_myDMA1_INTERRUPT_ACK_GROUP);
    rxDone = 1;
    return;
}

//
// End of File
//
