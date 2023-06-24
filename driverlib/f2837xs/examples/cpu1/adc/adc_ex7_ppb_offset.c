//###########################################################################
//
// FILE:   adc_ex7_ppb_offset.c
//
// TITLE:  ADC offset adjust using post-processing block
//
//! \addtogroup driver_example_list
//! <h1> ADC PPB Offset (adc_ppb_offset)</h1>
//!
//! This example software triggers the ADC.  Some SOCs have automatic offset
//! adjustment applied by the post-processing block. After the program runs,
//! the memory will contain ADC & post-processing block(PPB) results.
//!
//! \b External \b Connections \n
//!  - A2, D2 pins should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//!  - \b adcAResult \b: a digital representation of the voltage on pin A2
//!  - \b adcAPPBResult \b : a digital representation of the voltage
//!      on pin A2, minus 100 LSBs of automatically added offset
//!  - \b adcDResult \b: a digital representation of the voltage on pin D2
//!  - \b adcCPPBResult \b : a digital representation of the voltage
//!      on pin D2 plus 100 LSBs of automatically added offset
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

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define EX_ADC_RESOLUTION       12
// 12 for 12-bit conversion resolution, which supports (ADC_MODE_SINGLE_ENDED)
// Sample on single pin (VREFLO is the low reference)
// Or 16 for 16-bit conversion resolution, which supports (ADC_MODE_DIFFERENTIAL)
// Sample on pair of pins (difference between pins is converted, subject to
// common mode voltage requirements; see the device data manual)

//
// Function Prototypes
//
void configureADC(uint32_t adcBas);
void setupADCSoftware(uint32_t adcBase);
void setupPPBOffset(int16_t aOffset, int16_t bOffset);

//
// Globals
//
uint16_t adcAResult;
uint16_t adcAPPBResult;
uint16_t adcDResult;
uint16_t adcCPPBResult;

void main(void)
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
    // Configure the ADCs and power them up
    //
    configureADC(ADCA_BASE);
    configureADC(ADCD_BASE);

    //
    // Setup the ADCs for software conversions
    //
    setupADCSoftware(ADCA_BASE);
    setupADCSoftware(ADCD_BASE);

    //
    // Setup PPB offset correction.
    // conversion on channel A will subtract 100.
    // conversion on channel C will add 100.
    //
    setupPPBOffset(100, -100);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Convert, wait for completion, and store results.
        // Start conversions immediately via software, ADCA
        //
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER1);

        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == false);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

        //
        // Start conversions immediately via software, ADCD
        //
        ADC_forceSOC(ADCD_BASE, ADC_SOC_NUMBER0);
        ADC_forceSOC(ADCD_BASE, ADC_SOC_NUMBER1);

        //
        // Wait for ADCD to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1) == false);
        ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        adcAResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        adcAPPBResult = ADC_readPPBResult(ADCARESULT_BASE, ADC_PPB_NUMBER1);
        adcDResult = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER0);
        adcCPPBResult = ADC_readPPBResult(ADCDRESULT_BASE, ADC_PPB_NUMBER1);

        //
        // Software breakpoint, hit run again to get updated conversions
        //
        asm("   ESTOP0");
    }
    while(1);
}

//
// configureADC - Write ADC configurations and power up the ADC for both
//                ADC A and ADC C
//
void configureADC(uint32_t adcBase)
{
    //
    // Set ADCDLK divider to /4
    //
    ADC_setPrescaler(adcBase, ADC_CLK_DIV_4_0);

    //
    // Set resolution and signal mode (see #defines above) and load
    // corresponding trims.
    //
#if(EX_ADC_RESOLUTION == 12)
    ADC_setMode(adcBase, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
#elif(EX_ADC_RESOLUTION == 16)
    ADC_setMode(adcBase, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);
#endif

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(adcBase, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADCs and then delay for 1 ms
    //
    ADC_enableConverter(adcBase);

    //
    // Delay for 1ms to allow ADC time to power up
    //
    DEVICE_DELAY_US(1000);
}

//
// setupADCSoftware - Configure ADC SOC and acquisition window
//
void setupADCSoftware(uint32_t adcBase)
{
    uint16_t acqps;

    //
    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    //
    if(EX_ADC_RESOLUTION == 12)
    {
        acqps = 14; // 75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; // 320ns
    }
    //
    // - NOTE: A longer sampling window will be required if the ADC driving
    //   source is less than ideal (an ideal source would be a high bandwidth
    //   op-amp with a small series resistance). See TI application report
    //   SPRACT6 for guidance on ADC driver design.
    //

    //
    // Select the channels to convert and end of conversion flag
    // ADCA
    //
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)2U, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)2U, acqps);

    //
    // Configure source as EOC1, clear & enable the interrupt
    //
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER1, ADC_SOC_NUMBER1);
    ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER1);
    ADC_enableInterrupt(adcBase, ADC_INT_NUMBER1);
}

//
// setupPPBOffset - Configure PPB for SOC
//
void setupPPBOffset(int16_t aOffset, int16_t bOffset)
{
    //
    // PPB1 is associated with SOC1. PPB1 will subtract OFFCAL value
    // from associated SOC
    //
    // ADCA
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setPPBCalibrationOffset(ADCA_BASE, ADC_PPB_NUMBER1, aOffset);

    // ADCB
    ADC_setupPPB(ADCD_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER1);
    ADC_setPPBCalibrationOffset(ADCD_BASE, ADC_PPB_NUMBER1, bOffset);
}

//
// End of file
//
