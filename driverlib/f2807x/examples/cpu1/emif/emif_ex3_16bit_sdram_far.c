//#############################################################################
//
// FILE:   emif_ex3_16bit_sdram_far.c
//
// TITLE:  EMIF1 module accessing 16bit SDRAM using memcpy_fast_far().
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 module accessing 16bit SDRAM using memcpy_fast_far(). </h1>
//!
//! This example configures EMIF1 in 16bit SYNC mode and uses CS0 as chip
//! enable.It will first write to an array in the SDRAM and then read it
//! back using the FPU function, memcpy_fast_far(), for both operations.
//!
//! The buffer in SDRAM will be placed in the .farbss memory on account
//! of the fact that its assigned the attribute "far" indicating it lies
//! beyond the 22-bit program address space. The compiler will take care
//! to avoid using instructions such as PREAD, which uses the Program
//! Read Bus, or addressing modes restricted to the lower 22-bit space
//! when accessing data with the attribute "far".
//!
//! \note The memory space beyond 22-bits must be treated as data space
//! for load/store operations only. The user is cautioned against using
//! this space for either instructions or working memory.
//!
//! \b External \b Connections \n
//!  - External SDR-SDRAM memory (MT48LC32M16A2 -75) daughter card
//!
//! \b Watch \b Variables \n
//! - \b testStatusGlobal - Equivalent to \b TEST_PASS if test finished
//!                         correctly, else the value is set to \b TEST_FAIL
//! - \b errCountGlobal - Error counter
//!
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
// FPU header file to access memcpy_fast_far().
//
#include "fpu_vector.h"

//
// Defines
//
#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD
#define MEM_BUFFER_SIZE 0x500

//
// Globals
//
uint16_t errCountGlobal = 0;
uint32_t testStatusGlobal;

//
// Buffer in local memory.
//
uint32_t localRAMBuf[MEM_BUFFER_SIZE];

//
// Buffer in far memory.
//
__attribute__((far)) volatile uint32_t extSDRAMBuf[MEM_BUFFER_SIZE];
#pragma DATA_SECTION(localRAMBuf, "ramgs0");

//
// Function Prototypes
//
extern void setupEMIF1PinmuxSync16Bit(void);
void clearDataBuffer(uint32_t memSize);
uint16_t readWriteSyncMemory(uint32_t memSize);

//
// Main
//
void main(void)
{
    uint16_t i;
    uint16_t errCountLocal;
    EMIF_SyncConfig sdConfig;
    EMIF_SyncTimingParams tParam;
    testStatusGlobal = TEST_FAIL;

    //
    // Initialize device clock and peripherals.
    //
    Device_init();

    //
    // Disable all the interrupts.
    //
    DINT;

    //
    // Setup GPIO by disabling pin locks and enabling pullups.
    //
    Device_initGPIO();

    //
    // This function initializes the PIE control registers. After globally
    // disabling interrupts and enabling the PIE, it clears all of the PIE
    // interrupt enable bits and interrupt flags.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table by setting all vectors to a default
    // handler function.
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM).
    //
    EINT;
    ERTM;

    //
    // Configure to run EMIF1 on half Rate. (EMIF1CLK = CPU1SYSCLK/2)
    //
    SysCtl_setEMIF1ClockDivider(SYSCTL_EMIF1CLK_DIV_2);

    //
    // Disable Access Protection. (CPU_FETCH/CPU_WR/DMA_WR)
    //
    EMIF_setAccessProtection(EMIF1CONFIG_BASE, 0x0);

    //
    // Commit the configuration related to protection. Till this bit remains
    // set content of EMIF1ACCPROT0 register can't be changed.
    //
    EMIF_commitAccessConfig(EMIF1CONFIG_BASE);

    //
    // Lock the configuration so that EMIF1COMMIT register can't be changed
    // any more.
    //
    EMIF_lockAccessConfig(EMIF1CONFIG_BASE);

    //
    // Configure GPIO pins for EMIF1.
    //
    setupEMIF1PinmuxSync16Bit();

    //
    // Configure SDRAM control registers. Needs to be
    // programmed based on SDRAM Data-Sheet. For this example:
    // T_RFC = 60ns = 0x6; T_RP  = 18ns = 0x1;
    // T_RCD = 18ns = 0x1; T_WR  = 1CLK + 6 ns = 0x1;
    // T_RAS = 42ns = 0x4; T_RC  = 60ns = 0x6;
    // T_RRD = 12ns = 0x1.
    //
    tParam.tRfc = 0x6U;
    tParam.tRp  = 0x1U;
    tParam.tRcd = 0x1U;
    tParam.tWr  = 0x1U;
    tParam.tRas = 0x4U;
    tParam.tRc  = 0x6U;
    tParam.tRrd = 0x1U;
    EMIF_setSyncTimingParams(EMIF1_BASE, &tParam);

    //
    // Configure Self Refresh exit timing.
    // Txsr = 70ns = 0x7.
    //
    EMIF_setSyncSelfRefreshExitTmng(EMIF1_BASE, 0x7U);

    //
    // Configure Refresh Rate.
    // Tref = 64ms for 8192 ROW, RR = 64000*100(Tfrq)/8192 = 781.25 (0x30E).
    //
    EMIF_setSyncRefreshRate(EMIF1_BASE, 781);

    //
    // Configure SDRAM parameters. PAGESIZE=2 (1024 elements per ROW),
    // IBANK = 2 (4 BANK), CL = 3, NM = 1 (16bit).
    //
    sdConfig.casLatency = EMIF_SYNC_CAS_LAT_3;
    sdConfig.iBank = EMIF_SYNC_BANK_4;
    sdConfig.narrowMode = EMIF_SYNC_NARROW_MODE_TRUE;
    sdConfig.pageSize = EMIF_SYNC_COLUMN_WIDTH_10;
    EMIF_setSyncMemoryConfig(EMIF1_BASE, &sdConfig);

    //
    // Adding some delay.
    //
    for(i = 0; i < 123; i++)
    {
    }

    //
    // Clear local and far memory buffers.
    //
    clearDataBuffer(MEM_BUFFER_SIZE);

    //
    // Basic read/write check.
    //
    errCountLocal  = readWriteSyncMemory(MEM_BUFFER_SIZE);
    errCountGlobal = errCountGlobal + errCountLocal;
    if(errCountGlobal == 0x0)
    {
        testStatusGlobal = TEST_PASS;
    }

    //
    // Checking total memory accesses.
    //
    uint32_t totAccess = EMIF_getSyncTotalAccesses(EMIF1_BASE);
    uint32_t totActAccess = EMIF_getSyncTotalActivateAccesses(EMIF1_BASE);
    while(1);
}

//
// Clear Data Buffer - This function clears the memory location of size memSize.
//
void clearDataBuffer(uint32_t memSize)
{
    uint32_t i;
    uint32_t memWdl = 0x0;

    //
    // Clear far memory buffer.
    //
    for(i=0; i < memSize; i++)
    {
        memcpy_fast_far((extSDRAMBuf + i), &memWdl, 2);
    }

    //
    // Clear local memory buffer.
    //
    for(i = 0; i < memSize; i++)
    {
        localRAMBuf[i] = memWdl;
    }
}

//
// Read Write Sync Memory - This function writes data into memory & verifies
// the written data.
//
uint16_t readWriteSyncMemory(uint32_t memSize)
{
    uint32_t memWdl;
    uint32_t i;

    //
    // Fill far memory buffer with data.
    //
    memWdl = 0x0;
    for(i=0; i < memSize; i++)
    {
        memcpy_fast_far((extSDRAMBuf + i), &memWdl, 2);
        memWdl += 0x00050001;
    }

    //
    // Read far memory buffer into local buffer and verify data.
    //
    memWdl = 0x0;
    for(i=0; i < memSize; i++)
    {
        memcpy_fast_far((localRAMBuf + i), (extSDRAMBuf + i), 2);

        //
        // Return error if read data is incorrect.
        //
        if(localRAMBuf[i] != memWdl)
        {
            return(1);
        }
        memWdl += 0x00050001;
    }
    return(0);
}

//
// End of File
//
