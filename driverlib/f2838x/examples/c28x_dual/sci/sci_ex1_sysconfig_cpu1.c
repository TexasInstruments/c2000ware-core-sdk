//#############################################################################
//
// FILE:   sci_ex1_sysconfig_cpu1.c
//
// TITLE: SysConfig SCI exhoback example
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
#include "inc/hw_ipc.h"
#include "board.h"

//
// Defines
//
// Define AUTOBAUD to use the autobaud lock feature
//#define AUTOBAUD


//
// Main
//
void main(void)
{
    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Hand-over the SCIA module access to CPU2
    //
    //SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL5_SCI, 1, SYSCTL_CPUSEL_CPU2);
    Board_init();

    //
    // Configuration for STANDALONE and FLASH mode
    //
#ifdef _STANDALONE
    //
    // Send boot command to allow the CPU2 application to begin execution
    //
    Device_bootCPU2(BOOT_MODE_CPU2);
#endif // _STANDALONE

    //
    // Configuration for the SCI Rx pin.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);

    //
    // Configuration for the SCI Tx pin.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);

    //
    // Sync CPU1 and CPU2. Send IPC flag 17 to CPU2.
    //
    IPC_sync(IPC_CPU1_L_CPU2_R, SYNC_FLAG);

    //
    // Initialize interrupt controller and vector table.
    //
    Interrupt_initModule();
    Interrupt_initVectorTable();

}

//
// End of File
//

