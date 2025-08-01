//#############################################################################
//
// FILE:   memcfg_ex1_error_handling.c
//
// TITLE:  Uncorrectable Memory Error Handling
//
//! \addtogroup driver_example_list
//! <h1> Correctable & Uncorrectable Memory Error Handling</h1>
//!
//! This example demonstrates error handling in case of various erroneous memory
//! read/write operations. Error handling in case of CPU read/write violations,
//! uncorrectable memory errors has been demonstrated.
//! Uncorrectable memory errors & violations can generate NMI interrupt
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b  Watch \b Variables
//! - \b testStatusGlobal - Equivalent to \b TEST_PASS if test finished
//!                         correctly, else the value is set to \b TEST_FAIL
//! - \b errCountGlobal - Error counter
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
#include "device.h"
#include "driverlib.h"

//
// Defines
//
#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD

//
// Globals
//
uint16_t errCountGlobal = 0;
uint32_t testStatusGlobal;

//
// Globals to capture error type & address in ISR
//
volatile uint32_t errorAddress = 0, errorType = 0;

//
// Global to capture source of memory error
//
volatile uint32_t intStatus = 0;

//
// Flags for uncorrectable interrupts
//
volatile uint32_t uncorrErrIntFlg = 0;

//
// Function Prototypes
//
void writeCAFE(uint32_t startAddress, uint32_t endAddress);
uint32_t generateECCMemUncorrError(void);

//
// ISRs
//
__interrupt void nmiISR(void);

//
// Main
//
void main(void)
{
    uint16_t errCountLocal = 0;
    testStatusGlobal = TEST_FAIL;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
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
    // Masking all the other interrupt sources for memcfg test cases.
    // Unmask the other interrupts as per application need.
    //
    SysCtl_setInterruptStatusMask(0x3E2U);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;
    ERTM;

    //
    // Register ISR for NMI
    //
    Interrupt_register(INT_NMI, nmiISR);
    SysCtl_enableNMIGlobalInterrupt();

    //
    // ECC memory uncorrectable error generation & handling
    //
    errCountLocal = generateECCMemUncorrError();
    errCountGlobal = errCountGlobal + errCountLocal;

    if(errCountGlobal == 0x0)
    {
        testStatusGlobal = TEST_PASS;
    }

    //
    // Loop indefinitely
    //
    while(1)
    {
    }
}

//
// generateECCMemUncorrError - Generate uncorrectable error in ECC memory &
// demonstrate the interrupt handling in case of uncorr error in ECC memories.
// Note - Double bit errors in ECC memories generate uncorrectable errors.
//
uint32_t generateECCMemUncorrError()
{
    uint32_t i, memOffset;
    uint32_t readMemData = 0, testPassCnt = 0;
    uint32_t eccRead1 = 0;

    //
    // Clear uncorrectable error status.
    //
    MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_CPUREAD);

    //
    // Initialize memories & check if it is getting initialized
    //
    MemCfg_initSections(MEMCFG_SECT_M1);
    while(MemCfg_getInitStatus(MEMCFG_SECT_M1) != 1U);

    //
    // Write to M0 RAM - 0x0000-0x03FF
    //
    writeCAFE(M1_RAM_BASE, 0x7FFU);

    //
    // Reset the error flag
    //
    uncorrErrIntFlg = 0U;

    //
    // Generating 5 uncorrectable errors at some locations in memory
    //
    for(i = 0; i < 0x5U; i++)
    {
        //
        // Reset error flag which gets set in ISR
        //
        uncorrErrIntFlg = 0;

        //
        // Corrupting some random address
        //
        memOffset = 0x10U + (i * 8U);

        //
        // Set the memory in ECC write mode.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_WRITE_ECC);
        eccRead1 = HWREGH(M1_RAM_BASE + memOffset);

        //
        // Set the memory in Data write mode & flip 1 bit in data to generate
        // uncorrectable error. Writing the data to memory in test mode
        // doesn't modify the ECC.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_WRITE_DATA);
        HWREGH(M1_RAM_BASE + memOffset) = HWREGH(M1_RAM_BASE + memOffset) ^
                                           0x01;

        //
        // Go to functional mode and try to read data from memory to generate
        // uncorrectable error as 1 bits of data were flipped in data write
        // mode but ECC was unchanged.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_FUNCTIONAL);
        readMemData = HWREGH(M1_RAM_BASE + memOffset);

        while(uncorrErrIntFlg == 0);

        //
        // Check whether uncorrectable error is getting generated at the
        // correct address or not.
        //
        if((readMemData != 0xCAFE) &&
           (errorType & MEMCFG_UCERR_CPUREAD != 0) &&
           (errorAddress == M1_RAM_BASE + memOffset))
        {
            testPassCnt++;
        }

        //
        // Write the correct data in memory. Application can choose to re-write the
        // whole memory region to avoid any possible data corruption using following:
        // writeCAFE(M0_RAM_BASE, 0x03FFU);
        //
        HWREGH(errorAddress) = 0xCAFE;
    }

    //
    // Return status
    //
    if(testPassCnt == 5)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

__interrupt void nmiISR(void)
{
    //
    // Capture error type
    //
    errorType = MemCfg_getUncorrErrorStatus();
    if(errorType & MEMCFG_UCERR_CPUREAD != 0x0U)
    {
        //
        // capture error address
        //
        errorAddress = MemCfg_getUncorrErrorAddress(MEMCFG_UCERR_CPUREAD);

        //
        // Clear the flag at peripheral level
        //
        MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_CPUREAD);
    }

    //
    // Clear NMI flags
    //
    intStatus = SysCtl_getNMIFlagStatus();
    SysCtl_clearNMIStatus(intStatus);

    //
    // Set the flag
    //
    uncorrErrIntFlg = 1U;
}

void writeCAFE(uint32_t startAddress, uint32_t endAddress)
{
    uint16_t* addr;
    for (addr = (uint16_t*)startAddress; addr <= (uint16_t*)endAddress; addr++)
    {
        *addr = 0xCAFE;
    }
}

//
// End of File
//
