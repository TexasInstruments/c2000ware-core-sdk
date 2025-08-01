//###########################################################################
//
// FILE:   adc_ex6_soc_continuous_dma.c
//
// TITLE:  ADC continuous conversions read by DMA.
//
//! \addtogroup driver_example_list
//! <h1> ADC Continuous Conversions Read by DMA (adc_soc_continuous_dma)</h1>
//!
//! This example sets up ADC channel to conversion. The results will be
//! transferred by the DMA into a buffer in RAM.
//!
//! \b External \b Connections \n
//!  - A3 pins should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//! - \b myADC0DataBuffer \b: a digital representation of the voltage on pin A3
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Function Prototypes
//
__interrupt void dmach1ISR(void);

void configureMCPWM(uint32_t mcpwmBase);
void initializeDMA(void);
void configureDMAChannels(void);

//
// Defines
//
#define RESULTS_BUFFER_SIZE     512 //buffer for storing conversion results
                                //(size must be multiple of 16)

//
// Globals
//
#pragma DATA_SECTION(myADC0DataBuffer, "ramgs0");
uint16_t myADC0DataBuffer[RESULTS_BUFFER_SIZE];
volatile uint16_t done;

void main(void)
{
    uint16_t resultsIndex;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
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
    // Board Initializatrion
    // - Configure the ADCA and power it up
    // - Setup the ADC for continuous conversions on A3 channel
    // - Set up ISR for ADCA INT1 - occurs after first conversion
    // - Enable specific PIE & CPU interrupts: ADCA INT1 - Group 1, interrupt 1
    // 
    Board_init();

    //
    // Set up ISRs used by this example
    // ISR for DMA ch1 - occurs when DMA transfer is complete
    //
    Interrupt_register(INT_DMA_CH1, &dmach1ISR);

    //
    // Enable specific PIE & CPU interrupts:
    // DMA interrupt - Group 7, interrupt 1
    //
    Interrupt_enable(INT_DMA_CH1);

    //
    // Stop the MCPWM clock
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Call the set up function for MCPWM 1
    //
    configureMCPWM(PWM1_BASE);

    //
    // Start the MCPWM clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize the DMA & configure DMA channels 1 & 2
    //
    initializeDMA();
    configureDMAChannels();

    //
    // Initialize results buffer
    //
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
        myADC0DataBuffer[resultsIndex] = 0;
    }

    //
    // Clearing all pending interrupt flags
    //
    DMA_clearTriggerFlag(DMA_CH1_BASE);   // DMA channel 1
    ADC_clearDMAInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    MCPWM_clearADCTriggerFlag(PWM1_BASE, MCPWM_SOC_A);    // MCPWM1 SOCA

    //
    // Enable continuous operation by setting the last SOC to re-trigger
    // the first
    //
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0,    // ADCA
                               ADC_INT_SOC_TRIGGER_ADCINT2);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Start DMA
    //
    done = 0;
    DMA_startChannel(DMA_CH1_BASE);

    //
    // Finally, enable the SOCA trigger from MCPWM. This will kick off
    // conversions at the next MCPWM event.
    //
    MCPWM_enableADCTrigger(PWM1_BASE, MCPWM_SOC_A);

    //
    // Loop until the ISR signals the transfer is complete
    //
    while(done == 0)
    {
        __asm(" NOP");
    }
    ESTOP0;
}

//
// adcA1ISR - This is called after the very first conversion and will disable
//                      the MCPWM SOC to avoid re-triggering problems.
//
#pragma CODE_SECTION(adcA1ISR, ".TI.ramfunc");
__interrupt void adcA1ISR(void)
{
    //
    // Remove MCPWM trigger
    //
    MCPWM_disableADCTrigger(PWM1_BASE, MCPWM_SOC_A);

    //
    // Disable this interrupt from happening again
    //
    Interrupt_disable(INT_ADCA1);

    //
    // Acknowledge interrupt
    //
    Interrupt_clearACKGroup(INT_myADC0_1_INTERRUPT_ACK_GROUP);
}

//
// dmach1ISR - This is called at the end of the DMA transfer, the conversions
//              are stopped by removing the trigger of the first SOC from
//              the last.
//
#pragma CODE_SECTION(dmach1ISR, ".TI.ramfunc");
__interrupt void dmach1ISR(void)
{
    //
    // Stop the ADC by removing the trigger for SOC0
    //
    ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0,
                               ADC_INT_SOC_TRIGGER_NONE);
    done = 1;

    //
    // Acknowledge interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
}

//
// configureMCPWM - Set up the MCPWM1 module so that the A output has a period
//                 of 40us with a 50% duty. The SOCA signal is coincident with
//                 the rising edge of this.
//
void configureMCPWM(uint32_t mcpwmBase)
{
    //
    // Load Mode configurations
    //
    // - Time Base Load Mode: Disabled
    // - Counter Compare Load Mode: Freeze shadow to active load
    // - Action Qualifier Load Mode: Freeze shadow to active load
    //
    MCPWM_setPeriodLoadMode(mcpwmBase, MCPWM_PERIOD_SHADOW_LOAD_DISABLE);
    MCPWM_setCounterCompareShadowLoadMode(mcpwmBase, MCPWM_COUNTER_COMPARE_1A, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(mcpwmBase, MCPWM_ACTION_QUALIFIER_1A, MCPWM_AQ_LOAD_FREEZE);

    //
    // Make the timer count up with a period of 40us
    //
    MCPWM_setTimeBaseCounterMode(mcpwmBase, MCPWM_COUNTER_MODE_UP);
    MCPWM_setTimeBasePeriodActive(mcpwmBase, 4000U);

    //
    // Set the A output on zero and reset on CMPA
    //
    MCPWM_setActionQualifierActionCompleteActive(PWM1_BASE, MCPWM_AQ_OUTPUT_1A, MCPWM_AQ_OUTPUT_HIGH_ZERO |
        MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD |
        MCPWM_AQ_OUTPUT_LOW_UP_CMPA |
        MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA |
        MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB |
        MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    //
    // Set CMPA to 20us to get a 50% duty
    //
    MCPWM_setCounterCompareActiveValue(mcpwmBase, MCPWM_COUNTER_COMPARE_1A, 2000U);

    //
    // Start ADC when timer equals zero (note: don't enable yet)
    //
    MCPWM_setADCTriggerSource(mcpwmBase, MCPWM_SOC_A, MCPWM_SOC_TBCTR_ZERO);
    MCPWM_setADCTriggerEventPrescale(mcpwmBase, MCPWM_SOC_A, 1);
}

//
// initializeDMA - Initialize DMA through hard reset
//
void initializeDMA(void)
{
    //
    // Perform a hard reset on DMA
    //
    DMA_initController();

    //
    // Allow DMA to run free on emulation suspend
    //
    DMA_setEmulationMode(DMA_EMULATION_FREE_RUN);
}

//
// configureDMAChannels - Initialize DMA ch 1 to transfer ADCA results
//
void configureDMAChannels(void)
{
    //
    // DMA channel 1 set up for ADCA
    //
    DMA_configAddresses(DMA_CH1_BASE, (uint16_t *)&myADC0DataBuffer,
                        (uint16_t *)ADCARESULT_BASE);

    //
    // Perform enough 16-word bursts to fill the results buffer. Data will be
    // transferred 32 bits at a time hence the address steps below.
    //
    DMA_configBurst(DMA_CH1_BASE, 16, 2, 2);
    DMA_configTransfer(DMA_CH1_BASE, (RESULTS_BUFFER_SIZE >> 4), -14, 2);
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_ADCA2,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_32BIT));

    DMA_enableTrigger(DMA_CH1_BASE);
    DMA_disableOverrunInterrupt(DMA_CH1_BASE);
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH1_BASE);
}

//
// End of file
//
