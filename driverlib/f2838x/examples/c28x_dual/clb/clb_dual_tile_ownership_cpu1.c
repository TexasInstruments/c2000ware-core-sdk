//#############################################################################
//
// FILE:   clb_dual_tile_ownership_cpu1.c
//
// TITLE:  CLB Dual-Core Tile Ownership — CPU1 (F2838x)
//
//! \addtogroup driver_dual_example_list
//! <h1>CLB Dual-Core Tile Ownership (CPU1)</h1>
//!
//! Demonstrates which CPU must configure and own each CLB tile on the
//! F2838x (TMS320F28388D).  The device contains eight CLB tiles (CLB1-CLB8).
//!
//! Tile ownership summary:
//!
//!   CPU1 owns CLB1, CLB2  — default ownership, no assignment call needed
//!   CPU2 owns CLB5, CLB6  — CPU1 assigns them before booting CPU2
//!
//!   CLB3, CLB4, CLB7, CLB8 remain on CPU1 by default and are not used
//!   in this example to keep it directly comparable to the F28P65x version.
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
//
#define CPU1_CLB1_MARKER    0xC1B10001UL
#define CPU1_CLB2_MARKER    0xC1B20002UL
//
// IPC flag for CPU1 <-> CPU2 synchronisation.
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
    CLB_setHLCRegisters(base, marker, 0U, 0U, 0U);
}
void main(void)
{
    Device_init();
    //=========================================================================
    // Step 1 — Allocate GS4 RAM for CPU2 (RAM build only).
    //
    // F2838x does NOT use SysCtl_allocateFlashBank() — CPU2 flash access is
    // controlled entirely by the linker command file (2838x_FLASH_lnk_cpu2.cmd
    // maps CPU2 code to the correct flash sectors automatically).
    //=========================================================================
    MemCfg_setGSRAMControllerSel(MEMCFG_SECT_GS4, MEMCFG_GSRAMCONTROLLER_CPU2);
    //=========================================================================
    // Step 2 — Assign CLB5 and CLB6 to CPU2.
    //
    // RULE: Only CPU1 can call SysCtl_selectCPUForPeripheralInstance().
    //       This MUST happen BEFORE Device_bootCPU2().
    //       After this call, CPU1 must NEVER access CLB5_BASE or CLB6_BASE.
    //
    // F2838x has 8 CLB tiles (CLB1-CLB8).  CLB1-CLB4, CLB7, CLB8 remain on
    // CPU1 by default.  No explicit assignment call is needed for them.
    //=========================================================================
    SysCtl_selectCPUForPeripheralInstance(SYSCTL_CPUSEL_CLB5,
                                          SYSCTL_CPUSEL_CPU2);
    SysCtl_selectCPUForPeripheralInstance(SYSCTL_CPUSEL_CLB6,
                                          SYSCTL_CPUSEL_CPU2);
    //=========================================================================
    // Step 3 — Boot CPU2.
    //
    // F2838x uses sector-based flash bootmodes (not bank-based like F28P65x).
    //=========================================================================
#ifdef _FLASH
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
#endif
    Interrupt_initModule();
    Interrupt_initVectorTable();
    //=========================================================================
    // Step 4 — Enable CLB peripheral clocks for CPU1-owned tiles only.
    //=========================================================================
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB2);
    //=========================================================================
    // Step 5 — Configure the CLB tiles owned by CPU1.
    //=========================================================================
    initCLBTile_CPU1(CLB1_BASE, CPU1_CLB1_MARKER, 10000U);
    initCLBTile_CPU1(CLB2_BASE, CPU1_CLB2_MARKER, 20000U);
    cpu1_clb1_r0 = CLB_getRegister(CLB1_BASE, CLB_REG_HLC_R0);
    cpu1_clb2_r0 = CLB_getRegister(CLB2_BASE, CLB_REG_HLC_R0);
    cpu1_clbInitDone = 1U;
    //=========================================================================
    // Step 6 — Synchronise with CPU2 via IPC.
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
    //=========================================================================
    while(1)
    {
        asm(" NOP");
    }
}
//
// End of File
//
