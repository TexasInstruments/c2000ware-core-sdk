//#############################################################################
//
// FILE:    ecap_ex5_signal_monitor.c
//
// TITLE:   eCAP Signal Monitor Example for Low-Pulse Width monitoring.
//
//! \addtogroup driver_example_list
//! <h1>eCAP Signal Monitor Example</h1>
//!
//! This example configures ePWM1A for:
//! - Up-down count mode
//! - Period value : 4000 (16000 sysclk)
//! - CMPA value : 2000 (8000 sysclk)
//! - The low-pulse width will be ~16000 sysclk
//!
//! eCAP1 configuration:
//! - Absolute mode
//! - Continous mode (one-shot mode can be used but limited duration)
//! - 4 captures are enabled 
//! - Low Pulse width monitoring  : Rising to falling edge
//!
//! This example generates an error event ERROR_EVT1 as the actual low-pulse
//! width does not occur during the expected window and trip the PWM signal.
//! The monitor window can be changed by changing the monitor min and max value.
//!
//! Note: When ecapMonitorMin < 16000 and ecapMonitorMax > 16000, this example
//! will not generate Error_Evt
//! When ecapMonitorMin, ecapMonitorMax > 16000 , Error_Evt1 will be generated
//! When ecapMonitorMin, ecapMonitorMax < 16000 , Error_Evt2 will be generated
//!
//! \b External \b Connections \n
//! - eCAP1 is on GPIO16
//! - ePWM1A is on GPIO0
//! - Connect GPIO0 to GPIO16.
//!
//! \b Watch \b Variables \n
//! - \b ecapMonitorMin - Min value for the signal monitoring window
//! (ecapMonitorMin < 16000 sysclk)
//! - \b ecapMonitorMax - Max value for the signal monitoring window
//! (ecapMonitorMax > 16000 sysclk)
//
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
volatile uint16_t cap1Count;
volatile uint16_t cap2Count;
volatile uint16_t cap3Count;
volatile uint16_t cap4Count;
volatile uint16_t ecapMonitorMin;
volatile uint16_t ecapMonitorMax;

//
// Function Prototypes
//
void error(void);
void initECAP(void);

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
    // Configure the signal monitoring min and max value
    //
    ECAP_configureMinValue(myECAP0_SIGNAL_MUNIT_BASE, ECAP_MONITORING_UNIT_1, ecapMonitorMin);
    ECAP_configureMaxValue(myECAP0_SIGNAL_MUNIT_BASE, ECAP_MONITORING_UNIT_1, ecapMonitorMax);

    //
    // Board initialization
    // Configure GPIO 16 as eCAP input
    // Enable interrupts required for this example
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Board_init();

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize counters:
    //
    cap1Count = 0U;
    cap2Count = 0U;
    cap3Count = 0U;
    cap4Count = 0U;

    //
    // Enable Global Interrupt (INTM) and Real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    for(;;)
    {
       NOP;
    }
}

//
// myECAP0 ISR
//
__interrupt void INT_myECAP0_ISR(void)
{
    //
    // Capture the ECAP events.
    //
    cap1Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1);
    cap2Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2);
    cap3Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3);
    cap4Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_4);

    //
    // Clear interrupt flags for more interrupts.
    //
    ECAP_clearInterrupt(myECAP0_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_4 | ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1);
    ECAP_clearGlobalInterrupt(myECAP0_BASE);

    //
    // Start eCAP
    //
    ECAP_reArm(myECAP0_BASE);

    //
    // Acknowledge the group interrupt for more interrupts.
    //
    Interrupt_clearACKGroup(INT_myECAP0_INTERRUPT_ACK_GROUP);
}

//
// error - Error function
//
void error()
{
    ESTOP0;
}
