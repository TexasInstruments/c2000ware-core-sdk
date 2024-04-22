//###########################################################################
//
// FILE:   cla_iir2p2z_cpu01.c
//
// TITLE:  CLA IIR2p2Z Example for F2837xD.
//
//! \addtogroup dual_example_list
//! <h1>CLA 2 Pole 2 Zero Infinite Impulse Response Filter (cla_iir2p2z_cpu01)</h1>
//!
//! This example implements a Transposed Direct Form II IIR filter, commonly
//! known as a Biquad. The input vector is a software simulated noisy signal
//! that is fed to the biquad one sample at a time, filtered and then stored
//! in an output buffer for storage.
//!
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1 (RAML2)
//!    - S1_A - Feedback coefficients
//!    - S1_B - Feedforward coefficients
//!  - CLA1 to CPU Message RAM
//!    - yn - Output of the Biquad
//!  - CPU to CLA1 Message RAM
//!    - xn - Sample input to the filter
//!
//! \b Watch \b Variables \n
//!  - fBiquadOutput
//!  - pass
//!  - fail
//!
//! \note CPU2 must turn on the CLA clock by writing a 1 to
//! CpuSysRegs.PCLKCR0.bit.CLA1.
//!
//
//###########################################################################
//
// $Release Date:  $
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
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"

//
// Globals
//
uint16_t pass=0;
uint16_t fail=0;

//
// Function Prototypes
//
void CLA_initCpuXCla1(void);

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();

#ifdef _STANDALONE
#ifdef _FLASH
//
// Send boot command to allow the CPU2 application to begin execution
//
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
//
// Send boot command to allow the CPU2 application to begin execution
//
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

//
// Step 2. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Step 3. Turn on the CLA clocks on both CPUs
//
    CLA_initCpuXCla1();

//
// Step 4. Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM
}

//
// CLA_initCpuXCla1 - Enable CLA1 on CPU1 and CPU2
//
void CLA_initCpuXCla1(void)
{
    EALLOW;
#ifdef CPU1
    //
    // Enable CPU1.CLA1
    //
    DevCfgRegs.DC1.bit.CPU1_CLA1 = 1;

    //
    // Enable CPU2.CLA1
    //
    DevCfgRegs.DC1.bit.CPU2_CLA1 = 1;
#endif //CPU1
    EDIS;

    //
    // Send flag 5 to CPU2
    //
    IpcSync(5);
}

//
// End of file
//
