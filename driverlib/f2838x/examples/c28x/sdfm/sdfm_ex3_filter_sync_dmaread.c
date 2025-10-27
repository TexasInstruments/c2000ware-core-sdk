//###########################################################################
//
// FILE:   sdfm_ex3_filter_sync_dmaread.c
//
// TITLE:  SDFM Filter Sync DMA Example.
//
//! \addtogroup driver_example_list
//! <h1> SDFM Filter Sync DMA </h1>
//!
//! In this example, SDFM filter data is read by DMA. The
//! SDFM configuration is shown below:
//!  - SDFM1 used in this example. For using SDFM2, few modifications
//!    would be needed in the example.
//!  - MODE0 Input control mode selected
//!  - Comparator settings
//!      - Sinc3 filter selected
//!      - OSR = 32
//!      - hlt = 0x7FFF (Higher threshold setting)
//!      - llt  = 0x0000(Lower threshold setting)
//!  - Data filter settings
//!      - All the 4 filter modules enabled
//!      - Sinc3 filter selected
//!      - OSR = 256
//!      - All the 4 filters are synchronized by using MFE
//!       (Master Filter enable bit)
//!      - Filter output represented in 16 bit format
//!      - In order to convert 25 bit Data filter
//!        into 16 bit format user needs to right shift by 10 bits for
//!        Sinc3 filter with OSR = 256
//!  - Interrupt module settings for SDFM filter
//!      - All the 4 higher threshold comparator interrupts disabled
//!      - All the 4 lower threshold comparator interrupts disabled
//!      - All the 4 modulator failure interrupts disabled
//!      - All the 4 filter will generate interrupt when a new filter
//!        data is available
//!
//! \b External \b Connections \n
//!   - SDFM_PIN_MUX_OPTION1 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO16-GPIO31
//!   - SDFM_PIN_MUX_OPTION2 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO48-GPIO63
//!   - SDFM_PIN_MUX_OPTION3 Connect Sigma-Delta streams to
//!     (SDx-D1, SDx-C1 to SDx-D4,SDx-C4) on GPIO122-GPIO137
//!
//! \b Watch \b Variables \n
//! -  \b filter1Result - Output of filter 1
//! -  \b filter2Result - Output of filter 2
//! -  \b filter3Result - Output of filter 3
//! -  \b filter4Result - Output of filter 4
//!
//
//###########################################################################
//
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
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include <stdio.h>

//
// Defines
//
#define MAX_SAMPLES                               1024
#define SDFM_PIN_MUX_OPTION1                      1
#define SDFM_PIN_MUX_OPTION2                      2
#define SDFM_PIN_MUX_OPTION3                      3

//
// Globals
//
uint32_t sdfmInstance;
int16_t  filter1Result[MAX_SAMPLES];
int16_t  filter2Result[MAX_SAMPLES];
int16_t  filter3Result[MAX_SAMPLES];
int16_t  filter4Result[MAX_SAMPLES];
#pragma DATA_SECTION(filter1Result, "Filter1_RegsFile");
#pragma DATA_SECTION(filter2Result, "Filter2_RegsFile");
#pragma DATA_SECTION(filter3Result, "Filter3_RegsFile");
#pragma DATA_SECTION(filter4Result, "Filter4_RegsFile");

// Pointers for DMA source & destination addresses
int16_t *dma1SrcAddr, *dma1DestAddr;
int16_t *dma2SrcAddr, *dma2DestAddr;
int16_t *dma3SrcAddr, *dma3DestAddr;
int16_t *dma4SrcAddr, *dma4DestAddr;

// Variable to update DMA transfer status
volatile uint16_t dmaDone = 0;

//
// Function Prototypes
//
__interrupt void dmaCh1ISR(void);
__interrupt void dmaCh2ISR(void);
__interrupt void dmaCh3ISR(void);
__interrupt void dmaCh4ISR(void);
void initializeDMA(void);
void configureDMAChannels(void);
void configureSDFMPins(uint16_t sdfmPinOption);
void setPinConfig1(void);
void setPinConfig2(void);
void setPinConfig3(void);

//
// Main
//
void main(void)
{
    uint16_t  pinMuxOption;
    uint16_t  hlt, llt;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Setup GPIO by disabling pin locks and enabling pullups
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
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    Interrupt_register(INT_DMA_CH1, dmaCh1ISR);
    Interrupt_register(INT_DMA_CH2, dmaCh2ISR);
    Interrupt_register(INT_DMA_CH3, dmaCh3ISR);
    Interrupt_register(INT_DMA_CH4, dmaCh4ISR);

    //
    // Enable DMA INTn in the PIE: Group 7 __interrupt 1-6
    //
    Interrupt_enable(INT_DMA_CH1);
    Interrupt_enable(INT_DMA_CH2);
    Interrupt_enable(INT_DMA_CH3);
    Interrupt_enable(INT_DMA_CH4);

    //
    // Configure DMA for the transfer
    //
    initializeDMA();
    configureDMAChannels();

    //
    // Configure SDFM type to 0 and see if data ack generated SDINT.
    //
    SysCtl_configureType(SYSCTL_SDFMTYPE, 0, 1);

#ifdef CPU1
    pinMuxOption = SDFM_PIN_MUX_OPTION1;

    //
    // Configure GPIO pins as SDFM pins
    //
    configureSDFMPins(pinMuxOption);
#endif

    sdfmInstance = SDFM1_BASE;

    //
    // Input Control Unit
    //
    // Configure Input Control Unit: Modulator Clock rate = Modulator data rate
    //
    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_1,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_2,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_3,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(sdfmInstance, SDFM_FILTER_4,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    //
    // Comparator Module
    //
    hlt = 0x7FFF;  // Over value threshold settings
    llt = 0x0000;  // Under value threshold settings

    //
    // Configure Comparator module's comparator filter type and comparator's OSR
    // value, higher threshold, lower threshold
    //
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_THRESHOLD(hlt,llt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_THRESHOLD(hlt,llt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_3 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_THRESHOLD(hlt,llt)), 0);
    SDFM_configComparator(sdfmInstance,
        (SDFM_FILTER_4 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_THRESHOLD(hlt,llt)), 0);

    //
    // Data filter Module
    //
    // Configure Data filter modules filter type, OSR value and
    // enable / disable data filter
    //
    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_3 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    SDFM_configDataFilter(sdfmInstance, (SDFM_FILTER_4 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

    //
    // Enable Master filter bit: Unless this bit is set none of the filter
    // modules can be enabled. All the filter modules are synchronized when
    // master filter bit is enabled after individual filter modules are enabled.
    //
    SDFM_enableMainFilter(sdfmInstance);

    //
    // PWM11.CMPC, PWM11.CMPD signals can synchronize SDFM1 filters and
    // PWM12.CMPC and PWM12.CMPD signals can synchronize SDFM2 filters. This
    // option is not being used in this example for SDFM1.
    //
    SDFM_disableExternalReset(sdfmInstance, SDFM_FILTER_1);
    SDFM_disableExternalReset(sdfmInstance, SDFM_FILTER_2);
    SDFM_disableExternalReset(sdfmInstance, SDFM_FILTER_3);
    SDFM_disableExternalReset(sdfmInstance, SDFM_FILTER_4);

    //
    // Enable interrupts
    //
    // Following SDFM interrupts can be enabled / disabled using this function.
    //    Enable / disable comparator high threshold
    //    Enable / disable comparator low threshold
    //    Enable / disable modulator clock failure
    //    Enable / disable filter acknowledge
    //
    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_1,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_2,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_3,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(sdfmInstance, SDFM_FILTER_4,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_1,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_2,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_3,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(sdfmInstance, SDFM_FILTER_4,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    //
    // Enable master interrupt so that any of the filter interrupts can trigger
    // by SDFM interrupt to CPU
    //
    SDFM_enableMainInterrupt(sdfmInstance);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1);
}

//
// configureSDFMPins - Configure SDFM GPIOs
//
void configureSDFMPins(uint16_t sdfmPinOption)
{
    uint16_t pin;

    switch (sdfmPinOption)
    {
        case SDFM_PIN_MUX_OPTION1:
            for(pin = 16; pin <= 31; pin++)
            {
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setControllerCore(pin, GPIO_CORE_CPU1);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig1();
            break;

        case SDFM_PIN_MUX_OPTION2:
            for(pin = 48; pin <= 63; pin++)
            {
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setControllerCore(pin, GPIO_CORE_CPU1);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig2();
            break;

        case SDFM_PIN_MUX_OPTION3:
            for(pin = 122; pin <= 137; pin++)
            {
                GPIO_setControllerCore(pin, GPIO_CORE_CPU1);
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig3();
            break;
    }
}

//
// setPinConfig1 - sets the pin configuration for pins 16-21
//
void setPinConfig1()
{
    GPIO_setPinConfig(GPIO_16_SD1_D1);
    GPIO_setPinConfig(GPIO_17_SD1_C1);
    GPIO_setPinConfig(GPIO_18_SD1_D2);
    GPIO_setPinConfig(GPIO_19_SD1_C2);
    GPIO_setPinConfig(GPIO_20_SD1_D3);
    GPIO_setPinConfig(GPIO_21_SD1_C3);
    GPIO_setPinConfig(GPIO_22_SD1_D4);
    GPIO_setPinConfig(GPIO_23_SD1_C4);
    GPIO_setPinConfig(GPIO_24_SD2_D1);
    GPIO_setPinConfig(GPIO_25_SD2_C1);
    GPIO_setPinConfig(GPIO_26_SD2_D2);
    GPIO_setPinConfig(GPIO_27_SD2_C2);
    GPIO_setPinConfig(GPIO_28_SD2_D3);
    GPIO_setPinConfig(GPIO_29_SD2_C3);
    GPIO_setPinConfig(GPIO_30_SD2_D4);
    GPIO_setPinConfig(GPIO_31_SD2_C4);
}

//
// setPinConfig2 - sets the pin configuration for
// pins 48-63
//
void setPinConfig2()
{
    GPIO_setPinConfig(GPIO_48_SD1_D1);
    GPIO_setPinConfig(GPIO_49_SD1_C1);
    GPIO_setPinConfig(GPIO_50_SD1_D2);
    GPIO_setPinConfig(GPIO_51_SD1_C2);
    GPIO_setPinConfig(GPIO_52_SD1_D3);
    GPIO_setPinConfig(GPIO_53_SD1_C3);
    GPIO_setPinConfig(GPIO_54_SD1_D4);
    GPIO_setPinConfig(GPIO_55_SD1_C4);
    GPIO_setPinConfig(GPIO_56_SD2_D1);
    GPIO_setPinConfig(GPIO_57_SD2_C1);
    GPIO_setPinConfig(GPIO_58_SD2_D2);
    GPIO_setPinConfig(GPIO_59_SD2_C2);
    GPIO_setPinConfig(GPIO_60_SD2_D3);
    GPIO_setPinConfig(GPIO_61_SD2_C3);
    GPIO_setPinConfig(GPIO_62_SD2_D4);
    GPIO_setPinConfig(GPIO_63_SD2_C4);
}

//
// setPinConfig3 - sets the pin configuration for pins 122-137
//
void setPinConfig3()
{
    GPIO_setPinConfig(GPIO_122_SD1_D1);
    GPIO_setPinConfig(GPIO_123_SD1_C1);
    GPIO_setPinConfig(GPIO_124_SD1_D2);
    GPIO_setPinConfig(GPIO_125_SD1_C2);
    GPIO_setPinConfig(GPIO_126_SD1_D3);
    GPIO_setPinConfig(GPIO_127_SD1_C3);
    GPIO_setPinConfig(GPIO_128_SD1_D4);
    GPIO_setPinConfig(GPIO_129_SD1_C4);
    GPIO_setPinConfig(GPIO_130_SD2_D1);
    GPIO_setPinConfig(GPIO_131_SD2_C1);
    GPIO_setPinConfig(GPIO_132_SD2_D2);
    GPIO_setPinConfig(GPIO_133_SD2_C2);
    GPIO_setPinConfig(GPIO_134_SD2_D3);
    GPIO_setPinConfig(GPIO_135_SD2_C3);
    GPIO_setPinConfig(GPIO_136_SD2_D4);
    GPIO_setPinConfig(GPIO_137_SD2_C4);
}

//
// dmaCh1ISR - DMA Channel 1 ISR
//
__interrupt void dmaCh1ISR(void)
{
    dmaDone |= 0x0001;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    ESTOP0;
}

//
// dmaCh2ISR - DMA Channel 2 ISR
//
__interrupt void dmaCh2ISR(void)
{
    dmaDone |= 0x0002;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    ESTOP0;
}

//
// dmaCh3ISR - DMA Channel 3 ISR
//
__interrupt void dmaCh3ISR(void)
{
    dmaDone |= 0x0004;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    ESTOP0;
}

//
// dmaCh4ISR - DMA Channel 4 ISR
//
__interrupt void dmaCh4ISR(void)
{
    dmaDone |= 0x0008;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    ESTOP0;
}

//
// initializeDMA - Initialize DMA through hard reset
//
void initializeDMA(void)
{
    //
    // Perform a hard reset on DMA
    //
    DMA_initController();

    //
    // Allow DMA to run free on emulation suspend
    //
    DMA_setEmulationMode(DMA_EMULATION_FREE_RUN);
}

//
// configureDMAChannels - Configure DMA channels 1,2,3, and 4
//
void configureDMAChannels(void)
{
    //
    // Initialize the DMA channel addresses
    //
    dma1SrcAddr = (int16_t *)(0x5E17);
    dma1DestAddr = &filter1Result[0];
    dma2SrcAddr = (int16_t *)(0x5E27);
    dma2DestAddr = &filter2Result[0];
    dma3SrcAddr = (int16_t *)(0x5E37);
    dma3DestAddr = &filter3Result[0];
    dma4SrcAddr = (int16_t *)(0x5E47);
    dma4DestAddr = &filter4Result[0];

    DMA_configAddresses(DMA_CH1_BASE, dma1DestAddr, dma1SrcAddr);
    DMA_configAddresses(DMA_CH2_BASE, dma2DestAddr, dma2SrcAddr);
    DMA_configAddresses(DMA_CH3_BASE, dma3DestAddr, dma3SrcAddr);
    DMA_configAddresses(DMA_CH4_BASE, dma4DestAddr, dma4SrcAddr);

    //
    // Set up to use 16-bit data size
    // Pointers are based on 16-bit words
    // Increment by 1 (16 16-bit words)
    //

    //
    // BURST size = 1 | Source step size = 0 | Dest step size += 1
    //
    DMA_configBurst(DMA_CH1_BASE, 1, 0, 1);
    DMA_configBurst(DMA_CH2_BASE, 1, 0, 1);
    DMA_configBurst(DMA_CH3_BASE, 1, 0, 1);
    DMA_configBurst(DMA_CH4_BASE, 1, 0, 1);

    //
    // Transfer size = 0x400 | Source step size = 0 | Dest step size += 1
    //
    DMA_configTransfer(DMA_CH1_BASE, 0x400, 0, 1);
    DMA_configTransfer(DMA_CH2_BASE, 0x400, 0, 1);
    DMA_configTransfer(DMA_CH3_BASE, 0x400, 0, 1);
    DMA_configTransfer(DMA_CH4_BASE, 0x400, 0, 1);

    //
    // Configure wrap for DMA channels 1-4
    //
    DMA_configWrap(DMA_CH1_BASE, 0xFFFF, 0, 0xFFFF, 0);
    DMA_configWrap(DMA_CH2_BASE, 0xFFFF, 0, 0xFFFF, 0);
    DMA_configWrap(DMA_CH3_BASE, 0xFFFF, 0, 0xFFFF, 0);
    DMA_configWrap(DMA_CH4_BASE, 0xFFFF, 0, 0xFFFF, 0);

    //
    // Configure mode for DMA channels 1-4
    //

    // DMA channel 1
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_SDFM1FLT1,
               (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH1_BASE);
    DMA_disableOverrunInterrupt(DMA_CH1_BASE);
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH1_BASE);

    // DMA channel 2
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_SDFM1FLT1,
               (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH2_BASE);
    DMA_disableOverrunInterrupt(DMA_CH2_BASE);
    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH2_BASE);

    // DMA channel 3
    DMA_configMode(DMA_CH3_BASE, DMA_TRIGGER_SDFM1FLT1,
               (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH3_BASE);
    DMA_disableOverrunInterrupt(DMA_CH3_BASE);
    DMA_setInterruptMode(DMA_CH3_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH3_BASE);

    // DMA channel 4
    DMA_configMode(DMA_CH4_BASE, DMA_TRIGGER_SDFM1FLT1,
               (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH4_BASE);
    DMA_disableOverrunInterrupt(DMA_CH4_BASE);
    DMA_setInterruptMode(DMA_CH4_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH4_BASE);

    //
    // Start DMA channels
    //
    DMA_startChannel(DMA_CH1_BASE);
    DMA_startChannel(DMA_CH2_BASE);
    DMA_startChannel(DMA_CH3_BASE);
    DMA_startChannel(DMA_CH4_BASE);
}

//
// End of file
//
