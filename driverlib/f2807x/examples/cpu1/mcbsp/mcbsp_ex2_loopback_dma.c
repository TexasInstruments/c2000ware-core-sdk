//#############################################################################
//
// FILE:   mcbsp_ex2_loopback_dma.c
//
// TITLE:  McBSP loopback with DMA example.
//
//! \addtogroup driver_example_list
//! <h1> McBSP loopback with DMA example. </h1>
//!
//! This example demonstrates the McBSP operation using internal loopback and
//! utilizes the DMA to transfer data from one buffer to the McBSP and then
//! from McBSP to another buffer.
//!
//! Initially, txData[] is filled with values from 0x0000- 0x007F. The DMA moves
//! the values in txData[] one by one to the DXRx registers of the McBSP. These
//! values are transmitted and subsequently received by the McBSP. Then, the
//! the DMA moves each data value to rxData[] as it is received by the McBSP.
//!
//! The sent data buffer looks like this: \n
//!    0000 0001 0002 0003 0004 0005 .... 007F   \n
//!
//! Three different serial word sizes can be tested.  Before compiling
//! this project, select the serial word size of 8, 16 or 32 by using
//! the \#define statements at the beginning of the code.
//!
//! This example uses DMA channel 1 and 2 interrupts. The incoming data is
//! checked for accuracy.
//!
//! \b External \b Connections \n
//! - None
//!
//! \b Watch \b Variables: \n
//! - \b txData - Sent data buffer
//! - \b rxData - Received data buffer
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
// Define to select delay in clock cycles.
//
#define MCBSP_CYCLE_NOP0(n)  __asm(" RPT #(" #n ") || NOP")
#define MCBSP_CYCLE_NOP(n)   MCBSP_CYCLE_NOP0(n)

//
// Define to select the word-size for McBSP operation to 8, 16 or 32 bit.
//
#define WORD_SIZE     8U
//#define WORD_SIZE     16U
//#define WORD_SIZE     32U

#pragma DATA_SECTION(txData, "ramgs0")
#pragma DATA_SECTION(rxData, "ramgs1")

//
// Globals
uint16_t txData[128];
uint16_t rxData[128];
uint16_t dataSize;
uint16_t errCountGlobal = 0;

//
// Function Prototypes
//
extern void setupMcBSPAPinmux(void);
void configDMAChannel1(void);
void configDMAChannel2(void);
void configDMA32Channel1(void);
void configDMA32Channel2(void);
void initDMA(void);
void initDMA32(void);
void initMcBSPLoopback(void);
void startDMA(void);

//
// ISR for DMA channel 1 & 2 interrupts.
//
__interrupt void localDMAINTCH1ISR(void);
__interrupt void localDMAINTCH2ISR(void);

//
// Main
//
void main(void)
{
    uint16_t i;

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

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_DMA_CH1, localDMAINTCH1ISR);
    Interrupt_register(INT_DMA_CH2, localDMAINTCH2ISR);

    //
    // User defined code.
    //
    dataSize = WORD_SIZE;

    //
    // Initialize data buffers.
    //
    for(i = 0; i<128; i++)
    {
        //
        // Fill txData with values between 0 and 0x007F.
        //
        txData[i] = i;

        //
        // Initialize rxData to 0xFFFF.
        //
        rxData[i] = 0xFFFFU;
    }

    //
    // Initialize DMA based on desired word size.
    //
    if(dataSize == 32)
    {
        //
        // Initialize DMA for 32-bit transfers.
        //
        initDMA32();
    }
    else
    {
        //
        // Initialize DMA for 16-bit transfers.
        //
        initDMA();
    }

    //
    // When using DMA, initialize DMA with peripheral interrupts first and then
    // initialize and release McBSP from reset.
    //
    startDMA();
    initMcBSPLoopback();

    //
    // Enable interrupts in PIE block.
    //
    Interrupt_enable(INT_DMA_CH1);
    Interrupt_enable(INT_DMA_CH2);

    //
    // Enable group 7 CPU interrupt.
    //
    IER = 0x40;

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
// Configure DMA Channel 1 - This function configures the DMA channel 1 for
// writing data to transmit buffer for 8 to 16-bit word size.
//
void configDMAChannel1()
{
    //
    // Configure DMA Channel 1 (16 - bit datasize).
    //
    DMA_disableInterrupt(DMA_CH1_BASE);

    //
    // Configure 1 word per burst.
    //
    DMA_configBurst(DMA_CH1_BASE, 1U, 0U, 0U);

    //
    // Configure 127 bursts per transfer.
    //
    DMA_configTransfer(DMA_CH1_BASE, 128, 1, 0);

    //
    // Src start address = buffer & dest start address = MCBSPA DXR
    //
    DMA_configAddresses(DMA_CH1_BASE,(const void*)(MCBSPA_BASE + MCBSP_O_DXR1),
                        (const void*)(&txData[0]));

    //
    // Clear peripheral interrupt event flag.
    //
    DMA_clearTriggerFlag(DMA_CH1_BASE);

    //
    // Clear sync error flag.
    //
    DMA_clearErrorFlag(DMA_CH1_BASE);

    //
    // Configure wrap size to maximum to avoid wrapping.
    //
    DMA_configWrap(DMA_CH1_BASE, 0x10000U, 0, 0x10000U, 0);

    //
    // Enable channel interrupt.
    //
    DMA_enableInterrupt(DMA_CH1_BASE);

    //
    // Interrupt at end of the transfer.
    //
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);

    //
    // Enable selected peripheral trigger to start a DMA transfer on DMA
    // channel 1.
    //
    DMA_enableTrigger(DMA_CH1_BASE);

    //
    // Configure DMA trigger source as McBSPA Tx EVT.
    //
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_MCBSPAMXEVT, 0);

    //
    // Clear any spurious Peripheral interrupts flags.
    //
    DMA_clearTriggerFlag(DMA_CH1_BASE);
}

//
// Configure DMA Channel 2 - This function configures the DMA channel 2 for
// reading from receive buffer for 8 to 16-bit word size.
//
void configDMAChannel2()
{
    //
    // Configure DMA Channel 2 (16 - bit datasize).
    //
    DMA_disableInterrupt(DMA_CH2_BASE);

    //
    // Configure 1 word per burst.
    //
    DMA_configBurst(DMA_CH2_BASE, 1U, 0U, 0U);

    //
    // Configure 127 bursts per transfer.
    //
    DMA_configTransfer(DMA_CH2_BASE, 128, 0, 1);

    //
    // Dest start address = buffer & Src start address = MCBSPA DRR
    //
    DMA_configAddresses(DMA_CH2_BASE,(const void*)(&rxData[0]),
                        (const void*)(MCBSPA_BASE + MCBSP_O_DRR1));

    //
    // Clear peripheral interrupt event flag.
    //
    DMA_clearTriggerFlag(DMA_CH2_BASE);

    //
    // Clear sync error flag.
    //
    DMA_clearErrorFlag(DMA_CH2_BASE);

    //
    // Configure wrap size to maximum to avoid wrapping.
    //
    DMA_configWrap(DMA_CH2_BASE, 0x10000U, 0, 0x10000U, 0);

    //
    // Enable channel interrupt.
    //
    DMA_enableInterrupt(DMA_CH2_BASE);

    //
    // Interrupt at end of the transfer.
    //
    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);

    //
    // Enable selected peripheral trigger to start a DMA transfer on DMA
    // channel 2.
    //
    DMA_enableTrigger(DMA_CH2_BASE);

    //
    // Configure DMA trigger source as McBSPA Tx EVT.
    //
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_MCBSPAMREVT, 0);

    //
    // Clear any spurious Peripheral interrupts flags.
    //
    DMA_clearTriggerFlag(DMA_CH2_BASE);
}

//
// Configure DMA 32 Channel 1 - This function configures the DMA channel 1 for
// writing to transmit buffer for 32-bit word size.
//
void configDMA32Channel1()
{
    //
    // Configure DMA Channel 1
    //
    DMA_disableInterrupt(DMA_CH1_BASE);

    //
    // Configure 2 word per burst. Increment one 16-bit address between words
    // for src & dest address.
    //
    DMA_configBurst(DMA_CH1_BASE, 2U, 1U, 1U);

    //
    // Configure 63 bursts per transfer. For src move to next word in buffer
    // after each word in a burst. For dest go back to DXR2.
    //
    DMA_configTransfer(DMA_CH1_BASE, 64, 1, 0xFFFF);

    //
    // Src start address = buffer & dest start address = MCBSPA DXR
    //
    DMA_configAddresses(DMA_CH1_BASE,(const void*)(MCBSPA_BASE + MCBSP_O_DXR2),
                        (const void*)(&txData[0]));

    //
    // Clear peripheral interrupt event flag.
    //
    DMA_clearTriggerFlag(DMA_CH1_BASE);

    //
    // Clear sync error flag.
    //
    DMA_clearErrorFlag(DMA_CH1_BASE);

    //
    // Configure wrap size to maximum to avoid wrapping.
    //
    DMA_configWrap(DMA_CH1_BASE, 0x10000U, 0, 0x10000U, 0);

    //
    // Enable channel interrupt.
    //
    DMA_enableInterrupt(DMA_CH1_BASE);

    //
    // Interrupt at end of the transfer.
    //
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);

    //
    // Enable selected peripheral trigger to start a DMA transfer on DMA
    // channel 1.
    //
    DMA_enableTrigger(DMA_CH1_BASE);

    //
    // Configure DMA trigger source as McBSPA Tx EVT.
    //
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_MCBSPAMXEVT, 0);

    //
    // Clear any spurious Peripheral interrupts flags.
    //
    DMA_clearTriggerFlag(DMA_CH1_BASE);
}

//
// Configure DMA Channel 2 - This function configures the DMA channel 2 for
// reading from receive buffer for 32-bit word-size.
//
void configDMA32Channel2()
{
    //
    // Configure DMA Channel 2 (16 - bit datasize).
    //
    DMA_disableInterrupt(DMA_CH2_BASE);

    //
    // Configure 2 word per burst. Increment one 16-bit address between words
    // for src & dest address.
    //
    DMA_configBurst(DMA_CH2_BASE, 2U, 1U, 1U);

    //
    // Configure 63 bursts per transfer. For src move to next word in buffer
    // after each word in a burst. For dest go back to DRR2.
    //
    DMA_configTransfer(DMA_CH2_BASE, 64, 0xFFFF, 1);

    //
    // Dest start address = buffer & Src start address = MCBSPA DRR
    //
    DMA_configAddresses(DMA_CH2_BASE, (const void*)(&rxData[0]),
                        (const void*)(MCBSPA_BASE + MCBSP_O_DRR2));

    //
    // Clear peripheral interrupt event flag.
    //
    DMA_clearTriggerFlag(DMA_CH2_BASE);

    //
    // Clear sync error flag.
    //
    DMA_clearErrorFlag(DMA_CH2_BASE);

    //
    // Configure wrap size to maximum to avoid wrapping.
    //
    DMA_configWrap(DMA_CH2_BASE, 0x10000U, 0, 0x10000U, 0);

    //
    // Enable channel interrupt.
    //
    DMA_enableInterrupt(DMA_CH2_BASE);

    //
    // Interrupt at end of the transfer.
    //
    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);

    //
    // Enable selected peripheral trigger to start a DMA transfer on DMA
    // channel 1.
    //
    DMA_enableTrigger(DMA_CH2_BASE);

    //
    // Configure DMA trigger source as McBSPA Rx EVT.
    //
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_MCBSPAMREVT, 0);

    //
    // Clear any spurious Peripheral interrupts flags.
    //
    DMA_clearTriggerFlag(DMA_CH2_BASE);
}

//
// Init DMA - This function initialises the DMA channel 1 & 2 for the 8 or
// 16-bit transfer.
//
void initDMA(void)
{
    DMA_initController();
    configDMAChannel1();
    configDMAChannel2();
}

//
// Init DMA 32 - This function initialises the DMA channel 1 & 2 for the 32-bit
// transfer.
//
void initDMA32(void)
{
    DMA_initController();
    configDMA32Channel1();
    configDMA32Channel2();
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
    McBSP_setFrameSyncPulsePeriod(MCBSPA_BASE, 31);

    //
    // Set frame-sync pulse width.
    //
    McBSP_setFrameSyncPulseWidthDivider(MCBSPA_BASE, 0);

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
    // Set Divide down value for CLKG. CLKG frequency = LSPCLK/(CLKGDV+1)
    //
    McBSP_setSRGDataClockDivider(MCBSPA_BASE, 0);

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
    HWREGH(MCBSPA_BASE + MCBSP_O_SPCR2) |= MCBSP_SPCR2_XRST;
    HWREGH(MCBSPA_BASE + MCBSP_O_SPCR1) |= MCBSP_SPCR1_RRST;
}

//
// Start DMA - This function starts DMA channel 1 & 2.
//
void startDMA(void)
{
    DMA_startChannel(DMA_CH1_BASE);
    DMA_startChannel(DMA_CH2_BASE);
}

//
// Local DMA INT CH1 ISR - ISR for DMA channel 1 interrupt.
//
__interrupt void localDMAINTCH1ISR(void)
{
    DMA_stopChannel(DMA_CH1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    return;
}

//
// Local DMA INT CH2 ISR - ISR for DMA channel 2 interrupt.
//
__interrupt void localDMAINTCH2ISR(void)
{
    uint16_t i;
    DMA_stopChannel(DMA_CH2_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    for(i = 0; i < 128; i++)
    {
        if(dataSize == 8)
        {
            if((rxData[i] & 0x00FF) != (txData[i] & 0x00FF))
            {
                errCountGlobal++;
                Example_Fail = 1;
                ESTOP0;
            }

            Example_PassCount++;
        }
        else
        {
            if(rxData[i] != txData[i])
            {
                errCountGlobal++;
                Example_Fail = 1;
                ESTOP0;
            }

            Example_PassCount++;
        }
    }
    return;
}

//
// End of File
//
