//#############################################################################
//
// FILE:   mcbsp_ex3_loopback_interrupts.c
//
// TITLE:  McBSP loopback with interrupts example.
//
//! \addtogroup driver_example_list
//! <h1> McBSP loopback with interrupts example </h1>
//!
//! This example demonstrates the McBSP operation using internal loopback.
//! This example uses interrupts. Both Rx and Tx interrupts are enabled.
//!
//! \b External \b Connections \n
//! - None
//!
//! \b Watch \b Variables: \n
//! - \b txData - Sent data word
//! - \b rxData - Received data word
//! - \b errCountGlobal - Error counter
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

//
// Define to select wait delay.
//
#define MCBSP_CYCLE_NOP0(n)  __asm(" RPT #(" #n ") || NOP")
#define MCBSP_CYCLE_NOP(n)   MCBSP_CYCLE_NOP0(n)

//
// Define to select the word size for McBSP operation to 8, 16 or 32 bit.
//
#define WORD_SIZE     8U
//#define WORD_SIZE     16U
//#define WORD_SIZE     32U

//
// Globals
//
uint32_t errCountGlobal   = 0;

//
// Variables for transmitting, receiving and testing the data.
//
uint16_t txData;
uint16_t rxData;
uint16_t testData;

//
// Function Prototypes
//
extern void setupMcBSPAPinmux(void);
void initMcBSPLoopback(void);

//
// ISR for McBSPA Tx & Rx interrupts.
//
__interrupt void localMcBSPTxINTAISR(void);
__interrupt void localMcBSPRxINTAISR(void);

//
// Main
//
void main(void)
{
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
    // Initialize McBSP pins.
    //
    setupMcBSPAPinmux();

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
    Interrupt_register(INT_MCBSPA_RX, localMcBSPRxINTAISR);
    Interrupt_register(INT_MCBSPA_TX, localMcBSPTxINTAISR);

    //
    // Initialize and release peripheral (MCBSP) from reset.
    //
    initMcBSPLoopback();
    txData = 0;
    testData = txData;

    //
    // Enable McBSP Tx and RX interrupts in PIE block.
    //
    Interrupt_enable(INT_MCBSPA_RX);
    Interrupt_enable(INT_MCBSPA_TX);

    //
    // Enable group 7 CPU interrupt.
    //
    IER = 0x20;

    //
    // Enable global interrupts.
    //
    EINT;
    ERTM;

    //
    // Idle loop.
    //
    while(1);
}

//
// Init McBSP Loopback - This function initialises McBSP peripheral in digital
// loopback mode.
//
void initMcBSPLoopback()
{
    //
    // Reset FS generator, sample rate generator, transmitter & receiver.
    //
    McBSP_resetFrameSyncLogic(MCBSPA_BASE);
    McBSP_resetSampleRateGenerator(MCBSPA_BASE);
    McBSP_resetTransmitter(MCBSPA_BASE);
    McBSP_resetReceiver(MCBSPA_BASE);

    //
    // Set Rx sign-extension and justification mode.
    //
    McBSP_setRxSignExtension(MCBSPA_BASE, MCBSP_RIGHT_JUSTIFY_FILL_ZERO);

    //
    // Enable DLB mode. Comment out for non-DLB mode.
    //
    McBSP_enableLoopback(MCBSPA_BASE);

    //
    // Set Rx & Tx delay to 1 cycle.
    //
    McBSP_setRxDataDelayBits(MCBSPA_BASE, MCBSP_DATA_DELAY_BIT_1);
    McBSP_setTxDataDelayBits(MCBSPA_BASE, MCBSP_DATA_DELAY_BIT_1);

    //
    // Set CLKX & FSX source as sample rate generator.
    //
    McBSP_setTxClockSource(MCBSPA_BASE, MCBSP_INTERNAL_TX_CLOCK_SOURCE);
    McBSP_setTxFrameSyncSource(MCBSPA_BASE, MCBSP_TX_INTERNAL_FRAME_SYNC_SOURCE);

    //
    // Configure McBSP data behaviour.
    //
    McBSP_setRxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                        MCBSP_BITS_PER_WORD_8, 0);
    McBSP_setTxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                        MCBSP_BITS_PER_WORD_8, 0);

    //
    // Set frame-sync pulse period.
    //
    McBSP_setFrameSyncPulsePeriod(MCBSPA_BASE, 320);

    //
    // Set frame-sync pulse width.
    //
    McBSP_setFrameSyncPulseWidthDivider(MCBSPA_BASE, 1);

    //
    // Set the trigger source for internally generated frame-sync pulse.
    //
    McBSP_setTxInternalFrameSyncSource(MCBSPA_BASE,
                                       MCBSP_TX_INTERNAL_FRAME_SYNC_SRG);

    //
    // Set LSPCLK as input source for sample rate generator.
    //
    McBSP_setTxSRGClockSource(MCBSPA_BASE, MCBSP_SRG_TX_CLOCK_SOURCE_LSPCLK);

    //
    // Set Divide down value for CLKG.
    //
    McBSP_setSRGDataClockDivider(MCBSPA_BASE, 15);

    //
    // Set no external clock sync for CLKG.
    //
    McBSP_disableSRGSyncFSR(MCBSPA_BASE);

    //
    // Enable Tx and Rx interrupts.
    //
    McBSP_enableRxInterrupt(MCBSPA_BASE);
    McBSP_enableTxInterrupt(MCBSPA_BASE);

    //
    // Wait for CPU cycles equivalent to 2 SRG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/LSPCLK). In this example
    // LSPCLK = SYSCLK/4.
    //
    MCBSP_CYCLE_NOP(8);

    //
    // Enable Sample rate generator and wait for at least 2 CLKG clock cycles.
    //
    McBSP_enableSampleRateGenerator(MCBSPA_BASE);

    //
    // Wait for CPU cycles equivalent to 2 CLKG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/(LSPCLK/(1+CLKGDV_VAL))). In this
    // example LSPCLK = SYSCLK/4 and CLKGDV_VAL = 1.
    //
    MCBSP_CYCLE_NOP(16);

    //
    // Release Rx, Tx from reset.
    //
    McBSP_enableReceiver(MCBSPA_BASE);
    McBSP_enableTransmitter(MCBSPA_BASE);
    McBSP_enableFrameSyncLogic(MCBSPA_BASE);
}

//
// local McBSP Tx INTA ISR - ISR for McBSPA Tx interrupt.
//
__interrupt void localMcBSPTxINTAISR(void)
{
    McBSP_write16bitData(MCBSPA_BASE, txData);
    txData = (txData + 1) & 0x00FF;

    //
    // Acknowledge the interrupt to receive more interrupts.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
}

//
// local McBSP Rx INTA ISR - ISR for McBSPA Rx interrupt.
//
__interrupt void localMcBSPRxINTAISR(void)
{
    rxData = McBSP_read16bitData(MCBSPA_BASE);
    if(rxData != (testData & 0x00FF))
    {
        errCountGlobal++;
        Example_Fail = 1;
        ESTOP0;
    }
    testData = (testData + 1) & 0x00FF;

    //
    // Acknowledge the interrupt to receive more interrupts.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);

    Example_PassCount++;
}

//
// End of File
//
