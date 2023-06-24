//#############################################################################
//
// FILE:   memcfg_ex1_error_handling.c
//
// TITLE:  Correctable & Uncorrectable Memory Error Handling
//
//! \addtogroup driver_example_list
//! <h1> Correctable & Uncorrectable Memory Error Handling</h1>
//!
//! This example demonstrates error handling in case of various erroneous memory
//! read/write operations. Error handling in case of CPU read/write violations,
//! correctable & uncorrectable memory errors has been demonstrated.
//!
//! Test functions used in this example
//! - generateMasterCPUWrViolation - 
//!    - This test configures Memconfig to block CPU writes to GS0 RAM. A write
//!      attempt to this memory location by CPU causes RAM_ACC_VIOL Interrupt
//! - generateParityMemUncorrError
//!    - This test induces parity error in GS0 RAM. A read from the corrupted
//!      memory location causes NMI
//! - generateECCMemCorrError
//!    - This test induces single bit ECC error in GS0 RAM. A read from the
//!      corrupted memory location causes INT_RAM_CORR_ERR Interrupt
//! - generateECCMemUncorrError
//!    - This test induces double bit ECC error in GS0 RAM. A read from the 
//!      corrupted memory location causes NMI
//! - forceNonMasterDMAReadViolation
//!    - This forces a DMA access violation using MemCfg_forceViolationInterrupt
//!      API. This casuses RAM_ACC_VIOL Interrupt
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
//############################################################################
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

#define GS0_RAM_BASE        0x0000C000
#define GS0_RAM_END_ADDR    0x0000C7FF
#define M1_RAM_BASE         0x00000400
#define M1_RAM_END_ADDR     0x000007FF

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
// Global to capture source of sys_int interrupt
//
volatile uint32_t sysIntStatus = 0;

//
// Interrupt counters
//
volatile uint32_t ramAccViolCnt = 0;
volatile uint32_t ramCorrErrCnt = 0;
volatile uint32_t nmiIntCnt = 0;

//
// Flags for correctable & uncorrectable interrupts
//
volatile uint32_t corrErrIntFlg = 0;
volatile uint32_t uncorrErrIntFlg = 0;

//
// Function Prototypes
//
void writeCAFE(uint32_t startAddress, uint32_t endAddress);
uint32_t generateMasterCPUWrViolation(void);
uint32_t generateParityMemUncorrError(void);
uint32_t generateECCMemCorrError(void);
uint32_t generateECCMemUncorrError(void);
uint32_t forceNonMasterDMAReadViolation(void);

//
// ISRs
//
__interrupt void ramAccViolISR(void);;
__interrupt void ramCorrErrISR(void);;
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
    // Enable RAM Correctable Error Interrupt register the ISR
    //
    Interrupt_register(INT_RAM_CORR_ERR, ramCorrErrISR);
    Interrupt_enable(INT_RAM_CORR_ERR);

    //
    // Enable RAM Correctable Error Interrupt register the ISR
    //
    Interrupt_register(INT_RAM_ACC_VIOL, ramAccViolISR);
    Interrupt_enable(INT_RAM_ACC_VIOL);

    //
    // Register ISR for NMI
    //
    Interrupt_register(INT_NMI, nmiISR);
    SysCtl_enableNMIGlobalInterrupt();
    
    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;
    ERTM;

    //
    // Parity memory uncorrectable error generation & handling
    //
    errCountLocal = generateParityMemUncorrError();
    errCountGlobal = errCountGlobal + errCountLocal;

    //
    // ECC memory uncorrectable error generation & handling
    //
    errCountLocal = generateECCMemUncorrError();
    errCountGlobal = errCountGlobal + errCountLocal;

    //
    // ECC memory correctable error generation & handling
    //
    errCountLocal = generateECCMemCorrError();
    errCountGlobal = errCountGlobal + errCountLocal;

    //
    // Master CPU-write violation generation & handling
    //
    errCountLocal = generateMasterCPUWrViolation();
    errCountGlobal = errCountGlobal + errCountLocal;

    //
    // Non-Master DMA-read violation generation & handling
    //
    errCountLocal = forceNonMasterDMAReadViolation();
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
// forceNonMasterDMAReadViolation - Force non-master DMA read access violation
// through software and demonstrate violation handling.
//
uint32_t forceNonMasterDMAReadViolation(void)
{
    uint32_t i, testPassCnt = 0U;

    //
    // Enable interrupt
    //
    MemCfg_enableViolationInterrupt(MEMCFG_NMVIOL_DMAREAD);

    //
    // Reset ISR counter
    //
    ramAccViolCnt = 0;

    //
    // Force non-master DMA read violation through software
    //
    for(i = 0U; i < 5U; i++)
    {
        MemCfg_forceViolationInterrupt(MEMCFG_NMVIOL_DMAREAD);
    }

    while(ramAccViolCnt == 0U);
    if(ramAccViolCnt == 5U)
    {
        testPassCnt++;
    }

    //
    // Return status
    //
    if(testPassCnt == 1U)
    {
        return(0U);
    }
    else
    {
        return(1U);
    }
}

//
// generateParityMemUncorrError - Generate uncorrectable error in parity memory
// and demonstrate error handling in case of uncorr errors in parity memories.
// Note- Single bit error in parity memories generate uncorrectable errors.
//
uint32_t generateParityMemUncorrError()
{
    uint32_t i, memOffset;
    uint32_t readMemData = 0, testPassCnt = 0;
    uint32_t parityRead1 = 0, parityRead2 = 0;

    //
    // Clear uncorrectable error status.
    //
    MemCfg_clearUncorrErrorStatus(MEMCFG_UCERR_CPUREAD);

    //
    // Initialize memories & check if it is getting initialized
    //
    MemCfg_initSections(MEMCFG_SECT_GS0);
    while(MemCfg_getInitStatus(MEMCFG_SECT_GS0) != 1U);

    //
    // Write to GS0 RAM
    //
    writeCAFE(GS0_RAM_BASE, GS0_RAM_END_ADDR);

    //
    // Reset the error flag
    //
    uncorrErrIntFlg = 0U;

    //
    // Generating 5 uncorrectable errors at different memory locations
    //
    for(i = 0; i < 0x5U; i++)
    {
        //
        // Reset the error flag
        //
        uncorrErrIntFlg = 0U;

        //
        // Corrupting some random address
        //
        memOffset = 0x08U + (i * 8U);

        //
        // Set the memory in ECC write mode.
        //
        MemCfg_setTestMode(MEMCFG_SECT_GS0, MEMCFG_TEST_WRITE_PARITY);
        parityRead1 = HWREGH(GS0_RAM_BASE + memOffset);

        //
        // Set the memory in Data write mode & flip 2 bits in data to generate
        // uncorrectable error. Writing the data to memory in test mode
        // doesn't modify the ECC.
        //
        MemCfg_setTestMode(MEMCFG_SECT_GS0 ,MEMCFG_TEST_WRITE_DATA);
        HWREGH(GS0_RAM_BASE + memOffset) = HWREGH(GS0_RAM_BASE + memOffset) ^
                                           0x01;

        //
        // Go back to ECC write mode to confirm that ECC is not changed.
        //
        MemCfg_setTestMode(MEMCFG_SECT_GS0 ,MEMCFG_TEST_WRITE_PARITY);
        parityRead2 = HWREGH(GS0_RAM_BASE + memOffset);

        //
        // Go to functional mode and try to read data from memory to generate
        // uncorrectable error as 2 bits of data were flipped in data write
        // mode but ECC was unchanged.
        //
        MemCfg_setTestMode(MEMCFG_SECT_GS0 ,MEMCFG_TEST_FUNCTIONAL);
        readMemData = HWREGH(GS0_RAM_BASE + memOffset);

        while(uncorrErrIntFlg == 0x0U);

        //
        // Check whether uncorrectable error is getting generated at the
        // correct address or not.
        //
        if((readMemData != 0xCAFE) && (parityRead1 == parityRead2) &&
           (errorType & MEMCFG_UCERR_CPUREAD != 0) &&
           (errorAddress == GS0_RAM_BASE + memOffset))
        {
            testPassCnt++;
        }

        //
        // Write the correct data in memory. Application can choose to re-write the
        // whole memory region to avoid any possible data corruption using following:
        // writeCAFE(GS0_RAM_BASE, GS0_RAM_END_ADDR);
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

//
// generateECCMemUncorrError - Generate uncorrectable error in ECC memory &
// demonstrate the interrupt handling in case of uncorr error in ECC memories.
// Note - Double bit errors in ECC memories generate uncorrectable errors.
//
uint32_t generateECCMemUncorrError()
{
    uint32_t i, memOffset;
    uint32_t readMemData = 0, testPassCnt = 0;
    uint32_t eccRead1 = 0, eccRead2 = 0;

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
    // Write to M1 RAM
    //
    writeCAFE(M1_RAM_BASE, M1_RAM_END_ADDR);

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
        memOffset = 0x08U + (i * 8U);

        //
        // Set the memory in ECC write mode.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_WRITE_ECC);
        eccRead1 = HWREGH(M1_RAM_BASE + memOffset);

        //
        // Set the memory in Data write mode & flip 2 bits in data to generate
        // uncorrectable error. Writing the data to memory in test mode
        // doesn't modify the ECC.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_WRITE_DATA);
        HWREGH(M1_RAM_BASE + memOffset) = HWREGH(M1_RAM_BASE + memOffset) ^
                                           0x03;

        //
        // Go back to ECC write mode to confirm that ECC is not changed.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_WRITE_ECC);
        eccRead2 = HWREGH(M1_RAM_BASE + memOffset);

        //
        // Go to functional mode and try to read data from memory to generate
        // uncorrectable error as 2 bits of data were flipped in data write
        // mode but ECC was unchanged.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_FUNCTIONAL);
        readMemData = HWREGH(M1_RAM_BASE + memOffset);

        while(uncorrErrIntFlg == 0);

        //
        // Check whether uncorrectable error is getting generated at the
        // correct address or not.
        //
        if((readMemData != 0xCAFE) && (eccRead1 == eccRead2) &&
           (errorType & MEMCFG_UCERR_CPUREAD != 0) &&
           (errorAddress == M1_RAM_BASE + memOffset))
        {
            testPassCnt++;
        }

        //
        // Write the correct data in memory. Application can choose to re-write the
        // whole memory region to avoid any possible data corruption using following:
        // writeCAFE(M1_RAM_BASE, 0xB7FFU);
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

//
// generateECCMemCorrError - Generate correctable error in ECC memory
// Note- Single bit errors in ECC memories generate correctable errors.
//
uint32_t generateECCMemCorrError()
{
    uint32_t i, memOffset;
    uint32_t readMemData = 0, testPassCnt = 0;
    uint32_t eccRead1 = 0, eccRead2 = 0;

    //
    // Initialize memories & check if it is getting initialized
    //
    MemCfg_initSections(MEMCFG_SECT_M1);
    while(MemCfg_getInitStatus(MEMCFG_SECT_M1) != 1U);

    //
    // Write to LS7 RAM - 0xB800 - 0xBFFF
    //
    writeCAFE(M1_RAM_BASE, M1_RAM_END_ADDR);

    //
    // Clear correctable error status
    //
    MemCfg_clearCorrErrorStatus(MEMCFG_CERR_CPUREAD);
    MemCfg_clearCorrErrorInterruptStatus(MEMCFG_CERR_CPUREAD);

    //
    // Set error threshold to generate interrupt after configured no of
    // correctable errors. Setting it to 1 to generate error on each error.
    //
    MemCfg_setCorrErrorThreshold(1U);

    //
    // Enable correctable errors at peripheral level
    //
    MemCfg_enableCorrErrorInterrupt(MEMCFG_CERR_CPUREAD);

    //
    // Clear sys_int counter
    //
    ramCorrErrCnt = 0;

    //
    // Generating 5 correctable errors at some locations in memory
    //
    for(i = 0U; i < 0x5U; i++)
    {
        //
        // Reset the corr error count.
        //
        corrErrIntFlg = 0U;

        //
        //  Corrupting some random address
        //
        memOffset = 0x08U + (i * 8U);

        //
        // Set the memory in ECC write mode.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_WRITE_ECC);
        eccRead1 = HWREGH(M1_RAM_BASE + memOffset);

        //
        // Set the memory in Data write mode & flip 1 bit in data to generate
        // correctable error. Writing the data to memory in test mode
        // doesn't modify the ECC.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_WRITE_DATA);
        HWREGH(M1_RAM_BASE + memOffset) = HWREGH(M1_RAM_BASE + memOffset) ^
                                           0x02U;

        //
        // Go back to ECC write mode to confirm that ecc is not changed.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1, MEMCFG_TEST_WRITE_ECC);
        eccRead2 = HWREGH(M1_RAM_BASE + memOffset);

        //
        // Go to functional mode and try to read data from memory to generate
        // correctable error as 1 bits of data was flipped in data write
        // mode but ECC was unchanged.
        //
        MemCfg_setTestMode(MEMCFG_SECT_M1 ,MEMCFG_TEST_FUNCTIONAL);
        readMemData = HWREGH(M1_RAM_BASE + memOffset);

        while(corrErrIntFlg == 0U);
        if((eccRead1 == eccRead2) && (readMemData == 0xCAFE))
        {
            testPassCnt++;
        }
    }

    //
    // Return status
    //
    if(testPassCnt == 5)
    {
        return 0U;
    }
    else
    {
        return 1U;
    }
}
// generateMasterCPUWrViolation - Generate Master CPU Write Violation
//
uint32_t generateMasterCPUWrViolation()
{
    uint32_t i, testPassCnt = 0U;

    //
    // Initialize memories & check if it is getting initialized
    //
    MemCfg_initSections(MEMCFG_SECT_GS0);
    while(MemCfg_getInitStatus(MEMCFG_SECT_GS0) != 1U);

    //
    // Write to GS2 RAM - 0xF000-0xFFFF
    //
    writeCAFE(GS0_RAM_BASE, GS0_RAM_END_ADDR);

    //
    // Enable violation interrupt
    //
    MemCfg_enableViolationInterrupt(MEMCFG_MVIOL_CPUWRITE);

    //
    // Set write protection which generates master CPU-write violation in
    // case of CPU-writes.
    //
    MemCfg_setProtection(MEMCFG_SECT_GS0, MEMCFG_PROT_BLOCKCPUWRITE);

    //
    // Clear sys_int counter
    //
    ramAccViolCnt = 0;

    //
    // Write to memory will generate master CPU write violation as
    // CPU writes are blocked
    //
    for(i = 0U; i < 5U; i++)
    {
        HWREGH(GS0_RAM_BASE + (0x08U + (2U * i))) = 0xEFFFU;
    }

    while(ramAccViolCnt < 5U);
    testPassCnt++;
    MemCfg_disableViolationInterrupt(MEMCFG_MVIOL_CPUWRITE);

    //
    // Return status
    //
    if(testPassCnt == 1U)
    {
        return 0U;
    }
    else
    {
        return 1U;
    }
}


//
// sys_error interrupt ISR
//
__interrupt void ramAccViolISR(void)
{
    ramAccViolCnt++;

    intStatus = MemCfg_getViolationInterruptStatus();

    if((intStatus & MEMCFG_NMVIOL_DMAREAD) != 0x0U)
    {
        //
        // Capture the address at which violation occurred
        //
        errorAddress = MemCfg_getViolationAddress(MEMCFG_NMVIOL_DMAREAD);

        //
        // Clear peripheral related flags
        //
        MemCfg_clearViolationInterruptStatus(MEMCFG_NMVIOL_DMAREAD);
    }
    if((intStatus & MEMCFG_NMVIOL_CPUREAD) != 0x0U)
    {
        //
        // Capture the address at which violation occurred
        //
        errorAddress = MemCfg_getViolationAddress(MEMCFG_NMVIOL_CPUREAD);

        //
        // Clear peripheral related flags
        //
        MemCfg_clearViolationInterruptStatus(MEMCFG_NMVIOL_CPUREAD);
    }
    if((intStatus & MEMCFG_NMVIOL_CPUWRITE) != 0x0U)
    {
        //
        // Capture the address at which violation occurred
        //
        errorAddress = MemCfg_getViolationAddress(MEMCFG_NMVIOL_CPUWRITE);

        //
        // Clear peripheral related flags
        //
        MemCfg_clearViolationInterruptStatus(MEMCFG_NMVIOL_CPUWRITE);
    }
    if((intStatus & MEMCFG_MVIOL_CPUWRITE) != 0x0U)
    {
        //
        // Capture the address at which violation occurred
        //
        errorAddress = MemCfg_getViolationAddress(MEMCFG_MVIOL_CPUWRITE);

        //
        // Clear peripheral related flags
        //
        MemCfg_clearViolationInterruptStatus(MEMCFG_MVIOL_CPUWRITE);
    }

    //
    // Clear the interrupt at PIE level
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP12);
}

__interrupt void ramCorrErrISR(void)
{
    ramCorrErrCnt++;

    intStatus = MemCfg_getCorrErrorStatus();
    if((intStatus & MEMCFG_CERR_CPUREAD) != 0x0U)
    {
        corrErrIntFlg = 1U;

        //
        // Capture error address
        //
        errorAddress = MemCfg_getCorrErrorAddress(MEMCFG_CERR_CPUREAD);

        //
        // Clear flags at the memcfg peripheral side
        //
        MemCfg_clearCorrErrorStatus(MEMCFG_CERR_CPUREAD);
        MemCfg_clearCorrErrorInterruptStatus(MEMCFG_CERR_CPUREAD);
    }

    //
    // Clear the interrupt at PIE level
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP12);
}

__interrupt void nmiISR(void)
{
    nmiIntCnt++;
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
