//#############################################################################
//
// FILE:   clb_dual_tile_ownership_cpu1.c
//
// TITLE:  CLB Dual-Core Tile Ownership — CPU1
//
//! \addtogroup driver_dual_example_list
//! <h1>CLB Dual-Core Tile Ownership (CPU1)</h1>
//!
//! Demonstrates which CPU must configure and own each CLB tile on the
//! F28P65x (TMS320F28P650DK9).  The device contains six CLB tiles (CLB1-CLB6).
//!
//! Tile ownership summary:
//!
//!   CPU1 owns CLB1, CLB2  — default ownership, no assignment call needed
//!   CPU2 owns CLB5, CLB6  — CPU1 assigns them before booting CPU2
//!
//! Sequence enforced by hardware:
//!   1. Only CPU1 can call SysCtl_selectCPUForPeripheralInstance() to transfer
//!      a peripheral from CPU1 to CPU2.  CPU2 has no such capability.
//!   2. After the assignment, any CPU1 access to CLB5/CLB6 registers
//!      generates a bus fault.
//!   3. Each CPU enables the clock (SysCtl_enablePeripheral) only for the
//!      tiles it owns.
//!   4. In production, CLB tile logic is configured by the SysConfig CLB Tool,
//!      which generates initTILEx() functions in clb_config.c/.h.  This
//!      example uses direct driverlib calls for clarity without SysConfig.
//!
//! Ownership proof:
//!   CPU1 writes a unique 32-bit marker to HLC register R0 of CLB1 and CLB2
//!   via CLB_setHLCRegisters(), then reads it back with CLB_getRegister().
//!   CPU2 does the same for CLB5 and CLB6.
//!
//! Watch variables (Expressions / Watch window):
//!   cpu1_clb1_r0     — expects 0xC1B10001 after CPU1 init
//!   cpu1_clb2_r0     — expects 0xC1B20002 after CPU1 init
//!   cpu1_clbInitDone — becomes 1 when CPU1 CLB configuration is complete
//!   cpu2_clbInitDone — becomes 1 after IPC sync (CPU2 init is complete)
//!
//! Build configurations: RAM (debug) and FLASH
//
//#############################################################################
//
// 
// C2000Ware v26.02.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "driverlib.h"
#include "device.h"
//
// Unique marker values written to HLC R0 of each tile.
// Encoding: 0xCxBy000z where x=CPU, y=CLB number, z=tile index.
// These values let you immediately identify which CPU and tile
// wrote a given value when inspecting them in the Watch window.
//
#define CPU1_CLB1_MARKER    0xC1B10001UL
#define CPU1_CLB2_MARKER    0xC1B20002UL
//
// IPC flag for CPU1 <-> CPU2 synchronisation.
// Both cores call IPC_sync() with IPC_SYNC_FLAG; the call blocks until
// the partner core has also called IPC_sync(), guaranteeing that both
// CLB initialisations are complete before either core enters its idle loop.
//
#define IPC_SYNC_FLAG   IPC_FLAG31
//
// Watch variables — inspect in the Expressions / Watch window.
//
volatile uint32_t cpu1_clb1_r0;      // Read-back of CLB1 HLC R0
volatile uint32_t cpu1_clb2_r0;      // Read-back of CLB2 HLC R0
volatile uint32_t cpu1_clbInitDone;  // 1 when CPU1 CLB config is complete
volatile uint32_t cpu2_clbInitDone;  // 1 after IPC sync (CPU2 CLB done)
//
// initCLBTile_CPU1 — configure one CLB tile that CPU1 owns.
//
// Steps performed:
//   1. Enable the CLB tile (CLB_LOAD_EN_GLOBAL_EN bit).
//   2. Route all eight external inputs from the GP register (software-driven).
//      CLB_GP_IN_MUX_GP_REG means bit i of the GP register drives CLB_INi.
//   3. Drive all GP inputs low initially.
//   4. Preload counter 0 with load=0, MATCH1=match1Val, MATCH2=match1Val+1.
//      Without a connected event source the counter stays at 0; the MATCH
//      values are here to show the configuration API.
//   5. Write a unique marker to HLC register R0 via CLB_setHLCRegisters().
//      CLB_setHLCRegisters() calls CLB_writeInterface() to transfer the value
//      into CLB program memory; it is immediately readable via
//      CLB_getRegister(base, CLB_REG_HLC_R0).
//
static void initCLBTile_CPU1(uint32_t base, uint32_t marker, uint32_t match1Val)
{
    uint16_t i;
    CLB_enableCLB(base);
    for(i = 0U; i < 8U; i++)
    {
        CLB_configGPInputMux(base, (CLB_Inputs)i, CLB_GP_IN_MUX_GP_REG);
    }
    CLB_setGPREG(base, 0U);
    CLB_configCounterLoadMatch(base, CLB_CTR0, 0U, match1Val, match1Val + 1U);
    // Initialise HLC registers: R0 = marker, R1/R2/R3 = 0.
    // With no HLC program loaded R0 stays at this value, so CLB_getRegister()
    // returns the marker unchanged — proof that this CPU owns the tile.
    CLB_setHLCRegisters(base, marker, 0U, 0U, 0U);
}
void main(void)
{
    Device_init();
    //=========================================================================
    // Step 1 — Allocate shared resources for CPU2 (must precede bootCPU2).
    //
    // GS4 RAM  : CPU2 code and data in the RAM build.
    // Flash Bank3/4 : CPU2 code in the FLASH build.
    //=========================================================================
    MemCfg_setGSRAMControllerSel(MEMCFG_SECT_GS4, MEMCFG_GSRAMCONTROLLER_CPU2);
    SysCtl_allocateFlashBank(SYSCTL_FLASH_BANK3, SYSCTL_CPUSEL_CPU2);
    SysCtl_allocateFlashBank(SYSCTL_FLASH_BANK4, SYSCTL_CPUSEL_CPU2);
    //=========================================================================
    // Step 2 — Assign CLB5 and CLB6 to CPU2.
    //
    // RULE: Only CPU1 can call SysCtl_selectCPUForPeripheralInstance().
    //       This MUST happen BEFORE Device_bootCPU2().
    //       After this call, CPU1 must NEVER access CLB5_BASE or CLB6_BASE
    //       — any such access raises a bus fault.
    //
    // CLB1, CLB2, CLB3, CLB4 remain CPU1 property by default.
    // No explicit assignment call is needed to keep them on CPU1.
    //=========================================================================
    SysCtl_selectCPUForPeripheralInstance(SYSCTL_CPUSEL_CLB5,
                                          SYSCTL_CPUSEL_CPU2);
    SysCtl_selectCPUForPeripheralInstance(SYSCTL_CPUSEL_CLB6,
                                          SYSCTL_CPUSEL_CPU2);
    //=========================================================================
    // Step 3 — Boot CPU2.
    //=========================================================================
#ifdef _FLASH
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_BANK3_SECTOR0);
#else
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
#endif
    Interrupt_initModule();
    Interrupt_initVectorTable();
    //=========================================================================
    // Step 4 — Enable CLB peripheral clocks for CPU1-owned tiles only.
    //
    // CPU1 may enable clocks for CLB1-CLB4.
    // CPU2 is responsible for enabling the clock for CLB5 and CLB6 after
    // those tiles have been assigned and CPU2 has started.
    //=========================================================================
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB2);
    //=========================================================================
    // Step 5 — Configure the CLB tiles owned by CPU1.
    //
    // CLB1: GP inputs, counter MATCH1 = 10000, HLC R0 = CPU1_CLB1_MARKER
    // CLB2: GP inputs, counter MATCH1 = 20000, HLC R0 = CPU1_CLB2_MARKER
    //=========================================================================
    initCLBTile_CPU1(CLB1_BASE, CPU1_CLB1_MARKER, 10000U);
    initCLBTile_CPU1(CLB2_BASE, CPU1_CLB2_MARKER, 20000U);
    // Read back the markers to confirm CPU1 owns and can access CLB1/CLB2.
    // If either value differs from its MARKER constant, check ownership.
    cpu1_clb1_r0 = CLB_getRegister(CLB1_BASE, CLB_REG_HLC_R0);
    cpu1_clb2_r0 = CLB_getRegister(CLB2_BASE, CLB_REG_HLC_R0);
    cpu1_clbInitDone = 1U;
    //=========================================================================
    // Step 6 — Synchronise with CPU2 via IPC.
    //
    // IPC_sync() is a polling barrier: CPU1 sets IPC_SYNC_FLAG on the
    // CPU1->CPU2 channel, then spins until CPU2 sets the same flag on the
    // CPU2->CPU1 channel.  When IPC_sync() returns here, both cores have
    // reached this point — CPU2 CLB init is complete.
    //=========================================================================
    IPC_clearFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG_ALL);
    IPC_sync(IPC_CPU1_L_CPU2_R, IPC_SYNC_FLAG);
    cpu2_clbInitDone = 1U;
    EINT;
    ERTM;
    //=========================================================================
    // Idle loop.
    //
    // At this point:
    //   cpu1_clb1_r0 == CPU1_CLB1_MARKER (0xC1B10001)
    //   cpu1_clb2_r0 == CPU1_CLB2_MARKER (0xC1B20002)
    //   cpu1_clbInitDone == 1
    //   cpu2_clbInitDone == 1
    //
    // See cpu2_clb5_r0 and cpu2_clb6_r0 on CPU2 for that core's results.
    //=========================================================================
    while(1)
    {
        asm(" NOP");
    }
}
//
// End of File
//
