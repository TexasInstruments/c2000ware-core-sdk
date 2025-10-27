//#############################################################################
//
// FILE:   nmi_ex1_cpu1handling.c
//
// TITLE:  NMI Handling between CPU cores
//
//! \addtogroup driver_dual_example_list
//! <h1> NMI handling</h1>
//!
//! This example demonstrates how to handle an NMI.
//!
//! The watchdog of CPU2 is configured to reset the core once the watchdog
//! overflows and in the CPU1 the NMI is triggered.
//! The NMI status is read and is verified to be due to CPU2 Watchdog reset.
//! The NMI ISR reboots the CPU2 core and the process is repeated.
//!
//! \b  Watch \b Variables
//!  - \e nmi_isr_count Indicates the number of times the NMI ISR was hit
//!                     because of CPU2 watchdog reset.
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include <stdint.h>
#include <stdbool.h>

#include "sysctl.h"
#include "driverlib.h"
#include "device.h"

//
// Globals
//
volatile uint32_t nmiflagstatus = 0, nmisdflagstatus = 0;
volatile uint16_t nmi_isr_called = 0, nmi_isr_count = 0;

//
// Function Prototypes
//
interrupt void nmi_isr(void);

void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();
    //
    // Boot CPU2 core
    //
#ifdef _FLASH
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
#endif


    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR)
    //
    Interrupt_initVectorTable();
    SysCtl_clearAllNMIFlags();
    Interrupt_register(INT_NMI, &nmi_isr);

    //
    // Configure LED1 pin and assign it to CPU2 core
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU2);

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

    while(1)
    {
        //
        // Wait for the NMI ISR
        //
        while(nmi_isr_called != 1);

        //
        // Check the NMI flag
        //
        if(nmiflagstatus != (SYSCTL_NMI_CPU2WDRSN | SYSCTL_NMI_NMIINT))
        {
            //
            // Invalid NMI occurred.
            //
            ESTOP0;
        }

        nmi_isr_called = 0;
        nmi_isr_count++;
    }
}




interrupt void nmi_isr(void)
{
    nmi_isr_called = 1;

    //
    // Read the NMI flags and NMI shadow flags
    //
    nmiflagstatus = SysCtl_getNMIFlagStatus();
    nmisdflagstatus = SysCtl_getNMIShadowFlagStatus();

    //
    // Clear all the NMI flags
    //
    SysCtl_clearAllNMIFlags();

    //
    // If the NMI is caused due to CPU2 watchdog reset, boot the CPU2 core
    //
    if((nmiflagstatus & SYSCTL_NMI_CPU2WDRSN) != 0)
    {
#ifdef _FLASH
        Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
        Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
#endif
    }
}
