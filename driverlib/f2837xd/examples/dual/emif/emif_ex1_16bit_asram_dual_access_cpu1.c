//#############################################################################
//
// FILE:   emif_ex1_16bit_asram_dual_access_cpu1.c
//
// TITLE:  EMIF1 ASYNC module accessing 16bit ASRAM through CPU1 and CPU2.
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 ASYNC module accessing 16bit ASRAM through CPU1 and CPU2. </h1>
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
//! - \b testStatusGlobalCPU1 - Equivalent to \b TEST_PASS if test finished
//!                         correctly, else the value is set to \b TEST_FAIL
//! - \b errCountGlobalCPU1 - Error counter
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
// size used for this example is 256K x 16. CPU1 accesses upper 128K x 16
// memory range.
//
#define ASRAM_CS2_START_ADDR_CPU1 0x120000U
#define ASRAM_CS2_SIZE 0x20000U

//
// Define for memory R/W iterations
//
#define MEM_RW_ITER    0x2U

//
// Globals
//
uint16_t errCountGlobalCPU1 = 0U;
uint32_t testStatusGlobalCPU1;
uint32_t i, iter;

//
// Function Prototypes
//
void setupEMIF1Pinmux256KAsync16Bit(void);
uint16_t readWriteMemCPU1(uint32_t startAddr, uint32_t memSize);

//
// Main
//
void main(void)
{
    uint16_t errCountLocal;
    uint16_t ipcFlag11 = 11U;
    testStatusGlobalCPU1 = TEST_FAIL;

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
    // Configure EMIF1 Pins.
    //
    setupEMIF1Pinmux256KAsync16Bit();

    //
    // Wait until CPU2 is ready and IPC flag 11 is set.
    //
    while(!(HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag11)))
    {
    }

    for(iter = 0; iter < MEM_RW_ITER; iter++)
    {
        //
        // Grab EMIF1 for CPU1.
        //
        while(HWREGH(EMIF1CONFIG_BASE + MEMCFG_O_EMIF1MSEL) !=
                                                           EMIF_MASTER_CPU1_G)
        {
            EMIF_selectMaster(EMIF1CONFIG_BASE, EMIF_MASTER_CPU1_G);
        }

        //
        // Check basic RD/WR access to CS2 space.
        //
        errCountLocal = readWriteMemCPU1(ASRAM_CS2_START_ADDR_CPU1,
                                         ASRAM_CS2_SIZE);
        errCountGlobalCPU1 = errCountGlobalCPU1 + errCountLocal;

        //
        // Release EMI1.
        //
        EMIF_selectMaster(EMIF1CONFIG_BASE, EMIF_MASTER_CPU1_NG);
    }

    if(errCountGlobalCPU1 == 0x0U)
    {
        testStatusGlobalCPU1 = TEST_PASS;
    }
    else
    {
        testStatusGlobalCPU1 = TEST_FAIL;
    }

    while(1);
}

//
// Setup EMIF1 Pinmux 256K Async 16Bit - This function configures pins
// for 16-bit 256x16 size Asynchronous EMIF1.
//
void setupEMIF1Pinmux256KAsync16Bit(void)
{
    uint16_t i;

    //
    // Selecting control pins.
    //
    GPIO_setPinConfig(GPIO_34_EM1CS2N);
    GPIO_setPinConfig(GPIO_31_EM1WEN);
    GPIO_setPinConfig(GPIO_37_EM1OEN);
    GPIO_setPinConfig(GPIO_36_EM1WAIT);
    GPIO_setPinConfig(GPIO_33_EM1RNW);

    //
    // Selecting 18 address lines.
    //
    GPIO_setPinConfig(GPIO_92_EM1BA1);
    GPIO_setPinConfig(GPIO_38_EM1A0);
    GPIO_setPinConfig(GPIO_39_EM1A1);
    GPIO_setPinConfig(GPIO_40_EM1A2);
    GPIO_setPinConfig(GPIO_41_EM1A3);
    GPIO_setPinConfig(GPIO_44_EM1A4);
    GPIO_setPinConfig(GPIO_45_EM1A5);
    GPIO_setPinConfig(GPIO_46_EM1A6);
    GPIO_setPinConfig(GPIO_47_EM1A7);
    GPIO_setPinConfig(GPIO_48_EM1A8);
    GPIO_setPinConfig(GPIO_49_EM1A9);
    GPIO_setPinConfig(GPIO_50_EM1A10);
    GPIO_setPinConfig(GPIO_51_EM1A11);
    GPIO_setPinConfig(GPIO_52_EM1A12);
    GPIO_setPinConfig(GPIO_86_EM1A13);
    GPIO_setPinConfig(GPIO_87_EM1A14);
    GPIO_setPinConfig(GPIO_88_EM1A15);
    GPIO_setPinConfig(GPIO_89_EM1A16);

    //
    // Selecting 16 data lines.
    //
    GPIO_setPinConfig(GPIO_69_EM1D15);
    GPIO_setPinConfig(GPIO_70_EM1D14);
    GPIO_setPinConfig(GPIO_71_EM1D13);
    GPIO_setPinConfig(GPIO_72_EM1D12);
    GPIO_setPinConfig(GPIO_73_EM1D11);
    GPIO_setPinConfig(GPIO_74_EM1D10);
    GPIO_setPinConfig(GPIO_75_EM1D9);
    GPIO_setPinConfig(GPIO_76_EM1D8);
    GPIO_setPinConfig(GPIO_77_EM1D7);
    GPIO_setPinConfig(GPIO_78_EM1D6);
    GPIO_setPinConfig(GPIO_79_EM1D5);
    GPIO_setPinConfig(GPIO_80_EM1D4);
    GPIO_setPinConfig(GPIO_81_EM1D3);
    GPIO_setPinConfig(GPIO_82_EM1D2);
    GPIO_setPinConfig(GPIO_83_EM1D1);
    GPIO_setPinConfig(GPIO_85_EM1D0);

    //
    // Setup async mode and enable pull-ups for Data pins.
    //
    for(i=69; i<=85;i++)
    {
        if(i != 84)
        {
            GPIO_setPadConfig(i, GPIO_PIN_TYPE_PULLUP);
            GPIO_setQualificationMode(i, GPIO_QUAL_ASYNC);
        }
    }
 }

//
// Read Write Memory - This function performs simple read/write word accesses
// to memory.
//
uint16_t readWriteMemCPU1(uint32_t startAddr, uint32_t memSize)
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
    memWriteData = 0x0101U;
    for(i = 0U; i < memSize; i++)
    {
        *memPtr++ = memWriteData;
        memWriteData += (0x0001U + iterCnt);
    }

    //
    // Verify data written to memory.
    //
    memWriteData = 0x0101U;
    memPtr = (uint16_t *)startAddr;
    for(i = 0U; i < memSize; i++)
    {
        memReadData = *memPtr;
        if(memReadData != memWriteData)
        {
            return(1U);
        }
        memPtr++;
        memWriteData += (0x0001U + iterCnt);
    }
    return(0U);
}

//
// End of File
//
