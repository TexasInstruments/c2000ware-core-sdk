//###########################################################################
//
// FILE:   sdfm_ex5_filter_sync_fifo_cpuread.c
//
// TITLE:  SDFM Type 1 Filter FIFO Example.
//
//! \addtogroup driver_example_list
//! <h1> SDFM Type 1 Filter FIFO </h1>
//!
//! This example configures SDFM1 filter to demonstrate data read through
//! CPU in FIFO & non-FIFO mode. Data filter is configured in mode 0
//! to select SINC3 filter with OSR of 256. Filter output is configured
//! for 16-bit format and data shift of 10 is used.
//!
//! This example demonstrates the FIFO usage if enabled. FIFO length is set
//! at 16 and data ready interrupt is configured to be triggered when FIFO is
//! full. In this example, SDFM filter data is read by CPU in SDFM Data Ready
//! ISR routine.
//!
//! \b External \b Connections \n
//!    Connect Sigma-Delta streams to (SD-D1, SD-C1 to SD-D4,SD-C4)
//!    on GPIO24-GPIO31
//!
//! \b Watch \b Variables \n
//! -  \b filter1Result - Output of filter 1
//!
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#define FIFO_INT_NUM              16U
#define SDFM_FILTER_ENABLE 0x2U

//
// Macro to enable FIFO mode. Make it zero to disable
// FIFO mode.
//
#define ENABLE_FIFO               1

//
// Globals
//
int16_t  filter1Result[MAX_SAMPLES];
#pragma DATA_SECTION(filter1Result, "Filter1_RegsFile");

//
// Function Prototypes
//
void configureSDFMPins(void);

//
// ISRs
//
__interrupt void sdfmFIFO1ISR(void);
__interrupt void sdfm1ErrorISR(void);

//
// Main
//
void main(void)
{
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
    Interrupt_register(INT_SDFM1DR1, sdfmFIFO1ISR);
    Interrupt_register(INT_SDFM1, sdfm1ErrorISR);

    //
    // Enable SDFM1 interrupts(Data Ready & Error interrupts)
    //
    Interrupt_enableMaster();
    Interrupt_enable(INT_SDFM1DR1);
    Interrupt_enable(INT_SDFM1);

    //
    // Configure GPIO pins as SDFM pins
    //
    configureSDFMPins();

    //
    // Input Control Unit
    //
    // Configure Input Control Unit: Modulator Clock rate = Modulator data rate
    //
    SDFM_setupModulatorClock(SDFM1_BASE, SDFM_FILTER_1,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    //
    // Data Filter Unit
    //

    // Configure Data Filter Unit - filter type, OSR value and
    // enable / disable data filter
    //
    SDFM_configDataFilter(SDFM1_BASE, (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(256)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x000A)));

#if (ENABLE_FIFO)
        //
        // Set data ready interrupt source as fifo interrupt
        //
        SDFM_setDataReadyInterruptSource(SDFM1_BASE, SDFM_FILTER_1,
                                         SDFM_DATA_READY_SOURCE_FIFO);

        //
        // Enable FIFO and set the FIFO interrupt level
        //
        SDFM_enableFIFOBuffer(SDFM1_BASE, SDFM_FILTER_1);

        SDFM_setFIFOInterruptLevel(SDFM1_BASE, SDFM_FILTER_1, FIFO_INT_NUM);

        SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_1,
                         (SDFM_FIFO_INTERRUPT | SDFM_FIFO_OVERFLOW_INTERRUPT));
#else
        //
        // Set data ready interrupt source as fifo interrupt
        //
        SDFM_setDataReadyInterruptSource(SDFM1_BASE, SDFM_FILTER_1,
                                         SDFM_DATA_READY_SOURCE_DIRECT);

        SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_1,
                             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT);
#endif


    //
    // Enable Master filter bit: Unless this bit is set none of the filter
    // modules can be enabled. All the filter modules are synchronized when
    // master filter bit is enabled after individual filter modules are enabled.
    //
    SDFM_enableMasterFilter(SDFM1_BASE);

    //
    // PWM11.CMPC, PWM11.CMPD, PWM12.CMPC and PWM12.CMPD signals cannot
    // synchronize the filters. This option is not being used in this example.
    //
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_1);

    //
    // Enable modulator failure interrupt, disable threshold interrupts
    //
    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_1,
                         SDFM_MODULATOR_FAILURE_INTERRUPT);

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_1,
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
// sdfm1ErrorISR - SDFM1 Error ISR
//
__interrupt void sdfm1ErrorISR(void)
{
    //
    // Clear SDFM flag register (SDIFLG)
    //
    SDFM_clearInterruptFlag(SDFM1_BASE, SDFM_MASTER_INTERRUPT_FLAG |
                            0xFFFF);

    //
    // Acknowledge this interrupt to receive more interrupts from group 5
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}


//
// sdfmFIFO1ISR - SDFM FIFO1 ISR
//
__interrupt void sdfmFIFO1ISR(void)
{
    uint16_t i;
    static uint16_t loopCounter1 = 0;

    SDFM_setOutputDataFormat(SDFM1_BASE, SDFM_FILTER_1,
                             SDFM_DATA_FORMAT_16_BIT);

    //
    // Read SDFM flag register (SDIFLG)
    //
    if(loopCounter1 >= MAX_SAMPLES)
    {
        ESTOP0;
    }
    else if(SDFM_getFIFOISRStatus(SDFM1_BASE, SDFM_FILTER_1) == 0x1U)
    {
        for(i = 0; i < FIFO_INT_NUM; i++)
        {
            filter1Result[loopCounter1++] =
                         (int16_t)(SDFM_getFIFOData(SDFM1_BASE,
                                                    SDFM_FILTER_1) >> 16U);
        }

    }
    else if(SDFM_getNewFilterDataStatus(SDFM1_BASE, SDFM_FILTER_1) == 0x1U)
    {
        filter1Result[loopCounter1++] =
               (int16_t)(SDFM_getFilterData(SDFM1_BASE, SDFM_FILTER_1) >> 16U);
    }

    //
    // Clear SDFM flag register (SDIFLG)
    //
    SDFM_clearInterruptFlag(SDFM1_BASE, SDFM_MASTER_INTERRUPT_FLAG |
                            SDFM_FILTER_1_FIFO_INTERRUPT_FLAG      |
                            SDFM_FILTER_1_NEW_DATA_FLAG            |
                            SDFM_FILTER_1_FIFO_OVERFLOW_FLAG);

    //
    // Acknowledge this interrupt to receive more interrupts from group 5
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

//
// configureSDFMPins - Configure SDFM GPIOs
//
void configureSDFMPins(void)
{
    uint16_t pin;
    for(pin = 24; pin <= 31; pin++)
    {
        GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
        GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
        GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
    }

    //
    // Configure GPIO16-GPIO31 as SDFM pins
    //
    GPIO_setPinConfig(GPIO_24_SD1_D1);
    GPIO_setPinConfig(GPIO_25_SD1_C1);
    GPIO_setPinConfig(GPIO_26_SD1_D2);
    GPIO_setPinConfig(GPIO_27_SD1_C2);
    GPIO_setPinConfig(GPIO_28_SD1_D3);
    GPIO_setPinConfig(GPIO_29_SD1_C3);
    GPIO_setPinConfig(GPIO_30_SD1_D4);
    GPIO_setPinConfig(GPIO_31_SD1_C4);
}

//
// End of file
//
