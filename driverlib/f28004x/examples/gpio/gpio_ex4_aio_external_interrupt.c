//#############################################################################
//
// FILE:   gpio_ex4_aio_external_interrupt.c
//
// TITLE:  Configure Analog IO (AIO) pin as External Interrupt (XINT)
//
//! \addtogroup driver_example_list
//! <h1>External Interrupt (XINT)</h1>
//!
//! In this example AIO pins are configured as digital inputs. Two other GPIO
//! signals (connected externally to AIO pins) are toggled in software to
//! trigger external interrupt through AIO224 and AIO225 (AIO224 assigned to
//! XINT1 and AIO225 assigned to XINT2). The user is required to externally
//! connect these signals for the program to work properly.  Each interrupt
//! is fired in sequence: XINT1 first and then XINT2.
//!
//! GPIO34 will go high outside of the interrupts and low within the
//! interrupts. This signal can be monitored on a scope.
//!
//! \b External \b Connections \n
//! - Connect GPIO30 to AIO224.  AIO224 will be assigned to XINT1
//! - Connect GPIO31 to AIO225.  AIO225 will be assigned to XINT2
//! - GPIO34 can be monitored on an oscilloscope
//!
//! \b Watch \b Variables \n
//!  - xint1Count for the number of times through XINT1 interrupt
//!  - xint2Count for the number of times through XINT2 interrupt
//!  - loopCount for the number of times through the idle loop
//!
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

//
// Defines
//
// Qualification period at 6 samples in microseconds
#define DELAY   (6.0 * 510.0 * 1000000.0 * (1.0 / DEVICE_SYSCLK_FREQ))

//
// Globals
//
volatile uint32_t xint1Count = 0;
volatile uint32_t xint2Count = 0;
uint32_t loopCount = 0;

//
// Function Prototypes
//
__interrupt void xint1ISR(void);
__interrupt void xint2ISR(void);

//
// Main
//
void main(void)
{
    uint32_t xint1CountTemp;
    uint32_t xint2CountTemp;

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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_XINT1, &xint1ISR);
    Interrupt_register(INT_XINT2, &xint2ISR);

    //
    // Enable XINT interrupts
    //
    Interrupt_enable(INT_XINT1);
    Interrupt_enable(INT_XINT2);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // GPIO30 & GPIO31 are outputs that will trigger the interrupts through
    // AIO224 and AIO225.  Starting with GPIO30 as high and GPIO31 as low.
    //
    GPIO_writePin(30, 1);
    GPIO_setPinConfig(GPIO_30_GPIO30);
    GPIO_setDirectionMode(30, GPIO_DIR_MODE_OUT);

    GPIO_writePin(31, 0);
    GPIO_setPinConfig(GPIO_31_GPIO31);
    GPIO_setDirectionMode(31, GPIO_DIR_MODE_OUT);

    //
    // AIO224 and AIO225 are inputs and the pins tied to the external interrupts.
    // AIO224 will be synchronous to SYSCLKOUT only.  AIO225 will use a
    // qualification mode of 6 samples. Configure AIO in digital input mode.
    // These AIO pins do not have digital output capability. Setting direction
	// of the AIO pin is not required.
    //
    GPIO_setPinConfig(GPIO_224_GPIO224);
    GPIO_setAnalogMode(224, GPIO_ANALOG_DISABLED);
    GPIO_setQualificationMode(224, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(GPIO_225_GPIO225);
    GPIO_setAnalogMode(225, GPIO_ANALOG_DISABLED);
    GPIO_setQualificationMode(225, GPIO_QUAL_6SAMPLE);

    //
    // Each sampling window will be 510 SYSCLKOUT cycles.  Note that this
    // function actually sets the qualification period for GPIOs 0 through 7
    // (if they are using qualification).
    //
    GPIO_setQualificationPeriod(225, 510);

    //
    // Select AIO224 as XINT1 and AIO225 as XINT2
    //
    GPIO_setInterruptPin(224, GPIO_INT_XINT1);
    GPIO_setInterruptPin(225, GPIO_INT_XINT2);

    //
    // Configure XINT1 to be a triggered by a falling edge and XINT2 to be
    // triggered by a rising edge.
    //
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_setInterruptType(GPIO_INT_XINT2, GPIO_INT_TYPE_RISING_EDGE);

    //
    // Enable XINT1 and XINT2
    //
    GPIO_enableInterrupt(GPIO_INT_XINT1);
    GPIO_enableInterrupt(GPIO_INT_XINT2);

    //
    // GPIO34 will go low inside each interrupt.  Monitor this on a scope.
    //
    GPIO_setPinConfig(GPIO_34_GPIO34);
    GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);

    //
    // Loop indefinitely
    //
    while(1)
    {
        xint1CountTemp = xint1Count;
        xint2CountTemp = xint2Count;

        //
        // Trigger XINT1
        //
        GPIO_writePin(34, 1);       // GPIO34 is high
        GPIO_writePin(30, 0);       // Lower GPIO30, trigger XINT1

        //
        // Wait until ISR has finished
        //
        while(xint1Count == xint1CountTemp)
        {
            ;
        }

        //
        // Trigger XINT2
        //
        GPIO_writePin(34, 1);       // GPIO34 is high
        DEVICE_DELAY_US(DELAY);     // Wait for qual period
        GPIO_writePin(31, 1);       // Raise GPIO31, trigger XINT2

        //
        // Wait until ISR has finished
        //
        while(xint2Count == xint2CountTemp)
        {
            ;
        }

        //
        // Check that the counts were incremented properly and get ready
        // to start over.
        //
        if((xint1Count == (xint1CountTemp + 1)) &&
           (xint2Count == (xint2CountTemp + 1)))
        {
            loopCount++;
            GPIO_writePin(30, 1);   // Raise GPIO30
            GPIO_writePin(31, 0);   // Lower GPIO31
        }
        else
        {
            //
            // Something went wrong
            //
            ESTOP0;
        }
    }
}

//
// xint1ISR - XINT1 ISR
//
__interrupt void xint1ISR(void)
{
    //
    // Lower GPIO34 and increment interrupt count
    //
    GPIO_writePin(34, 0);
    xint1Count++;

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// xint2ISR -  XINT2 ISR
//
__interrupt void xint2ISR(void)
{
    //
    // Lower GPIO34 and increment interrupt count
    //
    GPIO_writePin(34, 0);
    xint2Count++;

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
