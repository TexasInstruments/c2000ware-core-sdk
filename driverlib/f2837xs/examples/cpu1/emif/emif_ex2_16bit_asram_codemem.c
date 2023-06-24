//#############################################################################
//
// FILE:   emif_ex2_16bit_asram_codemem.c
//
// TITLE:  EMIF1 module accessing 16bit ASRAM as code memory.
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 module accessing 16bit ASRAM as code memory. </h1>
//!
//! This example configures EMIF1 in 16bit ASYNC mode and uses CS2 as chip
//! enable. This example enables use of ASRAM as code memory.
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
// This tells the compiler to put methods in code section which influences
// the location in memory where linker will put it.
//
#pragma CODE_SECTION(add,"xintffuncs");
#pragma CODE_SECTION(multiply,"xintffuncs");

//
// Globals
//
extern uint16_t XintffuncsLoadStart;
extern uint16_t XintffuncsLoadEnd;
extern uint16_t XintffuncsRunStart;
uint16_t errCountGlobal = 0;
uint32_t testStatusGlobal;
uint32_t i;

//
// Function Prototypes
//
extern void setupEMIF1PinmuxAsync16Bit(void);
uint16_t add(uint16_t, uint16_t);
uint16_t multiply(uint16_t, uint16_t);
void memCopy(uint16_t *sourceAddr, uint16_t *sourceEndAddr, uint16_t *destAddr);
uint16_t readWriteMem(uint32_t startAddr, uint32_t memSize);

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
    // Configure Normal Asynchronous Mode of Operation.
    //
    EMIF_setAsyncMode(EMIF1_BASE, EMIF_ASYNC_CS2_OFFSET,
                      EMIF_ASYNC_NORMAL_MODE);

    //
    // Disable Extended Wait Mode.
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

    if(errCountGlobal == 0x0)
    {
        testStatusGlobal = TEST_PASS;

        //
        // Copies methods from load address to run address.
        //
        memCopy(&XintffuncsLoadStart, &XintffuncsLoadEnd, &XintffuncsRunStart);

        //
        // These methods are executed from ASRAM. Refer method addresses to
        // confirm. The addresses should lie in ASRAM address range.
        //
        uint16_t sum = add(5, 7);
        uint16_t mult = multiply(8, 5);
    }
    while(1);
}

//
// Add - This function is for reference only. It will be copied to ASRAM
// and is executed from ASRAM.
//
uint16_t add(uint16_t a, uint16_t b)
{
    return(a+b);
}

//
// Multiply - This function is for reference only. It will be copied to ASRAM
// and is executed from ASRAM.
//
uint16_t multiply(uint16_t a, uint16_t b)
{
    return(a*b);
}

//
// Memory Copy - This function copies source memory data to destination memory.
//
void memCopy(uint16_t *sourceAddr, uint16_t *sourceEndAddr, uint16_t *destAddr)
{
    while(sourceAddr < sourceEndAddr)
    {
       *destAddr++ = *sourceAddr++;
    }
    return;
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
// End of File
//
