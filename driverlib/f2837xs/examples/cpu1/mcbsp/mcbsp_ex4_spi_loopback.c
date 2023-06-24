//#############################################################################
//
// FILE:   mcbsp_ex4_spi_loopback.c
//
// TITLE:  McBSP loopback example using SPI mode.
//
//! \addtogroup driver_example_list
//! <h1> McBSP loopback example using SPI mode </h1>
//!
//! This example demonstrates the McBSP operation in SPI mode using internal
//! loopback. This example demonstrates SPI master mode transfer of 32-bit word
//! size with digital loopback enabled.
//!
//! \b McBSP \b Signals - \b SPI \b equivalent
//!  - MCLKX            - SPICLK  (master)
//!  - MFSX             - SPISTE  (master)
//!  - MDX              - SPISIMO
//!  - MCLKR            - SPICLK  (slave - not used for this example)
//!  - MFSR             - SPISTE  (slave - not used for this example)
//!  - MDR              - SPISOMI (not used for this example)
//!
//! \b External \b Connections \n
//! - None
//!
//! \b Watch \b Variables: \n
//! - \b txData1 - Sent data word:     8 or 16-bit or low half of 32-bit
//! - \b txData2 - Sent data word:     upper half of 32-bit
//! - \b rxData1 - Received data word: 8 or 16-bit or low half of 32-bit
//! - \b rxData2 - Received data word: upper half of 32-bit
//! - \b errCountGlobal   - Error counter
//
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

//
// Function Prototypes
//
extern void setupMcBSPAPinmux(void);
void initSPImode(void);

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

    //
    // Initialize and release peripheral (McBSP) from reset.
    //
    initSPImode();
    txData1 = 0x55aa;
    txData2 = 0xaa55;

    //
    // Main loop to transfer 32-bit words through McBSP in SPI mode
    // periodically.
    //
    while(1)
    {
        //
        // Write data to be transmitted.
        //
        tempData = (txData1|(((uint32_t)txData2) << 16U));
        while(!McBSP_isTxReady(MCBSPA_BASE));
        McBSP_write32bitData(MCBSPA_BASE, tempData);

        //
        // Check if data is recieved.
        //
        while(!McBSP_isRxReady(MCBSPA_BASE));
        tempData = McBSP_read32bitData(MCBSPA_BASE);
        rxData1 = (uint16_t)(tempData & 0xFFFF);
        rxData2 = (uint16_t)(tempData >> 16U);
        if(rxData1 != txData1 || rxData2 != txData2)
        {
            errCountGlobal++;
            Example_Fail = 1;
            ESTOP0;
        }
        txData1 ^= 0xFFFF;
        txData2 ^= 0xFFFF;
        NOP;

        Example_PassCount++;
    }
}

//
// Init SPI Mode - This function initialises McBSP in SPI with digital loopback
// mode.
//
void initSPImode()
{
    //
    // Reset FS generator, sample rate generator, transmitter, receiver.
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
    // Enable clock stop mode.
    //
    McBSP_setClockStopMode(MCBSPA_BASE, MCBSP_CLOCK_SPI_MODE_NO_DELAY);

    //
    // Set Rx & Tx delay to 1 cycle.
    //
    McBSP_setRxDataDelayBits(MCBSPA_BASE, MCBSP_DATA_DELAY_BIT_1);
    McBSP_setTxDataDelayBits(MCBSPA_BASE, MCBSP_DATA_DELAY_BIT_1);

    //
    // Set CLKX & FSX source as sample rate generator.
    //
    McBSP_setTxClockSource(MCBSPA_BASE, MCBSP_INTERNAL_TX_CLOCK_SOURCE);
    McBSP_setRxClockSource(MCBSPA_BASE, MCBSP_INTERNAL_RX_CLOCK_SOURCE);
    McBSP_setTxFrameSyncSource(MCBSPA_BASE, MCBSP_TX_INTERNAL_FRAME_SYNC_SOURCE);
    McBSP_setRxFrameSyncSource(MCBSPA_BASE, MCBSP_RX_INTERNAL_FRAME_SYNC_SOURCE);

    //
    // Set Tx and Rx clock and frame-sync polarity.
    //
    McBSP_setTxFrameSyncPolarity(MCBSPA_BASE, MCBSP_TX_FRAME_SYNC_POLARITY_LOW);
    McBSP_setTxClockPolarity(MCBSPA_BASE, MCBSP_TX_POLARITY_RISING_EDGE);
    McBSP_setRxClockPolarity(MCBSPA_BASE, MCBSP_RX_POLARITY_FALLING_EDGE);

    //
    // Initialize McBSP data length.
    //
    McBSP_setRxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                        MCBSP_BITS_PER_WORD_32, 0);
    McBSP_setTxDataSize(MCBSPA_BASE, MCBSP_PHASE_ONE_FRAME,
                        MCBSP_BITS_PER_WORD_32, 0);

    //
    // Set frame synchronization pulse period to 1 CLKG cycle.
    //
    McBSP_setFrameSyncPulsePeriod(MCBSPA_BASE, 0);

    //
    // Set frame-sync pulse width to 1 CLKG cycle.
    //
    McBSP_setFrameSyncPulseWidthDivider(MCBSPA_BASE, 0);

    //
    // Set the trigger source for internally generated frame-sync pulse.
    //
    McBSP_setTxInternalFrameSyncSource(MCBSPA_BASE,
                                       MCBSP_TX_INTERNAL_FRAME_SYNC_DATA);

    //
    // Set LSPCLK as input source for sample rate generator.
    //
    McBSP_setTxSRGClockSource(MCBSPA_BASE, MCBSP_SRG_TX_CLOCK_SOURCE_LSPCLK);

    //
    // Set Divide down value for CLKG.
    //
    McBSP_setSRGDataClockDivider(MCBSPA_BASE, 16);

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
    // Enable Sample rate generator and wait for at least 2 CLKG clock cycles.
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
    // Release Rx, Tx and frame-sync generator from reset.
    //
    McBSP_enableTransmitter(MCBSPA_BASE);
    McBSP_enableReceiver(MCBSPA_BASE);

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
