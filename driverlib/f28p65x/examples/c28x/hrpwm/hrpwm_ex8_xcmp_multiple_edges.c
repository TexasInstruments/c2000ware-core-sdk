//#############################################################################
//
// FILE:   hrpwm_ex8_xcmp_multiple_edges.c
//
// TITLE:  HRPWM Using XCMP Mode with Type5 features.
//
//! \addtogroup driver_example_list
//! <h1>HRPWM XCMP Mode</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! for high-resolution period with ePWM in Up count mode
//! due to the HRPWM control extension of the respective ePWM module.
//!
//! This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//! software library V8 functions:
//!
//! \b int \b SFO(); \n
//! - updates MEP_ScaleFactor dynamically when HRPWM is in use
//! - updates HRMSTEP register (exists only in EPwm1Regs register space)
//! with MEP_ScaleFactor value
//! - returns 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!   (Auto-conversion may not function properly under this condition)
//! - returns 1 when complete for the specified channel
//! - returns 0 if not complete for the specified channel
//!
//! This example is intended to explain the XCMP MODE with HRPWM capabilities. The code can be
//! optimized for code efficiency. Refer to TI's Digital power application
//! examples and TI Digital Power Supply software libraries for details.
//!- ePWM1A is allocated for XCMP1-4 and ePWM1B is allocated XCMP5-8 registers.
//! - No Shadow registers used
//! \b External \b Connections \n
//!  - Monitor ePWM1 A/B pins on an oscilloscope.
//!  - ePWM1A is on GPIO0
//!  - ePWM1B is on GPIO1
//#############################################################################
//
//
// 
// C2000Ware v6.00.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "board.h"
#include "sfo_v8.h"

//
// Defines
//
#define EPWM_TIMER_TBPRD            1000UL
#define MIN_HRPWM_DUTY_PERCENT      25.0
#define LAST_EPWM_INDEX_FOR_EXAMPLE    2

//
// Globals
//
float32_t dutyFine = MIN_HRPWM_DUTY_PERCENT;
uint16_t status;

int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO() function.

volatile uint32_t ePWM[] =
    {0, myEPWM0_BASE};
//
// Function Prototypes
//
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
    //
    // Initialize the EPWM GPIO Pins and change the XBAR inputs from using GPIO0
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


    for(;;)
    {
         //
         // Sweep DutyFine
         //
         for(dutyFine = MIN_HRPWM_DUTY_PERCENT; dutyFine < 75; dutyFine += 0.01)
         {
             DEVICE_DELAY_US(1000);
             for(i=1; i<LAST_EPWM_INDEX_FOR_EXAMPLE; i++)
             {
                 //
                 // Bit shifting by 16 to prevent truncation to HR register
                 //      
                 float32_t count2 = ((dutyFine -25.0) * (float32_t)((1000UL) << 16))/100;
                 uint32_t compCount2 = (count2);
                 HRPWM_setXCMPRegValue(ePWM[i], EPWM_XCMP2_ACTIVE, compCount2);
                 float32_t count4 = ((dutyFine +25.0) * (float32_t)((1000UL) << 16))/100;
                 uint32_t compCount4 = (count4);
                 HRPWM_setXCMPRegValue(ePWM[i], EPWM_XCMP4_ACTIVE, compCount4);        
                 float32_t count6 = ((dutyFine -25.0) * (float32_t)((1000UL) << 16))/100;
                 uint32_t compCount6 = (count6);
                 HRPWM_setXCMPRegValue(ePWM[i], EPWM_XCMP6_ACTIVE, compCount6);
                 float32_t count8 = ((dutyFine +25.0) * (float32_t)((1000UL) << 16))/100;
                 uint32_t compCount8 = (count8);
                 HRPWM_setXCMPRegValue(ePWM[i], EPWM_XCMP8_ACTIVE, compCount8);

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

 
//
// error - Halt debugger when called
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}
