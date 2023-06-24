//#############################################################################
//
// FILE:   interrupt_ex4_epwm_realtime_interrupt.c
//
// TITLE:  EPWM Real-Time Interrupt
//
//! \addtogroup driver_example_list
//! <h1> EPWM Real-Time Interrupt </h1>
//!
//!  This example configures the ePWM1 Timer and increments a counter each time
//!  the ISR is executed. ePWM interrupt can be configured as time critical
//!  to demonstrate real-time mode functionality and real-time interrupt
//!  capability.
//!
//!  The example uses 2 LEDs - LED1 is toggled in the main loop and LED2 is
//!  toggled in the EPWM Timer Interrupt. FREE_SOFT bits and DBGIER.INT3 bit
//!  must be set to enable ePWM1 interrupt to be time critical and operational
//!  in real time mode after halt command
//!
//!  How to run the example?
//!  - Add the watch variables as mentioned below and enable Continuous Refresh.
//!  - Enable real-time mode (Run->Advanced->Enable Silicon Real-time Mode)
//!  - Initially, the DBGIER register is set to 0 and the EPWM emulation mode
//!    is set to EPWM_EMULATION_STOP_AFTER_NEXT_TB (FREE_SOFT = 0)
//!  - When the application is running, you will find both LEDs toggling and
//!    the watch variables EPwm1TimerIntCount, EPwm1Regs.TBCTR getting updated.
//!  - When the application is halted, both LEDs stop toggling and the watch
//!    variables remain constant. EPWM counter is stopped on debugger halt.
//!  - To enable EPWM counter run during debugger halt, set emulation mode as
//!    EPWM_EMULATION_FREE_RUN (FREE_SOFT = 2). You will find EPwm1Regs.TBCTR
//!    is running, but EPwm1TimerIntCount remains constant. This means,
//!    the EPWM counter is running, but the ISRs are not getting serviced.
//!  - To enable real-time interrupts, set DBGIER.INT3 = 1 (EPWM1 interrupt is
//!    part of PIE Group 3). You will find that the EPwm1TimerIntCount is
//!    incrementing and the LED starts toggling. The EPWM ISR is getting
//!    serviced even during a debugger halt.
//!
//! For more details, watch this video :
//! [C2000 Real-Time 
//! Features](https://training.ti.com/c2000-real-time-features)
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - EPwm1TimerIntCount        - EPWM1 ISR counter
//! - EPwm1Regs.TBCTR.TBCTR     - EPWM1 Time Base counter
//! - EPwm1Regs.TBCTL.FREE_SOFT - Set this to 2 to enable free run
//! - DBGIER.INT3               - Set to 1 to enable real time interrupt
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
#define EPWM1_TIMER_TBPRD   0x2000


//
// Globals
//
uint32_t EPwm1TimerIntCount;
uint16_t LEDcount;

//
// Function Prototypes
//
extern void SetDBGIER(uint16_t dbgier); // Defined in <device>_dbgier.asm file
void initEPWM(void);
__interrupt void epwm1ISR(void);

//
// Main
//
void main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Configures the GPIO pin as a push-pull output
    //
    Device_initGPIO();
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    Interrupt_register(INT_EPWM1, &epwm1ISR);

    //
    // Initialize EPWM1
    //
    initEPWM();

    //
    // Initialize counters
    //
    EPwm1TimerIntCount = 0;
    LEDcount = 0;

    //
    // Enable EPWM1 Interrupt
    //
    Interrupt_enable(INT_EPWM1);

    //
    // Initially disable time-critical interrupts.
    // The parameter to SetDBGIER() can be Ored value of INTERRUPT_CPU_INTx.
    // Eg : SetDBGIER(INTERRUPT_CPU_INT3);
    //
    SetDBGIER(0x0000);   // PIE groups time-critical designation

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever
    //
    while(1)
    {
        //
        // Toggle LED1
        //
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);

        //
        // 200ms delay
        //
        DEVICE_DELAY_US(200000);
    }
}

void initEPWM()
{
    //
    // Disable sync
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initially disable Free/Soft Bits
    //
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_STOP_AFTER_NEXT_TB);

    //
    // Setup TBCLK
    //
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_TIMER_TBPRD);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);

    //
    // CompareA event at half of period
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A,
                                EPWM1_TIMER_TBPRD/2);

    //
    // Action Qualifiers : Set on CMPA, Clear on PRD
    //
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

    //
    // Configure interrupt on event CTR=ZERO
    //
    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM1_BASE);
    EPWM_setInterruptEventCount(EPWM1_BASE, 1);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

__interrupt void
epwm1ISR(void)
{
    EPwm1TimerIntCount++;
    LEDcount++;

    //
    // Toggle LED2 when the count reaches 500
    //
    if (LEDcount == 500)
    {
        GPIO_togglePin(DEVICE_GPIO_PIN_LED2);
        LEDcount=0;
    }

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

//
// End of File
//
