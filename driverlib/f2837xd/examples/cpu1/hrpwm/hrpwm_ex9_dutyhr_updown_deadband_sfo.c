//#############################################################################
//
// FILE:   hrpwm_dutyhr_updown_deadband.c
//
// TITLE:  HRPWM Duty Control with Up-Down, Active High Complementary Deadband.
//
//! \addtogroup driver_example_list
//! <h1>HRPWM Duty Control with AHC Deadband</h1>
//!
//! This example implements High-Resolution EPWM duty control capability. The
//! example begins with a basic Active-High Complementary (AHC) output
//! on channels A and B of the EPWM module(s) by using the Dead Band submodule
//! to apply rising and falling edge delays on channel A and B respectively.
//! High-Resolution duty control is then applied on both A/B channels of the
//! EPWM module(s). HR duty control is implemented by applying the CMPAHR
//! (for channel A) and CMPBHR (for channel B) values to control both edges of
//! both EPWM channel outputs with finer granularity. The duty cycle of the
//! EPWM module(s) are updated with calculations performed in main().
//! This example also calls the following TI's MEP Scale Factor Optimizer (SFO)
//! software library V8 functions:
//!
//! \b int \b SFO(); \n
//! - Updates MEP_ScaleFactor dynamically when HRPWM is in use
//! - Updates HRMSTEP register (exists only in EPwm1Regs register space)
//!   with MEP_ScaleFactor value
//! - Returns 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!   (Auto-conversion may not function properly under this condition)
//! - Returns 1 when complete for the specified channel
//! - Returns 0 if not complete for the specified channel
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
//
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "sfo_v8.h"

//
// Defines
//
// The below TBPRD, RED, and FED values are programmed in SysConfig. Note
// that the HRPWM edges must be placed outside of the 3-clock-cycle restricted
// areas. Please see your device technical reference manual for details on this
// HRPWM duty cycle range limitation.
//
#define EPWM_TIMER_TBPRD            100UL // Time-Base Period
#define EPWM_RED                    10UL  // Rising Edge Delay
#define EPWM_FED                    10UL  // Falling Edge Delay

//
// In this example, we want to increment the CMPx values to update the HRPWM
// duty cycle during run-time. While varying CMPx, TBPRD should remain
// greater than or equal to CMPx + RED/2 and TBPRD should remain greater
// than or equal to CMPx + FED/2, otherwise one of the channels will be
// demanded low for longer than the full EPWM period. In this PWM 
// configuration, the desired CMPx range is:
// - The minimum CMPx value should be larger than the FED/2.
// - The maximum CMPx value should be smaller than (TBPRD - (RED/2)).
// These min and max values are converted to percentages to be used in main().
//
#define MIN_HRPWM_DUTY_PERCENT      ((float32_t)EPWM_FED/2)/((float32_t)EPWM_TIMER_TBPRD)*100.0
#define MAX_HRPWM_DUTY_PERCENT      ((float32_t)EPWM_TIMER_TBPRD - EPWM_RED/2)/((float32_t)EPWM_TIMER_TBPRD)*100.0

#define LAST_EPWM_INDEX_FOR_EXAMPLE    5

//
// Globals
//
float32_t dutyFine = 50.0; // Start the duty cycle at 50%

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
void error(void);
//__interrupt void epwm1ISR(void);
//__interrupt void epwm2ISR(void);
//__interrupt void epwm3ISR(void);
//__interrupt void epwm4ISR(void);

//
// Main
//
void main(void)
{
    uint16_t i = 0;

    //
    // Initialize device clock and peripherals.
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
    // Assign the interrupt service routines to ePWM interrupts.
    //
    //Interrupt_register(INT_EPWM1, &epwm1ISR);
    //Interrupt_register(INT_EPWM2, &epwm2ISR);
    //Interrupt_register(INT_EPWM3, &epwm3ISR);
    //Interrupt_register(INT_EPWM4, &epwm4ISR);

    //
    // Disable sync (Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize EPWM modules and change EXTSYNCIN XBAR Inputs from GPIO0.
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
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


    // Enable ePWM interrupts
    //
    //Interrupt_enable(INT_EPWM1);
    //Interrupt_enable(INT_EPWM2);
    //Interrupt_enable(INT_EPWM3);
    //Interrupt_enable(INT_EPWM4);

    //
    // Enable Global Interrupt (INTM) and real-time interrupt (DBGM)
    //
    EINT;
    ERTM;


    for(;;)
    {
        //
        // Sweep dutyFine from the minimum to maximum duty percentages.
        //
        for(dutyFine = MIN_HRPWM_DUTY_PERCENT; dutyFine < MAX_HRPWM_DUTY_PERCENT; dutyFine += 0.01)
        {
            DEVICE_DELAY_US(1000);
            for(i=1; i<LAST_EPWM_INDEX_FOR_EXAMPLE; i++)
            {
                float32_t count = ((100.0 - dutyFine) * (float32_t)(EPWM_TIMER_TBPRD << 8))/100.0;
                uint32_t compCount = (count);
                uint32_t hrCompCount = (compCount & (0x000000FF));
                if (hrCompCount == 0)
                {
                    //
                    // Add 1 so that CMPxHR is never equal to 0.
                    //
                    compCount |= 0x00000001;
                }
                //
                // Update CMPA/B and their HR components.
                //
                HRPWM_setCounterCompareValue(ePWM[i], HRPWM_COUNTER_COMPARE_A, compCount);
                HRPWM_setCounterCompareValue(ePWM[i], HRPWM_COUNTER_COMPARE_B, compCount);
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
            status = SFO(); // In the background, the MEP calibration module
                            // continuously updates MEP_ScaleFactor.

            if (status == SFO_ERROR)
            {
                error();   // SFO function returns 2 if an error occurs & #
                           // of MEP steps/coarse step exceeds the maximum
            }              // of 255.
        }
    }
}


//
// epwm1ISR - ePWM 1 ISR
//
//__interrupt void epwm1ISR(void)
//{
//    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
//}

//
// epwm2ISR - ePWM 2 ISR
//
//__interrupt void epwm2ISR(void)
//{
//    EPWM_clearEventTriggerInterruptFlag(EPWM2_BASE);
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
//}

//
// epwm3ISR - ePWM 3 ISR
//
//__interrupt void epwm3ISR(void)
//{
//    EPWM_clearEventTriggerInterruptFlag(EPWM3_BASE);
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
//}

//
// epwm4ISR - ePWM 4 ISR
//
//__interrupt void epwm4ISR(void)
//{
//    EPWM_clearEventTriggerInterruptFlag(EPWM4_BASE);
//    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
//}



//
// Error - Halt debugger when called
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}
