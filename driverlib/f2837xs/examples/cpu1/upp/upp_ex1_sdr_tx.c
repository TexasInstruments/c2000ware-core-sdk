//#############################################################################
//
// FILE:   upp_ex1_sdr_tx.c
//
// TITLE:  uPP single data rate transmit example
//
//! \addtogroup driver_example_list
//! <h1> uPP single data rate transmit example </h1>
//!
//! This example sets up the board's uPP with single-data-rate(SDR) interface
//! as a transmitter.
//!
//! \b Important: In order to run this example, two boards with uPP interface
//! are required. All the uPP pins from one board to the other must be connected
//! with common ground. One board must be loaded with this example code and the
//! other board must be loaded with the "upp_sdr_rx" example.
//!
//! \b Instructions:
//! # Load the "upp_sdr_tx" on board 1
//! # Load the "upp_sdr_rx" on board 2
//! # Run the "upp_sdr_rx" code on board 2 (Needs to be run before the tx code)
//! # Run the "upp_sdr_tx" code on board 1
//!
//! \b External \b Connections \n
//! - All Tx pins except wait pin should be connected to respective Rx pins.
//!
//! \b Watch \b Variables: \n
//! - None
//!
//
//      |-----------|               |-----------|
//      |           |=====D0-D7=====|           |
//      |  Device   |-----CLK-------|   Device  |
//      |  Board-1  |               |   Board-2 |
//      |    TX     |-----ENABLE----|     RX    |
//      |           |-----START-----|           |
//      |-----------|               |-----------|
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "device.h"
#include "driverlib.h"

//
// Defines
//
#define TEST_PASS     0xABCDABCD
#define TEST_FAIL     0xDEADDEAD

//
// Defines for setting DMA descriptors.
//
#define LINE_CNT             4U
#define BYTE_CNT             64U
#define WIN_CNT              8U
#define WIN_BYTE_CNT         256U
#define WIN_WORD_CNT         128U
#define UPP_TX_MSGRAM_SIZE   512U
#define UPP_RX_MSGRAM_SIZE   512U

//
// Typedefs
//


//
// Globals
//
uint32_t errCountGlobal   = 0;
uint32_t testStatusGlobal = TEST_FAIL;
uint32_t eowCount         = 0;
uint32_t eolCount         = 0;
uint32_t rdVal            = 0;
uint32_t wrVal            = 0;
uint32_t initTxMsgRAM     = 0;

//
// Function Prototypes
//
void setupUPPPinmux(void);

//
// ISR for uPP Interrupts.
//
__interrupt void localUPPISR(void);


//
// Main
//
void main(void)
{
    uint32_t i;
    testStatusGlobal = TEST_FAIL;
    errCountGlobal = 0x0;

    //
    // Initialize device clock and peripherals.
    //
    Device_init();

    //
    // Disable all the interrupts.
    //
    DINT;

    //
    // Setup GPIO by disabling pin locks and enabling pullups.
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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_UPPA, localUPPISR);

    //
    // Enable UPPA interrupt in the PIE: Group 8 interrupt 15.
    //
    Interrupt_enable(INT_UPPA);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM).
    //
    EINT;
    ERTM;

    //
    // Issue Soft Reset(internal) to uPP.
    //
    UPP_performSoftReset(UPP_BASE);

    //
    // Configure GPIO muxing for uPP pins.
    //
    setupUPPPinmux();

    //
    // Initialize Tx MSG RAM.
    //
    for(i = 0; i < UPP_TX_MSGRAM_SIZE/2; i+=2)
    {
        wrVal = wrVal + 0x12345678;
        HWREG(UPP_CPU_TX_MSGRAM_STARTADDR + i) = wrVal;
    }

    //
    // Configure uPP for Transmission.
    //
    UPP_setTxClockDivider(UPP_BASE, 0x4);
    UPP_setClockPolarity(UPP_BASE, UPP_CLK_INVERTED);
    UPP_setOperationMode(UPP_BASE, UPP_TRANSMIT_MODE);
    UPP_setDataRate(UPP_BASE, UPP_DATA_RATE_SDR);
    UPP_setTxIdleValue(UPP_BASE, 0x0000);

    //
    // Enable EOL/EOW Interrupts.
    //
    UPP_enableInterrupt(UPP_BASE, (UPP_INT_CHI_END_OF_WINDOW |
                                   UPP_INT_CHI_END_OF_LINE));
    UPP_enableGlobalInterrupt(UPP_BASE);

    //
    // Enable uPP Module.
    //
    UPP_enableModule(UPP_BASE);

    //
    // Setup DMA Channel.
    //
    UPP_DMADescriptor dmaDesc;
    dmaDesc.addr       = UPP_DMA_TX_MSGRAM_STARTADDR;
    dmaDesc.lineCount  = LINE_CNT;
    dmaDesc.byteCount  = BYTE_CNT;
    dmaDesc.lineOffset = BYTE_CNT;
    UPP_setDMADescriptor(UPP_BASE, UPP_DMA_CHANNEL_I, &dmaDesc);

    while(eowCount < WIN_CNT);

    //
    // Disable uPP to stop transmission after expected window count is
    // reached.
    //
    UPP_disableModule(UPP_BASE);

    ESTOP0;
    while(1);
}

//
// Local UPP ISR - ISR for UPPA Interrupt.
//
interrupt void localUPPISR(void)
{
    uint32_t i;
    UPP_DMADescriptor txDesc;

    //
    // Acknowledge Group 8 interrupt to receive more interrupts.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
    if(UPP_isInterruptGenerated(UPP_BASE) == true)
    {
        //
        // Check for EOW Interrupt Flag.
        //
        if((UPP_getInterruptStatus(UPP_BASE) & UPP_INT_CHI_END_OF_WINDOW)
           != 0x0000)
        {
            eowCount++;
            if(eowCount < (WIN_CNT-1))
            {
                initTxMsgRAM = 1;
            }

            //
            // Enable EOL Interrupt.
            //
            UPP_enableInterrupt(UPP_BASE, UPP_INT_CHI_END_OF_LINE);

            //
            // Clear the status of EOW Interrupt.
            //
            UPP_clearInterruptStatus(UPP_BASE, UPP_INT_CHI_END_OF_WINDOW);
        }

        //
        // Check for EOL Interrupt.
        //
        if((UPP_getInterruptStatus(UPP_BASE) & UPP_INT_CHI_END_OF_LINE)
           != 0x0000)
        {
            eolCount++;

            //
            // Clear status & disable EOL interrupt.
            //
            UPP_clearInterruptStatus(UPP_BASE, UPP_INT_CHI_END_OF_LINE);
            UPP_disableInterrupt(UPP_BASE, UPP_INT_CHI_END_OF_LINE);

            //
            // Initialize channel descriptor for next window transfer.
            //
            if(eowCount < (WIN_CNT - 1))
            {
                if(eowCount%2)
                {
                    //
                    // Copy data to be transmitted to Tx MSG RAM if previous
                    // transfer has completed.
                    //
                    if(initTxMsgRAM == 1)
                    {
                        for(i=0; i<WIN_WORD_CNT; i+=2)
                        {
                            wrVal = wrVal + 0x12345678;
                            HWREG(UPP_DMA_TX_MSGRAM_STARTADDR + i) = wrVal;
                        }
                        initTxMsgRAM = 0;
                    }

                    //
                    // Set DMA descriptor for the transfer.
                    //
                    txDesc.addr = UPP_DMA_TX_MSGRAM_STARTADDR;
                    txDesc.lineCount = LINE_CNT;
                    txDesc.byteCount = BYTE_CNT;
                    txDesc.lineOffset = BYTE_CNT;
                    UPP_setDMADescriptor(UPP_BASE, UPP_DMA_CHANNEL_I, &txDesc);
                }
                else
                {
                    //
                    // Copy data to be transmitted to Tx MSG RAM if previous
                    // transfer has completed.
                    //
                    if(initTxMsgRAM == 1)
                    {
                        for(i=0;i<WIN_WORD_CNT;i+=2)
                        {
                            wrVal = wrVal + 0x12345678;
                            HWREG(UPP_CPU_TX_MSGRAM_STARTADDR +
                                  WIN_WORD_CNT + i) = wrVal;
                        }
                        initTxMsgRAM = 0;
                    }

                    //
                    // Set DMA descriptor for the transfer.
                    //
                    txDesc.addr       = UPP_DMA_TX_MSGRAM_STARTADDR +
                                        (LINE_CNT * BYTE_CNT);
                    txDesc.lineCount  = LINE_CNT;
                    txDesc.byteCount  = BYTE_CNT;
                    txDesc.lineOffset = BYTE_CNT;
                    UPP_setDMADescriptor(UPP_BASE, UPP_DMA_CHANNEL_I, &txDesc);
                }
            }
        }
    }

    //
    // Clear Global Interrupt.
    //
    UPP_clearGlobalInterruptStatus(UPP_BASE);
}

//
// Setup UPP Pinmux - This function configures pins for uPP.
//
void setupUPPPinmux(void)
{
    uint16_t i;

    //
    // Disable pull up for uPP pins.
    //
    HWREG(GPIOCTRL_BASE + GPIO_O_GPAPUD) |= 0x3FFC00U;

    //
    // Setup async mode for uPP pins.
    //
    for(i = 10; i <= 21; i++)
    {
        GPIO_setQualificationMode(i, GPIO_QUAL_ASYNC);
    }

    //
    // Configure uPP pins.
    //
    GPIO_setPinConfig(GPIO_10_UPP_WAIT);
    GPIO_setPinConfig(GPIO_11_UPP_STRT);
    GPIO_setPinConfig(GPIO_12_UPP_ENA);
    GPIO_setPinConfig(GPIO_13_UPP_D7);
    GPIO_setPinConfig(GPIO_14_UPP_D6);
    GPIO_setPinConfig(GPIO_15_UPP_D5);
    GPIO_setPinConfig(GPIO_16_UPP_D4);
    GPIO_setPinConfig(GPIO_17_UPP_D3);
    GPIO_setPinConfig(GPIO_18_UPP_D2);
    GPIO_setPinConfig(GPIO_19_UPP_D1);
    GPIO_setPinConfig(GPIO_20_UPP_D0);
    GPIO_setPinConfig(GPIO_21_UPP_CLK);
 }

//
// End of File
//
