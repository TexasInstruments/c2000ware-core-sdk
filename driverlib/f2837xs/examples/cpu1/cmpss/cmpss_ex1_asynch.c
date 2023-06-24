//#############################################################################
//
// FILE:   cmpss_ex1_asynch.c
//
// TITLE:  CMPSS Asynchronous Trip
//
//! \addtogroup driver_example_list
//! <h1> CMPSS Asynchronous Trip </h1>
//!
//! This example enables the CMPSS1 COMPH comparator and feeds the asynchronous
//! CTRIPOUTH signal to the GPIO14/OUTPUTXBAR3 pin and CTRIPH to GPIO15/EPWM8B.
//!
//! CMPSS is configured to generate trip signals to trip the EPWM signals.
//! CMPIN1P is used to give positive input and internal DAC is configured
//! to provide the negative input. Internal DAC is configured to provide a
//! signal at VDD/2. An EPWM signal is generated at GPIO15 and is configured
//! to be tripped by CTRIPOUTH.
//!
//! When a low input(VSS) is provided to CMPIN1P,
//!     - Trip signal(GPIO14) output is low
//!     - PWM8B(GPIO15) gives a PWM signal
//!
//! When a high input(higher than VDD/2) is provided to CMPIN1P,
//!     - Trip signal(GPIO14) output turns high
//!     - PWM8B(GPIO15) gets tripped and outputs as high
//!
//! \b External \b Connections \n
//!  - Outputs can be observed on GPIO14 and GPIO15
//!  - Comparator input pin is on ADCINA2
//!
//! \b Watch \b Variables \n
//!  - None
//!
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
#include "driverlib.h"
#include "device.h"

//
// Function Prototypes
//
void initCMPSS(void);
void initEPWM(void);

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
    // Set up COMP1H
    //
    initCMPSS();

    //
    // Set up ePWM8 to take CTRIPH as TRIP4 for its DC trip input
    //
    initEPWM();

    //
    // Configure GPIO14 to output CTRIPOUT1H (routed through XBAROUTPUT3) and
    // GPIO15 to output CTRIPH (routed through ePWM TRIP4 and ePWM8)
    //
    GPIO_setPinConfig(GPIO_14_OUTPUTXBAR3);
    GPIO_setPinConfig(GPIO_15_EPWM8B);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Trip flag is set when CTRIP signal is asserted
        //
        if((EPWM_getTripZoneFlagStatus(EPWM8_BASE) &
            EPWM_TZ_FLAG_OST) != 0U)
        {
            //
            // Wait for comparator CTRIP to de-assert
            //
            while((CMPSS_getStatus(CMPSS1_BASE) & CMPSS_STS_HI_FILTOUT) != 0U)
            {
                ;
            }

            //
            // Clear trip flags
            //
            EPWM_clearTripZoneFlag(EPWM8_BASE, EPWM_TZ_INTERRUPT |
                                   EPWM_TZ_FLAG_OST);
        }
    }
}


//
// initCMPSS - Function to configure the high comparator of CMPSS1
//
void initCMPSS(void)
{
    //
    // Enable CMPSS and configure the negative input signal to come from
    // the DAC
    //
    CMPSS_enableModule(CMPSS1_BASE);
    CMPSS_configHighComparator(CMPSS1_BASE, CMPSS_INSRC_DAC);

    //
    // Use VDDA as the reference for the DAC and set DAC value to midpoint for
    // arbitrary reference.
    //
    CMPSS_configDAC(CMPSS1_BASE, CMPSS_DACREF_VDDA | CMPSS_DACVAL_SYSCLK |
                    CMPSS_DACSRC_SHDW);
    CMPSS_setDACValueHigh(CMPSS1_BASE, 2048);

    //
    // Configure the output signals. Both CTRIPH and CTRIPOUTH will be fed by
    // the asynchronous comparator output.
    //
    CMPSS_configOutputsHigh(CMPSS1_BASE, CMPSS_TRIP_ASYNC_COMP |
                            CMPSS_TRIPOUT_ASYNC_COMP);

    //
    // Setup the Output X-BAR to output CTRIPOUTH on OUTPUTXBAR3
    //
    XBAR_setOutputMuxConfig(XBAR_OUTPUT3, XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH);
    XBAR_enableOutputMux(XBAR_OUTPUT3, XBAR_MUX00);
}

//
// initEPWM - Function to configure ePWM8 and the ePWM X-BAR to take CTRIPH as
//            the DC trip input
//
void initEPWM(void)
{
    //
    // Disable the ePWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set the time base clock prescalers to /1
    //
    EPWM_setClockPrescaler(EPWM8_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Initializing dummy values for ePWM counter and period
    //
    EPWM_setTimeBaseCounter(EPWM8_BASE, 0);
    EPWM_setTimeBasePeriod(EPWM8_BASE, 0xFFFF);

    //
    // Set-up compare
    //
    EPWM_setCounterCompareValue(EPWM8_BASE, EPWM_COUNTER_COMPARE_B, 0x8000);

    //
    // Set actions
    //
    EPWM_setActionQualifierAction(EPWM8_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setActionQualifierAction(EPWM8_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Configure ePWM8B to output high on TZB TRIP
    //
    EPWM_setTripZoneAction(EPWM8_BASE, EPWM_TZ_ACTION_EVENT_TZB,
                           EPWM_TZ_ACTION_HIGH);

    //
    // Trigger event when DCBH is high
    //
    EPWM_setTripZoneDigitalCompareEventCondition(EPWM8_BASE,
                                                 EPWM_TZ_DC_OUTPUT_B1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);

    //
    // Configure DCBH to use TRIP4 as an input
    //
    EPWM_enableDigitalCompareTripCombinationInput(EPWM8_BASE,
                                                  EPWM_DC_COMBINATIONAL_TRIPIN4,
                                                  EPWM_DC_TYPE_DCBH);
    //
    // Enable DCB as OST
    //
    EPWM_enableTripZoneSignals(EPWM8_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

    //
    // Configure the DCB path to be unfiltered and asynchronous
    //
    EPWM_setDigitalCompareEventSource(EPWM8_BASE,
                                      EPWM_DC_MODULE_B,
                                      EPWM_DC_EVENT_1,
                                      EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    //
    // Sync the ePWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure TRIP4 to be CTRIP1H using the ePWM X-BAR
    //
    XBAR_setEPWMMuxConfig(XBAR_TRIP4, XBAR_EPWM_MUX00_CMPSS1_CTRIPH);
    XBAR_enableEPWMMux(XBAR_TRIP4, XBAR_MUX00);

    //
    // Clear trip flags
    //
    EPWM_clearTripZoneFlag(EPWM8_BASE, EPWM_TZ_INTERRUPT |
                           EPWM_TZ_FLAG_OST);

    //
    // Put the time base counter into up-count mode
    //
    EPWM_setTimeBaseCounterMode(EPWM8_BASE, EPWM_COUNTER_MODE_UP);
}


