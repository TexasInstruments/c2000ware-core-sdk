//#############################################################################
//
// FILE:   mcbsp_ex5_ext_loopback.c
//
// TITLE:  McBSP external loopback example.
//
//! \addtogroup driver_example_list
//! <h1> McBSP external loopback example </h1>
//!
//! This example demonstrates the McBSP operation using external loopback.
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
//! \b McBSPA \b Signals - \b McBSPB \b signals
//!  - MCLKXA            - MCLKRB
//!  - MFSXA             - MFSRB
//!  - MDXA              - MDRB
//!  - MCLKRA            - MCLKXB
//!  - MFSRA             - MFSXB
//!  - MDRA              - MDXB
//!
//! \b Watch \b Variables: \n
//! - \b txData1A - Sent data word by McBSPA Transmitter:8 or 16-bit or low
//!                 half of 32-bit
//! - \b txData2A - Sent data word by McBSPA Transmitter:upper half of 32-bit
//! - \b rxData1A - Received data word by MCBSPA Receiver:8 or 16-bit or lower
//!                 half of 32-bit
//! - \b rxData2A - Received data word by McBSPA Receiver:upper half of 32-bit
//! - \b txData1B - Sent data word by McBSPB Transmitter:8 or 16-bit or low
//!                 half of 32-bit
//! - \b txData2B - Sent data word by McBSPB Transmitter:upper half of 32-bit
//! - \b rxData1B - Received data word by McBSPB Receiver:8 or 16-bit or lower
//!                 half of 32-bit
//! - \b rxData2B - Received data word by McBSPB Receiver:upper half of 32-bit
//! - \b errCountGlobal   - Error counter
//!
//! \note txData2A, rxData2A, txData2B and rxData2B are not used for 8-bit or
//! 16-bit word size.
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
// Define to select wait delay.
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
uint16_t txData1A = 0x0000;
uint16_t txData2A = 0x0000;

uint16_t rxData1A = 0x0000;
uint16_t rxData2A = 0x0000;

uint16_t txData1B = 0x0000;
uint16_t txData2B = 0x0000;

uint16_t rxData1B = 0x0000;
uint16_t rxData2B = 0x0000;

uint16_t dataSize;

//
// Function Prototypes
//
extern void setupMcBSPAPinmux(void);
extern void setupMcBSPBPinmux(void);
void initMcBSPLoopback(void);
void initTransmitter(uint32_t base);
void initReceiver(uint32_t base);
void enableModule(uint32_t base);
void resetModule(uint32_t base);

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
    // Initialize GPIOs for McBSPA and McBSPB.
    //
    setupMcBSPAPinmux();
    setupMcBSPBPinmux();

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
    // Reset McBSPA & McBSPB modules.
    //
    resetModule(MCBSPA_BASE);
    resetModule(MCBSPB_BASE);

    //
    // Initialize the transmitter & receiver modules in McBSPA & McBSPB.
    //
    initTransmitter(MCBSPA_BASE);
    initReceiver(MCBSPA_BASE);
    initTransmitter(MCBSPB_BASE);
    initReceiver(MCBSPB_BASE);

    //
    // Enable McBSPA & McBSP modules.
    //
    enableModule(MCBSPA_BASE);
    enableModule(MCBSPB_BASE);

    //
    // Run a loopback test in 8-bit mode.
    //
    if(dataSize == 8)
    {
        txData1A = 0x0000;
        while(1)
        {
            //
            // Transmit 8-bit data from McBSPSA Tx.
            //
            while(!McBSP_isTxReady(MCBSPA_BASE));
            McBSP_write16bitData(MCBSPA_BASE, txData1A);

            //
            // Checks if data is received at McBSPB Rx.
            //
            while(!McBSP_isRxReady(MCBSPB_BASE));
            rxData1B = McBSP_read16bitData(MCBSPB_BASE);

            txData1B = rxData1B;

            //
            // Retransmit the received data from McBSPB Tx to McBSPA Rx.
            //
            while(!McBSP_isTxReady(MCBSPB_BASE));
            McBSP_write16bitData(MCBSPB_BASE, txData1B);

            //
            // Receive data at McBSPA Rx.
            //
            while(!McBSP_isRxReady(MCBSPA_BASE));
            rxData1A = McBSP_read16bitData(MCBSPA_BASE);

            //
            // Check if correct data is received.
            //
            if(rxData1A != txData1A)
            {
                errCountGlobal++;
                Example_Fail = 1;
                ESTOP0;
            }
            txData1A++;
            txData1A = txData1A & 0x00FF;
            NOP;

            Example_PassCount++;
        }
    }
    else if(dataSize == 16)
    {
        txData1A = 0x0000;
        while(1)
        {
            //
            // Transmit 16-bit data from McBSPSA Tx.
            //
            while(!McBSP_isTxReady(MCBSPA_BASE));
            McBSP_write16bitData(MCBSPA_BASE, txData1A);

            //
            // Checks if data is received at McBSPB Rx.
            //
            while(!McBSP_isRxReady(MCBSPB_BASE));
            rxData1B = McBSP_read16bitData(MCBSPB_BASE);

            txData1B = rxData1B;

            //
            // Retransmit the received data from McBSPB Tx to McBSPA Rx.
            //
            while(!McBSP_isTxReady(MCBSPB_BASE));
            McBSP_write16bitData(MCBSPB_BASE, txData1B);

            //
            // Receive data at McBSPA Rx.
            //
            while(!McBSP_isRxReady(MCBSPA_BASE));
            rxData1A = McBSP_read16bitData(MCBSPA_BASE);

            //
            // Check if correct data is received.
            //
            if(rxData1A != txData1A)
            {
                errCountGlobal++;
                Example_Fail = 1;
                ESTOP0;
            }
            txData1A++;
            NOP;

            Example_PassCount++;
        }
    }
    else if(dataSize == 32)
    {
        txData2A = 0xFFFF;
        txData1A = 0x0000;
        while(1)
        {
            //
            // Transmit 32-bit data from McBSPSA Tx.
            //
            tempData = (txData1A|(((uint32_t)txData2A) << 16U));
            while(!McBSP_isTxReady(MCBSPA_BASE));
            McBSP_write32bitData(MCBSPA_BASE, tempData);

            //
            // Check if data is received at McBSPB Rx.
            //
            while(!McBSP_isRxReady(MCBSPB_BASE));
            tempData = McBSP_read32bitData(MCBSPB_BASE);
            rxData1B = tempData & 0xFFFF;
            rxData2B = tempData >> 16U;

            //
            // Retransmit the received data from McBSPB Tx to McBSPA Rx.
            //
            txData1B = rxData1B;
            txData2B = rxData2B;
            tempData = (txData1B|(((uint32_t)txData2B) << 16U));
            while(!McBSP_isTxReady(MCBSPB_BASE));
            McBSP_write32bitData(MCBSPB_BASE, tempData);

            //
            // Receive data at McBSPA Rx.
            //
            while(!McBSP_isRxReady(MCBSPA_BASE));
            tempData = McBSP_read32bitData(MCBSPA_BASE);
            rxData1A = tempData & 0xFFFF;
            rxData2A = tempData >> 16U;

            //
            // Check if correct data is received.
            //
            if(rxData1A != txData1A || rxData2A != txData2A)
            {
                errCountGlobal++;
                Example_Fail = 1;
                ESTOP0;
            }
            txData1A++;
            txData2A--;
            NOP;

            Example_PassCount++;
        }
    }
}

//
// Enable Module - This function enables the modules in McBSP.
//
void enableModule(uint32_t base)
{
    //
    // Enable Sample rate generator and frame-sync logic and wait for atleast
    // 2 CLKG clock cycles.
    //
    McBSP_enableSampleRateGenerator(base);
    McBSP_enableFrameSyncLogic(base);

    //
    // Wait for CPU cycles equivalent to 2 CLKG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/(LSPCLK/(1+CLKGDV_VAL))). In this
    // example LSPCLK = SYSCLK/4 and CLKGDV_VAL = 1.
    //
    MCBSP_CYCLE_NOP(16);

    //
    // Release Tx from reset.
    //
    McBSP_enableTransmitter(base);
    McBSP_enableReceiver(base);
}

//
// Reset Module - This function disables the modules in McBSP.
//
void resetModule(uint32_t base)
{
    //
    // Reset FS generator, sample rate generator, transmitter & receiver.
    //
    McBSP_resetFrameSyncLogic(base);
    McBSP_resetSampleRateGenerator(base);
    McBSP_resetTransmitter(base);
    McBSP_resetReceiver(base);
}

//
// Init Transmitter - This function initialises McBSP transmitter module.
//
void initTransmitter(uint32_t base)
{
    //
    // Right justify word.
    //
    McBSP_setRxSignExtension(base, MCBSP_RIGHT_JUSTIFY_FILL_ZERO);

    //
    // Set Rx & Tx delay to 1 cycle.
    //
    McBSP_setTxDataDelayBits(base, MCBSP_DATA_DELAY_BIT_1);


    //
    // Configure McBSP data behaviour: phase = 1; frame length = 1 word and
    // word length = dataSize.
    //
    if(dataSize == 8)
    {
        McBSP_setTxDataSize(base, MCBSP_PHASE_ONE_FRAME, MCBSP_BITS_PER_WORD_8,
                            0);
    }
    else if(dataSize == 16)
    {
        McBSP_setTxDataSize(base, MCBSP_PHASE_ONE_FRAME, MCBSP_BITS_PER_WORD_16,
                            0);
    }
    else if(dataSize == 32)
    {
        McBSP_setTxDataSize(base, MCBSP_PHASE_ONE_FRAME, MCBSP_BITS_PER_WORD_32,
                             0);
    }

    //
    // Configure Frame synchronization behaviour.
    //

    //
    // Enable transmit frame-sync ignore function.
    //
    McBSP_disableTxFrameSyncErrorDetection(base);

    //
    // Set Tx frame-sync source as internal.
    //
    McBSP_setTxFrameSyncSource(base, MCBSP_TX_INTERNAL_FRAME_SYNC_SOURCE);

    //
    // Set the trigger source for internally generated frame-sync pulse.
    //
    McBSP_setTxInternalFrameSyncSource(base, MCBSP_TX_INTERNAL_FRAME_SYNC_DATA);

    //
    // Set no external clock sync for CLKG.
    //
    McBSP_disableSRGSyncFSR(base);

    //
    // Set frame-sync pulse period.
    //
    McBSP_setFrameSyncPulsePeriod(base, 320);

    //
    // Set frame-sync pulse width.
    //
    McBSP_setFrameSyncPulseWidthDivider(base, 1);

    //
    // Configure Tx Clock behaviour.
    //

    //
    // Set LSPCLK as input source for sample rate generator.
    //
    McBSP_setTxSRGClockSource(base, MCBSP_SRG_TX_CLOCK_SOURCE_LSPCLK);

    //
    // Set CLKX source as sample rate generator.
    //
    McBSP_setTxClockSource(base, MCBSP_INTERNAL_TX_CLOCK_SOURCE);

    //
    // Set Divide down value for CLKG.
    //
    McBSP_setSRGDataClockDivider(base, 1);

    //
    // Wait for CPU cycles equivalent to 2 SRG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/LSPCLK). In this example
    // LSPCLK = SYSCLK/4.
    //
    MCBSP_CYCLE_NOP(8);
}

//
// Init Receiver - This function initialises the McBSP Receiver module.
//
void initReceiver(uint32_t base)
{
    //
    // Configure McBSP data behaviour.
    //
    if(dataSize == 8)
    {
        McBSP_setRxDataSize(base, MCBSP_PHASE_ONE_FRAME, MCBSP_BITS_PER_WORD_8,
                            0);
    }
    else if(dataSize == 16)
    {
        McBSP_setRxDataSize(base, MCBSP_PHASE_ONE_FRAME, MCBSP_BITS_PER_WORD_16,
                            0);
    }
    else if(dataSize == 32)
    {
        McBSP_setRxDataSize(base, MCBSP_PHASE_ONE_FRAME, MCBSP_BITS_PER_WORD_32,
                            0);
    }

    //
    // Set Rx data delay to 1 cycle.
    //
    McBSP_setRxDataDelayBits(base, MCBSP_DATA_DELAY_BIT_1);

    //
    // Set receive sign-extension and justification mode.
    //
    McBSP_setRxSignExtension(base, MCBSP_RIGHT_JUSTIFY_FILL_ZERO);

    //
    // Configure Rx frame-sync behaviour.
    //

    //
    // Set Rx frame sync source as external.
    //
    McBSP_setRxFrameSyncSource(base, MCBSP_RX_EXTERNAL_FRAME_SYNC_SOURCE);

    //
    // Disable DLB mode.
    //
    McBSP_disableLoopback(base);

    //
    // Set no external clock sync for CLKG i.e. GSYNC = 0.
    //
    McBSP_disableSRGSyncFSR(base);

    //
    // Configure Rx clock behaviour.
    //

    //
    // Set MCLKR pin as source for CLKR.
    //
    McBSP_setRxClockSource(base, MCBSP_EXTERNAL_RX_CLOCK_SOURCE);

    //
    // Set LSPCLK as input source for sample rate generator.
    //
    McBSP_setRxSRGClockSource(base, MCBSP_SRG_RX_CLOCK_SOURCE_LSPCLK);

    //
    // Set Divide down value for CLKG.
    //
    McBSP_setSRGDataClockDivider(base, 1);

    //
    // Wait for CPU cycles equivalent to 2 SRG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/LSPCLK). In this example
    // LSPCLK = SYSCLK/4.
    //
    MCBSP_CYCLE_NOP(8);
}

//
// End of File
//
