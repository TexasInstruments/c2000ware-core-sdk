//#############################################################################
//
// FILE:   spi_ex4_spifsi_full_duplex.c
//
// TITLE: FSI and SPI communication full-duplex.
//
//! \addtogroup spifsi_communication
//! <h1>FSI and SPI communication full-duplex</h1>
//!
//! FSI supports SPI compatibility mode to talk to the devices not having FSI
//! but SPI module.
//! API to decode FSI frame received at SPI end is implemented and checks are
//! made to ensure received details(frame tag/type, userdata, data) match with
//! transfered frame.
//!
//! This program is the SPI part of SPI-to-FSI communication. It first
//! enables SPI module as a slave, driven by FSI TX, and sends flush sequence to
//! FSI when it receives Ping frame with tag 0. After flush sequence, SPI waits
//! for frames from FSI. When it receives first of duplicate frames, it enables
//! TALK bit of SPI_CTL register, decodes and encodes the frame, then stages the
//! echo-back frame. It also assumes that when frame is N_WORD_DATA_FRAME, number
//! of data words will be incremental by one. Then when it receives the second
//! part of duplicate frames, it waits for TX FIFO to be emptied out or staged
//! frames to be sent to FSI RX before disabling TALK bit of SPI_CTL register for
//! next staging.
//!
//! SPI-side also profiles SPIFSI_read/writeFrame() by how many cpu-cycle each
//! API call takes.
//!
//! To enable full functional duplex of SPI-to-FSI, you must load
//! fsi_ex11_spifsi_full_duplex to f28004x device and spi_ex4_spifsi_full_duplex
//! to any device that has SPI module. You must run SPI-side before FSI-side.
//!
//! If there are any comparison failures during transfers or any of error
//! event occurs, execution will stop.
//!
//! \b External \b Connections \n
//!   Number in parenthesis indicates a pin number on docking station.
//!   f28004x_FSITX                f2837x_SPIA                f28004x_FSIRX
//!   -TXCLK, GPIO7(56)         -> SPICLK, GPIO18(71)
//!   -TXD0, GPIO6(54)          -> SPISIMO, GPIO16(67)
//!   -TXD1, GPIO5(52)          -> ~SPISTE, GPIO19(73)
//!                                -SPISOMI, GPIO17(69)    -> RXD0, GPIO12(57)
//!
//! \b Watch \b Variables \n
//!  - \b spiRxCntr  Number of Data frames received.
//!  - \b spiTxCntr  Number of Data frames transmitted.
//!  - \b error      Non zero for error reading/writing from SPI FIFO.
//!
//
//#############################################################################
//
// $Release Date:  $
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
#include <stdbool.h>
#include <stdint.h>
#include "cputimer.h"
#include "driverlib.h"
#include "device.h"
#include "spifsi.h"

//
// Function Prototypes
//
void initialize(void);
void configureSPI(SPI_Mode spiMode);
void configureGPIOs(void);
void toggleOrOnLED(uint16_t ledType, uint16_t toggle);
void turnOffLEDs(void);
void turnOnLEDs(void);
void sendFlushSeq(void);
void disableTalk(void);
void enableTalk(void);
void configProfiler(uint32_t base);
void startProfiler(uint32_t base);
uint32_t stopProfiler(uint32_t base);
__interrupt void spiRxFIFOISR(void);

//
// Defines.
//
#define SPIFSI_CLK_SPEED 12500000U
#define ON               0x0000U
#define TOGGLE           0x0001U

//
// Interrupt flag.
//
volatile uint32_t spiRxIntReceived = 0;

//
// Globals.
//
SPIFSI_FrameInfo  spiFrameInfo;
SPIFSI_Error spifsiErrorStatus = SPIFSI_NO_ERROR;
uint32_t error = 0;
uint16_t spiRxCntr = 0;
uint16_t spiTxCntr = 0;

//
// Profile result arrays. Each holds number of cpu-cycle each frame took.
// Ping -> 0 (index), 1_WORD -> 1, 2_WORD -> 2, N_WORD with 3 words -> 3,
// 4_WORD -> 4, N_WORD with 5 words -> 5, 6_WORD -> 6, N_WORD with 7 words
// -> 7, and so on.
//
uint32_t decodeProfile[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint32_t encodeProfile[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t profileIndex = 0;

//*****************************************************************************
//
// Main
//
//*****************************************************************************
void main(void)
{
    //
    // Initialize.
    //
    initialize();

    //
    // Initialize spiFrameInfo.
    //
    uint16_t data[16] = {3};
    spiFrameInfo.data = data;

    //
    // Stage flush.
    //
    sendFlushSeq();
    turnOffLEDs();

    //
    // Infinite Loop.
    //
    while(1)
    {
        ;
    }
}

//*****************************************************************************
//
// sendFlushSeq - pushes 0xFFFF to SPI TX FIFO.
//
//*****************************************************************************
void sendFlushSeq(void)
{
    //
    // push the flush sequence.
    //
    uint16_t flushSeq = 0xFFFF;
    SPI_write16Bits(SPIA_BASE, &flushSeq);

    spiTxCntr++;
}


//*****************************************************************************
//
// Initialization module.
//
//*****************************************************************************
void initialize(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
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
    // Interrupts that are used in this example are re-mapped to ISR functions
    //
    Interrupt_register(INT_SPIA_RX, &spiRxFIFOISR);

    //
    // Configure GPIOs for SPIA_SLAVE from FSI in SPI-MODE.
    //
    configureGPIOs();

    //
    // Configure SPI module for Rx operation
    //
    configureSPI(SPI_MODE_SLAVE);

    //
    // Enable SPIA_RX interrupt.
    //
    Interrupt_enable(INT_SPIA_RX);

    //
    // Init profilers.
    //
    configProfiler(CPUTIMER0_BASE);

    //
    // Turn off LEDs.
    //
    turnOnLEDs();

    //
    // Enable Global Interrupt (INTM) and real-time interrupt (DBGM)
    //
    EINT;
    ERTM;
}

//*****************************************************************************
//
// configureSPI - configuration of SPIA to spiMode.
//
//*****************************************************************************
void configureSPI(SPI_Mode spiMode)
{
    //
    // Must put SPI into reset before configuring it
    //
    SPI_disableModule(SPIA_BASE);

    //
    // SPI configuration.
    //
    SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  spiMode, SPIFSI_CLK_SPEED, 16);
    SPI_disableLoopback(SPIA_BASE);
    SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_FREE_RUN);

    //
    // FIFO and interrupt configuration
    //
    SPI_enableFIFO(SPIA_BASE);
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
    SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX1, SPI_FIFO_RX1);
    SPI_enableInterrupt(SPIA_BASE, SPI_INT_RXFF);
    SPI_disableInterrupt(SPIA_BASE, SPI_INT_TXFF);

    //
    // Configuration complete. Enable the module.
    //
    SPI_enableModule(SPIA_BASE);
}

//*****************************************************************************
//
// configureGPIOs - configure GPIOs for SPIA_SLAVE connected to FSI full duplex.
//
//*****************************************************************************
void configureGPIOs(void)
{
    //
    // GPIO18 is the SPICLKA driven by FSITX_CLK.
    //
    GPIO_setMasterCore(18, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_18_SPICLKA);
    GPIO_setQualificationMode(18, GPIO_QUAL_ASYNC);

    //
    // GPIO16 is the SPISIMOA receiving TXD0.
    //
    GPIO_setMasterCore(16, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_16_SPISIMOA);
    GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC);

    //
    // GPIO19 is the SPISTEA receiving TXD1.
    //
    GPIO_setMasterCore(19, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_19_SPISTEA);
    GPIO_setQualificationMode(19, GPIO_QUAL_ASYNC);

    //
    // GPIO17 is the SPISOMIA writing to RXD0.
    //
    GPIO_setMasterCore(17, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_17_SPISOMIA);

    //
    // LED GPIO. Not sure if this will work for LaunchPad.
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);


}

//*****************************************************************************
//
// spiRxFIFOISR - Interrupt Line triggered when SPIA_RX_FIFO level reaches 1.
//
//*****************************************************************************
__interrupt void spiRxFIFOISR(void)
{
    //
    // Number of received frame.
    //
    spiRxCntr++;

    //
    // Incremental nLength when N_WORD_DATA_FRAME.
    //
    spiFrameInfo.nLength = profileIndex;

    //
    // Disable talk in priming frame, then stage in actual frame.
    //
    if((spiRxCntr % 2U) == 1U)
    {
        //
        // Wait for FSI-SPI communication to finish.
        //
        DEVICE_DELAY_US(1000);
        disableTalk();
    }
    else
    {
        //
        // Profile cpu-cycle of software-defined decode.
        //
        startProfiler(CPUTIMER0_BASE);
        spifsiErrorStatus = SPIFSI_readFrame(SPIA_BASE, &spiFrameInfo);
        decodeProfile[profileIndex] = stopProfiler(CPUTIMER0_BASE);

        //
        // Enable transfer of staged frame in next transmission.
        //
        enableTalk();

        //
        // Profile cpu-cycle of software-defined encode.
        //
        startProfiler(CPUTIMER0_BASE);

        //
        // Stage for next frame.
        //
        spifsiErrorStatus = SPIFSI_writeFrame(SPIA_BASE, &spiFrameInfo);
        encodeProfile[profileIndex] = stopProfiler(CPUTIMER0_BASE);
        profileIndex++;
        spiTxCntr++;


        if(spifsiErrorStatus)
        {
            error++;

            //
            // LED2 goes high if error.
            //
            toggleOrOnLED(DEVICE_GPIO_PIN_LED2, ON);
            ESTOP0;
        }

    }

    //
    // Reset RX FIFO.
    //
    SPI_resetRxFIFO(SPIA_BASE);

    toggleOrOnLED(DEVICE_GPIO_PIN_LED1, TOGGLE);

    spiRxIntReceived = 1U;
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
}

//*****************************************************************************
//
// toggleOrOnLED - toggles or turns on one of two LEDs.
//
//*****************************************************************************
void toggleOrOnLED(uint16_t ledType, uint16_t toggle) {
    //
    // Turn on LED
    //
    GPIO_writePin(ledType, 0);

    //
    // Delay for a bit.
    //
    DEVICE_DELAY_US(500000);

    if(toggle)
    {
        //
        // Turn off LED
        //
        GPIO_writePin(ledType, 1);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(500000);
    }
}

//*****************************************************************************
//
// turnOffLEDs - turns off both LEDs.
//
//*****************************************************************************
void turnOffLEDs(void)
{
    //
    // Turn off both leds
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);
}

//*****************************************************************************
//
// turnOnLEDs - turns on both LEDs.
//
//*****************************************************************************
void turnOnLEDs(void)
{
    //
    // Turn on both leds
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0);
}

//*****************************************************************************
//
// disableTalk - disables SPI_CTL_TALK bit.
//
//*****************************************************************************
void disableTalk(void)
{
    HWREGH(SPIA_BASE + SPI_O_CTL) = HWREGH(SPIA_BASE + SPI_O_CTL) & ~SPI_CTL_TALK;
}

//*****************************************************************************
//
// enableTalk - enables SPI_CTL_TALK bit.
//
//*****************************************************************************
void enableTalk(void)
{
    HWREGH(SPIA_BASE + SPI_O_CTL) = HWREGH(SPIA_BASE + SPI_O_CTL) | SPI_CTL_TALK;
}

//*****************************************************************************
//
// configProfiler - configures the CPUTimer specified by the parameter base for
// profiling cycle counts. base is the base address of a valid CPUTimer.
//
//
//*****************************************************************************
void configProfiler(uint32_t base)
{
    //
    // Clear overflow flag.
    //
    CPUTimer_clearOverflowFlag(base);

    //
    // Initialize timer period.
    //
    CPUTimer_setPeriod(base, 0xFFFFFFFFU);

    //
    // Initialize pre-scaler.
    //
    CPUTimer_setPreScaler(base, 0U);

    //
    // Reload timer counter.
    //
    CPUTimer_reloadTimerCounter(base);

    //
    // Set the timer to stop after next decrement on emulation halt.
    //
    CPUTimer_setEmulationMode(base, CPUTIMER_EMULATIONMODE_RUNFREE);
}

//*****************************************************************************
//
// startProfiler - starts the CPUTimer used for profiling cycles. 
//
//*****************************************************************************
void startProfiler(uint32_t base)
{
    //
    // Set TSS bit of register TCR
    //
    HWREGH(base + CPUTIMER_O_TCR) |= CPUTIMER_TCR_TSS;

    //
    // Reload the timer counter.
    //
    HWREGH(base + CPUTIMER_O_TCR) |= CPUTIMER_TCR_TRB;

    //
    // Clear TSS bit of register TCR
    //
    HWREGH(base + CPUTIMER_O_TCR) &= ~CPUTIMER_TCR_TSS;
}

//*****************************************************************************
//
// stopProfiler - stops the CPUTimer used for profiling cycles.
//
//*****************************************************************************
uint32_t stopProfiler(uint32_t base)
{
    //
    // Set TSS bit of register TCR
    //
    HWREGH(base + CPUTIMER_O_TCR) |= CPUTIMER_TCR_TSS;

    //
    // Return the cycle count
    //
    return(0xFFFFFFFFU - HWREG(base + CPUTIMER_O_TIM));
}

//
// End of File
//
