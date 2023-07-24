//#############################################################################
//
// FILE:   epwm_ex17_diode_emulation.c
//
// TITLE:  ePWM Using Diode Emulation
//
//! \addtogroup driver_example_list
//! <h1>ePWM Diode Emulation</h1>
//!
//! This example configures ePWM1, ePWM2 and ePWM4 as follows
//!  - All ePWM's are 50 KHz, 50% duty cycle Type 4 generated signals
//!
//! Buffered DAC1 configuration used as positive input to CMPSS1 High and Low:
//!  - Reference voltage source = internal ADC VREFHI = 2.5V
//!  - Gain = 1
//!
//! CMPSS1 configuration for TRIPH/TRIPL signal inputs to enter DE mode:
//!  - Positive input = DACA_OUT (from DAC1) for both CMPSS1 High, Low
//!  - Negative input = 825 mV from internal DAC for CMPSS1 High
//!                     3.3V from internal DAC for CMPSS1 Low
//!  - This means only CMPSSTRIPH1 is triggered when DACA_OUT > 825 mV
//!    CMPSSTRIPL1 is always low
//!
//! Diode Emulation configuration:
//!  - For all ePWM's, TripH = CMPSSTRIPH1 and TRIPL = CMPSSTRIPL1
//!    Since a TRIPH_OR_TRIPL triggers DE entry, only TripH is used for demo
//!  - ePWM1A is set to active high and 1B set to low during DE
//!  - ePWM2 is configured same as ePWM1 with a re-entry delay
//!      - Re-entry delay = 250 EPWMSYNCPER cycles = 5 ms
//!  - ePWM4 is configured same as ePWM1 with DE monitor
//!      - Increment/ Decrement on EPWMSYNCPER = +1 when TRIPH_OR_TRIPL high
//!                                              -1 when TRIPH_OR_TRIPL low
//!      - Threshold value = 250
//!        In this case, 5 ms after entering DE, DEMONTRIP is generated
//!
//!  \b External \b Connections \n
//!  - ePWM1A is on GPIO0 and ePWM1B is on GPIO1
//!  - ePWM2A is on GPIO2 and ePWM2B is on GPIO3
//!  - ePWM4A is on GPIO6 and ePWM4B is on GPIO7
//!  - CMPSS1_TRIPH is on GPIO25 and CMPSS1_TRIPL is on GPIO26
//!  - ePWM1_DEACTIVE is on GPIO24
//!  - ePWM4_DEMONTRIP is on GPIO15
//!  - DAC1 output can be seen on P1 (ADC-A0) pin
//!
//! For DAC1, DACVALS -> DACVALA shadow to active load happening
//! on SYSCLK and a 2 us delay is provided after loading.
//! Shadow to active load can be configured to load on EPWMSYNCPER
//! for better control.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#include "c2000ware_libraries.h"

//
// Globals
//
uint16_t dacVal = 0U;

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
    // Set EPWM Clock Divider to 1 to feed 200 MHz SysClock.
    // Note: Default value is 2.
    //
    SysCtl_setEPWMClockDivider(SYSCTL_EPWMCLK_DIV_1);

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        //
        // Varying analog voltage value from 0V to 2.5V
        //
        if(dacVal >= 4096U)
        {
            dacVal = 0U;
        }
        DAC_setShadowValue(myDAC1_BASE, dacVal++);
        DEVICE_DELAY_US(2U);
    }
}

//
// End of File
//
