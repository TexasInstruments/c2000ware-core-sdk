//#############################################################################
//
// FILE:   interrupt_ex4_mcpwm_realtime_interrupt.c
//
// TITLE:  MCPWM Real-Time Interrupt
//
//! \addtogroup driver_example_list
//! <h1> MCPWM Real-Time Interrupt </h1>
//!
//!  This example configures the mcPWM1 Timer and increments a counter each time
//!  the ISR is executed. mcPWM interrupt can be configured as time critical
//!  to demonstrate real-time mode functionality and real-time interrupt
//!  capability.
//!
//!  The example uses 2 LEDs - LED1 is toggled in the main loop and LED2 is
//!  toggled in the MCPWM Timer Interrupt. FREE_SOFT bits and DBGIER.INT3 bit
//!  must be set to enable mcPWM1 interrupt to be time critical and operational
//!  in real time mode after halt command
//!
//!  How to run the example?
//!  - Add the watch variables as mentioned below and enable Continuous Refresh.
//!  - Enable real-time mode (Run->Advanced->Enable Silicon Real-time Mode)
//!  - Initially, the DBGIER register is set to 0 and the MCPWM emulation mode
//!    is set to MCPWM_EMULATION_STOP_AFTER_NEXT_TB (FREE_SOFT = 0)
//!  - When the application is running, you will find both LEDs toggling and
//!    the watch variables MCPwm1TimerIntCount, MCPwm1Regs.TBCTR getting updated.
//!  - When the application is halted, both LEDs stop toggling and the watch
//!    variables remain constant. MCPWM counter is stopped on debugger halt.
//!  - To enable MCPWM counter run during debugger halt, set emulation mode as
//!    MCPWM_EMULATION_FREE_RUN (FREE_SOFT = 2). You will find MCPwm1Regs.TBCTR
//!    is running, but MCPwm1TimerIntCount remains constant. This means,
//!    the MCPWM counter is running, but the ISRs are not getting serviced.
//!  - To enable real-time interrupts, set DBGIER.INT3 = 1 (MCPWM1 interrupt is
//!    part of PIE Group 3). You will find that the MCPwm1TimerIntCount is
//!    incrementing and the LED starts toggling. The MCPWM ISR is getting
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
//! - MCPwm1TimerIntCount        - MCPWM1 ISR counter
//! - MCPwm1Regs.TBCTR.TBCTR     - MCPWM1 Time Base counter
//! - MCPwm1Regs.TBCTL.FREE_SOFT - Set this to 2 to enable free run
//! - DBGIER.INT3               - Set to 1 to enable real time interrupt
//!
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
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define MCPWM1_TIMER_TBPRD   0x2000


//
// Globals
//
uint32_t MCPwm1TimerIntCount;
uint16_t LEDcount;

//
// Function Prototypes
//
extern void SetDBGIER(uint16_t dbgier); // Defined in <device>_dbgier.asm file
void initMCPWM(void);
__interrupt void mcpwm1ISR(void);

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
    Interrupt_register(INT_MCPWM1, &mcpwm1ISR);

    //
    // Initialize MCPWM1
    //
    initMCPWM();

    //
    // Initialize counters
    //
    MCPwm1TimerIntCount = 0;
    LEDcount = 0;

    //
    // Enable MCPWM1 Interrupt
    //
    Interrupt_enable(INT_MCPWM1);

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

void initMCPWM()
{
    //
    // Disable sync
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initially disable Free/Soft Bits
    //
    MCPWM_setEmulationMode(PWM1_BASE, MCPWM_EMULATION_STOP_AFTER_NEXT_TB);

    //
    // Setup TBCLK
    //
    MCPWM_setTimeBasePeriodActive(PWM1_BASE, MCPWM1_TIMER_TBPRD);
    MCPWM_setTimeBaseCounterMode(PWM1_BASE, MCPWM_COUNTER_MODE_UP);
    MCPWM_setTimeBaseCounter(PWM1_BASE, 0U);

    //
    // CompareA event at half of period
    //
    MCPWM_setCounterCompareActiveValue(PWM1_BASE, MCPWM_COUNTER_COMPARE_1A,
                                MCPWM1_TIMER_TBPRD/2);

    //
    // Action Qualifiers : Set on CMPA, Clear on PRD
    //
    MCPWM_setActionQualifierActionActive(PWM1_BASE,
                                  MCPWM_AQ_OUTPUT_1A,
                                  MCPWM_AQ_OUTPUT_HIGH,
                                  MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    MCPWM_setActionQualifierActionActive(PWM1_BASE,
                                  MCPWM_AQ_OUTPUT_1A,
                                  MCPWM_AQ_OUTPUT_LOW,
                                  MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

    //
    // Configure interrupt on event CTR=ZERO
    //
    MCPWM_setEventTriggerSource(PWM1_BASE, MCPWM_ET_1, MCPWM_EVT_TBCTR_ZERO);
    MCPWM_setEventTriggerEventPrescale(PWM1_BASE, MCPWM_ET_1, 1);
    MCPWM_enableInterrupt(PWM1_BASE, MCPWM_INT_ET_1);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

__interrupt void
mcpwm1ISR(void)
{
    MCPwm1TimerIntCount++;
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
    MCPWM_clearInterrupt(PWM1_BASE, MCPWM_INT_ET_1);
    MCPWM_clearGlobalInterrupt(PWM1_BASE);

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

//
// End of File
//
