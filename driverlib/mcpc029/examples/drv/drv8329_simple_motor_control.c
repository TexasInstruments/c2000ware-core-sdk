//#############################################################################
//
// FILE:   drv8329_simple_motor_control.c
//
// TITLE:  Simple 3-Phase Motor Control with DRV8329
//
//! \addtogroup driver_example_list
//! <h1>DRV8329 Simple 3-Phase Motor Control</h1>
//!
//! This example shows a simple implementation of 3-phase motor control.
//! Sysconfig is used to configure the DRV8329 and the MCPWM module. The
//! MCPWM module is set up to generate 3-phase PWM signals.
//!
//! \b External \b Connections \n
//!  - Monitor GLA, GLB, GLC to see the 3-phase PWM signals
//!
//! \b Watch \b Variables \n
//!  - \b interruptcounter - Counts the number of MCPWM interrupts
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2026 Texas Instruments Incorporated - http://www.ti.com/
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
#include "sw_workaround_6x_mcpwm.h"
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#pragma CODE_SECTION(INT_myMCPWM0_ISR, ".TI.ramfunc");
//
// Defines and globals for MCPWM counter updates
//
#define PI       3.14159265359
#define TWOPI    6.283185
#define PIDIV3   1.047197
#define PIDIV180 0.01745292519943
#define PRD      myMCPWM0_TBPRD
float32_t mult = 2;
float32_t theta = 0;
float32_t thetapu = 0;
float32_t delTheta = 1.8;
float32_t valA, valB, valC;
volatile uint16_t interruptcounter = 0;
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
    // Disable pin locks and enable internal pull-ups.
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
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    //
    // PinMux and Peripheral Initialization
    //
    Board_init();
    SW_Workaround_6x_MCPWM_Config();
    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();
    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;
    while(1)
    {;}
}
//
// MCPWM ISR
//
void INT_myMCPWM0_ISR(void)
{
    //
    // Update the CMPA values
    //
    interruptcounter++;
    // Increasing theta by 0.005 pu, 0.005pu is 1.8 degrees.
    theta += delTheta;
    thetapu = theta/(360.0); // values in per-unit
    //thetapu = thetapu/25;
    valA = (0.5*PRD +
            (sinf((theta*PIDIV180)) * 0.5 * PRD * mult));
    valB = (0.5*PRD +
            (sinf(((theta*PIDIV180) + (2 * PIDIV3))) * 0.5 * PRD * mult));
    valC = (0.5*PRD +
            (sinf(((theta*PIDIV180) + (4 * PIDIV3))) * 0.5 * PRD * mult));
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1A, (uint16_t)valA);
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2A, (uint16_t)valB);
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3A, (uint16_t)valC);
    if(theta >=360)
    {
        theta = 0;
    }
    DEVICE_DELAY_US(1);
    //
    // Clear the interrupt flags.
    // to clear all flags, MCPWM_INT_SOURCE_ALL may be used as arg.
    //
    MCPWM_clearInterrupt(myMCPWM0_BASE, MCPWM_INT_ET_1);
    //
    // Clear the global interrupt flag. Only with this flag clear,
    // will the next interrupt be received.
    //
    MCPWM_clearGlobalInterrupt(myMCPWM0_BASE);
    //
    // Acknowledge this interrupt to receive more interrupts from group
    //
    Interrupt_clearACKGroup(INT_myMCPWM0_INTERRUPT_ACK_GROUP);
}
