//#############################################################################
//
// FILE:   mcbsp_ex3_loopback_interrupts_sysconfig.c
//
// TITLE:  McBSP loopback with interrupts example using sysconfig.
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
// Define to select wait delay.
//
#define MCBSP_CYCLE_NOP0(n)  __asm(" RPT #(" #n ") || NOP")
#define MCBSP_CYCLE_NOP(n)   MCBSP_CYCLE_NOP0(n)

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



__interrupt void localMcBSPTxINTAISR(void);
__interrupt void localMcBSPRxINTAISR(void);
//
// Main
//
void main(void)
{
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
        // Setup GPIO by disabling pin locks and enabling pullups.
        //
        Device_initGPIO();


        McBSP_resetFrameSyncLogic(MCBSPA_BASE);
        McBSP_resetSampleRateGenerator(MCBSPA_BASE);
        McBSP_resetTransmitter(MCBSPA_BASE);
        McBSP_resetReceiver(MCBSPA_BASE);

        //
        //Call Board_init() to invoke the Sysconfig controlled settings
        //
        Board_init();

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

        while(1);

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
        ESTOP0;
    }
    testData = (testData + 1) & 0x00FF;

    //
    // Acknowledge the interrupt to receive more interrupts.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);

   
}


//
// End of File
//
