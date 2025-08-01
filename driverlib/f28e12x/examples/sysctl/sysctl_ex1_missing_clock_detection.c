//#############################################################################
//
// FILE:   sysctl_ex1_missing_clock_detection.c
//
// TITLE:  Missing clock detection
//
//! \addtogroup driver_example_list
//! <h1> Missing clock detection (MCD) </h1>
//!
//! This example demonstrates the missing clock detection functionality and
//! the way to handle it.
//! Once the MCD is simulated by disconnecting the OSCCLK to the MCD module
//! an NMI would be generated. This NMI determines that an MCD was generated
//! due to a clock failure which is handled in the ISR.
//!
//! Before an MCD the clock frequency would be as per device initialization (160Mhz).
//! Post MCD the frequency would move to SYSOSCDIV4.
//!
//! The example also shows how we can lock the PLL after missing clock,
//! detection, by first explicitly switching the clock source to SYSOSCDIV4,
//!  resetting the missing clock detect circuit and then re-locking the PLL.
//! Post a re-lock the clock frequency would be 160Mhz but using the SYSOSCDIV4 as
//! clock source.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - \b fail - Indicates that a missing clock was either not detected or was
//!       not handled correctly.
//!  - \b mcd_clkfail_isr - Indicates that the missing clock failure caused an
//!       NMI to be triggered and called an the ISR to handle it.
//!  - \b mcd_detect - Indicates that a missing clock was detected.
//!  - \b result - Status of a successful handling of missing clock detection
//!
//
//#############################################################################
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
// Globals
//
bool mcd_detect;
uint16_t nmistatus = 0;
uint32_t mcd_clkfail_isr = 0;

//
// Defines
//
#define PASS 0
#define FAIL 1

uint32_t result = FAIL;


//
// Define to pass to SysCtl_setClock(). Will configure the clock as follows:
// PLLSYSCLK = 8MHz (SYSOSCDIV4) * 40 (QDIV) / (1 (PDIV) * 2 (RDIVCLK0) * 1(SYSDIV))
//

//
// Function Prototypes
//
__interrupt void nmi_isr(void);

//
// Main
//
void main(void)
{
    uint32_t fail = 0;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

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
    // Re-map NMI signal to call the ISR function in this
    // example
    //
    SysCtl_clearAllNMIFlags();
    Interrupt_register(INT_NMI, &nmi_isr);

    //
    // Enabling the NMI global interrupt
    //
    SysCtl_enableNMIGlobalInterrupt();

    Interrupt_enable(INT_NMI);

    //
    // Enable Global Interrupt (INTM) and Real Time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Check the PLL System clock before the Missing clock detection
    // is simulated. It should be same as that set by Device_init().
    //
    if(SysCtl_getClock(DEVICE_OSCSRC_FREQ) != DEVICE_SYSCLK_FREQ)
        fail++;

    //
    // Enable the missing clock detection (MCD) Logic as a precaution.
    // The is continuously active, unless the MCD was disabled previously
    //
    SysCtl_enableMCD();

    //
    // Simulate a missing clock detection
    //
    SysCtl_disconnectMCDClockSource();

    //
    // Wait till the NMI is fired on clock failure
    //
    while(mcd_clkfail_isr != 0x1U);

    //
    // A missing clock was detected
    //
    if(mcd_detect != true)
        fail++;

    //
    // Check if the NMI triggered was due to a clock failure
    //
    if((nmistatus & SYSCTL_NMI_CLOCKFAIL) != SYSCTL_NMI_CLOCKFAIL)
        fail++;

    //
    // Check the PLL System clock after the Missing clock detection
    // is simulated. It should be equal to SYSOSCDIV4(8Mhz).
    //
    if(SysCtl_getClock(DEVICE_OSCSRC_FREQ) != SYSCTL_DEFAULT_OSC_FREQ)
        fail++;


    //
    // Disabling the PLL before changing the clk src
    //
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL) &=
        ~SYSCTL_SYSPLLCTL_PLLEN;
    EDIS;

    //
    // To lock the PLL after missing clock detection, we first explicitly
    // switch the clock source to SYSOSCDIV4, reset the missing clock detect
    // circuit and then re-lock the PLL.
    //
    // Configure oscillator source to SYSOSCDIV4
    //
    SysCtl_selectOscSource(SYSCTL_OSCSRC_SYSOSCDIV4);

    //
    // Re-connect missing clock detection clock source to stop simulating clock
    // failure
    //
    SysCtl_connectMCDClockSource();

    //
    // Reset the missing clock detection logic after clock failure
    //
    SysCtl_resetMCD();

    //
    // Set up PLL control and clock dividers using SYSOSCDIV4 as clock source
    //
    SysCtl_setClock(SYSCTL_OSCSRC_SYSOSCDIV4, SYSCTL_PLL_ENABLE, SYSCTL_PDIV_1,
                    SYSCTL_PLLMULT_40, SYSCTL_RDIVCLK0_2, SYSCTL_SYSDIV_1,
                    SYSCTL_DCC_BASE_0);

    //
    // Check the PLL System clock after the Missing clock detection
    // is cleared and handled using SYSOSCDIV4 as clock source.
    //
    if(SysCtl_getClock(SYSCTL_DEFAULT_SYSOSCDIV4_FREQ) != DEVICE_SYSCLK_FREQ)
        fail++;


    //
    // Status of a successful handling of missing clock detection
    //
    if (fail)
    {
        result = FAIL;
    }
    else
    {
        result = PASS;

    }
    while(1);
}

//
// NMI ISR - The interrupt service routine called when the NMI
//           is generated on clock failure detection
//
__interrupt void nmi_isr(void)
{
    mcd_clkfail_isr = 0x1U;
    mcd_detect = SysCtl_isMCDClockFailureDetected();
    nmistatus = SysCtl_getNMIFlagStatus();
    SysCtl_clearAllNMIFlags();
}


//
// End of File
//
