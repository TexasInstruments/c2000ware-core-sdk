//#############################################################################
//
// FILE:   drv8329_readback_registers.c
//
// TITLE:  DRV8329 Register Readback
//
//! \addtogroup driver_example_list
//! <h1>DRV8329 Register Readback</h1>
//!
//! This example demonstrates DRV8329_readbackRegisters(), which reads the
//! STATUS, CTRL1, and CTRL2 registers into a DRV8329_REGS_T structure with
//! named bitfields. This allows individual register fields to be inspected
//! directly in the CCS debugger without manually decoding raw SPI values.
//!
//! The example configures the DRV8329 with a specific VDS threshold and OTS
//! auto-recovery setting, then continuously reads back the registers so the
//! watch variable always reflects the live device state.
//!
//! \b Note: DRV8329_readbackRegisters() is only available in DEBUG builds.
//! Ensure the project is built with the DEBUG symbol defined.
//!
//! \b External \b Connections \n
//!  - Connect SCLK, NSCS, SDI, SDO pins to the DRV8329
//!
//! \b Watch \b Variables \n
//!  - \b drvRegs.status - STATUS register: fault flags and power-on status
//!  - \b drvRegs.ctrl1  - CTRL1 register: VDS level and fault enable config
//!  - \b drvRegs.ctrl2  - CTRL2 register: driver enable, TCP, OTS recovery
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2026 Texas Instruments Incorporated - http://www.ti.com/
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
#include "board.h"
#ifdef DEBUG
//
// Global - DRV8329 register readback structure.
// Add to the CCS Expressions window to inspect individual bitfields:
//   drvRegs.status.b.fault        - any active fault
//   drvRegs.status.b.pwr_on       - power-on indicator
//   drvRegs.ctrl1.b.sel_vdslvl    - active VDS threshold selection
//   drvRegs.ctrl1.b.sel_vds_spi   - SPI VDS level select enabled
//   drvRegs.ctrl2.b.dis_drv       - gate driver outputs disabled
//   drvRegs.ctrl2.b.ots_auto_recover - OTS auto-recovery enabled
//
DRV8329_REGS_T drvRegs;
#endif // DEBUG
//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();
    //
    // Disable pin locks and enable internal pull-ups
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
    // PinMux and Peripheral Initialization.
    // Configures the SPI interface and initializes the DRV8329.
    //
    Board_init();
    //
    // Clear any latched faults and reset fault status to defaults
    //
    DRV8329_resetFaultStatus();
    //
    // Enable gate driver outputs (GHx and GLx)
    //
    DRV8329_enableDrv();
    //
    // Allow VDS overcurrent threshold to be set via SPI, then configure
    // the threshold to 0.48V
    //
    DRV8329_enableVdsLevelSelectionThroughSpi();
    DRV8329_setVdsLevel(DRV8329_VDSLVL_0_48V);
    //
    // Configure OTS auto-recovery so the driver re-enables automatically
    // after an overtemperature condition clears
    //
    DRV8329_setOtsRecoveryMode(DRV8329_OTS_AUTO_RECOVER);
#ifdef DEBUG
    //
    // Read back STATUS, CTRL1, and CTRL2 registers into drvRegs.
    // Set a breakpoint on the next line and inspect drvRegs in the
    // CCS Expressions window to verify the configuration above.
    //
    DRV8329_readbackRegisters(&drvRegs);
#endif // DEBUG
    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;
    while(1)
    {
#ifdef DEBUG
        //
        // Continuously refresh the register readback so drvRegs always
        // reflects the live DRV8329 state during a debug session
        //
        DRV8329_readbackRegisters(&drvRegs);
        DEVICE_DELAY_US(1000);
#endif // DEBUG
    }
}
