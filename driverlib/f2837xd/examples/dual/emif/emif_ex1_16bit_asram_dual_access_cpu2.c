//#############################################################################
//
// FILE:   emif_ex1_16bit_asram_dual_access_cpu2.c
//
// TITLE:  EMIF1 ASYNC module accessing 16bit ASRAM through CPU1 and CPU2.
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 ASYNC module accessing 16bit ASRAM trhough CPU1 and CPU2. </h1>
//!
//! This example configures EMIF1 in 16bit ASYNC mode and uses CS2 as chip
//! enable. The EMIF1 ownership is passed between CPU1 and CPU2 to access
//! different memory regions. Initially CPU2 grabs and configures the EMIF1,
//! thereafter both CPU1 and CPU2 grabs EMIF1 to access different memory regions
//! in external memory.
//!
//! \b External \b Connections \n
//!  - External ASRAM memory (CY7C1041CV33 -10ZSXA) daughter card
//!
//! \b Watch \b Variables \n
//! - \b testStatusGlobalCPU2 - Equivalent to \b TEST_PASS if test finished
//!                         correctly, else the value is set to \b TEST_FAIL
//! - \b errCountGlobalCPU2 - Error counter
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
// Defines
//
#define TEST_PASS 0xABCDABCDU
#define TEST_FAIL 0xDEADDEADU

//
// Defines for external memory addresses to be be accessed. The ASRAM memory
// size used for this example is 256K x 16. CPU2 accesses lower 128K x 16
// memory range.
//
#define ASRAM_CS2_START_ADDR_CPU2 0x100000U
#define ASRAM_CS2_SIZE 0x20000U

//
// Define for memory R/W iterations
//
#define MEM_RW_ITER    0x2U

//
// Globals
//
uint16_t errCountGlobalCPU2 = 0U;
uint32_t testStatusGlobalCPU2;
uint32_t i, iter;

//
// Function Prototypes
//
uint16_t readWriteMemCPU2(uint32_t startAddr, uint32_t memSize);

//
// Main
//
void main(void)
{
    uint16_t errCountLocal;
    EMIF_AsyncTimingParams tparam;
    uint16_t ipcFlag11 = 11U;
    testStatusGlobalCPU2 = TEST_FAIL;

    //
    // Initialize device clock and peripherals.
    //
    Device_init();

    //
    // Disable all the interrupts.
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
    // Grab EMIF1 For CPU2.
    //
    EMIF_selectMaster(EMIF1CONFIG_BASE, EMIF_MASTER_CPU2_G);

    //
    // Configure to run EMIF1 on full Rate. (EMIF1CLK = CPU1SYSCLK)
    //
    SysCtl_setEMIF1ClockDivider(SYSCTL_EMIF1CLK_DIV_1);

    //
    // Configures Normal Asynchronous Mode of Operation.
    //
    EMIF_setAsyncMode(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET,
                      EMIF_ASYNC_NORMAL_MODE);

    //
    // Disables Extended Wait Mode.
    //
    EMIF_disableAsyncExtendedWait(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET);

    //
    // Configure EMIF1 Data Bus Width.
    //
    EMIF_setAsyncDataBusWidth(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET,
                              EMIF_ASYNC_DATA_WIDTH_16);

    //
    // Configure the access timing for CS2 space.
    //
    tparam.rSetup = 0;
    tparam.rStrobe = 3;
    tparam.rHold = 0;
    tparam.turnArnd = 0;
    tparam.wSetup = 0;
    tparam.wStrobe = 1;
    tparam.wHold = 0;
    EMIF_setAsyncTimingParams(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET, &tparam);
    EMIF_selectMaster(EMIF1CONFIG_BASE, EMIF_MASTER_CPU1_NG);

    //
    // Sync CPU1 and CPU2. Send IPC flag 11 to CPU1.
    //
    HWREG(IPC_BASE + IPC_O_SET) = 1UL << ipcFlag11;

    for(iter = 0; iter < MEM_RW_ITER; iter++)
    {
        //
        // Grab EMIF1 For CPU2.
        //
        while(HWREGH(EMIF1CONFIG_BASE + MEMCFG_O_EMIF1MSEL) !=
                                                       EMIF_MASTER_CPU2_G)
        {
            EMIF_selectMaster(EMIF1CONFIG_BASE, EMIF_MASTER_CPU2_G);
        }

        //
        // Check basic RD/WR access to CS2 space.
        //
        errCountLocal = readWriteMemCPU2(ASRAM_CS2_START_ADDR_CPU2,
                                         ASRAM_CS2_SIZE);
        errCountGlobalCPU2 = errCountGlobalCPU2 + errCountLocal;

        //
        // Release EMIF1.
        //
        EMIF_selectMaster(EMIF1CONFIG_BASE, EMIF_MASTER_CPU1_NG);
    }

    if(errCountGlobalCPU2 == 0x0U)
    {
        testStatusGlobalCPU2 = TEST_PASS;
    }
    else
    {
        testStatusGlobalCPU2 = TEST_FAIL;
    }

    while(1);
}

//
// Read Write Memory - This function performs simple read/write word accesses
// to memory.
//
uint16_t readWriteMemCPU2(uint32_t startAddr, uint32_t memSize)
{
    static uint16_t iterCnt = 0;
    uint16_t memReadData;
    uint16_t memWriteData;
    uint16_t *memPtr;
    uint32_t i;

    iterCnt++;
    memPtr = (uint16_t *)startAddr;

    //
    // Write data to memory.
    //
    memWriteData = 0x1111U;
    for(i = 0U; i < memSize; i++)
    {
        *memPtr++ = memWriteData;
        memWriteData += (0x1111U + iterCnt);
    }

    //
    // Verify data written to memory.
    //
    memWriteData = 0x1111U;
    memPtr = (uint16_t *)startAddr;
    for(i = 0U; i < memSize; i++)
    {
        memReadData = *memPtr;
        if(memReadData != memWriteData)
        {
            return(1U);
        }
        memPtr++;
        memWriteData += (0x1111U + iterCnt);
    }
    return(0U);
}

//
// End of File
//
