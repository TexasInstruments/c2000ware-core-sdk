//###########################################################################
//
// FILE:   sdfm_ex1_filters.c
//
// TITLE:  SDFM Filter sync CPU Example.
//
//! \addtogroup driver_example_list
//! <h1> SDFM Filter Sync CPU</h1>
//!
//! In this example, SDFM filter data is read by CPU in SDFM ISR routine. The
//! SDFM configuration is shown below:
//!  -  SDFM used in this example - SDFM1
//!  -  Input control mode selected - MODE0
//!  -  Comparator settings
//!       - Sinc3 filter selected
//!       - OSR = 32
//!       - HLT = 0x7FFF (Higher threshold setting)
//!       - LLT  = 0x0000(Lower threshold setting)
//!  -  Data filter settings
//!      - All the 4 filter modules enabled
//!      - Sinc3 filter selected
//!      - OSR = 128
//!      - All the 4 filters are synchronized by using MFE
//!       (Master Filter enable bit)
//!      - Filter output represented in 16 bit format
//!      - In order to convert 25 bit Data filter
//!        into 16 bit format user needs to right shift by 8 bits for
//!        Sinc3 filter with OSR = 128
//!  - Interrupt module settings for SDFM filter
//!      - All the 4 higher threshold comparator interrupts disabled
//!      - All the 4 lower threshold comparator interrupts disabled
//!      - All the 4 modulator failure interrupts disabled
//!      - All the 4 filter will generate interrupt when a new filter data
//!        is available.
//!
//
//###########################################################################
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
#define MAX_SAMPLES               1024
#define SDFM_PIN_MUX_OPTION1      1
#define SDFM_PIN_MUX_OPTION2      2
#define SDFM_PIN_MUX_OPTION3      3

//
// Globals
//
uint16_t peripheralNumber;
int16_t  filter1Result[MAX_SAMPLES];
int16_t  filter2Result[MAX_SAMPLES];
int16_t  filter3Result[MAX_SAMPLES];
int16_t  filter4Result[MAX_SAMPLES];
#pragma DATA_SECTION(filter1Result, "Filter1_RegsFile");
#pragma DATA_SECTION(filter2Result, "Filter2_RegsFile");
#pragma DATA_SECTION(filter3Result, "Filter3_RegsFile");
#pragma DATA_SECTION(filter4Result, "Filter4_RegsFile");

//
// Defines
//
#define SDFM_FILTER_ENABLE 0x2U

//
// Function Prototypes
//
void configureSDFMPins(uint16_t);
void done(void);
__interrupt void sdfm1ISR(void);
__interrupt void sdfm2ISR(void);
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
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
    Interrupt_register(INT_SD1, sdfm1ISR);
    Interrupt_register(INT_SD2, sdfm2ISR);

    //
    // Enable SDFM1 amd SDFM2 interrupts
    //
    Interrupt_enable(INT_SD1);
    Interrupt_enable(INT_SD2);

#ifdef CPU1
    pinMuxOption = SDFM_PIN_MUX_OPTION1;

    //
    // Configure GPIO pins as SDFM pins
    //
    configureSDFMPins(pinMuxOption);
#endif

    //
    // Input Control Unit
    //
    // Configure Input Control Unit: Modulator Clock rate = Modulator data rate
    //
    SDFM_setupModulatorClock(SDFM1_BASE, SDFM_FILTER_1,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(SDFM1_BASE, SDFM_FILTER_2,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(SDFM1_BASE, SDFM_FILTER_3,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(SDFM1_BASE, SDFM_FILTER_4,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    //
    // Comparator Unit - over and under value threshold settings
    //
    hlt = 0x7FFF;
    llt = 0x0000;

    //
    // Configure Comparator Unit's comparator filter type and comparator's
    // OSR value, higher threshold, lower threshold
    //
    SDFM_configComparator(SDFM1_BASE,
        (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)));
    SDFM_configComparator(SDFM1_BASE,
        (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)));
    SDFM_configComparator(SDFM1_BASE,
        (SDFM_FILTER_3 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)));
    SDFM_configComparator(SDFM1_BASE,
        (SDFM_FILTER_4 | SDFM_FILTER_SINC_3 | SDFM_SET_OSR(32)),
        (SDFM_GET_LOW_THRESHOLD(llt) | SDFM_GET_HIGH_THRESHOLD(hlt)));

    //
    // Data Filter Unit
    //
    // Configure Data Filter Unit - filter type, OSR value and
    // enable / disable data filter
    //
    SDFM_configDataFilter(SDFM1_BASE, (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(128)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x0008)));

    SDFM_configDataFilter(SDFM1_BASE, (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(128)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x0008)));

    SDFM_configDataFilter(SDFM1_BASE, (SDFM_FILTER_3 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(128)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x0008)));

    SDFM_configDataFilter(SDFM1_BASE, (SDFM_FILTER_4 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(128)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x0008)));

    //
    // Enable Master filter bit: Unless this bit is set none of the filter modules
    // can be enabled. All the filter modules are synchronized when master filter
    // bit is enabled after individual filter modules are enabled.
    //
    SDFM_enableMasterFilter(SDFM1_BASE);

    //
    // PWM11.CMPC, PWM11.CMPD, PWM12.CMPC and PWM12.CMPD signals cannot synchronize
    // the filters. This option is not being used in this example.
    //
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_1);
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_2);
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_3);
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_4);

    //
    // Enable interrupts
    //
    // Following SDFM interrupts can be enabled / disabled using this function.
    // Enable / disable comparator high threshold
    // Enable / disable comparator low threshold
    // Enable / disable modulator clock failure
    // Enable / disable data filter acknowledge
    //
    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_1,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_2,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_3,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_4,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_1,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_2,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_3,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_4,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    //
    // Enable master interrupt so that any of the filter interrupts can trigger
    // by SDFM interrupt to CPU
    //
    SDFM_enableMasterInterrupt(SDFM1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Wait for an interrupt
    //
    while(1);
}

//
// sdfm1ISR - SDFM 1 ISR
//
__interrupt void sdfm1ISR(void)
{
    volatile uint32_t sdfmReadFlagRegister = 0;
    static uint16_t loopCounter1 = 0;

    SDFM_setOutputDataFormat(SDFM1_BASE, SDFM_FILTER_1,
                             SDFM_DATA_FORMAT_16_BIT);

    SDFM_setOutputDataFormat(SDFM1_BASE, SDFM_FILTER_2,
                             SDFM_DATA_FORMAT_16_BIT);

    SDFM_setOutputDataFormat(SDFM1_BASE, SDFM_FILTER_3,
                             SDFM_DATA_FORMAT_16_BIT);

    SDFM_setOutputDataFormat(SDFM1_BASE, SDFM_FILTER_4,
                             SDFM_DATA_FORMAT_16_BIT);

    //
    // Read SDFM flag register (SDIFLG)
    //
    sdfmReadFlagRegister = HWREG(SDFM1_BASE + SDFM_O_SDIFLG);

    if(loopCounter1 < MAX_SAMPLES)
    {
        //
        // Read each SDFM filter output and store it in respective filter
        // result array
        //
        filter1Result[loopCounter1] =
              (int16_t)(SDFM_getFilterData(SDFM1_BASE, SDFM_FILTER_1) >> 16U);

        filter2Result[loopCounter1] =
              (int16_t)(SDFM_getFilterData(SDFM1_BASE, SDFM_FILTER_2) >> 16U);

        filter3Result[loopCounter1] =
              (int16_t)(SDFM_getFilterData(SDFM1_BASE, SDFM_FILTER_3) >> 16U);

        filter4Result[loopCounter1++] =
              (int16_t)(SDFM_getFilterData(SDFM1_BASE, SDFM_FILTER_4) >> 16U);

        //
        // Clear SDFM flag register (SDIFLG)
        //
        SDFM_clearInterruptFlag(SDFM1_BASE, SDFM_MASTER_INTERRUPT_FLAG |
                                            0xFFFF);

        //
        // Read SDFM flag register (SDIFLG)
        //
        sdfmReadFlagRegister = HWREG(SDFM1_BASE + SDFM_O_SDIFLG);

        //
        // If any flags have been set, stop
        //
        if(sdfmReadFlagRegister != 0x0)
        {
            ESTOP0;
        }
    }
    else
    {
        ESTOP0;
        done();
    }

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 5
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

//
// sdfm2ISR - SDFM 2 ISR
//
__interrupt void sdfm2ISR(void)
{
    uint32_t sdfmReadFlagRegister = 0;
    static uint16_t loopCounter1 = 0;

    SDFM_setOutputDataFormat(SDFM2_BASE, SDFM_FILTER_1,
                             SDFM_DATA_FORMAT_16_BIT);

    SDFM_setOutputDataFormat(SDFM2_BASE, SDFM_FILTER_2,
                             SDFM_DATA_FORMAT_16_BIT);

    SDFM_setOutputDataFormat(SDFM2_BASE, SDFM_FILTER_3,
                             SDFM_DATA_FORMAT_16_BIT);

    SDFM_setOutputDataFormat(SDFM2_BASE, SDFM_FILTER_4,
                             SDFM_DATA_FORMAT_16_BIT);

    //
    // Read SDFM flag register (SDIFLG)
    //
    sdfmReadFlagRegister = HWREG(SDFM2_BASE + SDFM_O_SDIFLG);

    if(loopCounter1 < MAX_SAMPLES)
    {
        //
        // Read each SDFM filter output and store it in respective filter
        // result array
        //
        filter1Result[loopCounter1] =
                (int16_t)SDFM_getFilterData(SDFM2_BASE, SDFM_FILTER_1);

        filter2Result[loopCounter1] =
                (int16_t)SDFM_getFilterData(SDFM2_BASE, SDFM_FILTER_2);

        filter3Result[loopCounter1] =
                (int16_t)SDFM_getFilterData(SDFM2_BASE, SDFM_FILTER_3);

        filter4Result[loopCounter1++] =
                (int16_t)SDFM_getFilterData(SDFM2_BASE, SDFM_FILTER_4);

        //
        // Clear SDFM flag register
        //
        SDFM_clearInterruptFlag(SDFM2_BASE,
                                (SDFM_MASTER_INTERRUPT_FLAG | 0xFFFF));

        sdfmReadFlagRegister = HWREG(SDFM2_BASE + SDFM_O_SDIFLG);

        if(sdfmReadFlagRegister != 0x0)
        {
            ESTOP0;
        }
    }
    else
    {
        ESTOP0;
        done();
    }

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 5
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
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
                GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig1();
            break;

        case SDFM_PIN_MUX_OPTION2:
            for(pin = 48; pin <= 63; pin++)
            {
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig2();
            break;

        case SDFM_PIN_MUX_OPTION3:
            for(pin = 122; pin <= 137; pin++)
            {
                GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            setPinConfig3();
            break;
    }
}

//
// done - Function to halt debugger and stop application
//
void done(void)
{
    asm(" ESTOP0");
    for(;;);
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
// setPinConfig2 - sets the pin configuration for pins 48-63
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
// End of file
//
