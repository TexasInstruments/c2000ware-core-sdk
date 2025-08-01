//#############################################################################
//
// FILE:   mcpwm_ex7_dma.c
//
// TITLE:  MCPWM Using DMA for Advanced PWM Generation
//
//! \addtogroup driver_example_list
//! <h1>MCPWM DMA Configuration for Dynamic PWM Control</h1>
//!
//! This example demonstrates how to configure MCPWM modules and DMA controllers
//! to implement dynamic updates of PWM parameters without CPU intervention:
//!
//! \b MCPWM \b Configuration:
//!  - MCPWM0 and MCPWM1 are configured for PWM output generation
//!  - MCPWM0 provides SOC trigger for DMA CH1 operations
//!  - MCPWM1 provides SOC trigger for DMA CH2 operations
//!
//! \b DMA \b Configuration:
//!  - DMA CH1 is configured to update MCPWM0 compare registers (PWM1-3 CMPAs)
//!    in burst mode, transferring 3 words per trigger
//!  - DMA CH2 is configured to update MCPWM1 compare registers (PWM1 CMPA)
//!    in burst mode, transferring 1 word per trigger
//!  - Both DMA channels operate continuously, cycling through 4 different 
//!    configurations stored in memory
//!  - The example demonstrates advanced PWM pattern generation without
//!    CPU overhead by allowing DMA to dynamically update multiple PWM
//!    parameters on each PWM period
//!
//! This technique is particularly useful for:
//!  - Generating complex PWM patterns for motor control
//!  - Creating arbitrary waveforms with precise timing
//!  - Implementing efficient, real-time PWM updates for dynamic system control
//!
//!  \b External \b Connections \n
//!     Monitor the MCPWM pins for the waveforms.
//!         Observe J4 40 - GPIO0  - myMCPWM0 Output A1
//!         Observe J4 39 - GPIO1  - myMCPWM0 Output B1
//!         Observe J4 38 - GPIO2  - myMCPWM0 Output A2
//!         Observe J4 37 - GPIO3  - myMCPWM0 Output B2
//!         Observe J4 36 - GPIO4  - myMCPWM0 Output A3
//!         Observe J4 35 - GPIO5  - myMCPWM0 Output B3
//!         Observe J4 7  - GPIO12 - myMCPWM1 Output A1
//!         Observe J2 19 - GPIO29 - myMCPWM1 Output B1
//!
//! \b Watch \b Variables \n
//! - compareConfigs_6ch[] - Array containing MCPWM0 compare values for PWM1-3 CMPAs
//! - compareConfigs_2ch[] - Array containing MCPWM1 compare values for PWM1 CMPA
//
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
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

#define MCPWM_TIMER_TBPRD    20000UL

//
// Defines
//
#define BURST_MCPWM_6CH         3              // 3 words per transfer
#define BURST_MCPWM_2CH         1              // 1 words per transfer
#define TRANSFER                4              // 4 transfers (different configs)
#define MCPWM_PERIOD            5000U           

//
// Globals
//

uint16_t compareConfigs_6ch[TRANSFER*BURST_MCPWM_6CH] = {
//  CMP_1A, CMP_2A,  CMP_3A,
    500U,   1000U,   1500U, 
    1000U,  1500U,   2000U, 
    1500U,  2000U,   2500U, 
    2000U,  2500U,   3000U, 
};

uint16_t compareConfigs_2ch[TRANSFER*BURST_MCPWM_2CH] = {
//  CMP_1A,,
    500U,  
    1000U, 
    1500U, 
    2000U, 
};

// Place buffers in GSRAM
#pragma DATA_SECTION(compareConfigs_6ch,    "ramgs0");
#pragma DATA_SECTION(compareConfigs_2ch,    "ramgs0");

//
// Function Prototypes
//
void initDMA(void);
void initMCPWM(uint32_t base);

__interrupt void dmaCh1ISR(void);
__interrupt void dmaCh2ISR(void);
__interrupt void MCPWM1ISR(void);

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
    // Disable pin locks and enable internal pull ups.
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
    // Assign the interrupt service routines to MCPWM interrupts
    //
    Interrupt_register(INT_DMA_CH1, &dmaCh1ISR);
    Interrupt_register(INT_DMA_CH2, &dmaCh2ISR);

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure MCPWM and Input X-BAR Pins
    //
    Board_init();
    initDMA();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // init the DMA interrupts
    //
    Interrupt_enable(INT_DMA_CH1);
    Interrupt_enable(INT_DMA_CH2);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    EALLOW;
    DMA_startChannel(DMA_CH1_BASE);
    DMA_startChannel(DMA_CH2_BASE);

    //
    // IDLE loop. Just sit and loop forever (optional):
    //

    for(;;)
    {

    }
}


//
// DMA setup channels.
//
void initDMA()
{
    //
    // Initialize DMA
    //
    DMA_initController();

    //
    // DMA CH1
    //
    DMA_configAddresses(DMA_CH1_BASE, (uint16_t *)(myMCPWM0_BASE + MCPWM_O_PWM1_CMPAS), compareConfigs_6ch);
    
    //
    // The CMPAS registers are separated by 50 words in the MCPWM memory map.
    //
    uint16_t cmp_step_16_bit = (MCPWM_O_PWM2_CMPAS - MCPWM_O_PWM1_CMPAS); 

    DMA_configBurst(DMA_CH1_BASE, BURST_MCPWM_6CH, 1, cmp_step_16_bit);
    //
    //
    DMA_configTransfer(DMA_CH1_BASE, TRANSFER, 1, (int16_t) ((1-BURST_MCPWM_6CH)*cmp_step_16_bit));
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_MCPWM1SOCA, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA Ch1 interrupts
    //
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH1_BASE);
    DMA_enableTrigger(DMA_CH1_BASE);

    //
    // DMA CH2
    //
    DMA_configAddresses(DMA_CH2_BASE, (uint16_t *)(myMCPWM1_BASE + MCPWM_O_PWM1_CMPAS),
                        compareConfigs_2ch);
    DMA_configBurst(DMA_CH2_BASE, BURST_MCPWM_2CH, 1, 1-BURST_MCPWM_2CH);
    DMA_configTransfer(DMA_CH2_BASE, TRANSFER, 1, 1-BURST_MCPWM_2CH);
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_MCPWM3SOCA, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA Ch2 interrupts
    //
    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH2_BASE);
    DMA_enableTrigger(DMA_CH2_BASE);
}

//
// DMA Channel 1 ISR
//
__interrupt void dmaCh1ISR(void)
{

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    return;
}

//
// DMA Channel 6 ISR
//
__interrupt void dmaCh2ISR(void)
{

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
    return;
}
