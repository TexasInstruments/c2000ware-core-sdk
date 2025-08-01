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
//! CTRIPOUTH signal to the GPIO4/OUTPUTXBAR3 pin and CTRIPH to GPIO0/MCPWM1A.
//!
//! CMPSS is configured to generate trip signals to trip the MCPWM signals.
//! CMPIN2P is used to give positive input and internal DAC is configured 
//! to provide the negative input. Internal DAC is configured to provide a
//! signal at VDD/2. An MCPWM signal is generated at GPIO0 and is configured
//! to be tripped by CTRIPOUTH.
//!
//! When a low input(VSS) is provided to CMPIN2P,
//!     - Trip signal(GPIO4) output is low
//!     - PWM1A(GPIO0) gives a PWM signal
//!
//! When a high input(higher than VDD/2) is provided to CMPIN2P,
//!     - Trip signal(GPIO4) output turns high
//!     - PWM1A(GPIO0) gets tripped and outputs as high
//!
//! \note PWMXBAR is used to provide the trip signal (CTRIPH) to MCPWM. The trip
//! signal is inverted in PWMXBAR since MCPWM trip zone signals are active low
//! signals.
//!
//! \b External \b Connections \n
//!  - Give input on CMPIN2P. The pin is shared with ADCINA12 for CMPHPMXSEL = 1
//!  - Outputs can be observed on GPIO4 and GPIO0 using an oscilloscope
//!
//! \b Watch \b Variables \n
//!  - None
//!
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
void initMCPWM(void);

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
    initMCPWM();

    //
    // Board Initialization
    // - Configure GPIO4 to output CTRIPOUTH (routed through XBAROUTPUT3)
    // - Setup the Output X-BAR to output CTRIPOUTH on OUTPUTXBAR3
    // - Configure the high comparator of CMPSS2
    // - Enable CMPSS and configure the negative input signal to come from
    //   the DAC
    // - Use VDDA as the reference for the DAC and set DAC value to midpoint for
    //   arbitrary reference.
    // - Configure the output signals. Both CTRIPH and CTRIPOUTH will be fed by
    //   the asynchronous comparator output.
    //
    Board_init();


    //
    // Configure GPIO0 to output CTRIPH (routed through MCPWM TRIP4 and MCPWM1)
    //
    GPIO_setPinConfig(GPIO_0_MCPWM1_1A);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);

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
        if((MCPWM_getTripZoneFlagStatus(PWM1_BASE) & MCPWM_TZ_FLAG_OST_TZ4) != 0U)
        {
            //
            // Wait for comparator CTRIP to de-assert
            //
            while((CMPSSLITE_getStatus(CMPSSLITE2_BASE) & CMPSS_STS_HI_FILTOUT) != 0U)
            {
                ;
            }

            //
            // Clear trip zone flags
            //
            MCPWM_clearInterrupt(PWM1_BASE, MCPWM_INT_TZ_OST);
            MCPWM_clearTripZoneFlagStatus(PWM1_BASE, MCPWM_TZ_FLAG_OST_TZ4);

        }
    }
}

//
// initMCPWM - Function to configure MCPWM1 and the MCPWM X-BAR to take CTRIPH as
//            the DC trip input
//
void initMCPWM(void)
{
    //
    // Disable the MCPWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Load Mode configurations
    //
    // - Time Base Load Mode: Disabled
    // - Counter Compare Load Mode: Freeze shadow to active load
    // - Action Qualifier Load Mode: Freeze shadow to active load
    //
    MCPWM_setPeriodLoadMode(PWM1_BASE, MCPWM_PERIOD_SHADOW_LOAD_DISABLE);
    MCPWM_setCounterCompareShadowLoadMode(PWM1_BASE, MCPWM_COUNTER_COMPARE_1A, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(PWM1_BASE, MCPWM_ACTION_QUALIFIER_1A, MCPWM_AQ_LOAD_FREEZE);

    //
    // Set the time base clock prescalers to /1
    //
    MCPWM_setClockPrescaler(PWM1_BASE, MCPWM_CLOCK_DIVIDER_1);

    //
    // Initializing dummy values for ePWM counter and period
    //
    MCPWM_setTimeBaseCounter(PWM1_BASE, 0);
    MCPWM_setTimeBasePeriodActive(PWM1_BASE, 0xFFFF);

    //
    // Set-up compare
    //
    MCPWM_setCounterCompareActiveValue(PWM1_BASE, MCPWM_COUNTER_COMPARE_1A, 0x8000);

    //
    // Set actions
    //
    MCPWM_setActionQualifierActionActive(PWM1_BASE,
                                  MCPWM_AQ_OUTPUT_1A,
                                  MCPWM_AQ_OUTPUT_HIGH,
                                  MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    MCPWM_setActionQualifierActionActive(PWM1_BASE,
                                  MCPWM_AQ_OUTPUT_1A,
                                  MCPWM_AQ_OUTPUT_LOW,
                                  MCPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Configure TRIP4 to be CTRIP1H using the ePWM X-BAR
    //
    XBAR_setPWMMuxConfig(XBAR_TRIP4, XBAR_PWM_MUX02_CMPSS2_CTRIPH);
    XBAR_enablePWMMux(XBAR_TRIP4, XBAR_MUX02);

    //
    // Invert the trip signal since MCPWM trip-zone signal is active low signal
    //
    XBAR_invertPWMSignal(XBAR_TRIP4, true);

    //
    // Configure MCPWM1A to output high on TZA TRIP
    //
    MCPWM_setTripZoneAction(PWM1_BASE, MCPWM_TZ_ACTION_EVENT_TZA,
                           MCPWM_TZ_ACTION_HIGH);

    //
    // Enable DCB as OST
    //
    MCPWM_enableTripZoneSignals(PWM1_BASE, MCPWM_TZ_SIGNAL_OSHT4);

    //
    // Sync the ePWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Clear trip flags
    //
    MCPWM_clearTripZoneFlagStatus(PWM1_BASE, MCPWM_TZ_FLAG_OST_TZ4);

    //
    // Clear the OneShot Trip interrupt flag
    //
    MCPWM_clearInterrupt(PWM1_BASE, MCPWM_INT_TZ_OST);

    //
    // Put the time base counter into up-count mode
    //
    MCPWM_setTimeBaseCounterMode(PWM1_BASE, MCPWM_COUNTER_MODE_UP);
}
