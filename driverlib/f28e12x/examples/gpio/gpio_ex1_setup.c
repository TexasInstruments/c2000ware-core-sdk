//#############################################################################
//
// FILE:    gpio_ex1_setup.c
//
// TITLE:   Device GPIO Setup
//
//! \addtogroup driver_example_list
//! <h1> Device GPIO Setup </h1>
//!
//! Configures the device GPIO into two different configurations
//! This code is verbose to illustrate how the GPIO could be setup.
//! In a real application, lines of code can be combined for improved
//! code size and efficiency.
//!
//! This example only sets-up the GPIO. Nothing is actually done with
//! the pins after setup.
//!
//! \b In \b general: \n
//!  - All pullup resistors are enabled.  For PWMs this may not be desired.
//!  - Input qual for communication ports (SPI, SCI, I2C) is asynchronous
//!  - Input qual for Trip pins (TZ) is asynchronous
//!  - Input qual for eCAP and eQEP signals is synch to SYSCLKOUT
//!  - Input qual for some I/O's and __interrupts may have a sampling window
//
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

//
// Included Files
//
#include "device.h"

//
// Function Prototypes
//
void setup1GPIO(void);

//
// Main
//
void main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //
    Device_init();

    //
    // Initializes PIE and clear PIE registers. Disables CPU interrupts.
    // and clear all CPU interrupt flags.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // This example is a basic pinout
    //
    setup1GPIO();

}

//
// setup1GPIO - Is an example that demonstrates the basic pinout
//
void
setup1GPIO(void)
{
    //
    // Example 1: Basic Pinout.
    // This basic pinout includes:
    // PWM1-3, ECAP1, ECAP2, TZ1-TZ4, SPI-A, EQEP1, SCI-A ,I2C
    // and a number of I/O pins
    // These can be combined into single statements for improved
    // code efficiency.
    //

    //
    // Enable MCPWM1-3 on GPIO0-GPIO5
    //
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO0
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO1
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO2
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO3
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO4
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO5
    GPIO_setPinConfig(GPIO_0_MCPWM1_1A);              // GPIO0 = MCPWM1A
    GPIO_setPinConfig(GPIO_1_MCPWM1_1B);              // GPIO1 = MCPWM1B
    GPIO_setPinConfig(GPIO_2_MCPWM1_2A);              // GPIO2 = MCPWM2A
    GPIO_setPinConfig(GPIO_3_MCPWM1_2B);              // GPIO3 = MCPWM2B
    GPIO_setPinConfig(GPIO_4_MCPWM1_3A);              // GPIO4 = MCPWM3A
    GPIO_setPinConfig(GPIO_5_MCPWM1_3B);              // GPIO5 = MCPWM3B

    //
    // Enable EQEP1 on GPIO's 6,7,12,133
    //
    GPIO_setPadConfig(6, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO6
    GPIO_setPadConfig(7, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO7
    GPIO_setPadConfig(12, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO12
    GPIO_setPadConfig(13, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO13
    GPIO_setQualificationMode(6, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(7, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(12, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(13, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setPinConfig(GPIO_6_EQEP1_A);             // GPIO6 = EQEP1A
    GPIO_setPinConfig(GPIO_7_EQEP1_B);             // GPIO7 = EQEP1B
    GPIO_setPinConfig(GPIO_12_EQEP1_STROBE);        // GPIO12 = EQEP1S
    GPIO_setPinConfig(GPIO_13_EQEP1_INDEX);         // GPIO13 = EQEP1I

    //
    // Enable eCAP1 on GPIO7
    //
    GPIO_setPadConfig(7, GPIO_PIN_TYPE_PULLUP);         // Enable pullup on GPIO7
    GPIO_setQualificationMode(7, GPIO_QUAL_SYNC);       // Synch to SYSCLKOUT
    XBAR_setInputPin(INPUTXBAR_BASE, XBAR_INPUT7, 7);   // GPIO7 = ECAP1

    //
    // Enable Trip Zone inputs on GPIO12 - GPIO13
    //
    GPIO_setPadConfig(12, GPIO_PIN_TYPE_PULLUP);        // Enable pullup on GPIO12
    GPIO_setPadConfig(13, GPIO_PIN_TYPE_PULLUP);        // Enable pullup on GPIO13
    GPIO_setQualificationMode(12, GPIO_QUAL_ASYNC);     // asynch input
    GPIO_setQualificationMode(13, GPIO_QUAL_ASYNC);     // asynch input
    XBAR_setInputPin(INPUTXBAR_BASE, XBAR_INPUT1, 12); // GPIO12 = TZ1
    XBAR_setInputPin(INPUTXBAR_BASE, XBAR_INPUT2, 13); // GPIO13 = TZ2

    //
    // Enable SPI-A
    //
    GPIO_setPadConfig(16, GPIO_PIN_TYPE_PULLUP);    // Pullup GPIO16 (SPIPICOA)
    GPIO_setPadConfig(13, GPIO_PIN_TYPE_PULLUP);    // Pullup GPIO13 (SPIPOCIA)
    GPIO_setPadConfig(12, GPIO_PIN_TYPE_PULLUP);    // Pullup GPIO12 (SPICLKA)
    GPIO_setPadConfig(29, GPIO_PIN_TYPE_PULLUP);    // Pullup GPIO29 (SPIPTEA)
    GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(13, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(12, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(29, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setPinConfig(GPIO_16_SPIA_PICO);            // GPIO16 = SPIPICOA
    GPIO_setPinConfig(GPIO_13_SPIA_POCI);            // GPIO13 = SPIPOCIA
    GPIO_setPinConfig(GPIO_12_SPIA_CLK);             // GPIO12 = SPICLKA
    GPIO_setPinConfig(GPIO_29_SPIA_PTE);             // GPIO29 = SPIPTEA


    //
    // Make GPIO29 wakeup from STANDBY Low Power Modes
    //
    GPIO_setPinConfig(GPIO_29_GPIO29);           // GPIO29 = GPIO29
    GPIO_setDirectionMode(29, GPIO_DIR_MODE_IN); // GPIO29 = input
    SysCtl_enableLPMWakeupPin(29);               // GPIO29 will wake the device
    SysCtl_setStandbyQualificationPeriod(2);     // Qualify GPIO29 by 2 OSCCLK
                                                 // cycles before waking
                                                 // the device from STANDBY

    //
    // Enable SCI-A on GPIO35 - GPIO37
    //
    GPIO_setPadConfig(35, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO35
    GPIO_setQualificationMode(35, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPinConfig(GPIO_35_SCIA_RX);              // GPIO35 = SCIRXDA
    GPIO_setPadConfig(37, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO37
    GPIO_setPinConfig(GPIO_37_SCIA_TX);              // GPIO37 = SCITXDA

    //
    // Enable I2C-A on GPIO19 - GPIO18
    //
    GPIO_setPadConfig(19, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO19
    GPIO_setPinConfig(GPIO_19_I2CA_SDA);             // GPIO19 = SDAA
    GPIO_setQualificationMode(19, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPadConfig(18, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO18
    GPIO_setQualificationMode(18, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPinConfig(GPIO_18_I2CA_SCL);             // GPIO18 = SCLA

}

//
// End of File
//

