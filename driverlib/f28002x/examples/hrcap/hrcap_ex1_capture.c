//#############################################################################
//
// FILE:    hrcap_ex1_capture.c
//
// TITLE:   HRCAP Capture and Calibration Example
//
//! \addtogroup driver_example_list
//! <h1>HRCAP Capture and Calibration Example</h1>
//!
//! This example configures an ECAP to use HRCAP functionality to capture time
//! between edges on input GPIO2.
//!
//! \b External \b Connections \n
//! The user must provide a signal to GPIO2. XCLKOUT has been configured to
//! an output GPIO and can be externally jumped to serve this purpose. See
//! Sysconfig file for XCLKOUT GPIO selected.
//!
//! \b Watch \b Variables \n
//! - onTime1, onTime2
//! - offTime1, offTime2
//! - period1, period2
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "hrcap_ex1_capture.h"
#include "board.h"

//
// Globals
//
volatile uint32_t cap1Count;
volatile uint32_t cap2Count;
volatile uint32_t cap3Count;
volatile uint32_t cap4Count;

uint32_t absCountOn1, absCountOn2;
uint32_t absCountOff1, absCountOff2;
uint32_t absCountPeriod1, absCountPeriod2;

float32_t onTime1 = 0, onTime2 = 0;
float32_t offTime1 = 0, offTime2 = 0;
float32_t period1 = 0, period2 = 0;

uint32_t ecapIntCount;
uint16_t hrcapIntCount = 0;
uint16_t ecapIntCalCount = 0;
uint16_t calStatus = 0;

HRCAPCAL_CalResultObj hrcapCalResult;

uint64_t totalCount = 0;
float32_t inputFreqMHz = 0;

//
// Function Prototypes
//
void initXCLKOUT(void);

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
    // Board Initialization
    //
    Board_init();

    //
    // Initialize XCLKOUT
    //
    initXCLKOUT();

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_myECAP0);
    Interrupt_enable(INT_myECAP0_HR);

    //
    // Initialize counters
    //
    ecapIntCount = 0;
    cap2Count = 0U;
    cap3Count = 0U;
    cap4Count = 0U;

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and Real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Wait for a value to be captured by the HRCAP
        //
        if (period1 != 0)
        {
            //
            // Convert from nS to MHz
            //
            inputFreqMHz = 1 / (period1 / 1000);
        }

    }
}

//
// initXCLKOUT - Configure XCLKOUT
//
void initXCLKOUT(void)
{
    //
    // Clock source is SYSCLK
    //
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_XTALOSC);

    //
    // XCLKOUT = Clock Source / 8
    //
    EALLOW;
    SysCtl_setXClk(SYSCTL_XCLKOUT_DIV_8);
    EDIS;
}

//
// INT_myECAP0_ISR -  eCAP ISR
//
__interrupt void INT_myECAP0_ISR(void)
{
    ecapIntCalCount++;
    if(ecapIntCount++ > 10)
    {
        ecapIntCount = 0;

        //
        // Get the raw time stamps
        //
        cap1Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1);
        cap2Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2);
        cap3Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3);
        cap4Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_4);

        absCountOn1 = cap2Count - cap1Count;
        absCountOff1 = cap3Count - cap2Count;
        absCountPeriod1 = cap3Count - cap1Count;

        absCountOn2 = cap4Count - cap3Count;
        absCountOff2 = cap3Count - cap2Count;
        absCountPeriod2 = cap4Count - cap2Count;

        //
        // Convert counts to nanoseconds using the scale factor
        //
        onTime1 = HRCAP_convertEventTimeStampNanoseconds(absCountOn1,
                                                   hrcapCalResult.scaleFactor);
        offTime1 = HRCAP_convertEventTimeStampNanoseconds(absCountOff1,
                                                   hrcapCalResult.scaleFactor);
        period1 = HRCAP_convertEventTimeStampNanoseconds(absCountPeriod1,
                                                   hrcapCalResult.scaleFactor);

        onTime2 = HRCAP_convertEventTimeStampNanoseconds(absCountOn2,
                                                   hrcapCalResult.scaleFactor);
        offTime2 = HRCAP_convertEventTimeStampNanoseconds(absCountOff2,
                                                   hrcapCalResult.scaleFactor);
        period2 = HRCAP_convertEventTimeStampNanoseconds(absCountPeriod2,
                                                   hrcapCalResult.scaleFactor);

        totalCount++;
    }

    ECAP_clearInterrupt(myECAP0_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(myECAP0_BASE);
    ECAP_reArm(myECAP0_BASE);
    ECAP_resetCounters(myECAP0_BASE);

    //
    // Acknowledge the PIE interrupt group
    //
    Interrupt_clearACKGroup(INT_myECAP0_INTERRUPT_ACK_GROUP);
}

//
// INT_myECAP0_HR_ISR -  HRCAP Calibration ISR
//
__interrupt void INT_myECAP0_HR_ISR(void)
{
    hrcapIntCount++;

    //
    // Get calibration interrupt sources
    //
    calStatus = HRCAP_getCalibrationFlags(myECAP0_HR_BASE);

    //
    // Get calibration clock counts
    //
    hrcapCalResult.hrclkCount = HRCAP_getCalibrationClockPeriod(myECAP0_HR_BASE,
                                            HRCAP_CALIBRATION_CLOCK_HRCLK);
    hrcapCalResult.sysclkcount = HRCAP_getCalibrationClockPeriod(myECAP0_HR_BASE,
                                            HRCAP_CALIBRATION_CLOCK_SYSCLK);

    //
    // The following options are possible
    //   - HRCALCAL_STATUS_DONE_ISR
    //   - HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR
    //   - Software forced generated interrupt
    //
    if(HRCALCAL_STATUS_DONE_ISR == calStatus)
    {
        //
        // Calculate scale factor
        //
        hrcapCalResult.scaleFactor = HRCAP_getScaleFactor(myECAP0_HR_BASE);
    }
    else if (HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR == calStatus)
    {
        //
        // Calibration done with an overflow. Determine which counter has
        // overflowed
        //
        if(hrcapCalResult.hrclkCount > hrcapCalResult.sysclkcount)
        {
            //
            // HRCLK has overflowed
            //
            hrcapCalResult.scaleFactor = hrcapCalResult.sysclkcount *
                                         HRCAPCAL_INV_OVERFLOW;
        }
        else if(hrcapCalResult.hrclkCount < hrcapCalResult.sysclkcount)
        {
            //
            // SYSCLK has overflowed
            //
            hrcapCalResult.scaleFactor = HRCAPCAL_OVERFLOW /
                                         hrcapCalResult.hrclkCount;
        }
        else
        {
            //
            // Both SYSCLK and HRCLK have overflowed
            //
            hrcapCalResult.scaleFactor = 1.0f;
        }
    }
    else
    {
        //
        // Software generated interrupt
        //
    }

    //
    // Clear the interrupts
    //
    HRCAP_clearCalibrationFlags(myECAP0_HR_BASE, calStatus);

    //
    // Acknowledge the PIE interrupt group
    //
    Interrupt_clearACKGroup(INT_myECAP0_HR_INTERRUPT_ACK_GROUP);
}
