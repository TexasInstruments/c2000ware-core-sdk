//###########################################################################
//
// FILE:   buffdac_ex3_sine.c
//
// TITLE:  Buffered DAC Sine Wave Output Example for F2838x.
//
//! \addtogroup driver_example_list
//! <h1> Buffered DAC Sine (buffdac_sine) </h1>
//!
//! This example generates a sine wave on the buffered DAC output,
//! DACOUTA/ADCINA0 (HSEC Pin 9) and uses the default DAC reference setting
//! of VDAC.
//!
//! When the DAC reference is set to VDAC, an external reference voltage
//! must be applied to the VDAC pin. This can accomplished by connecting a
//! jumper wire from 3.3V to ADCINB3.
//!
//! Run the included .js file to add the watch variables.
//! This example uses the SGEN module. Documentation for the SGEN module can be
//! found in the SGEN library directory.
//!
//! The generated waveform can be adjusted with the following variables while
//! running:
//! - \b waveformGain \b : Adjust the magnitude of the waveform.
//! Range is from 0.0 to 1.0. The default value of 0.8003 centers the waveform
//! within the linear range of the DAC
//! - \b waveformOffset \b : Adjust the offset of the waveform.
//!    Range is from -1.0 to 1.0. The default value of 0 centers the waveform
//! - \b outputFreq_hz \b : Adjust the output frequency of the waveform.
//! Range is from 0 to maxOutputFreq_hz
//! - \b maxOutputFreq_hz \b : Adjust the max output frequency of the waveform.
//! Range - See SGEN module documentation for how this affects other parameters
//!
//! The generated waveform can be adjusted with the following variables/macros
//! but require recompile:
//! - \b samplingFreq_hz \b : Adjust the rate at which the DAC is updated.
//! Range - See SGEN module documentation for how this affects other parameters
//! - \b SINEWAVE_TYPE \b : The type of sine generated.
//! Range - LOW_THD_SINE, HIGH_PRECISION_SINE
//!
//! The following variables give additional information about the generated
//! waveform:
//! See SGEN module documentation for details
//! - \b freqResolution_hz \b
//! - \b maxOutput_lsb \b : Maximum value written to the DAC.
//! - \b minOutput_lsb \b : Minimum value written to the DAC.
//! - \b pk_to_pk_lsb \b : Magnitude of generated waveform.
//! - \b cpuPeriod_us \b : Period of cpu.
//! - \b samplingPeriod_us \b : The rate at which the DAC is updated.
//! Note that samplingPeriod_us has to be greater than the DAC settling time.
//! - \b interruptCycles \b : Interrupt duration in cycles.
//! - \b interruptDuration_us \b : Interrupt duration in uS.
//! - \b sgen \b : The SGEN module instance.
//! - \b DataLog \b : Circular log of writes to the DAC.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
//
// Included Files
//
#include <time.h>
#include <stdlib.h>
#include "driverlib.h"
#include "device.h"
#include "sgen.h"
#include "board.h"

//
// Defines
//
#define DLOG_SIZE             1024
#define LOW_THD_SINE          0
#define HIGH_PRECISION_SINE   1
#define SINEWAVE_TYPE         LOW_THD_SINE

//
// Globals
//
uint16_t cpuTimer0IntCount;
uint16_t cpuTimer1IntCount;
uint16_t cpuTimer2IntCount;

//
// Globals
//
uint16_t DataLog[DLOG_SIZE];
#pragma DATA_SECTION(DataLog, "DLOG");
uint32_t samplingFreq_hz = 200000;
uint32_t outputFreq_hz = 1000;
uint32_t maxOutputFreq_hz = 5000;
float waveformGain = 0.8003F; // Range 0.0 -> 1.0
float waveformOffset = 0;    // Range -1.0 -> 1.0
uint16_t lowLimit = 410;
uint16_t highLimit = 3686;

#if SINEWAVE_TYPE==LOW_THD_SINE //initialize sine wave type
SGENTI_1 sgen = SGENTI_1_DEFAULTS;
#elif SINEWAVE_TYPE==HIGH_PRECISION_SINE
SGENHP_1 sgen = SGENHP_1_DEFAULTS;
#endif

uint16_t sgen_out = 0;
uint16_t ndx = 0;
float freqResolution_hz = 0;
float cpuPeriod_us = 0;
uint32_t interruptCycles = 0;
float interruptDuration_us = 0;
float samplingPeriod_us = 0;
uint16_t maxOutput_lsb = 0;
uint16_t minOutput_lsb = 0;
uint16_t pk_to_pk_lsb = 0;

//
// Function Prototypes
//
static inline void dlog(uint16_t value);
static inline void setFreq(void);
static inline void setGain(void);
static inline void setOffset(void);
static inline uint16_t getMax(void);
static inline uint16_t getMin(void);
void configureWaveform(void);
interrupt void cpu_timer0_isr(void);
void initCPUTimers(void);
void configCPUTimer(uint32_t, uint32_t);

//
// Main
//
void main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Map Cpu Timer0 interrupt function to the PIE vector table
    //
    Interrupt_register(INT_TIMER0, &cpu_timer0_isr);

    //
    // Initialize variables
    //
    cpuPeriod_us = (1000000.0F/DEVICE_SYSCLK_FREQ);
    samplingPeriod_us = (1000000.0F/samplingFreq_hz);

    //
    // Initialize datalog
    //
    for(ndx=0; ndx<DLOG_SIZE; ndx++)
    {
        DataLog[ndx] = 0;
    }
    ndx = 0;

    //
    // Board initialization
    // Configure DAC
    //
    Board_init();

    //
    // Configure Waveform
    //
    configureWaveform();

    //
    // Initialize Cpu Timers
    //
    initCPUTimers();

    //
    // Configure Cpu Timer0 to interrupt at specified sampling frequency
    //
    configCPUTimer(CPUTIMER0_BASE, samplingPeriod_us);

    //
    // Enable interrupt
    //
    Interrupt_enable(INT_TIMER0);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    //
    // Start Cpu Timer0
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        setFreq();   // Set Output Frequency and Max Output Frequency
        setGain();   // Set Magnitude of Waveform
        setOffset(); // Set Offset of Waveform
        maxOutput_lsb = getMax();
        minOutput_lsb = getMin();
        pk_to_pk_lsb = maxOutput_lsb - minOutput_lsb;
    }
}

//
// dlog - Circular DataLog. DataLog[0] contains the next index to
//        be overwritten
//
static inline void dlog(uint16_t value)
{
    DataLog[ndx] = value;
    if(++ndx == DLOG_SIZE)
    {
        ndx = 0;
    }
    DataLog[0] = ndx;
}

//
// setFreq - Set the SINE frequency in SGEN
//
static inline void setFreq(void)
{
#if SINEWAVE_TYPE==LOW_THD_SINE
    //
    // Range(Q0) = 0x0000 -> 0x7FFF, step_max(Q0) =
    // (Max_Freq_hz*0x10000)/Sampling_Freq_hz
    //
    sgen.step_max = (maxOutputFreq_hz*0x10000)/samplingFreq_hz;

    //
    // Range(Q15) = 0x0000 -> 0x7FFF, freq(Q15) =
    // (Required_Freq_hz/Max_Freq_hz)*0x8000
    //
    sgen.freq = ((float)outputFreq_hz/maxOutputFreq_hz)*0x8000;
#elif SINEWAVE_TYPE==HIGH_PRECISION_SINE
    //
    // Range(Q0) = 0x00000000 -> 0x7FFFFFFF, step_max(Q0) =
    // (Max_Freq_hz*0x100000000)/Sampling_Freq_hz
    //
    sgen.step_max = (maxOutputFreq_hz*0x100000000)/samplingFreq_hz;

    //
    // Range(Q31) = 0x00000000 -> 0x7FFFFFFF, freq(Q31) =
    // (Required_Freq_hz/Max_Freq_hz)*0x80000000
    //
    sgen.freq = ((float)outputFreq_hz/maxOutputFreq_hz)*0x80000000;
#endif

    freqResolution_hz = (float)maxOutputFreq_hz/sgen.step_max;
}

//
// setGain - Set the gain in SGEN
//
static inline void setGain(void)
{
    sgen.gain = waveformGain * 0x7FFF;   // Range(Q15) = 0x0000 -> 0x7FFF
}

//
// setOffset - Set the offset in SGEN
//
static inline void setOffset(void)
{
    sgen.offset = waveformOffset * 0x7FFF; // Range(Q15) = 0x8000 -> 0x7FFF
}

//
// getMax - Get the max value in the data log
//
static inline uint16_t getMax(void)
{
    uint16_t index = 0;
    uint16_t tempMax = 0;

    for(index=1; index<DLOG_SIZE; index++)
    {
        if(tempMax<DataLog[index])
        {
            tempMax = DataLog[index];
        }
    }

    return tempMax;
}

//
// getMin - Get the min value in the data log
//
static inline uint16_t getMin(void)
{
    uint16_t index = 0;
    uint16_t tempMin = 0xFFFF;

    for(index=1; index<DLOG_SIZE; index++)
    {
        if(tempMin>DataLog[index])
        {
            tempMin = DataLog[index];
        }
    }

    return tempMin;
}

//
// configureWaveform - Configure the SINE waveform
//
void configureWaveform(void)
{
    sgen.alpha = 0; // Range(16) = 0x0000 -> 0xFFFF
    setFreq();
    setGain();
    setOffset();
}

//
// cpu_timer0_isr - Timer ISR that writes the sine value to DAC, log the sine
//                  value, compute the next sine value, and calculate interrupt
//                  duration
//
interrupt void cpu_timer0_isr(void)
{
    //
    // Start Cpu Timer1 to indicate begin of interrupt
    //
    CPUTimer_startTimer(CPUTIMER1_BASE);

    //
    // Write current sine value to buffered DAC
    //
    DAC_setShadowValue(myDAC0_BASE, sgen_out);

    //
    // Log current sine value
    //
    dlog(sgen_out);

    //
    // Compute next sine value
    //
    sgen.calc(&sgen);

    //
    // Scale next sine value
    //
    sgen_out = (sgen.out + 32768) >> 4;

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    //
    // Stop Cpu Timer1 to indicate end of interrupt
    //
    CPUTimer_stopTimer(CPUTIMER1_BASE);

    //
    // Calculate interrupt duration in cycles
    //
    interruptCycles = 0xFFFFFFFFUL - CPUTimer_getTimerCount(CPUTIMER1_BASE);

    //
    // Calculate interrupt duration in micro seconds
    //
    interruptDuration_us = cpuPeriod_us * interruptCycles;

    //
    // Reload Cpu Timer1
    //
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);

}


//
// initCPUTimers - This function initializes all three CPU timers
// to a known state.
//
void
initCPUTimers(void)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_stopTimer(CPUTIMER2_BASE);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);

    //
    // Reset interrupt counter
    //
    cpuTimer0IntCount = 0;
    cpuTimer1IntCount = 0;
    cpuTimer2IntCount = 0;
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" variables. The "freq" is
// CPU frequency in Hz and the period in uSeconds. The timer is held in
// the stopped state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, uint32_t period)
{
    uint32_t temp, freq = DEVICE_SYSCLK_FREQ;

    //
    // Initialize timer period:
    //
    temp = ((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    //
    // Resets interrupt counters for the three cpuTimers
    //
    if (cpuTimer == CPUTIMER0_BASE)
    {
        cpuTimer0IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER1_BASE)
    {
        cpuTimer1IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER2_BASE)
    {
        cpuTimer2IntCount = 0;
    }
}
//
// End of File
//
