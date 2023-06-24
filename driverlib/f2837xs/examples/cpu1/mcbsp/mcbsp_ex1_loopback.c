//#############################################################################
//
// FILE:   mcbsp_ex1_loopback.c
//
// TITLE:  McBSP loopback example.
//
//! \addtogroup driver_example_list
//! <h1> McBSP loopback example </h1>
//!
//! This example demonstrates the McBSP operation using internal loopback.
//! This example does not use interrupts. Instead, a polling method is used
//! to check the receive data. The incoming data is checked for accuracy.
//!
//! Three different serial word sizes can be tested.  Before compiling
//! this project, select the serial word size of 8, 16 or 32 by using
//! the \#define statements at the beginning of the code.
//!
//! This program will execute until terminated by the user.
//!
//! \b 8-bit \b word \b example: \n
//!      The sent data looks like this:\n
//!      00 01 02 03 04 05 06 07 .... FE FF\n
//!
//! \b 16-bit \b word \b example: \n
//!      The sent data looks like this:\n
//!      0000 0001 0002 0003 0004 0005 0006 0007 .... FFFE FFFF\n
//!
//! \b 32-bit \b word \b example: \n
//!      The sent data looks like this: \n
//!      FFFF0000 FFFE0001 FFFD0002 .... 0000FFFF \n
//!
//! \b External \b Connections \n
//! - None
//!
//! \b Watch \b Variables: \n
//! - \b txData1 - Sent data word: 8 or 16-bit or low half of 32-bit
//! - \b txData2 - Sent data word: upper half of 32-bit
//! - \b rxData1 - Received data word: 8 or 16-bit or low half of 32-bit
//! - \b rxData2 - Received data word: upper half of 32-bit
//! - \b errCountGlobal   - Error counter
//!
//! \note txData2 and rxData2 are not used for 8-bit or 16-bit word size.
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
// Define to select clock delay.
//
#define MCBSP_CYCLE_NOP0(n)  __asm(" RPT #(" #n ") || NOP")
#define MCBSP_CYCLE_NOP(n)   MCBSP_CYCLE_NOP0(n)

//
// Define to select the word-size for McBSP operation to 8, 16 or 32 bit.
//
//#define WORD_SIZE     8U
//#define WORD_SIZE     16U
#define WORD_SIZE     32U

//
// Globals
//
uint32_t errCountGlobal   = 0;

//
// Variables for transmitting, receiving and testing the data.
//
uint16_t txData1 = 0x0000;
uint16_t txData2 = 0x0000;
uint16_t rxData1 = 0x0000;
uint16_t rxData2 = 0x0000;
uint16_t dataSize;

//
// Function Prototypes
//
extern void setupMcBSPAPinmux(void);
void initMcBSPLoopback(void);

//
// Main
//
void main(void)
{
    uint32_t tempData;
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
    // Initialize GPIO.
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
    dataSize = WORD_SIZE;

    //
    // Initialize and release peripheral (McBSP) from reset.
    //
    initMcBSPLoopback();

    //
    // Run a loopback test in 8-bit mode.
    //
    if(dataSize == 8)
    {
        txData1 = 0x0000;
        while(1)
        {
            //
            // Write data to be transmitted.
            //
            while(!McBSP_isTxReady(MCBSPA_BASE));
            McBSP_write16bitData(MCBSPA_BASE, txData1);

            //
            // Check if data is received.
            //
            while(!McBSP_isRxReady(MCBSPA_BASE));
            rxData1 = McBSP_read16bitData(MCBSPA_BASE);

            if(rxData1 != txData1)
            {
                errCountGlobal++;
                Example_Fail = 1;
                ESTOP0;
            }
            txData1++;
            txData1 = txData1 & 0x00FF;
            NOP;

            Example_PassCount++;
        }
    }
    else if(dataSize == 16)
    {
        txData1 = 0x0000;
        while(1)
        {
            //
            // Write data to be transmitted.
            //
            while(!McBSP_isTxReady(MCBSPA_BASE));
            McBSP_write16bitData(MCBSPA_BASE, txData1);

            //
            // Check if data is received.
            //
            while(!McBSP_isRxReady(MCBSPA_BASE));
            rxData1 = McBSP_read16bitData(MCBSPA_BASE);
            if(rxData1 != txData1)
            {
                errCountGlobal++;
                Example_Fail = 1;
                ESTOP0;
            }
            txData1++;
            NOP;

            Example_PassCount++;
        }
    }
    else if(dataSize == 32)
    {
        txData2 = 0xFFFF;
        txData1 = 0x0000;
        while(1)
        {
            //
            // Write data to be transmitted.
            //
            tempData = (txData1|(((uint32_t)txData2) << 16U));
            while(!McBSP_isTxReady(MCBSPA_BASE));
            McBSP_write32bitData(MCBSPA_BASE, tempData);

            //
            // Check if data is received.
            //
            while(!McBSP_isRxReady(MCBSPA_BASE));
            tempData = McBSP_read32bitData(MCBSPA_BASE);
            rxData1 = tempData & 0xFFFF;
            rxData2 = tempData >> 16U;
            if(rxData1 != txData1 || rxData2 != txData2)
            {
                errCountGlobal++;
                Example_Fail = 1;
                ESTOP0;
            }
            txData1++;
            txData2--;
            NOP;

            Example_PassCount++;
        }
    }
}

//
// Init McBSP Loopback - This function initialises McBSP in digital loopback
// mode.
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
    // Set the source for CLKX & FSX as sample rate generator.
    //
    McBSP_setTxClockSource(MCBSPA_BASE, MCBSP_INTERNAL_TX_CLOCK_SOURCE);
    McBSP_setTxFrameSyncSource(MCBSPA_BASE, MCBSP_TX_INTERNAL_FRAME_SYNC_SOURCE);

    //
    // Configure McBSP data behaviour.
    //
    if(dataSize == 8)
    {
        McBSP_setRxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                            MCBSP_BITS_PER_WORD_8, 0);
        McBSP_setTxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                            MCBSP_BITS_PER_WORD_8, 0);
    }
    else if(dataSize == 16)
    {
        McBSP_setRxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                            MCBSP_BITS_PER_WORD_16, 0);
        McBSP_setTxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                            MCBSP_BITS_PER_WORD_16, 0);
    }
    else if(dataSize == 32)
    {
        McBSP_setRxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                            MCBSP_BITS_PER_WORD_32, 0);
        McBSP_setTxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                            MCBSP_BITS_PER_WORD_32, 0);
    }

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
    McBSP_setSRGDataClockDivider(MCBSPA_BASE, 1);

    //
    // Set no external clock sync for CLKG.
    //
    McBSP_disableSRGSyncFSR(MCBSPA_BASE);

    //
    // Wait for CPU cycles equivalent to 2 SRG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/LSPCLK). In this example
    // LSPCLK = SYSCLK/4.
    //
    MCBSP_CYCLE_NOP(8);

    //
    // Enable Sample rate generator and wait for atleast 2 CLKG clock cycles.
    //
    McBSP_enableSampleRateGenerator(MCBSPA_BASE);
    McBSP_enableFrameSyncLogic(MCBSPA_BASE);

    //
    // Wait for CPU cycles equivalent to 2 CLKG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/(LSPCLK/(1+CLKGDV_VAL))). In this
    // example LSPCLK = SYSCLK/4 and CLKGDV_VAL = 1.
    //
    MCBSP_CYCLE_NOP(16);

    //
    // Release Rx, Tx from reset.
    //
    McBSP_enableTransmitter(MCBSPA_BASE);
    McBSP_enableReceiver(MCBSPA_BASE);
}

//
// End of File
//
