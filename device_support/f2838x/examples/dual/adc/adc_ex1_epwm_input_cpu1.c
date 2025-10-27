//###########################################################################
//
// FILE:   adc_ex1_epwm_input_cpu1.c
//
// TITLE:  Example to demonstrate ADCA and EPWM1 on CPU2
//
//! \addtogroup dual_example_list
//! <h1> ADC & EPWM on CPU2 </h1>
//!
//! This example demonstrates how to make use of the ADC and EPWM peripherals
//! from CPU2.  Device clocking (PLL) and GPIO setup are done using CPU1,
//! while all other configuration of the peripherals is done using CPU2.
//!
//! CPU2 configures EPWM1 in up count mode in a similar fashion to what is
//! done in the epwm_up_aq example.  The ADC is configured in continuous
//! conversion mode similar to the adc_soc_continuous example.  GPIO0 can be
//! connected to ADCINA0 and the results buffer AdcaResults graphed in CCS to
//! view the duty cycle of the generated waveform.
//!
//
//###########################################################################
// 
// C2000Ware v6.00.01.00
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
//###########################################################################

//
// Included Files
//
#include "f28x_project.h"

//
// Main
//
void main(void)
{
    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2838x_sysctrl.c file.
    //
    InitSysCtrl();

    //
    // Initialize GPIO:
    // This example function is found in the f2838x_gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    InitGpio();

    //
    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2838x_piectrl.c file.
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
    // The shell ISR routines are found in f2838x_defaultisr.c.
    // This function is found in f2838x_pievect.c.
    //
    InitPieVectTable();

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // For this case just init GPIO pins for ePWM1
    // Only CPU1 can configure GPIO muxing so this is done here
    // These functions are in the f2838x_epwm.c file
    //
    InitEPwm1Gpio();

    //
    // Transfer ownership of EPWM1 and ADCA to CPU02
    //
    EALLOW;
    DevCfgRegs.CPUSEL0.bit.EPWM1 = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_A = 1;
    EDIS;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    while(1)
    {
        asm(" nop");
    }
}

//
// End of file
//
