//###########################################################################
//
// FILE:   dma_ex2_gsram_transfer.c
//
// TITLE:  DMA GSRAM Transfer
//
//! \addtogroup driver_example_list
//! <h1>DMA GSRAM Transfer (dma_ex2_gsram_transfer)</h1>
//!
//!  This example uses one DMA channel to transfer data from a buffer in
//!  RAMGS0 to a buffer in RAMGS1. The example sets the DMA channel
//!  PERINTFRC bit repeatedly until the transfer of 16 bursts (where each
//!  burst is 8 16-bit words) has been completed. When the whole transfer is
//!  complete, it will trigger the DMA interrupt.
//!
//!  \b Watch \b Variables \n
//!  - \b sData - Data to send
//!  - \b rData - Received data
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

//
// DMA data sections
//
#pragma DATA_SECTION(sData, "ramgs0");  // map the TX data to memory
#pragma DATA_SECTION(rData, "ramgs1");  // map the RX data to memory

//
// Defines
//
#define BURST       8       // write 8 to the register for a burst size of 8
#define TRANSFER    16      // [(MEM_BUFFER_SIZE/(BURST)]

//
// Globals
//
uint16_t sData[128];   // Send data buffer
uint16_t rData[128];   // Receive data buffer
volatile uint16_t done;

//
// Function Prototypes
//
__interrupt void INT_myDMA6_ISR(void);
void initDMA(void);
void error();

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
    //Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    //Initialize the PIE vector table with pointers to the shell Interrupt
    //Service Routines (ISR)
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_DMA_CH6, &INT_myDMA6_ISR);

    //
    // Initialize the Device Peripherals:
    //
    initDMA();  // set up the dma

    //
    // User specific code, enable interrupts:
    // Initialize the data buffers
    //
    for(i = 0; i < 128; i++)
    {
        sData[i] = i;
        rData[i] = 0;
    }

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_DMA_CH6);
    EINT;                                // Enable Global Interrupts
    // Start DMA channel
    DMA_startChannel(DMA_CH6_BASE);

    done = 0;           // Test is not done yet

    while(!done)        // wait until the DMA transfer is complete
    {
       DMA_forceTrigger(DMA_CH6_BASE);

       asm(" RPT #255 || NOP");
    }

    //
    // When the DMA transfer is complete the program will stop here
    //
    ESTOP0;
}

//
// error - Error Function which will halt the debugger
//
void error(void)
{
    ESTOP0;  //Test failed!! Stop!
    for (;;);
}

//
// dma_init - DMA setup for both TX and RX channels.
//
void initDMA()
{
    //
    // Refer to dma.c for the descriptions of the following functions.
    //

    //
    // Initialize DMA
    //
    DMA_initController();

    DMA_ConfigParams  transfParams;
    const void *destAddr;
    const void *srcAddr;
    srcAddr = (const void *)sData;
    destAddr = (const void *)rData;

    //
    // configure DMA CH6
    //
    transfParams.transferTrigger  = DMA_TRIGGER_SOFTWARE;
    transfParams.interruptMode    = DMA_INT_AT_END;
    transfParams.enableInterrupt  = 1;
    transfParams.configSize       = DMA_CFG_SIZE_16BIT;
    transfParams.transferMode     = DMA_CFG_ONESHOT_DISABLE;
    transfParams.reinitMode       = DMA_CFG_CONTINUOUS_DISABLE;
    transfParams.burstSize        = BURST;
    transfParams.transferSize     = TRANSFER;
    transfParams.srcWrapSize      = 0xFFFF;
    transfParams.destWrapSize     = 0xFFFF;
    transfParams.destAddr         = (uint32_t)destAddr;
    transfParams.srcAddr          = (uint32_t)srcAddr;
    transfParams.srcBurstStep     = 1;
    transfParams.destBurstStep    = 1;
    transfParams.srcTransferStep  = 1;
    transfParams.destTransferStep = 1;
    transfParams.srcWrapStep      = 0;
    transfParams.destWrapStep     = 0;

    DMA_configChannel(DMA_CH6_BASE, &transfParams);
}

//
// local_D_INTCH6_ISR - DMA Channel6 ISR
//
__interrupt void INT_myDMA6_ISR(void)
{
    uint16_t i;

    DMA_stopChannel(DMA_CH6_BASE);
    // ACK to receive more interrupts from this PIE group
    EALLOW;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    EDIS;

    for( i = 0; i < 128; i++ )
    {
        //
        // check for data integrity
        //
        if (rData[i] != i)
        {
            error();
        }
    }

    done = 1; // Test done.
    return;
}

//
// End of file
//
