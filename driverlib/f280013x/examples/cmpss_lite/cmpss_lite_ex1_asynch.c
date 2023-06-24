//#############################################################################
//
// FILE:   cmpss_lite_ex1_asynch.c
//
// TITLE:  CMPSSLITE Asynchronous Trip
//
//! \addtogroup driver_example_list
//! <h1> CMPSSLITE Asynchronous Trip </h1>
//!
//! This example enables the CMPSSLITE2 COMPH comparator and feeds the asynchronous
//! CTRIPOUTH signal to the GPIO4/OUTPUTXBAR3 pin and CTRIPH to GPIO29/EPWM7B.
//!
//! CMPSS is configured to generate trip signals to trip the EPWM signals.
//! CMPIN2P is used to give positive input and internal DAC is configured 
//! to provide the negative input. Internal DAC is configured to provide a
//! signal at VDD/2. An EPWM signal is generated at GPIO29 and is configured
//! to be tripped by CTRIPOUTH.
//!
//! When a low input(VSS) is provided to CMPIN2P,
//!     - Trip signal(GPIO4) output is low
//!     - PWM7B(GPIO29) gives a PWM signal
//!
//! When a high input(higher than VDD/2) is provided to CMPIN2P,
//!     - Trip signal(GPIO4) output turns high
//!     - PWM7B(GPIO29) gets tripped and outputs as high
//!
//! \b External \b Connections \n
//!  - Give input on CMPIN2P. The pin is shared with ADCINA9 for CMPHPMXSEL = 2
//!  - Outputs can be observed on GPIO4 and GPIO29 using an oscilloscope
//!
//! \b Watch \b Variables \n
//!  - None
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
#include "board.h"

//
// Function Prototypes
//
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
    // Set up ePWM7 to take CTRIPH as TRIP4 for its DC trip input
    //
    initEPWM();

    //
    // Board Initialization
    // - Configure GPIO4 to output CTRIPOUT1H (routed through XBAROUTPUT3)
    // - Setup the Output X-BAR to output CTRIPOUTH on OUTPUTXBAR3
    // - Configure the high comparator of CMPSS1
    // - Enable CMPSS and configure the negative input signal to come from
    //   the DAC
    // - Use VDDA as the reference for the DAC and set DAC value to midpoint for
    //   arbitrary reference.
    // - Configure the output signals. Both CTRIPH and CTRIPOUTH will be fed by
    //   the asynchronous comparator output.
    //
    Board_init();


    //
    // Configure GPIO29 to output CTRIPH (routed through ePWM TRIP4 and ePWM7)
    //
    GPIO_setPinConfig(GPIO_29_EPWM7_B);

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
        if((EPWM_getTripZoneFlagStatus(EPWM7_BASE) &
            EPWM_TZ_FLAG_OST) != 0U)
        {
            //
            // Wait for comparator CTRIP to de-assert
            //
            while((CMPSSLITE_getStatus(CMPSSLITE2_BASE) & CMPSS_STS_HI_FILTOUT) != 0U)
            {
                ;
            }

            //
            // Clear trip flags
            //
            EPWM_clearTripZoneFlag(EPWM7_BASE, EPWM_TZ_INTERRUPT |
                                   EPWM_TZ_FLAG_OST);
        }
    }
}

//
// initEPWM - Function to configure ePWM7 and the ePWM X-BAR to take CTRIPH as
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
    EPWM_setClockPrescaler(EPWM7_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Initializing dummy values for ePWM counter and period
    //
    EPWM_setTimeBaseCounter(EPWM7_BASE, 0);
    EPWM_setTimeBasePeriod(EPWM7_BASE, 0xFFFF);

    //
    // Set-up compare
    //
    EPWM_setCounterCompareValue(EPWM7_BASE, EPWM_COUNTER_COMPARE_B, 0x8000);

    //
    // Set actions
    //
    EPWM_setActionQualifierAction(EPWM7_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setActionQualifierAction(EPWM7_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Configure ePWM7B to output high on TZB TRIP

    //
    EPWM_setTripZoneAction(EPWM7_BASE, EPWM_TZ_ACTION_EVENT_TZB,
                           EPWM_TZ_ACTION_HIGH);

    //
    // Trigger event when DCBH is high
    //
    EPWM_setTripZoneDigitalCompareEventCondition(EPWM7_BASE,
                                                 EPWM_TZ_DC_OUTPUT_B1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);

    //
    // Configure DCBH to use TRIP4 as an input
    //
    EPWM_enableDigitalCompareTripCombinationInput(EPWM7_BASE,
                                                  EPWM_DC_COMBINATIONAL_TRIPIN4,
                                                  EPWM_DC_TYPE_DCBH);

    //
    // Enable DCB as OST
    //
    EPWM_enableTripZoneSignals(EPWM7_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

    //
    // Configure the DCB path to be unfiltered and asynchronous
    //
    EPWM_setDigitalCompareEventSource(EPWM7_BASE,
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
    XBAR_setEPWMMuxConfig(XBAR_TRIP4, XBAR_EPWM_MUX02_CMPSS2_CTRIPH);
    XBAR_enableEPWMMux(XBAR_TRIP4, XBAR_MUX02);

    //
    // Clear trip flags
    //
    EPWM_clearTripZoneFlag(EPWM7_BASE, EPWM_TZ_INTERRUPT |
                           EPWM_TZ_FLAG_OST);

    //
    // Put the time base counter into up-count mode
    //
    EPWM_setTimeBaseCounterMode(EPWM7_BASE, EPWM_COUNTER_MODE_UP);
}


