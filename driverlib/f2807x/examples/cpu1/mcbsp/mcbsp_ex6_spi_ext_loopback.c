//#############################################################################
//
// FILE:   mcbsp_ex6_spi_ext_loopback.c
//
// TITLE:  McBSP external loopback example using SPI mode.
//
//! \addtogroup driver_example_list
//! <h1> McBSP external loopback example using SPI mode </h1>
//!
//! This example demonstrates the McBSP operation in SPI mode using external
//! loopback. This example configures McBSP instances available on the device
//! as SPI master and slave and demonstrates transfer of 32-bit word size data
//! with external loopback.
//!
//! \b External \b Connections \n
//! \b SPI Master(McBSPA)            \b SPI Slave(McBSPB)    \n
//! -  MCLKXA(SPICLK) (GPIO22)    -     MCLKXB(SPICLK) (GPIO26)
//! -  MFSXA (SPISTE) (GPIO23)    -     MFSXB (SPISTE) (GPIO27)
//! -  MDXA  (SPISIMO)(GPIO20)    -     MDRB  (SPISIMO)(GPIO25)
//! -  MDRA  (SPISOMI)(GPIO21)    -     MDXB  (SPISOMI)(GPIO24)
//!
//! \b Watch \b Variables: \n
//! - \b txData1 - Sent data word:     8 or 16-bit or low half of 32-bit
//! - \b txData2 - Sent data word:     upper half of 32-bit
//! - \b rxData1 - Received data word: 8 or 16-bit or low half of 32-bit
//! - \b rxData2 - Received data word: upper half of 32-bit
//! - \b errCountGlobal   - Error counter
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
extern void setupMcBSPBPinmux(void);
void initSPIMasterMode(uint32_t masterBase);
void initSPISlaveMode(uint32_t slaveBase);

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

    //
    // Initialize and release McBSPA and McBSPB from reset.
    //
    initSPIMasterMode(MCBSPA_BASE);
    initSPISlaveMode(MCBSPB_BASE);
    txData1 = 0x55aa;
    txData2 = 0xaa55;

    //
    // Main loop to transfer 32-bit words through McBSP in SPI mode
    // periodically.
    //
    while(1)
    {
        //
        // Write data to be transmitted from SPI master
        //
        tempData = (txData1|(((uint32_t)txData2) << 16U));
        while(!McBSP_isTxReady(MCBSPA_BASE));
        McBSP_write32bitData(MCBSPA_BASE, tempData);

        //
        // Check if data is received as SPI slave
        //
        while(!McBSP_isRxReady(MCBSPB_BASE));
        tempData = McBSP_read32bitData(MCBSPB_BASE);
        rxData1 = (uint16_t)(tempData & 0xFFFF);
        rxData2 = (uint16_t)(tempData >> 16U);
        if((rxData1 != txData1) || (rxData2 != txData2))
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
// Init SPI Master Mode - This function initializes McBSP in SPI master mode.
//
void initSPIMasterMode(uint32_t masterBase)
{
    //
    // Reset FS generator, sample rate generator, transmitter, receiver.
    //
    McBSP_resetFrameSyncLogic(masterBase);
    McBSP_resetSampleRateGenerator(masterBase);
    McBSP_resetTransmitter(masterBase);
    McBSP_resetReceiver(masterBase);

    //
    // Set Rx sign-extension and justification mode.
    //
    McBSP_setRxSignExtension(masterBase, MCBSP_RIGHT_JUSTIFY_FILL_ZERO);

    //
    // Enable clock stop mode.
    //
    McBSP_setClockStopMode(masterBase, MCBSP_CLOCK_SPI_MODE_NO_DELAY);

    //
    // Set Rx & Tx delay to 1 cycle.
    //
    McBSP_setRxDataDelayBits(masterBase, MCBSP_DATA_DELAY_BIT_1);
    McBSP_setTxDataDelayBits(masterBase, MCBSP_DATA_DELAY_BIT_1);

    //
    // Set CLKX & FSX source as sample rate generator.
    //
    McBSP_setTxClockSource(masterBase, MCBSP_INTERNAL_TX_CLOCK_SOURCE);
    McBSP_setRxClockSource(masterBase, MCBSP_INTERNAL_RX_CLOCK_SOURCE);
    McBSP_setTxFrameSyncSource(masterBase, MCBSP_TX_INTERNAL_FRAME_SYNC_SOURCE);
    McBSP_setRxFrameSyncSource(masterBase, MCBSP_RX_INTERNAL_FRAME_SYNC_SOURCE);

    //
    // Set Tx and Rx clock and frame-sync polarity.
    //
    McBSP_setTxFrameSyncPolarity(masterBase, MCBSP_TX_FRAME_SYNC_POLARITY_LOW);
    McBSP_setTxClockPolarity(masterBase, MCBSP_TX_POLARITY_RISING_EDGE);
    McBSP_setRxClockPolarity(masterBase, MCBSP_RX_POLARITY_FALLING_EDGE);

    //
    // Initialize McBSP data length.
    //
    McBSP_setRxDataSize(masterBase, MCBSP_PHASE_ONE_FRAME,
                        MCBSP_BITS_PER_WORD_32, 0);
    McBSP_setTxDataSize(masterBase, MCBSP_PHASE_ONE_FRAME,
                        MCBSP_BITS_PER_WORD_32, 0);

    //
    // Set frame synchronization pulse period to 1 CLKG cycle.
    //
    McBSP_setFrameSyncPulsePeriod(masterBase, 0);

    //
    // Set frame-sync pulse width to 1 CLKG cycle.
    //
    McBSP_setFrameSyncPulseWidthDivider(masterBase, 0);

    //
    // Set the trigger source for internally generated frame-sync pulse.
    //
    McBSP_setTxInternalFrameSyncSource(masterBase,
                                       MCBSP_TX_INTERNAL_FRAME_SYNC_DATA);

    //
    // Set LSPCLK as input source for sample rate generator.
    //
    McBSP_setTxSRGClockSource(masterBase, MCBSP_SRG_TX_CLOCK_SOURCE_LSPCLK);

    //
    // Set Divide down value for CLKG.
    //
    McBSP_setSRGDataClockDivider(masterBase, 16);

    //
    // Set no external clock sync for CLKG.
    //
    McBSP_disableSRGSyncFSR(masterBase);

    //
    // Wait for CPU cycles equivalent to 2 SRG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/LSPCLK). In this example
    // LSPCLK = SYSCLK/4.
    //
    MCBSP_CYCLE_NOP(8);

    //
    // Enable Sample rate generator and wait for at least 2 CLKG clock cycles.
    //
    McBSP_enableSampleRateGenerator(masterBase);
    McBSP_enableFrameSyncLogic(masterBase);

    //
    // Wait for CPU cycles equivalent to 2 CLKG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/(LSPCLK/(1+CLKGDV_VAL))). In this
    // example LSPCLK = SYSCLK/4 and CLKGDV_VAL = 1.
    //
    MCBSP_CYCLE_NOP(16);

    //
    // Release Rx, Tx and frame-sync generator from reset.
    //
    McBSP_enableTransmitter(masterBase);
    McBSP_enableReceiver(masterBase);

    //
    // Wait for CPU cycles equivalent to 2 SRG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/LSPCLK). In this example
    // LSPCLK = SYSCLK/4.
    //
    MCBSP_CYCLE_NOP(8);
}


//
// Init SPI Slave Mode - This function initializes McBSP in SPI slave mode.
//
void initSPISlaveMode(uint32_t slaveBase)
{
    //
    // Reset FS generator, sample rate generator, transmitter, receiver.
    //
    McBSP_resetFrameSyncLogic(slaveBase);
    McBSP_resetSampleRateGenerator(slaveBase);
    McBSP_resetTransmitter(slaveBase);
    McBSP_resetReceiver(slaveBase);

    //
    // Set Rx sign-extension and justification mode.
    //
    McBSP_setRxSignExtension(slaveBase, MCBSP_RIGHT_JUSTIFY_FILL_ZERO);

    //
    // Enable clock stop mode.
    //
    McBSP_setClockStopMode(slaveBase, MCBSP_CLOCK_SPI_MODE_NO_DELAY);

    //
    // Set Rx & Tx delay to 0.
    //
    McBSP_setRxDataDelayBits(slaveBase, MCBSP_DATA_DELAY_BIT_0);
    McBSP_setTxDataDelayBits(slaveBase, MCBSP_DATA_DELAY_BIT_0);

    //
    // Set CLKX & FSX as inputs
    //
    McBSP_setTxClockSource(slaveBase, MCBSP_EXTERNAL_TX_CLOCK_SOURCE);
    McBSP_setTxFrameSyncSource(slaveBase, MCBSP_TX_EXTERNAL_FRAME_SYNC_SOURCE);

    //
    // Set Tx and Rx clock and frame-sync polarity.
    //
    McBSP_setTxFrameSyncPolarity(slaveBase, MCBSP_TX_FRAME_SYNC_POLARITY_LOW);
    McBSP_setTxClockPolarity(slaveBase, MCBSP_TX_POLARITY_RISING_EDGE);
    McBSP_setRxClockPolarity(slaveBase, MCBSP_RX_POLARITY_FALLING_EDGE);

    //
    // Initialize McBSP data length.
    //
    McBSP_setRxDataSize(slaveBase, MCBSP_PHASE_ONE_FRAME,
                        MCBSP_BITS_PER_WORD_32, 0);
    McBSP_setTxDataSize(slaveBase, MCBSP_PHASE_ONE_FRAME,
                        MCBSP_BITS_PER_WORD_32, 0);

    //
    // Set LSPCLK as input source for sample rate generator.
    //
    McBSP_setTxSRGClockSource(slaveBase, MCBSP_SRG_TX_CLOCK_SOURCE_LSPCLK);

    //
    // Set Divide down value for CLKG.
    //
    McBSP_setSRGDataClockDivider(slaveBase, 1);

    //
    // Set no external clock sync for CLKG.
    //
    McBSP_disableSRGSyncFSR(slaveBase);

    //
    // Wait for CPU cycles equivalent to 2 SRG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/LSPCLK). In this example
    // LSPCLK = SYSCLK/4.
    //
    MCBSP_CYCLE_NOP(8);

    //
    // Enable Sample rate generator and wait for at least 2 CLKG clock cycles.
    //
    McBSP_enableSampleRateGenerator(slaveBase);
    McBSP_enableFrameSyncLogic(slaveBase);

    //
    // Wait for CPU cycles equivalent to 2 CLKG cycles-init delay.
    // Total cycles required = 2*(SYSCLK/(LSPCLK/(1+CLKGDV_VAL))). In this
    // example LSPCLK = SYSCLK/4 and CLKGDV_VAL = 1.
    //
    MCBSP_CYCLE_NOP(16);

    //
    // Release Rx, Tx and frame-sync generator from reset.
    //
    McBSP_enableTransmitter(slaveBase);
    McBSP_enableReceiver(slaveBase);

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
