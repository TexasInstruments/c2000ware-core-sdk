//#############################################################################
//
// FILE:   mcpwm_ex6_global_load_use_case.c
//
// TITLE:  MCPWM Global Load Use Case
////! \addtogroup driver_example_list
//! <h1>MCPWM Global Load Feature Showcase</h1>
//!
//! This example configures myMCPWM0 and myMCPWM1 with global load feature for 
//! synchronized parameter updates across multiple PWM channels as follows:
//!
//!     myMCPWM0 (Primary Module)
//!         Time Base Configurations:
//!             - Up Count Mode
//!             - Period = 3999 (40 kHz @ TBCLK of 160MHz)
//!             - Free Run emulation mode
//!         
//!         Initial Compare Values:
//!             - PWM1A/B : 1800 (45% duty cycle)
//!             - PWM2A/B : 3133 (78% duty cycle)
//!             - PWM3A/B : 467  (12% duty cycle)
//!
//!         Action Qualifier Configurations:
//!             All pairs (A/B outputs):
//!             - Set HIGH on Counter matches CMPA/CMPB counting up
//!             - Set LOW on Counter Period
//!
//!         Deadband Configurations:
//!             - Initial: 32 counts (200ns @ 160MHz)
//!             - Both Rising and Falling edge delay enabled
//!
//!     myMCPWM1 (Secondary Module)
//!         Time Base Configurations:
//!             - Up Count Mode synchronized to myMCPWM0
//!             - Period = 3999 (40 kHz)
//!
//!         Initial Compare Values:
//!             - PWM1A/B : 1000 (25% duty cycle)
//!
//!         Action Qualifier Configurations:
//!             PWM1A/B outputs:
//!             - Set HIGH on Counter matches CMPA/CMPB counting up
//!             - Set LOW on Counter Period
//!
//!     Global Load Feature Implementation:
//!         When perform_one_shot_load flag is set:
//!         1. Compare Value Updates:
//!             myMCPWM0:
//!             - PWM1A: 2000 (50% duty)
//!             - PWM2A: 3333 (83% duty)
//!             - PWM3A: 667  (17% duty)
//!             
//!             myMCPWM1:
//!             - PWM1A: 2000 (50% duty)
//!
//!         2. Deadband Updates (both modules):
//!             - 48 counts (300ns @ 160MHz)
//!             - Applied to both rising and falling edges
//!
//!         3. Update Mechanism:
//!             - All changes written to shadow registers
//!             - Global load trigger synchronizes all updates
//!             - Changes take effect simultaneously
//!
//! \b External \b Connections \n
//!     Monitor the MCPWM pins for the waveforms:
//!         Observe J4 40 - GPIO0  - myMCPWM0 Output A1
//!         Observe J4 39 - GPIO1  - myMCPWM0 Output B1
//!         Observe J4 38 - GPIO2  - myMCPWM0 Output A2
//!         Observe J4 37 - GPIO3  - myMCPWM0 Output B2
//!         Observe J4 36 - GPIO4  - myMCPWM0 Output A3
//!         Observe J4 35 - GPIO5  - myMCPWM0 Output B3
//!         Observe J1 7  - GPIO12 - myMCPWM1 Output A1
//!         Observe J2 19 - GPIO29 - myMCPWM1 Output B1
//!
//! \note
//!     - Use an oscilloscope to observe synchronized updates
//!     - Watch deadband transitions on complementary pairs
//!     - All updates occur on the next global load event
//!     - Period remains constant during updates
//#############################################################################
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
//#############################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
uint16_t perform_one_shot_load = 0;

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
    // Initialize GPIO and configure the GPIO pin as a push-pull output
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
    // Disable sync(Freeze clock to PWM)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure MCPWMs
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop
    //
    for(;;)
    {
        if(perform_one_shot_load == 1)
        {
            //
            // Update shadow compare values for MCPWM1 and MCPWM3
            //
            MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1A, 2000);
            MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2A, 3333); 
            MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3A, 667);  

            MCPWM_setCounterCompareShadowValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1A, 2000);

            //
            // Change Action Qualifier shadow settings for all pairs in MCPWM1 and MCPWM3
            //
            MCPWM_setActionQualifierActionShadow(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_1A, MCPWM_AQ_OUTPUT_LOW,  MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            MCPWM_setActionQualifierActionShadow(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_1A, MCPWM_AQ_OUTPUT_HIGH, MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
            
            MCPWM_setActionQualifierActionShadow(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_2A, MCPWM_AQ_OUTPUT_LOW,  MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            MCPWM_setActionQualifierActionShadow(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_2A, MCPWM_AQ_OUTPUT_HIGH, MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
            
            MCPWM_setActionQualifierActionShadow(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_3A, MCPWM_AQ_OUTPUT_LOW,  MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            MCPWM_setActionQualifierActionShadow(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_3A, MCPWM_AQ_OUTPUT_HIGH, MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
            
            
            MCPWM_setActionQualifierActionShadow(myMCPWM1_BASE, MCPWM_AQ_OUTPUT_3A, MCPWM_AQ_OUTPUT_LOW,  MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
            MCPWM_setActionQualifierActionShadow(myMCPWM1_BASE, MCPWM_AQ_OUTPUT_3A, MCPWM_AQ_OUTPUT_HIGH, MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

            //
            // Update Deadband shadow parameters (example: increase to 300ns)
            //
            MCPWM_setRisingEdgeDelayCountShadow(myMCPWM0_BASE, 48);  // 300ns @ 160MHz
            MCPWM_setFallingEdgeDelayCountShadow(myMCPWM0_BASE, 48); // 300ns @ 160MHz

            MCPWM_setRisingEdgeDelayCountShadow(myMCPWM1_BASE, 48);  // 300ns @ 160MHz
            MCPWM_setFallingEdgeDelayCountShadow(myMCPWM1_BASE, 48); // 300ns @ 160MHz

            //
            // Trigger global load - will update all shadow registers
            //
            MCPWM_setGlobalLoadOneShotLatch(myMCPWM0_BASE);
            MCPWM_setGlobalLoadOneShotLatch(myMCPWM1_BASE);

            //
            // Clear the flag
            //
            perform_one_shot_load = 0;
        }
    }
}
