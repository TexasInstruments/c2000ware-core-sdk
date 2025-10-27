//#############################################################################
//
// FILE:   mcbsp_ex7_tdm8_test.c
//
// TITLE:  McBSP TDM-8 Test Example
//
//! \addtogroup driver_example_list
//! <h1> McBSP TDM-8 Test </h1>
//!
//! For the detailed description of this example, please refer to:
//!  How to Implement Custom Serial Interfaces Using the Configurable Logic
//!  Block (CLB) Application Note (SPRAD62).
//!
//! In this example a MCBSP is used to generate and receive a TDM-8 test
//! stream. This example uses interrupts. Both RX and TX interrupts are
//! enabled. The McBSP TDM stream is set to eight 32-bit channels per frame.
//!
//! \note This example is specifically created for use with SPRAD62.
//!
//! To use the McBSP inputs and outputs, the following connections are needed:
//!
//! \b External \b Connections \n
//!
//! McBSP Output Pins   GPIO pin    Device Under Test (DUT)
//! MCLKX               GPIO22      BCLK_IN
//! MFSX                GPIO23      FSYNC_IN
//! MDX                 GPIO20      DATA1_IN
//!
//! McBSP Input Pins    GPIO pin    Device Under Test (DUT)
//! MCLKR               GPIO58     BCLK_OUT
//! FSR                 GPIO59     FSYNC_OUT
//! MDR                 GPIO21     DATA1_OUT
//!
//! \note The McBSP TX and RX pins can be externally looped back to create
//! self contained test.
//!
//! \b Watch \b Variables: \n
//! - \b txData - Sent data word by McBSP Transmitter
//! - \b rxData - Received data word by McBSP Receiver
//! - \b testWordDetected - Indicates when test has started
//! - \b errCountGlobal - Number of errors detected
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
// Define key word to start test
//
#define STARTTESTWORD   0xacedbabe

//
// Define to select wait delay.
//
#define MCBSP_CYCLE_NOP0(n)  __asm(" RPT #(" #n ") || NOP")
#define MCBSP_CYCLE_NOP(n)   MCBSP_CYCLE_NOP0(n)

// ISRs
__interrupt void localMcbspTxIntISR(void);
__interrupt void localMcbspRxIntISR(void);

// Local function declarations
void enableMcbspTdm(void);

uint32_t errCountGlobal   = 0;
uint32_t txData = 0x80000000;
uint32_t rxData;
uint32_t testData = 0x80000000;
uint16_t testWordDetected = 0;
uint16_t testStartCountdown = 0;

//
// Main
//
void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Board_init();

    //
    // Enable Global Interrupt (INTM) and real-time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Start TDM test stream
    //
    enableMcbspTdm();

    while(1){}

}

//
// Enable McBSP TDM - This function enables McBSP TX, RX, and frame sync generation.
// NOTE: Stream starts immediately after calling this function.
//
void enableMcbspTdm()
{
    //
    // McBSP configuration done in syscfg as part of Board_init().
    //

    //
    // Wait for CPU cycles equivalent to 2 SRG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/LSPCLK). In this example
    // LSPCLK = SYSCLK/4.
    //
    MCBSP_CYCLE_NOP(8);

    //
    // Enable Sample rate generator and wait for at least 2 CLKG clock cycles.
    //
    McBSP_enableSampleRateGenerator(myMCBSP0_BASE);

    //
    // Wait for CPU cycles equivalent to 2 CLKG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/(LSPCLK/(1+CLKGDV_VAL))). In this
    // example LSPCLK = SYSCLK/4 and CLKGDV_VAL = 1.
    //
    MCBSP_CYCLE_NOP(16);

    //
    // Release Rx, Tx from reset.
    //
    McBSP_enableReceiver(myMCBSP0_BASE);
    McBSP_enableTransmitter(myMCBSP0_BASE);
    McBSP_enableFrameSyncLogic(myMCBSP0_BASE);
}

//
// Local McBSP Tx INTA ISR - ISR for McBSP Tx interrupt.
//
// Note: 8 dummy values will be sent to flush out CLB logic on receiving
// device and ensure at least one frame-sync is received before starting
// actual test.
//
__interrupt void localMcbspTxIntISR(void)
{
    if(testStartCountdown <= 8)
    {
        if (testStartCountdown == 8)
            McBSP_write32bitData(MCBSPA_BASE, STARTTESTWORD);
        else
            McBSP_write32bitData(MCBSPA_BASE, 0x00000000);

        testStartCountdown++;
    }
    else
    {
        McBSP_write32bitData(MCBSPA_BASE, txData);
        txData = txData + 1;
    }

    //
    // Acknowledge the interrupt to receive more interrupts.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
}

//
// Local McBSP Rx INTA ISR - ISR for McBSP Rx interrupt.
//
__interrupt void localMcbspRxIntISR(void)
{
    rxData = McBSP_read32bitData(MCBSPA_BASE);

    if(testWordDetected)
    {
        if(rxData != testData)
        {
            errCountGlobal++;
//            ESTOP0;
        }
        testData = testData + 1;
    }
    else
    {
        if(rxData == STARTTESTWORD)
            testWordDetected = 1;
    }

    //
    // Acknowledge the interrupt to receive more interrupts.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
}


//
// End of File
//
