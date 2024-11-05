//###########################################################################
//
// FILE:   buffdac_ex2_sine_dma.c
//
// TITLE:  Buffered DAC Sine Wave Output Using DMA Example
//
//! \addtogroup cpu01_example_list
//! <h1> Buffered DAC Sine DMA (buffdac_sine_dma) </h1>
//!
//! This example generates a sine wave on the buffered DAC output using the DMA
//! to transfer sine values stored in a sine table in GSRAM to DACVALS,
//! DACOUTA/ADCINA0 (HSEC Pin 9) and uses the default DAC reference setting
//! of VREF.
//!
//!
//! Run the included .js file to add the watch variables.
//!
//! outputFreq_hz = (samplingFreq_hz/SINE_TBL_SIZE)*tableStep
//!
//! The generated waveform can be adjusted with the following variables/macros
//! but require recompile:
//! - \b waveformGain \b : Adjust the magnitude of the waveform.
//! Range is from 0.0 to 1.0. The default value of 0.8003 centers the waveform
//! within the linear range of the DAC.
//! - \b waveformOffset \b : Adjust the offset of the waveform.
//! Range is from -1.0 to 1.0. The default value of 0 centers the waveform.
//! - \b samplingFreq_hz \b : Adjust the rate at which the DAC is updated.
//! Range - Bounded by cpu timer maximum interrupt rate.
//! - \b tableStep \b : The sine table step size.
//! Range - Bounded by sine table size, should be much less than sine table size
//! to have good resolution.
//! - \b REFERENCE \b : The reference for the DAC.
//! Range - REFERENCE_VDAC, REFERENCE_VREF
//! - \b CPUFREQ_MHZ \b : The cpu frequency. This does not set the cpu frequency.
//! Range - See device data manual
//! - \b DAC_NUM \b : The DAC to use.
//! Range - DACA, DACC
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
#include "math.h"

//
// Defines
//
#define REFERENCE             REFERENCE_VREF

#define CPUFREQ_MHZ           200
#define DAC_NUM               DACA
#define PI                    3.14159265
#define SINE_TBL_SIZE         360

//
// Globals
//
Uint16 SINE_TBL[SINE_TBL_SIZE];
#pragma DATA_SECTION(SINE_TBL, "ramgs0");
volatile struct DAC_REGS* DAC_PTR[4] = {0x0,&DacaRegs};
Uint32 samplingFreq_hz = 360000;
Uint16 tableStep = 1;
float waveformGain = 0.8003F; // Range 0.0 -> 1.0
float waveformOffset = 0;    // Range -1.0 -> 1.0

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

//
// Function Prototypes
//
void configureDAC(Uint16 dac_num);
void configureDMA(Uint16 dac_num);
void configureWaveform(void);

//
// Main
//
void main(void)
{
//
// Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
//
    InitSysCtrl();

//
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags are cleared.
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

//
// Configure Waveform
//
    configureWaveform();

//
// Initialize Cpu Timers
//
    InitCpuTimers();

//
// Configure Cpu Timer0 to interrupt at specified sampling frequency
//
    ConfigCpuTimer(&CpuTimer0, CPUFREQ_MHZ, 1000000.0F/samplingFreq_hz);

//
// Configure DMA
//
    configureDMA(DAC_NUM);

//
// Start Cpu Timer0
//
    CpuTimer0Regs.TCR.all = 0x4000;

    while(1);
}

//
// configureDAC - Enable and configure the requested DAC module
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
// configureDMA - Configures the DMA to read from the SINE table and write to the DAC
//
void configureDMA(Uint16 dac_num)
{
    //
    // Initialize DMA
    //
    DMAInitialize();

    DMASource = (volatile Uint16 *)&SINE_TBL[0];
    DMADest = (volatile Uint16 *)&DAC_PTR[dac_num]->DACVALS;

    //
    // Configure DMA CH1
    //
    DMACH1AddrConfig(DMADest,DMASource);
    DMACH1BurstConfig(0,0,0);
    DMACH1TransferConfig(SINE_TBL_SIZE/tableStep-1,tableStep,0);
    DMACH1WrapConfig(SINE_TBL_SIZE/tableStep-1,0,0,0);
    DMACH1ModeConfig(0,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_DISABLE);

    EALLOW;
    DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH1 = DMA_TINT0;    // Timer0 is DMA trigger
    EDIS;

    StartDMACH1(); // Start DMA channel
}

//
// configureWaveform - Configure the SINE waveform
//
void configureWaveform(void)
{
    Uint16 j;
    float offset;
    float waveformValue;

    //
    // Fill Sine Table
    //
    for(j=0;j<SINE_TBL_SIZE;j++) 
    {
        SINE_TBL[j] = (sin(j*PI/180.0F)+1.0F)*2047.5F;
    }

    //
    // Adjust for Gain and Offset
    //
    offset = (SINE_TBL[0] - (SINE_TBL[0]*waveformGain)) + (SINE_TBL[0]*waveformOffset);

    for(j=0;j<SINE_TBL_SIZE;j++) 
    {
        waveformValue = (SINE_TBL[j]*waveformGain)+offset;
        SINE_TBL[j] = waveformValue < 0 ? 0 : waveformValue > 4095 ? 4095 : waveformValue;
    }
}

//
// End of file
//
