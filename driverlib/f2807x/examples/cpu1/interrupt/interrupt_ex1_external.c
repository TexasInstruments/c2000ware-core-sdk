//###########################################################################
//
// FILE:   interrupt_ex1_external.c
//
// TITLE:  External Interrupt test program.
//
//! \addtogroup driver_example_list
//! <h1>External Interrupts (ExternalInterrupt)</h1>
//!
//! This program sets up GPIO0 as XINT1 and GPIO1 as XINT2.  Two other
//! GPIO signals are used to trigger the interrupt (GPIO30 triggers
//! XINT1 and GPIO31 triggers XINT2).  The user is required to
//! externally connect these signals for the program to work
//! properly.
//!
//! XINT1 input is synced to SYSCLKOUT.
//!
//! XINT2 has a long qualification - 6 samples at 510*SYSCLKOUT each.
//!
//! GPIO34 will go high outside of the interrupts and low within the
//! interrupts. This signal can be monitored on a scope.
//!
//! Each interrupt is fired in sequence - XINT1 first and then XINT2
//!
//! \b External \b Connections \n
//! - Connect GPIO30 to GPIO0.  GPIO0 will be assigned to XINT1
//! - Connect GPIO31 to GPIO1.  GPIO1 will be assigned to XINT2
//!
//! Monitor GPIO34 with an oscilloscope. GPIO34 will be high outside of the
//! ISRs and low within each ISR.
//!
//! \b Watch \b Variables \n
//!  - XINT1Count for the number of times through XINT1 interrupt
//!  - XINT2Count for the number of times through XINT2 interrupt
//!  - loopCount for the number of times through the idle loop
//!
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define CPU_RATE    5.00L
#define DELAY (CPU_RATE/1000*6*510)  //Qual period at 6 samples

//
// Globals
//
volatile uint32_t XINT1Count;
volatile uint32_t XINT2Count;
volatile uint32_t loopCount;

//
// Function Prototypes
//
interrupt void xint1_isr(void);
interrupt void xint2_isr(void);

//
// Main
//
void main(void)
{
    uint32_t tempX1Count;
    uint32_t tempX2Count;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups
    //
    //Device_initGPIO(); // Skipped for this example

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrups
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR)
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_XINT1, &xint1_isr);
    Interrupt_register(INT_XINT2, &xint2_isr);

    //
    // User specific code, enable interrupts:
    //
    // Clear the counters
    //
    XINT1Count = 0; // Count XINT1 interrupts
    XINT2Count = 0; // Count XINT2 interrupts
    loopCount = 0;  // Count times through idle loop

    //
    // Enable XINT1 and XINT2 in the PIE: Group 1 interrupt 4 & 5
    // Enable INT1 which is connected to WAKEINT:
    //
    Interrupt_enable(INT_XINT1);
    Interrupt_enable(INT_XINT2);
    EINT;                                       // Enable Global Interrupts

    //
    // GPIO30 & GPIO31 are outputs, start GPIO30 high and GPIO31 low
    //
    // Load the output latch
    GPIO_setPortPins(GPIO_PORT_A,GPIO_GPADIR_GPIO30);
    GPIO_setDirectionMode(30,GPIO_DIR_MODE_OUT);            // output
    // Load the output latch
    GPIO_clearPortPins(GPIO_PORT_A,GPIO_GPADIR_GPIO31);
    GPIO_setDirectionMode(31,GPIO_DIR_MODE_OUT);            // output

    //
    // GPIO0 and GPIO1 are inputs
    //
    GPIO_setDirectionMode(0,GPIO_DIR_MODE_IN);          // input
    // XINT1 Synch to SYSCLKOUT only
    GPIO_setQualificationMode(0, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(1,GPIO_DIR_MODE_IN);          // input
    // XINT2 Qual using 6 samples
    GPIO_setQualificationMode(1, GPIO_QUAL_6SAMPLE);
    // Set qualification period for GPIO0 to GPIO7
    // Each sampling window is 510*SYSCLKOUT
    GPIO_setQualificationPeriod(3,510);

    //
    // GPIO0 is XINT1, GPIO1 is XINT2
    //
    GPIO_setInterruptPin(0,GPIO_INT_XINT1);
    GPIO_setInterruptPin(1,GPIO_INT_XINT2);

    //
    // Configure XINT1
    //
    // Falling edge interrupt
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
    // Rising edge interrupt
    GPIO_setInterruptType(GPIO_INT_XINT2, GPIO_INT_TYPE_RISING_EDGE);

    //
    // Enable XINT1 and XINT2
    //
    GPIO_enableInterrupt(GPIO_INT_XINT1);         // Enable XINT1
    GPIO_enableInterrupt(GPIO_INT_XINT2);         // Enable XINT2

    //
    // GPIO34 will go low inside each interrupt.  Monitor this on a scope
    //
    GPIO_setDirectionMode(34,GPIO_DIR_MODE_OUT);    // output


    //
    // IDLE loop:
    //
    for(;;)
    {
        tempX1Count = XINT1Count;
        tempX2Count = XINT2Count;

        //
        // Trigger both XINT1
        //

        GPIO_setPortPins(GPIO_PORT_B,GPIO_GPBDIR_GPIO34); // GPIO34 is high
        // Lower GPIO30, trigger XINT1
        GPIO_clearPortPins(GPIO_PORT_A,GPIO_GPADIR_GPIO30);
        while(XINT1Count == tempX1Count) {}

        //
        // Trigger both XINT2
        //
        GPIO_setPortPins(GPIO_PORT_B,GPIO_GPBDIR_GPIO34); // GPIO34 is high
        DEVICE_DELAY_US(DELAY);                      // Wait for Qual period
        // Raise GPIO31, trigger XINT2
        GPIO_setPortPins(GPIO_PORT_A,GPIO_GPADIR_GPIO31);
        while(XINT2Count == tempX2Count) {}

        //
        // Check that the counts were incremented properly and get ready
        // to start over.
        //
        if(XINT1Count == tempX1Count + 1 && XINT2Count == tempX2Count + 1)
        {
            loopCount++;
            //raise GPIO30
            GPIO_setPortPins(GPIO_PORT_A,GPIO_GPADIR_GPIO30);
            // lower GPIO31
            GPIO_clearPortPins(GPIO_PORT_A,GPIO_GPADIR_GPIO31);

            Example_PassCount++;
        }
        else
        {
            Example_Fail = 1;
            asm("      ESTOP0"); // stop here
        }
    }
}

//
// xint1_isr - External Interrupt 1 ISR
//
interrupt void xint1_isr(void)
{
    GPIO_clearPortPins(GPIO_PORT_B,GPIO_GPBDIR_GPIO34); //GPIO34 is low
    XINT1Count++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

}

//
// xint2_isr - External Interrupt 2 ISR
//
interrupt void xint2_isr(void)
{
    GPIO_clearPortPins(GPIO_PORT_B,GPIO_GPBDIR_GPIO34); // GPIO34 is low
    XINT2Count++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// End of file
//
