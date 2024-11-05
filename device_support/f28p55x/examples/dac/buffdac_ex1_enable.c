//###########################################################################
//
// FILE:   buffdac_ex1_enable.c
//
// TITLE:  Buffered DAC Enable Output Example.
//
//! \addtogroup cpu01_example_list
//! <h1> Buffered DAC Enable (buffdac_enable) </h1>
//!
//! This example generates a voltage on the buffered DAC output,
//! DACOUTA/ADCINA0 (HSEC Pin 9) and uses the default DAC reference setting
//! of VREF.

//!
//!
//
//###########################################################################
//
//
// 
// C2000Ware v5.04.00.00
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
// Globals
//
volatile struct DAC_REGS* DAC_PTR[4] = {0x0,&DacaRegs};

Uint16 dacval = 2048;

//
// Defines
//
#define REFERENCE            REFERENCE_VREF

#define DAC_NUM                DACA

//
// Function Prototypes
//
void configureDAC(Uint16 dac_num);

void main(void)
{
//
// Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the f28p65x_sysctrl.c file.
//
    InitSysCtrl();

//
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags are cleared.
// This function is found in the f28p65x_pievect.c file.
//
    InitPieCtrl();

//
// Clear all interrupts and initialize PIE vector table:
//
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);

//
// Configure DAC
//
    configureDAC(DAC_NUM);

    while(1)
    {
        DAC_PTR[DAC_NUM]->DACVALS.all = dacval;
        DELAY_US(2);
    }
}

//
// configureDAC - Configure specified DAC output
//
void configureDAC(Uint16 dac_num)
{
    EALLOW;
    DAC_PTR[dac_num]->DACCTL.bit.DACREFSEL = REFERENCE;
    DAC_PTR[dac_num]->DACCTL.bit.MODE = 2;
    DAC_PTR[dac_num]->DACOUTEN.bit.DACOUTEN = 1;
    DAC_PTR[dac_num]->DACVALS.all = 0;
    DELAY_US(10); // Delay for buffered DAC to power up
    EDIS;
}

//
// End of file
//
