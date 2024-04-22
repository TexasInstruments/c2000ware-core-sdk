//#############################################################################
//
// FILE:   lin_ex6_detect_incomplete_header.c
//
// TITLE:   LIN Incomplete Header Detection
//
//! \addtogroup driver_example_list
//! <h1> LIN Incomplete Header Detection   </h1>
//!
//!  This example demonstrates how an error in the header field of a LIN frame
//!  can be detected. It configures the LIN module in responder mode and waits
//!  till new frame is received. It configures an external interrupt to trigger
//!  by a falling edge in the LIN Rx pin confirming start of frame. In the ISR
//!  of XINT, a timer is configured to trigger after max time consumed by
//!  reception of a complete LIN frame. If a LIN frame is successfully received
//!  the timer is disabled before getting triggered in the LIN ISR else
//!  the timer ISR is called which indicates an error in header frame.
//!
//!
//! \b External \b Connections \n
//!  - LINATX/RX to host node via transciever.
//!
//! \b Watch \b Variables \n
//!  - linHeaderError - Number of times header error was detected
//!  - rxData - An array with the data that was received
//!             if successful reception
//!  - xint1Count - Number of timer XINT triggered
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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
#define LIN_PASS        0xABCD
#define LIN_FAIL        0xFFFF
#define MAX_PACKET_TRAN_TIME 5000000U // Max LIN frame transmission time in uSeconds
#define DEVICE_GPIO_PIN_LINATX 22U
#define DEVICE_GPIO_PIN_LINARX 23U

//
// Globals
//
uint16_t rxID = 0x1A;

volatile uint32_t level0Count = 0;
volatile uint32_t vectorOffset = 0;
volatile uint32_t linIntStatus = 0;
volatile uint32_t linHeaderError = 0 ;

uint16_t rxData[8];
uint16_t cpuTimer0IntCount;

volatile uint32_t xint1Count = 0;

//
// Function Prototypes
//
__interrupt void xint1ISR(void);
__interrupt void cpuTimer0ISR(void);
__interrupt void level0ISR(void);
void initCPUTimers(void);
void configCPUTimer(uint32_t, float, float);

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
    // Initialize GPIO and configure GPIO pins for LINTX/LINRX
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

    GPIO_setPinConfig(DEVICE_GPIO_CFG_LINTXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LINRXA);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LINARX, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LINARX, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LINARX, GPIO_QUAL_ASYNC);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LINATX, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LINATX, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LINATX, GPIO_QUAL_ASYNC);

    //
    // Select DEVICE_GPIO_PIN_LINARX as XINT1 source
    //
    GPIO_setInterruptPin(DEVICE_GPIO_PIN_LINARX, GPIO_INT_XINT1);

    //
    // Configure XINT1 to be a triggered by a falling edge
    //
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);

    //
    // Enable XINT1
    //
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    //
    // Initialize the LIN module
    //
    LIN_initModule(LINA_BASE);

    //
    // Set LIN mode to responder
    //

    LIN_setLINMode(LINA_BASE, LIN_MODE_LIN_RESPONDER);

    //
    // Enable LIN interrupt to trigger when received a message
    // with matching id.
    //
    LIN_enableInterrupt(LINA_BASE, LIN_INT_RX);
    LIN_setInterruptLevel0(LINA_BASE, LIN_INT_ALL);
    LIN_enableGlobalInterrupt(LINA_BASE, LIN_INTERRUPT_LINE0);
    LIN_clearGlobalInterruptStatus(LINA_BASE, LIN_INTERRUPT_LINE0);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_XINT1, &xint1ISR);
    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);
    Interrupt_register(INT_LINA_0, &level0ISR);

    //
    // Enable interrupts
    //
    Interrupt_enable(INT_LINA_0);
    Interrupt_enable(INT_TIMER0);
    Interrupt_enable(INT_XINT1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    //-------------------------------------------------------------
    // Main task starts here

    //
    // Set the ID to match while receiving
    //
    LIN_setIDResponderTask(LINA_BASE, rxID);

    //
    // Set the frame length (number of bytes to be received)
    //
    LIN_setFrameLength(LINA_BASE, 8);

    //
    // IDLE loop. Just sit and loop forever (waiting for new LIN msg)
    //
    while(1)
    {
    }

}

//
// initCPUTimers - This function initializes CPU timer
// to a known state.
//
void
initCPUTimers(void)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);

}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in uSeconds. The timer is held in the stopped
// state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)(freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp - 1);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);
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

    linIntStatus = LIN_getInterruptStatus(LINA_BASE);

    //
    // Check for LIN BUSY flag to see if this falling edge
    // is the start of reception of LIN frame
    //
    if((linIntStatus & LIN_FLAG_BUSY) == LIN_FLAG_BUSY)
    {
        //
        // Disable the XINT from further detection of falling
        // edges in the LIN frame
        //
        GPIO_disableInterrupt(GPIO_INT_XINT1);

        //
        // Initialize CPU timer
        //
        initCPUTimers();

        //
        // Configure CPU-Timer 0 to interrupt every MAX LIN packet length
        // transmission time + buffer time:
        //
        configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, MAX_PACKET_TRAN_TIME);

        //
        // Enable CPU timer interrupt
        //
        CPUTimer_enableInterrupt(CPUTIMER0_BASE);

        CPUTimer_startTimer(CPUTIMER0_BASE);

    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
__interrupt void
cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;

    linIntStatus = LIN_getInterruptStatus(LINA_BASE);

    //
    // Check if LIN frame ID was received
    // If not there was an error in the header frame
    //
    if((linIntStatus & LIN_FLAG_RXID) != LIN_FLAG_RXID)
        linHeaderError++;

    //
    // Enable XINT for further detection of new packets start edge
    //
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    //
    // Disable CPU timer interrupt until any new frame received on bus
    //
    CPUTimer_disableInterrupt(CPUTIMER0_BASE);

    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // Reset the LIN module
    //
    LIN_initModule(LINA_BASE);

    //
    // Set LIN mode to responder
    //

    LIN_setLINMode(LINA_BASE, LIN_MODE_LIN_RESPONDER);

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// LIN High Priority (Level 0) ISR - Interrupt service routine for interrupt
// line 0. This ISR saves the offset vector indicating the current highest
// priority pending interrupt.
//
__interrupt void
level0ISR(void)
{
    //
    // Increment the interrupt count
    //
    level0Count++;

    //
    // Read the high priority interrupt vector
    //
    vectorOffset = LIN_getInterruptLine0Offset(LINA_BASE);

    linIntStatus = LIN_getInterruptStatus(LINA_BASE);

    //
    // Check if a LIN frame was received
    //
    if((linIntStatus & LIN_INT_RX) == LIN_INT_RX)

    //
    // Read the received data in the receive buffers
    //
    LIN_getData(LINB_BASE, rxData);

    LIN_clearInterruptStatus(LINA_BASE,LIN_INT_ALL);

    LIN_clearGlobalInterruptStatus(LINA_BASE, LIN_INTERRUPT_LINE0);

    //
    // Enable CPU timer interrupt
    //
    CPUTimer_disableInterrupt(CPUTIMER0_BASE);

    CPUTimer_stopTimer(CPUTIMER0_BASE);

    //
    // To detect new packet start edge
    //
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    //
    // Acknowledge this interrupt located in group 8
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

//
// End of File
//
