//#############################################################################
//
// FILE:   hrpwm_ex3_prdupdown_sfo.c
//
// TITLE:  HRPWM Period Control.
//
//! \addtogroup driver_example_list
//! <h1>HRPWM Period Control</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! for high-resolution period with ePWM in Up-Down count mode
//! due to the HRPWM control extension of the respective ePWM module.
//!
//! This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//! software library V8 functions:
//!
//! \b int \b SFO(); \n
//! - updates MEP_ScaleFactor dynamically when HRPWM is in use
//! - updates HRMSTEP register (exists only in EPwm1Regs register space)
//!   with MEP_ScaleFactor value
//! - returns 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!   (Auto-conversion may not function properly under this condition)
//! - returns 1 when complete for the specified channel
//! - returns 0 if not complete for the specified channel
//!
//! This example is intended to explain the HRPWM capabilities. The code can be
//! optimized for code efficiency. Refer to TI's Digital power application
//! examples and TI Digital Power Supply software libraries for details.
//!
//! \b External \b Connections \n
//!  - Monitor ePWM1/2/3/4 A/B pins on an oscilloscope.
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
#include "board.h"
#include "SFO_V8.h"

//
// Defines
//
#define EPWM_TIMER_TBPRD    20UL
#define LAST_EPWM_INDEX_FOR_EXAMPLE    5
#define MIN_HRPWM_PRD_PERCENT   0.2

//
// Globals
//

float32_t periodFine = MIN_HRPWM_PRD_PERCENT;
uint16_t status;

int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO() function.

volatile uint32_t ePWM[] =
    {0, myEPWM1_BASE, myEPWM2_BASE, myEPWM3_BASE, myEPWM4_BASE};
//
// Function Prototypes
//
void initHRPWM(uint32_t period);
void error(void);

//
// Main
//
void main(void)
{
    uint16_t i = 0;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull ups.
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
    // Initialize EPWM GPIOs and change XBAR inputs from using GPIO0
    //
    Board_init();


    //
    // Calling SFO() updates the HRMSTEP register with calibrated MEP_ScaleFactor.
    // HRMSTEP must be populated with a scale factor value prior to enabling
    // high resolution period control.
    //
    while(status == SFO_INCOMPLETE)
    {
        status = SFO();
        if(status == SFO_ERROR)
        {
            error();   // SFO function returns 2 if an error occurs & # of MEP
        }              // steps/coarse step exceeds maximum of 255.
    }



    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initHRPWM(EPWM_TIMER_TBPRD);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    for(;;)
    {
         //
         // Sweep DutyFine
         //
         for(periodFine = MIN_HRPWM_PRD_PERCENT; periodFine < 0.9; periodFine += 0.01)
         {
             DEVICE_DELAY_US(1000);
             for(i=1; i<LAST_EPWM_INDEX_FOR_EXAMPLE; i++)
             {
                 float32_t count = ((EPWM_TIMER_TBPRD-1) << 8UL) + (float32_t)(periodFine * 256);
                 uint32_t compCount = count;
                 HRPWM_setTimeBasePeriod(ePWM[i], compCount);
             }

             //
             // Call the scale factor optimizer lib function SFO()
             // periodically to track for any change due to temp/voltage.
             // This function generates MEP_ScaleFactor by running the
             // MEP calibration module in the HRPWM logic. This scale
             // factor can be used for all HRPWM channels. The SFO()
             // function also updates the HRMSTEP register with the
             // scale factor value.
             //
             status = SFO(); // in background, MEP calibration module
                             // continuously updates MEP_ScaleFactor

             if (status == SFO_ERROR)
             {
                 error();   // SFO function returns 2 if an error occurs & #
                            // of MEP steps/coarse step
             }              // exceeds maximum of 255.
         }
     }
}


void initHRPWM(uint32_t period)
{

    uint16_t j;

    //
    // ePWM channel register configuration with HRPWM
    //
    for (j=1;j<LAST_EPWM_INDEX_FOR_EXAMPLE;j++)
    {
        EPWM_setEmulationMode(ePWM[j], EPWM_EMULATION_FREE_RUN);

        //
        // Set-up TBCLK
        //
        EPWM_setPeriodLoadMode(ePWM[j], EPWM_PERIOD_SHADOW_LOAD);
        EPWM_setTimeBasePeriod(ePWM[j], period-1);
        EPWM_setPhaseShift(ePWM[j], 0U);
        EPWM_setTimeBaseCounter(ePWM[j], 0U);

        //
        // set duty 50% initially
        //
        HRPWM_setCounterCompareValue(ePWM[j], HRPWM_COUNTER_COMPARE_A, (period/2 << 8));
        HRPWM_setCounterCompareValue(ePWM[j], HRPWM_COUNTER_COMPARE_B, (period/2 << 8));


        //
        // Set up counter mode
        //
        EPWM_setTimeBaseCounterMode(ePWM[j], EPWM_COUNTER_MODE_UP_DOWN);
        EPWM_disablePhaseShiftLoad(ePWM[j]);
        EPWM_setClockPrescaler(ePWM[j],
                               EPWM_CLOCK_DIVIDER_1,
                               EPWM_HSCLOCK_DIVIDER_1);
        EPWM_setSyncOutPulseMode(ePWM[j], EPWM_SYNC_OUT_PULSE_DISABLED);

        //
        // Set up shadowing
        //
        EPWM_setCounterCompareShadowLoadMode(ePWM[j],
                                             EPWM_COUNTER_COMPARE_A,
                                             EPWM_COMP_LOAD_ON_CNTR_ZERO);
        EPWM_setCounterCompareShadowLoadMode(ePWM[j],
                                             EPWM_COUNTER_COMPARE_B,
                                             EPWM_COMP_LOAD_ON_CNTR_ZERO);

        //
        // Set actions
        //

        EPWM_setActionQualifierAction(ePWM[j],
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);


        EPWM_setActionQualifierAction(ePWM[j],
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

        EPWM_setActionQualifierAction(ePWM[j],
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
        EPWM_setActionQualifierAction(ePWM[j],
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);


        HRPWM_setMEPEdgeSelect(ePWM[j], HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
        HRPWM_setMEPControlMode(ePWM[j], HRPWM_CHANNEL_A, HRPWM_MEP_DUTY_PERIOD_CTRL);
        HRPWM_setCounterCompareShadowLoadEvent(ePWM[j], HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);

        HRPWM_setMEPEdgeSelect(ePWM[j], HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
        HRPWM_setMEPControlMode(ePWM[j], HRPWM_CHANNEL_B, HRPWM_MEP_DUTY_PERIOD_CTRL);
        HRPWM_setCounterCompareShadowLoadEvent(ePWM[j], HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);

        HRPWM_enableAutoConversion(ePWM[j]);

        //
        // Turn on high-resolution period control.
        //

        HRPWM_enablePeriodControl(ePWM[j]);
        HRPWM_enablePhaseShiftLoad(ePWM[j]);

        EPWM_forceSyncPulse(ePWM[j]);
    }

}

//
// error - Halt debugger when called
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}

