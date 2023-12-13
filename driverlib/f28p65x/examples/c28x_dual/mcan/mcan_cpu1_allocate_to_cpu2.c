//#############################################################################
//
// FILE:   mcan_cpu1_allocate_to_cpu2.c
//
// TITLE:  MCAN Dual Core Example
//
//! \addtogroup driver_dual_example_list
//! <h1> MCAN Dual Core Example</h1>
//!
//! This example demonstrates how to allocate MCAN peripheral using CPU1
//! so that it can be operated using CPU2.
//!
//! \note In the default CPU2 linker cmd file, GS4, FLASH_BANK3 and FLASH_BANK4
//! are used for allocating various CPU2 sections. The CPU1 application
//! assigns the ownership of these memory regions to CPU2. Please note that CPU2
//! .out file can be loaded only after CPU1 completes this configuration
//!
//! The erase setting (CPU1/CPU2 On-Chip Flash -> erase setting) needs to be
//! configured as selected banks only (Choose the corresponding BANKS allocated
//! for CPUs) or necessary sectors only before loading CPU1/CPU2.out file
//! (This is applicable only for FLASH configuration)
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
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
    // Assign RAMs and Flash banks to CPU2.
    // In the default CPU2 linker cmd files, GS4, FLASH_BANK3 and FLASH_BANK4
    // are used for allocating various CPU2 sections.
    // In case CPU2 needs additional RAM or Flash regions, CPU1 needs to assign
    // its ownership to CPU2 using the following functions :
    //      - MemCfg_setGSRAMControllerSel for GSRAM
    //      - SysCtl_allocateDxRAM for DRAM
    //      - SysCtl_allocateFlashBank for Flash
    //
    MemCfg_setGSRAMControllerSel(MEMCFG_SECT_GS4, MEMCFG_GSRAMCONTROLLER_CPU2);
    SysCtl_allocateFlashBank(SYSCTL_FLASH_BANK3, SYSCTL_CPUSEL_CPU2);
    SysCtl_allocateFlashBank(SYSCTL_FLASH_BANK4, SYSCTL_CPUSEL_CPU2);
 
    //
    // Boot CPU2 core
    //
#ifdef _FLASH
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_BANK3_SECTOR0);
#else
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
#endif

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Configuring the GPIOs for MCAN.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANTXA);

    //
    // Configure the divisor for the MCAN bit-clock
    //
    SysCtl_setMCANClk(SYSCTL_MCANA, SYSCTL_MCANCLK_DIV_5);

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
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Allocate Ethercat to CPU2
    //
    SysCtl_selectCPUForPeripheralInstance(SYSCTL_CPUSEL_MCANA, SYSCTL_CPUSEL_CPU2);

    //
    // Wait Forever
    //
    while(1)
    {
        //
        // Additional CPU1 actions can be added here
        //
    }
}

//
// End of File
//
