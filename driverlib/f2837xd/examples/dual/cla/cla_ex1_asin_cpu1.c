//###########################################################################
//
// FILE:   cla_ex1_asin_cpu1.c
//
// TITLE:  CLA Arcsine Example for F2837xD.
//
//! \addtogroup dual_example_list
//! <h1>CLA \f$arcsine(x)\f$ using a lookup table  (cla_asin_cpu01)</h1>
//!
//! In this example,  cpu1 will be used to initialize the clocks for cpu2.cla1.
//! Task 1 of the CLA on cpu2 will calculate the arcsine of
//! an input argument in the range (-1.0 to 1.0) using a lookup table.
//!
//! \b Memory \b Allocation \n
//!  - CLA1 Math Tables (RAMLS0)
//!    - CLAasinTable - Lookup table
//!  - CLA1 to CPU Message RAM
//!    - fResult - Result of the lookup algorithm
//!  - CPU to CLA1 Message RAM
//!    - fVal - Sample input to the lookup algorithm
//!
//! \b Watch \b Variables \n
//! - fVal - Argument to task 1
//! - fResult - Result of \f$arcsin(fVal)\f$
//!
//! \note CPU2 must turn on the CLA clock by writing a 1 to
//! CpuSysRegs.PCLKCR0.bit.CLA1.
//!
//
//#############################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Globals
//
uint16_t pass=0;
uint16_t fail=0;

//
// Function Prototypes
//
void initCpuXCla1(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

#ifdef _STANDALONE
#ifdef _FLASH
    //
    // Send boot command to allow the CPU2 application to begin execution
    //
    Device_bootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
    //
    // Send boot command to allow the CPU2 application to begin execution
    //
    Device_bootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);

#endif // _FLASH
#endif // _STANDALONE

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Disable global interrupts.
    //
    DINT;

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
    // Turn on the CLA clocks on both CPUs.
    //
    initCpuXCla1();

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global real-time interrupt DBGM

    while(1);
}

//
// initCpuXCla1 - Enable CLA1 on CPU1 and CPU2
//
void initCpuXCla1(void)
{
    uint16_t ipcFlag = 5U;

#ifdef CPU1
    EALLOW;
    //
    // Enable CPU1 CLA1
    //
    HWREG(DEVCFG_BASE + SYSCTL_O_DC1) |= SYSCTL_DC1_CPU1_CLA1;

    //
    // Enable CPU2 CLA1
    //
    HWREG(DEVCFG_BASE + SYSCTL_O_DC1) |= SYSCTL_DC1_CPU2_CLA1;

    EDIS;
#endif //CPU1

    //
    // Send IPC flag 5 to CPU2
    //
    HWREG(IPC_BASE + IPC_O_SET) = 1UL << ipcFlag;

    //
    // Wait for IPC flag 5 from CPU2
    //
    while((HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag)) == 0x00000000UL)
    {
    }

    //
    // ACK IPC flag 5 for CPU2
    //
    HWREG(IPC_BASE + IPC_O_ACK) = 1UL << ipcFlag;

    //
    // Wait for ACK of IPC flag 5 from CPU2
    //
    while((HWREG(IPC_BASE + IPC_O_FLG) & (1UL << ipcFlag)) != 0x00000000UL)
    {
    }
}

//
// End of file
//
