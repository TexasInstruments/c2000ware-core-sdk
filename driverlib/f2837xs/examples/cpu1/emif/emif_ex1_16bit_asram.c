//#############################################################################
//
// FILE:   emif_ex1_16bit_asram.c
//
// TITLE:  EMIF1 ASYNC module accessing 16bit ASRAM.
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 ASYNC module accessing 16bit ASRAM. </h1>
//!
//! This example configures EMIF1 in 16bit ASYNC mode and uses CS2 as chip
//! enable.
//!
//! \b External \b Connections \n
//!  - External ASRAM memory (CY7C1041CV33 -10ZSXA) daughter card
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
// Defines
//
#define TEST_PASS 0xABCDABCD
#define TEST_FAIL 0xDEADDEAD
#define ASRAM_CS2_START_ADDR 0x100000
#define ASRAM_CS2_SIZE 0x8000

//
// Globals
//
uint16_t errCountGlobal = 0;
uint32_t testStatusGlobal;
uint32_t i;

//
// Function Prototypes
//
extern void setupEMIF1PinmuxAsync16Bit(void);
uint16_t readWriteMem(uint32_t startAddr, uint32_t memSize);
uint16_t walkMemData(uint32_t startAddr, uint32_t memSize);
uint16_t walkMemAddr(uint32_t startAddr, uint32_t addrSize);
uint16_t accessMemData(uint32_t startAddr, uint32_t sizeToCheck);

//
// Main
//
void main(void)
{
    uint16_t errCountLocal;
    EMIF_AsyncTimingParams tparam;
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
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Configure to run EMIF1 on full Rate. (EMIF1CLK = CPU1SYSCLK)
    //
    SysCtl_setEMIF1ClockDivider(SYSCTL_EMIF1CLK_DIV_1);

    //
    // Disable Access Protection. (CPU_FETCH/CPU_WR/DMA_WR)
    //
    EMIF_setAccessProtection(EMIF1CONFIG_BASE, 0x0);

    //
    // Commit the configuration related to protection. Till this bit remains
    // set, contents of EMIF1ACCPROT0 register can't be changed.
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
    setupEMIF1PinmuxAsync16Bit();

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

    //
    // Checks basic RD/WR access to CS2 space.
    //
    errCountLocal = readWriteMem(ASRAM_CS2_START_ADDR, ASRAM_CS2_SIZE);
    errCountGlobal = errCountGlobal + errCountLocal;

    //
    // Address walk checks. (Tested for Memory with address width of 16bit)
    //
    errCountLocal = walkMemAddr(ASRAM_CS2_START_ADDR, 16);
    errCountGlobal = errCountGlobal + errCountLocal;

    //
    // Data walk checks.
    //
    errCountLocal = walkMemData(ASRAM_CS2_START_ADDR, ASRAM_CS2_SIZE);
    errCountGlobal = errCountGlobal + errCountLocal;

    //
    // Data size checks.
    //
    errCountLocal = accessMemData(ASRAM_CS2_START_ADDR, 4);
    errCountGlobal = errCountGlobal + errCountLocal;

    if(errCountGlobal == 0x0)
    {
        testStatusGlobal = TEST_PASS;
    }
    while(1);
}

//
// Read Write Memory - This function performs simple read/write word accesses
// to memory.
//
uint16_t readWriteMem(uint32_t startAddr, uint32_t memSize)
{
    uint32_t memReadData;
    uint32_t memWriteData;
    uint32_t *memPtr;
    uint32_t i;

    memPtr = (uint32_t *)startAddr;

    //
    // Write data to memory.
    //
    memWriteData = 0x01234567;
    for(i = 0; i < memSize; i++)
    {
        *memPtr++ = memWriteData;
        memWriteData += 0x11111111;
    }

    //
    // Verify data written to memory.
    //
    memWriteData = 0x01234567;
    memPtr = (uint32_t *)startAddr;
    for(i = 0; i < memSize; i++)
    {
        memReadData = *memPtr;
        if(memReadData != memWriteData)
        {
            return(1);
        }
        memPtr++;
        memWriteData += 0x11111111;
    }
    return(0);
}

//
// Walk Memory Data - This function performs a walking 0 & 1 on data lines
// for SRAM RD & WR.
//
uint16_t walkMemData(uint32_t startAddr, uint32_t memSize)
{
    uint32_t sramReadData;
    uint32_t sramWriteData;
    uint32_t i;
    uint32_t k;
    uint32_t m;
    uint32_t *memPtr;
    uint32_t *memPtrIter;

    memPtr = (uint32_t *)startAddr;

    for(i = 0; i < memSize; i = i + 64)
    {
        for(m = 0; m < 2; m++)
        {
            //
            // Write loop.
            //
            memPtrIter = memPtr;
            sramWriteData = 0x01;
            for(k = 0; k < 32; k++)
            {
                if(m == 0)
                {
                    *memPtrIter++ = sramWriteData;
                }
                else
                {
                    *memPtrIter++ = ~sramWriteData;
                }
                sramWriteData = sramWriteData << 1;
            }

            //
            // Read loop.
            //
            memPtrIter = memPtr;
            sramWriteData = 0x01;
            for(k = 0; k < 32; k++)
            {
                sramReadData = *memPtrIter;
                if(m == 1)
                {
                    sramReadData = ~sramReadData;
                }
                if(sramReadData != sramWriteData)
                {
                    return(1);
                }
                memPtrIter++;
                sramWriteData = sramWriteData << 1;
            }
        }
        memPtr = memPtrIter;
    }
    return(0);
}

//
// Walk Memory Addresses - This function performs a toggle on each address bit.
//
uint16_t walkMemAddr(uint32_t startAddr, uint32_t addrSize)
{
    uint32_t sramReadData;
    uint32_t sramWriteData;
    uint32_t k;
    uint32_t xshift;
    uint32_t *memPtr;
    uint32_t *memPtrIter;

    memPtr = (uint32_t *)startAddr;

    //
    // Write loop.
    //
    xshift = 0x00000001;
    sramWriteData = 0x00;
    for(k = 0; k < addrSize; k++)
    {
        memPtrIter = (uint32_t *)(startAddr + xshift);
        *memPtrIter = sramWriteData++;
        xshift = xshift << 1;
    }

    //
    // Read loop.
    //
    memPtrIter = memPtr;
    xshift = 0x00000001;
    sramWriteData = 0x00;
    for(k = 0; k < addrSize; k++)
    {
        memPtrIter = (uint32_t *)(startAddr + xshift);
        sramReadData = *memPtrIter;
        if(sramReadData != sramWriteData)
        {
            return(1);
        }
        xshift = xshift << 1;
        sramWriteData++;
    }
    return(0);
}

//
// Access Memory Data - This function performs different data type
// (HALFWORD/WORD) access.
//
uint16_t accessMemData(uint32_t startAddr, uint32_t sizeToCheck)
{
    uint16_t memRdShort;
    uint32_t memRdLong;
    uint16_t memWrShort;
    uint32_t memWrLong;
    uint32_t i;
    uint16_t *memPtrShort;
    uint32_t *memPtrLong;

    //
    // Write short data.
    //
    memPtrShort = (uint16_t *)startAddr;
    memWrShort = 0x0605;

    for(i = 0; i < 2; i++)
    {
        *memPtrShort++ = memWrShort;
        memWrShort += 0x0202;
    }

    //
    // Write long data.
    //
    memPtrLong = (uint32_t *)memPtrShort;
    memWrLong = 0x0C0B0A09;
    for(i = 0; i < 2; i++)
    {
        *memPtrLong++ = memWrLong;
        memWrLong += 0x04040404;
    }

    //
    // Read short data.
    //
    memPtrShort = (uint16_t *)startAddr;
    memWrShort = 0x0605;
    for(i = 0; i < 6; i++)
    {
        memRdShort = *memPtrShort;
        if(memRdShort != memWrShort)
        {
            return(1);
        }
        memPtrShort++;
        memWrShort += 0x0202;
    }

    //
    // Read long data.
    //
    memPtrLong = (uint32_t *)startAddr;
    memWrLong = 0x08070605;
    for(i = 0; i < 3; i++)
    {
        memRdLong = *memPtrLong;
        if(memRdLong != memWrLong)
        {
            return(1);
        }
        memPtrLong++;
        memWrLong += 0x04040404;
    }
    return(0);
}

//
// End of File
//
