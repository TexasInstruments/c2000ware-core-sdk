//#############################################################################
//
// FILE:   emif_ex5_16bit_sdram_dma.c
//
// TITLE:  EMIF1 module accessing 32bit SDRAM using DMA.
//
//! \addtogroup driver_example_list
//! <h1> EMIF1 module accessing 32bit SDRAM using DMA. </h1>
//!
//! This example configures EMIF1 in 16bit SYNC(SDRAM) mode and uses CS0
//! as chip enable. It will first write to an array in the SDRAM and then
//! read it back, using the DMA for both operations.
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
//!  - External SDR-SDRAM (Micron MT48LC32M16A2 "P -75 C") daughter card.
//!
//! \b Watch \b Variables \n
//! - \b testStatusGlobal - Equivalent to \b TEST_PASS if test finished
//!                         correctly, else the value is set to \b TEST_FAIL
//! - \b errCountGlobal   - Error counter
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

//
// Considering 32-bit word. Total 0x800 memory locations read/written.
//
#define MEM_BUFFER_SIZE 0x400

//
// Globals
//
uint16_t errCountGlobal = 0;
uint32_t testStatusGlobal;
volatile uint32_t initData = 0;
volatile uint32_t *destDMA;
volatile uint32_t *srcDMA;

//
// Buffer in local memory.
//
uint32_t localSrcRAMBuf[MEM_BUFFER_SIZE];
uint32_t localDstRAMBuf[MEM_BUFFER_SIZE];

//
// Buffer in far memory.
//
__attribute__((far)) volatile uint32_t extSDRAMBuf[MEM_BUFFER_SIZE];
#pragma DATA_SECTION(localSrcRAMBuf, "ramgs0");
#pragma DATA_SECTION(localDstRAMBuf, "ramgs1");

//
// Function Prototypes
//
extern void setupEMIF1PinmuxSync16Bit(void);
void clearDestDataBuffer(uint32_t memSize);
void configDMAChannel1(void);
void configDMAChannel2(void);

//
// Main
//
void main(void)
{
    uint16_t i;
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
    // Configure to run EMIF1 on half Rate (EMIF1CLK = CPU1SYSCLK/2).
    //
    SysCtl_setEMIF1ClockDivider(SYSCTL_EMIF1CLK_DIV_2);

    //
    // Disable Access Protection (CPU_FETCH/CPU_WR/DMA_WR).
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
    // Initialize source buffer for DMA transfer.
    //
    initData = 0x12103456;
    for(i = 0; i < MEM_BUFFER_SIZE; i++)
    {
        initData = initData + 0x11111111;
        localSrcRAMBuf[i] = initData;
    }

    //
    // Initialize DMA.
    //
    DMA_initController();

    //
    // Configure channel 1 for writing into external memory & channel 2 for
    // reading from the external memory.
    //
    configDMAChannel1();
    configDMAChannel2();

    //
    // Start DMA channels 1 & 2.
    //
    DMA_startChannel(DMA_CH1_BASE);
    DMA_startChannel(DMA_CH2_BASE);

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
    // Clear destination data buffers.
    //
    clearDestDataBuffer(MEM_BUFFER_SIZE);

    //
    // Write to External Memory(16-bit).
    //
    DMA_forceTrigger(DMA_CH1_BASE);
    EALLOW;
    while((HWREGH(DMA_CH1_BASE + DMA_O_CONTROL) &
           DMA_CONTROL_TRANSFERSTS) != 0x0U);
    EDIS;

    //
    // Read from External Memory(32-bit).
    //
    DMA_forceTrigger(DMA_CH2_BASE);
    EALLOW;
    while((HWREGH(DMA_CH2_BASE + DMA_O_CONTROL) &
           DMA_CONTROL_TRANSFERSTS) != 0x0U);
    EDIS;

    //
    // Compare source & destination local buffer data.
    //
    for(i = 0; i < MEM_BUFFER_SIZE; i++)
    {
        if(localSrcRAMBuf[i] != localDstRAMBuf[i])
        {
            errCountGlobal++;
        }
    }

    if(errCountGlobal == 0x0)
    {
        testStatusGlobal = TEST_PASS;
    }
    while(1);
}

//
// Clear Dest Data Buffer - This function clears the destination memory
// location of size memSize.
//
void clearDestDataBuffer(uint32_t memSize)
{
    uint32_t i;
    uint32_t memWdl = 0x0;

    //
    // Clear far memory buffer.
    //
    for(i=0; i < memSize; i++)
    {
        __addr32_write_uint32((uint32_t)(extSDRAMBuf + (i*2)), 0x0);
    }

    //
    // Clear local memory buffer.
    //
    for(i = 0; i < memSize; i++)
    {
        localDstRAMBuf[i] = memWdl;
    }
}

//
// Configure DMA Channel 1 - This function configures the DMA channel 1 for
// writing to external SDRAM memory.
//
void configDMAChannel1()
{
    //
    // Configure DMA Channel 1 (16 - bit datasize).
    //
    destDMA = extSDRAMBuf;
    srcDMA = (volatile uint32_t *)localSrcRAMBuf;
    DMA_configAddresses(DMA_CH1_BASE,(const void*)destDMA,(const void*)srcDMA);
    DMA_configBurst(DMA_CH1_BASE, 32U, 1U, 1U);
    DMA_configTransfer(DMA_CH1_BASE, ((MEM_BUFFER_SIZE * 2) / 32), 1, 1);
    DMA_configWrap(DMA_CH1_BASE, 0x10000U, 0, 0x10000U, 0);

    //
    // Configure DMA trigger source as software, enable oneshot, disable
    // continuous mode, data size of DMA transfer to 16 bits.
    //
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_SOFTWARE, (DMA_CFG_ONESHOT_ENABLE
                   | DMA_CFG_CONTINUOUS_DISABLE | DMA_CFG_SIZE_16BIT));

    //
    // Enable selected peripheral trigger to start a DMA transfer on DMA
    // channel 1.
    //
    DMA_enableTrigger(DMA_CH1_BASE);

    //
    // Clear any spurious Peripheral interrupts flags.
    //
    DMA_clearTriggerFlag(DMA_CH1_BASE);

    //
    // Clear any spurious sync error flags.
    //
    DMA_clearErrorFlag(DMA_CH1_BASE);
}

//
// Configure DMA Channel 2-This function configures the DMA channel 2 for
// reading from external SDRAM memory.
//
void configDMAChannel2()
{
    //
    // Configure DMA channel 2.
    //
    destDMA = (volatile uint32_t *)localDstRAMBuf;
    srcDMA = extSDRAMBuf;
    DMA_configAddresses(DMA_CH2_BASE,(const void*)destDMA,(const void*)srcDMA);
    DMA_configBurst(DMA_CH2_BASE, 32U, 2U, 2U);
    DMA_configTransfer(DMA_CH2_BASE, ((MEM_BUFFER_SIZE * 2) / 32), 2, 2);
    DMA_configWrap(DMA_CH2_BASE, 0x10000U, 0, 0x10000U, 0);

    //
    // Configure DMA trigger source as software, enable oneshot, disable
    // continuous mode, data size of DMA transfer to 16 bits.
    //
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_SOFTWARE, (DMA_CFG_ONESHOT_ENABLE
                   | DMA_CFG_CONTINUOUS_DISABLE | DMA_CFG_SIZE_32BIT));

    //
    // Enable selected peripheral trigger to start a DMA transfer on DMA
    // channel 2.
    //
    DMA_enableTrigger(DMA_CH2_BASE);

    //
    // Clear any spurious Peripheral interrupts flags.
    //
    DMA_clearTriggerFlag(DMA_CH2_BASE);

    //
    // Clear any spurious sync error flags.
    //
    DMA_clearErrorFlag(DMA_CH2_BASE);
}

//
// End of File
//
