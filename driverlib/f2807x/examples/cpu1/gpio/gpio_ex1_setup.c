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
//!  - All pullup resistors are enabled.  For ePWMs this may not be desired.
//!  - Input qual for communication ports (CAN, SPI, SCI, I2C) is asynchronous
//!  - Input qual for Trip pins (TZ) is asynchronous
//!  - Input qual for eCAP and eQEP signals is synch to SYSCLKOUT
//!  - Input qual for some I/O's and __interrupts may have a sampling window
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

//
// Defines
// Select the example to compile in.  Only one example should be set as 1
// the rest should be set as 0.
//
#define EXAMPLE1 1  // Basic pinout configuration example
#define EXAMPLE2 0  // Communication pinout example

//
// Function Prototypes
//
void setup1GPIO(void);
void setup2GPIO(void);

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

#if EXAMPLE1

    //
    // This example is a basic pinout
    //
    setup1GPIO();

#endif  // - EXAMPLE1

#if EXAMPLE2

    //
    // This example is a communications pinout
    //
    setup2GPIO();

#endif

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
    // PWM1-3, ECAP1, ECAP2, TZ1-TZ4, SPI-A, EQEP1, SCI-A, I2C
    // and a number of I/O pins
    // These can be combined into single statements for improved
    // code efficiency.
    //

    //
    // Enable PWM1-3 on GPIO0-GPIO5
    //
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO0
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO1
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO2
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO3
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO4
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO5
    GPIO_setPinConfig(GPIO_0_EPWM1A);               // GPIO0 = PWM1A
    GPIO_setPinConfig(GPIO_1_EPWM1B);               // GPIO1 = PWM1B
    GPIO_setPinConfig(GPIO_2_EPWM2A);               // GPIO2 = PWM2A
    GPIO_setPinConfig(GPIO_3_EPWM2B);               // GPIO3 = PWM2B
    GPIO_setPinConfig(GPIO_4_EPWM3A);               // GPIO4 = PWM3A
    GPIO_setPinConfig(GPIO_5_EPWM3B);               // GPIO5 = PWM3B

    //
    // Enable a GPIO output on GPIO6, set it high
    //
    GPIO_setPadConfig(6, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO6
    GPIO_writePin(6, 1);                            // Load output latch
    GPIO_setPinConfig(GPIO_6_GPIO6);                // GPIO6 = GPIO6
    GPIO_setDirectionMode(6, GPIO_DIR_MODE_OUT);    // GPIO6 = output

    //
    // Enable eCAP1 on GPIO7
    //
    GPIO_setPadConfig(7, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO7
    GPIO_setQualificationMode(7, GPIO_QUAL_SYNC);   // Synch to SYSCLKOUT
    XBAR_setInputPin(XBAR_INPUT7, 7);               // GPIO7 = ECAP1

    //
    // Enable GPIO outputs on GPIO8 - GPIO11, set it high
    //
    GPIO_setPadConfig(8, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO8
    GPIO_writePin(8, 1);                            // Load output latch
    GPIO_setPinConfig(GPIO_8_GPIO8);                // GPIO8 = GPIO8
    GPIO_setDirectionMode(8, GPIO_DIR_MODE_OUT);    // GPIO8 = output

    GPIO_setPadConfig(9, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO9
    GPIO_writePin(9, 1);                            // Load output latch
    GPIO_setPinConfig(GPIO_9_GPIO9);                // GPIO9 = GPIO9
    GPIO_setDirectionMode(9, GPIO_DIR_MODE_OUT);    // GPIO9 = output

    GPIO_setPadConfig(10, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO10
    GPIO_writePin(10, 1);                           // Load output latch
    GPIO_setPinConfig(GPIO_10_GPIO10);              // GPIO10 = GPIO10
    GPIO_setDirectionMode(10, GPIO_DIR_MODE_OUT);   // GPIO10 = output

    GPIO_setPadConfig(11, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO11
    GPIO_writePin(11, 1);                           // Load output latch
    GPIO_setPinConfig(GPIO_11_GPIO11);              // GPIO11 = GPIO11
    GPIO_setDirectionMode(11, GPIO_DIR_MODE_OUT);   // GPIO11 = output

    //
    // Enable Trip Zone inputs on GPIO12 - GPIO14
    //
    GPIO_setPadConfig(12, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO12
    GPIO_setPadConfig(13, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO13
    GPIO_setPadConfig(14, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO14
    GPIO_setQualificationMode(12, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(13, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(14, GPIO_QUAL_ASYNC); // asynch input
    XBAR_setInputPin(XBAR_INPUT1, 12);              // GPIO12 = TZ1
    XBAR_setInputPin(XBAR_INPUT2, 13);              // GPIO13 = TZ2
    XBAR_setInputPin(XBAR_INPUT3, 14);              // GPIO14 = TZ3

    //
    // Enable SPI-A on GPIO16 - GPIO19
    //
    GPIO_setPadConfig(16, GPIO_PIN_TYPE_PULLUP);    // Pullup GPIO16 (SPISIMOA)
    GPIO_setPadConfig(17, GPIO_PIN_TYPE_PULLUP);    // Pullup GPIO17 (SPIS0MIA)
    GPIO_setPadConfig(18, GPIO_PIN_TYPE_PULLUP);    // Pullup GPIO18 (SPICLKA)
    GPIO_setPadConfig(19, GPIO_PIN_TYPE_PULLUP);    // Pullup GPIO19 (SPISTEA)
    GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(17, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(18, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(19, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setPinConfig(GPIO_16_SPISIMOA);            // GPIO16 = SPISIMOA
    GPIO_setPinConfig(GPIO_17_SPISOMIA);            // GPIO17 = SPIS0MIA
    GPIO_setPinConfig(GPIO_18_SPICLKA);             // GPIO18 = SPICLKA
    GPIO_setPinConfig(GPIO_19_SPISTEA);             // GPIO19 = SPISTEA

    //
    // Enable EQEP1 on GPIO's 20,21,22,23
    //
    GPIO_setPadConfig(20, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO20
    GPIO_setPadConfig(21, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO21
    GPIO_setPadConfig(22, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO22
    GPIO_setPadConfig(23, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO23
    GPIO_setQualificationMode(20, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(21, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(22, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(23, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setPinConfig(GPIO_20_EQEP1A);              // GPIO20 = EQEP1A
    GPIO_setPinConfig(GPIO_21_EQEP1B);              // GPIO21 = EQEP1B
    GPIO_setPinConfig(GPIO_22_EQEP1S);              // GPIO22 = EQEP1S
    GPIO_setPinConfig(GPIO_23_EQEP1I);              // GPIO23 = EQEP1I

    //
    // Enable eCAP1 on GPIO24
    //
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_PULLUP);    // Pullup on GPIO24 (ECAP1)
    GPIO_setQualificationMode(24, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    XBAR_setInputPin(XBAR_INPUT7, 24);              // GPIO24 = ECAP1

    //
    // Set input qualification period for GPIO25 & GPIO26
    //
    GPIO_setQualificationPeriod(24, 2);              // Qual period=SYSCLKOUT/2
    GPIO_setQualificationMode(25, GPIO_QUAL_6SAMPLE);// 6 samples
    GPIO_setQualificationMode(26, GPIO_QUAL_6SAMPLE);// 6 samples

    //
    // Make GPIO25 the input source for XINT1
    //
    GPIO_setPinConfig(GPIO_25_GPIO25);            // GPIO25 = GPIO25
    GPIO_setDirectionMode(25, GPIO_DIR_MODE_IN);  // GPIO25 = input
    GPIO_setInterruptPin(25,GPIO_INT_XINT1);      // XINT1 connected to GPIO25

    //
    // Make GPIO26 the input source for XINT2
    //
    GPIO_setPinConfig(GPIO_26_GPIO26);             // GPIO26 = GPIO26
    GPIO_setDirectionMode(26, GPIO_DIR_MODE_IN);   // GPIO26 = input
    GPIO_setInterruptPin(26, GPIO_INT_XINT2);      // XINT2 connected to GPIO26

    //
    // Make GPIO27 wakeup from HALT/STANDBY Low Power Modes
    //
    GPIO_setPinConfig(GPIO_27_GPIO27);           // GPIO27 = GPIO27
    GPIO_setDirectionMode(27, GPIO_DIR_MODE_IN); // GPIO27 = input
    SysCtl_enableLPMWakeupPin(27);               // GPIO27 will wake the device
    SysCtl_setStandbyQualificationPeriod(2);     // Qualify GPIO27 by 2 OSCCLK
                                                 // cycles before waking
                                                 // the device from STANDBY

    //
    // Enable SCI-A on GPIO28 - GPIO29
    //
    GPIO_setPadConfig(28, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO28
    GPIO_setQualificationMode(28, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPinConfig(GPIO_28_SCIRXDA);              // GPIO28 = SCIRXDA
    GPIO_setPadConfig(29, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO29
    GPIO_setPinConfig(GPIO_29_SCITXDA);              // GPIO29 = SCITXDA

    //
    // Enable CAN-A on GPIO30 - GPIO31
    //
    GPIO_setPadConfig(30, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO30
    GPIO_setPinConfig(GPIO_30_CANRXA);               // GPIO30 = CANRXA
    GPIO_setPadConfig(31, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO31
    GPIO_setQualificationMode(31, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPinConfig(GPIO_31_CANTXA);               // GPIO31 = CANTXA

    //
    // Enable I2C-A on GPIO32 - GPIO33
    //
    GPIO_setPadConfig(32, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO32
    GPIO_setPinConfig(GPIO_32_SDAA);                 // GPIO32 = SDAA
    GPIO_setQualificationMode(32, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPadConfig(33, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO33
    GPIO_setQualificationMode(33, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPinConfig(GPIO_33_SCLA);                 // GPIO33 = SCLA

    //
    // Make GPIO34 an input on GPIO34
    //
    GPIO_setPadConfig(34, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO34
    GPIO_setPinConfig(GPIO_34_GPIO34);               // GPIO34 = GPIO34
    GPIO_setDirectionMode(34, GPIO_DIR_MODE_IN);     // GPIO34 = input
}

//
// setup2GPIO - Is an example that demonstrates the communications pinout
//
void
setup2GPIO(void)
{
    //
    // Example 2:
    // Communications Pinout.
    // This basic communications pinout includes:
    // PWM1-3, CAP1, CAP2, SPI-A, SPI-B, CAN-A, SCI-A and I2C
    // and a number of I/O pins
    //

    //
    // Enable PWM1-3 on GPIO0-GPIO5
    //
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO0
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO1
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO2
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO3
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO4
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO5
    GPIO_setPinConfig(GPIO_0_EPWM1A);              // GPIO0 = PWM1A
    GPIO_setPinConfig(GPIO_1_EPWM1B);              // GPIO1 = PWM1B
    GPIO_setPinConfig(GPIO_2_EPWM2A);              // GPIO2 = PWM2A
    GPIO_setPinConfig(GPIO_3_EPWM2B);              // GPIO3 = PWM2B
    GPIO_setPinConfig(GPIO_4_EPWM3A);              // GPIO4 = PWM3A
    GPIO_setPinConfig(GPIO_5_EPWM3B);              // GPIO5 = PWM3B

    //
    // Enable an GPIO output on GPIO6
    //
    GPIO_setPadConfig(6, GPIO_PIN_TYPE_PULLUP);   // Enable pullup on GPIO6
    GPIO_writePin(6, 1);                          // Load output latch
    GPIO_setPinConfig(GPIO_6_GPIO6);              // GPIO6 = GPIO6
    GPIO_setDirectionMode(6, GPIO_DIR_MODE_OUT);  // GPIO6 = output

    //
    // Enable eCAP1 on GPIO7
    //
    GPIO_setPadConfig(7, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO7
    GPIO_setQualificationMode(7, GPIO_QUAL_SYNC);   // Synch to SYSCLKOUT
    XBAR_setInputPin(XBAR_INPUT7, 7);               // GPIO7 = ECAP1

    //
    // Enable GPIO outputs on GPIO8 - GPIO11
    //
    GPIO_setPadConfig(8, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO8
    GPIO_writePin(8, 1);                           // Load output latch
    GPIO_setPinConfig(GPIO_8_GPIO8);               // GPIO8 = GPIO8
    GPIO_setDirectionMode(8, GPIO_DIR_MODE_OUT);   // GPIO8 = output

    GPIO_setPadConfig(9, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO9
    GPIO_writePin(9, 1);                           // Load output latch
    GPIO_setPinConfig(GPIO_9_GPIO9);               // GPIO9 = GPIO9
    GPIO_setDirectionMode(9, GPIO_DIR_MODE_OUT);   // GPIO9 = output

    GPIO_setPadConfig(10, GPIO_PIN_TYPE_PULLUP);   // Enable pullup on GPIO10
    GPIO_writePin(10, 1);                          // Load output latch
    GPIO_setPinConfig(GPIO_10_GPIO10);             // GPIO10 = GPIO10
    GPIO_setDirectionMode(10, GPIO_DIR_MODE_OUT);  // GPIO10 = output

    GPIO_setPadConfig(11, GPIO_PIN_TYPE_PULLUP);   // Enable pullup on GPIO11
    GPIO_writePin(11, 1);                          // Load output latch
    GPIO_setPinConfig(GPIO_11_GPIO11);             // GPIO11 = GPIO11
    GPIO_setDirectionMode(11, GPIO_DIR_MODE_OUT);  // GPIO11 = output

    //
    // Enable SPI-B on GPIO22 - GPIO25
    //
    GPIO_setPadConfig(22, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO22 (SPICLKB)
    GPIO_setPadConfig(23, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO23 (SPISTEB)
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO24 (SPISIMOB)
    GPIO_setPadConfig(25, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO25 (SPISOMIB)
    GPIO_setQualificationMode(22, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(23, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(24, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(25, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setPinConfig(GPIO_22_GPIO22);              // Set Group Mux
    GPIO_setPinConfig(GPIO_23_GPIO23);              // Set Group Mux
    GPIO_setPinConfig(GPIO_24_GPIO24);              // Set Group Mux
    GPIO_setPinConfig(GPIO_25_GPIO25);              // Set Group Mux
    GPIO_setPinConfig(GPIO_22_SPICLKB);             // GPIO22 = SPICLK
    GPIO_setPinConfig(GPIO_23_SPISTEB);             // GPIO23 = SPISTEB
    GPIO_setPinConfig(GPIO_24_SPISIMOB);            // GPIO24 = SPISIMOB
    GPIO_setPinConfig(GPIO_25_SPISOMIB);            // GPIO25 = SPISOMIB

    //
    // Enable SPI-A on GPIO16 - GPIO19
    //
    GPIO_setPadConfig(16, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO16 (SPISIMOA)
    GPIO_setPadConfig(17, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO17 (SPIS0MIA)
    GPIO_setPadConfig(18, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO18 (SPICLKA)
    GPIO_setPadConfig(19, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO19 (SPISTEA)
    GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(17, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(18, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(19, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setPinConfig(GPIO_16_SPISIMOA);            // GPIO16 = SPISIMOA
    GPIO_setPinConfig(GPIO_17_SPISOMIA);            // GPIO17 = SPIS0MIA
    GPIO_setPinConfig(GPIO_18_SPICLKA);             // GPIO18 = SPICLKA
    GPIO_setPinConfig(GPIO_19_SPISTEA);             // GPIO19 = SPISTEA

    //
    // Enable eCAP1 on GPIO24
    //
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_PULLUP);    // Pullup on GPIO24 (ECAP1)
    GPIO_setQualificationMode(24, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    XBAR_setInputPin(XBAR_INPUT7, 24);              // GPIO24 = ECAP1

    //
    // Set input qualifcation period for GPIO25 & GPIO26 inputs
    //
    GPIO_setQualificationPeriod(24, 2);            // Qual period = SYSCLKOUT/2
    GPIO_setQualificationMode(25, GPIO_QUAL_6SAMPLE);   // 6 samples
    GPIO_setQualificationMode(26, GPIO_QUAL_3SAMPLE);   // 3 samples

    //
    // Make GPIO25 the input source for XINT1
    //
    GPIO_setPinConfig(GPIO_25_GPIO25);            // GPIO25 = GPIO25
    GPIO_setDirectionMode(25, GPIO_DIR_MODE_IN);  // GPIO25 = input
    GPIO_setInterruptPin(25,GPIO_INT_XINT1);      // XINT1 connected to GPIO25

    //
    // Make GPIO26 the input source for XINT2
    //
    GPIO_setPinConfig(GPIO_26_GPIO26);             // GPIO26 = GPIO26
    GPIO_setDirectionMode(26, GPIO_DIR_MODE_IN);   // GPIO26 = input
    GPIO_setInterruptPin(26,GPIO_INT_XINT2);       // XINT2 connected to GPIO26

    //
    // Make GPIO27 wakeup from HALT/STANDBY Low Power Modes
    //
    GPIO_setPinConfig(GPIO_27_GPIO27);           // GPIO27 = GPIO27
    GPIO_setDirectionMode(27, GPIO_DIR_MODE_IN); // GPIO27 = input
    SysCtl_enableLPMWakeupPin(27);               // GPIO27 will wake the device
    SysCtl_setStandbyQualificationPeriod(2);     // Qualify GPIO27 by 2 OSCCLK
                                                 // cycles before waking
                                                 // the device from STANDBY

    //
    // Enable SCI-A on GPIO28 - GPIO29
    //
    GPIO_setPadConfig(28, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO28
    GPIO_setQualificationMode(28, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPinConfig(GPIO_28_SCIRXDA);              // GPIO28 = SCIRXDA
    GPIO_setPadConfig(29, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO29
    GPIO_setPinConfig(GPIO_29_SCITXDA);              // GPIO29 = SCITXDA

    //
    // Enable CAN-A on GPIO30 - GPIO31
    //
    GPIO_setPadConfig(30, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO30
    GPIO_setPinConfig(GPIO_30_CANRXA);               // GPIO30 = CANRXA
    GPIO_setPadConfig(31, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO31
    GPIO_setQualificationMode(31, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setPinConfig(GPIO_31_CANTXA);               // GPIO31 = CANTXA

    //
    // Enable I2C-A on GPIO32 - GPIO33
    //
    GPIO_setPadConfig(32, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO32
    GPIO_setPadConfig(33, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO33
    GPIO_setQualificationMode(32, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setQualificationMode(33,GPIO_QUAL_ASYNC);   // asynch input
    GPIO_setPinConfig(GPIO_32_SDAA);                 // GPIO32 = SDAA
    GPIO_setPinConfig(GPIO_33_SCLA);                 // GPIO33 = SCLA

    //
    // Make GPIO34 an input
    //
    GPIO_setPadConfig(34, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO34
    GPIO_setPinConfig(GPIO_34_GPIO34);              // GPIO34 = GPIO34
    GPIO_setDirectionMode(34, GPIO_DIR_MODE_IN);    // GPIO34 = input
}

//
// End of File
//

