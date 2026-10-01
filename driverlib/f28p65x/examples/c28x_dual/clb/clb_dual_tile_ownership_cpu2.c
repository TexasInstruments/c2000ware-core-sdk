//#############################################################################
//
// FILE:   clb_dual_tile_ownership_cpu2.c
//
// TITLE:  CLB Dual-Core Tile Ownership — CPU2
//
//! \addtogroup driver_dual_example_list
//! <h1>CLB Dual-Core Tile Ownership (CPU2)</h1>
//!
//! This is the CPU2 side of the F28P65x dual-core CLB tile ownership example.
//! See clb_dual_tile_ownership_cpu1.c for the full description.
//!
//! CPU2 is responsible for:
//!   1. Waiting for CPU1 to complete the IPC sync (blocking call).
//!   2. Enabling the CLB peripheral clocks for its own tiles (CLB5, CLB6).
//!      CPU2 must NOT enable clocks for CLB1-CLB4 — those belong to CPU1.
//!   3. Configuring CLB5 and CLB6 entirely independently of CPU1.
//!
//! Ownership proof:
//!   CPU2 writes a unique 32-bit marker to HLC register R0 of CLB5 and CLB6
//!   via CLB_setHLCRegisters(), then reads it back with CLB_getRegister().
//!
//! Watch variables (Expressions / Watch window — CPU2 context):
//!   cpu2_clb5_r0     — expects 0xC2B50005 after CPU2 init
//!   cpu2_clb6_r0     — expects 0xC2B60006 after CPU2 init
//!   cpu2_clbInitDone — becomes 1 when CPU2 CLB configuration is complete
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
#define CPU2_CLB5_MARKER    0xC2B50005UL
#define CPU2_CLB6_MARKER    0xC2B60006UL
//
// Must match the flag used in the CPU1 application.
//
#define IPC_SYNC_FLAG   IPC_FLAG31
//
// Watch variables — inspect in the Expressions / Watch window.
//
volatile uint32_t cpu2_clb5_r0;      // Read-back of CLB5 HLC R0
volatile uint32_t cpu2_clb6_r0;      // Read-back of CLB6 HLC R0
volatile uint32_t cpu2_clbInitDone;  // 1 when CPU2 CLB config is complete
//
// initCLBTile_CPU2 — configure one CLB tile that CPU2 owns.
//
// Identical logic to CPU1's helper, shown here separately to make the
// per-CPU responsibility boundary clear: CPU2 configures its own tiles
// and CPU1 never touches them after the ownership transfer.
//
static void initCLBTile_CPU2(uint32_t base, uint32_t marker, uint32_t match1Val)
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
    //
    // CPU2 does NOT call Device_init() — CPU1 handles system-level init
    // and boots CPU2.  CPU2 begins execution here after CPU1 calls
    // Device_bootCPU2().
    //
    //=========================================================================
    // Step 1 — Synchronise with CPU1 via IPC.
    //
    // IPC_sync() blocks until CPU1 also calls IPC_sync() with the same flag.
    // At this point CPU1 has already:
    //   - Assigned CLB5 and CLB6 to CPU2
    //   - Booted CPU2
    // So it is safe for CPU2 to access CLB5 and CLB6 registers.
    //=========================================================================
    IPC_clearFlagLtoR(IPC_CPU2_L_CPU1_R, IPC_FLAG_ALL);
    IPC_sync(IPC_CPU2_L_CPU1_R, IPC_SYNC_FLAG);
    //=========================================================================
    // Step 2 — Enable CLB peripheral clocks for CPU2-owned tiles.
    //
    // CLB5 and CLB6 were assigned to CPU2 by CPU1 in Step 2 of the CPU1
    // application.  CPU2 may now enable their clocks and access all registers.
    // CPU2 must NOT enable clocks for CLB1-CLB4.
    //=========================================================================
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB6);
    //=========================================================================
    // Step 3 — Configure the CLB tiles owned by CPU2.
    //
    // CLB5: GP inputs, counter MATCH1 = 30 000, HLC R0 = CPU2_CLB5_MARKER
    // CLB6: GP inputs, counter MATCH1 = 40 000, HLC R0 = CPU2_CLB6_MARKER
    //=========================================================================
    initCLBTile_CPU2(CLB5_BASE, CPU2_CLB5_MARKER, 30000U);
    initCLBTile_CPU2(CLB6_BASE, CPU2_CLB6_MARKER, 40000U);
    // Read back the markers to confirm CPU2 owns and can access CLB5/CLB6.
    cpu2_clb5_r0 = CLB_getRegister(CLB5_BASE, CLB_REG_HLC_R0);
    cpu2_clb6_r0 = CLB_getRegister(CLB6_BASE, CLB_REG_HLC_R0);
    cpu2_clbInitDone = 1U;
    //=========================================================================
    // Idle loop.
    //
    // At this point:
    //   cpu2_clb5_r0 == CPU2_CLB5_MARKER (0xC2B50005)
    //   cpu2_clb6_r0 == CPU2_CLB6_MARKER (0xC2B60006)
    //   cpu2_clbInitDone == 1
    //=========================================================================
    EINT;
    ERTM;
    while(1)
    {
        asm(" NOP");
    }
}
//
// End of File
//
