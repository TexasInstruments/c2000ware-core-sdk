//###########################################################################
//
// FILE:   sdfm_ex5_type1_filter_fifo_cpuread.c
//
// TITLE:  SDFM Type 1 Filter FIFO Example.
//
//! \addtogroup driver_example_list
//! <h1> SDFM Type 1 Filter FIFO </h1>
//!
//! This example configures SDFM1 filter in type 1 to demonstrate data read
//! through CPU in FIFO & non-FIFO mode. Data filter is configured in mode 0
//! to select SINC3 filter with OSR of 256. Filter output is configured
//! for 16-bit format and data shift of 10 is used.
//!
//! This example demonstrates the FIFO usage if enabled. FIFO length is set
//! at 16 and data ready interrupt is configured to be triggered when FIFO is
//! full. In this example, SDFM filter data is read by CPU in SDFM Data Ready
//! ISR routine.
//!
//! \b External \b Connections \n
//!   - SDFM_PIN_MUX_OPTION1 Connect Sigma-Delta streams(SD1-D1, SD1-C1) to
//!     (GPIO16, GPIO17)
//!   - SDFM_PIN_MUX_OPTION2 Connect Sigma-Delta streams(SD1-D1, SD1-C1) to
//!     (GPIO48, GPIO49)
//!   - SDFM_PIN_MUX_OPTION3 Connect Sigma-Delta streams(SD1-D1, SD1-C1) to
//!     (GPIO122, GPIO123)
//!
//! \b Watch \b Variables \n
//! -  \b filter1Result - Output of filter 1
//!
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
// Macro for pin-mux options
//
#define SDFM_PIN_MUX_OPTION1      1
#define SDFM_PIN_MUX_OPTION2      2
#define SDFM_PIN_MUX_OPTION3      3

//
// Globals
//
int16_t  filter1Result[MAX_SAMPLES];
#pragma DATA_SECTION(filter1Result, "Filter1_RegsFile");

//
// Function Prototypes
//
void configureSDFMPins(uint16_t);
void setPinConfig1(void);
void setPinConfig2(void);
void setPinConfig3(void);
void done(void);

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
    uint16_t  pinMuxOption;

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
    Interrupt_enableGlobal();
    Interrupt_enable(INT_SDFM1DR1);
    Interrupt_enable(INT_SDFM1);

    //
    // Configure SDFM type to 1.
    //
    SysCtl_configureType(SYSCTL_SDFMTYPE, 1, 1);

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
    SDFM_enableMainFilter(SDFM1_BASE);

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
    SDFM_enableMainInterrupt(SDFM1_BASE);

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
    SDFM_clearInterruptFlag(SDFM1_BASE, SDFM_MAIN_INTERRUPT_FLAG |
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
    SDFM_clearInterruptFlag(SDFM1_BASE, SDFM_MAIN_INTERRUPT_FLAG |
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
// End of file
//
